/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_coordinate_type_description.cpp
 * @brief unit test for coordinate type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-23
 */

#include <gtest/gtest.h>
#include <holo/common/timestamp.h>
#include <holo/metadata/common/coordinate_type_description.h>

TEST(TypeDescription, Timestamp)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::Coordinate>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
