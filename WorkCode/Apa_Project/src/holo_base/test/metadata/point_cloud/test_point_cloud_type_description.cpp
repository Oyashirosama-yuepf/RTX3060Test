/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_point_cloud_type_description.cpp
 * @brief unit test for point_cloud type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-06-28
 */

#include <gtest/gtest.h>
#include <holo/metadata/point_cloud/point_cloud_type_description.h>
#include <holo/point_cloud/point_cloud.h>

using PointType = holo::geometry::Point3T<holo::float32_t>;
using PointCloudTypeUnLayout =
    holo::point_cloud::PointCloudT<PointType, 50U, sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;
using PointCloudTypeLayout =
    holo::point_cloud::PointCloudT<PointType, 50U, sizeof(PointType), holo::point_cloud::OrganizedLayoutTag>;

TEST(TypeDescription, PointCloudTypeUnLayout)
{
    auto desc = holo::metadata::TypeDescriptionResolver<PointCloudTypeUnLayout>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, PointCloudTypeLayout)
{
    auto desc = holo::metadata::TypeDescriptionResolver<PointCloudTypeLayout>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
