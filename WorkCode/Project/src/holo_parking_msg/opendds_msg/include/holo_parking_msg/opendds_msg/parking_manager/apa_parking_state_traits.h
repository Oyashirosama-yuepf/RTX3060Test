/**
 * @file parking_manager_command_traits.h
 * @brief This header file defines trait for parking manager command.
 * @author liaozhenyu(liaozhenyu@holomaitc.com)
 * @date 2022-02-27
 */

#ifndef PARKING_STATE_TRAITS_H
#define PARKING_STATE_TRAITS_H

#include <opendds_wrapper/traits.h>

#include <holo/parking/parking_manager/apa_parking_status.h>

#include <holo_parking_msg/parking_manager/APAParkingStateC.h>
#include <holo_parking_msg/parking_manager/APAParkingStateS.h>
#include <holo_parking_msg/parking_manager/APAParkingStateTypeSupportC.h>
#include <holo_parking_msg/parking_manager/APAParkingStateTypeSupportImpl.h>
#include <holo_parking_msg/parking_manager/APAParkingStateTypeSupportS.h>

namespace opendds_wrapper
{
template <>
struct DefaultMessageTraits<::holo_parking_msg::parking_manager::APAParkingState>
{
    using ValueType   = ::holo_parking_msg::parking_manager::APAParkingState;
    using MessageType = ::holo_parking_msg::parking_manager::APAParkingState;
};

template <>
struct DefaultMessageTraits<::holo::parking::parking_manager::APAParkingState>
{
    using ValueType   = ::holo::parking::parking_manager::APAParkingState;
    using MessageType = ::holo_parking_msg::parking_manager::APAParkingState;
};

template <>
struct DefaultConversionTraits<::holo::parking::parking_manager::APAParkingState>
{
    using ValueType   = ::holo::parking::parking_manager::APAParkingState;
    using MessageType = ::holo_parking_msg::parking_manager::APAParkingState;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.timestamp.sec = value.GetTimestamp().GetSec();
        message.timestamp.nsec = value.GetTimestamp().GetNsec();
        message.current_state = value.GetCurrentState();
        message.last_state = value.GetLastState();
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp(::holo::Timestamp{message.timestamp.sec, message.timestamp.nsec});
        value.SetCurrentState(message.current_state);
        value.SetLastCurrentState(message.current_state);
    }
};
}  // namespace opendds_wrapper

#endif  // PARKING_STATE_TRAITS_H
