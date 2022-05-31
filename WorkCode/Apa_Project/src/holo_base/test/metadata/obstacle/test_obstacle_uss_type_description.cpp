/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_uss_type_description.cpp
 * @brief unit test for obstacle_uss type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-09-18
 */

#include <gtest/gtest.h>
#include <holo/obstacle/obstacle_uss.h>
#include <holo/metadata/obstacle/obstacle_uss_type_description.h>

TEST(TypeDescription, ObstacleUssT)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::obstacle::ObstacleUssT<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
