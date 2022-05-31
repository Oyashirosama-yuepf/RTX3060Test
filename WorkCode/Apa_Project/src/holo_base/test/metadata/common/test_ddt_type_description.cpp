/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_ddt_type_description.cpp
 * @brief unit test for ddt type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-28
 */

#include <gtest/gtest.h>
#include <holo/common/ddt.h>
#include <holo/metadata/common/ddt_type_description.h>

TEST(TypeDescription, DdtState)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::DdtState>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, DdtStates)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::DdtStates<10U>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}