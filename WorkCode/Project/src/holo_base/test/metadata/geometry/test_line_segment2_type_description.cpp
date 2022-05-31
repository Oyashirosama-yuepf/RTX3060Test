/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_line_segment2_type_description.cpp
 * @brief unit test for line_segment2 type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-22
 */

#include <gtest/gtest.h>
#include <holo/metadata/geometry/line_segment2_type_description.h>

TEST(TypeDescription, LineSegment2)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::geometry::LineSegment2T<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
