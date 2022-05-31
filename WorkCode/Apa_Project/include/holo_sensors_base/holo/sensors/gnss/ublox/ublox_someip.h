/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ublox_someip.h
 * @brief This header file define the function of ublox ark
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/08/27
 */

#ifndef _HOLO_SENSORS_GNSS_UBLOX_UBLOX_SOMEIP_H
#define _HOLO_SENSORS_GNSS_UBLOX_UBLOX_SOMEIP_H

#include <holo/core/types.h>
#include <holo/sensors/format/someip.h>
#include <holo/sensors/gnss/ublox/ublox.h>

namespace holo
{
namespace sensors
{
namespace ublox
{
using SomeipPacketType = holo::sensors::format::SomeipPacket<4096>;

template <>
class UbloxDriverT<SomeipPacketType> : public UbloxDriverBaseT<SomeipPacketType>
{
public:
    UbloxDriverT(const SensorId& sensor_id = 0) : UbloxDriverBaseT<SomeipPacketType>(sensor_id)
    {
    }

    void ParseData(const SomeipPacketType& data)
    {
        uint32_t length = data.GetPayloadLength();
        if (length < 8)
        {
            return;
        }
        uint8_t m_class = data.GetPayload()[6];
        uint8_t m_id    = data.GetPayload()[7];
        /* parse data */
        if (UbxMessageType(m_class) == UbxMessageType::UBX_NAV)
        {
            if (UbxNavType(m_id) == UbxNavType::NAV_PVT)
            {
                ParseNavPvt(&data.GetPayload()[10], length - 4 - 8);
            }
        }
        else if (UbxMessageType(m_class) == UbxMessageType::UBX_RXM)
        {
            if (UbxRxmType(m_id) == UbxRxmType::RXM_RAWX)
            {
                ParseRxmRawx(&data.GetPayload()[10], length - 4 - 8);
            }
        }
        else
        {
            /* ignore other messages, add more branches if necessary */
        }
    }
};

}  // namespace ublox
}  // namespace sensors
}  // namespace holo

#endif
