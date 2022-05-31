/*!
 * \brief graph builder class header file in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Jan-15-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_GRAPH_BUILDER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_GRAPH_BUILDER_H_

#include <gtsam/slam/OrientedPlane3Factor.h>
#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/factor_graph.h>
#include <holo/localization/vision/vslam/pose_only_unit3_factor.h>
#include <holo/localization/vision/vslam/rotation_only_imu_factor.h>
#include <holo/localization/vision/vslam/semantic/data_association.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_parallel_factor.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_point_plane_factor.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_vertex_factor.h>
#include <holo/localization/vision/vslam/sliding_window_state.h>
#include <holo/localization/vision/vslam/unit3_factor.h>
#include <holo/localization/vision/vslam/velocity_factor.h>

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
 * @brief input measurement for graph builder
 *
 */
struct FactorMeasurements
{
    /// @brief imu preinttegrated measurement
    PreintegratedImuMeasurements pim;

    PreintegratedAhrsMeasurements pam;

    /// @brief global map projection measurement
    MapProjectionMeasurements mpm;

    /// @brief velocity in body frame
    VelocityMeasurement vm;

    /// @brief wheel integration measurement
    WheelIntegrationMeasurement wim;

    /// @brief predict values
    Values predicted_values;

    /// @brief gt pose for mapping mode
    boost::optional<Pose3> gt_pose;

    /// @brief position in UTM coordinate
    boost::optional<UtmPosition> position;

    /// @brief global slot map projection measurement
    SlotMapFactorMeasurement sfm;

    /// @brief rotation measurement between two frames
    EssentialMatrixMeasurements emms;

