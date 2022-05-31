/*!
 * @file test_convex_polygon2_float32.c
 * @brief unit test of convex polygon2
 * @author duyanwei@holomatic.com
 * @date 2019-08-24
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/geometry/convex_polygon2_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_init(void)
{
    struct ConvexPolygon2f polygon;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_init(&polygon));
    TEST_ASSERT_EQUAL(0u, polygon.size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_init_from_point2f_array(void)
{
    const uint8_t  buffer_size = 5u;
    struct Point2f buffer[buffer_size];
    {
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, 0.0f);
    }

    struct ConvexPolygon2f self;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_init_from_point2f_array(&self, buffer, buffer_size));
    TEST_ASSERT_EQUAL(buffer_size, self.size);

    struct Point2f actual;
    point2f_init(&actual);
    for (uint8_t i = 0u; i < buffer_size; i++)
    {
        convex_polygon2f_get_vertex(&self, i, &actual);
        TEST_ASSERT_TRUE(point2f_is_equal(&buffer[i], &actual));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_init_from_convex_polygon2f(void)
{
    struct ConvexPolygon2f other;
    {
        const uint8_t  buffer_size = 5u;
        struct Point2f buffer[buffer_size];
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&other, buffer, buffer_size);
    }

    struct ConvexPolygon2f self;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_init_from_convex_polygon2f(&self, &other));
    TEST_ASSERT_TRUE(convex_polygon2f_is_equal(&self, &other));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_is_valid(void)
{
    struct ConvexPolygon2f first;
    convex_polygon2f_init(&first);

    struct ConvexPolygon2f second;
    {
        const uint8_t  buffer_size = 5u;
        struct Point2f buffer[buffer_size];
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&second, buffer, buffer_size);
    }

    struct ConvexPolygon2f third;
    {
        const uint8_t  buffer_size = 6u;
        struct Point2f buffer[buffer_size];
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], 0.0f, -0.5f);
        point2f_init_from_scalars(&buffer[4], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[5], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&third, buffer, buffer_size);
    }

    // call method and check results
    TEST_ASSERT_FALSE(convex_polygon2f_is_valid(&first));
    TEST_ASSERT_TRUE(convex_polygon2f_is_valid(&second));
    TEST_ASSERT_FALSE(convex_polygon2f_is_valid(&third));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_is_equal(void)
{
    struct ConvexPolygon2f self;
    {
        const uint8_t  buffer_size = 5u;
        struct Point2f buffer[buffer_size];
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&self, buffer, buffer_size);
    }

    struct ConvexPolygon2f other;
    {
        const uint8_t  buffer_size = 5u;
        struct Point2f buffer[buffer_size];
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&other, buffer, buffer_size);
    }

    struct ConvexPolygon2f third;
    {
        const uint8_t  buffer_size = 6u;
        struct Point2f buffer[buffer_size];
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], 0.0f, -2.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[5], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&third, buffer, buffer_size);
    }

    // call method and check results
    TEST_ASSERT_TRUE(convex_polygon2f_is_equal(&self, &other));
    TEST_ASSERT_FALSE(convex_polygon2f_is_equal(&self, &third));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_if_contains_point2f(void)
{
    struct ConvexPolygon2f polygon;
    {
        const uint8_t  buffer_size = 5u;
        struct Point2f buffer[buffer_size];
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&polygon, buffer, buffer_size);
    }

    struct Point2f pt1;
    point2f_init_from_scalars(&pt1, 0.0f, 0.0f);

    struct Point2f pt2;
    point2f_init_from_scalars(&pt2, 1.0f, 1.0f);

    // call method and check results
    TEST_ASSERT_TRUE(convex_polygon2f_if_contains_point2f(&polygon, &pt1));
    TEST_ASSERT_FALSE(convex_polygon2f_if_contains_point2f(&polygon, &pt2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_add_vertex(void)
{
    struct ConvexPolygon2f polygon;
    convex_polygon2f_init(&polygon);

    // call method and check results
    struct Point2f vertex;

    point2f_init_from_scalars(&vertex, 0.0f, 1.0f);
    TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_add_vertex(&polygon, &vertex));

    point2f_init_from_scalars(&vertex, 1.0f, 0.0f);
    TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_add_vertex(&polygon, &vertex));

    point2f_init_from_scalars(&vertex, 1.0f, -1.0f);
    TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_add_vertex(&polygon, &vertex));

    point2f_init_from_scalars(&vertex, -1.0f, -1.0f);
    TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_add_vertex(&polygon, &vertex));

    point2f_init_from_scalars(&vertex, -1.0f, 0.0f);
    TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_add_vertex(&polygon, &vertex));

    point2f_init_from_scalars(&vertex, 0.0f, 0.0f);
    TEST_ASSERT_EQUAL(RC_FAIL, convex_polygon2f_add_vertex(&polygon, &vertex));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_set_vertex(void)
{
    struct ConvexPolygon2f polygon;
    {
        const uint8_t  buffer_size = 5u;
        struct Point2f buffer[buffer_size];
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&polygon, buffer, buffer_size);
    }

    // call method and check results
    struct Point2f vertex;
    point2f_init_from_scalars(&vertex, 0.0f, 0.0f);

    TEST_ASSERT_EQUAL(RC_FAIL, convex_polygon2f_set_vertex(&polygon, 0u, &vertex));
    TEST_ASSERT_EQUAL(RC_FAIL, convex_polygon2f_set_vertex(&polygon, 1u, &vertex));

    point2f_init_from_scalars(&vertex, 0.0f, 2.0f);
    TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_set_vertex(&polygon, 0u, &vertex));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_get_vertex(void)
{
    struct ConvexPolygon2f polygon;

    const uint8_t  buffer_size = 5u;
    struct Point2f buffer[buffer_size];
    {
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&polygon, buffer, buffer_size);
    }

    // call method and check results
    struct Point2f actual;
    point2f_init(&actual);

    for (uint8_t i = 0u; i < buffer_size; i++)
    {
        TEST_ASSERT_EQUAL(RC_SUCCESS, convex_polygon2f_get_vertex(&polygon, i, &actual));
        TEST_ASSERT_TRUE(point2f_is_equal(&buffer[i], &actual));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_convex_polygon2f_get_vertex_size(void)
{
    struct ConvexPolygon2f polygon;
    convex_polygon2f_init(&polygon);

    // call method and check results
    TEST_ASSERT_EQUAL(0u, convex_polygon2f_get_vertex_size(&polygon));

    {
        const uint8_t  buffer_size = 5u;
        struct Point2f buffer[buffer_size];
        point2f_init_from_scalars(&buffer[0], 0.0f, 1.0f);
        point2f_init_from_scalars(&buffer[1], 1.0f, 0.0f);
        point2f_init_from_scalars(&buffer[2], 1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[3], -1.0f, -1.0f);
        point2f_init_from_scalars(&buffer[4], -1.0f, 0.0f);
        convex_polygon2f_init_from_point2f_array(&polygon, buffer, buffer_size);
    }

    TEST_ASSERT_EQUAL(5u, convex_polygon2f_get_vertex_size(&polygon));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_convex_polygon2f_init);
    RUN_TEST(test_convex_polygon2f_init_from_point2f_array);
    RUN_TEST(test_convex_polygon2f_init_from_convex_polygon2f);
    RUN_TEST(test_convex_polygon2f_is_valid);
    RUN_TEST(test_convex_polygon2f_is_equal);
    RUN_TEST(test_convex_polygon2f_if_contains_point2f);
    RUN_TEST(test_convex_polygon2f_add_vertex);
    RUN_TEST(test_convex_polygon2f_set_vertex);
    RUN_TEST(test_convex_polygon2f_get_vertex);
    RUN_TEST(test_convex_polygon2f_get_vertex_size);
    return UNITY_END();
}