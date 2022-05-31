/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file position_filter.h
 * @brief This header file defines position filter
 * @author wangming(wangming@holomatic.com)
 * @date "2021-10-16"
 */

#ifndef HOLO_PERCEPTION_FUSION_STRATEGY_FILTER_POSITION_FILTER_H_
#define HOLO_PERCEPTION_FUSION_STRATEGY_FILTER_POSITION_FILTER_H_

#include <holo/geometry/details/point3.h>
#include <holo/perception/fusion/track_base.h>

namespace holo
{
namespace perception
{
class PositionFilter
{
public:
    using Scalar = holo::float32_t;
    using Point3 = holo::geometry::details::Point3T<Scalar>;

    /**
     * @brief whether position of obstacle is valid
     *
     * @param position position of obstacle
     * @return bool_t true position of obstacle is valid else false
     */
    virtual bool_t IsValid(const Point3& position);

    /**
     * @brief Set the Params
     *
     * @param x_min min x
     * @param x_max max x
     * @param y_min min y
     * @param y_max max y
     */
    void SetParams(Scalar x_min, Scalar x_max, Scalar y_min, Scalar y_max)
    {
        x_min_thresh_ = x_min;
        x_max_thresh_ = x_max;
        y_min_thresh_ = y_min;
        y_max_thresh_ = y_max;
    }

private:
    Scalar x_min_thresh_ = -100.f;
    Scalar y_min_thresh_ = -18.f;
    Scalar x_max_thresh_ = 120.f;
    Scalar y_max_thresh_ = 18.f;
};
}  // namespace perception
}  // namespace holo
#endif