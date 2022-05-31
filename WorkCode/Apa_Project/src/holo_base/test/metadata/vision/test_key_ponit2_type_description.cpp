/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_keypoint2_type_description.cpp
 * @brief unit test for keypoint2 type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-23
 */

#include <gtest/gtest.h>
#include <holo/vision/keypoint2.h>
#include <holo/metadata/vision/key_ponit2_type_description.h>

TEST(TypeDescription, KeyPoint2T)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::vision::KeyPoint2T<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
