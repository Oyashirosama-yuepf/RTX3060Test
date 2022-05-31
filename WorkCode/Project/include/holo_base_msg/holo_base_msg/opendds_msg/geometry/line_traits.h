#ifndef OPENDDS_MSG_GEOMETRY_LINE_TRAITS_H_
#define OPENDDS_MSG_GEOMETRY_LINE_TRAITS_H_

#include <holo/geometry/line2.h>
#include <holo_base_msg/geometry/LineC.h>
#include <holo_base_msg/geometry/LineS.h>
#include <holo_base_msg/geometry/LineTypeSupportC.h>
#include <holo_base_msg/geometry/LineTypeSupportImpl.h>
#include <holo_base_msg/geometry/LineTypeSupportS.h>
#include <holo_base_msg/opendds_msg/numerics/vector_traits.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* Line2T traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Line2f>
{
    using ValueType   = ::holo_base_msg::geometry::Line2f;
    using MessageType = ::holo_base_msg::geometry::Line2f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Line2T<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::Line2T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Line2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Line2d>
{
    using ValueType   = ::holo_base_msg::geometry::Line2d;
    using MessageType = ::holo_base_msg::geometry::Line2d;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Line2T<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::Line2T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Line2d;
};


template <typename T>
struct DefaultConversionTraits<::holo::geometry::Line2T<T>>
{
    using ValueType   = ::holo::geometry::Line2T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        DefaultConversionTraits<::holo::numerics::Vector3T<T>>::Convert(value.GetCoeffs(), message.cofficients);
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        ::holo::numerics::Vector3T<T> cofficients;
        DefaultConversionTraits<::holo::numerics::Vector3T<T>>::Convert(message.cofficients, cofficients);
        value = ValueType(cofficients);
    }
};

}  // namespace opendds_wrapper

#endif
