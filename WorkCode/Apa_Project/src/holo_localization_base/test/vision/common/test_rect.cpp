/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_rect.cpp
 * @brief rect unit test
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/common/rect.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Rect, DefaultConstructor)
{
    const holo::localization::Rect2i rect;

    // check result
    ASSERT_EQ(0, rect.GetWidth());
    ASSERT_EQ(0, rect.GetHeight());
    ASSERT_EQ(0, rect.GetArea());
    ASSERT_EQ(0, rect.GetTopLeftX());
    ASSERT_EQ(0, rect.GetTopLeftY());
    ASSERT_EQ(0, rect.GetBottomRightX());
    ASSERT_EQ(0, rect.GetBottomRightY());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Rect, DestructorForAllInstantiatedTypes)
{
    holo::localization::Rect2i* recti(new holo::localization::Rect2i());
    holo::localization::Rect2f* rectf(new holo::localization::Rect2f());
    holo::localization::Rect2d* rectd(new holo::localization::Rect2d());

    // check result
    delete recti;
    delete rectf;
    delete rectd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Rect, Constructor)
{
    const holo::float64_t x(1.0);
    const holo::float64_t y(-1.0);
    const holo::float64_t width(10.0);
    const holo::float64_t height(20.0);

    const holo::localization::Rect2d rect(x, y, width, height);

    // check result
    ASSERT_EQ(width, rect.GetWidth());
    ASSERT_EQ(height, rect.GetHeight());
    ASSERT_EQ(width * height, rect.GetArea());
    ASSERT_EQ(x, rect.GetTopLeftX());
    ASSERT_EQ(y, rect.GetTopLeftY());
    ASSERT_EQ(x + width, rect.GetBottomRightX());
    ASSERT_EQ(y + height, rect.GetBottomRightY());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Rect, InvalidConstruct)
{
    // check result
    ASSERT_THROW(const holo::localization::Rect2f rect(1.0f, 3.0f, -1.0f, -1.0f), std::runtime_error);
    ASSERT_THROW(const holo::localization::Rect2f rect(1.0f, 3.0f, -1.0f, 1.0f), std::runtime_error);
    ASSERT_THROW(const holo::localization::Rect2f rect(1.0f, 3.0f, 1.0f, -1.0f), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
