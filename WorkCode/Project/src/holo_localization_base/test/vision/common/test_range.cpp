/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_range.cpp
 * @brief range unit test
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/common/range.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Range, DefaultConstructor)
{
    const holo::localization::RangeInt range;

    // check result
    ASSERT_EQ(0, range.GetStart());
    ASSERT_EQ(1, range.GetEnd());
    ASSERT_EQ(1, range.GetSize());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Range, Constructor)
{
    const holo::localization::RangeInt range(-10, 20);

    // check result
    ASSERT_EQ(-10, range.GetStart());
    ASSERT_EQ(20, range.GetEnd());
    ASSERT_EQ(30, range.GetSize());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Size, InvalidConstruct)
{
    // check result
    ASSERT_THROW(const holo::localization::RangeInt range(3, 1), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
