#ifndef OPENDDS_MSG_GEOMETRY_POINT_TRAITS_H_
#define OPENDDS_MSG_GEOMETRY_POINT_TRAITS_H_

#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo_base_msg/geometry/PointC.h>
#include <holo_base_msg/geometry/PointS.h>
#include <holo_base_msg/geometry/PointTypeSupportC.h>
#include <holo_base_msg/geometry/PointTypeSupportImpl.h>
#include <holo_base_msg/geometry/PointTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* Point2T traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Point2f>
{
    using ValueType   = ::holo_base_msg::geometry::Point2f;
    using MessageType = ::holo_base_msg::geometry::Point2f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Point2T<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::Point2T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Point2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Point2d>
{
    using ValueType   = ::holo_base_msg::geometry::Point2d;
    using MessageType = ::holo_base_msg::geometry::Point2d;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Point2T<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::Point2T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Point2d;
};

template <typename T>
struct DefaultConversionTraits<::holo::geometry::Point2T<T>>
{
    using ValueType   = ::holo::geometry::Point2T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.x = value.GetX();
        message.y = value.GetY();
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetX(message.x);
        value.SetY(message.y);
    }
};

/* Point3f traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Point3f>
{
    using ValueType   = ::holo_base_msg::geometry::Point3f;
    using MessageType = ::holo_base_msg::geometry::Point3f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Point3T<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::Point3T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Point3f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Point3d>
{
    using ValueType   = ::holo_base_msg::geometry::Point3d;
    using MessageType = ::holo_base_msg::geometry::Point3d;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Point3T<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::Point3T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Point3d;
};

template <typename T>
struct DefaultConversionTraits<::holo::geometry::Point3T<T>>
{
    using ValueType   = ::holo::geometry::Point3T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.x = value.GetX();
        message.y = value.GetY();
        message.z = value.GetZ();
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetX(message.x);
        value.SetY(message.y);
        value.SetZ(message.z);
    }
};

}  // namespace opendds_wrapper

#endif
