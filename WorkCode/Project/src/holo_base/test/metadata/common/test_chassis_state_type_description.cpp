/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_chassis_state_type_description.cpp
 * @brief unit test for chassis_state type descriptions
 * @author zhangjiannan@holomatic.com
 * @date 2021-01-08
 */

#include <gtest/gtest.h>
#include <holo/common/chassis_state.h>
#include <holo/metadata/common/chassis_state_type_description.h>

TEST(TypeDescription, ChassisState)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::ChassisState>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
