/*!
 * @file test_box3_float32.c
 * @brief unit test of box3
 * @author duyanwei@holomatic.com
 * @date 2019-08-16
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/geometry/box3_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_init(void)
{
    struct Box3f box;

    struct Pose3f expected_pose;
    pose3f_init(&expected_pose);
    pose3f_set_identity(&expected_pose);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box3f_init(&box));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, box.width);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, box.height);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, box.depth);
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected_pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_init_from_two_point3f()
{
    struct Point3f pt1;
    point3f_init_from_scalars(&pt1, -1.0f, -2.0f, 3.0f);
    struct Point3f pt2;
    point3f_init_from_scalars(&pt2, 1.0f, 2.0f, -3.0f);

    struct Pose3f expected_pose;
    pose3f_init(&expected_pose);
    {
        point3f_init_from_scalars(&expected_pose.translation, -1.0f, -2.0f, -3.0f);
    }

    struct Box3f box;
    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box3f_init_from_two_point3f(&box, &pt1, &pt2));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, box.width);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, box.height);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, box.depth);
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected_pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_init_from_width_height_and_depth()
{
    // expected result
    const float32_t width  = 2.0f;
    const float32_t height = 3.0f;
    const float32_t depth  = 4.0f;
    struct Pose3f   expected_pose;
    pose3f_init(&expected_pose);
    pose3f_set_identity(&expected_pose);

    struct Box3f box;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box3f_init_from_width_height_and_depth(&box, width, height, depth));
    TEST_ASSERT_EQUAL_FLOAT(width, box.width);
    TEST_ASSERT_EQUAL_FLOAT(height, box.height);
    TEST_ASSERT_EQUAL_FLOAT(depth, box.depth);
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected_pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_init_from_width_height_depth_and_pose3f()
{
    // expected result
    const float32_t width  = 2.0f;
    const float32_t height = 3.0f;
    const float32_t depth  = 4.0f;
    struct Pose3f   pose;
    pose3f_init(&pose);
    {
        rot3f_from_rpy(&pose.rotation, -0.1f, 0.2f, -0.3f);
        point3f_init_from_scalars(&pose.translation, 0.4f, -0.5f, 0.6f);
    }

    struct Box3f box;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box3f_init_from_width_height_depth_and_pose3f(&box, width, height, depth, &pose));
    TEST_ASSERT_EQUAL_FLOAT(width, box.width);
    TEST_ASSERT_EQUAL_FLOAT(height, box.height);
    TEST_ASSERT_EQUAL_FLOAT(depth, box.depth);
    TEST_ASSERT_TRUE(pose3f_is_equal(&pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_init_from_vector3f_and_pose3f()
{
    // expected result
    const float32_t width  = 2.0f;
    const float32_t height = 3.0f;
    const float32_t depth  = 4.0f;

    struct Vectorf vector;
    float32_t      vector_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vector, 3, vector_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vector, 0u, width);
    vectorf_set(&vector, 1u, height);
    vectorf_set(&vector, 2u, depth);

    struct Pose3f pose;
    pose3f_init(&pose);
    {
        rot3f_from_rpy(&pose.rotation, -0.1f, 0.2f, -0.3f);
        point3f_init_from_scalars(&pose.translation, 0.4f, -0.5f, 0.6f);
    }

    struct Box3f box;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box3f_init_from_vector3f_and_pose3f(&box, &vector, &pose));
    TEST_ASSERT_EQUAL_FLOAT(width, box.width);
    TEST_ASSERT_EQUAL_FLOAT(height, box.height);
    TEST_ASSERT_EQUAL_FLOAT(depth, box.depth);
    TEST_ASSERT_TRUE(pose3f_is_equal(&pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_init_from_box3f()
{
    struct Box3f expected;
    {
        const float32_t width  = 2.0f;
        const float32_t height = 3.0f;
        const float32_t depth  = 4.0f;
        struct Pose3f   pose;
        pose3f_init(&pose);
        {
            rot3f_from_rpy(&pose.rotation, -0.1f, 0.2f, -0.3f);
            point3f_init_from_scalars(&pose.translation, 0.4f, -0.5f, 0.6f);
        }

        box3f_init_from_width_height_depth_and_pose3f(&expected, width, height, depth, &pose);
    }

    struct Box3f actual;
    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box3f_init_from_box3f(&actual, &expected));
    TEST_ASSERT_EQUAL_FLOAT(expected.width, actual.width);
    TEST_ASSERT_EQUAL_FLOAT(expected.height, actual.height);
    TEST_ASSERT_EQUAL_FLOAT(expected.depth, actual.depth);
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected.pose, &actual.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_is_valid()
{
    struct Box3f box1;
    {
        const float32_t width  = 2.0f;
        const float32_t height = 3.0f;
        const float32_t depth  = 4.0f;
        struct Pose3f   pose;
        pose3f_init(&pose);
        {
            rot3f_from_rpy(&pose.rotation, -0.1f, 0.2f, -0.3f);
            point3f_init_from_scalars(&pose.translation, 0.4f, -0.5f, 0.6f);
        }

        box3f_init_from_width_height_depth_and_pose3f(&box1, width, height, depth, &pose);
    }

    struct Box3f box2;
    box3f_init(&box2);

    // call method and check results
    TEST_ASSERT_TRUE(box3f_is_valid(&box1));
    TEST_ASSERT_TRUE(box3f_is_valid(&box2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_is_equal()
{
    struct Box3f box1;
    {
        const float32_t width  = 1.0f;
        const float32_t height = 1.0f;
        const float32_t depth  = 1.0f;
        struct Pose3f   pose;
        pose3f_init(&pose);
        pose3f_set_identity(&pose);
        box3f_init_from_width_height_depth_and_pose3f(&box1, width, height, depth, &pose);
    }

    struct Box3f box2;
    box3f_init(&box2);

    // call method and check results
    TEST_ASSERT_TRUE(box3f_is_equal(&box1, &box2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_contains_point3f()
{
    struct Box3f box;
    {
        const float32_t width  = 2.0f;
        const float32_t height = 3.0f;
        const float32_t depth  = 4.0f;
        struct Pose3f   pose;
        pose3f_init(&pose);
        {
            rot3f_from_yaw(&pose.rotation, M_PI / 4.0f);
            point3f_init_from_scalars(&pose.translation, 0.0f, 0.0f, 0.0f);
        }

        box3f_init_from_width_height_depth_and_pose3f(&box, width, height, depth, &pose);
    }

    struct Point3f point1;
    point3f_init_from_scalars(&point1, -1.0f, -1.0f, -1.0f);
    struct Point3f point2;
    point3f_init_from_scalars(&point2, 0.0f, 1.0f, 3.0f);

    // call method and check results
    TEST_ASSERT_FALSE(box3f_contains_point3f(&box, &point1));
    TEST_ASSERT_TRUE(box3f_contains_point3f(&box, &point2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_get_axis_aligned_external_box()
{
    struct Box3f box;
    {
        struct Point3f pt1;
        point3f_init_from_scalars(&pt1, -1.0f, -2.0f, 3.0f);
        struct Point3f pt2;
        point3f_init_from_scalars(&pt2, 1.0f, 2.0f, -3.0f);
        box3f_init_from_two_point3f(&box, &pt1, &pt2);
    }

    struct Point3f expected_pt1;
    point3f_init_from_scalars(&expected_pt1, -1.0f, -2.0f, -3.0f);
    struct Point3f expected_pt2;
    point3f_init_from_scalars(&expected_pt2, 1.0f, 2.0f, 3.0f);

    struct Point3f actual_pt1;
    point3f_init(&actual_pt1);
    struct Point3f actual_pt2;
    point3f_init(&actual_pt2);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box3f_get_axis_aligned_external_box(&box, &actual_pt1, &actual_pt2));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected_pt1, &actual_pt1));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected_pt2, &actual_pt2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_get_volume()
{
    struct Box3f box1;
    {
        const float32_t width  = 2.0f;
        const float32_t height = 3.0f;
        const float32_t depth  = 4.0f;
        struct Pose3f   pose;
        pose3f_init(&pose);
        {
            rot3f_from_rpy(&pose.rotation, -0.1f, 0.2f, -0.3f);
            point3f_init_from_scalars(&pose.translation, 0.4f, -0.5f, 0.6f);
        }

        box3f_init_from_width_height_depth_and_pose3f(&box1, width, height, depth, &pose);
    }

    struct Box3f box2;
    box3f_init(&box2);

    const float32_t expected_volume1 = 24.0f;
    const float32_t expected_volume2 = 1.0f;

    // call method and check results
    TEST_ASSERT_EQUAL_FLOAT(expected_volume1, box3f_get_volume(&box1));
    TEST_ASSERT_EQUAL_FLOAT(expected_volume2, box3f_get_volume(&box2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box3f_get_center()
{
    struct Box3f box1;
    {
        const float32_t width  = 2.0f;
        const float32_t height = 3.0f;
        const float32_t depth  = 4.0f;
        struct Pose3f   pose;
        pose3f_init(&pose);
        {
            rot3f_from_yaw(&pose.rotation, M_PI / 2.0f);
            point3f_init_from_scalars(&pose.translation, 0.4f, -0.5f, 0.6f);
        }

        box3f_init_from_width_height_depth_and_pose3f(&box1, width, height, depth, &pose);
    }

    struct Box3f box2;
    box3f_init(&box2);

    struct Point3f expected_center1;
    point3f_init_from_scalars(&expected_center1, -1.1f, 0.5f, 2.6f);
    struct Point3f expected_center2;
    point3f_init_from_scalars(&expected_center2, 0.5f, 0.5f, 0.5f);

    struct Point3f actual_center1, actual_center2;
    point3f_init(&actual_center1);
    point3f_init(&actual_center2);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box3f_get_center(&box1, &actual_center1));
    TEST_ASSERT_EQUAL(RC_SUCCESS, box3f_get_center(&box2, &actual_center2));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected_center1, &actual_center1));
    TEST_ASSERT_TRUE(point3f_is_equal(&expected_center2, &actual_center2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_box3f_init);
    RUN_TEST(test_box3f_init_from_two_point3f);
    RUN_TEST(test_box3f_init_from_width_height_and_depth);
    RUN_TEST(test_box3f_init_from_width_height_depth_and_pose3f);
    RUN_TEST(test_box3f_init_from_vector3f_and_pose3f);
    RUN_TEST(test_box3f_init_from_box3f);
    RUN_TEST(test_box3f_is_valid);
    RUN_TEST(test_box3f_is_equal);
    RUN_TEST(test_box3f_contains_point3f);
    RUN_TEST(test_box3f_get_axis_aligned_external_box);
    RUN_TEST(test_box3f_get_volume);
    RUN_TEST(test_box3f_get_center);
    return UNITY_END();
}
