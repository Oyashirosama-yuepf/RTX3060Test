/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file me8_obstacle.cpp
 * @brief A class to describe me8 obstacle
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/12/09
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/me8/structure/me8_obstacle.h>

namespace holo
{
namespace sensors
{
namespace me8
{
const float32_t      Me8Obstacle::kobj_width_min_            = 0.1f;
const float32_t      Me8Obstacle::kobj_length_min_           = 0.1f;
const float32_t      Me8Obstacle::kobj_height_min_           = 0.1f;
const float32_t      Me8Obstacle::kconfidence_               = 1.0f;
const Classification Me8Obstacle::kobj_class_remap_table_[8] = {
    Classification(Classification::MainType::VEHICLE, Classification::SubType::CAR),            //! 0 - car
    Classification(Classification::MainType::VEHICLE, Classification::SubType::TRUCK),          //! 1 - truck
    Classification(Classification::MainType::BIKE, Classification::SubType::UNKNOWN),           //! 2 - bike
    Classification(Classification::MainType::BIKE, Classification::SubType::BICYCLE),           //! 3 - bicycle
    Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN),  //! 4 - pedestrian
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),        //! 5 - general_object
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),        //! 6 - UNDEFINED
    Classification(Classification::MainType::VEHICLE, Classification::SubType::UNKNOWN)         //! 7 - uncertain_vcl
};
const holo::obstacle::MotionStatus Me8Obstacle::kmotion_status_remap_table_[8] = {
    MotionStatus::UNKNOWN,     //!  0 - Unknown
    MotionStatus::MOVING,      //!  1 - Moving
    MotionStatus::STATIONARY,  //!  2 - Stationary
    MotionStatus::STOPPED,     //!  3 - Stopped
    MotionStatus::UNKNOWN,     //!  4 - Moving Slowly
    MotionStatus::UNKNOWN,     //!  5 - UNDEFINED
    MotionStatus::UNKNOWN,     //!  6 - UNDEFINED
    MotionStatus::UNKNOWN      //!  7 - UNDEFINED
};

const holo::obstacle::CutInCutOut Me8Obstacle::kcut_inout_remap_table_[13][6] = {

    // !NEXT_LEFT_LANE             LEFT_LANE                      EGO_LANE              RIGHT_LANE                      NEXT_RIGHT_LANE                 NOT_ASSIGNED,
    CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN, CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,  //! MC_UNDEFINED
    CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN, CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,  //! MC_PASSING,
    CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN, CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,  //! MC_PASSING_IN,
    CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN, CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,  //! MC_PASSING_OUT,
    CutInCutOut::NEXT_CUT_IN_LEFT, CutInCutOut::HOST_CUT_IN_LEFT, CutInCutOut::UNKNOWN, CutInCutOut::HOST_CUT_IN_RIGHT, CutInCutOut::NEXT_CUT_IN_RIGHT, CutInCutOut::UNKNOWN,  //! MC_CLOSE_CUT_IN,
    CutInCutOut::NEXT_CUT_IN_LEFT, CutInCutOut::HOST_CUT_IN_LEFT, CutInCutOut::UNKNOWN, CutInCutOut::HOST_CUT_IN_RIGHT, CutInCutOut::NEXT_CUT_IN_RIGHT, CutInCutOut::UNKNOWN,  //! MC_MOVING_IN,
    CutInCutOut::NEXT_CUT_IN_LEFT, CutInCutOut::HOST_CUT_OUT_LEFT,CutInCutOut::UNKNOWN, CutInCutOut::HOST_CUT_OUT_RIGHT,CutInCutOut::NEXT_CUT_OUT_RIGHT,CutInCutOut::UNKNOWN,  //! MC_MOVING_OUT,
    CutInCutOut::NEXT_CUT_IN_LEFT, CutInCutOut::HOST_CUT_IN_LEFT, CutInCutOut::UNKNOWN, CutInCutOut::HOST_CUT_IN_RIGHT, CutInCutOut::NEXT_CUT_IN_RIGHT, CutInCutOut::UNKNOWN,  //! MC_CROSSING,
    CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN, CutInCutOut::HOST_CUT_IN_RIGHT, CutInCutOut::NEXT_CUT_IN_RIGHT, CutInCutOut::UNKNOWN,  //! MC_LTAP,
    CutInCutOut::NEXT_CUT_IN_LEFT, CutInCutOut::HOST_CUT_IN_LEFT, CutInCutOut::UNKNOWN, CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,  //! MC_RTAP,
    CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN, CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,  //! MC_MOVING,
    CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN, CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,  //! MC_PRECEEDING,
    CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN,          CutInCutOut::UNKNOWN, CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,           CutInCutOut::UNKNOWN,  //! MC_ONCOMING,
};

void Me8Obstacle::ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const
{
    holo::geometry::Point3f  position(long_distance_acc_, -lateral_distance_, 0.0f);
    holo::geometry::Point3f  position_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f relative_velocity(relative_long_velocity_, -relative_lat_velocity_, 0.0f);
    holo::numerics::Vector3f relative_velocity_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration(absolute_long_acc_, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration_sigma(0.0f, 0.0f, 0.0f);
    holo::geometry::Point2f  position2f(long_distance_acc_, -lateral_distance_);
    float32_t                width  = std::max(object_width_, kobj_width_min_);
    float32_t                height = std::max(1.0f, kobj_height_min_);  // no height with me8, set 1.0f
    float32_t                length = std::max(object_length_, kobj_length_min_);
    holo::geometry::Box2f    box2(position2f, width, length, 0.0f);
    holo::geometry::Rot3f    rot3;
    holo::geometry::Point3f  point3(long_distance_acc_ - length * 0.5f, -lateral_distance_ - width * 0.5f,
                                   -height * 0.5f);
    holo::geometry::Pose3f   pose3(rot3, point3);
    holo::geometry::Box3f    box3(width, height, length, pose3);

    output.SetTimestamp(timestamp_);
    output.SetObstacleId(object_id_);
    output.SetClassification(kobj_class_remap_table_[object_class_]);
    output.SetObstacleExistScore(kconfidence_);
    output.SetPosition(position);
    output.SetPositionSigma(position_sigma);
    output.SetRelativeVelocity(relative_velocity);
    output.SetRelativeVelocitySigma(relative_velocity_sigma);
    output.SetObstacleBBox3D(box3);
    output.SetMotionStatus(kmotion_status_remap_table_[object_motion_status_]);

    output.SetCutInCutOut(kcut_inout_remap_table_[object_motion_category_][lane_assignment_]);

    output.SetAcceleration(acceleration);
    output.SetAccelerationSigma(acceleration_sigma);
    output.SetImageBBox2D(box2);
}

void Me8Obstacle::ConvertToHoloObstacleWithTransform(holo::obstacle::ObstacleVisionT<float32_t>& output,
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

}  // namespace me8
}  // namespace sensors
}  // namespace holo
