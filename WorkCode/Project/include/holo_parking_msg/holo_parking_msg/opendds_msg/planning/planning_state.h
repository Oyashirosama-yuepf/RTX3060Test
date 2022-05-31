/**
 * @file parking_manager_command_traits.h
 * @brief This header file defines trait for parking manager command.
 * @author liaozhenyu(liaozhenyu@holomaitc.com)
 * @date 2022-02-27
 */

#ifndef PARKING_CTRL_REQ_TRAITS_H
#define PARKING_CTRL_REQ_TRAITS_H

#include <opendds_wrapper/traits.h>

#include <holo_parking_msg/parking_manager/PlanningStateC.h>
#include <holo_parking_msg/parking_manager/PlanningStateS.h>

namespace opendds_wrapper
{
template <>
struct DefaultMessageTraits<uint32_t>
{
    using ValueType   = uint32_t;
    using MessageType = uint32_t;
};

template <>
struct DefaultMessageTraits<uint32_t>
{
    using ValueType   = uint32_t;
    using MessageType = uint32_t;
};

template <>
struct DefaultConversionTraits<uint32_t>
{
    using ValueType   = uint32_t;
    using MessageType = uint32_t;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message;
    }
};
}  // namespace opendds_wrapper

#endif  // PARKING_CTRL_REQ_TRAITS_H
