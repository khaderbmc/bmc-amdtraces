#include <boost/asio.hpp>
#include <cstdio>
#include <iostream>
#include <phosphor-logging/log.hpp>
#include <sdbusplus/asio/connection.hpp>
#include <sdbusplus/asio/object_server.hpp>
#include <sdbusplus/server.hpp>
#include <xyz/openbmc_project/Traces/Tbai/server.hpp>

extern "C" {
#include "apml.h"
#include "esmi_cpuid_msr.h"
#include "esmi_mailbox.h"
#include "esmi_mailbox_nda.h"
#include "esmi_rmi.h"
}

static constexpr auto objectPath = "/xyz/openbmc_project/Traces";

using Base = sdbusplus::xyz::openbmc_project::Traces::server::Tbai;
namespace fs = std::filesystem;

/** @class Manager
 *
 *  @brief Implements the Scandump Manager
 */
class Manager : public Base
{

  public:
    Manager() = delete;
    ~Manager() = default;
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    Manager(Manager&&) = delete;
    Manager& operator=(Manager&&) = delete;

    Manager(sdbusplus::asio::object_server& objectServer,
            std::shared_ptr<sdbusplus::asio::connection>& systemBus);

    std::uint32_t getPowerLimit() override;

  private:
    sdbusplus::asio::object_server& objServer;
    std::shared_ptr<sdbusplus::asio::connection>& systemBus;
    sdbusplus::bus::bus bus;
};
