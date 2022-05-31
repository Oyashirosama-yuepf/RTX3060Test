/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_light_signal_request_type_description.cpp
 * @brief unit test for light signal request type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-03
 */

#include <gtest/gtest.h>
#include <holo/metadata/common/light_signal_request_type_description.h>
TEST(TypeDescription, LightSignalRequest)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::LightSignalRequest>::Get();
    EXPECT_EQ("holo::LightSignalRequest", desc->GetName());
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
