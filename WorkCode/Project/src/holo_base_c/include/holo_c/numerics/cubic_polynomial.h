/**
 * @file cubic_polynomial.h
 * @brief cubic polynomial
 * @author lijiawen (lijiawen@holomatic.com)
 * @date 2019-09-27
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_NUMERICS_CUBIC_POLYNOMIAL_H_
#define HOLO_C_NUMERICS_CUBIC_POLYNOMIAL_H_

#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief       This structure represents a cubic polynomial:
 *              f(x) = c0 + c1 * x + c2 * x^2 + c3 * x^3;
 */
struct CubicPolynomial
{
    float32_t c0;
    float32_t c1;
    float32_t c2;
    float32_t c3;
};

/**
 * @brief       Initialize cubic polynomial by input parameters
 *
 * @param       curve Pointer to CubicPolynomial structure
 * @param       c0 Parameter of cubic polynomial
 * @param       c1 Parameter of cubic polynomial
 * @param       c2 Parameter of cubic polynomial
 * @param       c3 Parameter of cubic polynomial
 */
void cubic_polynomial_init(struct CubicPolynomial* curve, float32_t c0, float32_t c1, float32_t c2, float32_t c3);

/**
 * @brief       Get the result of cubic polynomial
 *
 * @param       curve Pointer to CubicPolynomial structure
 * @param       input_x The input x value
 *
 * @return      output value of cubic polynomial
 */
float32_t cubic_polynomial_get_result(struct CubicPolynomial* curve, float32_t input_x);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_NUMERICS_CUBIC_POLYNOMIAL_H_
