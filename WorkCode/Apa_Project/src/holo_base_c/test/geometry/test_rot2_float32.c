/*!
 * @brief Unit test for rot2.
 * @author lichao@holomaitc.com
 * @date Aug 10, 2019
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2_float32.h>
#include <holo_c/geometry/rot2_float32.h>
#include <holo_c/port/endian.h>
#include <math.h>
#include <unity.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_init(void)
{
    struct Rot2f in1;

    /* test initialization function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_init(&in1));
    TEST_ASSERT_EQUAL_FLOAT(1.0, in1.c);
    TEST_ASSERT_EQUAL_FLOAT(0.0, in1.s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_init_from_angle(void)
{
    struct Rot2f in1;

    float32_t theta = M_PI / 4.0;  // in radians

    /* test initialization from angle function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_init_from_angle(&in1, theta));
    TEST_ASSERT_EQUAL_FLOAT(cosf(theta), in1.c);
    TEST_ASSERT_EQUAL_FLOAT(sinf(theta), in1.s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_init_from_rot2f(void)
{
    struct Rot2f in1, in2;

    float32_t theta = M_PI / 4.0;  // in radians
    rot2f_init_from_angle(&in1, theta);

    /* test initialization from rot2f function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_init_from_rot2f(&in2, &in1));
    TEST_ASSERT_EQUAL_FLOAT(cosf(theta), in2.c);
    TEST_ASSERT_EQUAL_FLOAT(sinf(theta), in2.s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_init_from_matrix(void)
{
    struct Rot2f in1;

    /* initial matrix to identity matrix */
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&mat, 2, 2, mat_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_identity(&mat);

    /* set rotation matrix */
    matrixf_set(&mat, 0, 0, 0);
    matrixf_set(&mat, 0, 1, -1);
    matrixf_set(&mat, 1, 0, 1);
    matrixf_set(&mat, 1, 1, 0);

    /* test initialization from matrix function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_init_from_matrix(&in1, &mat));
    TEST_ASSERT_EQUAL_FLOAT(0.0, in1.c);
    TEST_ASSERT_EQUAL_FLOAT(1.0, in1.s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_inverse(void)
{
    const float32_t theta = M_PI / 2.0;  // in radian
    struct Rot2f    in;

    /* initialize 2D rotation from angle */
    rot2f_init_from_angle(&in, theta);

    /* initialize 2D vector and set it to (1.0, 1.0) */
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&vec, 0, 1.0);
    vectorf_set(&vec, 1, 1.0);

    /* generate expected rotated vector (-1.0, 1.0) */
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&expected_vec, 2, expected_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&expected_vec, 0, -1.0);
    vectorf_set(&expected_vec, 1, 1.0);

    /* test inverse function */
    struct Vectorf actual_vec;
    float32_t      actual_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&actual_vec, 2, actual_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_rotate_vector2f(&in, &vec, &actual_vec));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_vec, &actual_vec));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_rotate_point2f(void)
{
    const float32_t theta = M_PI / 2.0;  // in radian
    struct Rot2f    in;
    struct Point2f  pt;

    /* initialize 2D rotation from angle */
    rot2f_init_from_angle(&in, theta);

    /* initialize 2D point (1.0, 1.0) */
    point2f_init_from_scalars(&pt, 1.0, 1.0);

    /* generate expected 2D point (-1.0, 1.0) */
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, -1.0, 1.0);

    /* test rotate vector function */
    struct Point2f actual_pt;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_rotate_point2f(&in, &pt, &actual_pt));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_rotate_vector2f(void)
{
    const float32_t theta = M_PI / 2.0;  // in radian
    struct Rot2f    in;
    struct Vectorf  vec;
    float32_t       vec_buf[VECTORF_MIN_BUF_SIZE(2u)];

    /* initialize 2D rotation from angle */
    rot2f_init_from_angle(&in, theta);

