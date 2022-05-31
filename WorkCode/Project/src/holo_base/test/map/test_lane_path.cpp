/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_lane_path.cpp
 * @brief Testing for LanePath
 * @author zhouhuishuang(zhouhuishuang@holomaitc.com)
 * @date "2021-05-06"
 */

#include <gtest/gtest.h>
#include <holo/map/lane_path.h>

using LaneItem = holo::map::LaneItem;
using LanePath = holo::map::LanePathT<3U>;
using Advice   = holo::map::AdviceT<3U, 3U>;

TEST(LaneItem, DefaultConstructor)
{
    LaneItem lane_item;
    ASSERT_EQ(0U, lane_item.GetLaneId());
    ASSERT_EQ(0U, lane_item.GetLength());
    ASSERT_EQ(holo::common::LaneCategory(0U), lane_item.GetLaneCategory());
    ASSERT_EQ(holo::common::RoadCategory(0U), lane_item.GetRoadCategory());
    ASSERT_EQ(LaneItem::LaneMark::UNDEFINED, lane_item.GetLaneMark());
    ASSERT_EQ(LaneItem::LaneModel::NORMAL, lane_item.GetLaneModel());
    ASSERT_EQ(false, lane_item.IsIntersection());
    ASSERT_EQ(holo::geometry::Point2(0U, 0U), lane_item.GetStartDirection());
    ASSERT_EQ(holo::geometry::Point2(0U, 0U), lane_item.GetEndDirection());
}

TEST(LaneItem, Constructor)
{
    LaneItem lane_item(5U, 3.5, holo::common::RoadType(16777219U), holo::common::LaneType(50331648U),
                       LaneItem::LaneMark::U_TURN_RIGHT, LaneItem::LaneModel::MERGE_FROM, true, {788775U, 59999U}, {22222U, 11111U});
    ASSERT_EQ(5U, lane_item.GetLaneId());
    ASSERT_EQ(3.5, lane_item.GetLength());
    ASSERT_EQ(holo::common::RoadType(16777219U), lane_item.GetRoadType());
    ASSERT_EQ(holo::common::LaneType(50331648U), lane_item.GetLaneType());
    ASSERT_EQ(LaneItem::LaneMark::U_TURN_RIGHT, lane_item.GetLaneMark());
    ASSERT_EQ(LaneItem::LaneModel::MERGE_FROM, lane_item.GetLaneModel());
    ASSERT_EQ(true, lane_item.IsIntersection());
    ASSERT_EQ(holo::geometry::Point2(788775U, 59999U), lane_item.GetStartDirection());
    ASSERT_EQ(holo::geometry::Point2(22222U, 11111U), lane_item.GetEndDirection());
}

TEST(LaneItem, Constructor_2)
{
    LaneItem lane_item(5U, 3.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(50331648U),
                       LaneItem::LaneMark::U_TURN_RIGHT, LaneItem::LaneModel::MERGE_FROM, true, {788775U, 59999U}, {22222U, 11111U});
    ASSERT_EQ(5U, lane_item.GetLaneId());
    ASSERT_EQ(3.5, lane_item.GetLength());
    ASSERT_EQ(holo::common::RoadCategory(16777219U), lane_item.GetRoadCategory());
    ASSERT_EQ(holo::common::LaneCategory(50331648U), lane_item.GetLaneCategory());
    ASSERT_EQ(LaneItem::LaneMark::U_TURN_RIGHT, lane_item.GetLaneMark());
    ASSERT_EQ(LaneItem::LaneModel::MERGE_FROM, lane_item.GetLaneModel());
    ASSERT_EQ(true, lane_item.IsIntersection());
    ASSERT_EQ(holo::geometry::Point2(788775U, 59999U), lane_item.GetStartDirection());
    ASSERT_EQ(holo::geometry::Point2(22222U, 11111U), lane_item.GetEndDirection());
}

