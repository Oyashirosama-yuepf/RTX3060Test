/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 *  \brief the holo socket definition
 *  \author penggang (penggang@holomatic.ai)
 *  \date 2019-12-02
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_SENSORS_CMW_APP_HOLO_SOCKET_TCP_CLIENT_H
#define HOLO_SENSORS_CMW_APP_HOLO_SOCKET_TCP_CLIENT_H

#include <holo/sensors/interface/holo_socket/socket.h>

namespace holo
{
namespace sensors
{
namespace interface
{
class HoloSocketTcpClient : public HoloSocket
{
public:
    /**
     * @brief      Construct a new Holo Socket Tcp Client object
     *
     * @param      ip          socket ip
     * @param      port        socket port
     * @param      timeout_ms  Block time in milli-seconds
     */
    HoloSocketTcpClient(const std::string& ip, uint16_t port);
    /**
     * @brief      send buffer
     *
     * @param      buffer     The buffer
     * @param      send_size  The send size
     *
     * @return     int32_t         -1 means send failed
     */
    int32_t Send(const uint8_t* buffer, uint32_t send_size);
    /**
     * @brief      { function_description }
     *
     * @param      buffer         The buffer
     * @param      buffer_size    The buffer size
     * @param      received_size  will be set 0 if receive failed
     *
     * @return     int32_t        -1 means receive failed
     */
    int32_t Receive(uint8_t* buffer, uint32_t buffer_size, int32_t& received_size);
    /**
     * @brief      connect server
     *
     * @return     0 for ok, else failed
     */
    int32_t Connect();
    /**
     * @brief      reconnect server
     *
     * @return     0 for ok, else failed
     */
    int32_t Reconnect();

private:
    struct sockaddr_in server_addr_;
};

}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif  // HOLO_SENSORS_CMW_APP_HOLO_SOCKET_TCP_CLIENT_H
