/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_radar.cpp
 * @brief This file implements test for ObstacleRadarT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-19
 */

#include <gtest/gtest.h>
#include <holo/obstacle/obstacle_radar.h>

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
TEST(ObstacleRadarT, DefaultConstructor)
{
    obstacle::ObstacleRadarT<float32_t> obs;
    SensorId                            sensor_id(SensorId::Category::RADAR, SensorId::Model::RADAR_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::CENTER));

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
    ASSERT_EQ(obs.GetObstacleShape(), Vector3f());
    ASSERT_EQ(obs.GetObstacleRCS(), 0.0f);

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
    obs.SetObstacleShape(Vector3f(2.0f, 3.0f, 4.0f));
    obs.SetObstacleRCS(0.5f);

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
    ASSERT_EQ(obs.GetObstacleShape(), Vector3f(2.0f, 3.0f, 4.0f));
    ASSERT_NEAR(obs.GetObstacleRCS(), 0.5f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleRadarT, CopyConstructor)
{
    obstacle::ObstacleRadarT<float32_t> rhs;
    SensorId                            sensor_id(SensorId::Category::RADAR, SensorId::Model::RADAR_UNKNOWN,
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
    rhs.SetAcceleration(test_vector3f);
    rhs.SetPositionSigma(test_point3f);
    rhs.SetRelativeVelocitySigma(test_vector3f);
    rhs.SetAccelerationSigma(test_vector3f);
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetObstacleShape(Vector3f(2.0f, 3.0f, 4.0f));
    rhs.SetObstacleRCS(0.5f);

    obstacle::ObstacleRadarT<float32_t> lhs(rhs);

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
    ASSERT_EQ(lhs.GetObstacleShape(), rhs.GetObstacleShape());
    ASSERT_NEAR(lhs.GetObstacleRCS(), rhs.GetObstacleRCS(), tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleRadarT, OperatorEqual)
{
    obstacle::ObstacleRadarT<float32_t> rhs;
    SensorId                            sensor_id(SensorId::Category::RADAR, SensorId::Model::RADAR_UNKNOWN,
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
    rhs.SetAcceleration(test_vector3f);
    rhs.SetPositionSigma(test_point3f);
    rhs.SetRelativeVelocitySigma(test_vector3f);
    rhs.SetAccelerationSigma(test_vector3f);
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetObstacleShape(Vector3f(2.0f, 3.0f, 4.0f));
    rhs.SetObstacleRCS(0.5f);

    obstacle::ObstacleRadarT<float32_t> lhs = rhs;

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
    ASSERT_EQ(lhs.GetObstacleShape(), rhs.GetObstacleShape());
    ASSERT_NEAR(lhs.GetObstacleRCS(), rhs.GetObstacleRCS(), tolf);
}

TEST(ObstacleRadarT, BasicSerializeDeserialize)
{
    obstacle::ObstacleRadarT<float32_t> radar_input, radar_output;
    SensorId                            sensor_id(SensorId::Category::RADAR, SensorId::Model::RADAR_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::CENTER));

    radar_input.SetTimestamp(Timestamp(1U, 0U));
    radar_input.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    radar_input.SetObstacleId(10U);
    radar_input.SetSensorId(sensor_id);
    radar_input.SetClassification(
        Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    radar_input.SetObstacleExistScore(0.5f);
    radar_input.SetPosition(test_point3f);
    radar_input.SetRelativeVelocity(test_vector3f);
    radar_input.SetAcceleration(test_vector3f);
    radar_input.SetPositionSigma(test_point3f);
    radar_input.SetRelativeVelocitySigma(test_vector3f);
    radar_input.SetAccelerationSigma(test_vector3f);
    radar_input.SetMotionStatus(MotionStatus::MOVING);
    radar_input.SetObstacleShape(Vector3f(2.0f, 3.0f, 4.0f));
    radar_input.SetObstacleRCS(0.5f);

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << radar_input;
    ASSERT_EQ(radar_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> radar_output;

    ASSERT_EQ(radar_input.GetTimestamp(), radar_output.GetTimestamp());
    ASSERT_EQ(radar_input.GetCoordinate(), radar_output.GetCoordinate());
    ASSERT_EQ(radar_input.GetObstacleId(), radar_output.GetObstacleId());
    ASSERT_EQ(radar_input.GetSensorId(), radar_output.GetSensorId());
    ASSERT_EQ(radar_input.GetClassification(), radar_output.GetClassification());
    ASSERT_NEAR(radar_input.GetObstacleExistScore(), radar_output.GetObstacleExistScore(), tolf);
    ASSERT_EQ(radar_input.GetPosition(), radar_output.GetPosition());
    ASSERT_EQ(radar_input.GetRelativeVelocity(), radar_output.GetRelativeVelocity());
    ASSERT_EQ(radar_input.GetAcceleration(), radar_output.GetAcceleration());
    ASSERT_EQ(radar_input.GetPositionSigma(), radar_output.GetPositionSigma());
    ASSERT_EQ(radar_input.GetRelativeVelocitySigma(), radar_output.GetRelativeVelocitySigma());
    ASSERT_EQ(radar_input.GetAccelerationSigma(), radar_output.GetAccelerationSigma());
    ASSERT_EQ(radar_input.GetMotionStatus(), radar_output.GetMotionStatus());
    ASSERT_EQ(radar_input.GetObstacleShape(), radar_output.GetObstacleShape());
    ASSERT_NEAR(radar_input.GetObstacleRCS(), radar_output.GetObstacleRCS(), tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleRadarT, ToString)
{
    obstacle::ObstacleRadarT<float32_t> rhs;
    SensorId                            sensor_id(SensorId::Category::RADAR, SensorId::Model::RADAR_UNKNOWN,
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
    rhs.SetAcceleration(test_vector3f);
    rhs.SetPositionSigma(test_point3f);
    rhs.SetRelativeVelocitySigma(test_vector3f);
    rhs.SetAccelerationSigma(test_vector3f);
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetObstacleShape(Vector3f(2.0f, 3.0f, 4.0f));
    rhs.SetObstacleRCS(0.5f);

    rhs.ToString();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
