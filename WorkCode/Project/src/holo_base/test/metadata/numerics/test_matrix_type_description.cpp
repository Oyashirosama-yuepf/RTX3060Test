/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_matrix_type_description.cpp
 * @brief unit test for matrix type descriptions
 * @author zhangjiannan@holomatic.com
 * @date 2021-01-08
 */

#include <gtest/gtest.h>
#include <holo/metadata/numerics/matrix_type_description.h>

TEST(TypeDescription, Sequence)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::numerics::MatrixT<holo::float32_t, 3, 6>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
