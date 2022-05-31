/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_obstacle_list_type_description.cpp
 * @brief unit test for obstacle_list type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-23
 */

#include <gtest/gtest.h>
#include <holo/metadata/obstacle/obstacle_list_type_description.h>
#include <holo/obstacle/obstacle_list.h>

TEST(TypeDescription, ObstaclePtrListT)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::ObstaclePtrListT<holo::float32_t, 3>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
