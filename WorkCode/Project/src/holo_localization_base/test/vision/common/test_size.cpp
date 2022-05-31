/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_size.cpp
 * @brief size unit test
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/common/size.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Size, DefaultConstructor)
{
    const holo::localization::Size2i size;

    // check result
    ASSERT_EQ(0, size.GetWidth());
    ASSERT_EQ(0, size.GetHeight());
    ASSERT_EQ(0, size.GetArea());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Size, DestructorForAllInstantiatedTypes)
{
    holo::localization::Size2i* sizei(new holo::localization::Size2i());
    holo::localization::Size2f* sizef(new holo::localization::Size2f());
    holo::localization::Size2d* sized(new holo::localization::Size2d());

    // check result
    delete sizei;
    delete sizef;
    delete sized;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Size, Constructor)
{
    const holo::float64_t width  = 100.0;
    const holo::float64_t height = 200.0;

    const holo::localization::Size2d size(width, height);

    // check result
    ASSERT_EQ(width, size.GetWidth());
    ASSERT_EQ(height, size.GetHeight());
    ASSERT_EQ(20000.0, size.GetArea());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Size, InvalidConstruct)
{
    // check result
    ASSERT_THROW(const holo::localization::Size2f size(-1.0f, -2.0f), std::runtime_error);
    ASSERT_THROW(const holo::localization::Size2f size(-1.0f, 2.0f), std::runtime_error);
    ASSERT_THROW(const holo::localization::Size2f size(1.0f, -2.0f), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
