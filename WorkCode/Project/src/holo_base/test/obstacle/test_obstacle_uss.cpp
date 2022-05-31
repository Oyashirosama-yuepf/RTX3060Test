/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_uss.cpp
 * @brief This file implements test for ObstacleUssT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-19
 */

#include <gtest/gtest.h>
#include <holo/obstacle/obstacle_uss.h>

using namespace holo;
using holo::common::Classification;
using holo::common::Coordinate;
using holo::common::SensorId;
using holo::common::VehicleLocation;

const float32_t          tolf = EpsilonT<float32_t>::value;
holo::geometry::Point3f  test_point3f(1.0f, 1.0f, 1.0f);
holo::numerics::Vector3f test_vector3f(1.0f, 1.0f, 1.0f);

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleUssT, DefaultConstructor)
{
    ObstacleUssT<float32_t> obs;

    SensorId sensor_id(SensorId::Category::USS, SensorId::Model::USS_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER));

    ASSERT_EQ(obs.GetTimestamp(), Timestamp());
    ASSERT_EQ(obs.GetCoordinate(), Coordinate(Coordinate::UNKNOWN));
    ASSERT_EQ(obs.GetObstacleId(), 0U);
    ASSERT_EQ(obs.GetSensorId(), SensorId());
    ASSERT_EQ(obs.GetClassification(), Classification());
    ASSERT_EQ(obs.GetObstacleExistScore(), 0.0f);
    ASSERT_EQ(obs.GetPosition(), holo::geometry::Point3f());
    ASSERT_EQ(obs.GetPositionSigma(), holo::geometry::Point3f());
    ASSERT_EQ(obs.GetFov(), 0.0f);

    obs.SetTimestamp(Timestamp(1U, 0U));
    obs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    obs.SetObstacleId(10U);
    obs.SetSensorId(sensor_id);
    obs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    obs.SetObstacleExistScore(0.5f);
    obs.SetPosition(test_point3f);
    obs.SetPositionSigma(test_point3f);
    obs.SetFov(0.5f);

    ASSERT_EQ(obs.GetTimestamp(), Timestamp(1U, 0U));
    ASSERT_EQ(obs.GetCoordinate(), Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    ASSERT_EQ(obs.GetObstacleId(), 10U);
    ASSERT_EQ(sensor_id, obs.GetSensorId());
    ASSERT_EQ(obs.GetClassification(),
              Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    ASSERT_NEAR(obs.GetObstacleExistScore(), 0.5f, tolf);
    ASSERT_EQ(obs.GetPosition(), test_point3f);
    ASSERT_EQ(obs.GetPositionSigma(), test_point3f);
    ASSERT_NEAR(obs.GetFov(), 0.5f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleUssT, Constructor)
{
    SensorId                sensor_id(SensorId::Category::USS, SensorId::Model::USS_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER));
    ObstacleUssT<float32_t> obs(
        Timestamp(1U, 0U), Coordinate::Utm6Coordinate(50U, false), 10U, sensor_id,
        Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN), 0.5f, test_point3f,
        test_point3f, 0.5f);

    ASSERT_EQ(obs.GetTimestamp(), Timestamp(1U, 0U));
    ASSERT_EQ(obs.GetCoordinate(), Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    ASSERT_EQ(obs.GetObstacleId(), 10U);
    ASSERT_EQ(sensor_id, obs.GetSensorId());
    ASSERT_EQ(obs.GetClassification(),
              Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    ASSERT_NEAR(obs.GetObstacleExistScore(), 0.5f, tolf);
    ASSERT_EQ(obs.GetPosition(), test_point3f);
    ASSERT_EQ(obs.GetPositionSigma(), test_point3f);
    ASSERT_NEAR(obs.GetFov(), 0.5f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleUssT, CopyConstructor)
{
    ObstacleUssT<float32_t> rhs;
    SensorId                sensor_id(SensorId::Category::USS, SensorId::Model::USS_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetPositionSigma(test_point3f);
    rhs.SetFov(0.5f);

    ObstacleUssT<float32_t> lhs(rhs);

    ASSERT_EQ(lhs.GetTimestamp(), rhs.GetTimestamp());
    ASSERT_EQ(lhs.GetCoordinate(), rhs.GetCoordinate());
    ASSERT_EQ(lhs.GetObstacleId(), rhs.GetObstacleId());
    ASSERT_EQ(lhs.GetSensorId(), rhs.GetSensorId());
    ASSERT_EQ(lhs.GetClassification(), rhs.GetClassification());
    ASSERT_NEAR(lhs.GetObstacleExistScore(), rhs.GetObstacleExistScore(), tolf);
    ASSERT_EQ(lhs.GetPosition(), rhs.GetPosition());
    ASSERT_EQ(lhs.GetPositionSigma(), rhs.GetPositionSigma());
    ASSERT_NEAR(lhs.GetFov(), rhs.GetFov(), tolf);
}

TEST(ObstacleUssT, MoveConstructor)
{
    ObstacleUssT<float32_t> rhs;
    SensorId                sensor_id(SensorId::Category::USS, SensorId::Model::USS_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetPositionSigma(test_point3f);
    rhs.SetFov(0.5f);

    ObstacleUssT<float32_t> lhs(std::move(rhs));

    ASSERT_EQ(lhs.GetTimestamp(), rhs.GetTimestamp());
    ASSERT_EQ(lhs.GetCoordinate(), rhs.GetCoordinate());
    ASSERT_EQ(lhs.GetObstacleId(), rhs.GetObstacleId());
    ASSERT_EQ(lhs.GetSensorId(), rhs.GetSensorId());
    ASSERT_EQ(lhs.GetClassification(), rhs.GetClassification());
    ASSERT_NEAR(lhs.GetObstacleExistScore(), rhs.GetObstacleExistScore(), tolf);
    ASSERT_EQ(lhs.GetPosition(), rhs.GetPosition());
    ASSERT_EQ(lhs.GetPositionSigma(), rhs.GetPositionSigma());
    ASSERT_NEAR(lhs.GetFov(), rhs.GetFov(), tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleUssT, OperatorEqual)
{
    ObstacleUssT<float32_t> rhs;
    SensorId                sensor_id(SensorId::Category::USS, SensorId::Model::USS_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetPositionSigma(test_point3f);
    rhs.SetFov(0.5f);

    ObstacleUssT<float32_t> lhs;
    lhs = rhs;

    ASSERT_EQ(lhs.GetTimestamp(), rhs.GetTimestamp());
    ASSERT_EQ(lhs.GetCoordinate(), rhs.GetCoordinate());
    ASSERT_EQ(lhs.GetObstacleId(), rhs.GetObstacleId());
    ASSERT_EQ(lhs.GetSensorId(), rhs.GetSensorId());
    ASSERT_EQ(lhs.GetClassification(), rhs.GetClassification());
    ASSERT_NEAR(lhs.GetObstacleExistScore(), rhs.GetObstacleExistScore(), tolf);
    ASSERT_EQ(lhs.GetPosition(), rhs.GetPosition());
    ASSERT_EQ(lhs.GetPositionSigma(), rhs.GetPositionSigma());
    ASSERT_NEAR(lhs.GetFov(), rhs.GetFov(), tolf);
}

TEST(ObstacleUssT, OperatorEqualWithMove)
{
    ObstacleUssT<float32_t> rhs;
    SensorId                sensor_id(SensorId::Category::USS, SensorId::Model::USS_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetPositionSigma(test_point3f);
    rhs.SetFov(0.5f);

    ObstacleUssT<float32_t> lhs;
    lhs = std::move(lhs);
    lhs = std::move(rhs);

    ASSERT_EQ(lhs.GetTimestamp(), rhs.GetTimestamp());
    ASSERT_EQ(lhs.GetCoordinate(), rhs.GetCoordinate());
    ASSERT_EQ(lhs.GetObstacleId(), rhs.GetObstacleId());
    ASSERT_EQ(lhs.GetSensorId(), rhs.GetSensorId());
    ASSERT_EQ(lhs.GetClassification(), rhs.GetClassification());
    ASSERT_NEAR(lhs.GetObstacleExistScore(), rhs.GetObstacleExistScore(), tolf);
    ASSERT_EQ(lhs.GetPosition(), rhs.GetPosition());
    ASSERT_EQ(lhs.GetPositionSigma(), rhs.GetPositionSigma());
    ASSERT_NEAR(lhs.GetFov(), rhs.GetFov(), tolf);
}

TEST(ObstacleUssT, ToString)
{
    ObstacleUssT<float32_t> rhs;
    SensorId                sensor_id(SensorId::Category::USS, SensorId::Model::USS_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER));

    rhs.SetTimestamp(Timestamp(1U, 0U));
    rhs.SetCoordinate(Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    rhs.SetObstacleId(10U);
    rhs.SetSensorId(sensor_id);
    rhs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    rhs.SetObstacleExistScore(0.5f);
    rhs.SetPosition(test_point3f);
    rhs.SetPositionSigma(test_point3f);
    rhs.SetFov(0.5f);

    rhs.ToString();
}

TEST(ObstacleUssT, BasicSerializeDeserialize)
{
    holo::ObstacleUssT<float32_t> input_obstacle_uss, output_obstacle_uss;
    input_obstacle_uss.SetTimestamp(holo::Timestamp(300U, 100U));
    input_obstacle_uss.SetCoordinate(Coordinate(Coordinate::BODY));  // COORD_BODY
    input_obstacle_uss.SetObstacleId(3U);
    input_obstacle_uss.SetSensorId(SensorId(15U));
    input_obstacle_uss.SetClassification(
        Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::ANIMAL_DOG));
    input_obstacle_uss.SetObstacleExistScore(90.0f);
    input_obstacle_uss.SetPosition(holo::geometry::Point3T<float32_t>(4.5, 6.7, 8.9));

    input_obstacle_uss.SetPositionSigma(holo::geometry::Point3f(0.5, 0.7, 0.9));
    input_obstacle_uss.SetFov(static_cast<float32_t>(20));

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> ser(buffer, 1024);

    ser << input_obstacle_uss;

    ASSERT_EQ(input_obstacle_uss.GetSerializedSize(), ser.GetSize());

    holo::serialization::Deserializer<> des(buffer, ser.GetSize());
    des >> output_obstacle_uss;

    EXPECT_EQ(input_obstacle_uss.GetTimestamp(), output_obstacle_uss.GetTimestamp());
    EXPECT_EQ(input_obstacle_uss.GetCoordinate(), output_obstacle_uss.GetCoordinate());
    EXPECT_EQ(input_obstacle_uss.GetObstacleId(), output_obstacle_uss.GetObstacleId());
    EXPECT_EQ(input_obstacle_uss.GetSensorId(), output_obstacle_uss.GetSensorId());
    EXPECT_EQ(input_obstacle_uss.GetClassification(), output_obstacle_uss.GetClassification());
    EXPECT_EQ(input_obstacle_uss.GetObstacleExistScore(), output_obstacle_uss.GetObstacleExistScore());
    EXPECT_EQ(input_obstacle_uss.GetPosition(), output_obstacle_uss.GetPosition());
    EXPECT_EQ(input_obstacle_uss.GetPositionSigma(), output_obstacle_uss.GetPositionSigma());
    EXPECT_EQ(input_obstacle_uss.GetFov(), output_obstacle_uss.GetFov());
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
