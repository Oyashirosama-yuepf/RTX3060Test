/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_road_frame2.h
 * @brief This file tests RoadFrame object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-06-17
 */

#include <gtest/gtest.h>
#include <holo/common/road_frame2.h>
#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>

using ScalarType    = holo::float64_t;
using PointType     = holo::geometry::Point2T<ScalarType>;
using CurveType     = holo::geometry::CurvePolynomial<PointType, 64U, 3U>;
using RoadFrameType = holo::common::RoadFrame<CurveType>;

using Serializer   = holo::serialization::Serializer<false, 4>;
using Deserializer = holo::serialization::Deserializer<false, 4>;

TEST(RoadFrame, DefaultConstructor)
{
    RoadFrameType rf;
    ASSERT_EQ(1U, rf.size());
    auto       node       = rf.GetDefaultLane();
    auto const const_node = rf.GetDefaultLane();
    ASSERT_TRUE(node->HasLeftBoundary());
    ASSERT_TRUE(node->HasRightBoundary());
    ASSERT_TRUE(const_node->HasLeftBoundary());
    ASSERT_TRUE(const_node->HasRightBoundary());
}

TEST(RoadFrame, PushBackConflictPath)
{
    RoadFrameType::ConflictPathType ConflictPath1;
    RoadFrameType::ConflictPathType ConflictPath2;

    ConflictPath1.path_id = 1;
    ConflictPath2.path_id = 2;

    for (size_t i = 0; i < 30; i++)
    {
        ConflictPath1.path.push_back(PointType(10 + i, 20 + i));
        ConflictPath2.path.push_back(PointType(50 + i, 60 + i));
    }

    RoadFrameType rf;
    rf.PushBackConflictPath(ConflictPath1);
    rf.PushBackConflictPath(ConflictPath2);

    ASSERT_EQ(ConflictPath1.path_id, rf.GetConflictPath(0).path_id);
    ASSERT_EQ(ConflictPath1.path, rf.GetConflictPath(0).path);

    ASSERT_EQ(ConflictPath2.path_id, rf.GetConflictPath(1).path_id);
    ASSERT_EQ(ConflictPath2.path, rf.GetConflictPath(1).path);
}

TEST(RoadFrame, EmplaceBackConflictPath)
{
    RoadFrameType                             rf;
    RoadFrameType::ConflictPathType::PathType path;
    for (size_t i = 0; i < 30; i++)
    {
        path.push_back(PointType(10 + i, 20 + i));
    }

    rf.template EmplaceBackConflictPath(5, path);
    ASSERT_EQ(path, rf.GetConflictPath(0).path);
    ASSERT_EQ(5, rf.GetConflictPath(0).path_id);
}

TEST(RoadFrame, GetConflictPaths)
{
    RoadFrameType::ConflictPathType ConflictPath1;
    RoadFrameType::ConflictPathType ConflictPath2;

    ConflictPath1.path_id = 1;
    ConflictPath1.path_id = 2;

    for (size_t i = 0; i < 30; i++)
    {
        ConflictPath1.path.push_back(PointType(10 + i, 20 + i));
        ConflictPath2.path.push_back(PointType(50 + i, 60 + i));
    }

    RoadFrameType rf;
    rf.PushBackConflictPath(ConflictPath1);
    rf.PushBackConflictPath(ConflictPath2);

    ASSERT_EQ(ConflictPath1.path_id, rf.GetConflictPaths()[0].path_id);
    ASSERT_EQ(ConflictPath1.path, rf.GetConflictPaths()[0].path);

    ASSERT_EQ(ConflictPath2.path_id, rf.GetConflictPaths()[1].path_id);
    ASSERT_EQ(ConflictPath2.path, rf.GetConflictPaths()[1].path);
}

TEST(RoadFrame, ClearConflictPaths)
{
    RoadFrameType::ConflictPathType ConflictPath1;
    RoadFrameType::ConflictPathType ConflictPath2;

    ConflictPath1.path_id = 1;
    ConflictPath1.path_id = 2;

    for (size_t i = 0; i < 30; i++)
    {
        ConflictPath1.path.push_back(PointType(10 + i, 20 + i));
        ConflictPath2.path.push_back(PointType(50 + i, 60 + i));
    }

    RoadFrameType rf;
    rf.PushBackConflictPath(ConflictPath1);
    rf.PushBackConflictPath(ConflictPath2);
    rf.ClearConflictPaths();

    ASSERT_EQ(0, rf.GetConflictPaths().size());
}

TEST(RoadFrame, AddLaneToLeft)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    auto new_node = rf.AddLaneToLeft(node);
    ASSERT_EQ(2U, rf.size());
    ASSERT_EQ(&node->GetLeftBoundary(), &new_node->GetRightBoundary());

    ASSERT_EQ(node.GetLeft(), new_node);
    ASSERT_EQ(new_node.GetRight(), node);
}

TEST(RoadFrame, AddLaneToRight)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    auto new_node = rf.AddLaneToRight(node);
    ASSERT_EQ(2U, rf.size());
    ASSERT_EQ(&node->GetRightBoundary(), &new_node->GetLeftBoundary());

    ASSERT_EQ(node.GetRight(), new_node);
    ASSERT_EQ(new_node.GetLeft(), node);
}

