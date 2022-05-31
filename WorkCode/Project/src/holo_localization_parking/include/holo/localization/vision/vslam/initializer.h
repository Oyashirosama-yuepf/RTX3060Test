/*!
 * \brief visual slam initializer class header file
 * \author Quan.Chen chenquan@holomatic.com
 * \date Jan-2-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_INITIALIZER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_INITIALIZER_H_

#include <gtsam_unstable/nonlinear/BatchFixedLagSmoother.h>
#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/descriptor_matcher.h>
#include <holo/localization/vision/vslam/factor_graph.h>
#include <holo/localization/vision/vslam/localization/relocalization.h>
#include <holo/localization/vision/vslam/pose_only_unit3_factor.h>

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
 * @brief initializer class
 *
 * @details this class implements compute initial vehicle state
 *          Input:
 *              raw_measurement, features, initial_bias, intrinsic, T_bc
 *          Output:
 *              initial vehicle_state, T_wm
 *          MainSteps:
 *              Compute init prior pose from Pnp solved pose when have optional_map,
 *              then we can choose to optimize the result of PNP solved pose.
 *              Or get init prior pose from gravity aligned odometry for highway.
 */
class Initializer
{
public:
    /**
     * @brief define parameters
     */
    struct Parameters
    {
        /// @brief specify the source to compute initial pose.
        /// @details by now we have provided three method to compute the initial pose
        ///          1. gravity_aligned_odometry
        ///          2. prebuilt_map matching
        ///          3. stationary
        const std::string source_to_compute_initial_pose;

        /// @brief flag which indicate if checking the solved pose by start point of prebuilt map
        /// @details this flag only used when compute initial pose by prebuilt feature map in HPP like mode.
        const bool checking_solved_pose_by_path_start_point;

        /// @brief max acceptable difference between current vehicle pose and origin point of learned map
        const Vector3 maximum_acceptable_diff_ypr;   ///< difference in [yaw, pitch, roll]. [degree]
        const Scalar  maximum_acceptable_diff_z;     ///< difference in z. [meter]
        const Scalar  maximum_acceptable_diff_dist;  ///< difference in distance. [meter]

        /// @brief define init imu bias
        ImuBias initial_bias;

        /**
         * @brief Construct a new Parameters object
         *
         * @param _iterator
         * @param _projection_threshold
         * @param _confidence
         * @param _minimum_inliers
         * @param _distance_threshold
         * @param _ratio_test
         * @param _match_pairs_threshold
         * @param _sigma_uv
         * @param _huber_loss
         * @param _pose_sigma
         */
        Parameters(const std::string& _source_to_compute_initial_pose,
                   const bool _checking_solved_pose_by_path_start_point, const Vector3 _maximum_acceptable_diff_ypr,
                   const Scalar _maximum_acceptable_diff_z, const Scalar _maximum_acceptable_diff_dist,
                   const ImuBias& _initial_bias)
          : source_to_compute_initial_pose(_source_to_compute_initial_pose)
          , checking_solved_pose_by_path_start_point(_checking_solved_pose_by_path_start_point)
          , maximum_acceptable_diff_ypr(_maximum_acceptable_diff_ypr)
          , maximum_acceptable_diff_z(_maximum_acceptable_diff_z)
          , maximum_acceptable_diff_dist(_maximum_acceptable_diff_dist)
          , initial_bias(_initial_bias)
        {
        }

        /**
         * @brief output stream for Parameters
         *
         * @param os std::ostream&
         * @param params Parameters
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& params)
        {
            os << "InitializerParameters:\n"
               << " source_to_compute_initial_pose = " << params.source_to_compute_initial_pose
               << "\n checking_solved_pose_by_path_start_point = " << params.checking_solved_pose_by_path_start_point
               << "\n maximum_acceptable_diff_ypr = " << params.maximum_acceptable_diff_ypr.Transpose()
               << "\n maximum_acceptable_diff_z = " << params.maximum_acceptable_diff_z
               << "\n maximum_acceptable_diff_dist = " << params.maximum_acceptable_diff_dist << "\n initial bias:"
               << "\n  acc = " << params.initial_bias.GetLinearAccelerationBias().Transpose()
               << "\n  gyro = " << params.initial_bias.GetAngularVelocityBias().Transpose() << std::endl;
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
     * @brief Construct a new Initializer object
     *
     * @param parameters
     */
    Initializer(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters) noexcept
      : parameters_(parameters), camera_parameters_(camera_parameters)
    {
    }

    /**
     * @brief Destroy the Initializer object
     */
    ~Initializer()
    {
    }

    /**
     * @brief main function for computing initial vehiclestate
     *
     * @param raw_measurement raw sensor measurements
     * @param multi_camera_features features from multi-camera system
     * @param prior_T_wb an optional prior vehicle pose, use to check if the solved pose by initializer is reasonable.
     *                   eg: for localization in HPP, we think the initial vehicle pose should near the learned path.
     * @return optional vehiclestate
     */
    boost::optional<VehicleState> Run(const RawMeasurement&         raw_measurement,
                                      const std::vector<Features>&  multi_camera_features,
                                      const boost::optional<Pose3>& prior_T_wb = boost::none) const;

    /**
     * @brief set relocalization pointer to this module.
     * @details the relocalization module will used to solve initial pose in a prebuilt map
     * @param relocalization the smart pointer to a relocalization module
     */
    void SetRelocalizationPtr(Relocalization::Ptr relocalization)
    {
        relocalization_ = relocalization;
    }

private:
    /**
     * @brief compute initial pose and imu bias.
     * @details this function assumes that the vehicle is absolutely stationary during initialization. then we cache  a
     * set of imu readings to initial the rotation and imu bias. that is, the translation of the returned pose is zero.
     *
     * @param raw_measurement raw sensor measurements
     * @return an optional initial pose and imu bias.
     *         if the vehicle is moving on or the cached imu reading is not enough, the return value will be evaluated
     *         to false.
     */
    boost::optional<std::pair<Pose3, ImuBias>>
    ComputeInitPoseAndBiasFromStandstill(const RawMeasurement& raw_measurement) const;

    /**
     * @brief get initial prior pose from gravity aligned odometry
     *
     * @param gravity_aligned_odometry
     * @return optional Pose3
     */
    boost::optional<Pose3> GetInitPriorPoseFromGravityAlignedOdometry(const Odometry& gravity_aligned_odometry) const;

    /**
     * @brief checking solved pose by reference pose
     * @details It checks the relative translation and rotation between the solved pose and reference pose. if the
     * relative values is larger than certain threshold, it will return false, which means the solved pose is
     * unreasonable.
     * @note this function will only be used when compute initial pose by prebuilt feature map in HPP like mode.
     *
     * @param solved_pose pose to be checked
     * @param reference_pose the reference pose. in HPP mode, the reference pose is the start point of learned path.
     * @return true is passing the checking rules, else return false
     */
    bool CheckingWithReferencePose(const Pose3& solved_pose, const Pose3& reference_pose) const;

    /// @brief parameters
    const Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;

    /// @brief relocalization module. used to initialize system in localiation mode
    Relocalization::Ptr relocalization_;
};  // class Initializer

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_INITIALIZER_H_
