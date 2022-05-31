/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_ref_point_attributes.cpp
 * @brief Unit test for road attributes.
 * @author lisong(lisong@holomaitc.com)
 * @date "2020-08-04"
 */

#include <gtest/gtest.h>
#include <holo/map/road_ref_point_attributes.h>

using Serializer   = holo::serialization::Serializer<false, 4>;
using Deserializer = holo::serialization::Deserializer<false, 4>;

using holo::common::Coordinate;

using holo::map::RoadScs;
using holo::map::RoadTypeInterval;

template <typename T, std::size_t MAX_SIZE = 1024U>
using RoadRefPointAttributes = holo::map::RoadRefPointAttributes<T, MAX_SIZE>;

using RoadRefPointScssesType        = RoadRefPointAttributes<RoadScs>;
using RoadRefPointTypeIntervalsType = RoadRefPointAttributes<RoadTypeInterval>;

/// For RoadScs
TEST(RoadScs, DefaultConstructor)
{
    RoadScs road_scs;
    EXPECT_FLOAT_EQ(road_scs.GetDistance(), 0.0f);
    EXPECT_FLOAT_EQ(road_scs.GetSlope(), 0.0f);
    EXPECT_FLOAT_EQ(road_scs.GetCurvatureRadius(), 0.0f);
    EXPECT_FLOAT_EQ(road_scs.GetSuperelevation(), 0.0f);
}

TEST(RoadScs, ConstructorWithParameters)
{
    RoadScs road_scs{100.0f, 0.01f, 500.0f, 0.05f};
    EXPECT_FLOAT_EQ(road_scs.GetDistance(), 100.0f);
    EXPECT_FLOAT_EQ(road_scs.GetSlope(), 0.01f);
    EXPECT_FLOAT_EQ(road_scs.GetCurvatureRadius(), 500.0f);
    EXPECT_FLOAT_EQ(road_scs.GetSuperelevation(), 0.05f);
}

TEST(RoadScs, CopyConstructor)
{
    RoadScs road_scs01{100.0f, 0.01f, 500.0f, 0.05f};
    EXPECT_FLOAT_EQ(road_scs01.GetDistance(), 100.0f);
    EXPECT_FLOAT_EQ(road_scs01.GetSlope(), 0.01f);
    EXPECT_FLOAT_EQ(road_scs01.GetCurvatureRadius(), 500.0f);
    EXPECT_FLOAT_EQ(road_scs01.GetSuperelevation(), 0.05f);

    RoadScs road_scs02(road_scs01);
    EXPECT_FLOAT_EQ(road_scs01.GetDistance(), road_scs02.GetDistance());
    EXPECT_FLOAT_EQ(road_scs01.GetSlope(), road_scs02.GetSlope());
    EXPECT_FLOAT_EQ(road_scs01.GetCurvatureRadius(), road_scs02.GetCurvatureRadius());
    EXPECT_FLOAT_EQ(road_scs01.GetSuperelevation(), road_scs02.GetSuperelevation());
}

TEST(RoadScs, MoveConstructor)
{
    RoadScs road_scs01{100.0f, 0.01f, 500.0f, 0.05f};
    EXPECT_FLOAT_EQ(road_scs01.GetDistance(), 100.0f);
    EXPECT_FLOAT_EQ(road_scs01.GetSlope(), 0.01f);
    EXPECT_FLOAT_EQ(road_scs01.GetCurvatureRadius(), 500.0f);
    EXPECT_FLOAT_EQ(road_scs01.GetSuperelevation(), 0.05f);

    RoadScs road_scs02(std::move(road_scs01));
    EXPECT_FLOAT_EQ(road_scs02.GetDistance(), 100.0f);
    EXPECT_FLOAT_EQ(road_scs02.GetSlope(), 0.01f);
    EXPECT_FLOAT_EQ(road_scs02.GetCurvatureRadius(), 500.0f);
    EXPECT_FLOAT_EQ(road_scs02.GetSuperelevation(), 0.05f);
}

