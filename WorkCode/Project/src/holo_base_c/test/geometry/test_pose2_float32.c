/*!
 * @brief Unit test for rot2.
 * @author lichao@holomaitc.com
 * @date Aug 20, 2019
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/pose2_float32.h>
#include <holo_c/port/endian.h>
#include <math.h>
#include <unity.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_init(void)
{
    struct Pose2f in1;

    /* test initialization functions */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_init(&in1));
    struct Rot2f expected_rot, actual_rot;
    rot2f_init(&expected_rot);
    pose2f_get_rotation(&in1, &actual_rot);
    struct Point2f expected_pt, actual_pt;
    point2f_init(&expected_pt);
    pose2f_get_translation(&in1, &actual_pt);
    TEST_ASSERT_TRUE(rot2f_is_equal(&expected_rot, &actual_rot));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_init_from_rot2f_and_point2f(void)
{
    struct Pose2f in1;

    struct Rot2f   expected_rot, actual_rot;
    struct Point2f expected_pt, actual_pt;
    rot2f_init(&expected_rot);
    point2f_init(&expected_pt);

    /* test initialization from rot2f and point2f function */
    float32_t theta = 5.0, x = 2.0, y = 3.0;
    rot2f_init_from_angle(&expected_rot, theta);
    point2f_init_from_scalars(&expected_pt, x, y);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_init_from_rot2f_and_point2f(&in1, &expected_rot, &expected_pt));
    pose2f_get_rotation(&in1, &actual_rot);
    pose2f_get_translation(&in1, &actual_pt);
    TEST_ASSERT_TRUE(rot2f_is_equal(&expected_rot, &actual_rot));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_init_from_angle_and_point2f(void)
{
    struct Pose2f in1;

    struct Rot2f   expected_rot, actual_rot;
    struct Point2f expected_pt, actual_pt;
    rot2f_init(&expected_rot);
    point2f_init(&expected_pt);

    /* test initialization from angle and point2f function */
    float32_t theta = 5.0, x = 2.0, y = 3.0;
    rot2f_init_from_angle(&expected_rot, theta);
    point2f_init_from_scalars(&expected_pt, x, y);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_init_from_angle_and_point2f(&in1, theta, &expected_pt));
    pose2f_get_rotation(&in1, &actual_rot);
    pose2f_get_translation(&in1, &actual_pt);
    TEST_ASSERT_TRUE(rot2f_is_equal(&expected_rot, &actual_rot));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_init_from_matrix33f(void)
{
    struct Pose2f in1;

    /* generate expected objects */
    struct Rot2f   expected_rot, actual_rot;
    struct Point2f expected_pt, actual_pt;
    float32_t      theta = M_PI / 2.0, x = 2.0, y = 3.0;
    point2f_init_from_scalars(&expected_pt, x, y);
    rot2f_init_from_angle(&expected_rot, theta);

    /* initial matrix to identity matrix */
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    matrixf_set_identity(&mat);

    /* set rotation matrix */
    matrixf_set(&mat, 0, 0, 0);
    matrixf_set(&mat, 0, 1, -1);
    matrixf_set(&mat, 0, 2, x);
    matrixf_set(&mat, 1, 0, 1);
    matrixf_set(&mat, 1, 1, 0);
    matrixf_set(&mat, 1, 2, y);
    matrixf_set(&mat, 2, 0, 0);
    matrixf_set(&mat, 2, 1, 0);
    matrixf_set(&mat, 2, 2, 1);

    /* test initialization from matrix33f function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_init_from_matrix33f(&in1, &mat));
    pose2f_get_rotation(&in1, &actual_rot);
    pose2f_get_translation(&in1, &actual_pt);
    TEST_ASSERT_TRUE(rot2f_is_equal(&expected_rot, &actual_rot));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_init_from_pose2f(void)
{
    struct Pose2f in1;

    /* generate expected objects */
    struct Rot2f   expected_rot, actual_rot;
    struct Point2f expected_pt, actual_pt;
    float32_t      theta = M_PI / 2.0, x = 2.0, y = 3.0;
    point2f_init_from_scalars(&expected_pt, x, y);
    rot2f_init_from_angle(&expected_rot, theta);

    /* test initialization from pose2f function */
    struct Pose2f pose;
    pose2f_init_from_rot2f_and_point2f(&pose, &expected_rot, &expected_pt);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_init_from_pose2f(&in1, &pose));
    pose2f_get_rotation(&in1, &actual_rot);
    pose2f_get_translation(&in1, &actual_pt);
    TEST_ASSERT_TRUE(rot2f_is_equal(&expected_rot, &actual_rot));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_composition(void)
{
    struct Pose2f   pose1, pose2;
    const float32_t theta = M_PI / 4.0, x1 = 1.0, y1 = 5.0, x2 = 3.0, y2 = 3.0;
    const float32_t s = sinf(theta), c = cosf(theta);
    struct Point2f  point1, point2;
    point2f_init_from_scalars(&point1, x1, y1);
    point2f_init_from_scalars(&point2, x2, y2);
    pose2f_init_from_angle_and_point2f(&pose1, theta, &point1);
    pose2f_init_from_angle_and_point2f(&pose2, theta, &point2);

    /* generate expected 2D pose */
    struct Point2f  expected_point;
    struct Pose2f   expected_pose;
    const float32_t expected_x = (x2 * c) - (y2 * s) + x1;
    const float32_t expected_y = (x2 * s) + (y2 * c) + y1;
    point2f_init_from_scalars(&expected_point, expected_x, expected_y);
    pose2f_init_from_angle_and_point2f(&expected_pose, 2.0 * theta, &expected_point);

    /* test composition functions */
    struct Pose2f actual_pose;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_compose(&pose1, &pose2, &actual_pose));
    TEST_ASSERT_TRUE(pose2f_is_equal(&expected_pose, &actual_pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_equivalent(void)
{
    struct Pose2f   pose1, pose2;
    struct Point2f  pt1, pt2;
    const float32_t theta = 4.0;

    /* initialize two 2D poses */
    point2f_init_from_scalars(&pt1, 1.0, 2.0);
    point2f_init_from_scalars(&pt2, 2.0, 2.0);
    pose2f_init_from_angle_and_point2f(&pose1, theta, &pt1);
    pose2f_init_from_angle_and_point2f(&pose2, theta, &pt2);

    /* test equal function */
    TEST_ASSERT_FALSE(pose2f_is_equal(&pose1, &pose2));
    pose2f_set_translation(&pose2, &pt1);
    TEST_ASSERT_TRUE(pose2f_is_equal(&pose1, &pose2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_inverse(void)
{
    const float32_t theta = M_PI / 4.0, x = 1.0, y = 2.0;

    /* initialize 2D pose */
    struct Point2f pt;
    point2f_init_from_scalars(&pt, x, y);
    struct Pose2f pose;
    pose2f_init_from_angle_and_point2f(&pose, theta, &pt);

    /* generate expected 2D pose */
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, -x, -y);
    struct Pose2f expected_pose;
    pose2f_init_from_angle_and_point2f(&expected_pose, -theta, &expected_pt);

    /* test inverse function */
    struct Pose2f actual_pose;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_inverse(&pose, &actual_pose));
    TEST_ASSERT_TRUE(pose2f_is_equal(&expected_pose, &actual_pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_between(void)
{
    struct Pose2f   pose1, pose2;
    struct Point2f  pt1, pt2;
    const float32_t theta1 = M_PI / 2.0, x1 = 1.0, y1 = 2.0;
    const float32_t theta2 = M_PI, x2 = -1.0, y2 = 4.0;
    const float32_t s1 = sinf(-theta1), c1 = cosf(-theta1);

    /* initialize two 2D poses */
    point2f_init_from_scalars(&pt1, x1, y1);
    point2f_init_from_scalars(&pt2, x2, y2);
    pose2f_init_from_angle_and_point2f(&pose1, theta1, &pt1);
    pose2f_init_from_angle_and_point2f(&pose2, theta2, &pt2);

    /* generate expected pose */
    struct Point2f  expected_pt;
    const float32_t expected_x = (x2 * c1) - (y2 * s1) - x1;
    const float32_t expected_y = (x2 * s1) + (y2 * c1) - y1;
    point2f_init_from_scalars(&expected_pt, expected_x, expected_y);
    struct Pose2f expected_pose;
    pose2f_init_from_angle_and_point2f(&expected_pose, theta2 - theta1, &expected_pt);

    /* test between function */
    struct Pose2f actual_pose;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_between(&pose1, &pose2, &actual_pose));
    struct Point2f pt;
    pose2f_get_translation(&actual_pose, &pt);
    TEST_ASSERT_TRUE(pose2f_is_equal(&expected_pose, &actual_pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_transform_to_point2f(void)
{
    const float32_t theta = M_PI / 2.0;

    /* initialize 2D pose */
    struct Pose2f  pose;
    struct Point2f tmp_pt;
    point2f_init_from_scalars(&tmp_pt, 1.0, 2.0);
    pose2f_init_from_angle_and_point2f(&pose, theta, &tmp_pt);

    /* initialize 2D point */
    struct Point2f pt;
    point2f_init_from_scalars(&pt, -4.0, 6.0);

    /* generate expected 2D point */
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, 4.0, 5.0);

    /* test transform to point2f function */
    struct Point2f actual_pt;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_transform_to_point2f(&pose, &pt, &actual_pt));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_transform_to_vector2f(void)
{
    const float32_t theta = M_PI / 2.0;

    /* initialize 2D pose */
    struct Pose2f  pose;
    struct Point2f tmp_pt;
    point2f_init_from_scalars(&tmp_pt, 1.0, 2.0);
    pose2f_init_from_angle_and_point2f(&pose, theta, &tmp_pt);

    /* initialize 2D vector */
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&vec, 0, -4.0);
    vectorf_set(&vec, 1, 6.0);

    /* generate expected 2D vector */
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&expected_vec, 2, expected_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&expected_vec, 0, 4.0);
    vectorf_set(&expected_vec, 1, 5.0);

    /* test transform to vector2f function */
    struct Vectorf actual_vec;
    float32_t      actual_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&actual_vec, 2, actual_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_transform_to_vector2f(&pose, &vec, &actual_vec));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_vec, &actual_vec));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_transform_from_point2f(void)
{
    const float32_t theta = M_PI / 2.0;

    /* initialize 2D pose */
    struct Pose2f  pose;
    struct Point2f tmp_pt;
    point2f_init_from_scalars(&tmp_pt, 1.0, 2.0);
    pose2f_init_from_angle_and_point2f(&pose, theta, &tmp_pt);

    /* initialize 2D point */
    struct Point2f pt;
    point2f_init_from_scalars(&pt, 4.0, 5.0);

    /* generate expected 2D point */
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, -4.0, 6.0);

    /* test transform from point2f function */
    struct Point2f actual_pt;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_transform_from_point2f(&pose, &pt, &actual_pt));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));
    struct Point2f actual_pt2;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_multiply_point2f(&pose, &pt, &actual_pt2));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_transform_from_vector2f(void)
{
    const float32_t theta = M_PI / 2.0;

