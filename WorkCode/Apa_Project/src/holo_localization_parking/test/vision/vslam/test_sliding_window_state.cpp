/*!
 * \brief sliding window state unit test in vslam
 * \author Shuaijie. Li, lishuaijie@holomaitc.com
 * \date Dec-13-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/vslam/sliding_window_state.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SlidingWindowState, Constructor)
{
    SlidingWindowState state;

    /// @brief check result
    ASSERT_EQ(0, state.static_tracker_state.frame_id);
    ASSERT_EQ(0, state.static_tracker_state.tracks.size());
    ASSERT_TRUE(state.static_smoother.getFactors().empty());
    ASSERT_TRUE(state.values.empty());
    ASSERT_TRUE(state.compensated_values.empty());
    ASSERT_FALSE(state.IsInitialized());
    ASSERT_EQ(holo::Timestamp(), state.GetTimestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SlidingWindowState, Basic)
{
    const uint16_t camera_index   = 0;
    const uint64_t first_frame_id = 0u;

    /// @brief generate a track
    const Tracker::Parameters tracker_parameters = Tracker::Parameters::Example();

    const Feature feature(cv::Point2f(1.0, 2.0), boost::none, Point3(0.5, 0.8, 1), camera_index);
    const auto    measurement =
        std::make_pair(first_frame_id, FeatureTrack::CameraIndexedFeature{{camera_index, feature}});

    /// @brief construct feature_track
    const FeatureTrack feature_track =
        FeatureTrack::CreateNewTrack(tracker_parameters.track_params, CameraParameters::Example(), measurement);

    /// @brief generate tracker state
    Tracker::State  state;
    holo::Timestamp timestamp = holo::Timestamp();
    state.frame_id            = first_frame_id;
    state.tracks.push_back(feature_track);

    /// @brief generate pose1, velocity1, bias1
    const gtsam::Rot3                  R1 = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const gtsam::Point3                t1 = gtsam::Point3(0.4, 0.5, 0.6);
    const gtsam::Pose3                 pose1(R1, t1);
    const gtsam::Vector3               velocity1 = gtsam::Vector3(1.0, 1.0, 1.0);
    const gtsam::imuBias::ConstantBias bias1     = gtsam::imuBias::ConstantBias();

    /**
     * @brief generate a slinding window state constains
     *  1 feature track and 1 vehicle state corresponding to first_frame_id
     */
    SlidingWindowState sliding_window_state;
    sliding_window_state.static_tracker_state = state;

    // insert values
    sliding_window_state.compensated_values.insert(X(first_frame_id), pose1);
    sliding_window_state.compensated_values.insert(V(first_frame_id), velocity1);
    sliding_window_state.compensated_values.insert(B(first_frame_id), bias1);

    /* check sliding window state */
    ASSERT_FALSE(sliding_window_state.IsInitialized());
    ASSERT_EQ(timestamp, sliding_window_state.GetTimestamp());
    ASSERT_TRUE(assert_equal(
        pose1, holo::localization::HoloGtsam::Convert(sliding_window_state.NewestVehicleState().Pose()), 1e-9));
    ASSERT_TRUE(assert_equal(gtsam::Pose3(), sliding_window_state.NewestRelativePose(), 1e-9));

    /**
     * @brief add a vehicle state to slinding window state
     *  1 feature track and 2 vehicle state
     */
    const uint64_t second_frame_id                     = 1u;
    sliding_window_state.static_tracker_state.frame_id = second_frame_id;

    /// @brief generate pose2, velocity2, bias2
    const gtsam::Rot3                  R2 = gtsam::Rot3::RzRyRx(0.15, 0.25, 0.35);
    const gtsam::Point3                t2 = gtsam::Point3(0.45, 0.55, 0.65);
    const gtsam::Pose3                 pose2(R2, t2);
    const gtsam::Vector3               velocity2 = gtsam::Vector3(1.0, 1.0, 1.0);
    const gtsam::imuBias::ConstantBias bias2     = gtsam::imuBias::ConstantBias();

    // insert values
    sliding_window_state.compensated_values.insert(X(second_frame_id), pose2);
    sliding_window_state.compensated_values.insert(V(second_frame_id), velocity2);
    sliding_window_state.compensated_values.insert(B(second_frame_id), bias2);

    ASSERT_FALSE(sliding_window_state.IsInitialized());
    ASSERT_EQ(timestamp, sliding_window_state.GetTimestamp());
    ASSERT_TRUE(assert_equal(
        pose2, holo::localization::HoloGtsam::Convert(sliding_window_state.NewestVehicleState().Pose()), 1e-9));
    ASSERT_TRUE(assert_equal(pose1.inverse() * pose2, (sliding_window_state.NewestRelativePose()).inverse(), 1e-9));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SlidingWindowState, test_throw)
{
    const uint64_t frame_id = 10u;

    /// @brief generate tracker state
    Tracker::State state;
    state.frame_id = frame_id;

    SlidingWindowState sliding_window_state;
    sliding_window_state.static_tracker_state = state;

    /// @brief ${framd_id}th vehicle does not exist
    ASSERT_THROW(sliding_window_state.NewestVehicleState(), std::runtime_error);
    ASSERT_THROW(sliding_window_state.NewestRelativePose(), std::runtime_error);

    /// @brief ${framd_id - 1}th vehicle does not exist
    sliding_window_state.compensated_values.insert(X(frame_id), gtsam::Pose3());
    sliding_window_state.compensated_values.insert(V(frame_id), gtsam::Vector3());
    sliding_window_state.compensated_values.insert(B(frame_id), gtsam::imuBias::ConstantBias());
    ASSERT_THROW(sliding_window_state.NewestRelativePose(), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
