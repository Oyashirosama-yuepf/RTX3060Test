/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_coordinate_io.cpp
 * @brief unit test io utils for coordinate objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */
#include <yaml-cpp/yaml.h>

#include <gtest/gtest.h>
#include <holo/common/coordinate.h>
#include <holo/io/common/coordinate.h>
#include <string>

using Coordinate = holo::common::Coordinate;

TEST(coordinateIO, CoordinateSaveYaml)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::VEHICLE);
    coord.SetVehicleSensorId(50529679);

    YAML::Node node;
    node["test"]   = coord;
    coord_expected = node["test"].as<Coordinate>();

    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeCoordinate)
{
    Coordinate coord_expected;
    Coordinate coord(0x12345678);

    YAML::Node node = YAML::Load("305419896");
    coord_expected  = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));

    node           = YAML::Load("0x12345678");
    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, EncodeAndDecodeVehicle)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::VEHICLE);
    coord.SetVehicleSensorId(50529679);
    YAML::Node node;
    node["test"]   = coord;
    coord_expected = node["test"].as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeVehicle_1)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::VEHICLE);
    coord.SetVehicleSensorId(0x22c);

    YAML::Node node = YAML::Load("{'type':'VEHICLE','param':0x22c}");

    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeVehicle_2)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::VEHICLE);
    coord.SetVehicleSensorId(0x22c);

    YAML::Node node = YAML::Load("{'type':1,'param':0x22c}");
    coord_expected  = node.as<Coordinate>();

    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeVehicle_3)
{
    Coordinate coord(318966348), coord_expected;
    YAML::Node node =
        YAML::Load("{'type':1,'param':{'location':{'x':0x4,'y':0x0c,'plane':0x0a},'model':0x03,'category':0x03}}");
    coord_expected = node.as<Coordinate>();

    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, EncodeAndDecodeUTM6)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::UTM6);
    coord.SetUtmZone(100);
    coord.SetUtmSouthFlag(true);
    coord.SetUtmOffsetX(300);
    coord.SetUtmOffsetY(700);
    YAML::Node node;
    node["test"] = coord;

    coord_expected = node["test"].as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeUTM6_1)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::UTM6);
    coord.SetUtmZone(100);
    coord.SetUtmSouthFlag(true);
    coord.SetUtmOffsetX(300);
    coord.SetUtmOffsetY(700);

    YAML::Node node =
        YAML::Load("{'type':'UTM6','param':{'zone':100,'south_flag':true,'offset_x':300,'offset_y':700,}}");

    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeUTM6_2)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::UTM6);
    coord.SetUtmZone(100);
    coord.SetUtmSouthFlag(true);
    coord.SetUtmOffsetX(300);
    coord.SetUtmOffsetY(700);

    YAML::Node node = YAML::Load("{'type':'3','param':{'zone':100,'south_flag':true,'offset_x':300,'offset_y':700,}}");

    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeUTM3_1)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::UTM3);
    coord.SetUtmZone(100);
    coord.SetUtmSouthFlag(true);
    coord.SetUtmOffsetX(300);
    coord.SetUtmOffsetY(700);

    YAML::Node node =
        YAML::Load("{'type':'UTM3','param':{'zone':100,'south_flag':true,'offset_x':300,'offset_y':700,}}");

    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeUTM3_2)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::UTM3);
    coord.SetUtmZone(100);
    coord.SetUtmSouthFlag(true);
    coord.SetUtmOffsetX(300);
    coord.SetUtmOffsetY(700);

    YAML::Node node = YAML::Load("{'type':'4','param':{'zone':100,'south_flag':true,'offset_x':300,'offset_y':700,}}");

    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, EncodeAndDecodeDR)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::DR);
    coord.SetDrVersion(100);
    YAML::Node node;
    node["test"] = coord;

    coord_expected = node["test"].as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeDR_1)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::DR);
    coord.SetDrVersion(100);

    YAML::Node node = YAML::Load("{'type':'DR','param':{'version':100}}");

    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeDR_2)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::DR);
    coord.SetDrVersion(100);

    YAML::Node node = YAML::Load("{'type':5,'param':{'version':100}}");

    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, EncodeAndDecodeCUSTOM1)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::CUSTOM1);
    coord.SetParam(30);
    YAML::Node node;
    node["test"] = coord;

    coord_expected = node["test"].as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeCUSTOM1_1)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::CUSTOM1);
    coord.SetParam(100);

    YAML::Node node = YAML::Load("{'type':'CUSTOM1','param':100}");

    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeCUSTOM1_2)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::CUSTOM1);
    coord.SetParam(100);

    YAML::Node node = YAML::Load("{'type':13,'param':100}");

    coord_expected = node.as<Coordinate>();
    ASSERT_EQ(static_cast<uint32_t>(coord_expected), static_cast<uint32_t>(coord));
}

TEST(coordinateIO, DecodeCoordinateException)
{
    Coordinate coord, coord_expected;
    coord.SetType(Coordinate::Type::CUSTOM1);
    coord.SetParam(100);

    YAML::Node node = YAML::Load("{'type':'13?','param':100}");
    
    EXPECT_THROW(node.as<Coordinate>(), YAML::BadConversion);
}

TEST(coordinateIO, DecodeCoordinateException_2)
{
    Coordinate coord_expected;
    YAML::Node node = YAML::Load("{'type11':'CUSTOM1','param':100}");

    try
    {
        coord_expected = node.as<Coordinate>();
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
