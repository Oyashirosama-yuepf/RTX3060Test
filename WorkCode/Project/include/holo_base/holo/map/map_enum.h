/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_enum.h
 * @brief Map enumerate
 * @author zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#ifndef HOLO_MAP_MAP_ENUM_H__
#define HOLO_MAP_MAP_ENUM_H__

#include <iostream>

#include <holo/core/types.h>

// Update here if new model is added ///////////
#define ENUM_CROSSING_MODEL_TYPE                                                                                       \
    X(DESTINATION)                                                                                                     \
    X(TOLL_ENTRANCE)                                                                                                   \
    X(TOLL_STOP)                                                                                                       \
    X(TOLL_EXIT)                                                                                                       \
    X(TOLL_ETC_ENTRANCE)                                                                                               \
    X(TOLL_ETC_SLOW)                                                                                                   \
    X(TOLL_ETC_EXIT)                                                                                                   \
    X(TUNNEL_ENTRANCE)                                                                                                 \
    X(TUNNEL_EXIT)                                                                                                     \
    X(MOTORWAY_PASS_BY_ENTRANCE)                                                                                       \
    X(MOTORWAY_PASS_BY_EXIT)                                                                                           \
    X(MOTORWAY_TO_RAMP)                                                                                                \
    X(MOTORWAY_TO_JCT)                                                                                                 \
    X(RAMP_TO_MOTORWAY)                                                                                                \
    X(JCT_TO_MOTORWAY)                                                                                                 \
    X(JCT_SPLIT)                                                                                                       \
    X(JCT_MERGE)                                                                                                       \
    X(MOTORWAY_RIGHT_NARROWED)                                                                                         \
    X(MOTORWAY_RIGHT_EXPANDED)                                                                                         \
    X(MOTORWAY_MIDDLE_NARROWED)                                                                                        \
    X(MOTORWAY_MIDDLE_EXPANDED)                                                                                        \
    X(MOTORWAY_LEFT_NARROWED)                                                                                          \
    X(MOTORWAY_LEFT_EXPANDED)                                                                                          \
    X(MOTORWAY_BOTH_SIDE_NARROWED)                                                                                     \
    X(MOTORWAY_BOTH_SIDE_EXPANDED)                                                                                     \
    X(JCT_RIGHT_NARROWED)                                                                                              \
    X(JCT_RIGHT_EXPANDED)                                                                                              \
    X(JCT_MIDDLE_NARROWED)                                                                                             \
    X(JCT_MIDDLE_EXPANDED)                                                                                             \
    X(JCT_LEFT_NARROWED)                                                                                               \
    X(JCT_LEFT_EXPANDED)                                                                                               \
    X(JCT_BOTH_SIDE_NARROWED)                                                                                          \
    X(JCT_BOTH_SIDE_EXPANDED)                                                                                          \
    X(MOTORWAY_LANE_NUM_INCREASE)                                                                                      \
    X(MOTORWAY_LANE_NUM_DECREASE)                                                                                      \
    X(JCT_LANE_NUM_INCREASE)                                                                                           \
    X(JCT_LANE_NUM_DECREASE)                                                                                           \
    X(ACCELERATION_LANE)                                                                                               \
    X(DECELERATION_LANE)                                                                                               \
    X(JCT)                                                                                                             \
    X(TOLL)                                                                                                            \
    X(TUNNEL)                                                                                                          \
    X(BRIDGE)                                                                                                          \
    X(RAMP_ENTRANCE)                                                                                                   \
    X(RAMP_EXIT)                                                                                                       \
    X(MOTORWAY)                                                                                                        \
    X(NONE_MOTORWAY_AREA)                                                                                              \
    X(RESTRICT_ROAD)                                                                                                   \
    X(MAP_ERROR)                                                                                                       \
    X(NO_MODEL)                                                                                                        \
    X(ENUM_MODEL_TYPE_MAX)

/// Define link type.
#define ENUM_COMMON_LINK_TYPE                                                                                          \
    X(LINK_TYPE_UNDEFINED)                                                                                             \
    X(LINK_TYPE_MOTORWAY)                                                                                              \
    X(LINK_TYPE_MOTORWAY_BRIDGE)                                                                                       \
    X(LINK_TYPE_MOTORWAY_TUNNEL)                                                                                       \
    X(LINK_TYPE_MOTORWAY_RAMP_ENTRANCE)                                                                                \
    X(LINK_TYPE_MOTORWAY_RAME_EXIT)                                                                                    \
    X(LINK_TYPE_MOTORWAY_JCT)                                                                                          \
    X(LINK_TYPE_MOTORWAY_TOLL)                                                                                         \
    X(LINK_TYPE_MOTORWAY_TOLL_ENTRANCE)                                                                                \
    X(LINK_TYPE_MOTORWAY_TOOL_EXIT)                                                                                    \
    X(LINK_TYPE_MAX)

