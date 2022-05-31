/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_landmark.cpp
 * @brief test landmark class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-12"
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/vslam/landmark.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Landmark, constructor)
{
    /* default constructor */
    Landmark landmark;

    ASSERT_EQ(0u, landmark.Id());
    ASSERT_EQ(gtsam::Point3(), landmark.Point());

    // /* constructor with a point3 */
    gtsam::Point3 point(1.0, 2.0, 3.0);
    Landmark      landmark_with_point(point);

    ASSERT_EQ(0u, landmark_with_point.Id());
    ASSERT_EQ(point, landmark_with_point.Point());
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Landmark, update)
{
    Landmark landmark;

    ASSERT_EQ(0u, landmark.Id());
    ASSERT_EQ(gtsam::Point3(), landmark.Point());

    gtsam::Point3 point(-1.0, -2.0, -3.0);
    Landmark      updated_landmark = landmark.UpdateLandmark(point);

    ASSERT_EQ(landmark.Id(), updated_landmark.Id());
    ASSERT_EQ(point, updated_landmark.Point());
    ASSERT_EQ(gtsam::Point3(), landmark.Point());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Landmark, id)
{
    gtsam::Point3 point;
    Landmark      landmark(point);
    ASSERT_NE(0u, landmark.Id());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}