#ifndef OPENDDS_MSG_COMMON_ODM_STATES_TRAITS_H_
#define OPENDDS_MSG_COMMON_ODM_STATES_TRAITS_H_

#include <holo/common/odm.h>
#include <holo_base_msg/common/OdmStatesC.h>
#include <holo_base_msg/common/OdmStatesS.h>
#include <holo_base_msg/common/OdmStatesTypeSupportC.h>
#include <holo_base_msg/common/OdmStatesTypeSupportImpl.h>
#include <holo_base_msg/common/OdmStatesTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* Chassis state traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::OdmStates>
{
    using ValueType   = ::holo_base_msg::common::OdmStates;
    using MessageType = ::holo_base_msg::common::OdmStates;
};

template <>
struct DefaultMessageTraits<::holo::common::OdmStates>
{
    using ValueType   = ::holo::common::OdmStates;
    using MessageType = ::holo_base_msg::common::OdmStates;
};

template <>
struct DefaultConversionTraits<::holo::common::OdmStates>
{
    using ValueType   = ::holo::common::OdmStates;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

}  // namespace opendds_wrapper

#endif
