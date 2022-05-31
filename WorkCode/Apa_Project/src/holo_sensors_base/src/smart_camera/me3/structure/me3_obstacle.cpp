/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_obstacle.c
 * @brief A class to describe mobileye obstacle
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/01/15
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/me3/structure/me3_obstacle.h>

namespace holo
{
namespace sensors
{
namespace mobileye
{
const float32_t MobileyeObstacle::kconfidence_ = 1.0f;

const Classification MobileyeObstacle::kclass_remap_table_[8] = {
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),        //! 0 "Unknown"
    Classification(Classification::MainType::VEHICLE, Classification::SubType::TRUCK),          //! 1 "Truck"
    Classification(Classification::MainType::VEHICLE, Classification::SubType::CAR),            //! 2 "Car"
    Classification(Classification::MainType::BIKE, Classification::SubType::MOTOBIKE),          //! 3 "MotorBike"
    Classification(Classification::MainType::BIKE, Classification::SubType::BICYCLE),           //! 4 "Bicycle"
    Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN),  //! 5 "Pedestrian"
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),        //! 6 "Undecided"
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),        //! 7 "Undefined"
};

const MotionStatus MobileyeObstacle::kmotion_status_remap_table_[16] = {
    MotionStatus::UNKNOWN,     //!  0 "Not Defined"
    MotionStatus::STATIONARY,  //!  1 "Standing (never moved back lights are on)"
    MotionStatus::STATIONARY,  //!  2 "Parked (never moved, back lights are off)"
    MotionStatus::STATIONARY,  //!  3 "Stopped (movable)"
    MotionStatus::UNKNOWN,     //!  4 "Unknown (movable)"
    MotionStatus::MOVING,      //!  5 "Moving (movable)"
    MotionStatus::STATIONARY,  //!  6 "Stopped (Oncoming )"
    MotionStatus::UNKNOWN,     //!  7 "Unknown (Oncoming )"
    MotionStatus::MOVING,      //!  8 "Moving (Oncoming )"
    MotionStatus::UNKNOWN,     //!  9 UNDEFINED
    MotionStatus::UNKNOWN,     //! 10 UNDEFINED
    MotionStatus::UNKNOWN,     //! 11 UNDEFINED
    MotionStatus::UNKNOWN,     //! 12 UNDEFINED
    MotionStatus::UNKNOWN,     //! 13 UNDEFINED
    MotionStatus::UNKNOWN,     //! 14 UNDEFINED
    MotionStatus::UNKNOWN,     //! 15 UNDEFINED
};

const CutInCutOut MobileyeObstacle::kcut_inout_remap_table_[16] = {
    CutInCutOut::UNKNOWN,             //!  0 "Unknown"
    CutInCutOut::HOST_CUT_IN_LEFT,    //!  1 "Host Cut In Left"
    CutInCutOut::HOST_CUT_IN_RIGHT,   //!  2 "Host Cut In Right"
    CutInCutOut::HOST_CUT_OUT_LEFT,   //!  3 "Host Cut Out Left"
    CutInCutOut::HOST_CUT_OUT_RIGHT,  //!  4 "Host Cut Out Right"
    CutInCutOut::NEXT_CUT_IN_LEFT,    //!  5 "Next Cut In Left"
    CutInCutOut::NEXT_CUT_IN_RIGHT,   //!  6 "Next Cut In Right"
    CutInCutOut::NEXT_CUT_OUT_LEFT,   //!  7 "Next Cut Out Left"
    CutInCutOut::NEXT_CUT_OUT_RIGHT,  //!  8 "Next Cut Out Right"
    CutInCutOut::UNKNOWN,             //!  9 UNDEFINED
    CutInCutOut::UNKNOWN,             //! 10 UNDEFINED
    CutInCutOut::UNKNOWN,             //! 11 UNDEFINED
    CutInCutOut::UNKNOWN,             //! 12 UNDEFINED
    CutInCutOut::UNKNOWN,             //! 13 UNDEFINED
    CutInCutOut::UNKNOWN,             //! 14 UNDEFINED
    CutInCutOut::UNKNOWN,             //! 15 UNDEFINED
};

void MobileyeObstacle::ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const
{
    holo::geometry::Point3f  position(longitudinal_dist_, -lateral_dist_, 0.0f);
    holo::geometry::Point3f  position_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f relative_velocity(longitudinal_velocity_, -lateral_velocity_, 0.0f);
    holo::numerics::Vector3f relative_velocity_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration(acceleration_, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration_sigma(0.0f, 0.0f, 0.0f);
    holo::geometry::Point2f  position2f(longitudinal_dist_, -lateral_dist_);
    float32_t                width  = std::max(width_, 0.01f);
    float32_t                length = 0.1f;
    float32_t                height = 1.0f;
    holo::geometry::Box2f    box2(position2f, width, length, 0.0f);
    holo::geometry::Rot3f    rot3;
    holo::geometry::Point3f  point3(longitudinal_dist_ - length * 0.5f, -lateral_dist_ - width * 0.5f, -height * 0.5f);
    holo::geometry::Pose3f   pose3(rot3, point3);
    holo::geometry::Box3f    box3(width, height, length, pose3);

    output.SetTimestamp(timestamp_);
    output.SetObstacleId(id_);
    output.SetClassification(kclass_remap_table_[object_class_]);
    output.SetObstacleExistScore(kconfidence_);
    output.SetPosition(position);
    output.SetPositionSigma(position_sigma);
    output.SetRelativeVelocity(relative_velocity);
    output.SetRelativeVelocitySigma(relative_velocity_sigma);
    output.SetObstacleBBox3D(box3);
    output.SetMotionStatus(kmotion_status_remap_table_[motion_status_]);
    output.SetCutInCutOut(kcut_inout_remap_table_[cut_in_out_]);
    output.SetAcceleration(acceleration);
    output.SetAccelerationSigma(acceleration_sigma);
    output.SetImageBBox2D(box2);
}

void MobileyeObstacle::ConvertToHoloObstacleWithTransform(holo::obstacle::ObstacleVisionT<float32_t>& output,
                                                          const holo::common::Extrinsicf&             extrinsic) const
{
    ConvertToHoloObstacle(output);

    holo::geometry::Point3f  position          = extrinsic.GetPose().TransformFrom(output.GetPosition());
    holo::numerics::Vector3f relative_velocity = extrinsic.GetPose().TransformFrom(output.GetRelativeVelocity());
    holo::geometry::Rot3f    rot3;
    holo::geometry::Pose3f   pose3(rot3, position);
    holo::geometry::Box3f    box3_in = output.GetObstacleBBox3D();
    holo::geometry::Box3f    box3_out(box3_in.GetWidth(), box3_in.GetHeight(), box3_in.GetDepth(), pose3);
    (void)relative_velocity;

    output.SetCoordinate(extrinsic.GetParentCoordinate());
    output.SetPosition(position);
    output.SetObstacleBBox3D(box3_out);
}

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
