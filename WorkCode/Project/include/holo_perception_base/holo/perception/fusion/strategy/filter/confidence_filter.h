/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file confidence_filter.h
 * @brief This header file defines confidence filter
 * @author wangming(wangming@holomatic.com)
 * @date "2021-10-16"
 */

#ifndef HOLO_PERCEPTION_FUSION_STRATEGY_FILTER_CONFIDENCE_FILTER_H_
#define HOLO_PERCEPTION_FUSION_STRATEGY_FILTER_CONFIDENCE_FILTER_H_

#include <holo/perception/fusion/track_base.h>

namespace holo
{
namespace perception
{
class ConfidenceFilter
{
public:
    using Scalar = holo::float32_t;

    /**
     * @brief whether confidence of obstacle is valid
     *
     * @param conf confidence of obstacle
     * @return bool_t true confidence of obstacle is valid else false
     */
    virtual bool_t IsValid(Scalar conf);

    /**
     * @brief Set confidence thresh
     *
     * @param conf_thresh thresh of confidence
     */
    void SetConfidence(Scalar conf_thresh)
    {
        confidence_thresh_ = conf_thresh;
    }

private:
    Scalar confidence_thresh_ = 0.9f;
};
}  // namespace perception
}  // namespace holo
#endif