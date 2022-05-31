/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief Unit test for float32_t type odometry class
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date Sep 14, 2019
 */

#include <gtest/gtest.h>
#include <holo/common/odometry.h>

using holo::common::Coordinate;
using holo::common::Timestamp;

using Odometryf = holo::common::Odometryf;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorDefaultTestConst, NormalInput)
{
    /* Create a Odometryf by default constructor */
    Odometryf odometry;

    /* Test default constructor */
    ASSERT_TRUE(Timestamp() == odometry.GetTimestamp());
    ASSERT_TRUE(Coordinate() == odometry.GetCoordinate());
    ASSERT_TRUE(Coordinate() == odometry.GetChildCoordinate());
    ASSERT_TRUE(holo::geometry::Pose3f() == odometry.GetPose());
    ASSERT_TRUE(holo::Vector6f::Zero() == odometry.GetVelocity());
    ASSERT_TRUE(holo::numerics::Matrix6f::Identity() == odometry.GetPoseCovariance());
    ASSERT_TRUE(holo::numerics::Matrix6f::Identity() == odometry.GetVelocityCovariance());
    ASSERT_TRUE(Odometryf::Status::ALLGOOD == odometry.GetStatus());
    ASSERT_TRUE(Odometryf::Source::NONE == odometry.GetSource());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorDefaultTest, NormalInput)
{
    /* Create a Odometryf by default constructor */
    Odometryf odometry;

    /* Test default constructor */
    ASSERT_TRUE(Timestamp() == odometry.GetTimestamp());
    ASSERT_TRUE(Coordinate() == odometry.GetCoordinate());
    ASSERT_TRUE(Coordinate() == odometry.GetChildCoordinate());
    ASSERT_TRUE(holo::geometry::Pose3f() == odometry.GetPose());
    ASSERT_TRUE(holo::Vector6f::Zero() == odometry.GetVelocity());
    ASSERT_TRUE(holo::numerics::Matrix6f::Identity() == odometry.GetPoseCovariance());
    ASSERT_TRUE(holo::numerics::Matrix6f::Identity() == odometry.GetVelocityCovariance());
    ASSERT_TRUE(Odometryf::Status::ALLGOOD == odometry.GetStatus());
    ASSERT_TRUE(Odometryf::Source::NONE == odometry.GetSource());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(IsSolutionGoodTest, NormalInput)
{
    /* Construct a Odometryf */
    Odometryf odometry;

    /* Generate expected value */
    const Odometryf::Status expected_status = Odometryf::Status::POSITIONINACTIVE;
    odometry.SetStatus(expected_status);

    /* Test is solution good function */
    ASSERT_FALSE(odometry.IsSolutionGood());
    odometry.SetStatus(Odometryf::Status::ALLGOOD);
    ASSERT_TRUE(odometry.IsSolutionGood());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetTimestampTest, NormalInput)
{
    /* Construct a Odometryf */
    Odometryf odometry;

    /* Generate expected value */
    Timestamp expected_timestamp(5u, 10u);
    odometry.SetTimestamp(expected_timestamp);

    /* Test get timestamp function */
    ASSERT_TRUE(expected_timestamp == odometry.GetTimestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetCoordTest, NormalInput)
{
    /* Construct a Odometryf */
    Odometryf odometry;

    /* Generate expected coordinate id */
    Coordinate expected_coord(Coordinate(0x12345678));

    /* Set coord id to Odometryf */
    odometry.SetCoordinate(expected_coord);

    /* test result */
    ASSERT_TRUE(expected_coord == odometry.GetCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetChildCoordTest, NormalInput)
{
    /* Construct a Odometryf */
    Odometryf odometry;

    /* Generate expected child coordinate */
    Coordinate expected_child_coord(Coordinate(0x02345678));

    /* Set child coord to Odometryf */
    odometry.SetChildCoordinate(expected_child_coord);

    /* test result */
    ASSERT_TRUE(expected_child_coord == odometry.GetChildCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetStatusTest, NormalInput)
{
    /* Create a Odometryf */
    Odometryf odometry;

    /* Generate expected value */
    const Odometryf::Status expected_status = Odometryf::Status::POSITIONINACTIVE;
    odometry.SetStatus(expected_status);

    /* Test get status function */
    ASSERT_TRUE(expected_status == odometry.GetStatus());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetSourceTest, NormalInput)
{
    /* Create a Odometryf */
    Odometryf odometry;

    /* Generate expected value */
    const Odometryf::Source expected_source = Odometryf::Source::SEMANTIC;
    odometry.SetSource(expected_source);

    /* Test get source function */
    ASSERT_TRUE(expected_source == odometry.GetSource());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetPoseTest, NormalInput)
{
    /* Create a Odometryf */
    Odometryf odometry;

    /* Generate expected value */
    const Odometryf::Pose3Type expected_pose(holo::geometry::Rot3f::Rz(holo::geometry::Radian(36.0)),
                                             holo::geometry::Point3f(1.0l, 2.0l, 3.0l));

    /* Test set and get pose function */
    odometry.SetPose(expected_pose);
    ASSERT_TRUE(expected_pose == odometry.GetPose());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetVelocityTest, NormalInput)
{
    /* Create a Odometryf */
    Odometryf odometry;

    /* Generate expected value */
    const Odometryf::Vector6Type expected_velocity(6.0l, 5.0l, 4.0l, 3.0l, 2.0l, 1.0l);

    /* Test set and get velocity function */
    odometry.SetVelocity(expected_velocity);
    ASSERT_TRUE(expected_velocity == odometry.GetVelocity());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetPoseCovarianceTest, NormalInput)
{
    /* Create a Odometryf */
    Odometryf odometry;

    /* Generate expected value */
    Odometryf::Matrix6Type expected_pose_covariance;
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
    /* Create a Odometryf */
    Odometryf odometry;

    /* Generate expected value */
    Odometryf::Matrix6Type expected_velocity_covariance;
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
    /* Create a Odometryf */
    Odometryf odometry;

    /* Generate expected value */
    const Odometryf::Vector3Type expected_linear_acceleration(6.0l, 5.0l, 4.0l);

    /* Test set and get linear acceleration function */
    odometry.SetLinearAcceleration(expected_linear_acceleration);
    ASSERT_TRUE(expected_linear_acceleration == odometry.GetLinearAcceleration());
}

TEST(Odometryf, SetCheckPosePrecision)
{
    Odometryf odo;
    EXPECT_TRUE(odo.IsPoseUnknownPrecision());

    odo.SetPosePrecision(Odometryf::PrecisionValueType::HIGH);
    EXPECT_TRUE(odo.IsPoseHighPrecision());
    EXPECT_FALSE(odo.IsPoseMediumPrecision());
    EXPECT_FALSE(odo.IsPoseLowPrecision());

    odo.SetPosePrecision(Odometryf::PrecisionValueType::MEDIUM);
    EXPECT_FALSE(odo.IsPoseHighPrecision());
    EXPECT_TRUE(odo.IsPoseMediumPrecision());
    EXPECT_FALSE(odo.IsPoseLowPrecision());

    odo.SetPosePrecision(Odometryf::PrecisionValueType::LOW);
    EXPECT_FALSE(odo.IsPoseHighPrecision());
    EXPECT_FALSE(odo.IsPoseMediumPrecision());
    EXPECT_TRUE(odo.IsPoseLowPrecision());
    odo.SetPosePrecision(Odometryf::PrecisionValueType::UNKNOWN);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetLinearAccelerationTest, GetSerializedSize)
{
    Odometryf odometry;
    ASSERT_EQ(396, odometry.GetSerializedSize<4U>());
    ASSERT_EQ(408, odometry.GetSerializedSize<8U>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Odometryf, SerializeDeserialize)
{
    /* Create Odometryd */
    Odometryf input_odometry, output_odometry;

    input_odometry.SetTimestamp(Timestamp(20, 30));
    Coordinate coordinate;
    input_odometry.SetCoordinate(coordinate);
    input_odometry.SetChildCoordinate(coordinate);
    input_odometry.SetStatus(Odometryf::Status::SOLUTIONNOGOOD);
    input_odometry.SetSource(Odometryf::Source::HD_MAP);
    holo::geometry::Pose3f pose3;
    pose3.SetRotation(holo::geometry::Rot3f(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0));
    pose3.SetTranslation(holo::geometry::Point3f(1.0, 2.0, 3.0));
    input_odometry.SetPose(pose3);
    input_odometry.SetVelocity(holo::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5));
    holo::numerics::Matrix6f pose_cov;
    pose_cov.SetIdentity();
    input_odometry.SetPoseCovariance(pose_cov);
    holo::numerics::Matrix6f vel_cov;
    vel_cov.SetIdentity();
    input_odometry.SetVelocityCovariance(vel_cov);
    input_odometry.SetLinearAcceleration(holo::Vector3f(0.0, 0.1, 0.2));

    uint8_t                           buffer[512];
    holo::serialization::Serializer<> serializer(buffer, 512);
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

TEST(IsSolutionGoodTest, SetUnknownPrecision)
{
    Odometryf odometry;
    odometry.SetUnknownPrecision(Odometryf::PrecisionFieldType::ANGULAR_VELOCITY_X,
                                 Odometryf::PrecisionFieldType::ANGULAR_VELOCITY_Y);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using LocalMapOdometryf = holo::common::LocalMapOdometryf;

TEST(LocalMapOdometryf, Constructor)
{
    LocalMapOdometryf odometry;

    ASSERT_TRUE(Timestamp() == odometry.GetTimestamp());
    ASSERT_TRUE(Coordinate() == odometry.GetCoordinate());
    ASSERT_TRUE(Coordinate() == odometry.GetChildCoordinate());
    ASSERT_TRUE(holo::geometry::Pose3f() == odometry.GetPose());
    ASSERT_TRUE(holo::Vector6f::Zero() == odometry.GetVelocity());
    ASSERT_TRUE(holo::numerics::Matrix6f::Identity() == odometry.GetPoseCovariance());
    ASSERT_TRUE(holo::numerics::Matrix6f::Identity() == odometry.GetVelocityCovariance());
    ASSERT_TRUE(LocalMapOdometryf::Status::ALLGOOD == odometry.GetStatus());
    ASSERT_TRUE(LocalMapOdometryf::Source::NONE == odometry.GetSource());
    ASSERT_EQ(odometry.GetSpeed(), 0);
    ASSERT_EQ(odometry.GetHeading(), 0);
    ASSERT_EQ(odometry.GetMatchingResultsActived(), false);
    ASSERT_EQ(odometry.GetMatchingResults().size(), 0);
    ASSERT_EQ(odometry.GetLocalMapOdometryStatus(), LocalMapOdometryf::LocalMapOdometryStatus::UNKNOWN);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalMapOdometryf, SetAndGetTimestamp)
{
    LocalMapOdometryf odometry;

    LocalMapOdometryf::Timestamp expected_timestamp(5u, 10u);
    odometry.SetTimestamp(expected_timestamp);

    ASSERT_TRUE(expected_timestamp == odometry.GetTimestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalMapOdometryf, SetAndGetStatus)
{
    LocalMapOdometryf odometry;
    odometry.SetLocalMapOdometryStatus(LocalMapOdometryf::LocalMapOdometryStatus::MIDDLE);

    ASSERT_EQ(odometry.GetLocalMapOdometryStatus(), LocalMapOdometryf::LocalMapOdometryStatus::MIDDLE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalMapOdometryf, SetAndGetSpeed)
{
    LocalMapOdometryf odometry;
    odometry.SetSpeed(10);

    ASSERT_TRUE(odometry.GetSpeed() == 10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalMapOdometryf, SetAndGetHeading)
{
    LocalMapOdometryf odometry;
    odometry.SetHeading(10);

    ASSERT_TRUE(odometry.GetHeading() == 10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalMapOdometryf, SetAndGetMatchingResultsActived)
{
    LocalMapOdometryf odometry;
    odometry.SetMatchingResultsActived(true);

    ASSERT_TRUE(odometry.GetMatchingResultsActived() == true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalMapOdometryf, SetAndGetLocationCovariance)
{
    LocalMapOdometryf              odometry;
    LocalMapOdometryf::Vector3Type ve(10.1, 12.2, 13.3);
    odometry.SetLocationCovariance(ve);

    LocalMapOdometryf::Vector3Type location_covariance = odometry.GetLocationCovariance();
    ASSERT_EQ(ve[0], location_covariance[0]);
    ASSERT_EQ(ve[1], location_covariance[1]);
    ASSERT_EQ(ve[2], location_covariance[2]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalMapOdometryf, SetAndGetLocationCovariance_2)
{
    LocalMapOdometryf odometry;

    Odometryf::Matrix6Type expected_pose_covariance;
    for (uint8_t i = 0u; i < expected_pose_covariance.GetRows(); ++i)
    {
        for (uint8_t j = 0u; j < expected_pose_covariance.GetCols(); ++j)
        {
            expected_pose_covariance(i, j) = i + j;
        }
    }

    odometry.SetPoseCovariance(expected_pose_covariance);
    LocalMapOdometryf::Vector3Type location_covariance = odometry.GetLocationCovariance();
    ASSERT_TRUE(holo::numerics::Vector3f(6.0, 8.0, 10.0) == location_covariance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalMapOdometryf, SetAndGetMatchResults)
{
    LocalMapOdometryf                 odometry;
    LocalMapOdometryf::MatchingResult result;
    result.link_id                = 1;
    result.lane_id                = 2;
    result.longitudinal_off_start = 3;
    result.longitudinal_off_end   = 4;
    result.accuracy               = 5;
    result.relative_heading       = 6;
    result.lateral_off_left       = 7;
    result.lateral_off_right      = 8;
    result.lateral_off_middle     = 9;
    result.probobility            = 1;

    LocalMapOdometryf::MatchingResult result1;
    result1.link_id                = 11;
    result1.lane_id                = 12;
    result1.longitudinal_off_start = 13;
    result1.longitudinal_off_end   = 14;
    result1.accuracy               = 15;
    result1.relative_heading       = 16;
    result1.lateral_off_left       = 17;
    result1.lateral_off_right      = 18;
    result1.lateral_off_middle     = 19;
    result1.probobility            = 1;

    holo::container::Vector<LocalMapOdometryf::MatchingResult, 3U> result_vector;
    result_vector.push_back(result);
    result_vector.push_back(result1);

    odometry.SetMatchingResults(result_vector);

    ASSERT_EQ(odometry.GetMatchingResults()[0].link_id, result.link_id);
    ASSERT_EQ(odometry.GetMatchingResults()[0].lane_id, result.lane_id);
    ASSERT_EQ(odometry.GetMatchingResults()[0].longitudinal_off_end, result.longitudinal_off_end);
    ASSERT_EQ(odometry.GetMatchingResults()[0].lateral_off_right, result.lateral_off_right);
    ASSERT_EQ(odometry.GetMatchingResults()[0].probobility, result.probobility);

    ASSERT_EQ(odometry.GetMatchingResults()[1].link_id, result1.link_id);
    ASSERT_EQ(odometry.GetMatchingResults()[1].lane_id, result1.lane_id);
    ASSERT_EQ(odometry.GetMatchingResults()[1].longitudinal_off_end, result1.longitudinal_off_end);
    ASSERT_EQ(odometry.GetMatchingResults()[1].lateral_off_right, result1.lateral_off_right);
    ASSERT_EQ(odometry.GetMatchingResults()[1].probobility, result1.probobility);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LocalMapOdometryf, SerializeDeserialize)
{
    LocalMapOdometryf input_odometry, output_odometry;

    input_odometry.SetTimestamp(Timestamp(20, 30));
    Coordinate coordinate;
    input_odometry.SetCoordinate(coordinate);
    input_odometry.SetChildCoordinate(coordinate);
    input_odometry.SetStatus(Odometryf::Status::SOLUTIONNOGOOD);
    input_odometry.SetSource(Odometryf::Source::HD_MAP);
    holo::geometry::Pose3f pose3;
    pose3.SetRotation(holo::geometry::Rot3f(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0));
    pose3.SetTranslation(holo::geometry::Point3f(1.0, 2.0, 3.0));
    input_odometry.SetPose(pose3);
    input_odometry.SetVelocity(holo::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5));
    holo::numerics::Matrix6f pose_cov;
    pose_cov.SetIdentity();
    input_odometry.SetPoseCovariance(pose_cov);
    holo::numerics::Matrix6f vel_cov;
    vel_cov.SetIdentity();
    input_odometry.SetVelocityCovariance(vel_cov);
    input_odometry.SetLinearAcceleration(holo::Vector3f(0.0, 0.1, 0.2));

    input_odometry.SetLocalMapOdometryStatus(LocalMapOdometryf::LocalMapOdometryStatus::MIDDLE);
    input_odometry.SetSpeed(10);
    input_odometry.SetHeading(10);
    input_odometry.SetMatchingResultsActived(true);

    LocalMapOdometryf::MatchingResult result;
    result.link_id                = 1;
    result.lane_id                = 2;
    result.longitudinal_off_start = 3;
    result.longitudinal_off_end   = 4;
    result.accuracy               = 5;
    result.relative_heading       = 6;
    result.lateral_off_left       = 7;
    result.lateral_off_right      = 8;
    result.lateral_off_middle     = 9;
    result.probobility            = 1;

    LocalMapOdometryf::MatchingResult result1;
    result1.link_id                = 11;
    result1.lane_id                = 12;
    result1.longitudinal_off_start = 13;
    result1.longitudinal_off_end   = 14;
    result1.accuracy               = 15;
    result1.relative_heading       = 16;
    result1.lateral_off_left       = 17;
    result1.lateral_off_right      = 18;
    result1.lateral_off_middle     = 19;
    result1.probobility            = 1;

    holo::container::Vector<LocalMapOdometryf::MatchingResult, 3U> result_vector;
    result_vector.push_back(result);
    result_vector.push_back(result1);

    input_odometry.SetMatchingResults(result_vector);

    uint8_t                           buffer[2048];
    holo::serialization::Serializer<> serializer(buffer, 2048);
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
    ASSERT_EQ(input_odometry.GetLocalMapOdometryStatus(), LocalMapOdometryf::LocalMapOdometryStatus::MIDDLE);
    ASSERT_EQ(input_odometry.GetSpeed(), 10);
    ASSERT_EQ(input_odometry.GetHeading(), 10);
    ASSERT_EQ(input_odometry.GetMatchingResultsActived(), true);

    ASSERT_EQ(input_odometry.GetMatchingResults()[0].link_id, result.link_id);
    ASSERT_EQ(input_odometry.GetMatchingResults()[0].lane_id, result.lane_id);
    ASSERT_EQ(input_odometry.GetMatchingResults()[0].longitudinal_off_end, result.longitudinal_off_end);
    ASSERT_EQ(input_odometry.GetMatchingResults()[0].lateral_off_right, result.lateral_off_right);
    ASSERT_EQ(input_odometry.GetMatchingResults()[0].probobility, result.probobility);

    ASSERT_EQ(input_odometry.GetMatchingResults()[1].link_id, result1.link_id);
    ASSERT_EQ(input_odometry.GetMatchingResults()[1].lane_id, result1.lane_id);
    ASSERT_EQ(input_odometry.GetMatchingResults()[1].longitudinal_off_end, result1.longitudinal_off_end);
    ASSERT_EQ(input_odometry.GetMatchingResults()[1].lateral_off_right, result1.lateral_off_right);
    ASSERT_EQ(input_odometry.GetMatchingResults()[1].probobility, result1.probobility);
}

using DrOdometryf = holo::common::DrOdometryf;
TEST(DrOdometryf, Constructor)
{
    const DrOdometryf odometry;

    ASSERT_TRUE(Timestamp() == odometry.GetTimestamp());
    ASSERT_TRUE(Coordinate() == odometry.GetCoordinate());
    ASSERT_TRUE(Coordinate() == odometry.GetChildCoordinate());
    ASSERT_TRUE(holo::geometry::Pose3f() == odometry.GetPose());
    ASSERT_TRUE(holo::Vector6f::Zero() == odometry.GetVelocity());
    ASSERT_TRUE(holo::numerics::Matrix6f::Identity() == odometry.GetPoseCovariance());
    ASSERT_TRUE(holo::numerics::Matrix6f::Identity() == odometry.GetVelocityCovariance());
    ASSERT_TRUE(DrOdometryf::Status::ALLGOOD == odometry.GetStatus());
    ASSERT_TRUE(DrOdometryf::Source::NONE == odometry.GetSource());
    ASSERT_FLOAT_EQ(1.0f, odometry.GetGroundRotation().GetW());
    ASSERT_FLOAT_EQ(0.0f, odometry.GetGroundRotation().GetX());
    ASSERT_FLOAT_EQ(0.0f, odometry.GetGroundRotation().GetY());
    ASSERT_FLOAT_EQ(0.0f, odometry.GetGroundRotation().GetZ());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(DrOdometryf, SetAndGetGroundRotation)
{
    DrOdometryf odometry;

    holo::float32_t             data[4u] = {0.1, 0.2, 0.3, 0.4};
    holo::geometry::Quaternionf quaternion(data, 4u);

    odometry.SetGroundRotation(quaternion);

    holo::float64_t value = std::sqrt(0.1 * 0.1 + 0.2 * 0.2 + 0.3 * 0.3 + 0.4 * 0.4);
    ASSERT_FLOAT_EQ(0.4 / value, odometry.GetGroundRotation().GetW());
    ASSERT_FLOAT_EQ(0.1 / value, odometry.GetGroundRotation().GetX());
    ASSERT_FLOAT_EQ(0.2 / value, odometry.GetGroundRotation().GetY());
    ASSERT_FLOAT_EQ(0.3 / value, odometry.GetGroundRotation().GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(DrOdometryf, SetAndGetAngularVelocity)
{
    DrOdometryf odometry;
    odometry.SetAngularVelocity(DrOdometryf::Vector3Type(10.1, 12.2, 13.3));

    ASSERT_EQ(DrOdometryf::Vector3Type(10.1, 12.2, 13.3), odometry.GetAngularVelocity());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(DrOdometryf, SetAndGetAngularVelocity_2)
{
    DrOdometryf odometry;

    odometry.SetVelocity(holo::numerics::Vector6f(1.1, 1.2, 1.3, 1.4, 1.5, 1.6));
    odometry.SetAngularVelocity(holo::numerics::Vector3f(2.1, 2.2, 2.3));
    ASSERT_TRUE(holo::numerics::Vector3f(2.1, 2.2, 2.3) == odometry.GetAngularVelocity());
    ASSERT_TRUE(holo::numerics::Vector6f(1.1, 1.2, 1.3, 2.1, 2.2, 2.3) == odometry.GetVelocity());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(DrOdometryf, SetAndGetLocationCovariance)
{
    DrOdometryf              odometry;
    DrOdometryf::Vector3Type ve(10.1, 12.2, 13.3);
    odometry.SetLocationCovariance(ve);

    DrOdometryf::Vector3Type location_covariance = odometry.GetLocationCovariance();
    ASSERT_EQ(ve[0], location_covariance[0]);
    ASSERT_EQ(ve[1], location_covariance[1]);
    ASSERT_EQ(ve[2], location_covariance[2]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(DrOdometryf, SetAndGetLocationCovariance_2)
{
    DrOdometryf odometry;

    Odometryf::Matrix6Type expected_pose_covariance;
    for (uint8_t i = 0u; i < expected_pose_covariance.GetRows(); ++i)
    {
        for (uint8_t j = 0u; j < expected_pose_covariance.GetCols(); ++j)
        {
            expected_pose_covariance(i, j) = i + j;
        }
    }

    odometry.SetPoseCovariance(expected_pose_covariance);
    DrOdometryf::Vector3Type location_covariance = odometry.GetLocationCovariance();
    ASSERT_TRUE(holo::numerics::Vector3f(6.0, 8.0, 10.0) == location_covariance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(DrOdometryf, SerializeDeserialize)
{
    DrOdometryf input_odometry, output_odometry;

    input_odometry.SetTimestamp(Timestamp(20, 30));
    Coordinate coordinate;
    input_odometry.SetCoordinate(coordinate);
    input_odometry.SetChildCoordinate(coordinate);
    input_odometry.SetStatus(Odometryf::Status::SOLUTIONNOGOOD);
    input_odometry.SetSource(Odometryf::Source::HD_MAP);
    holo::geometry::Pose3f pose3;
    pose3.SetRotation(holo::geometry::Rot3f(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0));
    pose3.SetTranslation(holo::geometry::Point3f(1.0, 2.0, 3.0));
    input_odometry.SetPose(pose3);
    input_odometry.SetVelocity(holo::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5));
    holo::numerics::Matrix6f pose_cov;
    pose_cov.SetIdentity();
    input_odometry.SetPoseCovariance(pose_cov);
    holo::numerics::Matrix6f vel_cov;
    vel_cov.SetIdentity();
    input_odometry.SetVelocityCovariance(vel_cov);
    input_odometry.SetLinearAcceleration(holo::Vector3f(0.0, 0.1, 0.2));
    holo::float32_t             data[4u] = {0.1, 0.2, 0.3, 0.4};
    holo::geometry::Quaternionf quaternion(data, 4u);
    input_odometry.SetGroundRotation(quaternion);

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
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
    ASSERT_EQ(input_odometry.GetGroundRotation().GetW(), output_odometry.GetGroundRotation().GetW());
    ASSERT_EQ(input_odometry.GetGroundRotation().GetX(), output_odometry.GetGroundRotation().GetX());
    ASSERT_EQ(input_odometry.GetGroundRotation().GetY(), output_odometry.GetGroundRotation().GetY());
    ASSERT_EQ(input_odometry.GetGroundRotation().GetZ(), output_odometry.GetGroundRotation().GetZ());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
