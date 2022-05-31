/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_point2_io.cpp
 * @brief unit test io utils for point2 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/point2.h>
#include <holo/io/geometry/point2.h>

using Point2f = holo::geometry::Point2f;

TEST(point2IO, Point2TSaveYaml)
{
    Point2f point2 = Point2f(1.0f, 2.0f);
    Point2f point2_expected;

    YAML::Node node;
    node["test"]    = point2;
    point2_expected = node["test"].as<Point2f>();

    ASSERT_EQ(point2, point2_expected);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
