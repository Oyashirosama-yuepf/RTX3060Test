/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_lane2.h
 * @brief This file tests Lane object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-06-17
 */

#include <gtest/gtest.h>
#include <holo/common/lane2.h>
#include <holo/common/lane_boundary2.h>
#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>

using ScalarType      = holo::float32_t;
using PointType       = holo::geometry::Point2T<ScalarType>;
using CurveType       = holo::geometry::CurvePolynomial<PointType, 64U, 3U>;
using CurvePtrType    = std::shared_ptr<CurveType>;
using LaneType        = holo::common::Lane<CurveType>;
using BoundaryType    = typename LaneType::BoundaryType;
using BoundaryPtrType = std::shared_ptr<BoundaryType>;
using MapAttributes   = LaneType::MapAttributes;
using Point2d         = holo::geometry::Point2T<holo::float64_t>;

TEST(Lane, DefaultConstructor)
{
    LaneType lane(0);
    ASSERT_FALSE(lane.HasLeftBoundary());
    ASSERT_FALSE(lane.HasRightBoundary());
}

TEST(Lane, SetGetLeftBoundary)
{
    LaneType        lane(0);
    CurvePtrType    curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, -1}, {10, -1}}));
    BoundaryPtrType bound = std::make_shared<BoundaryType>(0, 0, curve);

    ASSERT_FALSE(lane.HasLeftBoundary());

    lane.SetLeftBoundary(bound);
    ASSERT_TRUE(lane.HasLeftBoundary());
    bound->SetKnotRange(0, curve->size() - 1);

    BoundaryType&       ref_bound      = lane.GetLeftBoundary();
    BoundaryType const& constref_bound = lane.GetLeftBoundary();

    ASSERT_EQ(bound.get(), &ref_bound);
    ASSERT_EQ(bound.get(), &constref_bound);
}

TEST(Lane, SetGetRightBoundary)
{
    LaneType        lane(0);
    CurvePtrType    curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 1}, {10, 1}}));
    BoundaryPtrType bound = std::make_shared<BoundaryType>(0, 0, curve);

    ASSERT_FALSE(lane.HasRightBoundary());

    lane.SetRightBoundary(bound);
    ASSERT_TRUE(lane.HasRightBoundary());
    bound->SetKnotRange(0, curve->size() - 1);

    BoundaryType&       ref_bound      = lane.GetRightBoundary();
    BoundaryType const& constref_bound = lane.GetRightBoundary();

    ASSERT_EQ(bound.get(), &ref_bound);
    ASSERT_EQ(bound.get(), &constref_bound);
}

TEST(Lane, SetGetExternalId)
{
    LaneType lane(0);

    ASSERT_EQ(0, lane.GetExternalId());
    lane.SetExternalId(1);
    ASSERT_EQ(1, lane.GetExternalId());
}

TEST(Lane, SetGetSpeedLimit)
{
    LaneType lane(0);
    lane.SetSpeedLimit(10, 20);

    auto limits = lane.GetSpeedLimit();

    ASSERT_EQ(10, limits.first);
    ASSERT_EQ(20, limits.second);
    ASSERT_EQ(10, lane.GetMinSpeedLimit());
    ASSERT_EQ(20, lane.GetMaxSpeedLimit());
}

TEST(Lane, SetGetLength)
{
    LaneType lane(0);
    lane.SetLength(12345.67);

    ASSERT_FLOAT_EQ(12345.67, lane.GetLength());
}

TEST(Lane, SetGetRoadType)
{
    LaneType lane(0);

    holo::common::RoadType rt;
    rt.SetTypeMainRoad();
    lane.SetRoadType(rt);

    ASSERT_TRUE(lane.GetRoadType().IsTypeMainRoad());
    ASSERT_FALSE(lane.GetRoadType().IsTypeRamp());

    rt.SetTypeRamp();
    lane.SetRoadType(rt);
    ASSERT_FALSE(lane.GetRoadType().IsTypeMainRoad());
    ASSERT_TRUE(lane.GetRoadType().IsTypeRamp());
}

