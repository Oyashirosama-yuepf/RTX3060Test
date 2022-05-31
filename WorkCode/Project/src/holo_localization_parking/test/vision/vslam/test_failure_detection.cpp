/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_failure_detection.cpp
 * @brief failure detection unit test
 * @author Yanwei Du(duyanwei@holomaitc.com)
 * @date "2019-12-12"
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/vslam/failure_detection.h>

using namespace holo::localization::vision::vslam;

namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief construct sliding window state
 *
 * @return SlidingWindowState
 */
SlidingWindowState ConstructState()
{
    const uint64_t first_frame_id = 0u;
    const uint16_t camera_index   = 0;

    /* @brief generate a track */
    const Tracker::Parameters tracker_parameters = Tracker::Parameters::Example();
    const Feature             feature(cv::Point2f(1.0, 2.0), boost::none, Point3(1.0, 2.0, 1.0), 0);
    const auto                measurement =
        std::make_pair(first_frame_id, FeatureTrack::CameraIndexedFeature{{camera_index, feature}});
    const FeatureTrack feature_track =
        FeatureTrack::CreateNewTrack(tracker_parameters.track_params, CameraParameters::Example(), measurement);

    /* @brief generate holo::image */
    Image image(640, 480, Image::Encoding::GRAYSCALE);
    image.SetTriggerStamp(holo::Timestamp(first_frame_id));

    /* @brief generate tracker state */
    Tracker::State state;
    state.frame_id  = first_frame_id;
    state.timestamp = image.GetTimestamp();
    state.tracks.push_back(feature_track);

    /* @brief generate a vehiclestate */
    const Pose3  pose1 = Pose3(Rot3(), Point3(1.0, 2.0, 3.0));
    VehicleState vehicle_state1(pose1, Vector3(), ImuBias());

    /**
     * @brief generate a slinding window state constains
     *  1 feature track and 1 vehicle state corresponding to first_frame_id
     */
    Values values;
    values.insert(X(first_frame_id), holo::localization::HoloGtsam::Convert(pose1));
    SlidingWindowState sliding_window_state;
    sliding_window_state.static_tracker_state = state;
    sliding_window_state.compensated_values.insert(X(first_frame_id), holo::localization::HoloGtsam::Convert(pose1));

    /* @brief generate the second vehiclestate */
    const Pose3  pose2 = Pose3(Rot3(), Point3(2.0, 2.0, 3.0));
    VehicleState vehicle_state2(pose2, Vector3(), ImuBias());

    /**
     * @brief add a vehicle state to slinding window state
     *  1 feature track and 2 vehicle state
     */
    const uint64_t second_frame_id = 1u;
    sliding_window_state.compensated_values.insert(X(second_frame_id), holo::localization::HoloGtsam::Convert(pose2));

    return sliding_window_state;
}
}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FailureDetectionParameters, DefaultConstructor)
{
    const FailureDetection::Parameters parameters;

    ASSERT_DOUBLE_EQ(3.3, parameters.x_translation_threshold);
    ASSERT_DOUBLE_EQ(0.44, parameters.y_translation_threshold);
    ASSERT_DOUBLE_EQ(0.55, parameters.yaw_threshold);
    ASSERT_DOUBLE_EQ(33.0, parameters.vehicle_speed_threshold);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FailureDetectionParameters, Example)
{
    const FailureDetection::Parameters parameters = FailureDetection::Parameters::Example();

    ASSERT_DOUBLE_EQ(3.3, parameters.x_translation_threshold);
    ASSERT_DOUBLE_EQ(0.44, parameters.y_translation_threshold);
    ASSERT_DOUBLE_EQ(0.55, parameters.yaw_threshold);
    ASSERT_DOUBLE_EQ(33.0, parameters.vehicle_speed_threshold);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FailureDetection, RunNormal)
{
    const FailureDetection::Parameters parameters = FailureDetection::Parameters::Example();
    const FailureDetection             f(parameters);

    // construct old state
    const holo::Timestamp old_stamp;

    // construct new state
    const SlidingWindowState state = internal::ConstructState();

    // check results
    ASSERT_FALSE(f.Run(state, old_stamp, 1.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FailureDetection, LargeErrorInXY)
{
    const FailureDetection::Parameters parameters = FailureDetection::Parameters::Example();
    const FailureDetection             f(parameters);

    // construct old state
    const holo::Timestamp old_stamp(0.5);

    // construct new state
    SlidingWindowState state = internal::ConstructState();
    {
        const Pose3 pose = Pose3(Rot3(), Point3(35.0, 10.0, 3.0));
        state.compensated_values.update(X(1u), holo::localization::HoloGtsam::Convert(pose));
    }

    // check results
    ASSERT_TRUE(f.Run(state, old_stamp, 1.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FailureDetection, LargeErrorInYaw)
{
    const FailureDetection::Parameters parameters = FailureDetection::Parameters::Example();
    const FailureDetection             f(parameters);

    // construct old state
    const holo::Timestamp old_stamp(0.5);

    // construct new state
    SlidingWindowState state = internal::ConstructState();
    {
        const Pose3 pose = Pose3(Rot3::Rz(3.0), Point3(2.0, 2.0, 3.0));
        state.compensated_values.update(X(1u), holo::localization::HoloGtsam::Convert(pose));
    }

    // check results
    ASSERT_TRUE(f.Run(state, old_stamp, 1.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FailureDetection, LargeErrorInVelocity)
{
    const FailureDetection::Parameters parameters = FailureDetection::Parameters::Example();
    const FailureDetection             f(parameters);

    // construct old state
    const holo::Timestamp old_stamp(0.5);

    // construct new state
    SlidingWindowState state = internal::ConstructState();
    {
        state.compensated_values.insert(V(0u), gtsam::Vector3(0.0, 0.0, 0.0));
        state.compensated_values.insert(V(1u), gtsam::Vector3(100.0, 0.0, 0.0));
    }

    // check results
    ASSERT_TRUE(f.Run(state, old_stamp, 1.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
