/*!
 * @file test_rot3_float32.c
 * @brief unit test of rot3
 * @author duyanwei@holomatic.com
 * @date 2019-08-16
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/geometry/rot3_float32.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_init(void)
{
    struct Rot3f rot;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_init(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r00(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r01(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r10(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r11(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_init_from_scalars(void)
{
    struct Rot3f rot;
    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_init_from_scalars(&rot, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r00(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r01(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r10(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r11(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_init_from_rot3f(void)
{
    const float32_t cos45 = cosf(M_PI / 4.0f);
    const float32_t sin45 = sinf(M_PI / 4.0f);
    struct Rot3f    other;
    rot3f_init_from_scalars(&other, cos45, -sin45, 0.0f, sin45, cos45, 0.0f, 0.0f, 0.0f, 1.0f);

    struct Rot3f rot;
    rot3f_init(&rot);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_init_from_rot3f(&rot, &other));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r00(&rot));
    TEST_ASSERT_EQUAL_FLOAT(-sin45, rot3f_get_r01(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_EQUAL_FLOAT(sin45, rot3f_get_r10(&rot));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r11(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_is_valid(void)
{
    struct Rot3f rot1;
    rot3f_init(&rot1);

    const float32_t cos45 = cosf(M_PI / 4.0f);
    const float32_t sin45 = sinf(M_PI / 4.0f);
    struct Rot3f    rot2;
    rot3f_init_from_scalars(&rot2, cos45, -sin45, 0.0f, sin45, cos45, 0.0f, 0.0f, 0.0f, 1.0f);

    // call method and check results
    TEST_ASSERT_TRUE(rot3f_is_valid(&rot1));
    TEST_ASSERT_TRUE(rot3f_is_valid(&rot2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_is_equal(void)
{
    struct Rot3f rot1;
    rot3f_init(&rot1);
    rot3f_from_yaw(&rot1, M_PI / 4.0f);

    struct Rot3f rot2;
    const float32_t cos45 = cosf(M_PI / 4.0f);
    const float32_t sin45 = sinf(M_PI / 4.0f);
    rot3f_init_from_scalars(&rot2, cos45, -sin45, 0.0f, sin45, cos45, 0.0f, 0.0f, 0.0f, 1.0f);

    // call method and check results
    TEST_ASSERT_TRUE(rot3f_is_equal(&rot1, &rot2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_to_matrix33f(void)
{
    const float32_t cos45    = cosf(M_PI / 4.0f);
    const float32_t sin45    = sinf(M_PI / 4.0f);
    float32_t       array[9] = {cos45, -sin45, 0.0f, sin45, cos45, 0.0f, 0.0f, 0.0f, 1.0f};

    struct Rot3f self;
    rot3f_init_from_scalars(&self, array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7],
                            array[8]);
    // expected matrix
    struct Matrixf expected;
    float32_t      expected_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&expected, 3, 3, expected_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    matrixf_set_from_array(&expected, array, 9);

    // actual matrix
    struct Matrixf actual;
    float32_t      actual_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&actual, 3, 3, actual_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_to_matrix33f(&self, &actual));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_transpose(void)
{
    const float32_t cos45 = cosf(M_PI / 4.0f);
    const float32_t sin45 = sinf(M_PI / 4.0f);
    struct Rot3f    self;
    rot3f_init_from_scalars(&self, cos45, -sin45, 0.0f, sin45, cos45, 0.0f, 0.0f, 0.0f, 1.0f);

    struct Rot3f rot;
    rot3f_init(&rot);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_transpose(&self, &rot));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r00(&rot));
    TEST_ASSERT_EQUAL_FLOAT(sin45, rot3f_get_r01(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_EQUAL_FLOAT(-sin45, rot3f_get_r10(&rot));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r11(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_inverse(void)
{
    const float32_t cos45 = cosf(M_PI / 4.0f);
    const float32_t sin45 = sinf(M_PI / 4.0f);
    struct Rot3f    self;
    rot3f_init_from_scalars(&self, cos45, -sin45, 0.0f, sin45, cos45, 0.0f, 0.0f, 0.0f, 1.0f);

    struct Rot3f rot;
    rot3f_init(&rot);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_inverse(&self, &rot));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r00(&rot));
    TEST_ASSERT_EQUAL_FLOAT(sin45, rot3f_get_r01(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_EQUAL_FLOAT(-sin45, rot3f_get_r10(&rot));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r11(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_rotate_vector3f(void)
{
    struct Rot3f self;
    rot3f_init(&self);
    rot3f_from_yaw(&self, M_PI / 2.0f);

    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 1.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 1.0f);

    // expected vector
    struct Vectorf expected;
    float32_t      expected_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected, 3, expected_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected, 0u, -1.0f);
    vectorf_set(&expected, 1u, 1.0f);
    vectorf_set(&expected, 2u, 1.0f);

    // call method and check results
    struct Vectorf actual;
    float32_t      actual_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&actual, 3, actual_buf, VECTORF_MIN_BUF_SIZE(3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_rotate_vector3f(&self, &vec, &actual));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_unrotate_vector3f(void)
{
    struct Rot3f self;
    rot3f_init(&self);
    rot3f_from_yaw(&self, M_PI / 2.0f);

    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 1.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 1.0f);

    // expected vector
    struct Vectorf expected;
    float32_t      expected_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected, 3, expected_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected, 0u, 1.0f);
    vectorf_set(&expected, 1u, -1.0f);
    vectorf_set(&expected, 2u, 1.0f);

    // call method and check results
    struct Vectorf actual;
    float32_t      actual_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&actual, 3, actual_buf, VECTORF_MIN_BUF_SIZE(3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_unrotate_vector3f(&self, &vec, &actual));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_multiply_vector3f(void)
{
    struct Rot3f self;
    rot3f_init(&self);
    rot3f_from_yaw(&self, M_PI / 2.0f);

    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 1.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 1.0f);

    // expected vector
    struct Vectorf expected;
    float32_t      expected_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected, 3, expected_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected, 0u, -1.0f);
    vectorf_set(&expected, 1u, 1.0f);
    vectorf_set(&expected, 2u, 1.0f);

    // call method and check results
    struct Vectorf actual;
    float32_t      actual_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&actual, 3, actual_buf, VECTORF_MIN_BUF_SIZE(3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_multiply_vector3f(&self, &vec, &actual));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_rotate_point3f(void)
{
    struct Rot3f self;
    rot3f_init(&self);
    rot3f_from_yaw(&self, M_PI / 2.0f);

    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 1.0f, 1.0f);

    // expected point
    struct Point3f expected;
    point3f_init_from_scalars(&expected, -1.0f, 1.0f, 1.0f);

    // call method and check results
    struct Point3f actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_rotate_point3f(&self, &point, &actual));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_unrotate_point3f(void)
{
    struct Rot3f self;
    rot3f_init(&self);
    rot3f_from_yaw(&self, M_PI / 2.0f);

    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 1.0f, 1.0f);

    // expected point
    struct Point3f expected;
    point3f_init_from_scalars(&expected, 1.0f, -1.0f, 1.0f);

    // call method and check results
    struct Point3f actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_unrotate_point3f(&self, &point, &actual));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_multiply_point3f(void)
{
    struct Rot3f self;
    rot3f_init(&self);
    rot3f_from_yaw(&self, M_PI / 2.0f);

    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 1.0f, 1.0f);

    // expected point
    struct Point3f expected;
    point3f_init_from_scalars(&expected, -1.0f, 1.0f, 1.0f);

    // call method and check results
    struct Point3f actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_multiply_point3f(&self, &point, &actual));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected, &actual));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_compose(void)
{
    const float32_t yaw = M_PI / 2.0f;
    struct Rot3f    self;
    rot3f_init(&self);
    rot3f_from_yaw(&self, yaw);

    const float32_t pitch = M_PI / 3.0f;
    struct Rot3f    other;
    rot3f_init(&other);
    rot3f_from_pitch(&other, pitch);

    struct Rot3f expected;
    rot3f_init(&expected);
    rot3f_from_rpy(&expected, 0.0f, pitch, yaw);

    struct Rot3f actual;
    rot3f_init(&actual);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_compose(&self, &other, &actual));
    TEST_ASSERT_TRUE(rot3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_multiply(void)
{
    const float32_t yaw = M_PI / 2.0f;
    struct Rot3f    self;
    rot3f_init(&self);
    rot3f_from_yaw(&self, yaw);

    const float32_t pitch = M_PI / 3.0f;
    struct Rot3f    other;
    rot3f_init(&other);
    rot3f_from_pitch(&other, pitch);

    struct Rot3f expected;
    rot3f_init(&expected);
    rot3f_from_rpy(&expected, 0.0f, pitch, yaw);

    struct Rot3f actual;
    rot3f_init(&actual);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_multiply(&self, &other, &actual));
    TEST_ASSERT_TRUE(rot3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_from_angle_axis(void)
{
    // construct an angle-axis which rotates y-axis about theta angle
    const float32_t theta = M_PI / 2.0f;
    struct Vectorf  vec;
    float32_t       vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 0.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 0.0f);
    vectorf_multiply_float32(&vec, theta, &vec);

    // expected matrix
    struct Rot3f expected;
    rot3f_init(&expected);
    rot3f_from_pitch(&expected, theta);

    // call method and check results
    struct Rot3f actual;
    rot3f_init(&actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_from_angle_axis(&actual, &vec));
    TEST_ASSERT_TRUE(rot3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_to_angle_axis(void)
{
    // construct a matrix which rotates y-axis about theta angle
    const float32_t theta = -M_PI / 5.0f;
    struct Rot3f    rot;
    rot3f_init(&rot);
    rot3f_from_pitch(&rot, theta);

    // expected vector
    struct Vectorf expected;
    float32_t      expected_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected, 3, expected_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected, 0u, 0.0f);
    vectorf_set(&expected, 1u, 1.0f);
    vectorf_set(&expected, 2u, 0.0f);
    vectorf_multiply_float32(&expected, theta, &expected);

    // call method and check results
    struct Vectorf actual;
    float32_t      actual_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&actual, 3, actual_buf, VECTORF_MIN_BUF_SIZE(3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_to_angle_axis(&rot, &actual));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_expmap(void)
{
    // construct an angle-axis which rotates y-axis about theta angle
    const float32_t theta = M_PI / 2.0f;
    struct Vectorf  vec;
    float32_t       vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 0.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 0.0f);
    vectorf_multiply_float32(&vec, theta, &vec);

    // expected matrix
    struct Rot3f expected;
    rot3f_init(&expected);
    rot3f_from_pitch(&expected, theta);

    // call method and check results
    struct Rot3f actual;
    rot3f_init(&actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_expmap(&actual, &vec));
    TEST_ASSERT_TRUE(rot3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_logmap(void)
{
    // construct a matrix which rotates y-axis about theta angle
    const float32_t theta = -M_PI / 5.0f;
    struct Rot3f    rot;
    rot3f_init(&rot);
    rot3f_from_pitch(&rot, theta);

    // expected vector
    struct Vectorf expected;
    float32_t      expected_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected, 3, expected_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected, 0u, 0.0f);
    vectorf_set(&expected, 1u, 1.0f);
    vectorf_set(&expected, 2u, 0.0f);
    vectorf_multiply_float32(&expected, theta, &expected);

    // call method and check results
    struct Vectorf actual;
    float32_t      actual_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&actual, 3, actual_buf, VECTORF_MIN_BUF_SIZE(3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_logmap(&rot, &actual));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_compute_angle_diff(void)
{
    struct Rot3f rot1;
    rot3f_init(&rot1);
    rot3f_set_identity(&rot1);

    const float32_t pitch = M_PI / 3.0f;
    struct Rot3f    rot2;
    rot3f_init(&rot2);
    rot3f_from_pitch(&rot2, pitch);

    struct Rot3f rot3;
    rot3f_init(&rot3);
    rot3f_from_pitch(&rot3, -pitch);

    // call method and check results
    TEST_ASSERT_EQUAL_FLOAT(pitch, rot3f_compute_angle_diff(&rot1, &rot2));
    TEST_ASSERT_EQUAL_FLOAT(pitch, rot3f_compute_angle_diff(&rot1, &rot3));
    TEST_ASSERT_EQUAL_FLOAT(2.0f * pitch, rot3f_compute_angle_diff(&rot2, &rot3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_from_rpy(void)
{
    struct Rot3f rot;
    rot3f_init(&rot);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_from_rpy(&rot, M_PI / 2.0f, M_PI / 2.0f, M_PI / 2.0f));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r00(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r01(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 1.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r10(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 1.0f, rot3f_get_r11(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, -1.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_from_ypr(void)
{
    struct Rot3f rot;
    rot3f_init(&rot);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_from_ypr(&rot, M_PI / 2.0f, M_PI / 2.0f, M_PI / 2.0f));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r00(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r01(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 1.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r10(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 1.0f, rot3f_get_r11(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, -1.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_FLOAT_WITHIN(holo_float32_epsilon, 0.0f, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_from_roll(void)
{
    const float32_t roll  = M_PI / 3.0f;
    const float32_t cos45 = cosf(M_PI / 3.0f);
    const float32_t sin45 = sinf(M_PI / 3.0f);

    struct Rot3f rot;
    rot3f_init(&rot);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_from_roll(&rot, roll));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r00(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r01(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r10(&rot));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r11(&rot));
    TEST_ASSERT_EQUAL_FLOAT(-sin45, rot3f_get_r12(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_EQUAL_FLOAT(sin45, rot3f_get_r21(&rot));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_from_pitch(void)
{
    const float32_t pitch = M_PI / 3.0f;
    const float32_t cos45 = cosf(M_PI / 3.0f);
    const float32_t sin45 = sinf(M_PI / 3.0f);

    struct Rot3f rot;
    rot3f_init(&rot);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_from_pitch(&rot, pitch));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r00(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r01(&rot));
    TEST_ASSERT_EQUAL_FLOAT(sin45, rot3f_get_r02(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r10(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r11(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_EQUAL_FLOAT(-sin45, rot3f_get_r20(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_from_yaw(void)
{
    const float32_t yaw   = M_PI / 3.0f;
    const float32_t cos45 = cosf(M_PI / 3.0f);
    const float32_t sin45 = sinf(M_PI / 3.0f);

    struct Rot3f rot;
    rot3f_init(&rot);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_from_yaw(&rot, yaw));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r00(&rot));
    TEST_ASSERT_EQUAL_FLOAT(-sin45, rot3f_get_r01(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_EQUAL_FLOAT(sin45, rot3f_get_r10(&rot));
    TEST_ASSERT_EQUAL_FLOAT(cos45, rot3f_get_r11(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_to_ypr(void)
{
    const float32_t roll  = 0.1;
    const float32_t pitch = -0.2;
    const float32_t yaw   = 0.3;

    struct Rot3f rot;
    rot3f_init(&rot);
    rot3f_from_rpy(&rot, roll, pitch, yaw);

    float32_t actual_roll, actual_pitch, actual_yaw;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_to_ypr(&rot, &actual_yaw, &actual_pitch, &actual_roll));
    TEST_ASSERT_EQUAL_FLOAT(roll, actual_roll);
    TEST_ASSERT_EQUAL_FLOAT(pitch, actual_pitch);
    TEST_ASSERT_EQUAL_FLOAT(yaw, actual_yaw);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_to_rpy(void)
{
    const float32_t roll  = 0.1;
    const float32_t pitch = -0.2;
    const float32_t yaw   = 0.3;

    struct Rot3f rot;
    rot3f_init(&rot);
    rot3f_from_rpy(&rot, roll, pitch, yaw);

    float32_t actual_roll, actual_pitch, actual_yaw;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_to_rpy(&rot, &actual_roll, &actual_pitch, &actual_yaw));
    TEST_ASSERT_EQUAL_FLOAT(roll, actual_roll);
    TEST_ASSERT_EQUAL_FLOAT(pitch, actual_pitch);
    TEST_ASSERT_EQUAL_FLOAT(yaw, actual_yaw);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3f_set_identity(void)
{
    struct Rot3f rot;
    rot3f_init(&rot);

    // all method and check resutls
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_set_identity(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r00(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r01(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r10(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r11(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&rot));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&rot));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r22(&rot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_rot3_to_quaternionf(void)
{
    struct Rot3f rot;
    rot3f_init(&rot);
    rot3f_from_pitch(&rot, -M_PI / 2.0f);

    const float32_t    value = sqrtf(2.0f) / 2.0f;
    struct Quaternionf expected;
    quaternionf_init_from_scalars(&expected, value, 0.0f, -value, 0.0f);

    // call method and check results
    struct Quaternionf actual;
    quaternionf_init(&actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rot3f_to_quaternionf(&rot, &actual));
    TEST_ASSERT_TRUE(quaternionf_is_equal(&expected, &actual));
}

static void test_rot3f_serialize_deserialize(void)
{
    struct Rot3f rot;
    uint8_t buffer[128];
    uint32_t expected_size;
    retcode_t rc;

    rot3f_init(&rot);

    expected_size = rot3f_get_serialized_size(&rot);

    rc = rot3f_serialize(&rot, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, rc);
    rc = rot3f_deserialize(&rot, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, rc);

    rc = rot3f_serialize(&rot, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(expected_size, rc);
    rc = rot3f_deserialize(&rot, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(expected_size, rc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_rot3f_init);
    RUN_TEST(test_rot3f_init_from_scalars);
    RUN_TEST(test_rot3f_init_from_rot3f);
    RUN_TEST(test_rot3f_is_valid);
    RUN_TEST(test_rot3f_is_equal);
    RUN_TEST(test_rot3f_to_matrix33f);
    RUN_TEST(test_rot3f_transpose);
    RUN_TEST(test_rot3f_inverse);
    RUN_TEST(test_rot3f_rotate_vector3f);
    RUN_TEST(test_rot3f_unrotate_vector3f);
    RUN_TEST(test_rot3f_multiply_vector3f);
    RUN_TEST(test_rot3f_rotate_point3f);
    RUN_TEST(test_rot3f_unrotate_point3f);
    RUN_TEST(test_rot3f_multiply_point3f);
    RUN_TEST(test_rot3f_compose);
    RUN_TEST(test_rot3f_multiply);
    RUN_TEST(test_rot3f_from_angle_axis);
    RUN_TEST(test_rot3f_to_angle_axis);
    RUN_TEST(test_rot3f_expmap);
    RUN_TEST(test_rot3f_logmap);
    RUN_TEST(test_rot3f_compute_angle_diff);
    RUN_TEST(test_rot3f_from_rpy);
    RUN_TEST(test_rot3f_from_ypr);
    RUN_TEST(test_rot3f_from_roll);
    RUN_TEST(test_rot3f_from_pitch);
    RUN_TEST(test_rot3f_from_yaw);
    RUN_TEST(test_rot3f_to_ypr);
    RUN_TEST(test_rot3f_to_rpy);
    RUN_TEST(test_rot3f_set_identity);
    RUN_TEST(test_rot3_to_quaternionf);
    RUN_TEST(test_rot3f_serialize_deserialize);
    return UNITY_END();
}
