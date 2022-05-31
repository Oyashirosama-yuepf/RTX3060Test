/*!
 * \brief visual slam track triangulation
 * \author guopeikai@holomatic.com
 * \date Mar-5-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/triangulator.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Triangulator::Parameters Triangulator::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const uint64_t minimum_track_length           = node["minimum_track_length"].as<uint64_t>(3);
    const Scalar   max_acceptable_reproject_error = node["max_acceptable_reproject_error"].as<Scalar>(1.0);
    const Scalar   minimum_disparity_angle        = node["minimum_disparity_angle"].as<Scalar>(1.0);
    const Scalar   maximum_landmark_distance      = node["maximum_landmark_distance"].as<Scalar>(2000);
    const Scalar   minimum_landmark_distance      = node["minimum_landmark_distance"].as<Scalar>(2.0);
    const Scalar   minimum_triangulation_baseline = node["minimum_triangulation_baseline"].as<Scalar>(0.5);

    // return parameters
    return Parameters(minimum_track_length, max_acceptable_reproject_error, minimum_disparity_angle,
                      maximum_landmark_distance, minimum_landmark_distance, minimum_triangulation_baseline);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Triangulator::Parameters Triangulator::Parameters::Example()
{
    return Parameters(3, 2.0, 1.0, 2000, 2.0, 0.5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<Point3> Triangulator::Run(const FeatureTrack& track, const Values& values) const
{
    if (track.Length() >= parameters_.minimum_track_length && IsTrackReadyForTriangulation(track, values))
    {
        const auto result = Triangulation(track, values);

        if (result && result.valid())
        {
            return HoloGtsam::Convert(*result);
        }
    }
    return boost::none;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Pose3 Triangulator::GetCamPose(const Values& values, const gtsam::Pose3& T_bc, const uint64_t frame_id) const
{
    if (!values.exists(X(frame_id)))
    {
        LOG(ERROR) << "Triangulator --- frame id: " << frame_id << "is not existed in values.\n";
        std::runtime_error("Triangulator --- frame id is not existed in values.");
    }
    const gtsam::Pose3 T_mb = values.at(X(frame_id)).cast<gtsam::Pose3>();
    return T_mb * T_bc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Triangulator::IsTrackReadyForTriangulation(const FeatureTrack& track, const Values& values) const
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
bool Triangulator::IsGoodForTriangulation(const ViewDirectionAndPose& first_observed_info,
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
Triangulator::ViewDirectionsAndPoses Triangulator::GetRayDirectionAndPose(const FeatureTrack::Measurement& measurement,
                                                                          const Values&                    values) const
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
gtsam::TriangulationResult Triangulator::Triangulation(const FeatureTrack& track, const Values& values) const
{
    // prepare data for triangulation
    gtsam::CameraSet<gtsam::SimpleCamera> cameras;
    gtsam::Point2Vector                   points;

    const uint64_t length = track.Length();
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
        const auto          ptw = HoloGtsam::Convert(triangulatePoint3(cameras, points, kRankTolerance, kEnableEPI));
        Scalar              threshold = 4.0;
        std::vector<Scalar> measurement_errors;

        // outliers rejection
        for (uint64_t i = 0; i < length; i++)
        {
            const auto&    m        = track.Measurements(i);
            const uint64_t frame_id = m.first;

            // traversal all observed camera
            for (const auto& camera_indexed_feature : m.second)
            {
                // get camera index and corresponding extrinsic
                const auto& feature          = camera_indexed_feature.second;
                const auto& camera_index     = camera_indexed_feature.first;
                const auto& T_bc             = camera_parameters_->extrinsics.at(camera_index);
                const auto& camera_intrinsic = camera_parameters_->intrinsics.at(camera_index);

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

                // compute reprojection error for later check
                Point2d pt_projected;
                camera_intrinsic->Project(ptc, pt_projected);
                const auto& pt_measurment = feature.image_point;
                Vector2d    pt1           = pt_projected.ToVector();
                Vector2d    pt2(pt_measurment.x, pt_measurment.y);
                Vector2d    error(pt1 - pt2);

                measurement_errors.emplace_back(error.GetNorm());
            }
        }

        // check if mean reprojection error exceed threshold
        if ((std::accumulate(measurement_errors.begin(), measurement_errors.end(), 0.0) / measurement_errors.size()) >
            threshold)
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

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo