/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_box3_type_description.cpp
 * @brief unit test for box3 type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-22
 */

#include <gtest/gtest.h>
#include <holo/metadata/geometry/box3_type_description.h>

TEST(TypeDescription, Box3)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::geometry::Box3T<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
