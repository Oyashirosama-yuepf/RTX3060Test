/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_lane_boundary_type_description.cpp
 * @brief unit test for lane_boundary type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-01
 */

#include <gtest/gtest.h>
#include <holo/metadata/common/lane_boundary_type_description.h>

TEST(TypeDescription, LaneBoundaryT)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::LaneBoundary<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, LaneBoundaryPolynomialT)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float64_t, 3U>>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
