/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_tracker.h
 * @brief This header file defines line feature tracker.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2022-03-02"
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_LINE_FEATURE_LINE_TRACKER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_LINE_FEATURE_LINE_TRACKER_H_

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/line_feature/line_feature_track.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @brief this class defines line feature tracker
 * @details this class is mainly responsible for line feature association between a set of line feature tracks and
 *          newest line features extracted on newest image. It provides two match mode for this job: match with line
 *          feature descriptor only and check with line feature geometric information. Also, it supports different kinds
 *          of input line descriptors(such as float type and binary type). Diffetent match methods can be chosen
 *          including brute force matching, flow matching(like optical flow) and map projection matching.
 */
class LineTracker
{
public:
    /**
     * @brief handy types
     *
     */
    typedef std::vector<std::pair<uint16_t, uint16_t>> MatchPairs;

    /**
     * @brief line feature match mode
     *
     */
    enum class MatchMode : uint32_t
    {
        ONLY_DESCRIPTOR   = 0u,  ///< match two sets of lines only using descriptor
        WITH_GEOMETRYINFO = 1u,  ///< match two sets of lines with descriptor and geometric info
    };

    /**
     * @brief line feature descriptor match method
     *
     */
    enum class DescriptorMatchMethod : uint32_t
    {
        BFM          = 0u,  ///< match two sets of line descriptors using brute force matching
        FLOW_MATCHER = 1u,  ///< match two sets of line descriptors using flow matching
        MAP_MATCHER  = 2u,  ///< match a set of 2d lines and a set of 3d lines
    };

    /**
     * @brief Parameters
     *
     */
    struct Parameters
    {
        /**
         * @brief parameters for descriptor matching
         *
         */
        struct DescriptorInfo
        {
            Scalar   euclidean_distance_threshold;  ///< euclidean distance threshold used in float form descriptors
            uint16_t hamming_distance_threshold;    ///< hamming distance threshold used in binary form descriptors

            /**
             * @brief Construct a new Descriptor Info object
             *
             * @param[in] _euclidean_distance_threshold ///< euclidean distance threshold used in float form descriptors
             * @param[in] _hamming_distance_threshold ///< hamming distance threshold used in binary form descriptors
             */
            DescriptorInfo(Scalar const _euclidean_distance_threshold, uint16_t const _hamming_distance_threshold)
              : euclidean_distance_threshold(_euclidean_distance_threshold)
              , hamming_distance_threshold(_hamming_distance_threshold)
            {
            }
        };

        /**
         * @brief parameters for geometric info matching
         *
         */
        struct GeometricInfo
        {
            Scalar   angle_threshold;            ///< threshold for angle between two matched lines, unit: rad
            uint16_t length_threshold;           ///< threshold for length of line, unit: pixel
            uint16_t center_distance_threshold;  ///< threshold for center distance of two matched lines, unit: pixel

            /**
             * @brief Construct a new Geometric Info object
             *
             * @param[in] _angle_threshold ///< threshold for angle between two matched lines, unit: rad
             * @param[in] _length_threshold ///< threshold for length of line, unit: pixel
             * @param[in] _center_distance_threshold ///< threshold for center distance of two matched lines, unit:
             * pixel
             */
            GeometricInfo(Scalar const _angle_threshold, uint16_t const _length_threshold,
                          uint16_t _center_distance_threshold)
              : angle_threshold(_angle_threshold)
              , length_threshold(_length_threshold)
              , center_distance_threshold(_center_distance_threshold)
            {
            }
        };

        /**
         * @brief line feature non-maximum-suppresion parameters
         *
         */
        struct LineNMS
        {
            Scalar   image_margin;  ///< image margin to suppress edge effect in feature extraction, unit: pixel
            uint16_t maximum_feature_number;    ///< maximum number of features in each image
            uint16_t minimum_feature_distance;  ///< minimum distance of the adjacent features, unit: pixel
            Scalar   minimum_disparity;         ///< minimum disparity of the same feature in two frame, unit: pixel
        };

        MatchMode                    match_mode;               ///< match mode
        DescriptorMatchMethod        descriptor_match_method;  ///< descriptor match method
        DescriptorInfo               descriptor_info;          ///< descriptor info of line feature
        GeometricInfo                geometric_info;           ///< geometric info of line features
        LineNMS                      line_nms_params;          ///< line feature nms parameters
        LineFeatureTrack::Parameters track_params;             ///< feature track parameters

