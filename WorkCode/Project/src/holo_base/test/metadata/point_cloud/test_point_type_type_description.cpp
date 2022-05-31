/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_point_type_type_description.cpp
 * @brief unit test for point_type type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-06-28
 */

#include <gtest/gtest.h>
#include <holo/metadata/point_cloud/point_type_type_description.h>
#include <holo/point_cloud/point_type.h>

TEST(TypeDescription, PointXYZIRSt)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::point_cloud::PointXYZIRSt<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, PointXYZIRRgbSt)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::point_cloud::PointXYZIRRgbSt<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
