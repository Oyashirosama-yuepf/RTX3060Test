/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_pose2_type_description.cpp
 * @brief unit test for pose2 type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-22
 */

#include <gtest/gtest.h>
#include <holo/metadata/geometry/pose2_type_description.h>

TEST(TypeDescription, Pose2)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::geometry::Pose2T<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
