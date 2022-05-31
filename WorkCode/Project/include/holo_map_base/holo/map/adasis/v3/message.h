/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file AdasisMessageBase.h
 * @brief This header file defines the base adasis v3 message.
 * @author zhengshulei@holomatic.com
 * @date 2021-09-28
 */
#ifndef HOLO_MAP_ADASIS_V3_ADASISMESSAGEBASE_H_
#define HOLO_MAP_ADASIS_V3_ADASISMESSAGEBASE_H_

#include <holo/map/adasis/v3/profile_value.h>

namespace holo
{
namespace map
{
namespace adasis
{
namespace v3_1_1
{
class AdasisMessageBase
{
};

template <typename T>
class GlobalData
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(type) << static_cast<holo::uint8_t>(available) << value;
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        s >> v1 >> v2 >> value;
        type      = static_cast<ProfileType>(v1);
        available = static_cast<Availability>(v2);
    }

public:
    ProfileType type       = ProfileType::CountryCode;
    Availability available = Availability::NotAvailable;
    T value;
};

// class GlobalDataMessage : public AdasisMessageBase
// {
// public:
//     GlobalDataMessage()
//     {
//     }
//     ~GlobalDataMessage()
//     {
//     }

// public:
//     void Serialize(Serializer& s) const
//     {
//         s << data;
//     }
//     void Deserialize(Deserializer& s)
//     {
//         s >> data;
//     }

// public:
//     std::vector<GlobalData> data;
// };

class PathControl
{
public:
    PathControl() {}
    ~PathControl() {}

public:
    void Serialize(Serializer& s) const { s << Id << parentId << offset; }
    void Deserialize(Deserializer& s) { s >> Id >> parentId >> offset; }

public:
    bool operator==(const PathControl& ptc) { return Id == ptc.Id; }

public:
    PathId Id       = 0;
    PathId parentId = 0;
    Offset offset   = 0;
};

class PathControlMessage : public AdasisMessageBase
{
public:
    PathControlMessage() {}
    ~PathControlMessage() {}

public:
    void Serialize(Serializer& s) const { s << idFirst << idLast << values; }
    void Deserialize(Deserializer& s) { s >> idFirst >> idLast >> values; }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "PathControlMessage info, idFirst=" << idFirst << " idLast=" << idLast;
        for (std::size_t i = 0; i < values.size(); i++)
        {
            v3_1_1::PathControl ptc = values[i];
            LOG(INFO) << "PathControl info, parentId=" << ptc.parentId << " id=" << ptc.Id << " offset=" << ptc.offset;
        }
    }

public:
    PathId idFirst = 0;
    PathId idLast  = 0;
    std::vector<PathControl> values;
};

class Position
{
public:
    Position() {}
    ~Position() {}

public:
    void Serialize(Serializer& s) const
    {
        s << pathId << offset << accuracy << deviation << speed << relativeHeading << probability << currentLane
          << preferredPath;
    }
    void Deserialize(Deserializer& s)
    {
        s >> pathId >> offset >> accuracy >> deviation >> speed >> relativeHeading >> probability >> currentLane >>
            preferredPath;
    }

public:
    PathId pathId           = 0;
    Offset offset           = 0;
    Distance accuracy       = 0;
    holo::int32_t deviation = 0;
    VehicleSpeed speed      = 0;
    Angle relativeHeading   = 0;
    Probability probability = 0;
    LaneIdx currentLane     = 0;
    PathId preferredPath    = 0;
};

class PositionMessage : public AdasisMessageBase
{
public:
    PositionMessage() {}
    ~PositionMessage() {}

public:
    void Serialize(Serializer& s) const { s << timestamp << positionAge << positions; }
    void Deserialize(Deserializer& s) { s >> timestamp >> timestamp >> positions; }

public:
    Timestamp timestamp   = 0;
    Timestamp positionAge = 0;
    std::vector<Position> positions;
};

class ProfileControl
{
public:
    ProfileControl() {}
    ~ProfileControl() {}

public:
    void Serialize(Serializer& s) const { s << pathId << offset; }
    void Deserialize(Deserializer& s) { s >> pathId >> offset; }

public:
    void PrintDebugInfo() { LOG(INFO) << "ProfileControl info, pathid=" << pathId << " offset=" << offset; }

public:
    PathId pathId = 0;
    Offset offset = 0;
};

class ProfileControlMessage : public AdasisMessageBase
{
public:
    ProfileControlMessage() {}
    ~ProfileControlMessage() {}

public:
    void Serialize(Serializer& s) const { s << values; }
    void Deserialize(Deserializer& s) { s >> values; }

public:
    std::vector<ProfileControl> values;
};

class ProfileHeader
{
public:
    ProfileHeader() {}
    ~ProfileHeader() {}

public:
    void Serialize(Serializer& s) const
    {
        s << instanceId << isRetransmission << static_cast<holo::uint8_t>(change) << confidence << pathId << laneNumbers
          << static_cast<holo::uint8_t>(direction) << offset << endOffset << endOffsetFinal
          << static_cast<holo::uint8_t>(type) << static_cast<holo::uint8_t>(available);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        holo::uint8_t v3;
        holo::uint8_t v4;
        s >> instanceId >> isRetransmission >> v1 >> confidence >> pathId >> laneNumbers >> v2 >> offset >> endOffset >>
            endOffsetFinal >> v3 >> v4;
        change    = static_cast<ChangeMode>(v1);
        direction = static_cast<RelativeDirection>(v2);
        type      = static_cast<ProfileType>(v3);
        available = static_cast<Availability>(v4);
    }

public:
    InstanceId instanceId         = 0;
    holo::bool_t isRetransmission = false;
    ChangeMode change             = ChangeMode::Create;
    holo::float32_t confidence    = 100;
    PathId pathId                 = 0;
    std::vector<LaneIdx> laneNumbers;
    RelativeDirection direction = RelativeDirection::AlongPathDirection;
    Offset offset               = 0;
    Offset endOffset            = 0;
    holo::bool_t endOffsetFinal = false;
    ProfileType type            = ProfileType::Node;
    Availability available      = Availability::Valid;
};

class ProfileEntry
{
public:
    ProfileEntry() {}
    ~ProfileEntry() {}

public:
    void Serialize(Serializer& s) const
    {
        s << Header;
        // todo: store profilevalue by type
        // s<<*value
    }
    void Deserialize(Deserializer& s)
    {
        s >> Header;
        // todo: store profilevalue by type
        // s>>*value
    }

public:
    ProfileHeader Header;
    ProfileValue* Value;
};

class ProfileMessage : public AdasisMessageBase
{
public:
    ProfileMessage() {}
    ~ProfileMessage() {}

public:
    void Serialize(Serializer& s) const { s << profiles; }
    void Deserialize(Deserializer& s) { s >> profiles; }

public:
    std::vector<ProfileEntry> profiles;
};

class MessageOnBus
{
public:
    holo::uint8_t cyclicCounter = 0;
    MessageType type            = MessageType::Profile;
    AdasisMessageBase* message;
};

} // namespace v3_1_1
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_V3_ADASISMESSAGEBASE_H_ */