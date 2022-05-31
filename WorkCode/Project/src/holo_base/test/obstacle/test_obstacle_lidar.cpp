/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_lidar.cpp
 * @brief This file implements test for ObstacleLidarT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-19
 */

#include <gtest/gtest.h>
#include <holo/obstacle/obstacle_lidar.h>

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
TEST(ObstacleLidarT, DefaultConstructor)
{
    holo::obstacle::ObstacleLidarT<float32_t> obs;
    SensorId                                  sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
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
    ASSERT_EQ(obs.GetObstacleBBox3D(), Box3f());
    ASSERT_EQ(obs.GetNumLidarPoints(), 0U);
    ASSERT_EQ(obs.GetNumContourPoints(), 0U);

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
    obs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    obs.SetNumLidarPoints(100U);
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
    ASSERT_EQ(obs.GetAcceleration(), test_vector3f);
    ASSERT_EQ(obs.GetPositionSigma(), test_point3f);
    ASSERT_EQ(obs.GetRelativeVelocitySigma(), test_vector3f);
    ASSERT_EQ(obs.GetAccelerationSigma(), test_vector3f);
    ASSERT_EQ(obs.GetMotionStatus(), MotionStatus::MOVING);
    ASSERT_EQ(obs.GetObstacleBBox3D(), Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    ASSERT_EQ(obs.GetNumLidarPoints(), 100U);
    ASSERT_EQ(obs.GetNumContourPoints(), 10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> out_points = obs.GetContourPoints();
    for (uint32_t i = 0U; i < obs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(out_points[i], holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i),
                                                         static_cast<float32_t>(i)));
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleLidarT, Constructor)
{
    SensorId sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::CENTER));

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < 10; ++i)
    {
        in_points[i] =
            holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i), static_cast<float32_t>(i));
    }

    holo::obstacle::ObstacleLidarT<float32_t> obs(
        Timestamp(1U, 0U), Coordinate::Utm6Coordinate(50U, false), 10U, sensor_id,
        Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN), 0.5f, test_point3f,
        test_vector3f, test_vector3f, test_point3f, test_vector3f, test_vector3f, MotionStatus::MOVING,
        Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)), 100U, 10U, in_points);

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
    ASSERT_EQ(obs.GetObstacleBBox3D(), Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    ASSERT_EQ(obs.GetNumLidarPoints(), 100U);
    ASSERT_EQ(obs.GetNumContourPoints(), 10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> out_points = obs.GetContourPoints();
    for (uint32_t i = 0U; i < obs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(out_points[i], holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i),
                                                         static_cast<float32_t>(i)));
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleLidarT, MoveConstructor)
{
    SensorId sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::CENTER));

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < 10; ++i)
    {
        in_points[i] =
            holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i), static_cast<float32_t>(i));
    }

    holo::obstacle::ObstacleLidarT<float32_t> obs2(
        Timestamp(1U, 0U), Coordinate::Utm6Coordinate(50U, false), 10U, sensor_id,
        Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN), 0.5f, test_point3f,
        test_vector3f, test_vector3f, test_point3f, test_vector3f, test_vector3f, MotionStatus::MOVING,
        Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)), 100U, 10U, in_points);

    holo::obstacle::ObstacleLidarT<float32_t> obs(std::move(obs2));

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
    ASSERT_EQ(obs.GetObstacleBBox3D(), Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    ASSERT_EQ(obs.GetNumLidarPoints(), 100U);
    ASSERT_EQ(obs.GetNumContourPoints(), 10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> out_points = obs.GetContourPoints();
    for (uint32_t i = 0U; i < obs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(out_points[i], holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i),
                                                         static_cast<float32_t>(i)));
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleLidarT, CopyConstructor)
{
    holo::obstacle::ObstacleLidarT<float32_t> rhs;
    SensorId                                  sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
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
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetNumLidarPoints(100U);
    rhs.SetNumContourPoints(10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < rhs.GetNumContourPoints(); ++i)
    {
        in_points[i] =
            holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i), static_cast<float32_t>(i));
    }
    rhs.SetContourPoints(in_points);

    holo::obstacle::ObstacleLidarT<float32_t> lhs(rhs);

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
    ASSERT_EQ(lhs.GetObstacleBBox3D(), rhs.GetObstacleBBox3D());
    ASSERT_EQ(lhs.GetNumLidarPoints(), rhs.GetNumLidarPoints());
    ASSERT_EQ(lhs.GetNumContourPoints(), rhs.GetNumContourPoints());

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> lhs_points = lhs.GetContourPoints();
    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> rhs_points = rhs.GetContourPoints();
    for (uint32_t i = 0U; i < lhs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(lhs_points[i], rhs_points[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleLidarT, OperatorEqual)
{
    holo::obstacle::ObstacleLidarT<float32_t> rhs;
    SensorId                                  sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
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
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetNumLidarPoints(100U);
    rhs.SetNumContourPoints(10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < rhs.GetNumContourPoints(); ++i)
    {
        in_points[i] =
            holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i), static_cast<float32_t>(i));
    }
    rhs.SetContourPoints(in_points);

    holo::obstacle::ObstacleLidarT<float32_t> lhs;
    lhs = rhs;

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
    ASSERT_EQ(lhs.GetObstacleBBox3D(), rhs.GetObstacleBBox3D());
    ASSERT_EQ(lhs.GetNumLidarPoints(), rhs.GetNumLidarPoints());
    ASSERT_EQ(lhs.GetNumContourPoints(), rhs.GetNumContourPoints());

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> lhs_points = lhs.GetContourPoints();
    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> rhs_points = rhs.GetContourPoints();
    for (uint32_t i = 0U; i < lhs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(lhs_points[i], rhs_points[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleLidarT, OperatorEqualWithMove)
{
    holo::obstacle::ObstacleLidarT<float32_t> rhs;
    SensorId                                  sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
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
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetNumLidarPoints(100U);
    rhs.SetNumContourPoints(10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < rhs.GetNumContourPoints(); ++i)
    {
        in_points[i] =
            holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i), static_cast<float32_t>(i));
    }
    rhs.SetContourPoints(std::move(in_points));

    holo::obstacle::ObstacleLidarT<float32_t> lhs;
    lhs = std::move(lhs);
    lhs = std::move(rhs);

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
    ASSERT_EQ(lhs.GetObstacleBBox3D(), rhs.GetObstacleBBox3D());
    ASSERT_EQ(lhs.GetNumLidarPoints(), rhs.GetNumLidarPoints());
    ASSERT_EQ(lhs.GetNumContourPoints(), rhs.GetNumContourPoints());

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> lhs_points = lhs.GetContourPoints();
    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> rhs_points = rhs.GetContourPoints();
    for (uint32_t i = 0U; i < lhs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(lhs_points[i], rhs_points[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(ObstacleLidarT, ToString)
{
    holo::obstacle::ObstacleLidarT<float32_t> rhs;
    SensorId                                  sensor_id(SensorId::Category::LIDAR, SensorId::Model::LIDAR_UNKNOWN,
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
    rhs.SetMotionStatus(MotionStatus::MOVING);
    rhs.SetObstacleBBox3D(Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    rhs.SetNumLidarPoints(100U);
    rhs.SetNumContourPoints(10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < rhs.GetNumContourPoints(); ++i)
    {
        in_points[i] =
            holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i), static_cast<float32_t>(i));
    }
    rhs.SetContourPoints(std::move(in_points));

    rhs.ToString();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
