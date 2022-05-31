/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_type_traits.cpp
 * @brief Unit test for type traits.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-2-7
 */

#include <gtest/gtest.h>

#include <holo/core/type_traits.h>

TEST(TYPE_TRATIS, And)
{
    static_assert(holo::And<true>::value, "");
    static_assert(holo::And<true, true>::value, "");
    static_assert(holo::And<true, true, true>::value, "");
    static_assert(holo::And<true, true, true, true>::value, "");
    static_assert(!holo::And<false>::value, "");
    static_assert(!holo::And<true, false>::value, "");
    static_assert(!holo::And<false, false>::value, "");
    static_assert(!holo::And<false, true, true>::value, "");
    static_assert(!holo::And<true, false, true>::value, "");
    static_assert(!holo::And<true, false, false>::value, "");
    static_assert(!holo::And<false, true, true, true>::value, "");
    static_assert(!holo::And<true, false, true, true>::value, "");
    static_assert(!holo::And<true, true, false, true>::value, "");
    static_assert(!holo::And<true, true, true, false>::value, "");
};

TEST(TYPE_TRAITS, Or)
{
    static_assert(!holo::Or<false>::value, "");
    static_assert(!holo::Or<false, false>::value, "");
    static_assert(!holo::Or<false, false, false>::value, "");
    static_assert(!holo::Or<false, false, false, false>::value, "");
    static_assert(holo::Or<true>::value, "");
    static_assert(holo::Or<false, true>::value, "");
    static_assert(holo::Or<true, false>::value, "");
    static_assert(holo::Or<true, false, false>::value, "");
    static_assert(holo::Or<false, true, false>::value, "");
    static_assert(holo::Or<false, true, false>::value, "");
    static_assert(holo::Or<true, false, false, false>::value, "");
    static_assert(holo::Or<false, true, false, false>::value, "");
    static_assert(holo::Or<false, false, true, false>::value, "");
    static_assert(holo::Or<false, false, false, true>::value, "");
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