TEST(Lane, SetGetRoadCategory)
{
    LaneType lane(0);

    holo::common::RoadCategory rt;
    rt.SetCategoryMainRoad();
    lane.SetRoadCategory(rt);

    ASSERT_TRUE(lane.GetRoadCategory().IsCategoryMainRoad());
    ASSERT_FALSE(lane.GetRoadCategory().IsCategoryRamp());

    rt.SetCategoryRamp();
    lane.SetRoadCategory(rt);
    ASSERT_FALSE(lane.GetRoadCategory().IsCategoryMainRoad());
    ASSERT_TRUE(lane.GetRoadCategory().IsCategoryRamp());
}

TEST(Lane, SetGetLaneType)
{
    LaneType lane(0);

    holo::common::LaneType lt;
    lt.SetTypeUnknown();
    lane.SetLaneType(lt);
    ASSERT_TRUE(lane.GetLaneType().IsTypeUnknown());
    ASSERT_FALSE(lane.GetLaneType().IsTypeRegular());
    ASSERT_FALSE(lane.GetLaneType().IsTypeAcceleration());
    ASSERT_FALSE(lane.GetLaneType().IsTypeDeceleration());

    lt.SetTypeRegular();
    lane.SetLaneType(lt);
    ASSERT_FALSE(lane.GetLaneType().IsTypeUnknown());
    ASSERT_TRUE(lane.GetLaneType().IsTypeRegular());
    ASSERT_FALSE(lane.GetLaneType().IsTypeAcceleration());
    ASSERT_FALSE(lane.GetLaneType().IsTypeDeceleration());

    lt.SetTypeAcceleration();
    lane.SetLaneType(lt);
    ASSERT_FALSE(lane.GetLaneType().IsTypeUnknown());
    ASSERT_FALSE(lane.GetLaneType().IsTypeRegular());
    ASSERT_TRUE(lane.GetLaneType().IsTypeAcceleration());
    ASSERT_FALSE(lane.GetLaneType().IsTypeDeceleration());

    lt.SetTypeDeceleration();
    lane.SetLaneType(lt);
    ASSERT_FALSE(lane.GetLaneType().IsTypeUnknown());
    ASSERT_FALSE(lane.GetLaneType().IsTypeRegular());
    ASSERT_FALSE(lane.GetLaneType().IsTypeAcceleration());
    ASSERT_TRUE(lane.GetLaneType().IsTypeDeceleration());
}

TEST(Lane, SetGetLaneCategory)
{
    LaneType lane(0);

    holo::common::LaneCategory lt;
    lt.SetCategoryUnknown();
    lane.SetLaneCategory(lt);
    ASSERT_TRUE(lane.GetLaneCategory().IsCategoryUnknown());
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryRegular());
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryAcceleration());
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryDeceleration());

    lt.SetCategoryRegular();
    lane.SetLaneCategory(lt);
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryUnknown());
    ASSERT_TRUE(lane.GetLaneCategory().IsCategoryRegular());
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryAcceleration());
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryDeceleration());

    lt.SetCategoryAcceleration();
    lane.SetLaneCategory(lt);
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryUnknown());
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryRegular());
    ASSERT_TRUE(lane.GetLaneCategory().IsCategoryAcceleration());
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryDeceleration());

    lt.SetCategoryDeceleration();
    lane.SetLaneCategory(lt);
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryUnknown());
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryRegular());
    ASSERT_FALSE(lane.GetLaneCategory().IsCategoryAcceleration());
    ASSERT_TRUE(lane.GetLaneCategory().IsCategoryDeceleration());
}

TEST(Lane, SetAndGetMapAttributes)
{
    LaneType      lane(0);
    MapAttributes attr, attr2;

    std::array<Point2d, 4U> crosswalk1 = {Point2d(1.0f, 1.1f), Point2d(1.2f, 1.3f), Point2d(1.4f, 1.5f),
                                          Point2d(1.6f, 1.7f)};
    std::array<Point2d, 4U> crosswalk2 = {Point2d(2.0f, 2.1f), Point2d(2.2f, 2.3f), Point2d(2.4f, 2.5f),
                                          Point2d(2.6f, 2.7f)};

    std::array<Point2d, 2U> stop_line1 = {Point2d(3.0f, 3.1f), Point2d(3.2f, 3.3f)};
    std::array<Point2d, 2U> stop_line2 = {Point2d(4.0f, 4.1f), Point2d(4.2f, 4.3f)};

    attr.center_points         = {{0, 0}, {1, 1}, {1, 2}};
    attr.conflict_path_indexes = {1, 3};
    attr.crosswalks.push_back(crosswalk1);
    attr.crosswalks.push_back(crosswalk2);
    attr.stop_lines.push_back(stop_line1);
    attr.stop_lines.push_back(stop_line2);

    lane.SetMapAttributes(attr);

    attr2 = lane.GetMapAttributes();

    ASSERT_EQ(attr.center_points, attr2.center_points);
    ASSERT_EQ(attr.conflict_path_indexes, attr2.conflict_path_indexes);
    ASSERT_EQ(attr.crosswalks[0], attr2.crosswalks[0]);
    ASSERT_EQ(attr.crosswalks[1], attr2.crosswalks[1]);
    ASSERT_EQ(attr.stop_lines[0], attr2.stop_lines[0]);
    ASSERT_EQ(attr.stop_lines[1], attr2.stop_lines[1]);
}

