/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file absolute_velocity_estimator.hpp
 * @brief This header file defines implementation of absolute velocity estimator
 * @author wangming(wangming@holomatic.com)
 * @date "2021-10-25"
 */
#ifndef HOLO_PERCEPTION_FUSION_STRATEGY_ABSOLUTE_VELOCITY_ESTIMATOR_HPP_
#define HOLO_PERCEPTION_FUSION_STRATEGY_ABSOLUTE_VELOCITY_ESTIMATOR_HPP_

#include <holo/perception/fusion/strategy/absolute_velocity_estimator.h>

namespace holo
{
namespace perception
{
template <typename ObstacleType,
          typename std::enable_if<std::is_base_of<TrackBase, ObstacleType>::value, bool>::type>
AbsoluteVelocityEstimator::Vector3f AbsoluteVelocityEstimator::Estimate(std::shared_ptr<ObstacleType> obs)
{
    const auto& props = obs->GetObstacleProperty();
    Scalar      x     = props.x;
    Scalar      y     = props.y;
    Scalar      vx    = props.vx;
    Scalar      vy    = props.vy;
    return {vx + velocity_body_[0] - y * angular_velocity_, vy + velocity_body_[1] + x * angular_velocity_, 0.0f};
}

template <typename ObstacleType,
          typename std::enable_if<
              std::is_base_of<obstacle::ObstacleBaseT<AbsoluteVelocityEstimator::Scalar>, ObstacleType>::value,
              bool>::type>
AbsoluteVelocityEstimator::Vector3f AbsoluteVelocityEstimator::Estimate(std::shared_ptr<ObstacleType> obs)
{
    Scalar x  = obs->GetPosition().GetX();
    Scalar y  = obs->GetPosition().GetY();
    Scalar vx = obs->GetRelativeVelocity()[0U];
    Scalar vy = obs->GetRelativeVelocity()[1U];
    return {vx + velocity_body_[0] - y * angular_velocity_, vy + velocity_body_[1] + x * angular_velocity_, 0.0f};
}
}  // namespace perception
}  // namespace holo
#endif