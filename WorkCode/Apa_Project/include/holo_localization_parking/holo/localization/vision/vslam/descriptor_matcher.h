/*!
 * \brief visual slam descriptor matcher class header file
 * \author Feng.Li lifeng@holomatic.com
 * \date Nov-13-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_DESCRIPTOR_MATCHER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_DESCRIPTOR_MATCHER_H_

#include <holo/localization/vision/vslam/mapping/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
///////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief this class provide some static function interface for descriptor matching.
 *
 */
class DescriptorMatcher
{
public:
    /**
     * @brief init kernel
     *
     */
    static void InitKernel();

    /**
     * @brief check if kernel init or not
     *
     */
    static bool IsKernelInit();

    /**
     * @brief handy type define
     */
    typedef std::vector<std::pair<uint16_t, uint16_t>> MatchPairs;
    typedef std::pair<Feature, Pose3>                  FeatureWithObservedPose;
    typedef std::vector<FeatureWithObservedPose>       FeaturesWithObservedPoses;

    // define matche pair with their descriptor distance
    // key: index in first set of data, value: <index in second set of data, descriptor distance>
    typedef std::unordered_map<uint16_t, std::pair<uint16_t, Scalar>> MatchPairsWithDistance;

    /**
     * @brief compute distance of two given descriptor
     * @throws std::runtime_error Thrown if any input descriptor was not normalized.
     */
    static Scalar DescriptorDistance(const cv::Mat& d1, const cv::Mat& d2);

    /**
     * @brief brute force matching in two set of descriptors
     * @param[in]desc1 a set of descriptors for matching
     * @param[in]desc2 an other set of descriptors for matching
     * @param[in]dist_th threshold of descriptor distance
     * @param[in]ratio_test_th threshold of ratio between smallest disatance and smaller distance
     * @return inliers index pairs in desc1 and desc2
     */
    static MatchPairs BruteForceMatching(const std::vector<cv::Mat>& desc1, const std::vector<cv::Mat>& desc2,
                                         Scalar dist_th, Scalar ratio_test_th);

    /**
     * @brief flow matching method
     * @details this function will be used in consecutive frame feature tracking, it is inspired by optical flow
     * tracking algorithm, for each feature in features1, it will search candidates in features2 for matching in a
     * certain window size
     * @throws std::runtime_error Thrown if any feature's optional descriptor is evaluated to false.
     *
     * @param[in]features1 a set of features for matching
     * @param[in]features2 an other set of features for matching
     * @param[in]window_size window size for filter candidate
     * @param[in]dist_th threshold of descriptor distance
     * @param[in]ratio_test_th threshold of ratio between smallest disatance and smaller distance
     * @return inliers index pairs in features1 and features2
     */
    static MatchPairs FlowMatching(const Features& features1, const Features& features2, const uint16_t window_size,
                                   Scalar dist_th, Scalar ratio_test_th);

    /**
     * @brief match a set of 3d points and 2d features
     * @details project each 3d point by camera pose and camera intrinsic onto image plane,
     *          then search candidate descriptor near the projected point for matching.
     * @throws std::runtime_error Thrown if any feature's optional descriptor is evaluated to false.
     *
     * @param[in]points3d 3d position in world frame and its corresponding descriptor
     * @param[in]features2d 2d features detected on image plane
     * @param[in]intrinsic camera intrinsic
     * @param[in]T_wc camera pose in world frame
     * @param[in]window_size search window size
     * @param[in]descriptor_dist_th threshold of descriptor distance
     * @param[in]ratio_test_th threshold of ratio between smallest disatance and smaller distance
     * @param[in]view_distance_th threshold of distance between mappoint's reference pose and T_wc
     * @param[in]view_direction_th threshold of view direction between mappoints and features
     * @param[in]use_kernel use kernel to reduce cpu loading
     * @return inliers index pairs in mappoints and features
     */
    static MatchPairs MappointsToFeaturesMatching(const ConstMapPtr& map, const Features& features,
                                                  const IntrinsicBaseTypePtr& intrinsic, const Pose3& T_wc,
                                                  Scalar window_size, Scalar descriptor_dist_th, Scalar ratio_test_th,
                                                  Scalar view_distance_th, Scalar view_direction_th,
                                                  bool use_kernel = false);

