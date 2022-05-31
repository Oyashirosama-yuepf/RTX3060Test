/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_quaternion_type_description.cpp
 * @brief unit test for quaternion type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-22
 */

#include <gtest/gtest.h>
#include <holo/metadata/geometry/quaternion_type_description.h>

TEST(TypeDescription, Quaternion)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::geometry::QuaternionT<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
