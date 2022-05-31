/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file msg_payload.h
 * @brief This header file defines the baidu message payload definitions.
 * @author zhengshulei@holomatic.com
 * @date 2021-10-25
 */
#ifndef HOLO_MAP_ADASIS_BAIDU_V3_MSG_PAYLOAD_H_
#define HOLO_MAP_ADASIS_BAIDU_V3_MSG_PAYLOAD_H_

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
 * @brief  Definition of baidu-ehp road class.
 */
enum class BaiduFunctionalRoadClass : holo::uint8_t
{
    Highway = 0,
    UrbanExpressway=1,
    GeneralRoad=2
};

enum class BaiduFormOfWay : holo::uint8_t
{
    FormOfWay_Normal      = 1,
    FormOfWay_RampEntry   = 16,
    FormOfWay_RampExit    = 17,
    FormOfWay_JCT         = 19,
    FormOfWay_RampConnect = 31
};

/**
 * @brief Definition of baidu-ehp lane type.
 */
enum BaiduLaneType : holo::uint8_t
{
    LAT_NORMAL                  = 0,
    LAT_ENTRY                   = 1,
    LAT_EXIT                    = 2,
    LAT_EMERGENCY               = 3,
    LAT_ON_RAMP                 = 4,
    LAT_OFF_RAMP                = 5,
    LAT_CONNECT_RAMP            = 6,
    LAT_ACCELERATE              = 7,
    LAT_DECELERATE              = 8,
    LAT_EMERGENCY_PARKING_STRIP = 9,
    LAT_CLIMBING                = 10,
    LAT_ESCAPE                  = 11,
    LAT_DEDICATED_CUSTOMS       = 12,
    LAT_VIEWING_PLATFROM        = 13,
    LAT_PARALLEL_LANE           = 14,
    LAT_DIVERSION               = 17 // diversion zone
};

/**
 * @brief Definition of baidu-ehp tx message types.
 */
enum class MessageType : holo::uint32_t
{
    /// location message, value 50331649U
    MLM_LOC = 0x03000001,
    /// path control message, value 50331651U
    MLM_PTC = 0x03000003,
    /// global data message, value 50331652U
    MLM_GLBD = 0x03000004,
    /// profile control message, value 50331653U
    MLM_PFC = 0x03000005,
    /// node profile, value 50331654U
    MLM_PFN = 0x03000006,
    /// lane model profile, value 50331655U
    MLM_PFLM = 0x03000007,
    /// lane connectivity profile, value 50331656U
    MLM_PFLC = 0x03000008,
    /// linear object profile, value 50331657U
    MLM_PFLO = 0x03000009,
    /// lane geometry profile, value 50331658U
    MLM_PFLG = 0x0300000A,
    /// curvature profile, value 50331659U
    MLM_PFCV = 0x0300000B,
    /// slope profile, value 50331660U
    MLM_PFSP = 0x0300000C,
    /// speed limit profile, value 50331661U
    MLM_PFSL = 0x0300000D,
    /// road geometry profile, value 50331662U
    MLM_PFRG = 0x0300000E,
    // NumOfLane profile, value 50331663U
    MLM_PFLI1 = 0x0300000F,
    /// road function class profile, value 50331664U
    MLM_PFLI2 = 0x03000010,
    /// FormOfWay profile, value 50331665U
    MLM_PFLI3 = 0x03000011,
    /// tunnel profile, value 50331666U
    MLM_PFLI4 = 0x03000012,
    /// linkidentifier profile, value 50331667U
    MLM_PFLI5 = 0x03000013,
    /// lane width profile, value 50331672U
    MLM_PFLW = 0x03000018,
    /// map line, value 50331673U
    MLM_MPL = 0x03000019,
    /// road junction, value 50331681U
    MLM_PFRJ = 0x03000021,
    /// road junction connectivity, value 50331682U
    MLM_PFRJC = 0x03000022,
    /// road junction lane, value 50331683U
    MLM_PFRJL = 0x03000023,
    /// object pedestrian crossing, value 50331684U
    MLM_PFOPC = 0x03000024,
    ///  object traffic sign, value 50331685U
    MLM_PFOTS = 0x03000025,
    /// object stop line, value 50331686U
    MLM_PFOSL = 0x03000026,
    /// object traffic light, value 50331687U
    MLM_PFOTL = 0x03000027,
    /// object Safety island, value 50331688U
    MLM_PFOSI = 0x03000028,
    /// object round island, value 50331689U
    MLM_PFORI = 0x03000029
};