    /* initialize 2D vector and set it to (1.0, 1.0) */
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&vec, 0, 1.0);
    vectorf_set(&vec, 1, 1.0);

    /* generate expected rotated vector (-1.0, 1.0) */
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&expected_vec, 2, expected_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&expected_vec, 0, -1.0);
    vectorf_set(&expected_vec, 1, 1.0);

    /* test rotate vector function */
    struct Vectorf actual_vec;
    float32_t      actual_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&actual_vec, 2, actual_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_rotate_vector2f(&in, &vec, &actual_vec));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_vec, &actual_vec));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_unrotate_vector2f(void)
{
    const float32_t theta = M_PI / 2.0;  // in radian
    struct Rot2f    in;
    struct Vectorf  vec;
    float32_t       vec_buf[VECTORF_MIN_BUF_SIZE(2u)];

    /* initialize 2D rotation from angle */
    rot2f_init_from_angle(&in, theta);

    /* initialize 2D vector and set it to (1.0, 1.0) */
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&vec, 0, 1.0);
    vectorf_set(&vec, 1, 1.0);

    /* generate expected rotated vector (1.0, -1.0) */
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&expected_vec, 2, expected_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&expected_vec, 0, 1.0);
    vectorf_set(&expected_vec, 1, -1.0);

    /* test unrotate vector function */
    struct Vectorf actual_vec;
    float32_t      actual_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&actual_vec, 2, actual_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_unrotate_vector2f(&in, &vec, &actual_vec));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_vec, &actual_vec));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_unrotate_point2f(void)
{
    const float32_t theta = M_PI / 2.0;  // in radian
    struct Rot2f    in;
    struct Point2f  pt;

    /* initialize 2D rotation from angle */
    rot2f_init_from_angle(&in, theta);

    /* initialize 2D point (1.0, 1.0) */
    point2f_init_from_scalars(&pt, 1.0, 1.0);

    /* generate expected point (1.0, -1.0) */
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, 1.0, -1.0);

    /* test unrotate point function */
    struct Point2f actual_pt;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_unrotate_point2f(&in, &pt, &actual_pt));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_multiple(void)
{
    const float32_t theta = M_PI / 2.0;  // in radian
    struct Rot2f this, other;

    /* initialize 2D rotation from angle */
    rot2f_init_from_angle(&this, theta);
    rot2f_init_from_angle(&other, -theta);

    /* generate expected rotation matrix */
    struct Rot2f expected_rot;
    rot2f_init_from_angle(&expected_rot, 0.0);

