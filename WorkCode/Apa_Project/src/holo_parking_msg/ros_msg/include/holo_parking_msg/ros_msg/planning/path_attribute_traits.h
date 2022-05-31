/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file path_attribute_traits.h
 * @brief This header file defines trait for path attribute.
 * @author zhangchun(zhangchun@holomaitc.com)
 * @date 2021-05-19
 */

#ifndef HOLO_PARKING_MSG_ROS_MSG_PATH_ATTRIBUTE_TRAITS_H_
#define HOLO_PARKING_MSG_ROS_MSG_PATH_ATTRIBUTE_TRAITS_H_

#include <holo/parking/planning/path_attribute.h>

#include <ros_wrapper/traits.h>

#include <holo_parking_msg/PathAttribute.h>

namespace ros_wrapper
{
/* PathAttribute traits */

template <>
struct DefaultMessageTraits<::holo_parking_msg::PathAttribute>
{
    using ValueType   = ::holo_parking_msg::PathAttribute;
    using MessageType = ::holo_parking_msg::PathAttribute;
};

template <>
struct DefaultMessageTraits<::holo::parking::planning::PathAttribute>
{
    using ValueType   = ::holo::parking::planning::PathAttribute;
    using MessageType = ::holo_parking_msg::PathAttribute;
};

template <>
struct DefaultConversionTraits<::holo::parking::planning::PathAttribute>
{
    using ValueType   = ::holo::parking::planning::PathAttribute;
    using MessageType = ::holo_parking_msg::PathAttribute;

    static void Convert(ValueType const& value, MessageType& message)
    {
        // timestamp
        message.timestamp.sec  = value.GetTimestamp().GetSec();
        message.timestamp.nsec = value.GetTimestamp().GetNsec();

        message.path_gear         = value.GetPathGear();
        message.path_id           = value.GetPathId();
        message.path_type         = value.GetPathType();
        message.path_size         = value.GetPathSize();
        message.plan_complete     = value.GetPathComplete();
        message.plan_error        = value.GetPlanError();
        message.path_len          = value.GetPathLen();
        message.remain_path_len   = value.GetRemainPathLen();
        message.brk_flag          = value.GetBrkFlag();
        message.brk_dist          = value.GetBrkDist();
        message.speed_limit       = value.GetSpeedLimit();
        message.lamp_req          = value.GetLampReq();
        message.read_file_status  = value.GetReadFileStatus();
        message.ref_lat_error     = value.GetRefLatError();
        message.ref_heading_error = value.GetRefHeadingError();
        message.road_curvature    = value.GetRoadCurvature();
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        // timestamp_
        value.SetTimestamp(::holo::Timestamp{message.timestamp.sec, message.timestamp.nsec});

        value.SetPathGear(message.path_gear);
        value.SetPathId(message.path_id);
        value.SetPathType(message.path_type);
        value.SetPathSize(message.path_size);
        value.SetPathComplete(message.plan_complete);
        value.SetPlanError(message.plan_error);
        value.SetPathLen(message.path_len);
        value.SetRemainPathLen(message.remain_path_len);
        value.SetBrkFlag(message.brk_flag);
        value.SetBrkDist(message.brk_dist);
        value.SetSpeedLimit(message.speed_limit);
        value.SetLampReq(message.lamp_req);
        value.SetReadFileStatus(message.read_file_status);
        value.SetRefLatError(message.ref_lat_error);
        value.SetRefHeadingError(message.ref_heading_error);
        value.SetRoadCurvature(message.road_curvature);
    }
};

}  // namespace ros_wrapper

#endif
