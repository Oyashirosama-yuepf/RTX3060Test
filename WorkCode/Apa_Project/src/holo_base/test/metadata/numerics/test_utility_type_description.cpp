/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_utility_type_description.cpp
 * @brief unit test for utility type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-01
 */

#include <gtest/gtest.h>
#include <holo/metadata/numerics/utility_type_description.h>

TEST(TypeDescription, Sequence)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::numerics::Polynomial<holo::float32_t, 8>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