/// define lane type according to the data
#define ENUM_COMMON_LANE_TYPE                                                                                          \
    X(LANE_TYPE_UNDEFINED)                                                                                             \
    X(LANE_TYPE_REGULAR)                                                                                               \
    X(LANE_TYPE_ACCELERATION)                                                                                          \
    X(LANE_TYPE_DECELERATION)                                                                                          \
    X(LANE_TYPE_HOV)                                                                                                   \
    X(LANE_TYPE_SLOW)                                                                                                  \
    X(LANE_TYPE_PASSING_OVERTAKING)                                                                                    \
    X(LANE_TYPE_HARD_SHOULDER)                                                                                         \
    X(LANE_TYPE_TRUCK_PARKING)                                                                                         \
    X(LANE_TYPE_REGULATED_ACCESS)                                                                                      \
    X(LANE_TYPE_SOFT_SHOULDER)                                                                                         \
    X(LANE_TYPE_EMERGENCY_PARKING_STRIP)                                                                               \
    X(LANE_TYPE_BUS)                                                                                                   \
    X(LANE_TYPE_BICYCLE)                                                                                               \
    X(LANE_TYPE_TURN)                                                                                                  \
    X(LANE_TYPE_REVERSIBLE)                                                                                            \
    X(LANE_TYPE_CENTER_TUEN)                                                                                           \
    X(LANE_TYPE_TRUCK_ESCAPE)                                                                                          \
    X(LANE_TYPE_VARIABLE_DRIVING_LANE)                                                                                 \
    X(LANE_TYPE_PARKING_LANE)                                                                                          \
    X(LANE_TYPE_COMPOUND_LANE)                                                                                         \
    X(LANE_TYPE_JUNCTION_LANE)                                                                                         \
    X(LANE_TYPE_ROUNDABOUT_LANE)                                                                                       \
    X(LANE_TYPE_OTHER)                                                                                                 \
    X(LANE_TYPE_MAX)

/// Define lane translation type.
#define ENUM_COMMON_LANE_TRANS_TYPE                                                                                    \
    X(LANE_TRANS_TYPE_NO_ATTRIBUTE)                                                                                    \
    X(LANE_TRANS_TYPE_MERGE_TO_LEFT_FORBIDDEN)                                                                         \
    X(LANE_TRANS_TYPE_MERGE_TO_RIGHT_FORBIDDEN)                                                                        \
    X(LANE_TRANS_TYPE_MERGE_TO_LEFT_OPTIONAL)                                                                          \
    X(LANE_TRANS_TYPE_MERGE_TO_LEFT_FORCED)                                                                            \
    X(LANE_TRANS_TYPE_MERGE_TO_RIGHT_OPTIONAL)                                                                         \
    X(LANE_TRANS_TYPE_MERGE_TO_RIGHT_FORCED)                                                                           \
    X(LANE_TRANS_TYPE_MERGED_BY_LEFT)                                                                                  \
    X(LANE_TRANS_TYPE_MERGED_BY_RIGHT)                                                                                 \
    X(LANE_TRANS_TYPE_MAX)

/// define lane mark color according to the data
#define ENUM_MARK_COLOR_TYPE                                                                                           \
    X(MARK_COLOR_NOT_APPLICABLE)                                                                                       \
    X(MARK_COLOR_OTHERS)                                                                                               \
    X(MARK_COLOR_WHITE)                                                                                                \
    X(MARK_COLOR_YELLOW)                                                                                               \
    X(MARK_COLOR_LEFT_YELLOW_RIGHT_WHITE)                                                                              \
    X(MARK_COLOR_LEFT_WHITE_RIGHT_YELLOW)                                                                              \
    X(MARK_COLOR_MAX)
/// define lane mark type according to the data
#define ENUM_MARK_TYPE_TYPE                                                                                            \
    X(MARK_TYPE_NOT_INVESTIGATED)                                                                                      \
    X(MARK_TYPE_SINGLE_DASHED)                                                                                         \
    X(MARK_TYPE_SHORT_THICK_DASHED)                                                                                    \
    X(MARK_TYPE_DOUBLE_DASHED)                                                                                         \
    X(MARK_TYPE_SINGLE_SOLID)                                                                                          \
    X(MARK_TYPE_DOUBLE_SOLID)                                                                                          \
    X(MARK_TYPE_LEFT_SOLID_RIGHT_DASHED)                                                                               \
    X(MARK_TYPE_LEFT_DASHED_RIGHT_SOLID)                                                                               \
    X(MARK_TYPE_VIRTUAL_MARKING)                                                                                       \
    X(MARK_TYPE_MAX)

