/*!
 * \brief visual slam track state transition
 * \author duyanwei@holomatic.com
 * \date April-15-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_TRACK_STATE_TRANSITION_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_TRACK_STATE_TRANSITION_H_

#include <gtsam/geometry/triangulation.h>
#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/factor_graph.h>
#include <holo/localization/vision/vslam/tracker.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @brief define TrackStateTransition Class
 *
 * @details it'll transit track state according to some rules. Particularly, a
 *          track must be triangulated when it becomes a "FRESH" track
 */
class TrackStateTransition
{
public:
    // handy typedef
    typedef Tracker::State                                                    State;
    typedef std::pair<gtsam::Vector3, gtsam::Pose3>                           ViewDirectionAndPose;
    typedef std::vector<std::pair<gtsam::Vector3, gtsam::Pose3>>              ViewDirectionsAndPoses;
    typedef std::unordered_map<Scalar, Scalar>                                PixelErrorAtImageCenterToUnit3Error;
    typedef std::unordered_map<uint16_t, PixelErrorAtImageCenterToUnit3Error> IndexedPixelErrorToUnit3Error;

    /**
     * @brief define parameters
     */
    struct Parameters
    {
        /// @brief the minimum tracked times that a FreatureTrack will be triangulated
        const uint64_t minimum_track_length;

        /// @brief the maximum tracked times that a FreatureTrack will be dropped if it is not successfully triangulated
        const uint64_t maximum_candidate_track_length;

        /// @brief max acceptable reproject error after triangulate.// Unit (pixel)
        const Scalar triangulation_threshold;

        /// @brief projection error threshold to determine whether the newest measurement is acceptable. // Unit (pixel)
        /// @note used in checking before optimzization
        const Scalar tracking_threshold;

        /// @brief projection error threshold to determine whether the newest measurement is acceptable. // Unit (pixel)
        /// @note used in checking after optimzization
        const Scalar rejection_threshold;

        /// @brief minimum camera view angle requirement for triangulation. Unit (degree)
        const Scalar minimum_disparity_angle;

        /// @brief maximum landmark distance. Unit (m)
        const Scalar maximum_landmark_distance;

        /// @brief minimum landmark distance. Unit (m)
        const Scalar minimum_landmark_distance;

        /// @brief minimum baseline requirement for triangulation. Unit (m)
        const Scalar minimum_triangulation_baseline;

        // constructor
        Parameters(const uint64_t _minimum_track_length, const uint64_t _maximum_candidate_track_length,
                   const Scalar _traingulation_threshold, const Scalar _tracking_threshold,
                   const Scalar _rejection_threshold, const Scalar _minimum_disparity_angle,
                   const Scalar _maximum_landmark_distance, const Scalar _minimum_landmark_distance,
                   const Scalar _minimum_triangulation_baseline)
          : minimum_track_length(_minimum_track_length)
          , maximum_candidate_track_length(_maximum_candidate_track_length)
          , triangulation_threshold(_traingulation_threshold)
          , tracking_threshold(_tracking_threshold)
          , rejection_threshold(_rejection_threshold)
          , minimum_disparity_angle(_minimum_disparity_angle)
          , maximum_landmark_distance(_maximum_landmark_distance)
          , minimum_landmark_distance(_minimum_landmark_distance)
          , minimum_triangulation_baseline(_minimum_triangulation_baseline)
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "\n minimum_track_length = " << parameters.minimum_track_length
               << "\n maximum_candidate_track_length = " << parameters.maximum_candidate_track_length
               << "\n triangulation_threshold = " << parameters.triangulation_threshold
               << "\n tracking_threshold = " << parameters.tracking_threshold
               << "\n rejection_threshold = " << parameters.rejection_threshold
               << "\n minimum_disparity_angle = " << parameters.minimum_disparity_angle
               << "\n maximum_landmark_distance = " << parameters.maximum_landmark_distance
               << "\n minimum_landmark_distance = " << parameters.minimum_landmark_distance
               << "\n minimum_triangulation_baseline = " << parameters.minimum_triangulation_baseline << std::endl;
            return os;
        }

