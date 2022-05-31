/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_road_type.cpp
 * @brief Unit test for road type and lane tag.
 * @author lisong(lisong@holomaitc.com)
 * @date "2020-08-14"
 */

#include <gtest/gtest.h>

#include <holo/common/road_type.h>

using Serializer      = holo::serialization::Serializer<false, 4>;
using Deserializer    = holo::serialization::Deserializer<false, 4>;

using holo::common::RoadType;

// For RoadType
TEST(RoadType, TestDefaultConstructor)
{
    RoadType road_type;
    EXPECT_EQ(road_type.GetValue(), 0U);
    EXPECT_EQ(road_type.IsTypeUnknown(), true);
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), false);
    EXPECT_EQ(road_type.HasTagToll(), false);
}

TEST(RoadType, TestConstructorWithParameters)
{
    RoadType road_type{16777219U};
    EXPECT_EQ(road_type.GetValue(), 16777219U);
    EXPECT_EQ(road_type.IsTypeUnknown(), false);
    EXPECT_EQ(road_type.IsTypeMainRoad(), true);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), true);
    EXPECT_EQ(road_type.HasTagToll(), true);
}

TEST(RoadType, TestCopyConstructor)
{
    RoadType road_type01{16777219U};
    RoadType road_type02(road_type01);

    EXPECT_EQ(road_type02.GetValue(), road_type01.GetValue());
    EXPECT_EQ(road_type02.IsTypeUnknown(), road_type01.IsTypeUnknown());
    EXPECT_EQ(road_type02.IsTypeMainRoad(), road_type01.IsTypeMainRoad());
    EXPECT_EQ(road_type02.IsTypeRamp(), road_type01.IsTypeRamp());
    EXPECT_EQ(road_type02.HasTagTunnel(), road_type01.HasTagTunnel());
    EXPECT_EQ(road_type02.HasTagToll(), road_type01.HasTagToll());
}


TEST(RoadType, TestMoveConstructor)
{
    RoadType road_type01{33554433U};
    RoadType road_type02(std::move(road_type01));

    EXPECT_EQ(road_type02.GetValue(), 33554433U);
    EXPECT_EQ(road_type02.IsTypeUnknown(), false);
    EXPECT_EQ(road_type02.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type02.IsTypeRamp(), true);
    EXPECT_EQ(road_type02.HasTagTunnel(), true);
    EXPECT_EQ(road_type02.HasTagToll(), false); 
}

TEST(RoadType, TestCopyAssignOperator)
{
    RoadType road_type01{16777219U};

    RoadType road_type02;
    road_type02 = road_type01;

    EXPECT_EQ(road_type02.GetValue(), road_type01.GetValue());
    EXPECT_EQ(road_type02.IsTypeUnknown(), road_type01.IsTypeUnknown());
    EXPECT_EQ(road_type02.IsTypeMainRoad(), road_type01.IsTypeMainRoad());
    EXPECT_EQ(road_type02.IsTypeRamp(), road_type01.IsTypeRamp());
    EXPECT_EQ(road_type02.HasTagTunnel(), road_type01.HasTagTunnel());
    EXPECT_EQ(road_type02.HasTagToll(), road_type01.HasTagToll()); 
}

TEST(RoadType, TestMoveAssignOperator)
{
    RoadType road_type01{33554434U};

    RoadType road_type02;
    road_type02 = std::move(road_type01);

    EXPECT_EQ(road_type02.GetValue(), 33554434U);
    EXPECT_EQ(road_type02.IsTypeUnknown(), false);
    EXPECT_EQ(road_type02.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type02.IsTypeRamp(), true);
    EXPECT_EQ(road_type02.HasTagTunnel(), false);
    EXPECT_EQ(road_type02.HasTagToll(), true); 
}

TEST(RoadType, TestGetRoadTypeValue)
{
    RoadType road_type;
    EXPECT_EQ(road_type.GetValue(), 0U);
}

TEST(RoadType, TestSetRoadTypeValue)
{
    RoadType road_type;
    road_type.SetValue(33554435U);
    EXPECT_EQ(road_type.GetValue(), 33554435U);  
}

