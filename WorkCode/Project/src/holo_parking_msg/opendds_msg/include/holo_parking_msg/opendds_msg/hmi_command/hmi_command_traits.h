/**
 * @file parking_manager_command_traits.h
 * @brief This header file defines trait for parking manager command.
 * @author liaozhenyu(liaozhenyu@holomaitc.com)
 * @date 2022-02-27
 */

#ifndef HMI_COMMAND_TRAITS_H
#define HMI_COMMAND_TRAITS_H

#include <opendds_wrapper/traits.h>

#include <holo_parking_msg/parking_manager/HmiCommandC.h>
#include <holo_parking_msg/parking_manager/HmiCommandS.h>
#include <holo_parking_msg/parking_manager/HmiCommandTypeSupportC.h>
#include <holo_parking_msg/parking_manager/HmiCommandTypeSupportImpl.h>
#include <holo_parking_msg/parking_manager/HmiCommandTypeSupportS.h>

namespace opendds_wrapper
{
template <>
struct DefaultMessageTraits<::holo_parking_msg::parking_manager::HmiCommand>
{
    using ValueType   = ::holo_parking_msg::parking_manager::HmiCommand;
    using MessageType = ::holo_parking_msg::parking_manager::HmiCommand;
};

template <>
struct DefaultMessageTraits<::holo::parking::system::HmiCommand>
{
    using ValueType   = ::holo::parking::system::HmiCommand;
    using MessageType = ::holo_parking_msg::parking_manager::HmiCommand;
};

template <>
struct DefaultConversionTraits<::holo::parking::system::HmiCommand>
{
    using ValueType   = ::holo::parking::system::HmiCommand;
    using MessageType = ::holo_parking_msg::parking_manager::HmiCommand;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.path_id_ = value.GetPathId();
        message.parkinglot_type_ = value.GetParkinglotType();
        message.path_type_ = value.GetPathType();
        message.heartbeat_ = value.GetHeartbeat();
        message.park_type_ = value.GetParkType();
        message.route_id_ = value.GetRouteId();
        message.delete_id_ = value.GetDeleteId();
        message.mapping_offline_ = value.GetMappingOffline();
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetPathId(message.path_id_);
        value.SetParkinglotType(message.parkinglot_type_);
        value.SetPathType(message.path_type_);
        value.SetHeartbeat(message.heartbeat_);
        value.SetParkType(message.park_type_);
        value.SetRouteId(message.route_id_);
        value.SetDeleteId(message.delete_id_);
        value.SetMappingOffline(message.mapping_offline_);
    }
};
}  // namespace opendds_wrapper

#endif  // HMI_COMMAND_TRAITS_H
