/*!
 * @brief Unit test for Point2f and Duration.
 * @author liuya(liuya@holomaitc.com), lichao@holomatic.com
 * @date 2019-1-4
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2_float32.h>
#include <holo_c/port/endian.h>
#include <math.h>
#include <unity.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_init(void)
{
    struct Point2f in1;

    /*test init functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_init(&in1));
    TEST_ASSERT_EQUAL_FLOAT(0.0, in1.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0, in1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_init_from_scalars(void)
{
    struct Point2f in1;

    /*test init from scalars functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_init_from_scalars(&in1, 3.0, 3.0));
    TEST_ASSERT_EQUAL_FLOAT(3.0, in1.x);
    TEST_ASSERT_EQUAL_FLOAT(3.0, in1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_init_from_array(void)
{
    float32_t array[2] = {2.0, 2.0};

    struct Point2f in1;

    /*test init from array functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_init_from_array(&in1, &array[0], 2u));
    TEST_ASSERT_EQUAL_FLOAT(2.0, in1.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0, in1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_init_from_vector2f(void)
{
    struct Point2f in1;

    /* initialize 2D vector */
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&vec, 0, 6.0);
    vectorf_set(&vec, 1, 8.0);

    /*test init from vector2f functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_init_from_vector2f(&in1, &vec));
    TEST_ASSERT_EQUAL_FLOAT(6.0, in1.x);
    TEST_ASSERT_EQUAL_FLOAT(8.0, in1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_init_from_point2f(void)
{
    struct Point2f out;
    struct Point2f in1;
    point2f_init_from_scalars(&in1, 3.0, 3.0);

    /*test init from point2f functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_init_from_point2f(&out, &in1));
    TEST_ASSERT_EQUAL_FLOAT(3.0, out.x);
    TEST_ASSERT_EQUAL_FLOAT(3.0, out.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_dim(void)
{
    struct Point2f in1;
    point2f_init(&in1);

    /* test dim function */
    TEST_ASSERT_EQUAL_INT32(2, point2f_dim());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_addition(void)
{
    struct Point2f out;
    struct Point2f in1;
    struct Point2f in2;

    /* initialize two 2D points */
    point2f_init_from_scalars(&in1, 3.0, 3.0);
    point2f_init_from_scalars(&in2, 2.0, 2.0);

    /*test add function*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_add(&in1, &in2, &out));
    TEST_ASSERT_EQUAL_FLOAT(5.0, out.x);
    TEST_ASSERT_EQUAL_FLOAT(5.0, out.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_add_vector2f(void)
{
    struct Point2f in1, in2;
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];

    /* initialize first points */
    point2f_init_from_scalars(&in1, 6.1, 7.2);

    /* initialize 2D vector and set it to (1.0, 1.0) */
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&vec, 0, 1.0);
    vectorf_set(&vec, 1, 1.0);

    /* generate expected point */
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, 7.1, 8.2);

    /*test equal function*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_add_vector2f(&in1, &vec, &in2));
    TEST_ASSERT_TRUE(point2f_is_equal(&in2, &expected_pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_translation(void)
{
    struct Point2f in1, in2, in3;
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];

    /* initialize first points */
    point2f_init_from_scalars(&in1, 6.1, 7.2);

    /* initialize 2D vector and set it to (1.0, 1.0) */
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&vec, 0, 1.0);
    vectorf_set(&vec, 1, 1.0);

    vectorf_init(&expected_vec, 2, expected_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&expected_vec, 0, 1.0);
    vectorf_set(&expected_vec, 1, 1.0);

    /* generate expected point */
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, 7.1, 8.2);

    /*test equal function*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_translate(&in1, &vec, &in2));
    TEST_ASSERT_TRUE(point2f_is_equal(&in2, &expected_pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_reverse_translate(&in2, &vec, &in3));
    TEST_ASSERT_TRUE(vectorf_is_equal((const struct Vectorf*)&expected_vec, (const struct Vectorf*)&vec));
    TEST_ASSERT_TRUE(point2f_is_equal(&in3, &in1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_subtraction(void)
{
    struct Point2f in1, in2;
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));

    /* initialize two 2D points */
    point2f_init_from_scalars(&in1, 3.0, 3.0);
    point2f_init_from_scalars(&in2, 2.0, 2.0);

    /* generate expected vector */
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&expected_vec, 2, expected_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&expected_vec, 0, 1.0);
    vectorf_set(&expected_vec, 1, 1.0);

    /* test subtraction function*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_sub(&in1, &in2, &vec));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_vec, &vec));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_negation(void)
{
    struct Point2f in1;

    /* initialize 2D point */
    point2f_init_from_scalars(&in1, -1.0, -1.0);

    /* test negative function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_negate(&in1, &in1));
    TEST_ASSERT_EQUAL_FLOAT(1.0, in1.x);
    TEST_ASSERT_EQUAL_FLOAT(1.0, in1.y);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_negate(&in1, &in1));
    TEST_ASSERT_EQUAL_FLOAT(-1.0, in1.x);
    TEST_ASSERT_EQUAL_FLOAT(-1.0, in1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_equivalent(void)
{
    struct Point2f in1;
    struct Point2f in2;

    /* initialize two 2D points */
    point2f_init_from_scalars(&in1, 6.1, 7.2);
    point2f_init_from_point2f(&in2, &in1);

    /* test equal function */
    TEST_ASSERT_TRUE(point2f_is_equal(&in1, &in2));
    in2.y = 8.299;
    TEST_ASSERT_FALSE(point2f_is_equal(&in1, &in2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_multiply_scalar(void)
{
    struct Point2f out;
    struct Point2f in1;

    /* initialize 2D point */
    point2f_init_from_scalars(&in1, 6.1, 7.2);

    /* test scale */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_multiply_float32(&in1, 5.0, &out));
    TEST_ASSERT_EQUAL_FLOAT(30.5, out.x);
    TEST_ASSERT_EQUAL_FLOAT(36.0, out.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_divide_scalar(void)
{
    struct Point2f out;
    struct Point2f in1;

    /* initialize 2D opoint */
    point2f_init_from_scalars(&in1, 6.1, 7.2);

    /* test scale */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_divide_float32(&in1, 5.0, &out));
    TEST_ASSERT_EQUAL_FLOAT(1.22, out.x);
    TEST_ASSERT_EQUAL_FLOAT(1.44, out.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_distance(void)
{
    struct Point2f in1;
    struct Point2f in2;

    /* initialize two 2D points */
    point2f_init_from_scalars(&in1, 2.0, 3.0);
    point2f_init_from_scalars(&in2, 4.0, 5.0);

    /* test distsqr and dist function */
    float32_t distsqr = 0.0, dist = 0.0;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_dist_sqr(&in1, &in2, &distsqr));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_dist(&in1, &in2, &dist));
    TEST_ASSERT_EQUAL_INT32(8.0, distsqr);
    TEST_ASSERT_EQUAL_FLOAT(sqrt(8.0), dist);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_getter_and_setter(void)
{
    struct Point2f in1;

    float32_t x = 2.0, y = 3.0;

    /* initialize 2D point */
    point2f_init(&in1);

    /* test setter and getter functions */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_set_x(&in1, x));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_set_y(&in1, y));
    TEST_ASSERT_EQUAL_INT32(x, point2f_get_x(&in1));
    TEST_ASSERT_EQUAL_INT32(y, point2f_get_y(&in1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_to_vector(void)
{
    struct Vectorf out;
    float32_t      out_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&out, 2, out_buf, VECTORF_MIN_BUF_SIZE(2u));
    struct Point2f in1;

    float32_t x = 2.0, y = 3.0;

    /* initialize 2D point */
    point2f_init_from_scalars(&in1, x, y);

    /* generate expected 2D vector */
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&expected_vec, 2, expected_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&expected_vec, 0, x);
    vectorf_set(&expected_vec, 1, y);

    /* test to vector function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_to_vector2f(&in1, &out));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_vec, &out));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_homogeneous(void)
{
    struct Vectorf out;
    float32_t      out_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&out, 3, out_buf, VECTORF_MIN_BUF_SIZE(3u));
    struct Point2f in1;

    float32_t x = 2.0, y = 3.0;

    /* initialize 2D point */
    point2f_init_from_scalars(&in1, x, y);

    /* generate expected 2D vector */
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_vec, 3, expected_vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected_vec, 0, x);
    vectorf_set(&expected_vec, 1, y);
    vectorf_set(&expected_vec, 2, 1.0);

    /* test homogeneous function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_homogeneous(&in1, &out));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_vec, &out));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_expmap(void)
{
    struct Point2f out;
    struct Vectorf in1;
    float32_t      in1_buf[VECTORF_MIN_BUF_SIZE(2u)];

    float32_t x = 2.0, y = 3.0;

    /* initialize two 2D vector */
    vectorf_init(&in1, 2, in1_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&in1, 0, x);
    vectorf_set(&in1, 1, y);

    /* generate expected 2D point */
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, x, y);

    /* test exponential map function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_expmap(&in1, &out));
    TEST_ASSERT_TRUE(point2f_is_equal(&out, &expected_pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_logmap(void)
{
    struct Vectorf out;
    float32_t      out_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&out, 2, out_buf, VECTORF_MIN_BUF_SIZE(2u));
    struct Point2f in1;

    float32_t x = 2.0, y = 3.0;

    /* initialize 2D point */
    point2f_init_from_scalars(&in1, x, y);

    /* generate expected 2D vector */
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&expected_vec, 2, expected_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&expected_vec, 0, x);
    vectorf_set(&expected_vec, 1, y);

    /* test logarithmic map function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_logmap(&in1, &out));
    TEST_ASSERT_TRUE(vectorf_is_equal(&out, &expected_vec));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_specific_vector(void)
{
    struct Point2f out;

    retcode_t ret = RC_FAIL;

    /* test zero function */
    ret = point2f_set_zero(&out);
    TEST_ASSERT_EQUAL_FLOAT(0.0, out.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0, out.y);
    TEST_ASSERT_EQUAL_INT32(ret, RC_SUCCESS);

    /* test unit x function */
    ret = point2f_set_unit_x(&out);
    TEST_ASSERT_EQUAL_FLOAT(1.0, out.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0, out.y);
    TEST_ASSERT_EQUAL_INT32(ret, RC_SUCCESS);

    /* test unit y function */
    ret = point2f_set_unit_y(&out);
    TEST_ASSERT_EQUAL_FLOAT(0.0, out.x);
    TEST_ASSERT_EQUAL_FLOAT(1.0, out.y);
    TEST_ASSERT_EQUAL_INT32(ret, RC_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2f_to_string(void)
{
    struct Point2f in;

    /* test to string function */
    point2f_init_from_scalars(&in, 10.0, 9.0);

    const uint32_t buffer_length = 50u;

    char_t str[buffer_length];
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, point2f_to_string(&in, str, buffer_length));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_validation(void)
{
    struct Point2f in;

    /* test valid function */
    point2f_init_from_scalars(&in, 1, 2);
    TEST_ASSERT_TRUE(point2f_is_valid(&in));
    in.x = NAN;
    in.y = NAN;
    TEST_ASSERT_FALSE(point2f_is_valid(&in));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_is_finite(void)
{
    struct Point2f in;

    /* test valid function */
    point2f_init_from_scalars(&in, 1, 2);
    TEST_ASSERT_TRUE(point2f_is_finite(&in));
    point2f_init_from_scalars(&in, INFINITY, INFINITY);
    TEST_ASSERT_FALSE(point2f_is_finite(&in));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_is_zero(void)
{
    struct Point2f in;

    /* test valid function */
    point2f_init_from_scalars(&in, 0, 0);
    TEST_ASSERT_TRUE(point2f_is_zero(&in));
    point2f_init_from_scalars(&in, 0.1, 0.2);
    TEST_ASSERT_FALSE(point2f_is_zero(&in));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_serialize(void)
{
    uint8_t buffer[8u];

    struct Point2f in;

    /* test get serialized size function */
    TEST_ASSERT_EQUAL_INT32(8u, point2f_get_serialized_size(&in));

    /* test serialize function */
    point2f_init_from_scalars(&in, 1, 0);
    TEST_ASSERT_EQUAL_INT32(8u, point2f_serialize(&in, buffer, 8u));
    uint8_t expected_buffer[8u] = {0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point2_deserialize(void)
{
    uint8_t buffer[8u];
    buffer[0u] = 0x3f;
    buffer[1u] = 0x80;
    buffer[2u] = 0x00;
    buffer[3u] = 0x00;
    buffer[4u] = 0x00;
    buffer[5u] = 0x00;
    buffer[6u] = 0x00;
    buffer[7u] = 0x00;

    struct Point2f pt;

    /* test deserialize function */
    point2f_init_from_scalars(&pt, 0, 0);
    TEST_ASSERT_EQUAL_INT32(8u, point2f_deserialize(&pt, buffer, 8u));
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, 1, 0);
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_point2_init);
    RUN_TEST(test_point2_init_from_scalars);
    RUN_TEST(test_point2_init_from_array);
    RUN_TEST(test_point2_init_from_vector2f);
    RUN_TEST(test_point2_init_from_point2f);
    RUN_TEST(test_point2_dim);
    RUN_TEST(test_point2_addition);
    RUN_TEST(test_point2_add_vector2f);
    RUN_TEST(test_point2_translation);
    RUN_TEST(test_point2_subtraction);
    RUN_TEST(test_point2_negation);
    RUN_TEST(test_point2_equivalent);
    RUN_TEST(test_point2_multiply_scalar);
    RUN_TEST(test_point2_divide_scalar);
    RUN_TEST(test_point2_distance);
    RUN_TEST(test_point2_getter_and_setter);
    RUN_TEST(test_point2_to_vector);
    RUN_TEST(test_point2_homogeneous);
    RUN_TEST(test_point2_expmap);
    RUN_TEST(test_point2_logmap);
    RUN_TEST(test_point2_specific_vector);
    RUN_TEST(test_point2f_to_string);
    RUN_TEST(test_point2_validation);
    RUN_TEST(test_point2_is_finite);
    RUN_TEST(test_point2_is_zero);
    RUN_TEST(test_point2_serialize);
    RUN_TEST(test_point2_deserialize);
    return UNITY_END();
}
