/*!
 * \brief sliding window estimator class in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date July-31-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/sliding_window_estimator.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SlidingWindowEstimator::Parameters SlidingWindowEstimator::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // track state transition parameters
    const holo::yaml::Node                 tst_node   = node["tst_params"].as<holo::yaml::Node>(holo::yaml::Node());
    const TrackStateTransition::Parameters tst_params = TrackStateTransition::Parameters::LoadFromYaml(tst_node);

    // gtsam::IncrementalFixedLagSmoother parameters
    const holo::yaml::Node smoother_node = node["smoother_params"];
    const Scalar           lag_size      = smoother_node["lag_size"].as<Scalar>(10);
    gtsam::ISAM2Params     isam2_params;
    isam2_params.enablePartialRelinearizationCheck =
        smoother_node["enable_partial_relinearization_check"].as<bool>(false);
    isam2_params.findUnusedFactorSlots = smoother_node["find_unused_factor_slots"].as<bool>(true);

    // combine all into parameters
    return Parameters(tst_params, lag_size, isam2_params);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SlidingWindowEstimator::Parameters SlidingWindowEstimator::Parameters::Example()
{
    // return parameters
    return Parameters(TrackStateTransition::Parameters::Example());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SlidingWindowEstimator::SlidingWindowEstimator(const Parameters&            parameters,
                                               const CameraParameters::Ptr& camera_parameters)
  : parameters_(parameters)
  , camera_parameters_(camera_parameters)
  , track_state_transition_(parameters_.tst_params, camera_parameters)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SlidingWindowEstimator::Initialize(SlidingWindowState&       state,
                                        const FactorMeasurements& initial_factor_measurements,
                                        const Timestamp& initial_timestamp, const uint64_t initial_frame_id) const
{
    // @Step 1: create initial factor graph and values
    const auto initial_problem = builder_->Initialize(initial_factor_measurements, initial_frame_id);

    if (!Optimization(SlidingWindowState::static_smoother, initial_problem, initial_frame_id))
    {
        return false;
    }

    state.timestamp          = initial_timestamp;
    state.frame_id           = initial_frame_id;
    state.values             = SlidingWindowState::static_smoother.calculateEstimate();
    state.compensated_values = state.values;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SlidingWindowEstimator::Run(SlidingWindowState& state, const FactorMeasurements& new_factor_measurement,
                                 const Timestamp& new_timestamp, const uint64_t new_frame_id) const
{
    if (!state.IsInitialized())
    {
        throw std::runtime_error("SlidingWindowEstimator --- you should call Initialize() first");
    }

    auto& smoother      = state.static_smoother;
    auto& tracker_state = state.static_tracker_state;

    holo::TicTocTimer timer;

    if (builder_->Params().enable_unit3_factor)
    {
        // Step 1: call track state transition
        track_state_transition_.RunBeforeOptimization(tracker_state, new_factor_measurement.predicted_values,
                                                      smoother.getFactors());
        LOG(INFO) << "RunBeforeOptimization takes " << 1000.0 * timer.Elapsed() << " ms.\n";
    }

    timer.Tic();

    // Step 2: build new sub factor graph and prepare new values
    // FactorMeasurements fm(new_factor_measurement.pim, new_factor_measurement.pam, new_factor_measurement.mpm,
    //                       new_factor_measurement.vm, new_factor_measurement.wim,
    //                       new_factor_measurement.predicted_values, new_factor_measurement.gt_pose,
    //                       new_factor_measurement.position, new_factor_measurement.between_rotations);

    const auto new_sub_problem = builder_->Run(new_factor_measurement, tracker_state.tracks, new_frame_id);

    LOG(INFO) << "GraphBuilder takes " << 1000.0 * timer.Elapsed() << " ms.\n";

    // Step 3: optimize by fix lag smoother
    if (!Optimization(smoother, new_sub_problem, new_frame_id, state.factors_to_remove))
    {
        return false;
    }

    const Values optimized_values = smoother.calculateEstimate();

    // Step 4: call track state transition, filter bad tracks with optimized values
    timer.Tic();

    if (builder_->Params().enable_unit3_factor)
    {
        track_state_transition_.RunAfterOptimization(tracker_state, optimized_values, smoother.getFactors());
        LOG(INFO) << "RunAfterOptimization takes " << 1000.0 * timer.Elapsed() << " ms.\n";
    }

    // Step 5: compensate values. to temporarily solve the observibility issues of an sliding window state estimator
    timer.Tic();
    state.values = optimized_values;
    state.compensated_values =
        CompensateValues(state.compensated_values, optimized_values, smoother.getFactors(), new_frame_id);
    LOG(INFO) << "CompensateValues takes " << 1000.0 * timer.Elapsed() << " ms.\n";

    // Step 6: find factors to remove
    timer.Tic();
    state.factors_to_remove = FindFactorsToRemove(state);
    LOG(INFO) << "FindFactorsToRemove takes " << 1000.0 * timer.Elapsed() << " ms.\n";

    state.timestamp = new_timestamp;
    state.frame_id  = new_frame_id;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values SlidingWindowEstimator::CompensateValues(const Values& old_compensated_values,
                                                const Values& new_optimized_values, const FactorGraph& new_factor_graph,
                                                const uint64_t new_frame_id) const
{
    // check if this smoother contain any global factors, if true, no need to compensate values
    bool with_global_factors = false;

    for (const auto& factor : new_factor_graph)
    {
        if (dynamic_cast<const gtsam::PriorFactor<gtsam::Pose3>*>(&(*factor)) ||
            dynamic_cast<const vslam::PoseOnlyUnit3Factor*>(&(*factor)))
        {
            with_global_factors = true;
            break;
        }
    }

    if (with_global_factors)
    {
        return new_optimized_values;
    }

    const uint64_t oldest_frame_id = GetOldestFrameId(new_frame_id);

    // if oldest_frame_id == 0, the sliding window will not jump due to prior factor
    // so use estimated values as compensated values
    if (oldest_frame_id == 0)
    {
        return new_optimized_values;
    }

    // get reference parameters (x, y, z, yaw) of oldest frame from old compensated values
    gtsam::Pose3  old_reference_pose = old_compensated_values.at(X(oldest_frame_id)).cast<gtsam::Pose3>();
    gtsam::Point3 old_reference_xyz;
    Scalar        old_reference_yaw;
    std::tie(old_reference_xyz, old_reference_yaw) = GetXYZYaw(old_reference_pose);

    // get reference parameters (x, y, z, yaw) of oldest frame from current estimated values
    gtsam::Pose3  new_reference_pose = new_optimized_values.at(X(oldest_frame_id)).cast<gtsam::Pose3>();
    gtsam::Point3 new_reference_xyz;
    Scalar        new_reference_yaw;
    std::tie(new_reference_xyz, new_reference_yaw) = GetXYZYaw(new_reference_pose);

    // delta rotation to compensate rotation
    const gtsam::Rot3 delta_rotation = gtsam::Rot3::Yaw(old_reference_yaw - new_reference_yaw);

    Values compensated_values;

    if (SlidingWindowState::enable_estimation_with_acc)
    {
        // compensate x,y,z,yaw
        compensated_values = CompensateXYZYaw(old_reference_xyz, new_reference_xyz, delta_rotation, oldest_frame_id,
                                              new_optimized_values);
    }
    else
    {
        compensated_values = Compensate6DoFInSlidingWindow(old_reference_pose, new_reference_pose, oldest_frame_id,
                                                           new_optimized_values);
    }
    return compensated_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SlidingWindowEstimator::Parameters& SlidingWindowEstimator::Params() const
{
    return parameters_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SlidingWindowEstimator::Optimization(gtsam::IncrementalFixedLagSmoother& smoother,
                                          const GraphBuilder::Problem& new_sub_problem, const uint64_t new_frame_id,
                                          const gtsam::FactorIndices& factors_to_remove) const
{
    TicTocTimer        timer;
    const FactorGraph& new_sub_factor_graph = new_sub_problem.factor_graph;
    const Values&      new_sub_values       = new_sub_problem.values;
    // use frame_id as timestamp in IncrementalFixedLagSmoother to make
    // the number of frame in IncrementalFixedLagSmoother unchangeable
    const Scalar                                        timestamp = new_frame_id;
    gtsam::IncrementalFixedLagSmoother::KeyTimestampMap key_timestamp_map;

    // step1: prepare key-timestamp map
    for (const FactorGraph::Base::sharedFactor& factor : new_sub_factor_graph)
    {
        for (const gtsam::Key& key : factor->keys())
        {
            gtsam::Symbol symbol(key);

            if (symbol.chr() == 'l') /* update landmark timestamp */
            {
                key_timestamp_map[key] = timestamp;
            }
            else if (symbol.chr() == 's')
            {
                key_timestamp_map[key] = timestamp;
            }
            else if (symbol.chr() == 'p')
            {
                key_timestamp_map[key] = timestamp;
            }
            else if (symbol.index() == new_frame_id) /* only add pose, velocity, bias of current frame */
            {
                key_timestamp_map[key] = timestamp;
            }
        }
    }
    LOG(INFO) << "Prepare key-timestamp map takes " << 1000.0 * timer.Elapsed() << " ms.\n";
    timer.Tic();

    // step2: update smoother
    gtsam::FixedLagSmoother::Result result;
    LOG(INFO) << "SlidingWindowEstimator --- factor num to remove: " << factors_to_remove.size() << "\n";

    try
    {
        result = smoother.update(new_sub_factor_graph, new_sub_values, key_timestamp_map, factors_to_remove);
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "SlidingWindowEstimator --- caught exception "
                   << "from IncrementalFixedLagSmoother, exception is " << e.what() << ", vSLAM will be reset!!!";
        return false;
    }
    LOG(INFO) << "Smoother takes " << 1000.0 * timer.Elapsed() << " ms.\n";
    LOG(INFO) << "#iterations = " << result.getIterations() << std::endl;
    timer.Tic();

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::FactorIndices SlidingWindowEstimator::FindFactorsToRemove(const SlidingWindowState& state) const
{
    const auto& tracker_state = state.static_tracker_state;
    const auto& factor_graph  = state.static_smoother.getFactors();

    // 1. get outliers landmarks
    std::set<gtsam::Key> outlier_landmark_keys;

    for (const auto& track : tracker_state.tracks)
    {
        if (track.GetState() != FeatureTrack::State::BAD_AFTER_OPTIMIZATION ||
            track.NewestMeasurement().first != tracker_state.frame_id || !track.GetLandmark())
        {
            continue;
        }

        outlier_landmark_keys.emplace(L(track.GetLandmark()->Id()));
    }

    if (outlier_landmark_keys.empty())
    {
        return gtsam::FactorIndices();
    }

    // 2. find factors associated to outlier landmarks
    gtsam::FactorIndices factors_to_remove;
    gtsam::Key           current_pose_key = X(tracker_state.frame_id);

    for (size_t i = 0; i < factor_graph.size(); i++)
    {
        const FactorGraph::Base::sharedFactor& factor = factor_graph.at(i);

        if (const Unit3Factor* f = dynamic_cast<const Unit3Factor*>(&(*factor)))
        {
            if (f->keys()[0] != current_pose_key || !outlier_landmark_keys.count(f->keys()[1]))
            {
                continue;
            }

            factors_to_remove.push_back(i);
        }
    }

    return factors_to_remove;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t SlidingWindowEstimator::GetOldestFrameId(const uint64_t current_frame_id) const
{
    uint64_t oldest_frame_id = 0;

    // compute oldest frame id
    if (current_frame_id > parameters_.lag_size)
    {
        oldest_frame_id = current_frame_id - parameters_.lag_size;
    }

    return oldest_frame_id;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<gtsam::Point3, Scalar> SlidingWindowEstimator::GetXYZYaw(const gtsam::Pose3& pose) const
{
    const gtsam::Point3 xyz = pose.translation();
    const Scalar        yaw = pose.rotation().yaw();
    return std::make_pair(xyz, yaw);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Values SlidingWindowEstimator::CompensateXYZYaw(const gtsam::Point3& old_reference_xyz,
                                                       const gtsam::Point3& new_reference_xyz,
                                                       const gtsam::Rot3&   delta_rotation,
                                                       const uint64_t       oldest_frame_id,
                                                       const gtsam::Values& new_values) const
{
    gtsam::Values compensated_values;

    for (const gtsam::Key key : new_values.keys())
    {
        const gtsam::Symbol symbol(key);

        if (symbol.chr() == 'l' || symbol.chr() == 's' || symbol.chr() == 'p')
        {
            // do nothing
            continue;
        }

        if (symbol.index() < oldest_frame_id)
        {
            // the marginalization might be wrong
            std::stringstream ss;
            ss << "SlidingWindowEstimator --- the key: " << symbol.chr() << symbol.index()
               << " is smaller than the oldest frame: " << oldest_frame_id;
            LOG(ERROR) << ss.str();
            throw std::runtime_error(ss.str());
        }

        if (symbol.chr() == 'x')
        {
            const gtsam::Pose3  pose                 = (new_values.at(key)).cast<gtsam::Pose3>();
            const gtsam::Rot3   compensated_rotation = delta_rotation * pose.rotation();
            const gtsam::Point3 compensated_translation =
                old_reference_xyz + delta_rotation * (pose.translation() - new_reference_xyz);
            const gtsam::Pose3 compensated_pose(compensated_rotation, compensated_translation);
            compensated_values.insert(key, compensated_pose);
        }
        else if (symbol.chr() == 'v')
        {
            const gtsam::Vector3 velocity             = (new_values.at(key)).cast<gtsam::Vector3>();
            const gtsam::Vector3 compensated_velocity = (delta_rotation * gtsam::Point3(velocity)).vector();
            compensated_values.insert(key, compensated_velocity);
        }
        else if (symbol.chr() == 'b')
        {
            compensated_values.insert(key, new_values.at(key));
        }
    }

    return compensated_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Values SlidingWindowEstimator::Compensate6DoFInSlidingWindow(const gtsam::Pose3&  old_reference_pose,
                                                                    const gtsam::Pose3&  new_reference_pose,
                                                                    uint64_t             oldest_frame_id,
                                                                    const gtsam::Values& new_values) const
{
    gtsam::Values compensated_values;

    for (const gtsam::Key key : new_values.keys())
    {
        const gtsam::Symbol symbol(key);

        if (symbol.chr() == 'l' || symbol.chr() == 's' || symbol.chr() == 'p')
        {
            // do nothing
            continue;
        }

        if (symbol.index() < oldest_frame_id)
        {
            // the marginalization might be wrong
            std::stringstream ss;
            ss << "SlidingWindowEstimator --- the key: " << symbol.chr() << symbol.index()
               << " is smaller than the oldest frame: " << oldest_frame_id;
            LOG(ERROR) << ss.str();
            throw std::runtime_error(ss.str());
        }

        if (symbol.chr() == 'x')
        {
            const gtsam::Pose3 pose = (new_values.at(key)).cast<gtsam::Pose3>();
            const gtsam::Pose3 lTc  = new_reference_pose.inverse() * pose;
            compensated_values.insert(key, old_reference_pose * lTc);
        }
        else if (symbol.chr() == 'b')
        {
            compensated_values.insert(key, new_values.at(key));
        }
    }

    return compensated_values;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
