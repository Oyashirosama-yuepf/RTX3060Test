/*!
 * \brief visual slam tracker class
 * \author Yanwei. Du duyanwei@holomatic.com
 * \author Feng. Li lifeng@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_TRACKER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_TRACKER_H_

#include <map>
#include <unordered_map>
#include <unordered_set>

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/descriptor_matcher.h>
#include <holo/localization/vision/vslam/feature_track.h>

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
 * @brief visual slam feature tracker class
 * @details this class is mainly responsible for feature association between a set of feature tracks and newest features
 *          extracted on newest image. It provides two method for this job: KLT and DescriptorMatcher. KLT method can
 *          only support consecutive frame feature tracking, while DescriptorMatcher method can tracking features which
 *          has broken several times.
 */
class Tracker
{
public:
    /**
     * @brief parameters
     */
    struct Parameters
    {
        /**
         * @brief define flow matching parameters
         * @details flow matching only support matching between adjacent frames.
         */
        struct FlowMatching
        {
            const Scalar window_size;         ///< flow matching searched window size
            const Scalar descriptor_dist_th;  ///< flow matching descriptor distance threshold
            const Scalar ratio_test_th;       ///< flow matching ratio test threshold
            const bool   cross_check;         ///< flag indicate whether do cross check in flow matching

            /// @brief constructor
            FlowMatching(const Scalar _fm_window_size = 50.0, const Scalar _fm_descriptor_dist_th = 1.0,
                         const Scalar _fm_ratio_test_th = 0.7, const bool _fm_cross_check = false)
              : window_size(_fm_window_size)
              , descriptor_dist_th(_fm_descriptor_dist_th)
              , ratio_test_th(_fm_ratio_test_th)
              , cross_check(_fm_cross_check)
            {
            }
        };  // FlowMatching

        /**
         * @brief define ransac fundamental matrix problem parameters
         */
        struct RansacFMParameters
        {
            const Scalar confidence;           ///< confidence level [0.0 - 1.0] that the result is the best model
            const Scalar pixel_tolerance;      ///< the threshold to classify inliers / outliers
            const Scalar max_iterations;       ///< maximum number of ransac iterations
            const bool   enable_optimization;  ///< flag indicate whether optimize model with inliers

            /**
             * @brief constructor
             */
            RansacFMParameters(const Scalar _confidence = 0.99, const Scalar _pixel_tolerance = 2.0,
                               const Scalar _max_iterations = 20.0, const bool _enable_optimization = true)
              : confidence(_confidence)
              , pixel_tolerance(_pixel_tolerance)
              , max_iterations(_max_iterations)
              , enable_optimization(_enable_optimization)
            {
            }
        };

        /// @brief flow matching parameters
        const FlowMatching fm;

        /// @brief specify tracking method. [DescriptorMatching or NONE]
        const std::string tracking_algorithm;

        /// @brief ransac parameters for geometric consistency checking
        const RansacFMParameters ransac_params;

        /// @brief feature track's parameters
        const FeatureTrack::Parameters::ConstPtr track_params;

        /**
         * @brief constructor
         */
        Parameters(const FlowMatching&       _fm                 = FlowMatching(),
                   const std::string&        _tracking_algorithm = "DescriptorMatching",
                   const RansacFMParameters& _ransac_params      = RansacFMParameters())
          : fm(_fm)
          , tracking_algorithm(_tracking_algorithm)
          , ransac_params(_ransac_params)
          , track_params(new FeatureTrack::Parameters(false, false))
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "TrackerParameters:"
               << "\n fm.window_size: " << parameters.fm.window_size
               << "\n fm.descriptor_dist_th: " << parameters.fm.descriptor_dist_th
               << "\n fm.ratio_test_th: " << parameters.fm.ratio_test_th
               << "\n fm.cross_check: " << parameters.fm.cross_check
               << "\n tracking_algorithm = " << parameters.tracking_algorithm << "\n RansacFMParameters:"
               << "\n confidence = " << parameters.ransac_params.confidence
               << "\n pixel_tolerance = " << parameters.ransac_params.pixel_tolerance
               << "\n max_iterations = " << parameters.ransac_params.max_iterations
               << "\n enable_optimization = " << parameters.ransac_params.enable_optimization << "\n"
               << *(parameters.track_params) << std::endl;
            return os;
        }

        // load from yaml
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        // static method to generate example for unit test
        static Parameters Example();
    };

    /**
     * @brief define track state
     */
    struct State
    {
        uint64_t                  frame_id;
        Timestamp                 timestamp;
        std::vector<FeatureTrack> tracks;

        /**
         * @brief constructor
         */
        State(const uint64_t _frame_id = 0, const Timestamp& _timestamp = Timestamp(),
              const std::vector<FeatureTrack>& _tracks = {})
          : frame_id(_frame_id), timestamp(_timestamp), tracks(_tracks)
        {
        }

        /**
         * @brief get next frame id
         */
        uint64_t NextFrameId() const
        {
            if (tracks.empty())
            {
                return 0;
            }
            return frame_id + 1;
        }
    };  // state

    /**
     * @brief constructor with parameters
     */
    Tracker(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters)
      : parameters_(parameters), camera_parameters_(camera_parameters)
    {
    }

    /**
     * @brief main function for feature tracking pipeline
     * @details it will call RunWithDescriptor() or do nothing respectively according to the specific tracking
     *          algorithm defined in prameters
     * @throws std::runtime_error thrown if parameters_.tracking_algorithm dose not equals to "NONE" or
     * "DescriptorMatching". or parameters_.tracking_algorithm is "DescriptorMatching" but given measurements do not
     * contain features.
     *
     * @param[out]tracker_state the old tracker state
     * @param[in] new_timestamp the timestamp of new features
     * @param[in] new_multi_camera_features new features extracted on new image
     */
    void Run(State& tracker_state, const Timestamp& new_timestamp, const uint64_t new_frame_id,
             const std::vector<Features>& new_multi_camera_features) const;

    /**
     * @brief pick the inlier matched pair by epipolar constraint checking
     * @note if the number of given matched pairs less than 9, all pair will be treat as inliers.
     * @param last_features a set of features
     * @param curr_features another set of features
     * @param matched_pairs machted index between the two given features
     * @return inliers index of given matched_pairs
     */
    std::vector<uint16_t> DoGeometricConsistencyCheck(const Features& last_features, const Features& curr_features,
                                                      const DescriptorMatcher::MatchPairs& matched_pairs) const;

private:
    /**
     * @brief main function for feature tracking by decriptor matching method
     *
     * @param[out]tracker_state the old tracker state
     * @param[in]new_multi_camera_features new features extracted on new image
     */
    void RunWithDescriptor(State& tracker_state, const std::vector<Features>& new_multi_camera_features,
                           const uint64_t new_frame_id) const;

    /**
     * @brief parameters
     */
    const Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;
};  // Tracker

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_TRACKER_H_
