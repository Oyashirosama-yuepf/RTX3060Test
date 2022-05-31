/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_general.cpp
 * @brief This file implements test for ObstacleGeneralT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-19
 */

#include <gtest/gtest.h>
#include <holo/obstacle/obstacle_general.h>

using namespace holo;
using holo::common::Classification;
using holo::common::Coordinate;
using holo::common::SensorId;
using holo::common::VehicleLocation;
using holo::numerics::Vector3f;

const float32_t         tolf = EpsilonT<float32_t>::value;
holo::geometry::Point3f test_point3f(1.0f, 1.0f, 1.0f);
Vector3f                test_vector3f(1.0f, 1.0f, 1.0f);

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleGeneralT, DefaultConstructor)
{
    obstacle::ObstacleGeneralT<float32_t> obs;
    SensorId                              sensor_id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_UNKNOWN,
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
    ASSERT_EQ(obs.GetAbsoluteVelocity(), Vector3f());
    ASSERT_EQ(obs.GetAcceleration(), Vector3f());
    ASSERT_EQ(obs.GetMotionStatus(), MotionStatus::UNKNOWN);
    ASSERT_EQ(obs.GetObstacleBBox3D(), Box3f());
    ASSERT_EQ(obs.GetCutInCutOut(), CutInCutOut::UNKNOWN);
    ASSERT_EQ(obs.GetNumContourPoints(), 0);

    obs.SetTimestamp(Timestamp(1U, 0U));
    obs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    obs.SetObstacleId(10U);
    obs.SetSensorId(sensor_id);
    obs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    obs.SetObstacleExistScore(0.5f);
    obs.SetPosition(test_point3f);
    obs.SetRelativeVelocity(test_vector3f);
    obs.SetAbsoluteVelocity(test_vector3f);
    obs.SetAcceleration(test_vector3f);
    obs.SetMotionStatus(MotionStatus::MOVING);
    obs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    obs.SetCutInCutOut(CutInCutOut::UNKNOWN);
    obs.SetNumContourPoints(10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < obs.GetNumContourPoints(); ++i)
    {
        in_points[i] =
            holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i), static_cast<float32_t>(i));
    }
    obs.SetContourPoints(in_points);

    ASSERT_EQ(obs.GetTimestamp(), Timestamp(1U, 0U));
    ASSERT_EQ(obs.GetCoordinate(), Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    ASSERT_EQ(obs.GetObstacleId(), 10U);
    ASSERT_EQ(obs.GetSensorId(), sensor_id);
    ASSERT_EQ(obs.GetClassification(),
              Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    ASSERT_NEAR(obs.GetObstacleExistScore(), 0.5f, tolf);
    ASSERT_EQ(obs.GetPosition(), test_point3f);
    ASSERT_EQ(obs.GetRelativeVelocity(), test_vector3f);
    ASSERT_EQ(obs.GetAbsoluteVelocity(), test_vector3f);
    ASSERT_EQ(obs.GetAcceleration(), test_vector3f);
    ASSERT_EQ(obs.GetMotionStatus(), MotionStatus::MOVING);
    ASSERT_EQ(obs.GetObstacleBBox3D(), Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    ASSERT_EQ(obs.GetCutInCutOut(), CutInCutOut::UNKNOWN);
    ASSERT_EQ(obs.GetNumContourPoints(), 10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> out_points = obs.GetContourPoints();
    for (uint32_t i = 0U; i < obs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(out_points[i], holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i),
                                                         static_cast<float32_t>(i)));
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleGeneralT, CopyConstructor)
{
    obstacle::ObstacleGeneralT<float32_t> rhs;
    SensorId                              sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::CENTER));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetRelativeVelocity(test_vector3f);
    rhs.SetAbsoluteVelocity(test_vector3f);
    rhs.SetAcceleration(test_vector3f);
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetCutInCutOut(CutInCutOut::UNKNOWN);
    rhs.SetNumContourPoints(10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < rhs.GetNumContourPoints(); ++i)
    {
        in_points[i] = holo::geometry::Point3f(float32_t(i), float32_t(i), float32_t(i));
    }
    rhs.SetContourPoints(in_points);

    obstacle::ObstacleGeneralT<float32_t> lhs(rhs);

    ASSERT_EQ(lhs.GetTimestamp(), rhs.GetTimestamp());
    ASSERT_EQ(lhs.GetCoordinate(), rhs.GetCoordinate());
    ASSERT_EQ(lhs.GetObstacleId(), rhs.GetObstacleId());
    ASSERT_EQ(lhs.GetSensorId(), rhs.GetSensorId());
    ASSERT_EQ(lhs.GetClassification(), rhs.GetClassification());
    ASSERT_NEAR(lhs.GetObstacleExistScore(), rhs.GetObstacleExistScore(), tolf);
    ASSERT_EQ(lhs.GetPosition(), rhs.GetPosition());
    ASSERT_EQ(lhs.GetRelativeVelocity(), rhs.GetRelativeVelocity());
    ASSERT_EQ(lhs.GetAbsoluteVelocity(), rhs.GetAbsoluteVelocity());
    ASSERT_EQ(lhs.GetAcceleration(), rhs.GetAcceleration());
    ASSERT_EQ(lhs.GetMotionStatus(), rhs.GetMotionStatus());
    ASSERT_EQ(lhs.GetObstacleBBox3D(), rhs.GetObstacleBBox3D());
    ASSERT_EQ(lhs.GetCutInCutOut(), rhs.GetCutInCutOut());
    ASSERT_EQ(lhs.GetNumContourPoints(), rhs.GetNumContourPoints());

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> lhs_points = lhs.GetContourPoints();
    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> rhs_points = rhs.GetContourPoints();
    for (uint32_t i = 0U; i < lhs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(lhs_points[i], rhs_points[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleGeneralT, OperatorEqual)
{
    obstacle::ObstacleGeneralT<float32_t> rhs;
    SensorId                              sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::CENTER));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetRelativeVelocity(test_vector3f);
    rhs.SetAbsoluteVelocity(test_vector3f);
    rhs.SetAcceleration(test_vector3f);
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetCutInCutOut(CutInCutOut::UNKNOWN);
    rhs.SetNumContourPoints(10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < rhs.GetNumContourPoints(); ++i)
    {
        in_points[i] =
            holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i), static_cast<float32_t>(i));
    }
    rhs.SetContourPoints(in_points);

    obstacle::ObstacleGeneralT<float32_t> lhs = rhs;

    ASSERT_EQ(lhs.GetTimestamp(), rhs.GetTimestamp());
    ASSERT_EQ(lhs.GetCoordinate(), rhs.GetCoordinate());
    ASSERT_EQ(lhs.GetObstacleId(), rhs.GetObstacleId());
    ASSERT_EQ(lhs.GetSensorId(), rhs.GetSensorId());
    ASSERT_EQ(lhs.GetClassification(), rhs.GetClassification());
    ASSERT_NEAR(lhs.GetObstacleExistScore(), rhs.GetObstacleExistScore(), tolf);
    ASSERT_EQ(lhs.GetPosition(), rhs.GetPosition());
    ASSERT_EQ(lhs.GetRelativeVelocity(), rhs.GetRelativeVelocity());
    ASSERT_EQ(lhs.GetAbsoluteVelocity(), rhs.GetAbsoluteVelocity());
    ASSERT_EQ(lhs.GetAcceleration(), rhs.GetAcceleration());
    ASSERT_EQ(lhs.GetMotionStatus(), rhs.GetMotionStatus());
    ASSERT_EQ(lhs.GetObstacleBBox3D(), rhs.GetObstacleBBox3D());
    ASSERT_EQ(lhs.GetCutInCutOut(), rhs.GetCutInCutOut());
    ASSERT_EQ(lhs.GetNumContourPoints(), rhs.GetNumContourPoints());

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> lhs_points = lhs.GetContourPoints();
    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> rhs_points = rhs.GetContourPoints();
    for (uint32_t i = 0U; i < lhs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(lhs_points[i], rhs_points[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleGeneralT, GetSerializedSize)
{
    obstacle::ObstacleGeneralT<float32_t> obs;
    ASSERT_EQ(144, obs.GetSerializedSize<4U>());
    ASSERT_EQ(176, obs.GetSerializedSize<8U>());
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleGeneralT, SerializeAndDeserialize)
{
    holo::obstacle::ObstacleGeneralT<float32_t> obstacle_general_input, obstacle_general_output;
    obstacle_general_input.SetTimestamp(holo::Timestamp(300U, 100U));
    obstacle_general_input.SetCoordinate(Coordinate(Coordinate::BODY));  // COORD_BODY
    obstacle_general_input.SetObstacleId(3U);
    obstacle_general_input.SetSensorId(SensorId(15U));
    obstacle_general_input.SetClassification(
        Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::ANIMAL_DOG));
    obstacle_general_input.SetObstacleExistScore(90.0f);
    obstacle_general_input.SetPosition(holo::geometry::Point3T<float32_t>(4.5f, 6.7f, 8.9f));

    obstacle_general_input.SetRelativeVelocity(holo::Vector3f(1.5f, 2.7f, 3.9f));
    obstacle_general_input.SetAbsoluteVelocity(holo::Vector3f(0.5f, 0.7f, 0.9f));
    obstacle_general_input.SetAcceleration(holo::Vector3f(2.5f, 3.7f, 4.9f));
    obstacle_general_input.SetMotionStatus(holo::MotionStatus::STATIONARY);
    holo::geometry::Pose3f pose3;
    pose3.SetTranslation(holo::geometry::Point3f(10.1f, 10.2f, 10.3f));
    holo::geometry::Rot3f rot3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    pose3.SetRotation(rot3);
    obstacle_general_input.SetObstacleBBox3D(holo::geometry::Box3f(0.4f, 0.5f, 0.6f, pose3));
    obstacle_general_input.SetCutInCutOut(holo::CutInCutOut::HOST_CUT_OUT_RIGHT);
    srand(time(0));
    int32_t point_cnt_f = rand() % holo::OBSTACLE_MAX_NUM_CONTOUR_POINTS;

    std::array<holo::geometry::Point3T<float32_t>, holo::OBSTACLE_MAX_NUM_CONTOUR_POINTS> contour_points_f;
    for (int32_t i = 0; i < point_cnt_f; i++)
    {
        contour_points_f[i] = holo::geometry::Point3T<float32_t>(static_cast<float32_t>(rand() % 10000),
                                                                 static_cast<float32_t>(rand() % 10000),
                                                                 static_cast<float32_t>(rand() % 10000));
    }
    obstacle_general_input.SetNumContourPoints(point_cnt_f);
    obstacle_general_input.SetContourPoints(std::move(contour_points_f));

    uint8_t                           buffer[8192];
    holo::serialization::Serializer<> serializer(buffer, 8192);
    serializer << obstacle_general_input;
    ASSERT_EQ(obstacle_general_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> obstacle_general_output;

    ASSERT_EQ(obstacle_general_input.GetTimestamp(), obstacle_general_output.GetTimestamp());
    ASSERT_EQ(obstacle_general_input.GetCoordinate(), obstacle_general_output.GetCoordinate());
    ASSERT_EQ(obstacle_general_input.GetObstacleId(), obstacle_general_output.GetObstacleId());
    ASSERT_EQ(obstacle_general_input.GetSensorId(), obstacle_general_output.GetSensorId());
    ASSERT_EQ(obstacle_general_input.GetClassification(), obstacle_general_output.GetClassification());
    ASSERT_EQ(obstacle_general_input.GetObstacleExistScore(), obstacle_general_output.GetObstacleExistScore());
    ASSERT_EQ(obstacle_general_input.GetPosition(), obstacle_general_output.GetPosition());
    ASSERT_EQ(obstacle_general_input.GetRelativeVelocity(), obstacle_general_output.GetRelativeVelocity());
    ASSERT_EQ(obstacle_general_input.GetAbsoluteVelocity(), obstacle_general_output.GetAbsoluteVelocity());
    ASSERT_EQ(obstacle_general_input.GetAcceleration(), obstacle_general_output.GetAcceleration());
    ASSERT_EQ(obstacle_general_input.GetMotionStatus(), obstacle_general_output.GetMotionStatus());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetWidth(),
              obstacle_general_output.GetObstacleBBox3D().GetWidth());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetHeight(),
              obstacle_general_output.GetObstacleBBox3D().GetHeight());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetDepth(),
              obstacle_general_output.GetObstacleBBox3D().GetDepth());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetRotation().R00(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetRotation().R00());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetRotation().R01(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetRotation().R01());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetRotation().R02(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetRotation().R01());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetRotation().R10(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetRotation().R10());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetRotation().R11(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetRotation().R11());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetRotation().R12(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetRotation().R12());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetRotation().R20(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetRotation().R20());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetRotation().R21(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetRotation().R21());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetRotation().R22(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetRotation().R22());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetTranslation().GetX(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetTranslation().GetX());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetTranslation().GetY(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetTranslation().GetY());
    ASSERT_EQ(obstacle_general_input.GetObstacleBBox3D().GetPose().GetTranslation().GetZ(),
              obstacle_general_output.GetObstacleBBox3D().GetPose().GetTranslation().GetZ());
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleGeneralT, ToString)
{
    obstacle::ObstacleGeneralT<float32_t> rhs;
    SensorId                              sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::CENTER));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetRelativeVelocity(test_vector3f);
    rhs.SetAbsoluteVelocity(test_vector3f);
    rhs.SetAcceleration(test_vector3f);
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetCutInCutOut(CutInCutOut::UNKNOWN);
    rhs.SetNumContourPoints(10U);

    rhs.ToString();
    obstacle::ObstacleGeneralT<float32_t>::Base base;
    base.ToString();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
