/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file filter_state.h
 * @brief This header file defines a bsae class of filter state of a snapshot.
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-06"
 */

#ifndef HOLO_PERCEPTION_TRACKING_FILTER_STATE_H_
#define HOLO_PERCEPTION_TRACKING_FILTER_STATE_H_

#include <string>

namespace holo
{
namespace perception
{
/**
 * @addtogroup tracking
 *
 * @{
 */

/**
 * @brief filter state and corresponding string
 *
 */
enum class FilterState : uint8_t
{
    PASSED = 0,
    FILTERED_BY_SIZE,
    FILTERED_BY_LATENCY,
    FILTER_BY_AREA_OR_RATIO,
    FILTERED_BY_SENSORID,
    FILTER_BY_WORK_ZONE,
    FILTER_BY_TRACK_PREDICTION,
    FILTER_BY_ROI,
    FILTER_BY_MOTION
};

/**
 * @}
 *
 */
}  // namespace perception
}  // namespace holo

#endif  //! HOLO_PERCEPTION_TRACKING_FILTER_STATE_H_
