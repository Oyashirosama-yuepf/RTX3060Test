#ifndef OPENDDS_MSG_GEOMETRY_ROT_TRAITS_H_
#define OPENDDS_MSG_GEOMETRY_ROT_TRAITS_H_

#include <holo/geometry/quaternion.h>
#include <holo/geometry/rot2.h>
#include <holo/geometry/rot3.h>
#include <holo_base_msg/geometry/RotC.h>
#include <holo_base_msg/geometry/RotS.h>
#include <holo_base_msg/geometry/RotTypeSupportC.h>
#include <holo_base_msg/geometry/RotTypeSupportImpl.h>
#include <holo_base_msg/geometry/RotTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* Rot2T traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Rot2f>
{
    using ValueType   = ::holo_base_msg::geometry::Rot2f;
    using MessageType = ::holo_base_msg::geometry::Rot2f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Rot2T<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::Rot2T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Rot2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Rot2d>
{
    using ValueType   = ::holo_base_msg::geometry::Rot2d;
    using MessageType = ::holo_base_msg::geometry::Rot2d;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Rot2T<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::Rot2T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Rot2d;
};

template <typename T>
struct DefaultConversionTraits<::holo::geometry::Rot2T<T>>
{
    using ValueType   = ::holo::geometry::Rot2T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.theta = value.GetTheta();
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value = ValueType(message.theta);
    }
};


/* Rot3T traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Rot3f>
{
    using ValueType   = ::holo_base_msg::geometry::Rot3f;
    using MessageType = ::holo_base_msg::geometry::Rot3f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Rot3T<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::Rot3T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Rot3f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::geometry::Rot3d>
{
    using ValueType   = ::holo_base_msg::geometry::Rot3d;
    using MessageType = ::holo_base_msg::geometry::Rot3d;
};

template <>
struct DefaultMessageTraits<::holo::geometry::Rot3T<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::Rot3T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Rot3d;
};

template <typename T>
struct DefaultConversionTraits<::holo::geometry::Rot3T<T>>
{
    using ValueType   = ::holo::geometry::Rot3T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        ::holo::geometry::QuaternionT<T> quaternion = value.ToQuaternion();
        message.w = quaternion.GetW();
        message.x = quaternion.GetX();
        message.y = quaternion.GetY();
        message.z = quaternion.GetZ();
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        ::holo::geometry::QuaternionT<T> quaternion(message.w, message.x, message.y, message.z);
        ::holo::numerics::MatrixT<T, 3, 3> rotation_matrix = quaternion.ToRotationMatrix();
        value = ValueType(rotation_matrix);
    }
};


/* QuaternionT traits */

template <>
struct DefaultMessageTraits<::holo::geometry::QuaternionT<::holo::float32_t>>
{
    using ValueType   = ::holo::geometry::QuaternionT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::geometry::Rot3f;
};

template <>
struct DefaultMessageTraits<::holo::geometry::QuaternionT<::holo::float64_t>>
{
    using ValueType   = ::holo::geometry::QuaternionT<::holo::float64_t>;
    using MessageType = ::holo_base_msg::geometry::Rot3d;
};

template <typename T>
struct DefaultConversionTraits<::holo::geometry::QuaternionT<T>>
{
    using ValueType   = ::holo::geometry::QuaternionT<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.w = value.GetW();
        message.x = value.GetX();
        message.y = value.GetY();
        message.z = value.GetZ();
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value = ValueType(message.w, message.x, message.y, message.z);
    }
};

}  // namespace opendds_wrapper

#endif
