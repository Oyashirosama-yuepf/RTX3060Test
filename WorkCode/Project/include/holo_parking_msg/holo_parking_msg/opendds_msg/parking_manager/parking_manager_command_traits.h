/**
 * @file parking_manager_command_traits.h
 * @brief This header file defines trait for parking manager command.
 * @author liaozhenyu(liaozhenyu@holomaitc.com)
 * @date 2022-02-27
 */

#ifndef PARKING_MANAGER_COMMAND_TRAITS_H
#define PARKING_MANAGER_COMMAND_TRAITS_H

#include <holo/parking/parking_manager/parking_manager_command.h>

#include <opendds_wrapper/traits.h>

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

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetRouteId(message.route_id);
        value.SetAvmCommand(message.avm_command);
        value.SetHpaCommand(message.hpa_command);
        value.SetSlotSendEN(message.slot_send_en);
        value.SetVSlamCommand(message.vslam_command);
        value.SetHpaTidlCommand(message.hpa_tidl_command);
        value.SetSlotMangCommand(message.slot_mang_command);
        value.SetMapServerCommand(message.map_server_command);
    }
    static void Convert(ValueType const& value, MessageType& message)
    {
        message.route_id           = value.GetRouteId();
        message.avm_command        = value.GetAvmCommand();
        message.hpa_command        = value.GetHpaCommand();
        message.slot_send_en       = value.GetSlotSendEN();
        message.vslam_command      = value.GetVSlamCommand();
        message.hpa_tidl_command   = value.GetHpaTidlCommand();
        message.slot_mang_command  = value.GetSlotMangCommand();
        message.map_server_command = value.GetMapServerCommand();
    }
};
}  // namespace opendds_wrapper

#endif  // PARKING_MANAGER_COMMAND_TRAITS_H
