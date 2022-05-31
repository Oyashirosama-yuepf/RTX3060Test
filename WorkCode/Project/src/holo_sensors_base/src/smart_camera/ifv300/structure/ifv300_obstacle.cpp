/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_obstacle.c
 * @brief A class to describe delphi ifv300 obstacle
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/25
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/ifv300/structure/ifv300_obstacle.h>

namespace holo
{
namespace sensors
{
namespace ifv300
{
const float32_t      Ifv300Obstacle::kobj_width_min_             = 0.1f;
const float32_t      Ifv300Obstacle::kobj_length_                = 0.1f;
const float32_t      Ifv300Obstacle::kobj_height_min_            = 0.1f;
const float32_t      Ifv300Obstacle::kconfidence_                = 1.0f;
const Classification Ifv300Obstacle::kobj_class_remap_table_[16] = {
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),          // 0 "undetermined"
    Classification(Classification::MainType::VEHICLE, Classification::SubType::CAR),              // 1 "car"
    Classification(Classification::MainType::BIKE, Classification::SubType::MOTOBIKE),            // 2 "motorcycle"
    Classification(Classification::MainType::VEHICLE, Classification::SubType::TRUCK),            // 3 "truck"
    Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN),    // 4 "pedestrian"
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),          // 5 "reserved"
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),          // 6 "reserved"
    Classification(Classification::MainType::ANIMAL, Classification::SubType::UNKNOWN),           // 7 "animal"
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN_MOVABLE),  // 8 "general on-road
                                                                                                  // object"
    Classification(Classification::MainType::BIKE, Classification::SubType::BICYCLE),             // 9 "bicycle"
    Classification(Classification::MainType::VEHICLE, Classification::SubType::UNKNOWN),  // 10 "unidentified vehicle"
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),  // 11
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),  // 12
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),  // 13
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),  // 14
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN)   // 15
};

void Ifv300Obstacle::ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const
{
    holo::geometry::Point3f  position(long_pos_, -lat_pos_, 0.0f);
    holo::geometry::Point3f  position_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f relative_velocity(long_vel_, -lat_vel_, 0.0f);
    holo::numerics::Vector3f relative_velocity_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration(long_accel_, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration_sigma(0.0f, 0.0f, 0.0f);
    holo::geometry::Point2f  position2f(long_pos_, -lat_pos_);
    float32_t                width  = std::max(width_, kobj_width_min_);
    float32_t                height = std::max(height_, kobj_height_min_);
    holo::geometry::Box2f    box2(position2f, width, kobj_length_, 0.0f);
    holo::geometry::Rot3f    rot3;
    holo::geometry::Point3f  point3(long_pos_ - kobj_length_ * 0.5f, -lat_pos_ - width * 0.5f, -height * 0.5f);
    holo::geometry::Pose3f   pose3(rot3, point3);
    holo::geometry::Box3f    box3(width, height, kobj_length_, pose3);

    output.SetTimestamp(timestamp_);
    output.SetObstacleId(object_id_);
    output.SetClassification(kobj_class_remap_table_[classification_]);
    output.SetObstacleExistScore(kconfidence_);
    output.SetPosition(position);
    output.SetPositionSigma(position_sigma);
    output.SetRelativeVelocity(relative_velocity);
    output.SetRelativeVelocitySigma(relative_velocity_sigma);
    output.SetObstacleBBox3D(box3);
    output.SetMotionStatus(obstacle::MotionStatus::UNKNOWN);
    if (cut_in_out_ == 3)  // CUT IN
    {
        if (-lat_pos_ < 0)
        {
            output.SetCutInCutOut(obstacle::CutInCutOut::NEXT_CUT_IN_RIGHT);
        }
        else
        {
            output.SetCutInCutOut(obstacle::CutInCutOut::NEXT_CUT_IN_LEFT);
        }
    }
    else if (cut_in_out_ == 4)  // CUT OUT
    {
        if (-lat_pos_ < 0)
        {
            output.SetCutInCutOut(obstacle::CutInCutOut::NEXT_CUT_OUT_RIGHT);
        }
        else
        {
            output.SetCutInCutOut(obstacle::CutInCutOut::NEXT_CUT_OUT_LEFT);
        }
    }
    else
    {
        output.SetCutInCutOut(obstacle::CutInCutOut::UNKNOWN);
    }
    output.SetAcceleration(acceleration);
    output.SetAccelerationSigma(acceleration_sigma);
    output.SetImageBBox2D(box2);
}

void Ifv300Obstacle::ConvertToHoloObstacleWithTransform(holo::obstacle::ObstacleVisionT<float32_t>& output,
                                                        const holo::common::Extrinsicf&             extrinsic) const
{
    ConvertToHoloObstacle(output);

    holo::geometry::Point3f      position          = extrinsic.GetPose().TransformFrom(output.GetPosition());
    holo::numerics::Vector3f     relative_velocity = extrinsic.GetPose().TransformFrom(output.GetRelativeVelocity());
    holo::geometry::Pose3f       pose3             = extrinsic.GetPose() * output.GetObstacleBBox3D().GetPose();
    const holo::geometry::Box3f& box3_in           = output.GetObstacleBBox3D();
    holo::geometry::Box3f        box3_out(box3_in.GetWidth(), box3_in.GetHeight(), box3_in.GetDepth(), pose3);

    output.SetCoordinate(extrinsic.GetParentCoordinate());
    output.SetPosition(position);
    output.SetRelativeVelocity(relative_velocity);
    output.SetObstacleBBox3D(box3_out);
}

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo
