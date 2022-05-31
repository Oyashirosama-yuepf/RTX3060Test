/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file conti_radar_obsatcle.c
 * @brief A class to describe continental ars408/srr308 radar obstacles
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/11
 */

#include <holo/log/hololog.h>
#include <holo/sensors/radar/ars408/structure/ars408_obstacle.h>

namespace holo
{
namespace sensors
{
namespace conti_radar
{
const Classification ContiRadarObstacle::kobj_class_remap_table_[8] = {
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),       /* POINT      */
    Classification(Classification::MainType::VEHICLE, Classification::SubType::CAR),           /* CAR        */
    Classification(Classification::MainType::VEHICLE, Classification::SubType::TRUCK),         /* TRUCK      */
    Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN), /* PEDESTRIAN */
    Classification(Classification::MainType::BIKE, Classification::SubType::MOTOBIKE),         /* MOTORCYCLE */
    Classification(Classification::MainType::BIKE, Classification::SubType::BICYCLE),          /* BICYCLE    */
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),       /* WIDE?      */
    Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN),       /* RESERVED   */
};

const float32_t ContiRadarObstacle::kobj_confidece_remap_table_[8] = {0.0f, 0.25f, 0.50f, 0.75f, 0.90f, 0.99f, 0.999f, 1.00f};

const MotionStatus ContiRadarObstacle::kobj_motion_status_remap_table_[8]{
    MotionStatus::MOVING,     /* moving */
    MotionStatus::STATIONARY, /* stationary */
    MotionStatus::ONCOMING,   /* oncoming */
    MotionStatus::STATIONARY, /* stationary candidate */
    MotionStatus::UNKNOWN,    /* unknown */
    MotionStatus::CROSSING,   /* crossing stationary */
    MotionStatus::CROSSING,   /* crossing moving */
    MotionStatus::STOPPED,    /* stopped */
};

const float32_t ContiRadarObstacle::kobj_dvasigma_remap_table_[32] = {
    0.005f, /* 0x0 */
    0.006f, /* 0x1 */
    0.008f, /* 0x2 */
    0.011f, /* 0x3 */
    0.014f, /* 0x4 */
    0.018f, /* 0x5 */
    0.023f, /* 0x6 */
    0.029f, /* 0x7 */
    0.038f, /* 0x8 */
    0.049f, /* 0x9 */
    0.063f, /* 0xA */
    0.081f, /* 0xB */
    0.105f, /* 0xC */
    0.135f, /* 0xD */
    0.174f, /* 0xE */
    0.224f, /* 0xF */
    0.288f, /* 0x10 */
    0.371f, /* 0x11 */
    0.478f, /* 0x12 */
    0.616f, /* 0x13 */
    0.794f, /* 0x14 */
    1.023f, /* 0x15 */
    1.317f, /* 0x16 */
    1.697f, /* 0x17 */
    2.187f, /* 0x18 */
    2.817f, /* 0x19 */
    3.630f, /* 0x1A */
    4.676f, /* 0x1B */
    6.025f, /* 0x1C */
    7.762f, /* 0x1D */
    10.00f, /* 0x1E */
    100.0f  /* 0x1F */
};

const float32_t ContiRadarObstacle::kobj_angsigma_remap_table_[32] = {
    0.005f,   /* 0x0 */
    0.007f,   /* 0x1 */
    0.010f,   /* 0x2 */
    0.014f,   /* 0x3 */
    0.020f,   /* 0x4 */
    0.029f,   /* 0x5 */
    0.041f,   /* 0x6 */
    0.058f,   /* 0x7 */
    0.082f,   /* 0x8 */
    0.116f,   /* 0x9 */
    0.165f,   /* 0xA */
    0.234f,   /* 0xB */
    0.332f,   /* 0xC */
    0.471f,   /* 0xD */
    0.669f,   /* 0xE */
    0.949f,   /* 0xF */
    1.346f,   /* 0x10 */
    1.909f,   /* 0x11 */
    2.709f,   /* 0x12 */
    3.843f,   /* 0x13 */
    5.451f,   /* 0x14 */
    7.734f,   /* 0x15 */
    10.971f,  /* 0x16 */
    15.565f,  /* 0x17 */
    22.081f,  /* 0x18 */
    31.325f,  /* 0x19 */
    44.439f,  /* 0x1A */
    63.044f,  /* 0x1B */
    89.437f,  /* 0x1C */
    126.881f, /* 0x1D */
    180.000f, /* 0x1E */
    180.000f, /* 0x1F */
};

