/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_convex_polygon2_io.cpp
 * @brief unit test io utils for convex_polygon2 objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/geometry/convex_polygon2.h>
#include <holo/io/geometry/convex_polygon2.h>

using ConvexPolygon2f       = holo::geometry::ConvexPolygon2f;

TEST(convex_polygon2IO, convex_polygon2SaveYaml)
{
    holo::geometry::ConvexPolygon2f input_pf, output_expect;

    srand(time(0));

    int32_t point_cnt = 10;
    int32_t i          = 0;
    for (i = 0; i < point_cnt; ++i)
    {
        input_pf.AppendVertex(holo::geometry::Point2f((holo::float32_t)(rand() % 100), (holo::float32_t)(rand() % 1000)));
    }

    YAML::Node node;
    node["test"] = input_pf;
    output_expect  = node["test"].as<ConvexPolygon2f>();

    ASSERT_EQ(input_pf.GetSize(), output_expect.GetSize());
    for (i = 0; i < input_pf.GetSize(); ++i)
    {
        ASSERT_EQ(input_pf.GetVertex(i).GetX(), output_expect.GetVertex(i).GetX());
        ASSERT_EQ(input_pf.GetVertex(i).GetY(), output_expect.GetVertex(i).GetY());
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