TEST(RoadFrame, AddLaneToLeftWithPrevLeft)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();

    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    rf.AddLaneToLeft(node);

    node.GetLeft()->GetLeftBoundary().push_back({0, -3});
    node.GetLeft()->GetLeftBoundary().push_back({10, -3});
    rf.AddLaneToRight(node);
    node.GetRight()->GetRightBoundary().push_back({0, 3});
    node.GetRight()->GetRightBoundary().push_back({10, 3});

    auto next_node = rf.AddLaneToNext(node);
    auto new_node  = rf.AddLaneToLeft(next_node);

    ASSERT_EQ(new_node.GetRight(), next_node);
    ASSERT_EQ(next_node.GetLeft(), new_node);
    ASSERT_EQ(&new_node->GetRightBoundary(), &next_node->GetLeftBoundary());
    ASSERT_EQ(new_node->GetLeftBoundary()[0], node.GetLeft()->GetLeftBoundary()[1]);
}

TEST(RoadFrame, AddLaneToRightWithPrevRight)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();

    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    rf.AddLaneToLeft(node);

    node.GetLeft()->GetLeftBoundary().push_back({0, -3});
    node.GetLeft()->GetLeftBoundary().push_back({10, -3});
    rf.AddLaneToRight(node);
    node.GetRight()->GetRightBoundary().push_back({0, 3});
    node.GetRight()->GetRightBoundary().push_back({10, 3});

    auto next_node = rf.AddLaneToNext(node);
    auto new_node  = rf.AddLaneToRight(next_node);

    ASSERT_EQ(new_node.GetLeft(), next_node);
    ASSERT_EQ(next_node.GetRight(), new_node);
    ASSERT_EQ(&new_node->GetLeftBoundary(), &next_node->GetRightBoundary());
    ASSERT_EQ(new_node->GetRightBoundary()[0], node.GetRight()->GetRightBoundary()[1]);
}

TEST(RoadFrame, AddLaneToNext)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    auto new_node = rf.AddLaneToNext(node);
    ASSERT_EQ(2U, rf.size());
    ASSERT_EQ(node->GetRightBoundary()[1], new_node->GetRightBoundary()[0]);
    ASSERT_EQ(node->GetLeftBoundary()[1], new_node->GetLeftBoundary()[0]);

    ASSERT_EQ(node.GetNext(), new_node);
    ASSERT_EQ(new_node.GetPrev(), node);
}

TEST(RoadFrame, AddLaneToNextWithLeftNext)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();

    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    rf.AddLaneToLeft(node);
    node.GetLeft()->GetLeftBoundary().push_back({0, -3});
    node.GetLeft()->GetLeftBoundary().push_back({10, -3});

    rf.AddLaneToRight(node);
    node.GetRight()->GetRightBoundary().push_back({0, 3});
    node.GetRight()->GetRightBoundary().push_back({10, 3});

    auto next_node = rf.AddLaneToNext(node.GetLeft());
    auto new_node  = rf.AddLaneToNext(node);

    ASSERT_EQ(new_node.GetLeft(), next_node);
    ASSERT_EQ(next_node.GetRight(), new_node);
    ASSERT_EQ(&new_node->GetLeftBoundary(), &next_node->GetRightBoundary());
    ASSERT_EQ(new_node->GetRightBoundary()[0], node->GetRightBoundary()[1]);
}

TEST(RoadFrame, AddLaneToNextWithRightNext)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();

    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    rf.AddLaneToLeft(node);
    node.GetLeft()->GetLeftBoundary().push_back({0, -3});
    node.GetLeft()->GetLeftBoundary().push_back({10, -3});

    rf.AddLaneToRight(node);
    node.GetRight()->GetRightBoundary().push_back({0, 3});
    node.GetRight()->GetRightBoundary().push_back({10, 3});

    auto next_node = rf.AddLaneToNext(node.GetRight());
    auto new_node  = rf.AddLaneToNext(node);

    ASSERT_EQ(new_node.GetRight(), next_node);
    ASSERT_EQ(next_node.GetLeft(), new_node);
    ASSERT_EQ(&new_node->GetRightBoundary(), &next_node->GetLeftBoundary());
    ASSERT_EQ(new_node->GetLeftBoundary()[0], node->GetLeftBoundary()[1]);
}

TEST(RoadFrame, AddLaneToNextWithLeftNextAndRightNext)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();

    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    rf.AddLaneToLeft(node);
    node.GetLeft()->GetLeftBoundary().push_back({0, -3});
    node.GetLeft()->GetLeftBoundary().push_back({10, -3});

    rf.AddLaneToRight(node);
    node.GetRight()->GetRightBoundary().push_back({0, 3});
    node.GetRight()->GetRightBoundary().push_back({10, 3});

    auto next_left_node  = rf.AddLaneToNext(node.GetLeft());
    auto next_right_node = rf.AddLaneToNext(node.GetRight());
    auto new_node        = rf.AddLaneToNext(node);

    ASSERT_EQ(new_node.GetRight(), next_right_node);
    ASSERT_EQ(new_node.GetLeft(), next_left_node);
    ASSERT_EQ(next_right_node.GetLeft(), new_node);
    ASSERT_EQ(next_left_node.GetRight(), new_node);

    ASSERT_EQ(&new_node->GetRightBoundary(), &next_right_node->GetLeftBoundary());
    ASSERT_EQ(&new_node->GetLeftBoundary(), &next_left_node->GetRightBoundary());
}

TEST(RoadFramePolynomial, Constructor)
{
    holo::common::RoadFrame<holo::numerics::Polynomial<holo::float64_t, 3U>> rf;
    ASSERT_EQ(0U, rf.size());
}

