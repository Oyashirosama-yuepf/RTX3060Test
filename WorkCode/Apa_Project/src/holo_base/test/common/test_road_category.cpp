/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_road_category.cpp
 * @brief Unit test for road category and lane tag.
 * @author lisong(lisong@holomaitc.com)
 * @date "2021-12-10"
 */

#include <gtest/gtest.h>

#include <holo/common/road_category.h>

using Serializer   = holo::serialization::Serializer<false, 4>;
using Deserializer = holo::serialization::Deserializer<false, 4>;

using holo::common::RoadCategory;

// For RoadCategory
TEST(RoadCategory, TestDefaultConstructor)
{
    RoadCategory road_category;
    EXPECT_EQ(road_category.GetValue(), 0U);
    EXPECT_EQ(road_category.IsCategoryUnknown(), true);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), false);
    EXPECT_EQ(road_category.HasTagToll(), false);
}

TEST(RoadCategory, TestConstructorWithParameters)
{
    RoadCategory road_category{16777219U};
    EXPECT_EQ(road_category.GetValue(), 16777219U);
    EXPECT_EQ(road_category.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), true);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), true);
    EXPECT_EQ(road_category.HasTagToll(), true);
}

TEST(RoadCategory, TestCopyConstructor)
{
    RoadCategory road_category01{16777219U};
    RoadCategory road_category02(road_category01);

    EXPECT_EQ(road_category02.GetValue(), road_category01.GetValue());
    EXPECT_EQ(road_category02.IsCategoryUnknown(), road_category01.IsCategoryUnknown());
    EXPECT_EQ(road_category02.IsCategoryMainRoad(), road_category01.IsCategoryMainRoad());
    EXPECT_EQ(road_category02.IsCategoryRamp(), road_category01.IsCategoryRamp());
    EXPECT_EQ(road_category02.HasTagTunnel(), road_category01.HasTagTunnel());
    EXPECT_EQ(road_category02.HasTagToll(), road_category01.HasTagToll());
}

TEST(RoadCategory, TestMoveConstructor)
{
    RoadCategory road_category01{33554433U};
    RoadCategory road_category02(std::move(road_category01));

    EXPECT_EQ(road_category02.GetValue(), 33554433U);
    EXPECT_EQ(road_category02.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category02.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category02.IsCategoryRamp(), true);
    EXPECT_EQ(road_category02.HasTagTunnel(), true);
    EXPECT_EQ(road_category02.HasTagToll(), false);
}

TEST(RoadCategory, TestCopyAssignOperator)
{
    RoadCategory road_category01{16777219U};

    RoadCategory road_category02;
    road_category02 = road_category01;

    EXPECT_EQ(road_category02.GetValue(), road_category01.GetValue());
    EXPECT_EQ(road_category02.IsCategoryUnknown(), road_category01.IsCategoryUnknown());
    EXPECT_EQ(road_category02.IsCategoryMainRoad(), road_category01.IsCategoryMainRoad());
    EXPECT_EQ(road_category02.IsCategoryRamp(), road_category01.IsCategoryRamp());
    EXPECT_EQ(road_category02.HasTagTunnel(), road_category01.HasTagTunnel());
    EXPECT_EQ(road_category02.HasTagToll(), road_category01.HasTagToll());
}

TEST(RoadCategory, TestMoveAssignOperator)
{
    RoadCategory road_category01{33554434U};

    RoadCategory road_category02;
    road_category02 = std::move(road_category01);

    EXPECT_EQ(road_category02.GetValue(), 33554434U);
    EXPECT_EQ(road_category02.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category02.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category02.IsCategoryRamp(), true);
    EXPECT_EQ(road_category02.HasTagTunnel(), false);
    EXPECT_EQ(road_category02.HasTagToll(), true);
}

TEST(RoadCategory, TestGetRoadCategoryValue)
{
    RoadCategory road_category;
    EXPECT_EQ(road_category.GetValue(), 0U);
}

TEST(RoadCategory, TestSetRoadCategoryValue)
{
    RoadCategory road_category;
    road_category.SetValue(33554435U);
    EXPECT_EQ(road_category.GetValue(), 33554435U);
}

