/*!
 * \brief sliding window state in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Jan-15-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SLIDING_WINDOW_STATE_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SLIDING_WINDOW_STATE_H_

#include <gtsam_unstable/nonlinear/IncrementalFixedLagSmoother.h>
#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/factor_graph.h>
#include <holo/localization/vision/vslam/semantic/data_association.h>
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
 * @brief sliding window state
 * @details it contains all the variables in a sliding window
 */
struct SlidingWindowState
{
    /// @brief gtsam incremental fixed lag smoother to replace batch optimization and marginalization
    static gtsam::IncrementalFixedLagSmoother static_smoother;

    /// @brief tracker state
    static Tracker::State static_tracker_state;

    /// @brief static semantic state, used to recode all state in sliding window
    static semantic::DataAssociation::State static_semantic_state;

    /// @brief frame id
    uint64_t frame_id;

    /// @brief timestamp
    Timestamp timestamp;

    /// @brief estimated values in sliding window including X(Pose), V(Velocity), B(Bias) and L(Landmark)
    Values values;

    /**
     * @brief compensated values including X(Pose), V(Velocity) and B(Bias)
     *
     * @detial to deal with the trajectory jump, the x,y,z,yaw of the estimated values is compensated
     *         and the compensated_values is published to other modules
     */
    Values compensated_values;

    /**
     * @brief factor indices to be removed
     *
     * @note the factor indices will be added to smoother in next iteration while update smoother with new factor graph
     */
    gtsam::FactorIndices factors_to_remove;

    /// @brief inliers global correspondence number in sliding window
    uint32_t inlier_global_correspondence_num;

    static bool enable_estimation_with_acc;

    /**
     * @brief Construct a new Sliding Window State object
     *
     * @param _values values
     * @param _compensated_values compensated values
     * @param _factors_to_remove factor indices to be remove
     */
    SlidingWindowState(const uint64_t _frame_id = 0, const Timestamp _timestamp = Timestamp(0, 0),
                       const Values& _values = {}, const Values& _compensated_values = {},
                       const gtsam::FactorIndices& _factors_to_remove = {})
      : frame_id(_frame_id)
      , timestamp(_timestamp)
      , values(_values)
      , compensated_values(_compensated_values)
      , factors_to_remove(_factors_to_remove)
      , inlier_global_correspondence_num(0)
    {
    }

    /**
     * @brief return the most recent timestamp
     *
     * @return timestamp of the newset vehicle state
     */
    Timestamp GetTimestamp() const noexcept;

    /**
     * @brief is initialized
     *
     * @return true if the slinding window state is initialized
     *         false otherwise
     */
    bool IsInitialized() const noexcept;

    /**
     * @brief return newest vehicle state in sliding window
     *
     * @return the newest vehicle state
     * @throw when the vehicle state corresponding to frame_id does not exist
     */
    VehicleState NewestVehicleState() const;

    /**
     * @brief retrun newest relative pose
     *        i.e. (T_w_frame_id-1).Inverse() * T_w_frame_id for frame_id > 0
     *             gtsam::Pose3() for frame_id == 0
     *
     * @return the relative pose of the newest pose and the second newest pose
     *         it will be an identity pose if there is only one pose in the slinding window state
     * @throw when either navstate of frame_id or frame_id - 1 does not exist in values
     */
    gtsam::Pose3 NewestRelativePose() const;

private:
    /**
     * @brief get a specified vehicle state in sliding window
     *
     * @param index the retrived frame index
     * @return vehicle state of the ${index}th frame
     * @throw when the ${index} navstate does not exist in values
     */
    VehicleState GetVehicleState(const uint64_t index) const;

};  // SlidingWindowState

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SLIDING_WINDOW_STATE_H_