TEST(RoadFramePolynomial, EmplaceBoundaries)
{
    holo::common::RoadFrame<holo::numerics::Polynomial<holo::float64_t, 3U>> rf;
    rf.emplace_back(holo::numerics::Polynomial<holo::float64_t, 3U>({1, 2, 3}), 0, 100);
    ASSERT_EQ(1U, rf.size());
    rf.emplace_back(holo::numerics::Polynomial<holo::float64_t, 3U>({-1, 2, 3}), 0, 100);
    ASSERT_EQ(2U, rf.size());
    rf.emplace_back(holo::numerics::Polynomial<holo::float64_t, 3U>({-3, 2, 3}), 0, 100);
    ASSERT_EQ(3U, rf.size());

    auto& boundary = rf[0];
    ASSERT_EQ(6U, boundary.GetSampleByCoordinate(1)[1]);
    boundary = rf[1];
    ASSERT_EQ(4U, boundary.GetSampleByCoordinate(1)[1]);
    boundary = rf[2];
    ASSERT_EQ(2U, boundary.GetSampleByCoordinate(1)[1]);
}

TEST(ConflictPathType, TestGetSerializedSize)
{
    RoadFrameType::ConflictPathType ConflictPath1;

    ConflictPath1.path_id = 1;

    for (size_t i = 0; i < 30; i++)
    {
        ConflictPath1.path.push_back(PointType(10 + i, 20 + i));
    }

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    serializer << ConflictPath1;

    ASSERT_EQ(ConflictPath1.GetSerializedSize(), serializer.GetSize());
}

TEST(RoadFrame, TestGetSerializedSize)
{
    RoadFrameType::ConflictPathType ConflictPath1;
    RoadFrameType::ConflictPathType ConflictPath2;

    ConflictPath1.path_id = 1;
    ConflictPath1.path_id = 2;

    for (size_t i = 0; i < 30; i++)
    {
        ConflictPath1.path.push_back(PointType(10 + i, 20 + i));
        ConflictPath2.path.push_back(PointType(50 + i, 60 + i));
    }

    RoadFrameType rf;
    rf.PushBackConflictPath(ConflictPath1);
    rf.PushBackConflictPath(ConflictPath2);

    auto node = rf.GetDefaultLane();

    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    rf.AddLaneToLeft(node);
    node.GetLeft()->GetLeftBoundary().push_back({0, -3});
    node.GetLeft()->GetLeftBoundary().push_back({10, -3});

    rf.AddLaneToNext(node, false, false);
    node.GetNext()->GetLeftBoundary().push_back({15, -1});
    node.GetNext()->GetLeftBoundary().push_back({20, -1});
    node.GetNext()->GetRightBoundary().push_back({15, 1});
    node.GetNext()->GetRightBoundary().push_back({20, 1});

    rf.AddLaneToRight(node);
    node.GetRight()->GetRightBoundary().push_back({0, 3});
    node.GetRight()->GetRightBoundary().push_back({10, 3});

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    serializer << rf;
    ASSERT_EQ(rf.GetSerializedSize(), serializer.GetSize());
}

bool IsLaneBoundariesSame(holo::common::LaneBoundary<CurveType> const& lb1,
                          holo::common::LaneBoundary<CurveType> const& lb2)
{
    bool ok = true;

    ok = ok && lb1.size() == lb2.size();
    ok = ok && lb1.GetColor() == lb2.GetColor();
    ok = ok && lb1.GetStyle() == lb2.GetStyle();
    ok = ok && lb1.GetWidth() == lb2.GetWidth();
    ok = ok && lb1.GetConfidence() == lb2.GetConfidence();
    for (size_t i = 0U; ok && i < lb1.size(); ++i)
    {
        ok = ok && lb1.at(i).Dist(lb2.at(i)) < 1e-4;
    }
    return ok;
}

bool IsLanesSame(holo::common::Lane<CurveType> const& l1, holo::common::Lane<CurveType> const& l2)
{
    bool ok = true;

    ok = ok && l1.GetExternalId() == l2.GetExternalId();
    ok = ok && l1.GetMaxSpeedLimit() == l2.GetMaxSpeedLimit();
    ok = ok && l1.GetMinSpeedLimit() == l2.GetMinSpeedLimit();
    ok = ok && IsLaneBoundariesSame(l1.GetLeftBoundary(), l2.GetLeftBoundary());
    ok = ok && IsLaneBoundariesSame(l1.GetRightBoundary(), l2.GetRightBoundary());
    return ok;
}

bool IsNodesSame(RoadFrameType::GraphNode n1, RoadFrameType::GraphNode n2)
{
    bool ok = true;

    ok = ok && IsLanesSame(*n1, *n2);

    for (size_t i = 0U; ok && i < 8U; ++i)
    {
        auto const dir = static_cast<RoadFrameType::Direction>(i);

        ok = ok && n1.HasNeighbour(dir) == n2.HasNeighbour(dir);
        if (ok && n1.HasNeighbour(dir) && n2.HasNeighbour(dir))
        {
            ok = ok && IsLanesSame(*n1.Get(dir), *n2.Get(dir));
        }
    }
    return ok;
}

