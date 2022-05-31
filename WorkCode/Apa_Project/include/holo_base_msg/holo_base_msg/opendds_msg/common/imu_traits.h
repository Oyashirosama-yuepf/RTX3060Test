#ifndef OPENDDS_MSG_COMMON_IMU_TRAITS_H_
#define OPENDDS_MSG_COMMON_IMU_TRAITS_H_

#include <holo/common/imu.h>
#include <holo/common/imu_bias.h>
#include <holo_base_msg/common/ImuC.h>
#include <holo_base_msg/common/ImuS.h>
#include <holo_base_msg/common/ImuTypeSupportC.h>
#include <holo_base_msg/common/ImuTypeSupportImpl.h>
#include <holo_base_msg/common/ImuTypeSupportS.h>
#include <holo_base_msg/opendds_msg/geometry/point_traits.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* ImuT traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::Imuf>
{
    using ValueType   = ::holo_base_msg::common::Imuf;
    using MessageType = ::holo_base_msg::common::Imuf;
};

template <>
struct DefaultMessageTraits<::holo::common::ImuT<::holo::float32_t>>
{
    using ValueType   = ::holo::common::ImuT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::common::Imuf;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::common::Imud>
{
    using ValueType   = ::holo_base_msg::common::Imud;
    using MessageType = ::holo_base_msg::common::Imud;
};

template <>
struct DefaultMessageTraits<::holo::common::ImuT<::holo::float64_t>>
{
    using ValueType   = ::holo::common::ImuT<::holo::float64_t>;
    using MessageType = ::holo_base_msg::common::Imud;
};

template <typename T>
struct DefaultConversionTraits<::holo::common::ImuT<T>>
{
    using ValueType   = ::holo::common::ImuT<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        using Point3Type       = typename ValueType::Point3Type;
        using Point3TraitsType = DefaultConversionTraits<Point3Type>;
        message.stamp.sec       = value.GetTimestamp().GetSec();
        message.stamp.nsec      = value.GetTimestamp().GetNsec();
        message.coord           = static_cast<::holo::uint32_t>(value.GetCoordinate());
        Point3TraitsType::Convert(value.template GetAngularVelocity<Point3Type>(), message.angular_velocity);
        Point3TraitsType::Convert(value.template GetLinearAcceleration<Point3Type>(), message.linear_acceleration);
        message.status = static_cast<holo_base_msg::common::ImuStatus>(value.GetStatus());
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        using Point3Type       = typename ValueType::Point3Type;
        using Point3TraitsType = DefaultConversionTraits<Point3Type>;
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});
        value.SetCoordinate(static_cast<::holo::common::Coordinate>(message.coord));
        Point3Type angular_velocity;
        Point3TraitsType::Convert(message.angular_velocity, angular_velocity);
        Point3Type linear_acceleration;
        Point3TraitsType::Convert(message.linear_acceleration, linear_acceleration);
        value.template SetAngularVelocity(angular_velocity);
        value.template SetLinearAcceleration(linear_acceleration);
        value.template SetStatus(static_cast<typename ValueType::Status>(message.status));
    }
};

/* ImuBiasT traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::ImuBiasf>
{
    using ValueType   = ::holo_base_msg::common::ImuBiasf;
    using MessageType = ::holo_base_msg::common::ImuBiasf;
};

template <>
struct DefaultMessageTraits<::holo::common::ImuBiasT<::holo::float32_t>>
{
    using ValueType   = ::holo::common::ImuBiasT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::common::ImuBiasf;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::common::ImuBiasd>
{
    using ValueType   = ::holo_base_msg::common::ImuBiasd;
    using MessageType = ::holo_base_msg::common::ImuBiasd;
};

template <>
struct DefaultMessageTraits<::holo::common::ImuBiasT<::holo::float64_t>>
{
    using ValueType   = ::holo::common::ImuBiasT<::holo::float64_t>;
    using MessageType = ::holo_base_msg::common::ImuBiasd;
};

template <typename T>
struct DefaultConversionTraits<::holo::common::ImuBiasT<T>>
{
    using ValueType   = ::holo::common::ImuBiasT<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        using Point3Type       = typename ValueType::Point3Type;
        using Point3TraitsType = DefaultConversionTraits<Point3Type>;
        message.stamp.sec       = value.GetTimestamp().GetSec();
        message.stamp.nsec      = value.GetTimestamp().GetNsec();
        message.coord      = static_cast<::holo::uint32_t>(value.GetCoordinate());
        Point3TraitsType::Convert(value.template GetAngularVelocityBias<Point3Type>(), message.angular_velocity_bias);
        Point3TraitsType::Convert(value.template GetLinearAccelerationBias<Point3Type>(), message.linear_acceleration_bias);
        Point3TraitsType::Convert(value.template GetAngularVelocityBiasCovariance<Point3Type>(), message.angular_velocity_bias_cov);
        Point3TraitsType::Convert(value.template GetLinearAccelerationBiasCovariance<Point3Type>(), message.linear_acceleration_bias_cov);
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        using Point3Type       = typename ValueType::Point3Type;
        using Point3TraitsType = DefaultConversionTraits<Point3Type>;
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});
        value.SetCoordinate(static_cast<::holo::common::Coordinate>(message.coord));
        Point3Type angular_velocity_bias;
        Point3Type linear_acceleration_bias;
        Point3Type angular_velocity_bias_cov;
        Point3Type linear_acceleration_bias_cov;
        Point3TraitsType::Convert(message.angular_velocity_bias, angular_velocity_bias);
        Point3TraitsType::Convert(message.linear_acceleration_bias, linear_acceleration_bias);
        Point3TraitsType::Convert(message.angular_velocity_bias_cov, angular_velocity_bias_cov);
        Point3TraitsType::Convert(message.linear_acceleration_bias_cov, linear_acceleration_bias_cov);
        value.template SetAngularVelocityBias(angular_velocity_bias);
        value.template SetLinearAccelerationBias(linear_acceleration_bias);
        value.template SetAngularVelocityBiasCovariance(angular_velocity_bias_cov);
        value.template SetLinearAccelerationBiasCovariance(linear_acceleration_bias_cov);
    }
};

}  // namespace opendds_wrapper

#endif
