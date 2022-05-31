/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file relative_velocity_matcher.h
 * @brief This header file defines relative velocity matcher
 * @author wangming(wangming@holomatic.com)
 * @date "2021-10-13"
 */

#ifndef HOLO_PERCEPTION_FUSION_STRATEGY_MATCHER_RELATIVE_VELOCITY_MATCHER_H_
#define HOLO_PERCEPTION_FUSION_STRATEGY_MATCHER_RELATIVE_VELOCITY_MATCHER_H_

#include <holo/perception/fusion/track_base.h>

namespace holo
{
namespace perception
{
class RelativeVelocityMatcher
{
public:
    using Scalar = holo::float32_t;

    /**
     * @brief determine whether relative velocity is matched
     *
     * @param lhs pointer to one obstacle
     * @param rhs pointer to another obstacle
     * @return bool_t true if relative velocity is matched else false
     */
    virtual bool_t IsMatch(const TrackBasePtr lhs, const TrackBasePtr rhs);

    /**
     * @brief Set the Parmas
     *
     * @param dvx_max_thresh thresh of dvx
     * @param dvy_max_thresh thresh of dvy
     */
    void SetParmas(Scalar dvx_max_thresh, Scalar dvy_max_thresh)
    {
        dvx_max_thresh_ = dvx_max_thresh;
        dvy_max_thresh_ = dvy_max_thresh;
    }

protected:
    /**
     * @brief Get absolute Dvx And Dvy
     *
     * @param lhs [in] pointer to one obstacle
     * @param rhs [in] pointer to another obstacle
     * @param dvx [out] absolute difference of velcoity in direction X
     * @param dvy [out] absolute difference of velcoity in direction Y
     */
    void getAbsoluteDvxAndDvy(const TrackBasePtr lhs, const TrackBasePtr rhs, Scalar& dvx, Scalar& dvy);

protected:
    Scalar dvx_max_thresh_ = 2.0f;
    Scalar dvy_max_thresh_ = 2.0f;
};
}  // namespace perception
}  // namespace holo
#endif