/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file msg_position.h
 * @brief This header file defines the baidu position message definitions.
 * @author zhengshulei@holomatic.com
 * @date 2021-10-25
 */
#ifndef HOLO_MAP_ADASIS_BAIDU_V3_MSG_POSITION_H_
#define HOLO_MAP_ADASIS_BAIDU_V3_MSG_POSITION_H_

#include <holo/map/adasis/baidu_v3/msg_header.h>
#include <vector>

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
 * @brief Defition of absolute position.
 */
class AbsoPos
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::int32_t>(longitude) << static_cast<holo::int32_t>(latitude)
          << static_cast<holo::int32_t>(altitude) << static_cast<holo::int32_t>(heading);
    }
    void Deserialize(Deserializer &s)
    {
        s >> longitude >> latitude >> altitude >> heading;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "AbsoPos info, heading=" << heading
                  << " latitude=" << latitude
                  << " longitude=" << longitude
                  << " altitude=" << altitude;
    }

public:
    holo::int32_t longitude = 0; ///< Matrix P3 017
    holo::int32_t latitude  = 0;
    holo::int32_t altitude  = 0;
    holo::int32_t heading   = 0; ///< Matrix P3 019
};

/**
 * @brief Defition of coordinate system.
 */
class Coordinate
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::uint8_t>(type) 
          << static_cast<holo::uint8_t>(zoom_id)
          << static_cast<holo::uint8_t>(south_flag);
    }
    void Deserialize(Deserializer &s)
    {
        s >> type >> zoom_id >> south_flag;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "Coordinate info, zoom_id=" << static_cast<holo::uint16_t>(zoom_id)
                  << " south_flag=" << static_cast<holo::uint16_t>(south_flag)
                  << " type=" << static_cast<holo::uint16_t>(type);
    }

public:
    holo::uint8_t type       = 0;
    holo::uint8_t zoom_id    = 0;
    holo::uint8_t south_flag = 0;
};

/**
 * @brief Defition of quaternion. 
 */
class Quaternion
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::float64_t>(x) 
          << static_cast<holo::float64_t>(y) 
          << static_cast<holo::float64_t>(z)
          << static_cast<holo::float64_t>(w);
    }
    void Deserialize(Deserializer &s)
    {
        s >> x >> y >> z >> w;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "Quaternion info, x=" << x << " y=" << y << " z=" << z << " w=" << w;
    }

public:
    holo::float64_t x = 0;
    holo::float64_t y = 0;
    holo::float64_t z = 0;
    holo::float64_t w = 0;
};

/**
 * @brief Defition of location status.
 */
class Localization
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::uint8_t>(status)
          << static_cast<holo::uint64_t>(raw_ts) 
          << static_cast<holo::uint8_t>(actived);
    }
    void Deserialize(Deserializer &s)
    {
        s >> status >> raw_ts >> actived;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "Localization info, status=" << static_cast<holo::uint16_t>(status)
                  << " raw_ts=" << raw_ts
                  << " actived=" << static_cast<holo::uint16_t>(actived);
    }

public:
    holo::uint8_t status = 0;
    holo::uint64_t raw_ts = 0;
    holo::bool_t actived  = false;
};

/**
 * @brief Baidu-EHP position message.
 * @detail two change point compare with standard ADASIS V3:
 *         1. add link_id and lane_id match-result info;
 *         2. add llateral_off_lef/lateral_off_right/longitudinal_off_start/longitudinal_off_end match-result info.
 */
class BDPosition : public v3_1_1::Position
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::uint64_t>(timestamp) << static_cast<holo::uint64_t>(position_age)
          << static_cast<holo::uint32_t>(pathId) << static_cast<holo::uint32_t>(offset)
          << static_cast<holo::uint32_t>(accuracy) << static_cast<holo::int32_t>(deviation)
          << static_cast<holo::float32_t>(speed) << static_cast<holo::float32_t>(relativeHeading)
          << static_cast<holo::float32_t>(probability) 
          << static_cast<holo::uint64_t>(current_link) << static_cast<holo::uint64_t>(current_lane) 
          << static_cast<holo::uint32_t>(preferredPath)
          << static_cast<holo::int32_t>(lateral_off_left) << static_cast<holo::int32_t>(lateral_off_right)
          << static_cast<holo::int32_t>(longitudinal_off_start) << static_cast<holo::int32_t>(longitudinal_off_end);
    }

    void Deserialize(Deserializer &s)
    {
        s >> timestamp >> position_age 
          >> pathId >> offset >> accuracy >> deviation 
          >> speed >> relativeHeading >> probability 
          >> current_link >> current_lane 
          >> preferredPath 
          >> lateral_off_left >> lateral_off_right 
          >> longitudinal_off_start >> longitudinal_off_end;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "Positon info, timestamp=" << timestamp
                  << " position_age=" << position_age
                  << " pathId=" << pathId << " offset=" << offset << " accuracy=" << accuracy
                  << " deviation=" << deviation
                  << " speed=" << speed << " relativeHeading=" << relativeHeading << " probability=" << probability
                  << " current_link=" << current_link << " current_lane=" << current_lane
                  << " preferredPath=" << preferredPath
                  << " lateral_off_left=" << lateral_off_left << " lateral_off_right=" << lateral_off_right
                  << " longitudinal_off_start=" << longitudinal_off_start << " longitudinal_off_end=" << longitudinal_off_end;
    }

