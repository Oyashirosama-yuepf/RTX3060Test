/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rec_length_width_matcher.h
 * @brief This header file defines rectangle length width matcher
 * @author wangming(wangming@holomatic.com)
 * @date "2021-10-14"
 */

#ifndef HOLO_PERCEPTION_FUSION_STRATEGY_MATCHER_REC_LENGTH_WIDTH_MATCHER_H_
#define HOLO_PERCEPTION_FUSION_STRATEGY_MATCHER_REC_LENGTH_WIDTH_MATCHER_H_

#include <holo/perception/fusion/track_base.h>

namespace holo
{
namespace perception
{
/**
 * @brief rectangle width length matcher
 * @ref https://holomatic.feishu.cn/docs/doccneOBOeWSmv5K4a6hg4mQuKg
 */
class RecLengthWidthMatcher
{
public:
    using Scalar = holo::float32_t;

    /**
     * @brief whether obstacle rectangle is matched
     *
     * @param lhs pointer to one obstacle
     * @param rhs pointer to another obstacle
     * @return bool_t true if obstacle rectangle is matched else false
     */
    virtual bool_t IsMatch(const TrackBasePtr lhs, const TrackBasePtr rhs);

    /**
     * @brief compute rectangle dist
     *
     * @param lhs [in] pointer to one obstacle
     * @param rhs [in] pointer to another obstacle
     * @param rec_dx [out] distance of x between obstacle rectangles
     * @param rec_dy [out] distance of y between obstacle rectangles
     */
    static void ComputeRecDist(const TrackBasePtr lhs, const TrackBasePtr rhs, Scalar& rec_dx, Scalar& rec_dy);

    /**
     * @brief Set the Params
     *
     * @param rec_dx_max_thresh thresh of rec_dx
     * @param rec_dy_max_thresh thresh of rec_dy
     * @param dy_max_thresh thresh of dy
     * @param dy_max_thresh thresh of dx
     */
    void SetParams(Scalar rec_dx_max_thresh, Scalar rec_dy_max_thresh, Scalar dy_max_thresh,
                   Scalar dx_max_thresh = 50.f);

private:
    Scalar rec_dx_max_thresh_ = 2.0f;
    Scalar rec_dy_max_thresh_ = 2.0f;
    Scalar dy_max_thresh_     = 2.0f;
    Scalar dx_max_thresh_     = 50.f;
};
}  // namespace perception
}  // namespace holo
#endif