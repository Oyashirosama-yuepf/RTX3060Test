/**
 * @file test_angle_float32.c
 * @brief unit test of angle
 * @author duyanwei@holomatic.com
 * @date 2019-08-26
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/geometry/angle_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_radianf(void)
{
    const float32_t expected1 = M_PI / 4.0;
    const float32_t expected2 = -M_PI / 3.0;
    const float32_t expected3 = 3.0 * M_PI;

    // call method and check results
    TEST_ASSERT_EQUAL_FLOAT(expected1, radianf(45.0f));
    TEST_ASSERT_EQUAL_FLOAT(expected2, radianf(-60.0f));
    TEST_ASSERT_EQUAL_FLOAT(expected3, radianf(540.0f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_radian2f(void)
{
    const float32_t expected1 = M_PI / 4.0;
    const float32_t expected2 = M_PI * 5.0f / 3.0;
    const float32_t expected3 = M_PI;

    // call method and check results
    TEST_ASSERT_EQUAL_FLOAT(expected1, radian2f(45.0f));
    TEST_ASSERT_EQUAL_FLOAT(radian_normalize(expected2), radian2f(-60.0f));
    TEST_ASSERT_EQUAL_FLOAT(radian_normalize(expected3), radian2f(540.0f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_degreef(void)
{
    const float32_t expected1 = 45.0f;
    const float32_t expected2 = -60.0f;
    const float32_t expected3 = 540.0f;

    // call method and check results
    TEST_ASSERT_EQUAL_FLOAT(expected1, degreef(M_PI / 4.0));
    TEST_ASSERT_EQUAL_FLOAT(expected2, degreef(-M_PI / 3.0));
    TEST_ASSERT_EQUAL_FLOAT(expected3, degreef(3.0 * M_PI));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_degree2f(void)
{
    const float32_t expected1 = 45.0f;
    const float32_t expected2 = 300.0f;
    const float32_t expected3 = 180.0f;

    // call method and check results
    TEST_ASSERT_EQUAL_FLOAT(expected1, degree2f(M_PI / 4.0));
    TEST_ASSERT_EQUAL_FLOAT(degree_normalize(expected2), degree2f(-M_PI / 3.0));
    TEST_ASSERT_EQUAL_FLOAT(degree_normalize(expected3), degree2f(3.0 * M_PI));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_radianf);
    RUN_TEST(test_radian2f);
    RUN_TEST(test_degreef);
    RUN_TEST(test_degree2f);
    return UNITY_END();
}