void ContiRadarObstacle::ConvertToHoloObstacle(holo::obstacle::ObstacleRadarT<float32_t>& output) const
{
    holo::geometry::Point3f position(dist_long_, dist_lat_, 0.0f);
    holo::geometry::Point3f position_sigma(kobj_dvasigma_remap_table_[dist_long_rms_],
                                           kobj_dvasigma_remap_table_[dist_lat_rms_], 0.0f);
    holo::numerics::Vector3f relative_velocity(vrel_long_, vrel_lat_, 0.0f);
    holo::numerics::Vector3f relative_velocity_sigma(kobj_dvasigma_remap_table_[vrel_long_rms_],
                                                     kobj_dvasigma_remap_table_[vrel_lat_rms_], 0.0f);
    holo::numerics::Vector3f acceleration(arel_long_, arel_lat_, 0.0f);
    holo::numerics::Vector3f acceleration_sigma(kobj_dvasigma_remap_table_[arel_long_rms_],
                                                kobj_dvasigma_remap_table_[arel_lat_rms_], 0.0f);
    holo::numerics::Vector3f shape(std::max<float32_t>(width_, 0.5f), 0.5f, std::max<float32_t>(length_, 0.5f));
    output.SetTimestamp(timestamp_);
    output.SetObstacleId(uint32_t(id_));
    output.SetClassification(kobj_class_remap_table_[classification_]);
    output.SetObstacleExistScore(kobj_confidece_remap_table_[prob_of_exist_]);
    output.SetPosition(position);
    output.SetRelativeVelocity(relative_velocity);
    output.SetAcceleration(acceleration);
    output.SetPositionSigma(position_sigma);
    output.SetRelativeVelocitySigma(relative_velocity_sigma);
    output.SetAccelerationSigma(acceleration_sigma);
    output.SetMotionStatus(kobj_motion_status_remap_table_[dynprop_]);
    output.SetObstacleShape(shape);
    output.SetObstacleRCS(rcs_);
}

void ContiRadarObstacle::ConvertToHoloObstacleWithTransform(const holo::common::Extrinsicf&            extrinsic,
                                                            holo::obstacle::ObstacleRadarT<float32_t>& output) const
{
    ConvertToHoloObstacle(output);

    holo::geometry::Point3f  position           = extrinsic.GetPose().TransformFrom(output.GetPosition());
    holo::geometry::Point3f  position_sigma     = extrinsic.GetPose().TransformFrom(output.GetPositionSigma());
    holo::numerics::Vector3f relative_velocity  = extrinsic.GetPose().TransformFrom(output.GetRelativeVelocity());
    holo::numerics::Vector3f relative_vel_sigma = extrinsic.GetPose().TransformFrom(output.GetRelativeVelocitySigma());
    holo::numerics::Vector3f acceleration       = extrinsic.GetPose().TransformFrom(output.GetAcceleration());
    holo::numerics::Vector3f acceleration_sigma = extrinsic.GetPose().TransformFrom(output.GetAccelerationSigma());

    output.SetCoordinate(extrinsic.GetParentCoordinate());
    output.SetPosition(position);
    output.SetPositionSigma(position_sigma);
    output.SetRelativeVelocity(relative_velocity);
    output.SetRelativeVelocitySigma(relative_vel_sigma);
    output.SetAcceleration(acceleration);
    output.SetAccelerationSigma(acceleration_sigma);
}

}  // namespace conti_radar
}  // namespace sensors
}  // namespace holo