TEST(RoadFrame, TestSerialization)
{
    holo::container::Vector<PointType, 64U> vector1, vector2, vector3;
    for (size_t i = 0; i < 30; i++)
    {
        vector1.push_back(PointType(10 + i, 20 + i));
        vector2.push_back(PointType(50 + i, 60 + i));
    }

    holo::container::Vector<holo::container::Vector<PointType, 64U>, 16U> paths, paths_expected;
    paths.push_back(vector1);
    paths.push_back(vector2);

    RoadFrameType::ConflictPathType ConflictPath1;
    RoadFrameType::ConflictPathType ConflictPath2;

    ConflictPath1.path_id = 1;
    ConflictPath1.path_id = 2;

    for (size_t i = 0; i < 30; i++)
    {
        ConflictPath1.path.push_back(PointType(10 + i, 20 + i));
        ConflictPath2.path.push_back(PointType(50 + i, 60 + i));
    }

    RoadFrameType rf;
    rf.PushBackConflictPath(ConflictPath1);
    rf.PushBackConflictPath(ConflictPath2);
    auto node = rf.GetDefaultLane();

    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetLeftBoundary().SetWidth(19);
    node->GetLeftBoundary().SetConfidence(20);
    node->GetLeftBoundary().SetStyle(holo::common::BoundaryStyle::ROAD_EDGE);
    node->GetLeftBoundary().SetColor(holo::common::BoundaryColor::YELLOW);

    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});
    node->GetLeftBoundary().SetWidth(17);
    node->GetLeftBoundary().SetConfidence(18);
    node->GetLeftBoundary().SetStyle(holo::common::BoundaryStyle::DOUBLE_SOLID);
    node->GetLeftBoundary().SetColor(holo::common::BoundaryColor::WHITE);

    node->SetExternalId(1);
    node->SetSpeedLimit(80, 100);

    rf.AddLaneToLeft(node);
    node.GetLeft()->GetLeftBoundary().push_back({0, -3});
    node.GetLeft()->GetLeftBoundary().push_back({10, -3});
    node.GetLeft()->GetLeftBoundary().SetWidth(16);
    node.GetLeft()->GetLeftBoundary().SetConfidence(17);
    node.GetLeft()->GetLeftBoundary().SetStyle(holo::common::BoundaryStyle::DASHED);
    node.GetLeft()->GetLeftBoundary().SetColor(holo::common::BoundaryColor::YELLOW);

    node.GetLeft()->SetExternalId(2);
    node.GetLeft()->SetSpeedLimit(50, 60);

    rf.AddLaneToNext(node, false, false);
    node.GetNext()->GetLeftBoundary().push_back({15, -1});
    node.GetNext()->GetLeftBoundary().push_back({20, -1});
    node.GetNext()->GetLeftBoundary().SetWidth(14);
    node.GetNext()->GetLeftBoundary().SetConfidence(15);
    node.GetNext()->GetLeftBoundary().SetStyle(holo::common::BoundaryStyle::LEFT_SOLID_RIGHT_DOT);
    node.GetNext()->GetLeftBoundary().SetColor(holo::common::BoundaryColor::WHITE);

    node.GetNext()->GetRightBoundary().push_back({15, 1});
    node.GetNext()->GetRightBoundary().push_back({20, 1});
    node.GetNext()->GetRightBoundary().SetWidth(12);
    node.GetNext()->GetRightBoundary().SetConfidence(13);
    node.GetNext()->GetRightBoundary().SetStyle(holo::common::BoundaryStyle::LEFT_SOLID_RIGHT_DOT);
    node.GetNext()->GetRightBoundary().SetColor(holo::common::BoundaryColor::UNKNOWN);

    node.GetNext()->SetExternalId(4);
    node.GetNext()->SetSpeedLimit(100, 120);

    rf.AddLaneToRight(node);
    node.GetRight()->GetRightBoundary().push_back({0, 3});
    node.GetRight()->GetRightBoundary().push_back({10, 3});
    node.GetRight()->GetRightBoundary().SetWidth(10);
    node.GetRight()->GetRightBoundary().SetConfidence(11);
    node.GetRight()->GetRightBoundary().SetStyle(holo::common::BoundaryStyle::BOTTS_DOT);
    node.GetRight()->GetRightBoundary().SetColor(holo::common::BoundaryColor::YELLOW);

    node.GetRight()->SetExternalId(3);
    node.GetRight()->SetSpeedLimit(20, 40);

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    rf.Serialize(serializer);

    Deserializer  deserializer(buffer, serializer.GetSize());
    RoadFrameType out_rf;
    out_rf.Deserialize(deserializer);
    ASSERT_EQ(out_rf.size(), rf.size());

    auto out_node = out_rf.GetDefaultLane();

    bool result = false;

    result = IsNodesSame(node, out_node);
    ASSERT_TRUE(result);

    result = IsNodesSame(node.GetLeft(), out_node.GetLeft());
    ASSERT_TRUE(result);

    result = IsNodesSame(node.GetRight(), out_node.GetRight());
    ASSERT_TRUE(result);

    result = IsNodesSame(node.GetNext(), out_node.GetNext());
    ASSERT_TRUE(result);

    ASSERT_EQ(ConflictPath1.path_id, out_rf.GetConflictPath(0).path_id);
    ASSERT_EQ(ConflictPath1.path, out_rf.GetConflictPath(0).path);

    ASSERT_EQ(ConflictPath2.path_id, out_rf.GetConflictPath(1).path_id);
    ASSERT_EQ(ConflictPath2.path, out_rf.GetConflictPath(1).path);
}

