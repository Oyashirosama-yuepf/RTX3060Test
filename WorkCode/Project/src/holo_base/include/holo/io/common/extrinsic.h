#ifndef HOLO_IO_COMMON_EXTRINSIC_H_
#define HOLO_IO_COMMON_EXTRINSIC_H_

#include <holo/common/extrinsic.h>

namespace YAML
{
template <typename T>
struct convert<holo::common::ExtrinsicT<T>>
{
    using ScalarType = T;
    using ValueType  = holo::common::ExtrinsicT<ScalarType>;

    static Node encode(ValueType const& rhs)
    {
        holo::geometry::QuaternionT<ScalarType> q(rhs.GetPose().GetRotation().ToMatrix());

        Node node;
        node["x"]  = rhs.GetPose().GetX();
        node["y"]  = rhs.GetPose().GetY();
        node["z"]  = rhs.GetPose().GetZ();
        node["qw"] = q.GetW(); 
        node["qx"] = q.GetX(); 
        node["qy"] = q.GetY(); 
        node["qz"] = q.GetZ();
        node["parent_coordinate"] =
            static_cast<uint32_t>(rhs.GetParentCoordinate());
        node["child_coordinate"] = static_cast<uint32_t>(rhs.GetChildCoordinate());
        if (rhs.GetChildCoordinate().GetType() == holo::common::Coordinate::Type::VEHICLE)
        {
            node["sensor_id"] = static_cast<uint32_t>(rhs.GetSensorId());
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        ScalarType               x = 0.0, y = 0.0, z = 0.0, qw = 1.0, qx = 0.0, qy = 0.0, qz = 0.0;
        holo::common::Coordinate parent_coordinate;
        holo::common::Coordinate child_coordinate;

        try
        {
            x                 = node["x"].as<ScalarType>();
            y                 = node["y"].as<ScalarType>();
            z                 = node["z"].as<ScalarType>();
            qw                = node["qw"].as<ScalarType>();
            qx                = node["qx"].as<ScalarType>();
            qy                = node["qy"].as<ScalarType>();
            qz                = node["qz"].as<ScalarType>();
            parent_coordinate = node["parent_coordinate"].as<uint32_t>();

            if (node["sensor_id"])
            {
                holo::common::SensorId sid = node["sensor_id"].as<uint32_t>();
                child_coordinate.SetType(holo::common::Coordinate::Type::VEHICLE);
                child_coordinate.SetVehicleSensorId(sid);
            }
            if (node["child_coordinate"])
            {
                child_coordinate = node["child_coordinate"].as<uint32_t>();
            }

            holo::geometry::QuaternionT<ScalarType> q(qw, qx, qy, qz);

            holo::geometry::Rot3T<ScalarType>   r(q.ToRotationMatrix());
            holo::geometry::Point3T<ScalarType> t(x, y, z);

            rhs.SetParentCoordinate(parent_coordinate);
            rhs.SetChildCoordinate(child_coordinate);
            rhs.SetPose(holo::geometry::Pose3T<ScalarType>(r, t));

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
