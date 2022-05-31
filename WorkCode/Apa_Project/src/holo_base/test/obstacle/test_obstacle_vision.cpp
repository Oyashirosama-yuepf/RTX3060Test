/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_vision.cpp
 * @brief This file implements test for ObstacleVisionT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-19
 */

#include <gtest/gtest.h>
#include <holo/obstacle/obstacle_vision.h>

using namespace holo;
using holo::common::Classification;
using holo::common::Coordinate;
using holo::common::SensorId;
using holo::common::VehicleLocation;
using holo::numerics::Vector3f;

const float32_t         tolf = EpsilonT<float32_t>::value;
holo::geometry::Point2f test_point2f(1.0f, 1.0f);
holo::geometry::Point3f test_point3f(1.0f, 1.0f, 1.0f);
Vector3f                test_vector3f(1.0f, 1.0f, 1.0f);

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleVisionT, DefaultConstructor)
{
    obstacle::ObstacleVisionT<float32_t, 8U> obs;
    SensorId                             sensor_id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::TOP_MOST));

    ASSERT_EQ(obs.GetTimestamp(), Timestamp());
    ASSERT_EQ(obs.GetCoordinate(), Coordinate(Coordinate::UNKNOWN));  // COORD_UNKNOWN
    ASSERT_EQ(obs.GetObstacleId(), 0U);
    ASSERT_EQ(obs.GetSensorId(), SensorId());
    ASSERT_EQ(obs.GetClassification(), Classification());
    ASSERT_EQ(obs.GetObstacleExistScore(), 0.0f);
    ASSERT_EQ(obs.GetPosition(), holo::geometry::Point3f());
    ASSERT_EQ(obs.GetRelativeVelocity(), Vector3f());
    ASSERT_EQ(obs.GetAcceleration(), Vector3f());
    ASSERT_EQ(obs.GetPositionSigma(), holo::geometry::Point3f());
    ASSERT_EQ(obs.GetRelativeVelocitySigma(), Vector3f());
    ASSERT_EQ(obs.GetAccelerationSigma(), Vector3f());
    ASSERT_EQ(obs.GetMotionStatus(), MotionStatus::UNKNOWN);
    ASSERT_EQ(obs.GetImageBBox2D(), Box2f());
    ASSERT_EQ(obs.GetObstacleBBox3D(), Box3f());
    ASSERT_EQ(obs.GetCutInCutOut(), CutInCutOut::UNKNOWN);
    ASSERT_EQ(obs.GetKeyPoints2DSize(), 0);
    ASSERT_EQ(obs.GetKeyPoints3DSize(), 0);

    obs.SetTimestamp(Timestamp(1U, 0U));
    obs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    obs.SetObstacleId(10U);
    obs.SetSensorId(sensor_id);
    obs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    obs.SetObstacleExistScore(0.5f);
    obs.SetPosition(test_point3f);
    obs.SetRelativeVelocity(test_vector3f);
    obs.SetAcceleration(test_vector3f);
    obs.SetPositionSigma(test_point3f);
    obs.SetRelativeVelocitySigma(test_vector3f);
    obs.SetAccelerationSigma(test_vector3f);
    obs.SetMotionStatus(MotionStatus::MOVING);
    obs.SetImageBBox2D(Box2f(test_point2f, holo::geometry::Point2f(2.0f, 3.0f)));
    obs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    obs.SetCutInCutOut(CutInCutOut::HOST_CUT_IN_LEFT);
    holo::container::Vector<holo::vision::KeyPoint2f, 8U> expected_kps;
    for (size_t i = 0; i < 2; ++i)
    {
        holo::vision::KeyPoint2f kp(static_cast<holo::float32_t>(i), static_cast<holo::float32_t>(i), 0.5f, true);
        expected_kps.push_back(kp);
    }
    obs.SetKeyPoints2D(expected_kps);

    ASSERT_EQ(obs.GetTimestamp(), Timestamp(1U, 0U));
    ASSERT_EQ(obs.GetCoordinate(), Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    ASSERT_EQ(obs.GetObstacleId(), 10U);
    ASSERT_EQ(obs.GetSensorId(), sensor_id);
    ASSERT_EQ(obs.GetClassification(),
              Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    ASSERT_NEAR(obs.GetObstacleExistScore(), 0.5f, tolf);
    ASSERT_EQ(obs.GetPosition(), test_point3f);
    ASSERT_EQ(obs.GetRelativeVelocity(), test_vector3f);
    ASSERT_EQ(obs.GetAcceleration(), test_vector3f);
    ASSERT_EQ(obs.GetPositionSigma(), test_point3f);
    ASSERT_EQ(obs.GetRelativeVelocitySigma(), test_vector3f);
    ASSERT_EQ(obs.GetAccelerationSigma(), test_vector3f);
    ASSERT_EQ(obs.GetMotionStatus(), MotionStatus::MOVING);
    ASSERT_EQ(obs.GetImageBBox2D(), Box2f(test_point2f, holo::geometry::Point2f(2.0f, 3.0f)));
    ASSERT_EQ(obs.GetObstacleBBox3D(), Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    ASSERT_EQ(obs.GetCutInCutOut(), CutInCutOut::HOST_CUT_IN_LEFT);
    ASSERT_EQ(obs.GetKeyPoints2DSize(), 2);
    holo::container::Vector<holo::vision::KeyPoint2f, 8U> returned_kps = obs.GetKeyPoints2D();
    for (size_t i = 0; i < returned_kps.size(); ++i)
    {
        ASSERT_EQ(expected_kps[i], returned_kps[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleVisionT, CopyConstructor)
{
    obstacle::ObstacleVisionT<float32_t, 8U> rhs;
    SensorId                             sensor_id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::TOP_MOST));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetRelativeVelocity(test_vector3f);
    rhs.SetAcceleration(test_vector3f);
    rhs.SetPositionSigma(test_point3f);
    rhs.SetRelativeVelocitySigma(test_vector3f);
    rhs.SetAccelerationSigma(test_vector3f);
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetImageBBox2D(Box2f(test_point2f, holo::geometry::Point2f(2.0f, 3.0f)));
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetCutInCutOut(CutInCutOut::HOST_CUT_IN_LEFT);
    holo::container::Vector<holo::vision::KeyPoint2f, 8U> expected_kps;
    for (size_t i = 0; i < 2; ++i)
    {
        holo::vision::KeyPoint2f kp(static_cast<holo::float32_t>(i), static_cast<holo::float32_t>(i), 0.5f, true);
        expected_kps.push_back(kp);
    }
    rhs.SetKeyPoints2D(expected_kps);

    obstacle::ObstacleVisionT<float32_t, 8U> lhs(rhs);

    ASSERT_EQ(lhs.GetTimestamp(), rhs.GetTimestamp());
    ASSERT_EQ(lhs.GetCoordinate(), rhs.GetCoordinate());
    ASSERT_EQ(lhs.GetObstacleId(), rhs.GetObstacleId());
    ASSERT_EQ(lhs.GetSensorId(), rhs.GetSensorId());
    ASSERT_EQ(lhs.GetClassification(), rhs.GetClassification());
    ASSERT_NEAR(lhs.GetObstacleExistScore(), rhs.GetObstacleExistScore(), tolf);
    ASSERT_EQ(lhs.GetPosition(), rhs.GetPosition());
    ASSERT_EQ(lhs.GetRelativeVelocity(), rhs.GetRelativeVelocity());
    ASSERT_EQ(lhs.GetAcceleration(), rhs.GetAcceleration());
    ASSERT_EQ(lhs.GetPositionSigma(), rhs.GetPositionSigma());
    ASSERT_EQ(lhs.GetRelativeVelocitySigma(), rhs.GetRelativeVelocitySigma());
    ASSERT_EQ(lhs.GetAccelerationSigma(), rhs.GetAccelerationSigma());
    ASSERT_EQ(lhs.GetMotionStatus(), rhs.GetMotionStatus());
    ASSERT_EQ(lhs.GetImageBBox2D(), rhs.GetImageBBox2D());
    ASSERT_EQ(lhs.GetObstacleBBox3D(), rhs.GetObstacleBBox3D());
    ASSERT_EQ(lhs.GetCutInCutOut(), rhs.GetCutInCutOut());
    holo::container::Vector<holo::vision::KeyPoint2f, 8U> lhs_kps = lhs.GetKeyPoints2D();
    holo::container::Vector<holo::vision::KeyPoint2f, 8U> rhs_kps = rhs.GetKeyPoints2D();
    for (size_t i = 0; i < lhs_kps.size(); ++i)
    {
        ASSERT_EQ(lhs_kps[i], rhs_kps[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleVisionT, OperatorEqual)
{
    obstacle::ObstacleVisionT<float32_t, 8U> rhs;
    SensorId                             sensor_id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::TOP_MOST));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetRelativeVelocity(test_vector3f);
    rhs.SetAcceleration(test_vector3f);
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetImageBBox2D(Box2f(test_point2f, holo::geometry::Point2f(2.0f, 3.0f)));
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetCutInCutOut(CutInCutOut::HOST_CUT_IN_LEFT);
    holo::container::Vector<holo::vision::KeyPoint2f, 8U> expected_kps;
    for (size_t i = 0; i < 2; ++i)
    {
        holo::vision::KeyPoint2f kp(static_cast<holo::float32_t>(i), static_cast<holo::float32_t>(i), 0.5f, true);
        expected_kps.push_back(kp);
    }
    rhs.SetKeyPoints2D(expected_kps);

    obstacle::ObstacleVisionT<float32_t, 8U> lhs = rhs;

    ASSERT_EQ(lhs.GetTimestamp(), rhs.GetTimestamp());
    ASSERT_EQ(lhs.GetCoordinate(), rhs.GetCoordinate());
    ASSERT_EQ(lhs.GetObstacleId(), rhs.GetObstacleId());
    ASSERT_EQ(lhs.GetSensorId(), rhs.GetSensorId());
    ASSERT_EQ(lhs.GetClassification(), rhs.GetClassification());
    ASSERT_NEAR(lhs.GetObstacleExistScore(), rhs.GetObstacleExistScore(), tolf);
    ASSERT_EQ(lhs.GetPosition(), rhs.GetPosition());
    ASSERT_EQ(lhs.GetRelativeVelocity(), rhs.GetRelativeVelocity());
    ASSERT_EQ(lhs.GetAcceleration(), rhs.GetAcceleration());
    ASSERT_EQ(lhs.GetPositionSigma(), rhs.GetPositionSigma());
    ASSERT_EQ(lhs.GetRelativeVelocitySigma(), rhs.GetRelativeVelocitySigma());
    ASSERT_EQ(lhs.GetAccelerationSigma(), rhs.GetAccelerationSigma());
    ASSERT_EQ(lhs.GetMotionStatus(), rhs.GetMotionStatus());
    ASSERT_EQ(lhs.GetImageBBox2D(), rhs.GetImageBBox2D());
    ASSERT_EQ(lhs.GetObstacleBBox3D(), rhs.GetObstacleBBox3D());
    ASSERT_EQ(lhs.GetCutInCutOut(), rhs.GetCutInCutOut());
    holo::container::Vector<holo::vision::KeyPoint2f, 8U> lhs_kps = lhs.GetKeyPoints2D();
    holo::container::Vector<holo::vision::KeyPoint2f, 8U> rhs_kps = rhs.GetKeyPoints2D();
    for (size_t i = 0; i < lhs_kps.size(); ++i)
    {
        ASSERT_EQ(lhs_kps[i], rhs_kps[i]);
    }
}

TEST(ObstacleVisionT, GetSerializedSize)
{
    obstacle::ObstacleVisionT<float32_t, 8U> obstacle_vision;
    ASSERT_EQ(196, obstacle_vision.GetSerializedSize<4U>());
    ASSERT_EQ(248, obstacle_vision.GetSerializedSize<8U>());
}

TEST(ObstacleVisionT, SerializeAndDeserialize)
{
    srand(time(0));
    obstacle::ObstacleVisionT<float32_t, 8U> input_obstacle_vision, output_obstacle_vision;
    input_obstacle_vision.SetTimestamp(holo::Timestamp(300U, 100U));
    input_obstacle_vision.SetCoordinate(Coordinate(Coordinate::BODY));  // COORD_BODY
    input_obstacle_vision.SetObstacleId(3U);
    input_obstacle_vision.SetSensorId(SensorId(15U));
    input_obstacle_vision.SetClassification(
        Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::ANIMAL_DOG));
    input_obstacle_vision.SetObstacleExistScore(90.0f);
    input_obstacle_vision.SetPosition(holo::geometry::Point3T<float32_t>(4.5f, 6.7f, 8.9f));

    input_obstacle_vision.SetRelativeVelocity(holo::Vector3f(1.5f, 2.7f, 3.9f));
    input_obstacle_vision.SetRelativeVelocitySigma(holo::Vector3f(3.5f, 3.7f, 3.9f));
    input_obstacle_vision.SetAcceleration(holo::Vector3f(2.5f, 3.7f, 4.9f));
    input_obstacle_vision.SetAccelerationSigma(holo::Vector3f(5.5f, 5.7f, 5.9f));
    input_obstacle_vision.SetPositionSigma(holo::geometry::Point3f(0.5f, 0.7f, 0.9f));
    input_obstacle_vision.SetMotionStatus(holo::MotionStatus::STATIONARY);
    holo::geometry::Pose3f pose3;
    pose3.SetTranslation(holo::geometry::Point3f(10.1f, 10.2f, 10.3f));
    holo::geometry::Rot3f rot3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    pose3.SetRotation(rot3);
    holo::geometry::Pose2f pose2;
    pose2 = holo::geometry::Pose2f(holo::geometry::Rot2f(0.3275f), holo::geometry::Point2f(1.1f, 1.2f));
    input_obstacle_vision.SetImageBBox2D(holo::geometry::Box2f(0.14f, 0.25f, pose2));
    input_obstacle_vision.SetObstacleBBox3D(holo::geometry::Box3f(0.4f, 0.5f, 0.6f, pose3));
    input_obstacle_vision.SetCutInCutOut(holo::CutInCutOut::HOST_CUT_OUT_RIGHT);

    holo::container::Vector<holo::vision::KeyPoint2f, 8U> expected_kps;
    for (size_t i = 0; i < 2; ++i)
    {
        holo::vision::KeyPoint2f kp(static_cast<holo::float32_t>(i), static_cast<holo::float32_t>(i), 0.5f, true);
        expected_kps.push_back(kp);
    }
    input_obstacle_vision.SetKeyPoints2D(expected_kps);

    uint8_t                           buffer[8192];
    holo::serialization::Serializer<> serializer(buffer, 8192);
    serializer << input_obstacle_vision;
    ASSERT_EQ(input_obstacle_vision.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_obstacle_vision;

    ASSERT_TRUE(input_obstacle_vision.GetTimestamp() == output_obstacle_vision.GetTimestamp());
    ASSERT_TRUE(input_obstacle_vision.GetCoordinate() == output_obstacle_vision.GetCoordinate());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleId() == output_obstacle_vision.GetObstacleId());
    ASSERT_TRUE(input_obstacle_vision.GetSensorId() == output_obstacle_vision.GetSensorId());
    ASSERT_TRUE(input_obstacle_vision.GetClassification() == output_obstacle_vision.GetClassification());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleExistScore() == output_obstacle_vision.GetObstacleExistScore());
    ASSERT_TRUE(input_obstacle_vision.GetPosition() == output_obstacle_vision.GetPosition());
    ASSERT_TRUE(input_obstacle_vision.GetPositionSigma() == output_obstacle_vision.GetPositionSigma());
    ASSERT_TRUE(input_obstacle_vision.GetRelativeVelocity() == output_obstacle_vision.GetRelativeVelocity());
    ASSERT_TRUE(input_obstacle_vision.GetRelativeVelocitySigma() == output_obstacle_vision.GetRelativeVelocitySigma());
    ASSERT_TRUE(input_obstacle_vision.GetAcceleration() == output_obstacle_vision.GetAcceleration());
    ASSERT_TRUE(input_obstacle_vision.GetAccelerationSigma() == output_obstacle_vision.GetAccelerationSigma());
    ASSERT_TRUE(input_obstacle_vision.GetMotionStatus() == output_obstacle_vision.GetMotionStatus());
    ASSERT_TRUE(input_obstacle_vision.GetImageBBox2D().GetWidth() ==
                output_obstacle_vision.GetImageBBox2D().GetWidth());
    ASSERT_TRUE(input_obstacle_vision.GetImageBBox2D().GetHeight() ==
                output_obstacle_vision.GetImageBBox2D().GetHeight());
    ASSERT_TRUE(input_obstacle_vision.GetImageBBox2D().GetPose().GetTranslation().GetX() ==
                output_obstacle_vision.GetImageBBox2D().GetPose().GetTranslation().GetX());
    ASSERT_TRUE(input_obstacle_vision.GetImageBBox2D().GetPose().GetTranslation().GetY() ==
                output_obstacle_vision.GetImageBBox2D().GetPose().GetTranslation().GetY());
    ASSERT_TRUE(input_obstacle_vision.GetImageBBox2D().GetPose().GetRotation().GetTheta() ==
                output_obstacle_vision.GetImageBBox2D().GetPose().GetRotation().GetTheta());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetWidth() ==
                output_obstacle_vision.GetObstacleBBox3D().GetWidth());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetHeight() ==
                output_obstacle_vision.GetObstacleBBox3D().GetHeight());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetDepth() ==
                output_obstacle_vision.GetObstacleBBox3D().GetDepth());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R00() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R00());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R01() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R01());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R02() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R01());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R10() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R10());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R11() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R11());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R12() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R12());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R20() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R20());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R21() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R21());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R22() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetRotation().R22());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetTranslation().GetX() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetTranslation().GetX());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetTranslation().GetY() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetTranslation().GetY());
    ASSERT_TRUE(input_obstacle_vision.GetObstacleBBox3D().GetPose().GetTranslation().GetZ() ==
                output_obstacle_vision.GetObstacleBBox3D().GetPose().GetTranslation().GetZ());
    ASSERT_TRUE(input_obstacle_vision.GetCutInCutOut() == output_obstacle_vision.GetCutInCutOut());
    ASSERT_TRUE(input_obstacle_vision.GetKeyPoints2DSize() == output_obstacle_vision.GetKeyPoints2DSize());
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleVisionT, ToString)
{
    obstacle::ObstacleVisionT<float32_t, 8U> rhs;
    SensorId                             sensor_id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::TOP_MOST));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetRelativeVelocity(test_vector3f);
    rhs.SetAcceleration(test_vector3f);
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetImageBBox2D(Box2f(test_point2f, holo::geometry::Point2f(2.0f, 3.0f)));
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetCutInCutOut(CutInCutOut::HOST_CUT_IN_LEFT);

    holo::container::Vector<holo::vision::KeyPoint2f, 8U> expected_kps;
    for (size_t i = 0; i < 2; ++i)
    {
        holo::vision::KeyPoint2f kp(static_cast<holo::float32_t>(i), static_cast<holo::float32_t>(i), 0.5f, true);
        expected_kps.push_back(kp);
    }
    rhs.SetKeyPoints2D(expected_kps);

    rhs.ToString();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