TEST(RoadFrame, TestSerialization_2)
{
    RoadFrameType                          rf;
    auto                                   node = rf.GetDefaultLane();
    RoadFrameType::LaneType::MapAttributes att;
    att.center_points.emplace_back(0, 1);
    att.center_points.emplace_back(0, 2);
    att.center_points.emplace_back(0, 3);
    node->SetMapAttributes(att);

    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});

    rf.AddLaneToLeft(node);
    node.GetLeft()->GetLeftBoundary().push_back({0, -3});
    node.GetLeft()->GetLeftBoundary().push_back({10, -3});

    rf.AddLaneToNext(node, false, false);
    node.GetNext()->GetLeftBoundary().push_back({15, -1});
    node.GetNext()->GetLeftBoundary().push_back({20, -1});
    node.GetNext()->GetRightBoundary().push_back({15, 1});
    node.GetNext()->GetRightBoundary().push_back({20, 1});

    rf.AddLaneToRight(node);
    node.GetRight()->GetRightBoundary().push_back({0, 3});
    node.GetRight()->GetRightBoundary().push_back({10, 3});

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    rf.Serialize(serializer);
    ASSERT_EQ(rf.GetSerializedSize(), serializer.GetSize());
}

TEST(RoadFrame, LaneToNext_1)
{
    RoadFrameType rf;
    ASSERT_EQ(1U, rf.size());
    auto node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back(PointType(0, 1));
    node->GetLeftBoundary().push_back(PointType(1, 1));
    node->GetLeftBoundary().push_back(PointType(2, 1));
    node->GetRightBoundary().push_back(PointType(0, -1));
    node->GetRightBoundary().push_back(PointType(1, -1));
    node->GetRightBoundary().push_back(PointType(2, -1));

    auto left_node = rf.AddLaneToLeft(node);
    left_node->GetLeftBoundary().push_back(PointType(0, 1));
    left_node->GetLeftBoundary().push_back(PointType(1, 1));
    left_node->GetLeftBoundary().push_back(PointType(2, 1));

    rf.AddLaneToNext2(left_node, true, true, false);
    left_node.GetOutRight()->GetRightBoundary().push_back(PointType(3, 1));
    left_node.GetOutRight()->GetRightBoundary().push_back(PointType(4, 1));
    left_node.GetOutRight()->GetRightBoundary().push_back(PointType(5, 1));

    auto next_node = rf.AddLaneToNext(node, true, true);

    ASSERT_EQ(next_node->GetLeftBoundary().GetKnotRange().first, 2);
    ASSERT_EQ(next_node->GetLeftBoundary().GetKnotRange().second, 6);
    ASSERT_EQ(next_node->GetLeftBoundary().size(), 4);
}

TEST(RoadFrame, LaneToNext_2)
{
    RoadFrameType rf;
    ASSERT_EQ(1U, rf.size());
    auto node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back(PointType(0, 1));
    node->GetLeftBoundary().push_back(PointType(1, 1));
    node->GetLeftBoundary().push_back(PointType(2, 1));
    node->GetRightBoundary().push_back(PointType(0, -1));
    node->GetRightBoundary().push_back(PointType(1, -1));
    node->GetRightBoundary().push_back(PointType(2, -1));

    auto right_node = rf.AddLaneToRight(node);
    right_node->GetLeftBoundary().push_back(PointType(3, 1));
    right_node->GetLeftBoundary().push_back(PointType(4, 1));
    right_node->GetLeftBoundary().push_back(PointType(5, 1));

    rf.AddLaneToNext2(right_node, true, true, false);
    right_node.GetOutLeft()->GetLeftBoundary().push_back(PointType(6, 1));
    right_node.GetOutLeft()->GetLeftBoundary().push_back(PointType(7, 1));
    right_node.GetOutLeft()->GetLeftBoundary().push_back(PointType(8, 1));

    auto next_node = rf.AddLaneToNext(node, true, true);

    ASSERT_EQ(next_node->GetRightBoundary().GetKnotRange().first, 5);
    ASSERT_EQ(next_node->GetRightBoundary().GetKnotRange().second, 9);
    ASSERT_EQ(next_node->GetRightBoundary().size(), 4);
}

TEST(RoadFrame, AddLaneToNext22)
{
    RoadFrameType rf;
    ASSERT_EQ(1U, rf.size());
    auto node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back(PointType(0, 1));
    node->GetLeftBoundary().push_back(PointType(1, 1));
    node->GetLeftBoundary().push_back(PointType(2, 1));
    node->GetRightBoundary().push_back(PointType(0, -1));
    node->GetRightBoundary().push_back(PointType(1, -1));
    node->GetRightBoundary().push_back(PointType(2, -1));

    auto left_node = rf.AddLaneToLeft(node);
    left_node->GetLeftBoundary().push_back(PointType(0, 1));
    left_node->GetLeftBoundary().push_back(PointType(1, 1));
    left_node->GetLeftBoundary().push_back(PointType(2, 1));
    auto right_node = rf.AddLaneToRight(node);

    rf.AddLaneToNext2(left_node, true, true, true);
    rf.AddLaneToNext2(right_node, true, true, false);
}

TEST(Iterator, Set)
{
    RoadFrameType rf;
    ASSERT_EQ(1U, rf.size());
    auto node = rf.GetDefaultLane();
    rf.AddLaneToLeft(node);
    rf.AddLaneToRight(node);
    EXPECT_THROW(node.Set(RoadFrameType::Direction::LEFT, node), holo::exception::OperationNotPermittedException);
}

