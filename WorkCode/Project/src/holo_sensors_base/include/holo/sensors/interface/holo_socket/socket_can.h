/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file socket_can_interface.h
 * @brief define the socket can interface class
 * @author wujunfeng@holomatic.com
 * @date 2021/11/09
 */

#ifndef SOCKET_CAN_INTERFACE_H
#define SOCKET_CAN_INTERFACE_H

#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>
#include <vector>

namespace holo
{
namespace sensors
{
namespace interface
{
class SocketCan
{
public:
    SocketCan()  = default;
    ~SocketCan() = default;

    bool    Init(const std::string& canDevice);
    bool    SetRecvTimeout(const struct timeval& tv) const;
    bool    SetCanFiLter(const struct can_filter& filter) const;
    bool    SetCanFilters(const std::vector<can_filter>& filters) const;
    int32_t ReadCan(canfd_frame& receiveFrame, struct timeval& tstamp, int32_t& readBytes) const;
    int32_t WriteCan(const can_frame& sendFrame) const;
    int32_t WriteCanfd(const canfd_frame& sendFrame) const;
    void    CloseSocketCan();

private:
    int32_t m_sockCan = -1;
};
}
}
}  // namespace holo_cmw

#endif
