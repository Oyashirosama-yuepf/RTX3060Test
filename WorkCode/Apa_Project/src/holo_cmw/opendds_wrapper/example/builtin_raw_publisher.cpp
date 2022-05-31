/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file builtin_raw_publisher.cpp
 * @brief This file tests and demonstrates publishing builtin raw types.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-12
 */

#include <opendds_wrapper/opendds_bus.h>

#include <unistd.h>
#include <iostream>

using BusType = opendds_wrapper::DdsBus;

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, std::string("builtin_raw_publisher"));
    signal(SIGINT, BusType::SignalHandler);
    BusType bus(100, std::string("Data"));
    std::cout << "Bus name = " << bus.GetId() << std::endl;

    auto writer1 = bus.AddWriter<BusType::BuiltinMessageType::String>("example_string_topic");
    auto writer2 = bus.AddWriter<BusType::BuiltinMessageType::Uint64>("example_uint64_topic");
    auto writer3 = bus.AddWriter<BusType::BuiltinMessageType::Uint32>("example_uint32_topic");
    auto writer4 = bus.AddWriter<BusType::BuiltinMessageType::Uint16>("example_uint16_topic");
    auto writer5 = bus.AddWriter<BusType::BuiltinMessageType::Uint8>("example_uint8_topic");
    auto writer6 = bus.AddWriter<BusType::BuiltinMessageType::Float32>("example_float32_topic");
    auto writer7 = bus.AddWriter<BusType::BuiltinMessageType::Float64>("example_float64_topic");
    auto writer8 = bus.AddWriter<BusType::BuiltinMessageType::Buffer>("example_buffer_topic");

    writer1.WaitSubscription();
    std::cout << "writer1 subscritpion matched" << std::endl;
    writer2.WaitSubscription();
    std::cout << "writer2 subscritpion matched" << std::endl;
    writer3.WaitSubscription();
    std::cout << "writer3 subscritpion matched" << std::endl;
    writer4.WaitSubscription();
    std::cout << "writer4 subscritpion matched" << std::endl;
    writer5.WaitSubscription();
    std::cout << "writer5 subscritpion matched" << std::endl;
    writer6.WaitSubscription();
    std::cout << "writer6 subscritpion matched" << std::endl;
    writer7.WaitSubscription();
    std::cout << "writer7 subscritpion matched" << std::endl;
    writer8.WaitSubscription();
    std::cout << "writer8 subscritpion matched" << std::endl;

    std::cout << "All writer subscritpion matched" << std::endl;

    std::cout << "Writer1 topic name: " << writer1.GetTopicName() << std::endl;
    std::cout << "Writer1 topic type: " << writer1.GetTypeName() << std::endl;
    std::cout << "Writer2 topic name: " << writer2.GetTopicName() << std::endl;
    std::cout << "Writer2 topic type: " << writer2.GetTypeName() << std::endl;
    std::cout << "Writer3 topic name: " << writer3.GetTopicName() << std::endl;
    std::cout << "Writer3 topic type: " << writer3.GetTypeName() << std::endl;
    std::cout << "Writer4 topic name: " << writer4.GetTopicName() << std::endl;
    std::cout << "Writer4 topic type: " << writer4.GetTypeName() << std::endl;
    std::cout << "Writer5 topic name: " << writer5.GetTopicName() << std::endl;
    std::cout << "Writer5 topic type: " << writer5.GetTypeName() << std::endl;
    std::cout << "Writer6 topic name: " << writer6.GetTopicName() << std::endl;
    std::cout << "Writer6 topic type: " << writer6.GetTypeName() << std::endl;
    std::cout << "Writer7 topic name: " << writer7.GetTopicName() << std::endl;
    std::cout << "Writer7 topic type: " << writer7.GetTypeName() << std::endl;
    std::cout << "Writer8 topic name: " << writer8.GetTopicName() << std::endl;
    std::cout << "Writer8 topic type: " << writer8.GetTypeName() << std::endl;

    size_t i = 0U;
    while (BusType::IsRunning())
    {
        writer1.Write(BusType::BuiltinMessageType::String{"HelloWorld!"});
        writer2.Write(BusType::BuiltinMessageType::Uint64{static_cast<uint64_t>(i)});
        writer3.Write(BusType::BuiltinMessageType::Uint32{static_cast<uint32_t>(i)});
        writer4.Write(BusType::BuiltinMessageType::Uint16{static_cast<uint16_t>(i)});
        writer5.Write(BusType::BuiltinMessageType::Uint8{static_cast<uint8_t>(i)});
        writer6.Write(BusType::BuiltinMessageType::Float32{static_cast<float>(i)});
        writer7.Write(BusType::BuiltinMessageType::Float64{static_cast<double>(i)});

        uint8_t buffer[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

        BusType::BuiltinMessageType::Buffer message;
        message.value.length(8U);
        std::memcpy(&message.value[0], buffer, 8U);
        writer8.Write(message);

        ++i;
        usleep(1000000);
    }

    return 0;
}
