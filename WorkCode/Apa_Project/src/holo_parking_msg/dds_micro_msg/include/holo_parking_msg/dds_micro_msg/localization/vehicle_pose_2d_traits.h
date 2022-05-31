/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_pose_2d_traits.h
 * @brief This header file defines vehicle pose 2d traits.
 * @author guo peikai(guopeikai@holomaitc.com)
 * @date 2021-05-21
 */

#ifndef HOLO_PARKING_MSG_DDS_MICRO_MSG_LOCALIZATION_VECHILE_POSE_2D_TRAITS_H_
#define HOLO_PARKING_MSG_DDS_MICRO_MSG_LOCALIZATION_VECHILE_POSE_2D_TRAITS_H_

#include <dds_micro_wrapper/traits.h>

#include <holo/parking/localization/vehicle_pose_2d.h>
#include "holo_parking_msg/holo_base_msg/common/VehPos.h"
#include "holo_parking_msg/holo_base_msg/common/VehPosPlugin.h"
#include "holo_parking_msg/holo_base_msg/common/VehPosSupport.h"

namespace dds_micro_wrapper
{
/* VehiclePose2Df traits    */

template <>
struct DefaultMessageTraits<holo_base_msg_common_VehPosX3V>
{
    using ValueType   = holo_base_msg_common_VehPosX3V;
    using MessageType = holo_base_msg_common_VehPosX3V;
};

template <>
struct DefaultMessageTraits<::holo::parking::localization::VehiclePose2Df>
{
    using ValueType   = ::holo::parking::localization::VehiclePose2Df;
    using MessageType = holo_base_msg_common_VehPosX3V;
};

template <>
struct DefaultConversionTraits<::holo::parking::localization::VehiclePose2Df>
{
    using ValueType   = ::holo::parking::localization::VehiclePose2Df;
    using MessageType = holo_base_msg_common_VehPosX3V;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.curv       = value.GetCurve();
        message.vehStatus  = static_cast<holo::uint8_t>(value.GetStatus());
        message.vehPos_X   = value.GetPose()[0];
        message.vehPos_Y   = value.GetPose()[1];
        message.vehPos_Yaw = value.GetPose()[2];

        message.vehPosPred_X   = value.GetPredictedPose()[0];
        message.vehPosPred_Y   = value.GetPredictedPose()[1];
        message.vehPosPred_Yaw = value.GetPredictedPose()[2];
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        ValueType::Vector3Type pose(message.vehPos_X, message.vehPos_Y, message.vehPos_Yaw);
        ValueType::Vector3Type predicted_pose(message.vehPosPred_X, message.vehPosPred_Y, message.vehPosPred_Yaw);

        value = ValueType(message.curv, pose, predicted_pose, ValueType::VehicleStatus(message.vehStatus));
    }
};

}  // namespace dds_micro_wrapper

#endif  // HOLO_PARKING_MSG_DDS_MICRO_MSG_LOCALIZATION_VECHILE_POSE_2D_TRAITS_H_
