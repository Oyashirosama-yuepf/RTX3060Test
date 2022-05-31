/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_advanced_navstate.h
 * @brief test functions for advanced navstate
 * @author lichao@holomatic.com
 * @date Oct 08, 2019
 */

#include <gtest/gtest.h>
#include <holo/localization/common/navstate.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorDefaultTest, NormalCase)
{
    const AdvancedNavstateType navstate;

    ASSERT_TRUE(AdvancedNavstateType::Status::ALLGOOD == navstate.GetStatus());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetParentCoordinate());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetChildCoordinate());
    ASSERT_TRUE(AdvancedNavstateType::Pose3Type::Identity() == navstate.GetPose());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetVelocity());
    ASSERT_TRUE(AdvancedNavstateType::Matrix6Type::Identity() == navstate.GetPoseCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetVelocityCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocity());
    ASSERT_TRUE(AdvancedNavstateType::Source::NONE == navstate.GetSource());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocityBias());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetLinearAccelerationBias());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetAngularVelocityBiasCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetLinearAccelerationBiasCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CopyConstructorTest, NormalCase)
{
    const AdvancedNavstateType::Pose3Type expected_pose(
        holo::Rot3T<AdvancedNavstateType::ScalarType>::Rz(holo::geometry::Radian(36.0)),
        holo::Point3T<AdvancedNavstateType::ScalarType>(1.0, 2.0, 3.0));
    const AdvancedNavstateType::Vector3Type expected_velocity(6.0, 5.0, 4.0);
    const AdvancedNavstateType              other(expected_pose, expected_velocity);
    const AdvancedNavstateType              navstate(other);

    ASSERT_TRUE(AdvancedNavstateType::Status::ALLGOOD == navstate.GetStatus());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetParentCoordinate());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetChildCoordinate());
    ASSERT_TRUE(expected_pose == navstate.GetPose());
    ASSERT_TRUE(expected_velocity == navstate.GetVelocity());
    ASSERT_TRUE(AdvancedNavstateType::Matrix6Type::Identity() == navstate.GetPoseCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetVelocityCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocity());

    ASSERT_TRUE(AdvancedNavstateType::Source::NONE == navstate.GetSource());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocityBias());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetLinearAccelerationBias());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetAngularVelocityBiasCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetLinearAccelerationBiasCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CopyAssignmentOverloadingTest, NormalCase)
{
    const AdvancedNavstateType::Pose3Type expected_pose(
        holo::Rot3T<AdvancedNavstateType::ScalarType>::Rz(holo::geometry::Radian(36.0)),
        holo::Point3T<AdvancedNavstateType::ScalarType>(1.0, 2.0, 3.0));
    const AdvancedNavstateType::Vector3Type expected_velocity(6.0, 5.0, 4.0);
    const AdvancedNavstateType              other(expected_pose, expected_velocity);
    AdvancedNavstateType                    navstate;
    navstate = other;

    ASSERT_TRUE(AdvancedNavstateType::Status::ALLGOOD == navstate.GetStatus());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetParentCoordinate());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetChildCoordinate());
    ASSERT_TRUE(expected_pose == navstate.GetPose());
    ASSERT_TRUE(expected_velocity == navstate.GetVelocity());
    ASSERT_TRUE(AdvancedNavstateType::Matrix6Type::Identity() == navstate.GetPoseCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetVelocityCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocity());

    ASSERT_TRUE(AdvancedNavstateType::Source::NONE == navstate.GetSource());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocityBias());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetLinearAccelerationBias());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetAngularVelocityBiasCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetLinearAccelerationBiasCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorFromPoseAndVelocityTest, NormalCase)
{
    const AdvancedNavstateType::Pose3Type expected_pose(
        holo::Rot3T<AdvancedNavstateType::ScalarType>::Rz(holo::geometry::Radian(36.0)),
        holo::Point3T<AdvancedNavstateType::ScalarType>(1.0, 2.0, 3.0));
    const AdvancedNavstateType::Vector3Type expected_velocity(6.0, 5.0, 4.0);
    const AdvancedNavstateType              navstate(expected_pose, expected_velocity);

    ASSERT_TRUE(AdvancedNavstateType::Status::ALLGOOD == navstate.GetStatus());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetParentCoordinate());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetChildCoordinate());
    ASSERT_TRUE(expected_pose == navstate.GetPose());
    ASSERT_TRUE(expected_velocity == navstate.GetVelocity());
    ASSERT_TRUE(AdvancedNavstateType::Matrix6Type::Identity() == navstate.GetPoseCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetVelocityCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocity());

    ASSERT_TRUE(AdvancedNavstateType::Source::NONE == navstate.GetSource());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocityBias());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetLinearAccelerationBias());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetAngularVelocityBiasCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetLinearAccelerationBiasCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorFromNavstateTest, NormalCase)
{
    const AdvancedNavstateType::Pose3Type expected_pose(
        holo::Rot3T<AdvancedNavstateType::ScalarType>::Rz(holo::geometry::Radian(36.0)),
        holo::Point3T<AdvancedNavstateType::ScalarType>(1.0, 2.0, 3.0));
    const AdvancedNavstateType::Vector3Type expected_velocity(6.0, 5.0, 4.0);
    const AdvancedNavstateType::Base        navstate(expected_pose, expected_velocity);
    const AdvancedNavstateType              advanced_navstate(navstate);

    ASSERT_TRUE(AdvancedNavstateType::Status::ALLGOOD == advanced_navstate.GetStatus());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetParentCoordinate());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetChildCoordinate());
    ASSERT_TRUE(expected_pose == advanced_navstate.GetPose());
    ASSERT_TRUE(expected_velocity == advanced_navstate.GetVelocity());
    ASSERT_TRUE(AdvancedNavstateType::Matrix6Type::Identity() == advanced_navstate.GetPoseCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == advanced_navstate.GetVelocityCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == advanced_navstate.GetAngularVelocity());

    ASSERT_TRUE(AdvancedNavstateType::Source::NONE == advanced_navstate.GetSource());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == advanced_navstate.GetAngularVelocityBias());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == advanced_navstate.GetLinearAccelerationBias());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == advanced_navstate.GetAngularVelocityBiasCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() ==
                advanced_navstate.GetLinearAccelerationBiasCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorFromPoseVelocityAndImuBiasTest, NormalCase)
{
    const AdvancedNavstateType::Pose3Type expected_pose(
        holo::Rot3T<AdvancedNavstateType::ScalarType>::Rz(holo::geometry::Radian(36.0)),
        holo::Point3T<AdvancedNavstateType::ScalarType>(1.0, 2.0, 3.0));
    const AdvancedNavstateType::Vector3Type expected_velocity(6.0, 5.0, 4.0);
    const AdvancedNavstateType::Vector6Type expected_imu_bias(1.0, 0.1, 0.01, 0.01, 1.0, 0.1);
    const AdvancedNavstateType::Vector3Type expected_angular_velocity_bias(1.0, 0.1, 0.01);
    const AdvancedNavstateType::Vector3Type expected_linear_acceleration_bias(0.01, 1.0, 0.1);
    const AdvancedNavstateType              navstate(expected_pose, expected_velocity, expected_imu_bias);

    ASSERT_TRUE(AdvancedNavstateType::Status::ALLGOOD == navstate.GetStatus());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetParentCoordinate());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetChildCoordinate());
    ASSERT_TRUE(expected_pose == navstate.GetPose());
    ASSERT_TRUE(expected_velocity == navstate.GetVelocity());
    ASSERT_TRUE(AdvancedNavstateType::Matrix6Type::Identity() == navstate.GetPoseCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetVelocityCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocity());

    ASSERT_TRUE(AdvancedNavstateType::Source::NONE == navstate.GetSource());
    ASSERT_TRUE(expected_angular_velocity_bias == navstate.GetAngularVelocityBias());
    ASSERT_TRUE(expected_linear_acceleration_bias == navstate.GetLinearAccelerationBias());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetAngularVelocityBiasCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetLinearAccelerationBiasCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorFromPoseVelocityAngularVelocityBiasAndLinearAccelerationBiasTest, NormalCase)
{
    const AdvancedNavstateType::Pose3Type expected_pose(
        holo::Rot3T<AdvancedNavstateType::ScalarType>::Rz(holo::geometry::Radian(36.0)),
        holo::Point3T<AdvancedNavstateType::ScalarType>(1.0, 2.0, 3.0));
    const AdvancedNavstateType::Vector3Type expected_velocity(6.0, 5.0, 4.0);
    const AdvancedNavstateType::Vector3Type expected_angular_velocity_bias(1.0, 0.1, 0.01);
    const AdvancedNavstateType::Vector3Type expected_linear_acceleration_bias(0.01, 1.0, 0.1);
    const AdvancedNavstateType              navstate(expected_pose, expected_velocity, expected_angular_velocity_bias,
                                        expected_linear_acceleration_bias);

    ASSERT_TRUE(AdvancedNavstateType::Status::ALLGOOD == navstate.GetStatus());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetParentCoordinate());
    ASSERT_TRUE(AdvancedNavstateType::CoordinateType() == navstate.GetChildCoordinate());
    ASSERT_TRUE(expected_pose == navstate.GetPose());
    ASSERT_TRUE(expected_velocity == navstate.GetVelocity());
    ASSERT_TRUE(AdvancedNavstateType::Matrix6Type::Identity() == navstate.GetPoseCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetVelocityCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Vector3Type::Zero() == navstate.GetAngularVelocity());

    ASSERT_TRUE(AdvancedNavstateType::Source::NONE == navstate.GetSource());
    ASSERT_TRUE(expected_angular_velocity_bias == navstate.GetAngularVelocityBias());
    ASSERT_TRUE(expected_linear_acceleration_bias == navstate.GetLinearAccelerationBias());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetAngularVelocityBiasCovariance());
    ASSERT_TRUE(AdvancedNavstateType::Matrix3Type::Identity() == navstate.GetLinearAccelerationBiasCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetSourceTest, NormalCase)
{
    AdvancedNavstateType navstate;

    /* generate expected values */
    const AdvancedNavstateType::Source expected_source = AdvancedNavstateType::Source::GPS;
    navstate.SetSource(expected_source);

    ASSERT_TRUE(expected_source == navstate.GetSource());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetParentCoordinateTest, NormalCase)
{
    AdvancedNavstateType navstate;

    /* generate expected parent coordinate */
    const AdvancedNavstateType::CoordinateType expected_parent_coordinate = AdvancedNavstateType::CoordinateType::WGS84;
    navstate.SetParentCoordinate(expected_parent_coordinate);

    ASSERT_TRUE(expected_parent_coordinate == navstate.GetParentCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetChildCoordinateTest, NormalCase)
{
    AdvancedNavstateType navstate;

    /* generate expected child coordinate */
    const AdvancedNavstateType::CoordinateType expected_child_coordinate = AdvancedNavstateType::CoordinateType::BODY;
    navstate.SetChildCoordinate(expected_child_coordinate);

    ASSERT_TRUE(expected_child_coordinate == navstate.GetChildCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetAngularVelocityBiasTest, NormalCase)
{
    AdvancedNavstateType navstate;

    /* generate expected values */
    const AdvancedNavstateType::Vector3Type expected_angular_velocity_bias(1.0, 0.1, 0.01);
    navstate.SetAngularVelocityBias(expected_angular_velocity_bias);

    ASSERT_TRUE(expected_angular_velocity_bias == navstate.GetAngularVelocityBias());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetLinearAccelerationBiasTest, NormalCase)
{
    AdvancedNavstateType navstate;

    /* generate expected values */
    const AdvancedNavstateType::Vector3Type expected_linear_acceleration_bias(1.0, 0.1, 0.01);
    navstate.SetLinearAccelerationBias(expected_linear_acceleration_bias);

    ASSERT_TRUE(expected_linear_acceleration_bias == navstate.GetLinearAccelerationBias());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetAngularVelocityBiasCovarianceTest, NormalCase)
{
    AdvancedNavstateType navstate;

    /* generate expected values */
    const AdvancedNavstateType::Matrix3Type expected_angular_velocity_bias_covariance =
        AdvancedNavstateType::ScalarType(0.12) * AdvancedNavstateType::Matrix3Type::Identity();
    navstate.SetAngularVelocityBiasCovariance(expected_angular_velocity_bias_covariance);

    ASSERT_TRUE(expected_angular_velocity_bias_covariance == navstate.GetAngularVelocityBiasCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetLinearAccelerationBiasCovarianceTest, NormalCase)
{
    AdvancedNavstateType navstate;

    /* generate expected values */
    const AdvancedNavstateType::Matrix3Type expected_linear_acceleration_bias_covariance =
        AdvancedNavstateType::ScalarType(0.12) * AdvancedNavstateType::Matrix3Type::Identity();
    navstate.SetLinearAccelerationBiasCovariance(expected_linear_acceleration_bias_covariance);

    ASSERT_TRUE(expected_linear_acceleration_bias_covariance == navstate.GetLinearAccelerationBiasCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, NormalCase)
{
    AdvancedNavstateType navstate;

    ASSERT_NO_THROW(navstate.ToString());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Underlying, NormalCase)
{
    AdvancedNavstateType navstate;

    ASSERT_NO_THROW(navstate.GetSourceUnderlying());
    ASSERT_TRUE(navstate.GetSourceUnderlying() == 0u);
}