TEST(RoadScs, CopyAssignOperator)
{
    RoadScs road_scs01;

    RoadScs road_scs02{100.0f, 0.01f, 500.0f, 0.05f};
    road_scs01 = road_scs02;

    EXPECT_FLOAT_EQ(road_scs01.GetDistance(), road_scs02.GetDistance());
    EXPECT_FLOAT_EQ(road_scs01.GetSlope(), road_scs02.GetSlope());
    EXPECT_FLOAT_EQ(road_scs01.GetCurvatureRadius(), road_scs02.GetCurvatureRadius());
    EXPECT_FLOAT_EQ(road_scs01.GetSuperelevation(), road_scs02.GetSuperelevation());
}

TEST(RoadScs, MoveAssignOperator)
{
    RoadScs road_scs01;

    RoadScs road_scs02{100.0f, 0.01f, 500.0f, 0.05f};
    road_scs01 = std::move(road_scs02);

    EXPECT_FLOAT_EQ(road_scs01.GetDistance(), 100.0f);
    EXPECT_FLOAT_EQ(road_scs01.GetSlope(), 0.01f);
    EXPECT_FLOAT_EQ(road_scs01.GetCurvatureRadius(), 500.0f);
    EXPECT_FLOAT_EQ(road_scs01.GetSuperelevation(), 0.05f);
}

TEST(RoadScs, GetDistance)
{
    RoadScs road_scs{100.0f, 0.01f, 500.0f, 0.05f};
    EXPECT_FLOAT_EQ(road_scs.GetDistance(), 100.0f);
}

TEST(RoadScs, SetDistance)
{
    RoadScs road_scs;
    road_scs.SetDistance(500.0f);
    EXPECT_FLOAT_EQ(road_scs.GetDistance(), 500.0f);
}

TEST(RoadScs, GetSlope)
{
    RoadScs road_scs{100.0f, 0.01f, 500.0f, 0.05f};
    EXPECT_FLOAT_EQ(road_scs.GetSlope(), 0.01f);
}

TEST(RoadScs, SetSlope)
{
    RoadScs road_scs;
    road_scs.SetSlope(0.05f);
    EXPECT_FLOAT_EQ(road_scs.GetSlope(), 0.05f);
}

TEST(RoadScs, GetCurvatureRadius)
{
    RoadScs road_scs{100.0f, 0.01f, 500.0f, 0.05f};
    EXPECT_FLOAT_EQ(road_scs.GetCurvatureRadius(), 500.0f);
}

TEST(RoadScs, SetCurvature)
{
    RoadScs road_scs;
    road_scs.SetCurvatureRadius(1000.0f);
    EXPECT_FLOAT_EQ(road_scs.GetCurvatureRadius(), 1000.0f);
}

TEST(RoadScs, GetSuperelevation)
{
    RoadScs road_scs{100.0f, 0.01f, 500.0f, 0.05f};
    EXPECT_FLOAT_EQ(road_scs.GetSuperelevation(), 0.05f);
}

TEST(RoadScs, SetSuperelevation)
{
    RoadScs road_scs;
    road_scs.SetSuperelevation(0.08f);
    EXPECT_FLOAT_EQ(road_scs.GetSuperelevation(), 0.08f);
}

TEST(RoadScs, CompareOperator)
{
    RoadScs road_scs01;
    RoadScs road_scs02;

    bool is_equal = (road_scs01 == road_scs02);
    EXPECT_EQ(is_equal, true);

    road_scs02.SetDistance(500.0f);
    road_scs02.SetSlope(0.05f);
    road_scs02.SetCurvatureRadius(1000.0f);
    road_scs02.SetSuperelevation(0.08f);

    is_equal = (road_scs01 == road_scs02);
    EXPECT_EQ(is_equal, false);
}

