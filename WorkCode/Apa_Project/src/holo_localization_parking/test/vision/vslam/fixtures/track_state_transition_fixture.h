/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file track_state_transition_fixture.h
 * @brief test fixture for track state transition class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-16"
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/track_state_transition.h>

using namespace holo::localization::vision::vslam;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief generate test data for track state transition
 */
class TestFixture : public ::testing::Test
{
public:
    /**
     * @brief constructor
     *
     */
    TestFixture()
      : camera_index_(0)
      , camera_parameters_(CameraParameters::Example())
      , track_state_transition_params_(TrackStateTransition::Parameters::Example())
      , track_state_transition_(track_state_transition_params_, camera_parameters_)
      , feature_track_params_ptr_(new FeatureTrack::Parameters(1.0))
    {
    }

    /**
     * @brief destructor
     *
     */
    virtual ~TestFixture()
    {
    }

    /**
     * @brief generate data
     *
     */
    virtual void SetUp() override
    {
        GenerateGroundTruth();
        GenerateALLToFinished();
        GenerateCandidate();
        GenerateFresh();
        GenerateLive();
        GenerateLiveWithUnit3Factors();
    }

    void GenerateGroundTruth()
    {
        /// @breif generate feature track parameters
        landmark_       = Point3(15.0f, 0.0f, 30.0f);
        start_frame_id_ = 10u;
        end_frame_id_   = 20u;

        /// @brief generate a trajectory along camera z-axis, the consective frame moves 2.0m along z-axis
        for (uint64_t frame_id = start_frame_id_; frame_id <= end_frame_id_; frame_id++)
        {
            Pose3        camera_pose(Rot3(),
                              Point3(0.0f, 0.0f, 2.0f * static_cast<holo::float32_t>(frame_id - start_frame_id_)));
            Pose3        vehicle_pose = camera_pose * camera_parameters_->extrinsics.at(camera_index_).Inverse();
            VehicleState vehicle_state(vehicle_pose, Vector3(), ImuBias());
            values_.insert(X(frame_id), holo::localization::HoloGtsam::Convert(vehicle_pose));

            Point3  pt_c = camera_pose.Inverse() * landmark_;
            Vector3 v_c  = camera_parameters_->intrinsics.at(camera_index_).GetK() * pt_c.ToVector();
            Point2  image_point(v_c(0u) / v_c(2u), v_c(1u) / v_c(2u));
            measurements_[frame_id] = Feature(cv::Point2f(image_point.GetX(), image_point.GetY()), boost::none,
                                              pt_c / pt_c.GetZ(), camera_index_);
        }
    }

    void GenerateALLToFinished()
    {
        const uint64_t lost_frame_id = end_frame_id_ - 1u;
        /// @brief generate candidate to finished
        FeatureTrack candidate_track = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(lost_frame_id,
                           FeatureTrack::CameraIndexedFeature{{camera_index_, measurements_.at(lost_frame_id)}}));

