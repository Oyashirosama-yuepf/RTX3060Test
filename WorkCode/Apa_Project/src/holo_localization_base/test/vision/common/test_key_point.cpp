/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_key_point.cpp
 * @brief keypoint unit test
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/common/key_point.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(KeyPoint, DefaultConstructor)
{
    const holo::localization::KeyPoint2f keypoint;

    // check result
    ASSERT_EQ(holo::geometry::Point2f::Zero(), keypoint.GetPoint());
    ASSERT_EQ(1.0f, keypoint.GetSize());
    ASSERT_EQ(-1.0f, keypoint.GetAngle());
    ASSERT_EQ(0.0f, keypoint.GetResponse());
    ASSERT_EQ(0, keypoint.GetOctave());
    ASSERT_EQ(-1, keypoint.GetClassId());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(KeyPoint, Constructor)
{
    const holo::geometry::Point2f pt(1.0f, -2.0f);
    const holo::float32_t size(3.0f);
    const holo::float32_t angle(-4.0f);
    const holo::float32_t response(5.0f);
    const holo::int32_t   octave(6);
    const holo::int32_t   class_id(7);

    const holo::localization::KeyPoint2f keypoint(pt, size, angle, response, octave, class_id);

    // check result
    ASSERT_EQ(pt, keypoint.GetPoint());
    ASSERT_EQ(size, keypoint.GetSize());
    ASSERT_EQ(angle, keypoint.GetAngle());
    ASSERT_EQ(response, keypoint.GetResponse());
    ASSERT_EQ(octave, keypoint.GetOctave());
    ASSERT_EQ(class_id, keypoint.GetClassId());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
