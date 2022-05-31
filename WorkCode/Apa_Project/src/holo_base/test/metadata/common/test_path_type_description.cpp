/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_path_type_description.cpp
 * @brief unit test for path type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-28
 */

#include <gtest/gtest.h>
#include <holo/common/path.h>
#include <holo/metadata/common/path_type_description.h>

TEST(TypeDescription, PathT)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::PathT<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
