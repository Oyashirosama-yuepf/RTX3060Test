/*!
 * @file test_pose3_float32.c
 * @brief unit test of pose3
 * @author duyanwei@holomatic.com
 * @date 2019-08-16
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/geometry/pose3_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_init(void)
{
    struct Pose3f pose;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_init(&pose));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r00(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r01(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r10(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r11(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r22(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pose.translation.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pose.translation.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pose.translation.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_init_from_pose3f(void)
{
    struct Pose3f expected;
    pose3f_init(&expected);
    rot3f_from_rpy(&expected.rotation, 0.1f, -0.2f, 0.3f);
    point3f_init_from_scalars(&expected.translation, -0.4f, 0.5f, -0.6f);

    struct Pose3f actual;
    pose3f_init(&actual);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_init_from_pose3f(&actual, &expected));
    TEST_ASSERT_TRUE(rot3f_is_equal(&expected.rotation, &actual.rotation));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected.translation, &actual.translation));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_init_from_rot3f_and_point3f(void)
{
    struct Rot3f rot;
    rot3f_init(&rot);
    rot3f_from_rpy(&rot, 0.1f, -0.2f, 0.3f);

    struct Point3f point;
    point3f_init_from_scalars(&point, -0.4f, 0.5f, -0.6f);

    struct Pose3f pose;
    pose3f_init(&pose);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_init_from_rot3f_and_point3f(&pose, &rot, &point));
    TEST_ASSERT_TRUE(rot3f_is_equal(&rot, &pose.rotation));
    TEST_ASSERT_TRUE(point3f_is_equal(&point, &pose.translation));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_init_from_matrix44f(void)
{
    struct Matrixf matrix;
    float32_t      matrix_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&matrix, 4, 4, matrix_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    float32_t array[16];
    {
        struct Rot3f rot;
        rot3f_init(&rot);
        rot3f_from_rpy(&rot, 0.1f, -0.2f, 0.3f);

        array[0]  = rot3f_get_r00(&rot);
        array[1]  = rot3f_get_r01(&rot);
        array[2]  = rot3f_get_r02(&rot);
        array[3]  = 0.5f;
        array[4]  = rot3f_get_r10(&rot);
        array[5]  = rot3f_get_r11(&rot);
        array[6]  = rot3f_get_r12(&rot);
        array[7]  = 1.5f;
        array[8]  = rot3f_get_r20(&rot);
        array[9]  = rot3f_get_r21(&rot);
        array[10] = rot3f_get_r22(&rot);
        array[11] = 2.5f;
        array[12] = 0.0f;
        array[13] = 0.0f;
        array[14] = 0.0f;
        array[15] = 1.0f;

        matrixf_set_from_array(&matrix, array, 16);
    }

    // call method and check results
    struct Pose3f pose;
    pose3f_init(&pose);
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_init_from_matrix44f(&pose, &matrix));
    TEST_ASSERT_EQUAL_FLOAT(array[0], rot3f_get_r00(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(array[1], rot3f_get_r01(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(array[2], rot3f_get_r02(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(array[4], rot3f_get_r10(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(array[5], rot3f_get_r11(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(array[6], rot3f_get_r12(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(array[8], rot3f_get_r20(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(array[9], rot3f_get_r21(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(array[10], rot3f_get_r22(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(array[3], pose.translation.x);
    TEST_ASSERT_EQUAL_FLOAT(array[7], pose.translation.y);
    TEST_ASSERT_EQUAL_FLOAT(array[11], pose.translation.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_is_valid(void)
{
    struct Pose3f pose1;
    pose3f_init(&pose1);
    struct Pose3f pose2;
    pose3f_init(&pose2);
    {
        struct Rot3f rot;
        rot3f_init(&rot);
        rot3f_from_rpy(&rot, 0.1f, -0.2f, 0.3f);

        struct Point3f point;
        point3f_init_from_scalars(&point, -0.4f, 0.5f, -0.6f);
        pose3f_init_from_rot3f_and_point3f(&pose2, &rot, &point);
    }

    // call method and check results
    TEST_ASSERT_TRUE(pose3f_is_valid(&pose1));
    TEST_ASSERT_TRUE(pose3f_is_valid(&pose2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_is_equal(void)
{
    struct Pose3f pose1;
    pose3f_init(&pose1);
    {
        rot3f_from_rpy(&pose1.rotation, 0.1f, -0.2f, 0.3f);
        point3f_init_from_scalars(&pose1.translation, -0.4f, 0.5f, -0.6f);
    }

    struct Pose3f pose2;
    pose3f_init_from_pose3f(&pose2, &pose1);

    // call method and check results
    TEST_ASSERT_TRUE(pose3f_is_equal(&pose1, &pose2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_to_matrix44f(void)
{
    struct Pose3f pose;
    pose3f_init(&pose);
    {
        rot3f_from_rpy(&pose.rotation, 0.1f, -0.2f, 0.3f);
        point3f_init_from_scalars(&pose.translation, -0.4f, 0.5f, -0.6f);
    }

    // expectecd matrix
    struct Matrixf expected;
    float32_t      expected_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&expected, 4, 4, expected_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    matrixf_set_identity(&expected);
    {
        matrixf_set(&expected, 0u, 0u, rot3f_get_r00(&pose.rotation));
        matrixf_set(&expected, 0u, 1u, rot3f_get_r01(&pose.rotation));
        matrixf_set(&expected, 0u, 2u, rot3f_get_r02(&pose.rotation));
        matrixf_set(&expected, 0u, 3u, pose.translation.x);
        matrixf_set(&expected, 1u, 0u, rot3f_get_r10(&pose.rotation));
        matrixf_set(&expected, 1u, 1u, rot3f_get_r11(&pose.rotation));
        matrixf_set(&expected, 1u, 2u, rot3f_get_r12(&pose.rotation));
        matrixf_set(&expected, 1u, 3u, pose.translation.y);
        matrixf_set(&expected, 2u, 0u, rot3f_get_r20(&pose.rotation));
        matrixf_set(&expected, 2u, 1u, rot3f_get_r21(&pose.rotation));
        matrixf_set(&expected, 2u, 2u, rot3f_get_r22(&pose.rotation));
        matrixf_set(&expected, 2u, 3u, pose.translation.z);
    }

    // actual matrix
    struct Matrixf actual;
    float32_t      actual_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&actual, 4, 4, actual_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_to_matrix44f(&pose, &actual));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_inverse(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 11.0f, 21.0f, 31.0f);
    }

    struct Pose3f expected;
    pose3f_init(&expected);

    {
        rot3f_from_yaw(&expected.rotation, -M_PI / 2.0f);
        point3f_init_from_scalars(&expected.translation, -21.0f, 11.0f, -31.0f);
    }

    struct Pose3f actual;
    pose3f_init(&actual);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_inverse(&self, &actual));
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_compose(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 11.0f, 21.0f, 31.0f);
    }

    struct Pose3f other;
    pose3f_init(&other);
    {
        rot3f_from_roll(&other.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&other.translation, 11.0f, 21.0f, 31.0f);
    }

    struct Pose3f expected;
    pose3f_init(&expected);
    {
        rot3f_from_rpy(&expected.rotation, M_PI / 2.0f, 0.0f, M_PI / 2.0f);
        point3f_init_from_scalars(&expected.translation, -10.0f, 32.0f, 62.0f);
    }

    struct Pose3f actual;
    pose3f_init(&actual);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_compose(&self, &other, &actual));
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_multiply(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 11.0f, 21.0f, 31.0f);
    }

    struct Pose3f other;
    pose3f_init(&other);
    {
        rot3f_from_roll(&other.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&other.translation, 11.0f, 21.0f, 31.0f);
    }

    struct Pose3f expected;
    pose3f_init(&expected);
    {
        rot3f_from_rpy(&expected.rotation, M_PI / 2.0f, 0.0f, M_PI / 2.0f);
        point3f_init_from_scalars(&expected.translation, -10.0f, 32.0f, 62.0f);
    }

    struct Pose3f actual;
    pose3f_init(&actual);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_multiply(&self, &other, &actual));
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_transform_from_point3f(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 1.0f, -1.0f, -1.0f);
    }

    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 1.0f, 1.0f);

    // expected point
    struct Point3f expected;
    point3f_init_from_scalars(&expected, 0.0f, 0.0f, 0.0f);

    // call method and check results
    struct Point3f actual;
    point3f_init(&actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_transform_from_point3f(&self, &point, &actual));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_transform_to_point3f(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 1.0f, -1.0f, -1.0f);
    }

    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 1.0f, 1.0f);

    // expected point
    struct Point3f expected;
    point3f_init_from_scalars(&expected, 2.0f, 0.0f, 2.0f);

    // call method and check results
    struct Point3f actual;
    point3f_init(&actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_transform_to_point3f(&self, &point, &actual));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_multiply_point3f(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 1.0f, -1.0f, -1.0f);
    }

    struct Point3f point;
    point3f_init_from_scalars(&point, 1.0f, 1.0f, 1.0f);

    // expected point
    struct Point3f expected;
    point3f_init_from_scalars(&expected, 0.0f, 0.0f, 0.0f);

    // call method and check results
    struct Point3f actual;
    point3f_init(&actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_multiply_point3f(&self, &point, &actual));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_transform_from_vector3f(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 1.0f, -1.0f, -1.0f);
    }

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
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_transform_from_vector3f(&self, &vec, &actual));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_transform_to_vector3f(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 1.0f, -1.0f, -1.0f);
    }

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
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_transform_to_vector3f(&self, &vec, &actual));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_multiply_vector3f(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 1.0f, -1.0f, -1.0f);
    }

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
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_multiply_vector3f(&self, &vec, &actual));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_dist(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 11.0f, 21.0f, 31.0f);
    }

    struct Pose3f other;
    pose3f_init(&other);
    {
        rot3f_from_roll(&other.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&other.translation, 11.0f, 21.0f, 31.0f);
    }

    const float32_t expected = 0;

    // call method and check results
    float32_t actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_dist(&self, &other, &actual));
    TEST_ASSERT_EQUAL_FLOAT(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_between(void)
{
    struct Pose3f self;
    pose3f_init(&self);
    {
        rot3f_from_yaw(&self.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&self.translation, 11.0f, 21.0f, 31.0f);
    }

    struct Pose3f other;
    pose3f_init(&other);

    {
        rot3f_from_roll(&other.rotation, M_PI / 2.0f);
        point3f_init_from_scalars(&other.translation, 11.0f, 21.0f, 31.0f);
    }

    struct Pose3f expected;
    pose3f_init(&expected);
    {
        rot3f_from_rpy(&expected.rotation, M_PI / 2.0f, 0.0f, -M_PI / 2.0f);
        point3f_init_from_scalars(&expected.translation, 0.0f, 0.0f, 0.0f);
    }

    struct Pose3f actual;
    pose3f_init(&actual);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_between(&self, &other, &actual));
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_expmap(void)
{
    // construct an angle-axis which rotates y-axis about theta angle
    const float32_t tx    = 0.1f;
    const float32_t ty    = 0.2f;
    const float32_t tz    = 0.3f;
    const float32_t theta = M_PI / 2.0f;

    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&vec, 6, vec_buf, VECTORF_MIN_BUF_SIZE(6u));
    vectorf_set(&vec, 0u, 0.0f);
    vectorf_set(&vec, 1u, theta);
    vectorf_set(&vec, 2u, 0.0f);
    vectorf_set(&vec, 3u, tx);
    vectorf_set(&vec, 4u, ty);
    vectorf_set(&vec, 5u, tz);

    // expected pose3
    struct Pose3f expected;
    pose3f_init(&expected);
    rot3f_from_pitch(&expected.rotation, theta);
    point3f_init_from_scalars(&expected.translation, tx, ty, tz);

    // call method and check results
    struct Pose3f actual;
    pose3f_init(&actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_expmap(&actual, &vec));
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_logmap(void)
{
    struct Pose3f pose;
    pose3f_init(&pose);

    // construct a translation vector
    const float32_t tx = -0.1f;
    const float32_t ty = -0.2f;
    const float32_t tz = -0.3f;
    point3f_init_from_scalars(&pose.translation, tx, ty, tz);

    // construct a matrix which rotates y-axis about theta angle
    const float32_t theta = -M_PI / 5.0f;
    rot3f_from_pitch(&pose.rotation, theta);

    // expected vector
    struct Vectorf expected;
    float32_t      expected_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&expected, 6, expected_buf, VECTORF_MIN_BUF_SIZE(6u));
    vectorf_set(&expected, 0u, 0.0f);
    vectorf_set(&expected, 1u, theta);
    vectorf_set(&expected, 2u, 0.0f);
    vectorf_set(&expected, 3u, tx);
    vectorf_set(&expected, 4u, ty);
    vectorf_set(&expected, 5u, tz);

    // call method and check results
    struct Vectorf actual;
    float32_t      actual_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&actual, 6, actual_buf, VECTORF_MIN_BUF_SIZE(6u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_logmap(&pose, &actual));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_set_identity(void)
{
    struct Pose3f pose;
    pose3f_init(&pose);

    // all method and check resutls
    TEST_ASSERT_EQUAL(RC_SUCCESS, pose3f_set_identity(&pose));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r00(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r01(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r02(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r10(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r11(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r12(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r20(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, rot3f_get_r21(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, rot3f_get_r22(&pose.rotation));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pose.translation.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pose.translation.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pose.translation.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_get_translation(void)
{
    struct Rot3f rot;
    rot3f_init(&rot);
    rot3f_from_rpy(&rot, 0.1f, -0.2f, 0.3f);

    struct Point3f expected_point;
    point3f_init_from_scalars(&expected_point, -0.4f, 0.5f, -0.6f);

    struct Pose3f pose;
    pose3f_init_from_rot3f_and_point3f(&pose, &rot, &expected_point);

    /* Test get translation funcion */
    TEST_ASSERT_TRUE(point3f_is_equal(&expected_point, pose3f_get_translation(&pose)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_get_rotation(void)
{
    struct Rot3f expected_rot;
    rot3f_init(&expected_rot);
    rot3f_from_rpy(&expected_rot, 0.1f, -0.2f, 0.3f);

    struct Point3f point;
    point3f_init_from_scalars(&point, -0.4f, 0.5f, -0.6f);

    struct Pose3f pose;
    pose3f_init_from_rot3f_and_point3f(&pose, &expected_rot, &point);

    /* Test get rotation funcion */
    TEST_ASSERT_TRUE(rot3f_is_equal(&expected_rot, pose3f_get_rotation(&pose)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_pose3f_get_yaw(void)
{
    const float32_t expected_yaw = 0.3f;

    struct Rot3f rot;
    rot3f_init(&rot);
    rot3f_from_rpy(&rot, 0.1f, -0.2f, expected_yaw);

    struct Point3f point;
    point3f_init_from_scalars(&point, -0.4f, 0.5f, -0.6f);

    struct Pose3f pose;
    pose3f_init_from_rot3f_and_point3f(&pose, &rot, &point);

    /* Test get rotation funcion */
    TEST_ASSERT_EQUAL_FLOAT(expected_yaw, pose3f_get_yaw(&pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_pose3f_init);
    RUN_TEST(test_pose3f_init_from_pose3f);
    RUN_TEST(test_pose3f_init_from_rot3f_and_point3f);
    RUN_TEST(test_pose3f_init_from_matrix44f);
    RUN_TEST(test_pose3f_is_valid);
    RUN_TEST(test_pose3f_is_equal);
    RUN_TEST(test_pose3f_to_matrix44f);
    RUN_TEST(test_pose3f_inverse);
    RUN_TEST(test_pose3f_compose);
    RUN_TEST(test_pose3f_multiply);
    RUN_TEST(test_pose3f_transform_from_point3f);
    RUN_TEST(test_pose3f_transform_to_point3f);
    RUN_TEST(test_pose3f_multiply_point3f);
    RUN_TEST(test_pose3f_transform_from_vector3f);
    RUN_TEST(test_pose3f_transform_to_vector3f);
    RUN_TEST(test_pose3f_multiply_vector3f);
    RUN_TEST(test_pose3f_dist);
    RUN_TEST(test_pose3f_between);
    RUN_TEST(test_pose3f_expmap);
    RUN_TEST(test_pose3f_logmap);
    RUN_TEST(test_pose3f_set_identity);
    RUN_TEST(test_pose3f_get_translation);
    RUN_TEST(test_pose3f_get_rotation);
    RUN_TEST(test_pose3f_get_yaw);
    return UNITY_END();
}
