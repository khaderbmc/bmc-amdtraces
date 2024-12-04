#include "trace.hpp"

static constexpr auto service = "xyz.openbmc_project.Traces";

int main()
{
    boost::asio::io_service io;

    auto systemBus = std::make_shared<sdbusplus::asio::connection>(io);

    systemBus->request_name(service);

    sdbusplus::asio::object_server objectServer(systemBus);

    Manager manager(objectServer, systemBus);

    io.run();

    return 0;
}
