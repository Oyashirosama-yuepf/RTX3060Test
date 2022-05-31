/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_line_segment2_io.cpp
 * @brief unit test io utils for line_segment2 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/line_segment2.h>
#include <holo/io/geometry/line_segment2.h>

using LineSegment2f = holo::geometry::LineSegment2f;
using Point2f       = holo::geometry::Point2f;

TEST(LineSegment2TIO, LineSegment2TSaveYaml)
{
    LineSegment2f line_segment2(Point2f(-5.0f, 1.0f), Point2f(3.0f, 7.0f));
    LineSegment2f line_segment2_expect;

    YAML::Node node;
    node["test"]         = line_segment2;
    line_segment2_expect = node["test"].as<LineSegment2f>();

    ASSERT_EQ(line_segment2, line_segment2_expect);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