TEST(RoadFrame, LaneToNext_3)
{
    RoadFrameType rf;
    ASSERT_EQ(1U, rf.size());
    auto node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back(PointType(0, 1));
    node->GetLeftBoundary().push_back(PointType(1, 1));
    node->GetLeftBoundary().push_back(PointType(2, 1));
    node->GetRightBoundary().push_back(PointType(0, -1));
    node->GetRightBoundary().push_back(PointType(1, -1));
    node->GetRightBoundary().push_back(PointType(2, -1));

    auto left_node = rf.AddLaneToLeft(node);
    left_node->GetLeftBoundary().push_back(PointType(0, 2));
    left_node->GetLeftBoundary().push_back(PointType(1, 2));
    left_node->GetLeftBoundary().push_back(PointType(2, 2));

    auto right_node = rf.AddLaneToRight(node);
    right_node->GetRightBoundary().push_back(PointType(0, -2));
    right_node->GetRightBoundary().push_back(PointType(1, -2));
    right_node->GetRightBoundary().push_back(PointType(2, -2));

    auto right_right_node = rf.AddLaneToRight(right_node);
    right_right_node->GetRightBoundary().push_back(PointType(0, -3));
    right_right_node->GetRightBoundary().push_back(PointType(1, -3));
    right_right_node->GetRightBoundary().push_back(PointType(2, -3));

    auto right_next = rf.AddLaneToNext(right_node, right_right_node, true, false);
    right_next->GetLeftBoundary().push_back(PointType(3, 2));
    right_next->GetLeftBoundary().push_back(PointType(4, 2));
    right_next->GetLeftBoundary().push_back(PointType(5, 2));

    auto left_next_node = rf.AddLaneToNext(left_node, false, true);
    left_next_node->GetRightBoundary().push_back(PointType(3, -2));
    left_next_node->GetRightBoundary().push_back(PointType(4, -2));
    left_next_node->GetRightBoundary().push_back(PointType(5, -2));

    auto next_node = rf.AddLaneToNext(node, true, true);

    ASSERT_EQ(next_node->GetRightBoundary().size(), 4U);
    ASSERT_EQ(next_node->GetRightBoundary().GetKnotRange().first, 2U);
    ASSERT_EQ(next_node->GetRightBoundary().GetKnotRange().second, 6U);

    ASSERT_EQ(next_node->GetLeftBoundary().size(), 4U);
    ASSERT_EQ(next_node->GetLeftBoundary().GetKnotRange().first, 2U);
    ASSERT_EQ(next_node->GetLeftBoundary().GetKnotRange().second, 6U);
}

TEST(RoadFrame, LaneToNext_4)
{
    RoadFrameType rf;
    ASSERT_EQ(1U, rf.size());
    auto node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back(PointType(0, 1));
    node->GetLeftBoundary().push_back(PointType(1, 1));
    node->GetLeftBoundary().push_back(PointType(2, 1));
    node->GetRightBoundary().push_back(PointType(0, -1));
    node->GetRightBoundary().push_back(PointType(1, -1));
    node->GetRightBoundary().push_back(PointType(2, -1));

    auto left_node = rf.AddLaneToLeft(node);
    left_node->GetLeftBoundary().push_back(PointType(0, 2));
    left_node->GetLeftBoundary().push_back(PointType(1, 2));
    left_node->GetLeftBoundary().push_back(PointType(2, 2));

    auto left_left_node = rf.AddLaneToLeft(left_node);
    left_left_node->GetLeftBoundary().push_back(PointType(0, -3));
    left_left_node->GetLeftBoundary().push_back(PointType(1, -3));
    left_left_node->GetLeftBoundary().push_back(PointType(2, -3));

    auto right_node = rf.AddLaneToRight(node);
    right_node->GetRightBoundary().push_back(PointType(0, -2));
    right_node->GetRightBoundary().push_back(PointType(1, -2));
    right_node->GetRightBoundary().push_back(PointType(2, -2));

    auto left_next = rf.AddLaneToNext(left_left_node, left_node, false, true);
    left_next->GetRightBoundary().push_back(PointType(3, 2));
    left_next->GetRightBoundary().push_back(PointType(4, 2));
    left_next->GetRightBoundary().push_back(PointType(5, 2));

    auto right_next_node = rf.AddLaneToNext(right_node, true, false);
    right_next_node->GetLeftBoundary().push_back(PointType(3, -2));
    right_next_node->GetLeftBoundary().push_back(PointType(4, -2));
    right_next_node->GetLeftBoundary().push_back(PointType(5, -2));

    auto next_node = rf.AddLaneToNext(node, true, true);

    ASSERT_EQ(next_node->GetRightBoundary().size(), 4U);
    ASSERT_EQ(next_node->GetRightBoundary().GetKnotRange().first, 2U);
    ASSERT_EQ(next_node->GetRightBoundary().GetKnotRange().second, 6U);

    ASSERT_EQ(next_node->GetLeftBoundary().size(), 4U);
    ASSERT_EQ(next_node->GetLeftBoundary().GetKnotRange().first, 2U);
    ASSERT_EQ(next_node->GetLeftBoundary().GetKnotRange().second, 6U);
}

