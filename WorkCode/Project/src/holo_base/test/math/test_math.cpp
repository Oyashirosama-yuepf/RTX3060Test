/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_math.cpp
 * @brief This file implement unit test for math module.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-06-01
 */

#include <gtest/gtest.h>
#include <holo/math/math.h>

TEST(MATH, Factorial)
{
    ASSERT_EQ(1U, holo::math::Factorial<0U>());
    ASSERT_EQ(1U, holo::math::Factorial<1U>());
    ASSERT_EQ(2U, holo::math::Factorial<2U>());
    ASSERT_EQ(6U, holo::math::Factorial<3U>());
    ASSERT_EQ(24U, holo::math::Factorial<4U>());
    ASSERT_EQ(120U, holo::math::Factorial<5U>());
}

TEST(MATH, PowInt)
{
    ASSERT_NEAR(1.0, holo::math::Pow<0U>(1.0), 1e-6);
    ASSERT_NEAR(1.0, holo::math::Pow<1U>(1.0), 1e-6);
    ASSERT_NEAR(1.0, holo::math::Pow<2U>(1.0), 1e-6);
    ASSERT_NEAR(1.0, holo::math::Pow<3U>(1.0), 1e-6);

    ASSERT_NEAR(1.0, holo::math::Pow<0U>(2.0), 1e-6);
    ASSERT_NEAR(2.0, holo::math::Pow<1U>(2.0), 1e-6);
    ASSERT_NEAR(4.0, holo::math::Pow<2U>(2.0), 1e-6);
    ASSERT_NEAR(8.0, holo::math::Pow<3U>(2.0), 1e-6);
    ASSERT_NEAR(16.0, holo::math::Pow<4U>(2.0), 1e-6);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

