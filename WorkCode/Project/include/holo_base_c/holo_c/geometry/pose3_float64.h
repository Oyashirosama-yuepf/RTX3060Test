/*!
 * @file pose3_float64.h
 * @brief This header file defines pose in 3D.
 * @author duyanwei@holomatic.com
 * @date 2019-08-11
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_POSE3_FLOAT64_H_
#define HOLO_C_GEOMETRY_POSE3_FLOAT64_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point3_float64.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @todo this is a temporary fix to provide struct Pose3 with float64_t,
 *       it only provides declaration without any other functions
 * @date 2019-09-10
 * @author liwenjun@holomatic.com
 */

/**
 * @brief define common float32_t matrix struct
 *
 */
struct Matrix33d
{
    uint8_t   rows;     ///< row dimension of matrix
    uint8_t   cols;     ///< col dimension of matrix
    uint16_t  size;     ///< size (row x col) of matrix
    float64_t base[9];  ///< pointer of allocated memory
};

/**
 * @brief define Rot3d struct
 *
 */
struct Rot3d
{
    struct Matrix33d m;
};

/**
 * @brief define pose3d struct
 *
 */
struct Pose3d
{
    struct Rot3d   rotation;
    struct Point3d translation;
};

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_POSE3_FLOAT64_H_
