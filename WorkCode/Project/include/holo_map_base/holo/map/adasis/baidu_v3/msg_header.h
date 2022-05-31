/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file msg_header.h
 * @brief This header file defines the baidu message header definitions.
 * @author zhengshulei@holomatic.com
 * @date 2021-10-25
 */
#ifndef HOLO_MAP_ADASIS_BAIDU_V3_MSG_HEADER_H_
#define HOLO_MAP_ADASIS_BAIDU_V3_MSG_HEADER_H_

#include <holo/map/adasis/v3/v3_1_1.h>

namespace holo
{
namespace map
{
namespace adasis
{
namespace baidu_v3
{

/**
 * @addtogroup baidu_v3
 * @{
 *
 */

/**
 * @brief EHP package header.
 */
class E2EHeader
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::uint16_t>(pdu_length) 
          << static_cast<holo::uint32_t>(pdu_id)
          << static_cast<holo::uint8_t>(reserved_1) 
          << static_cast<holo::uint8_t>(reserved_2)
          << static_cast<holo::uint16_t>(counter) 
          << static_cast<holo::uint32_t>(checksum);
    }

    void Deserialize(Deserializer &s)
    {
        s >> pdu_length >> pdu_id >> reserved_1 >> reserved_2 >> counter >> checksum;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "E2E header info, pdu_id=" << pdu_id 
                  << " counter=" << counter 
                  << " pdu_length=" << pdu_length 
                  << " checksum=" << checksum;
    }

public:
    holo::uint16_t pdu_length = 0;
    holo::uint32_t pdu_id     = 0;
    holo::uint8_t reserved_1  = 0;
    holo::uint8_t reserved_2  = 0;
    holo::uint16_t counter    = 0;
    holo::uint32_t checksum   = 0;
};

/**
 * @brief EHP package timestamp.
 */
class Timestamp
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::uint8_t>(reserved) 
          << static_cast<holo::bool_t>(time_valid)
          << static_cast<holo::uint16_t>(time_week) 
          << static_cast<holo::uint64_t>(time_ms)
          << static_cast<holo::uint64_t>(sys_time);
    }

    void Deserialize(Deserializer &s)
    {
        s >> reserved >> time_valid >> time_week >> time_ms >> sys_time;
    }

public:
    holo::uint8_t reserved   = 0;
    holo::bool_t time_valid  = true;
    holo::uint16_t time_week = 0;
    holo::uint64_t time_ms   = 0;
    holo::uint64_t sys_time  = 0;
};

/**
 * @brief EHP package map bundle index for profile message.
 */
class MapData
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::uint16_t>(part_count) 
          << static_cast<holo::uint16_t>(part_index)
          << static_cast<holo::uint32_t>(bundle_id);
    }

    void Deserialize(Deserializer &s)
    {
        s >> part_count >> part_index >> bundle_id;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "MapData info, bundle_id=" << bundle_id 
                  << " part_index=" << part_index
                  << " part_count=" << part_count;
    }

public:
    holo::uint16_t part_count = 0;
    holo::uint16_t part_index = 0;
    holo::uint32_t bundle_id  = 0;
};

class PayloadHeader
{
public:
    void Serialize(Serializer& s) const
    {
        s << timestamp << map_bundle;
    }
    void Deserialize(Deserializer& s)
    {
        s >> timestamp >> map_bundle;
    }

public:
    Timestamp timestamp;
    MapData map_bundle;
};

/**
 * @brief EHP package adasis header for profile message.
 */
class AdasisHeader
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::uint8_t>(reserved) 
          << static_cast<holo::uint8_t>(cyc_counter)
          << static_cast<holo::uint8_t>(msg_type);
          // << static_cast<holo::uint8_t>(msg_count);
    }

    void Deserialize(Deserializer &s)
    {
        s >> reserved >> cyc_counter >> msg_type;// >> msg_count;
    }

public:
    holo::uint8_t reserved    = 0;
    holo::uint8_t cyc_counter = 0;
    holo::uint8_t msg_type    = 0;
    // holo::uint8_t msg_count   = 0;
};

/**
 * @}
 */

} // namespace baidu_v3
} // namespace adasis
} // namespace map
} // namespace holo

#endif // HOLO_MAP_ADASIS_BAIDU_V3_MSG_HEADER_H_
