/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file builtin_raw_subscriber.cpp
 * @brief This file tests and demonstrates subscribing builtin raw types.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-12
 */

#include <opendds_wrapper/opendds_bus.h>

#include <unistd.h>
#include <iostream>

using BusType = opendds_wrapper::DdsBus;

void StringCallback(BusType::BuiltinMessageType::String const& sample)
{
    std::cout << sample.value << std::endl;
}

void Uint64Callback(BusType::BuiltinMessageType::Uint64 const& sample)
{
    std::cout << "uint64 callback: " << sample.value << std::endl;
}

void Uint32Callback(BusType::BuiltinMessageType::Uint32 const& sample)
{
    std::cout << "uint32 callback: " << sample.value << std::endl;
}

void Uint16Callback(BusType::BuiltinMessageType::Uint16 const& sample)
{
    std::cout << "uint16 callback: " << sample.value << std::endl;
}

void Uint8Callback(BusType::BuiltinMessageType::Uint8 const& sample)
{
    std::cout << "uint8 callback: " << static_cast<uint32_t>(sample.value) << std::endl;
}

void Float32Callback(BusType::BuiltinMessageType::Float32 const& sample)
{
    std::cout << "float32 callback: " << sample.value << std::endl;
}

void Float64Callback(BusType::BuiltinMessageType::Float64 const& sample)
{
    std::cout << "float64 callback: " << sample.value << std::endl;
}

void BufferCallback(BusType::BuiltinMessageType::Buffer const& sample)
{
    std::cout << "buffer callback. buffer of size " << sample.value.length() << ": " << std::hex;
    for (size_t i = 0; i < sample.value.length(); ++i)
    {
        std::cout << static_cast<uint32_t>(sample.value[i]) << ", ";
    }
    std::cout << std::dec << std::endl;
}

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, std::string("builtin_raw_subscriber"));
    signal(SIGINT, BusType::SignalHandler);
    BusType bus(100, std::string("Data"));

    std::cout << "Bus name = " << bus.GetId() << std::endl;

    auto reader1 = bus.AddReader<BusType::BuiltinMessageType::String>("example_string_topic");
    reader1.SetOnDataAvailableCallback(StringCallback);

    auto reader2 = bus.AddReader<BusType::BuiltinMessageType::Uint64>("example_uint64_topic");
    reader2.SetOnDataAvailableCallback(Uint64Callback);

    auto reader3 = bus.AddReader<BusType::BuiltinMessageType::Uint32>("example_uint32_topic");
    reader3.SetOnDataAvailableCallback(Uint32Callback);

    auto reader4 = bus.AddReader<BusType::BuiltinMessageType::Uint16>("example_uint16_topic");
    reader4.SetOnDataAvailableCallback(Uint16Callback);

    auto reader5 = bus.AddReader<BusType::BuiltinMessageType::Uint8>("example_uint8_topic");
    reader5.SetOnDataAvailableCallback(Uint8Callback);

    auto reader6 = bus.AddReader<BusType::BuiltinMessageType::Float32>("example_float32_topic");
    reader6.SetOnDataAvailableCallback(Float32Callback);

    auto reader7 = bus.AddReader<BusType::BuiltinMessageType::Float64>("example_float64_topic");
    reader7.SetOnDataAvailableCallback(Float64Callback);

    auto reader8 = bus.AddReader<BusType::BuiltinMessageType::Buffer>("example_buffer_topic");
    reader8.SetOnDataAvailableCallback(BufferCallback);

    BusType::AsyncSpin(1U);

    while (BusType::IsRunning())
    {
        auto topics = bus.GetTopicList();
        std::cout << std::endl
                  << "################################################################################" << std::endl;
        for (auto& t : topics)
        {
            std::cout << t.topic_name << std::endl;
            std::cout << t.type_name << std::endl;
        }
        std::cout << std::endl
                  << "################################################################################" << std::endl;

        sleep(10);
        std::cout << std::endl
                  << "################################################################################" << std::endl;
        auto nodes = bus.GetNodeList();
        for (auto& n : nodes)
        {
            std::cout << n << std::endl;
        }
        std::cout << std::endl
                  << "################################################################################" << std::endl;
        sleep(10);
    }

    return 0;
}