/**
 * @brief Helper functions for baidu-ehp tx message types(enum2string).
 */
class MessageTypeConverter
{
public:
    static std::string Enum2String(MessageType msg_type);
};

/**
 * @brief Message on bus, payload is one object T.
 * @tparam T ADASIS V3 profile value.
 */
template <typename T>
class OneMessageOnBus
{
public:
    void Serialize(Serializer &s) const
    {
        s << e2e_header << timestamp << map_bundle 
          << ais_header << static_cast<holo::uint8_t>(msg_count) << msg;
    }

    void Deserialize(Deserializer &s)
    {
        s >> e2e_header >> timestamp >> map_bundle >> ais_header >> msg_count >> msg;
    }

public:
    void PrintDebugInfo()
    {
        MessageType type = static_cast<MessageType>(e2e_header.pdu_id);
        LOG(INFO) << MessageTypeConverter::Enum2String(type)
                  << " info, msg_type=" << static_cast<holo::uint16_t>(ais_header.msg_type)
                  << " msg_count=" << static_cast<holo::uint16_t>(msg_count) 
                  << " time_week=" << timestamp.time_week
                  << " sys_time=" << timestamp.sys_time;
        msg.PrintDebugInfo();
    }

public:
    E2EHeader       e2e_header;
    Timestamp       timestamp;
    MapData         map_bundle;
    AdasisHeader    ais_header;
    holo::uint8_t   msg_count = 0;
    T  msg;
};

/**
 * @brief Message on bus, payload is object array T.
 * @tparam T ADASIS V3 profile value.
 */
template <typename T>
class MultiMessageOnBus
{
public:
    void Serialize(Serializer &s) const
    {
        s << e2e_header << timestamp << map_bundle 
          << ais_header << static_cast<holo::uint8_t>(msg_count);
        for(T msg : msgs)
        {
            s << msg;
        }
    }

    void Deserialize(Deserializer &s)
    {
        s >> e2e_header >> timestamp >> map_bundle >> ais_header >> msg_count;
        for(std::size_t i = 0;i < msg_count;i++)
        {
            T msg;
            s >> msg;
            msgs.push_back(msg);
        }
    }

public:
    void PrintDebugInfo()
    {
        MessageType type = static_cast<MessageType>(e2e_header.pdu_id);
        LOG(INFO) << MessageTypeConverter::Enum2String(type)
                  << " info, msg_type=" << static_cast<holo::uint16_t>(ais_header.msg_type)
                  << " msg_count=" << static_cast<holo::uint16_t>(msg_count) 
                  << " time_week=" << timestamp.time_week
                  << " sys_time=" << timestamp.sys_time;

        for (std::size_t i = 0; i < msgs.size(); i++)
        {
            T profile = msgs[i];
            profile.PrintDebugInfo();
        }
    }

public:
    E2EHeader       e2e_header;
    Timestamp       timestamp;
    MapData         map_bundle;
    AdasisHeader    ais_header;
    holo::uint8_t   msg_count = 0;
    std::vector<T>  msgs;
};

/**
 * @brief ADASIS V3 profile header.
 */
class ProfileHeader : public v3_1_1::ProfileHeader
{
public:
    void Serialize(Serializer &s) const
    {
        s << static_cast<uint32_t>(instanceId) 
          << static_cast<bool_t>(isRetransmission) 
          << static_cast<uint8_t>(change)
          << static_cast<float32_t>(confidence) 
          << static_cast<uint32_t>(pathId)
          << static_cast<uint8_t>(laneNumber) // different with adasis v3，baidu only use one
          << static_cast<uint32_t>(offset) 
          << static_cast<uint32_t>(endOffset) 
          << static_cast<bool_t>(endOffsetFinal)
          << static_cast<uint8_t>(interpolat) 
          << static_cast<uint8_t>(type)
          << static_cast<bool_t>(available); // missing direction field，so none serialize
    }

