/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_sensor_id_io.cpp
 * @brief unit test io utils for sensor_id objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/common/sensor_id.h>
#include <holo/io/common/sensor_id.h>

using SensorId        = holo::common::SensorId;
using VehicleLocation = holo::common::VehicleLocation;

TEST(SensorIdIO, EncodeAndDecodeSensorId)
{
    VehicleLocation location = VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                               VehicleLocation::Location::TOP_MOST);

    SensorId id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_BOSCH_MPC, location);
    SensorId id_expected;

    YAML::Node node;
    node["test"] = id;
    id_expected  = node["test"].as<SensorId>();

    ASSERT_EQ(static_cast<uint32_t>(id_expected), static_cast<uint32_t>(id));
}

TEST(SensorIdIO, DecodeSensorId_1)
{
    VehicleLocation location = VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                               VehicleLocation::Location::TOP_MOST);

    SensorId id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_BOSCH_MPC, location);
    SensorId id_expected;

    YAML::Node node = YAML::Load(
        "{'location':{'x':'CENTER','y':'TOP_MOST','plane':'FRONT_WINDOW'},'model':'CAMERA_BOSCH_MPC','category':'CAMERA'}");
    id_expected = node.as<SensorId>();

    ASSERT_EQ(static_cast<uint32_t>(id_expected), static_cast<uint32_t>(id));
}

TEST(SensorIdIO, DecodeSensorId_2)
{
    VehicleLocation location = VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                               VehicleLocation::Location::TOP_MOST);

    SensorId id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_BOSCH_MPC, location);
    SensorId id_expected;

    YAML::Node node = YAML::Load("{'location':{'x':0x8,'y':0xf,'plane':0x05},'model':0x03,'category':0x03}");
    id_expected     = node.as<SensorId>();

    ASSERT_EQ(static_cast<uint32_t>(id_expected), static_cast<uint32_t>(id));
}

TEST(SensorIdIO, DecodeSensorId_3)
{
    VehicleLocation location = VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                               VehicleLocation::Location::TOP_MOST);

    SensorId id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_BOSCH_MPC, location);
    SensorId id_expected;

    YAML::Node node = YAML::Load("{'location':{'x':0x8,'y':0xf,'plane':0x05},'model':0x03,'category':0x03}");
    id_expected     = node.as<SensorId>();

    ASSERT_EQ(static_cast<uint32_t>(id_expected), static_cast<uint32_t>(id));
}

TEST(SensorIdIO, DecodeSensorId_4)
{
    SensorId id_expected;
    YAML::Node node = YAML::Load("312");
    id_expected = node.as<SensorId>();
}

TEST(SensorIdIO, DecodeSensorIdException)
{
    VehicleLocation location = VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                               VehicleLocation::Location::TOP_MOST);

    SensorId id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_BOSCH_MPC, location);
    SensorId id_expected;

    YAML::Node node = YAML::Load("{'location':{'x':0x4,'y':0x0c,'plane':0x0a},'model':'XXXX','category':0x03}");
    
    EXPECT_THROW(node.as<SensorId>(), YAML::BadConversion);
}

TEST(SensorIdIO, DecodeSensorIdException_2)
{
    SensorId id_expected;
    YAML::Node node = YAML::Load("{'model':'XXXX','category':0x03}");

    try
    {
        id_expected = node.as<SensorId>();
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
