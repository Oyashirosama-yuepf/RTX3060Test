/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lattice_constant.h
 * @brief the header of the constant defination in lattice
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_LATTICE_CONSTANT_H_
#define _HOLO_PLANNING_LATTICE_CONSTANT_H_

#include <limits>

#include <holo/core/types.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief lattice epislon
 */
const float64_t LATTICE_EPISLON = 1e-6;

/**
 * @brief time interval in lattice planner
 */
const float64_t TIME_INTERVAL = 0.1;
/**
 * @brief predicted trajectory time length
 */
const float64_t TRAJECTORY_TIME_LENGTH = 8.0;

/**
 * @brief lateral offset cost opposite side weight
 */
const float64_t LATTICE_WEIGHT_OPPOSITE_SIDE_OFFSET = 20.0;

/**
 * @brief lateral offset cost same side weight
 */
const float64_t LATTICE_WEIGHT_SAME_SIDE_OFFSET = 1.0;

/**
 * @brief longitudinal offset cost weight(apollo cost function, not used yet)
 */
const float64_t LATTICE_WEIGHT_TARGET_SPEED = 1.0;

/**
 * @brief longitudinal dist offset cost weight(apollo cost function, not used yet)
 */
const float64_t LATTICE_WEIGHT_DIST_TRAVELLED = 10.0;

/**
 * @brief longitudinal offset cost weight
 */
const float64_t LATTICE_WEIGHT_LON_OBJECTIVE = 10.0;

/**
 * @brief longitudinal comfort cost weight
 */
const float64_t LATTICE_WEIGHT_LON_JERK = 1.0;

/**
 * @brief centripetal acceleration cost weight
 */
const float64_t LATTICE_WEIGHT_CENTRIPETAL_ACC = 1.5;

/**
 * @brief lateral offset cost weight
 */
const float64_t LATTICE_WEIGHT_LAT_OFFSET = 2.0;

/**
 * @brief lateral comfort cost weight
 */
const float64_t LATTICE_WEIGHT_LAT_COMFORT = 10.0;

/**
 * @brief minimum headway time
 */
const float64_t MIN_HEADWAY_TIME = 0.5;

/**
 * @brief longitudinal front safe distance
 */
const float64_t LON_FRONT_DIST_BUFFER = 5.0;

/**
 * @brief longitudinal rear safe distance
 */
const float64_t LON_REAR_DIST_BUFFER = 2.0;

/**
 * @brief lateral safe distance
 */
const float64_t LAT_DIST_BUFFER = 0.6;
}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif