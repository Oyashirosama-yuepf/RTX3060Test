/*!
 * \brief visual localization implementation in vslam
 * \author Yanwei. Du duyanwei@holomatic.com
 * \author Feng. Li lifeng@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtsam/nonlinear/ISAM2.h>
#include <holo/localization/vision/vslam/localization/localization.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Localization::Parameters Localization::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // base parameters
    const std::string base_params_file =
        holo::GetHoloConfigRootDirectory() + "/" + node["vslam_base_params_file"].as<std::string>("");
    if (!boost::filesystem::exists(base_params_file))
    {
        LOG(ERROR) << "Localization --- failed to load vslam base parameters, invalid base_params_file: \n"
                   << base_params_file << "\n";
        throw std::runtime_error("Localization --- failed to load vslam base parameters");
    }

    const holo::yaml::Node base_params_node = holo::yaml::LoadFile(base_params_file);
    auto                   base_params      = Base::Parameters::LoadFromYaml(base_params_node["vslam"]);
    base_params.do_imu_preintegration_with_fixed_frequency =
        node["do_imu_preintegration_with_fixed_frequency"].as<bool>(false);
    LOG(INFO) << "do_imu_preintegration_with_fixed_frequency: "
              << base_params.do_imu_preintegration_with_fixed_frequency;

    if (base_params.do_imu_preintegration_with_fixed_frequency)
    {
        base_params.preintegration_frequency = node["preintegration_frequency"].as<Scalar>(10.0);
        LOG(INFO) << "preintegration_frequency: " << base_params.preintegration_frequency;
    }

    base_params.frequency = node["vslam_frequency"].as<Scalar>(1.0);
    LOG(INFO) << "vslam_frequency: " << base_params.frequency;

    base_params.se_params.lag_size = node["lag_size"].as<Scalar>(10.0);

    base_params.enable_estimation_with_acc = node["enable_estimation_with_acc"].as<bool>(false);

    // minimum accepted frequency
    const Scalar minimum_acceptable_frequency = node["minimum_acceptable_frequency"].as<Scalar>(10.0);

    // imu prediction frequency
    const Scalar imu_prediction_frequency = node["imu_prediction_frequency"].as<Scalar>(100.0);

    // initializer parameters
    const holo::yaml::Node        initializer_node   = node["initializer_params"];
    const Initializer::Parameters initializer_params = Initializer::Parameters::LoadFromYaml(initializer_node);

    // data association parameters
    const holo::yaml::Node              fa_node   = node["fa_params"];
    const FeatureAssociator::Parameters fa_params = FeatureAssociator::Parameters::LoadFromYaml(fa_node);

    // relocalization parameters
    const holo::yaml::Node reloc_node   = node["relocalization_params"].as<holo::yaml::Node>(holo::yaml::Node());
    const auto             reloc_params = Relocalization::Parameters::LoadFromYaml(reloc_node);

    // sub mapping parameters
    const bool             enable_sub_mapping = node["enable_sub_mapping"].as<bool>(false);
    SubMapping::Parameters sub_mapping_params = SubMapping::Parameters::Example();

    if (enable_sub_mapping)
    {
        const holo::yaml::Node sub_mapping_node = node["sub_mapping_params"].as<holo::yaml::Node>(holo::yaml::Node());
        sub_mapping_params                      = SubMapping::Parameters::LoadFromYaml(sub_mapping_node);
    }

    // map database manager parameters
    const holo::yaml::Node mdm_node   = node["mdm_params"].as<holo::yaml::Node>(holo::yaml::Node());
    const auto             mdm_params = MapDatabaseManager::Parameters::LoadFromYaml(mdm_node);

    // flag which indicate if predicte nav state by pure imu integration
    const bool predict_navstate_by_pure_imu_integration =
        node["predict_navstate_by_pure_imu_integration"].as<bool>(false);

    base_params.max_inlier_global_correspondence_num = node["max_inlier_global_correspondence_num"].as<uint32_t>(300);

    base_params.minimum_inlier_correspondence_num = node["minimum_inlier_correspondence_num"].as<uint32_t>(20);

    return Parameters(base_params, minimum_acceptable_frequency, imu_prediction_frequency, initializer_params,
                      fa_params, reloc_params, sub_mapping_params, mdm_params, enable_sub_mapping,
                      predict_navstate_by_pure_imu_integration);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Localization::Parameters Localization::Parameters::Example()
{
    const Scalar minimum_acceptable_frequency = 10.0;
    const Scalar imu_prediction_frequency     = 100;

    return Parameters(Base::Parameters::Example(), minimum_acceptable_frequency, imu_prediction_frequency,
                      Initializer::Parameters::Example(), FeatureAssociator::Parameters::Example(),
                      Relocalization::Parameters::Example(), SubMapping::Parameters::Example(),
                      MapDatabaseManager::Parameters::Example(), false, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Localization::Localization(const Parameters& parameters)
  : Base(parameters, parameters.fa_params, parameters.initializer_params)
  , parameters_(parameters)
  , estimator_thread_(nullptr)
  , imu_prediction_thread_(nullptr)
  , is_imu_prediction_running_(false)
  , prebuilt_map_(nullptr)
  , is_vslam_updated_(false)
  , is_vslam_initialized_(false)
  , sub_map_id_(0)
  , relocalization_(std::make_shared<Relocalization>(parameters_.reloc_params, parameters_.camera_params))
  , map_database_manager_(std::make_shared<MapDatabaseManager>(parameters_.mdm_params))
  , lacking_feature_points_distance(0.0f)
{
    if (parameters.enable_sub_mapping)
    {
        sub_mapping_ = std::make_shared<SubMapping>(parameters_.sub_mapping_params, parameters_.camera_params);

        // set graph builder to sub mapping
        sub_mapping_->SetGraphBuilderPtr(graph_builder_);

        // set map database manager to sub mapping
        sub_mapping_->SetMapDatabaseManagerPtr(map_database_manager_);
    }
    // init descriptor matching kernel
    DescriptorMatcher::InitKernel();

    // load prebuilt path for HPP
    learned_path_ = map_database_manager_->GetLearnedPath();

    // load prebuilt map
    prebuilt_map_ = map_database_manager_->GetPrebuiltMap();

    prebuilt_slot_map_ = map_database_manager_->GetPrebuiltSlotMap();

    // set map to measurement manager
    measurements_manager_.SetMap(prebuilt_map_, prebuilt_slot_map_);

    // convert prebuilt map to pcd
    visualization_map_ = ConvertToPointCloud(prebuilt_map_);

    // start main thread
    estimator_thread_ = std::make_shared<std::thread>(std::bind(&Localization::threadFunc, this, std::placeholders::_1),
                                                      parameters_.frequency);
    pthread_setname_np(estimator_thread_->native_handle(), "VslamLocalizationEstiatorThread");

    // start imu prediction thread
    imu_prediction_thread_ =
        std::make_shared<std::thread>(std::bind(&Localization::PredictionThreadFunc, this, std::placeholders::_1),
                                      parameters_.imu_prediction_frequency);
    pthread_setname_np(imu_prediction_thread_->native_handle(), "VslamImuPredictionThread");

    // set relocalization to initializer
    initializer_.SetRelocalizationPtr(relocalization_);
    relocalization_->SetKeyFramesDatabase(map_database_manager_->GetKeyframes());
    relocalization_->SetKeyFramesDbowVector(map_database_manager_->GetKeyframesBowVector());
    relocalization_->Stop();

    // initialize fix lag smoother
    SlidingWindowState::static_smoother =
        gtsam::IncrementalFixedLagSmoother(parameters_.se_params.lag_size, parameters_.se_params.isam2_params);

    // toggle state to ready
    state_ = State::READY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Localization::~Localization()
{
    if (relocalization_)
    {
        relocalization_ = nullptr;
        LOG(INFO) << "Localization --- Visual Based Relocalization Finished!!!";
    }

    if (estimator_thread_)
    {
        estimator_thread_->join();
    }

    if (sub_mapping_)
    {
        sub_mapping_ = nullptr;
        LOG(INFO) << "Localization --- Visual Based Sub Mapping Finished!!!";
    }

    SlidingWindowState::static_smoother       = gtsam::IncrementalFixedLagSmoother();
    SlidingWindowState::static_tracker_state  = Tracker::State();
    SlidingWindowState::static_semantic_state = semantic::DataAssociation::State();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Localization::Stop()
{
    // update prebuilt map state
    RemoveMappointsWithRememberRate(prebuilt_map_);

    // stop vslam thread
    Base::Stop();

    // stop imu prediction thread
    if (imu_prediction_thread_)
    {
        imu_prediction_thread_->join();
        LOG(INFO) << "Localization --- Imu Prediction Finished!!!";
    }

    if (relocalization_)
    {
        relocalization_->Stop();
    }

    if (sub_mapping_)
    {
        LOG(INFO) << "Come into sub mapping stop!!!";
        sub_mapping_->Stop();
    }

    if (parameters_.enable_sub_mapping)
    {
        // wait to  get new maps and frames databases which are not optimized completely
        const auto new_maps_and_framesdatebases = sub_mapping_->GetOptimizedResultsAndClearOldResults();
        new_maps_framesdatabases_.insert(new_maps_framesdatabases_.end(), new_maps_and_framesdatebases.begin(),
                                         new_maps_and_framesdatebases.end());

        // save updated map and key frames
        map_database_manager_->UpdatePrebiltMapAndKeyFramesDatabase(new_maps_framesdatabases_);
        map_database_manager_->SaveMapAndKeyFrames();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Localization::SetVisualizer(std::shared_ptr<vslam::Visualizer> visualizer)
{
    if (visualizer == nullptr)
    {
        return;
    }

    Base::SetVisualizer(visualizer);

    if (prebuilt_slot_map_ != nullptr)
    {
        visualizer_->SetPrebuiltSlotMap(prebuilt_slot_map_);
    }

    if (prebuilt_map_ != nullptr)
    {
        visualizer_->SetPrebuiltMap(prebuilt_map_);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Localization::postProcess()
{
    // publish prebuilt map
    PublishPrebuiltMap();

    // if estimation core not work well, do nothing
    if (!is_estimation_core_work_well_)
    {
        LOG(WARNING) << "Localization --- something wrong happened in EstimationCore.\n";
        return false;
    }

    // if sliding window state was not well initialized, do nothing
    if (!sliding_window_state_.IsInitialized())
    {
        LOG(INFO) << "Localization --- sliding window state was not well initialized.";
        return false;
    }
    else if (reset_flags_)
    {
        // if system should be reset, do nothing
        return false;
    }
    else
    {
        // inform imu prediction thread that vslam has updated.
        std::unique_lock<std::mutex> lock(update_mutex_);
        is_vslam_initialized_         = true;
        is_vslam_updated_             = true;
        newest_updated_vehicle_state_ = sliding_window_state_.NewestVehicleState();
        newest_updated_timestamp_     = sliding_window_state_.GetTimestamp();
    }

    TicTocTimer timer_step;
    timer_step.Tic();
    // update sliding window state by remove bad tracks
    UpdateStateByFilterRejectedTracks(sliding_window_state_);
    LOG(INFO) << "UpdateStateByFilterRejectedTracks takes " << 1e3 * timer_step.Elapsed() << " ms";

    // publish estimated odometry
    timer_step.Tic();
    PublishVslamResult(sliding_window_state_, sequence_counter_.vslam_callback_sequence_counter++);
    LOG(INFO) << "PublishVslamResult takes " << 1e3 * timer_step.Elapsed() << " ms";

    timer_step.Tic();
    sliding_window_state_.inlier_global_correspondence_num = PublishPointClouds(sliding_window_state_);
    LOG(INFO) << "Publish global correspondence takes " << 1e3 * timer_step.Elapsed() << " ms";
    LOG(INFO) << "Inlier global correspondence number: " << sliding_window_state_.inlier_global_correspondence_num;

    /// add localization matched point features few error code
    if (sliding_window_state_.inlier_global_correspondence_num > parameters_.ec_params.feature_point_num_few_threshold)
    {
        lacking_feature_points_distance = 0.0f;
    }
    else
    {
        lacking_feature_points_distance += sliding_window_state_.NewestRelativePose().translation().norm();
    }
    if (lacking_feature_points_distance >= parameters_.ec_params.feature_few_tolerance)
    {
        std::unique_lock<std::mutex>(app_error_status_mutex_);
        app_error_status_->feature_point_num_few = true;
        LOG(ERROR) << "Localization --- feature point inliers num too low, lasting distance is: "
                   << lacking_feature_points_distance;
    }

    // visualize result
    timer_step.Tic();
    if (!new_corrected_measurements_.images.empty())
    {
        Visualizer::VisualizerStates visualizer_state(sliding_window_state_, {}, {}, new_corrected_measurements_.images,
                                                      new_factor_measurements_.sfm, new_raw_measurements_.visible_map);
        VisualizeVslamResult(visualizer_state);
    }
    LOG(INFO) << "Visualization takes " << 1e3 * timer_step.Elapsed() << " ms";

    if (parameters_.enable_sub_mapping)
    {
        const auto mpm_inlier_indexes =
            ComputeReprojectionError(new_factor_measurements_.mpm, sliding_window_state_.compensated_values);

        // add measurement to sub mapping thread
        timer_step.Tic();
        AddNewMeasurementToSubMapping(new_corrected_measurements_, new_factor_measurements_, mpm_inlier_indexes);
        LOG(INFO) << "Add measurement to sub mapping thread takes " << 1e3 * timer_step.Elapsed() << " ms";

        // update prebuild visualization map
        const auto new_maps_and_framesdatebases = sub_mapping_->GetOptimizedResultsAndClearOldResults();

        for (const auto& sub_map_framesdatebase : new_maps_and_framesdatebases)
        {
            new_maps_framesdatabases_.push_back(sub_map_framesdatebase);
            visualization_map_ = UpdatePrebuiltCloudMap(visualization_map_, sub_map_framesdatebase.first);
        }
    }

    LOG(INFO) << "The Whole Estimation takes " << 1e3 * timer_.Elapsed() << " ms\n";
    LOG(INFO) << "Done iteration = " << estimation_core_iteration_counter_++ << "\n\n";
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Localization::Reset()
{
    // Step1: pause vslam thread and imu prediction thread
    Pause();  // vslam thread paused

    while (is_imu_prediction_running_)
    {
        usleep(1e3);
    }  // imu prediction thread paused

    // Step2: do not add measurement and clear all measurements
    state_ = State::WAIT;
    measurements_manager_.Reset();

    // Step3: reset all Localization variable
    {
        // reset SlidingWindowState
        sliding_window_state_ = SlidingWindowState();
        // reset iteration counter of estimation core
        estimation_core_iteration_counter_ = 0;
        // reset ResetFlags
        reset_flags_ = ResetFlags();
        // reset SequenceCounter
        sequence_counter_ = SequenceCounter();
    }

    state_ = State::READY;

    // Step4: restart Localization thread
    Spin();

    LOG(WARNING) << "Localization --- vslam system is restarted!!!";

    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t Localization::PublishPointClouds(const SlidingWindowState& state) const
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
            pcd_msg[i++].Set(pt.GetX(), pt.GetY(), pt.GetZ());
        }
        output_local_feature_map_callback_(pcd_msg);
    }

    // publish global correspondence in factor graph
    std::vector<gtsam::Point3> inliers_landmarks;
    const auto&                factor_graph = state.static_smoother.getFactors();
    inliers_landmarks.reserve(factor_graph.size());

    // compute inliers
    for (size_t i = 0; i < factor_graph.size(); ++i)
    {
        const FactorGraph::Base::sharedFactor& factor = factor_graph.at(i);

        if (const PoseOnlyUnit3Factor* f = dynamic_cast<const PoseOnlyUnit3Factor*>(&(*factor)))
        {
            static const Scalar threshold = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
                parameters_.camera_params->intrinsics.at(0), 3.5);
            const Scalar error = (f->unwhitenedError(state.values)).norm();

            if (error > threshold)
            {
                continue;
            }

            inliers_landmarks.emplace_back(f->GetLandmarkMeasurement());
        }
    }

    // publish global correspondence if required
    if (output_global_correspondence_callback_ && !inliers_landmarks.empty())
    {
        PointCloudXYZIRRgbSt pcd(inliers_landmarks.size());

        for (size_t i = 0; i < inliers_landmarks.size(); i++)
        {
            const gtsam::Point3& point = inliers_landmarks.at(i);
            float32_t            x     = static_cast<float32_t>(point.x());
            float32_t            y     = static_cast<float32_t>(point.y());
            float32_t            z     = static_cast<float32_t>(point.z());
            pcd[i].Set(x, y, z);
        }

        output_global_correspondence_callback_(pcd);
    }

    return inliers_landmarks.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Localization::PublishPrebuiltMap() const
{
    holo::uint32_t sec, n_sec;
    holo::os::GetLocalTime(sec, n_sec);
    Timestamp        curr_timestamp(sec, n_sec);
    static Timestamp last_timestamp(0, 0);

    // publish prebuilt map
    if (output_global_feature_map_callback_ && (curr_timestamp - last_timestamp).ToSec() > 10.0)
    {
        last_timestamp = curr_timestamp;
        output_global_feature_map_callback_(visualization_map_);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Localization::PredictionThreadFunc(const Scalar frequency)
{
    // timer to control frequency of this function
    Timer timer(frequency);

    // the newest vehicle state & timestamp updated in vslam thread
    VehicleState newest_vslam_updated_state;
    Timestamp    newest_vslam_updated_timestamp(static_cast<uint64_t>(0));

    // the last predicted vehicle state & timestamp
    VehicleState last_predicted_state;
    Timestamp    last_predicted_timestamp(static_cast<uint64_t>(0));

    // declare nonlinear solver
    gtsam::ISAM2 isam;
    uint64_t     new_frame_id = 0;
    /// <timestamp, frameID>
    std::vector<std::pair<holo::uint64_t, holo::uint64_t>> timestamps_to_frameID;

    while (GetStatus() != Status::STOP)
    {
        timer.Start();

        // do prediction when vslam thread works
        if (GetStatus() == Status::SPIN && checkState())
        {
            is_imu_prediction_running_ = true;

            {
                if (is_vslam_initialized_)
                {
                    std::unique_lock<std::mutex> lock(update_mutex_);
                    if (is_vslam_updated_)
                    {
                        if (!timestamps_to_frameID.empty())
                        {
                            auto point_right =
                                std::lower_bound(timestamps_to_frameID.begin(), timestamps_to_frameID.end(),
                                                 newest_updated_timestamp_.ToNsec(),
                                                 [](const std::pair<holo::uint64_t, holo::uint64_t>& x,
                                                    holo::uint64_t t) { return x.first < t; });
                            LOG(INFO) << "LocalizationVSLAM --- updated vslam timestamp: "
                                      << newest_updated_timestamp_.ToString();
                            LOG(INFO) << "LocalizationVSLAM --- oldest prediction timestamp: "
                                      << timestamps_to_frameID.front().first;
                            if (point_right == timestamps_to_frameID.end() ||
                                point_right == timestamps_to_frameID.begin())
                            {
                                newest_vslam_updated_state     = newest_updated_vehicle_state_;
                                newest_vslam_updated_timestamp = newest_updated_timestamp_;
                                last_predicted_state           = newest_vslam_updated_state;
                                last_predicted_timestamp       = newest_updated_timestamp_;
                                is_vslam_updated_              = false;
                                LOG(ERROR)
                                    << "LocalizationVSLAM --- updated vslam timestamp is NOT contained in isam.\n";
                            }
                            else
                            {
                                auto  point_left = point_right - 1;
                                Pose3 pose_left  = HoloGtsam::Convert(
                                     isam.calculateEstimate(X(point_left->second)).cast<gtsam::Pose3>());
                                Pose3 pose_right = HoloGtsam::Convert(
                                    isam.calculateEstimate(X(point_right->second)).cast<gtsam::Pose3>());
                                holo::uint64_t interpolate_ratio =
                                    (newest_updated_timestamp_.ToNsec() - point_left->first) /
                                    (point_right->first - point_left->first);
                                Pose3 predicted_pose_at_updated_timestamp =
                                    Pose3::Interpolate(pose_left, pose_right, interpolate_ratio);

                                Pose3 delta_pose = predicted_pose_at_updated_timestamp.Inverse() *
                                                   newest_updated_vehicle_state_.navstate.GetPose();

                                const Pose3 last_predicted_pose = last_predicted_state.navstate.GetPose();
                                last_predicted_state.navstate.SetPose(last_predicted_pose * delta_pose);
                                last_predicted_state.bias      = newest_updated_vehicle_state_.bias;
                                newest_vslam_updated_state     = newest_updated_vehicle_state_;
                                newest_vslam_updated_timestamp = newest_updated_timestamp_;
                                is_vslam_updated_              = false;
                            }
                            // reset isam state
                            isam         = gtsam::ISAM2();
                            new_frame_id = 0;
                            timestamps_to_frameID.clear();
                        }
                        else
                        {
                            newest_vslam_updated_state     = newest_updated_vehicle_state_;
                            newest_vslam_updated_timestamp = newest_updated_timestamp_;
                            last_predicted_state           = newest_vslam_updated_state;
                            last_predicted_timestamp       = newest_updated_timestamp_;
                            is_vslam_updated_              = false;
                        }
                    }
                }
                else
                {
                    // vslam thread was not initialized yet. nothing can this thread do.
                    is_imu_prediction_running_ = false;
                    timer.Stop();
                    continue;
                }
            }

            // step2: check whether vslam is good
            bool vslam_is_good = true;

            // step3: do prediction
            VehicleState predicted_navstate;
            Timestamp    current_time;
            bool         prediction_success = false;

            if (parameters_.predict_navstate_by_pure_imu_integration)
            {
                Imu newest_imu;

                if (!measurements_manager_.GetLatestMeasurement(newest_imu) ||
                    newest_imu.GetTimestamp() == last_predicted_timestamp)
                {
                    LOG(ERROR) << "LocalizationVSLAM --- imu is not updated!!!";
                    timer.Stop();
                    continue;
                }

                current_time = newest_imu.GetTimestamp();
                std::vector<Imu> imus;

                if (!measurements_manager_.GetImuMeasurements(newest_vslam_updated_timestamp, current_time, imus))
                {
                    LOG(ERROR) << "LocalizationVSLAM --- failed to get imus chain in prediction thread";
                    timer.Stop();
                    continue;
                }

                predicted_navstate = ImuPrediction(newest_vslam_updated_state, imus);
                prediction_success = true;
            }
            else
            {
                ChassisState newest_chassis_state;

                if (!measurements_manager_.GetLatestMeasurement(newest_chassis_state) ||
                    newest_chassis_state.GetTimestamp() == last_predicted_timestamp)
                {
                    LOG(ERROR) << "LocalizationVSLAM --- chassis state is not updated!!!";
                    timer.Stop();
                    continue;
                }

                current_time = newest_chassis_state.GetTimestamp();

                const Scalar kTimeThreshold = 1.0 / parameters_.minimum_acceptable_frequency;

                if (vslam_is_good && (current_time - newest_vslam_updated_timestamp).ToSec() > kTimeThreshold)
                {
                    LOG(ERROR) << "LocalizationVSLAM --- Newest chassis state timestamp is " << current_time.ToString();
                    LOG(ERROR) << "LocalizationVSLAM --- Newest processed image timestamp is "
                               << newest_vslam_updated_timestamp.ToString();
                    LOG(ERROR)
                        << "LocalizationVSLAM --- Latency of vslam raw measurement is too seriously. this thread "
                           "will not work well!!!\n";
                    vslam_is_good = false;
                }

                std::vector<ChassisState> chassis_states, low_frequency_chassis_states;

                if (!measurements_manager_.GetChassisStatesMeasurements(last_predicted_timestamp, current_time,
                                                                        chassis_states))
                {
                    LOG(ERROR) << "LocalizationVSLAM --- failed to get chassis state in prediction thread";
                    timer.Stop();
                    continue;
                }

                std::vector<std::vector<Imu>> imu_blocks;
                imu_blocks.reserve(chassis_states.size());

                if (SlidingWindowState::enable_estimation_with_acc)
                {
                    low_frequency_chassis_states.reserve(chassis_states.size());
                    low_frequency_chassis_states.emplace_back(chassis_states.front());

                    holo::uint64_t chassis_frame_id = new_frame_id;
                    for (size_t i = 1; i < chassis_states.size(); i++)
                    {
                        const Timestamp& end   = chassis_states.at(i).GetTimestamp();
                        const Timestamp& start = low_frequency_chassis_states.back().GetTimestamp();

                        if ((end - start).ToSec() < 0.019999 &&  // Underclocking to 50 Hz
                            i < chassis_states.size() - 1)
                        {
                            continue;
                        }

                        std::vector<Imu> imus;

                        if (!measurements_manager_.GetImuMeasurements(start, end, imus))
                        {
                            LOG(WARNING) << "LocalizationVSLAM --- failed to get imus between " << start.ToString()
                                         << " and " << end.ToString();
                            break;
                        }

                        imu_blocks.emplace_back(imus);
                        low_frequency_chassis_states.emplace_back(chassis_states.at(i));
                        timestamps_to_frameID.emplace_back(
                            std::make_pair(chassis_states.at(i).GetTimestamp().ToNsec(), ++chassis_frame_id));
                    }

                    if (imu_blocks.empty())
                    {
                        timer.Stop();
                        LOG(ERROR) << "LocalizationVSLAM --- failed to get imus in prediction thread.\n";
                        continue;
                    }

                    current_time = low_frequency_chassis_states.back().GetTimestamp();

                    TicTocTimer timer;
                    timer.Tic();
                    predicted_navstate = NavigationStatePrediction(isam, new_frame_id, last_predicted_state, imu_blocks,
                                                                   low_frequency_chassis_states);
                    std::fstream file(holo::GetLogFileAbsolutePath("holo_localization_parking/vslam/prediction_hz.txt"),
                                      std::fstream::app);
                    file << 1e3 * timer.Elapsed() << " " << 1.0 / timer.Elapsed() << " " << chassis_states.size() << " "
                         << low_frequency_chassis_states.size() << " "
                         << (newest_chassis_state.GetTimestamp() - current_time).ToSec() << "\n";
                    file.close();
                }
                else
                {
                    std::vector<std::vector<ChassisState>> chassis_state_blocks;
                    chassis_state_blocks.reserve(chassis_states.size());

                    holo::uint64_t chassis_frame_id   = new_frame_id;
                    ChassisState   last_chassis_state = chassis_states.front();

                    for (size_t i = 1; i < chassis_states.size(); i++)
                    {
                        const Timestamp& end   = chassis_states.at(i).GetTimestamp();
                        const Timestamp& start = last_chassis_state.GetTimestamp();

                        if ((end - start).ToSec() < 0.1 &&  // Underclocking to 10 Hz
                            i < chassis_states.size() - 1)
                        {
                            continue;
                        }

                        std::vector<Imu> imus;

                        if (!measurements_manager_.GetImuMeasurements(start, end, imus))
                        {
                            LOG(WARNING) << "LocalizationVSLAM --- failed to get imus between " << start.ToString()
                                         << " and " << end.ToString();
                            break;
                        }

                        imu_blocks.emplace_back(imus);

                        std::vector<ChassisState> current_chassis_state_chain;

                        if (!measurements_manager_.GetChassisStatesMeasurements(start, end,
                                                                                current_chassis_state_chain))
                        {
                            LOG(WARNING) << "LocalizationVSLAM --- failed to get imus between " << start.ToString()
                                         << " and " << end.ToString();
                            break;
                        }
                        chassis_state_blocks.emplace_back(current_chassis_state_chain);
                        last_chassis_state = current_chassis_state_chain.back();

                        timestamps_to_frameID.emplace_back(
                            std::make_pair(chassis_states.at(i).GetTimestamp().ToNsec(), ++chassis_frame_id));
                    }

                    if (imu_blocks.empty())
                    {
                        timer.Stop();
                        LOG(ERROR) << "LocalizationVSLAM --- failed to get imus in prediction thread.\n";
                        continue;
                    }

                    current_time = chassis_state_blocks.back().back().GetTimestamp();

                    predicted_navstate = NavigationStatePrediction(isam, new_frame_id, last_predicted_state, imu_blocks,
                                                                   chassis_state_blocks);
                }

                prediction_success = true;
            }

            // publish prediction result
            if (prediction_success)
            {
                PublishImuPredictionResult(predicted_navstate, current_time,
                                           sequence_counter_.prediction_callback_sequence_counter++, vslam_is_good);
                last_predicted_timestamp = current_time;
                last_predicted_state     = predicted_navstate;
            }
        }

        is_imu_prediction_running_ = false;

        timer.Stop();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VehicleState Localization::ImuPrediction(const VehicleState& newest_vehicle_state, const std::vector<Imu>& imus) const
{
    const gtsam::imuBias::ConstantBias bias(HoloGtsam::Convert(newest_vehicle_state.AccBias()),
                                            HoloGtsam::Convert(newest_vehicle_state.GyroBias()));
    const PreintegratedImuMeasurements pim                = preprocessor_.CreateNewPim(imus, bias);
    const gtsam::NavState              navstate           = HoloGtsam::Convert(newest_vehicle_state.navstate);
    const gtsam::NavState              predicted_navstate = pim.predict(navstate, bias);

    return VehicleState(HoloGtsam::Convert(predicted_navstate), newest_vehicle_state.bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VehicleState Localization::NavigationStatePrediction(gtsam::ISAM2& isam, uint64_t& new_frame_id,
                                                     const VehicleState&                  newest_vehicle_state,
                                                     const std::vector<std::vector<Imu>>& imu_blocks,
                                                     const std::vector<ChassisState>&     chassis_states) const
{
    FactorGraph factor_graph;
    Values      values;

    // retrieve prior values
    const gtsam::Pose3                 prior_pose     = HoloGtsam::Convert(newest_vehicle_state.Pose());
    const gtsam::Vector3               prior_velocity = HoloGtsam::Convert(newest_vehicle_state.Velocity());
    const gtsam::imuBias::ConstantBias prior_bias(HoloGtsam::Convert(newest_vehicle_state.AccBias()),
                                                  HoloGtsam::Convert(newest_vehicle_state.GyroBias()));

    if (!isam.valueExists(X(new_frame_id)))
    {
        // add prior pose factor
        gtsam::Vector6 prior_pose_sigma;
        prior_pose_sigma << 1e-9, 1e-9, 1e-9, 1e-9, 1e-9, 1e-9;
        const gtsam::PriorFactor<gtsam::Pose3> prior_pose_factor(X(new_frame_id), prior_pose,
                                                                 gtsam::noiseModel::Diagonal::Sigmas(prior_pose_sigma));
        factor_graph.add(prior_pose_factor);

        // add prior velocity factor
        const gtsam::PriorFactor<gtsam::Vector3> prior_velocity_factor(
            V(new_frame_id), prior_velocity,
            gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.builder_params.velocity_factor_sigma)));
        factor_graph.add(prior_velocity_factor);

        // add prior bias factor
        const gtsam::PriorFactor<gtsam::imuBias::ConstantBias> prior_bias_factor(
            B(new_frame_id), prior_bias,
            gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.builder_params.prior_noise.bias_sigma)));
        factor_graph.add(prior_bias_factor);

        // add initial value
        values.insert(X(new_frame_id), prior_pose);
        values.insert(V(new_frame_id), prior_velocity);
        values.insert(B(new_frame_id), prior_bias);
    }

    gtsam::NavState predicted_navstate = HoloGtsam::Convert(newest_vehicle_state.navstate);

    // build factor graph by new measurements
    for (size_t i = 1; i < chassis_states.size(); i++)
    {
        Vector3 velocity(parameters_.rmpp_params.speed_correction_coeff[0] * chassis_states.at(i).GetVehicleSpeed() +
                             parameters_.rmpp_params.speed_correction_coeff[1],
                         0.0, 0.0);
        const auto& imus = preprocessor_.ConvertImuMeasurements(imu_blocks.at(i - 1), parameters_.rmpp_params.T_bi);
        const auto  pim  = preprocessor_.CreateNewPim(imus, prior_bias);

        const uint64_t old_frame_index = new_frame_id;
        const uint64_t new_frame_index = new_frame_id + 1;
        new_frame_id                   = new_frame_index;

        // create imu factor
        factor_graph.add(boost::make_shared<ImuFactor>(X(old_frame_index), V(old_frame_index), X(new_frame_index),
                                                       V(new_frame_index), B(old_frame_index), pim));

        // create imu bias noise
        const gtsam::SharedNoiseModel bias_noise =
            gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.builder_params.bias_between_sigma));
        factor_graph.add(boost::make_shared<ImuBiasFactor>(B(old_frame_index), B(new_frame_index),
                                                           gtsam::imuBias::ConstantBias(), bias_noise));

        // add pose3 between factor with identity measurement when the vehicle is stationary
        bool is_zero_speed_state = preprocessor_.IsZeroSpeedState({chassis_states.at(i - 1), chassis_states.at(i)});

        if (is_zero_speed_state)
        {
            // create pose3 between factor noise model
            const gtsam::SharedNoiseModel pose3_between_factor_noise = gtsam::noiseModel::Diagonal::Sigmas(
                HoloGtsam::Convert(parameters_.builder_params.zero_velocity_between_pose_sigma));
            factor_graph.add(boost::make_shared<Pose3BetweenFactor>(X(old_frame_index), X(new_frame_index),
                                                                    gtsam::Pose3(), pose3_between_factor_noise));
        }

        // insert new values
        predicted_navstate = pim.predict(predicted_navstate, prior_bias);
        values.insert(X(new_frame_index), predicted_navstate.pose());
        values.insert(V(new_frame_index), predicted_navstate.velocity());
        values.insert(B(new_frame_index), prior_bias);

        // slipping checking
        const auto measured_speed     = velocity[0];
        const auto predicted_pose     = predicted_navstate.pose();
        const auto predicted_velocity = predicted_navstate.velocity();
        const auto predicted_speed    = (predicted_pose.inverse().rotation().rotate(predicted_velocity)).x();

        if (std::fabs(holo::Degree(predicted_pose.rotation().pitch())) > parameters_.rmpp_params.slope_threshold &&
            measured_speed * predicted_speed < 0)
        {
            LOG(WARNING) << "NavigationStatePrediction --- measured speed and predicted speed are diametrically "
                            "opposed. vehicle may be slipping now.\n";
        }
        else
        {
            // add velocity factor
            const Scalar rotation_threshold = 5e-3;  // rotation threshold to determine if turn
            auto         sigma              = parameters_.builder_params.velocity_factor_sigma;

            if (pim.deltaRij().rpy().norm() > rotation_threshold)
            {
                sigma = parameters_.builder_params.velocity_factor_sigma_when_turns;
            }

            if (!is_zero_speed_state && std::fabs(measured_speed) < 1e-3)
            {
                LOG(WARNING) << "NavigationStatePrediction --- the vehicle is NOT stationary while measured speed is "
                                "almost zero.\n";
                sigma = parameters_.builder_params.low_precision_velocity_factor_sigma;

                Scalar sign = 1.0;

                if (chassis_states.at(i).GetGearPosition() == ChassisState::GearPosition::R)
                {
                    sign = -1.0;
                }

                velocity = Vector3(sign * 0.15, 0.0, 0.0);
            }

            const gtsam::SharedNoiseModel velocity_noise =
                gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(sigma));
            factor_graph.add(boost::make_shared<VelocityFactor>(X(new_frame_index), V(new_frame_index),
                                                                HoloGtsam::Convert(velocity), velocity_noise));
        }
    }

    isam.update(factor_graph, values);
    values = isam.calculateEstimate();

    // retrieve newest navstate
    const Pose3   pose     = HoloGtsam::Convert(values.at(X(new_frame_id)).cast<gtsam::Pose3>());
    const Vector3 velocity = HoloGtsam::Convert(values.at(V(new_frame_id)).cast<gtsam::Vector3>());

    return VehicleState(pose, velocity, newest_vehicle_state.bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VehicleState Localization::NavigationStatePrediction(
    gtsam::ISAM2& isam, uint64_t& new_frame_id, const VehicleState& newest_vehicle_state,
    const std::vector<std::vector<Imu>>&          imu_blocks,
    const std::vector<std::vector<ChassisState>>& chassis_state_blocks) const
{
    FactorGraph factor_graph;
    Values      values;

    // retrieve prior values
    const gtsam::Pose3   prior_pose = HoloGtsam::Convert(newest_vehicle_state.Pose());
    const gtsam::Vector3 prior_bias = HoloGtsam::Convert(newest_vehicle_state.GyroBias());

    if (!isam.valueExists(X(new_frame_id)))
    {
        // add prior pose factor
        gtsam::Vector6 prior_pose_sigma;
        prior_pose_sigma << 1e-9, 1e-9, 1e-9, 1e-9, 1e-9, 1e-9;
        const gtsam::PriorFactor<gtsam::Pose3> prior_pose_factor(X(new_frame_id), prior_pose,
                                                                 gtsam::noiseModel::Diagonal::Sigmas(prior_pose_sigma));
        factor_graph.add(prior_pose_factor);

        // add prior bias factor
        const gtsam::PriorFactor<gtsam::Vector3> prior_bias_factor(
            B(new_frame_id), prior_bias, gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(1e-1, 1e-1, 1e-1)));
        factor_graph.add(prior_bias_factor);

        // add initial value
        values.insert(X(new_frame_id), prior_pose);
        values.insert(B(new_frame_id), prior_bias);
    }

    gtsam::Pose3 new_pose = HoloGtsam::Convert(newest_vehicle_state.Pose());

    // build factor graph by new measurements
    for (size_t i = 0; i < chassis_state_blocks.size(); i++)
    {
        const uint64_t old_frame_index = new_frame_id;
        const uint64_t new_frame_index = new_frame_id + 1;
        new_frame_id                   = new_frame_index;

        static boost::shared_ptr<PreintegratedAhrsMeasurements::Params> ahrs_params =
            boost::make_shared<PreintegratedAhrsMeasurements::Params>(
                parameters_.rmpp_params.pim_params->getGyroscopeCovariance(),
                parameters_.rmpp_params.pim_params->getOmegaCoriolis());

        // create rotation only
        const auto& imus = preprocessor_.ConvertImuMeasurements(imu_blocks.at(i), parameters_.rmpp_params.T_bi);
        PreintegratedAhrsMeasurements pam(ahrs_params, prior_bias);

        for (uint16_t i = 0; i < (uint16_t)(imus.size() - 1); i++)
        {
            const Scalar dt = (imus.at(i + 1).GetTimestamp() - imus.at(i).GetTimestamp()).ToSec();

            const auto angular_velocity =
                0.5 * imus.at(i).GetAngularVelocity() + 0.5 * imus.at(i + 1).GetAngularVelocity();

            pam.integrateMeasurement(HoloGtsam::Convert(angular_velocity), dt);
        }

        // create imu factor
        factor_graph.add(
            boost::make_shared<RotationOnlyImuFactor>(X(old_frame_index), X(new_frame_index), B(old_frame_index), pam));

        // create wim
        static AckermannWheelIntegration wheel_integration(parameters_.rmpp_params.wim_params);
        const auto                       new_wim = wheel_integration.integrateMeasurement(chassis_state_blocks.at(i));

        // create wheel integration factor
        const gtsam::Pose2 pose2(new_wim.delta_x, new_wim.delta_y, new_wim.delta_yaw);
        const auto         t                              = pose2.translation().norm();
        Vector6            wheel_integration_factor_sigma = parameters_.builder_params.wheel_integration_factor_sigma;

        if (t < 1e-5)
        {
            wheel_integration_factor_sigma = parameters_.builder_params.zero_velocity_between_pose_sigma;
        }
        else if (new_wim.delta_x < 0)
        {
            /// @brief relative large gyro noise may cause yaw discontinueity when in R gear status. Ackermann wheel
            /// integration performs better in this case, so we decrease wim sigma to the same level with gyro
            wheel_integration_factor_sigma(2) = 3e-3;
        }

        // create pose3 between factor noise model
        const gtsam::SharedNoiseModel pose3_between_factor_noise =
            gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(wheel_integration_factor_sigma));

        factor_graph.add(boost::make_shared<Pose3BetweenFactor>(
            X(old_frame_index), X(new_frame_index),
            gtsam::Pose3(gtsam::Pose2(new_wim.delta_x, new_wim.delta_y, new_wim.delta_yaw)),
            pose3_between_factor_noise));

        // create imu bias noise
        static gtsam::Vector3         gyro_bias_sigma(parameters_.builder_params.bias_between_sigma[3],
                                                      parameters_.builder_params.bias_between_sigma[4],
                                                      parameters_.builder_params.bias_between_sigma[5]);
        const gtsam::SharedNoiseModel bias_noise = gtsam::noiseModel::Diagonal::Sigmas(gyro_bias_sigma);
        factor_graph.add(boost::make_shared<Vector3BetweenFactor>(B(old_frame_index), B(new_frame_index),
                                                                  gtsam::Vector3(0, 0, 0), bias_noise));

        // predict new vehicle state with wim
        gtsam::Pose3 delta_pose(gtsam::Pose2(new_wim.delta_x, new_wim.delta_y, new_wim.delta_yaw));
        new_pose = new_pose * delta_pose;

        // insert new values
        values.insert(X(new_frame_index), new_pose);
        values.insert(B(new_frame_index), prior_bias);
    }

    isam.update(factor_graph, values);
    values = isam.calculateEstimate();

    // retrieve newest navstate
    const Pose3 pose = HoloGtsam::Convert(values.at(X(new_frame_id)).cast<gtsam::Pose3>());

    const Scalar speed =
        chassis_state_blocks.back().back().GetVehicleSpeed() * parameters_.rmpp_params.speed_correction_coeff[0] +
        parameters_.rmpp_params.speed_correction_coeff[1];

    return VehicleState(pose, Vector3(speed, 0, 0), newest_vehicle_state.bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Localization::PublishImuPredictionResult(const VehicleState& vehicle_state, const Timestamp& current_time,
                                              const uint64_t sequence_counter, bool vslam_is_good) const
{
    if (!imu_prediction_result_callback_)
    {
        return;
    }

    Odometry predicted_odo = VehicleStateToOdometry(vehicle_state, current_time, sequence_counter);

    if (!vslam_is_good)
    {
        // change status to SOLUTIONNOGOOD
        predicted_odo.SetStatus(Odometry::Status::SOLUTIONNOGOOD);
    }

    // result callback
    imu_prediction_result_callback_(predicted_odo);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCloudXYZIRRgbSt Localization::UpdatePrebuiltCloudMap(const PointCloudXYZIRRgbSt& old_point_cloud_map,
                                                          const Map&                  new_map) const
{
    PointCloudXYZIRRgbSt updated_map         = old_point_cloud_map;
    ConstMapPtr          map_ptr             = std::make_shared<const Map>(new_map);
    const auto           point_cloud_sub_map = ConvertToPointCloud(map_ptr);
    updated_map.insert(updated_map.end(), point_cloud_sub_map.begin(), point_cloud_sub_map.end());
    return updated_map;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Localization::AddNewMeasurementToSubMapping(const CorrectedMeasurement& corrected_measurement,
                                                 const FactorMeasurements&   factor_measurements,
                                                 const std::set<uint64_t>&   mpm_inlier_indexes)
{
    static bool               is_sub_map_data_collecting    = false;
    static uint64_t           good_retracking_num           = 0;
    const uint64_t            inilers_num_threshold         = 10;
    const uint64_t            good_retracking_num_threshold = 5;
    uint64_t                  inliers_num                   = mpm_inlier_indexes.size();
    auto                      new_factor_measurement        = factor_measurements;
    MapProjectionMeasurements mpm_inliers;

    for (auto index : mpm_inlier_indexes)
    {
        mpm_inliers.push_back(factor_measurements.mpm.at(index));
    }
    new_factor_measurement.mpm = mpm_inliers;

    /// @todo (guopeikai) remove it later
    LOG(INFO) << "inlier_num: " << inliers_num << std::endl;

    if (inliers_num > inilers_num_threshold && !is_sub_map_data_collecting)
    {
        return;
    }

    if (inliers_num > inilers_num_threshold)
    {
        good_retracking_num++;
    }
    else
    {
        good_retracking_num = 0;
    }

    const auto curr_frame_id = sliding_window_state_.static_tracker_state.frame_id;
    LOG(INFO) << "the frame: " << curr_frame_id << " is added for sub mapping ...";

    SubMappingMeasurement sub_mapping_data;
    sub_mapping_data.frame_id            = curr_frame_id;
    sub_mapping_data.images              = corrected_measurement.images;
    sub_mapping_data.tracks              = sliding_window_state_.static_tracker_state.tracks;
    sub_mapping_data.factor_measurements = new_factor_measurement;
    sub_mapping_data.sub_map_id          = sub_map_id_;

    /// @todo update the status of visible mappoints

    if (good_retracking_num > good_retracking_num_threshold)
    {
        sub_mapping_data.status = SubMapping::MeasurementStatus::END_FRAME;
        good_retracking_num     = 0;
        sub_map_id_++;
        is_sub_map_data_collecting = false;
    }
    else
    {
        sub_mapping_data.status    = is_sub_map_data_collecting ? SubMapping::MeasurementStatus::OTHER_FRAME :
                                                                  SubMapping::MeasurementStatus::START_FRAME;
        is_sub_map_data_collecting = true;
    }
    sub_mapping_->AddNewMeasurement(sub_mapping_data);
    LOG(INFO) << "Localization --- Adding measurement to sub mapping thread is finished ";
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::set<uint64_t> Localization::ComputeReprojectionError(const std::vector<MapProjectionMeasurement>& mpms,
                                                          const Values&                                xvb_values) const
{
    std::set<uint64_t> inlier_mpm_indexes;
    for (uint64_t index = 0; index < mpms.size(); index++)
    {
        const auto& mpm = mpms.at(index);

        // get newest frame id
        const uint64_t frame_id = mpm.frame_id;

        // get camera index and corresponding extrinsic
        const auto& camera_index = mpm.camera_index;
        const auto& T_bc         = parameters_.camera_params->extrinsics.at(camera_index);

        // compute camera pose in vslam map frame
        const gtsam::Pose3 T_wc =
            xvb_values.at(X(frame_id)).cast<gtsam::Pose3>() * holo::localization::HoloGtsam::Convert(T_bc);

        // compute landmark location
        gtsam::Point3 landmark = holo::localization::HoloGtsam::Convert(mpm.map_point->position);

        // transform landmark to camera coordinate
        const auto ptc = HoloGtsam::Convert(T_wc.inverse() * landmark);

        // check if behind camera
        const auto&  ray                                        = mpm.bearing;
        const Scalar angle_between_feature_ray_and_optical_axis = holo::Degree(std::acos(ray[2] / ray.GetNorm()));

        if (angle_between_feature_ray_and_optical_axis < 90.0 && ptc.GetZ() < 0)
        {
            // behind camera
            continue;
        }

        // create two vectors
        const gtsam::Unit3 p = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(ptc));
        const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(Point3(mpm.bearing)));

        // compute error
        const Scalar threshold = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
            parameters_.camera_params->intrinsics.at(0), 3.5);
        if (p.errorVector(q).norm() < threshold)
        {
            mpm.map_point->reprojection_errors.push_back(p.errorVector(q).norm());
            inlier_mpm_indexes.insert(index);
        }
    }
    return inlier_mpm_indexes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Localization::RemoveMappointsWithRememberRate(const MapPtr& prebuilt_map) const
{
    if (prebuilt_map == nullptr)
    {
        return;
    }

    uint64_t removed_mp_num = 0;
    for (auto& mp : *prebuilt_map)
    {
        mp->UpdateRememberRate();
        if (mp->remember_rate < 0.3)
        {
            mp = nullptr;
            removed_mp_num++;
        }
    }
    LOG(INFO) << "Localization --- Remove mappoints which below remember rate threshold: " << removed_mp_num;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
