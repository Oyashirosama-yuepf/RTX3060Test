/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_point3_io.cpp
 * @brief unit test io utils for point3 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/point3.h>
#include <holo/io/geometry/point3.h>

using Point3f = holo::geometry::Point3f;

TEST(point3IO, Point3TSaveYaml)
{
    Point3f point3 = Point3f(1.0f, 2.0f, 3.0f);
    Point3f point3_expected;

    YAML::Node node;
    node["test"]    = point3;
    point3_expected = node["test"].as<Point3f>();

    ASSERT_EQ(point3, point3_expected);
}

TEST(point3IO, Point3TException)
{
    Point3f point3_expected;
    YAML::Node node = YAML::Load("{'x':1,'y':2}");

    try
    {
        point3_expected = node.as<Point3f>();
    }
    catch(...)
    {
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
