/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file types.h
 * @brief the definition of types
 * @author yangpeiwen@holomatic.com
 * @date 2020-10-26
 */

#ifndef HOLO_CALIBRATION_RADAR_TYPES_H_
#define HOLO_CALIBRATION_RADAR_TYPES_H_

#include <holo/log/hololog.h>
#include <holo/common/chassis_state.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/point3.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace calibration
{
namespace radar
{
/**
 * @addtogroup radar
 * @{
 *
 */

/**
 * @brief define basic types
 *
 * @note define sepcific types for radar module or types from holo::calibration:: will be used
 * @author yangpeiwen@holomatic.com
 */

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief  basic geometry types
 *
 */
using Scalar       = holo::float64_t;
using Scalar_32_t  = holo::float32_t;
using Point3Type   = holo::geometry::Point3T<Scalar>;
using ChassisState = holo::common::ChassisState;
using Timestamp    = holo::common::Timestamp;

///////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup calibration
 * @brief the wrapper of radar point in radar frame
 */
struct RadarPoint
{
    // obstacle id
    uint32_t obs_id;

    // velocity along x-axis
    Scalar vx;

    // velocity along y-axis
    Scalar vy;

    // translation along x-axis
    Scalar tx;

    // translation along y-axis
    Scalar ty;
};
/**
 * @ingroup calibration
 * @brief the wrapper of radar points clouds
 */
struct RadarFrame
{
    // time stamp
    Timestamp time;

    // points cloud
    std::vector<RadarPoint> radar_points;
};
using RadarFrames = std::vector<RadarFrame>;

/**
 * @brief correspondence
 */
struct Correspondence
{
};  // correspondence

/**
 * @}
 *
 */
}  // namespace radar
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_RADAR_TYPES_H_