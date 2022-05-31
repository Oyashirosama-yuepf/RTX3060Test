/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_alarm_io.cpp
 * @brief unit test io utils for alarm objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/common/path.h>
#include <holo/io/common/path.h>

using PathPointf = holo::common::PathPointf;
using Pathf      = holo::common::Pathf;

TEST(PathPointIO, EncodeAndDecodePathPoint)
{
    PathPointf path_point, path_point_expected;

    path_point.SetAcceleration(1.234);
    path_point.SetSpeed(2.234);
    path_point.SetCurvature(3.234);
    path_point.SetTheta(4.23);
    path_point.Set(1.0, 2.0, 3.0);

    YAML::Node node;
    node["test"]        = path_point;
    path_point_expected = node["test"].as<PathPointf>();

    ASSERT_EQ(path_point.GetAcceleration(), path_point_expected.GetAcceleration());
    ASSERT_EQ(path_point.GetSpeed(), path_point_expected.GetSpeed());
    ASSERT_EQ(path_point.GetCurvature(), path_point_expected.GetCurvature());
    ASSERT_EQ(path_point.GetTheta(), path_point_expected.GetTheta());
    ASSERT_NEAR(path_point.GetX(), path_point_expected.GetX(), 1e-10);
    ASSERT_NEAR(path_point.GetY(), path_point_expected.GetY(), 1e-10);
    ASSERT_NEAR(path_point.GetZ(), path_point_expected.GetZ(), 1e-10);
}

TEST(PathIO, EncodeAndDecodePath)
{
    Pathf path, path_expected;
    path = {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 1, 1}, {5, 1, 1}};
    path.SetTimestamp({1, 2});
    path.SetCoordinate(holo::common::Coordinate::UtmCoordinate(50, false));
    path.SetValidValue(31);
    for (size_t i = 0; i < path.size(); ++i)
    {
        path[i].SetTheta(i);
        path[i].SetCurvature(i);
        path[i].SetSpeed(i);
        path[i].SetAcceleration(i);
    }

    YAML::Node node;
    node["test"]  = path;
    path_expected = node["test"].as<Pathf>();

    ASSERT_EQ(path.GetTimestamp(), path_expected.GetTimestamp());
    ASSERT_EQ(path.GetCoordinate(), path_expected.GetCoordinate());
    ASSERT_EQ(path.GetValidValue(), path_expected.GetValidValue());
    ASSERT_EQ(path.size(), path_expected.size());

    for (size_t i = 0; i < path.size(); ++i)
    {
        ASSERT_EQ(path[i].GetTheta(), path_expected[i].GetTheta());
        ASSERT_EQ(path[i].GetCurvature(), path_expected[i].GetCurvature());
        ASSERT_EQ(path[i].GetSpeed(), path_expected[i].GetSpeed());
        ASSERT_EQ(path[i].GetAcceleration(), path_expected[i].GetAcceleration());
        ASSERT_EQ(path[i][0], path_expected[i][0]);
        ASSERT_EQ(path[i][1], path_expected[i][1]);
        ASSERT_EQ(path[i][2], path_expected[i][2]);
    }
}

TEST(PathIO, DecodePath_1)
{
    Pathf path, path_expected;
    path = {};
    path.SetTimestamp({1, 2});
    path.SetCoordinate(holo::common::Coordinate::UtmCoordinate(50, false));
    path.SetValidValue(21);

    YAML::Node node;
    node["timestamp"]  = holo::Timestamp(1, 2);
    node["coordinate"] = holo::common::Coordinate::UtmCoordinate(50, false);
    node["valid_value"].push_back("POSITION");
    node["valid_value"].push_back("CURVATURE");
    node["valid_value"].push_back("ACCELERATION");

    path_expected = node.as<Pathf>();

    ASSERT_EQ(path.GetTimestamp(), path_expected.GetTimestamp());
    ASSERT_EQ(path.GetCoordinate(), path_expected.GetCoordinate());
    ASSERT_EQ(path.GetValidValue(), path_expected.GetValidValue());
    ASSERT_EQ(path.size(), path_expected.size());

    for (size_t i = 0; i < path.size(); ++i)
    {
        ASSERT_EQ(path[i].GetTheta(), path_expected[i].GetTheta());
        ASSERT_EQ(path[i].GetCurvature(), path_expected[i].GetCurvature());
        ASSERT_EQ(path[i].GetSpeed(), path_expected[i].GetSpeed());
        ASSERT_EQ(path[i].GetAcceleration(), path_expected[i].GetAcceleration());
        ASSERT_EQ(path[i][0], path_expected[i][0]);
        ASSERT_EQ(path[i][1], path_expected[i][1]);
        ASSERT_EQ(path[i][2], path_expected[i][2]);
    }
}

TEST(PathIO, DecodePath_2)
{
    Pathf path, path_expected;
    path = {};
    path.SetTimestamp({1, 2});
    path.SetCoordinate(holo::common::Coordinate::UtmCoordinate(50, false));
    path.SetValidValue(21);

    YAML::Node node;
    node["timestamp"]  = holo::Timestamp(1, 2);
    node["coordinate"] = holo::common::Coordinate::UtmCoordinate(50, false);
    node["valid_value"].push_back("POSITION");
    node["valid_value"].push_back(0x04);
    node["valid_value"].push_back("ACCELERATION");

    path_expected = node.as<Pathf>();

    ASSERT_EQ(path.GetTimestamp(), path_expected.GetTimestamp());
    ASSERT_EQ(path.GetCoordinate(), path_expected.GetCoordinate());
    ASSERT_EQ(path.GetValidValue(), path_expected.GetValidValue());
    ASSERT_EQ(path.size(), path_expected.size());

    for (size_t i = 0; i < path.size(); ++i)
    {
        ASSERT_EQ(path[i].GetTheta(), path_expected[i].GetTheta());
        ASSERT_EQ(path[i].GetCurvature(), path_expected[i].GetCurvature());
        ASSERT_EQ(path[i].GetSpeed(), path_expected[i].GetSpeed());
        ASSERT_EQ(path[i].GetAcceleration(), path_expected[i].GetAcceleration());
        ASSERT_EQ(path[i][0], path_expected[i][0]);
        ASSERT_EQ(path[i][1], path_expected[i][1]);
        ASSERT_EQ(path[i][2], path_expected[i][2]);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
