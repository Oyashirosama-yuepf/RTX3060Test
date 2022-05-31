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

#ifndef HOLO_SENSORS_CMW_APP_HOLO_SOCKET_UDP_CLIENT_H
#define HOLO_SENSORS_CMW_APP_HOLO_SOCKET_UDP_CLIENT_H

#include <holo/sensors/interface/holo_socket/socket.h>

namespace holo
{
namespace sensors
{
namespace interface
{
class HoloSocketUdpClient : public HoloSocket
{
public:
    /**
     * @brief Default Construct a new Holo Socket Udp Client object
     *
     */
    HoloSocketUdpClient();
    /**
     * @brief      Construct a new Holo Socket Udp Client object
     *
     * @param      ip          The ip
     * @param      port        The port
     * @param      timeout_ms  block time in milli-second, -1 for forever
     */
    HoloSocketUdpClient(const std::string& ip, uint16_t port, int32_t timeout_ms = -1);
    /**
     * @brief      send buffer
     *
     * @param      buffer     The buffer
     * @param      send_size  The send size
     *
     * @return     0 for ok, else failed
     */
    int32_t Send(const uint8_t* buffer, uint32_t send_size);
    /**
     * @brief      receive data to buffer
     *
     * @param      buffer         The buffer
     * @param      buffer_size    The buffer size
     * @param      received_size  The received size
     *
     * @return     0 for ok, else failed
     */
    int32_t Receive(uint8_t* buffer, uint32_t buffer_size, int32_t& received_size);

private:
    struct sockaddr_in server_addr_;
};

}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif  // HOLO_SENSORS_CMW_APP_HOLO_SOCKET_UDP_CLIENT_H
