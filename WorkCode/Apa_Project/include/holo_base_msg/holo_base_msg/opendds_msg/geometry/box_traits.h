#ifndef OPENDDS_MSG_GEOMETRY_BOX_TRAITS_H_
#define OPENDDS_MSG_GEOMETRY_BOX_TRAITS_H_

#include <holo/geometry/box2.h>
#include <holo/geometry/box3.h>
#include <holo_base_msg/geometry/BoxC.h>
#include <holo_base_msg/geometry/BoxS.h>
#include <holo_base_msg/geometry/BoxTypeSupportC.h>
#include <holo_base_msg/geometry/BoxTypeSupportImpl.h>
#include <holo_base_msg/geometry/BoxTypeSupportS.h>
#include <holo_base_msg/opendds_msg/geometry/pose_traits.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* Box2T traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Box2f>
{
    using ValueType   = ::holo_base_msg::geometry::Box2f;
    using MessageType = ::holo_base_msg::geometry::Box2f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Box2T<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::Box2T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Box2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Box2d>
{
    using ValueType   = ::holo_base_msg::geometry::Box2d;
    using MessageType = ::holo_base_msg::geometry::Box2d;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Box2T<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::Box2T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Box2d;
};


template <typename T>
struct DefaultConversionTraits<::holo::geometry::Box2T<T>>
{
    using ValueType   = ::holo::geometry::Box2T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.width = value.GetWidth();
        message.height = value.GetHeight();
        DefaultConversionTraits<::holo::geometry::Pose2T<T>>::Convert(value.GetPose(), message.pose);
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        ::holo::geometry::Pose2T<T> pose;
        DefaultConversionTraits<::holo::geometry::Pose2T<T>>::Convert(message.pose, pose);
        value = ValueType(message.width, message.height, pose);
    }
};

/* Box3T traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Box3f>
{
    using ValueType   = ::holo_base_msg::geometry::Box3f;
    using MessageType = ::holo_base_msg::geometry::Box3f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Box3T<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::Box3T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Box3f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Box3d>
{
    using ValueType   = ::holo_base_msg::geometry::Box3d;
    using MessageType = ::holo_base_msg::geometry::Box3d;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Box3T<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::Box3T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Box3d;
};


template <typename T>
struct DefaultConversionTraits<::holo::geometry::Box3T<T>>
{
    using ValueType   = ::holo::geometry::Box3T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.width = value.GetWidth();
        message.height = value.GetHeight();
        message.depth  = value.GetDepth();
        DefaultConversionTraits<::holo::geometry::Pose3T<T>>::Convert(value.GetPose(), message.pose);
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        ::holo::geometry::Pose3T<T> pose;
        DefaultConversionTraits<::holo::geometry::Pose3T<T>>::Convert(message.pose, pose);
        value = ValueType(message.width, message.height, message.depth, pose);
    }
};

}  // namespace opendds_wrapper

#endif
