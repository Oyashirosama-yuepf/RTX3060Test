/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_slot_fusion.h
 * @brief This header file parking slot main pipeline
 * @author Feng. Li lifeng@holomatic.com
 * @author Changxi. Cheng chengchangxi@holomatic.com
 * @date 2021-11-04
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_FUSION_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_FUSION_H_

#include <gtsam_unstable/nonlinear/IncrementalFixedLagSmoother.h>
#include <holo/localization/common/localization_base.h>
#include <holo/localization/vision/vslam/graph_builder.h>
#include <holo/localization/vision/vslam/semantic/common_types.h>
#include <holo/localization/vision/vslam/semantic/data_association.h>
#include <holo/localization/vision/vslam/semantic/psf_measurement_manager.h>
#include <holo/localization/vision/vslam/sliding_window_state.h>

#include <thread>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief parking slot fusion main estimator class
 *
 * @details all the threads will be created in this class
 */
class ParkingSlotFusion : public LocalizationBase
{
public:
    /**
     * @brief handy typedefs
     */
    using Base                           = LocalizationBase;
    using OutputParkingSlotFrameCallback = std::function<holo::int32_t(const ParkingSlotFrameType&)>;

    /**
     * @brief parking slot fusion parameters
     */
    struct Parameters
    {
        /// @brief frequency is defined in Base class
        Scalar                      frequency = 5;
        Scalar                      lag_size;
        DataAssociation::Parameters da_params;

        /// @brief sigma for vertex factor
        Vector3 vertex_factor_sigma;

        /// @brief sigma for plane factor
        Vector3 plane_factor_sigma;

        /// @brief sigma for point plane factor
        Vector1 point_plane_factor_sigma;

        /// @brief sigma for parallel factor
        Vector3 parallel_factor_sigma;

        /// @brief sigma for prior pose factor
        Vector6 prior_pose_sigma;

        /// @brief sigma for pose3 between factor
        Vector6 pose3_between_factor_sigma;

        /// @brief if enable tracking
        bool enable_slot_tracking;

        /// @brief if enable optimization
        bool enable_slot_optimization;

        Parameters()
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
            os << "ParkingSlotFusionParameters:\n"
               << "\n data_association_parameters : " << params.da_params << "frequency = " << params.frequency
               << "\n lag_size = " << params.lag_size
               << "\n vertex_factor_sigma = " << params.vertex_factor_sigma.Transpose()
               << "\n plane_factor_sigma = " << params.plane_factor_sigma.Transpose()
               << "\n point_plane_factor_sigma = " << params.plane_factor_sigma.Transpose()
               << "\n parallel_factor_sigma = " << params.parallel_factor_sigma.Transpose()
               << "\n prior_pose_sigma = " << params.prior_pose_sigma.Transpose()
               << "\n pose3_between_factor_sigma = " << params.pose3_between_factor_sigma.Transpose()
               << "\n enable_slot_tracking = " << params.enable_slot_tracking
               << "\n enable_slot_optimization = " << params.enable_slot_optimization << std::endl;
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

    };  // Parameters

    /**
     * @ingroup localization
     * @brief sliding window state
     * @details it contains all the variables in a sliding window
     */
    struct PSFusionSlidingWindowState
    {
        /// @brief gtsam incremental fixed lag smoother to replace batch optimization and marginalization
        static gtsam::IncrementalFixedLagSmoother static_smoother;

        /// @brief static semantic state, used to recode all state in sliding window
        static DataAssociation::State static_semantic_state;

        /// @brief frame id
        uint64_t frame_id;

        /// @brief timestamp
        Timestamp timestamp;

        /// @brief estimated values in sliding window including X(Pose), V(Velocity), B(Bias) and L(Landmark)
        Values values;

        /**
         * @brief Construct a new Sliding Window State object
         *
         * @param _values values
         */
        PSFusionSlidingWindowState(const uint64_t _frame_id = 0, const Timestamp _timestamp = Timestamp(0, 0),
                                   const Values& _values = {})
          : frame_id(_frame_id), timestamp(_timestamp), values(_values)
        {
        }

