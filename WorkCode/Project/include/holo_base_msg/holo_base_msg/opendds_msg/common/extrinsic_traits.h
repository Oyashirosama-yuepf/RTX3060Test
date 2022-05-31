#ifndef OPENDDS_MSG_COMMON_EXTRINSIC_TRAITS_H_
#define OPENDDS_MSG_COMMON_EXTRINSIC_TRAITS_H_

#include <holo/common/extrinsic.h>
#include <holo_base_msg/common/ExtrinsicC.h>
#include <holo_base_msg/common/ExtrinsicS.h>
#include <holo_base_msg/common/ExtrinsicTypeSupportC.h>
#include <holo_base_msg/common/ExtrinsicTypeSupportImpl.h>
#include <holo_base_msg/common/ExtrinsicTypeSupportS.h>
#include <holo_base_msg/opendds_msg/geometry/pose_traits.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* Extrinsic traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::Extrinsic>
{
    using ValueType   = ::holo_base_msg::common::Extrinsic;
    using MessageType = ::holo_base_msg::common::Extrinsic;
};

template <>
struct DefaultMessageTraits<::holo::common::ExtrinsicT<::holo::float32_t>>
{
    using ValueType   = ::holo::common::ExtrinsicT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::common::Extrinsic;
};

template <>
struct DefaultConversionTraits<::holo::common::ExtrinsicT<::holo::float32_t>>
{
    using ValueType   = ::holo::common::ExtrinsicT<::holo::float32_t>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

}  // namespace opendds_wrapper

#endif
