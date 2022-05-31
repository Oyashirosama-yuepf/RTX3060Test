/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_sensor_id.cpp
 * @brief Unit test for SensorId object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-11
 */

#include <gtest/gtest.h>
#include <holo/common/sensor_id.h>
#include <holo/common/vehicle_location.h>

using holo::common::VehicleLocation;
using holo::common::SensorId;

TEST(SensorId, ConstructDefault)
{
    SensorId id;
    ASSERT_EQ(SensorId::Category::UNKNOWN, id.GetCategory());
    ASSERT_EQ(SensorId::Model::UNKNOWN, id.GetModel());
    ASSERT_EQ(VehicleLocation(), id.GetLocation());
    ASSERT_EQ(0U, id);
}

TEST(SensorId, ConstructFromUint32)
{
    SensorId id(0U);
    ASSERT_EQ(SensorId::Category::UNKNOWN, id.GetCategory());
    ASSERT_EQ(SensorId::Model::UNKNOWN, id.GetModel());
    ASSERT_EQ(VehicleLocation(), id.GetLocation());
    ASSERT_EQ(0U, id);

    SensorId id2(0x01020304U);
    ASSERT_EQ(SensorId::Category::GNSS, id2.GetCategory());
    ASSERT_EQ(SensorId::Model::GNSS_XSENS, id2.GetModel());
    ASSERT_EQ(0x0304, id2.GetLocation());
    ASSERT_EQ(0x01020304U, id2);

    SensorId id3 = 0x02030405U;
    ASSERT_EQ(SensorId::Category::IMU, id3.GetCategory());
    ASSERT_EQ(SensorId::Model::GNSS_UBLOX_M8L, id3.GetModel());
    ASSERT_EQ(0x0405, id3.GetLocation());
    ASSERT_EQ(0x02030405U, id3);
}

TEST(SensorId, ConstructFromCatModelLoc)
{
    VehicleLocation location = VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW,
                                               VehicleLocation::Location::CENTER,
                                               VehicleLocation::Location::TOP_MOST);
    SensorId id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_BOSCH_MPC, location);

    ASSERT_EQ(SensorId::Category::CAMERA, id.GetCategory());
    ASSERT_EQ(SensorId::Model::CAMERA_BOSCH_MPC, id.GetModel());
    ASSERT_EQ(location, id.GetLocation());
    ASSERT_EQ(0x0303058FU, id);
}

TEST(SensorId, AssignUint32)
{
    SensorId id;
    id = 0x12345678;
    ASSERT_EQ(0x02345678U, id);
}

TEST(SensorId, CastUint32)
{
    VehicleLocation location = VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW,
                                               VehicleLocation::Location::CENTER,
                                               VehicleLocation::Location::TOP_MOST);
    SensorId id(SensorId::Category::CAMERA, SensorId::Model::CAMERA_BOSCH_MPC, location);

    uint32_t value = id;
    ASSERT_EQ(0x0303058FU, value);
}

TEST(SensorId, SetGetLocation)
{
    SensorId id;
    ASSERT_EQ(SensorId::Category::UNKNOWN, id.GetCategory());
    ASSERT_EQ(SensorId::Model::UNKNOWN, id.GetModel());
    ASSERT_EQ(VehicleLocation(), id.GetLocation());

    id.SetLocation(0x1234);
    ASSERT_EQ(0x1234, id.GetLocation());

    id.GetLocation() = 0x4321;
    ASSERT_EQ(0x4321, id.GetLocation());

    SensorId const id2(0x01020304);
    ASSERT_EQ(0x0304, id2.GetLocation());
}

TEST(SensorId, SetGetModel)
{
    SensorId id;
    ASSERT_EQ(SensorId::Category::UNKNOWN, id.GetCategory());
    ASSERT_EQ(SensorId::Model::UNKNOWN, id.GetModel());
    ASSERT_EQ(VehicleLocation(), id.GetLocation());

    id.SetModel(SensorId::Model::IMU_ACEINNA_305);
    ASSERT_EQ(SensorId::Model::IMU_ACEINNA_305, id.GetModel());
}

TEST(SensorId, SetGetCategory)
{
    SensorId id;
    ASSERT_EQ(SensorId::Category::UNKNOWN, id.GetCategory());
    ASSERT_EQ(SensorId::Model::UNKNOWN, id.GetModel());
    ASSERT_EQ(VehicleLocation(), id.GetLocation());

    id.SetCategory(SensorId::Category::USS);
    ASSERT_EQ(SensorId::Category::USS, id.GetCategory());
}

TEST(SensorId, GetSerializedSize)
{
    SensorId id;
    ASSERT_EQ(4, id.GetSerializedSize<4U>());
    ASSERT_EQ(4, id.GetSerializedSize<8U>());
}

TEST(SensorId, SerializeAndDeserialize)
{
    SensorId id_input(0x01020304);
    SensorId id_output(0x01020304);

    uint8_t buffer[1024];
    holo::serialization::Serializer<>          serializer(buffer, 1024);
    serializer << id_input;
    ASSERT_EQ(id_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> id_output;

    ASSERT_EQ(id_input, id_output);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

