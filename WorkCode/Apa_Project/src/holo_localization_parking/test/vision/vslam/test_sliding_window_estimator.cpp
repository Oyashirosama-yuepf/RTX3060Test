/*!
 * \brief Unit test for sliding window estimator in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtsam/navigation/ScenarioRunner.h>

#define private public
#include <vision/vslam/fixtures/sliding_window_estimator_fixture.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, InitializationAndRun)
{
    SlidingWindowState sliding_window_state;
    FeatureTrack       dummy_track(std::make_shared<FeatureTrack::Parameters>(FeatureTrack::Parameters::Example()),
                             camera_parameters_, 1, {});
    const auto&        timestamp_0 = raw_measurements_.at(0).multi_point_feature_list.at(camera_index_).GetTimestamp();
    sliding_window_state.static_tracker_state = Tracker::State(
        0, raw_measurements_.at(0).multi_point_feature_list.at(camera_index_).GetTimestamp(), {dummy_track});

    /**
     * @brief call initialize
     *
     * @details it should call the tracker and add three prior factors (pose,
     *          velocity, bias)
     */
    bool ret = estimator_.Initialize(sliding_window_state, factor_measurements_.at(0), timestamp_0, 0);
    // check result
    ASSERT_TRUE(ret);
    ASSERT_EQ(sliding_window_state.GetTimestamp(),
              raw_measurements_.at(0).multi_point_feature_list.at(camera_index_).GetTimestamp());
    ASSERT_EQ(sliding_window_state.static_smoother.getFactors().size(), 4u);
    ASSERT_EQ(sliding_window_state.values.size(), 3u);

    /**
     * @brief call Run() method after Initialize()
     *
     * @details it should propagate the state one step forward and return a
     *          factor graph with one new IMU factor and one new velocity factor
     */
    sliding_window_state.static_tracker_state = Tracker::State(
        1, raw_measurements_.at(1).multi_point_feature_list.at(camera_index_).GetTimestamp(), {dummy_track});
    const auto& timestamp_1 = raw_measurements_.at(1).multi_point_feature_list.at(camera_index_).GetTimestamp();
    ret                     = estimator_.Run(sliding_window_state, factor_measurements_.at(1), timestamp_1, 1);

    // check results
    ASSERT_TRUE(ret);
    ASSERT_EQ(sliding_window_state.GetTimestamp(),
              raw_measurements_.at(1).multi_point_feature_list.at(camera_index_).GetTimestamp());
    // 3PriorFactors+1ImuFactor+1ImuBiasFactor+2Velocity3Factor
    ASSERT_EQ(sliding_window_state.static_smoother.getFactors().size(), 7u);
    // 3PriorValues+1Pose+1Velocity+1Bias
    ASSERT_EQ(sliding_window_state.values.size(), 6u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, GetOldestFrameId)
{
    uint64_t current_frame_id = 5;

    const auto first_id = estimator_.GetOldestFrameId(current_frame_id);

    /// @brief check result
    ASSERT_EQ(0, first_id);

    current_frame_id = 15;

    const auto second_id = estimator_.GetOldestFrameId(current_frame_id);

    /// @brief check result
    ASSERT_EQ(5, second_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, GetXYZYaw)
{
    const gtsam::Rot3   R = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const gtsam::Point3 t = gtsam::Point3(0.4, 0.5, 0.6);
    const gtsam::Pose3  pose(R, t);
    const Scalar        yaw = pose.rotation().yaw();

    const auto xyz_yaw = estimator_.GetXYZYaw(pose);

    /// @brief check result
    ASSERT_EQ(t, xyz_yaw.first);
    ASSERT_EQ(yaw, xyz_yaw.second);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