TEST(LaneItem, GetAndSetLaneId)
{
    LaneItem lane_item;
    lane_item.SetLaneId(80U);
    ASSERT_EQ(80U, lane_item.GetLaneId());
}

TEST(LaneItem, GetAndSetLength)
{
    LaneItem lane_item;
    lane_item.SetLength(12.25);
    ASSERT_EQ(12.25, lane_item.GetLength());
}

TEST(LaneItem, GetAndSetRoadType)
{
    LaneItem lane_item;
    lane_item.SetRoadType(holo::common::RoadType(16777219U));
    ASSERT_EQ(holo::common::RoadType(16777219U), lane_item.GetRoadType());
}

TEST(LaneItem, GetAndSetRoadCategory)
{
    LaneItem lane_item;
    lane_item.SetRoadCategory(holo::common::RoadCategory(16777219U));
    ASSERT_EQ(holo::common::RoadCategory(16777219U), lane_item.GetRoadCategory());
}

TEST(LaneItem, GetAndSetLaneType)
{
    LaneItem lane_item;
    lane_item.SetLaneType(holo::common::LaneType(50331648U));
    ASSERT_EQ(holo::common::LaneType(50331648U), lane_item.GetLaneType());
}

TEST(LaneItem, GetAndSetLaneCategory)
{
    LaneItem lane_item;
    lane_item.SetLaneCategory(holo::common::LaneCategory(50331648U));
    ASSERT_EQ(holo::common::LaneCategory(50331648U), lane_item.GetLaneCategory());
}

TEST(LaneItem, GetAndSetLaneMark)
{
    LaneItem lane_item;
    lane_item.SetLaneMark(LaneItem::LaneMark::STRAIGHT);
    ASSERT_EQ(LaneItem::LaneMark::STRAIGHT, lane_item.GetLaneMark());
}

TEST(LaneItem, GetAndSetLaneModel)
{
    LaneItem lane_item;
    lane_item.SetLaneModel(LaneItem::LaneModel::SPLIT);
    ASSERT_EQ(LaneItem::LaneModel::SPLIT, lane_item.GetLaneModel());
}

TEST(LaneItem, IsIntersection)
{
    LaneItem lane_item;
    lane_item.SetIntersectionFlag(true);
    ASSERT_EQ(true, lane_item.IsIntersection());

    lane_item.SetIntersectionFlag(false);
    ASSERT_EQ(false, lane_item.IsIntersection());
}

TEST(LaneItem, GetAndSetStartDirection)
{
    LaneItem lane_item;
    lane_item.SetStartDirection(holo::geometry::Point2(16777219U, 445222U));
    ASSERT_EQ(holo::geometry::Point2(16777219U, 445222U), lane_item.GetStartDirection());
}

TEST(LaneItem, GetAndSetEndDirection)
{
    LaneItem lane_item;
    lane_item.SetEndDirection(holo::geometry::Point2(16777219U, 445222U));
    ASSERT_EQ(holo::geometry::Point2(16777219U, 445222U), lane_item.GetEndDirection());
}

TEST(LaneItem, GetRotation)
{
    LaneItem lane_item;
    lane_item.SetStartDirection(holo::geometry::Point2(0U, 1U));
    lane_item.SetEndDirection(holo::geometry::Point2(1U, 1U));
    ASSERT_EQ(static_cast<holo::int32_t>(-45), static_cast<holo::int32_t>(lane_item.GetRotation()*180/M_PI));
    lane_item.SetStartDirection(holo::geometry::Point2(1U, 0U));
    lane_item.SetEndDirection(holo::geometry::Point2(1U, 1U));
    ASSERT_EQ(static_cast<holo::int32_t>(45), static_cast<holo::int32_t>(lane_item.GetRotation()*180/M_PI));
    lane_item.SetStartDirection(holo::geometry::Point2(1U, 1U));
    lane_item.SetEndDirection(holo::geometry::Point2(0U, 2U));
    ASSERT_EQ(static_cast<holo::int32_t>(45), static_cast<holo::int32_t>(lane_item.GetRotation()*180/M_PI));
    lane_item.SetStartDirection(holo::geometry::Point2(1U, 1U));
    lane_item.SetEndDirection(holo::geometry::Point2(2U, 0U));
    ASSERT_EQ(static_cast<holo::int32_t>(-45), static_cast<holo::int32_t>(lane_item.GetRotation()*180/M_PI));
}

