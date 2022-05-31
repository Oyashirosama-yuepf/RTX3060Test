#ifndef OPENDDS_MSG_COMMON_CONTROL_TRAITS_H_
#define OPENDDS_MSG_COMMON_CONTROL_TRAITS_H_

#include <holo/common/control_command.h>
#include <holo/common/light_signal_request.h>
#include <holo_base_msg/common/ControlC.h>
#include <holo_base_msg/common/ControlS.h>
#include <holo_base_msg/common/ControlTypeSupportC.h>
#include <holo_base_msg/common/ControlTypeSupportImpl.h>
#include <holo_base_msg/common/ControlTypeSupportS.h>
#include <opendds_wrapper/builtin/BuiltinC.h>
#include <opendds_wrapper/builtin/BuiltinS.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportC.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportImpl.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* Control command traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::ControlCommand>
{
    using MessageType = ::holo_base_msg::common::ControlCommand;
};

template <>
struct DefaultMessageTraits<::holo::common::ControlCommand>
{
    using MessageType = ::holo_base_msg::common::ControlCommand;
};

template <>
struct DefaultConversionTraits<::holo::common::ControlCommand>
{
    using ValueType   = ::holo::common::ControlCommand;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec  = value.GetTimestamp().GetSec();
        message.stamp.nsec = value.GetTimestamp().GetNsec();

        message.lateral_control_model      = static_cast<::holo::uint8_t>(value.GetLateralControlModel());
        message.longitudinal_control_model = static_cast<::holo::uint8_t>(value.GetLongitudinalControlModel());
        message.gear_control_model         = static_cast<::holo::uint8_t>(value.GetGearControlModel());
        message.gear_control_command       = static_cast<::holo::uint8_t>(value.GetGearCommand());

        message.lateral_control_value       = value.GetLateralControlValue();
        message.longitudinal_control_value1 = value.GetLongitudinalControlValue1();
        message.longitudinal_control_value2 = value.GetLongitudinalControlValue2();
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});
        value.SetLateralControlModel(static_cast<ValueType::LateralControlModel>(message.lateral_control_model));
        value.SetLongitudinalControlModel(
            static_cast<ValueType::LongitudinalControlModel>(message.longitudinal_control_model));
        value.SetGearControlModel(static_cast<ValueType::GearControlModel>(message.gear_control_model));
        value.SetLateralControlValue(message.lateral_control_value);
        value.SetLongitudinalControlValue1(message.longitudinal_control_value1);
        value.SetLongitudinalControlValue2(message.longitudinal_control_value2);
        value.SetGearCommand(message.gear_control_command);
    }
};

/* Light signal request */

template <>
struct DefaultMessageTraits<::holo::LightSignalRequest>
{
    using MessageType = ::holo_base_msg::common::LightSignalRequest;
};

template <>
struct DefaultConversionTraits<::holo::LightSignalRequest>
{
    using ValueType   = ::holo::LightSignalRequest;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec  = value.GetTimestamp().GetSec();
        message.stamp.nsec = value.GetTimestamp().GetNsec();
        message.command    = value.GetLightCommand();
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp({message.stamp.sec, message.stamp.nsec});
        value.SetLightCommand(message.command);
    }
};

}  // namespace opendds_wrapper

#endif
