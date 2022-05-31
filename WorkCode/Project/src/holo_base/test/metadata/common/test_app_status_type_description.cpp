/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_app_status_type_description.cpp
 * @brief unit test for app status type descriptions
 * @author zhangjiannan@holomatic.com
 * @date 2021-01-12
 */

#include <gtest/gtest.h>
#include <holo/common/app_status.h>
#include <holo/metadata/common/app_status_type_description.h>

TEST(TypeDescription, AppStatus)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::AppStatus>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
