/**
 * @file bosch_mpc_obstacle.cpp
 * @brief This file defines functions of bosch mpc obstacle.
 * @author
 * @date 2019-12-3
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/mpc2/structure/mpc2_obstacle.h>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
const float32_t      BoschMpcObstacle::kobj_width_min_             = 0.1f;
const float32_t      BoschMpcObstacle::kobj_length_                = 0.1f;
const float32_t      BoschMpcObstacle::kobj_height_                = 0.1f;
const float32_t      BoschMpcObstacle::kobj_confidence_min_        = 0.3f;
// clang-format off
const Classification BoschMpcObstacle::kobj_class_remap_table_[16] = {
    Classification(Classification::MainType::UNKNOWN,    Classification::SubType::UNKNOWN),           //! 0 "unbekannt" UNKNOWN
    Classification(Classification::MainType::UNKNOWN,    Classification::SubType::UNKNOWN_MOVABLE),   //! 1 "ueberfahrbar" UNKNOWN
    Classification(Classification::MainType::UNKNOWN,    Classification::SubType::UNKNOWN_UNMOVABLE), //! 2 "unterfahrbar" UNKNOWN
    Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN),        //! 3 "Fussgaenger" PEDESTRIAN
    Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN),        //! 4 "Fussgaengergruppe" PEDESTRIAN
    Classification(Classification::MainType::BIKE,       Classification::SubType::BICYCLE),           //! 5 "Fahrrad"           BICYCLE
    Classification(Classification::MainType::BIKE,       Classification::SubType::MOTOBIKE),          //! 6 "Motorrad" MOTORBIKE
    Classification(Classification::MainType::VEHICLE,    Classification::SubType::CAR),               //! 7 "PKW"               CAR
    Classification(Classification::MainType::VEHICLE,    Classification::SubType::VAN),               //! 8 "Van"               UNKNOWN
    Classification(Classification::MainType::VEHICLE,    Classification::SubType::TRUCK),             //! 9 "LKW"               TRUCK
    Classification(Classification::MainType::UNKNOWN,    Classification::SubType::UNKNOWN),           //! 10 "Randbebauung" UNKNOWN
    Classification(Classification::MainType::ANIMAL,     Classification::SubType::UNKNOWN),            //! 11 "Tier" UNKNOWN
    Classification(Classification::MainType::UNKNOWN,    Classification::SubType::UNKNOWN),           //! 12 "Retroreflektor"  UNKNOWN
    Classification(Classification::MainType::UNKNOWN,    Classification::SubType::UNKNOWN),           //!                       UNKNOWN
    Classification(Classification::MainType::UNKNOWN,    Classification::SubType::UNKNOWN),           //!                       UNKNOWN
    Classification(Classification::MainType::UNKNOWN,    Classification::SubType::UNKNOWN),           //! 15 "Init" UNKNOWN
};
// clang-format on
void BoschMpcObstacle::ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const
{
    float32_t                angle_center     = (angle_edge_left_ + angle_edge_right_) / 2.0f;
    float32_t                width            = static_cast<float32_t>(long_dist_ * std::fabs(tan(angle_edge_right_) - tan(angle_edge_left_)));
    float32_t                lateral_distance = static_cast<float32_t>(long_dist_ * tan(angle_center));
    holo::geometry::Point3f  position(long_dist_, lateral_distance, 0.0f);
    holo::geometry::Point3f  position_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f relative_velocity(long_velocity_, 0.0f, 0.0f);
    holo::numerics::Vector3f relative_velocity_sigma(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration(0.0f, 0.0f, 0.0f);
    holo::numerics::Vector3f acceleration_sigma(0.0f, 0.0f, 0.0f);
    holo::geometry::Point2f  position2f(long_dist_, lateral_distance);
    width = std::max(width,  kobj_width_min_);
    holo::geometry::Box2f    box2(position2f, width, kobj_length_, 0.0f);
    holo::geometry::Rot3f    rot3;
    holo::geometry::Point3f  point3(long_dist_ - kobj_length_ * 0.5f, lateral_distance - width * 0.5f, -kobj_height_ * 0.5f);
    holo::geometry::Pose3f   pose3(rot3, point3);
    holo::geometry::Box3f    box3(width, kobj_height_, kobj_length_, pose3);

    output.SetTimestamp(timestamp_);
    output.SetObstacleId(id_);
    output.SetClassification(kobj_class_remap_table_[classification_]);
    output.SetObstacleExistScore(confidence_);
    output.SetPosition(position);
    output.SetPositionSigma(position_sigma);
    output.SetRelativeVelocity(relative_velocity);
    output.SetRelativeVelocitySigma(relative_velocity_sigma);
    output.SetObstacleBBox3D(box3);
    output.SetMotionStatus(obstacle::MotionStatus::UNKNOWN);
    output.SetCutInCutOut(obstacle::CutInCutOut::UNKNOWN);
    output.SetAcceleration(acceleration);
    output.SetAccelerationSigma(acceleration_sigma);
    output.SetImageBBox2D(box2);
}

void BoschMpcObstacle::ConvertToHoloObstacleWithTransform(holo::obstacle::ObstacleVisionT<float32_t>& output,
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

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
