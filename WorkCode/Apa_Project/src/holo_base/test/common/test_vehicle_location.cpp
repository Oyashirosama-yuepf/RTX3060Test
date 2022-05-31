/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_vehicle_location.cpp
 * @brief Unit test for VehicleLocation object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-11
 */

#include <gtest/gtest.h>
#include <holo/common/vehicle_location.h>

using VehicleLocation = holo::common::VehicleLocation;

TEST(VehicleLocation, ConstructDefault)
{
    VehicleLocation location;
    ASSERT_EQ(VehicleLocation::Plane::UNKNOWN, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location.GetLocationY());
}

TEST(VehicleLocation, ConstructWithUint16)
{
    VehicleLocation location(0x01CC);
    ASSERT_EQ(VehicleLocation::Plane::FRONT, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::TOP, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::TOP, location.GetLocationY());

    VehicleLocation location2 = 0x0288; //implicit call
    ASSERT_EQ(VehicleLocation::Plane::REAR, location2.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::MIDDLE, location2.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::CENTER, location2.GetLocationY());
}

TEST(VehicleLocation, ConstructWithAllParams)
{
    VehicleLocation location(VehicleLocation::Plane::ROOF, 
                             VehicleLocation::Location::LEFT, 
                             VehicleLocation::Location::FRONT);
    ASSERT_EQ(VehicleLocation::Plane::ROOF, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::LEFT, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::FRONT, location.GetLocationY());


    VehicleLocation location2(VehicleLocation::Plane::CHASSIS, 
                              VehicleLocation::Location::CENTER);
    ASSERT_EQ(VehicleLocation::Plane::CHASSIS, location2.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::CENTER, location2.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location2.GetLocationY());

    VehicleLocation location3(VehicleLocation::Plane::TRUNK);
    ASSERT_EQ(VehicleLocation::Plane::TRUNK, location3.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location3.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location3.GetLocationY());
}

TEST(VehicleLocation, AssignOperatorUint16)
{
    VehicleLocation location;
    location = 0x01CCU;
    ASSERT_EQ(VehicleLocation::Plane::FRONT, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::TOP, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::TOP, location.GetLocationY());

    VehicleLocation location2;
    location2 = 0x0288U;
    ASSERT_EQ(VehicleLocation::Plane::REAR, location2.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::MIDDLE, location2.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::CENTER, location2.GetLocationY());
}

TEST(VehicleLocation, CastOperatorUint16)
{
    VehicleLocation location = 0x01CC;
    ASSERT_EQ(VehicleLocation::Plane::FRONT, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::TOP, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::TOP, location.GetLocationY());
    ASSERT_EQ(0x01CC, static_cast<uint16_t>(location));
    // implicit cast
    ASSERT_EQ(0x01CC, location);
}

TEST(VehicleLocation, SetGetPlane)
{
    VehicleLocation location;
    ASSERT_EQ(VehicleLocation::Plane::UNKNOWN, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location.GetLocationY());

    location.SetPlane(VehicleLocation::Plane::FRONT_WINDOW);
    ASSERT_EQ(VehicleLocation::Plane::FRONT_WINDOW, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location.GetLocationY());
}

TEST(VehicleLocation, SetGetLocation)
{
    VehicleLocation location;
    ASSERT_EQ(VehicleLocation::Plane::UNKNOWN, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::UNKNOWN, location.GetLocationY());

    location.SetLocation(VehicleLocation::Location::RIGHT, VehicleLocation::Location::CENTER);
    ASSERT_EQ(VehicleLocation::Plane::UNKNOWN, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::RIGHT, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::CENTER, location.GetLocationY());

    location.SetLocationX(VehicleLocation::Location::LEFT);
    ASSERT_EQ(VehicleLocation::Plane::UNKNOWN, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::LEFT, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::CENTER, location.GetLocationY());

    location.SetLocationY(VehicleLocation::Location::FRONT);
    ASSERT_EQ(VehicleLocation::Plane::UNKNOWN, location.GetPlane());
    ASSERT_EQ(VehicleLocation::Location::LEFT, location.GetLocationX());
    ASSERT_EQ(VehicleLocation::Location::FRONT, location.GetLocationY());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

