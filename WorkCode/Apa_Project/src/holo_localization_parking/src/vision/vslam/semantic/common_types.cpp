/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_types.cpp
 * @brief this file defines common_types for semantic slam
 * @author Yanwei Du (duyanwei@holomatic.com), Heiko Yu (yuchangsong@holomatic.com), Changxi
 * Cheng(chengchangxi@holomatic.com)
 * @date 2021-02-25
 */

#include <holo/localization/vision/vslam/semantic/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
/**
 * @addtogroup semantic
 * @{
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point3 BirdviewParameters::convertToBody(const Point2& pti) const
{
    // extrinsic which can transform a point from avm camera to ground coordinate
    // @todo(Feng.Li; chengchangxi@holomatic.com) add this parameters to config file
    static Pose3 gEa(Rot3::Rx(holo::Radian(180.0)), Point3(-6.0, 6.0, 0.0));
    return bEg.TransformFrom(gEa * Point3(pti * pixel_per_meter));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point3 BirdviewParameters::convertToImage(const Point3& ptb, const Scalar downscale) const
{
    static Pose3 gEa(Rot3::Rx(holo::Radian(180.0)), Point3(-6.0, 6.0, 0.0));
    Pose3        bEa = bEg * gEa;
    const Point3 ptc = bEa.TransformTo(ptb / downscale) / pixel_per_meter;
    return Point3(ptc.GetX(), ptc.GetY(), 0.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewParameters BirdviewParameters::GenerateExample()
{
    BirdviewParameters parameters;

    parameters.pixel_per_meter = 1;
    parameters.bEg             = Pose3::Identity();

    return parameters;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewParameters BirdviewParameters::LoadFromYaml(const yaml::Node& node)
{
    BirdviewParameters parameters;

    try
    {
        /*
        const Scalar min_x = node["min_x"].as<Scalar>();
        // const Scalar max_x = node["max_x"].as<Scalar>();
        // const Scalar min_y = node["min_y"].as<Scalar>();
        const Scalar max_y = node["max_y"].as<Scalar>();
        // const Scalar car_front_length    = node["car_front_length"].as<Scalar>();
        // const Scalar car_rear_length     = node["car_rear_length"].as<Scalar>();
        // const Scalar car_half_width      = node["car_half_width"].as<Scalar>();
        const Scalar car_body_height     = node["car_body_height"].as<Scalar>();
        */
        const Scalar pixel_per_milimeter = node["pixel_per_milimeter"].as<Scalar>();

        parameters.pixel_per_meter = pixel_per_milimeter / 1e3;

        Quaternion q_bg(node["q_bg"][0].as<Scalar>(1.0), node["q_bg"][1].as<Scalar>(0.0),
                        node["q_bg"][2].as<Scalar>(0.0), node["q_bg"][3].as<Scalar>(0.0));
        Rot3       R_bg(q_bg.ToRotationMatrix());
        Point3     t_bg(node["t_bg"][0].as<Scalar>(), node["t_bg"][1].as<Scalar>(), node["t_bg"][2].as<Scalar>());
        parameters.bEg = Pose3(R_bg, t_bg);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return parameters;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotType Utility::TransformParkingSlot(const ParkingSlotType& in, const Pose3& tTs)
{
    // @todo how should we handle (width, height, angle) which is the description of the detected box

    // transforming vertices
    ParkingSlotType out = in;
    out.vertices[0]     = tTs.TransformFrom(in.vertices[0]);
    out.vertices[1]     = tTs.TransformFrom(in.vertices[1]);
    if (in.is_rear_vertex_available)
    {
        out.vertices[2] = tTs.TransformFrom(in.vertices[2]);
        out.vertices[3] = tTs.TransformFrom(in.vertices[3]);
    }
    if (in.is_center_vertex_available)
    {
        out.center_vertex = tTs.TransformFrom(in.center_vertex);
    }
    if (in.is_stopper_available)
    {
        out.stopper_vertices[0] = tTs.TransformFrom(in.stopper_vertices[0]);
        out.stopper_vertices[1] = tTs.TransformFrom(in.stopper_vertices[1]);
    }
    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotFrameType Utility::TransformParkingSlotFrame(const ParkingSlotFrameType& in, const Pose3& tTs)
{
    ParkingSlotFrameType out(in.GetTimestamp(), in.GetCoordinate());

    for (const auto& ps : in)
    {
        if (!ps.is_valid)
        {
            out.emplace_back(ps);
        }
        else
        {
            out.emplace_back(TransformParkingSlot(ps, tTs));
        }
    }

    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Point3> Utility::ConvertToVector(const ParkingSlotType& in)
{
    std::vector<Point3> out;

    // front vertices
    out.emplace_back(in.vertices[0u]);
    out.emplace_back(in.vertices[1u]);

    // rear vertices
    if (in.is_rear_vertex_available)
    {
        out.emplace_back(in.vertices[2u]);
        out.emplace_back(in.vertices[3u]);
    }

    // center vertex
    if (in.is_center_vertex_available)
    {
        out.emplace_back(in.center_vertex);
    }

    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Utility::GeneratePointOnLine(const Point3& start, const Point3& end, std::vector<Point3>& pts)
{
    uint16_t pt_num = 50;

    float64_t start_x = start.GetX();
    float64_t start_y = start.GetY();
    float64_t start_z = start.GetZ();

    float64_t end_x = end.GetX();
    float64_t end_y = end.GetY();
    float64_t end_z = end.GetZ();

    float64_t inc_x = (end_x - start_x) / pt_num;
    float64_t inc_y = (end_y - start_y) / pt_num;
    float64_t inc_z = (end_z - start_z) / pt_num;

    for (float64_t i = 0; i < pt_num; i += 1)
    {
        float64_t x = start_x + i * inc_x;
        float64_t y = start_y + i * inc_y;
        float64_t z = start_z + i * inc_z;
        pts.emplace_back(Point3(x, y, z));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCloudXYZIRRgbSt Utility::ConvertToPointCloud(const std::unordered_map<int64_t, ParkingSlotType>& slot_map,
                                                  const std::vector<Pose3>&                           trajectory)
{
    PointCloudXYZIRRgbSt pcd_msg(slot_map.size() * 250 + trajectory.size() * 10 + 300);
    pcd_msg.SetTimestamp(holo::Timestamp());
    pcd_msg.SetCoordinate(holo::Coordinate());
    pcd_msg.SetPose(Pose3::Identity().Cast<holo::float32_t>());
    uint64_t i = 0;

    for (const auto& indexed_slot : slot_map)
    {
        const auto& slot = indexed_slot.second;

        for (size_t j = 0; j < 4; j++)
        {
            Point3f pt = slot.vertices[j].Cast<::holo::float32_t>();
            pcd_msg[i].SetX(pt.GetX());
            pcd_msg[i].SetY(pt.GetY());
            pcd_msg[i].SetZ(pt.GetZ());
            pcd_msg[i].SetIntensity(0.0);
            i++;
        }

        std::vector<Point3> pts;

        // draw edge 1-2, 2-3, 3-0
        GeneratePointOnLine(slot.vertices[1], slot.vertices[2], pts);
        GeneratePointOnLine(slot.vertices[2], slot.vertices[3], pts);
        GeneratePointOnLine(slot.vertices[3], slot.vertices[0], pts);

        // draw entrance 0-1
        // GeneratePointOnLine(slot.vertices[0], slot.vertices[1], pts);

        for (const auto& edge : pts)
        {
            Point3f pt = edge.Cast<::holo::float32_t>();
            pcd_msg[i].SetX(pt.GetX());
            pcd_msg[i].SetY(pt.GetY());
            pcd_msg[i].SetZ(pt.GetZ());
            pcd_msg[i].SetIntensity(0.0);
            i++;
        }
    }

    for (const auto& pose : trajectory)
    {
        Point3  p  = pose.GetTranslation();
        Point3f pt = p.Cast<::holo::float32_t>();
        pcd_msg[i].Set(pt.GetX(), pt.GetY(), pt.GetZ());
        pcd_msg[i].SetIntensity(0.0);
        i++;
    }

    const auto learned_path = holo_io::Load<Odometry>("./vehicle_odometry.txt");
    for (const auto& odo : learned_path)
    {
        Point3  p  = odo.GetPose().GetTranslation();
        Point3f pt = p.Cast<::holo::float32_t>();
        pcd_msg[i].Set(pt.GetX(), pt.GetY(), pt.GetZ());
        pcd_msg[i].SetIntensity(0.0);
        i++;
    }

    return pcd_msg;
}

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo
