/**
 * @brief unit test for path class
 * @author zhangjiannan@holomatic.com
 * @date 2019.10.21
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/common/path.h>

using holo::common::Coordinate;
using holo::common::Pathd;
using holo::common::Pathf;
using holo::common::PathPointd;
using holo::common::PathPointf;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PathPointd, Construct)
{
    PathPointd pt;
    ASSERT_NEAR(pt.GetDistance(), 0.0, 1e-10);
    ASSERT_NEAR(pt.GetTime(), 0.0, 1e-10);
    ASSERT_NEAR(pt.GetAcceleration(), 0.0, 1e-10);
    ASSERT_NEAR(pt.GetCurvature(), 0.0, 1e-10);
    ASSERT_NEAR(pt.GetSpeed(), 0.0, 1e-10);
    ASSERT_NEAR(pt.GetTheta(), 0.0, 1e-10);
    ASSERT_NEAR(pt.GetX(), 0.0, 1e-10);
    ASSERT_NEAR(pt.GetY(), 0.0, 1e-10);
    ASSERT_NEAR(pt.GetZ(), 0.0, 1e-10);

    PathPointd pt2(1, 2, 3);
    ASSERT_NEAR(pt2.GetDistance(), 0.0, 1e-10);
    ASSERT_NEAR(pt2.GetTime(), 0.0, 1e-10);
    ASSERT_NEAR(pt2.GetAcceleration(), 0.0, 1e-10);
    ASSERT_NEAR(pt2.GetCurvature(), 0.0, 1e-10);
    ASSERT_NEAR(pt2.GetSpeed(), 0.0, 1e-10);
    ASSERT_NEAR(pt2.GetTheta(), 0.0, 1e-10);
    ASSERT_NEAR(pt2.GetX(), 1.0, 1e-10);
    ASSERT_NEAR(pt2.GetY(), 2.0, 1e-10);
    ASSERT_NEAR(pt2.GetZ(), 3.0, 1e-10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PathPointd, point)
{
    PathPointd pp;
    pp.Set(1.0, 2.0, 3.0);

    ASSERT_NEAR(pp.GetX(), 1.0, 1e-10);
    ASSERT_NEAR(pp.GetY(), 2.0, 1e-10);
    ASSERT_NEAR(pp.GetZ(), 3.0, 1e-10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PathPointd, theta)
{
    PathPointd pp;
    double     theta = 1.23456789;
    pp.SetTheta(theta);

    ASSERT_NEAR(pp.GetTheta(), theta, 1e-10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PathPointd, curvature)
{
    PathPointd pp;
    double     curvature = 1.23456789;
    pp.SetCurvature(curvature);

    ASSERT_NEAR(pp.GetCurvature(), curvature, 1e-10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PathPointd, speed)
{
    PathPointd pp;
    double     speed = 1.23456789;
    pp.SetSpeed(speed);

    ASSERT_NEAR(pp.GetSpeed(), speed, 1e-10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PathPointd, acceleration)
{
    PathPointd pp;
    double     acceleration = 1.23456789;
    pp.SetAcceleration(acceleration);

    ASSERT_NEAR(pp.GetAcceleration(), acceleration, 1e-10);
}

TEST(PathPointd, distance)
{
    PathPointd pp;
    double     distance = 5.2345679;
    pp.SetDistance(distance);

    ASSERT_NEAR(pp.GetDistance(), distance, 1e-10);
}

TEST(PathPointd, time)
{
    PathPointd pp;
    double     time = 8.23456789;
    pp.SetTime(time);

    ASSERT_NEAR(pp.GetTime(), time, 1e-10);
}

TEST(PathPointd, GetSerializedSize)
{
    PathPointd pp;
    ASSERT_EQ(72, pp.GetSerializedSize<4U>());
    ASSERT_EQ(72, pp.GetSerializedSize<8U>());
}

TEST(PathPointd, SerializeAndDeserialize)
{
    PathPointd pp;
    pp.SetDistance(1.23456789);
    pp.SetTime(1.23456789);
    pp.SetAcceleration(1.23456789);
    pp.SetSpeed(1.23456789);
    pp.SetCurvature(1.23456789);
    pp.SetTheta(1.23456789);
    pp.Set(1.0, 2.0, 3.0);

    uint8_t                           buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << pp;
    ASSERT_EQ(pp.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    PathPointd                          pp2;
    deserializer >> pp2;

    ASSERT_EQ(pp.GetAcceleration(), pp2.GetAcceleration());
    ASSERT_EQ(pp.GetSpeed(), pp2.GetSpeed());
    ASSERT_EQ(pp.GetSpeed(), pp2.GetSpeed());
    ASSERT_EQ(pp.GetTheta(), pp2.GetTheta());
    ASSERT_EQ(pp.GetDistance(), pp2.GetDistance());
    ASSERT_EQ(pp.GetTime(), pp2.GetTime());
    ASSERT_NEAR(pp.GetX(), 1.0, 1e-10);
    ASSERT_NEAR(pp.GetY(), 2.0, 1e-10);
    ASSERT_NEAR(pp.GetZ(), 3.0, 1e-10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, DefaultConstruct)
{
    Pathd path;
    ASSERT_EQ(holo::common::Timestamp(), path.GetTimestamp());
    ASSERT_EQ(Coordinate::Utm6Coordinate(50U, false), path.GetCoordinate());  // COORD_WORLD
    ASSERT_EQ(Pathd::PlanningState::UNKNOWN, path.GetPlanningState());
    ASSERT_EQ(0, path.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, CopyConstruct)
{
    Pathd path1;
    path1.SetCoordinate(Coordinate(Coordinate::BODY));  // COORD_BODY
    Pathd path2(path1);
    ASSERT_EQ(holo::common::Timestamp(), path2.GetTimestamp());
    ASSERT_EQ(Coordinate(Coordinate::BODY), path2.GetCoordinate());  // COORD_BODY
    ASSERT_EQ(Pathd::PlanningState::UNKNOWN, path2.GetPlanningState());
    ASSERT_EQ(0, path2.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, MoveConstruct)
{
    Pathd      path1;
    PathPointd pp;

    for (int i = 0; i < 100; ++i)
    {
        path1.push_back(pp);
    }
    auto  pointer_record = &path1[0];
    Pathd path2(std::move(path1));
    auto  pointer_new = &path2[0];

    ASSERT_EQ(pointer_record, pointer_new);
}

TEST(Pathd, InitializerConstruct)
{
    Pathd path1({{0, 0, 0}, {1, 1, 0}});
    ASSERT_EQ(2, path1.size());
    ASSERT_NEAR(0, path1[0].GetX(), 1e-10);
    ASSERT_NEAR(0, path1[0].GetY(), 1e-10);
    ASSERT_NEAR(0, path1[0].GetZ(), 1e-10);
    ASSERT_NEAR(1, path1[1].GetX(), 1e-10);
    ASSERT_NEAR(1, path1[1].GetY(), 1e-10);
    ASSERT_NEAR(0, path1[1].GetZ(), 1e-10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, operator_assignment)
{
    Pathd path1, path2;
    path1.SetCoordinate(Coordinate(Coordinate::BODY));  // COORD_BODY

    path2 = path1;
    ASSERT_EQ(holo::common::Timestamp(), path2.GetTimestamp());
    ASSERT_EQ(Coordinate(Coordinate::BODY), path2.GetCoordinate());  // COORD_BODY
    ASSERT_EQ(Pathd::PlanningState::UNKNOWN, path2.GetPlanningState());
    ASSERT_EQ(0, path2.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, operator_move_assignment)
{
    Pathd path1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Pathd path2;
    path1.SetCoordinate(Coordinate(Coordinate::BODY));  // COORD_BODY
    path1.SetValidValue(20);
    path1.SetPlanningState(Pathd::PlanningState::HOLD);
    ASSERT_EQ(3, path1.size());
    ASSERT_EQ(Pathd::Point3Type(1, 2, 3), path1[0]);
    ASSERT_EQ(path1[0], Pathd::Point3Type(1, 2, 3));
    auto pointer_record = &path1[0];

    path2 = std::move(path1);
    ASSERT_EQ(holo::common::Timestamp(), path2.GetTimestamp());
    ASSERT_EQ(Coordinate(Coordinate::BODY), path2.GetCoordinate());   // COORD_BODY
    ASSERT_EQ(20, path2.GetValidValue());                             // COORD_BODY
    ASSERT_EQ(Pathd::PlanningState::HOLD, path2.GetPlanningState());  // COORD_BODY
    ASSERT_EQ(3, path2.size());
    ASSERT_EQ(Pathd::Point3Type(1, 2, 3), path2[0]);

    auto pointer_new = &path2[0];
    ASSERT_EQ(pointer_record, pointer_new);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, operator_initializer_list_assignment)
{
    Pathd path1;
    path1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    path1.SetCoordinate(Coordinate(Coordinate::BODY));  // COORD_BODY

    ASSERT_EQ(3, path1.size());
    ASSERT_EQ(Pathd::Point3Type(1, 2, 3), path1[0]);
    ASSERT_EQ(path1[0], Pathd::Point3Type(1, 2, 3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, Timestamp)
{
    Pathd                   path1;
    holo::common::Timestamp timestamp(5, 6);
    path1.SetTimestamp(timestamp);

    ASSERT_EQ(path1.GetTimestamp().GetSec(), 5);
    ASSERT_EQ(path1.GetTimestamp().GetNsec(), 6);

    const Pathd path2;
    ASSERT_EQ(path2.GetTimestamp().GetSec(), 0);
    ASSERT_EQ(path2.GetTimestamp().GetNsec(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, Coord)
{
    Pathd      path1;
    Coordinate coord = Coordinate(Coordinate::BODY);  // COORD_BODY
    path1.SetCoordinate(coord);

    ASSERT_EQ(path1.GetCoordinate(), Coordinate(Coordinate::BODY));  // COORD_BODY
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, PlanningState)
{
    Pathd path1;
    path1.SetPlanningState(Pathd::PlanningState::HOLD);
    ASSERT_EQ(Pathd::PlanningState::HOLD, path1.GetPlanningState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, at_and_operator_square_bracket)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i, 0.0, 0.0);
        path.push_back(pp);
        ASSERT_EQ(path.at(i).GetX(), i);
        ASSERT_EQ(path[i].GetX(), i);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, front)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    ASSERT_EQ(path.front().GetX(), 7);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, back)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    ASSERT_EQ(path.back().GetX(), 16);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, begin_and_cbegin)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    ASSERT_EQ((*(path.begin())).GetX(), 7);
    ASSERT_EQ((*(path.cbegin())).GetX(), 7);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, rbegin_and_crbegin)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    ASSERT_EQ((*(path.rbegin())).GetX(), 16);
    ASSERT_EQ((*(path.crbegin())).GetX(), 16);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, end_and_cend)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    auto iter_end  = path.end();
    auto iter_cend = path.cend();

    iter_end--;
    iter_cend--;

    ASSERT_EQ((*iter_end).GetX(), 16);
    ASSERT_EQ((*iter_cend).GetX(), 16);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, rend_and_crend)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    auto iter_rend  = path.rend();
    auto iter_crend = path.crend();

    iter_rend--;
    iter_crend--;

    ASSERT_EQ((*iter_rend).GetX(), 7);
    ASSERT_EQ((*iter_crend).GetX(), 7);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, empty)
{
    Pathd      path;
    PathPointd pp;

    ASSERT_TRUE(path.empty());

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }
    ASSERT_FALSE(path.empty());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, size)
{
    Pathd      path;
    PathPointd pp;

    ASSERT_EQ(path.size(), 0);

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
        ASSERT_EQ(path.size(), i + 1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, insert)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    pp.Set(100.0, 0.0, 0.0);
    auto iter = path.begin();
    iter++;
    iter++;
    iter++;
    iter++;
    iter++;
    path.insert(iter, pp);

    ASSERT_EQ(path[5].GetX(), 100.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, emplace)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    pp.Set(100.0, 0.0, 0.0);
    auto iter = path.begin();
    iter++;
    iter++;
    iter++;
    iter++;
    iter++;
    path.emplace(iter, pp);

    ASSERT_EQ(path[5].GetX(), 100.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, erase)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    auto iter = path.begin();
    iter++;
    iter++;
    iter++;
    iter++;
    iter++;
    path.erase(iter);

    ASSERT_EQ(path[5].GetX(), 6.0 + 7.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, push_back)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);

        ASSERT_EQ(path[i].GetX(), i + 7);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, emplace_back)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    pp.Set(100.0, 0.0, 0.0);
    auto iter = path.begin();
    iter++;
    iter++;
    iter++;
    iter++;
    iter++;
    path.emplace_back(pp);
    ASSERT_EQ(path.back().GetX(), 100);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, pop_back)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);

        ASSERT_EQ(path[i].GetX(), i + 7);
    }
    ASSERT_EQ(path.size(), 10);
    path.pop_back();
    ASSERT_EQ(path.size(), 9);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, swap)
{
    Pathd      path, path2;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }

    ASSERT_EQ(path2.size(), 0);
    path2.swap(path);
    ASSERT_EQ(path2.size(), 10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, FindClosestPoint)
{
    Pathd      path;
    PathPointd pp;

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i, 0.0, 0.0);
        path.push_back(pp);
    }

    holo::geometry::Point3d target_point1(3.2, 0.0, 0.0);
    holo::geometry::Point3d target_point2(100.2, 0.0, 0.0);
    holo::geometry::Point3d target_point3(-100.2, 0.0, 0.0);
    holo::geometry::Point3d target_point4(2.9, 0.0, 0.0);

    auto closest_iterator1 = path.FindClosestPoint(path.begin(), target_point1);
    auto closest_iterator2 = path.FindClosestPoint(path.begin(), target_point2);
    auto closest_iterator3 = path.FindClosestPoint(path.begin(), target_point3);
    auto closest_iterator4 = path.FindClosestPoint(path.begin(), target_point4);

    ASSERT_EQ((*closest_iterator1).GetX(), 4.0);
    ASSERT_EQ((*closest_iterator2).GetX(), 9.0);
    ASSERT_EQ((*closest_iterator3).GetX(), 1.0);
    ASSERT_EQ((*closest_iterator4).GetX(), 4.0);
}

TEST(Pathd, FindClosestPoint_3)
{
    Pathd                   path;
    holo::geometry::Point3d target_point1(3.2, 0.0, 0.0);
    path.FindClosestPoint(target_point1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Pathd, ValidValue)
{
    Pathd path;

    ASSERT_EQ(path.GetValidValue(), 0U);
    ASSERT_EQ(path.IsPositionValid(), false);
    ASSERT_EQ(path.IsThetaValid(), false);
    ASSERT_EQ(path.IsCurvatureValid(), false);
    ASSERT_EQ(path.IsSpeedValid(), false);
    ASSERT_EQ(path.IsAccelerationValid(), false);
    ASSERT_EQ(path.IsDistanceValid(), false);
    ASSERT_EQ(path.IsTimeValid(), false);
    ASSERT_EQ(path.AreAllDataValid(), false);

    path.SetValidValue(static_cast<uint32_t>(Pathd::ValidValue::POSITION));
    ASSERT_EQ(path.GetValidValue(), static_cast<uint32_t>(Pathd::ValidValue::POSITION));

    path.SetSingleValidValue(Pathd::ValidValue::THETA);
    ASSERT_EQ(path.GetValidValue(),
              static_cast<uint32_t>(Pathd::ValidValue::POSITION) | static_cast<uint32_t>(Pathd::ValidValue::THETA));

    path.SetSingleValidValue(Pathd::ValidValue::CURVATURE);
    path.SetSingleValidValue(Pathd::ValidValue::SPEED);
    path.SetSingleValidValue(Pathd::ValidValue::ACCELERATION);
    path.SetSingleValidValue(Pathd::ValidValue::DISTANCE);
    path.SetSingleValidValue(Pathd::ValidValue::TIME);

    ASSERT_EQ(path.IsPositionValid(), true);
    ASSERT_EQ(path.IsThetaValid(), true);
    ASSERT_EQ(path.IsCurvatureValid(), true);
    ASSERT_EQ(path.IsSpeedValid(), true);
    ASSERT_EQ(path.IsAccelerationValid(), true);
    ASSERT_EQ(path.IsDistanceValid(), true);
    ASSERT_EQ(path.IsTimeValid(), true);
    ASSERT_EQ(path.AreAllDataValid(), true);
}

TEST(Pathd, GetSerializedSize)
{
    Pathd path;
    ASSERT_EQ(24, path.GetSerializedSize<4U>());
    ASSERT_EQ(24, path.GetSerializedSize<8U>());
}

TEST(Pathd, SerializeDeserialize)
{
    Pathd path1;
    Pathd path2;
    path1 = {{0, 0, 0},
             {1, 0, 0},
             {2, 0, 0},
             {3, 0, 0},
             {4, 1, 1},
             {5, 1, 1}};
    path1.SetTimestamp({1, 2});
    path1.SetCoordinate(holo::common::Coordinate::UtmCoordinate(50, false));
    for (size_t i = 0; i < path1.size(); ++i)
    {
        path1[i].SetTheta(i);
        path1[i].SetCurvature(i);
        path1[i].SetSpeed(i);
        path1[i].SetAcceleration(i);
        path1[i].SetDistance(i);
        path1[i].SetTime(i);
    }

    uint8_t                           buffer[512];
    holo::serialization::Serializer<> serializer(buffer, 512);
    serializer << path1;
    ASSERT_EQ(path1.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> path2;

    ASSERT_EQ(path1.GetTimestamp(), path2.GetTimestamp());
    ASSERT_EQ(path1.GetCoordinate(), path2.GetCoordinate());
    ASSERT_EQ(path1.GetValidValue(), path2.GetValidValue());
    ASSERT_EQ(path1.size(), path2.size());

    for (size_t i = 0; i < path1.size(); ++i)
    {
        ASSERT_EQ(path1[i].GetTheta(), path2[i].GetTheta());
        ASSERT_EQ(path1[i].GetCurvature(), path2[i].GetCurvature());
        ASSERT_EQ(path1[i].GetSpeed(), path2[i].GetSpeed());
        ASSERT_EQ(path1[i].GetAcceleration(), path2[i].GetAcceleration());
        ASSERT_EQ(path1[i].GetDistance(), path2[i].GetDistance());
        ASSERT_EQ(path1[i].GetTime(), path2[i].GetTime());
        ASSERT_EQ(path1[i][0], path2[i][0]);
        ASSERT_EQ(path1[i][1], path2[i][1]);
        ASSERT_EQ(path1[i][2], path2[i][2]);
    }
}

TEST(Pathd, FindClosestPoint_2)
{
    Pathd      path;
    PathPointd pp;
    path.FindClosestPoint(path.begin(), Pathd::Point3Type(1, 2, 3));

    for (int i = 0; i < 10; ++i)
    {
        pp.Set(i + 7, 0.0, 0.0);
        path.push_back(pp);
    }
    path.FindClosestPoint(path.end(), Pathd::Point3Type(1, 2, 3));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
