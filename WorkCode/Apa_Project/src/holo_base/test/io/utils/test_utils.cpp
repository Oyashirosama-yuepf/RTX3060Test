/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_utils.cpp
 * @brief unit test utils objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */
#include <gtest/gtest.h>
#include <holo/io/utils/utils.h>

TEST(utils, IsDigit)
{
    std::string str = "12345";
    ASSERT_TRUE(YAML::IsDigit(str));

    str = "0x12345";
    ASSERT_TRUE(YAML::IsDigit(str));

    str = "0x123abc";
    ASSERT_TRUE(YAML::IsDigit(str));

    str = "0xabcABC";
    ASSERT_TRUE(YAML::IsDigit(str));

    str = "0x8888880995b990c9";
    ASSERT_TRUE(YAML::IsDigit(str));

    str = "12345";
    ASSERT_TRUE(YAML::IsDigit(str));

    str = "0x88cg";
    ASSERT_FALSE(YAML::IsDigit(str));

    str = "123xx";
    ASSERT_FALSE(YAML::IsDigit(str));

    str = "123bg";
    ASSERT_FALSE(YAML::IsDigit(str));

    str = "0x123bg";
    ASSERT_FALSE(YAML::IsDigit(str));

    str = "--12345";
    ASSERT_FALSE(YAML::IsDigit(str));

    str = "0x8888880_0990893";
    ASSERT_FALSE(YAML::IsDigit(str));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
