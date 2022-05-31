#ifndef OPENDDS_MSG_COMMON_PATH_TRAITS_H_
#define OPENDDS_MSG_COMMON_PATH_TRAITS_H_

#include <holo/common/path.h>
#include <holo_base_msg/common/PathC.h>
#include <holo_base_msg/common/PathS.h>
#include <holo_base_msg/common/PathTypeSupportC.h>
#include <holo_base_msg/common/PathTypeSupportImpl.h>
#include <holo_base_msg/common/PathTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* PathT traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::Pathf>
{
    using ValueType   = ::holo_base_msg::common::Pathf;
    using MessageType = ::holo_base_msg::common::Pathf;
};

template <>
struct DefaultMessageTraits<::holo::common::PathT<::holo::float32_t>>
{
    using ValueType   = ::holo::common::PathT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::common::Pathf;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::common::Pathd>
{
    using ValueType   = ::holo_base_msg::common::Pathd;
    using MessageType = ::holo_base_msg::common::Pathd;
};

template <>
struct DefaultMessageTraits<::holo::common::PathT<::holo::float64_t>>
{
    using ValueType   = ::holo::common::PathT<::holo::float64_t>;
    using MessageType = ::holo_base_msg::common::Pathd;
};

template <typename T>
struct DefaultConversionTraits<::holo::common::PathT<T>>
{
    using ValueType   = ::holo::common::PathT<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec      = value.GetTimestamp().GetSec();
        message.stamp.nsec     = value.GetTimestamp().GetNsec();
        message.coord          = static_cast<::holo::uint32_t>(value.GetCoordinate());
        message.valid_value    = value.GetValidValue();
        message.planning_state = static_cast<::holo::uint32_t>(value.GetPlanningState());

        message.point_list.length(value.size());
        for (size_t idx = 0; idx < value.size(); idx++)
        {
            message.point_list[idx].point.x      = value[idx].GetX();
            message.point_list[idx].point.y      = value[idx].GetY();
            message.point_list[idx].point.z      = value[idx].GetZ();
            message.point_list[idx].theta        = value[idx].GetTheta();
            message.point_list[idx].curvature    = value[idx].GetCurvature();
            message.point_list[idx].speed        = value[idx].GetSpeed();
            message.point_list[idx].acceleration = value[idx].GetAcceleration();
            message.point_list[idx].distance     = value[idx].GetDistance();
            message.point_list[idx].time         = value[idx].GetTime();
        }
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});
        value.SetCoordinate(static_cast<::holo::common::Coordinate>(message.coord));
        value.SetValidValue(message.valid_value);
        value.SetPlanningState(static_cast<typename ValueType::PlanningState>(message.planning_state));

        value.clear();
        value.reserve(message.point_list.length());
        for (size_t idx = 0; idx < message.point_list.length(); idx++)
        {
            ::holo::common::PathPointT<T> path_point;

            path_point.SetX(message.point_list[idx].point.x);
            path_point.SetY(message.point_list[idx].point.y);
            path_point.SetZ(message.point_list[idx].point.z);
            path_point.SetTheta(message.point_list[idx].theta);
            path_point.SetCurvature(message.point_list[idx].curvature);
            path_point.SetSpeed(message.point_list[idx].speed);
            path_point.SetAcceleration(message.point_list[idx].acceleration);
            path_point.SetDistance(message.point_list[idx].distance);
            path_point.SetTime(message.point_list[idx].time);

            value.push_back(path_point);
        }
    }
};

}  // namespace opendds_wrapper

#endif