/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_fast.cpp
 * @brief test fast class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-10"
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/feature/fast.h>

using FAST = holo::localization::FAST;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FAST, constructor)
{
    /* constructor */
    FAST fast(10, false, FAST::Type::TYPE_9_16);
    ASSERT_EQ(10, fast.GetThreshold());
    ASSERT_FALSE(fast.GetNonmaxSuppression());
    ASSERT_EQ(FAST::Type::TYPE_9_16, fast.GetType());

    /* copy constructor */
    FAST other(fast);
    ASSERT_EQ(fast.GetThreshold(), other.GetThreshold());
    ASSERT_TRUE(fast.GetNonmaxSuppression() == other.GetNonmaxSuppression());
    ASSERT_EQ(fast.GetType(), other.GetType());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FAST, constructor_throw)
{
    ASSERT_THROW(FAST fast(10, false, static_cast<FAST::Type>(255u)), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FAST, basic)
{
    FAST fast(10, false, FAST::Type::TYPE_9_16);

    /* set and get threshold */
    fast.SetThreshold(20);
    ASSERT_EQ(20, fast.GetThreshold());

    /* set and get nonmax suppression */
    fast.SetNonmaxSuppression(true);
    ASSERT_TRUE(fast.GetNonmaxSuppression());

    /* set and get type */
    fast.SetType(FAST::Type::TYPE_7_12);
    ASSERT_EQ(FAST::Type::TYPE_7_12, fast.GetType());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FAST, operator_assign)
{
    FAST fast(10, false, FAST::Type::TYPE_5_8);
    FAST other(20, true, FAST::Type::TYPE_9_16);

    other = fast;
    ASSERT_EQ(fast.GetThreshold(), other.GetThreshold());
    ASSERT_TRUE(fast.GetNonmaxSuppression() == other.GetNonmaxSuppression());
    ASSERT_EQ(fast.GetType(), other.GetType());

    /* assign itself */
    other = other;
    ASSERT_EQ(FAST::Type::TYPE_5_8, other.GetType());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FAST, Detect)
{
    /// @brief use mask to construct a image because we can operate on Mat directly
    FAST::Mask image(200u, 200u, 0u);

    uint16_t step = 30u;  /// < the step size between the point

    for (uint16_t i = 1u; i < 7u; i++)  /// < generate 36 points
    {
        for (uint16_t j = 1u; j < 7u; j++)
        {
            image.At(i * step, j * step) = 255u;
        }
    }

    /// @brief detect fast corner
    FAST                          fast(10, false, FAST::Type::TYPE_9_16);
    std::vector<FAST::KeyPoint2f> keypoints;
    const holo::bool_t            is_success = fast.Detect(image, keypoints);

    ASSERT_TRUE(is_success);
    ASSERT_EQ(36u, static_cast<uint16_t>(keypoints.size()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
