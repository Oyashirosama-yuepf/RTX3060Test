/*!
 * \brief feature associator base class implementation file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date May-19-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/feature_associator.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FeatureAssociator::Parameters FeatureAssociator::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // tracker parameters
    const holo::yaml::Node    tracker_node   = node["tracker_params"];
    const Tracker::Parameters tracker_params = Tracker::Parameters::LoadFromYaml(tracker_node);

    // global descriptor matching parameters
    const holo::yaml::Node gdm_node = node["global_match_params"].as<holo::yaml::Node>(holo::yaml::Node());

    if (gdm_node.IsNull())
    {
        LOG(INFO) << "FeatureAssociator --- prebuilt map matching parameters are NOT provided!";
        return Parameters(tracker_params);
    }

    // descriptor matching parameters
    const Scalar window_size = gdm_node["window_size"].as<Scalar>(50);  ///< searched window size
    const Scalar descriptor_distance_threshold =
        gdm_node["descriptor_distance_threshold"].as<Scalar>(1.2);  ///< max descriptor distance
    const Scalar ratio_test_threshold = gdm_node["ratio_test_threshold"].as<Scalar>(
        0.8);  ///< threshold of ratio between smallest disatance and smaller distance
    const Scalar             view_distance_threshold  = gdm_node["view_distance_threshold"].as<Scalar>(3.0);
    const Scalar             view_direction_threshold = gdm_node["view_direction_threshold"].as<Scalar>(15.0);
    GlobalDescriptorMatching gdm(window_size, descriptor_distance_threshold, ratio_test_threshold,
                                 view_distance_threshold, view_direction_threshold);

    // combine all into parameters
    return Parameters(tracker_params, gdm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FeatureAssociator::Parameters FeatureAssociator::Parameters::Example()
{
    // return parameters
    return Parameters(Tracker::Parameters::Example());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FeatureAssociator::FeatureAssociator(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters)
  : parameters_(parameters)
  , camera_parameters_(camera_parameters)
  , tracker_(parameters_.tracker_params, camera_parameters)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureAssociator::Run(const Pose3& prior_T_wb, const Timestamp& new_timestamp, const uint64_t new_frame_id,
                            const std::vector<Features>& new_features, const MapPtr& visible_map,
                            Scalar global_map_matching_window_size, Tracker::State& tracker_state,
                            MapProjectionMeasurements& mpm) const
{
    holo::TicTocTimer timer;
    timer.Tic();

    if (!new_features.empty())
    {
        tracker_.Run(tracker_state, new_timestamp, new_frame_id, new_features);
    }
    else
    {
        LOG(INFO) << "FeatureAssociator --- input point features is empty. disable feature tracking.\n";
    }

    LOG(INFO) << "ExtendTracks takes " << 1e3 * timer.Elapsed() << " ms";

    timer.Tic();

    // Step 2: global map association
    if (!new_features.empty())
    {
        static std::vector<std::pair<Feature, MapPointPtr>> associated_features_and_mappoints;
        if (visible_map && !visible_map->empty())
        {
            for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
            {
                const auto predicted_camera_pose = prior_T_wb * camera_parameters_->extrinsics.at(camera_index);
                CreateMapProjectionFactorMeasurement(visible_map, new_features.at(camera_index), new_frame_id,
                                                     camera_parameters_->intrinsics.at(camera_index),
                                                     predicted_camera_pose, global_map_matching_window_size, mpm,
                                                     associated_features_and_mappoints);
                LOG(INFO) << "global matching result : mappoint number = " << visible_map->size()
                          << ", window_size = " << global_map_matching_window_size
                          << ",  match result number = " << mpm.size() << "\n";
            }
        }
        else if (!associated_features_and_mappoints.empty())
        {
            for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
            {
                TrackingAssociatedFeatures(new_features.at(camera_index), associated_features_and_mappoints);

                CreateMapProjectionFactorMeasurement(new_frame_id, camera_index,
                                                     camera_parameters_->intrinsics.at(camera_index),
                                                     associated_features_and_mappoints, mpm);
            }
        }
    }

    LOG(INFO) << "MapProjectionFacotrMeasurement number : " << mpm.size();

    LOG(INFO) << "CreateMapProjectionFactorMeasurement takes " << 1e3 * timer.Elapsed() << " ms";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureAssociator::TrackingAssociatedFeatures(
    const Features& new_features, std::vector<std::pair<Feature, MapPointPtr>>& associated_features_and_mappoints) const
{
    Features                 old_features;
    std::vector<MapPointPtr> old_mappoints;
    old_features.reserve(associated_features_and_mappoints.size());

    old_mappoints.reserve(associated_features_and_mappoints.size());

    for (const auto feature_and_mappoint : associated_features_and_mappoints)
    {
        old_features.emplace_back(feature_and_mappoint.first);
        old_mappoints.emplace_back(feature_and_mappoint.second);
    }

    holo::TicTocTimer timer;
    timer.Tic();
    const auto matched_pairs = DescriptorMatcher::FlowMatching(
        old_features, new_features, 2 * parameters_.tracker_params.fm.window_size,
        parameters_.tracker_params.fm.descriptor_dist_th, parameters_.tracker_params.fm.ratio_test_th);

    LOG(INFO) << "flow matching takes " << 1e3 * timer.Elapsed() << " ms";

    timer.Tic();
    // geometric consistency checking
    const auto inliers_index = tracker_.DoGeometricConsistencyCheck(old_features, new_features, matched_pairs);
    LOG(INFO) << "DoGeometricConsistencyCheck takes " << 1e3 * timer.Elapsed() << " ms";

    // update associated features and mappoints
    associated_features_and_mappoints.clear();

    for (const auto& inlier_index : inliers_index)
    {
        const auto& matched_pair = matched_pairs.at(inlier_index);

        associated_features_and_mappoints.emplace_back(new_features.at(matched_pair.second),
                                                       old_mappoints.at(matched_pair.first));
    }

    // VisualizeInterFrameTrackingResult(old_features, new_features, inliers_index, matched_pairs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureAssociator::VisualizeInterFrameTrackingResult(const Features& old_features, const Features& new_features,
                                                          const std::vector<uint16_t>&         inliers_index,
                                                          const DescriptorMatcher::MatchPairs& matched_pairs) const
{
    Features matched_old_features;
    Features matched_new_features;

    matched_old_features.reserve(inliers_index.size());
    matched_new_features.reserve(inliers_index.size());

    for (const auto& inlier_index : inliers_index)
    {
        const auto& matched_pair = matched_pairs.at(inlier_index);

        matched_old_features.emplace_back(old_features.at(matched_pair.first));
        matched_new_features.emplace_back(new_features.at(matched_pair.second));
    }

    uint16_t height = 1080, width = 1920;
    cv::Mat  img(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    // draw track position in current new_image
    for (size_t i = 0; i < matched_old_features.size(); ++i)
    {
        const auto matched_old_point = matched_old_features.at(i).image_point;
        const auto matched_new_point = matched_new_features.at(i).image_point;
        cv::circle(img, matched_old_point, 3, cv::Scalar(0, 0, 255));  // red
        cv::circle(img, matched_new_point, 3, cv::Scalar(0, 255, 0));  // green

        cv::line(img, matched_old_point, matched_new_point, cv::Scalar(255, 0, 0));  // blue
    }

    cv::namedWindow("frame between feature track", CV_WINDOW_NORMAL);

    cv::imshow("frame between feature track", img);

    cv::waitKey(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const FeatureAssociator::Parameters& FeatureAssociator::Params() const
{
    return parameters_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureAssociator::CreateMapProjectionFactorMeasurement(
    const uint64_t new_frame_id, const uint16_t camera_id, const IntrinsicBaseTypePtr& intrinsic,
    const std::vector<std::pair<Feature, MapPointPtr>>& associated_features_and_mappoints,
    MapProjectionMeasurements&                          result) const
{
    TicTocTimer timer;
    timer.Tic();

    result.reserve(result.size() + associated_features_and_mappoints.size());

    // retrieve 3d2d correspondences and get MapProjectionMeasurements
    for (const auto associated_feature_and_mappoint : associated_features_and_mappoints)
    {
        const auto& kpt          = associated_feature_and_mappoint.first.image_point;
        const auto& mappoint_ptr = associated_feature_and_mappoint.second;

        const auto pt = Point2(kpt.x, kpt.y);

        // unproject get bearing vector
        Point3 bearing;
        intrinsic->Unproject(pt, bearing);

        result.emplace_back(MapProjectionMeasurement(new_frame_id, camera_id, mappoint_ptr, bearing.ToVector()));
    }
    LOG(INFO) << "FeatureAssociator --- add map projection measurements takes : " << timer.Elapsed() * 1e3 << " ms";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureAssociator::CreateMapProjectionFactorMeasurement(
    const MapPtr& map, const Features& features, const uint64_t new_frame_id, const IntrinsicBaseTypePtr& intrinsic,
    const Pose3& T_wc, Scalar global_map_matching_window_size, MapProjectionMeasurements& result,
    std::vector<std::pair<Feature, MapPointPtr>>& matched_features_and_mappoints) const
{
    // check if features is valid
    if (map->empty() || features.empty() || !features.at(0).optional_descriptor)
    {
        return;
    }

    const GlobalDescriptorMatching& gdm = Params().gdm;

    TicTocTimer timer;
    timer.Tic();

    // mappoints to features matching
    const auto matchpairs = DescriptorMatcher::MappointsToFeaturesMatching(
        map, features, intrinsic, T_wc, global_map_matching_window_size, gdm.descriptor_distance_threshold,
        gdm.ratio_test_threshold, gdm.view_distance_threshold, gdm.view_direction_threshold,
        DescriptorMatcher::IsKernelInit());

    LOG(INFO) << "FeatureAssociator --- mappings to feature matching takes : " << timer.Elapsed() * 1e3 << " ms";
    timer.Tic();

    result.reserve(result.size() + matchpairs.size());

    matched_features_and_mappoints.clear();

    // retrieve 3d2d correspondences and get MapProjectionMeasurements
    for (uint16_t i = 0; i < matchpairs.size(); i++)
    {
        const uint64_t map_index    = matchpairs.at(i).first;
        const auto&    mappoint_ptr = map->at(map_index);

        const uint64_t    feature_index = matchpairs.at(i).second;
        const cv::Point2f kpt           = features.at(feature_index).image_point;

        const auto pt = Point2(kpt.x, kpt.y);

        // unproject get bearing vector
        Point3 bearing;
        intrinsic->Unproject(pt, bearing);

        result.emplace_back(
            MapProjectionMeasurement(new_frame_id, features.at(0).camera_id, mappoint_ptr, bearing.ToVector()));
        matched_features_and_mappoints.emplace_back(std::make_pair(features.at(feature_index), mappoint_ptr));
    }
    LOG(INFO) << "FeatureAssociator --- get map projection measurements takes : " << timer.Elapsed() * 1e3 << " ms";
}
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