TEST(RoadScs, GetSerializedSize)
{
    RoadScs road_scs{100.0f, 0.01f, 500.0f, 0.05f};

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_scs.Serialize(serializer);
    EXPECT_EQ(road_scs.GetSerializedSize(), serializer.GetSize());
}

TEST(RoadScs, Serialization)
{
    RoadScs road_scss_s{100.0f, 0.01f, 500.0f, 0.05f};

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_scss_s.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    RoadScs      road_scss_d;
    road_scss_d.Deserialize(deserializer);

    EXPECT_EQ(road_scss_d, road_scss_d);
}

// For RoadTypeInterval
using holo::common::RoadCategory;

TEST(RoadTypeInterval, DefaultConstructor)
{
    RoadTypeInterval road_type_interval;
    EXPECT_EQ(road_type_interval.GetInterval(), RoadTypeInterval::IntervalType());
    EXPECT_EQ(road_type_interval.GetRoadCategory(), RoadCategory());
}

TEST(RoadTypeInterval, ConstructorWithParameters)
{
    RoadTypeInterval road_type_interval{RoadTypeInterval::IntervalType(100.0f, 500.0f), RoadCategory(16777219U)};
    EXPECT_EQ(road_type_interval.GetInterval(), RoadTypeInterval::IntervalType(100.0f, 500.0f));
    EXPECT_EQ(road_type_interval.GetRoadCategory(), RoadCategory(16777219U));
}

TEST(RoadTypeInterval, CopyConstructor)
{
    RoadTypeInterval road_type_interval01{RoadTypeInterval::IntervalType(100.0f, 500.0f), RoadCategory(16777219U)};
    RoadTypeInterval road_type_interval02(road_type_interval01);

    EXPECT_EQ(road_type_interval02.GetInterval(), road_type_interval01.GetInterval());
    EXPECT_EQ(road_type_interval02.GetRoadCategory(), road_type_interval01.GetRoadCategory());
}

TEST(RoadTypeInterval, MoveConstructor)
{
    RoadTypeInterval road_type_interval01{RoadTypeInterval::IntervalType(100.0f, 500.0f), RoadCategory(16777219U)};
    RoadTypeInterval road_type_interval02(std::move(road_type_interval01));

    EXPECT_EQ(road_type_interval02.GetInterval(), RoadTypeInterval::IntervalType(100.0f, 500.0f));
    EXPECT_EQ(road_type_interval02.GetRoadCategory(), RoadCategory(16777219U));
}

TEST(RoadTypeInterval, CopyAssignOperator)
{
    RoadTypeInterval road_type_interval01{RoadTypeInterval::IntervalType(100.0f, 500.0f), RoadCategory(16777219U)};

    RoadTypeInterval road_type_interval02;
    road_type_interval02 = road_type_interval01;

    EXPECT_EQ(road_type_interval02.GetInterval(), road_type_interval01.GetInterval());
    EXPECT_EQ(road_type_interval02.GetRoadCategory(), road_type_interval01.GetRoadCategory());
}

TEST(RoadTypeInterval, MoveAssignOperator)
{
    RoadTypeInterval road_type_interval01{RoadTypeInterval::IntervalType(100.0f, 500.0f), RoadCategory(16777219U)};

    RoadTypeInterval road_type_interval02;
    road_type_interval02 = std::move(road_type_interval01);

    EXPECT_EQ(road_type_interval02.GetInterval(), RoadTypeInterval::IntervalType(100.0f, 500.0f));
    EXPECT_EQ(road_type_interval02.GetRoadCategory(), RoadCategory(16777219U));
}

TEST(RoadTypeInterval, GetInterval)
{
    RoadTypeInterval road_type_interval;
    EXPECT_EQ(road_type_interval.GetInterval(), RoadTypeInterval::IntervalType());
}