TEST(LaneItem, GetSerializedSize)
{
    LaneItem lane_item;
    ASSERT_EQ(60, lane_item.GetSerializedSize<4U>());
    ASSERT_EQ(64, lane_item.GetSerializedSize<8U>());
}

TEST(LaneItem, SerializeAndDeserialize)
{
    LaneItem lane_item(5U, 3.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(50331648U),
                       LaneItem::LaneMark::U_TURN_RIGHT, LaneItem::LaneModel::MERGE_FROM, true, {23U, 68U}, {435U, 2469U});

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << lane_item;
    ASSERT_EQ(lane_item.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    LaneItem                            lane_item_output;
    deserializer >> lane_item_output;

    ASSERT_EQ(lane_item.GetLaneId(), lane_item_output.GetLaneId());
    ASSERT_EQ(lane_item.GetLength(), lane_item_output.GetLength());
    ASSERT_EQ(lane_item.GetRoadCategory(), lane_item_output.GetRoadCategory());
    ASSERT_EQ(lane_item.GetLaneCategory(), lane_item_output.GetLaneCategory());
    ASSERT_EQ(lane_item.GetLaneMark(), lane_item_output.GetLaneMark());
    ASSERT_EQ(lane_item.GetLaneModel(), lane_item_output.GetLaneModel());
    ASSERT_EQ(lane_item.IsIntersection(), lane_item_output.IsIntersection());
    ASSERT_EQ(lane_item.GetStartDirection(), lane_item_output.GetStartDirection());
    ASSERT_EQ(lane_item.GetEndDirection(), lane_item_output.GetEndDirection());
}

TEST(LanePath, DefaultConstructor)
{
    LanePath lane_path;
    ASSERT_EQ(0U, lane_path.GetId());
    ASSERT_EQ(0U, lane_path.GetSequenceNumber());
    ASSERT_EQ(LanePath::TerminationType::UNDEFINED, lane_path.GetTerminationType());
    ASSERT_EQ(0U, lane_path.size());
}

TEST(LanePath, Constructor)
{
    LanePath lane_path(5U, -1, LanePath::TerminationType::EXTEND_ROUTE);
    ASSERT_EQ(5U, lane_path.GetId());
    ASSERT_EQ(-1, lane_path.GetSequenceNumber());
    ASSERT_EQ(LanePath::TerminationType::EXTEND_ROUTE, lane_path.GetTerminationType());
    ASSERT_EQ(0U, lane_path.size());
}

TEST(LanePath, SetAndGetId)
{
    LanePath lane_path;
    lane_path.SetId(6U);
    ASSERT_EQ(6U, lane_path.GetId());
}

TEST(LanePath, SetAndGetSequenceNumber)
{
    LanePath lane_path;
    lane_path.SetSequenceNumber(-5U);
    ASSERT_EQ(-5U, lane_path.GetSequenceNumber());
}

TEST(LanePath, SetAndGetTerminationType)
{
    LanePath lane_path;
    lane_path.SetTerminationType(LanePath::TerminationType::OUT_SEARCH_RANGE);
    ASSERT_EQ(LanePath::TerminationType::OUT_SEARCH_RANGE, lane_path.GetTerminationType());
}

TEST(LanePath, PushBackLaneItem)
{
    LaneItem lane_item1(5U, 3.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(50331648U),
                        LaneItem::LaneMark::U_TURN_RIGHT, LaneItem::LaneModel::MERGE_FROM, true, {23U, 68U}, {435U, 2469U});
    LaneItem lane_item2(10U, 13.5, holo::common::RoadCategory(1677219U), holo::common::LaneCategory(5033648U),
                        LaneItem::LaneMark::LEFT, LaneItem::LaneModel::MERGE_TO, true, {23U, 68U}, {435U, 2469U});

    LanePath lane_path(5U, -1, LanePath::TerminationType::EXTEND_ROUTE);
    lane_path.push_back(lane_item1);
    lane_path.push_back(lane_item2);
    ASSERT_EQ(2, lane_path.size());

    ASSERT_EQ(5U, lane_path[0].GetLaneId());
    ASSERT_EQ(3.5, lane_path[0].GetLength());
    ASSERT_EQ(holo::common::RoadCategory(16777219U), lane_path[0].GetRoadCategory());
    ASSERT_EQ(holo::common::LaneCategory(50331648U), lane_path[0].GetLaneCategory());
    ASSERT_EQ(LaneItem::LaneMark::U_TURN_RIGHT, lane_path[0].GetLaneMark());
    ASSERT_EQ(LaneItem::LaneModel::MERGE_FROM, lane_path[0].GetLaneModel());
    ASSERT_EQ(true, lane_path[0].IsIntersection());
    ASSERT_EQ(holo::geometry::Point2(23U, 68U), lane_path[0].GetStartDirection());
    ASSERT_EQ(holo::geometry::Point2(435U, 2469U), lane_path[0].GetEndDirection());

    ASSERT_EQ(10U, lane_path[1].GetLaneId());
    ASSERT_EQ(13.5, lane_path[1].GetLength());
    ASSERT_EQ(holo::common::RoadCategory(1677219U), lane_path[1].GetRoadCategory());
    ASSERT_EQ(holo::common::LaneCategory(5033648U), lane_path[1].GetLaneCategory());
    ASSERT_EQ(LaneItem::LaneMark::LEFT, lane_path[1].GetLaneMark());
    ASSERT_EQ(LaneItem::LaneModel::MERGE_TO, lane_path[1].GetLaneModel());
    ASSERT_EQ(true, lane_path[1].IsIntersection());
    ASSERT_EQ(holo::geometry::Point2(23U, 68U), lane_path[1].GetStartDirection());
    ASSERT_EQ(holo::geometry::Point2(435U, 2469U), lane_path[1].GetEndDirection());
}

TEST(LanePath, GetSerializedSize)
{
    LanePath lane_path(5U, -1, LanePath::TerminationType::EXTEND_ROUTE);
    ASSERT_EQ(28, lane_path.GetSerializedSize<4U>());
    ASSERT_EQ(32, lane_path.GetSerializedSize<8U>());
}

TEST(LanePath, SerializeAndDeserialize)
{
    LaneItem lane_item1(5U, 3.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(50331648U),
                        LaneItem::LaneMark::U_TURN_RIGHT, LaneItem::LaneModel::MERGE_FROM, true, {23U, 68U}, {435U, 2469U});
    LaneItem lane_item2(10U, 13.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(5033648U),
                        LaneItem::LaneMark::LEFT, LaneItem::LaneModel::MERGE_TO, true, {23U, 68U}, {435U, 2469U});

    LanePath::SpeedLimitSegment SpeedSeg1, SpeedSeg2;
    SpeedSeg1.start_distance = 10.1;
    SpeedSeg1.end_distance   = 10.2;
    SpeedSeg1.min_speed      = 10.3;
    SpeedSeg1.max_speed      = 10.4;

    SpeedSeg2.start_distance = 20.1;
    SpeedSeg2.end_distance   = 20.2;
    SpeedSeg2.min_speed      = 20.3;
    SpeedSeg2.max_speed      = 20.4;

    LanePath                  lane_path(5U, -1, LanePath::TerminationType::EXTEND_ROUTE);
    LanePath::LaneSpeedLimits lane_limit;
    lane_limit.push_back(SpeedSeg1);
    lane_limit.push_back(SpeedSeg2);

    lane_path.push_back(lane_item1);
    lane_path.push_back(lane_item2);
    lane_path.SetLaneSpeedLimits(lane_limit);
    lane_path.SetTerminationType(LanePath::TerminationType::NO_SUCCEEDINGS);

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << lane_path;
    ASSERT_EQ(lane_path.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    LanePath                            lane_path_output;

    deserializer >> lane_path_output;

    ASSERT_EQ(2, lane_path_output.size());
    ASSERT_EQ(5U, lane_path_output.GetId());
    ASSERT_EQ(-1, lane_path_output.GetSequenceNumber());
    ASSERT_EQ(LanePath::TerminationType::NO_SUCCEEDINGS, lane_path_output.GetTerminationType());

    ASSERT_EQ(lane_item1.GetLaneId(), lane_path_output[0].GetLaneId());
    ASSERT_EQ(lane_item1.GetLength(), lane_path_output[0].GetLength());
    ASSERT_EQ(lane_item1.GetRoadCategory(), lane_path_output[0].GetRoadCategory());
    ASSERT_EQ(lane_item1.GetLaneCategory(), lane_path_output[0].GetLaneCategory());
    ASSERT_EQ(lane_item1.GetLaneMark(), lane_path_output[0].GetLaneMark());
    ASSERT_EQ(lane_item1.GetLaneModel(), lane_path_output[0].GetLaneModel());
    ASSERT_EQ(lane_item1.IsIntersection(), lane_path_output[0].IsIntersection());
    ASSERT_EQ(lane_item1.GetStartDirection(), lane_path_output[0].GetStartDirection());
    ASSERT_EQ(lane_item1.GetEndDirection(), lane_path_output[0].GetEndDirection());

    ASSERT_EQ(lane_item2.GetLaneId(), lane_path_output[1].GetLaneId());
    ASSERT_EQ(lane_item2.GetLength(), lane_path_output[1].GetLength());
    ASSERT_EQ(lane_item2.GetRoadCategory(), lane_path_output[1].GetRoadCategory());
    ASSERT_EQ(lane_item2.GetLaneCategory(), lane_path_output[1].GetLaneCategory());
    ASSERT_EQ(lane_item2.GetLaneMark(), lane_path_output[1].GetLaneMark());
    ASSERT_EQ(lane_item2.GetLaneModel(), lane_path_output[1].GetLaneModel());
    ASSERT_EQ(lane_item2.IsIntersection(), lane_path_output[1].IsIntersection());
    ASSERT_EQ(lane_item2.GetStartDirection(), lane_path_output[1].GetStartDirection());
    ASSERT_EQ(lane_item2.GetEndDirection(), lane_path_output[1].GetEndDirection());

    for (size_t i = 0; i < lane_path_output.GetLaneSpeedLimits().size(); ++i)
    {
        ASSERT_EQ(lane_path.GetLaneSpeedLimits()[i].start_distance,
                  lane_path_output.GetLaneSpeedLimits()[i].start_distance);
        ASSERT_EQ(lane_path.GetLaneSpeedLimits()[i].end_distance,
                  lane_path_output.GetLaneSpeedLimits()[i].end_distance);
        ASSERT_EQ(lane_path.GetLaneSpeedLimits()[i].min_speed, lane_path_output.GetLaneSpeedLimits()[i].min_speed);
        ASSERT_EQ(lane_path.GetLaneSpeedLimits()[i].max_speed, lane_path_output.GetLaneSpeedLimits()[i].max_speed);
    }
}

TEST(Advice, DefaultConstructor)
{
    Advice advice;
    ASSERT_EQ(0U, advice.GetLanePathSize());
}

TEST(Advice, PushBackLanePathAndGetLanePath)
{
    LaneItem lane_item1(5U, 3.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(50331648U),
                        LaneItem::LaneMark::U_TURN_RIGHT, LaneItem::LaneModel::MERGE_FROM, true, {23U, 68U}, {435U, 2469U});
    LaneItem lane_item2(10U, 13.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(5033648U),
                        LaneItem::LaneMark::LEFT, LaneItem::LaneModel::MERGE_TO, true, {23U, 68U}, {435U, 2469U});

    LanePath lane_path1, lane_path2;
    lane_path1.push_back(lane_item1);
    lane_path2.push_back(lane_item2);

    Advice advice;
    advice.PushBackLanePath(lane_path1);
    advice.PushBackLanePath(lane_path2);

    ASSERT_EQ(2U, advice.GetLanePathSize());

    ASSERT_EQ(10U, advice.GetLanePath(1)[0].GetLaneId());
    ASSERT_EQ(13.5, advice.GetLanePath(1)[0].GetLength());
    ASSERT_EQ(holo::common::RoadCategory(16777219U), advice.GetLanePath(1)[0].GetRoadCategory());
    ASSERT_EQ(holo::common::LaneCategory(5033648U), advice.GetLanePath(1)[0].GetLaneCategory());
    ASSERT_EQ(LaneItem::LaneMark::LEFT, advice.GetLanePath(1)[0].GetLaneMark());
    ASSERT_EQ(LaneItem::LaneModel::MERGE_TO, advice.GetLanePath(1)[0].GetLaneModel());
    ASSERT_EQ(holo::geometry::Point2(23U, 68U), advice.GetLanePath(1)[0].GetStartDirection());
    ASSERT_EQ(holo::geometry::Point2(435U, 2469U), advice.GetLanePath(1)[0].GetEndDirection());
}

TEST(Advice, GetLanePaths)
{
    LaneItem lane_item1(5U, 3.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(50331648U),
                        LaneItem::LaneMark::U_TURN_RIGHT, LaneItem::LaneModel::MERGE_FROM, true, {23U, 68U}, {435U, 2469U});
    LaneItem lane_item2(10U, 13.5, holo::common::RoadCategory(1677219U), holo::common::LaneCategory(5033648U),
                        LaneItem::LaneMark::LEFT, LaneItem::LaneModel::MERGE_TO, true, {23U, 68U}, {435U, 2469U});

    LanePath lane_path1, lane_path2;
    lane_path1.push_back(lane_item1);
    lane_path2.push_back(lane_item2);

    Advice advice;
    advice.PushBackLanePath(lane_path1);
    advice.PushBackLanePath(lane_path2);

    holo::container::Vector<LanePath, 3U> lane_vector;
    lane_vector = advice.GetLanePaths();

    ASSERT_EQ(2U, lane_vector.size());

    ASSERT_EQ(5U, lane_vector[0][0].GetLaneId());
    ASSERT_EQ(3.5, lane_vector[0][0].GetLength());
    ASSERT_EQ(holo::common::RoadCategory(16777219U), lane_vector[0][0].GetRoadCategory());
    ASSERT_EQ(holo::common::LaneCategory(50331648U), lane_vector[0][0].GetLaneCategory());
    ASSERT_EQ(LaneItem::LaneMark::U_TURN_RIGHT, lane_vector[0][0].GetLaneMark());
    ASSERT_EQ(LaneItem::LaneModel::MERGE_FROM, lane_vector[0][0].GetLaneModel());
    ASSERT_EQ(holo::geometry::Point2(23U, 68U), lane_vector[0][0].GetStartDirection());
    ASSERT_EQ(holo::geometry::Point2(435U, 2469U), lane_vector[0][0].GetEndDirection());

    ASSERT_EQ(10U, lane_vector[1][0].GetLaneId());
    ASSERT_EQ(13.5, lane_vector[1][0].GetLength());
    ASSERT_EQ(holo::common::RoadCategory(1677219U), lane_vector[1][0].GetRoadCategory());
    ASSERT_EQ(holo::common::LaneCategory(5033648U), lane_vector[1][0].GetLaneCategory());
    ASSERT_EQ(LaneItem::LaneMark::LEFT, lane_vector[1][0].GetLaneMark());
    ASSERT_EQ(LaneItem::LaneModel::MERGE_TO, lane_vector[1][0].GetLaneModel());
    ASSERT_EQ(holo::geometry::Point2(23U, 68U), lane_vector[1][0].GetStartDirection());
    ASSERT_EQ(holo::geometry::Point2(435U, 2469U), lane_vector[1][0].GetEndDirection());
}

TEST(Advice, GetSerializedSize)
{
    Advice advice;
    ASSERT_EQ(4, advice.GetSerializedSize<4U>());
    ASSERT_EQ(8, advice.GetSerializedSize<8U>());
}

TEST(Advice, SerializeAndDeserialize)
{
    LaneItem lane_item1(5U, 3.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(50331648U),
                        LaneItem::LaneMark::U_TURN_RIGHT, LaneItem::LaneModel::MERGE_FROM, true, {23U, 68U}, {435U, 2469U});
    LaneItem lane_item2(10U, 13.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(5033648U),
                        LaneItem::LaneMark::LEFT, LaneItem::LaneModel::MERGE_TO, true, {23U, 68U}, {435U, 2469U});
    LaneItem lane_item3(50U, 30.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(503316480U),
                        LaneItem::LaneMark::RIGHT, LaneItem::LaneModel::SPLIT, true, {23U, 68U}, {435U, 2469U});
    LaneItem lane_item4(100U, 130.5, holo::common::RoadCategory(16777219U), holo::common::LaneCategory(50336480U),
                        LaneItem::LaneMark::STRAIGHT, LaneItem::LaneModel::SPLIT_LEFT, true, {23U, 68U}, {435U, 2469U});

    LanePath lane_path1(5U, -1, LanePath::TerminationType::EXTEND_ROUTE);
    LanePath lane_path2(10U, -2U, LanePath::TerminationType::EXTEND_ROUTE);

    lane_path1.push_back(lane_item1);
    lane_path1.push_back(lane_item2);

    lane_path2.push_back(lane_item3);
    lane_path2.push_back(lane_item4);

    Advice advice, advice_output;
    advice.PushBackLanePath(lane_path1);
    advice.PushBackLanePath(lane_path2);

    uint8_t                           buffer[10240];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << advice;
    ASSERT_EQ(advice.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> advice_output;

    ASSERT_EQ(2, advice_output.GetLanePathSize());
    ASSERT_EQ(lane_path1.GetId(), advice_output.GetLanePath(0).GetId());
    ASSERT_EQ(lane_path1.GetSequenceNumber(), advice_output.GetLanePath(0).GetSequenceNumber());
    ASSERT_EQ(lane_path1.GetTerminationType(), advice_output.GetLanePath(0).GetTerminationType());

    ASSERT_EQ(lane_item1.GetLaneId(), advice_output.GetLanePath(0)[0].GetLaneId());
    ASSERT_EQ(lane_item1.GetLength(), advice_output.GetLanePath(0)[0].GetLength());
    ASSERT_EQ(lane_item1.GetRoadCategory(), advice_output.GetLanePath(0)[0].GetRoadCategory());
    ASSERT_EQ(lane_item1.GetLaneCategory(), advice_output.GetLanePath(0)[0].GetLaneCategory());
    ASSERT_EQ(lane_item1.GetLaneMark(), advice_output.GetLanePath(0)[0].GetLaneMark());
    ASSERT_EQ(lane_item1.GetLaneModel(), advice_output.GetLanePath(0)[0].GetLaneModel());
    ASSERT_EQ(lane_item1.IsIntersection(), advice_output.GetLanePath(0)[0].IsIntersection());
    ASSERT_EQ(lane_item1.GetStartDirection(), advice_output.GetLanePath(0)[0].GetStartDirection());
    ASSERT_EQ(lane_item1.GetEndDirection(), advice_output.GetLanePath(0)[0].GetEndDirection());

    ASSERT_EQ(lane_item2.GetLaneId(), advice_output.GetLanePath(0)[1].GetLaneId());
    ASSERT_EQ(lane_item2.GetLength(), advice_output.GetLanePath(0)[1].GetLength());
    ASSERT_EQ(lane_item2.GetRoadCategory(), advice_output.GetLanePath(0)[1].GetRoadCategory());
    ASSERT_EQ(lane_item2.GetLaneCategory(), advice_output.GetLanePath(0)[1].GetLaneCategory());
    ASSERT_EQ(lane_item2.GetLaneMark(), advice_output.GetLanePath(0)[1].GetLaneMark());
    ASSERT_EQ(lane_item2.GetLaneModel(), advice_output.GetLanePath(0)[1].GetLaneModel());
    ASSERT_EQ(lane_item2.IsIntersection(), advice_output.GetLanePath(0)[1].IsIntersection());
    ASSERT_EQ(lane_item2.GetStartDirection(), advice_output.GetLanePath(0)[1].GetStartDirection());
    ASSERT_EQ(lane_item2.GetEndDirection(), advice_output.GetLanePath(0)[1].GetEndDirection());

    ASSERT_EQ(lane_path2.GetId(), advice_output.GetLanePath(1).GetId());
    ASSERT_EQ(lane_path2.GetSequenceNumber(), advice_output.GetLanePath(1).GetSequenceNumber());
    ASSERT_EQ(lane_path2.GetTerminationType(), advice_output.GetLanePath(0).GetTerminationType());

    ASSERT_EQ(lane_item3.GetLaneId(), advice_output.GetLanePath(1)[0].GetLaneId());
    ASSERT_EQ(lane_item3.GetLength(), advice_output.GetLanePath(1)[0].GetLength());
    ASSERT_EQ(lane_item3.GetRoadCategory(), advice_output.GetLanePath(1)[0].GetRoadCategory());
    ASSERT_EQ(lane_item3.GetLaneCategory(), advice_output.GetLanePath(1)[0].GetLaneCategory());
    ASSERT_EQ(lane_item3.GetLaneMark(), advice_output.GetLanePath(1)[0].GetLaneMark());
    ASSERT_EQ(lane_item3.GetLaneModel(), advice_output.GetLanePath(1)[0].GetLaneModel());
    ASSERT_EQ(lane_item3.IsIntersection(), advice_output.GetLanePath(1)[0].IsIntersection());
    ASSERT_EQ(lane_item3.GetStartDirection(), advice_output.GetLanePath(1)[0].GetStartDirection());
    ASSERT_EQ(lane_item3.GetEndDirection(), advice_output.GetLanePath(1)[0].GetEndDirection());

    ASSERT_EQ(lane_item4.GetLaneId(), advice_output.GetLanePath(1)[1].GetLaneId());
    ASSERT_EQ(lane_item4.GetLength(), advice_output.GetLanePath(1)[1].GetLength());
    ASSERT_EQ(lane_item4.GetRoadCategory(), advice_output.GetLanePath(1)[1].GetRoadCategory());
    ASSERT_EQ(lane_item4.GetLaneCategory(), advice_output.GetLanePath(1)[1].GetLaneCategory());
    ASSERT_EQ(lane_item4.GetLaneMark(), advice_output.GetLanePath(1)[1].GetLaneMark());
    ASSERT_EQ(lane_item4.GetLaneModel(), advice_output.GetLanePath(1)[1].GetLaneModel());
    ASSERT_EQ(lane_item4.IsIntersection(), advice_output.GetLanePath(1)[1].IsIntersection());
    ASSERT_EQ(lane_item4.GetStartDirection(), advice_output.GetLanePath(1)[1].GetStartDirection());
    ASSERT_EQ(lane_item4.GetEndDirection(), advice_output.GetLanePath(1)[1].GetEndDirection());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