        Pose3 GetNewestPose() const;
    };  // SlidingWindowState

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
     * @brief constructor
     */
    ParkingSlotFusion(const Parameters& parameters);

    /**
     * @brief destructor
     */
    virtual ~ParkingSlotFusion();

    /**
     * @brief get parameters
     */
    virtual const Parameters& Params() const
    {
        return parameters_;
    }

    /**
     * @brief stop all thread here
     */
    virtual void Stop() override;

    /**
     * @brief process parking slot frame
     * @param[in] measurement latest parking slot frame measurement
     */
    bool_t ProcessParkingSlotFrame(const ParkingSlotFrameType& measurement);

    /**
     * @brief process prior odometry
     * @details use prior odometry to build factor graph
     */
    bool_t ProcessPriorOdometry(const Odometry& measurement);

    /**
     * @brief Set the Output Parking Slot frame Callback
     */
    int32_t SetOutputGlobalParkingSlotFrameCallback(const OutputParkingSlotFrameCallback& cb);

protected:
    /**
     * @brief pre-condition checking
     *
     * @details it will be called before EstimationCore() to check
     *          pre-condition
     */
    virtual bool checkPreCondition() override
    {
        return true;
    };

    /**
     * @brief post-condition checking
     *
     * @details it will be called after EstimationCore()
     */
    virtual bool postProcess() override;

    /**
     * @brief estimator core function
     *
     * @details all the algorithms will be called in this function
     */
    virtual void run() override;

    /**
     * @brief add parking based semantic factor graph
     *
     */
    Problem addSemanticFactors(const DataAssociation::State& semantic_state, const gtsam::Pose3& wTb,
                               const int64_t& frame_index) const;

    /**
     * @brief run optimization with IncrementalFixedLagSmoother
     *
     * @param[in,out] smoother the processed fix lag smoother
     * @param new_sub_problem new factors and new values used to update smoother
     * @param new_frame_id new_frame_id
     * @param factors_to_remove factor indices to be remove
     * @return new sliding window state if success, boost::none if fail
     */
    bool_t optimization(gtsam::IncrementalFixedLagSmoother& smoother, const Problem& new_sub_problem,
                        const uint64_t new_frame_id, const gtsam::FactorIndices& factors_to_remove = {}) const;

    /**
     * @brief update global slot map
     *
     */
    void updateGlobalSlotMap(PSFusionSlidingWindowState& new_state);

    /**
     * @brief publish global slot map
     *
     */
    void publishGlobalSlotMap(const PSFusionSlidingWindowState& new_state);

    /**
     * @brief convert parking slot from global to body
     *
     * @param T_bw from world to body
     * @param in parking slot in world frame
     */
    ParkingSlotType ConvertFromGlobalToBody(const Pose3& bTw, const ParkingSlotType& in) const;

    /// @brief the newest raw measurement
    PSFusionRawMeasurement new_raw_measurement_;

    /**
     * @brief variables
     */
    const Parameters                parameters_;  ///< psd fusion parameters
    PSFusionRawMeasurement          last_raw_measurement_;
    PSFusionMeasurementManager::Ptr measurement_manager_;                ///< measurements_manager
    DataAssociation                 associator_;                         ///< data associator
    PSFusionSlidingWindowState      sliding_window_state_;               ///< sliding window state
    uint64_t                        new_frame_id_;                       ///< the newest frame id in sliding window
    uint64_t                        estimation_core_iteration_counter_;  ///< counter for EstimationCore
    bool_t                          is_estimation_core_work_well_;

    /**
     * define callback functions
     */
    OutputParkingSlotFrameCallback output_global_parking_slot_frame_callback_;

    // optimized slot map and vehicle trajectory
    std::unordered_map<int64_t, ParkingSlotType> optimized_slot_map_;
    std::vector<Pose3>                           trajectory_;
    std::unordered_map<uint64_t, Pose3>          frame_id_to_poses_;

    std::shared_ptr<std::thread> estimator_thread_;  ///< parking slot fusion estimator thread

    /// @brief time monitor for
    TicTocTimer timer_;

};  // ParkingSlotFusion

}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_FUSION_H_
