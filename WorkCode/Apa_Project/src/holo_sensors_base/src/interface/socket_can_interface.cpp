/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_interface.h
 * @brief The cpp file which realized mdc610 interface
 * @author wujunfeng@holomatic.com
 * @date 2021/11/09
 */

#include <holo/sensors/format/holocan.h>
#include <holo/sensors/interface/holo_socket/socket.h>
#include <holo/sensors/interface/socket_can_interface.h>

namespace holo
{
namespace sensors
{
namespace interface
{
const static uint32_t    CAN_CHANNEL_NUM                 = 12U;
const static std::string can_name_array[CAN_CHANNEL_NUM] = {"can0", "can1", "can2", "can3", "can4",  "can5",
                                                            "can6", "can7", "can8", "can9", "can10", "can11"};
template <typename T>
void SocketCanInterface<T>::Init(const std::string canname, InterfaceType type)
{
    if (!socket_can_.Init(canname))
    {
        LOG(ERROR) << "Init sockect can failed!";
        return;
    }
    channel_ = ConvertChannel(canname);
    if (channel_ < 0)
    {
        LOG(ERROR) << "Not supported canname!";
        return;
    }
    timeval tv = {2, 0};
    socket_can_.SetRecvTimeout(tv);

    if ((type == InterfaceType::SEND_AND_RECEIVE) || (type == InterfaceType::RECEIVE_ONLY))
    {
        receive_thread_ = std::shared_ptr<std::thread>(new std::thread(std::bind(&SocketCanInterface::Thread, this)));
    }
}

template <typename T>
int32_t SocketCanInterface<T>::ConvertChannel(const std::string& canname)
{
    for (uint32_t i = 0; i < CAN_CHANNEL_NUM; i++)
    {
        if (canname == can_name_array[i])
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
void SocketCanInterface<T>::Thread()
{
    while (running_)
    {
        canfd_frame    receiveFrame;
        struct timeval tstamp;
        int32_t        readBytes = 0;
        const auto     ret       = socket_can_.ReadCan(receiveFrame, tstamp, readBytes);

        if (ret == -1)
        {
            // waiting data time out...
            continue;
        }
        if ((readBytes != sizeof(can_frame)) && (readBytes != sizeof(canfd_frame)))
        {
            LOG(ERROR) << "fail CAN frame format";
            continue;
        }
        T output;
        Convert(receiveFrame, output);
        InterfaceT<T>::data_callback_(output);
    }
    socket_can_.CloseSocketCan();
}
template <typename T>
void SocketCanInterface<T>::Convert(const canfd_frame& input, T& output)
{
    output.SetChannel(static_cast<uint8_t>(channel_));
    output.SetId(input.can_id);
    output.SetDlc(input.len);
    memcpy(output.GetData(), &input.data[0], output.GetDlc());
}

template <>
void SocketCanInterface<holo::sensors::format::HoloCanPacket>::Send(const holo::sensors::format::HoloCanPacket& data)
{
    can_frame frame;
    frame.can_id  = data.GetId();
    frame.can_dlc = data.GetDlc();
    memcpy(&frame.data, data.GetData(), data.GetDlc());
    socket_can_.WriteCan(frame);
}

template <>
void SocketCanInterface<holo::sensors::format::HoloCanfdPacket>::Send(
    const holo::sensors::format::HoloCanfdPacket& data)
{
    canfd_frame frame;
    frame.can_id = data.GetId();
    frame.len    = data.GetDlc();
    memcpy(&frame.data, data.GetData(), data.GetDlc());
    socket_can_.WriteCanfd(frame);
}

template class SocketCanInterface<holo::sensors::format::HoloCanPacket>;
template class SocketCanInterface<holo::sensors::format::HoloCanfdPacket>;
}
}
}  // namespace holo_cmw
