/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file interface.h
 * @brief define the device interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-08-19
 */

#ifndef _HOLO_SENSORS_COMMON_INTERFACE_H
#define _HOLO_SENSORS_COMMON_INTERFACE_H

#include <holo/core/types.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/format/someip.h>
#include <functional>

namespace holo
{
namespace sensors
{
namespace common
{
template <typename DataType>
class InterfaceT
{
public:
    using DataCallbackType     = std::function<void(const DataType&)>;
    using ExtendedCallbackType = std::function<void(const DataType&, void*)>;

    InterfaceT() : data_callback_(nullptr), extended_callback_(nullptr)
    {
    }

    virtual ~InterfaceT() = default;

    void InstallCallback(const DataCallbackType& callback) noexcept
    {
        data_callback_ = callback;
    }

    void InstallCallback(const ExtendedCallbackType& callback) noexcept
    {
        extended_callback_ = callback;
    }

    // bool_t ParseData(const uint8_t* data, int32_t size, void* args = nullptr)
    // {
    //     DataType packet;
    //     uint32_t deserialized = packet.Deserialize(data, static_cast<uint32_t>(size));
    //     if (deserialized == 0)
    //     {
    //         return false;
    //     }
    //     if (nullptr != data_callback_)
    //     {
    //         data_callback_(packet);
    //     }
    //     if (nullptr != extended_callback_)
    //     {
    //         extended_callback_(packet, args);
    //     }
    //     return true;
    // }

    bool_t ParseData(const uint8_t* data, int32_t size, void* args = nullptr)
    {
        bool_t  retcode = false;
        int32_t offset  = 0;
        while (offset < size)
        {
            DataType packet;
            uint32_t deserialized = packet.Deserialize(data + offset, static_cast<uint32_t>(size) - offset);
            if (deserialized == 0)
            {
                break;
            }
            offset += deserialized;
            if (nullptr != data_callback_)
            {
                data_callback_(packet);
            }
            if (nullptr != extended_callback_)
            {
                extended_callback_(packet, args);
            }
            retcode = true;
        }
        return retcode;
    }

    // virtual int32_t Send(const DataType&) = 0;

protected:
    DataCallbackType     data_callback_;
    ExtendedCallbackType extended_callback_;
};

template <>
class InterfaceT<holo::sensors::format::HoloCanPacket>
{
public:
    using DataCallbackType = std::function<void(const holo::sensors::format::HoloCanPacket&)>;

    InterfaceT() : data_callback_(nullptr)
    {
    }

    virtual ~InterfaceT() = default;

    void InstallCallback(const DataCallbackType& callback) noexcept
    {
        data_callback_ = callback;
    }

    bool_t ParseData(const uint8_t* data, int32_t size, void* args = nullptr)
    {
        holo::sensors::format::HoloCanPacket message;
        size_t                               n = size / message.GetSerializedSize();
        for (size_t i = 0; i < n; i++)
        {
            (void)message.Deserialize(data + message.GetSerializedSize() * i, message.GetSerializedSize());
            if (nullptr != data_callback_)
            {
                data_callback_(message);
            }
        }
        (void)args;
        return true;
    }

    // virtual int32_t Send(const DataType&) = 0;

protected:
    DataCallbackType data_callback_;
};

}  // namespace common
}  // namespace sensors
}  // namespace holo

#endif
