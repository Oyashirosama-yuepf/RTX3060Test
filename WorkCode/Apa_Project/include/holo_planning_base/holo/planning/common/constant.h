/*!
 *  \brief constants for planning
 *  \author dongyong (dongyong@holomatic.com)
 *  \date Apr 17, 2018
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_CONSTANT_H_
#define _HOLO_PLANNING_CONSTANT_H_

#include <limits>

#include <holo/core/types.h>

namespace holo
{
namespace planning
{
// using to avoid precision when compare two float numbers
const float64_t ALMOST_ZERO = 10 * std::numeric_limits<float64_t>::epsilon();

// the maximum of double
const float64_t MAX_DOUBLE = 1e10;

// the max deceleration when passenger feel well
const float64_t DEC_MAX = -0.3;

const float64_t TIME_DIFF_TOL = 0.1 + 0.1 * 0.2;

// max speed limit 120km/h
const float64_t MAX_SPEED_LIMIT = 130.0 / 3.6;

const float64_t MAX_LANE_CHANGE_TIME = 12.0;
const float64_t MIN_LANE_CHANGE_TIME = 3.0;

const float64_t LANE_CHANGE_TIME_LOWER_BOUND = 10.0;
const float64_t TRAFFIC_JAM_TIME_LOWER_BOUND = 15.0;

const float64_t DEFAULT_DISTANCE     = 300.0;
const float64_t DEFAULT_MAX_VELOCITY = 25.0;
const float64_t PLANNING_TIME        = 2.0;

const uint32_t LANE_CONFIDENCE_LIMIT = 2;

const uint32_t  PILOT_LANE_CONFIDENCE_LIMIT = 3;
const float64_t PILOT_LANE_LENGTH_LIMIT     = 50.0;

const float64_t STEERING_WHEEL_RATIO = 16.2;
const float64_t MAXIMUM_ARKERMANN_CURVATURE_SPEED = 1.5;
const float64_t MINIMUM_YAWRATE_CURVATURE_SPEED = 1.0;

}  // namespace planning
}  // namespace holo

#endif
