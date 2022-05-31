/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_rot2_type_description.cpp
 * @brief unit test for rot2 type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-22
 */

#include <gtest/gtest.h>
#include <holo/metadata/geometry/rot2_type_description.h>

TEST(TypeDescription, Rot2)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::geometry::Rot2T<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
