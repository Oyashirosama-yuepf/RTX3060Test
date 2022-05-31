/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_quaternionT_io.cpp
 * @brief unit test io utils for quaternionT objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/quaternion.h>
#include <holo/io/geometry/quaternion.h>

using Quaternionf = holo::geometry::Quaternionf;

TEST(QuaternionIO, QuaternionSaveYaml)
{
    holo::float32_t data[4u] = {0.1, 0.2, 0.3, 0.4};
    Quaternionf     quaternion(data, 4u), quaternion_expect;

    YAML::Node node;
    node["test"]      = quaternion;
    quaternion_expect = node["test"].as<Quaternionf>();

    ASSERT_FLOAT_EQ(quaternion.GetW(), quaternion_expect.GetW());
    ASSERT_FLOAT_EQ(quaternion.GetX(), quaternion_expect.GetX());
    ASSERT_FLOAT_EQ(quaternion.GetY(), quaternion_expect.GetY());
    ASSERT_FLOAT_EQ(quaternion.GetZ(), quaternion_expect.GetZ());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
