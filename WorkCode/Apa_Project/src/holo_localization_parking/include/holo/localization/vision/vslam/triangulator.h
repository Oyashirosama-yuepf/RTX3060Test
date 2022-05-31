/*!
 * \brief visual slam track triangulation
 * \author guopeikai@holomatic.com
 * \date Mar-5-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_TRIANGULATOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_TRIANGULATOR_H_

#include <gtsam/geometry/triangulation.h>
#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/factor_graph.h>
#include <holo/localization/vision/vslam/feature_track.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @brief define Triangulator Class
 *
 * @details it'll triangulate a track when it satisfies the condition
 */
class Triangulator
{
public:
    // handy typedef
    using ViewDirectionAndPose   = std::pair<gtsam::Vector3, gtsam::Pose3>;
    using ViewDirectionsAndPoses = std::vector<ViewDirectionAndPose>;

    /**
     * @brief define parameters
     */
    struct Parameters
    {
        /// @brief the minimum tracked times that a FreatureTrack will be triangulated
        uint64_t minimum_track_length;

        /// @brief max acceptable reproject error after triangulate.// Unit (pixel)
        Scalar max_acceptable_reproject_error;

        /// @brief minimum camera view angle requirement for triangulation. Unit (degree)
        Scalar minimum_disparity_angle;

        /// @brief maximum landmark distance. Unit (m)
        Scalar maximum_landmark_distance;

        /// @brief minimum landmark distance. Unit (m)
        Scalar minimum_landmark_distance;

        /// @brief minimum baseline requirement for triangulation. Unit (m)
        Scalar minimum_triangulation_baseline;

        // constructor
        Parameters(const uint64_t _minimum_track_length, const Scalar _max_acceptable_reproject_error,
                   const Scalar _minimum_disparity_angle, const Scalar _maximum_landmark_distance,
                   const Scalar _minimum_landmark_distance, const Scalar _minimum_triangulation_baseline)
          : minimum_track_length(_minimum_track_length)
          , max_acceptable_reproject_error(_max_acceptable_reproject_error)
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
               << "\n triangulation_threshold = " << parameters.max_acceptable_reproject_error
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
    Triangulator(const Parameters& paramters, const CameraParameters::Ptr& camera_parameters)
      : parameters_(paramters), camera_parameters_(camera_parameters)
    {
    }

    /**
     * @brief triangulate a feature track
     * @param[in] track feature track
     * @param[in] values
     * return boost optional Point3
     */
    boost::optional<Point3> Run(const FeatureTrack& track, const Values& values) const;

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

    // define parameters
    const Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;

};  // class Triangulator

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_TRIANGULATOR_H_