    void Deserialize(Deserializer &s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        holo::uint8_t v3;
        s >> instanceId >> isRetransmission >> v1 
          >> confidence >> pathId 
          >> laneNumber 
          >> offset >> endOffset >> endOffsetFinal 
          >> interpolat >> v2 
          >> v3;
        change    = static_cast<v3_1_1::ChangeMode>(v1);
        type      = static_cast<v3_1_1::ProfileType>(v2);
        available = static_cast<v3_1_1::Availability>(v3);
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "Profile header info, type=" << static_cast<holo::uint16_t>(type) << " linkid=" << GetLinkId()
                  << " pathid=" << pathId << " offset=" << offset << " endOffset=" << endOffset
                  << " confidence=" << confidence << " interpolat="
                  << static_cast<holo::uint16_t>(interpolat)
                  // << "  , direction=" << static_cast<holo::uint16_t>(direction)
                  << " IsRoadProfile=" << IsRoadProfile()
                  << " laneNumber=" << static_cast<holo::uint16_t>(laneNumber);
    }

public:
    holo::uint64_t GetLinkId()
    {
        return instanceId;
    }

    holo::bool_t IsRoadProfile()
    {
        return laneNumber == 0;
    }

public:
    holo::uint8_t interpolat = 0;
    holo::uint8_t laneNumber = 0;
};

/**
 * @brief ADASIS V3 profile entry, compose of one profile header and one object T.
 * @tparam T ADASIS V3 profile value.
 */
template <typename T>
class OneProfileEntry
{
public:
    void Serialize(Serializer& s) const
    {
        s << header << entry;
    }
    void Deserialize(Deserializer& s)
    {
        s >> header >> entry;
    }

public:
    void PrintDebugInfo()
    {
        header.PrintDebugInfo();
        entry.PrintDebugInfo();
    }
public:
    ProfileHeader header;
    T entry;
};

/**
 * @brief ADASIS V3 profile entry, compose of one profile header and object array T.
 * @tparam T ADASIS V3 profile value.
 */
template <typename T>
class MultiProfileEntry
{
public:
    void Serialize(Serializer& s) const
    {
        s << header << entries;
    }
    void Deserialize(Deserializer& s)
    {
        s >> header >> entries;
    }

public:
    void PrintDebugInfo()
    {
        header.PrintDebugInfo();
        for (std::size_t i = 0; i < entries.size(); i++)
        {
            T entry = entries[i];
            entry.PrintDebugInfo(i);
        }
    }
public:
    ProfileHeader header;
    std::vector<T> entries;
};

/**
 * @brief Baidu ADASIS V3 global data message.
 */
class GlobalDataMessage
{
public:
    void Serialize(Serializer& s) const
    {
        s << driving_side
          << country_code
          << unit_system
          << ver_protocol
          << version_hw
          << version_map
          << map_age
          << map_provider
          << sys_status;
    }

    void Deserialize(Deserializer& s)
    {
        s >> driving_side 
          >> country_code 
          >> unit_system 
          >> ver_protocol 
          >> version_hw 
          >> version_map 
          >> map_age 
          >> map_provider 
          >> sys_status;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "GlobalDataMessage info, driving_side=" << static_cast<holo::uint16_t>(driving_side.value.value)
                  << " country_code=" << country_code.value.value
                  << " unit_system=" << static_cast<holo::uint16_t>(unit_system.value.value)
                  << " ver_protocol=" << ver_protocol.value.value
                  << " version_hw=" << version_hw.value.value
                  << " version_map=" << version_map.value.value
                  << " map_age=" << map_age.value.value
                  << " map_provider=" << static_cast<holo::uint16_t>(map_provider.value.value)
                  << " sys_status.guidance=" << static_cast<holo::uint16_t>(sys_status.value.guidance)
                  << " sys_status.simulating=" << sys_status.value.simulating;
    }

public:
    v3_1_1::GlobalData<v3_1_1::DrivingSideProfileValue>     driving_side;
    v3_1_1::GlobalData<v3_1_1::CountryCodeProfileValue>     country_code;
    v3_1_1::GlobalData<v3_1_1::UnitSystemProfileValue>      unit_system;
    v3_1_1::GlobalData<v3_1_1::VersionProtocolProfileValue> ver_protocol;
    v3_1_1::GlobalData<v3_1_1::VersionHardwareProfileValue> version_hw;
    v3_1_1::GlobalData<v3_1_1::VersionMapProfileValue>      version_map;
    v3_1_1::GlobalData<v3_1_1::MapAgeProfileValue>          map_age;
    v3_1_1::GlobalData<v3_1_1::MapProviderProfileValue>     map_provider;
    v3_1_1::GlobalData<v3_1_1::SystemStatusProfileValue>    sys_status;
};

