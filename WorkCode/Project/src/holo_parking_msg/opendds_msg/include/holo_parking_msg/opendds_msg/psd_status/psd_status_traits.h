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

#ifndef HOLO_PARKING_MSG_OPENDDS_MSG_PATH_ATTRIBUTE_TRAITS_H_
#define HOLO_PARKING_MSG_OPENDDS_MSG_PATH_ATTRIBUTE_TRAITS_H_

#include <opendds_wrapper/traits.h>

#include <holo/parking/system/psd_status.h>

#include <holo_parking_msg/planning/PathAttributeC.h>
#include <holo_parking_msg/planning/PathAttributeS.h>
#include <holo_parking_msg/planning/PathAttributeTypeSupportC.h>
#include <holo_parking_msg/planning/PathAttributeTypeSupportImpl.h>
#include <holo_parking_msg/planning/PathAttributeTypeSupportS.h>

namespace opendds_wrapper
{
/* PathAttribute traits */

template <>
struct DefaultMessageTraits<::holo_parking_msg::planning::PsdStatus>
{
    using ValueType   = ::holo_parking_msg::planning::PsdStatus;
    using MessageType = ::holo_parking_msg::planning::PsdStatus;
};

template <>
struct DefaultMessageTraits<::holo::parking::planning::PsdStatus>
{
    using ValueType   = ::holo::parking::planning::PsdStatus;
    using MessageType = ::holo_parking_msg::planning::PsdStatus;
};

template <>
struct DefaultConversionTraits<::holo::parking::planning::PsdStatus>
{
    using ValueType   = ::holo::parking::planning::PsdStatus;
    using MessageType = ::holo_parking_msg::planning::PsdStatus;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.slot_state = value.GetSlotState();
        message.slot_node_state = value.GetSlotNodeState();
        message.app_run_state = value.GetAppRunState();
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetSlotState(message.slot_state);
        value.SetSlotNodeState(message.slot_node_state);
        value.SetAppRunState(message.app_run_state);
    }
};

}  // namespace opendds_wrapper

#endif
