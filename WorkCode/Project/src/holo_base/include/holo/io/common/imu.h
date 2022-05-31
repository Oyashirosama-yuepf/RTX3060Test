#ifndef HOLO_IO_COMMON_IMU_H_
#define HOLO_IO_COMMON_IMU_H_

#include <yaml-cpp/yaml.h>
#include <holo/io/utils/utils.h>
#include <holo/io/common/coordinate.h>
#include <holo/io/common/timestamp.h>
#include <holo/io/geometry/point3.h>
#include <holo/common/imu.h>

namespace YAML
{
template <typename T>
struct convert<holo::common::ImuT<T>>
{
    using ValueType  = holo::common::ImuT<T>;
    using Timestamp  = holo::common::Timestamp;
    using Coordinate = holo::common::Coordinate;
    using Status     = typename ValueType::Status;
    using Point3Type = typename ValueType::Point3Type;
    
    static std::vector<std::pair<std::string, Status>> const& StatusStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, Status>> status_type_str = {
            {"ALLGOOD", Status::ALLGOOD},       {"GYROXERROR", Status::GYROXERROR},
            {"GYROYERROR", Status::GYROYERROR}, {"GYROZERROR", Status::GYROZERROR},
            {"ACCLXERROR", Status::ACCLXERROR}, {"ACCLYERROR", Status::ACCLYERROR},
            {"ACCLZERROR", Status::ACCLZERROR}, {"UNDEFINEDERROR", Status::UNDEFINEDERROR}};
        return status_type_str;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"]  = rhs.GetTimestamp();
        node["coordinate"] = rhs.GetCoordinate();

        node["angular_velocity"]    = rhs.template GetAngularVelocity<Point3Type>();
        node["linear_acceleration"] = rhs.template GetLinearAcceleration<Point3Type>();

        for (auto const& value : StatusStringTypePairs())
        {
            if (value.second == rhs.GetStatus())
            {
                node["status"] = value.first;
            }
        }
        return node;
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
            rhs.SetCoordinate(node["coordinate"].as<Coordinate>());
            rhs.SetAngularVelocity(node["angular_velocity"].as<Point3Type>());
            rhs.SetLinearAcceleration(node["linear_acceleration"].as<Point3Type>());

            bool status_flag = false;
            for (auto const& value : StatusStringTypePairs())
            {
                if (value.first == node["status"].as<std::string>())
                {
                    rhs.SetStatus(value.second);
                    status_flag = true;
                }
            }
            if (!status_flag)
            {
                if (IsDigit(node["status"].as<std::string>()))
                {
                    Status status = static_cast<Status>(node["status"].as<holo::uint16_t>());
                    rhs.SetStatus(status);
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
    };
};

}  // namespace YAML

#endif