        /// @brief generate fresh to finished
        const uint64_t fresh_first_frame_id = lost_frame_id - track_state_transition_params_.minimum_track_length;
        FeatureTrack   fresh_track          = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(fresh_first_frame_id, FeatureTrack::CameraIndexedFeature{
                                                     {camera_index_, measurements_.at(fresh_first_frame_id)}}));

        for (uint64_t frame_id = fresh_first_frame_id + 1u; frame_id <= lost_frame_id; frame_id++)
        {
            fresh_track = fresh_track.CreateNewTrackByAddingNewestMeasurement(frame_id, measurements_.at(frame_id));
        }

        fresh_track = fresh_track.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH,
                                                                holo::localization::HoloGtsam::Convert(landmark_));
        all_state_to_finished_.factor_graph.add(fresh_track.Unit3Factors());

        /// @brief generate live to finished
        FeatureTrack              live_track = fresh_track.CreateNewTrackByUpdatingState(FeatureTrack::State::LIVE);
        std::vector<FeatureTrack> tracks({candidate_track, fresh_track, live_track});

        // update factor graph and values
        Values values = values_;
        values.insert(L(fresh_track.GetLandmark()->Id()), holo::localization::HoloGtsam::Convert(landmark_));
        all_state_to_finished_.values = values;
        all_state_to_finished_.factor_graph.add(live_track.Unit3Factors());
        all_state_to_finished_.state.frame_id = end_frame_id_;
        all_state_to_finished_.state.tracks   = tracks;
    }

    void GenerateCandidate()
    {
        /// @brief candidate track that will be successfully triangulated
        const uint64_t first_frame_id1  = end_frame_id_ - track_state_transition_params_.minimum_track_length;
        FeatureTrack   candidate_track1 = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(first_frame_id1,
                           FeatureTrack::CameraIndexedFeature{{camera_index_, measurements_.at(first_frame_id1)}}));

        for (uint64_t frame_id = first_frame_id1 + 1u; frame_id <= end_frame_id_; frame_id++)
        {
            candidate_track1 =
                candidate_track1.CreateNewTrackByAddingNewestMeasurement(frame_id, measurements_.at(frame_id));
        }

        /// @brief candidate track that will be transited to BAD_BEFORE_OPTIMIZATION because failed triangulation
        const uint64_t first_frame_id2  = end_frame_id_ - track_state_transition_params_.maximum_candidate_track_length;
        FeatureTrack   candidate_track2 = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(first_frame_id2,
                           FeatureTrack::CameraIndexedFeature{{camera_index_, measurements_.at(first_frame_id2)}}));

        for (uint64_t frame_id = first_frame_id2 + 1u; frame_id <= end_frame_id_; frame_id++)
        {
            candidate_track2 =
                candidate_track2.CreateNewTrackByAddingNewestMeasurement(frame_id, measurements_.at(frame_id));
        }

        std::vector<FeatureTrack> tracks({candidate_track1, candidate_track2});

        candidates_.values         = values_;
        candidates_.state.frame_id = end_frame_id_;
        candidates_.state.tracks   = tracks;
    }

    void GenerateFresh()
    {
        const cv::Point2f noise_2d(0.3f, 0.3f);
        const Point3      noise_normalized(0.01f, 0.01f, 0.01f);

        /// @brief fresh track that will be transited to BAD_BEFORE_OPTIMIZATION / BAD_AFTER_OPTIMIZATION
        const uint64_t first_frame_id1 = end_frame_id_ - track_state_transition_params_.minimum_track_length;
        ///< add some noise to the measurement to make the projection error larger
        Feature      noise_feature(measurements_.at(first_frame_id1).image_point + noise_2d, boost::none,
                              measurements_.at(first_frame_id1).normalized_point + noise_normalized);
        FeatureTrack fresh_track1 = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(first_frame_id1, FeatureTrack::CameraIndexedFeature{{camera_index_, noise_feature}}));

        for (uint64_t frame_id = first_frame_id1 + 1u; frame_id < end_frame_id_; frame_id++)
        {
            noise_feature = Feature(measurements_.at(frame_id).image_point + noise_2d, boost::none,
                                    measurements_.at(frame_id).normalized_point + noise_normalized);
            fresh_track1  = fresh_track1.CreateNewTrackByAddingNewestMeasurement(frame_id, noise_feature);
        }

        ///< make the newest projection very large
        noise_feature = Feature(measurements_.at(end_frame_id_).image_point + 100.0 * noise_2d, boost::none,
                                measurements_.at(end_frame_id_).normalized_point + 100.0 * noise_normalized);
        fresh_track1  = fresh_track1.CreateNewTrackByAddingNewestMeasurement(end_frame_id_, noise_feature);
        fresh_track1  = fresh_track1.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH,
                                                                  holo::localization::HoloGtsam::Convert(landmark_));

        /// @brief fresh track that will be transited to LIVE / FRESH
        const uint64_t first_frame_id2 = end_frame_id_ - track_state_transition_params_.minimum_track_length;
        ///< add some noise to the measurement to make the projection error larger
        noise_feature             = Feature(measurements_.at(first_frame_id2).image_point + noise_2d, boost::none,
                                measurements_.at(first_frame_id2).normalized_point + noise_normalized);
        FeatureTrack fresh_track2 = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(first_frame_id2, FeatureTrack::CameraIndexedFeature{{camera_index_, noise_feature}}));

        for (uint64_t frame_id = first_frame_id2; frame_id <= end_frame_id_; frame_id++)
        {
            noise_feature = Feature(measurements_.at(frame_id).image_point + noise_2d, boost::none,
                                    measurements_.at(frame_id).normalized_point + noise_normalized);
            fresh_track2  = fresh_track2.CreateNewTrackByAddingNewestMeasurement(frame_id, noise_feature);
        }

        fresh_track2 = fresh_track2.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH,
                                                                  holo::localization::HoloGtsam::Convert(landmark_));

        std::vector<FeatureTrack> tracks({fresh_track1, fresh_track2});

        // update values
        Values values = values_;
        values.insert(L(fresh_track1.GetLandmark()->Id()), holo::localization::HoloGtsam::Convert(landmark_));
        values.insert(L(fresh_track2.GetLandmark()->Id()), holo::localization::HoloGtsam::Convert(landmark_));

        // store to fresh data
        fresh_.values = values;
        fresh_.factor_graph.add(fresh_track1.Unit3Factors());
        fresh_.factor_graph.add(fresh_track2.Unit3Factors());
        fresh_.state.frame_id = end_frame_id_;
        fresh_.state.tracks   = tracks;
    }

    void GenerateLive()
    {
        const cv::Point2f noise_2d(0.3f, 0.3f);
        const Point3      noise_normalized(0.01f, 0.01f, 0.01f);

        /// @brief live track that will be transited to BAD_BEFORE_OPTIMIZATION / BAD_AFTER_OPTIMIZATION
        const uint64_t first_frame_id1 = end_frame_id_ - track_state_transition_params_.minimum_track_length;
        ///< add some noise to the measurement to make the projection error larger
        Feature      noise_feature(measurements_.at(first_frame_id1).image_point + noise_2d, boost::none,
                              measurements_.at(first_frame_id1).normalized_point + noise_normalized);
        FeatureTrack live_track1 = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(first_frame_id1, FeatureTrack::CameraIndexedFeature{{camera_index_, noise_feature}}));

        for (uint64_t frame_id = first_frame_id1 + 1u; frame_id < end_frame_id_; frame_id++)
        {
            noise_feature = Feature(measurements_.at(frame_id).image_point + noise_2d, boost::none,
                                    measurements_.at(frame_id).normalized_point + noise_normalized);
            live_track1   = live_track1.CreateNewTrackByAddingNewestMeasurement(frame_id, noise_feature);
        }

        ///< make the newest projection very large
        noise_feature = Feature(measurements_.at(end_frame_id_).image_point + 100.0 * noise_2d, boost::none,
                                measurements_.at(end_frame_id_).normalized_point + 100.0 * noise_normalized);
        live_track1   = live_track1.CreateNewTrackByAddingNewestMeasurement(end_frame_id_, noise_feature);
        live_track1   = live_track1.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH,
                                                                holo::localization::HoloGtsam::Convert(landmark_));
        live_.factor_graph.add(live_track1.Unit3Factors());
        live_track1 = live_track1.CreateNewTrackByUpdatingState(FeatureTrack::State::LIVE);

        /// @brief fresh track that will be transited to LIVE / LIVE
        const uint64_t first_frame_id2 = end_frame_id_ - track_state_transition_params_.minimum_track_length;
        ///< add some noise to the measurement to make the projection error larger
        noise_feature            = Feature(measurements_.at(first_frame_id2).image_point + noise_2d, boost::none,
                                measurements_.at(first_frame_id2).normalized_point + noise_normalized);
        FeatureTrack live_track2 = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(first_frame_id2, FeatureTrack::CameraIndexedFeature{{camera_index_, noise_feature}}));

        for (uint64_t frame_id = first_frame_id2; frame_id <= end_frame_id_; frame_id++)
        {
            noise_feature = Feature(measurements_.at(frame_id).image_point + noise_2d, boost::none,
                                    measurements_.at(frame_id).normalized_point + noise_normalized);
            live_track2   = live_track2.CreateNewTrackByAddingNewestMeasurement(frame_id, noise_feature);
        }

        live_track2 = live_track2.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH,
                                                                holo::localization::HoloGtsam::Convert(landmark_));
        live_.factor_graph.add(live_track2.Unit3Factors());
        live_track2 = live_track2.CreateNewTrackByUpdatingState(FeatureTrack::State::LIVE);

        std::vector<FeatureTrack> tracks({live_track1, live_track2});

        // update values
        Values values = values_;
        values.insert(L(live_track1.GetLandmark()->Id()), holo::localization::HoloGtsam::Convert(landmark_));
        values.insert(L(live_track2.GetLandmark()->Id()), holo::localization::HoloGtsam::Convert(landmark_));

        live_.values         = values;
        live_.state.frame_id = end_frame_id_;
        live_.state.tracks   = tracks;
    }

    void GenerateLiveWithUnit3Factors()
    {
        const cv::Point2f noise_2d(0.3f, 0.3f);
        const Point3      noise_normalized(0.01f, 0.01f, 0.01f);

        /// @brief live track that will be transited to BAD_BEFORE_OPTIMIZATION / BAD_AFTER_OPTIMIZATION
        const uint64_t first_frame_id1 = end_frame_id_ - track_state_transition_params_.minimum_track_length;
        ///< add some noise to the measurement to make the projection error larger
        Feature      noise_feature(measurements_.at(first_frame_id1).image_point + noise_2d, boost::none,
                              measurements_.at(first_frame_id1).normalized_point + noise_normalized);
        FeatureTrack live_track1 = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(first_frame_id1, FeatureTrack::CameraIndexedFeature{{camera_index_, noise_feature}}));

        for (uint64_t frame_id = first_frame_id1 + 1u; frame_id < end_frame_id_; frame_id++)
        {
            noise_feature = Feature(measurements_.at(frame_id).image_point + noise_2d, boost::none,
                                    measurements_.at(frame_id).normalized_point + noise_normalized);
            live_track1   = live_track1.CreateNewTrackByAddingNewestMeasurement(frame_id, noise_feature);
        }

        ///< make the newest projection very large
        noise_feature = Feature(measurements_.at(end_frame_id_).image_point + 100.0 * noise_2d, boost::none,
                                measurements_.at(end_frame_id_).normalized_point + 100.0 * noise_normalized);
        live_track1   = live_track1.CreateNewTrackByAddingNewestMeasurement(end_frame_id_, noise_feature);
        live_track1   = live_track1.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH,
                                                                holo::localization::HoloGtsam::Convert(landmark_));
        live_with_unit3_factors_.factor_graph.add(live_track1.Unit3Factors());
        live_track1 = live_track1.CreateNewTrackByUpdatingState(FeatureTrack::State::LIVE);

        /// @brief fresh track that will be transited to LIVE / LIVE
        const uint64_t first_frame_id2 = end_frame_id_ - track_state_transition_params_.minimum_track_length;
        ///< add some noise to the measurement to make the projection error larger
        noise_feature            = Feature(measurements_.at(first_frame_id2).image_point + noise_2d, boost::none,
                                measurements_.at(first_frame_id2).normalized_point + noise_normalized);
        FeatureTrack live_track2 = FeatureTrack::CreateNewTrack(
            feature_track_params_ptr_, camera_parameters_,
            std::make_pair(first_frame_id2, FeatureTrack::CameraIndexedFeature{{camera_index_, noise_feature}}));

        for (uint64_t frame_id = first_frame_id2; frame_id <= end_frame_id_; frame_id++)
        {
            noise_feature = Feature(measurements_.at(frame_id).image_point + noise_2d, boost::none,
                                    measurements_.at(frame_id).normalized_point + noise_normalized);
            live_track2   = live_track2.CreateNewTrackByAddingNewestMeasurement(frame_id, noise_feature);
        }

        live_track2 = live_track2.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH,
                                                                holo::localization::HoloGtsam::Convert(landmark_));
        live_with_unit3_factors_.factor_graph.add(live_track2.Unit3Factors());
        live_track2 = live_track2.CreateNewTrackByUpdatingState(FeatureTrack::State::LIVE);

        std::vector<FeatureTrack> tracks({live_track1, live_track2});

        // update values
        Values values = values_;
        values.insert(L(live_track1.GetLandmark()->Id()), holo::localization::HoloGtsam::Convert(landmark_));
        values.insert(L(live_track2.GetLandmark()->Id()), holo::localization::HoloGtsam::Convert(landmark_));

        live_with_unit3_factors_.values         = values;
        live_with_unit3_factors_.state.frame_id = end_frame_id_;
        live_with_unit3_factors_.state.tracks   = tracks;
    }

    virtual void TearDown() override
    {
    }

protected:
    /// @brief camera id
    uint16_t camera_index_;

    /// @brief camera parameters
    CameraParameters::Ptr camera_parameters_;

    /**
     * @brief groundtruth
     */
    TrackStateTransition::Parameters track_state_transition_params_;
    TrackStateTransition             track_state_transition_;
    FeatureTrack::Parameters::Ptr    feature_track_params_ptr_;
    uint64_t                         start_frame_id_;
    uint64_t                         end_frame_id_;
    Values                           values_;
    std::map<uint64_t, Feature>      measurements_;
    Point3                           landmark_;

    /**
     * @brief struct contains data for each test case
     */
    struct Data
    {
        Tracker::State state;
        Values         values;
        FactorGraph    factor_graph;
    };

    Data all_state_to_finished_;
    Data candidates_;
    Data fresh_;
    Data live_;
    Data live_with_unit3_factors_;
};