TEST(RoadType, TestIsUnknownType)
{
    RoadType road_type;
    EXPECT_EQ(road_type.IsTypeUnknown(), true);
    EXPECT_EQ(road_type.GetValue(), 0U);
}

TEST(RoadType, TestSetToUnknownType)
{
    RoadType road_type;
    road_type.SetTypeUnknown();
    EXPECT_EQ(road_type.IsTypeUnknown(), true);
    EXPECT_EQ(road_type.GetValue(), 0U);
}

TEST(RoadType, TestIsMainRoad)
{
    RoadType road_type;
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
}

TEST(RoadType, TestSetToMainRoad)
{
    RoadType road_type;
    road_type.SetTypeMainRoad();
    EXPECT_EQ(road_type.IsTypeMainRoad(), true);
    EXPECT_EQ(road_type.GetValue(), 16777216U);
}

TEST(RoadType, TestIsRamp)
{
    RoadType road_type;
    EXPECT_EQ(road_type.IsTypeRamp(), false);
}

TEST(RoadType, TestSetToRamp)
{
    RoadType road_type;
    road_type.SetTypeRamp();
    EXPECT_EQ(road_type.IsTypeRamp(), true);
    EXPECT_EQ(road_type.GetValue(), 33554432U);
}

TEST(RoadType, TestIsTunnel)
{
    RoadType road_type;
    EXPECT_EQ(road_type.HasTagTunnel(), false);
}

TEST(RoadType, TestSetToTunnel)
{
    RoadType road_type;

    road_type.SetTagTunnel();
    EXPECT_EQ(road_type.HasTagTunnel(), true);
    EXPECT_EQ(road_type.GetValue(), 1U);

    road_type.ResetTagTunnel();
    EXPECT_EQ(road_type.HasTagTunnel(), false);
    EXPECT_EQ(road_type.GetValue(), 0U);
}

TEST(RoadType, TestIsToll)
{
    RoadType road_type;
    EXPECT_EQ(road_type.HasTagToll(), false);
}

TEST(RoadType, TestSetToToll)
{
    RoadType road_type;

    road_type.SetTagToll();
    EXPECT_EQ(road_type.HasTagToll(), true);
    EXPECT_EQ(road_type.GetValue(), 2U);

    road_type.ResetTagToll();
    EXPECT_EQ(road_type.HasTagToll(), false);
    EXPECT_EQ(road_type.GetValue(), 0U);
}

TEST(RoadType, TestCompareOperator)
{
    RoadType road_type01;
    RoadType road_type02;

    bool is_equal = (road_type01 == road_type02);
    EXPECT_EQ(is_equal, true);

    road_type02.SetValue(16777218U);

    is_equal = (road_type01 == road_type02);
    EXPECT_EQ(is_equal, false);
}

TEST(RoadType, TestToUint64CastOperator)
{
    RoadType road_type(33554434U);
    holo::uint32_t const value = static_cast<holo::uint32_t>(road_type);
    EXPECT_EQ(value, 33554434U);
}

