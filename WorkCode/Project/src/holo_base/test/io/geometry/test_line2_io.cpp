/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_line2_io.cpp
 * @brief unit test io utils for line2 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/line2.h>
#include <holo/io/geometry/line2.h>
#include <holo/io/numerics/vector.h>

using Line2f = holo::geometry::Line2f;

TEST(line2TIO, line2TSaveYaml)
{
    Line2f line2 = {1.0f, 0.0f, 4.0f};
    Line2f line2_expect;

    YAML::Node node;
    node["test"] = line2;
    line2_expect = node["test"].as<Line2f>();

    ASSERT_EQ(line2.GetCoeffs(), line2_expect.GetCoeffs());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