/// define lane mark material according to the data
#define ENUM_MARK_MATERIAL_TYPE                                                                                        \
    X(MARK_MATERIAL_NOT_APPLICABLE)                                                                                    \
    X(MARK_MATERIAL_PAINTED)                                                                                           \
    X(MARK_MATERIAL_RAISED_PAVEMENT_MARKER)                                                                            \
    X(MARK_MATERIAL_PAINTED_AND_RAISED_PAVEMENT_MARKER)                                                                \
    X(MARK_MATERIAL_MAX)

/// define rhombus deceleration mark according to the data
#define ENUM_MARK_RHOMBUS_DECELERATION_TYPE                                                                            \
    X(RHOMBUS_DECELERATION_MARKING_NOT_APPLICABLE)                                                                     \
    X(RHOMBUS_DECELERATION_MARKING_RIGHT)                                                                              \
    X(RHOMBUS_DECELERATION_MARKING_LEFT)                                                                               \
    X(RHOMBUS_DECELERATION_MARKING_BOTH)                                                                               \
    X(RHOMBUS_DECELERATION_MAX)

#define ENUM_OBJECT_TYPE                                                                                               \
    X(TYPE_UNDEFINED)                                                                                                  \
    X(TYPE_CURB)                                                                                                       \
    X(TYPE_TRAFFIC_BARRIER)                                                                                            \
    X(TYPE_OVERHEAD_CROSSING)                                                                                          \
    X(TYPE_TUNNEL)                                                                                                     \
    X(TYPE_GANTRY)                                                                                                     \
    X(TYPE_TRAFFIC_SIGN)                                                                                               \
    X(TYPE_VARIABLE_MESSAGE_SIGN)                                                                                      \
    X(TYPE_PERMANENT_DELINEATORS)                                                                                      \
    X(TYPE_TOLL_BOOTH)                                                                                                 \
    X(TYPE_EMERGENCY_CALL_BOX)                                                                                         \
    X(TYPE_DITCH)                                                                                                      \
    X(TYPE_POLE)                                                                                                       \
    X(TYPE_BUILDING)                                                                                                   \
    X(TYPE_TRAFFIC_LIGHTS)                                                                                             \
    X(TYPE_WALL)                                                                                                       \
    X(TYPE_ARROWS)                                                                                                     \
    X(TYPE_TEXT)                                                                                                       \
    X(TYPE_SYMBOL)                                                                                                     \
    X(TYPE_WARNING_AREA)                                                                                               \
    X(TYPE_FILL_AREA)                                                                                                  \
    X(TYPE_PARKING_SPACE)                                                                                              \
    X(TYPE_UNKNOWN)

/*----------------------------------------------------------------------------------------*/
namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */

/*------------------------------------------------------------------------------------------- */
// Update here if new model is added ///////////
enum class CrossingType : ::holo::uint8_t
{
#define X(type) type,
    ENUM_CROSSING_MODEL_TYPE
#undef X

};
char const* const CrossingTypeName[] = {
#define X(name) #name,
    ENUM_CROSSING_MODEL_TYPE
#undef X
};

inline std::ostream& operator<<(std::ostream& os, enum CrossingType c)
{
    if (c >= CrossingType::ENUM_MODEL_TYPE_MAX || c < CrossingType::DESTINATION)
    {
        return os << "???";
    }
    return os << CrossingTypeName[static_cast< ::holo::int8_t>(c)];
}

/*------------------------------------------------------------------------------------------- */
enum class CommonLinkType : ::holo::uint8_t
{
#define X(type) type,
        ENUM_COMMON_LINK_TYPE
#undef X
};
char const* const CommonLinkTypeName[] = {
#define X(name) #name,
    ENUM_COMMON_LINK_TYPE
#undef X
};
inline ::std::ostream& operator<<(std::ostream& os, const enum CommonLinkType c)
{
    if (c >= CommonLinkType::LINK_TYPE_MAX || c < CommonLinkType::LINK_TYPE_UNDEFINED)
    {
        return os << "???";
    }
    return os << CommonLinkTypeName[static_cast<::holo::int8_t>(c)];
}

/*------------------------------------------------------------------------------------------- */
/// define lane type according to the data
enum class CommonLaneType : ::holo::uint8_t
{
#define X(type) type,
    ENUM_COMMON_LANE_TYPE
#undef X

};
char const* const CommonLaneTypeName[] = {
#define X(name) #name,
    ENUM_COMMON_LANE_TYPE
#undef X
};
inline ::std::ostream& operator<<(std::ostream& os, enum CommonLaneType c)
{
    if (c >= CommonLaneType::LANE_TYPE_MAX || c < CommonLaneType::LANE_TYPE_UNDEFINED)
    {
        return os << "???";
    }
    return os << CommonLaneTypeName[static_cast< ::holo::int8_t>(c)];
}

