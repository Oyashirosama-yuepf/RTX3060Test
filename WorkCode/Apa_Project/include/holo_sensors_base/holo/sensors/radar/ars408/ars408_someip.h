/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file conti_radar_someip.h
 * @brief A class to receive and construct conti radar outputs in someip format
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/16
 */

#ifndef HOLO_SENSORS_CONTI_RADAR_CONTI_RADAR_SOMEIP_H_
#define HOLO_SENSORS_CONTI_RADAR_CONTI_RADAR_SOMEIP_H_

#include <holo/core/types.h>
#include <holo/sensors/format/someip.h>
#include <holo/sensors/radar/ars408/ars408_base.h>
#include <holo_c/sensors/conti_radar/structure/conti_radar_object.h>

namespace holo
{
namespace sensors
{
namespace conti_radar
{
using SomeipPacketType = holo::sensors::format::SomeipPacket<1024>;

static const uint32_t PACKET_PAYLOAD_CAPACITY = 1020;
static const uint32_t BUFFER_PAYLOAD_CAPACITY = 5120;

template <>
class ContiRadarDriverT<SomeipPacketType> : public ContiRadarDriverBase<SomeipPacketType>
{
public:
    ContiRadarDriverT(const Extrinsicf& extrinsic)
      : ContiRadarDriverBase<SomeipPacketType>(extrinsic), parsing_buffer_{}
    {
        parsing_buffer_.Reset();
    }

    void ParseData(const SomeipPacketType& data);

private:
    /**
     * @brief      parsing params structure
     */
    struct ParsingBuffer
    {
        uint8_t  rc;
        uint8_t  payload[BUFFER_PAYLOAD_CAPACITY];
        uint32_t payload_size;
        uint32_t payload_pnum;

        void Reset() noexcept
        {
            (void)std::memset(&rc, 0, sizeof(ParsingBuffer));
        }
    };
    /**
     * @brief someip payload header def
     */
    struct SomeIpPayloadHeader
    {
        uint8_t h0;  //! header '#'
        uint8_t rc;  //! rolling counter
        uint8_t pn;  //! total packet number
        uint8_t pi;  //! packet index number
    };

private:
    bool_t ParseObstacles(const uint8_t* data, uint32_t size);
    void   Convert(const ContiRadarObjectListRawData& input, ObstaclePtrListType& output) const;
    void   Convert(const ContiRadarObjectRawData& input, std::shared_ptr<ObstacleType>& obstacle) const;

private:
    ParsingBuffer parsing_buffer_;
};

}  // namespace conti_radar
}  // namespace sensors
}  // namespace holo

#endif
