/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ublox_rawbuf.h
 * @brief This header file define the function of ublox rawbuf
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/08/27
 */

#ifndef _HOLO_SENSORS_GNSS_UBLOX_UBLOX_RAWBUF_H
#define _HOLO_SENSORS_GNSS_UBLOX_UBLOX_RAWBUF_H

#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/gnss/ublox/ublox.h>

namespace holo
{
namespace sensors
{
namespace ublox
{
using RawbufferType = holo::sensors::format::Rawbuffer<4096>;

template <>
class UbloxDriverT<RawbufferType> : public UbloxDriverBaseT<RawbufferType>
{
public:
    UbloxDriverT(const SensorId& sensor_id = 0) : UbloxDriverBaseT<RawbufferType>(sensor_id)
    {
    }

    void ParseData(const RawbufferType& data)
    {
        const uint8_t* s   = data.data();

        if (!IsValid(data))
        {
            return;
        }
        s += 4;

        /* fetch timestamp */
        uint32_t                timestamp_high = holo::os::ntoh32(*((const uint32_t*)(s + 0)));
        uint32_t                timestamp_low  = holo::os::ntoh32(*((const uint32_t*)(s + 4)));
        holo::common::Timestamp timestamp(timestamp_high, timestamp_low);

        // timestamp -= Duration(0, 100000000);
        s += 8;

        /* go data */
        if ((s[0] == 0xB5) && (s[1] == 0x62))
        {
            uint8_t        m_class   = s[2];
            uint8_t        m_id      = s[3];
            uint16_t       m_length  = (s[4] + (s[5] * 256));
            const uint8_t* m_payload = s + 6;

            /* checksum */
            if (!Checksum(data, m_length))
            {
                return;
            }

            /* parse data */
            if (UbxMessageType(m_class) == UbxMessageType::UBX_NAV)
            {
                if (UbxNavType(m_id) == UbxNavType::NAV_PVT)
                {
                    UbloxDriverBaseT<RawbufferType>::ParseNavPvt(m_payload, m_length);
                }
            }
            else if (UbxMessageType(m_class) == UbxMessageType::UBX_RXM)
            {
                if (UbxRxmType(m_id) == UbxRxmType::RXM_RAWX)
                {
                    UbloxDriverBaseT<RawbufferType>::ParseRxmRawx(m_payload, m_length);
                }
            }
            else
            {
                /* ignore other messages, add more branches if necessary */
            }
        }
        else
        {
            LOG(WARNING) << "unknown payload header, data aborted!";
            return;
        }
    }

private:
    bool_t IsValid(const RawbufferType& data)
    {
        const uint8_t* s = data.data();
        /* check bytes */
        if (data.size() < 4 + 8 + 6)
        {
            LOG(WARNING) << "invalid data format, data aborted!";
            return false;
        }
        /* check header */
        if (0 != memcmp(s, "##@!", 4))
        {
            LOG(WARNING) << "unknown data header, data aborted!";
            return false;
        }
        return true;
    }

    bool_t Checksum(const RawbufferType& data, uint32_t m_length)
    {
        const uint8_t* s   = data.data();
        const uint8_t* end = s + data.size();

        if ((s + 6 + m_length + 2) > end)
        {
            LOG(ERROR) << "receive length is less than the message length!";
            return false;
        }

        uint8_t        checksum_a = 0;
        uint8_t        checksum_b = 0;
        const uint8_t* buf        = s + 2;
        uint32_t       bytes      = m_length + 4;

        for (uint32_t i = 0; i < bytes; ++i)
        {
            checksum_a = checksum_a + buf[i];
            checksum_b = checksum_b + checksum_a;
        }

        if ((checksum_a != s[m_length + 6]) || (checksum_b != s[m_length + 7]))
        {
            LOG(ERROR) << "ublox checksum is error!";
            return false;
        }
        return true;
    }
};

}  // namespace ublox
}  // namespace sensors
}  // namespace holo

#endif