/**
 * @file angle_float32.h
 * @brief This header file defines angle.
 * @author duyanwei@holomatic.com
 * @date 2019-08-26
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_ANGLE_FLOAT32_H_
#define HOLO_C_GEOMETRY_ANGLE_FLOAT32_H_

#include <math.h>

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/vector_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief convert degree to radian
 *
 * @param degree angle in degree
 * @return float32_t
 */
float32_t radianf(float32_t degree);

/**
 * @brief convert degree to radian in the range [-PI, PI)
 *
 * @note naming format is similiar to std::atan and std::atan2
 * @param degree angle in degree
 * @return float32_t
 */
float32_t radian2f(float32_t degree);

/**
 * @brief convert radian to degree
 *
 * @param radian angle in radian
 * @return float32_t
 */
float32_t degreef(float32_t radian);

/**
 * @brief convert radian to degree in the range [-180, 180)
 *
 * @note naming format is similiar to std::atan and std::atan2
 * @param radian angle in radian
 * @return float32_t
 */
float32_t degree2f(float32_t radian);

/**
 * @brief normalize radian in the range [-PI, PI)
 *
 * @param radian angle in radian
 * @return float32_t
 */
float32_t radian_normalize(float32_t radian);

/**
 * @brief normalize radian in the range [-180, 180)
 *
 * @param degree angle in degree
 * @return float32_t
 */
float32_t degree_normalize(float32_t degree);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_ANGLE_FLOAT32_H_