TEST(RoadFrame, AddLaneToNext3_1)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back(PointType(0, 1));
    node->GetLeftBoundary().push_back(PointType(1, 1));
    node->GetLeftBoundary().push_back(PointType(2, 1));
    node->GetRightBoundary().push_back(PointType(0, -1));
    node->GetRightBoundary().push_back(PointType(1, -1));
    node->GetRightBoundary().push_back(PointType(2, -1));

    auto new_node = rf.AddLaneToNext3(node, true, true, false, false);
    (void)new_node;

    node.GetOutLeft()->GetLeftBoundary().push_back(PointType(7, -3));
    node.GetOutLeft()->GetLeftBoundary().push_back(PointType(8, -3));
    node.GetOutLeft()->GetLeftBoundary().push_back(PointType(9, -3));

    node.GetOutLeft()->GetRightBoundary().push_back(PointType(7, -1));
    node.GetOutLeft()->GetRightBoundary().push_back(PointType(8, -1));
    node.GetOutLeft()->GetRightBoundary().push_back(PointType(9, -1));

    node.GetNext()->GetRightBoundary().push_back(PointType(7, 1));
    node.GetNext()->GetRightBoundary().push_back(PointType(8, 1));
    node.GetNext()->GetRightBoundary().push_back(PointType(9, 1));

    node.GetOutRight()->GetRightBoundary().push_back(PointType(7, 1));
    node.GetOutRight()->GetRightBoundary().push_back(PointType(8, 1));
    node.GetOutRight()->GetRightBoundary().push_back(PointType(9, 1));

    EXPECT_EQ(node.GetOutLeft()->GetLeftBoundary().size(), 4U);
    EXPECT_EQ(node.GetOutLeft()->GetRightBoundary().size(), 3U);
    EXPECT_EQ(node.GetNext()->GetLeftBoundary().size(), 3U);
    EXPECT_EQ(node.GetNext()->GetRightBoundary().size(), 3U);
    EXPECT_EQ(node.GetOutRight()->GetLeftBoundary().size(), 3U);
    EXPECT_EQ(node.GetOutRight()->GetRightBoundary().size(), 4U);
}

