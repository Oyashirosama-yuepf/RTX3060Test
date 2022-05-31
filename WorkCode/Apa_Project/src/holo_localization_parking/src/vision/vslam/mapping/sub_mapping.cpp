/*!
 * \brief sub mapping implementation in vslam
 * \author Peikai. Guo guopeikai@holomatic.com
 * \date Jan-11-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/mapping/sub_mapping.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SubMapping::Parameters SubMapping::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // frequency
    const Scalar frequency = node["frequency"].as<Scalar>(10.0);

    // max tracking lost frame
    const uint16_t elm_max_tracking_lost_frame = node["elm_max_tracking_lost_frame"].as<uint16_t>(3);

    // epipolar dist threshold
    const Scalar elm_epipolar_dist_th = node["elm_epipolar_dist_th"].as<Scalar>(4e-3);

    // descriptor dist threshold
    const Scalar elm_descriptor_dist_th = node["elm_descriptor_dist_th"].as<Scalar>(0.8);

    // ratio test threshold
    const Scalar elm_ratio_test_th = node["elm_ratio_test_th"].as<Scalar>(0.75);

    const Triangulator::Parameters triangulator_params =
        Triangulator::Parameters::LoadFromYaml(node["triangulator_params"]);

    return Parameters(frequency, elm_max_tracking_lost_frame, elm_epipolar_dist_th, elm_descriptor_dist_th,
                      elm_ratio_test_th, triangulator_params);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SubMapping::Parameters SubMapping::Parameters::Example()
{
    const Scalar frequency = 10;

    return Parameters(frequency, 3, 4e-3, 0.8, 0.75, Triangulator::Parameters::Example());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SubMapping::SubMapping(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters)
  : parameters_(parameters)
  , camera_parameters_(camera_parameters)
  , is_running_gba_(false)
  , measurement_queue_(1000)
  , triangulator_(parameters_.triangulator_params, camera_parameters)
  , num_of_sub_maps_to_be_optimized_(0)
{
    // start main thread
    sub_mapping_thread_ = std::make_shared<std::thread>(std::bind(&SubMapping::threadFunc, this, std::placeholders::_1),
                                                        parameters_.frequency);
    pthread_setname_np(sub_mapping_thread_->native_handle(), "VslamSubMappingThread");

    // toggle state to ready
    state_ = Base::State::READY;
    Spin();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SubMapping::~SubMapping()
{
    if (sub_mapping_thread_)
    {
        sub_mapping_thread_->join();
    }

    if (optimization_thread_)
    {
        optimization_thread_->join();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SubMapping::AddNewMeasurement(const Measurement& new_measurement)
{
    {
        std::unique_lock<std::mutex> lock(sub_mapping_mutex_);
        LOG(INFO) << "SubMapping --- the size of online sub mapping measurement queue: " << measurement_queue_.size()
                  << "\n";
        measurement_queue_.push_back(new_measurement);
        if (new_measurement.status == SubMapping::MeasurementStatus::END_FRAME)
        {
            num_of_sub_maps_to_be_optimized_++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SubMapping::Stop()
{
    // user requesting stop mapping thread.
    LOG(INFO) << "SubMapping --- Received a STOP request. we will really stop this sub mapping thread after "
                 "processing all measurements and optimizing all data.";

    // wait for the measurements in queue and data in optimization are processed
    while (num_of_sub_maps_to_be_optimized_ || !sub_map_id_to_ba_problem_.empty() || is_running_gba_)
    {
        sleep(1);
    }

    // stop vslam thread
    Base::Stop();
    LOG(INFO) << "SubMapping --- stop sub mapping thread done.";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SubMappingResults SubMapping::GetOptimizedResultsAndClearOldResults()
{
    std::unique_lock<std::mutex> lock(matching_results_mutex_);
    SubMappingResults            optimized_result = sub_mapping_results_;
    sub_mapping_results_.clear();
    return optimized_result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SubMapping::run()
{
    if (!is_running_gba_ && !sub_map_id_to_ba_problem_.empty())
    {
        is_running_gba_ = true;

        // start optimization thread
        if (optimization_thread_)
        {
            optimization_thread_->detach();
        }

        optimization_thread_ =
            std::make_shared<std::thread>(std::bind(&SubMapping::Optimization, this, std::placeholders::_1),
                                          sub_map_id_to_ba_problem_.begin()->second);
        pthread_setname_np(optimization_thread_->native_handle(), "VslamSubMappingOptimizationThread");

        {
            std::unique_lock<std::mutex> lock(optimization_mutex_);
            sub_map_id_to_ba_problem_.erase(sub_map_id_to_ba_problem_.begin()->first);
        }
        num_of_sub_maps_to_be_optimized_--;
    }

    LOG(INFO) << "SubMapping --- EstimationCore is running ...\n";
    TicTocTimer timer;
    timer.Tic();

    if (measurement_queue_.empty())
    {
        return;
    }

    {
        std::unique_lock<std::mutex> lock(sub_mapping_mutex_);
        current_measurement_ = measurement_queue_.front();
        measurement_queue_.pop_front();
    }

    if (current_measurement_.status == MeasurementStatus::END_FRAME)
    {
        {
            std::unique_lock<std::mutex> lock(optimization_mutex_);
            sub_map_id_to_ba_problem_.emplace(current_measurement_.sub_map_id, current_ba_problem_);
        }
        current_ba_problem_ = BundleAdjustmentProblem();
        return;
    }

    // preprocess images for visualization
    if (parameters_.enable_visualizer)
    {
        // convert gray to rgb
        for (size_t i = 0; i < current_measurement_.images.size(); i++)
        {
            cv::Mat rgb_image;
            auto    image = current_measurement_.images.at(i);
            cv::cvtColor(image.GetCvType(), rgb_image, CV_GRAY2RGB);
            const uint16_t width       = image.GetWidth();
            const uint16_t height      = image.GetHeight();
            const uint32_t buffer_size = width * height * 3;
            image.SetData(static_cast<uint8_t*>(rgb_image.data), buffer_size, width, height, Image::Encoding::RGB);
            current_measurement_.images.at(i) = image;
        }
    }

    if ((current_ba_problem_.tracks.empty() && current_measurement_.status != MeasurementStatus::START_FRAME) ||
        (!current_ba_problem_.tracks.empty() && current_measurement_.status == MeasurementStatus::START_FRAME))
    {
        LOG(ERROR) << "SubMapping --- measurement status and tracks size are not inconsistent.\n"
                   << " the tracks size is: " << current_ba_problem_.tracks.size()
                   << ". the frame status is: " << (uint16_t)current_measurement_.status << "\n";
        std::runtime_error("SubMapping --- measurement status and tracks size are not inconsistent.");
    }

    const auto roi_features = GetInterestedFeatures(
        current_measurement_.tracks, current_measurement_.factor_measurements.mpm, current_measurement_.frame_id);
    current_ba_problem_.xvb_values =
        AddNewXVBValues(current_ba_problem_.xvb_values, current_measurement_.factor_measurements.predicted_values,
                        current_measurement_.frame_id);
    FeatureMatching(current_ba_problem_.tracks, roi_features, current_ba_problem_.xvb_values,
                    current_measurement_.frame_id);

    if (current_measurement_.status == MeasurementStatus::START_FRAME)
    {
        LOG(INFO) << "SubMapping --- frame id: " << current_measurement_.frame_id << " is initalizing.\n ";
        auto sub_problem =
            graph_builder_->Initialize(FactorMeasurements(current_measurement_.factor_measurements.pim,
                                                          current_measurement_.factor_measurements.pam,
                                                          current_measurement_.factor_measurements.mpm,
                                                          current_measurement_.factor_measurements.vm,
                                                          current_measurement_.factor_measurements.wim,
                                                          current_measurement_.factor_measurements.predicted_values),
                                       current_measurement_.frame_id);
        current_ba_problem_.pose_graph.add(sub_problem.factor_graph);
    }
    else
    {
        LOG(INFO) << "SubMapping --- frame id: " << current_measurement_.frame_id << " is matching.\n ";
        auto sub_problem =
            graph_builder_->Run(FactorMeasurements(current_measurement_.factor_measurements.pim,
                                                   current_measurement_.factor_measurements.pam,
                                                   current_measurement_.factor_measurements.mpm,
                                                   current_measurement_.factor_measurements.vm,
                                                   current_measurement_.factor_measurements.wim,
                                                   current_measurement_.factor_measurements.predicted_values),
                                current_ba_problem_.tracks, current_measurement_.frame_id);
        current_ba_problem_.pose_graph.add(sub_problem.factor_graph);
    }

    last_processed_frame_id_ = current_measurement_.frame_id;
    LOG(INFO) << "The Whole sub mapping Estimation takes " << 1e3 * timer.Elapsed() << " ms\n";
    LOG(INFO) << "SubMapping --- EstimationCore runs " << current_measurement_.frame_id << " done.\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SubMapping::Optimization(const BundleAdjustmentProblem& ba_problem)
{
    auto        old_tracks       = ba_problem.tracks;
    const auto& old_values       = ba_problem.xvb_values;
    const auto& old_factor_graph = ba_problem.pose_graph;

    // the feature association is finished, next we will do these things below:
    // 1. triangulate the featuretracks
    TriangulateNewTracks(old_tracks, old_values);

    // 2. filtered old tracks
    const auto filtered_old_tracks = SelectTracksWithTriangulationResult(old_tracks);

    // 3. add visual factor graph
    const auto new_factor_graph = AddVisualFactorGraph(old_values, old_factor_graph, filtered_old_tracks);

    // 4. add landmarks' position to values
    auto new_values = AddLandmarksToValues(old_values, filtered_old_tracks);

    // 5. optimize the sub map
    const auto optimized_values = GlobalBundleAdjustment(new_factor_graph, new_values);

    // 6. remove the outliers
    new_values = RemoveOutlierLandmarksFromValue(optimized_values, filtered_old_tracks);

    // 7. creat and initalize the mappoints from retrained featuretracks
    Map new_map = ConvertTracksToMap(filtered_old_tracks, new_values);

    // 8. create frame database
    const auto new_frames_database = CreateFramesDatabase(filtered_old_tracks, new_values);

    // 9. select key frames
    const auto new_key_frames = SelectKeyFrames(new_frames_database, new_values);

    // 10. add new map and new key frames into sub mapping results
    {
        std::unique_lock<std::mutex> lock(matching_results_mutex_);
        sub_mapping_results_.emplace_back(std::make_pair(new_map, new_key_frames));
    }

    is_running_gba_ = false;
    LOG(INFO) << "Sub Mapping --- optimize sub map done.\n"
              << " create new map num: " << new_map.size() << "\n create new key frames num: " << new_key_frames.size()
              << "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraIndexedFeatures SubMapping::GetInterestedFeatures(const std::vector<FeatureTrack>& tracks,
                                                        const MapProjectionMeasurements& mpms,
                                                        const uint64_t                   frame_id) const
{
    CameraIndexedFeatures camera_index_features = ExtractFeaturesFromTracks(tracks, frame_id);
    CameraIndexedFeatures camera_index_interested_features;
    std::set<std::pair<holo::float64_t, holo::float64_t>> image_points;

    for (const auto& mpm : mpms)
    {
        Point2 image_point;
        camera_parameters_->intrinsics.at(mpm.camera_index)->Project(Point3(mpm.bearing), image_point);
        image_points.insert(std::make_pair(image_point.GetX(), image_point.GetY()));
    }

    for (uint16_t i = 0; i < camera_index_features.size(); i++)
    {
        for (const auto& feature : camera_index_features.at(i))
        {
            if (feature.semantic_label == SemanticLabel::STATIC &&
                !image_points.count(std::make_pair(feature.image_point.x, feature.image_point.y)))
            {
                camera_index_interested_features[i].push_back(feature);
            }
        }
    }
    return camera_index_interested_features;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values SubMapping::AddNewXVBValues(const Values& old_values, const Values& new_values,
                                   const uint64_t new_frame_id) const
{
    Values updated_values = old_values;
    if (!new_values.exists(X(new_frame_id)))
    {
        LOG(ERROR) << "SubMapping --- frame id: " << new_frame_id << "is not existed in new values.\n";
        std::runtime_error("SubMapping --- frame id is not existed in new values.");
    }
    updated_values.insert(X(new_frame_id), new_values.at(X(new_frame_id)));
    updated_values.insert(V(new_frame_id), new_values.at(V(new_frame_id)));
    updated_values.insert(B(new_frame_id), new_values.at(B(new_frame_id)));

    return updated_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<FeatureTrack> SubMapping::CreateNewTracks(const CameraIndexedFeatures& features,
                                                      const uint64_t               frame_id) const
{
    std::vector<FeatureTrack> tracks;
    for (const auto& item : features)
    {
        for (const auto& feature : item.second)
        {
            FeatureTrack::CameraIndexedFeature camera_indexed_feature;
            camera_indexed_feature.emplace(item.first, feature);
            tracks.emplace_back(
                FeatureTrack::CreateNewTrack(parameters_.track_params, camera_parameters_,
                                             FeatureTrack::Measurement(frame_id, camera_indexed_feature)));
        }
    }
    return tracks;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SubMapping::FeatureMatching(std::vector<FeatureTrack>& tracks, const CameraIndexedFeatures& features,
                                 const Values& values, const uint64_t new_frame_id) const
{
    if (!tracks.size())
    {
        LOG(INFO) << "SubMapping --- there are no tracks in sliding matching window, Initalizing...\n";
        tracks = CreateNewTracks(features, new_frame_id);
        return;
    }

    // loop all camras
    for (auto camera_index_feature : features)
    {
        // match old tracks with landmarks
        const uint64_t camera_index = camera_index_feature.first;

        // the features in roi area
        Features new_features = camera_index_feature.second;

        // compute camera pose in vslam map frame
        const auto prior_Twc = HoloGtsam::Convert(values.at(X(new_frame_id)).cast<gtsam::Pose3>()) *
                               camera_parameters_->extrinsics.at(camera_index);

        // match filtered old tracks by epipolar line matching method
        MatchOldTracksByEpipolarLineMatching(tracks, values, last_processed_frame_id_, new_features, new_frame_id,
                                             camera_index, prior_Twc);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SubMapping::MatchOldTracksByEpipolarLineMatching(std::vector<FeatureTrack>& old_tracks, const Values& old_values,
                                                      const uint64_t old_frame_id, const Features& new_features,
                                                      const uint64_t new_frame_id, const uint16_t camera_index,
                                                      const Pose3& prior_Twc) const
{
    // filtered_old_tracks contains tracks do not matched success with new_features
    // candidate_old_tracks will be used to match with new features
    std::vector<uint16_t> old_tracks_index;  // old feature's index in window tracks

    // construct features with its observed poses for EpipolarLineMatching
    DescriptorMatcher::FeaturesWithObservedPoses features_with_observed_poses_1, features_with_observed_poses_2;
    features_with_observed_poses_1.reserve(old_tracks.size());
    features_with_observed_poses_2.reserve(new_features.size());

    for (size_t i = 0; i < old_tracks.size(); i++)
    {
        const auto& reference_measurement = old_tracks.at(i).NewestMeasurement();
        const auto& reference_frame_id    = reference_measurement.first;
        const auto& reference_feature     = reference_measurement.second.at(camera_index);

        // check tracking lost times and the max matching times
        if (reference_frame_id + 3 /* parameters_.dm.elm.max_tracking_lost_frame*/ < old_frame_id ||
            old_tracks.at(i).GetState() == FeatureTrack::State::DEAD ||
            new_frame_id - old_tracks.at(i).OldestMeasurement().first > 15)
        {
            continue;
        }

        // get optimized pose from old values
        if (!old_values.exists(X(reference_frame_id)))
        {
            throw std::runtime_error(
                "SubMapping --- required frame id dose not exist in values, something must be wrong.\n");
        }
        const Pose3 reference_pose = HoloGtsam::Convert(old_values.at(X(reference_frame_id)).cast<gtsam::Pose3>()) *
                                     camera_parameters_->extrinsics.at(camera_index);
        features_with_observed_poses_1.emplace_back(reference_feature, reference_pose);
        old_tracks_index.push_back(i);
    }

    for (size_t i = 0; i < new_features.size(); i++)
    {
        features_with_observed_poses_2.emplace_back(new_features.at(i), prior_Twc);
    }

    // call EpipolarLineMatching
    TicTocTimer matching_timer;
    matching_timer.Tic();
    const auto match_pairs = DescriptorMatcher::EpipolarLineMatching(
        features_with_observed_poses_1, features_with_observed_poses_2, 4e-3 /* parameters_.dm.elm.epipolar_dist_th*/,
        0.8 /*parameters_.dm.elm.descriptor_dist_th */, 0.75 /* parameters_.dm.elm.ratio_test_th*/);
    LOG(INFO) << "The feature matching takes " << 1e3 * matching_timer.Elapsed() << " ms\n";

    // update tracks with new features
    UpdateTracksWithNewFeatures(old_tracks, old_tracks_index, new_features, new_frame_id, camera_index, match_pairs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FramesDatabase SubMapping::CreateFramesDatabase(const std::vector<FeatureTrack>& feature_tracks,
                                                const Values&                    xvb_values) const
{
    LOG(INFO) << "SubMapping --- CreateFramesDatabase is running ...\n";
    const auto                          values = xvb_values;
    std::unordered_map<uint64_t, Frame> indexed_frames;

    // loop all tracks
    for (const auto& track : feature_tracks)
    {
        const auto& lm_id = track.GetLandmark()->Id();

        // loop all measurement of this track
        for (const auto& m : track.Measurements())
        {
            // get associated frame id
            const auto& frame_id = m.first;

            // check if this frame exist in values
            if (!values.exists(X(frame_id)))
            {
                LOG(ERROR) << "SubMapping --- frame " << frame_id << " does NOT exist in values.";
                throw std::runtime_error("frame which associated to this track does NOT exist in values\n");
            }

            // check if this is a new frame
            if (!indexed_frames.count(frame_id))
            {
                indexed_frames.emplace(frame_id, Frame(frame_id, camera_parameters_));

                // get vehicle pose of this new frame
                const auto T_wb = HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());

                // get pose and image for all camera.
                for (size_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
                {
                    // add camera pose for this camera
                    const auto& T_bc = camera_parameters_->extrinsics.at(camera_index);
                    indexed_frames[frame_id].multi_camera_data[camera_index].pose       = T_wb * T_bc;
                    indexed_frames[frame_id].multi_camera_data[camera_index].image_name = "";
                }
            }

            // loop all camera
            for (size_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
            {
                if (!m.second.count(camera_index))
                {
                    continue;
                }

                // add features to this frame
                const auto& feature = m.second.at(camera_index);
                indexed_frames[frame_id].multi_camera_data[camera_index].features.push_back(feature);
                indexed_frames[frame_id].multi_camera_data[camera_index].associated_landmarks.push_back(lm_id);
            }
        }
    }

    FramesDatabase database;

    for (const auto& indexed_frame : indexed_frames)
    {
        database.AddFrame(indexed_frame.second);
    }

    LOG(INFO) << "SubMapping --- CreateFramesDatabase done. total frames number: " << indexed_frames.size() << ".";

    return database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values SubMapping::GlobalBundleAdjustment(const FactorGraph& new_factor_graph, const Values& new_values) const
{
    // optimize by gtsam
    LOG(INFO) << "SubMapping --- start to do sub map bundle adjustment ...\n";
    gtsam::LevenbergMarquardtParams params;
    params.setVerbosity(
        gtsam::LevenbergMarquardtParams::verbosityLMTranslator(gtsam::LevenbergMarquardtParams::VerbosityLM::LAMBDA));
    gtsam::LevenbergMarquardtOptimizer optimizer(new_factor_graph, new_values, params);
    const Values                       optimized_value = optimizer.optimize();
    LOG(INFO) << "SubMapping --- sub map bundle adjustment done.\n";
    return optimized_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values SubMapping::RemoveOutlierLandmarksFromValue(const Values&                    values,
                                                   const std::vector<FeatureTrack>& feature_tracks) const
{
    LOG(INFO) << "SubMapping --- start remove outlier landmarks after optimization ...\n";
    Values   new_value   = values;
    uint64_t outiers_num = 0;

    // check inliers
    for (const auto& track : feature_tracks)
    {
        const auto lm_id = track.GetLandmark()->Id();

        for (size_t measurement_index = 0; measurement_index < track.Length(); measurement_index++)
        {
            for (size_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
            {
                // convert error threshold from pixel error to unit3 error
                Scalar threshold = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
                    camera_parameters_->intrinsics.at(camera_index),
                    parameters_.triangulator_params.max_acceptable_reproject_error);
                if (track.ComputeReprojectionError(values, measurement_index, camera_index) < threshold)
                {
                    continue;
                }
                else if (new_value.exists(L(lm_id)))
                {
                    new_value.erase(L(lm_id));
                    outiers_num++;
                }
            }
        }
    }

    LOG(INFO) << "SubMapping --- remove outlier done. total outliers num: " << outiers_num << "\n";
    return new_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SubMapping::TriangulateNewTracks(std::vector<FeatureTrack>& tracks, const Values& values) const
{
    for (auto& track : tracks)
    {
        const FeatureTrack::State track_state = track.GetState();
        if (track_state == FeatureTrack::State::CANDIDATE)
        {
            auto result = triangulator_.Run(track, values);
            if (result)
            {
                track.UpdatingState(FeatureTrack::State::FRESH, HoloGtsam::Convert(*result));
            }
            else
            {
                // transit track state to BAD after triangulation failures
                track.UpdatingState(FeatureTrack::State::BAD_BEFORE_OPTIMIZATION);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Map SubMapping::ConvertTracksToMap(const std::vector<FeatureTrack>& feature_tracks, const Values& values) const
{
    // create map
    Map map;

    for (const auto& track : feature_tracks)
    {
        const auto landmark = track.GetLandmark();

        if (!landmark)
        {
            continue;
        }
        const auto& lm_id = landmark->Id();

        if (!values.exists(L(lm_id)))
        {
            continue;
        }

        // get position
        const Point3 position = HoloGtsam::Convert(values.at(L(lm_id)).cast<gtsam::Point3>());

        // get reference measurement
        // set the oldest measurement as this mappoint's reference measurement
        FeatureTrack::Measurement reference_measurement;

        for (size_t i = 0; i < track.Length(); i++)
        {
            reference_measurement = track.Measurements(i);

            if (values.exists(X(reference_measurement.first)))
            {
                break;
            }
        }

        // check validity of reference_measurement
        if (reference_measurement.second.empty())
        {
            throw std::runtime_error("SubMapping --- CreateMapAndPath, reference_measurement is "
                                     "invalid. something must be wrong.\n");
        }

        const auto& reference_frame_id                  = reference_measurement.first;
        const auto& reference_feature_with_camera_index = reference_measurement.second;

        // create a new mappoint
        /// @todo we need to init new mappoint's remember rate and confidence
        MapPoint mp;

        /// @todo(Feng. Li 2020-02-13) in multi-camera vslam system, if a feature track can be tracked by
        /// different camera. then how can we select the direction for the mappoint? since by now we just track
        /// features at the same camera, here we just select the first one, there shouldn't be much problem. if
        /// we enbale tracking feature at different camera, we should come back to fix this issue.
        const auto& camera_index      = reference_feature_with_camera_index.begin()->first;
        const auto& reference_feature = reference_feature_with_camera_index.begin()->second;
        const Pose3 T_wc              = HoloGtsam::Convert(values.at(X(reference_frame_id)).cast<gtsam::Pose3>()) *
                           camera_parameters_->extrinsics.at(camera_index);
        const auto direction = T_wc.GetRotation().Rotate(reference_feature.normalized_point.ToVector());

        // select the best category of this track
        const auto semantic_label = track.GetLabel();

        // assign the category to mappoint which satisfies the conditions
        // we only add the static and vehicle mappoint to map for localization
        if ((semantic_label == SemanticLabel::STATIC || semantic_label == SemanticLabel::VEHICLE))
        {
            mp.semantic_label = semantic_label;
        }

        mp.reference_pose     = T_wc;
        mp.reference_frame_id = reference_frame_id;
        mp.direction          = direction / direction.GetNorm();
        mp.score              = reference_feature.score;

        mp.position = position;
        /// @todo(Feng. Li) select best descriptor of this track
        mp.descriptor = *(reference_feature.optional_descriptor);
        mp.life_long_states.push_back(MapPointState::MATCHED);
        mp.remember_rate = std::exp(-(1.0 / 19));

        /// @todo compute covariance of this mappoint

        map.push_back(std::make_shared<MapPoint>(mp));
    }

    return map;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<FeatureTrack>
SubMapping::SelectTracksWithTriangulationResult(const std::vector<FeatureTrack>& feature_tracks) const
{
    std::vector<FeatureTrack> new_feature_tracks;
    for (const auto& track : feature_tracks)
    {
        if (track.GetState() == FeatureTrack::State::FRESH)
        {
            new_feature_tracks.push_back(track);
        }
    }
    return new_feature_tracks;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FactorGraph SubMapping::AddVisualFactorGraph(const Values& values, const FactorGraph& old_graph,
                                             const std::vector<FeatureTrack>& feature_tracks) const
{
    (void)values;
    FactorGraph new_graph = old_graph;

    // loop all tracks to add Unit3Factors
    for (const auto& track : feature_tracks)
    {
        const auto& factors = track.Unit3Factors();

        if (factors.empty())
        {
            continue;
        }
        new_graph.add(factors);
    }
    return new_graph;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values SubMapping::AddLandmarksToValues(const Values& old_values, const std::vector<FeatureTrack>& feature_tracks) const
{
    Values new_values = old_values;

    for (const auto& track : feature_tracks)
    {
        const auto& landmark = track.GetLandmark();

        if (!landmark)
        {
            throw std::runtime_error(
                "SubMapping --- AddLandmarksToValues. given tracks without landmark. something must be wrong.\n");
        }
        new_values.insert(L(landmark->Id()), landmark->Point());
    }
    return new_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraIndexedFeatures SubMapping::ExtractFeaturesFromTracks(const std::vector<FeatureTrack>& tracks,
                                                            const uint64_t                   frame_id) const
{
    CameraIndexedFeatures result;

    // traversal all cameras
    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        Features features;

        // traversal all tracks
        for (const auto& track : tracks)
        {
            if (track.NewestMeasurement().first == frame_id && track.NewestMeasurement().second.count(camera_index))
            {
                features.push_back(track.NewestMeasurement().second.at(camera_index));
            }
        }

        result.emplace(camera_index, features);
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SubMapping::UpdateTracksWithNewFeatures(std::vector<FeatureTrack>&   old_tracks,
                                             const std::vector<uint16_t>& old_tracks_index,
                                             const Features& new_features, const uint64_t new_frame_id,
                                             const uint64_t                       camera_index,
                                             const DescriptorMatcher::MatchPairs& match_pairs) const
{
    IndexedFeatures new_tracked_features;
    Features        new_detected_features;

    if (match_pairs.empty())
    {
        // match_pairs is empty, all features will used to create new track
        return;
    }
    else
    {
        // sort original match_pairs.
        // first element in a match_pair is a feature_track's index in the whole sliding window feature tracks, we
        // can use it to retrieve a specific feature track. second element in a match_pair is the new feature's
        // index in input features. we sort the match_pairs in an incremental way according to feature's index, to
        // facilitate classification later.
        DescriptorMatcher::MatchPairs sorted_match_pairs = match_pairs;
        std::sort(sorted_match_pairs.begin(), sorted_match_pairs.end(),
                  [](std::pair<uint16_t, uint16_t> a, std::pair<uint16_t, uint16_t> b) { return a.second < b.second; });

        // mark the first match pair index
        uint16_t match_pair_index      = 0;
        uint16_t old_track_index       = sorted_match_pairs[match_pair_index].first;
        uint16_t matched_feature_index = sorted_match_pairs[match_pair_index].second;

        // loop all input features
        for (uint16_t i = 0; i < new_features.size(); i++)
        {
            // current feature index is equals to matched_feature_index, this means it belongs to an old track, we
            // mark it associated track index.
            if (i == matched_feature_index)
            {
                // belongs to an old track
                new_tracked_features.emplace(old_track_index, new_features.at(i));

                // move match_pair_index to next one if not out of sorted_match_pairs's boundary
                if (match_pair_index < sorted_match_pairs.size() - 1)
                {
                    match_pair_index++;
                    old_track_index       = sorted_match_pairs[match_pair_index].first;
                    matched_feature_index = sorted_match_pairs[match_pair_index].second;
                }
            }
            else
            {
                // belongs to a new track
                new_detected_features.emplace_back(new_features.at(i));
            }
        }

        // update tracks with tracked features, meanwhile mark tracks which can NOT match with new features
        for (size_t i = 0; i < old_tracks_index.size(); i++)
        {
            if (new_tracked_features.count(i))
            {
                auto const& new_feature = new_tracked_features.at(i);
                auto&       old_track   = old_tracks.at(old_tracks_index.at(i));
                old_track.AddNewestMeasurement(new_frame_id, new_feature);
            }
        }

        // create new tracks
        old_tracks.reserve(old_tracks.size() + new_detected_features.size());

        // create new feature track for each new_features which does NOT matching any old_tracks
        for (size_t i = 0; i < new_detected_features.size(); i++)
        {
            FeatureTrack::CameraIndexedFeature camera_indexed_feature;
            camera_indexed_feature.emplace(camera_index, new_detected_features.at(i));
            old_tracks.emplace_back(
                FeatureTrack::CreateNewTrack(parameters_.track_params, camera_parameters_,
                                             FeatureTrack::Measurement(new_frame_id, camera_indexed_feature)));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KeyFramesDatabase SubMapping::SelectKeyFrames(const FramesDatabase& new_frames_database, const Values& xvb_values) const
{
    KeyFramesDatabase new_keyframes_database;
    //  select key frames
    const auto gridding_frame_ids = map_database_manager_->AssignFramesToVoxelGrid(xvb_values, new_frames_database);
    const auto keyframe_ids =
        map_database_manager_->SelectKeyFrames(xvb_values, new_frames_database, gridding_frame_ids);

    for (auto& keyframe_id : keyframe_ids)
    {
        auto           frame             = new_frames_database.GetFrame(keyframe_id);
        const uint64_t camera_number     = frame.multi_camera_data.size();
        auto&          multi_camera_data = frame.multi_camera_data;
        KeyFrame       keyframe(frame.frame_id, HoloGtsam::Convert(xvb_values.at(X(keyframe_id)).cast<gtsam::Pose3>()),
                                camera_number);

        // process all camera data
        for (uint16_t camera_index = 0; camera_index < camera_number; camera_index++)
        {
            // save camera pose
            const auto T_wc = HoloGtsam::Convert(xvb_values.at(X(keyframe_id)).cast<gtsam::Pose3>()) *
                              frame.camera_parameters->extrinsics.at(camera_index);

            // save features and associated landmark ids
            const auto& features             = multi_camera_data.at(camera_index).features;
            const auto& associated_landmarks = multi_camera_data.at(camera_index).associated_landmarks;

            // select features observed landmark
            Features             selected_features;
            std::vector<Point3>  landmarks;
            std::vector<int64_t> ids;

            for (uint16_t i = 0; i < features.size(); i++)
            {
                const auto& lm_id = associated_landmarks.at(i);
                if (lm_id < 0 || !xvb_values.exists(L(lm_id)))
                {
                    continue;
                }

                selected_features.push_back(features.at(i));
                ids.push_back(lm_id);
                const auto point = HoloGtsam::Convert(xvb_values.at(L(lm_id)).cast<gtsam::Point3>());
                landmarks.push_back(point);
            }

            keyframe.multi_camera_data[camera_index].pose                 = T_wc;
            keyframe.multi_camera_data[camera_index].features             = selected_features;
            keyframe.multi_camera_data[camera_index].associated_landmarks = associated_landmarks;
            keyframe.multi_camera_data[camera_index].mappoints            = landmarks;
        }
        new_keyframes_database.emplace(keyframe.frame_id, keyframe);
    }
    return new_keyframes_database;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