    /* test multiply function */
    struct Rot2f actual_rot;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_compose(&this, &other, &actual_rot));
    TEST_ASSERT_TRUE(rot2f_is_equal(&expected_rot, &actual_rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_equivalent(void)
{
    struct Rot2f in1;
    struct Rot2f in2;

    /* initialize two 2D rotation */
    rot2f_init_from_angle(&in1, 3.0);
    rot2f_init_from_rot2f(&in2, &in1);

    /* test equal function */
    TEST_ASSERT_TRUE(rot2f_is_equal(&in1, &in2));
    rot2f_init_from_angle(&in2, 0.0);
    TEST_ASSERT_FALSE(rot2f_is_equal(&in1, &in2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_to_matrix22f(void)
{
    const float32_t theta = M_PI / 2.0;  // in radian
    struct Rot2f    in;

    /* initialize 2D rotation from angle */
    rot2f_init_from_angle(&in, theta);

    /* generate expected rotation matrix */
    struct Matrixf expected_matrix;
    float32_t      expected_matrix_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&expected_matrix, 2, 2, expected_matrix_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set(&expected_matrix, 0, 0, cosf(theta));
    matrixf_set(&expected_matrix, 0, 1, -sinf(theta));
    matrixf_set(&expected_matrix, 1, 0, sinf(theta));
    matrixf_set(&expected_matrix, 1, 1, cosf(theta));

    /* test get matrix function */
    struct Matrixf actual_matrix;
    float32_t      actual_matrix_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&actual_matrix, 2, 2, actual_matrix_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_to_matrix22f(&in, &actual_matrix));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected_matrix, &actual_matrix));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_get_angle(void)
{
    const float32_t theta = M_PI / 2.0;  // in radian
    struct Rot2f    in;

    /* initialize 2D rotation from angle */
    rot2f_init_from_angle(&in, theta);

    /* test get angle function */
    float32_t actual_theta = 0.0;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_get_angle(&in, &actual_theta));
    TEST_ASSERT_EQUAL_FLOAT(theta, actual_theta);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_set_identity(void)
{
    const float32_t theta = M_PI / 4.0;  // in radian
    struct Rot2f    in;

    rot2f_init_from_angle(&in, theta);

    /* generate expected rotation */
    struct Matrixf expected_matrix;
    float32_t      expected_matrix_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&expected_matrix, 2, 2, expected_matrix_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_identity(&expected_matrix);

    /* test set identity function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_set_identity(&in));
    struct Matrixf actual_matrix;
    float32_t      actual_matrix_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&actual_matrix, 2, 2, actual_matrix_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    rot2f_to_matrix22f(&in, &actual_matrix);
    TEST_ASSERT_EQUAL_INT32(true, matrixf_is_equal(&expected_matrix, &actual_matrix));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_to_string(void)
{
    struct Rot2f in;

    /* test to string function */
    rot2f_init_from_angle(&in, 10.0);

    const uint32_t buffer_length = 50u;

    char_t str[buffer_length];
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rot2f_to_string(&in, str, buffer_length));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_is_valid(void)
{
    struct Rot2f in;

    /* test valid function */
    rot2f_init_from_angle(&in, 10.0);
    TEST_ASSERT_TRUE(rot2f_is_valid(&in));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_serialize(void)
{
    uint8_t buffer[8u];

    struct Rot2f in;

    /* test get serialized size function */
    TEST_ASSERT_EQUAL_INT32(8u, rot2f_get_serialized_size(&in));

    /* test serialize function */
    rot2f_init_from_angle(&in, 0.0);
    TEST_ASSERT_EQUAL_INT32(8u, rot2f_serialize(&in, buffer, 8u));
    uint8_t expected_buffer[8u] = {0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rot2f_deserialize(void)
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

    struct Rot2f rot;

    /* test deserialize function */
    rot2f_init_from_angle(&rot, 1.0);
    TEST_ASSERT_EQUAL_INT32(8u, rot2f_deserialize(&rot, buffer, 8u));
    struct Rot2f expected_rot;
    rot2f_init_from_angle(&expected_rot, 0.0);
    TEST_ASSERT_TRUE(rot2f_is_equal(&expected_rot, &rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_rot2f_init);
    RUN_TEST(test_rot2f_init_from_angle);
    RUN_TEST(test_rot2f_init_from_rot2f);
    RUN_TEST(test_rot2f_init_from_matrix);
    RUN_TEST(test_rot2f_inverse);
    RUN_TEST(test_rot2f_rotate_point2f);
    RUN_TEST(test_rot2f_rotate_vector2f);
    RUN_TEST(test_rot2f_unrotate_vector2f);
    RUN_TEST(test_rot2f_unrotate_point2f);
    RUN_TEST(test_rot2f_multiple);
    RUN_TEST(test_rot2f_equivalent);
    RUN_TEST(test_rot2f_to_matrix22f);
    RUN_TEST(test_rot2f_get_angle);
    RUN_TEST(test_rot2f_set_identity);
    RUN_TEST(test_rot2f_to_string);
    RUN_TEST(test_rot2f_is_valid);
    RUN_TEST(test_rot2f_serialize);
    RUN_TEST(test_rot2f_deserialize);
    return UNITY_END();
}
