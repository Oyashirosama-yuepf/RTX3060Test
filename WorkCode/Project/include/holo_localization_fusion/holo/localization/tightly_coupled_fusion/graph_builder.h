/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file graph_builder.h
 * @brief this file defines the class to build factor graph
 * @author Wenzhi Liu(liuwenzhi@holomatic.com)
 * @date  Feb 25, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_GRAPH_BUILDER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_GRAPH_BUILDER_H_

#include <holo/localization/sam/factors/gnss_position_velocity_factor.h>
#include <holo/localization/sam/factors/lane_factor.h>
#include <holo/localization/sam/factors/pose_only_unit3_factor.h>
#include <holo/localization/sam/factors/prior_rpy_factor.h>
#include <holo/localization/sam/factors/projection_line_factor.h>
#include <holo/localization/sam/factors/velocity_factor.h>
#include <holo/localization/sam/factors/wheel_speed_factor.h>
#include <holo/localization/sam/type_converter.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup tightly_coupled_fusion
 * @{
 *
 */

/**
 * @brief this class implements the algorithm that builds a factor graph
 *
 */
class GraphBuilder
{
public:
    using Ptr                           = std::shared_ptr<GraphBuilder>;
    using ConstPtr                      = std::shared_ptr<const GraphBuilder>;
    using PriorPoseFactorPtr            = boost::shared_ptr<GTPriorFactor<GTPose3>>;
    using PriorVelocityFactorPtr        = boost::shared_ptr<GTPriorFactor<GTVector3>>;
    using PriorImuBiasFactroPtr         = boost::shared_ptr<GTPriorFactor<GTConstantBias>>;
    using PoseOnlyUnit3FactorPtr        = boost::shared_ptr<GTPoseOnlyUnit3Factor>;
    using PriorRPYFactorPtr             = boost::shared_ptr<GTPriorRPYFactor>;
    using ImuBiasFactorPtr              = boost::shared_ptr<GTBetweenFactor<GTConstantBias>>;
    using ImuFactorPtr                  = boost::shared_ptr<GTImuFactor>;
    using WheelSpeedFactorPtr           = boost::shared_ptr<GTWheelSpeedFactor>;
    using RelativePoseFactorPtr         = boost::shared_ptr<GTBetweenFactor<GTPose3>>;
    using LaneFactorPtr                 = boost::shared_ptr<GTLane2Factor>;
    using ProjectionLineFactorPtr       = boost::shared_ptr<GTProjectionLineFactor>;
    using GnssFactorPtr                 = boost::shared_ptr<GTGnssPositionVelocityFactor>;
    using VelocityFactorPtr             = boost::shared_ptr<GTVelocityFactor>;
    using LineCorrespondence            = holo::localization::LaneCorrespondences;
    using PointCorrespondence           = holo::localization::PointCorrespondence;
    using VisualSemanticCorrespondences = holo::localization::VisionSemanticCorrespondences;
    using TypeConverter                 = holo::localization::TypeConverter;

    /**
     * @brief define parameters
     *
     */
    struct Parameters
    {
        bool_t enable_prior_pose_factor;              ///< switch of prior pose factor
        bool_t enable_prior_velocity_factor;          ///< switch of prior velocity factor
        bool_t enable_prior_imu_bias_factor;          ///< switch of prior imu bias factor
        bool_t enable_prior_rpy_factor;               ///< switch of prior rpy factor
        bool_t enable_gnss_position_velocity_factor;  ///< switch of gnss position velocity factor
        bool_t enable_imu_factor;                     ///< switch of imu factor
        bool_t enable_imu_bias_factor;                ///< switch of imu bias factor
        bool_t enable_wheel_speed_factor;             ///< switch of wheel speed factor
        bool_t enable_lane_factor;                    ///< switch of lane factor
        bool_t enable_zero_velocity_factor;           ///< switch of zero velocity factor
        bool_t enable_velocity_factor;                ///< switch of velocity factor
        bool_t enable_projection_line_factor;         ///< switch of projection line factor
        bool_t enable_projection_point_factor;        ///< switch of projection point factor

        /**
         * @brief Construct a new Parameters object
         *
         * @param _enable_prior_pose_factor switch of prior pose factor
         * @param _enable_prior_velocity_factor switch of prior velocity factor
         * @param _enable_prior_imu_bias_factor switch of prior imu bias factor
         * @param _enable_prior_rpy_factor switch of prior rpy factor
         * @param _enable_gnss_position_velocity_factor switch of gnss position velocity factor
         * @param _enable_imu_factor switch of imu factor
         * @param _enable_imu_bias_factor switch of imu bias factor
         * @param _enable_wheel_speed_factor switch of wheel speed factor
         * @param _enable_lane_factor switch of lane factor
         * @param _enable_zero_velocity_factor switch of zero velocity factor
         * @param _enable_velocity_factor switch of velocity factor
         * @param _enable_projection_line_factor switch of projection line factor
         * @param _enable_projection_point_factor switch of projection point factor
         */
        Parameters(bool_t const _enable_prior_pose_factor = true, bool_t const _enable_prior_velocity_factor = true,
                   bool_t const _enable_prior_imu_bias_factor = true, bool_t const _enable_prior_rpy_factor = true,
                   bool_t const _enable_gnss_position_velocity_factor = true, bool_t const _enable_imu_factor = true,
                   bool_t const _enable_imu_bias_factor = true, bool_t const _enable_wheel_speed_factor = true,
                   bool_t const _enable_lane_factor = false, bool_t const _enable_zero_velocity_factor = true,
                   bool_t const _enable_velocity_factor = true, bool_t _enable_projection_line_factor = false,
                   bool_t _enable_projection_point_factor = false)
          : enable_prior_pose_factor(_enable_prior_pose_factor)
          , enable_prior_velocity_factor(_enable_prior_velocity_factor)
          , enable_prior_imu_bias_factor(_enable_prior_imu_bias_factor)
          , enable_prior_rpy_factor(_enable_prior_rpy_factor)
          , enable_gnss_position_velocity_factor(_enable_gnss_position_velocity_factor)
          , enable_imu_factor(_enable_imu_factor)
          , enable_imu_bias_factor(_enable_imu_bias_factor)
          , enable_wheel_speed_factor(_enable_wheel_speed_factor)
          , enable_lane_factor(_enable_lane_factor)
          , enable_zero_velocity_factor(_enable_zero_velocity_factor)
          , enable_velocity_factor(_enable_velocity_factor)
          , enable_projection_line_factor(_enable_projection_line_factor)
          , enable_projection_point_factor(_enable_projection_point_factor)
        {
        }

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief Output stream overloading for GraphBuilder's parameter
         *
         * @param[in] os std::ostream&
         * @param[in] parameters Parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters);

        /**
         * @brief Static method to generate example parameters
         *
         * @return the example parameters
         */
        static Parameters GenerateExample();

    };  // Parameters

    /**
     * @brief define gnss position velocity factor measurement
     *
     */
    struct GnssPositionVelocityFactorMeasurement
    {
        GTPoint3                                        gnss_position;  ///< gnss position measurement
        GTVector3                                       gnss_velocity;  ///< gnss velocity measurement
        GTVector6                                       gnss_sigmas;    ///< gnss measurement's standard deviation
        boost::optional<GTPreintegratedImuMeasurements> pim;            ///< preintegrated measurements
        GTMatrix3                                       wRb;            ///< rotation in navigation frame

        /**
         * @brief constructor
         *
         * @param _gnss_position gnss position measurement
         * @param _gnss_velocity gnss velocity measurement
         * @param _gnss_sigmas gnss measurement's standard deviation
         * @param _pim preintegrated measurements
         * @param _wRb rotation in navigation frame
         */
        GnssPositionVelocityFactorMeasurement(GTPoint3 const& _gnss_position, GTVector3 const& _gnss_velocity,
                                              GTVector6 const&                                       _gnss_sigmas,
                                              boost::optional<GTPreintegratedImuMeasurements> const& _pim,
                                              GTMatrix3 const&                                       _wRb)
          : gnss_position(_gnss_position)
          , gnss_velocity(_gnss_velocity)
          , gnss_sigmas(_gnss_sigmas)
          , pim(_pim)
          , wRb(_wRb)
        {
        }
    };  // GnssPositionVelocityFactorMeasurement

    /**
     * @brief relative pose factor measurement
     *
     */
    struct RelativePoseFactorMeasurement
    {
        GTPose3   relative_pose;  ///< relative pose measurement
        GTVector6 sigmas;         ///< relative_pose's standard deviation

        /**
         * @brief constructor
         *
         * @param _relative_pose relative pose measurement
         * @param _sigmas _relative_pose's standard deviation
         */
        RelativePoseFactorMeasurement(GTPose3 const& _relative_pose, GTVector6 const& _sigmas)
          : relative_pose(_relative_pose), sigmas(_sigmas)
        {
        }
    };  // RelativePoseFactorMeasurement

    /**
     * @brief prior rpy factor measurement
     *
     */
    struct PriorRPYFactorMeasurement
    {
        GTVector3 prior_rpy;  ///< prior roll pitch yaw
        GTVector3 sigmas;     ///< prior_rpy's sigmas
        bool_t    fix_roll;   ///< flag to determine whether fix roll
        bool_t    fix_pitch;  ///< flag to determine whether fix pitch
        bool_t    fix_yaw;    ///< flag to determine whether fix yaw

        /**
         * @brief Construct a new Prior R P Y Factor Measurement object
         *
         * @param[in] _prior_rpy rpy measurement
         * @param[in] _sigmas _prior_rpy's standard deviation
         * @param[in] _fix_roll flag to determine whether fix roll
         * @param[in] _fix_pitch flag to determine whether fix pitch
         * @param[in] _fix_yaw flag to determine whether fix yaw
         */
        PriorRPYFactorMeasurement(GTVector3 const& _prior_rpy, GTVector3 const& _sigmas, bool_t const _fix_roll = false,
                                  bool_t const _fix_pitch = false, bool_t const _fix_yaw = true)
          : prior_rpy(_prior_rpy), sigmas(_sigmas), fix_roll(_fix_roll), fix_pitch(_fix_pitch), fix_yaw(_fix_yaw)
        {
        }
    };  // PriorRPYFactorMeasurement

    /**
     * @brief prior pose factor measurement
     *
     */
    struct PriorPoseFactorMeasurement
    {
        GTPose3   prior_pose;  ///< prior pose measurement
        GTVector6 sigmas;  ///< prior_pose's standard deviation, front 3d is rotation's standard deviation, back 3d is
                           ///< translation standard deviation

        /**
         * @brief constructor
         *
         * @param _prior_pose prior pose measurement
         * @param _sigmas _prior_pose's standard deviation
         */
        PriorPoseFactorMeasurement(GTPose3 const& _prior_pose, GTVector6 const& _sigmas)
          : prior_pose(_prior_pose), sigmas(_sigmas)
        {
        }
    };  // PriorPoseFactorMeasurement

    /**
     * @brief prior velocity factor measurement
     *
     */
    struct PriorVelocityFactorMeasurement
    {
        GTVector3 prior_velocity;  ///< prior velocity measurement
        GTVector3 sigmas;          ///< prior_velocity's standard deviation

        /**
         * @brief constructor
         *
         * @param _prior_velocity prior velocity measurement
         * @param _sigmas _prior_velocity's standard deviation
         */
        PriorVelocityFactorMeasurement(GTVector3 const& _prior_velocity, GTVector3 const& _sigmas)
          : prior_velocity(_prior_velocity), sigmas(_sigmas)
        {
        }
    };  // PriorVelocityFactorMeasurement

    /**
     * @brief prior imu bias factor measurement
     *
     */
    struct PriorImuBiasFactorMeasurement
    {
        GTConstantBias prior_imu_bias;  ///< prior imu bias measurement
        GTVector6      sigmas;          ///< prior_imu_bias's standard deviation

        /**
         * @brief constructor
         *
         * @param _prior_imu_bias prior imu bias measurement
         * @param _sigmas _prior_imu_bias's standard deviation
         */
        PriorImuBiasFactorMeasurement(GTConstantBias const& _prior_imu_bias, GTVector6 const& _sigmas)
          : prior_imu_bias(_prior_imu_bias), sigmas(_sigmas)
        {
        }
    };  // PriorImuBiasFactorMeasurement

    /**
     * @brief define measurements
     *
     */
    struct Measurements
    {
        // gnss position velocity factor measurements
        std::vector<StampedT<GnssPositionVelocityFactorMeasurement>> multi_gnss_position_velocity_factor_measurements;

        // imu factor measurements
        std::vector<StampedT<GTPreintegratedImuMeasurements>> multi_imu_factor_measurements;

        // velocity measurements
        std::vector<StampedCombinedVelocityMeasurement> multi_combined_velocity_measurements;

        // lane factor measurements
        std::vector<LaneCorrespondences> multi_lane_factor_measurements;

        // sign factor measurements
        std::vector<VisualSemanticCorrespondences> multi_visual_semantic_measurements;

        // relative pose factor measurements
        std::vector<StampedT<RelativePoseFactorMeasurement>> multi_relative_pose_factor_measurements;

        // imu bias between sigmas measurements
        std::vector<StampedT<GTVector6>> multi_imu_bias_between_sigmas_measurements;

        // prior rpy factor measurements
        std::vector<StampedT<PriorRPYFactorMeasurement>> multi_prior_rpy_factor_measurements;

        // prior pose factor measurements
        std::vector<StampedT<PriorPoseFactorMeasurement>> multi_prior_pose_factor_measurements;

        // prior velocity factor measurements
        std::vector<StampedT<PriorVelocityFactorMeasurement>> multi_prior_velocity_factor_measurements;

        // prior imu bias factor measurements
        std::vector<StampedT<PriorImuBiasFactorMeasurement>> multi_prior_imu_bias_factor_measurements;

        // prediction new stamped navstate
        std::vector<StampedT<GTNavStateAndImuBias>> multi_new_prediction_stamped_gt_state;
    };  // Measurements

    /**
     * @brief define a factor-graph problem
     */
    struct Problem
    {
        GTNonlinearFactorGraph     factor_graph;       ///< factor graph
        GTValues                   values;             ///< values
        GTFastMap<GTKey, GTScalar> key_timestamp_map;  ///< key timestamp map
        uint64_t                   index;              ///< the latest state index

        /**
         * @brief constructor
         *
         * @param _factor_graph factor graph
         * @param _values values
         * @param _key_timestamp_map key timestamp map
         */
        Problem(GTNonlinearFactorGraph const& _factor_graph, GTValues const& _values,
                GTFastMap<GTKey, GTScalar> const& _key_timestamp_map, uint64_t _index = 0u)
          : factor_graph(_factor_graph), values(_values), key_timestamp_map(_key_timestamp_map), index(_index)
        {
        }

    };  // Problem

    /**
     * @brief constructor
     *
     * @param _parameters parameters
     */
    GraphBuilder(Parameters const& _parameters) : parameters_(_parameters), last_index_(0u)
    {
    }

    /**
     * @brief Destroy the Graph Builder object
     *
     */
    ~GraphBuilder()
    {
    }

    /**
     * @brief create initial graph and values
     *
     * @param graph_builder_measurements graph builder measurements
     * @return Problem contains initial factor graph and initial values
     */
    Problem Initialize(Measurements const& graph_builder_measurements);

    /**
     * @brief main computing function
     *
     * @param graph_builder_measurements graph builder measurements
     * @return Problem contains new factor graph and new values
     */
    Problem Run(Measurements const& graph_builder_measurements);

protected:
    /**
     * @brief Convert holo type matrix to eigen type matrix
     *
     * @tparam RowValue the rows of matrix
     * @tparam ColValue the columns of matrix
     * @param mat input holo type matrix
     * @return Eigen::Matrix<float64_t, RowValue, ColValue> eigen type matrix
     */
    template <uint8_t RowValue, uint8_t ColValue>
    Eigen::Matrix<float64_t, RowValue, ColValue>
    convertMatrix(numerics::MatrixT<float64_t, RowValue, ColValue> const& mat) const
    {
        const uint32_t array_size = mat.GetCols() * mat.GetRows();

        Eigen::Matrix<float64_t, RowValue, ColValue> result;
        memcpy(result.data(), mat.GetData(), sizeof(float64_t) * array_size);
        return result;
    }

    /**
     * @brief create a problem
     *
     * @param graph_builder_measurements graph builder measurements
     * @return Problem contains initial factor graph and initial values
     */
    Problem createProblem(Measurements const& graph_builder_measurements);

    /**
     * @brief create a prior pose factor
     *
     * @param index state index
     * @param prior_pose_factor_measurements prior pose factor measurements
     * @return PriorPoseFactorPtr pointer of prior pose factor
     */
    PriorPoseFactorPtr createPriorPoseFactor(uint64_t const                    index,
                                             PriorPoseFactorMeasurement const& prior_pose_factor_measurements) const;

    /**
     * @brief create a prior velocity factor
     *
     * @param index state index
     * @param prior_velocity_factor_measurements prior velocity factor measurements
     * @return PriorVelocityFactorPtr pointer of prior velocity factor
     */
    PriorVelocityFactorPtr createPriorVelocityFactor(
        uint64_t const index, PriorVelocityFactorMeasurement const& prior_velocity_factor_measurements) const;

    /**
     * @brief create a prior Imu bias factor
     *
     * @param index state index
     * @param prior_imu_bias_factor_measurements prior imu bias factor measurements
     * @return PriorImuBiasFactroPtr
     */
    PriorImuBiasFactroPtr createPriorImuBiasFactor(
        uint64_t const index, PriorImuBiasFactorMeasurement const& prior_imu_bias_factor_measurements) const;

    /**
     * @brief create a prior Roll Pitch Yaw factor
     *
     * @param index state index
     * @param prior_rpy_factor_measurements prior rpy factor measurements
     * @return PriorRPYFactorPtr pointer of prior rpy factor
     */
    PriorRPYFactorPtr createPriorRPYFactor(uint64_t const                   index,
                                           PriorRPYFactorMeasurement const& prior_rpy_factor_measurements) const;

    /**
     * @brief create a imu bias factor
     *
     * @param new_index new state index
     * @param imu_bias_between_sigmas imu bias between sigmas
     * @return ImuBiasFactorPtr pointer of imu bias factor
     */
    ImuBiasFactorPtr createImuBiasFactor(uint64_t const new_index, GTVector6 const& imu_bias_between_sigmas) const;

    /**
     * @brief create a imu factor
     *
     * @param new_index new state index
     * @param preintegrated_imu_measurements preintegrated imu measurements
     * @return ImuFactorPtr pointer of imu factor
     */
    ImuFactorPtr createImuFactor(uint64_t const                        new_index,
                                 GTPreintegratedImuMeasurements const& preintegrated_imu_measurements) const;

    /**
     * @brief create a wheel speed factor
     *
     * @param new_index new state index
     * @param preintegrated_wheel_speed_measurements preintegrated wheel speed measurements
     * @return WheelSpeedFactorPtr pointer of wheel speed factor
     */
    WheelSpeedFactorPtr createWheelSpeedFactor(
        uint64_t const new_index, PreintegratedWheelMeasurements const& preintegrated_wheel_speed_measurements) const;

    /**
     * @brief create a relative pose factor
     *
     * @param new_index new state index
     * @param relative_pose_factor_measurement relative pose factor measurement
     * @return RelativePoseFactorPtr pointer of relative pose factor
     */
    RelativePoseFactorPtr createRelativePoseFactor(
        uint64_t const new_index, RelativePoseFactorMeasurement const& relative_pose_factor_measurement) const;

    /**
     * @brief create a lane factors
     *
     * @param index state index
     * @param lane_correspondences lane correspondences
     * @return std::vector<LaneFactorPtr>  pointer vector of lane factor
     */
    std::vector<LaneFactorPtr> createLaneFactor(uint64_t const             index,
                                                LaneCorrespondences const& lane_correspondences) const;

    /**
     * @brief create projection line factors
     *
     * @param index state index
     * @param visual_semantic_correspondences visual semantic correspondences
     * @return std::vector<ProjectionLineFactorPtr> pointer vector of projection line factor
     */
    std::vector<ProjectionLineFactorPtr> createProjectionLineFactor(
        uint64_t const index, VisualSemanticCorrespondences const& visual_semantic_correspondences) const;

    /**
     * @brief create projection point factors
     *
     * @param index state index
     * @param visual_semantic_correspondences visual semantic correspondences
     * @return std::vector<boost::shared_ptr<gtsam::ExpressionFactor<GTPoint2>>>  pointer vector of projection point
     * factor
     */
    std::vector<PoseOnlyUnit3FactorPtr> createVisualProjectionPointFactor(
        uint64_t const index, VisualSemanticCorrespondences const& visual_semantic_correspondences) const;

    /**
     * @brief create a gnss factor
     *
     * @param index state index
     * @param gnss_position_velocity_factor_measurements gnss position velocity factor measurements
     * @return GnssFactorPtr pointer of gnss factor
     */
    GnssFactorPtr
    createGnssFactor(uint64_t const                               index,
                     GnssPositionVelocityFactorMeasurement const& gnss_position_velocity_factor_measurements) const;

    /**
     * @brief create a velocity factor
     *
     * @param[in] index state index
     * @param[in] velocity_factor_measurement velocity factor measurement
     * @return VelocityFactorPtr pointer of velocity factor
     */
    VelocityFactorPtr createVelocityFactor(
        uint64_t const                                                index,
        CombinedVelocityMeasurement::VelocityFactorMeasurement const& velocity_factor_measurement) const;

private:
    const Parameters parameters_;  ///< parameters
    uint64_t         last_index_;  ///< the last index

};  // GraphBuilder

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_GRAPH_BUILDER_H_
