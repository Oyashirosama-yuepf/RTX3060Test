/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_odometry_type_description.cpp
 * @brief unit test for odometry type descriptions
 * @author zhangjiannan@holomatic.com
 * @date 2021-01-08
 */

#include <gtest/gtest.h>
#include <holo/common/odometry.h>
#include <holo/metadata/common/odometry_type_description.h>

TEST(TypeDescription, Odometry)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::Odometryf>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, OdometryToYaml)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::Odometryf>::Get();
    std::cout << desc->ToYaml() << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
