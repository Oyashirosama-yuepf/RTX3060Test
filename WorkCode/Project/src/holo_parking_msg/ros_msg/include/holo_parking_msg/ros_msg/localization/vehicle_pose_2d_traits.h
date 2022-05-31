/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_pose_2d_traits.h
 * @brief This header file defines PointFeaturePtrListTraits.
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-05-21
 */

#ifndef HOLO_PARKING_MSG_ROS_MSG_LOCALIZATION_VECHILE_POSE_2D_TRAITS_H_
#define HOLO_PARKING_MSG_ROS_MSG_LOCALIZATION_VECHILE_POSE_2D_TRAITS_H_

#include <ros_wrapper/traits.h>

#include <holo/parking/localization/vehicle_pose_2d.h>
#include <holo_parking_msg/VehiclePose2Df.h>

namespace ros_wrapper
{
/* VehiclePose2Df traits */

template <>
struct DefaultMessageTraits<::holo_parking_msg::VehiclePose2Df>
{
    using ValueType   = ::holo_parking_msg::VehiclePose2Df;
    using MessageType = ::holo_parking_msg::VehiclePose2Df;
};

template <>
struct DefaultMessageTraits<::holo::parking::localization::VehiclePose2Df>
{
    using ValueType   = ::holo::parking::localization::VehiclePose2Df;
    using MessageType = ::holo_parking_msg::VehiclePose2Df;
};

template <>
struct DefaultConversionTraits<::holo::parking::localization::VehiclePose2Df>
{
    using ValueType   = ::holo::parking::localization::VehiclePose2Df;
    using MessageType = ::holo_parking_msg::VehiclePose2Df;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.curv   = value.GetCurve();
        message.status = static_cast<holo::uint8_t>(value.GetStatus());
        message.pose.resize(3);
        message.predicted_pose.resize(3);

        for (size_t i = 0; i < 3; ++i)
        {
            message.pose[i]           = value.GetPose()[i];
            message.predicted_pose[i] = value.GetPredictedPose()[i];
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        ValueType::Vector3Type pose(message.pose[0], message.pose[1], message.pose[2]);
        ValueType::Vector3Type predicted_pose(message.predicted_pose[0], message.predicted_pose[1],
                                              message.predicted_pose[2]);

        value = ValueType(message.curv, pose, predicted_pose, ValueType::VehicleStatus(message.status));
    }
};

}  // namespace ros_wrapper

#endif  // HOLO_PARKING_MSG_ROS_MSG_LOCALIZATION_VECHILE_POSE_2D_TRAITS_H_
