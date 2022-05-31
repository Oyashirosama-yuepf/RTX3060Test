/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file st_boundary.h
 * @brief the header of shift-time boundary
 * @author wangchantong(wangchantong@holomatic.com)
 * @date 2020-09-07
 */
#ifndef _HOLO_PLANNING_COMMON_ST_BOUNDARY_H_
#define _HOLO_PLANNING_COMMON_ST_BOUNDARY_H_

#include <holo/core/types.h>

#include <holo/log/hololog.h>
#include <holo/planning/common/box/normal_box.h>

#include <algorithm>
#include <cfloat>
#include <functional>
#include <string>
#include <vector>

namespace holo
{
namespace planning
{
/**
 * @brief Struct for shift-time point
 */
struct StPoint
{
    /**
     * @brief Construct the Shift-time point object.
     *
     * @param time the timestamp of the point (relative to inital time)
     * @param shift the parameter of the point
     */
    StPoint(float64_t const time, float64_t const shift) : time_(time), shift_(shift){};

    float64_t time_;
    float64_t shift_;
};

/*                              -----------
  ------------------------------|POTENTIAL|--------------------------------
  ---------         ---------   -----------     ------------       ---------
  |IGNORED|- - - -  |  ego  | >>>>>>- - - - - - |NOTICEABLE|- - - -|IGNORED|
  -------- -------- ---------                   ------------       ---------
  --------|IGNORED|---------------------------------------------------------
          ---------
*/
enum class ObstableStatus : uint8_t
{
    NOTICEABLE = 0,  // The nearest obstalce which is occupies the whole lane
    POTENTIAL = 1,  // The obstacles which particially occupy lane from [EGO_s, NOTICEABLE_s] or is close in nearby lane
    IGNORED   = 2   // The obstacles which further than NOTICEABLE or behind in the moving direction
};

/**
 * @brief Struct for shift-time boundary
 */
class StBoundary
{
public:
    using Predicted_box_trajectory_ptr = std::shared_ptr<std::vector<NormalBox>>;
    /**
     * @brief Construct the Shift-time boundary object.
     */
    StBoundary() : is_initialized_(false), is_static_(false){};

    /**
     * @brief Initialize the shift-time boundary of a single obstacle.
     *
     * @param obs_id the identity number of obstacle.
     * @param lower_points the series of lower points of obstacle box.
     * @param upper_points the series of upper points of obstacle box.
     * @param velocity_points the series of velocity points of obstacle box.
     * @param predict_trajectory_ptr the pointer of predicted box trajectory.
     */
    void Init(uint32_t const&                     obs_id,
              std::vector<StPoint> const&         lower_points,
              std::vector<StPoint> const&         upper_points,
              std::vector<StPoint> const&         velocity_points,
              Predicted_box_trajectory_ptr const& predict_trajectory_ptr)
    {
        is_initialized_         = true;
        is_static_              = false;
        obs_id_                 = obs_id;
        lower_points_           = lower_points;
        upper_points_           = upper_points;
        velocity_points_        = velocity_points;
        predict_trajectory_ptr_ = predict_trajectory_ptr;
    }

    /**
     * @brief Set obstacle status.
     */
    void SetObstacleStatus(ObstableStatus obs_status)
    {
        obs_status_ = obs_status;
    }

    /**
     * @brief Set obstacle static mode.
     */
    void SetStaticMode(bool_t is_static)
    {
        is_static_ = is_static;
    }

    /**
     * @brief Get the lower and upper point at the specific timestamp.
     *
     * @param time the specific timestamp.
     * @param lower_points the lower point of obstacle box.
     * @param upper_points the upper point of obstacle box.
     *
     * @return True if getting boundary successfully.
     */
    bool_t GetBoundaryPointByTime(float64_t const time, float64_t& lower_s, float64_t& upper_s) const;

    /**
     * @brief Get obstacle identity number.
     *
     * @return The obstacle identity number.
     */
    uint32_t GetObsId() const
    {
        return obs_id_;
    }

    /**
     * @brief Get obstacle status.
     *
     * @return The obstacle identity number.
     */
    ObstableStatus GetObstacleStatus() const
    {
        return obs_status_;
    }

    /**
     * @brief Get obstacle static mode.
     *
     * @return The obstacle static mode.
     */
    bool_t GetStaticMode() const
    {
        return is_static_;
    }

    /**
     * @brief Get the velocity at the specific timestamp.
     *
     * @param time the specific timestamp.
     * @param velocity the velocity of obstacle box.
     *
     * @return True if getting velocity successfully.
     */
    bool_t GetVelocityPointByTime(float64_t time, float64_t& velocity) const;

    /**
     * @brief Get obstacle predicted box trajectory.
     *
     * @return Pointer of obstacle predicted box trajectory.
     */
    Predicted_box_trajectory_ptr GetPredictBoxesTrajectory() const
    {
        return predict_trajectory_ptr_;
    }

private:
    bool_t                       is_initialized_ = false;  // indicate whether initialized already
    bool_t                       is_static_      = false;  // indicate whether is static
    uint32_t                     obs_id_;                  // identity number of obstacle
    ObstableStatus               obs_status_;              // the obstacle status
    std::vector<StPoint>         lower_points_;            // series of lower boundary points of the obstacle
    std::vector<StPoint>         upper_points_;            // series of upper boundary points of the obstacle
    std::vector<StPoint>         velocity_points_;         // series of velocity of the obstacle
    Predicted_box_trajectory_ptr predict_trajectory_ptr_;  // Pointer of a predicted box trajectory
};
}  // namespace planning
}  // namespace holo

#endif
