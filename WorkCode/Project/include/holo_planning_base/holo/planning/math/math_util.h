/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-10-30
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_MATH_MATH_UTIL_H_
#define _HOLO_PLANNING_MATH_MATH_UTIL_H_

#include <holo/planning/common/curve_point.h>
#include <holo/planning/common/headers.h>

namespace holo
{
namespace planning
{
namespace math
{
/**
 * @brief      Normalize angle to [-PI, PI).
 *
 * @param[in]  angle  The original value of the angle.
 *
 * @return     The normalized value of the angle.
 */
float64_t NormalizeAngle(const float64_t angle);

/**
 * @brief      Spherical linear interpolation between two angles. The two angles
 *             are within range [-M_PI, M_PI).
 *
 * @param[in]  a0    The value of the first angle.
 * @param[in]  t0    The interpolation parameter of the first angle.
 * @param[in]  a1    The value of the second angle.
 * @param[in]  t1    The interpolation parameter of the second angle.
 * @param[in]  t     The interpolation parameter for interpolation.
 *
 * @return     Interpolated angle.
 */
float64_t Slerp(const float64_t a0, const float64_t t0, const float64_t a1, const float64_t t1, const float64_t t);

CurvePoint InterpolateUsingLinearApproximation(const CurvePoint& p0, const CurvePoint& p1, const float64_t s);

float64_t
LinearInterpolation(const float64_t x1, const float64_t y1, const float64_t x2, const float64_t y2, const float64_t x);

/**
 * @brief The parameter used for linear interpolation
 */
struct Param1D
{
    std::vector<float64_t> x;       ///< Inflection point on X-axis
    std::vector<float64_t> points;  ///< Inflection value
};

/**
 * @brief Linear Interpolation in 1-Dimension
 *
 * @param param the 1-Dimension parameters
 * @param x the value in x-axis
 *
 * @return the interpolated value
 */
float64_t LinearInterpolation1D(Param1D const& param, float64_t x);

/**
 * @brief The parameter used for quadratic linear interpolation
 */
struct Param2D
{
    std::vector<float64_t>              x;       ///< Inflection point on X-axis
    std::vector<float64_t>              y;       ///< Inflection point on Y-axis
    std::vector<std::vector<float64_t>> points;  ///< Inflection value
};

/**
 * @brief Linear Interpolation in 2-Dimension
 *
 * @param param the 2-Dimension parameters
 * @param x the value in x-axis
 * @param y the value in y-axis
 *
 * @return the interpolated value
 */
float64_t LinearInterpolation2D(Param2D const& param, float64_t x, float64_t y);

/**
 * @brief a classic function, it's another name is Logistic function.
 *
 * @details The sigmoid function is also called the logistic function, which is used for hidden layer neuron output.
 * The value range is (0,1). It can map a real number to the range of (0,1) and can be used for binary
 * classification. The effect is better when the feature difference is more complicated or the difference is not
 * particularly large.
 */
static inline float64_t Sigmoid(float64_t x)
{
    return 1.0 / (1.0 + std::exp(-x));
}

/**
 * @brief The modified logistic function.
 *
 * @details A function that returns a value between 0 and 1 for x in the range [0, infinity] and -1 to 1 for x in the
 * range [-infinity, infinity].
 */
static inline float64_t Logisitic(float64_t x)
{
    return 2.0 / (1.0 + std::exp(-x)) - 1.0;
}

}  // namespace math
}  // namespace planning
}  // namespace holo

#endif
