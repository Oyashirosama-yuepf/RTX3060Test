#include <opendds_wrapper/opendds_bus.h>

#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using BusType = opendds_wrapper::DdsBus;

int main(int argc, char** argv)
{
    std::cout << "./heartbeat_publisher domain_id value" << '\n';

    if (argc != 3)
    {
        std::cout << "param error" << '\n';
        return 0;
    }

    BusType::Initialize(argc, argv, std::string("heartbeat_publisher"));
    signal(SIGINT, BusType::SignalHandler);
    int      domain_id = std::atoi(argv[1]);
    uint32_t value     = static_cast<uint32_t>(std::atoi(argv[2]));

    BusType bus(domain_id, "");
    auto    writer = bus.AddWriter<uint32_t>("/holo/heartbeat_bag");

    std::cout << "domain id: " << domain_id << std::endl;
    std::cout << "topic name: " << writer.GetTopicName() << std::endl;
    std::cout << "topic type: " << writer.GetTypeName() << std::endl;

    while (BusType::IsRunning())
    {
        writer.Write(value);
        std::cout << "pub value: " << value << std::endl;
        usleep(100000);
    }

    return 0;
}
