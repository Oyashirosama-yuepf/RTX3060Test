#ifndef HOLO_IO_COMMON_ODOMETRY_H_
#define HOLO_IO_COMMON_ODOMETRY_H_

#include <holo/common/odometry.h>
#include <holo/io/common/coordinate.h>
#include <holo/io/common/timestamp.h>
#include <holo/io/geometry/pose3.h>
#include <holo/io/numerics/matrix.h>
#include <holo/io/numerics/vector.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::common::OdometryT<T>>
{
    using ValueType   = holo::common::OdometryT<T>;
    using Timestamp   = holo::common::Timestamp;
    using Vector3Type = typename ValueType::Vector3Type;
    using Vector6Type = typename ValueType::Vector6Type;
    using Matrix6Type = typename ValueType::Matrix6Type;
    using Pose3Type   = typename ValueType::Pose3Type;
    using Status      = typename ValueType::Status;
    using Source      = typename ValueType::Source;
    using Coordinate  = typename ValueType::Coordinate;

    static std::vector<std::pair<std::string, Status> > const& StatusStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, Status> > status_type_str = {
            {"ALLGOOD", Status::ALLGOOD},
            {"SOLUTIONNOGOOD", Status::SOLUTIONNOGOOD},
            {"POSITIONINACTIVE", Status::POSITIONINACTIVE},
            {"ORIENTATIONINACTIVE", Status::ORIENTATIONINACTIVE},
            {"LINEARVELOCITYINACTIVE", Status::LINEARVELOCITYINACTIVE},
            {"ANGULARVELOCITYINACTIVE", Status::ANGULARVELOCITYINACTIVE},
            {"LINEARACCELERATIONINACTIVE", Status::LINEARACCELERATIONINACTIVE},
            {"UNKNOWN", Status::UNKNOWN}
        };
        return status_type_str;
    }

    static std::vector<std::pair<std::string, Source> > const& SourceStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, Source> > source_type_str = {
            {"NONE", Source::NONE},
            {"GNSS", Source::GNSS},
            {"IMU", Source::IMU},
            {"VISION", Source::VISION},
            {"WHEEL", Source::WHEEL},
            {"RADAR", Source::RADAR},
            {"LIDAR", Source::LIDAR},
            {"SEMANTIC", Source::SEMANTIC},
            {"HD_MAP", Source::HD_MAP},
            {"RTK", Source::RTK},
            {"DETECTED_LANE", Source::DETECTED_LANE},
            {"UNKNOWN", Source::UNKNOWN}
        };
        return source_type_str;
    }

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"]           = rhs.GetTimestamp();
        node["parent_coordinate"]   = rhs.GetCoordinate();
        node["child_coordinate"]    = rhs.GetChildCoordinate();
        node["precision"]           = rhs.GetPrecisionFlags();
        node["pose"]                = rhs.GetPose();
        node["velocity"]            = rhs.GetVelocity();
        node["linear_acceleration"] = rhs.GetLinearAcceleration();
        node["pose_covariance"]     = rhs.GetPoseCovariance();
        node["velocity_covariance"] = rhs.GetVelocityCovariance();

        for (auto const& value : StatusStringTypePairs())
        {
            if (value.second == rhs.GetStatus())
            {
                node["status"] = value.first;
            }
        }    
        for (auto const& value : SourceStringTypePairs())
        {
            if (value.second == rhs.GetSource())
            {
                node["source"] = value.first;
            }
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
            rhs.SetCoordinate(node["parent_coordinate"].as<Coordinate>());
            rhs.SetChildCoordinate(node["child_coordinate"].as<Coordinate>());
            rhs.SetPrecisionFlags(node["precision"].as<uint32_t>());
            rhs.SetPose(node["pose"].as<Pose3Type>());
            rhs.SetVelocity(node["velocity"].as<Vector6Type>());
            rhs.SetLinearAcceleration(node["linear_acceleration"].as<Vector3Type>());
            rhs.SetPoseCovariance(node["pose_covariance"].as<Matrix6Type>());
            rhs.SetVelocityCovariance(node["velocity_covariance"].as<Matrix6Type>());

            bool status_flag = false;
            for (auto const& value : StatusStringTypePairs())
            {
                if (value.first == node["status"].as<std::string>())
                {
                    rhs.SetStatus(value.second);
                    status_flag = true;
                }
            }
            if(!status_flag)
            {
                if (YAML::IsDigit(node["status"].as<std::string>()))
                {
                    rhs.SetStatus(static_cast<Status>(node["status"].as<uint16_t>()));
                }
                else
                {
                    return false;
                }
            }

            bool source_flag = false;
            for (auto const& value : SourceStringTypePairs())
            {
                if (value.first == node["source"].as<std::string>())
                {
                    rhs.SetSource(value.second);
                    source_flag = true;
                }
            }
            if(!source_flag)
            {
                if (YAML::IsDigit(node["source"].as<std::string>()))
                {
                    rhs.SetSource(static_cast<Source>(node["source"].as<uint16_t>()));
                }
                else
                {
                    return false;
                }
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};

}  // namespace YAML
#endif