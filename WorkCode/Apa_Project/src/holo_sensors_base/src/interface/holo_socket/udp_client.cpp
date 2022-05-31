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

#include <holo/sensors/interface/holo_socket/udp_client.h>
#include <string.h>

namespace holo
{
namespace sensors
{
namespace interface
{
HoloSocketUdpClient::HoloSocketUdpClient() : HoloSocket(), server_addr_{}
{
}
/**
 * @brief      Construct a new Holo Socket Udp Client object
 *
 * @param      ip          The ip
 * @param      port        The port
 * @param      timeout_ms  block time in milli-second, -1 for forever
 */
HoloSocketUdpClient::HoloSocketUdpClient(const std::string& ip, uint16_t port, int32_t timeout_ms)
{
    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0)
    {
        std::string error = "failed to create socket";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    (void)memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family      = AF_INET;
    server_addr_.sin_port        = htons(port);
    server_addr_.sin_addr.s_addr = inet_addr(ip.c_str());
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
}
/**
 * @brief      send buffer
 *
 * @param      buffer     The buffer
 * @param      send_size  The send size
 *
 * @return     0 for ok, else failed
 */
int32_t HoloSocketUdpClient::Send(const uint8_t* buffer, uint32_t send_size)
{
    if (socket_ < 0)
    {
        return E_WRONG_SOCKET;
    }
    if (nullptr == buffer)
    {
        return E_WRONG_BUFFER;
    }
    if (0 == send_size)
    {
        return E_WRONG_SIZE;
    }
    socklen_t slen = sizeof(struct sockaddr_in);
    int32_t   ret  = sendto(socket_, buffer, send_size, 0, (struct sockaddr*)&(server_addr_), slen);
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
/**
 * @brief      receive data to buffer
 *
 * @param      buffer         The buffer
 * @param      buffer_size    The buffer size
 * @param      received_size  The received size
 *
 * @return     0 for ok, else failed
 */
int32_t HoloSocketUdpClient::Receive(uint8_t* buffer, uint32_t buffer_size, int32_t& received_size)
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
    struct sockaddr_in temp_addr;
    socklen_t          slen = sizeof(struct sockaddr_in);
    received_size           = recvfrom(socket_, buffer, buffer_size, 0, (struct sockaddr*)&temp_addr, &slen);
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