TEST(RoadCategory, TestIsUnknownCategory)
{
    RoadCategory road_category;
    EXPECT_EQ(road_category.IsCategoryUnknown(), true);
    EXPECT_EQ(road_category.GetValue(), 0U);
}

TEST(RoadCategory, TestSetToUnknownCategory)
{
    RoadCategory road_category;
    road_category.SetCategoryUnknown();
    EXPECT_EQ(road_category.IsCategoryUnknown(), true);
    EXPECT_EQ(road_category.GetValue(), 0U);
}

TEST(RoadCategory, TestIsMainRoad)
{
    RoadCategory road_category;
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
}

TEST(RoadCategory, TestSetToMainRoad)
{
    RoadCategory road_category;
    road_category.SetCategoryMainRoad();
    EXPECT_EQ(road_category.IsCategoryMainRoad(), true);
    EXPECT_EQ(road_category.GetValue(), 16777216U);
}

TEST(RoadCategory, TestIsRamp)
{
    RoadCategory road_category;
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
}

TEST(RoadCategory, TestSetToRamp)
{
    RoadCategory road_category;
    road_category.SetCategoryRamp();
    EXPECT_EQ(road_category.IsCategoryRamp(), true);
    EXPECT_EQ(road_category.GetValue(), 33554432U);
}

TEST(RoadCategory, TestIsTunnel)
{
    RoadCategory road_category;
    EXPECT_EQ(road_category.HasTagTunnel(), false);
}

TEST(RoadCategory, TestSetToTunnel)
{
    RoadCategory road_category;

    road_category.SetTagTunnel();
    EXPECT_EQ(road_category.HasTagTunnel(), true);
    EXPECT_EQ(road_category.GetValue(), 1U);

    road_category.ResetTagTunnel();
    EXPECT_EQ(road_category.HasTagTunnel(), false);
    EXPECT_EQ(road_category.GetValue(), 0U);
}

TEST(RoadCategory, TestIsToll)
{
    RoadCategory road_category;
    EXPECT_EQ(road_category.HasTagToll(), false);
}

TEST(RoadCategory, TestSetToToll)
{
    RoadCategory road_category;

    road_category.SetTagToll();
    EXPECT_EQ(road_category.HasTagToll(), true);
    EXPECT_EQ(road_category.GetValue(), 2U);

    road_category.ResetTagToll();
    EXPECT_EQ(road_category.HasTagToll(), false);
    EXPECT_EQ(road_category.GetValue(), 0U);
}

TEST(RoadCategory, TestCompareOperator)
{
    RoadCategory road_category01;
    RoadCategory road_category02;

    bool is_equal = (road_category01 == road_category02);
    EXPECT_EQ(is_equal, true);

    road_category02.SetValue(16777218U);

    is_equal = (road_category01 == road_category02);
    EXPECT_EQ(is_equal, false);
}

TEST(RoadCategory, TestToUint64CastOperator)
{
    RoadCategory         road_category(33554434U);
    holo::uint32_t const value = static_cast<holo::uint32_t>(road_category);
    EXPECT_EQ(value, 33554434U);
}

/**
 * @brief Category of lane
 *
 * u 0 0 : 0
 * u 0 1 : 1
 * u 1 0 : 2
 * u 1 1 : 3
 * m 0 0 : 16777216
 * m 0 1 : 16777217
 * m 1 0 : 16777218
 * m 1 1 : 16777219
 * r 0 0 : 33554432
 * r 0 1 : 33554433
 * r 1 0 : 33554434
 * r 1 1 : 33554435
 *
 */
