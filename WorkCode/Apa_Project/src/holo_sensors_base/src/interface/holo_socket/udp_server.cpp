/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * \brief the holo socket definition
 * \author penggang (penggang@holomatic.ai)
 * \date 2019-12-02
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/sensors/interface/holo_socket/udp_server.h>
#include <string.h>

namespace holo
{
namespace sensors
{
namespace interface
{
HoloSocketUdpServer::HoloSocketUdpServer() : HoloSocket(), local_addr_{}
{
}
/**
 * @brief      Construct a new Holo Socket Udp Server object
 *
 * @param      ip          The ip
 * @param      port        The port
 * @param      timeout_ms  Block if negative,The default is block
 */
HoloSocketUdpServer::HoloSocketUdpServer(const std::string& ip, uint16_t port, int32_t timeout_ms)
{
    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0)
    {
        std::string error = "failed to create socket";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    int so_reuseaddr = 1;
    if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &so_reuseaddr, sizeof(so_reuseaddr)) < 0)
    {
        (void)close(socket_);
        std::string error = "failed to set socket reusable";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    (void)memset(&local_addr_, 0, sizeof(local_addr_));
    local_addr_.sin_family = AF_INET;
    local_addr_.sin_port   = htons(port);
    if (INADDR_NONE == inet_addr(ip.c_str()))
    {
        local_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        local_addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    }
    if (timeout_ms > 0)
    {
        struct timeval timeout;
        timeout.tv_sec  = timeout_ms / 1000;
        timeout.tv_usec = (timeout_ms % 1000) * 1000;
        if (setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
        {
            std::string error = "failed to set socket timeout option";
            LOG(ERROR) << error;
            throw std::runtime_error(error);
        }
    }
    if (bind(socket_, (struct sockaddr*)&local_addr_, sizeof(local_addr_)) < 0)
    {
        std::string error = "failed to bind socket";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
}
/**
 * @brief      send buffer
 *
 * @param      buffer     The buffer
 * @param      send_size  The send size
 *
 * @return     0 for ok, else failed
 */
int32_t HoloSocketUdpServer::Send(const uint8_t* buffer, uint32_t size, const struct sockaddr_in* addr)
{
    if (socket_ < 0)
    {
        return E_WRONG_SOCKET;
    }
    if (nullptr == buffer)
    {
        return E_WRONG_BUFFER;
    }
    if (0 == size)
    {
        return E_WRONG_SIZE;
    }
    socklen_t slen = sizeof(struct sockaddr_in);
    int       ret  = sendto(socket_, buffer, size, 0, (const struct sockaddr*)addr, slen);
    if (ret < 0)
    {
        return ret;
    }
    if (ret == 0)
    {
        return E_SOCKET_CLOSE;
    }
    return E_OK;
}
int32_t HoloSocketUdpServer::Send(const uint8_t* buffer, uint32_t size, const char* ip, uint16_t port)
{
    struct sockaddr_in addr;
    (void)memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    return Send(buffer, size, &addr);
}
int32_t HoloSocketUdpServer::Send(const uint8_t* buffer, uint32_t size, const std::string& ip, uint16_t port)
{
    return Send(buffer, size, ip.c_str(), port);
}
/**
 * @brief      receive data to buffer
 *
 * @param      buffer         The buffer
 * @param      buffer_size    The buffer size
 * @param      received_size  The received size
 *
 * @return     0 for ok, else failed
 */
int32_t HoloSocketUdpServer::Receive(uint8_t* buffer, uint32_t buffer_size, int32_t& received_size,
                                     struct sockaddr_in* addr)
{
    if (socket_ < 0)
    {
        return E_WRONG_SOCKET;
    }
    if (nullptr == buffer)
    {
        return E_WRONG_BUFFER;
    }
    if (0 == buffer_size)
    {
        return E_WRONG_SIZE;
    }
    if (addr == nullptr)
    {
        static struct sockaddr_in temp_addr;
        addr = &temp_addr;
    }
    (void)memset(addr, 0, sizeof(struct sockaddr_in));
    socklen_t slen = sizeof(struct sockaddr_in);
    received_size  = recvfrom(socket_, buffer, buffer_size, 0, (struct sockaddr*)addr, &slen);
    if (received_size < 0)
    {
        int32_t ret   = received_size;
        received_size = 0;
        return ret;
    }
    if (received_size == 0)
    {
        return E_SOCKET_CLOSE;
    }
    return E_OK;
}
}  // namespace interface
}  // namespace sensors
}  // namespace holo
