/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_odometry_io.cpp
 * @brief unit test io utils for odometry objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-02-01
 */

#include <gtest/gtest.h>
#include <holo/common/odometry.h>
#include <holo/io/common/odometry.h>

using Odometryf = holo::common::Odometryf;
using holo::common::Coordinate;
using holo::common::Odometryf;

TEST(OdometryIO, EncodeAndDecodeOdometry)
{
    Odometryf input_odometry, output_odometry;

    input_odometry.SetTimestamp(holo::Timestamp(20, 30));
    Coordinate coordinate;
    input_odometry.SetCoordinate(coordinate);
    input_odometry.SetChildCoordinate(coordinate);
    input_odometry.SetStatus(Odometryf::Status::SOLUTIONNOGOOD);
    input_odometry.SetSource(Odometryf::Source::HD_MAP);
    holo::geometry::Pose3f pose3;
    pose3.SetRotation(holo::Rot3f(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0));
    pose3.SetTranslation(holo::Point3f(1.0, 2.0, 3.0));
    input_odometry.SetPose(pose3);
    input_odometry.SetVelocity(holo::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5));
    holo::numerics::Matrix6f pose_cov;
    pose_cov.SetIdentity();
    input_odometry.SetPoseCovariance(pose_cov);
    holo::numerics::Matrix6f vel_cov;
    vel_cov.SetIdentity();
    input_odometry.SetVelocityCovariance(vel_cov);
    input_odometry.SetLinearAcceleration(holo::Vector3f(0.0, 0.1, 0.2));

    YAML::Node node;
    node["test"]    = input_odometry;
    output_odometry = node["test"].as<Odometryf>();

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

TEST(OdometryIO, DecodeOdometry_1)
{
    Odometryf input_odometry, output_odometry;

    input_odometry.SetTimestamp(holo::Timestamp(20, 30));
    Coordinate coordinate;
    input_odometry.SetCoordinate(coordinate);
    input_odometry.SetChildCoordinate(coordinate);
    input_odometry.SetStatus(Odometryf::Status::SOLUTIONNOGOOD);
    input_odometry.SetSource(Odometryf::Source::HD_MAP);
    holo::geometry::Pose3f pose3;
    pose3.SetRotation(holo::Rot3f(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0));
    pose3.SetTranslation(holo::Point3f(1.0, 2.0, 3.0));
    input_odometry.SetPose(pose3);
    input_odometry.SetVelocity(holo::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5));
    holo::numerics::Matrix6f pose_cov;
    pose_cov.SetIdentity();
    input_odometry.SetPoseCovariance(pose_cov);
    holo::numerics::Matrix6f vel_cov;
    vel_cov.SetIdentity();
    input_odometry.SetVelocityCovariance(vel_cov);
    input_odometry.SetLinearAcceleration(holo::Vector3f(0.0, 0.1, 0.2));

    YAML::Node node;
    node["timestamp"]           = holo::Timestamp(20, 30);
    node["parent_coordinate"]   = coordinate;
    node["child_coordinate"]    = coordinate;
    node["precision"]           = 0;
    node["pose"]                = pose3;
    node["velocity"]            = holo::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5);
    node["linear_acceleration"] = holo::Vector3f(0.0, 0.1, 0.2);
    node["pose_covariance"]     = pose_cov;
    node["velocity_covariance"] = vel_cov;
    node["status"] = 1;
    node["source"] = 0x0080;

    output_odometry = node.as<Odometryf>();

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

TEST(OdometryIO, DecodeOdometry_2)
{
    Odometryf input_odometry, output_odometry;

    input_odometry.SetTimestamp(holo::Timestamp(20, 30));
    Coordinate coordinate;
    input_odometry.SetCoordinate(coordinate);
    input_odometry.SetChildCoordinate(coordinate);
    input_odometry.SetStatus(Odometryf::Status::SOLUTIONNOGOOD);
    input_odometry.SetSource(Odometryf::Source::HD_MAP);
    holo::geometry::Pose3f pose3;
    pose3.SetRotation(holo::Rot3f(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0));
    pose3.SetTranslation(holo::Point3f(1.0, 2.0, 3.0));
    input_odometry.SetPose(pose3);
    input_odometry.SetVelocity(holo::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5));
    holo::numerics::Matrix6f pose_cov;
    pose_cov.SetIdentity();
    input_odometry.SetPoseCovariance(pose_cov);
    holo::numerics::Matrix6f vel_cov;
    vel_cov.SetIdentity();
    input_odometry.SetVelocityCovariance(vel_cov);
    input_odometry.SetLinearAcceleration(holo::Vector3f(0.0, 0.1, 0.2));

    YAML::Node node;
    node["timestamp"]           = holo::Timestamp(20, 30);
    node["parent_coordinate"]   = coordinate;
    node["child_coordinate"]    = coordinate;
    node["precision"]           = 0;
    node["pose"]                = pose3;
    node["velocity"]            = holo::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5);
    node["linear_acceleration"] = holo::Vector3f(0.0, 0.1, 0.2);
    node["pose_covariance"]     = pose_cov;
    node["velocity_covariance"] = vel_cov;
    node["status"] = "xxx";
    node["source"] = 0x0080;

    try
    {
        output_odometry = node.as<Odometryf>();
    }
    catch(...)
    {
        
    }
}

TEST(OdometryIO, DecodeOdometry_3)
{
    Odometryf input_odometry, output_odometry;

    input_odometry.SetTimestamp(holo::Timestamp(20, 30));
    Coordinate coordinate;
    input_odometry.SetCoordinate(coordinate);
    input_odometry.SetChildCoordinate(coordinate);
    input_odometry.SetStatus(Odometryf::Status::SOLUTIONNOGOOD);
    input_odometry.SetSource(Odometryf::Source::HD_MAP);
    holo::geometry::Pose3f pose3;
    pose3.SetRotation(holo::Rot3f(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0));
    pose3.SetTranslation(holo::Point3f(1.0, 2.0, 3.0));
    input_odometry.SetPose(pose3);
    input_odometry.SetVelocity(holo::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5));
    holo::numerics::Matrix6f pose_cov;
    pose_cov.SetIdentity();
    input_odometry.SetPoseCovariance(pose_cov);
    holo::numerics::Matrix6f vel_cov;
    vel_cov.SetIdentity();
    input_odometry.SetVelocityCovariance(vel_cov);
    input_odometry.SetLinearAcceleration(holo::numerics::Vector3f(0.0, 0.1, 0.2));

    YAML::Node node;
    node["timestamp"]           = holo::common::Timestamp(20, 30);
    node["parent_coordinate"]   = coordinate;
    node["child_coordinate"]    = coordinate;
    node["precision"]           = 0;
    node["pose"]                = pose3;
    node["velocity"]            = holo::numerics::Vector6f(0.0, 0.1, 0.2, 0.3, 0.4, 0.5);
    node["linear_acceleration"] = holo::numerics::Vector3f(0.0, 0.1, 0.2);
    node["pose_covariance"]     = pose_cov;
    node["velocity_covariance"] = vel_cov;
    node["status"] = 1;
    node["source"] = "xxx";

    try
    {
        output_odometry = node.as<Odometryf>();
    }
    catch(...)
    {
        
    }
}


TEST(OdometryIO, DecodeOdometryException)
{
    Odometryf odometry;
    YAML::Node node = YAML::Load("{'precision':10,'status':1}");

    try
    {
        odometry = node.as<Odometryf>();
    }
    catch(...)
    {
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
