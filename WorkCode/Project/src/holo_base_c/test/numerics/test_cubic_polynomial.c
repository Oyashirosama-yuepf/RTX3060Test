/**
 * @brief Unit test for cubic polynomial.
 * @author lijiawen(lijiawen@holomaitc.com)
 * @date 2019-09-27
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <unity.h>

#include <holo_c/core/types.h>
#include <holo_c/core/retcode.h>
#include <holo_c/numerics/cubic_polynomial.h>

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test void cubic_polynomial_init(struct CubicPolynomial* curve, float32_t c0, float32_t c1, float32_t c2, float32_t c3);
 */
static void test_cubic_polynomial_init(void)
{
    struct CubicPolynomial curve;

    cubic_polynomial_init(&curve, 1.0f, 2.0f, 3.0f, 4.0f);

    TEST_ASSERT_FLOAT_WITHIN(1e-8, 1.0f, curve.c0);
    TEST_ASSERT_FLOAT_WITHIN(1e-8, 2.0f, curve.c1);
    TEST_ASSERT_FLOAT_WITHIN(1e-8, 3.0f, curve.c2);
    TEST_ASSERT_FLOAT_WITHIN(1e-8, 4.0f, curve.c3);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test float32_t cubic_polynomial_get_result(struct CubicPolynomial* curve, float32_t input_x);
 */
static void test_cubic_polynomial_get_result(void)
{
    struct CubicPolynomial curve;

    cubic_polynomial_init(&curve, 1.0f, 2.0f, 3.0f, 4.0f);

    TEST_ASSERT_FLOAT_WITHIN(1e-8, 1.0f, cubic_polynomial_get_result(&curve, 0.0f));
    TEST_ASSERT_FLOAT_WITHIN(1e-8, 10.0f, cubic_polynomial_get_result(&curve, 1.0f));
    TEST_ASSERT_FLOAT_WITHIN(1e-8, 49.0f, cubic_polynomial_get_result(&curve, 2.0f));
    TEST_ASSERT_FLOAT_WITHIN(1e-8, -23.0f, cubic_polynomial_get_result(&curve, -2.0f));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_cubic_polynomial_init);
    RUN_TEST(test_cubic_polynomial_get_result);
    return UNITY_END();
}
