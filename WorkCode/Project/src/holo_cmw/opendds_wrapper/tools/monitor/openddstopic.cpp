#include <opendds_wrapper/opendds_bus.h>

#include <cstdlib>
#include <cstring>
#include <thread>
#include "cxxopts.hpp"

#include <unistd.h>

#include "Description.h"
#include "Storage.h"

using BusType = opendds_wrapper::DdsBus;

int ParseDomainId(char* s)
{
    for (char* p = s; *p != 0; ++p)
    {
        if (!std::isdigit(*p))
        {
            throw std::exception();
        }
    }
    return std::atoi(s);
}

static char const* const HELP_STRING = "\
openddsnode is a command-line tool for printing information about opendds nodes\n\
\n\
Usage: openddsnode [domain_id] [command]\n\
\n\
Commands:\n\
    list List active nodes\n\
";

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        std::cout << HELP_STRING << std::endl;
        return 0;
    }

    int domain_id = ParseDomainId(argv[1]);

    BusType::Initialize(argc, argv, "monitor");
    signal(SIGINT, BusType::SignalHandler);

    BusType bus(domain_id);
    Storage db(bus);

    sleep(3);
    db.ProcessOnce();

    TopologyDescription topo("Participants");

    db.GetTopicDescriptions(topo);
    std::cout << topo.Format();

    return 0;
}
