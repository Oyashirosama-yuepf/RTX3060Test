/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_rot2_io.cpp
 * @brief unit test io utils for rot2 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/rot2.h>
#include <holo/io/geometry/rot2.h>

using Rot2f = holo::geometry::Rot2f;

TEST(Rot2TIO, Rot2TSaveYaml)
{
    Rot2f rot2;
    rot2.FromDegree(90.0);
    Rot2f rot2_expect;

    YAML::Node node;
    node["test"] = rot2;
    rot2_expect  = node["test"].as<Rot2f>();

    ASSERT_EQ(rot2.ToMatrix(), rot2_expect.ToMatrix());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
