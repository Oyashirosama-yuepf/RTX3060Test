/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_pose2_io.cpp
 * @brief unit test io utils for pose2 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/pose2.h>
#include <holo/io/geometry/pose2.h>

using Pose2f = holo::geometry::Pose2f;

TEST(pose2IO, Pose2SaveYaml)
{
    Pose2f pose2(holo::geometry::Rot2f(holo::geometry::Radian(3.0)), holo::geometry::Point2f(1.3, 2.3));
    Pose2f pose2_expected;

    YAML::Node node;
    node["test"]   = pose2;
    pose2_expected = node["test"].as<Pose2f>();

    ASSERT_EQ(pose2, pose2_expected);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
