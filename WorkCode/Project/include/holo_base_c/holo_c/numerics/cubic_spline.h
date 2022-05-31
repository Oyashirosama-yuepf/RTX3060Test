/**
 * @file cubic_spline.h
 * @brief the header of cubic spline
 * @author zhengshaoqian&lijiawen(zhengshaoqian@holomatic.com&lijiawen@holomatic.com)
 * @date 2019-09-26
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_NUMERICS_CUBIC_SPLINE_H_
#define HOLO_C_NUMERICS_CUBIC_SPLINE_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2.h>
#include <holo_c/numerics/cubic_polynomial.h>

#define CUBIC_SPLINE_MIN_POINTS_NUM 4
#define CUBIC_SPLINE_MAX_POINTS_NUM 10

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This function is generated from Matlab, so the coding-style maybe strange.
 * It is a original version: there is no changes on it.
 * MATLAB Coder version: 4.0 (R2018a)
 */
void splinepp(const float x_data[], const int x_size[2], const float y_data[], const int y_size[2],
              float pp_breaks_data[], int pp_breaks_size[2], float pp_coefs_data[], int pp_coefs_size[3]);

/**
 * @brief This structure represents a cubic spline.
 *
 * @detail It is made up of several parts. Each part is a cubic polynomial. CubicSpline generate every cubic
 *         polynomial's parameters by using spline.
 */
struct CubicSpline
{
    struct CubicPolynomial spline_func[CUBIC_SPLINE_MAX_POINTS_NUM - 1];
    float32_t              x_value[CUBIC_SPLINE_MAX_POINTS_NUM];
    uint32_t               size;
};

/**
 * @brief Initialize CubicSpline
 *
 * @param spline CubicSpline Pointer.
 * @param point_list List of interpolation point coordinate.
 * @param size The nums of interpolate point.
 *
 * @return RC_SUCCESS init successfully
 * @return RC_NUMERICS_CUBIC_SPLINE_LACK_POINTS input point list's size is too small
 * @return RC_NUMERICS_CUBIC_SPLINE_OVERFLOW_POINTS input point list's size is too large
 * @return RC_NUMERICS_CUBIC_SPLINE_INVALID_POINTLIST input point list's sequence is invalid
 */
retcode_t cubic_spline_init(struct CubicSpline* spline, const struct Point2f* point_list, uint32_t size);

/**
 * @brief According to x-interpolation, get y.
 *
 * @param spline CubicSpline Pointer
 * @param x The input x-point.
 *
 * @return interpolate output
 */
float32_t cubic_spline_interpolate(struct CubicSpline* spline, float32_t x);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_NUMERICS_CUBIC_SPLINE_H_ */
