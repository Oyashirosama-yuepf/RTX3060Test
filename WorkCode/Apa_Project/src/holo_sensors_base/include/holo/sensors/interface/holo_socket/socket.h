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

#ifndef HOLO_SENSORS_CMW_APP_HOLO_SOCKET_SOCKET_H
#define HOLO_SENSORS_CMW_APP_HOLO_SOCKET_SOCKET_H

#include <holo/os/predefine.h>
#include <unistd.h>
#if defined(HOLO_PLATFORM_LINUX)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#elif defined(HOLO_PLATFORM_QNX)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/time.h>
#else
#error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif
#include <holo/log/hololog.h>
#include <holo/core/types.h>

namespace holo
{
namespace sensors
{
namespace interface
{
static const uint8_t CLIENT_ARRAY_SIZE = 255;
static const uint8_t RECONNECT_TIMES   = 10;
enum ErrorCode : int32_t
{
    E_OK              = 0x00,
    E_WRONG_BUFFER    = 0x01,
    E_WRONG_CLIENT_ID = 0x02,
    E_WRONG_SIZE      = 0x03,
    E_WRONG_SOCKET    = 0x04,
    E_SOCKET_CLOSE    = 0x05
};

class HoloSocket
{
public:
    HoloSocket() : socket_(-1)
    {
    }

    virtual ~HoloSocket() noexcept
    {
        if (socket_ > 0)
        {
            (void)close(socket_);
            socket_ = -1;
        }
    }

    int32_t GetFd() const noexcept
    {
        return socket_;
    }

protected:
    int32_t socket_;
};

}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif  // HOLO_SENSORS_CMW_APP_HOLO_SOCKET_SOCKET_H
