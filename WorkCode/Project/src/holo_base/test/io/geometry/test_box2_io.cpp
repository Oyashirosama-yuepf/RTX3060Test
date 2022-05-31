/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_box2_io.cpp
 * @brief unit test io utils for box2 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/box2.h>
#include <holo/io/geometry/box2.h>

using Box2f = holo::geometry::Box2f;

TEST(box2TIO, box2TSaveYaml)
{
    Box2f box2, box2_expect;
    box2.SetWidth(10.0);
    box2.SetHeight(5.0);
    box2.SetPose(holo::geometry::Pose2f(0.1, 1.0, -1.0));

    YAML::Node node;
    node["test"] = box2;
    box2_expect  = node["test"].as<Box2f>();

    ASSERT_EQ(box2.GetWidth(), box2_expect.GetWidth());
    ASSERT_EQ(box2.GetHeight(), box2_expect.GetHeight());
    ASSERT_EQ(box2.GetPose(), box2_expect.GetPose());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
