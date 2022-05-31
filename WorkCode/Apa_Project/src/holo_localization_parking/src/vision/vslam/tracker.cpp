/*!
 * \brief implementation of vslam tracker class
 * \author Yanwei. Du duyanwei@holomatic.com
 * \author Feng. Li lifeng@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/tracker.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Tracker::Parameters Tracker::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // flow matching parameters
    const Scalar       fm_window_size        = node["fm_window_size"].as<Scalar>(80.0);
    const Scalar       fm_descriptor_dist_th = node["fm_descriptor_dist_th"].as<Scalar>(0.8);
    const Scalar       fm_ratio_test_th      = node["fm_ratio_test_th"].as<Scalar>(1.0);
    const bool         fm_cross_check        = node["fm_cross_check"].as<bool>(false);
    const FlowMatching fm(fm_window_size, fm_descriptor_dist_th, fm_ratio_test_th, fm_cross_check);

    // tracking_algorithm
    const std::string tracking_algorithm = node["tracking_algorithm"].as<std::string>("DescriptorMatching");

    // ransac fundamental matrix parameters
    const Scalar confidence          = node["confidence"].as<Scalar>(0.95);
    const Scalar pixel_tolerance     = node["pixel_tolerance"].as<Scalar>(4.0);
    const Scalar max_iterations      = node["max_iterations"].as<Scalar>(20);
    const bool   enable_optimization = node["enable_optimization"].as<bool>(true);

    return Parameters(fm, tracking_algorithm,
                      RansacFMParameters(confidence, pixel_tolerance, max_iterations, enable_optimization));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Tracker::Parameters Tracker::Parameters::Example()
{
    return Parameters(vslam::Tracker::Parameters::FlowMatching(), "DescriptorMatching");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tracker::Run(State& tracker_state, const Timestamp& new_timestamp, const uint64_t new_frame_id,
                  const std::vector<Features>& new_multi_camera_features) const
{
    if (parameters_.tracking_algorithm == "DescriptorMatching")
    {
        if (new_multi_camera_features.empty())
        {
            throw std::runtime_error("Tracker --- request matching with descriptor while do NOT give features.\n");
        }

        RunWithDescriptor(tracker_state, new_multi_camera_features, new_frame_id);
    }
    else if (parameters_.tracking_algorithm == "NONE")
    {
        LOG(INFO) << "Tracker --- Disabale local feature tracking, do nothing for this module.\n";
    }
    else
    {
        std::stringstream ss;
        ss << "Tracker --- Unsupported tracking algorithm: " << parameters_.tracking_algorithm << "\n";
        throw std::runtime_error(ss.str());
    }

    tracker_state.frame_id  = new_frame_id;
    tracker_state.timestamp = new_timestamp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tracker::RunWithDescriptor(State& tracker_state, const std::vector<Features>& new_multi_camera_features,
                                const uint64_t new_frame_id) const
{
    for (size_t camera_index = 0; camera_index < new_multi_camera_features.size(); camera_index++)
    {
        // retrieve new features to be tracked
        const auto& new_features = new_multi_camera_features.at(camera_index);

        // old features to be tracked
        std::vector<uint16_t> old_features_index;      // old feature's index in sliding window tracks
        Features              original_old_features;   // the original old features
        Features              predicted_old_features;  // old features with predicted 2d point
        const auto            old_frame_id = tracker_state.frame_id;

        for (uint64_t i = 0; i < tracker_state.tracks.size(); i++)
        {
            // check if this track's newest observed frame id equal to current frame id and track state is CANDIDATE,
            // FRESH or LIVE, and is observed by given camera
            const auto& track = tracker_state.tracks.at(i);
            const auto& m     = track.NewestMeasurement();

            if (m.first == old_frame_id && track.GetState() < FeatureTrack::State::FINISHED &&
                m.second.count(camera_index))
            {
                // mark old_features' index in the feature track vector;
                old_features_index.push_back(i);

                // predict old_features' position in current image
                const auto& old_feature = m.second.at(camera_index);
                original_old_features.push_back(old_feature);
                const auto predicted_pt = track.PredictNewPoints().at(camera_index);
                predicted_old_features.push_back(Feature(predicted_pt, old_feature.optional_descriptor));
            }
        }

        holo::TicTocTimer timer;
        timer.Tic();
        // matching old features with flow matching method
        const auto matched_pairs =
            DescriptorMatcher::FlowMatching(predicted_old_features, new_features, parameters_.fm.window_size,
                                            parameters_.fm.descriptor_dist_th, parameters_.fm.ratio_test_th);
        LOG(INFO) << "flow matching takes " << 1e3 * timer.Elapsed() << " ms";

        timer.Tic();
        // geometric consistency checking
        const auto inliers_index = DoGeometricConsistencyCheck(original_old_features, new_features, matched_pairs);
        LOG(INFO) << "DoGeometricConsistencyCheck takes " << 1e3 * timer.Elapsed() << " ms";

        // update old tracks
        std::unordered_set<uint16_t> filtered_new_feature_index;

        for (const auto& inlier_index : inliers_index)
        {
            const auto& matched_pair = matched_pairs.at(inlier_index);
            auto&       old_track    = tracker_state.tracks.at(old_features_index.at(matched_pair.first));
            old_track.AddNewestMeasurement(new_frame_id, new_features.at(matched_pair.second));
            filtered_new_feature_index.emplace(matched_pair.second);
        }

        // create new tracks
        tracker_state.tracks.reserve(tracker_state.tracks.size() +
                                     (new_features.size() - filtered_new_feature_index.size()));

        for (size_t i = 0; i < new_features.size(); i++)
        {
            if (filtered_new_feature_index.count(i))
            {
                continue;
            }

            FeatureTrack::CameraIndexedFeature camera_indexed_feature;
            camera_indexed_feature.emplace(camera_index, new_features.at(i));
            tracker_state.tracks.emplace_back(
                FeatureTrack::CreateNewTrack(parameters_.track_params, camera_parameters_,
                                             FeatureTrack::Measurement(new_frame_id, camera_indexed_feature)));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<uint16_t> Tracker::DoGeometricConsistencyCheck(const Features& last_features, const Features& curr_features,
                                                           const DescriptorMatcher::MatchPairs& matched_pairs) const
{
    LOG(INFO) << "DoGeometricConsistencyCheck --- last features nubmer : " << last_features.size()
              << ", current features number : " << curr_features.size()
              << ", matched pairs number : " << matched_pairs.size();

    std::vector<uint16_t> inliers_index;

    // If we have less than 9 newly tracked points, ransac does not help. Considering the 7-point method and the
    // 8-point method, take a larger value.
    if (matched_pairs.size() < 9)
    {
        inliers_index.reserve(matched_pairs.size());

        for (size_t i = 0; i < matched_pairs.size(); i++)
        {
            inliers_index.emplace_back(i);
        }

        return inliers_index;
    }

    // mark index of original matched pairs
    std::vector<uint16_t> index_of_matched_pairs;
    index_of_matched_pairs.reserve(matched_pairs.size());

    // prepare ransanc data
    std::vector<Point2> old_points;
    std::vector<Point2> new_points;
    old_points.reserve(matched_pairs.size());
    new_points.reserve(matched_pairs.size());

    for (size_t i = 0; i < matched_pairs.size(); i++)
    {
        index_of_matched_pairs.emplace_back(i);
        const auto& pair = matched_pairs.at(i);

        const auto& old_pt = last_features.at(pair.first).image_point;
        old_points.emplace_back(old_pt.x, old_pt.y);

        const auto& new_pt = curr_features.at(pair.second).image_point;
        new_points.emplace_back(new_pt.x, new_pt.y);
    }

    AdapterType                  left_hand_side(old_points);
    AdapterType                  right_hand_side(new_points);
    std::shared_ptr<ProblemType> problem(new ProblemType(left_hand_side, right_hand_side, MethodType::FM_8POINT,
                                                         parameters_.ransac_params.enable_optimization));

    // Check epipolar constraint.
    const static RansacParameters kRansacParams(parameters_.ransac_params.pixel_tolerance,
                                                parameters_.ransac_params.confidence,
                                                parameters_.ransac_params.max_iterations);
    RansacType                    ransac(problem, kRansacParams);

    if (!ransac.Compute())
    {
        LOG(WARNING) << "Tracker --- Failed to compute Fundamental Matrix";
        return std::vector<uint16_t>();
    }

    const auto inlier_indices = ransac.GetInliers();

    for (const auto& inlier : inlier_indices)
    {
        inliers_index.push_back(static_cast<uint16_t>(inlier));
    }

    return inliers_index;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
