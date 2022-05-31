/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_box3_io.cpp
 * @brief unit test io utils for box3 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 21-04-13
 */

#include <gtest/gtest.h>
#include <holo/geometry/box3.h>
#include <holo/io/geometry/box3.h>

using Box3f   = holo::geometry::Box3f;
using Point3f = holo::geometry::Point3f;

TEST(box3TIO, box3TSaveYaml)
{
    Point3f const center(10.0f, -11.0f, 12.0f);
    Box3f const   box3(1.0f, 2.0f, 3.0f, center);
    Box3f         box3_expect;

    YAML::Node node;
    node["test"] = box3;
    box3_expect  = node["test"].as<Box3f>();

    ASSERT_EQ(box3.GetWidth(), box3_expect.GetWidth());
    ASSERT_EQ(box3.GetHeight(), box3_expect.GetHeight());
    ASSERT_EQ(box3.GetDepth(), box3_expect.GetDepth());
    ASSERT_EQ(box3.GetPose(), box3_expect.GetPose());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
