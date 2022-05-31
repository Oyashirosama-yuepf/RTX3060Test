/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file builtin_publisher.cpp
 * @brief This file tests and demonstrates publishing builtin types.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-12
 */

#include <opendds_wrapper/opendds_bus.h>

#include <unistd.h>
#include <iostream>

using BusType = opendds_wrapper::DdsBus;

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, std::string("builtin_publisher"));
    signal(SIGINT, BusType::SignalHandler);
    BusType bus(100, std::string("Data"));
    std::cout << "Bus name = " << bus.GetId() << std::endl;

    auto writer1  = bus.AddWriter<std::string>("example_string_topic");
    auto writer2  = bus.AddWriter<uint64_t, BusType::DefaultConversionTraitsType<uint64_t>>("example_uint64_topic");
    auto writer3  = bus.AddWriter<int64_t>("example_int64_topic");
    auto writer4  = bus.AddWriter<uint32_t>("example_uint32_topic");
    auto writer5  = bus.AddWriter<int32_t>("example_int32_topic");
    auto writer6  = bus.AddWriter<uint16_t>("example_uint16_topic");
    auto writer7  = bus.AddWriter<int16_t>("example_int16_topic");
    auto writer8  = bus.AddWriter<uint8_t>("example_uint8_topic");
    auto writer9  = bus.AddWriter<int8_t>("example_int8_topic");
    auto writer10 = bus.AddWriter<float>("example_float32_topic");
    auto writer11 = bus.AddWriter<double, BusType::MemcpyTraitsType<double>>("example_float64_topic");
    auto writer12 = bus.AddWriter<uint8_t*>("example_buffer_topic");
    auto writer13  = bus.AddWriter<int64_t>("example_int64_topic2");

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
    writer9.WaitSubscription();
    std::cout << "writer9 subscritpion matched" << std::endl;
    writer10.WaitSubscription();
    std::cout << "writer10 subscritpion matched" << std::endl;
    writer11.WaitSubscription();
    std::cout << "writer11 subscritpion matched" << std::endl;
    writer12.WaitSubscription();
    std::cout << "writer12 subscritpion matched" << std::endl;

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
    std::cout << "Writer9 topic name: " << writer9.GetTopicName() << std::endl;
    std::cout << "Writer9 topic type: " << writer9.GetTypeName() << std::endl;
    std::cout << "Writer10 topic name: " << writer10.GetTopicName() << std::endl;
    std::cout << "Writer10 topic type: " << writer10.GetTypeName() << std::endl;
    std::cout << "Writer11 topic name: " << writer11.GetTopicName() << std::endl;
    std::cout << "Writer11 topic type: " << writer11.GetTypeName() << std::endl;
    std::cout << "Writer12 topic name: " << writer12.GetTopicName() << std::endl;
    std::cout << "Writer12 topic type: " << writer12.GetTypeName() << std::endl;

    bus.DeleteWriter<int64_t>(writer13);

    size_t i = 0U;
    while (BusType::IsRunning())
    {
        std::string sample("Hello World!");
        writer1.Write(sample);
        writer2.Write(static_cast<uint64_t>(i));
        writer3.Write(-static_cast<int64_t>(i));
        writer4.Write(static_cast<uint32_t>(i));
        writer5.Write(-static_cast<int32_t>(i));
        writer6.Write(static_cast<uint16_t>(i));
        writer7.Write(-static_cast<int16_t>(i));
        writer8.Write(static_cast<uint8_t>(i));
        writer9.Write(-static_cast<int8_t>(i));
        writer10.Write(static_cast<float>(i));
        writer11.Write(static_cast<double>(i));
        uint8_t buffer[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
        writer12.Write(buffer, 8U);

        ++i;
        usleep(1000000);
    }

    return 0;
}