TEST(Lane, GetSerializedAttributesSize)
{
    LaneType lane(0);

    ASSERT_EQ(40, lane.GetSerializedAttributesSize<4U>());
    ASSERT_EQ(56, lane.GetSerializedAttributesSize<8U>());
}

TEST(Lane, SerializeAndDeserialize)
{
    LaneType               lane1(0), lane2(0);
    holo::common::RoadCategory rt;
    rt.SetCategoryMainRoad();
    lane1.SetRoadCategory(rt);

    holo::common::LaneCategory lt;
    lt.SetCategoryUnknown();
    lane1.SetLaneCategory(lt);

    std::array<Point2d, 4U> crosswalk1 = {Point2d(1.0f, 1.1f), Point2d(1.2f, 1.3f), Point2d(1.4f, 1.5f),
                                          Point2d(1.6f, 1.7f)};
    std::array<Point2d, 4U> crosswalk2 = {Point2d(2.0f, 2.1f), Point2d(2.2f, 2.3f), Point2d(2.4f, 2.5f),
                                          Point2d(2.6f, 2.7f)};

    std::array<Point2d, 2U> stop_line1 = {Point2d(3.0f, 3.1f), Point2d(3.2f, 3.3f)};
    std::array<Point2d, 2U> stop_line2 = {Point2d(4.0f, 4.1f), Point2d(4.2f, 4.3f)};

    MapAttributes attr;
    attr.center_points         = {{0, 0}, {1, 1}, {1, 2}};
    attr.conflict_path_indexes = {1, 3};
    attr.crosswalks.push_back(crosswalk1);
    attr.crosswalks.push_back(crosswalk2);
    attr.stop_lines.push_back(stop_line1);
    attr.stop_lines.push_back(stop_line2);
    lane1.SetMapAttributes(attr);

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    lane1.SerializeAttributes(serializer);
    ASSERT_EQ(lane1.GetSerializedAttributesSize<4U>(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    lane2.DeserializeAttributes(deserializer);

    ASSERT_TRUE(lane2.GetRoadCategory().IsCategoryMainRoad());
    ASSERT_FALSE(lane2.GetRoadCategory().IsCategoryRamp());
    ASSERT_TRUE(lane2.GetLaneCategory().IsCategoryUnknown());
    ASSERT_FALSE(lane2.GetLaneCategory().IsCategoryRegular());
    ASSERT_FALSE(lane2.GetLaneCategory().IsCategoryAcceleration());
    ASSERT_FALSE(lane2.GetLaneCategory().IsCategoryDeceleration());
    ASSERT_EQ(lane1.GetMapAttributes().center_points, lane2.GetMapAttributes().center_points);
    ASSERT_EQ(lane1.GetMapAttributes().conflict_path_indexes, lane2.GetMapAttributes().conflict_path_indexes);
    ASSERT_EQ(lane1.GetMapAttributes().crosswalks[0], lane2.GetMapAttributes().crosswalks[0]);
    ASSERT_EQ(lane1.GetMapAttributes().crosswalks[1], lane2.GetMapAttributes().crosswalks[1]);
    ASSERT_EQ(lane1.GetMapAttributes().stop_lines[0], lane2.GetMapAttributes().stop_lines[0]);
    ASSERT_EQ(lane1.GetMapAttributes().stop_lines[1], lane2.GetMapAttributes().stop_lines[1]);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