        /**
         * @brief Construct a new Parameters object
         *
         * @param[in] _descriptor_info  ///< descriptor info of line feature
         * @param[in] _geometric_info ///< geometric info of line features
         * @param[in] _match_mode ///< match mode
         * @param[in] _descriptor_match_method ///< descriptor match method
         * @param[in] _line_nms_params ///< line nms parameters
         * @param[in] _track_params ///< feature track parameters
         */
        Parameters(DescriptorInfo const& _descriptor_info, GeometricInfo const& _geometric_info,
                   MatchMode const& _match_mode, DescriptorMatchMethod const& _descriptor_match_method,
                   LineNMS const& _line_nms_params, LineFeatureTrack::Parameters const _track_params)
          : descriptor_info(_descriptor_info)
          , geometric_info(_geometric_info)
          , match_mode(_match_mode)
          , descriptor_match_method(_descriptor_match_method)
          , line_nms_params(_line_nms_params)
          , track_params(_track_params)
        {
        }

        /**
         * @brief output stream for line tracker parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters line tracker parameters
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << parameters "LineTrackerParameters:"
               << "\n match_mode: " << uint32_t(parameters.match_mode)
               << "\n descriptor_match_method: " << uint32_t(parameters.descriptor_match_method)
               << "\n descriptor_info.euclidean_distance_threshold: "
               << parameters.descriptor_info.euclidean_distance_threshold
               << "\n descriptor_info.hamming_distance_threshold: "
               << parameters.descriptor_info.hamming_distance_threshold << "\n geometric_info.angle_threshold "
               << parameters.geometric_info.angle_threshold
               << "\n geometric_info.angle_threshold: " << parameters.geometric_info.angle_threshold
               << "\n geometric_info.length_threshold: " << parameters.geometric_info.length_threshold
               << "\n geometric_info.center_distance_threshold: " << parameters.geometric_info.center_distance_threshold
               << "\n line_nms_params.image_margin: " << parameters.line_nms_params.image_margin
               << "\n line_nms_params.maximum_feature_number: " << parameters.line_nms_params.maximum_feature_number
               << "\n line_nms_params.minimum_feature_distance: " << parameters.line_nms_params.minimum_feature_distance
               << "\n line_nms_params.minimum_disparity: " << parameters.line_nms_params.minimum_disparity << std::endl;
            return os;
        }

        // load from yaml
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        // static method to generate example for unit test
        static Parameters Example();
    };

    /**
     * @brief line tracker state
     *
     */
    struct State
    {
        uint64_t                      frame_id;         ///< last frame id which will not be consective
        Timestamp                     image_timestamp;  ///< last image timestamp
        std::vector<LineFeatureTrack> tracks;           ///< line feature tracks
    };

    /**
     * @brief Construct a new Line Tracker object
     *
     * @param[in] parameters line tracker parameters
     * @param[in] camera_parameters camera parameters
     */
    LineTracker(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters)
      : parameters_(parameters), camera_parameters_(camera_parameters)
    {
    }

    /**
     * @brief main function for line feature tracking
     * @details 1. the input new_multi_camera_features could provide float/binary type of line descriptors
     *          2. it supports different match mode by setting MatchMode parameter
     *          3. it supports different match method by setting DescriptorMatchMethod parameter
     * @param[in] track_state old track state
     * @param[in] new_frame_id frame id of new features
     * @param[in] new_timestamp timestamp of new features
     * @param[in] new_multi_camera_features new features extracted on new image
     */
    void Run(State& track_state, uint64_t const new_frame_id, Timestamp const& new_timestamp,
             std::vector<LineFeatures> const& new_multi_camera_features) const;

private:
    /**
     * @brief extract old features from old tracks
     *
     * @param[in] track_state old track state
     * @param[in] old_features old features
     */
    LineFeatures extractOldTrackedFeatures(State& track_state, uint8_t const camera_index) const;

    /**
     * @brief track old features
     *
     * @param[in] old_features old features
     * @param[in] new_multi_camera_features new features extracted on new image
     * @param[in] matched_pairs inliers index pairs in features1 and features2
     * @return LineFeatures new tracker features
     */
    LineFeatures trackOldFeatures(LineFeatures const&              old_features,
                                  std::vector<LineFeatures> const& new_multi_camera_features,
                                  MatchPairs&                      matched_pairs) const;

    /**
     * @brief brute force matching in two set of descriptors
     *
     * @param[in] desc1 a set of descriptors for matching
     * @param[in] desc2 another set of descriptors for matching
     * @param[in] dist_th threshold of descriptor distance
     * @param[in] ratio_test_th threshold of ratio between smallest disatance and smaller distance
     * @return MatchPairs inliers index pairs in desc1 and desc2
     */
    MatchPairs bruteForceMatching(const std::vector<cv::Mat>& desc1, const std::vector<cv::Mat>& desc2, Scalar dist_th,
                                  Scalar ratio_test_th) const;

