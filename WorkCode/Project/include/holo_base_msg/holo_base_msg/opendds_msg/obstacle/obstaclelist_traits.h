#ifndef OPENDDS_MSG_OBSTACLE_OBSTACLELIST_TRAITS_H_
#define OPENDDS_MSG_OBSTACLE_OBSTACLELIST_TRAITS_H_

#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_radar.h>
#include <holo/obstacle/obstacle_uss.h>
#include <holo/obstacle/obstacle_vision.h>

#include <opendds_wrapper/traits.h>

#include <holo_base_msg/obstacle/ObstacleSetC.h>
#include <holo_base_msg/obstacle/ObstacleSetS.h>
#include <holo_base_msg/obstacle/ObstacleSetTypeSupportC.h>
#include <holo_base_msg/obstacle/ObstacleSetTypeSupportS.h>
#include <holo_base_msg/obstacle/ObstacleSetTypeSupportImpl.h>

namespace opendds_wrapper
{
/* ObstacleGeneral traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::obstacle::ObstacleGeneral>
{
    using ValueType   = ::holo_base_msg::obstacle::ObstacleGeneral;
    using MessageType = ::holo_base_msg::obstacle::ObstacleGeneral;
};

template <>
struct DefaultMessageTraits<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>>
{
    using ValueType   = ::holo::obstacle::ObstacleGeneralT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleGeneral;
};

template <>
struct DefaultConversionTraits<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>>
{
    using ValueType   = ::holo::obstacle::ObstacleGeneralT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleGeneral;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

/* ObstacleGeneralList traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::obstacle::ObstacleGeneralList>
{
    using ValueType   = ::holo_base_msg::obstacle::ObstacleGeneralList;
    using MessageType = ::holo_base_msg::obstacle::ObstacleGeneralList;
};

template <size_t OBS_SIZE>
struct DefaultMessageTraits<::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>, OBS_SIZE>>
{
    using ValueType   = ::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>, OBS_SIZE>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleGeneralList;
};

template <size_t OBS_SIZE>
struct DefaultConversionTraits<::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>, OBS_SIZE>>
{
    using ValueType   = ::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>, OBS_SIZE>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleGeneralList;

    static void Convert(ValueType const& value, MessageType& message)
    {
        // timestamp
        message.stamp = ::holo_base_msg::common::Timestamp{value.GetTimestamp().GetSec(), value.GetTimestamp().GetNsec()};

        // coord
        message.coord = static_cast<uint32_t>(value.GetCoordinate());

        // sensor_id
        message.sensor_id = value.GetSensorId();

        // perception_ability
        message.perception_ability = value.GetPerceptionAbility();

        // obstacle_list
        message.obstacles.length(value.GetSize());
        for (size_t i = 0; i < value.GetSize(); ++i)
        {
            if (value.GetObstacleList()[i] == nullptr)
            {
                throw std::runtime_error("ERROR: Invalid nullptr obstacle list in convertor!");
            }
            opendds_wrapper::DefaultConversionTraits<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>>::Convert(
                *value.GetObstacleList()[i], message.obstacles[i]);
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        // timestamp_
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});

        // coord_
        value.SetCoordinate(message.coord);

        // sensor_id_
        value.SetSensorId(message.sensor_id);

        // size_
        uint32_t size = message.obstacles.length() > OBS_SIZE ? OBS_SIZE : message.obstacles.length();
        value.SetSize(size);

        // perception_ability_
        value.SetPerceptionAbility(message.perception_ability);

        auto& output_obstacle_list = value.GetObstacleList();

        for (size_t i = 0; i < size; ++i)
        {
            output_obstacle_list[i] = std::make_shared<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>>();
            opendds_wrapper::DefaultConversionTraits<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>>::Convert(
                message.obstacles[i], *output_obstacle_list[i]);
        }
    }
};

/* ObstacleRadar traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::obstacle::ObstacleRadar>
{
    using ValueType   = ::holo_base_msg::obstacle::ObstacleRadar;
    using MessageType = ::holo_base_msg::obstacle::ObstacleRadar;
};

template <>
struct DefaultMessageTraits<::holo::obstacle::ObstacleRadarT<::holo::float32_t>>
{
    using ValueType   = ::holo::obstacle::ObstacleRadarT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleRadar;
};

template <>
struct DefaultConversionTraits<::holo::obstacle::ObstacleRadarT<::holo::float32_t>>
{
    using ValueType   = ::holo::obstacle::ObstacleRadarT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleRadar;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

/* ObstacleRadarList traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::obstacle::ObstacleRadarList>
{
    using ValueType   = ::holo_base_msg::obstacle::ObstacleRadarList;
    using MessageType = ::holo_base_msg::obstacle::ObstacleRadarList;
};

template <size_t OBS_SIZE>
struct DefaultMessageTraits<::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleRadarT<::holo::float32_t>, OBS_SIZE>>
{
    using ValueType   = ::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleRadarT<::holo::float32_t>, OBS_SIZE>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleRadarList;
};

template <size_t OBS_SIZE>
struct DefaultConversionTraits<::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleRadarT<::holo::float32_t>, OBS_SIZE>>
{
    using ValueType   = ::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleRadarT<::holo::float32_t>, OBS_SIZE>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleRadarList;

    static void Convert(ValueType const& value, MessageType& message)
    {
        // timestamp
        message.stamp = ::holo_base_msg::common::Timestamp{value.GetTimestamp().GetSec(), value.GetTimestamp().GetNsec()};

        // coord
        message.coord = static_cast<uint32_t>(value.GetCoordinate());

        // sensor_id
        message.sensor_id = value.GetSensorId();

        // perception_ability
        message.perception_ability = value.GetPerceptionAbility();

        // obstacle_list
        message.obstacles.length(value.GetSize());
        for (size_t i = 0; i < value.GetSize(); ++i)
        {
            if (value.GetObstacleList()[i] == nullptr)
            {
                throw std::runtime_error("ERROR: Invalid nullptr obstacle list in convertor!");
            }
            opendds_wrapper::DefaultConversionTraits<::holo::obstacle::ObstacleRadarT<::holo::float32_t>>::Convert(
                *value.GetObstacleList()[i], message.obstacles[i]);
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        // timestamp_
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});

        // coord_
        value.SetCoordinate(message.coord);

        // sensor_id_
        value.SetSensorId(message.sensor_id);

        // size_
        uint32_t size = message.obstacles.length() > OBS_SIZE ? OBS_SIZE : message.obstacles.length();
        value.SetSize(size);

        // perception_ability_
        value.SetPerceptionAbility(message.perception_ability);

        // obstacle_list_
        auto& output_obstacle_list = value.GetObstacleList();
        for (size_t i = 0; i < size; ++i)
        {
            output_obstacle_list[i] = std::make_shared<::holo::obstacle::ObstacleRadarT<::holo::float32_t>>();
            opendds_wrapper::DefaultConversionTraits<::holo::obstacle::ObstacleRadarT<::holo::float32_t>>::Convert(
                message.obstacles[i], *output_obstacle_list[i]);
        }
    }
};

/* ObstacleUss traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::obstacle::ObstacleUss>
{
    using ValueType   = ::holo_base_msg::obstacle::ObstacleUss;
    using MessageType = ::holo_base_msg::obstacle::ObstacleUss;
};

template <>
struct DefaultMessageTraits<::holo::obstacle::ObstacleUssT<::holo::float32_t>>
{
    using ValueType   = ::holo::obstacle::ObstacleUssT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleUss;
};

template <>
struct DefaultConversionTraits<::holo::obstacle::ObstacleUssT<::holo::float32_t>>
{
    using ValueType   = ::holo::obstacle::ObstacleUssT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleUss;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

/* ObstacleUssList traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::obstacle::ObstacleUssList>
{
    using ValueType   = ::holo_base_msg::obstacle::ObstacleUssList;
    using MessageType = ::holo_base_msg::obstacle::ObstacleUssList;
};

template <size_t OBS_SIZE>
struct DefaultMessageTraits<::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleUssT<::holo::float32_t>, OBS_SIZE>>
{
    using ValueType   = ::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleUssT<::holo::float32_t>, OBS_SIZE>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleUssList;
};

template <size_t OBS_SIZE>
struct DefaultConversionTraits<::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleUssT<::holo::float32_t>, OBS_SIZE>>
{
    using ValueType   = ::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleUssT<::holo::float32_t>, OBS_SIZE>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleUssList;

    static void Convert(ValueType const& value, MessageType& message)
    {
        // timestamp
        message.stamp = ::holo_base_msg::common::Timestamp{value.GetTimestamp().GetSec(), value.GetTimestamp().GetNsec()};

        // coord
        message.coord = static_cast<uint32_t>(value.GetCoordinate());

        // sensor_id
        message.sensor_id = value.GetSensorId();

        // perception_ability
        message.perception_ability = value.GetPerceptionAbility();

        // obstacle_list
        message.obstacles.length(value.GetSize());
        for (size_t i = 0; i < value.GetSize(); ++i)
        {
            if (value.GetObstacleList()[i] == nullptr)
            {
                throw std::runtime_error("ERROR: Invalid nullptr obstacle list in convertor!");
            }
            opendds_wrapper::DefaultConversionTraits<::holo::obstacle::ObstacleUssT<::holo::float32_t>>::Convert(
                *value.GetObstacleList()[i], message.obstacles[i]);
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        // timestamp_
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});

        // coord_
        value.SetCoordinate(message.coord);

        // sensor_id_
        value.SetSensorId(message.sensor_id);

        // size_
        uint32_t size = message.obstacles.length() > OBS_SIZE ? OBS_SIZE : message.obstacles.length();
        value.SetSize(size);

        // perception_ability_
        value.SetPerceptionAbility(message.perception_ability);

        // obstacle_list_
        auto& output_obstacle_list = value.GetObstacleList();
        for (size_t i = 0; i < size; ++i)
        {
            output_obstacle_list[i] = std::make_shared<::holo::obstacle::ObstacleUssT<::holo::float32_t>>();
            opendds_wrapper::DefaultConversionTraits<::holo::obstacle::ObstacleUssT<::holo::float32_t>>::Convert(
                message.obstacles[i], *output_obstacle_list[i]);
        }
        value.SetObstacleList(output_obstacle_list);
    }
};

/* ObstacleVision traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::obstacle::ObstacleVision>
{
    using ValueType   = ::holo_base_msg::obstacle::ObstacleVision;
    using MessageType = ::holo_base_msg::obstacle::ObstacleVision;
};

template <>
struct DefaultMessageTraits<::holo::obstacle::ObstacleVisionT<::holo::float32_t>>
{
    using ValueType   = ::holo::obstacle::ObstacleVisionT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleVision;
};

template <>
struct DefaultConversionTraits<::holo::obstacle::ObstacleVisionT<::holo::float32_t>>
{
    using ValueType   = ::holo::obstacle::ObstacleVisionT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleVision;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

/* ObstacleVisionList traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::obstacle::ObstacleVisionList>
{
    using ValueType   = ::holo_base_msg::obstacle::ObstacleVisionList;
    using MessageType = ::holo_base_msg::obstacle::ObstacleVisionList;
};

template <size_t OBS_SIZE>
    struct DefaultMessageTraits < ::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleVisionT<::holo::float32_t>, OBS_SIZE>>
{
    using ValueType   = ::holo::obstacle::ObstaclePtrListT < ::holo::obstacle::ObstacleVisionT<::holo::float32_t>, OBS_SIZE>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleVisionList;
};

template <size_t OBS_SIZE>
    struct DefaultConversionTraits < ::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleVisionT<::holo::float32_t>, OBS_SIZE>>
{
    using ValueType   = ::holo::obstacle::ObstaclePtrListT < ::holo::obstacle::ObstacleVisionT<::holo::float32_t>, OBS_SIZE>;
    using MessageType = ::holo_base_msg::obstacle::ObstacleVisionList;

    static void Convert(ValueType const& value, MessageType& message)
    {
        // timestamp
        message.stamp = ::holo_base_msg::common::Timestamp{value.GetTimestamp().GetSec(), value.GetTimestamp().GetNsec()};

        // coord
        message.coord = static_cast<uint32_t>(value.GetCoordinate());

        // sensor_id
        message.sensor_id = value.GetSensorId();

        // perception_ability
        message.perception_ability = value.GetPerceptionAbility();

        // obstacle_list
        message.obstacles.length(value.GetSize());
        for (size_t i = 0; i < value.GetSize(); ++i)
        {
            if (value.GetObstacleList()[i] == nullptr)
            {
                throw std::runtime_error("ERROR: Invalid nullptr obstacle list in convertor!");
            }
            opendds_wrapper::DefaultConversionTraits<::holo::obstacle::ObstacleVisionT<::holo::float32_t>>::Convert(*value.GetObstacleList()[i], message.obstacles[i]);
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        // timestamp_
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});

        // coord_
        value.SetCoordinate(message.coord);

        // sensor_id_
        value.SetSensorId(message.sensor_id);

        // size_
        uint32_t size = message.obstacles.length() > ::holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY ?
                            ::holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY :
                            message.obstacles.length();
        value.SetSize(size);

        // perception_ability_
        value.SetPerceptionAbility(message.perception_ability);

        // obstacle_list_
        auto& output_obstacle_list = value.GetObstacleList();
        for (size_t i = 0; i < size; ++i)
        {
            ::holo::obstacle::ObstacleVisionT<::holo::float32_t> tmp_obstacle;

            opendds_wrapper::DefaultConversionTraits<::holo::obstacle::ObstacleVisionT<::holo::float32_t>>::Convert(message.obstacles[i], tmp_obstacle);
            output_obstacle_list[i] = std::make_shared<::holo::obstacle::ObstacleVisionT<::holo::float32_t>>(tmp_obstacle);
        }
    }
};

}  // namespace opendds_wrapper

#endif
