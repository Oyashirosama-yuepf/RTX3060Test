/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_slot_fusion.cpp
 * @brief This cpp file parking slot main pipeline
 * @author Feng. Li lifeng@holomatic.com
 * @author Changxi. Cheng chengchangxi@holomatic.com
 * @date 2021-11-04
 */

#include <holo/3d/common/io.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_fusion.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
gtsam::IncrementalFixedLagSmoother ParkingSlotFusion::PSFusionSlidingWindowState::static_smoother =
    gtsam::IncrementalFixedLagSmoother();
DataAssociation::State ParkingSlotFusion::PSFusionSlidingWindowState::static_semantic_state = DataAssociation::State();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotFusion::Parameters ParkingSlotFusion::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    Parameters parameters;
    parameters.frequency = node["psf_frequency"].as<Scalar>(5);
    parameters.da_params = DataAssociation::Parameters::LoadFromYaml(node["sda_params"]);

    const holo::yaml::Node smoother_node = node["smoother_params"];
    parameters.lag_size                  = smoother_node["lag_size"].as<Scalar>(10);

    const holo::yaml::Node builder_node = node["builder_params"];
    /// sigma for vertex factor
    {
        const holo::yaml::Node sigma_node =
            builder_node["vertex_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        parameters.vertex_factor_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        parameters.vertex_factor_sigma(1) = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        parameters.vertex_factor_sigma(2) = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
    }

    /// sigma for plane factor
    {
        const holo::yaml::Node sigma_node = builder_node["plane_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        parameters.plane_factor_sigma(0)  = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        parameters.plane_factor_sigma(1)  = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        parameters.plane_factor_sigma(2)  = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
    }

    /// sigma for point plane factor
    {
        const holo::yaml::Node sigma_node =
            builder_node["point_plane_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        parameters.point_plane_factor_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
    }

    /// sigma for parallel factor
    {
        const holo::yaml::Node sigma_node =
            builder_node["parallel_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        parameters.parallel_factor_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        parameters.parallel_factor_sigma(1) = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        parameters.parallel_factor_sigma(2) = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
    }
    /// sigma for prior pose factor
    {
        const holo::yaml::Node sigma_node = builder_node["prior_pose_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        parameters.prior_pose_sigma(0)    = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        parameters.prior_pose_sigma(1)    = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        parameters.prior_pose_sigma(2)    = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
        parameters.prior_pose_sigma(3)    = sigma_node.IsNull() ? 1e-3 : sigma_node[3].as<Scalar>();
        parameters.prior_pose_sigma(4)    = sigma_node.IsNull() ? 1e-3 : sigma_node[4].as<Scalar>();
        parameters.prior_pose_sigma(5)    = sigma_node.IsNull() ? 4e-4 : sigma_node[5].as<Scalar>();
    }

    /// sigma for pose3 between factor
    {
        const holo::yaml::Node sigma_node =
            builder_node["pose3_between_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        parameters.pose3_between_factor_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        parameters.pose3_between_factor_sigma(1) = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        parameters.pose3_between_factor_sigma(2) = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
        parameters.pose3_between_factor_sigma(3) = sigma_node.IsNull() ? 1e-3 : sigma_node[3].as<Scalar>();
        parameters.pose3_between_factor_sigma(4) = sigma_node.IsNull() ? 1e-3 : sigma_node[4].as<Scalar>();
        parameters.pose3_between_factor_sigma(5) = sigma_node.IsNull() ? 4e-4 : sigma_node[5].as<Scalar>();
    }

    parameters.enable_slot_tracking     = node["enable_slot_tracking"].as<bool>(true);
    parameters.enable_slot_optimization = node["enable_slot_optimization"].as<bool>(false);

    return parameters;
}

Pose3 ParkingSlotFusion::PSFusionSlidingWindowState::GetNewestPose() const
{
    if (!values.exists(X(frame_id)))
    {
        std::stringstream ss;
        ss << "VehicleState does NOT exist: query index = " << frame_id;
        LOG(ERROR) << ss.str();
        throw std::runtime_error(ss.str());
    }

    return HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotFusion::ParkingSlotFusion(const Parameters& parameters)
  : parameters_(parameters)
  , measurement_manager_(std::make_shared<PSFusionMeasurementManager>())
  , associator_(parameters.da_params)
  , sliding_window_state_()
  , new_frame_id_(0)
  , estimation_core_iteration_counter_(0)
  , is_estimation_core_work_well_(false)
{
    // start main thread
    estimator_thread_ = std::make_shared<std::thread>(
        std::bind(&ParkingSlotFusion::threadFunc, this, std::placeholders::_1), parameters_.frequency);
    pthread_setname_np(estimator_thread_->native_handle(), "VslamParkingSlotEstimatorThread");
    state_ = State::READY;

    // optimize by batch fix lag smoother
    gtsam::ISAM2Params isam2_params;
    isam2_params.enablePartialRelinearizationCheck = false;
    isam2_params.findUnusedFactorSlots             = true;

    sliding_window_state_.static_smoother       = gtsam::IncrementalFixedLagSmoother(parameters.lag_size, isam2_params);
    sliding_window_state_.static_semantic_state = DataAssociation::State();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotFusion::~ParkingSlotFusion()
{
    if (!optimized_slot_map_.empty())
    {
        PointCloudXYZIRRgbSt optimized_slot_map =
            semantic::Utility::ConvertToPointCloud(optimized_slot_map_, trajectory_);
        holo::pointcloud::SavePly("./slot_map.ply", optimized_slot_map);
    }

    if (estimator_thread_)
    {
        estimator_thread_->join();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParkingSlotFusion::Stop()
{
    // user requesting stop mapping thread.
    LOG(INFO) << "ParkingSlotFusion --- Received a STOP request. we will really stop this mapping thread after "
                 "processing all remaining images. wait a moment ...";

    Base::Stop();

    LOG(INFO) << "ParkingSlotFusion --- stop online mapping thread done.";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParkingSlotFusion::run()
{
    is_estimation_core_work_well_ = false;
    LOG(INFO) << "Start interation = " << estimation_core_iteration_counter_;
    timer_.Tic();

    TicTocTimer timer_step;
    timer_step.Tic();

    // step1: get raw measurements
    if (!measurement_manager_->GetPSFusionRawMeasurement(new_raw_measurement_))
    {
        LOG(INFO) << "ParkingSlotFusion --- could not get raw measurements.\n";
        return;
    }
    LOG(INFO) << "It takes " << 1e3 * timer_step.Elapsed() << "ms to get raw measurement";
    frame_id_to_poses_.emplace(new_frame_id_, new_raw_measurement_.prior_pose);

    // step2: semantic data association
    LOG(INFO) << "Start data association.";
    timer_step.Tic();
    associator_.Run(sliding_window_state_.static_semantic_state, new_raw_measurement_.parking_slot_frame,
                    new_raw_measurement_.prior_pose, new_frame_id_);
    LOG(INFO) << "Done data association, takes " << 1e3 * timer_step.Elapsed() << "ms";

    if (parameters_.enable_slot_optimization)
    {
        // step3: build factor graph
        LOG(INFO) << "Start build factor graph.";
        timer_step.Tic();
        const auto new_sub_problem =
            addSemanticFactors(sliding_window_state_.static_semantic_state,
                               HoloGtsam::Convert(new_raw_measurement_.prior_pose), new_frame_id_);
        LOG(INFO) << "Done build factor graph, takes " << 1e3 * timer_step.Elapsed() << "ms";

        // step4: optimize by fix lag smoother
        LOG(INFO) << "Start sliding window estimation";
        timer_step.Tic();
        if (!optimization(sliding_window_state_.static_smoother, new_sub_problem, new_frame_id_))
        {
            // reset_flags_.is_exception = true;
            LOG(INFO) << "PSFusion --- exception from gtsam catched. reset system!\n";
            throw std::runtime_error("smoother update failed.");
        }
        LOG(INFO) << "Done optimization, takes " << 1e3 * timer_step.Elapsed() << "ms";

        // step5: update values, timestamp, frame id
        LOG(INFO) << "Start update sliding window state";
        timer_step.Tic();
        sliding_window_state_.values = sliding_window_state_.static_smoother.calculateEstimate();
    }

    sliding_window_state_.frame_id  = new_frame_id_;
    sliding_window_state_.timestamp = new_raw_measurement_.newest_timestamp;
    LOG(INFO) << "Done update sliding window state, takes " << 1e3 * timer_step.Elapsed() << "ms";

    last_raw_measurement_ = new_raw_measurement_;

    is_estimation_core_work_well_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t ParkingSlotFusion::postProcess()
{
    // if estimation core not work well, do nothing
    if (!is_estimation_core_work_well_)
    {
        LOG(WARNING) << "PSFusion --- something wrong happened in EstimationCore.\n\n\n";
        return false;
    }

    TicTocTimer timer_step;
    timer_step.Tic();
    // update global slot map
    LOG(INFO) << "Start update global slot map";
    updateGlobalSlotMap(sliding_window_state_);
    LOG(INFO) << "Done update global slot map takes " << 1e3 * timer_step.Elapsed() << " ms";
    timer_step.Tic();

    LOG(INFO) << "Start publish global slot map";
    publishGlobalSlotMap(sliding_window_state_);
    LOG(INFO) << "Done publish global slot map takes " << 1e3 * timer_step.Elapsed() << " ms";

    // if disbale slot tracking, clear all tracks
    if (!parameters_.enable_slot_tracking)
    {
        sliding_window_state_.static_semantic_state.tracks.clear();
    }

    // update frame id
    new_frame_id_++;
    LOG(INFO) << "The Whole Estimation takes " << 1e3 * timer_.Elapsed() << " ms";
    LOG(INFO) << "Done interation = " << estimation_core_iteration_counter_++ << "\n\n\n";

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotFusion::Problem ParkingSlotFusion::addSemanticFactors(const DataAssociation::State& semantic_state,
                                                                 const gtsam::Pose3&           wTb,
                                                                 const int64_t&                frame_index) const
{
    FactorGraph new_factor_graph;
    Values      new_sub_values;
    // @todo define it in parameters
    const gtsam::SharedNoiseModel vertex_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.vertex_factor_sigma));
    const gtsam::SharedGaussian plane_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.plane_factor_sigma));
    const gtsam::SharedNoiseModel point_plane_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector1(parameters_.point_plane_factor_sigma[0]));
    const gtsam::SharedNoiseModel parallel_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.parallel_factor_sigma));
    const gtsam::SharedNoiseModel prior_pose_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.prior_pose_sigma));
    // const gtsam::SharedNoiseModel pose3_between_factor_sigma =
    //     gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.pose3_between_factor_sigma));

    // add new plane to values
    const auto& current_plane_id = semantic_state.current_plane_id;

    if (current_plane_id >= 0 && !sliding_window_state_.values.exists(P(current_plane_id)))
    {
        const auto& plane = semantic_state.plane_id_to_plane.at(current_plane_id);
        new_sub_values.insert(P(current_plane_id), plane.data);

        // add pose prior factor
        new_sub_values.insert(X(frame_index), wTb);
        new_factor_graph.emplace_shared<PosePriorFactor>(X(frame_index), wTb, prior_pose_noise);

        // add plane factor
        new_factor_graph.emplace_shared<gtsam::OrientedPlane3Factor>(plane.data.planeCoefficients(), plane_factor_noise,
                                                                     X(frame_index), P(current_plane_id));
    }

    // loop over the tracks
    for (const auto& track : semantic_state.tracks)
    {
        const auto& state = track.state;
        if (frame_index != track.frame_id || state == ParkingSlotTrack::State::CANDIDATE)
        {
            continue;
        }

        // add initial values for FRESH tracks
        if (state == semantic::ParkingSlotTrack::State::FRESH)
        {
            const auto vertices = track.GetIndexedVertices(0);
            for (const auto& vertex : vertices)
            {
                const gtsam::Point3 measured = HoloGtsam::Convert(vertex.point);
                new_sub_values.insert(S(vertex.id), wTb * measured);

                // add point to plane factor
                if (track.plane_id < 0)
                {
                    continue;
                }

                new_factor_graph.emplace_shared<semantic::ParkingSlotPointPlaneFactor>(S(vertex.id), P(track.plane_id),
                                                                                       point_plane_factor_noise);
            }

            // add parallel factor
            if (vertices.size() >= 4u)  // @todo is it appropriate to put this judgement here ???
            {
                new_factor_graph.emplace_shared<semantic::ParkingSlotParallelFactor>(
                    S(vertices[0].id), S(vertices[1].id), S(vertices[2].id), S(vertices[3].id), parallel_factor_noise);
                new_factor_graph.emplace_shared<semantic::ParkingSlotParallelFactor>(
                    S(vertices[1].id), S(vertices[2].id), S(vertices[3].id), S(vertices[0].id), parallel_factor_noise);
            }
        }

        // add vertex factor
        for (size_t i = 0; i < track.measurements.size(); i++)
        {
            if (state == semantic::ParkingSlotTrack::State::LIVE && i != track.measurements.size() - 1)
            {
                continue;
            }

            const auto vertices = track.GetIndexedVertices(i);

            for (const auto& vertex : vertices)
            {
                const gtsam::Point3 measured = HoloGtsam::Convert(vertex.point);

                new_factor_graph.emplace_shared<semantic::PointOnlySlotVertexFactor>(S(vertex.id), wTb, measured,
                                                                                     vertex_factor_noise);
            }
        }
    }

    return Problem(new_factor_graph, new_sub_values);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t ParkingSlotFusion::optimization(gtsam::IncrementalFixedLagSmoother& smoother, const Problem& new_sub_problem,
                                       const uint64_t new_frame_id, const gtsam::FactorIndices& factors_to_remove) const
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

            if (symbol.chr() == 's')
            {
                key_timestamp_map[key] = timestamp;
            }
            else if (symbol.chr() == 'x')
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
                   << "from IncrementalFixedLagSmoother, exception is " << e.what()
                   << ", Parking Slot fusion will be reset!!!";
        return false;
    }
    LOG(INFO) << "Smoother takes " << 1000.0 * timer.Elapsed() << " ms.\n";
    LOG(INFO) << "#iterations = " << result.getIterations() << std::endl;
    timer.Tic();

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParkingSlotFusion::updateGlobalSlotMap(PSFusionSlidingWindowState& new_state)
{
    auto track_iter = new_state.static_semantic_state.tracks.begin();
    while (track_iter != new_state.static_semantic_state.tracks.end())
    {
        if (track_iter->state == ParkingSlotTrack::State::FRESH)
        {
            track_iter->state = ParkingSlotTrack::State::LIVE;
        }

        if (track_iter->frame_id + parameters_.lag_size <= new_state.frame_id)
        {
            track_iter = new_state.static_semantic_state.tracks.erase(track_iter);
            continue;
        }

        if (parameters_.enable_slot_optimization)
        {
            auto out = track_iter->GetOptimizedParkingSlot(new_state.values);

            if (out)
            {
                optimized_slot_map_[track_iter->id] = *out;
                track_iter->optimized_parking_slot  = *out;
            }
            else if (track_iter->state == semantic::ParkingSlotTrack::State::CANDIDATE)
            {
                const auto& slot_in_body           = track_iter->measurements.front().second.second;
                const auto& wTb                    = frame_id_to_poses_.at(new_frame_id_);
                track_iter->optimized_parking_slot = Utility::TransformParkingSlot(slot_in_body, wTb);
            }
        }
        else
        {
            const auto& slot_in_body            = track_iter->measurements.back().second.second;
            const auto& frame_id                = track_iter->measurements.back().first;
            const auto& wTb                     = frame_id_to_poses_.at(frame_id);
            track_iter->optimized_parking_slot  = Utility::TransformParkingSlot(slot_in_body, wTb);
            optimized_slot_map_[track_iter->id] = track_iter->optimized_parking_slot;
        }

        track_iter++;
    }

    trajectory_.emplace_back(frame_id_to_poses_.at(new_frame_id_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParkingSlotFusion::publishGlobalSlotMap(const PSFusionSlidingWindowState& new_state)
{
    // publish parking slot frame
    if (output_global_parking_slot_frame_callback_)
    {
        // @todo Coordinate: it should be in navigation frame (a global frame)
        ParkingSlotFrameType frame(new_state.timestamp, common::Coordinate::UNKNOWN);

        for (const auto& track : new_state.static_semantic_state.tracks)
        {
            // auto out_w = track.GetOptimizedParkingSlot(new_state.values);
            // if (out_w)
            // {
            //     frame.emplace_back(*out_w);
            // }
            frame.emplace_back(track.optimized_parking_slot);
        }
        output_global_parking_slot_frame_callback_(frame);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotType ParkingSlotFusion::ConvertFromGlobalToBody(const Pose3& bTw, const ParkingSlotType& in) const
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
bool_t ParkingSlotFusion::ProcessParkingSlotFrame(const ParkingSlotFrameType& measurement)
{
    if (state_ < State::READY)
    {
        return false;
    }
    measurement_manager_->AddMeasurement(measurement);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t ParkingSlotFusion::ProcessPriorOdometry(const Odometry& measurement)
{
    if (state_ < State::READY)
    {
        return false;
    }
    measurement_manager_->AddMeasurement(measurement);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t ParkingSlotFusion::SetOutputGlobalParkingSlotFrameCallback(const OutputParkingSlotFrameCallback& cb)
{
    output_global_parking_slot_frame_callback_ = cb;
    return 1;
}

}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
