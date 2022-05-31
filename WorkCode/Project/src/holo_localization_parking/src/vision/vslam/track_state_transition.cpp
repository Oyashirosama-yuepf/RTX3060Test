/*!
 * \brief vslam track state transition
 * \author duyanwei@holomatic.com
 * \date April-15-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/track_state_transition.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TrackStateTransition::Parameters TrackStateTransition::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    uint64_t minimum_track_length           = 5;
    uint64_t maximum_candidate_track_length = 25;
    Scalar   triangulation_threshold        = 3.0;
    Scalar   tracking_threshold             = 4.0;
    Scalar   rejection_threshold            = 3.0;
    Scalar   minimum_disparity_angle        = 1.0;
    Scalar   maximum_landmark_distance      = 60.0;
    Scalar   minimum_landmark_distance      = 2.0;
    Scalar   minimum_triangulation_baseline = 0.5;

    if (!node.IsNull())
    {
        minimum_track_length           = node["minimum_track_length"].as<uint64_t>(5);
        maximum_candidate_track_length = node["maximum_candidate_track_length"].as<uint64_t>(25);
        triangulation_threshold        = node["triangulation_threshold"].as<Scalar>(3.0);
        tracking_threshold             = node["tracking_threshold"].as<Scalar>(4.0);
        rejection_threshold            = node["rejection_threshold"].as<Scalar>(3.0);
        minimum_disparity_angle        = node["minimum_disparity_angle"].as<Scalar>(1.0);
        maximum_landmark_distance      = node["maximum_landmark_distance"].as<Scalar>(60.0);
        minimum_landmark_distance      = node["minimum_landmark_distance"].as<Scalar>(2.0);
        minimum_triangulation_baseline = node["minimum_triangulation_baseline"].as<Scalar>(0.5);
    }

    // return parameters
    return Parameters(minimum_track_length, maximum_candidate_track_length, triangulation_threshold, tracking_threshold,
                      rejection_threshold, minimum_disparity_angle, maximum_landmark_distance,
                      minimum_landmark_distance, minimum_triangulation_baseline);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TrackStateTransition::Parameters TrackStateTransition::Parameters::Example()
{
    return Parameters(3, 5, 2.0, 10.0, 3.0, 1.0, 2000, 2.0, 0.5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TrackStateTransition::RunBeforeOptimization(State& state, const Values& values,
                                                 const boost::optional<FactorGraph>& old_factor_graph) const
{
    gtsam::VariableIndex old_variable_index;

    if (old_factor_graph)
    {
        old_variable_index.augment(*old_factor_graph);
    }

    // check all old tracks then transit track state
    for (auto& track : state.tracks)
    {
        // check broken tracks and transit broken tracks state to FINISHED
        if (IsTrackingBroken(track, state.frame_id))
        {
            track.UpdatingState(FeatureTrack::State::FINISHED);
            continue;
        }

        const FeatureTrack::State track_state = track.GetState();

        if (track_state == FeatureTrack::State::CANDIDATE)
        {
            if (track.Length() <= parameters_.maximum_candidate_track_length)
            {
                track = UpdateCandidateTrack(track, values);
            }
            else
            {
                // transit track state to BAD after triangulation failures
                track.UpdatingState(FeatureTrack::State::BAD_BEFORE_OPTIMIZATION);
            }

            continue;
        }

        if (track_state == FeatureTrack::State::FRESH)
        {
            track.UpdatingState(FeatureTrack::State::LIVE);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TrackStateTransition::RunAfterOptimization(State& state, const Values& values,
                                                const boost::optional<FactorGraph>& old_factor_graph) const
{
    gtsam::VariableIndex old_variable_index;

    if (old_factor_graph)
    {
        old_variable_index.augment(*old_factor_graph);
    }

    // check all old tracks
    for (auto& track : state.tracks)
    {
        const FeatureTrack::State track_state = track.GetState();

        if (!(track_state == FeatureTrack::State::LIVE || track_state == FeatureTrack::State::FRESH))
        {
            continue;
        }

        // get default error threshold
        const auto camera_index = track.NewestMeasurement().second.begin()->first;
        Scalar     threshold =
            pixel_error_threshold_to_unit3_error_threshold_.at(camera_index).at(parameters_.rejection_threshold);

        // compute adaptive_threshold for LIVE
        // for FRESH: 1. there is no factors in old_factor_graph
        //            2. it is only optimized one time, the adaptive_threshold is useless
        if (old_factor_graph && track_state == FeatureTrack::State::LIVE)
        {
            Scalar adaptive_threshold =
                ComputeTrackErrorThreshold(track, *old_factor_graph, old_variable_index, values);

            if (adaptive_threshold < threshold)
            {
                threshold = adaptive_threshold;
            }
        }

        if (CheckReprojectionError(track, values, threshold))
        {
            continue;
        }

        // transit track state to BAD_AFTER_OPTIMIZATION and emplace_back
        track.UpdatingState(FeatureTrack::State::BAD_AFTER_OPTIMIZATION);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scalar TrackStateTransition::ComputeTrackErrorThreshold(const FeatureTrack& track, const FactorGraph& old_factor_graph,
                                                        const gtsam::VariableIndex& old_variable_index,
                                                        const Values&               values) const
{
    const uint64_t landmark_id = (track.GetLandmark())->Id();
    gtsam::Key     landmark_key(L(landmark_id));
    Scalar         sum_square_error = 0.0;
    uint64_t       num_error        = 0;

    // compute sum of the error^2
    for (const uint64_t slot : old_variable_index[landmark_key])
    {
        const FactorGraph::Base::sharedFactor factor = old_factor_graph.at(slot);

        //@TODO holo to keep Unit3Factor and ProjectionFactor beeter
        if (const Unit3Factor* f = dynamic_cast<const Unit3Factor*>(&(*factor)))
        {
            const gtsam::Key& pose_key = f->keys()[0];

            // if the feature is tracked larger than slinding window size
            // the oldest pose might be marginalized so the values might not exist
            if (values.exists(pose_key))
            {
                const Scalar error = (f->unwhitenedError(values)).norm();
                sum_square_error += (error * error);
                num_error++;
            }
        }
        else if (const ProjectionFactor* f = dynamic_cast<const ProjectionFactor*>(&(*factor)))
        {
            const gtsam::Key& pose_key = f->keys()[0];

            // if the feature is tracked larger than slinding window size
            // the oldest pose might be marginalized so the values might not exist
            if (values.exists(pose_key))
            {
                const Scalar error = (f->unwhitenedError(values)).norm();
                sum_square_error += (error * error);
                num_error++;
            }
        }
    }

    if (num_error <= 1)
    {
        return parameters_.tracking_threshold;
    }

    // stdandard deviation
    Scalar error_sigma = std::sqrt(sum_square_error / (num_error - 1));

    // return 3*sigma as threshold
    return 3 * error_sigma;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TrackStateTransition::IsTrackingBroken(const FeatureTrack& track, const uint64_t frame_id) const
{
    return track.NewestMeasurement().first < frame_id;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TrackStateTransition::CheckReprojectionError(const FeatureTrack& track, const Values& values,
                                                  const Scalar threshold) const
{
    // get feature measurement
    const auto& m = track.NewestMeasurement();

    // get newest frame id
    const uint64_t frame_id = m.first;

    // loop for all observed camera
    for (const auto& camera_indexed_feature : m.second)
    {
        // get camera index and corresponding extrinsic
        const auto& camera_index = camera_indexed_feature.first;
        const auto& T_bc         = camera_parameters_->extrinsics.at(camera_index);
        const auto& feature      = camera_indexed_feature.second;

        // compute camera pose in vslam map frame
        const gtsam::Pose3 T_wc = GetCamPose(values, holo::localization::HoloGtsam::Convert(T_bc), frame_id);

        // compute landmark location
        if (!values.exists(L((track.GetLandmark())->Id())))
        {
            LOG(ERROR) << "TrackStateTransition --- given tracks dose NOT exist in valuse.\n";
            throw std::runtime_error("invalid input data.\n");
        }

        gtsam::Point3 landmark = values.at(L((track.GetLandmark())->Id())).cast<gtsam::Point3>();

        // transform landmark to camera coordinate
        const auto ptc = HoloGtsam::Convert(T_wc.inverse() * landmark);

        // check if behind camera
        const auto&  ray                                        = feature.normalized_point.ToVector();
        const Scalar angle_between_feature_ray_and_optical_axis = holo::Degree(std::acos(ray[2] / ray.GetNorm()));

        if (angle_between_feature_ray_and_optical_axis < 90.0 && ptc.GetZ() < 0)
        {
            // behind camera
            return false;
        }

        // create two vectors
        const gtsam::Unit3 p = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(ptc));
        const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(feature.normalized_point));

        // compute error
        if (p.errorVector(q).norm() > threshold)
        {
            return false;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Pose3 TrackStateTransition::GetCamPose(const Values& values, const gtsam::Pose3& T_bc,
                                              const uint64_t frame_id) const
{
    const gtsam::Pose3 T_mb = values.at(X(frame_id)).cast<gtsam::Pose3>();

    return T_mb * T_bc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TrackStateTransition::IsTrackReadyForTriangulation(const FeatureTrack& track, const Values& values) const
{
    // get newest observed ray direction and pose
    const auto newest_ray_direction_and_pose = GetRayDirectionAndPose(track.NewestMeasurement(), values);

    // retrieve first observed ray and pose
    const auto& first_one = newest_ray_direction_and_pose.at(0);

    // if newest measurement was observed by more than one camera, check threir baseline and disparity
    if (newest_ray_direction_and_pose.size() > 1)
    {
        // loop other observed ray and pose, if there exist any result has large baseline and disparity with first one,
        // we think this track can be triagulated.
        for (size_t i = 1; i < newest_ray_direction_and_pose.size(); i++)
        {
            const auto& second_one = newest_ray_direction_and_pose.at(i);
            if (IsGoodForTriangulation(first_one, second_one))
            {
                return true;
            }
        }
    }

    // if this function goes here, it means this track's newest measurement only observed by one camera.
    // so we check baseline and disparity between oldest and newest measurement
    const auto oldest_ray_direction_and_pose = GetRayDirectionAndPose(track.OldestMeasurement(), values);

    // loop all oldest observed ray and pose
    for (size_t i = 0; i < oldest_ray_direction_and_pose.size(); i++)
    {
        const auto& second_one = oldest_ray_direction_and_pose.at(i);
        if (IsGoodForTriangulation(first_one, second_one))
        {
            return true;
        }
    }

    // if this function goes here, it means this track wa not good enough for triangulation.
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TrackStateTransition::IsGoodForTriangulation(const ViewDirectionAndPose& first_observed_info,
                                                  const ViewDirectionAndPose& second_observed_info) const
{
    // check baseline
    if (first_observed_info.second.range(second_observed_info.second) < parameters_.minimum_triangulation_baseline)
    {
        return false;
    }

    // compute disparity
    const Scalar cos_disparity_angle = first_observed_info.first.dot(second_observed_info.first);

    // the disparity angle between two poses should larger than the angle threshold
    return cos_disparity_angle < std::cos(holo::Radian(parameters_.minimum_disparity_angle));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TrackStateTransition::ViewDirectionsAndPoses
TrackStateTransition::GetRayDirectionAndPose(const FeatureTrack::Measurement& measurement, const Values& values) const
{
    ViewDirectionsAndPoses result;
    result.reserve(measurement.second.size());
    const uint64_t& frame_id = measurement.first;

    for (const auto& camera_indexed_feature : measurement.second)
    {
        // get camera index and corresponding extrinsic
        const auto& camera_index = camera_indexed_feature.first;
        const auto& T_bc         = camera_parameters_->extrinsics.at(camera_index);

        // compute camera pose
        const gtsam::Pose3 camera_pose = GetCamPose(values, holo::localization::HoloGtsam::Convert(T_bc), frame_id);

        // compute observed ray direction
        const auto&          pt = camera_indexed_feature.second.normalized_point;
        const gtsam::Vector3 ray_in_cam(pt.GetX(), pt.GetY(), pt.GetZ());
        const gtsam::Unit3   ray_in_world = camera_pose.rotation().rotate(gtsam::Unit3(ray_in_cam));
        result.emplace_back(std::make_pair(ray_in_world.unitVector(), camera_pose));
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::TriangulationResult TrackStateTransition::Triangulation(const FeatureTrack& track, const Values& values) const
{
    // prepare data for triangulation
    gtsam::CameraSet<gtsam::SimpleCamera> cameras;
    gtsam::Point2Vector                   points;

    const uint64_t length = track.Length() - 1;
    cameras.reserve(camera_parameters_->camera_number * length);
    points.reserve(camera_parameters_->camera_number * length);

    for (uint64_t i = 0; i < length; i++)
    {
        const auto& m = track.Measurements(i);
        // get frame id
        const uint64_t frame_id = m.first;

        for (const auto& camera_indexed_feature : m.second)
        {
            // get camera index and corresponding feature
            const auto& camera_index = camera_indexed_feature.first;
            const auto& feature      = camera_indexed_feature.second;

            // get normalized point
            const gtsam::Point2 point(feature.normalized_point.GetX(), feature.normalized_point.GetY());
            points.emplace_back(point);

            // get extrinsic
            const auto& T_bc = camera_parameters_->extrinsics.at(camera_index);

            // compute camera pose in vslam map frame
            const gtsam::Pose3 T_mc = GetCamPose(values, holo::localization::HoloGtsam::Convert(T_bc), frame_id);

            // since feature point is already be unprojected to normalized plane, so the camera intrinsic matrix used
            // for triangulation should be Identity;
            cameras.emplace_back(T_mc, gtsam::Cal3_S2());
        }
    }

    // call triangulation, (load parameters in future, @yanwei)
    const static Scalar kRankTolerance = 1e-5;
    const static bool   kEnableEPI     = true;

    try
    {
        const auto ptw   = HoloGtsam::Convert(triangulatePoint3(cameras, points, kRankTolerance, kEnableEPI));
        Scalar     error = 0.0;

        // outliers rejection
        for (uint64_t i = 0; i < length; i++)
        {
            const auto&    m        = track.Measurements(i);
            const uint64_t frame_id = m.first;

            // traversal all observed camera
            for (const auto& camera_indexed_feature : m.second)
            {
                // get camera index and corresponding extrinsic
                const auto& feature      = camera_indexed_feature.second;
                const auto& camera_index = camera_indexed_feature.first;
                const auto& T_bc         = camera_parameters_->extrinsics.at(camera_index);

                // compute camera pose in vslam map frame
                const Pose3 T_wc =
                    HoloGtsam::Convert(GetCamPose(values, holo::localization::HoloGtsam::Convert(T_bc), frame_id));

                // transform point to observed camera frame
                const auto ptc      = T_wc.Inverse() * ptw;
                const auto distance = ptc.ToVector().GetNorm();

                // check if behind camera
                const auto&  ray = feature.normalized_point.ToVector();
                const Scalar angle_between_feature_ray_and_optical_axis =
                    holo::Degree(std::acos(ray[2] / ray.GetNorm()));

                if (angle_between_feature_ray_and_optical_axis < 90.0 && ptc.GetZ() < 0)
                {
                    return gtsam::TriangulationResult::BehindCamera();
                }

                // check distance
                if (distance < parameters_.minimum_landmark_distance)
                {
                    return gtsam::TriangulationResult::Outlier();
                }
                else if (distance > parameters_.maximum_landmark_distance)
                {
                    return gtsam::TriangulationResult::FarPoint();
                }

                // check residuals
                const gtsam::Unit3 p = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(ptc));
                const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(feature.normalized_point));
                error += p.errorVector(q).norm();
            }
        }

        const auto camera_index = track.OldestMeasurement().second.begin()->first;

        if (error / length >
            pixel_error_threshold_to_unit3_error_threshold_.at(camera_index).at(parameters_.triangulation_threshold))
        {
            return gtsam::TriangulationResult::Outlier();
        }

        return gtsam::TriangulationResult(HoloGtsam::Convert(ptw));
    }
    catch (const gtsam::CheiralityException& e)
    {
        LOG(WARNING) << "throw bad triangulated lanmark away !";
        return gtsam::TriangulationResult::Degenerate();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FeatureTrack TrackStateTransition::UpdateCandidateTrack(const FeatureTrack& track, const Values& values) const
{
    if (track.Length() >= parameters_.minimum_track_length && IsTrackReadyForTriangulation(track, values))
    {
        const auto result = Triangulation(track, values);

        if (result && result.valid())
        {
            return track.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH, *result);
        }
    }

    return track;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TrackStateTransition::IndexedPixelErrorToUnit3Error TrackStateTransition::UnifyErrorThreshold(
    const Parameters& parameters, const CameraParameters::Ptr camera_parameters) const
{
    IndexedPixelErrorToUnit3Error result;

    // traversal all camera
    for (uint16_t camera_index = 0; camera_index < camera_parameters->camera_number; camera_index++)
    {
        PixelErrorAtImageCenterToUnit3Error error_map;

        // retrieve camera intrinsic
        const auto& intrinsic = camera_parameters->intrinsics.at(camera_index);

        // convert pixel error threshold to unit3 error threshold
        // convert triangulation_threshold
        error_map.emplace(parameters_.triangulation_threshold,
                          CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
                              intrinsic, parameters.triangulation_threshold));

        // convert tracking_threshold
        error_map.emplace(
            parameters_.tracking_threshold,
            CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(intrinsic, parameters.tracking_threshold));

        // convert rejection_threshold
        error_map.emplace(
            parameters_.rejection_threshold,
            CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(intrinsic, parameters.rejection_threshold));

        // emplace to result
        result.emplace(camera_index, error_map);
    }
    return result;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
