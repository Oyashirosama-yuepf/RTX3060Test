/**
 * @brief Unit test for cubic spline.
 * @author zhengshaoqian(zhengshaoqian@holomaitc.com)
 * @date 2019-09-27
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <unity.h>

#include <holo_c/core/types.h>
#include <holo_c/core/retcode.h>
#include <holo_c/numerics/cubic_spline.h>

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t cubic_spline_init(struct CubicSpline* spline, const struct Point2f* point_list, uint32_t size);
 */
static void test_cubic_spline_init(void)
{
    uint32_t i;
    struct Point2f point_list[6], point_list1[6];
    struct CubicSpline spline;
    float32_t x[6] = {4,13.8,19.4,22.2,25,27.7};
    float32_t x1[6] = {1.1, 2.2, 3.3, 2.2, 5.5, 4.4};
    float32_t y[6] = {1.0,0.4,0.2,0.15,0.1,0.05};

    for(i = 0; i<6; i++)
    {
        point_list[i].x = x[i];
        point_list[i].y = y[i];
        point_list1[i].x = x1[i];
        point_list1[i].y = y[i];
    }
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, cubic_spline_init(&spline, point_list, 6));
    TEST_ASSERT_EQUAL_UINT32(RC_NUMERICS_CUBIC_SPLINE_LACK_POINTS, cubic_spline_init(&spline, point_list, 2));
    TEST_ASSERT_EQUAL_UINT32(RC_NUMERICS_CUBIC_SPLINE_OVERFLOW_POINTS, cubic_spline_init(&spline, point_list, 18));
    TEST_ASSERT_EQUAL_UINT32(RC_NUMERICS_CUBIC_SPLINE_INVALID_POINTLIST, cubic_spline_init(&spline, point_list1, 6));
}
/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test float32_t cubic_spline_interpolate(struct CubicSpline* spline, float32_t x);
 */
static void test_cubic_spline_interpolate(void)
{
    uint32_t i;
    struct Point2f point_list[6];
    struct CubicSpline spline;
    float32_t x[6] = {4,13.8,19.4,22.2,25,27.7};
    float32_t y[6] = {1.0,0.4,0.2,0.15,0.1,0.05};
    float32_t tmp;

    for(i = 0; i<6; i++)
    {
        point_list[i].x = x[i];
        point_list[i].y = y[i];
    }

    cubic_spline_init(&spline, point_list, 6);
    tmp = cubic_spline_interpolate(&spline, 10);

    TEST_ASSERT_FLOAT_WITHIN(1e-3, 0.605283f, tmp);
}

int main ()
{
    UNITY_BEGIN();

    RUN_TEST(test_cubic_spline_init);
    RUN_TEST(test_cubic_spline_interpolate);

    return UNITY_END();
}