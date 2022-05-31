/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief Unit test for float64_t type odometry class
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date Sep 14, 2019
 */

#include <gtest/gtest.h>
#include <holo/common/odometry.h>

using holo::common::Coordinate;
using holo::common::Odometryd;
using holo::common::Timestamp;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorDefaultTestConst, NormalInput)
{
    /* Create a Odometryd by default constructor */
    const Odometryd odometry;

    /* Test default constructor */
    ASSERT_TRUE(Timestamp() == odometry.GetTimestamp());
    ASSERT_TRUE(Coordinate() == odometry.GetCoordinate());
    ASSERT_TRUE(Coordinate() == odometry.GetChildCoordinate());
    ASSERT_TRUE(holo::geometry::Pose3d() == odometry.GetPose());
    ASSERT_TRUE(holo::Vector6d::Zero() == odometry.GetVelocity());
    ASSERT_TRUE(holo::numerics::Matrix6d::Identity() == odometry.GetPoseCovariance());
    ASSERT_TRUE(holo::numerics::Matrix6d::Identity() == odometry.GetVelocityCovariance());
    ASSERT_TRUE(Odometryd::Status::ALLGOOD == odometry.GetStatus());
    ASSERT_TRUE(Odometryd::Source::NONE == odometry.GetSource());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorDefaultTest, NormalInput)
{
    /* Create a Odometryd by default constructor */
    Odometryd odometry;

    /* Test default constructor */
    ASSERT_TRUE(Timestamp() == odometry.GetTimestamp());
    ASSERT_TRUE(Coordinate() == odometry.GetCoordinate());
    ASSERT_TRUE(Coordinate() == odometry.GetChildCoordinate());
    ASSERT_TRUE(holo::geometry::Pose3d() == odometry.GetPose());
    ASSERT_TRUE(holo::Vector6d::Zero() == odometry.GetVelocity());
    ASSERT_TRUE(holo::numerics::Matrix6d::Identity() == odometry.GetPoseCovariance());
    ASSERT_TRUE(holo::numerics::Matrix6d::Identity() == odometry.GetVelocityCovariance());
    ASSERT_TRUE(Odometryd::Status::ALLGOOD == odometry.GetStatus());
    ASSERT_TRUE(Odometryd::Source::NONE == odometry.GetSource());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(IsSolutionGoodTest, NormalInput)
{
    /* Construct a Odometryd */
    Odometryd odometry;

    /* Generate expected value */
    const Odometryd::Status expected_status = Odometryd::Status::POSITIONINACTIVE;
    odometry.SetStatus(expected_status);

    /* Test is solution good function */
    ASSERT_FALSE(odometry.IsSolutionGood());
    odometry.SetStatus(Odometryd::Status::ALLGOOD);
    ASSERT_TRUE(odometry.IsSolutionGood());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetTimestampTest, NormalInput)
{
    /* Construct a Odometryd */
    Odometryd odometry;

    /* Generate expected value */
    Timestamp expected_timestamp(5u, 10u);
    odometry.SetTimestamp(expected_timestamp);

    /* Test get timestamp function */
    ASSERT_TRUE(expected_timestamp == odometry.GetTimestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetCoordTest, NormalInput)
{
    /* Construct a Odometryd */
    Odometryd odometry;

    /* Generate expected coordinate id */
    Coordinate expected_coord(Coordinate(0x12345678));

    /* Set coord id to Odometryd */
    odometry.SetCoordinate(expected_coord);

    /* test result */
    ASSERT_TRUE(expected_coord == odometry.GetCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetChildCoordTest, NormalInput)
{
    /* Construct a Odometryd */
    Odometryd odometry;

    /* Generate expected child coordinate */
    Coordinate expected_child_coord(Coordinate(0x02345678));

    /* Set child coord to Odometryd */
    odometry.SetChildCoordinate(expected_child_coord);

    /* test result */
    ASSERT_TRUE(expected_child_coord == odometry.GetChildCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetStatusTest, NormalInput)
{
    /* Create a Odometryd */
    Odometryd odometry;

    /* Generate expected value */
    const Odometryd::Status expected_status = Odometryd::Status::POSITIONINACTIVE;
    odometry.SetStatus(expected_status);

    /* Test get status function */
    ASSERT_TRUE(expected_status == odometry.GetStatus());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetSourceTest, NormalInput)
{
    /* Create a Odometryd */
    Odometryd odometry;

    /* Generate expected value */
    const Odometryd::Source expected_source = Odometryd::Source::SEMANTIC;
    odometry.SetSource(expected_source);

    /* Test get source function */
    ASSERT_TRUE(expected_source == odometry.GetSource());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetPoseTest, NormalInput)
{
    /* Create a Odometryd */
    Odometryd odometry;

    /* Generate expected value */
    const Odometryd::Pose3Type expected_pose(holo::Rot3d::Rz(holo::geometry::Radian(36.0)), holo::geometry::Point3d(1.0l, 2.0l, 3.0l));

    /* Test set and get pose function */
    odometry.SetPose(expected_pose);
    ASSERT_TRUE(expected_pose == odometry.GetPose());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetVelocityTest, NormalInput)
{
    /* Create a Odometryd */
    Odometryd odometry;

    /* Generate expected value */
    const Odometryd::Vector6Type expected_velocity(6.0l, 5.0l, 4.0l, 3.0l, 2.0l, 1.0l);

    /* Test set and get velocity function */
    odometry.SetVelocity(expected_velocity);
    ASSERT_TRUE(expected_velocity == odometry.GetVelocity());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetPoseCovarianceTest, NormalInput)
{
    /* Create a Odometryd */
    Odometryd odometry;

    /* Generate expected value */
    Odometryd::Matrix6Type expected_pose_covariance;
    for (uint8_t i = 0u; i < expected_pose_covariance.GetRows(); ++i)
    {
        for (uint8_t j = 0u; j < expected_pose_covariance.GetCols(); ++j)
        {
            expected_pose_covariance(i, j) = i * expected_pose_covariance.GetCols() + j;
        }
    }

    /* Test set and get pose covariance function */
    odometry.SetPoseCovariance(expected_pose_covariance);
    ASSERT_TRUE(expected_pose_covariance == odometry.GetPoseCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetVelocityCovarianceTest, NormalInput)
{
    /* Create a Odometryd */
    Odometryd odometry;

    /* Generate expected value */
    Odometryd::Matrix6Type expected_velocity_covariance;
    for (uint8_t i = 0u; i < expected_velocity_covariance.GetRows(); ++i)
    {
        for (uint8_t j = 0u; j < expected_velocity_covariance.GetCols(); ++j)
        {
            expected_velocity_covariance(i, j) = i * expected_velocity_covariance.GetCols() + j;
        }
    }

    /* Test set and get velocity covariance function */
    odometry.SetVelocityCovariance(expected_velocity_covariance);
    ASSERT_TRUE(expected_velocity_covariance == odometry.GetVelocityCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetLinearAccelerationTest, NormalInput)
{
    /* Create a Odometryd */
    Odometryd odometry;

    /* Generate expected value */
    const Odometryd::Vector3Type expected_linear_acceleration(6.0l, 5.0l, 4.0l);

    /* Test set and get linear acceleration function */
    odometry.SetLinearAcceleration(expected_linear_acceleration);
    ASSERT_TRUE(expected_linear_acceleration == odometry.GetLinearAcceleration());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetLinearAccelerationTest, GetSerializedSize)
{
    Odometryd odometry;
    ASSERT_EQ(768, odometry.GetSerializedSize<4U>());
    ASSERT_EQ(768, odometry.GetSerializedSize<8U>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Odometryf64, SerializeDeserialize)
{
    /* Create Odometryd */
    Odometryd input_odometry, output_odometry;

    input_odometry.SetTimestamp(Timestamp(20, 30));
    Coordinate coordinate;
    input_odometry.SetCoordinate(coordinate);
    input_odometry.SetChildCoordinate(coordinate);
    input_odometry.SetStatus(Odometryd::Status::SOLUTIONNOGOOD);
    input_odometry.SetSource(Odometryd::Source::HD_MAP);
    holo::geometry::Pose3d pose3;
    pose3.SetRotation(holo::Rot3d(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0));
    pose3.SetTranslation(holo::geometry::Point3d(1.0, 2.0, 3.0));
    input_odometry.SetPose(pose3);
    input_odometry.SetVelocity(holo::Vector6d(0.0, 0.1, 0.2, 0.3, 0.4, 0.5));
    holo::numerics::Matrix6d pose_cov;
    pose_cov.SetIdentity();
    input_odometry.SetPoseCovariance(pose_cov);
    holo::numerics::Matrix6d vel_cov;
    vel_cov.SetIdentity();
    input_odometry.SetVelocityCovariance(vel_cov);
    input_odometry.SetLinearAcceleration(holo::Vector3d(0.0, 0.1, 0.2));

    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);
    serializer << input_odometry;
    EXPECT_EQ(serializer.GetSize(), input_odometry.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_odometry;

    ASSERT_EQ(input_odometry.GetTimestamp(), output_odometry.GetTimestamp());
    ASSERT_EQ(input_odometry.GetCoordinate(), output_odometry.GetCoordinate());
    ASSERT_EQ(input_odometry.GetChildCoordinate(), output_odometry.GetChildCoordinate());
    ASSERT_EQ(input_odometry.GetCoordinate(), output_odometry.GetCoordinate());
    ASSERT_EQ(input_odometry.GetChildCoordinate(), output_odometry.GetChildCoordinate());
    ASSERT_EQ(input_odometry.GetStatus(), output_odometry.GetStatus());
    ASSERT_EQ(input_odometry.GetSource(), output_odometry.GetSource());
    ASSERT_TRUE(input_odometry.GetPose().IsEqual(output_odometry.GetPose(), 1e-6));
    ASSERT_TRUE(input_odometry.GetVelocity().IsApprox(output_odometry.GetVelocity(), 1e-8));
    ASSERT_TRUE(input_odometry.GetPoseCovariance().IsApprox(output_odometry.GetPoseCovariance(), 1e-8));
    ASSERT_TRUE(input_odometry.GetVelocityCovariance().IsApprox(output_odometry.GetVelocityCovariance(), 1e-8));
    ASSERT_TRUE(input_odometry.GetLinearAcceleration().IsApprox(output_odometry.GetLinearAcceleration(), 1e-8));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