        // load from yaml
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        // static method to generate example for unit test
        static Parameters Example();
    };

    /**
     * @brief constructor
     * @param[in] paramters track state transition parameters
     */
    TrackStateTransition(const Parameters& paramters, const CameraParameters::Ptr& camera_parameters)
      : parameters_(paramters)
      , camera_parameters_(camera_parameters)
      , pixel_error_threshold_to_unit3_error_threshold_(UnifyErrorThreshold(parameters_, camera_parameters_))
    {
    }

    /**
     * @brief update track state after pure-tracking (tracker)
     * @param[in,out] state the processed tracker state
     * @param[in] values values for triangulation or other checking
     * @param[in] old_factor_graph old factor graph used to
     *            compute projection error threshold from
     *            previous projection factor of this track
     * @return new state, tracks will be updated, the rest stays the same
     */
    void RunBeforeOptimization(State& state, const Values& values,
                               const boost::optional<FactorGraph>& old_factor_graph = boost::none) const;

    /**
     * @brief filter the tracks with optimization results
     * @details transit track state to BAD_AFTER_OPTIMIZATION if not satisfies
     *          the projection constrain
     * @param[in,out] state the processed tracker state
     * @param[in] values values after graph optimzation
     * @param[in] old_factor_graph old factor graph used to
     *            compute projection error threshold from
     *            previous projection factor of this track
     * @return state after transit track state
     */
    void RunAfterOptimization(State& state, const Values& values,
                              const boost::optional<FactorGraph>& old_factor_graph = boost::none) const;

private:
    /**
     * @brief compute projection error threshold for the newest factor of the given FeatureTrack
     *        using the stdandard deviation of the projection error the old factors corresponding to the given
     * FeatureTrack
     * @param[in] track the given feature track
     * @param[in] old_factor_graph factor graph from last optimization without newest factors
     * @param[in] old_variable_index variable index corresponding to old_factor_graph
     * @param[in] values
     * @return computed threshold
     */
    Scalar ComputeTrackErrorThreshold(const FeatureTrack& track, const FactorGraph& old_factor_graph,
                                      const gtsam::VariableIndex& old_variable_index, const Values& values) const;

    /**
     * @brief check if a track is tracked
     * @param[in] track feature track
     * @param[in] frame_id newest frame id
     * return whether the track is broken
     */
    bool IsTrackingBroken(const FeatureTrack& track, const uint64_t frame_id) const;

    /**
     * @brief check if the new tracked satisfies the projection constrain
     * @param[in] track feature track
     * @param[in] values values for check
     * @param[in] threshold reprojection error threshold
     * return whether satisfies the projection constrain
     */
    bool CheckReprojectionError(const FeatureTrack& track, const Values& values, const Scalar threshold) const;

    /**
     * @brief get camera pose T_mc (camera pose in vio map frame)
     * @param[in] values
     * @param[in] T_bc camera extrinsic
     * @param[in] frame_id queried frame id.
     * return T_mc
     */
    gtsam::Pose3 GetCamPose(const Values& values, const gtsam::Pose3& T_bc, const uint64_t frame_id) const;

    /**
     * @brief judge whether the max disparity of the track is enough to do triangulation
     * @param[in] track track whose disparity will be checked
     * @param[in] values estimated values
     * @return whether is ready for triangulation
     */
    bool IsTrackReadyForTriangulation(const FeatureTrack& track, const Values& values) const;

    /**
     * @brief get the direction current camera position points to
     *        the landmark corresponding to the given measurement
     * @param[in] measurement
     * @param[in] values
     * @return uint vector represents the direction in world frame and camera pose
     */
    ViewDirectionsAndPoses GetRayDirectionAndPose(const FeatureTrack::Measurement& measurement,
                                                  const Values&                    values) const;

    /**
     * @brief judge whether the disparity and baseline of given observed information is good enough to do
     * triangulation
     *
     * @param first_observed_info first observed ray direction and pose
     * @param second_observed_info second observed ray direction and pose
     *
     * @return true if the baseline and disparity is larger than threshold in parameters. else return false
     */
    bool IsGoodForTriangulation(const ViewDirectionAndPose& first_observed_info,
                                const ViewDirectionAndPose& second_observed_info) const;
    /**
     * @brief triangulate a track
     * @param[in] track feature track
     * @param[in] values
     */
    gtsam::TriangulationResult Triangulation(const FeatureTrack& track, const Values& values) const;

    /**
     * @brief update candidate track
     * @param[in] track feature track
     * @param[in] values
     * return feature track after updating state
     */
    FeatureTrack UpdateCandidateTrack(const FeatureTrack& track, const Values& values) const;

    /**
     * @brief unify all threshold to support multi-camera vslam system
     * @details user could only care about the pipxel error at image center(in pixel) in yaml. this function
     * can unify all these threshold to satisfy all camera intrinsic.
     *
     * @param parameters parameters
     * @param camera_parameters camera parameters
     * @return camera indexed pixel error to unit3 error map
     */
    IndexedPixelErrorToUnit3Error UnifyErrorThreshold(const Parameters&           parameters,
                                                      const CameraParameters::Ptr camera_parameters) const;

    // define parameters
    const Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;

    /// @brief pixel error threshold to unit3 error threshold map
    const IndexedPixelErrorToUnit3Error pixel_error_threshold_to_unit3_error_threshold_;

};  // class TrackStateTransition

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_TRACK_STATE_TRANSITION_H_