TEST(RoadFrame, AddLaneToNext3_2)
{
    RoadFrameType rf;
    auto          node = rf.GetDefaultLane();
    node->GetLeftBoundary().push_back(PointType(0, 1));
    node->GetLeftBoundary().push_back(PointType(1, 1));
    node->GetLeftBoundary().push_back(PointType(2, 1));
    node->GetRightBoundary().push_back(PointType(0, -1));
    node->GetRightBoundary().push_back(PointType(1, -1));
    node->GetRightBoundary().push_back(PointType(2, -1));

    auto right_node = rf.AddLaneToRight(node);
    right_node->GetRightBoundary().push_back(PointType(0, -2));
    right_node->GetRightBoundary().push_back(PointType(1, -2));
    right_node->GetRightBoundary().push_back(PointType(2, -2));

    auto new_node = rf.AddLaneToNext3(node, right_node, true, true, false, false);
    (void)new_node;

    node.GetOutLeft()->GetLeftBoundary().push_back(PointType(7, -3));
    node.GetOutLeft()->GetLeftBoundary().push_back(PointType(8, -3));
    node.GetOutLeft()->GetLeftBoundary().push_back(PointType(9, -3));

    node.GetOutLeft()->GetRightBoundary().push_back(PointType(7, -1));
    node.GetOutLeft()->GetRightBoundary().push_back(PointType(8, -1));
    node.GetOutLeft()->GetRightBoundary().push_back(PointType(9, -1));

    node.GetOutRight()->GetRightBoundary().push_back(PointType(7, 1));
    node.GetOutRight()->GetRightBoundary().push_back(PointType(8, 1));
    node.GetOutRight()->GetRightBoundary().push_back(PointType(9, 1));

    right_node.GetOutRight()->GetRightBoundary().push_back(PointType(7, 3));
    right_node.GetOutRight()->GetRightBoundary().push_back(PointType(8, 3));
    right_node.GetOutRight()->GetRightBoundary().push_back(PointType(9, 3));

    EXPECT_EQ(node.GetOutLeft()->GetLeftBoundary().size(), 4U);
    EXPECT_EQ(node.GetOutLeft()->GetRightBoundary().size(), 3U);
    EXPECT_EQ(node.GetOutRight()->GetLeftBoundary().size(), 3U);
    EXPECT_EQ(node.GetOutRight()->GetRightBoundary().size(), 3U);
    EXPECT_EQ(right_node.GetOutLeft()->GetLeftBoundary().size(), 3U);
    EXPECT_EQ(right_node.GetOutLeft()->GetRightBoundary().size(), 3U);
    EXPECT_EQ(right_node.GetOutRight()->GetLeftBoundary().size(), 3U);
    EXPECT_EQ(right_node.GetOutRight()->GetRightBoundary().size(), 4U);
}
TEST(RoadFrame, TestAddLaneToNext3_3)
{
    holo::container::Vector<PointType, 64U> vector1, vector2, vector3;
    for (size_t i = 0; i < 30; i++)
    {
        vector1.push_back(PointType(10 + i, 20 + i));
        vector2.push_back(PointType(50 + i, 60 + i));
    }

    holo::container::Vector<holo::container::Vector<PointType, 64U>, 16U> paths, paths_expected;
    paths.push_back(vector1);
    paths.push_back(vector2);

    RoadFrameType::ConflictPathType ConflictPath1;
    RoadFrameType::ConflictPathType ConflictPath2;

    ConflictPath1.path_id = 1;
    ConflictPath1.path_id = 2;

    for (size_t i = 0; i < 30; i++)
    {
        ConflictPath1.path.push_back(PointType(10 + i, 20 + i));
        ConflictPath2.path.push_back(PointType(50 + i, 60 + i));
    }

    RoadFrameType rf;
    rf.PushBackConflictPath(ConflictPath1);
    rf.PushBackConflictPath(ConflictPath2);
    auto node = rf.GetDefaultLane();

    node->GetLeftBoundary().push_back({0, -1});
    node->GetLeftBoundary().push_back({10, -1});
    node->GetLeftBoundary().SetWidth(19);
    node->GetLeftBoundary().SetConfidence(20);
    node->GetLeftBoundary().SetStyle(holo::common::BoundaryStyle::ROAD_EDGE);
    node->GetLeftBoundary().SetColor(holo::common::BoundaryColor::YELLOW);

    node->GetRightBoundary().push_back({0, 1});
    node->GetRightBoundary().push_back({10, 1});
    node->GetLeftBoundary().SetWidth(17);
    node->GetLeftBoundary().SetConfidence(18);
    node->GetLeftBoundary().SetStyle(holo::common::BoundaryStyle::DOUBLE_SOLID);
    node->GetLeftBoundary().SetColor(holo::common::BoundaryColor::WHITE);

    node->SetExternalId(1);
    node->SetSpeedLimit(80, 100);

    rf.AddLaneToLeft(node);
    node.GetLeft()->GetLeftBoundary().push_back({0, -3});
    node.GetLeft()->GetLeftBoundary().push_back({10, -3});
    node.GetLeft()->GetLeftBoundary().SetWidth(16);
    node.GetLeft()->GetLeftBoundary().SetConfidence(17);
    node.GetLeft()->GetLeftBoundary().SetStyle(holo::common::BoundaryStyle::DASHED);
    node.GetLeft()->GetLeftBoundary().SetColor(holo::common::BoundaryColor::YELLOW);

    node.GetLeft()->SetExternalId(2);
    node.GetLeft()->SetSpeedLimit(50, 60);

    rf.AddLaneToNext3(node, false, false, false, true);
    node.GetNext()->GetLeftBoundary().push_back({15, -1});
    node.GetNext()->GetLeftBoundary().push_back({20, -1});
    node.GetNext()->GetLeftBoundary().SetWidth(14);
    node.GetNext()->GetLeftBoundary().SetConfidence(15);
    node.GetNext()->GetLeftBoundary().SetStyle(holo::common::BoundaryStyle::LEFT_SOLID_RIGHT_DOT);
    node.GetNext()->GetLeftBoundary().SetColor(holo::common::BoundaryColor::WHITE);

    node.GetNext()->GetRightBoundary().push_back({15, 1});
    node.GetNext()->GetRightBoundary().push_back({20, 1});
    node.GetNext()->GetRightBoundary().SetWidth(12);
    node.GetNext()->GetRightBoundary().SetConfidence(13);
    node.GetNext()->GetRightBoundary().SetStyle(holo::common::BoundaryStyle::LEFT_SOLID_RIGHT_DOT);
    node.GetNext()->GetRightBoundary().SetColor(holo::common::BoundaryColor::UNKNOWN);

    node.GetOutLeft()->GetLeftBoundary().push_back({15, -3});
    node.GetOutLeft()->GetLeftBoundary().push_back({20, -3});
    node.GetOutRight()->GetRightBoundary().push_back({15, 2});
    node.GetOutRight()->GetRightBoundary().push_back({20, 2});

    node.GetNext()->SetExternalId(4);
    node.GetNext()->SetSpeedLimit(100, 120);

    rf.AddLaneToRight(node);
    node.GetRight()->GetRightBoundary().push_back({0, 3});
    node.GetRight()->GetRightBoundary().push_back({10, 3});
    node.GetRight()->GetRightBoundary().SetWidth(10);
    node.GetRight()->GetRightBoundary().SetConfidence(11);
    node.GetRight()->GetRightBoundary().SetStyle(holo::common::BoundaryStyle::BOTTS_DOT);
    node.GetRight()->GetRightBoundary().SetColor(holo::common::BoundaryColor::YELLOW);

    node.GetRight()->SetExternalId(3);
    node.GetRight()->SetSpeedLimit(20, 40);

    uint8_t    buffer[2048];
    Serializer serializer(buffer, 2048);
    rf.Serialize(serializer);

    Deserializer  deserializer(buffer, serializer.GetSize());
    RoadFrameType out_rf;
    out_rf.Deserialize(deserializer);
    ASSERT_EQ(out_rf.size(), rf.size());

    auto out_node = out_rf.GetDefaultLane();

    bool result = false;

    result = IsNodesSame(node, out_node);
    ASSERT_TRUE(result);

    result = IsNodesSame(node.GetLeft(), out_node.GetLeft());
    ASSERT_TRUE(result);

    result = IsNodesSame(node.GetRight(), out_node.GetRight());
    ASSERT_TRUE(result);

    result = IsNodesSame(node.GetNext(), out_node.GetNext());
    ASSERT_TRUE(result);

    ASSERT_EQ(ConflictPath1.path_id, out_rf.GetConflictPath(0).path_id);
    ASSERT_EQ(ConflictPath1.path, out_rf.GetConflictPath(0).path);

    ASSERT_EQ(ConflictPath2.path_id, out_rf.GetConflictPath(1).path_id);
    ASSERT_EQ(ConflictPath2.path, out_rf.GetConflictPath(1).path);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