    /* initialize 2D pose */
    struct Pose2f  pose;
    struct Point2f tmp_pt;
    point2f_init_from_scalars(&tmp_pt, 1.0, 2.0);
    pose2f_init_from_angle_and_point2f(&pose, theta, &tmp_pt);

    /* initialize 2D vector */
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&vec, 0, 4.0);
    vectorf_set(&vec, 1, 5.0);

    /* generate expected 2D vector */
    struct Vectorf expected_vec;
    float32_t      expected_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&expected_vec, 2, expected_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&expected_vec, 0, -4.0);
    vectorf_set(&expected_vec, 1, 6.0);

    /* test transform from vector2f function */
    struct Vectorf actual_vec;
    float32_t      actual_vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&actual_vec, 2, actual_vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_transform_from_vector2f(&pose, &vec, &actual_vec));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_vec, &actual_vec));
    struct Vectorf actual_vec2;
    float32_t      actual_vec2_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&actual_vec2, 2, actual_vec2_buf, VECTORF_MIN_BUF_SIZE(2u));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_multiply_vector2f(&pose, &vec, &actual_vec2));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_vec, &actual_vec2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_getter_and_setter(void)
{
    struct Pose2f in;

    /* initialize 2D pose */
    pose2f_init(&in);

    /* test setter and getter functions */
    const float32_t expected_x = 4.0, expected_y = 5.0, expected_theta = 3.0;
    struct Rot2f    expected_rot, actual_rot;
    rot2f_init_from_angle(&expected_rot, expected_theta);
    rot2f_init(&actual_rot);
    struct Point2f expected_pt, actual_pt;
    point2f_init_from_scalars(&expected_pt, expected_x, expected_y);
    point2f_init(&actual_pt);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_set_rotation(&in, &expected_rot));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_set_translation(&in, &expected_pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_get_rotation(&in, &actual_rot));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_get_translation(&in, &actual_pt));
    TEST_ASSERT_TRUE(rot2f_is_equal(&expected_rot, &actual_rot));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt, &actual_pt));

    float32_t actual_x = 0.0, actual_y = 0.0, actual_theta = 0.0;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_get_x(&in, &actual_x));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_get_y(&in, &actual_y));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_get_angle(&in, &actual_theta));
    TEST_ASSERT_EQUAL_FLOAT(expected_x, actual_x);
    TEST_ASSERT_EQUAL_FLOAT(expected_y, actual_y);
    TEST_ASSERT_EQUAL_FLOAT(expected_theta, actual_theta);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_to_matrix33f(void)
{
    const float32_t x = 3.0, y = 5.0, theta = M_PI / 2.0;  // in meter and radian
    struct Pose2f   in;

    /* initialize 2D pose */
    struct Point2f pt;
    point2f_init_from_scalars(&pt, x, y);
    pose2f_init_from_angle_and_point2f(&in, theta, &pt);

    /* generate expected rotation matrix */
    struct Matrixf expected_matrix;
    float32_t      expected_matrix_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&expected_matrix, 3, 3, expected_matrix_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    matrixf_set(&expected_matrix, 0, 0, cosf(theta));
    matrixf_set(&expected_matrix, 0, 1, -sinf(theta));
    matrixf_set(&expected_matrix, 0, 2, x);
    matrixf_set(&expected_matrix, 1, 0, sinf(theta));
    matrixf_set(&expected_matrix, 1, 1, cosf(theta));
    matrixf_set(&expected_matrix, 1, 2, y);
    matrixf_set(&expected_matrix, 2, 0, 0);
    matrixf_set(&expected_matrix, 2, 1, 0);
    matrixf_set(&expected_matrix, 2, 2, 1);

    /* test to matrix function */
    struct Matrixf actual_matrix;
    float32_t      actual_matrix_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&actual_matrix, 3, 3, actual_matrix_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_to_matrix33f(&in, &actual_matrix));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected_matrix, &actual_matrix));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_set_identity(void)
{
    const float32_t theta = M_PI / 4.0;  // in radian
    struct Pose2f   in;

    struct Point2f pt;
    point2f_init_from_scalars(&pt, 1.0, 2.0);
    pose2f_init_from_angle_and_point2f(&in, theta, &pt);

    /* generate expected rotation */
    struct Matrixf expected_matrix;
    float32_t      expected_matrix_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&expected_matrix, 3, 3, expected_matrix_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    matrixf_set_identity(&expected_matrix);

    /* test set identity function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_set_identity(&in));
    struct Matrixf actual_matrix;
    float32_t      actual_matrix_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&actual_matrix, 3, 3, actual_matrix_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    pose2f_to_matrix33f(&in, &actual_matrix);
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected_matrix, &actual_matrix));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_to_string(void)
{
    struct Pose2f in;

    struct Point2f pt;
    point2f_init_from_scalars(&pt, 10.0, 9.0);
    pose2f_init_from_angle_and_point2f(&in, 5.0, &pt);

    /* test to string function */
    const uint32_t buffer_length = 100u;

    char_t str[buffer_length];
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_to_string(&in, str, buffer_length));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pose2f_to_string(&in, str, buffer_length));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_is_valid(void)
{
    struct Pose2f   in;
    struct Point2f  pt;
    const float32_t theta = 5.0;
    point2f_init_from_scalars(&pt, 3.0, 4.0);
    pose2f_init_from_angle_and_point2f(&in, theta, &pt);

    /* test valid function */
    TEST_ASSERT_TRUE(pose2f_is_valid(&in));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_serialize(void)
{
    uint8_t buffer[16u];

    struct Pose2f in;

    /* test get serialized size function */
    TEST_ASSERT_EQUAL_INT32(16u, pose2f_get_serialized_size(&in));

    /* test serialize function */
    struct Point2f pt;
    point2f_init_from_scalars(&pt, 1, 0);
    pose2f_init_from_angle_and_point2f(&in, 0.0, &pt);
    TEST_ASSERT_EQUAL_INT32(16u, pose2f_serialize(&in, buffer, 16u));
#if defined(HOLO_PLATFORM_BIG_ENDIAN)
    uint8_t expected_buffer[16u] = {0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 16u);
#elif defined(HOLO_PLATFORM_LITTLE_ENDIAN)
    uint8_t expected_buffer[16u] = {0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 16u);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_pose2f_deserialize(void)
{
    uint8_t buffer[16u];
#if defined(HOLO_PLATFORM_BIG_ENDIAN)
    buffer[0]  = 0x00;
    buffer[1]  = 0x00;
    buffer[2]  = 0x80;
    buffer[3]  = 0x3f;
    buffer[4]  = 0x00;
    buffer[5]  = 0x00;
    buffer[6]  = 0x00;
    buffer[7]  = 0x00;
    buffer[8]  = 0x00;
    buffer[9]  = 0x00;
    buffer[10] = 0x80;
    buffer[11] = 0x3f;
    buffer[12] = 0x00;
    buffer[13] = 0x00;
    buffer[14] = 0x00;
    buffer[15] = 0x00;
#elif defined(HOLO_PLATFORM_LITTLE_ENDIAN)
    buffer[0]  = 0x3f;
    buffer[1]  = 0x80;
    buffer[2]  = 0x00;
    buffer[3]  = 0x00;
    buffer[4]  = 0x00;
    buffer[5]  = 0x00;
    buffer[6]  = 0x00;
    buffer[7]  = 0x00;
    buffer[8]  = 0x3f;
    buffer[9]  = 0x80;
    buffer[10] = 0x00;
    buffer[11] = 0x00;
    buffer[12] = 0x00;
    buffer[13] = 0x00;
    buffer[14] = 0x00;
    buffer[15] = 0x00;
#endif

    struct Pose2f  pose;
    struct Point2f pt;

    /* test deserialize function */
    point2f_init_from_scalars(&pt, 0, 0);
    pose2f_init_from_angle_and_point2f(&pose, 3.0, &pt);
    TEST_ASSERT_EQUAL_INT32(16u, pose2f_deserialize(&pose, buffer, 16u));
    struct Pose2f  expected_pose;
    struct Point2f expected_pt;
    point2f_init_from_scalars(&expected_pt, 1, 0);
    pose2f_init_from_angle_and_point2f(&expected_pose, 0.0, &expected_pt);
    TEST_ASSERT_TRUE(pose2f_is_equal(&expected_pose, &pose));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_pose2f_init);
    RUN_TEST(test_pose2f_init_from_angle_and_point2f);
    RUN_TEST(test_pose2f_init_from_rot2f_and_point2f);
    RUN_TEST(test_pose2f_init_from_matrix33f);
    RUN_TEST(test_pose2f_init_from_pose2f);
    RUN_TEST(test_pose2f_composition);
    RUN_TEST(test_pose2f_equivalent);
    RUN_TEST(test_pose2f_inverse);
    RUN_TEST(test_pose2f_between);
    RUN_TEST(test_pose2f_transform_to_point2f);
    RUN_TEST(test_pose2f_transform_to_vector2f);
    RUN_TEST(test_pose2f_transform_from_point2f);
    RUN_TEST(test_pose2f_transform_from_vector2f);
    RUN_TEST(test_pose2f_getter_and_setter);
    RUN_TEST(test_pose2f_to_matrix33f);
    RUN_TEST(test_pose2f_set_identity);
    RUN_TEST(test_pose2f_to_string);
    RUN_TEST(test_pose2f_is_valid);
    RUN_TEST(test_pose2f_serialize);
    RUN_TEST(test_pose2f_deserialize);
    return UNITY_END();
}