public:
    holo::uint64_t timestamp             = 0;
    holo::uint64_t position_age          = 0;
    holo::uint64_t current_link          = 0;
    holo::uint64_t current_lane          = 0;
    holo::int32_t lateral_off_left       = 0;
    holo::int32_t lateral_off_right      = 0;
    holo::int32_t longitudinal_off_start = 0;
    holo::int32_t longitudinal_off_end   = 0;
};

enum class NavigationStatus : holo::uint8_t
{
    NONE = 0,
    PATH_CALCULATING,
    NAVIGATION,
    CRUISE,
    GOING_OFF_COURSE,
    REPLANNING
};

enum class MatchingStatus : holo::uint8_t
{
    DEFAULT = 0,
    MATCHING_TABLE_OK,
    SD_MAP_DESTINATION_REARCH,
    HD_MAP_DATA_END,
    NAVIGATION_OFFLINE_NO_LOCAL_ASSOCIATED_TABLE,
    MATCHING_TABLE_NOT_AVAILABLE,
    Reserved1,
    Reserved2,
    OTHERS
};

/**
 * @brief Baidu-EHP hdmap status.
 */
class HDMap
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<holo::uint8_t>(navigation_status) << static_cast<holo::uint16_t>(range)
          << static_cast<holo::uint8_t>(maching_status);
    }

    void Deserialize(Deserializer &s)
    {
        holo::uint8_t v1 = 0;
        holo::uint8_t v2 = 0;
        s >> v1 >> range >> v2;
        navigation_status=static_cast<NavigationStatus>(v1);
        maching_status=static_cast<MatchingStatus>(v2);
    }

public:
    holo::bool_t RearchEnd()
    {
        return maching_status == MatchingStatus::HD_MAP_DATA_END || 
               maching_status == MatchingStatus::SD_MAP_DESTINATION_REARCH;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "HDMap info, navigation_status=" << static_cast<holo::uint16_t>(navigation_status)
                  << " range=" << static_cast<holo::uint16_t>(range)
                  << " maching_status=" << static_cast<holo::uint16_t>(maching_status);
    }

public:
    NavigationStatus  navigation_status = NavigationStatus::NONE;
    holo::uint16_t range             = 0;
    MatchingStatus  maching_status    = MatchingStatus::DEFAULT;
};

/**
 * @brief Baidu-EHP position package.
 */
class PositionMessage
{
public:
    void Serialize(Serializer &s) const
    {
        s << e2e_header << timestamp
          << abso_pos << ais_header << static_cast<holo::uint8_t>(msg_count)
          << coord << quat << loc
          << static_cast<holo::uint32_t>(position_count);
        for(BDPosition pos : positions)
        {
            s << pos;
        }
        s << hd_map;
    }
    void Deserialize(Deserializer &s)
    {
        s >> e2e_header >> timestamp
          >> abso_pos >> ais_header >> msg_count 
          >> coord >> quat >> loc >> position_count;

        if(position_count > 0)
        {
            for(std::size_t i = 0;i < position_count; i++)
            {
                BDPosition pos;
                s >> pos;
                positions.push_back(pos);
            }
        }
        s >> hd_map;
    }

public:
    holo::uint8_t GetMLMStatus()
    {
        return timestamp.reserved;
    }
    void SetMLMStatus(holo::uint8_t mlm_status)
    {
        timestamp.reserved = mlm_status;
    }
    void PrintDebugInfo()
    {
        LOG(INFO) << "MLM_LOC info, msg_type=" << static_cast<holo::uint16_t>(ais_header.msg_type)
                  << " msg_count=" << static_cast<holo::uint16_t>(msg_count)
                  << " time_week=" << timestamp.time_week
                  << " sys_time=" << timestamp.sys_time
                  << " position_count=" << position_count;
        abso_pos.PrintDebugInfo();
        coord.PrintDebugInfo();
        quat.PrintDebugInfo();
        loc.PrintDebugInfo();
        for(std::size_t i=0;i<positions.size();i++)
        {
            positions[i].PrintDebugInfo();
        }
        hd_map.PrintDebugInfo();
    }

public:
    E2EHeader e2e_header;
    Timestamp timestamp;
    AbsoPos abso_pos;
    AdasisHeader ais_header;
    holo::uint8_t msg_count = 0;
    Coordinate coord;
    Quaternion quat;
    Localization loc;
    holo::uint32_t position_count = 0;
    std::vector<BDPosition> positions;
    HDMap hd_map;
};

/**
 * @}
 */

} // namespace baidu_v3
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_BAIDU_V3_MSG_POSITION_H_ */