/*!
 * \brief feature associator base class header file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date May-19-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_FEATURE_ASSOCIATOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_FEATURE_ASSOCIATOR_H_

#include <holo/localization/vision/vslam/sliding_window_state.h>
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
/**
 * @ingroup localization
 * @brief feature associator class
 *
 * @details this class is mainly responsible for visual fature association in vslam system.
 *          1. local feature tracks tracking(frame to frame and/or frame to local map build in sliding window).
 *          2. global map matching if given(frame to global map).
 */

class FeatureAssociator
{
public:
    /**
     * @brief define global descriptor matching parameters
     */
    struct GlobalDescriptorMatching
    {
        /// @brief searched window size
        const Scalar window_size;

        /// @brief max descriptor distance
        const Scalar descriptor_distance_threshold;

        /// @brief threshold of ratio between smallest disatance and smaller distance
        const Scalar ratio_test_threshold;

        /// @brief max distance between mappoint's reference pose and query camera pose. in meter
        const Scalar view_distance_threshold;

        /// @brief max angle of view direction between mappoints and features. in degree
        const Scalar view_direction_threshold;

        /**
         * @brief Construct a new Global Descriptor Matching object
         *
         * @param _window_size searched window size
         * @param _descriptor_distance_threshold max descriptor distance
         * @param _ratio_test_threshold threshold of ratio between smallest disatance and smaller distance
         * @param _view_distance_threshold max distance between mappoint's reference pose and query camera pose
         * @param _view_direction_threshold max angle of view direction between mappoints and features
         */
        GlobalDescriptorMatching(const Scalar _window_size = 50.0, const Scalar _descriptor_distance_threshold = 1.2,
                                 const Scalar _ratio_test_threshold = 0.8, const Scalar _view_distance_threshold = 3.0,
                                 const Scalar _view_direction_threshold = 15.0)
          : window_size(_window_size)
          , descriptor_distance_threshold(_descriptor_distance_threshold)
          , ratio_test_threshold(_ratio_test_threshold)
          , view_distance_threshold(_view_distance_threshold)
          , view_direction_threshold(_view_direction_threshold)
        {
        }

        /**
         * @brief output stream for GlobalDescriptorMatching
         *
         * @param os std::ostream&
         * @param gdm GlobalDescriptorMatching
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const GlobalDescriptorMatching& gdm)
        {
            os << "GlobalDescriptorMatchingParams:"
               << "\n window_size = " << gdm.window_size
               << "\n descriptor_distance_threshold = " << gdm.descriptor_distance_threshold
               << "\n ratio_test_threshold = " << gdm.ratio_test_threshold
               << "\n view_distance_threshold = " << gdm.view_distance_threshold
               << "\n view_direction_threshold = " << gdm.view_direction_threshold << std::endl;
            return os;
        }
    };

    /**
     * @brief define parameters
     *
     * @details it defines all the parameters governed by estimator, as well as
     *          the parameters of algorithm classes created by the estimator
     */
    struct Parameters
    {
        /// @brief define tracker parameters
        const Tracker::Parameters tracker_params;

        /// @brief define global descriptor matching parameters
        const GlobalDescriptorMatching gdm;

        /**
         * @brief Construct a new Parameters object
         *
         * @param _tracker_params tracker parameters
         * @param _gdm global descriptor matching parameters
         */
        Parameters(const Tracker::Parameters&      _tracker_params,
                   const GlobalDescriptorMatching& _gdm = GlobalDescriptorMatching())
          : tracker_params(_tracker_params), gdm(_gdm)
        {
        }

        /**
         * @brief output stream parameters
         *
         * @param os std::ostream&
         * @param parameters
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "FeatureAssociatorParams: \n" << parameters.tracker_params << parameters.gdm << std::endl;

            return os;
        }

        /**
         * @brief load from yaml
         *
         * @param node
         * @return Parameters
         */
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        /**
         * @brief static example parameters for unit test
         *
         * @return Parameters
         */
        static Parameters Example();
    };

    /**
     * @brief constructor with parameters
     */
    FeatureAssociator(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters);

    /**
     * @brief destructor
     */
    ~FeatureAssociator()
    {
    }

    /**
     * @brief main computing function
     *
     * @param[in] prior_T_wb prior vehicle pose in world frame
     * @param[in] new_timestamp the newest timestamp
     * @param[in] new_frame_id the newest frame id
     * @param[in] new_features all new features from new images
     * @param[in] visible_map visible map
     * @param[out] tracker_state new tracker state after feature tracking
     * @param[out] mpm new associated map projection factor measurements
     */
    void Run(const Pose3& prior_T_wb, const Timestamp& new_timestamp, const uint64_t new_frame_id,
             const std::vector<Features>& new_features, const MapPtr& visible_map,
             Scalar global_map_matching_window_size, Tracker::State& tracker_state,
             MapProjectionMeasurements& mpm) const;

    /**
     * @brief return parameters
     *
     * @return const Parameters&
     */
    const Parameters& Params() const;

private:
    /**
     * @brief find good map points to create unit3 factors
     *
     * @param map processed map
     * @param features features extracted on image which contained in raw_measurement
     * @param new_frame_id new frame id, used to construct MapProjectionFactorMeasurement
     * @param intrinsic camera intrinsic
     * @param T_wc camera pose in world frame
     * @param associated_features_and_mappoints associated features and mappoints
     * @param[out] MapProjectionMeasurements MapProjectionMeasurements created
     */
    void CreateMapProjectionFactorMeasurement(
        const MapPtr& map, const Features& features, const uint64_t new_frame_id, const IntrinsicBaseTypePtr& intrinsic,
        const Pose3& T_wc, Scalar global_map_matching_window_size, MapProjectionMeasurements& result,
        std::vector<std::pair<Feature, MapPointPtr>>& associated_features_and_mappints) const;

    /**
     * @brief track the features that have been associated with the map point
     *
     * @param new_features all new features from new images
     * @param[out] matched_features_and_mappoint association pairs of feature and mappoint
     * @param[out] MapProjectionMeasurements MapProjectionMeasurements created
     */
    void
    TrackingAssociatedFeatures(const Features&                               new_features,
                               std::vector<std::pair<Feature, MapPointPtr>>& associated_features_and_mappoints) const;

    /**
     * @brief visual feature tracks between two frames
     *
     * @param old_features all new features from old images
     * @param new_features all new features from new images
     */
    void VisualizeInterFrameTrackingResult(const Features& old_features, const Features& new_features,
                                           const std::vector<uint16_t>&         inliers_index,
                                           const DescriptorMatcher::MatchPairs& matched_pairs) const;

    /**
     * @brief according to associated features and mappoints, create map projection factor measuremeng
     *
     * @param new_frame_id new frame id, used to construct MapProjectionFactorMeasurement
     * @param new_frame_id camera id
     * @param intrinsic camera intrinsic
     * @param associated_features_and_mappoints associated features and mappoints
     * @param[out] MapProjectionMeasurements MapProjectionMeasurements created
     */
    void CreateMapProjectionFactorMeasurement(
        const uint64_t new_frame_id, const uint16_t camera_id, const IntrinsicBaseTypePtr& intrinsic,
        const std::vector<std::pair<Feature, MapPointPtr>>& associated_features_and_mappoints,
        MapProjectionMeasurements&                          result) const;

    /// @brief parameteres
    const Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;

    /// @brief feature tracker
    const Tracker tracker_;

};  // class FeatureAssociator

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_FEATURE_ASSOCIATOR_H_