TEST(RoadTypeInterval, SetInterval)
{
    RoadTypeInterval road_type_interval;
    road_type_interval.SetInterval(RoadTypeInterval::IntervalType(500.0f, 2000.0f));
    EXPECT_EQ(road_type_interval.GetInterval(), RoadTypeInterval::IntervalType(500.0f, 2000.0f));
}

TEST(RoadTypeInterval, GetRoadCategory)
{
    RoadTypeInterval road_type_interval;
    EXPECT_EQ(road_type_interval.GetRoadCategory(), RoadCategory());
}

TEST(RoadTypeInterval, SetRoadCategory)
{
    RoadTypeInterval road_type_interval;
    road_type_interval.SetRoadCategory(RoadCategory(16777219U));
    EXPECT_EQ(road_type_interval.GetRoadCategory(), RoadCategory(16777219U));
}

TEST(RoadTypeInterval, SetRoadType)
{
    RoadTypeInterval       road_type_interval;
    holo::common::RoadType road_type(16777219U);
    road_type_interval.SetRoadType(road_type);
    EXPECT_EQ(road_type_interval.GetRoadCategory().GetValue(), road_type.GetValue());
    EXPECT_THROW(road_type_interval.GetRoadType(), std::runtime_error);
}

TEST(RoadTypeInterval, CompareOperator)
{
    RoadTypeInterval road_type_interval01;
    RoadTypeInterval road_type_interval02;

    bool is_equal = (road_type_interval01 == road_type_interval02);
    EXPECT_EQ(is_equal, true);

    road_type_interval02.SetInterval(RoadTypeInterval::IntervalType(500.0f, 2000.0f));
    road_type_interval02.SetRoadCategory(RoadCategory(16777219U));

    is_equal = (road_type_interval01 == road_type_interval02);
    EXPECT_EQ(is_equal, false);
}

TEST(RoadTypeInterval, GetSerializedSize)
{
    RoadTypeInterval road_type_interval{RoadTypeInterval::IntervalType(100.0f, 500.0f), RoadCategory(16777219U)};

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_type_interval.Serialize(serializer);
    EXPECT_EQ(road_type_interval.GetSerializedSize(), serializer.GetSize());
}

TEST(RoadTypeInterval, Serialization)
{
    RoadTypeInterval road_type_interval_s{RoadTypeInterval::IntervalType(100.0f, 500.0f), RoadCategory(16777219U)};

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_type_interval_s.Serialize(serializer);

    Deserializer     deserializer(buffer, serializer.GetSize());
    RoadTypeInterval road_type_interval_d;
    road_type_interval_d.Deserialize(deserializer);

    EXPECT_EQ(road_type_interval_d, road_type_interval_s);
}

// For RoadRefPointScssesType
TEST(RoadRefPointScssesType, DefaultConstructor)
{
    RoadRefPointScssesType road_scsses;
    EXPECT_EQ(road_scsses.GetTimestamp(), holo::Timestamp());
    EXPECT_EQ(road_scsses.GetRefPoint(), RoadRefPointScssesType::PointType());
    EXPECT_EQ(road_scsses.GetCoordinate(), Coordinate());
    EXPECT_EQ(road_scsses.size(), 0U);
}

