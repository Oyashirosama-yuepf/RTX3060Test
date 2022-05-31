/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file socket_can_interface.cpp
 * @brief The cpp file which realized socket can interface
 * @author wujunfeng@holomatic.com
 * @date 2021/11/09
 */

#include <holo/sensors/interface/holo_socket/socket_can.h>

#include <cstring>
namespace holo
{
namespace sensors
{
namespace interface
{
const static int32_t sendBuffLen = 32768;
bool                 SocketCan::Init(const std::string& canDevice)
{
    m_sockCan = socket(PF_CAN, SOCK_RAW, CAN_RAW);  // create socket
    if (m_sockCan < 0)
    {
        return false;
    }
    struct ifreq ifr = {};
    int32_t      ret;
    strncpy(ifr.ifr_name, canDevice.c_str(), sizeof(ifr.ifr_name));
    ret = ioctl(m_sockCan, SIOCGIFINDEX, &ifr);  // specify can device
    if (ret < 0)
    {
        CloseSocketCan();
        return false;
    }

    const int32_t canFdFlag = 1;
    ret = setsockopt(m_sockCan, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &canFdFlag, static_cast<socklen_t>(sizeof(canFdFlag)));
    if (ret < 0)
    {
        CloseSocketCan();
        return false;
    }

    struct sockaddr_can addr = {};
    addr.can_family          = static_cast<__kernel_sa_family_t>(AF_CAN);
    addr.can_ifindex         = ifr.ifr_ifindex;
    // Bind socket to can device
    ret = bind(m_sockCan, reinterpret_cast<sockaddr*>(&addr), static_cast<socklen_t>(sizeof(addr)));
    if (ret < 0)
    {
        CloseSocketCan();
        return false;
    }

    ret = setsockopt(m_sockCan, SOL_SOCKET, SO_TIMESTAMP, &sendBuffLen, static_cast<socklen_t>(sizeof(sendBuffLen)));
    if (ret < 0)
    {
        CloseSocketCan();
        return false;
    }

    return true;
}

bool SocketCan::SetRecvTimeout(const struct timeval& tv) const
{
    const int32_t ret = setsockopt(m_sockCan, SOL_SOCKET, SO_RCVTIMEO, &tv, static_cast<socklen_t>(sizeof(tv)));
    if (ret < 0)
    {
        return false;
    }
    return true;
}

int32_t SocketCan::ReadCan(canfd_frame& receiveFrame, struct timeval& tstamp, std::int32_t& readBytes) const
{
    iovec iov = {.iov_base = static_cast<void*>(&receiveFrame), .iov_len = sizeof(receiveFrame)};

    const std::uint32_t controlSize = 512U;
    char                controlBuf[CMSG_SPACE(controlSize)];
    msghdr              canMsg = {
        .msg_name       = nullptr,
        .msg_namelen    = 0U,
        .msg_iov        = &iov,
        .msg_iovlen     = 1U,
        .msg_control    = controlBuf,
        .msg_controllen = sizeof(controlBuf),
        .msg_flags      = 0,
    };

    readBytes = static_cast<int32_t>(recvmsg(m_sockCan, &canMsg, 0));
    if (readBytes < 0)
    {
        return -1;
    }
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&canMsg);
    if (cmsg != nullptr)
    {
        tstamp = *(reinterpret_cast<timeval*>(CMSG_DATA(cmsg)));
    }
    return 0;
}

int32_t SocketCan::WriteCan(const can_frame& sendFrame) const
{
    const auto bytes = static_cast<int32_t>(write(m_sockCan, &sendFrame, sizeof(sendFrame)));
    if (bytes != static_cast<int32_t>(sizeof(sendFrame)))
    {
        return -1;
    }
    return 0;
}

int32_t SocketCan::WriteCanfd(const canfd_frame& sendFrame) const
{
    const auto bytes = static_cast<int32_t>(write(m_sockCan, &sendFrame, sizeof(sendFrame)));
    if (bytes != static_cast<int32_t>(sizeof(sendFrame)))
    {
        return -1;
    }
    return 0;
}

bool SocketCan::SetCanFiLter(const struct can_filter& filter) const
{
    const auto    filterSize = static_cast<socklen_t>(sizeof(filter));
    const int32_t ret        = setsockopt(m_sockCan, SOL_CAN_RAW, CAN_RAW_FILTER, &filter, filterSize);
    if (ret < 0)
    {
        return false;
    }
    return true;
}

bool SocketCan::SetCanFilters(const std::vector<can_filter>& filters) const
{
    if (filters.empty())
    {
        return false;
    }
    const auto    itemSize   = static_cast<socklen_t>(sizeof(can_filter));
    const auto    filterSize = static_cast<socklen_t>(static_cast<socklen_t>(filters.size()) * itemSize);
    const int32_t ret        = setsockopt(m_sockCan, SOL_CAN_RAW, CAN_RAW_FILTER, filters.data(), filterSize);
    if (ret < 0)
    {
        return false;
    }
    return true;
}

void SocketCan::CloseSocketCan()
{
    if (m_sockCan > 0)
    {
        (void)close(m_sockCan);
        m_sockCan = -1;
    }
}
}
}
}  // namespace holo_cmw