/*------------------------------------------------------------------------------------------- */
enum class CommonLaneTransType : ::holo::uint8_t
{
#define X(type) type,
    ENUM_COMMON_LANE_TRANS_TYPE
#undef X
};
char const* const CommonLaneTransTypeName[] = {
#define X(name) #name,
    ENUM_COMMON_LANE_TRANS_TYPE
#undef X
};
inline ::std::ostream& operator<<(std::ostream& os, const enum CommonLaneTransType c)
{
    if (c >= CommonLaneTransType::LANE_TRANS_TYPE_MAX || c < CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE)
    {
        return os << "???";
    }
    return os << CommonLaneTransTypeName[static_cast<::holo::int8_t>(c)];
}

/*------------------------------------------------------------------------------------------- */
enum class CommonMarkColor : ::holo::uint8_t
{
#define X(type) type,
    ENUM_MARK_COLOR_TYPE
#undef X

};
char const* const CommonMarkColorName[] = {
#define X(name) #name,
    ENUM_MARK_COLOR_TYPE
#undef X
};
inline ::std::ostream& operator<<(std::ostream& os, enum CommonMarkColor c)
{
    if (c >= CommonMarkColor::MARK_COLOR_MAX || c < CommonMarkColor::MARK_COLOR_NOT_APPLICABLE)
    {
        return os << "???";
    }
    return os << CommonMarkColorName[static_cast< ::holo::int8_t>(c)];
}
/*------------------------------------------------------------------------------------------- */
/// define lane mark type according to the data
enum class CommonMarkType : ::holo::uint8_t
{
#define X(type) type,
    ENUM_MARK_TYPE_TYPE
#undef X

};
char const* const CommonMarkTypeName[] = {
#define X(name) #name,
    ENUM_MARK_TYPE_TYPE
#undef X
};
inline ::std::ostream& operator<<(std::ostream& os, enum CommonMarkType c)
{
    if (c >= CommonMarkType::MARK_TYPE_MAX || c < CommonMarkType::MARK_TYPE_NOT_INVESTIGATED)
    {
        return os << "???";
    }
    return os << CommonMarkTypeName[static_cast< ::holo::int8_t>(c)];
}
/*------------------------------------------------------------------------------------------- */
/// define lane mark material according to the data
enum class CommonMarkMaterial : ::holo::uint8_t
{
#define X(type) type,
    ENUM_MARK_MATERIAL_TYPE
#undef X

};
char const* const CommonMarkMaterialName[] = {
#define X(name) #name,
    ENUM_MARK_MATERIAL_TYPE
#undef X
};
inline ::std::ostream& operator<<(std::ostream& os, enum CommonMarkMaterial c)
{
    if (c >= CommonMarkMaterial::MARK_MATERIAL_MAX || c < CommonMarkMaterial::MARK_MATERIAL_NOT_APPLICABLE)
    {
        return os << "???";
    }
    return os << CommonMarkMaterialName[static_cast< ::holo::int8_t>(c)];
}
/*------------------------------------------------------------------------------------------- */
/// define rhombus deceleration mark according to the data
enum class CommonRhombusDecelerationMarking : ::holo::uint8_t
{
#define X(type) type,
    ENUM_MARK_RHOMBUS_DECELERATION_TYPE
#undef X

};
char const* const CommonRhombusDecelerationMarkingName[] = {
#define X(name) #name,
    ENUM_MARK_RHOMBUS_DECELERATION_TYPE
#undef X
};
inline ::std::ostream& operator<<(std::ostream& os, enum CommonRhombusDecelerationMarking c)
{
    if (c >= CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MAX ||
        c < CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MARKING_NOT_APPLICABLE)
    {
        return os << "???";
    }
    return os << CommonRhombusDecelerationMarkingName[static_cast< ::holo::int8_t>(c)];
}

/*------------------------------------------------------------------------------------------- */
/// define rhombus deceleration mark according to the data
enum class ObjectType : ::holo::uint8_t
{
#define X(type) type,
    ENUM_OBJECT_TYPE
#undef X

};
char const* const ObjectTypeName[] = {
#define X(name) #name,
    ENUM_OBJECT_TYPE
#undef X
};
inline ::std::ostream& operator<<(std::ostream& os, enum ObjectType c)
{
    if (c >= ObjectType::TYPE_UNDEFINED || c < ObjectType::TYPE_PARKING_SPACE)
    {
        return os << "???";
    }
    return os << ObjectTypeName[static_cast< ::holo::int8_t>(c)];
}

/**
 * @}
 *
 */
}  // namespace map
}  // namespace holo

// #undef ENUM_MODEL_TYPE

#endif  // HOLO_MAP_MAP_ENUM_H__