TEST(RoadCategory, TestMixSet)
{
    RoadCategory road_category;

    // For U 0 0
    road_category.SetCategoryUnknown();
    road_category.ResetTagTunnel();
    road_category.ResetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), true);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), false);
    EXPECT_EQ(road_category.HasTagToll(), false);
    EXPECT_EQ(road_category.GetValue(), 0U);

    // For U 0 1
    road_category.SetTagTunnel();
    road_category.ResetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), true);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), true);
    EXPECT_EQ(road_category.HasTagToll(), false);
    EXPECT_EQ(road_category.GetValue(), 1U);

    // For U 1 0
    road_category.ResetTagTunnel();
    road_category.SetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), true);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), false);
    EXPECT_EQ(road_category.HasTagToll(), true);
    EXPECT_EQ(road_category.GetValue(), 2U);

    // For U 1 1
    road_category.SetTagTunnel();
    road_category.SetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), true);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), true);
    EXPECT_EQ(road_category.HasTagToll(), true);
    EXPECT_EQ(road_category.GetValue(), 3U);

    // For M 0 0
    road_category.SetCategoryMainRoad();
    road_category.ResetTagTunnel();
    road_category.ResetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), true);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), false);
    EXPECT_EQ(road_category.HasTagToll(), false);
    EXPECT_EQ(road_category.GetValue(), 16777216U);

    // For M 0 1
    road_category.SetTagTunnel();
    road_category.ResetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), true);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), true);
    EXPECT_EQ(road_category.HasTagToll(), false);
    EXPECT_EQ(road_category.GetValue(), 16777217U);

    // For M 1 0
    road_category.ResetTagTunnel();
    road_category.SetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), true);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), false);
    EXPECT_EQ(road_category.HasTagToll(), true);
    EXPECT_EQ(road_category.GetValue(), 16777218U);

    // For M 1 1
    road_category.SetTagTunnel();
    road_category.SetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), true);
    EXPECT_EQ(road_category.IsCategoryRamp(), false);
    EXPECT_EQ(road_category.HasTagTunnel(), true);
    EXPECT_EQ(road_category.HasTagToll(), true);
    EXPECT_EQ(road_category.GetValue(), 16777219U);

    // For R 0 0
    road_category.SetCategoryRamp();
    road_category.ResetTagTunnel();
    road_category.ResetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category.IsCategoryRamp(), true);
    EXPECT_EQ(road_category.HasTagTunnel(), false);
    EXPECT_EQ(road_category.HasTagToll(), false);
    EXPECT_EQ(road_category.GetValue(), 33554432U);

    // For R 0 1
    road_category.SetTagTunnel();
    road_category.ResetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category.IsCategoryRamp(), true);
    EXPECT_EQ(road_category.HasTagTunnel(), true);
    EXPECT_EQ(road_category.HasTagToll(), false);
    EXPECT_EQ(road_category.GetValue(), 33554433U);

    // For R 1 0
    road_category.ResetTagTunnel();
    road_category.SetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category.IsCategoryRamp(), true);
    EXPECT_EQ(road_category.HasTagTunnel(), false);
    EXPECT_EQ(road_category.HasTagToll(), true);
    EXPECT_EQ(road_category.GetValue(), 33554434U);

    // For R 1 1
    road_category.SetTagTunnel();
    road_category.SetTagToll();
    EXPECT_EQ(road_category.IsCategoryUnknown(), false);
    EXPECT_EQ(road_category.IsCategoryMainRoad(), false);
    EXPECT_EQ(road_category.IsCategoryRamp(), true);
    EXPECT_EQ(road_category.HasTagTunnel(), true);
    EXPECT_EQ(road_category.HasTagToll(), true);
    EXPECT_EQ(road_category.GetValue(), 33554435U);
}

TEST(RoadCategory, TestGetSerializedSize)
{
    RoadCategory road_category{16777219U};

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_category.Serialize(serializer);
    EXPECT_EQ(road_category.GetSerializedSize(), serializer.GetSize());
}

TEST(RoadCategory, TestSerialization)
{
    RoadCategory road_category_s{33554435U};

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_category_s.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    RoadCategory road_category_d;
    road_category_d.Deserialize(deserializer);

    EXPECT_EQ(road_category_d, road_category_s);
}

// For LaneCategory
/**
 * @brief category of lane
 *
 * u : 0
 * r : 16777216
 * a : 33554432
 * d : 50331648
 *
 */
TEST(LaneCategory, TestDefaultConstructor)
{
    holo::common::LaneCategory lane_category;

    EXPECT_TRUE(lane_category.IsCategoryUnknown());
}

TEST(LaneCategory, TestConstructorWithParameters)
{
    holo::common::LaneCategory lane_category(50331648U);

    EXPECT_TRUE(lane_category.IsCategoryDeceleration());
}

