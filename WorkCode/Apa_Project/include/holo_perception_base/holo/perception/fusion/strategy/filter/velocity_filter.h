/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velocity_filter.h
 * @brief This header file defines velocity filter
 * @author wangming(wangming@holomatic.com)
 * @date "2021-10-16"
 */

#ifndef HOLO_PERCEPTION_FUSION_STRATEGY_FILTER_VELOCITY_FILTER_H_
#define HOLO_PERCEPTION_FUSION_STRATEGY_FILTER_VELOCITY_FILTER_H_

#include <holo/numerics/vector.h>
#include <holo/perception/fusion/track_base.h>

namespace holo
{
namespace perception
{
class VelocityFilter
{
public:
    using Vector3f = holo::numerics::Vector3f;
    using Scalar   = holo::float32_t;

    /**
     * @brief whether velocity of obstacle is valid
     *
     * @param velocity velocity of obstacle
     * @return bool_t true velocity of obstacle is valid else false
     */
    virtual bool_t IsValid(const Vector3f& velocity);

    /**
     * @brief Set the vx_min_thresh
     *
     * @param vx_min thresh of min vx
     */
    void SetVxMinThresh(Scalar vx_min)
    {
        vx_min_thresh_ = vx_min;
    }

private:
    Scalar vx_min_thresh_ = 2.5f;
};
}  // namespace perception
}  // namespace holo
#endif