/**
 * @brief Types of lane
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
TEST(RoadType, TestMixSet)
{
    RoadType road_type;

    // For U 0 0
    road_type.SetTypeUnknown();
    road_type.ResetTagTunnel();
    road_type.ResetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), true);
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), false);
    EXPECT_EQ(road_type.HasTagToll(), false);
    EXPECT_EQ(road_type.GetValue(), 0U);

    // For U 0 1
    road_type.SetTagTunnel();
    road_type.ResetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), true);
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), true);
    EXPECT_EQ(road_type.HasTagToll(), false);
    EXPECT_EQ(road_type.GetValue(), 1U);

    // For U 1 0
    road_type.ResetTagTunnel();
    road_type.SetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), true);
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), false);
    EXPECT_EQ(road_type.HasTagToll(), true);
    EXPECT_EQ(road_type.GetValue(), 2U);

    // For U 1 1
    road_type.SetTagTunnel();
    road_type.SetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), true);
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), true);
    EXPECT_EQ(road_type.HasTagToll(), true);
    EXPECT_EQ(road_type.GetValue(), 3U);

    // For M 0 0
    road_type.SetTypeMainRoad();
    road_type.ResetTagTunnel();
    road_type.ResetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), false);
    EXPECT_EQ(road_type.IsTypeMainRoad(), true);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), false);
    EXPECT_EQ(road_type.HasTagToll(), false);
    EXPECT_EQ(road_type.GetValue(), 16777216U);

    // For M 0 1
    road_type.SetTagTunnel();
    road_type.ResetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), false);
    EXPECT_EQ(road_type.IsTypeMainRoad(), true);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), true);
    EXPECT_EQ(road_type.HasTagToll(), false);
    EXPECT_EQ(road_type.GetValue(), 16777217U);

    // For M 1 0
    road_type.ResetTagTunnel();
    road_type.SetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), false);
    EXPECT_EQ(road_type.IsTypeMainRoad(), true);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), false);
    EXPECT_EQ(road_type.HasTagToll(), true);
    EXPECT_EQ(road_type.GetValue(), 16777218U);

    // For M 1 1
    road_type.SetTagTunnel();
    road_type.SetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), false);
    EXPECT_EQ(road_type.IsTypeMainRoad(), true);
    EXPECT_EQ(road_type.IsTypeRamp(), false);
    EXPECT_EQ(road_type.HasTagTunnel(), true);
    EXPECT_EQ(road_type.HasTagToll(), true);
    EXPECT_EQ(road_type.GetValue(), 16777219U);

    // For R 0 0
    road_type.SetTypeRamp();
    road_type.ResetTagTunnel();
    road_type.ResetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), false);
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type.IsTypeRamp(), true);
    EXPECT_EQ(road_type.HasTagTunnel(), false);
    EXPECT_EQ(road_type.HasTagToll(), false);
    EXPECT_EQ(road_type.GetValue(), 33554432U);

    // For R 0 1
    road_type.SetTagTunnel();
    road_type.ResetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), false);
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type.IsTypeRamp(), true);
    EXPECT_EQ(road_type.HasTagTunnel(), true);
    EXPECT_EQ(road_type.HasTagToll(), false);
    EXPECT_EQ(road_type.GetValue(), 33554433U);

    // For R 1 0
    road_type.ResetTagTunnel();
    road_type.SetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), false);
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type.IsTypeRamp(), true);
    EXPECT_EQ(road_type.HasTagTunnel(), false);
    EXPECT_EQ(road_type.HasTagToll(), true);
    EXPECT_EQ(road_type.GetValue(), 33554434U);

    // For R 1 1
    road_type.SetTagTunnel();
    road_type.SetTagToll();
    EXPECT_EQ(road_type.IsTypeUnknown(), false);
    EXPECT_EQ(road_type.IsTypeMainRoad(), false);
    EXPECT_EQ(road_type.IsTypeRamp(), true);
    EXPECT_EQ(road_type.HasTagTunnel(), true);
    EXPECT_EQ(road_type.HasTagToll(), true);
    EXPECT_EQ(road_type.GetValue(), 33554435U);
}

TEST(RoadType, TestGetSerializedSize)
{
    RoadType road_type{16777219U};

    uint8_t buffer[2048];
    Serializer serializer(buffer, 2048);
    road_type.Serialize(serializer);
    EXPECT_EQ(road_type.GetSerializedSize(), serializer.GetSize());
}

TEST(RoadType, TestSerialization)
{
    RoadType road_type_s{33554435U};

    uint8_t buffer[2048];
    Serializer serializer(buffer, 2048);
    road_type_s.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    RoadType road_type_d;
    road_type_d.Deserialize(deserializer);

    EXPECT_EQ(road_type_d, road_type_s);
}

// For LaneType
/**
 * @brief Types of lane
 * 
 * u : 0
 * r : 16777216
 * a : 33554432
 * d : 50331648
 * 
 */
TEST(LaneType, TestDefaultConstructor)
{
    holo::common::LaneType lane_type;

    EXPECT_TRUE(lane_type.IsTypeUnknown());
}

