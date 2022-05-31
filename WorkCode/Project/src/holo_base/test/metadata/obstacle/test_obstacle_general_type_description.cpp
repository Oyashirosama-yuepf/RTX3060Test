/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_general_type_description.cpp
 * @brief unit test for obstacle_general type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-23
 */

#include <gtest/gtest.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/metadata/obstacle/obstacle_general_type_description.h>

TEST(TypeDescription, ObstacleGeneralT)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::obstacle::ObstacleGeneralT<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
