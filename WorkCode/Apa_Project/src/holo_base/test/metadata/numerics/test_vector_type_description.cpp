/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_vector_type_description.cpp
 * @brief unit test for vector type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-23
 */

#include <gtest/gtest.h>
#include <holo/metadata/numerics/vector_type_description.h>

TEST(TypeDescription, Vector_1)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::numerics::VectorT<holo::float32_t, 3>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, Vector_2)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::numerics::VectorT<holo::float32_t, -1>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
