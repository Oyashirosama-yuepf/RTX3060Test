#ifndef HOLO_IO_COMMON_IMU_BIAS_H_
#define HOLO_IO_COMMON_IMU_BIAS_H_

#include <yaml-cpp/yaml.h>
#include <holo/io/utils/utils.h>
#include <holo/io/geometry/point3.h>
#include <holo/io/common/coordinate.h>
#include <holo/io/common/timestamp.h>
#include <holo/common/imu_bias.h>

namespace YAML
{
template <typename T>
struct convert<holo::common::ImuBiasT<T>>
{
    using ValueType  = holo::common::ImuBiasT<T>;
    using Timestamp  = holo::common::Timestamp;
    using Coordinate = holo::common::Coordinate;
    using Point3Type = typename ValueType::Point3Type;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"]  = rhs.GetTimestamp();
        node["coordinate"] = rhs.GetCoordinate();
        node["angular_velocity_bias"]    = rhs.template GetAngularVelocityBias<Point3Type>();
        node["linear_acceleration_bias"] = rhs.template GetLinearAccelerationBias<Point3Type>();
        node["angular_velocity_bias_covariance"] = rhs.template GetAngularVelocityBiasCovariance<Point3Type>();
        node["linear_acceleration_bias_covariance"] = rhs.template GetLinearAccelerationBiasCovariance<Point3Type>();
        return node;
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
            rhs.SetCoordinate(node["coordinate"].as<Coordinate>());
            rhs.SetAngularVelocityBias(node["angular_velocity_bias"].as<Point3Type>());
            rhs.SetLinearAccelerationBias(node["linear_acceleration_bias"].as<Point3Type>());
            rhs.SetAngularVelocityBiasCovariance(node["angular_velocity_bias_covariance"].as<Point3Type>());
            rhs.SetLinearAccelerationBiasCovariance(node["linear_acceleration_bias_covariance"].as<Point3Type>());

            return true;
        }
        catch (...)
        {
            return false;
        }
    };
};

}  // namespace YAML

#endif