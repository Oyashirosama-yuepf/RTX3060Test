/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_rot3_io.cpp
 * @brief unit test io utils for rot3 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/rot3.h>
#include <holo/io/geometry/rot3.h>

using Rot3f       = holo::geometry::Rot3f;
using Vector3Type = holo::numerics::Vector3f;

TEST(Rot3TIO, Rot3TSaveYaml)
{
    const Vector3Type v1(0.0, 1.0, 0.0);
    const Vector3Type v2(-1.0, 0.0, 0.0);
    const Vector3Type v3(0.0, 0.0, 1.0);

    Rot3f rot3(v1, v2, v3);
    Rot3f rot3_expect;

    YAML::Node node;
    node["test"] = rot3;
    rot3_expect  = node["test"].as<Rot3f>();
    std::cout << node["test"] << std::endl;

    ASSERT_EQ(rot3.ToMatrix(), rot3_expect.ToMatrix());
}

TEST(point3IO, Rot3TException)
{
    Rot3f rot3_expect;
    YAML::Node node = YAML::Load("{'row':1,'col':2}");

    try
    {
        rot3_expect = node.as<Rot3f>();
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
