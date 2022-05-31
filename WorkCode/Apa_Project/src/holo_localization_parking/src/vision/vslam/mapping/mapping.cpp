/*!
 * \brief mapping implementation in vslam
 * \author Yanwei. Du duyanwei@holomatic.com
 * \author Feng. Li lifeng@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/3d/common/io.h>
#include <holo/localization/vision/vslam/mapping/mapping.h>
#include <holo/localization/vision/vslam/semantic/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mapping::Parameters Mapping::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // base parameters
    const std::string base_params_file =
        holo::GetHoloConfigRootDirectory() + "/" + node["vslam_base_params_file"].as<std::string>("");
    if (!boost::filesystem::exists(base_params_file))
    {
        LOG(ERROR) << "Mapping --- failed to load vslam base parameters, invalid base_params_file: \n"
                   << base_params_file << "\n";
        throw std::runtime_error("Mapping --- failed to load vslam base parameters");
    }

    const holo::yaml::Node base_params_node = holo::yaml::LoadFile(base_params_file);
    auto                   base_params      = Base::Parameters::LoadFromYaml(base_params_node["vslam"]);

    base_params.do_imu_preintegration_with_fixed_frequency =
        node["do_imu_preintegration_with_fixed_frequency"].as<bool>();
    LOG(INFO) << "do_imu_preintegration_with_fixed_frequency: "
              << base_params.do_imu_preintegration_with_fixed_frequency;

    if (base_params.do_imu_preintegration_with_fixed_frequency)
    {
        base_params.preintegration_frequency = node["preintegration_frequency"].as<Scalar>(10.0);
        LOG(INFO) << "preintegration_frequency: " << base_params.preintegration_frequency;
    }

    base_params.frequency = node["vslam_frequency"].as<Scalar>(10.0);
    LOG(INFO) << "vslam_frequency: " << base_params.frequency;

    base_params.se_params.lag_size = node["lag_size"].as<Scalar>(10.0);

    base_params.enable_estimation_with_acc = node["enable_estimation_with_acc"].as<bool>(true);

    // initializer parameters
    const holo::yaml::Node        initializer_node   = node["initializer_params"];
    const Initializer::Parameters initializer_params = Initializer::Parameters::LoadFromYaml(initializer_node);

    // visual feature association parameters
    const holo::yaml::Node              fa_node   = node["fa_params"];
    const FeatureAssociator::Parameters fa_params = FeatureAssociator::Parameters::LoadFromYaml(fa_node);

    // map database manager parameters
    const holo::yaml::Node         mdm_node   = node["mdm_params"];
    MapDatabaseManager::Parameters mdm_params = MapDatabaseManager::Parameters::LoadFromYaml(mdm_node);

    // enable data save thread
    const bool_t enable_data_save_thread = node["enable_data_save_thread"].as<bool_t>(false);

    const Scalar minimum_keyframe_travel_distance = node["minimum_keyframe_travel_distance"].as<Scalar>(1.0);
    const Scalar minimum_keyframe_angle           = node["minimum_keyframe_angle"].as<Scalar>(5.0);

    return Parameters(base_params, initializer_params, fa_params, mdm_params, enable_data_save_thread,
                      minimum_keyframe_travel_distance, minimum_keyframe_angle);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mapping::Parameters Mapping::Parameters::Example()
{
    return Parameters(Base::Parameters::Example(), Initializer::Parameters::Example(),
                      FeatureAssociator::Parameters::Example(), MapDatabaseManager::Parameters::Example(), false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mapping::Mapping(const Parameters& parameters)
  : Base(parameters, parameters.fa_params, parameters.initializer_params)
  , parameters_(parameters)
  , estimator_thread_(nullptr)
  , map_database_manager_(parameters_.mdm_params)
  , vehicle_standing_time_(0.0f)
  , online_mapping_length_(0.0f)
  , online_mapping_time_(0.0f)
  , map_data_saving_thread_(nullptr)
  , offline_mapping_data_buffer_(20)
  , optional_last_keyfram_pose_(boost::none)
{
    // fisrt reset map_database_manager
    map_database_manager_.CleanMappingDatabase();

    // start main thread
    estimator_thread_ = std::make_shared<std::thread>(std::bind(&Mapping::threadFunc, this, std::placeholders::_1),
                                                      parameters_.frequency);
    pthread_setname_np(estimator_thread_->native_handle(), "VslamMappingEstimatorThread");

    if (parameters_.enable_data_save_thread)
    {
        // start data saving thread
        map_data_saving_thread_ = std::make_shared<std::thread>(
            std::bind(&Mapping::OfflineMappingDataSavingThreadFunc, this, std::placeholders::_1),
            parameters_.frequency);
        pthread_setname_np(map_data_saving_thread_->native_handle(), "VslamOfflineDataSavingThread");
    }

    // initialize fix lag smoother
    SlidingWindowState::static_smoother =
        gtsam::IncrementalFixedLagSmoother(parameters_.se_params.lag_size, parameters_.se_params.isam2_params);

    // toggle state to ready
    state_ = State::READY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mapping::~Mapping()
{
    if (map_data_saving_thread_)
    {
        map_data_saving_thread_->join();
    }

    if (estimator_thread_)
    {
        estimator_thread_->join();
    }

    SlidingWindowState::static_smoother       = gtsam::IncrementalFixedLagSmoother();
    SlidingWindowState::static_tracker_state  = Tracker::State();
    SlidingWindowState::static_semantic_state = semantic::DataAssociation::State();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::Stop()
{
    // user requesting stop mapping thread.
    LOG(INFO) << "Mapping --- Received a STOP request. we will really stop this mapping thread after processing "
                 "all remaining images. wait a moment ...";

    // process remaining images in measurement buffer
    ProcessRemainingImages();

    // stop vslam thread
    Base::Stop();

    // save all remaining mapping data in current sliding window
    SaveMappingDataInSlidingWindow(sliding_window_state_);

    LOG(INFO) << "Mapping --- stop online mapping thread done.";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::PublishPointClouds(const SlidingWindowState& state) const
{
    // publish local map in sliding window state
    if (output_local_feature_map_callback_)
    {
        std::vector<Point3> map_points;

        for (const auto& key : state.values.keys())
        {
            const gtsam::Symbol symbol(key);

            if (symbol.chr() == 'l')
            {
                map_points.emplace_back(HoloGtsam::Convert(state.values.at<gtsam::Point3>(key)));
            }
        }

        PointCloudXYZIRRgbSt pcd_msg(map_points.size());
        pcd_msg.SetTimestamp(state.GetTimestamp());
        pcd_msg.SetCoordinate(holo::common::Coordinate());
        pcd_msg.SetPose(Pose3::Identity().Cast<holo::float32_t>());
        uint64_t i = 0;

        for (const auto& ptw : map_points)
        {
            Point3f pt = ptw.Cast<::holo::float32_t>();
            pcd_msg[i].SetX(pt.GetX());
            pcd_msg[i].SetY(pt.GetY());
            pcd_msg[i].SetZ(pt.GetZ());
            pcd_msg[i].SetIntensity(0.0);
            i++;
        }
        output_local_feature_map_callback_(pcd_msg);
    }

    // publish whole map accumulated in sliding window state
    if (output_global_feature_map_callback_)
    {
        output_global_feature_map_callback_(ConvertToPointCloud(ConvertToMap(indexed_mappoints_)));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::ParkingSlotAssociation()
{
    const auto& parking_slot_frame =
        measurements_manager_.GetNewestParkingSlotFrame(new_raw_measurements_.newest_timestamp);
    if (!parking_slot_frame)
    {
        LOG(INFO) << "Mapping --- can't get paking slot frame in ParkingSlotAssociation";
        return;
    }

    const auto& cur_pose = HoloGtsam::Convert(sliding_window_state_.values.at(X(new_frame_id_)).cast<gtsam::Pose3>());

    preprocessor_.GetParkingSlotTrackResult(semantic_state_, *parking_slot_frame, cur_pose, new_frame_id_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Mapping::postProcess()
{
    TicTocTimer timer_step;

    // online mapping initialization condition error code
    if (!sliding_window_state_.IsInitialized() && !new_raw_measurements_.chassis_states.empty() &&
        !preprocessor_.IsZeroSpeedState(new_raw_measurements_.chassis_states))
    {
        std::unique_lock<std::mutex>(app_error_status_mutex_);
        app_error_status_->vehicle_is_not_standstill = true;
        LOG(ERROR) << "Mapping --- vehicle speed not zero while online mapping initializing";
    }

    // if sliding window state was not well initialized, do nothing
    if (!sliding_window_state_.IsInitialized())
    {
        LOG(INFO) << "Mapping --- sliding window state was not well initialized.";
        return false;
    }

    // if system should be reset, do nothing
    if (reset_flags_)
    {
        throw std::runtime_error("Mapping --- detect failure case. mapping faild.\n");
    }

    // if estimation core not work well, do nothing
    if (!is_estimation_core_work_well_)
    {
        LOG(WARNING) << "Mapping --- something wrong happened in EstimationCore.\n";
        return false;
    }

    // add vehicle speed abnormal error code and mapping over length error code
    if (!new_raw_measurements_.chassis_states.empty())
    {
        holo::float32_t mean_vehicle_speed(0);
        for (auto chassis_state : new_raw_measurements_.chassis_states)
        {
            mean_vehicle_speed += chassis_state.GetVehicleSpeed();
        }
        mean_vehicle_speed /= new_raw_measurements_.chassis_states.size();

        // mapping over length error code
        online_mapping_length_ +=
            std::fabs(mean_vehicle_speed) * (new_raw_measurements_.chassis_states.back().GetTimestamp().ToSec() -
                                             new_raw_measurements_.chassis_states.front().GetTimestamp().ToSec());
        if (online_mapping_length_ > parameters_.ec_params.online_mapping_over_length_threshold)
        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->online_mapping_over_length = true;
            LOG(ERROR) << "Mapping --- online mapping over length, current distance is: " << online_mapping_length_;
        }
        else if (online_mapping_length_ > parameters_.ec_params.online_mapping_over_length_warning_L2_threshold)
        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->online_mapping_over_length_warning_L2 = true;
            LOG(WARNING) << "Mapping --- online mapping over length warning L2, current distance is: "
                         << online_mapping_length_;
        }
        else if (online_mapping_length_ > parameters_.ec_params.online_mapping_over_length_warning_L1_threshold)
        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->online_mapping_over_length_warning_L1 = true;
            LOG(WARNING) << "Mapping --- online mapping over length warning L1, current distance is: "
                         << online_mapping_length_;
        }

        // online mapping overtime error code
        online_mapping_time_ += (new_raw_measurements_.chassis_states.back().GetTimestamp().ToSec() -
                                 new_raw_measurements_.chassis_states.front().GetTimestamp().ToSec());
        if (online_mapping_time_ > parameters_.ec_params.online_mapping_overtime_threshold)
        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->online_mapping_overtime = true;
            LOG(ERROR) << "Mapping --- online mapping over time, current time is: " << online_mapping_time_;
        }
        else if (online_mapping_time_ > parameters_.ec_params.online_mapping_overtime_warning_threshold)
        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->online_mapping_overtime_warning = true;
            LOG(WARNING) << "Mapping --- online mapping over time warning, current time is: " << online_mapping_time_;
        }

        // vehicle speed abnormal error code
        if (mean_vehicle_speed > 20.0f / 3.6f)
        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->online_mapping_over_speed_20 = true;
            LOG(ERROR) << "Mapping --- online mapping over speed, current speed is: " << mean_vehicle_speed;
        }
        else if (mean_vehicle_speed > 15.0 / 3.6f)
        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->online_mapping_over_speed_15 = true;
            LOG(WARNING) << "Mapping --- online mapping over speed warning, current speed is: " << mean_vehicle_speed;
        }

        // online mapping turning radius limit
        float32_t mean_steering_angle(0.0);
        for (auto chassis_state : new_raw_measurements_.chassis_states)
        {
            mean_steering_angle += chassis_state.GetFrontWheelAngle();
        }
        mean_steering_angle /= new_raw_measurements_.chassis_states.size();

        if (std::fabs(mean_vehicle_speed) > 0.5 &&
            mean_steering_angle * 180.0 / M_PI > parameters_.ec_params.onine_mapping_turning_radius_small_threshold)
        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->onine_mapping_turning_radius_small = true;
            LOG(ERROR) << "Mapping --- online mapping turning radius small, current steering angle is: "
                       << mean_steering_angle * 180.0 / M_PI;
        }

        // online mapping slope limit
        auto pitch = sliding_window_state_.NewestVehicleState().Pose().GetRotation().YPR()(1);
        if (std::fabs(pitch) > parameters_.ec_params.online_mapping_slope_large_threshold)
        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->online_mapping_slope_large = true;
            LOG(ERROR) << "Mapping --- online mapping slope large, current slope is: "
                       << std::fabs(pitch) * 180.0 / M_PI;
        }
    }

    // check if stop overtime during online mapping
    if (CheckIfStoppingOvertime(new_raw_measurements_.chassis_states))
    {
        std::unique_lock<std::mutex>(app_error_status_mutex_);
        app_error_status_->online_mapping_parking_overtime = true;
        LOG(ERROR) << "Mapping --- online mapping stop over time";
    }

    timer_step.Tic();
    ParkingSlotAssociation();

    // update global slot map and get marginalized_parking_slot_tracks;
    UpdateParkingSlots(indexed_parking_slots_, semantic_state_);
    UpdateParkingSlotTracks(semantic_state_);
    LOG(INFO) << "GetAndRemoveMarginalizedParkingSlotTracks takes " << 1e3 * timer_step.Elapsed() << " ms";
    timer_step.Tic();

    // update mappoints with new sliding window state, accumulate value and tracks
    {
        // update indexed mappoints
        UpdateMappoints(indexed_mappoints_, sliding_window_state_);
        LOG(INFO) << "UpdateMappoints takes " << 1e3 * timer_step.Elapsed() << " ms";
        timer_step.Tic();

        // Incrementally save optimized state and sensor measurements for further offline global optimization.
        const auto curr_frame_id = sliding_window_state_.frame_id;
        indexed_corrected_measurement_.emplace(curr_frame_id, new_corrected_measurements_);
        indexed_features_.emplace(curr_frame_id,
                                  RetrieveFeatures(sliding_window_state_.static_tracker_state.tracks, curr_frame_id));
        const auto oldest_frame_id = estimator_.GetOldestFrameId(curr_frame_id);

        // check if sliding window is full
        if (curr_frame_id >= estimator_.Params().lag_size)
        {
            OfflineMappingData mapping_data;
            mapping_data.camera_parameters      = parameters_.camera_params;
            mapping_data.map_name               = parameters_.mdm_params.map_names.front();
            mapping_data.frame_id               = oldest_frame_id;
            mapping_data.estimated_xvb_values   = sliding_window_state_.compensated_values;
            mapping_data.corrected_measurements = indexed_corrected_measurement_.at(oldest_frame_id);

            Pose3 current_pose =
                HoloGtsam::Convert(mapping_data.estimated_xvb_values.at(X(mapping_data.frame_id)).cast<gtsam::Pose3>());

            if (optional_last_keyfram_pose_ == boost::none)
            {
                mapping_data.indexed_features = indexed_features_.at(oldest_frame_id);
                indexed_features_.erase(oldest_frame_id);
                optional_last_keyfram_pose_ = current_pose;
            }
            else
            {
                Scalar t     = current_pose.Dist(*optional_last_keyfram_pose_);
                Scalar angle = current_pose.GetRotation().ComputeAngle(optional_last_keyfram_pose_->GetRotation());
                if (t > parameters_.minimum_keyframe_travel_distance || angle > parameters_.minimum_keyframe_angle)
                {
                    mapping_data.indexed_features = indexed_features_.at(oldest_frame_id);
                    indexed_features_.erase(oldest_frame_id);
                    optional_last_keyfram_pose_ = current_pose;
                }
            }

            // find imu factor
            const auto& factor_graph = sliding_window_state_.static_smoother.getFactors();

            for (size_t i = 0; i < factor_graph.size(); ++i)
            {
                const FactorGraph::Base::sharedFactor& factor = factor_graph.at(i);

                if (const ImuFactor* f = dynamic_cast<const ImuFactor*>(&(*factor)))
                {
                    gtsam::Symbol symbol(f->keys()[0]);

                    if (symbol.index() == oldest_frame_id)
                    {
                        mapping_data.imu_factor = factor;
                        break;
                    }
                }
            }

            // get marginalized good tracks
            GetMarginalizedGoodTracks(sliding_window_state_.static_tracker_state, sliding_window_state_.values,
                                      sliding_window_state_.compensated_values, mapping_data.tracks);
            {
                map_database_manager_.UpdateMappingDatabase(mapping_data);

                if (parameters_.enable_data_save_thread)
                {
                    std::unique_lock<std::mutex> lock(offline_mapping_data_buffer_mutex_);
                    offline_mapping_data_buffer_.push_back(mapping_data);
                }
            }

            indexed_corrected_measurement_.erase(oldest_frame_id);
        }

        LOG(INFO) << "Prepare MappingData For Offline Optimization takes " << 1e3 * timer_step.Elapsed() << " ms";
        timer_step.Tic();
    }

    // update sliding window state by remove bad tracks
    {
        UpdateStateByFilterRejectedTracks(sliding_window_state_);
        LOG(INFO) << "UpdateStateByFilterRejectedTracks takes " << 1e3 * timer_step.Elapsed() << " ms";
        timer_step.Tic();
    }

    // publish estimated odometry and local/global point clouds
    PublishVslamResult(sliding_window_state_, sequence_counter_.vslam_callback_sequence_counter++);
    PublishPointClouds(sliding_window_state_);
    LOG(INFO) << "PublishPointClouds takes " << 1e3 * timer_step.Elapsed() << " ms";
    timer_step.Tic();

    PublishGlobalSlotMap(sliding_window_state_);
    LOG(INFO) << "PublishGlobalSlotMap takes " << 1e3 * timer_step.Elapsed() << " ms";
    timer_step.Tic();

    // visualize result
    if (!new_corrected_measurements_.images.empty())
    {
        Visualizer::VisualizerStates visualizer_state(sliding_window_state_, indexed_mappoints_, indexed_parking_slots_,
                                                      new_corrected_measurements_.images);
        VisualizeVslamResult(visualizer_state);
    }
    LOG(INFO) << "VisualizeVslamResult takes " << 1e3 * timer_step.Elapsed() << " ms";

    // record processed iterations
    Scalar total_time_elapsed = 1e3 * timer_.Elapsed();
    if (total_time_elapsed > 180)
    {
        LOG(ERROR) << "The Whole Estimation takes " << total_time_elapsed << " ms";
        LOG(ERROR) << "Done iteration = " << estimation_core_iteration_counter_ << "\n\n";
    }
    LOG(INFO) << "The Whole Estimation takes " << total_time_elapsed << " ms";
    LOG(INFO) << "Done iteration = " << estimation_core_iteration_counter_++ << "\n\n";
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::UpdateParkingSlotTracks(semantic::DataAssociation::State& semantic_state)
{
    auto track_iter = semantic_state.tracks.begin();
    while (track_iter != semantic_state.tracks.end())
    {
        const auto& frame_id = track_iter->measurements.back().first;

        if (sliding_window_state_.values.exists(X(frame_id)))
        {
            const auto& slot_in_body = track_iter->measurements.back().second.second;
            const auto& wTb = HoloGtsam::Convert(sliding_window_state_.values.at(X(frame_id)).cast<gtsam::Pose3>());
            track_iter->optimized_parking_slot = semantic::Utility::TransformParkingSlot(slot_in_body, wTb);
        }
        track_iter++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::UpdateParkingSlots(IndexedParkingSlots&                    indexed_parking_slots,
                                 const semantic::DataAssociation::State& semantic_state) const
{
    for (uint64_t i = 0; i < semantic_state.tracks.size(); ++i)
    {
        const auto& parking_slot_track = semantic_state.tracks.at(i);

        indexed_parking_slots[parking_slot_track.id] = parking_slot_track.optimized_parking_slot;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::PublishGlobalSlotMap(const SlidingWindowState& new_state) const
{
    // publish parking slot frame
    if (output_global_parking_slot_frame_callback_)
    {
        // @todo Coordinate: it should be in vslam navigation frame (a global frame)
        ParkingSlotFrameType frame(new_state.GetTimestamp(), common::Coordinate::UNKNOWN);

        // @todo the implementation in this block must be improved
        for (const auto& track : new_state.static_semantic_state.tracks)
        {
            auto out_w = track.GetOptimizedParkingSlot(new_state.values);
            if (out_w)
            {
                auto bTw = HoloGtsam::Convert(new_state.values.at<gtsam::Pose3>(X(track.frame_id)).inverse());
                // @todo the real output is the body frame, not the world frame (chengchangxi@holomatic.com)
                auto out_b = ConvertFromGlobalToBody(bTw, *out_w);
                frame.emplace_back(out_b);
            }
        }
        output_global_parking_slot_frame_callback_(frame);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotType Mapping::ConvertFromGlobalToBody(const Pose3& bTw, const ParkingSlotType& in) const
{
    ParkingSlotType out(in);

    // front vertices
    out.vertices[0u] = bTw.TransformFrom(in.vertices[0u]);
    out.vertices[1u] = bTw.TransformFrom(in.vertices[1u]);
    // rear vertices
    if (in.is_rear_vertex_available)
    {
        out.vertices[2u] = bTw.TransformFrom(in.vertices[2u]);
        out.vertices[3u] = bTw.TransformFrom(in.vertices[3u]);
    }

    // center vertex
    if (in.is_center_vertex_available)
    {
        out.center_vertex = bTw.TransformFrom(in.center_vertex);
    }

    // stopper vertices
    if (in.is_stopper_available)
    {
        out.stopper_vertices[0u] = bTw.TransformFrom(in.stopper_vertices[0u]);
        out.stopper_vertices[1u] = bTw.TransformFrom(in.stopper_vertices[1u]);
    }

    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::UpdateMappoints(IndexedMappoints& indexed_map, const SlidingWindowState& new_state) const
{
    const auto& values = new_state.values;

    for (uint64_t i = 0; i < new_state.static_tracker_state.tracks.size(); i++)
    {
        const auto& track    = new_state.static_tracker_state.tracks.at(i);
        const auto  landmark = track.GetLandmark();

        if (!landmark)
        {
            continue;
        }

        const auto& lm_id = landmark->Id();

        const auto& track_state = track.GetState();

        if (track_state == FeatureTrack::State::LIVE || track_state == FeatureTrack::State::FRESH ||
            track_state == FeatureTrack::State::FINISHED)
        {
            if (!values.exists(L(lm_id)))
            {
                continue;
            }
            // get position
            const Point3 position = HoloGtsam::Convert(values.at(L(lm_id)).cast<gtsam::Point3>());

            if (indexed_map.count(lm_id))
            {
                // belongs to an old mappoint, update its position
                indexed_map[lm_id].position = position;

                // select the best category of this track
                const auto samentic_label = track.GetLabel();

                if (samentic_label != SemanticLabel::UNKNOWN)
                {
                    indexed_map[lm_id].semantic_label = SemanticLabel(samentic_label);
                }
                else
                {
                    indexed_map[lm_id].semantic_label = SemanticLabel(6);
                }
            }
            else
            {
                // get reference measurement
                // set the oldest measurement which still exist in sliding window as this mappoint's reference
                // measurement
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
                    throw std::runtime_error("Mapping --- UpdateMappoints, reference_measurement is "
                                             "invalid. something must be wrong.\n");
                }

                const auto& reference_frame_id                  = reference_measurement.first;
                const auto& reference_feature_with_camera_index = reference_measurement.second;

                // create a new mappoint
                MapPoint mp;

                /// @todo(Feng. Li 2020-02-13) in multi-camera vslam system, if a feature track can be tracked by
                /// different camera. then how can we select the direction for the mappoint? since by now we just track
                /// features at the same camera, here we just select the first one, there shouldn't be much problem. if
                /// we enbale tracking feature at different camera, we should come back to fix this issue.
                const auto& camera_index      = reference_feature_with_camera_index.begin()->first;
                const auto& reference_feature = reference_feature_with_camera_index.begin()->second;
                const Pose3 T_wc = HoloGtsam::Convert(values.at(X(reference_frame_id)).cast<gtsam::Pose3>()) *
                                   parameters_.camera_params->extrinsics.at(camera_index);
                const auto direction = T_wc.GetRotation().Rotate(reference_feature.normalized_point.ToVector());
                mp.reference_pose    = T_wc;
                mp.direction         = direction / direction.GetNorm();

                mp.position = position;
                // @todo(Feng. Li) select best descriptor of this track
                mp.descriptor     = *(reference_feature.optional_descriptor);
                mp.remember_rate  = std::exp(-(1.0 / 19));
                mp.semantic_label = reference_feature.semantic_label;

                // @todo compute covariance of this mappoint

                indexed_map[lm_id] = mp;
            }
        }
        else if ((track_state == FeatureTrack::State::BAD_AFTER_OPTIMIZATION ||
                  track_state == FeatureTrack::State::BAD_BEFORE_OPTIMIZATION) &&
                 indexed_map.count(lm_id))
        {
            // remove this bad mappoint
            indexed_map.erase(lm_id);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::ProcessRemainingImages() const
{
    // wait here until the image queue get empty.
    while (true)
    {
        if (measurements_manager_.GetImageNum() == 0)
        {
            LOG(INFO) << "Mapping::ProcessRemainingImages --- Progress: 100 %.\n";
            break;
        }

        if (!is_estimation_core_work_well_)
        {
            break;
        }

        static uint64_t total_buffer_size = measurements_manager_.GetImageNum();
        Scalar progress = 100.0 * (total_buffer_size - measurements_manager_.GetImageNum()) / total_buffer_size;
        LOG(INFO) << "Mapping::ProcessRemainingImages --- Progress: " << progress << " %.\n";

        sleep(1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapPtr Mapping::ConvertToMap(const IndexedMappoints& indexed_mappoints) const
{
    Map map;
    map.reserve(indexed_mappoints.size());

    for (const auto& indexed_mappoint : indexed_mappoints)
    {
        map.emplace_back(std::make_shared<MapPoint>(indexed_mappoint.second));
    }

    return std::make_shared<Map>(map);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraIndexedFeatures Mapping::RetrieveFeatures(const std::vector<FeatureTrack>& tracks, const uint64_t frame_id) const
{
    CameraIndexedFeatures result;

    // traversal all cameras
    for (uint16_t camera_index = 0; camera_index < parameters_.camera_params->camera_number; camera_index++)
    {
        Features features;
        features.reserve(500);

        // traversal all tracks
        for (const auto& track : tracks)
        {
            if (track.NewestMeasurement().first == frame_id && track.NewestMeasurement().second.count(camera_index))
            {
                features.emplace_back(track.NewestMeasurement().second.at(camera_index));
            }
        }

        result.emplace(camera_index, features);
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::GetMarginalizedGoodTracks(Tracker::State& state, const Values& optimized_values,
                                        const Values& compensated_value, std::vector<FeatureTrack>& tracks) const
{
    tracks.reserve(500);
    const auto oldest_frame_id = estimator_.GetOldestFrameId(state.frame_id);

    for (auto& track : state.tracks)
    {
        bool is_marginalied_tracks = false;

        if (parameters_.builder_params.enable_unit3_factor)
        {
            is_marginalied_tracks = track.NewestMeasurement().first <= oldest_frame_id;
        }
        else
        {
            is_marginalied_tracks = track.NewestMeasurement().first != state.frame_id;
        }

        if (is_marginalied_tracks)
        {
            // this track will be marginalized. if it is a "good" track, we retain it for global optimization later.

            // 1. candidate track will be further optimized in later
            if (track.GetState() == FeatureTrack::State::CANDIDATE &&
                track.Length() > parameters_.se_params.tst_params.minimum_track_length)
            {
                // create a pseudo landmark for this candidate track while do NOT change its state. then this track will
                // be triangulated again in offline optmization.
                track.UpdatingState(FeatureTrack::State::CANDIDATE, gtsam::Point3());
                tracks.emplace_back(track);
                continue;
            }

            // 2. already optimized in online progress
            const auto& landmark = track.GetLandmark();

            if (!landmark || track.GetState() != FeatureTrack::State::FINISHED ||
                !indexed_mappoints_.count(landmark->Id()))
            {
                // no landmark means triangulation failed;
                // has landmark but state is not FINISHED means triangulation success but optimization failed.
                // anyway, this is a bad tracks.
                continue;
            }

            // good one, we update its landmark position and state for offline global optimization.
            const auto position = HoloGtsam::Convert(indexed_mappoints_.at(landmark->Id()).position);

            // shift landmark position by the pose change in oldest frame
            const auto& m            = track.NewestMeasurement();
            const auto  camera_index = m.second.begin()->first;
            const auto  T_bc         = HoloGtsam::Convert(parameters_.camera_params->extrinsics.at(camera_index));
            const auto  old_Twc      = optimized_values.at(X(oldest_frame_id)).cast<gtsam::Pose3>() * T_bc;
            const auto  new_Twc      = compensated_value.at(X(oldest_frame_id)).cast<gtsam::Pose3>() * T_bc;
            const auto  new_position = new_Twc * (old_Twc.inverse() * position);

            track.UpdatingState(FeatureTrack::State::FINISHED, new_position);
            tracks.emplace_back(track);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<semantic::ParkingSlotTrack>
Mapping::GetMarginalizedGoodParkingSlotTracks(const semantic::DataAssociation::State& state,
                                              const Values& optimized_values, const Values& compensated_value) const
{
    std::vector<semantic::ParkingSlotTrack> result;
    (void)state;
    (void)optimized_values;
    (void)compensated_value;

    result.reserve(state.tracks.size());
    const auto oldest_frame_id = estimator_.GetOldestFrameId(state.current_frame_id);

    for (const auto& track : state.tracks)
    {
        if (track.measurements.front().first <= oldest_frame_id)
        {
            result.push_back(track);
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::SaveMappingDataInSlidingWindow(const SlidingWindowState& sliding_window_state)
{
    const auto curr_frame_id   = sliding_window_state.frame_id;
    const auto oldest_frame_id = estimator_.GetOldestFrameId(curr_frame_id);

    for (uint64_t frame_id = oldest_frame_id + 1; frame_id <= curr_frame_id; frame_id++)
    {
        OfflineMappingData mapping_data;
        mapping_data.camera_parameters      = parameters_.camera_params;
        mapping_data.map_name               = parameters_.mdm_params.map_names.front();
        mapping_data.frame_id               = frame_id;
        mapping_data.estimated_xvb_values   = sliding_window_state_.compensated_values;
        mapping_data.corrected_measurements = indexed_corrected_measurement_.at(frame_id);
        mapping_data.indexed_features       = indexed_features_.at(frame_id);
        mapping_data.tracks.reserve(sliding_window_state.static_tracker_state.tracks.size());
        mapping_data.parking_slot_tracks.reserve(sliding_window_state.static_semantic_state.tracks.size());

        // get good tracks in current sliding window
        // trversal all tracks
        for (const auto& track : sliding_window_state.static_tracker_state.tracks)
        {
            // get tracks which were tracking lost at this frame
            if (track.NewestMeasurement().first != frame_id)
            {
                continue;
            }

            // if it is a "good" track, we retain it for global optimization later.
            const auto& landmark = track.GetLandmark();

            if (!landmark || !indexed_mappoints_.count(landmark->Id()))
            {
                continue;
            }

            // good one, we update its landmark position and state for offline global optimization.
            const auto position = HoloGtsam::Convert(indexed_mappoints_.at(landmark->Id()).position);

            // shift landmark position by the pose change in oldest frame
            const auto& m            = track.NewestMeasurement();
            const auto  camera_index = m.second.begin()->first;
            const auto  T_bc         = HoloGtsam::Convert(parameters_.camera_params->extrinsics.at(camera_index));
            const auto  old_Twc      = sliding_window_state.values.at(X(oldest_frame_id)).cast<gtsam::Pose3>() * T_bc;
            const auto  new_Twc =
                sliding_window_state.compensated_values.at(X(oldest_frame_id)).cast<gtsam::Pose3>() * T_bc;
            const auto new_position = new_Twc * (old_Twc.inverse() * position);

            mapping_data.tracks.emplace_back(
                track.CreateNewTrackByUpdatingState(FeatureTrack::State::FINISHED, new_position));

            // find imu factor
            const auto& factor_graph = sliding_window_state_.static_smoother.getFactors();

            for (size_t i = 0; i < factor_graph.size(); ++i)
            {
                const FactorGraph::Base::sharedFactor& factor = factor_graph.at(i);

                if (const ImuFactor* f = dynamic_cast<const ImuFactor*>(&(*factor)))
                {
                    gtsam::Symbol symbol(f->keys()[0]);
                    if (symbol.index() == oldest_frame_id)
                    {
                        mapping_data.imu_factor = factor;
                        break;
                    }
                }
            }
        }

        // trversal all tracks in current sliding window
        for (const auto& track : semantic_state_.tracks)
        {
            mapping_data.parking_slot_tracks.push_back(track);
        }
        semantic_state_.tracks.clear();

        std::unique_lock<std::mutex> lock(offline_mapping_data_buffer_mutex_);
        map_database_manager_.UpdateMappingDatabase(mapping_data);
        if (parameters_.enable_data_save_thread)
        {
            offline_mapping_data_buffer_.push_back(mapping_data);
            map_database_manager_.SaveMappingDataForOfflineOptimization(mapping_data);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Mapping::CheckIfStoppingOvertime(const std::vector<ChassisState>& chassis_states)
{
    if (!chassis_states.empty())
    {
        if (preprocessor_.IsZeroSpeedState(chassis_states))
        {
            vehicle_standing_time_ +=
                chassis_states.back().GetTimestamp().ToSec() - chassis_states.front().GetTimestamp().ToSec();
        }
        else
        {
            vehicle_standing_time_ = 0.0f;
        }
    }

    if (vehicle_standing_time_ > parameters_.ec_params.online_mapping_parking_overtime_threshold)
    {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mapping::OfflineMappingDataSavingThreadFunc(const Scalar frequency)
{
    // timer to control frequency of this function
    Timer timer(frequency);

    while (GetStatus() != Status::STOP)
    {
        timer.Start();

        // do mapping saving when mapping thread works
        if (GetStatus() == Status::SPIN && checkState())
        {
            // get newest offline mapping database
            if (offline_mapping_data_buffer_.empty())
            {
                LOG(ERROR) << "Mapping --- OfflineMappingDataSavingThreadFunc database buffer is empty.";
                timer.Stop();
                continue;
            }

            OfflineMappingData database;
            {
                std::unique_lock<std::mutex> lock(offline_mapping_data_buffer_mutex_);
                database = offline_mapping_data_buffer_.front();
                offline_mapping_data_buffer_.pop_front();
            }

            // save database here
            TicTocTimer timer_step;
            timer_step.Tic();
            map_database_manager_.SaveMappingDataForOfflineOptimization(database);
            LOG(INFO) << "SaveMappingDataForOfflineOptimization in thread func takes " << 1e3 * timer_step.Elapsed()
                      << " ms";
        }

        timer.Stop();
    }
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
