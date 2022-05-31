/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_base_type_description.cpp
 * @brief unit test for obstacle_base type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-23
 */

#include <gtest/gtest.h>
#include <holo/obstacle/obstacle_base.h>
#include <holo/metadata/obstacle/obstacle_base_type_description.h>

TEST(TypeDescription, CutInCutOut)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::obstacle::details::CutInCutOut>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, MotionStatus)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::obstacle::details::MotionStatus>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
