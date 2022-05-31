/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_vehicle_location_io.cpp
 * @brief unit test io utils for vehicle_location objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-14
 */

#include <gtest/gtest.h>
#include <holo/common/vehicle_location.h>
#include <holo/io/common/vehicle_location.h>
#include <yaml-cpp/yaml.h>

using VehicleLocation = holo::common::VehicleLocation;

TEST(VehicleLocationIO, EncodeAndDecodeVehicleLocation)
{
    VehicleLocation location(VehicleLocation::Plane::ROOF, VehicleLocation::Location::LEFT,
                             VehicleLocation::Location::FRONT);
    VehicleLocation location_expected;

    YAML::Node node;
    node["test"]      = location;
    location_expected = node["test"].as<VehicleLocation>();

    ASSERT_EQ(location.GetPlane(), location_expected.GetPlane());
    ASSERT_EQ(location.GetLocationX(), location_expected.GetLocationX());
    ASSERT_EQ(location.GetLocationY(), location_expected.GetLocationY());
}

TEST(VehicleLocationIO, DecodeVehicleLocation_1)
{
    VehicleLocation location(VehicleLocation::Plane::ROOF, VehicleLocation::Location::LEFT,
                             VehicleLocation::Location::FRONT);
    VehicleLocation location_expected;

    YAML::Node node   = YAML::Load("{'x':'LEFT','y':'FRONT','plane':'ROOF'}");
    location_expected = node.as<VehicleLocation>();

    ASSERT_EQ(location.GetPlane(), location_expected.GetPlane());
    ASSERT_EQ(location.GetLocationX(), location_expected.GetLocationX());
    ASSERT_EQ(location.GetLocationY(), location_expected.GetLocationY());
}

TEST(VehicleLocationIO, DecodeVehicleLocation_2)
{
    VehicleLocation location(VehicleLocation::Plane::ROOF, VehicleLocation::Location::LEFT,
                             VehicleLocation::Location::FRONT);
    VehicleLocation location_expected;

    YAML::Node node   = YAML::Load("{'x':0x4,'y':0x0c,'plane':0x0a}");
    location_expected = node.as<VehicleLocation>();

    ASSERT_EQ(location.GetPlane(), location_expected.GetPlane());
    ASSERT_EQ(location.GetLocationX(), location_expected.GetLocationX());
    ASSERT_EQ(location.GetLocationY(), location_expected.GetLocationY());
}

TEST(VehicleLocationIO, DecodeVehicleLocationException)
{
    VehicleLocation location(VehicleLocation::Plane::ROOF, VehicleLocation::Location::LEFT,
                             VehicleLocation::Location::FRONT);
    VehicleLocation location_expected;

    YAML::Node node   = YAML::Load("{'x':0x4,'y':'0x0c?','plane':0x0a}");
    EXPECT_THROW(node.as<VehicleLocation>(), YAML::BadConversion);
}

TEST(SensorIdIO, DecodeVehicleLocationException_2)
{
    VehicleLocation location_expected;
    YAML::Node node   = YAML::Load("{'x':0x4,'plane':0x0a}");

    try
    {
        location_expected = node.as<VehicleLocation>();
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
