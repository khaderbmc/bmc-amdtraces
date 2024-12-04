#include "trace.hpp"

Manager::Manager(sdbusplus::asio::object_server& objectServer,
                 std::shared_ptr<sdbusplus::asio::connection>& systemBus) :
    sdbusplus::xyz::openbmc_project::Traces::server::Tbai(*systemBus,
							  objectPath),
    objServer(objectServer), systemBus(systemBus),
    bus(sdbusplus::bus::new_default())
{
}

std::uint32_t Manager::getPowerLimit()
{
    oob_status_t ret = OOB_MAILBOX_CMD_UNKNOWN;
    uint8_t soc_num = 0;
    std::uint32_t state;
    uint16_t retries = 0;

    while (ret != OOB_SUCCESS)
    {
	ret = read_socket_power_limit(soc_num, &status);

        if (ret != OOB_SUCCESS)
        {
            sd_journal_print(LOG_ERR,
                             "Failed to get ras mdc sdu action Err[%d]: %s \n",
                             ret, esmi_get_err_msg(ret));
            break;
        }
    }
    return state;
}