TEST(RoadRefPointScssesType, CopyConstructor)
{
    RoadRefPointScssesType road_scsses;
    road_scsses.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_scsses.SetRefPoint(RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
    road_scsses.SetCoordinate(Coordinate(2 << 28));
    road_scsses.emplace_back(100.0f, 0.01f, 1000.0f, 0.08f);

    RoadRefPointScssesType road_scsses02(road_scsses);
    EXPECT_EQ(road_scsses.GetTimestamp(), road_scsses02.GetTimestamp());
    EXPECT_EQ(road_scsses.GetRefPoint(), road_scsses02.GetRefPoint());
    EXPECT_EQ(road_scsses.GetCoordinate(), road_scsses02.GetCoordinate());
    EXPECT_EQ(road_scsses, road_scsses02);
}

TEST(RoadRefPointScssesType, MoveConstructor)
{
    RoadRefPointScssesType road_scsses;
    road_scsses.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_scsses.SetRefPoint(RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
    road_scsses.SetCoordinate(Coordinate(2 << 28));
    road_scsses.emplace_back(100.0f, 0.01f, 1000.0f, 0.08f);

    RoadRefPointScssesType road_scsses02(std::move(road_scsses));
    EXPECT_EQ(road_scsses02.GetTimestamp(), holo::Timestamp(1000U, 100000U));
    EXPECT_EQ(road_scsses02.GetRefPoint(), RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
    EXPECT_EQ(road_scsses02.GetCoordinate(), Coordinate(2 << 28));
    ASSERT_EQ(road_scsses02.size(), 1U);
    ASSERT_EQ(road_scsses02.at(0U), RoadScs(100.0f, 0.01f, 1000.0f, 0.08f));
}

TEST(RoadRefPointScssesType, CopyAssignOperator)
{
    RoadRefPointScssesType road_scsses;
    road_scsses.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_scsses.SetRefPoint(RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
    road_scsses.SetCoordinate(Coordinate(2 << 28));
    road_scsses.emplace_back(100.0f, 0.01f, 1000.0f, 0.08f);

    RoadRefPointScssesType road_scsses02;
    road_scsses02 = road_scsses;
    EXPECT_EQ(road_scsses.GetTimestamp(), road_scsses02.GetTimestamp());
    EXPECT_EQ(road_scsses.GetRefPoint(), road_scsses02.GetRefPoint());
    EXPECT_EQ(road_scsses.GetCoordinate(), road_scsses02.GetCoordinate());
    EXPECT_EQ(road_scsses, road_scsses02);
}

TEST(RoadRefPointScssesType, MoveAssignOperator)
{
    RoadRefPointScssesType road_scsses;
    road_scsses.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_scsses.SetRefPoint(RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
    road_scsses.SetCoordinate(Coordinate(2 << 28));
    road_scsses.emplace_back(100.0f, 0.01f, 1000.0f, 0.08f);

    RoadRefPointScssesType road_scsses02;
    road_scsses02 = std::move(road_scsses);
    EXPECT_EQ(road_scsses02.GetTimestamp(), holo::Timestamp(1000U, 100000U));
    EXPECT_EQ(road_scsses02.GetRefPoint(), RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
    EXPECT_EQ(road_scsses02.GetCoordinate(), Coordinate(2 << 28));
    ASSERT_EQ(road_scsses02.size(), 1U);
    ASSERT_EQ(road_scsses02.at(0U), RoadScs(100.0f, 0.01f, 1000.0f, 0.08f));
}

TEST(RoadRefPointScssesType, InitializerConstructor)
{
    RoadRefPointScssesType road_scsses{{0.0, 1.0, 1.0, 1.0}, {1.0, 2.0, 2.0, 2.0}, {2.0, 3.0, 3.0, 3.0}};
    ASSERT_EQ(3U, road_scsses.size());
    ASSERT_EQ((RoadScs{0.0, 1.0, 1.0, 1.0}), road_scsses[0]);
    road_scsses.emplace_back(3.0, 4.0, 4.0, 4.0);
    ASSERT_EQ((RoadScs{3.0, 4.0, 4.0, 4.0}), road_scsses.back());
    road_scsses.push_back({3.0, 4.0, 4.0, 5.0});
    ASSERT_EQ((RoadScs{3.0, 4.0, 4.0, 5.0}), road_scsses.back());
}

TEST(RoadRefPointScssesType, GetTimestamp)
{
    RoadRefPointScssesType road_scsses;
    EXPECT_EQ(road_scsses.GetTimestamp(), holo::Timestamp());
}

TEST(RoadRefPointScssesType, SetTimestamp)
{
    RoadRefPointScssesType road_scsses;
    road_scsses.SetTimestamp(holo::Timestamp(1000U, 100000U));
    EXPECT_EQ(road_scsses.GetTimestamp(), holo::Timestamp(1000U, 100000U));
}

TEST(RoadRefPointScssesType, GetRefPoint)
{
    RoadRefPointScssesType road_scsses;
    EXPECT_EQ(road_scsses.GetRefPoint(), RoadRefPointScssesType::PointType());
}

TEST(RoadRefPointScssesType, SetRefPoint)
{
    RoadRefPointScssesType road_scsses;
    road_scsses.SetRefPoint(RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
    EXPECT_EQ(road_scsses.GetRefPoint(), RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
}

TEST(RoadRefPointScssesType, GetCoordinate)
{
    RoadRefPointScssesType road_scsses;
    EXPECT_EQ(road_scsses.GetCoordinate(), Coordinate());
}

TEST(RoadRefPointScssesType, SetCoordinate)
{
    RoadRefPointScssesType road_scsses;
    road_scsses.SetCoordinate(Coordinate(2 << 28));
    EXPECT_EQ(road_scsses.GetCoordinate(), Coordinate(2 << 28));
}

TEST(RoadRefPointScssesType, GetSerializedSize)
{
    RoadRefPointScssesType road_scsses;
    road_scsses.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_scsses.SetRefPoint(RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
    road_scsses.SetCoordinate(Coordinate(2 << 28));
    road_scsses.emplace_back(100.0f, 0.01f, 1000.0f, 0.08f);

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_scsses.Serialize(serializer);
    EXPECT_EQ(road_scsses.GetSerializedSize(), serializer.GetSize());
}

TEST(RoadRefPointScssesType, Serialization)
{
    RoadRefPointScssesType road_scsses_s;
    road_scsses_s.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_scsses_s.SetRefPoint(RoadRefPointScssesType::PointType(200.0f, 200.0f, 200.0f));
    road_scsses_s.SetCoordinate(Coordinate(2 << 28));
    road_scsses_s.emplace_back(100.0f, 0.01f, 1000.0f, 0.08f);

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_scsses_s.Serialize(serializer);

    Deserializer           deserializer(buffer, serializer.GetSize());
    RoadRefPointScssesType road_scsses_d;
    road_scsses_d.Deserialize(deserializer);

    EXPECT_EQ(road_scsses_s.GetTimestamp(), road_scsses_d.GetTimestamp());
    EXPECT_EQ(road_scsses_s.GetRefPoint(), road_scsses_d.GetRefPoint());
    EXPECT_EQ(road_scsses_s.GetCoordinate(), road_scsses_d.GetCoordinate());

    EXPECT_EQ(road_scsses_d, road_scsses_s);
}

// For RoadRefPointTypeIntervalsType
TEST(RoadRefPointTypeIntervalsType, DefaultConstructor)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    EXPECT_EQ(road_type_intervals.GetTimestamp(), holo::Timestamp());
    EXPECT_EQ(road_type_intervals.GetRefPoint(), RoadRefPointTypeIntervalsType::PointType());
    EXPECT_EQ(road_type_intervals.GetCoordinate(), Coordinate());
    EXPECT_EQ(road_type_intervals.size(), 0U);
}

TEST(RoadRefPointTypeIntervalsType, CopyConstructor)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    road_type_intervals.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_type_intervals.SetRefPoint(RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
    road_type_intervals.SetCoordinate(Coordinate(2 << 28));
    road_type_intervals.emplace_back(RoadTypeInterval::IntervalType{0.0, 100.0}, RoadCategory(16777219U));

    RoadRefPointTypeIntervalsType road_type_intervals02(road_type_intervals);
    EXPECT_EQ(road_type_intervals.GetTimestamp(), road_type_intervals02.GetTimestamp());
    EXPECT_EQ(road_type_intervals.GetRefPoint(), road_type_intervals02.GetRefPoint());
    EXPECT_EQ(road_type_intervals.GetCoordinate(), road_type_intervals02.GetCoordinate());
    EXPECT_EQ(road_type_intervals, road_type_intervals02);
}

TEST(RoadRefPointTypeIntervalsType, MoveConstructor)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    road_type_intervals.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_type_intervals.SetRefPoint(RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
    road_type_intervals.SetCoordinate(Coordinate(2 << 28));
    road_type_intervals.emplace_back(RoadTypeInterval::IntervalType{0.0, 100.0}, RoadCategory(16777219U));

    RoadRefPointTypeIntervalsType road_type_intervals02(std::move(road_type_intervals));
    EXPECT_EQ(road_type_intervals02.GetTimestamp(), holo::Timestamp(1000U, 100000U));
    EXPECT_EQ(road_type_intervals02.GetRefPoint(), RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
    EXPECT_EQ(road_type_intervals02.GetCoordinate(), Coordinate(2 << 28));
    ASSERT_EQ(road_type_intervals02.size(), 1U);
    ASSERT_EQ(road_type_intervals02.at(0U),
              RoadTypeInterval(RoadTypeInterval::IntervalType{0.0, 100.0}, RoadCategory(16777219U)));
}

TEST(RoadRefPointTypeIntervalsType, CopyAssignOperator)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    road_type_intervals.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_type_intervals.SetRefPoint(RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
    road_type_intervals.SetCoordinate(Coordinate(2 << 28));
    road_type_intervals.emplace_back(RoadTypeInterval::IntervalType{0.0, 100.0}, RoadCategory(16777219U));

    RoadRefPointTypeIntervalsType road_type_intervals02;
    road_type_intervals02 = road_type_intervals;
    EXPECT_EQ(road_type_intervals.GetTimestamp(), road_type_intervals02.GetTimestamp());
    EXPECT_EQ(road_type_intervals.GetRefPoint(), road_type_intervals02.GetRefPoint());
    EXPECT_EQ(road_type_intervals.GetCoordinate(), road_type_intervals02.GetCoordinate());
    EXPECT_EQ(road_type_intervals, road_type_intervals02);
}

TEST(RoadRefPointTypeIntervalsType, MoveAssignOperator)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    road_type_intervals.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_type_intervals.SetRefPoint(RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
    road_type_intervals.SetCoordinate(Coordinate(2 << 28));
    road_type_intervals.emplace_back(RoadTypeInterval::IntervalType{0.0, 100.0}, RoadCategory(16777219U));

    RoadRefPointTypeIntervalsType road_type_intervals02;
    road_type_intervals02 = std::move(road_type_intervals);
    EXPECT_EQ(road_type_intervals02.GetTimestamp(), holo::Timestamp(1000U, 100000U));
    EXPECT_EQ(road_type_intervals02.GetRefPoint(), RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
    EXPECT_EQ(road_type_intervals02.GetCoordinate(), Coordinate(2 << 28));
    ASSERT_EQ(road_type_intervals02.size(), 1U);
    ASSERT_EQ(road_type_intervals02.at(0U),
              RoadTypeInterval(RoadTypeInterval::IntervalType{0.0, 100.0}, RoadCategory(16777219U)));
}

TEST(RoadRefPointTypeIntervalsType, InitializerConstructor)
{
    RoadRefPointTypeIntervalsType road_type_intervals{
        {RoadTypeInterval::IntervalType{0.0, 100.0}, RoadCategory(16777219U)},
        {RoadTypeInterval::IntervalType{100.0, 200.0}, RoadCategory(16777219U)},
        {RoadTypeInterval::IntervalType{200.0, 300.0}, RoadCategory(16777219U)}};
    ASSERT_EQ(3U, road_type_intervals.size());
    ASSERT_EQ((RoadTypeInterval{RoadTypeInterval::IntervalType{0.0, 100.0}, RoadCategory(16777219U)}),
              road_type_intervals[0]);
    road_type_intervals.emplace_back(RoadTypeInterval::IntervalType{300.0, 400.0}, RoadCategory(16777219U));
    ASSERT_EQ((RoadTypeInterval{RoadTypeInterval::IntervalType{300.0, 400.0}, RoadCategory(16777219U)}),
              road_type_intervals.back());
    road_type_intervals.push_back({RoadTypeInterval::IntervalType{400.0, 500.0}, RoadCategory(16777219U)});
    ASSERT_EQ((RoadTypeInterval{RoadTypeInterval::IntervalType{400.0, 500.0}, RoadCategory(16777219U)}),
              road_type_intervals.back());
}

TEST(RoadRefPointTypeIntervalsType, GetTimestamp)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    EXPECT_EQ(road_type_intervals.GetTimestamp(), holo::Timestamp());
}

TEST(RoadRefPointTypeIntervalsType, SetTimestamp)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    road_type_intervals.SetTimestamp(holo::Timestamp(1000U, 100000U));
    EXPECT_EQ(road_type_intervals.GetTimestamp(), holo::Timestamp(1000U, 100000U));
}

TEST(RoadRefPointTypeIntervalsType, GetRefPoint)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    EXPECT_EQ(road_type_intervals.GetRefPoint(), RoadRefPointTypeIntervalsType::PointType());
}

TEST(RoadRefPointTypeIntervalsType, SetRefPoint)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    road_type_intervals.SetRefPoint(RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
    EXPECT_EQ(road_type_intervals.GetRefPoint(), RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
}

TEST(RoadRefPointTypeIntervalsType, GetCoordinate)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    EXPECT_EQ(road_type_intervals.GetCoordinate(), Coordinate());
}

TEST(RoadRefPointTypeIntervalsType, SetCoordinate)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    road_type_intervals.SetCoordinate(Coordinate(2 << 28));
    EXPECT_EQ(road_type_intervals.GetCoordinate(), Coordinate(2 << 28));
}

TEST(RoadRefPointTypeIntervalsType, GetSerializedSize)
{
    RoadRefPointTypeIntervalsType road_type_intervals;
    road_type_intervals.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_type_intervals.SetRefPoint(RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
    road_type_intervals.SetCoordinate(Coordinate(2 << 28));
    road_type_intervals.emplace_back(RoadTypeInterval::IntervalType{300.0, 400.0}, RoadCategory(16777219U));

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_type_intervals.Serialize(serializer);
    EXPECT_EQ(road_type_intervals.GetSerializedSize(), serializer.GetSize());
}

TEST(RoadRefPointTypeIntervalsType, Serialization)
{
    RoadRefPointTypeIntervalsType road_type_intervals_s;
    road_type_intervals_s.SetTimestamp(holo::Timestamp(1000U, 100000U));
    road_type_intervals_s.SetRefPoint(RoadRefPointTypeIntervalsType::PointType(200.0f, 200.0f, 200.0f));
    road_type_intervals_s.SetCoordinate(Coordinate(2 << 28));
    road_type_intervals_s.emplace_back(RoadTypeInterval::IntervalType{0.0, 100.0}, RoadCategory(16777219U));

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    road_type_intervals_s.Serialize(serializer);

    Deserializer                  deserializer(buffer, serializer.GetSize());
    RoadRefPointTypeIntervalsType road_type_intervals_d;
    road_type_intervals_d.Deserialize(deserializer);

    EXPECT_EQ(road_type_intervals_s.GetTimestamp(), road_type_intervals_d.GetTimestamp());
    EXPECT_EQ(road_type_intervals_s.GetRefPoint(), road_type_intervals_d.GetRefPoint());
    EXPECT_EQ(road_type_intervals_s.GetCoordinate(), road_type_intervals_d.GetCoordinate());

    EXPECT_EQ(road_type_intervals_d, road_type_intervals_s);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