    /**
     * @brief Construct a new Factor Measurements object
     *
     * @param _pim imu preinttegrated measurement
     * @param _mpm global map projection measurement
     * @param _velocity velocity in body frame
     * @param _predicted_values predict values
     * @param _gt_pose gt pose for mapping mode
     * @param _position position
     */
    FactorMeasurements(const PreintegratedImuMeasurements&  _pim = PreintegratedImuMeasurements(),
                       const PreintegratedAhrsMeasurements& _pam = PreintegratedAhrsMeasurements(),
                       const MapProjectionMeasurements&     _mpm = {},
                       const VelocityMeasurement&           _vm  = VelocityMeasurement(),
                       const WheelIntegrationMeasurement&   _wim = WheelIntegrationMeasurement(),
                       const Values& _predicted_values = {}, const boost::optional<Pose3>& _gt_pose = boost::none,
                       const boost::optional<UtmPosition>& _position = boost::none,
                       const SlotMapFactorMeasurement& _sfm = {}, const EssentialMatrixMeasurements& _emms = {})
      : pim(_pim)
      , pam(_pam)
      , mpm(_mpm)
      , vm(_vm)
      , wim(_wim)
      , predicted_values(_predicted_values)
      , gt_pose(_gt_pose)
      , position(_position)
      , sfm(_sfm)
      , emms(_emms)
    {
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief this class implements the algorithm that builds a factor graph
 */
class GraphBuilder
{
public:
    /**
     * @brief define smart pointer
     */
    using Ptr      = std::shared_ptr<GraphBuilder>;
    using ConstPtr = std::shared_ptr<const GraphBuilder>;

    /**
     * @brief define parameters
     */
    struct Parameters
    {
        /// @brief noise sigma for prior factor
        const PriorVehicleStateNoise prior_noise;

        /// @brief sigma for wheel integration between pose
        const Vector6 wheel_integration_factor_sigma;

        /// @brief sigma for bias between factor acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z
        const Vector6 bias_between_sigma;

        /// @brief sigma for velocity factor vx, vy, vz
        const Vector3 velocity_factor_sigma;

        /// @brief sigma for velocity factor when turns vx, vy, vz
        const Vector3 velocity_factor_sigma_when_turns;

        /// @brief sigma for low precision velocity fmeasurements. vx, vy, vz
        const Vector3 low_precision_velocity_factor_sigma;

        /// @brief sigma for pose only unit3 factor
        const Vector2 pose_only_unit3_factor_sigma;

        /// @brief sigma for zero velocity between pose [R_x,R_y,R_z,T_x,T_y,T_z]
        const Vector6 zero_velocity_between_pose_sigma;

        /// @brief sigma for ground truth pose
        const Vector6 gt_pose_sigma;

        /// @brief pose only unit3 huber loss
        const Scalar pose_only_huber_loss;

        /// @brief whether add factor graph
        const bool enable_wheel_integration_factor;
        const bool enable_velocity_factor;
        const bool enable_zero_velocity_factor;
        const bool enable_prior_factor;
        const bool enable_pose_only_unit3_factor;
        const bool enable_unit3_factor;
        const bool enable_gt_pose_factor;
        const bool enable_position_factor;

        /**
         * @brief Construct a new Parameters object
         *
         * @param _prior_noise noise sigma for prior factor
         * @param _wheel_integration_factor_sigma sigma for wheel integration factor
         * @param _bias_between_sigma sigma for bias between factor
         * @param _velocity_factor_sigma sigma for velocity factor
         * @param _velocity_factor_sigma_when_turns sigma for velocity factor when turns
         * @param _low_precision_velocity_factor_sigma sigma for velocity factor when turns vx, vy, vz
         * @param _pose_only_unit3_factor_sigma sigma for pose only unit3 factor
         * @param _zero_velocity_between_pose_sigma sigma for zero velocity between pose
         * @param _gt_pose_sigma sigma for ground truth pose
         * @param _pose_only_huber_loss pose only unit3 huber loss
         * @param _enable_wheel_integration_factor whether add wheel integration factor
         * @param _enable_velocity_factor whether add velocity factor
         * @param _enable_zero_velocity_factor whether add zero velocity factor
         * @param _enable_prior_factor whether add prior factor
         * @param _enable_pose_only_unit3_factor whether add pose only unit3 factor
         * @param _enable_unit3_factor whether add unit3 factor
         * @param _enable_gt_pose_factor whether add gt pose factor
         */
        Parameters(const PriorVehicleStateNoise& _prior_noise, const Vector6 _wheel_integration_factor_sigma,
                   const Vector6& _bias_between_sigma, const Vector3& _velocity_factor_sigma,
                   const Vector3& _velocity_factor_sigma_when_turns,
                   const Vector3& _low_precision_velocity_factor_sigma, const Vector2& _pose_only_unit3_factor_sigma,
                   const Vector6& _zero_velocity_between_pose_sigma, const Vector6& _gt_pose_sigma,
                   const Scalar _pose_only_huber_loss, const bool _enable_wheel_integration_factor,
                   const bool _enable_velocity_factor, const bool _enable_zero_velocity_factor,
                   const bool _enable_prior_factor, const bool _enable_pose_only_unit3_factor,
                   const bool _enable_unit3_factor, const bool _enable_gt_pose_factor,
                   const bool _enable_position_factor = false)
          : prior_noise(_prior_noise)
          , wheel_integration_factor_sigma(_wheel_integration_factor_sigma)
          , bias_between_sigma(_bias_between_sigma)
          , velocity_factor_sigma(_velocity_factor_sigma)
          , velocity_factor_sigma_when_turns(_velocity_factor_sigma_when_turns)
          , low_precision_velocity_factor_sigma(_low_precision_velocity_factor_sigma)
          , pose_only_unit3_factor_sigma(_pose_only_unit3_factor_sigma)
          , zero_velocity_between_pose_sigma(_zero_velocity_between_pose_sigma)
          , gt_pose_sigma(_gt_pose_sigma)
          , pose_only_huber_loss(_pose_only_huber_loss)
          , enable_wheel_integration_factor(_enable_wheel_integration_factor)
          , enable_velocity_factor(_enable_velocity_factor)
          , enable_zero_velocity_factor(_enable_zero_velocity_factor)
          , enable_prior_factor(_enable_prior_factor)
          , enable_pose_only_unit3_factor(_enable_pose_only_unit3_factor)
          , enable_unit3_factor(_enable_unit3_factor)
          , enable_gt_pose_factor(_enable_gt_pose_factor)
          , enable_position_factor(_enable_position_factor)
        {
        }

        /**
         * @brief output stream for Parameters
         *
         * @param os std::ostream&
         * @param params parameters
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& params)
        {
            os << "GraphBuilderParameters:\n"
               << params.prior_noise << "bias_between sigma = " << params.bias_between_sigma.Transpose()
               << "\n wheel_integration_factor_sigma = " << params.wheel_integration_factor_sigma.Transpose()
               << "\n velocity_factor_sigma = " << params.velocity_factor_sigma.Transpose()
               << "\n velocity_factor_sigma_when_turns = " << params.velocity_factor_sigma_when_turns.Transpose()
               << "\n low_precision_velocity_factor_sigma = " << params.low_precision_velocity_factor_sigma.Transpose()
               << "\n pose_only_unit3_factor_sigma = " << params.pose_only_unit3_factor_sigma.Transpose()
               << "\n zero_velocity_between_pose_sigma = " << params.zero_velocity_between_pose_sigma.Transpose()
               << "\n gt_pose_sigma = " << params.gt_pose_sigma.Transpose()
               << "\n pose_only_huber_loss = " << params.pose_only_huber_loss
               << "\n enable_wheel_integration_factor = " << params.enable_wheel_integration_factor
               << "\n enable_velocity_factor = " << params.enable_velocity_factor
               << "\n enable_zero_velocity_factor = " << params.enable_zero_velocity_factor
               << "\n enable_prior_factor = " << params.enable_prior_factor
               << "\n enable_pose_only_unit3_factor = " << params.enable_pose_only_unit3_factor
               << "\n enable_unit3_factor = " << params.enable_unit3_factor
               << "\n enable_gt_pose_factor = " << params.enable_gt_pose_factor
               << "\n enable_position_factor = " << params.enable_position_factor << std::endl;
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
         * @brief static method to generate example for unit test
         *
         * @return Parameters
         */
        static Parameters Example();
    };  // struct Parameters

    /**
     * @brief define a factor-graph problem
     *
     * @details !!! NOT FP, because FactorGraph and Values are NOT FP !!!
     */
    struct Problem
    {
        FactorGraph factor_graph;
        Values      values;

        /**
         * @brief Construct a new Problem object
         *
         * @param _factor_graph
         * @param _values
         */
        Problem(const FactorGraph& _factor_graph, const Values& _values) : factor_graph(_factor_graph), values(_values)
        {
        }

        /// @brief check if problem is empty
        bool Empty() const;

        /// @brief add factor graph and values
        void Add(const FactorGraph& new_factor_graph, const Values& new_values);

        /// @brief add factor graph
        void Add(const FactorGraph& new_factor_graph);

    };  // Problem

    /**
     * @brief Construct a new Graph Builder object
     *
     * @param parameters
     */
    GraphBuilder(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters)
      : parameters_(parameters), camera_parameters_(camera_parameters)
    {
    }

    /**
     * @brief create initial graph and values
     *
     * @param initial_factor_measurements the initial factor measurements for graph builer
     * @param initial_frame_index the initial frame index
     * @return Problem that contains initial factor graph and initial values
     */
    Problem Initialize(const FactorMeasurements& initial_factor_measurements, uint64_t initial_frame_index) const;

    /**
     * @brief create new factors and gather new values for IncrementalFixedLagSmoother
     *
     * @param new_factor_measurements newest factor measurements for graph builer
     * @param tracks the feature tracks in sliding window
     * @param frame_index the current frame index
     * @return Problem contains new factors and new values
     */
    Problem Run(const FactorMeasurements& new_factor_measurements, const std::vector<FeatureTrack>& tracks,
                uint64_t frame_index) const;

    /**
     * @brief return parameters
     */
    const Parameters& Params() const;

private:
    /**
     * @brief calculate the index of the oldest frame (to be marginalized)
     *
     * @param variable_index
     * @return oldest_frame_index
     */
    uint64_t GetOldestFrameIndex(const gtsam::VariableIndex& variable_index) const;

    /**
     * @brief create prior factor for pose, velocity and bias
     *
     * @param frame_index the frame index where prior factor added
     * @param values values containes prior measurements
     * @return prior FactorGraph
     */
    FactorGraph CreatePriorFactor(const uint64_t frame_index, const Values& values) const;

    /**
     * @brief create new factors
     *
     * @param new_factor_measurements newest factor measurements for graph builer
     * @param new_tracks the feature tracks in sliding window
     * @param new_frame_index the newest frame index
     * @return new FactorGraph
     */
    FactorGraph NewFactorGraph(const FactorMeasurements&        new_factor_measurements,
                               const std::vector<FeatureTrack>& new_tracks, uint64_t new_frame_index) const;

    /**
     * @brief create new factor with new wheel integration measurement
     *
     * @param new_wim the new wheel integration measurement
     * @param new_frame_index the newest frame id
     * @return Pose3BetweenFactorPtr
     */
    Pose3BetweenFactorPtr NewWheelIntegrationFactor(const WheelIntegrationMeasurement& new_wim,
                                                    uint64_t                           new_frame_index) const;

    /**
     * @brief create new imu factor
     *
     * @param new_pim
     * @param new_frame_index
     * @return ImuFactorPtr
     */
    ImuFactorPtr NewImuFactor(const PreintegratedImuMeasurements& new_pim, const uint64_t new_frame_index) const;

    /**
     * @brief create new rotation only imu factor
     *
     * @param new_pim
     * @param new_frame_index
     * @return ImuFactorPtr
     */
    RotationOnlyImuFactorPtr NewRotationOnlyImuFactor(const PreintegratedAhrsMeasurements& new_pam,
                                                      const uint64_t                       new_frame_index) const;

    /**
     * @brief create BetweenFactor for consecutive pose X(${new_frame_index} - 1)
     *        and X(${new_frame_index}) when the vehicle speed is zero
     * @note ${new_frame_index} is always larger than 0, because this function will be called after Initialize()
     * @param new_frame_index
     * @return gtsam::BetweenFactor<gtsam::Pose3>
     */
    Pose3BetweenFactorPtr NewPose3BetweenFactor(const uint64_t new_frame_index) const;

    FactorGraph NewEssentialMatrixFactors(const EssentialMatrixMeasurements& emms) const;

    /**
     * @brief create new imu bias factor
     *
     * @param new_frame_index
     * @return ImuBiasFactorPtr
     */
    ImuBiasFactorPtr NewImuBiasFactor(const uint64_t new_frame_index) const;

    /**
     * @brief create new imu bias factor
     *
     * @param new_frame_index
     * @return GyroBiasFactorPtr
     */
    GyroBiasFactorPtr NewGyroBiasFactor(const uint64_t new_frame_index) const;

    /**
     * @brief create new velocity factor
     *
     * @param new_velocity
     * @param new_frame_index
     * @param sigma velocity factor noise sigma
     * @return VelocityFactorPtr
     */
    VelocityFactorPtr NewVelocityFactor(const Vector3& new_velocity, const uint64_t new_frame_index,
                                        const Vector3& sigma) const;

    /**
     * @brief create new pose only unit3 factor
     *
     * @param new_map_projection_measurement
     * @return PoseOnlyUnit3 Factor
     */
    PoseOnlyUnit3FactorPtr NewPoseOnlyUnit3Factor(const MapProjectionMeasurement& new_map_projection_measurement) const;

    /**
     * @brief create new pose only parking slot vertex factor
     *
     * @param new_sfm
     * @return factor graph
     */
    FactorGraph NewPoseOnlySlotVertexFactor(const SlotMapFactorMeasurement& new_sfm) const;

    /**
     * @brief create prior pose factor
     *
     * @param gt_pose
     * @param new_frame_index
     * @return PosePriorFactorPtr
     */
    PosePriorFactorPtr NewGtPoseFactor(const gtsam::Pose3& gt_pose, const uint64_t new_frame_index) const;

    /**
     * @brief create new landmark values
     *
     * @param new_tracks
     * @return new landmark values
     */
    Values NewLandmarkValues(const std::vector<FeatureTrack>& new_tracks) const;

    /**
     * @brief
     *
     * @param semantic_state semantic state
     * @param wTb from body to world
     * @param graph sub factor graph
     * @param values sub values
     * @param frame_index check whether the frame index is equal to track's frame id
     */
    void addSemanticFactors(const semantic::DataAssociation::State& semantic_state, const gtsam::Pose3& wTb,
                            FactorGraph& graph, Values& values, const int64_t& frame_index) const;

    /// @brief parameters
    const Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;
};  // class GraphBuilder

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_GRAPH_BUILDER_H_
