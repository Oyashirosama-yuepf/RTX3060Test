#ifndef OPENDDS_MSG_DEPRECATED_OBSTALCE_TRAITS_H_
#define OPENDDS_MSG_DEPRECATED_OBSTACLE_TRAITS_H_

#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>

#include <opendds_wrapper/traits.h>
#include <holo_base_msg/opendds_msg/obstacle/obstaclelist_traits.h>

#include <holo_base_msg/deprecated/ObstacleC.h>
#include <holo_base_msg/deprecated/ObstacleS.h>
#include <holo_base_msg/deprecated/ObstacleTypeSupportC.h>
#include <holo_base_msg/deprecated/ObstacleTypeSupportImpl.h>
#include <holo_base_msg/deprecated/ObstacleTypeSupportS.h>

namespace opendds_wrapper
{
template <size_t OBS_SIZE>
struct DefaultConversionTraits<::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>, OBS_SIZE>,
                               ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList>
{
    using ValueType   = ::holo::obstacle::ObstaclePtrListT<::holo::obstacle::ObstacleGeneralT<::holo::float32_t>, OBS_SIZE>;
    using MessageType = ::holo_base_msg::deprecated::obstacle::ObstacleGeneralList;

    static void Convert(ValueType const& value, MessageType& message)
    {
        // timestamp
        message.stamp = ::holo_base_msg::common::Timestamp{value.GetTimestamp().GetSec(), value.GetTimestamp().GetNsec()};

        // coord
        message.coord = static_cast<uint32_t>(value.GetCoordinate());

        // sensor_id
        message.sensor_id = value.GetSensorId();

        // size
        message.size = value.GetSize();

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

}  // namespace opendds_wrapper

#endif