    /**
     * @brief line flow matching method
     * @details this function will be used in consecutive frame feature tracking, it is inspired by optical flow
     *          tracking algorithm, for each feature in features1, it will search candidates in features2 for matching
     *          in a certain window size
     * @param[in] line_features1 a set of line features for matching
     * @param[in] line_features2 another set of line features for matching
     * @param[in] window_size window size for filter candidate
     * @param[in] dist_th threshold of descriptor distance
     * @param[in] ratio_test_th threshold of ratio between smallest disatance and smaller distance
     * @return MatchPairs inliers index pairs in features1 and features2
     */
    MatchPairs lineFlowMatching(const LineFeatures& line_features1, const LineFeatures& line_features2,
                                const uint16_t window_size, Scalar dist_th, Scalar ratio_test_th) const;

    /**
     * @brief match a set of 3d lines and 2d line features
     * @details project each 3d line by camera pose and camera intrinsic onto image plane,
     *          then search candidate descriptor near the projected line for matching.
     * @param[in] map 3d map with line landmark
     * @param[in] line_features 2d line features detected on image plane
     * @param[in] intrinsic camera intrinsic
     * @param[in] T_wc camera pose in world frame
     * @param[in] window_size search window size
     * @param[in] descriptor_dist_th threshold of descriptor distance
     * @param[in] ratio_test_th threshold of ratio between smallest disatance and smaller distance
     * @param[in] view_distance_th threshold of distance between mappoint's reference pose and T_wc
     * @param[in] view_direction_th threshold of view direction between mappoints and features
     * @return MatchPairs inliers index pairs in mappoints and line features
     */
    MatchPairs maplinesToLineFeaturesMatching(const ConstMapLinesPtr& map, const LineFeatures& line_features,
                                              const IntrinsicBaseTypePtr& intrinsic, const Pose3& T_wc,
                                              Scalar window_size, Scalar descriptor_dist_th, Scalar ratio_test_th,
                                              Scalar view_distance_th, Scalar view_direction_th) const;

    /**
     * @brief   search line feature by projecting the plucker line landmark
     * @details this method aims at reducing search scope of line feature
     * @param[in] last_features last set of line features
     * @param[in] current_features current set of line features
     * @param[in] wTc pose of camera in world frame
     * @param[in] matched_pairs machted index between the two given features
     */
    void searchByProjection(LineFeatures const& last_features, LineFeatures const& current_features, const Pose3& wTc,
                            MatchPairs& matched_pairs) const;

    /**
     * @brief check two sets of matched lines with line geometric info
     *
     * @param[in] last_features last set of line features
     * @param[in] current_features current set of line features
     * @param[in] matched_pairs machted index between the two given features
     */
    void checkWithGeometricInfo(LineFeatures const& last_features, LineFeatures const& current_features,
                                MatchPairs& matched_pairs) const;

    /**
     * @brief compute descriptor euclidean distance
     *
     * @param[in] descriptor1 input descriptor1
     * @param[in] descriptor2 input descriptor2
     * @return Scalar output euclidean distance
     */
    Scalar computeDescriptorEuclideanDistance(cv::Mat const& descriptor1, cv::Mat const& descriptor2) const;

    /**
     * @brief compute descriptor hamming distance
     *
     * @param[in] descriptor1 input descriptor1
     * @param[in] descriptor2 input descriptor2
     * @return uint16_t output hamming distance
     */
    uint16_t computeDescriptorHammingDistance(cv::Mat const& descriptor1, cv::Mat const& descriptor2) const;

    /**
     * @brief create a mask with NMS method
     *
     * @param[in] last_features last set of line features
     * @param[in] current_features current set of line features
     * @param[in] matched_pairs machted index between the two given features
     * @return std::pair<LineFeatures, Mask>
     */
    std::pair<LineFeatures, Mask> createMaskWithNMS(LineFeatures const& last_features,
                                                    LineFeatures const& current_features,
                                                    MatchPairs&         matched_pairs) const;

    /**
     * @brief update track including updating old tracks and add new tracks
     *
     * @param[in] track_state old track state
     * @param[in] new_frame_id frame id of new features
     * @param[in] new_timestamp timestamp of new features
     * @param[in] matched_pairs machted index between the two given features
     * @param[in] new_features a set of new line features
     */
    void updateTrack(State& track_state, uint64_t const new_frame_id, Timestasmp const& new_timestamp,
                     MatchPairs const& matched_pairs, LineFeatures const& new_features) const;

    Parameters            parameters_;         ///< line tracker parameters
    CameraParameters::Ptr camera_parameters_;  ///< camera parameters
};
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif