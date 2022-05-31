/*!
 * \brief sliding window estimator class header file in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SLIDING_WINDOW_ESTIMATOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SLIDING_WINDOW_ESTIMATOR_H_

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/descriptor_matcher.h>
#include <holo/localization/vision/vslam/graph_builder.h>
#include <holo/localization/vision/vslam/pose_only_unit3_factor.h>
#include <holo/localization/vision/vslam/sliding_window_state.h>
#include <holo/localization/vision/vslam/track_state_transition.h>
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
 * @brief sliding window estimator class
 *
 * @details this class mainly estimates a new sliding window state given the old state and new factor graph measurement
 */

class SlidingWindowEstimator
{
public:
    /**
     * @brief define parameters
     *
     * @details it defines all the parameters governed by estimator, as well as
     *          the parameters of algorithm classes created by the estimator
     */
    struct Parameters
    {
        /// @brief define track state transistion
        const TrackStateTransition::Parameters tst_params;

        /// @brief number of frame in the fixed lag
        Scalar lag_size;

        /// @brief isam2 parameters
        const gtsam::ISAM2Params isam2_params;

        /**
         * @brief Construct a new Parameters object
         *
         * @param _tst_params track state transistion
         * @param _builder_params graph builder parameters
         * @param _lag_size number of frame in the fixed lag
         * @param _isam2_params isam2 parameters
         */
        Parameters(const TrackStateTransition::Parameters& _tst_params, const Scalar _lag_size = 10,
                   const gtsam::ISAM2Params& _isam2_params = gtsam::ISAM2Params())
          : tst_params(_tst_params), lag_size(_lag_size), isam2_params(_isam2_params)
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
            os << "SlidingWindowEstimator:" << parameters.tst_params << std::endl;

            // gtsam IncrementalFixedLagSmoother
            std::cout << "\n lag_size = " << parameters.lag_size << std::endl;
            parameters.isam2_params.print("isam2 parameters");
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
    SlidingWindowEstimator(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters);

    /**
     * @brief destructor
     */
    ~SlidingWindowEstimator()
    {
    }

    /**
     * @brief initialization with first prior vehicle state
     *
     * @param[in, out] state the processed sliding window state
     * @param initial_factor_measurements the initial factor measurements for graph builder
     */
    bool Initialize(SlidingWindowState& state, const FactorMeasurements& initial_factor_measurements,
                    const Timestamp& initial_timestamp, const uint64_t initial_frame_id) const;

    /**
     * @brief main computing function
     *
     * @details !!!
     *          this method can only be called after the system is initialized
     *          (see @Initialize()) or it'll lead to unexpected result.
     *          !!!
     *          Bacially, it propagates the old state to a new state with new
     *          measurements
     * @param[in,out] state processed sliding window state
     * @param new_factor_measurement new_factor_measurement
     * @return boost::optional<SlidingWindowState>
     */
    bool Run(SlidingWindowState& state, const FactorMeasurements& new_factor_measurement,
             const Timestamp& new_timestamp, const uint64_t new_frame_id) const;

    /**
     * @brief compensate estimated values to fix trajectory jump
     *
     * @param old_state last optimized SlidingWindowState
     * @param new_state current optimized SlidingWindowState
     * @return SlidingWindowState with new compensated values
     * @TODO consider moving the compensation functions out of SlidingWindowEstimator class
     *       when vslam has a stable version. lishuaijie@holomatic.com
     */
    Values CompensateValues(const Values& old_compensated_values, const Values& new_optimized_values,
                            const FactorGraph& new_factor_graph, const uint64_t new_frame_id) const;

    /**
     * @brief return parameters
     *
     * @return const Parameters&
     */
    const Parameters& Params() const;

    /**
     * @brief set graph builder pointer to this module.
     * @param graph_builder the smart pointer to a graph builder module
     */
    void SetGraphBuilderPtr(GraphBuilder::Ptr graph_builder)
    {
        builder_ = graph_builder;
    }

    /**
     * @brief compute oldest frame id in the slinding window
     * @details the oldest frame id is equals to current_frame_id - lag_size.
     * and if current_frame_id <= lag_size, the oldest frame id is zero.
     *
     * @param current_frame_id current_frame_id
     * @return oldest frame id in the slinding window
     */
    uint64_t GetOldestFrameId(const uint64_t current_frame_id) const;

private:
    /**
     * @brief run optimization with IncrementalFixedLagSmoother
     *
     * @param[in,out] smoother the processed fix lag smoother
     * @param new_sub_problem new factors and new values used to update smoother
     * @param new_frame_id new_frame_id
     * @param factors_to_remove factor indices to be remove
     * @return new sliding window state if success, boost::none if fail
     */
    bool Optimization(gtsam::IncrementalFixedLagSmoother& smoother, const GraphBuilder::Problem& new_sub_problem,
                      const uint64_t new_frame_id, const gtsam::FactorIndices& factors_to_remove = {}) const;

    /**
     * @brief find factors to remove
     * @note the factor indices will be added to smoother in next iteration
     *
     * @param state processed sliding window state
     * @return factor indices to be removed
     */
    gtsam::FactorIndices FindFactorsToRemove(const SlidingWindowState& state) const;

    /****************functions to compensate values's x y z yaw******************/
    /**
     * @brief get translation and yaw from pose
     *
     * @param pose
     * @return translation and yaw
     */
    std::pair<gtsam::Point3, Scalar> GetXYZYaw(const gtsam::Pose3& pose) const;

    /**
     * @brief compensate x,y,z,yaw of estimated values by reference parameters
     *
     * @param old_reference_xyz old_reference_xyz
     * @param new_reference_xyz new_reference_xyz
     * @param delta_rotation delta_rotation
     * @param oldest_frame_id oldest_frame_id
     * @param new_values new_values
     * @return compensated values
     */
    gtsam::Values CompensateXYZYaw(const gtsam::Point3& old_reference_xyz, const gtsam::Point3& new_reference_xyz,
                                   const gtsam::Rot3& delta_rotation, const uint64_t oldest_frame_id,
                                   const gtsam::Values& new_values) const;

    gtsam::Values Compensate6DoFInSlidingWindow(const gtsam::Pose3& old_reference_pose,
                                                const gtsam::Pose3& new_reference_pose, uint64_t oldest_frame_id,
                                                const gtsam::Values& new_values) const;

    /****************functions to compensate values's x y z yaw******************/

    /// @brief parameteres
    const Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;

    /// @brief track state transition
    const TrackStateTransition track_state_transition_;

    /// @brief graph builder
    GraphBuilder::Ptr builder_;

};  // class SlidingWindowEstimator

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SLIDING_WINDOW_ESTIMATOR_H_
