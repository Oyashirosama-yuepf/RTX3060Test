/**
 * @file cubic_polynomial.c
 * @brief cubic polynomial
 * @author lijiawen (lijiawen@holomatic.com)
 * @date 2019-09-27
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>

#include <holo_c/numerics/cubic_polynomial.h>

void cubic_polynomial_init(struct CubicPolynomial* curve, float32_t c0, float32_t c1, float32_t c2, float32_t c3)
{
    assert(curve != NULL);

    curve->c0 = c0;
    curve->c1 = c1;
    curve->c2 = c2;
    curve->c3 = c3;
}

float32_t cubic_polynomial_get_result(struct CubicPolynomial* curve, float32_t input_x)
{
    assert(curve != NULL);

    return curve->c0 + input_x * (curve->c1 + input_x * (curve->c2 + input_x * curve->c3));
}
