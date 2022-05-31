/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file motion_status_estimator.h
 * @brief This header file defines motion status estimator.
 * @author wenxunzhe(wenxunzhe@holomaitc.com)
 * @date "2021-10-30"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_MOTION_STATUS_ESTIMATOR_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_MOTION_STATUS_ESTIMATOR_H_

#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/fusion/track.h>

#include <deque>

namespace holo
{
namespace perception
{
/**
 * @brief This class should bind to a track, estimate its motion
 *
 */
class MotionStatusEstimator
{
public:
    using Scalar              = float32_t;
    using MotionStatus        = holo::obstacle::details::MotionStatus;
    using MotionStatusHistory = std::deque<MotionStatus>;
    using Vector3f            = ::holo::numerics::Vector3f;
    using StateVector         = numerics::VectorT<Scalar, 6U>;
    using HistoryType         = std::deque<std::pair<ObstacleProperty<Scalar>, Timestamp>>;

    /**
     * @brief Construct a new Motion Status Estimator object
     *
     * @param vx_thresh velocity x thresh
     * @param vy_thresh velocity y thresh
     * @param max_history_size max history size
     */
    MotionStatusEstimator(Scalar const vx_thresh = 0.75f, Scalar const vy_thresh = 0.75f,
                          size_t const max_history_size = 10U);

    /**
     * @brief setup the estimator
     *
     * @param vx_thresh velocity x thresh
     * @param vy_thresh velocity y thresh
     * @param count_thresh count thresh
     */
    void Setup(Scalar const vx_thresh, Scalar const vy_thresh, Scalar const count_thresh);

    /**
     * @brief update state
     *
     * @param vx current velcoty along x
     * @param vy current velcity along y
     * @param vel_body ego car velocity
     */
    void Update(Vector3f const& abs_velocity, HistoryType const& history_measurements_);

    /**
     * @brief Get the current Motion Status object
     *
     * @return MotionStatus
     */
    MotionStatus GetCurrentMotionStatus() const
    {
        return current_motion_status_;
    }

    /**
     * @brief Set the Current Motion Status object
     *
     * @param motion
     */
    void SetCurrentMotionStatus(MotionStatus const& motion)
    {
        this->current_motion_status_ = motion;
    }

private:
    /**
     * @brief get motion state in current frame
     *
     * @param vx current velcoty along x
     * @param vy current velcity along y
     * @param vel_body ego car velocity
     */
    MotionStatus calculateMotionStatus(Vector3f const& abs_velocity, HistoryType const& measurements);

private:
    Scalar   vx_thresh_;
    Scalar   vy_thresh_;
    uint32_t count_thresh_;

    size_t max_history_size_;

    MotionStatusHistory motion_status_history_;
    MotionStatus        current_motion_status_;
};

}  // namespace perception
}  // namespace holo

#endif
