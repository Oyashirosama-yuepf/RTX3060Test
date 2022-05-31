/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_list.cpp
 * @brief This file test ObstaclePtrListT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-28
 */

#include <gtest/gtest.h>

#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>

using namespace holo;
using holo::common::Classification;
using holo::common::Coordinate;
using holo::common::PerceptionAbility;
using holo::common::SensorId;
using holo::common::Timestamp;
using holo::common::VehicleLocation;

const float32_t          tolf = EpsilonT<float32_t>::value;
holo::geometry::Point3f  test_point3f(1.0f, 1.0f, 1.0f);
holo::numerics::Vector3f test_vector3f(1.0f, 1.0f, 1.0f);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TestObstaclePtrListT, Constructor)
{
    // type define
    const std::size_t            OBSTACLE_LIST_SIZE = holo::obstacle::GENERAL_OBSTACLE_LIST_COMMON_CAPACITY;
    holo::ObstacleGeneralPtrList obstacle_ptr_list;

    ASSERT_EQ(obstacle_ptr_list.GetTimestamp(), Timestamp());
    ASSERT_EQ(obstacle_ptr_list.GetCoordinate(), Coordinate(Coordinate::UNKNOWN));  // COORD_UNKNOWN
    ASSERT_EQ(obstacle_ptr_list.GetSensorId(), SensorId());
    ASSERT_EQ(obstacle_ptr_list.GetSize(), 0U);
    ASSERT_EQ(obstacle_ptr_list.GetPerceptionAbility(), 0U);
    ASSERT_EQ(obstacle_ptr_list.GetCapacity(), OBSTACLE_LIST_SIZE);

    // member define
    Timestamp         timestamp(1U, 0U);
    Coordinate        coord = Coordinate::Utm6Coordinate(50U, false);  // COORD_WORLD
    SensorId          sensor_id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_UNKNOWN,
                       VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::TOP_MOST));
    PerceptionAbility perception_ability(1U);
    std::array<std::shared_ptr<obstacle::ObstacleGeneralT<float32_t>>, OBSTACLE_LIST_SIZE> obstacle_array;
    for (size_t i = 0UL; i < OBSTACLE_LIST_SIZE; ++i)
    {
        obstacle_array[i] = nullptr;
    }

    // construct ObstacleGeneralT
    obstacle::ObstacleGeneralT<float32_t> obs;
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
    obs.SetObstacleBBox3D(holo::geometry::Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    obs.SetCutInCutOut(CutInCutOut::UNKNOWN);
    obs.SetNumContourPoints(10U);
    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> in_points;
    for (uint32_t i = 0U; i < obs.GetNumContourPoints(); ++i)
    {
        in_points[i] =
            holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i), static_cast<float32_t>(i));
    }
    obs.SetContourPoints(in_points);

    obstacle_array[0] = std::make_shared<obstacle::ObstacleGeneralT<float32_t>>(obs);
    obstacle_array[1] = std::make_shared<obstacle::ObstacleGeneralT<float32_t>>(obs);

    // set members for ObstaclePtrListT
    obstacle_ptr_list.SetTimestamp(timestamp);
    obstacle_ptr_list.SetCoordinate(coord);
    obstacle_ptr_list.SetSensorId(sensor_id);
    obstacle_ptr_list.SetSize(2U);
    obstacle_ptr_list.SetPerceptionAbility(perception_ability);
    obstacle_ptr_list.SetObstacleList(obstacle_array);

    std::array<std::shared_ptr<obstacle::ObstacleGeneralT<float32_t>>, OBSTACLE_LIST_SIZE>& obstacle_array_ret =
        obstacle_ptr_list.GetObstacleList();
    std::shared_ptr<obstacle::ObstacleGeneralT<float32_t>> obstacle_ptr = obstacle_array_ret[0];

    ASSERT_EQ(obstacle_ptr_list.GetTimestamp(), timestamp);
    ASSERT_EQ(obstacle_ptr_list.GetCoordinate(), coord);
    ASSERT_EQ(obstacle_ptr_list.GetSensorId(), sensor_id);
    ASSERT_EQ(obstacle_ptr_list.GetSize(), 2U);
    ASSERT_EQ(obstacle_ptr_list.GetPerceptionAbility(), 1U);
    ASSERT_EQ(obstacle_ptr_list.GetCapacity(), OBSTACLE_LIST_SIZE);

    ASSERT_EQ(obstacle_ptr->GetTimestamp(), Timestamp(1U, 0U));
    ASSERT_EQ(obstacle_ptr->GetCoordinate(), Coordinate::Utm6Coordinate(50U, false));  // COORD_WORLD
    ASSERT_EQ(obstacle_ptr->GetObstacleId(), 10U);
    ASSERT_EQ(obstacle_ptr->GetSensorId(), sensor_id);
    ASSERT_EQ(obstacle_ptr->GetClassification(),
              Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN));
    ASSERT_NEAR(obstacle_ptr->GetObstacleExistScore(), 0.5f, tolf);
    ASSERT_EQ(obstacle_ptr->GetPosition(), test_point3f);
    ASSERT_EQ(obstacle_ptr->GetRelativeVelocity(), test_vector3f);
    ASSERT_EQ(obstacle_ptr->GetAbsoluteVelocity(), test_vector3f);
    ASSERT_EQ(obstacle_ptr->GetAcceleration(), test_vector3f);
    ASSERT_EQ(obstacle_ptr->GetMotionStatus(), MotionStatus::MOVING);
    ASSERT_EQ(obstacle_ptr->GetObstacleBBox3D(),
              holo::geometry::Box3f(test_point3f, holo::geometry::Point3f(2.0f, 3.0f, 4.0f)));
    ASSERT_EQ(obstacle_ptr->GetCutInCutOut(), CutInCutOut::UNKNOWN);
    ASSERT_EQ(obstacle_ptr->GetNumContourPoints(), 10U);

    std::array<holo::geometry::Point3f, OBSTACLE_MAX_NUM_CONTOUR_POINTS> out_points = obstacle_ptr->GetContourPoints();
    for (uint32_t i = 0U; i < obs.GetNumContourPoints(); ++i)
    {
        ASSERT_EQ(out_points[i], holo::geometry::Point3f(static_cast<float32_t>(i), static_cast<float32_t>(i),
                                                         static_cast<float32_t>(i)));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
