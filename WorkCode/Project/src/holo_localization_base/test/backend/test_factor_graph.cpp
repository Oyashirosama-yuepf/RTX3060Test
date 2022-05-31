/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file test_factor_graph.cpp
 * @brief the unit test for factor graph.
 * @author lichao@holomatic.com
 * @date Dec 10, 2019
 */

#include <gtest/gtest.h>
#include <holo/localization/backend/factor_graph.h>

using PriorPoseFactor               = holo::localization::PriorPoseFactor;
using PriorVelocityFactor           = holo::localization::PriorVelocityFactor;
using PriorImuBiasFactor            = holo::localization::PriorImuBiasFactor;
using GnssFactor                    = holo::localization::GnssFactor;
using ImuFactor                     = holo::localization::ImuFactor;
using ImuBiasFactor                 = holo::localization::ImuBiasFactor;
using RelativePoseFactor            = holo::localization::RelativePoseFactor;
using RelativeVelocityFactor        = holo::localization::RelativeVelocityFactor;
using LaneFactor                    = holo::localization::LaneFactor;
using SignFactor                    = holo::localization::SignFactor;
using ProjectionFactor              = holo::localization::ProjectionFactor;
using VelocityFactor                = holo::localization::VelocityFactor;
using WheelSpeedFactor              = holo::localization::WheelSpeedFactor;
using PriorVector3Factor            = holo::localization::PriorVector3Factor;
using PriorRot3Factor               = holo::localization::PriorRot3Factor;
using CameraImuExtrinsicCalibFactor = holo::localization::CameraImuExtrinsicCalibFactor;
using ProjectedLineFactor           = holo::localization::ProjectedLineFactor;
using ImuBodyExtrinsicCalibFactor   = holo::localization::ImuBodyExtrinsicCalibFactor;
using GnssPositionVelocityFactor    = holo::localization::GnssPositionVelocityFactor;
using PriorRPYFactor                = holo::localization::PriorRPYFactor;
using Position3Value                = holo::localization::Position3Value;
using Vector3Value                  = holo::localization::Vector3Value;
using Rot3Value                     = holo::localization::Rot3Value;
using FactorGraph                   = holo::localization::FactorGraph;
using FactorType                    = holo::localization::FactorType;
using Symbol                        = holo::localization::Symbol;
using ValueType                     = holo::localization::ValueType;
using Pose3Type                     = holo::localization::Pose3Type;
using Matrix6Type                   = holo::localization::Matrix6Type;
using Scalar                        = holo::localization::Scalar;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateValueTypeTest, NormalCase)
{
    ValueType value_type = ValueType::POSITION3;

    ASSERT_TRUE(value_type != ValueType::POSE3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreatePriorPoseFactorByDefaultTest, NormalCase)
{
    PriorPoseFactor temp;  /// to test default copy constructor
    PriorPoseFactor prior_pose_factor(temp);
    prior_pose_factor = temp;  /// to test default operator=

    ASSERT_TRUE(prior_pose_factor.arity == 1u);
    ASSERT_TRUE(prior_pose_factor.type == FactorType::PRIOR_POSE);
    ASSERT_TRUE(prior_pose_factor.symbol.value_type == ValueType::UNKNOWN);
    ASSERT_TRUE(prior_pose_factor.symbol.index == 0u);
    ASSERT_TRUE(prior_pose_factor.measurement == Pose3Type());
    ASSERT_TRUE(prior_pose_factor.covariance_matrix == Matrix6Type());
    ASSERT_TRUE(prior_pose_factor.error == Scalar(0.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreatePriorVelocityFactorByDefaultTest, NormalCase)
{
    PriorVelocityFactor temp;  /// to test default copy constructor
    PriorVelocityFactor prior_vel_factor(temp);
    prior_vel_factor = temp;  /// to test default operator=

    ASSERT_TRUE(prior_vel_factor.arity == 1u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreatePriorImuBiasFactorByDefaultTest, NormalCase)
{
    PriorImuBiasFactor temp;  /// to test default copy constructor
    PriorImuBiasFactor prior_bias_factor(temp);
    prior_bias_factor = temp;  /// to test default operator=

    ASSERT_TRUE(prior_bias_factor.arity == 1u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreatePriorVector3FactorByDefaultTest, NormalCase)
{
    PriorVector3Factor temp;  /// to test default copy constructor
    PriorVector3Factor prior_vector3_factor(temp);
    prior_vector3_factor = temp;  /// to test default operator=

    ASSERT_EQ(prior_vector3_factor.arity, 1u);
    ASSERT_EQ(prior_vector3_factor.type, FactorType::PRIOR_VECTOR3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreatePriorRot3FactorByDefaultTest, NormalCase)
{
    PriorRot3Factor temp;  /// to test default copy constructor
    PriorRot3Factor prior_rot3_factor(temp);
    prior_rot3_factor = temp;  /// to test default operator=

    ASSERT_EQ(prior_rot3_factor.arity, 1u);
    ASSERT_EQ(prior_rot3_factor.type, FactorType::PRIOR_ROT3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateGnssFactorByDefaultTest, NormalCase)
{
    GnssFactor temp;  /// to test default copy constructor
    GnssFactor gnss_factor(temp);
    gnss_factor = temp;  /// to test default operator=

    ASSERT_TRUE(gnss_factor.arity == 1u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateImuFactorByDefaultTest, NormalCase)
{
    ImuFactor temp;  /// to test default copy constructor
    ImuFactor imu_factor(temp);
    imu_factor = temp;  /// to test default operator=

    ASSERT_TRUE(imu_factor.arity == 2u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateImuBiasFactorByDefaultTest, NormalCase)
{
    ImuBiasFactor temp;  /// to test default copy constructor
    ImuBiasFactor imu_bias_factor(temp);
    imu_bias_factor = temp;  /// to test default operator=

    ASSERT_TRUE(imu_bias_factor.arity == 2u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateRelativePoseFactorByDefaultTest, NormalCase)
{
    RelativePoseFactor temp;  /// to test default copy constructor
    RelativePoseFactor rel_pose_factor(temp);
    rel_pose_factor = temp;  /// to test default operator=

    ASSERT_TRUE(rel_pose_factor.arity == 2u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateRelativeVelocityFactorByDefaultTest, NormalCase)
{
    RelativeVelocityFactor temp;  /// to test default copy constructor
    RelativeVelocityFactor rel_vel_factor(temp);
    rel_vel_factor = temp;  /// to test default operator=

    ASSERT_TRUE(rel_vel_factor.arity == 2u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateLaneFactorByDefaultTest, NormalCase)
{
    LaneFactor temp(std::move(LaneFactor()));  /// to test default copy constructor and right value constructor
    LaneFactor lane_factor(temp);
    lane_factor = temp;  /// to test default operator=

    ASSERT_TRUE(lane_factor.arity == 1u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateSignFactorByDefaultTest, NormalCase)
{
    SignFactor temp;  /// to test default copy constructor
    SignFactor sign_factor(temp);
    sign_factor = temp;  /// to test default operator=

    ASSERT_TRUE(sign_factor.arity == 1u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateProjectionFactorByDefaultTest, NormalCase)
{
    ProjectionFactor temp;  /// to test default copy constructor
    ProjectionFactor prj_factor(temp);
    prj_factor = temp;  /// to test default operator=

    ASSERT_TRUE(prj_factor.arity == 2u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateVelocityFactorByDefaultTest, NormalCase)
{
    VelocityFactor temp;  /// to test default copy constructor
    VelocityFactor vel_factor(temp);
    vel_factor = temp;  /// to test default operator=

    ASSERT_TRUE(vel_factor.arity == 2u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateWheelSpeedFactorByDefaultTest, NormalCase)
{
    WheelSpeedFactor temp;  /// to test default copy constructor
    WheelSpeedFactor wheel_speed_factor(temp);
    wheel_speed_factor = temp;  /// to test default operator=

    ASSERT_TRUE(wheel_speed_factor.arity == 2u);
    ASSERT_EQ(wheel_speed_factor.type, FactorType::WHEEL_SPEED);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateProjectedLineFactorByDefault, NormalCase)
{
    ProjectedLineFactor temp;  /// to test default copy constructor
    ProjectedLineFactor projected_line_factor(temp);
    projected_line_factor = temp;  /// to test default operator=

    ASSERT_TRUE(projected_line_factor.arity == 1u);
    ASSERT_EQ(projected_line_factor.type, FactorType::PROJECTION_LINE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateProjectedLineFactorMeasurement, NormalCase)
{
    ProjectedLineFactor::Measurement temp;
    ProjectedLineFactor::Measurement measurement(temp);
    measurement = temp;  /// to test default operator=

    ASSERT_TRUE(temp.bTc.IsEqual(measurement.bTc));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreatePosition3ValueByDefaultTest, NormalCase)
{
    Position3Value temp;  /// to test default copy constructor
    Position3Value position_value(temp);
    position_value = temp;  /// to test default operator=

    ASSERT_TRUE(position_value.timestamp == holo::Timestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateFactorGraphByDefaultTest, NormalCase)
{
    FactorGraph temp;  /// to test default copy constructor
    FactorGraph factor_graph(temp);
    factor_graph = temp;  /// to test default operator=

    ASSERT_TRUE(!factor_graph.prior_pose_factors);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateVector3ValueByDefaultTest, NormalCase)
{
    Vector3Value temp;  /// to test default copy constructor
    Vector3Value vector3_value(temp);
    vector3_value = temp;  /// to test default operator=

    ASSERT_EQ(vector3_value.state, holo::localization::Vector3Type());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateRot3ValueByDefaultTest, NormalCase)
{
    Rot3Value temp;  /// to test default copy constructor
    Rot3Value rot3_value(temp);
    rot3_value = temp;  /// to test default operator=

    ASSERT_TRUE(rot3_value.state.IsEqual(holo::localization::Rot3Type()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateCameraImuExtrinsicCalibFactorByDefaultTest, NormalCase)
{
    CameraImuExtrinsicCalibFactor temp;  /// to test default copy constructor
    CameraImuExtrinsicCalibFactor camera_imu_extrinsic_calib_factor(temp);
    camera_imu_extrinsic_calib_factor = temp;  /// to test default operator=

    ASSERT_EQ(camera_imu_extrinsic_calib_factor.arity, 4u);
    ASSERT_EQ(camera_imu_extrinsic_calib_factor.type, FactorType::CAMERA_IMU_EXTRINSIC);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateImuBodyExtrinsicCalibFactorByDefaultTest, NormalCase)
{
    ImuBodyExtrinsicCalibFactor temp;  /// to test default copy constructor
    ImuBodyExtrinsicCalibFactor imu_body_extrinsic_calib_factor(temp);
    imu_body_extrinsic_calib_factor = temp;  /// to test default operator=

    ASSERT_EQ(imu_body_extrinsic_calib_factor.arity, 3u);
    ASSERT_EQ(imu_body_extrinsic_calib_factor.type, FactorType::IMU_BODY_EXTRINSIC);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreateGnssPositionVelocityFactorByDefaultTest, NormalCase)
{
    GnssPositionVelocityFactor temp;  /// to test default copy constructor
    GnssPositionVelocityFactor factor(temp);
    factor = temp;  /// to test default operator=

    ASSERT_EQ(factor.arity, 2u);
    ASSERT_EQ(factor.type, FactorType::GNSS_POSITION_VELOCITY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CreatePriorRPYFactor, NormalCase)
{
    PriorRPYFactor temp;  /// to test default copy constructor
    PriorRPYFactor prior_rpy_factor(temp);
    prior_rpy_factor = temp;  /// to test default operator=

    ASSERT_EQ(prior_rpy_factor.arity, 1u);
    ASSERT_EQ(prior_rpy_factor.type, FactorType::PRIOR_RPY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