    /**
     * @brief matching two set of features with their known observed camera pose around epipolar line
     * @throws std::runtime_error Thrown if any feature's optional descriptor is evaluated to false.
     *
     * @param[in]first_data a set of features with it's observed pose. each feature in this set may comes from different
     * camera view.
     * @param[in]second_data an other set of features with it's observed pose. each feature in this set may comes from
     * different camera view.
     * @param[in]epipolar_dist_th threshold of distance between point and epipolar line
     * @param[in]descriptor_dist_th threshold of descriptor distance
     * @param[in]ratio_test_th threshold of ratio between smallest disatance and smaller distance
     * @return inliers index pairs in first_data and second_data
     */
    static MatchPairs EpipolarLineMatching(const FeaturesWithObservedPoses& first_data,
                                           const FeaturesWithObservedPoses& second_data, Scalar epipolar_dist_th,
                                           Scalar descriptor_dist_th, Scalar ratio_test_th);

private:
    /**
     * @brief select best one to one correspondence from many-to-one matching result
     * @param[in]many_to_one_match_result key: matched index in first set of data, value: <matched index in second set
     * of data, discriptor distance>
     */
    static MatchPairs OneToOneFiltering(const MatchPairsWithDistance& many_to_one_match_result);

};  // class DescriptorMatcher

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief define matching message,
 * @details it contain the matched index pairs and their descriptor distance, used to store the intermediate information
 *
 */
struct MatchingMessage
{
    cv::Mat  train_desc;        ///< train descriptor
    uint16_t train_index;       ///< trian index
    Scalar   minimum_distance;  ///< minimum descriptor distance
    Scalar   minor_distance;    /// < minor descriptor distance
    uint16_t best_query_index;  ///< best matched query index

    /**
     * @brief constructor
     *
     */
    MatchingMessage(const cv::Mat& _train_desc, const uint16_t _train_index, const Scalar _minimum_distance = 999.0,
                    const Scalar _minor_distance = 999.0, const uint16_t _best_query_index = 0)
      : train_desc(_train_desc)
      , train_index(_train_index)
      , minimum_distance(_minimum_distance)
      , minor_distance(_minor_distance)
      , best_query_index(_best_query_index)
    {
    }

    /**
     * @brief update matching message
     *
     * @param[in] old_msg old matching message
     * @param[in] query_desc query descriptor
     * @param[in] query_index index of query_desc
     * @return new matching message
     */
    MatchingMessage UpdateMessage(const MatchingMessage& old_msg, const cv::Mat& query_desc,
                                  const uint16_t query_index) const
    {
        // get old message
        Scalar   minimum_distance = old_msg.minimum_distance;
        Scalar   minor_distance   = old_msg.minor_distance;
        uint16_t best_query_index = old_msg.best_query_index;

        // compute new descriptor distance
        const auto dist = DescriptorMatcher::DescriptorDistance(train_desc, query_desc);

        // update distance info
        if (dist < old_msg.minimum_distance)
        {
            minor_distance   = old_msg.minimum_distance;
            minimum_distance = dist;
            best_query_index = query_index;
        }
        else if (dist < old_msg.minor_distance)
        {
            minor_distance = dist;
        }

        // create new matching message and return
        return MatchingMessage(train_desc, train_index, minimum_distance, minor_distance, best_query_index);
    }

    /**
     * @brief check if this matching message is acceptable
     *
     * @param[in] descriptor_dist_th descriptor distance threshold
     * @param[in] ratio_test_th ratio test threshold
     * @return true if acceptable, else return false
     */
    bool IsMatchingAcceptable(Scalar descriptor_dist_th, Scalar ratio_test_th = 1.0) const
    {
        if (minimum_distance < descriptor_dist_th && minimum_distance < minor_distance * ratio_test_th)
        {
            return true;
        }
        return false;
    }

};  // MatchingMessage

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_DESCRIPTOR_MATCHER_H_
