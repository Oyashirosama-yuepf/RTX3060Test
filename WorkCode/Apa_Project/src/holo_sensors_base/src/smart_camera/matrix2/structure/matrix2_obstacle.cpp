/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2_obstacle.cpp
 * @brief A class to describe horizon matrix2 obstacle
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/05/21
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/matrix2/structure/matrix2_obstacle.h>

namespace holo
{
namespace sensors
{
namespace horizon_matrix2
{
/*
    ObstacleType
    0 "Vehicle" ;
    1 "Pedestrian"
    2 "Cyclist"
    3 "General Object"
*/
const Classification HorizonMatrix2Obstacle::type_remap_table_const_[4] = {
    Classification(Classification::MainType::VEHICLE, Classification::SubType::UNKNOWN),        //! 0 "vehicle"
    Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN),  //! 1 "pedestrian"
    Classification(Classification::MainType::BIKE, Classification::SubType::BICYCLE),           //! 2 "bicycle"
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),        //! 3 "general object"
};

/*
    VehicleSubType
    0 "Bus"
    1 "Small_Medium_Car"
    2 "Trucks"
    3 "Motors"
    4 "Special_vehicle"
    5 "Tiny_car"
*/
const Classification::SubType HorizonMatrix2Obstacle::vehicle_subtype_remap_table_const_[16] = {
    Classification::SubType::BUS,       //! 0 BUS
    Classification::SubType::CAR,       //! 1 SMALL MEDIUM CAR
    Classification::SubType::TRUCK,     //! 2 TRUCKS
    Classification::SubType::MOTOBIKE,  //! 3 MOTORS
    Classification::SubType::UNKNOWN,   //! 4 SPECIAL VEHICLES
    Classification::SubType::CAR,       //! 5 TINY CAR
    Classification::SubType::UNKNOWN,   //! 6 ??
    Classification::SubType::UNKNOWN,   //! 7 ??
    Classification::SubType::UNKNOWN,   //! 8 ??
    Classification::SubType::UNKNOWN,   //! 9 ??
    Classification::SubType::UNKNOWN,   //! 10 ??
    Classification::SubType::UNKNOWN,   //! 11 ??
    Classification::SubType::UNKNOWN,   //! 12 ??
    Classification::SubType::UNKNOWN,   //! 13 ??
    Classification::SubType::UNKNOWN,   //! 14 ??
    Classification::SubType::UNKNOWN,   //! 15 ??
};

/*
    ObstacleStatus
    0 "not defined"
    1 "standing neverMoved bckLightsOn"
    2 "stopped (movable)"
    3 "moving"
    4 "Oncoming"
    5 "Parked never moved, BckLightsOff"
    6 "Unused"
*/
const MotionStatus HorizonMatrix2Obstacle::motion_status_remap_table_const_[8] = {
    MotionStatus::UNKNOWN,   //! 0 "INVALID"
    MotionStatus::STOPPED,   //! 1 "STOPPED"
    MotionStatus::STOPPED,   //! 2 "STOPPED"
    MotionStatus::MOVING,    //! 3 "MOVING"
    MotionStatus::ONCOMING,  //! 4 "UNKNOWN"
    MotionStatus::STOPPED,   //! 5 "STATIONARY"
    MotionStatus::UNKNOWN,   //! 6 ""
    MotionStatus::UNKNOWN,   //! 7 ""
};

void HorizonMatrix2Obstacle::ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const
{
    holo::geometry::Point3f  position(pos_x_, pos_y_, 0.0f);
    holo::geometry::Point3f  position_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f relative_velocity(vel_x_, vel_y_, 0.0f);
    holo::numerics::Vector3f relative_velocity_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration(accel_x_, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration_sigma(0.0f, 0.0f, 0.0f);
    holo::geometry::Point2f  position2f(pos_x_, pos_y_);
    float32_t                width  = std::max(width_, 0.1f);
    float32_t                length = std::max(length_, 0.1f);
    float32_t                height = 1.0f;
    holo::geometry::Box2f    box2(position2f, width, length, holo::geometry::Radian<float32_t>(vehicle_angle_));
    holo::geometry::Rot3f    rot3 = holo::geometry::Rot3f::Rz(holo::geometry::Radian<float32_t>(vehicle_angle_));
    holo::geometry::Point3f  point3(pos_x_ - length * 0.5f, pos_y_ - width * 0.5f, -height * 0.5f);
    holo::geometry::Pose3f   pose3(rot3, point3);
    holo::geometry::Box3f    box3(width, height, length, pose3);
    Classification           classification = type_remap_table_const_[type_];
    if (classification.GetMainType() == Classification::MainType::VEHICLE)
    {
        if (vehicle_subtype_remap_table_const_[vehicle_subtype_ & 0x0F] == Classification::SubType::MOTOBIKE)
        {
            classification.SetMainType(Classification::MainType::BIKE);
        }
        classification.SetSubType(vehicle_subtype_remap_table_const_[vehicle_subtype_ & 0x0F]);
    }
    /*
        Move_in_and_Out
        0 "undefined"
        1 "in_host_lane"
        2 "out_host_lane"
        3 "cut_in"
        4 "cut_out"
    */
    holo::obstacle::CutInCutOut cut;
    if (move_in_and_out_ == 3)
    {
        if (pos_y_ > 0)
        {
            cut = holo::obstacle::CutInCutOut::HOST_CUT_IN_LEFT;
        }
        else
        {
            cut = holo::obstacle::CutInCutOut::HOST_CUT_IN_RIGHT;
        }
    }
    else if (move_in_and_out_ == 4)
    {
        if (pos_y_ > 0)
        {
            cut = holo::obstacle::CutInCutOut::HOST_CUT_OUT_LEFT;
        }
        else
        {
            cut = holo::obstacle::CutInCutOut::HOST_CUT_OUT_RIGHT;
        }
    }
    else
    {
        cut = holo::obstacle::CutInCutOut::UNKNOWN;
    }
    output.SetTimestamp(timestamp_);
    output.SetObstacleId(id_);
    output.SetClassification(classification);
    output.SetObstacleExistScore(1.0f);
    output.SetPosition(position);
    output.SetPositionSigma(position_sigma);
    output.SetRelativeVelocity(relative_velocity);
    output.SetRelativeVelocitySigma(relative_velocity_sigma);
    output.SetObstacleBBox3D(box3);
    output.SetMotionStatus(motion_status_remap_table_const_[status_ & 0x07]);
    output.SetCutInCutOut(cut);
    output.SetAcceleration(acceleration);
    output.SetAccelerationSigma(acceleration_sigma);
    output.SetImageBBox2D(box2);
}

void HorizonMatrix2Obstacle::ConvertToHoloObstacleWithTransform(holo::obstacle::ObstacleVisionT<float32_t>& output,
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

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo
