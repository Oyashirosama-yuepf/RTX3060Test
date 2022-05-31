/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_navstate.h
 * @brief test functions for navstate
 * @author lichao@holomatic.com
 * @date Oct 08, 2019
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(NavstateTypeConstructorDefaultTest, NormalCase)
{
    const NavstateType navstate;

    ASSERT_TRUE(NavstateType::Status::ALLGOOD == navstate.GetStatus());
    ASSERT_TRUE(NavstateType::CoordinateType() == navstate.GetParentCoordinate());
    ASSERT_TRUE(NavstateType::CoordinateType() == navstate.GetChildCoordinate());
    ASSERT_TRUE(NavstateType::Pose3Type::Identity() == navstate.GetPose());
    ASSERT_TRUE(NavstateType::Vector3Type::Zero() == navstate.GetVelocity());
    ASSERT_TRUE(NavstateType::Matrix6Type::Identity() == navstate.GetPoseCovariance());
    ASSERT_TRUE(NavstateType::Matrix3Type::Identity() == navstate.GetVelocityCovariance());
    ASSERT_TRUE(NavstateType::Vector3Type::Zero() == navstate.GetAngularVelocity());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorFromPoseAndVelocityTest, NormalCase)
{
    const NavstateType::Pose3Type expected_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(36.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(1.0, 2.0, 3.0));
    const NavstateType::Vector3Type expected_velocity(6.0, 5.0, 4.0);
    const NavstateType              navstate(expected_pose, expected_velocity);

    ASSERT_TRUE(NavstateType::Status::ALLGOOD == navstate.GetStatus());
    ASSERT_TRUE(NavstateType::CoordinateType() == navstate.GetParentCoordinate());
    ASSERT_TRUE(NavstateType::CoordinateType() == navstate.GetChildCoordinate());
    ASSERT_TRUE(expected_pose == navstate.GetPose());
    ASSERT_TRUE(expected_velocity == navstate.GetVelocity());
    ASSERT_TRUE(NavstateType::Matrix6Type::Identity() == navstate.GetPoseCovariance());
    ASSERT_TRUE(NavstateType::Matrix3Type::Identity() == navstate.GetVelocityCovariance());
    ASSERT_TRUE(NavstateType::Vector3Type::Zero() == navstate.GetAngularVelocity());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OperatorAdditionTest, NormalCase)
{
    /* simulate a car driving on a circle path, the radius of circle is 10 meter */
    const NavstateType::Pose3Type lhs_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(90.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(10.0, 0.0, 0.0));
    const NavstateType::Vector3Type    lhs_velocity(0.0, 10.0, 0.0);
    const NavstateType::CoordinateType lhs_parent_coordinate = NavstateType::CoordinateType::WGS84;
    const NavstateType::CoordinateType lhs_child_coordinate  = NavstateType::CoordinateType::BODY;

    NavstateType lhs(lhs_pose, lhs_velocity);

    lhs.SetParentCoordinate(lhs_parent_coordinate);
    lhs.SetChildCoordinate(lhs_child_coordinate);

    const NavstateType::Pose3Type rhs_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(90.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(10.0, 10.0, 0.0));
    const NavstateType::Vector3Type    rhs_velocity(3.0, 0.0, 0.0);
    const NavstateType::CoordinateType rhs_parent_coordinate = NavstateType::CoordinateType::BODY;
    const NavstateType::CoordinateType rhs_child_coordinate  = NavstateType::CoordinateType::IMU_VEHICLE;

    NavstateType rhs(rhs_pose, rhs_velocity);

    rhs.SetParentCoordinate(rhs_parent_coordinate);
    rhs.SetChildCoordinate(rhs_child_coordinate);

    /* generate expected values */
    const NavstateType::Pose3Type expected_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(180.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(0.0, 10.0, 0.0));
    const NavstateType::Vector3Type expected_velocity(0.0, 13.0, 0.0);
    NavstateType                    expected(expected_pose, expected_velocity);

    expected.SetParentCoordinate(lhs_parent_coordinate);
    expected.SetChildCoordinate(rhs_child_coordinate);

    NavstateType actual = lhs + rhs;

    ASSERT_TRUE(expected_pose == actual.GetPose());
    ASSERT_TRUE(expected_velocity.IsApprox(actual.GetVelocity(), tolerance));
    ASSERT_TRUE(expected.GetParentCoordinate() == actual.GetParentCoordinate());
    ASSERT_TRUE(expected.GetChildCoordinate() == actual.GetChildCoordinate());

    /* @todo (lichao@holomatic.com) covariane matrix should be propagated as well */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OperatorAdditionTest, AbnormalCase)
{
    /* simulate a car driving on a circle path, the radius of circle is 10 meter */
    const NavstateType::Pose3Type lhs_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(90.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(10.0, 0.0, 0.0));
    const NavstateType::Vector3Type    lhs_velocity(0.0, 10.0, 0.0);
    const NavstateType::CoordinateType lhs_parent_coordinate = NavstateType::CoordinateType::WGS84;
    const NavstateType::CoordinateType lhs_child_coordinate  = NavstateType::CoordinateType::BODY;

    NavstateType lhs(lhs_pose, lhs_velocity);

    lhs.SetParentCoordinate(lhs_parent_coordinate);
    lhs.SetChildCoordinate(lhs_child_coordinate);

    const NavstateType::Pose3Type rhs_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(90.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(10.0, 10.0, 0.0));
    const NavstateType::Vector3Type    rhs_velocity(3.0, 0.0, 0.0);
    const NavstateType::CoordinateType rhs_parent_coordinate = NavstateType::CoordinateType::UNKNOWN;
    const NavstateType::CoordinateType rhs_child_coordinate  = NavstateType::CoordinateType::IMU_VEHICLE;

    NavstateType rhs(rhs_pose, rhs_velocity);

    rhs.SetParentCoordinate(rhs_parent_coordinate);
    rhs.SetChildCoordinate(rhs_child_coordinate);

    /* generate expected values */
    NavstateType expected(lhs_pose, lhs_velocity);

    expected.SetParentCoordinate(lhs_parent_coordinate);
    expected.SetChildCoordinate(lhs_child_coordinate);

    NavstateType actual = lhs + rhs;

    ASSERT_TRUE(expected.GetPose() == actual.GetPose());
    ASSERT_TRUE(expected.GetVelocity() == actual.GetVelocity());
    ASSERT_TRUE(expected.GetParentCoordinate() == actual.GetParentCoordinate());
    ASSERT_TRUE(expected.GetChildCoordinate() == actual.GetChildCoordinate());

    /* @todo (lichao@holomatic.com) covariane matrix should be propagated as well */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OepratorEqualTest, NormalCase)
{
    const NavstateType::Pose3Type pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(36.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(1.0, 2.0, 3.0));
    const NavstateType::Vector3Type velocity(6.0, 5.0, 4.0);
    const NavstateType              other(pose, velocity);

    /* construct navstate by copy constructor */
    NavstateType navstate(other);

    ASSERT_TRUE(navstate == other);
    navstate.SetStatus(NavstateType::Status::ANGULARVELOCITYINACTIVE);
    ASSERT_FALSE(navstate == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OperatorAdditionAssignmentTest, NormalCase)
{
    /* simulate a car driving on a circle path, the radius of circle is 10 meter */
    const NavstateType::Pose3Type lhs_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(90.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(10.0, 0.0, 0.0));
    const NavstateType::Vector3Type    lhs_velocity(0.0, 10.0, 0.0);
    const NavstateType::CoordinateType lhs_parent_coordinate = NavstateType::CoordinateType::WGS84;
    NavstateType::CoordinateType       lhs_child_coordinate  = NavstateType::CoordinateType::BODY;

    NavstateType lhs(lhs_pose, lhs_velocity);

    lhs.SetParentCoordinate(lhs_parent_coordinate);
    lhs.SetChildCoordinate(lhs_child_coordinate);

    const NavstateType::Pose3Type rhs_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(90.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(10.0, 10.0, 0.0));
    const NavstateType::Vector3Type    rhs_velocity(3.0, 0.0, 0.0);
    const NavstateType::CoordinateType rhs_parent_coordinate = NavstateType::CoordinateType::BODY;
    const NavstateType::CoordinateType rhs_child_coordinate  = NavstateType::CoordinateType::IMU_VEHICLE;

    NavstateType rhs(rhs_pose, rhs_velocity);

    rhs.SetParentCoordinate(rhs_parent_coordinate);
    rhs.SetChildCoordinate(rhs_child_coordinate);

    /* generate expected values */
    const NavstateType::Pose3Type expected_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(180.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(0.0, 10.0, 0.0));
    const NavstateType::Vector3Type expected_velocity(0.0, 13.0, 0.0);
    NavstateType                    expected(expected_pose, expected_velocity);

    expected.SetParentCoordinate(lhs_parent_coordinate);
    expected.SetChildCoordinate(rhs_child_coordinate);

    lhs += rhs;

    ASSERT_TRUE(expected_pose == lhs.GetPose());
    ASSERT_TRUE(expected_velocity.IsApprox(lhs.GetVelocity(), tolerance));
    ASSERT_TRUE(expected.GetParentCoordinate() == lhs.GetParentCoordinate());
    ASSERT_TRUE(expected.GetChildCoordinate() == lhs.GetChildCoordinate());

    /* @todo (lichao@holomatic.com) covariane matrix should be propagated as well */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OperatorAdditionAssignmentTest, AbnormalCase)
{
    /* simulate a car driving on a circle path, the radius of circle is 10 meter */
    const NavstateType::Pose3Type lhs_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(90.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(10.0, 0.0, 0.0));
    const NavstateType::Vector3Type    lhs_velocity(0.0, 10.0, 0.0);
    const NavstateType::CoordinateType lhs_parent_coordinate = NavstateType::CoordinateType::WGS84;
    NavstateType::CoordinateType       lhs_child_coordinate  = NavstateType::CoordinateType::BODY;

    NavstateType lhs(lhs_pose, lhs_velocity);

    lhs.SetParentCoordinate(lhs_parent_coordinate);
    lhs.SetChildCoordinate(lhs_child_coordinate);

    const NavstateType::Pose3Type rhs_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(90.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(10.0, 10.0, 0.0));
    const NavstateType::Vector3Type    rhs_velocity(3.0, 0.0, 0.0);
    const NavstateType::CoordinateType rhs_parent_coordinate = NavstateType::CoordinateType::UNKNOWN;
    const NavstateType::CoordinateType rhs_child_coordinate  = NavstateType::CoordinateType::IMU_VEHICLE;

    NavstateType rhs(rhs_pose, rhs_velocity);

    rhs.SetParentCoordinate(rhs_parent_coordinate);
    rhs.SetChildCoordinate(rhs_child_coordinate);

    /* generate expected values */
    NavstateType expected(lhs_pose, lhs_velocity);

    expected.SetParentCoordinate(lhs_parent_coordinate);
    expected.SetChildCoordinate(lhs_child_coordinate);

    lhs += rhs;

    ASSERT_TRUE(expected.GetPose() == lhs.GetPose());
    ASSERT_TRUE(expected.GetVelocity() == lhs.GetVelocity());
    ASSERT_TRUE(expected.GetParentCoordinate() == lhs.GetParentCoordinate());
    ASSERT_TRUE(expected.GetChildCoordinate() == lhs.GetChildCoordinate());

    /* @todo (lichao@holomatic.com) covariane matrix should be propagated as well */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetStatusTest, NormalCase)
{
    NavstateType navstate;

    /* generate expected value */
    const NavstateType::Status expected_status = NavstateType::Status::POSITIONINACTIVE;
    navstate.SetStatus(expected_status);

    ASSERT_TRUE(expected_status == navstate.GetStatus());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetParentCoordinateTest, NormalCase)
{
    NavstateType navstate;

    /* generate expected parent coordinate */
    const NavstateType::CoordinateType expected_parent_coordinate = NavstateType::CoordinateType::WGS84;
    navstate.SetParentCoordinate(expected_parent_coordinate);

    ASSERT_TRUE(expected_parent_coordinate == navstate.GetParentCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetChildCoordinateTest, NormalCase)
{
    NavstateType navstate;

    /* generate expected child coordinate */
    const NavstateType::CoordinateType expected_child_coordinate = NavstateType::CoordinateType::BODY;
    navstate.SetChildCoordinate(expected_child_coordinate);

    ASSERT_TRUE(expected_child_coordinate == navstate.GetChildCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetPoseTest, NormalCase)
{
    NavstateType navstate;

    /* generate expected value */
    const NavstateType::Pose3Type expected_pose(
        holo::geometry::Rot3T<NavstateType::ScalarType>::Rz(holo::geometry::Radian(36.0)),
        holo::geometry::Point3T<NavstateType::ScalarType>(1.0, 2.0, 3.0));
    navstate.SetPose(expected_pose);

    ASSERT_TRUE(expected_pose == navstate.GetPose());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetVelocityTest, NormalCase)
{
    NavstateType navstate;

    /* generate expected value */
    const NavstateType::Vector3Type expected_velocity(6.0, 5.0, 4.0);
    navstate.SetVelocity(expected_velocity);

    ASSERT_TRUE(expected_velocity == navstate.GetVelocity());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetPoseCovarianceTest, NormalCase)
{
    NavstateType navstate;

    /* generate expected value */
    const NavstateType::Matrix6Type expected_pose_covariance =
        NavstateType::ScalarType(0.12) * NavstateType::Matrix6Type::Identity();
    navstate.SetPoseCovariance(expected_pose_covariance);

    ASSERT_TRUE(expected_pose_covariance == navstate.GetPoseCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetVelocityCovarianceTest, NormalCase)
{
    NavstateType navstate;

    /* generate expected value */
    const NavstateType::Matrix3Type expected_velocity_covariance =
        NavstateType::ScalarType(0.31) * NavstateType::Matrix3Type::Identity();
    navstate.SetVelocityCovariance(expected_velocity_covariance);

    ASSERT_TRUE(expected_velocity_covariance == navstate.GetVelocityCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetAngularVelocityTest, NormalCase)
{
    NavstateType navstate;

    /* generate expected value */
    const NavstateType::Vector3Type expected_angular_velocity(6.0, 5.0, 4.0);
    navstate.SetAngularVelocity(expected_angular_velocity);

    ASSERT_TRUE(expected_angular_velocity == navstate.GetAngularVelocity());
}
