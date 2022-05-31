/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_can_interface.h
 * @brief define the mdc610 interface class
 * @author wujunfeng@holomatic.com
 * @date 2021/11/09
 */

#ifndef _MDC610_CAN_INTERFACE_H_
#define _MDC610_CAN_INTERFACE_H_

#include <holo/common/odometry.h>
#include <holo/sensors/common/interface.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/interface/holo_socket/socket_can.h>
#include <string>
#include <thread>

namespace holo
{
namespace sensors
{
namespace interface
{
using holo::sensors::common::InterfaceT;

enum class InterfaceType : uint8_t
{
    SEND_AND_RECEIVE = 0U,
    SEND_ONLY        = 1U,
    RECEIVE_ONLY     = 2U,
};

template <typename T>
class SocketCanInterface : public InterfaceT<T>
{
public:
    using HoloCanPacketType      = holo::sensors::format::HoloCanPacket;
    using HoloCanFdPacketType    = holo::sensors::format::HoloCanfdPacket;
    using CanPackageCallbackType = std::function<void(const HoloCanPacketType&)>;

    SocketCanInterface() : channel_(-1), receive_thread_(nullptr), running_(true)
    {
    }
    ~SocketCanInterface()
    {
        running_ = false;
        if (receive_thread_ && receive_thread_->joinable())
        {
            receive_thread_->join();
        }
    }

    void    Init(const std::string canname, InterfaceType type);
    void    Send(const T& data);

private:
    int32_t ConvertChannel(const std::string& canname);
    void    Thread();
    void    Convert(const canfd_frame& input, T& output);

private:
    SocketCan                    socket_can_;
    int32_t                      channel_;
    std::shared_ptr<std::thread> receive_thread_;
    bool                         running_;
};
}
}
}  // namespace holo_cmw

#endif
