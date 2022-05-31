#ifndef OPENDDS_MSG_COMMON_GNSS_TRAITS_H_
#define OPENDDS_MSG_COMMON_GNSS_TRAITS_H_

#include <holo/common/gnss_position.h>
#include <holo/common/gnss_pvt.h>
#include <holo/common/gnss_raw_measurement.h>
#include <holo_base_msg/common/GnssC.h>
#include <holo_base_msg/common/GnssS.h>
#include <holo_base_msg/common/GnssTypeSupportC.h>
#include <holo_base_msg/common/GnssTypeSupportImpl.h>
#include <holo_base_msg/common/GnssTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* GnssPvt traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::GnssPvt>
{
    using ValueType   = ::holo_base_msg::common::GnssPvt;
    using MessageType = ::holo_base_msg::common::GnssPvt;
};

template <>
struct DefaultMessageTraits<::holo::common::GnssPvt>
{
    using ValueType   = ::holo::common::GnssPvt;
    using MessageType = ::holo_base_msg::common::GnssPvt;
};

template <>
struct DefaultConversionTraits<::holo::common::GnssPvt>
{
    using ValueType   = ::holo::common::GnssPvt;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

/* GnssPosition traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::GnssPosition>
{
    using ValueType   = ::holo_base_msg::common::GnssPosition;
    using MessageType = ::holo_base_msg::common::GnssPosition;
};

template <>
struct DefaultMessageTraits<::holo::GnssPosition>
{
    using ValueType   = ::holo::GnssPosition;
    using MessageType = ::holo_base_msg::common::GnssPosition;
};

template <>
struct DefaultConversionTraits<::holo::GnssPosition>
{
    using ValueType   = ::holo::GnssPosition;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

/* GnssRawMeasurement traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::GnssRawMeasurement>
{
    using ValueType   = ::holo_base_msg::common::GnssRawMeasurement;
    using MessageType = ::holo_base_msg::common::GnssRawMeasurement;
};

template <>
struct DefaultMessageTraits<::holo::common::GnssRawMeasurement>
{
    using ValueType   = ::holo::common::GnssRawMeasurement;
    using MessageType = ::holo_base_msg::common::GnssRawMeasurement;
};

template <>
struct DefaultConversionTraits<::holo::common::GnssRawMeasurement>
{
    using ValueType   = ::holo::common::GnssRawMeasurement;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

}  // namespace opendds_wrapper

#endif