TEST(LaneType, TestConstructorWithParameters)
{
    holo::common::LaneType lane_type(50331648U);

    EXPECT_TRUE(lane_type.IsTypeDeceleration());
}

TEST(LaneType, TestGetValue)
{
    holo::common::LaneType lane_type;
    EXPECT_EQ(lane_type.GetValue(), 0U);
}

TEST(LaneType, TestSetValue)
{
    holo::common::LaneType lane_type;
    lane_type.SetValue(33554432U);
    EXPECT_EQ(lane_type.GetValue(), 33554432U);  
}

TEST(LaneType, TestIsUnknownType)
{
    holo::common::LaneType lane_type;

    EXPECT_EQ(lane_type.IsTypeUnknown(), true);
}

TEST(LaneType, TestSetUnknownType)
{
    holo::common::LaneType lane_type;

    lane_type.SetTypeUnknown();

    EXPECT_TRUE(lane_type.IsTypeUnknown());
    EXPECT_EQ(lane_type.GetValue(), 0U);
}

TEST(LaneType, TestIsRegularType)
{
    holo::common::LaneType lane_type;

    EXPECT_EQ(lane_type.IsTypeRegular(), false);
}

TEST(LaneType, TestSetRegularType)
{
    holo::common::LaneType lane_type;

    lane_type.SetTypeRegular();

    EXPECT_TRUE(lane_type.IsTypeRegular());
    EXPECT_EQ(lane_type.GetValue(), 16777216U);
}

TEST(LaneType, TestIsAccelerationType)
{
    holo::common::LaneType lane_type;

    EXPECT_EQ(lane_type.IsTypeAcceleration(), false);
}

TEST(LaneType, TestSetAccelerationType)
{
    holo::common::LaneType lane_type;

    lane_type.SetTypeAcceleration();

    EXPECT_TRUE(lane_type.IsTypeAcceleration());
    EXPECT_EQ(lane_type.GetValue(), 33554432U);
}

TEST(LaneType, TestIsDecelerationType)
{
    holo::common::LaneType lane_type;

    EXPECT_EQ(lane_type.IsTypeDeceleration(), false);
}

TEST(LaneType, TestSetDecelerationType)
{
    holo::common::LaneType lane_type;

    lane_type.SetTypeDeceleration();

    EXPECT_TRUE(lane_type.IsTypeDeceleration());
    EXPECT_EQ(lane_type.GetValue(), 50331648U);
}

TEST(LaneType, SetCheckEmergencyType)
{
    holo::common::LaneType lane_type;

    EXPECT_FALSE(lane_type.IsTypeEmergency());
    lane_type.SetTypeEmergency();
    EXPECT_TRUE(lane_type.IsTypeEmergency());
}

TEST(LaneType, TestCompareOperator)
{
    holo::common::LaneType lane_type01;
    holo::common::LaneType lane_type02;

    bool is_equal = (lane_type01 == lane_type02);
    EXPECT_EQ(is_equal, true);

    lane_type02.SetValue(16777216U);

    is_equal = (lane_type01 == lane_type02);
    EXPECT_EQ(is_equal, false);
}

TEST(LaneType, TestToUint32CastOperator)
{
    holo::common::LaneType lane_type(33554432U);
    holo::uint32_t const value = static_cast<holo::uint32_t>(lane_type);
    EXPECT_EQ(value, 33554432U);
}

TEST(LaneType, TestGetSerializedSize)
{
    holo::common::LaneType lane_type(50331648U);

    uint8_t buffer[2048];
    Serializer serializer(buffer, 2048);
    lane_type.Serialize(serializer);
    EXPECT_EQ(lane_type.GetSerializedSize(), serializer.GetSize());
}

TEST(LaneType, TestSerialization)
{
    holo::common::LaneType lane_type_s(16777216U);

    uint8_t buffer[2048];
    Serializer serializer(buffer, 2048);
    lane_type_s.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    holo::common::LaneType lane_type_d;
    lane_type_d.Deserialize(deserializer);

    EXPECT_EQ(lane_type_s, lane_type_d);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
