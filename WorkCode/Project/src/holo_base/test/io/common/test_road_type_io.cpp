/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_road_type_io.cpp
 * @brief unit test io utils for road_type objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/common/road_type.h>
#include <holo/io/common/road_type.h>

using RoadType = holo::common::RoadType;
using LaneType = holo::common::LaneType;

TEST(RoadTypeIO, EncodeAndDecodeRoadType_1)
{
    RoadType road_type, road_type_expected;
    road_type.SetTypeUnknown();
    road_type.SetTagTunnel();
    road_type.SetTagToll();

    YAML::Node node;
    node["test"]       = road_type;
    road_type_expected = node["test"].as<RoadType>();

    EXPECT_EQ(road_type, road_type_expected);
}

TEST(RoadTypeIO, EncodeAndDecodeRoadType_2)
{
    RoadType road_type, road_type_expected;
    road_type.SetTypeMainRoad();
    road_type.SetTagTunnel();
    road_type.SetTagToll();

    YAML::Node node;
    node["test"]       = road_type;
    road_type_expected = node["test"].as<RoadType>();

    EXPECT_EQ(road_type, road_type_expected);
}

TEST(RoadTypeIO, EncodeAndDecodeRoadType_3)
{
    RoadType road_type, road_type_expected;
    road_type.SetTypeRamp();
    road_type.SetTagTunnel();
    road_type.SetTagToll();

    YAML::Node node;
    node["test"]       = road_type;
    road_type_expected = node["test"].as<RoadType>();

    EXPECT_EQ(road_type, road_type_expected);
}

TEST(RoadTypeIO, EncodeAndDecodeRoadType_4)
{
    RoadType road_type, road_type_expected;
    road_type.SetTypeRamp();
    road_type.SetTagTunnel();
    road_type.SetTagToll();

    YAML::Node node = YAML::Load("33554435");

    road_type_expected = node.as<RoadType>();

    EXPECT_EQ(road_type, road_type_expected);
}

TEST(RoadTypeIO, EncodeAndDecodeRoadType_5)
{
    RoadType road_type, road_type_expected;
    road_type.SetTypeRamp();
    road_type.SetTagTunnel();
    road_type.SetTagToll();

    YAML::Node node = YAML::Load("{'type':'RAMP','tags':['TUNNEL','TOLL']}");

    road_type_expected = node.as<RoadType>();

    EXPECT_EQ(road_type, road_type_expected);
}

TEST(RoadTypeIO, EncodeAndDecodeRoadType_7)
{
    RoadType road_type, road_type_expected;
    road_type.SetTypeRamp();
    road_type.SetTagTunnel();
    road_type.SetTagToll();

    YAML::Node node = YAML::Load("{'type':2,'tags':[0x01, 0x02]}");

    road_type_expected = node.as<RoadType>();

    EXPECT_EQ(road_type, road_type_expected);
}

TEST(RoadTypeIO, DecodeRoadType)
{
    RoadType road_type(16777219), road_type_expected;

    YAML::Node node    = YAML::Load("16777219");
    road_type_expected = node.as<RoadType>();

    EXPECT_EQ(road_type, road_type_expected);
}

TEST(LaneTypeIO, EncodeAndDecodeLaneType_1)
{
    LaneType lane_type(33554432U), lane_type_expected;
    lane_type.SetTypeUnknown();

    YAML::Node node;
    node["test"]       = lane_type;
    lane_type_expected = node["test"].as<LaneType>();

    EXPECT_EQ(lane_type, lane_type_expected);
}

TEST(LaneTypeIO, EncodeAndDecodeLaneType_2)
{
    LaneType lane_type(33554432U), lane_type_expected;
    lane_type.SetTypeRegular();

    YAML::Node node;
    node["test"]       = lane_type;
    lane_type_expected = node["test"].as<LaneType>();

    EXPECT_EQ(lane_type, lane_type_expected);
}

TEST(LaneTypeIO, EncodeAndDecodeLaneType_3)
{
    LaneType lane_type(33554432U), lane_type_expected;
    lane_type.SetTypeAcceleration();

    YAML::Node node;
    node["test"]       = lane_type;
    lane_type_expected = node["test"].as<LaneType>();

    EXPECT_EQ(lane_type, lane_type_expected);
}

TEST(LaneTypeIO, EncodeAndDecodeLaneType_4)
{
    LaneType lane_type(33554432U), lane_type_expected;
    lane_type.SetTypeDeceleration();

    YAML::Node node;
    node["test"]       = lane_type;
    lane_type_expected = node["test"].as<LaneType>();

    EXPECT_EQ(lane_type, lane_type_expected);
}

TEST(LaneTypeIO, EncodeAndDecodeLaneType_5)
{
    LaneType lane_type(33554432U), lane_type_expected;
    lane_type.SetTypeEmergency();

    YAML::Node node;
    node["test"]       = lane_type;
    lane_type_expected = node["test"].as<LaneType>();

    EXPECT_EQ(lane_type, lane_type_expected);
}

TEST(LaneTypeIO, DecodeLaneType_1)
{
    LaneType lane_type(16777219U), lane_type_expected;

    YAML::Node node    = YAML::Load("16777219");
    lane_type_expected = node.as<LaneType>();

    EXPECT_EQ(lane_type, lane_type_expected);
}

TEST(LaneTypeIO, DecodeLaneType_2)
{
    LaneType lane_type(10), lane_type_expected;
    lane_type.SetTypeEmergency();

    YAML::Node node    = YAML::Load("{'tags':10, 'type':'EMERGENCY'}");
    lane_type_expected = node.as<LaneType>();

    EXPECT_EQ(lane_type, lane_type_expected);
}

TEST(LaneTypeIO, DecodeLaneType_3)
{
    LaneType lane_type(10), lane_type_expected;
    lane_type.SetTypeEmergency();

    YAML::Node node    = YAML::Load("{'tags':10, 'type':4}");
    lane_type_expected = node.as<LaneType>();

    EXPECT_EQ(lane_type, lane_type_expected);
}

TEST(LaneTypeIO, DecodeLaneType_4)
{
    LaneType lane_type(10), lane_type_expected;
    lane_type.SetTypeEmergency();

    YAML::Node node    = YAML::Load("{'tags':10, 'type':0x04}");
    lane_type_expected = node.as<LaneType>();

    EXPECT_EQ(lane_type, lane_type_expected);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
