/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file position_matcher.h
 * @brief This header file defines position matcher
 * @author wangming(wangming@holomatic.com)
 * @date "2021-10-14"
 */

#ifndef HOLO_PERCEPTION_FUSION_STRATEGY_MATCHER_POSITION_MATCHER_H_
#define HOLO_PERCEPTION_FUSION_STRATEGY_MATCHER_POSITION_MATCHER_H_

#include <holo/perception/fusion/track_base.h>

namespace holo
{
namespace perception
{
class PositionMatcher
{
public:
    using Scalar = holo::float32_t;

    /**
     * @brief etermine whether position(x, y) is matched
     * @details use SetParams before this function
     * @param lhs_x position x of one obstacle
     * @param lhs_y position y of one obstacle
     * @param rhs_x position x of another obstacle
     * @param rhs_y position y of another obstacle
     * @return bool_t true if position(x, y) is matched else false
     */
    virtual bool_t IsMatch(Scalar lhs_x, Scalar lhs_y, Scalar rhs_x, Scalar rhs_y);

    /**
     * @brief Set the params
     *
     * @param dx_max_thresh thresh of dx
     * @param dy_max_thresh thresh of dy
     */
    void SetParams(Scalar dx_max_thresh, Scalar dy_max_thresh)
    {
        dx_max_thresh_ = dx_max_thresh;
        dy_max_thresh_ = dy_max_thresh;
    }

private:
    Scalar dx_max_thresh_ = 2.0f;
    Scalar dy_max_thresh_ = 2.0f;
};
}  // namespace perception
}  // namespace holo
#endif