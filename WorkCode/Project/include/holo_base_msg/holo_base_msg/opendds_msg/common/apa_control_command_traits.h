/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file apa_control_command_traits.h
 * @brief This header file defines trait for apa control command.
 * @author zhangchun(zhangchun@holomaitc.com)
 * @date 2021-03-04
 */

#ifndef HOLO_BASE_MSG_OPENDDS_MSG_APA_CONTROL_COMMAND_TRAITS_H_
#define HOLO_BASE_MSG_OPENDDS_MSG_APA_CONTROL_COMMAND_TRAITS_H_

#include <holo/common/apa_control_command.h>

#include <opendds_wrapper/traits.h>

#include <holo_base_msg/common/ApaControlCommandC.h>
#include <holo_base_msg/common/ApaControlCommandS.h>
#include <holo_base_msg/common/ApaControlCommandTypeSupportC.h>
#include <holo_base_msg/common/ApaControlCommandTypeSupportImpl.h>
#include <holo_base_msg/common/ApaControlCommandTypeSupportS.h>
#include <opendds_wrapper/builtin/BuiltinC.h>
#include <opendds_wrapper/builtin/BuiltinS.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportC.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportImpl.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportS.h>

namespace opendds_wrapper
{
/* ApaControlCommand traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::ApaControlCommand>
{
    using ValueType   = ::holo_base_msg::common::ApaControlCommand;
    using MessageType = ::holo_base_msg::common::ApaControlCommand;
};

template <>
struct DefaultMessageTraits<::holo::common::ApaControlCommand>
{
    using ValueType   = ::holo::common::ApaControlCommand;
    using MessageType = ::holo_base_msg::common::ApaControlCommand;
};

template <>
struct DefaultConversionTraits<::holo::common::ApaControlCommand>
{
    using ValueType   = ::holo::common::ApaControlCommand;
    using MessageType = ::holo_base_msg::common::ApaControlCommand;

    static void Convert(ValueType const& value, MessageType& message)
    {
        // timestamp
        message.timestamp.sec  = value.GetTimestamp().GetSec();
        message.timestamp.nsec = value.GetTimestamp().GetNsec();

        // lon control
        message.lon_auto_mode           = value.GetLonAutoMode();
        message.target_gear_request     = value.GetTargetGearRequest();
        message.stop_dist_request       = value.GetStopDistRequest();
        message.speed_limit_request     = value.GetSpeedLimitRequest();
        message.apafail_brkmode_request = value.GetApafailBrkmodeRequest();

        // lat control
        message.steer_auto_mode = value.GetSteerAutoMode();
        message.steering_angle  = value.GetSteeringAngle();
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        // timestamp_
        value.SetTimestamp(::holo::common::Timestamp{message.timestamp.sec, message.timestamp.nsec});

        // lon control
        value.SetLonAutoMode(message.lon_auto_mode);
        value.SetTargetGearRequest(message.target_gear_request);
        value.SetStopDistRequest(message.stop_dist_request);
        value.SetSpeedLimitRequest(message.speed_limit_request);
        value.SetApafailBrkmodeRequest(message.apafail_brkmode_request);

        // lat control
        value.SetSteerAutoMode(message.steer_auto_mode);
        value.SetSteeringAngle(message.steering_angle);
    }
};

}  // namespace opendds_wrapper

#endif