TEST(LaneCategory, TestGetValue)
{
    holo::common::LaneCategory lane_category;
    EXPECT_EQ(lane_category.GetValue(), 0U);
}

TEST(LaneCategory, TestSetValue)
{
    holo::common::LaneCategory lane_category;
    lane_category.SetValue(33554432U);
    EXPECT_EQ(lane_category.GetValue(), 33554432U);
}

TEST(LaneCategory, TestIsUnknownCategory)
{
    holo::common::LaneCategory lane_category;

    EXPECT_EQ(lane_category.IsCategoryUnknown(), true);
}

TEST(LaneCategory, TestSetUnknownCategory)
{
    holo::common::LaneCategory lane_category;

    lane_category.SetCategoryUnknown();

    EXPECT_TRUE(lane_category.IsCategoryUnknown());
    EXPECT_EQ(lane_category.GetValue(), 0U);
}

TEST(LaneCategory, TestIsRegularCategory)
{
    holo::common::LaneCategory lane_category;

    EXPECT_EQ(lane_category.IsCategoryRegular(), false);
}

TEST(LaneCategory, TestSetRegularCategor)
{
    holo::common::LaneCategory lane_category;

    lane_category.SetCategoryRegular();

    EXPECT_TRUE(lane_category.IsCategoryRegular());
    EXPECT_EQ(lane_category.GetValue(), 16777216U);
}

TEST(LaneCategory, TestIsAccelerationCategory)
{
    holo::common::LaneCategory lane_category;

    EXPECT_EQ(lane_category.IsCategoryAcceleration(), false);
}

TEST(LaneCategory, TestSetAccelerationCategor)
{
    holo::common::LaneCategory lane_category;

    lane_category.SetCategoryAcceleration();

    EXPECT_TRUE(lane_category.IsCategoryAcceleration());
    EXPECT_EQ(lane_category.GetValue(), 33554432U);
}

TEST(LaneCategory, TestIsDecelerationCategory)
{
    holo::common::LaneCategory lane_category;

    EXPECT_EQ(lane_category.IsCategoryDeceleration(), false);
}

TEST(LaneCategory, TestSetDecelerationCategory)
{
    holo::common::LaneCategory lane_category;

    lane_category.SetCategoryDeceleration();

    EXPECT_TRUE(lane_category.IsCategoryDeceleration());
    EXPECT_EQ(lane_category.GetValue(), 50331648U);
}

TEST(LaneCategory, SetCheckEmergencyCategory)
{
    holo::common::LaneCategory lane_category;

    EXPECT_FALSE(lane_category.IsCategoryEmergency());
    lane_category.SetCategoryEmergency();
    EXPECT_TRUE(lane_category.IsCategoryEmergency());
}

TEST(LaneCategory, TestCompareOperator)
{
    holo::common::LaneCategory lane_category01;
    holo::common::LaneCategory lane_category02;

    bool is_equal = (lane_category01 == lane_category02);
    EXPECT_EQ(is_equal, true);

    lane_category02.SetValue(16777216U);

    is_equal = (lane_category01 == lane_category02);
    EXPECT_EQ(is_equal, false);
}

TEST(LaneCategory, TestToUint32CastOperator)
{
    holo::common::LaneCategory lane_category(33554432U);
    holo::uint32_t const       value = static_cast<holo::uint32_t>(lane_category);
    EXPECT_EQ(value, 33554432U);
}

TEST(LaneCategory, TestGetSerializedSize)
{
    holo::common::LaneCategory lane_category(50331648U);

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    lane_category.Serialize(serializer);
    EXPECT_EQ(lane_category.GetSerializedSize(), serializer.GetSize());
}

TEST(LaneCategory, TestSerialization)
{
    holo::common::LaneCategory lane_category_s(16777216U);

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    lane_category_s.Serialize(serializer);

    Deserializer               deserializer(buffer, serializer.GetSize());
    holo::common::LaneCategory lane_category_d;
    lane_category_d.Deserialize(deserializer);

    EXPECT_EQ(lane_category_s, lane_category_d);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
