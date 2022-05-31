#ifndef OPENDDS_MSG_COMMON_APP_STATUS_TRAITS_H_
#define OPENDDS_MSG_COMMON_APP_STATUS_TRAITS_H_

#include <opendds_wrapper/traits.h>
#include <holo/common/app_status.h>

#include <holo_base_msg/common/AppStatusC.h>
#include <holo_base_msg/common/AppStatusS.h>
#include <holo_base_msg/common/AppStatusTypeSupportC.h>
#include <holo_base_msg/common/AppStatusTypeSupportS.h>
#include <holo_base_msg/common/AppStatusTypeSupportImpl.h>


namespace opendds_wrapper
{

template <>
struct DefaultMessageTraits<::holo_base_msg::common::AppStatus>
{
    using ValueType = ::holo_base_msg::common::AppStatus;
    using MessageType = ::holo_base_msg::common::AppStatus;
};

template <>
struct DefaultMessageTraits<::holo::common::AppStatus>
{
    using ValueType = ::holo::common::AppStatus;
    using MessageType = ::holo_base_msg::common::AppStatus;
};

template <>
struct DefaultConversionTraits<::holo::common::AppStatus>
{
    using ValueType = ::holo::common::AppStatus;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;
    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

}//namespace opendds_wrapper

#endif
