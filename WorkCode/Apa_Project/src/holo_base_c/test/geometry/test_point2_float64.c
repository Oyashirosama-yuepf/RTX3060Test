/*!
 * @brief Unit test for Point2d and Duration.
 * @author liuya(liuya@holomaitc.com), lichao@holomatic.com
 * @date 2019-1-4
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <math.h>
#include <unity.h>

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2_float64.h>
#include <holo_c/port/endian.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_init(void)
{
    struct Point2d in1;

    /*test init functions*/
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_init(&in1));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, in1.x);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, in1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_init_from_scalars(void)
{
    struct Point2d in1;

    /*test init from scalars functions*/
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_init_from_scalars(&in1, 3.0, 3.0));
    TEST_ASSERT_EQUAL_DOUBLE(3.0, in1.x);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, in1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_init_from_array(void)
{
    float64_t array[2] = {2.0, 2.0};

    struct Point2d in1;

    /*test init from array functions*/
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_init_from_array(&in1, &array[0], 2u));
    TEST_ASSERT_EQUAL_DOUBLE(2.0, in1.x);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, in1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_init_from_point2d(void)
{
    struct Point2d out;
    struct Point2d in1;
    point2d_init_from_scalars(&in1, 3.0, 3.0);

    /*test init from point2d functions*/
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_init_from_point2d(&out, &in1));
    TEST_ASSERT_EQUAL_DOUBLE(3.0, out.x);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, out.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_dim(void)
{
    struct Point2d in1;
    point2d_init(&in1);

    /* test dim function */
    TEST_ASSERT_EQUAL_INT64(2, point2d_dim());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_addition(void)
{
    struct Point2d out;
    struct Point2d in1;
    struct Point2d in2;

    /* initialize two 2D points */
    point2d_init_from_scalars(&in1, 3.0, 3.0);
    point2d_init_from_scalars(&in2, 2.0, 2.0);

    /*test add function*/
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_add(&in1, &in2, &out));
    TEST_ASSERT_EQUAL_DOUBLE(5.0, out.x);
    TEST_ASSERT_EQUAL_DOUBLE(5.0, out.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_negation(void)
{
    struct Point2d in1;

    /* initialize 2D point */
    point2d_init_from_scalars(&in1, -1.0, -1.0);

    /* test negative function */
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_negate(&in1, &in1));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, in1.x);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, in1.y);
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_negate(&in1, &in1));
    TEST_ASSERT_EQUAL_DOUBLE(-1.0, in1.x);
    TEST_ASSERT_EQUAL_DOUBLE(-1.0, in1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_equivalent(void)
{
    struct Point2d in1;
    struct Point2d in2;

    /* initialize two 2D points */
    point2d_init_from_scalars(&in1, 6.1, 7.2);
    point2d_init_from_point2d(&in2, &in1);

    /* test equal function */
    TEST_ASSERT_TRUE(point2d_is_equal(&in1, &in2));
    in2.y = 8.299;
    TEST_ASSERT_FALSE(point2d_is_equal(&in1, &in2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_multiply_scalar(void)
{
    struct Point2d out;
    struct Point2d in1;

    /* initialize 2D point */
    point2d_init_from_scalars(&in1, 6.1, 7.2);

    /* test scale */
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_multiply_float64(&in1, 5.0, &out));
    TEST_ASSERT_EQUAL_DOUBLE(30.5, out.x);
    TEST_ASSERT_EQUAL_DOUBLE(36.0, out.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_divide_scalar(void)
{
    struct Point2d out;
    struct Point2d in1;

    /* initialize 2D opoint */
    point2d_init_from_scalars(&in1, 6.1, 7.2);

    /* test scale */
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_divide_float64(&in1, 5.0, &out));
    TEST_ASSERT_EQUAL_DOUBLE(1.22, out.x);
    TEST_ASSERT_EQUAL_DOUBLE(1.44, out.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_distance(void)
{
    struct Point2d in1;
    struct Point2d in2;

    /* initialize two 2D points */
    point2d_init_from_scalars(&in1, 2.0, 3.0);
    point2d_init_from_scalars(&in2, 4.0, 5.0);

    /* test distsqr and dist function */
    float64_t distsqr = 0.0, dist = 0.0;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_dist_sqr(&in1, &in2, &distsqr));
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_dist(&in1, &in2, &dist));
    TEST_ASSERT_EQUAL_INT64(8.0, distsqr);
    TEST_ASSERT_EQUAL_DOUBLE(sqrt(8.0), dist);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_getter_and_setter(void)
{
    struct Point2d in1;

    float64_t x = 2.0, y = 3.0;

    /* initialize 2D point */
    point2d_init(&in1);

    /* test setter and getter functions */
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_set_x(&in1, x));
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_set_y(&in1, y));
    TEST_ASSERT_EQUAL_INT64(x, point2d_get_x(&in1));
    TEST_ASSERT_EQUAL_INT64(y, point2d_get_y(&in1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_specific_vector(void)
{
    struct Point2d out;

    retcode_t ret = RC_FAIL;

    /* test zero function */
    ret = point2d_set_zero(&out);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, out.x);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, out.y);
    TEST_ASSERT_EQUAL_INT64(ret, RC_SUCCESS);

    /* test unit x function */
    ret = point2d_set_unit_x(&out);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, out.x);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, out.y);
    TEST_ASSERT_EQUAL_INT64(ret, RC_SUCCESS);

    /* test unit y function */
    ret = point2d_set_unit_y(&out);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, out.x);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, out.y);
    TEST_ASSERT_EQUAL_INT64(ret, RC_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_to_string(void)
{
    struct Point2d in;

    /* test to string function */
    point2d_init_from_scalars(&in, 10.0, 9.0);

    const uint64_t buffer_length = 50u;

    char_t str[buffer_length];
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, point2d_to_string(&in, str, buffer_length));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_validation(void)
{
    struct Point2d in;

    /* test valid function */
    point2d_init_from_scalars(&in, 1, 2);
    TEST_ASSERT_TRUE(point2d_is_valid(&in));
    in.x = NAN;
    in.y = NAN;
    TEST_ASSERT_FALSE(point2d_is_valid(&in));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_is_finite(void)
{
    struct Point2d in;

    /* test valid function */
    point2d_init_from_scalars(&in, 1, 2);
    TEST_ASSERT_TRUE(point2d_is_finite(&in));
    point2d_init_from_scalars(&in, INFINITY, INFINITY);
    TEST_ASSERT_FALSE(point2d_is_finite(&in));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_is_zero(void)
{
    struct Point2d in;

    /* test valid function */
    point2d_init_from_scalars(&in, 0, 0);
    TEST_ASSERT_TRUE(point2d_is_zero(&in));
    point2d_init_from_scalars(&in, 0.1, 0.2);
    TEST_ASSERT_FALSE(point2d_is_zero(&in));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_serialize(void)
{
    uint8_t buffer[16u];

    struct Point2d in;

    /* test get serialized size function */
    TEST_ASSERT_EQUAL_INT64(16u, point2d_get_serialized_size(&in));

    /* test serialize function */
    point2d_init_from_scalars(&in, 1, 0);
    TEST_ASSERT_EQUAL_INT64(16u, point2d_serialize(&in, buffer, 16u));
    uint8_t expected_buffer[16u] = {0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 16u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_deserialize(void)
{
    uint8_t buffer[16u];
    buffer[0u]  = 0x3f;
    buffer[1u]  = 0xf0;
    buffer[2u]  = 0x00;
    buffer[3u]  = 0x00;
    buffer[4u]  = 0x00;
    buffer[5u]  = 0x00;
    buffer[6u]  = 0x00;
    buffer[7u]  = 0x00;
    buffer[8u]  = 0x00;
    buffer[9u]  = 0x00;
    buffer[10u] = 0x00;
    buffer[11u] = 0x00;
    buffer[12u] = 0x00;
    buffer[13u] = 0x00;
    buffer[14u] = 0x00;
    buffer[15u] = 0x00;

    struct Point2d pt;

    /* test deserialize function */
    point2d_init_from_scalars(&pt, 0, 0);
    TEST_ASSERT_EQUAL_INT64(16u, point2d_deserialize(&pt, buffer, 16u));
    struct Point2d expected_pt;
    point2d_init_from_scalars(&expected_pt, 1, 0);
    TEST_ASSERT_TRUE(point2d_is_equal(&expected_pt, &pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_point2_init);
    RUN_TEST(test_point2_init_from_scalars);
    RUN_TEST(test_point2_init_from_array);
    RUN_TEST(test_point2_init_from_point2d);
    RUN_TEST(test_point2_dim);
    RUN_TEST(test_point2_addition);
    RUN_TEST(test_point2_negation);
    RUN_TEST(test_point2_equivalent);
    RUN_TEST(test_point2_multiply_scalar);
    RUN_TEST(test_point2_divide_scalar);
    RUN_TEST(test_point2_distance);
    RUN_TEST(test_point2_getter_and_setter);
    RUN_TEST(test_point2_specific_vector);
    RUN_TEST(test_point2_to_string);
    RUN_TEST(test_point2_validation);
    RUN_TEST(test_point2_is_finite);
    RUN_TEST(test_point2_is_zero);
    RUN_TEST(test_point2_serialize);
    RUN_TEST(test_point2_deserialize);
    return UNITY_END();
}
