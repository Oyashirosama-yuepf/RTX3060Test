/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file builtin_subscriber.cpp
 * @brief This file tests and demonstrates subscribing builtin types.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-12
 */

#include <opendds_wrapper/opendds_bus.h>

#include <unistd.h>
#include <iostream>

using BusType = opendds_wrapper::DdsBus;

void StringCallback(std::string const& sample)
{
    std::cout << sample << std::endl;
}

void Uint64Callback(uint64_t sample)
{
    std::cout << "uint64 callback: " << sample << std::endl;
}

void Int64Callback(int64_t sample)
{
    std::cout << "int64 callback: " << sample << std::endl;
}

void Uint32Callback(uint32_t sample)
{
    std::cout << "uint32 callback: " << sample << std::endl;
}

void Int32Callback(int32_t sample)
{
    std::cout << "int32 callback: " << sample << std::endl;
}

void Uint16Callback(uint16_t sample)
{
    std::cout << "uint16 callback: " << sample << std::endl;
}

void Int16Callback(int16_t sample)
{
    std::cout << "int16 callback: " << sample << std::endl;
}

void Uint8Callback(uint8_t sample)
{
    std::cout << "uint8 callback: " << static_cast<uint32_t>(sample) << std::endl;
}

void Int8Callback(int8_t sample)
{
    std::cout << "int8 callback: " << static_cast<int32_t>(sample) << std::endl;
}

void Float32Callback(float sample)
{
    std::cout << "float32 callback: " << sample << std::endl;
}

void Float64Callback(double sample)
{
    std::cout << "float64 callback: " << sample << std::endl;
}

void BufferCallback(uint8_t const* buffer, size_t size)
{
    std::cout << "buffer callback. buffer of size " << size << ": " << std::hex;
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << static_cast<uint32_t>(buffer[i]) << ", ";
    }
    std::cout << std::dec << std::endl;
}

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, std::string("builtin_subscriber"));
    signal(SIGINT, BusType::SignalHandler);
    BusType bus(100, std::string("Data"));

    std::cout << "Bus name = " << bus.GetId() << std::endl;

    auto reader1 = bus.AddReader<std::string>("example_string_topic");
    reader1.SetOnDataAvailableCallback(StringCallback);

    auto reader2 = bus.AddReader<uint64_t, BusType::DefaultConversionTraitsType<uint64_t>>("example_uint64_topic");
    reader2.SetOnDataAvailableCallback(Uint64Callback);

    auto reader3 = bus.AddReader<int64_t>("example_int64_topic");
    reader3.SetOnDataAvailableCallback(Int64Callback);

    auto reader4 = bus.AddReader<uint32_t>("example_uint32_topic");
    reader4.SetOnDataAvailableCallback(Uint32Callback);

    auto reader5 = bus.AddReader<int32_t>("example_int32_topic");
    reader5.SetOnDataAvailableCallback(Int32Callback);

    auto reader6 = bus.AddReader<uint16_t>("example_uint16_topic");
    reader6.SetOnDataAvailableCallback(Uint16Callback);

    auto reader7 = bus.AddReader<int16_t>("example_int16_topic");
    reader7.SetOnDataAvailableCallback(Int16Callback);

    auto reader8 = bus.AddReader<uint8_t>("example_uint8_topic");
    reader8.SetOnDataAvailableCallback(Uint8Callback);

    auto reader9 = bus.AddReader<int8_t>("example_int8_topic");
    reader9.SetOnDataAvailableCallback(Int8Callback);

    auto reader10 = bus.AddReader<float>("example_float32_topic");
    reader10.SetOnDataAvailableCallback(Float32Callback);

    auto reader11 = bus.AddReader<double, BusType::MemcpyTraitsType<double>>("example_float64_topic");
    reader11.SetOnDataAvailableCallback(Float64Callback);

    auto reader12 = bus.AddReader<uint8_t*>("example_buffer_topic");
    reader12.SetOnDataAvailableCallback(BufferCallback);

    auto reader13 = bus.AddReader<int64_t>("example_int64_topic2");
    reader13.SetOnDataAvailableCallback(Int64Callback);

    bus.DeleteReader(reader13);

    BusType::AsyncSpin(1);

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
        auto nodes = bus.GetNodeList();
        std::cout << std::endl
                  << "################################################################################" << std::endl;
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
