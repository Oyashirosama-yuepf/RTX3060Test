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

#include <holo/sensors/interface/holo_socket/tcp_client.h>
#include <string.h>

namespace holo
{
namespace sensors
{
namespace interface
{
HoloSocketTcpClient::HoloSocketTcpClient(const std::string& ip, uint16_t port) : HoloSocket()
{
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        throw std::runtime_error("failed to build socket");
    }
    (void)memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family      = AF_INET;
    server_addr_.sin_port        = htons(port);
    server_addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

int32_t HoloSocketTcpClient::Send(const uint8_t* buffer, uint32_t send_size)
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
    int32_t ret = send(socket_, buffer, send_size, 0);
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

int32_t HoloSocketTcpClient::Receive(uint8_t* buffer, uint32_t buffer_size, int32_t& received_size)
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
    received_size = recv(socket_, buffer, buffer_size, 0);
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

int32_t HoloSocketTcpClient::Connect()
{
    int32_t ret = connect(socket_, (struct sockaddr*)&server_addr_, sizeof(server_addr_));
    if (ret < 0)
    {
        return ret;
    }
    return E_OK;
}

int32_t HoloSocketTcpClient::Reconnect()
{
    if (socket_ > 0)
    {
        (void)close(socket_);
    }
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    return Connect();
}

}  // namespace interface
}  // namespace sensors
}  // namespace holo
