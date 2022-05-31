/**
 * @file parking_manager_command_traits.h
 * @brief This header file defines trait for parking manager command.
 * @author liaozhenyu(liaozhenyu@holomaitc.com)
 * @date 2022-02-27
 */

#ifndef PARKING_MANAGER_COMMAND_TRAITS_H
#define PARKING_MANAGER_COMMAND_TRAITS_H

#include <opendds_wrapper/traits.h>

#include <holo/parking/parking_manager/apa_parking_manager_command.h>
#include <holo_parking_msg/parking_manager/APAParkingManagerCommandC.h>
#include <holo_parking_msg/parking_manager/APAParkingManagerCommandS.h>
#include <holo_parking_msg/parking_manager/APAParkingManagerCommandTypeSupportC.h>
#include <holo_parking_msg/parking_manager/APAParkingManagerCommandTypeSupportImpl.h>
#include <holo_parking_msg/parking_manager/APAParkingManagerCommandTypeSupportS.h>

namespace opendds_wrapper
{
template <>
struct DefaultMessageTraits<::holo_parking_msg::parking_manager::APAParkingManagerCommand>
{
    using ValueType   = ::holo_parking_msg::parking_manager::APAParkingManagerCommand;
    using MessageType = ::holo_parking_msg::parking_manager::APAParkingManagerCommand;
};

template <>
struct DefaultMessageTraits<::holo::parking::parking_manager::APAParkingManagerCommand>
{
    using ValueType   = ::holo::parking::parking_manager::APAParkingManagerCommand;
    using MessageType = ::holo_parking_msg::parking_manager::APAParkingManagerCommand;
};

template <>
struct DefaultConversionTraits<::holo::parking::parking_manager::APAParkingManagerCommand>
{
    using ValueType   = ::holo::parking::parking_manager::APAParkingManagerCommand;
    using MessageType = ::holo_parking_msg::parking_manager::APAParkingManagerCommand;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.timestamp.sec = value.GetTimestamp().GetSec();
        message.timestamp.nsec = value.GetTimestamp().GetNsec();
        message.apa_enable = value.GetEnableApaStatus();
        message.apa_searching_method = value.GetSearchMethod();
        message.slot_method = value.GetSlotDirection();
        message.park_type = value.GetParkDirection();
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp(::holo::Timestamp{message.timestamp.sec, message.timestamp.nsec});
        value.SetEnableApaStatus(message.apa_enable);
        value.SetSearchMethod(message.apa_searching_method);
        value.SetSlotDirection(message.slot_method);
        value.SetParkDirection(message.park_type);
    }
};
}  // namespace opendds_wrapper

#endif  // PARKING_MANAGER_COMMAND_TRAITS_H
