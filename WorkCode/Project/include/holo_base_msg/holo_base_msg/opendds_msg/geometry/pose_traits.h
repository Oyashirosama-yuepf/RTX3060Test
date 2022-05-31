#ifndef OPENDDS_MSG_GEOMETRY_POSE_TRAITS_H_
#define OPENDDS_MSG_GEOMETRY_POSE_TRAITS_H_

#include <holo/geometry/pose2.h>
#include <holo/geometry/pose3.h>
#include <holo_base_msg/geometry/PoseC.h>
#include <holo_base_msg/geometry/PoseS.h>
#include <holo_base_msg/geometry/PoseTypeSupportC.h>
#include <holo_base_msg/geometry/PoseTypeSupportImpl.h>
#include <holo_base_msg/geometry/PoseTypeSupportS.h>
#include <holo_base_msg/opendds_msg/geometry/point_traits.h>
#include <holo_base_msg/opendds_msg/geometry/rot_traits.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* Pose2T traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Pose2f>
{
    using ValueType   = ::holo_base_msg::geometry::Pose2f;
    using MessageType = ::holo_base_msg::geometry::Pose2f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Pose2T<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::Pose2T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Pose2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Pose2d>
{
    using ValueType   = ::holo_base_msg::geometry::Pose2d;
    using MessageType = ::holo_base_msg::geometry::Pose2d;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Pose2T<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::Pose2T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Pose2d;
};

template <typename T>
struct DefaultConversionTraits<::holo::geometry::Pose2T<T>>
{
    using ValueType   = ::holo::geometry::Pose2T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        DefaultConversionTraits<::holo::geometry::Rot2T<T>>::Convert(value.GetRotation(), message.rotation);
        DefaultConversionTraits<::holo::geometry::Point2T<T>>::Convert(value.GetTranslation(), message.translation);
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        ::holo::geometry::Rot2T<T> rotation;
        DefaultConversionTraits<::holo::geometry::Rot2T<T>>::Convert(message.rotation, rotation);
        ::holo::geometry::Point2T<T> translation;
        DefaultConversionTraits<::holo::geometry::Point2T<T>>::Convert(message.translation, translation);
        value = ValueType(rotation, translation);
    }
};

/* Pose3f traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Pose3f>
{
    using ValueType   = ::holo_base_msg::geometry::Pose3f;
    using MessageType = ::holo_base_msg::geometry::Pose3f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Pose3T<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::Pose3T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Pose3f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Pose3d>
{
    using ValueType   = ::holo_base_msg::geometry::Pose3d;
    using MessageType = ::holo_base_msg::geometry::Pose3d;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Pose3T<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::Pose3T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Pose3d;
};

template <typename T>
struct DefaultConversionTraits<::holo::geometry::Pose3T<T>>
{
    using ValueType   = ::holo::geometry::Pose3T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        DefaultConversionTraits<::holo::geometry::Rot3T<T>>::Convert(value.GetRotation(), message.rotation);
        DefaultConversionTraits<::holo::geometry::Point3T<T>>::Convert(value.GetTranslation(), message.translation);
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        ::holo::geometry::Rot3T<T> rotation;
        DefaultConversionTraits<::holo::geometry::Rot3T<T>>::Convert(message.rotation, rotation);
        ::holo::geometry::Point3T<T> translation;
        DefaultConversionTraits<::holo::geometry::Point3T<T>>::Convert(message.translation, translation);
        value = ValueType(rotation, translation);
    }
};

}  // namespace opendds_wrapper

#endif