/**
 * @brief Baidu ADASIS V3 laneinfo definition.
 * @detail two change point compare with standard ADASIS V3:
 *         1. add lane_id property ahead;
 *         2. lanenum is one laneindex, not laneindex array.
 */
class BDLaneInfo : public v3_1_1::LaneInfo
{
public:
    void Serialize(Serializer& s) const
    {
        s << lane_id 
          << laneNumber
          << static_cast<holo::uint8_t>(direction) 
          << static_cast<holo::uint8_t>(transition) 
          << types
          << centerline 
          << leftBoundary 
          << rightBoundary;
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        s >> lane_id 
          >> laneNumber 
          >> v1 
          >> v2 
          >> types 
          >> centerline 
          >> leftBoundary 
          >> rightBoundary;
        direction  = static_cast<v3_1_1::RelativeDirection>(v1);
        transition = static_cast<v3_1_1::LaneTransition>(v2);
    }

public:
    void PrintDebugInfo(std::size_t index = 0)
    {
        LOG(INFO) << "LaneInfo info, index=" << index + 1
                  << " lane_id=" << lane_id
                  << " laneNumber=" << static_cast<holo::uint16_t>(laneNumber)
                  << " types=" << types
                  << " direction=" << static_cast<holo::uint16_t>(direction)
                  << " transition=" << static_cast<holo::uint16_t>(transition)
                  << " centerline=" << centerline
                  << " left_bound=" << leftBoundary
                  << " right_bound=" << rightBoundary;
    }

public:
    holo::uint32_t lane_id = 0;
};

/**
 * @brief Baidu ADASIS V3 Number of lanes per direction.
 * @detail one change point compare with standard ADASIS V3:
 *         1. use one byte instead of four byte.
 */
class NumberOfLanesPerDirection
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<uint8_t>(num_of_lane);
    }
    void Deserialize(Deserializer& s)
    {
        s >> num_of_lane;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "NumberOfLanesPerDirection info, numoflane=" << static_cast<holo::uint16_t>(num_of_lane);
    }
public:
    holo::uint8_t num_of_lane = 0;
};

/**
 * @brief Baidu ADASIS V3 LINKIDENTIFIER.
 */
class LinkIdentifier
{
public:
    void Serialize(Serializer& s) const
    {
        s << link_id;
    }

    void Deserialize(Deserializer& s)
    {
        s >> link_id;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "LinkIdentifier info, link_id=" << link_id;
    }

public:
    holo::uint64_t link_id;
};

/**
 * @brief Baidu ADASIS V3 road class.
 * @detail standard ADASIS V3 use uint32 but none detail defition.
 *         baidu-v3 use one byte instead of four byte and
 *         current definition only for hightway scene.
 */
class FunctionalRoadClass
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(road_class);
    }

    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        s >> v1;
        road_class = static_cast<BaiduFunctionalRoadClass>(v1);
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "FuncClass info, func_class=" << static_cast<holo::uint16_t>(road_class);
    }

public:
    BaiduFunctionalRoadClass road_class = BaiduFunctionalRoadClass::Highway;
};

class BDFormOfWay
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(form_of_way);
    }

    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        s >> v1;
        form_of_way = static_cast<BaiduFormOfWay>(v1);
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "FormOfWay info, form_of_way=" << static_cast<holo::uint16_t>(form_of_way);
    }

public:
    BaiduFormOfWay form_of_way = BaiduFormOfWay::FormOfWay_Normal;
};

/**
 * @brief Baidu ADASIS V3 tunnel profile value.
 */
class Tunnel
{
public:
    void Serialize(Serializer& s) const
    {
        s << value;
    }

    void Deserialize(Deserializer& s)
    {
        s >> value;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "Tunnel info, Tunnel=" << value.value;
    }

public:
    v3_1_1::TunnelProfileValue value;
};

/**
 * @}
 */

} // namespace baidu_v3
} // namespace adasis
} // namespace map
} // namespace holo

#endif // HOLO_MAP_ADASIS_BAIDU_V3_MSG_PAYLOAD_H_