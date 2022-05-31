/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for extrinsic class
 * @author lichao@holomatic.com
 * @date Sep 18, 2019
 */

#include <gtest/gtest.h>
#include <holo/common/extrinsic.h>

using Coordinate = holo::common::Coordinate;
using Extrinsicf = holo::common::Extrinsicf;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorDefaultTest, NormalInput)
{
    /* Create a Extrinsic by default constructor */
    const Extrinsicf extrinsic;

    /* Test default constructor */
    ASSERT_TRUE(Coordinate(Coordinate::UNKNOWN) == extrinsic.GetParentCoordinate());
    ASSERT_TRUE(Coordinate(Coordinate::UNKNOWN) == extrinsic.GetChildCoordinate());
    ASSERT_TRUE(Extrinsicf::Pose3Type() == extrinsic.GetPose());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, NormalInput)
{
    /* Generate expected values */
    const Coordinate    expected_parent_coord = Coordinate(Coordinate::IMU_MAIN); // COORD_IMU_MAIN
    const Coordinate    expected_child_coord  = Coordinate(Coordinate::BODY); // COORD_BODY
    const Extrinsicf::Pose3Type expected_pose;

    /* Create a Extrinsic by default constructor */
    const Extrinsicf extrinsic(expected_parent_coord, expected_child_coord, expected_pose);

    /* Test default constructor */
    ASSERT_TRUE(expected_parent_coord == extrinsic.GetParentCoordinate());
    ASSERT_TRUE(expected_child_coord == extrinsic.GetChildCoordinate());
    ASSERT_TRUE(Extrinsicf::Pose3Type() == extrinsic.GetPose());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////l
TEST(ConstructorbyCopyTest, NormalInput)
{
    /* Generate expected values */
    const Coordinate    expected_parent_coord = Coordinate(Coordinate::IMU_MAIN); // COORD_IMU_MAIN
    const Coordinate    expected_child_coord  = Coordinate(Coordinate::BODY); // COORD_BODY
    const Extrinsicf::Pose3Type expected_pose;

    /* Create a Extrinsic by default constructor */
    const Extrinsicf other(expected_parent_coord, expected_child_coord, expected_pose);

    /* Create a Extrinsic by copy constructor */
    const Extrinsicf extrinsic(other);

    /* Test default constructor */
    ASSERT_TRUE(other.GetParentCoordinate() == extrinsic.GetParentCoordinate());
    ASSERT_TRUE(other.GetChildCoordinate() == extrinsic.GetChildCoordinate());
    ASSERT_TRUE(other.GetPose() == extrinsic.GetPose());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////l
TEST(ConstructorbyMoveTest, NormalInput)
{
    /* Generate expected values */
    const Coordinate    expected_parent_coord = Coordinate(Coordinate::IMU_MAIN); // COORD_IMU_MAIN
    const Coordinate    expected_child_coord  = Coordinate(Coordinate::BODY); // COORD_BODY
    const Extrinsicf::Pose3Type expected_pose;

    /* Create a Extrinsic by default constructor */
    const Extrinsicf other(expected_parent_coord, expected_child_coord, expected_pose);

    /* Create a Extrinsic by move constructor */
    const Extrinsicf extrinsic = std::move(other);

    /* Test default constructor */
    ASSERT_TRUE(expected_parent_coord == extrinsic.GetParentCoordinate());
    ASSERT_TRUE(expected_child_coord == extrinsic.GetChildCoordinate());
    ASSERT_TRUE(expected_pose == extrinsic.GetPose());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////l
TEST(CopyAssignmentOperatorTest, NormalInput)
{
    /* Generate expected values */
    const Coordinate    expected_parent_coord = Coordinate(Coordinate::IMU_MAIN); // COORD_IMU_MAIN
    const Coordinate    expected_child_coord  = Coordinate(Coordinate::BODY); // COORD_BODY
    const Extrinsicf::Pose3Type expected_pose;

    /* Create a Extrinsic by default constructor */
    const Extrinsicf other(expected_parent_coord, expected_child_coord, expected_pose);

    /* Create a Extrinsic by copy assignment */
    Extrinsicf extrinsic;

    extrinsic = other;

    /* Test default constructor */
    ASSERT_TRUE(other.GetParentCoordinate() == extrinsic.GetParentCoordinate());
    ASSERT_TRUE(other.GetChildCoordinate() == extrinsic.GetChildCoordinate());
    ASSERT_TRUE(other.GetPose() == extrinsic.GetPose());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetParentCoordinateTest, NormalInput)
{
    /* Generate expected values */
    const Coordinate expected_parent_coord = Coordinate(Coordinate::IMU_MAIN); // COORD_IMU_MAIN

    /* Create a Extrinsic */
    Extrinsicf extrinsic;

    /* Test default constructor */
    extrinsic.SetParentCoordinate(expected_parent_coord);
    ASSERT_TRUE(expected_parent_coord == extrinsic.GetParentCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetChildCoordinateTest, NormalInput)
{
    /* Generate expected values */
    const Coordinate expected_child_coord = Coordinate(Coordinate::BODY); // COORD_BODY

    /* Create a Extrinsic */
    Extrinsicf extrinsic;

    /* Test default constructor */
    extrinsic.SetChildCoordinate(expected_child_coord);
    ASSERT_TRUE(expected_child_coord == extrinsic.GetChildCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////l
TEST(SetAndGetPoseTest, NormalInput)
{
    /* Generate expected values */
    const Extrinsicf::Pose3Type expected_pose(holo::geometry::Rot3f::Rz(holo::geometry::Radian(36.0f)),
                                                    holo::geometry::Point3f(1.0f, 2.0f, 3.0f));

    /* Create a Extrinsic */
    Extrinsicf extrinsic;

    /* Test default constructor */
    extrinsic.SetPose(expected_pose);
    ASSERT_TRUE(expected_pose == extrinsic.GetPose());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////l
TEST(GetSensorIdTest, NormalInput)
{
    const Coordinate    eparent_coord = Coordinate(Coordinate::IMU_MAIN); 
    const Coordinate    child_coord  = Coordinate(Coordinate::IMU_VEHICLE); 

    const Extrinsicf::Pose3Type pose(holo::geometry::Rot3f::Rz(holo::geometry::Radian(36.0f)),
                                                holo::geometry::Point3f(1.0f, 2.0f, 3.0f));

    Extrinsicf extrinsic(eparent_coord, child_coord, pose);

    ASSERT_EQ(extrinsic.GetSensorId(), 0x02000C84U);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SaveAndLoadYamlTest, NormalInput)
{
    const Coordinate    expected_parent_coord = Coordinate(Coordinate::IMU_MAIN); 
    const Coordinate    expected_child_coord  = Coordinate(Coordinate::IMU_VEHICLE); 

    const Extrinsicf::Pose3Type expected_pose(holo::geometry::Rot3f::Rz(holo::geometry::Radian(36.0f)),
                                                holo::geometry::Point3f(1.0f, 2.0f, 3.0f));

    Extrinsicf extrinsic(expected_parent_coord, expected_child_coord, expected_pose);
    Extrinsicf extrinsic_expect;

    Extrinsicf::SaveYaml("test.yaml", extrinsic);
    extrinsic_expect = Extrinsicf::LoadYaml("test.yaml");

    ASSERT_EQ(extrinsic.GetParentCoordinate(), extrinsic_expect.GetParentCoordinate());
    ASSERT_EQ(extrinsic.GetChildCoordinate(), extrinsic_expect.GetChildCoordinate());
    ASSERT_EQ(extrinsic.GetPose(), extrinsic_expect.GetPose());
    ASSERT_THROW(Extrinsicf::LoadYaml("test111.yaml"), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
