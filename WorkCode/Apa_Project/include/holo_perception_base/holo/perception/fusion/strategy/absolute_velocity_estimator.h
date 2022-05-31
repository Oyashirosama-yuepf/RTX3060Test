/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file absolute_velocity_estimator.h
 * @brief This header file defines absolute velocity estimator
 * @author wangming(wangming@holomatic.com)
 * @date "2021-10-18"
 */

#ifndef HOLO_PERCEPTION_FUSION_STRATEGY_ABSOLUTE_VELOCITY_ESTIMATOR_H_
#define HOLO_PERCEPTION_FUSION_STRATEGY_ABSOLUTE_VELOCITY_ESTIMATOR_H_

#include <holo/numerics/vector.h>
#include <holo/obstacle/obstacle_base.h>
#include <holo/perception/fusion/track_base.h>

#include <type_traits>

namespace holo
{
namespace perception
{
class AbsoluteVelocityEstimator
{
public:
    using Scalar   = holo::float32_t;
    using Vector3f = holo::numerics::Vector3T<Scalar>;

    /**
     * @brief Construct a new Absolute Velocity Estimator object
     *
     */
    AbsoluteVelocityEstimator()
    {
    }

    /**
     * @brief Set the Velocity Body object
     *
     * @param vel velocity body
     */
    void SetVelocityBody(const Vector3f& vel)
    {
        velocity_body_ = vel;
    }

    /**
     * @brief Set the Angular Velocity object
     *
     * @param angular_velocity angular velocity
     */
    void SetAngularVelocity(Scalar angular_velocity)
    {
        angular_velocity_ = angular_velocity;
    }

    /**
     * @brief estimate absolute velocity of obstacle
     * @details use for TrackBase or its derived class
     * @tparam std::enable_if<std::is_base_of<obstacle::ObstacleBaseT<Scalar>, ObstacleType>::value,
     * bool>::type  only type of TrackBase or its derived class use this function
     * @param obs pointer to obstacle
     * @return Vector3f absolute velocity
     */
    template <typename ObstacleType,
              typename std::enable_if<std::is_base_of<TrackBase, ObstacleType>::value, bool>::type = true>
    Vector3f Estimate(std::shared_ptr<ObstacleType> obs);

    /**
     * @brief estimate absolute velocity of obstacle
     *
     * @tparam ObstacleType obstacle type
     * @tparam std::enable_if<std::is_base_of<obstacle::ObstacleBaseT<Scalar>, ObstacleType>::value,
     * bool>::type  only type of ObstacleBaseT or its derived class use this function
     * @param obs pointer to obstacle
     * @return Vector3f absolute velocity
     */
    template <typename ObstacleType,
              typename std::enable_if<std::is_base_of<obstacle::ObstacleBaseT<Scalar>, ObstacleType>::value,
                                      bool>::type = true>
    Vector3f Estimate(std::shared_ptr<ObstacleType> obs);

private:
    Vector3f velocity_body_    = 0.f;
    Scalar   angular_velocity_ = 0.f;
};
}  // namespace perception
}  // namespace holo
#endif