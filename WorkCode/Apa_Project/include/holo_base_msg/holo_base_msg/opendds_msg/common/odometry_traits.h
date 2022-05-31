#ifndef OPENDDS_MSG_COMMON_ODOMETRY_TRAITS_H_
#define OPENDDS_MSG_COMMON_ODOMETRY_TRAITS_H_

#include <holo/common/odometry.h>
#include <holo_base_msg/common/OdometryC.h>
#include <holo_base_msg/common/OdometryS.h>
#include <holo_base_msg/common/OdometryTypeSupportC.h>
#include <holo_base_msg/common/OdometryTypeSupportImpl.h>
#include <holo_base_msg/common/OdometryTypeSupportS.h>
#include <holo_base_msg/opendds_msg/geometry/pose_traits.h>
#include <holo_base_msg/opendds_msg/numerics/matrix_traits.h>
#include <holo_base_msg/opendds_msg/numerics/vector_traits.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* OdometryT traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::Odometryf>
{
    using ValueType   = ::holo_base_msg::common::Odometryf;
    using MessageType = ::holo_base_msg::common::Odometryf;
};

template <>
struct DefaultMessageTraits<::holo::common::OdometryT<::holo::float32_t>>
{
    using ValueType   = ::holo::common::OdometryT<::holo::float32_t>;
    using MessageType = ::holo_base_msg::common::Odometryf;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::common::Odometryd>
{
    using ValueType   = ::holo_base_msg::common::Odometryd;
    using MessageType = ::holo_base_msg::common::Odometryd;
};

template <>
struct DefaultMessageTraits<::holo::common::OdometryT<::holo::float64_t>>
{
    using ValueType   = ::holo::common::OdometryT<::holo::float64_t>;
    using MessageType = ::holo_base_msg::common::Odometryd;
};

template <typename T>
struct DefaultConversionTraits<::holo::common::OdometryT<T>>
{
    using ValueType   = ::holo::common::OdometryT<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec   = value.GetTimestamp().GetSec();
        message.stamp.nsec  = value.GetTimestamp().GetNsec();
        message.coord       = static_cast<::holo_base_msg::common::Coordinate>(value.GetCoordinate());
        message.child_coord = static_cast<::holo_base_msg::common::Coordinate>(value.GetChildCoordinate());
        message.status      = static_cast<::holo_base_msg::common::OdometryStatus>(value.GetStatus());
        message.source      = static_cast<::holo_base_msg::common::OdometryStatus>(value.GetSource());
        message.precision   = value.GetPrecisionFlags();
        DefaultConversionTraits<::holo::geometry::Pose3T<T>>::Convert(value.GetPose(), message.pose);
        DefaultConversionTraits<::holo::numerics::Vector6T<T>>::Convert(value.GetVelocity(), message.velocity);
        DefaultConversionTraits<::holo::numerics::Matrix6T<T>>::Convert(value.GetPoseCovariance(), message.pose_covariance);
        DefaultConversionTraits<::holo::numerics::Matrix6T<T>>::Convert(value.GetVelocityCovariance(),
                                                              message.velocity_covariance);
        DefaultConversionTraits<::holo::numerics::Vector3T<T>>::Convert(value.GetLinearAcceleration(),
                                                              message.linear_acceleration);
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});
        value.SetCoordinate(static_cast<::holo::common::Coordinate>(message.coord));
        value.SetChildCoordinate(::holo::common::Coordinate(message.child_coord));
        value.SetStatus(static_cast<typename ValueType::Status>(message.status));
        value.SetSource(static_cast<typename ValueType::Source>(message.source));
        value.SetPrecisionFlags(message.precision);
        DefaultConversionTraits<::holo::geometry::Pose3T<T>>::Convert(message.pose, value.GetPose());
        DefaultConversionTraits<::holo::numerics::Vector6T<T>>::Convert(message.velocity, value.GetVelocity());
        DefaultConversionTraits<::holo::numerics::Matrix6T<T>>::Convert(message.pose_covariance, value.GetPoseCovariance());
        DefaultConversionTraits<::holo::numerics::Matrix6T<T>>::Convert(message.velocity_covariance,
                                                              value.GetVelocityCovariance());
        DefaultConversionTraits<::holo::numerics::Vector3T<T>>::Convert(message.linear_acceleration,
                                                              value.GetLinearAcceleration());
    }
};

}  // namespace opendds_wrapper

#endif
