/*!
 * @file test_point3_float64.c
 * @brief unit test of point3
 * @author duyanwei@holomatic.com
 * @date 2019-08-16
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/geometry/point3_float64.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_init_from_scalars(void)
{
    struct Point3d pt;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_init_from_scalars(&pt, 1.0, 2.0, 3.0));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, point3d_get_x(&pt));
    TEST_ASSERT_EQUAL_DOUBLE(2.0, point3d_get_y(&pt));
    TEST_ASSERT_EQUAL_DOUBLE(3.0, point3d_get_z(&pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_init(void)
{
    struct Point3d pt;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_init(&pt));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point3d_get_x(&pt));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point3d_get_y(&pt));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point3d_get_z(&pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_init_from_array(void)
{
    float64_t array[3];
    for (uint8_t i = 0; i < 3u; i++)
    {
        array[i] = i + 1.0;
    }

    struct Point3d point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_init_from_array(&point, array, 3));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_init_from_point3d(void)
{
    struct Point3d other;
    point3d_init_from_scalars(&other, 1.0, 2.0, 3.0);

    struct Point3d point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_init_from_point3d(&point, &other));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_is_valid(void)
{
    struct Point3d point;
    point3d_init_from_scalars(&point, 1.0, 2.0, 3.0);

    // call method and check results
    TEST_ASSERT_TRUE(point3d_is_valid(&point));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_is_equal(void)
{
    struct Point3d point;
    struct Point3d other;

    point3d_init_from_scalars(&point, 1.0, 2.0, 3.0);
    point3d_init_from_scalars(&other, 1.0, 2.0, 3.0);

    // call method and check results
    TEST_ASSERT_TRUE(point3d_is_equal(&point, &other));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_add(void)
{
    struct Point3d pt1;
    struct Point3d pt2;
    struct Point3d point;

    point3d_init_from_scalars(&pt1, 1.0, 2.0, 3.0);
    point3d_init_from_scalars(&pt2, 1.0, 2.0, 3.0);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_add(&pt1, &pt2, &point));
    TEST_ASSERT_EQUAL_DOUBLE(2.0, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(4.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(6.0, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_negate(void)
{
    struct Point3d point;
    point3d_init_from_scalars(&point, 1.0, 2.0, 3.0);

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_negate(&point));
    TEST_ASSERT_EQUAL_DOUBLE(-1.0, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(-2.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(-3.0, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_multiply_float64(void)
{
    struct Point3d pt;
    point3d_init_from_scalars(&pt, 1.0, 2.0, 3.0);

    struct Point3d point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_multiply_float64(&pt, 2.0, &point));
    TEST_ASSERT_EQUAL_DOUBLE(2.0, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(4.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(6.0, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_divide_float64(void)
{
    struct Point3d pt;

    point3d_init_from_scalars(&pt, 1.0, 2.0, 3.0);

    struct Point3d point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_divide_float64(&pt, 2.0, &point));
    TEST_ASSERT_EQUAL_DOUBLE(0.5, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(1.5, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_dist_sqr(void)
{
    struct Point3d point;
    struct Point3d other;
    point3d_init_from_scalars(&point, 1.0, 2.0, 3.0);
    point3d_init_from_scalars(&other, 4.0, 2.0, 7.0);

    // call method and check results
    const float64_t expected = 25.0;
    float64_t       actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_dist_sqr(&point, &other, &actual));
    TEST_ASSERT_EQUAL_DOUBLE(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_dist(void)
{
    struct Point3d point;
    struct Point3d other;
    point3d_init_from_scalars(&point, 1.0, 2.0, 3.0);
    point3d_init_from_scalars(&other, 4.0, 2.0, 7.0);

    // call method and check results
    const float64_t expected = 5.0;
    float64_t       actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_dist(&point, &other, &actual));
    TEST_ASSERT_EQUAL_DOUBLE(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_is_finite(void)
{
    struct Point3d point;
    point3d_init_from_scalars(&point, 1.0, 2.0, 3.0);

    // call method and check results
    TEST_ASSERT_TRUE(point3d_is_finite(&point));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_is_zero(void)
{
    struct Point3d pt1;
    struct Point3d pt2;
    point3d_init_from_scalars(&pt1, 0.0, 0.0, 0.0);
    point3d_init_from_scalars(&pt2, 4.0, 2.0, 7.0);

    // call method and check results
    TEST_ASSERT_TRUE(point3d_is_zero(&pt1));
    TEST_ASSERT_FALSE(point3d_is_zero(&pt2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_set_constant(void)
{
    struct Point3d point;

    // call method and check results
    const float64_t expected = -1.0;
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_set_constant(&point, expected));
    TEST_ASSERT_EQUAL_DOUBLE(expected, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(expected, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(expected, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_set_zero(void)
{
    struct Point3d point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_set_zero(&point));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_set_unit_x(void)
{
    struct Point3d point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_set_unit_x(&point));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_set_unit_y(void)
{
    struct Point3d point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_set_unit_y(&point));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3d_set_unit_z(void)
{
    struct Point3d point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3d_set_unit_z(&point));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point.x);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, point.y);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, point.z);
}

static void test_point3d_set_x_y_z(void)
{
    struct Point3d point;

    point3d_set_x(&point, 1.0);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, point3d_get_x(&point));
    point3d_set_y(&point, 2.0);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, point3d_get_y(&point));
    point3d_set_z(&point, 3.0);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, point3d_get_z(&point));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_point3d_init_from_scalars);
    RUN_TEST(test_point3d_init);
    RUN_TEST(test_point3d_init_from_array);
    RUN_TEST(test_point3d_init_from_point3d);
    RUN_TEST(test_point3d_is_valid);
    RUN_TEST(test_point3d_is_equal);
    RUN_TEST(test_point3d_add);
    RUN_TEST(test_point3d_negate);
    RUN_TEST(test_point3d_multiply_float64);
    RUN_TEST(test_point3d_divide_float64);
    RUN_TEST(test_point3d_dist_sqr);
    RUN_TEST(test_point3d_dist);
    RUN_TEST(test_point3d_is_finite);
    RUN_TEST(test_point3d_is_zero);
    RUN_TEST(test_point3d_set_constant);
    RUN_TEST(test_point3d_set_zero);
    RUN_TEST(test_point3d_set_unit_x);
    RUN_TEST(test_point3d_set_unit_y);
    RUN_TEST(test_point3d_set_unit_z);
    RUN_TEST(test_point3d_set_x_y_z);
    return UNITY_END();
}
