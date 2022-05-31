/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ddt_traits.h
 * @brief Ddt message traits
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-08
 */
#ifndef HOLO_BASE_MSG_OPENDDS_MSG_COMMON_DDT_TRAITS_H_
#define HOLO_BASE_MSG_OPENDDS_MSG_COMMON_DDT_TRAITS_H_

#include <holo/common/ddt.h>
#include <holo_base_msg/common/DdtStatesC.h>
#include <holo_base_msg/common/DdtStatesS.h>
#include <holo_base_msg/common/DdtStatesTypeSupportC.h>
#include <holo_base_msg/common/DdtStatesTypeSupportImpl.h>
#include <holo_base_msg/common/DdtStatesTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
template <>
struct DefaultMessageTraits<::holo_base_msg::common::DdtStates>
{
    using ValueType   = ::holo_base_msg::common::DdtStates;
    using MessageType = ::holo_base_msg::common::DdtStates;
};

template <size_t SIZE>
struct DefaultMessageTraits<::holo::common::DdtStates<SIZE>>
{
    using ValueType   = ::holo::common::DdtStates<SIZE>;
    using MessageType = ::holo_base_msg::common::DdtStates;
};

template <size_t SIZE>
struct DefaultConversionTraits<::holo::common::DdtStates<SIZE>>
{
    using ValueType   = ::holo::common::DdtStates<SIZE>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp = {value.GetTimestamp().GetSec(), value.GetTimestamp().GetNsec()};
        message.ddts.length(value.size());
        size_t i = 0U;
        for (holo::common::DdtState const& state : value)
        {
            message.ddts[i].type          = state.GetType();
            message.ddts[i].flags         = state.GetFlags();
            message.ddts[i].alarm         = state.GetAlarm();
            message.ddts[i].pred_distance = state.GetPredictedDistance();
            message.ddts[i].pred_time     = state.GetPredictedTime();
            ++i;
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp({message.stamp.sec, message.stamp.nsec});
        value.clear();
        for (size_t i = 0U; i < message.ddts.length(); ++i)
        {
            holo::common::DdtState& state = value[message.ddts[i].type];
            state.SetFlags(message.ddts[i].flags);
            state.SetAlarm(message.ddts[i].alarm);
            state.SetPredictedDistance(message.ddts[i].pred_distance);
            state.SetPredictedTime(message.ddts[i].pred_time);
        }
    }
};

}  // namespace opendds_wrapper
#endif
