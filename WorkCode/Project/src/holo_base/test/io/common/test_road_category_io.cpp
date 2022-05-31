/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_road_category_io.cpp
 * @brief unit test io utils for road_category objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-12-10
 */

#include <gtest/gtest.h>
#include <holo/common/road_category.h>
#include <holo/io/common/road_category.h>

using RoadCategory = holo::common::RoadCategory;
using LaneCategory = holo::common::LaneCategory;

TEST(RoadCategoryIO, EncodeAndDecodeRoadCategory_1)
{
    RoadCategory road_category, road_category_expected;
    road_category.SetCategoryUnknown();
    road_category.SetTagTunnel();
    road_category.SetTagToll();

    YAML::Node node;
    node["test"]           = road_category;
    road_category_expected = node["test"].as<RoadCategory>();

    EXPECT_EQ(road_category, road_category_expected);
}

TEST(RoadCategoryIO, EncodeAndDecodeRoadCategory_2)
{
    RoadCategory road_category, road_category_expected;
    road_category.SetCategoryMainRoad();
    road_category.SetTagTunnel();
    road_category.SetTagToll();

    YAML::Node node;
    node["test"]           = road_category;
    road_category_expected = node["test"].as<RoadCategory>();

    EXPECT_EQ(road_category, road_category_expected);
}

TEST(RoadCategoryIO, EncodeAndDecodeRoadCategory_3)
{
    RoadCategory road_category, road_category_expected;
    road_category.SetCategoryRamp();
    road_category.SetTagTunnel();
    road_category.SetTagToll();

    YAML::Node node;
    node["test"]           = road_category;
    road_category_expected = node["test"].as<RoadCategory>();

    EXPECT_EQ(road_category, road_category_expected);
}

TEST(RoadCategoryIO, EncodeAndDecodeRoadCategory_4)
{
    RoadCategory road_category, road_category_expected;
    road_category.SetCategoryRamp();
    road_category.SetTagTunnel();
    road_category.SetTagToll();

    YAML::Node node = YAML::Load("33554435");

    road_category_expected = node.as<RoadCategory>();

    EXPECT_EQ(road_category, road_category_expected);
}

TEST(RoadCategoryIO, EncodeAndDecodeRoadCategory_5)
{
    RoadCategory road_category, road_category_expected;
    road_category.SetCategoryRamp();
    road_category.SetTagTunnel();
    road_category.SetTagToll();

    YAML::Node node = YAML::Load("{'category':'RAMP','tags':['TUNNEL','TOLL']}");

    road_category_expected = node.as<RoadCategory>();

    EXPECT_EQ(road_category, road_category_expected);
}

TEST(RoadCategoryIO, EncodeAndDecodeRoadCategory_7)
{
    RoadCategory road_category, road_category_expected;
    road_category.SetCategoryRamp();
    road_category.SetTagTunnel();
    road_category.SetTagToll();

    YAML::Node node = YAML::Load("{'category':2,'tags':[0x01, 0x02]}");

    road_category_expected = node.as<RoadCategory>();

    EXPECT_EQ(road_category, road_category_expected);
}

TEST(RoadCategoryIO, DecodeRoadCategory)
{
    RoadCategory road_category(16777219), road_category_expected;

    YAML::Node node        = YAML::Load("16777219");
    road_category_expected = node.as<RoadCategory>();

    EXPECT_EQ(road_category, road_category_expected);
}

TEST(LaneCategoryIO, EncodeAndDecodeLaneCategory_1)
{
    LaneCategory Lane_category(33554432U), Lane_category_expected;
    Lane_category.SetCategoryUnknown();

    YAML::Node node;
    node["test"]           = Lane_category;
    Lane_category_expected = node["test"].as<LaneCategory>();

    EXPECT_EQ(Lane_category, Lane_category_expected);
}

TEST(LaneCategoryIO, EncodeAndDecodeLaneCategory_2)
{
    LaneCategory Lane_category(33554432U), Lane_category_expected;
    Lane_category.SetCategoryRegular();

    YAML::Node node;
    node["test"]           = Lane_category;
    Lane_category_expected = node["test"].as<LaneCategory>();

    EXPECT_EQ(Lane_category, Lane_category_expected);
}

TEST(LaneCategoryIO, EncodeAndDecodeLaneCategory_3)
{
    LaneCategory Lane_category(33554432U), Lane_category_expected;
    Lane_category.SetCategoryAcceleration();

    YAML::Node node;
    node["test"]           = Lane_category;
    Lane_category_expected = node["test"].as<LaneCategory>();

    EXPECT_EQ(Lane_category, Lane_category_expected);
}

TEST(LaneCategoryIO, EncodeAndDecodeLaneCategory_4)
{
    LaneCategory Lane_category(33554432U), Lane_category_expected;
    Lane_category.SetCategoryDeceleration();

    YAML::Node node;
    node["test"]           = Lane_category;
    Lane_category_expected = node["test"].as<LaneCategory>();

    EXPECT_EQ(Lane_category, Lane_category_expected);
}

TEST(LaneCategoryIO, EncodeAndDecodeLaneCategory_5)
{
    LaneCategory Lane_category(33554432U), Lane_category_expected;
    Lane_category.SetCategoryEmergency();

    YAML::Node node;
    node["test"]           = Lane_category;
    Lane_category_expected = node["test"].as<LaneCategory>();

    EXPECT_EQ(Lane_category, Lane_category_expected);
}

TEST(LaneCategoryIO, DecodeLaneCategory_1)
{
    LaneCategory Lane_category(16777219U), Lane_category_expected;

    YAML::Node node        = YAML::Load("16777219");
    Lane_category_expected = node.as<LaneCategory>();

    EXPECT_EQ(Lane_category, Lane_category_expected);
}

TEST(LaneCategoryIO, DecodeLaneCategory_2)
{
    LaneCategory Lane_category(10), Lane_category_expected;
    Lane_category.SetCategoryEmergency();

    YAML::Node node        = YAML::Load("{'tags':10, 'category':'EMERGENCY'}");
    Lane_category_expected = node.as<LaneCategory>();

    EXPECT_EQ(Lane_category, Lane_category_expected);
}

TEST(LaneCategoryIO, DecodeLaneCategory_3)
{
    LaneCategory Lane_category(10), Lane_category_expected;
    Lane_category.SetCategoryEmergency();

    YAML::Node node        = YAML::Load("{'tags':10, 'category':4}");
    Lane_category_expected = node.as<LaneCategory>();

    EXPECT_EQ(Lane_category, Lane_category_expected);
}

TEST(LaneCategoryIO, DecodeLaneCategory_4)
{
    LaneCategory Lane_category(10), Lane_category_expected;
    Lane_category.SetCategoryEmergency();

    YAML::Node node        = YAML::Load("{'tags':10, 'category':0x04}");
    Lane_category_expected = node.as<LaneCategory>();

    EXPECT_EQ(Lane_category, Lane_category_expected);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
