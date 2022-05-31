/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_localization_vslam.cpp
 * @brief test localization vslam class
 * @TODO(Feng. Li 2020-01-10) we should carefully design the TestFixture(simulate the trajectory and sensor
 * measurements) to test the vslam pipeline.
 *
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date Mar-18-2019
 */

#include <gtest/gtest.h>
#include <holo/localization/vision/vslam/localization/localization.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Localization, Run)
{
    // create localization
    Localization localization(Localization::Parameters::Example());

    // check status
    ASSERT_TRUE(localization.GetStatus() == Localization::Base::Status::PAUSE);

    // run localization for a while
    localization.Spin();
    std::this_thread::sleep_for(std::chrono::milliseconds(10u));

    // check status
    ASSERT_TRUE(localization.GetStatus() == Localization::Base::Status::SPIN);

    // stop localization
    localization.Stop();

    // check status
    ASSERT_TRUE(localization.GetStatus() == Localization::Base::Status::STOP);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
