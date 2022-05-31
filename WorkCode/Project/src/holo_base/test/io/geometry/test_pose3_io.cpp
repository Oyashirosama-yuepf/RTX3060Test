/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_pose3_io.cpp
 * @brief unit test io utils for pose3 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/pose3.h>
#include <holo/io/geometry/pose3.h>

using Pose3f = holo::geometry::Pose3f;

TEST(pose3IO, Pose3SaveYaml)
{
    Pose3f pose3, pose3_expected;

    pose3.SetRotation(holo::geometry::Rot3f(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0));
    pose3.SetTranslation(holo::geometry::Point3f(1.0, 2.0, 3.0));

    YAML::Node node;
    node["test"]   = pose3;
    pose3_expected = node["test"].as<Pose3f>();
    std::cout << node["test"] << std::endl;

    ASSERT_EQ(pose3, pose3_expected);
}

TEST(point3IO, Pose3TException)
{
    Pose3f pose3;
    YAML::Node node = YAML::Load("{'translation':{'x':1, 'y': 2}}");

    try
    {
        pose3 = node.as<Pose3f>();
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
