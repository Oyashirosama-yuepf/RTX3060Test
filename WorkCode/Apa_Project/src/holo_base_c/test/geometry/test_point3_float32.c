/*!
 * @file test_point3_float32.c
 * @brief unit test of point3
 * @author duyanwei@holomatic.com
 * @date 2019-08-16
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/geometry/point3_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_init_from_scalars(void)
{
    struct Point3f pt;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_init_from_scalars(&pt, 1.0f, 2.0f, 3.0f));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, pt.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, pt.y);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, pt.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_init(void)
{
    struct Point3f pt;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_init(&pt));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_init_from_array(void)
{
    retcode_t rc;
    float32_t array[3];
    for (uint8_t i = 0; i < 3u; i++)
    {
        array[i] = i + 1.0f;
    }

    struct Point3f point;

    rc = point3f_init_from_array(&point, array, 0);
    TEST_ASSERT_EQUAL(RC_FAIL, rc);

    // call method and check results
    rc = point3f_init_from_array(&point, array, 3);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_init_from_vector3f(void)
{
    retcode_t rc;
    struct Vectorf vec;
    struct Point3f point;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];

    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    rc = point3f_init_from_vector3f(&point, &vec);
    TEST_ASSERT_EQUAL(RC_FAIL, rc);

    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    {
        vectorf_set(&vec, 0u, 1.0f);
        vectorf_set(&vec, 1u, 2.0f);
        vectorf_set(&vec, 2u, 3.0f);
    }

    // call method and check results
    rc = point3f_init_from_vector3f(&point, &vec);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_init_from_point3f(void)
{
    struct Point3f other;
    point3f_init_from_scalars(&other, 1.0f, 2.0f, 3.0f);

    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_init_from_point3f(&point, &other));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_is_valid(void)
{
    bool_t rc;
    struct Point3f point;

    // call method and check results
    point3f_set_x(&point, 1.0f);
    point3f_set_y(&point, 2.0f);
    point3f_set_z(&point, 3.0f);

    rc = point3f_is_valid(&point);
    TEST_ASSERT_TRUE(rc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_is_equal(void)
{
    struct Point3f point;
    struct Point3f other;
    point3f_init_from_scalars(&point, 1.0f, 2.0f, 3.0f);
    point3f_init_from_scalars(&other, 1.0f, 2.0f, 3.0f);

    // call method and check results
    TEST_ASSERT_TRUE(point3f_is_equal(&point, &other));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_add(void)
{
    struct Point3f pt1;
    struct Point3f pt2;
    point3f_init_from_scalars(&pt1, 1.0f, 2.0f, 3.0f);
    point3f_init_from_scalars(&pt2, 1.0f, 2.0f, 3.0f);

    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_add(&pt1, &pt2, &point));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_add_vector3f(void)
{
    struct Point3f pt;
    point3f_init_from_scalars(&pt, 1.0f, 2.0f, 3.0f);

    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    {
        vectorf_set(&vec, 0u, 1.0f);
        vectorf_set(&vec, 1u, 2.0f);
        vectorf_set(&vec, 2u, 3.0f);
    }

    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_add_vector3f(&pt, &vec, &point));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_sub(void)
{
    struct Point3f pt1;
    struct Point3f pt2;
    point3f_init_from_scalars(&pt1, 1.0f, 2.0f, 3.0f);
    point3f_init_from_scalars(&pt2, 3.0f, 2.0f, 1.0f);

    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_sub(&pt1, &pt2, &vec));
    float32_t actual;
    vectorf_get(&vec, 0, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, actual);
    vectorf_get(&vec, 1, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    vectorf_get(&vec, 2, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_sub_vector3f(void)
{
    struct Point3f pt;
    point3f_init_from_scalars(&pt, 1.0f, 2.0f, 3.0f);
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    {
        vectorf_set(&vec, 0u, 3.0f);
        vectorf_set(&vec, 1u, 2.0f);
        vectorf_set(&vec, 2u, 1.0f);
    }

    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_sub_vector3f(&pt, &vec, &point));
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_negate(void)
{
    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 2.0f, 3.0f);

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_negate(&point));
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(-3.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_multiply_float32(void)
{
    struct Point3f pt;
    point3f_init_from_scalars(&pt, 1.0f, 2.0f, 3.0f);

    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_multiply_float32(&pt, 2.0f, &point));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_divide_float32(void)
{
    struct Point3f pt;
    point3f_init_from_scalars(&pt, 1.0f, 2.0f, 3.0f);

    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_divide_float32(&pt, 2.0f, &point));
    TEST_ASSERT_EQUAL_FLOAT(0.5f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(1.5f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_to_vector3f(void)
{
    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 2.0f, 3.0f);

    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_to_vector3f(&point, &vec));
    float32_t actual;
    vectorf_get(&vec, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    vectorf_get(&vec, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
    vectorf_get(&vec, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_homogeneous(void)
{
    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 2.0f, 3.0f);

    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&vec, 4, vec_buf, VECTORF_MIN_BUF_SIZE(4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_homogeneous(&point, &vec));
    float32_t actual;
    vectorf_get(&vec, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    vectorf_get(&vec, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
    vectorf_get(&vec, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, actual);
    vectorf_get(&vec, 3u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_dist_sqr(void)
{
    struct Point3f point;
    struct Point3f other;
    point3f_init_from_scalars(&point, 1.0f, 2.0f, 3.0f);
    point3f_init_from_scalars(&other, 4.0f, 2.0f, 7.0f);

    // call method and check results
    const float32_t expected = 25.0f;
    float32_t       actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_dist_sqr(&point, &other, &actual));
    TEST_ASSERT_EQUAL_FLOAT(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_dist(void)
{
    struct Point3f point;
    struct Point3f other;
    point3f_init_from_scalars(&point, 1.0f, 2.0f, 3.0f);
    point3f_init_from_scalars(&other, 4.0f, 2.0f, 7.0f);

    // call method and check results
    const float32_t expected = 5.0f;
    float32_t       actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_dist(&point, &other, &actual));
    TEST_ASSERT_EQUAL_FLOAT(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_is_finite(void)
{
    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 2.0f, 3.0f);

    // call method and check results
    TEST_ASSERT_TRUE(point3f_is_finite(&point));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_is_zero(void)
{
    struct Point3f pt1;
    struct Point3f pt2;
    point3f_init_from_scalars(&pt1, 0.0f, 0.0f, 0.0f);
    point3f_init_from_scalars(&pt2, 4.0f, 2.0f, 7.0f);

    // call method and check results
    TEST_ASSERT_TRUE(point3f_is_zero(&pt1));
    TEST_ASSERT_FALSE(point3f_is_zero(&pt2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_set_constant(void)
{
    struct Point3f point;

    // call method and check results
    const float32_t expected = -1.0f;
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_set_constant(&point, expected));
    TEST_ASSERT_EQUAL_FLOAT(expected, point.x);
    TEST_ASSERT_EQUAL_FLOAT(expected, point.y);
    TEST_ASSERT_EQUAL_FLOAT(expected, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_set_zero(void)
{
    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_set_zero(&point));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_set_unit_x(void)
{
    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_set_unit_x(&point));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, point3f_get_x(&point));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point3f_get_y(&point));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point3f_get_z(&point));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_set_unit_y(void)
{
    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_set_unit_y(&point));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_set_unit_z(void)
{
    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_set_unit_z(&point));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_expmap(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    {
        vectorf_set(&vec, 0u, 1.0f);
        vectorf_set(&vec, 1u, 2.0f);
        vectorf_set(&vec, 2u, 3.0f);
    }

    struct Point3f point;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_expmap(&point, &vec));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, point.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, point.y);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, point.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_logmap(void)
{
    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 2.0f, 3.0f);

    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, point3f_logmap(&point, &vec));
    float32_t actual;
    vectorf_get(&vec, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    vectorf_get(&vec, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
    vectorf_get(&vec, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_get_serialized_size(void)
{
    struct Point3f point;

    TEST_ASSERT_EQUAL_UINT32(12, point3f_get_serialized_size(&point));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_point3f_serialize_deserialize(void)
{
    struct Point3f point1;
    struct Point3f point2;
    uint8_t buffer[16];
    uint32_t expected_size;
    retcode_t rc;

    expected_size = point3f_get_serialized_size(&point1);

    rc = point3f_serialize(&point1, buffer, 0);
    TEST_ASSERT_EQUAL_UINT32(RC_SERIALIZATION_BUFFER_OVERFLOW, rc);
    rc = point3f_deserialize(&point2, buffer, 0);
    TEST_ASSERT_EQUAL_UINT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, rc);
    
    point1.x = 1.0f;
    point1.y = 2.0f;
    point1.z = 3.0f;

    rc = point3f_serialize(&point1, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(expected_size, rc);
    rc = point3f_deserialize(&point2, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(expected_size, rc);

    TEST_ASSERT_EQUAL_FLOAT(point2.x, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(point2.y, 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(point2.z, 3.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_point3f_init_from_scalars);
    RUN_TEST(test_point3f_init);
    RUN_TEST(test_point3f_init_from_array);
    RUN_TEST(test_point3f_init_from_vector3f);
    RUN_TEST(test_point3f_init_from_point3f);
    RUN_TEST(test_point3f_is_valid);
    RUN_TEST(test_point3f_is_equal);
    RUN_TEST(test_point3f_add);
    RUN_TEST(test_point3f_add_vector3f);
    RUN_TEST(test_point3f_sub);
    RUN_TEST(test_point3f_sub_vector3f);
    RUN_TEST(test_point3f_negate);
    RUN_TEST(test_point3f_multiply_float32);
    RUN_TEST(test_point3f_divide_float32);
    RUN_TEST(test_point3f_to_vector3f);
    RUN_TEST(test_point3f_homogeneous);
    RUN_TEST(test_point3f_dist_sqr);
    RUN_TEST(test_point3f_dist);
    RUN_TEST(test_point3f_is_finite);
    RUN_TEST(test_point3f_is_zero);
    RUN_TEST(test_point3f_set_constant);
    RUN_TEST(test_point3f_set_zero);
    RUN_TEST(test_point3f_set_unit_x);
    RUN_TEST(test_point3f_set_unit_y);
    RUN_TEST(test_point3f_set_unit_z);
    RUN_TEST(test_point3f_expmap);
    RUN_TEST(test_point3f_logmap);
    RUN_TEST(test_point3f_get_serialized_size);
    RUN_TEST(test_point3f_serialize_deserialize);
    return UNITY_END();
}
