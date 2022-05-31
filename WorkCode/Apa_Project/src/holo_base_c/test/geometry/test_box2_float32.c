/*!
 * @file test_box2_float32.c
 * @brief unit test of box2
 * @author duyanwei@holomatic.com
 * @date 2019-08-24
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/geometry/box2_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_init(void)
{
    struct Box2f box;

    struct Pose2f expected_pose;
    pose2f_init(&expected_pose);
    pose2f_set_identity(&expected_pose);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_init(&box));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, box.width);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, box.height);
    TEST_ASSERT_TRUE(pose2f_is_equal(&expected_pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_init_from_two_point2f()
{
    struct Point2f pt1;
    point2f_init_from_scalars(&pt1, -1.0f, -2.0f);
    struct Point2f pt2;
    point2f_init_from_scalars(&pt2, 1.0f, 2.0f);

    struct Pose2f expected_pose;
    pose2f_init(&expected_pose);
    {
        point2f_init_from_scalars(&expected_pose.translation, -1.0f, -2.0f);
    }

    struct Box2f box;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_init_from_two_point2f(&box, &pt1, &pt2));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, box.width);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, box.height);
    TEST_ASSERT_TRUE(pose2f_is_equal(&expected_pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_init_from_width_and_height()
{
    // expected result
    const float32_t width  = 2.0f;
    const float32_t height = 3.0f;
    struct Pose2f   expected_pose;
    pose2f_init(&expected_pose);
    pose2f_set_identity(&expected_pose);

    struct Box2f box;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_init_from_width_and_height(&box, width, height));
    TEST_ASSERT_EQUAL_FLOAT(width, box.width);
    TEST_ASSERT_EQUAL_FLOAT(height, box.height);
    TEST_ASSERT_TRUE(pose2f_is_equal(&expected_pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_init_from_width_height_and_pose2f()
{
    // expected result
    const float32_t width  = 2.0f;
    const float32_t height = 3.0f;
    struct Pose2f   pose;
    pose2f_init(&pose);
    {
        rot2f_init_from_angle(&pose.rotation, -0.1f);
        point2f_init_from_scalars(&pose.translation, 0.4f, -0.5f);
    }

    struct Box2f box;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_init_from_width_height_and_pose2f(&box, width, height, &pose));
    TEST_ASSERT_EQUAL_FLOAT(width, box.width);
    TEST_ASSERT_EQUAL_FLOAT(height, box.height);
    TEST_ASSERT_TRUE(pose2f_is_equal(&pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_init_from_vector2f_and_pose2f()
{
    // expected result
    const float32_t width  = 2.0f;
    const float32_t height = 3.0f;

    struct Vectorf vector;
    float32_t      vector_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vector, 2, vector_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set(&vector, 0u, width);
    vectorf_set(&vector, 1u, height);

    struct Pose2f pose;
    pose2f_init(&pose);
    {
        rot2f_init_from_angle(&pose.rotation, -0.1f);
        point2f_init_from_scalars(&pose.translation, 0.4f, -0.5f);
    }

    struct Box2f box;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_init_from_vector2f_and_pose2f(&box, &vector, &pose));
    TEST_ASSERT_EQUAL_FLOAT(width, box.width);
    TEST_ASSERT_EQUAL_FLOAT(height, box.height);
    TEST_ASSERT_TRUE(pose2f_is_equal(&pose, &box.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_init_from_box2f()
{
    struct Box2f expected;
    {
        const float32_t width  = 2.0f;
        const float32_t height = 3.0f;
        struct Pose2f   pose;
        pose2f_init(&pose);
        {
            rot2f_init_from_angle(&pose.rotation, -0.1f);
            point2f_init_from_scalars(&pose.translation, 0.4f, -0.5f);
        }

        box2f_init_from_width_height_and_pose2f(&expected, width, height, &pose);
    }

    struct Box2f actual;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_init_from_box2f(&actual, &expected));
    TEST_ASSERT_EQUAL_FLOAT(expected.width, actual.width);
    TEST_ASSERT_EQUAL_FLOAT(expected.height, actual.height);
    TEST_ASSERT_TRUE(pose2f_is_equal(&expected.pose, &actual.pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_is_valid()
{
    struct Box2f box1;
    {
        const float32_t width  = 2.0f;
        const float32_t height = 3.0f;
        struct Pose2f   pose;
        pose2f_init(&pose);
        {
            rot2f_init_from_angle(&pose.rotation, -0.1f);
            point2f_init_from_scalars(&pose.translation, 0.4f, -0.5f);
        }

        box2f_init_from_width_height_and_pose2f(&box1, width, height, &pose);
    }

    struct Box2f box2;
    box2f_init(&box2);

    // call method and check results
    TEST_ASSERT_TRUE(box2f_is_valid(&box1));
    TEST_ASSERT_TRUE(box2f_is_valid(&box2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_is_equal()
{
    struct Box2f box1;
    {
        const float32_t width  = 1.0f;
        const float32_t height = 1.0f;
        struct Pose2f   pose;
        pose2f_init(&pose);
        pose2f_set_identity(&pose);
        box2f_init_from_width_height_and_pose2f(&box1, width, height, &pose);
    }

    struct Box2f box2;
    box2f_init(&box2);

    // call method and check results
    TEST_ASSERT_TRUE(box2f_is_equal(&box1, &box2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_contains_point2f()
{
    struct Box2f box;
    {
        const float32_t width  = 2.0f;
        const float32_t height = 3.0f;
        struct Pose2f   pose;
        pose2f_init(&pose);
        {
            rot2f_init_from_angle(&pose.rotation, M_PI / 2.0f);
            point2f_init_from_scalars(&pose.translation, 0.0f, 0.0f);
        }

        box2f_init_from_width_height_and_pose2f(&box, width, height, &pose);
    }

    struct Point2f point1;
    point2f_init_from_scalars(&point1, -1.0f, -1.0f);

    struct Point2f point2;
    point2f_init_from_scalars(&point2, -1.0f, 1.0f);

    // call method and check results
    TEST_ASSERT_FALSE(box2f_contains_point2f(&box, &point1));
    TEST_ASSERT_TRUE(box2f_contains_point2f(&box, &point2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_get_corner_points()
{
    struct Box2f box;
    {
        struct Point2f pt1;
        point2f_init_from_scalars(&pt1, -1.0f, -2.0f);

        struct Point2f pt2;
        point2f_init_from_scalars(&pt2, 1.0f, 2.0f);

        box2f_init_from_two_point2f(&box, &pt1, &pt2);
    }

    struct Point2f expected_bl;
    point2f_init_from_scalars(&expected_bl, -1.0f, -2.0f);

    struct Point2f expected_br;
    point2f_init_from_scalars(&expected_br, 1.0f, -2.0f);

    struct Point2f expected_tr;
    point2f_init_from_scalars(&expected_tr, 1.0f, 2.0f);

    struct Point2f expected_tl;
    point2f_init_from_scalars(&expected_tl, -1.0f, 2.0f);

    struct Point2f actual_bl;
    point2f_init(&actual_bl);

    struct Point2f actual_br;
    point2f_init(&actual_br);

    struct Point2f actual_tr;
    point2f_init(&actual_tr);

    struct Point2f actual_tl;
    point2f_init(&actual_tl);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_get_corner_points(&box, &actual_bl, &actual_br, &actual_tr, &actual_tl));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_bl, &actual_bl));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_br, &actual_br));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_tr, &actual_tr));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_tl, &actual_tl));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_get_axis_aligned_external_box()
{
    struct Box2f box;
    {
        struct Point2f pt1;
        point2f_init_from_scalars(&pt1, -1.0f, -2.0f);

        struct Point2f pt2;
        point2f_init_from_scalars(&pt2, 1.0f, 2.0f);

        box2f_init_from_two_point2f(&box, &pt1, &pt2);
    }

    struct Point2f expected_pt1;
    point2f_init_from_scalars(&expected_pt1, -1.0f, -2.0f);

    struct Point2f expected_pt2;
    point2f_init_from_scalars(&expected_pt2, 1.0f, 2.0f);

    struct Point2f actual_pt1;
    point2f_init(&actual_pt1);

    struct Point2f actual_pt2;
    point2f_init(&actual_pt2);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_get_axis_aligned_external_box(&box, &actual_pt1, &actual_pt2));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt1, &actual_pt1));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_pt2, &actual_pt2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_get_area()
{
    struct Box2f box1;
    {
        const float32_t width  = 2.0f;
        const float32_t height = 3.0f;
        struct Pose2f   pose;
        pose2f_init(&pose);
        {
            rot2f_init_from_angle(&pose.rotation, M_PI / 2.0f);
            point2f_init_from_scalars(&pose.translation, 1.0f, 3.0f);
        }

        box2f_init_from_width_height_and_pose2f(&box1, width, height, &pose);
    }

    struct Box2f box2;
    box2f_init(&box2);

    const float32_t expected_area1 = 6.0f;
    const float32_t expected_area2 = 1.0f;

    // call method and check results
    TEST_ASSERT_EQUAL_FLOAT(expected_area1, box2f_get_area(&box1));
    TEST_ASSERT_EQUAL_FLOAT(expected_area2, box2f_get_area(&box2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_get_center()
{
    struct Box2f box1;
    {
        const float32_t width  = 2.0;
        const float32_t height = 3.0;
        struct Pose2f   pose;
        pose2f_init(&pose);
        {
            rot2f_init_from_angle(&pose.rotation, M_PI / 2.0f);
            point2f_init_from_scalars(&pose.translation, 0.4f, -0.5f);
        }

        box2f_init_from_width_height_and_pose2f(&box1, width, height, &pose);
    }

    struct Box2f box2;
    box2f_init(&box2);

    struct Point2f expected_center1;
    point2f_init_from_scalars(&expected_center1, -1.1f, 0.5f);

    struct Point2f expected_center2;
    point2f_init_from_scalars(&expected_center2, 0.5f, 0.5f);

    struct Point2f actual_center1, actual_center2;
    point2f_init(&actual_center1);
    point2f_init(&actual_center2);

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_get_center(&box1, &actual_center1));
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_get_center(&box2, &actual_center2));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_center1, &actual_center1));
    TEST_ASSERT_TRUE(point2f_is_equal(&expected_center2, &actual_center2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_box2f_compute_intersection_over_union()
{
    struct Box2f box1;
    {
        struct Point2f pt1, pt2;
        point2f_init_from_scalars(&pt1, 0.0f, 0.0f);
        point2f_init_from_scalars(&pt2, 2.0f, 2.0f);
        box2f_init_from_two_point2f(&box1, &pt1, &pt2);
    }

    struct Box2f box2;
    {
        struct Point2f pt1, pt2;
        point2f_init_from_scalars(&pt1, 1.0f, 1.0f);
        point2f_init_from_scalars(&pt2, 4.0f, 4.0f);
        box2f_init_from_two_point2f(&box2, &pt1, &pt2);
    }

    struct Box2f box3;
    {
        struct Point2f pt1, pt2;
        point2f_init_from_scalars(&pt1, 0.0f, 0.0f);
        point2f_init_from_scalars(&pt2, -1.0f, -1.0f);
        box2f_init_from_two_point2f(&box3, &pt1, &pt2);
    }

    // call method and check results
    const float32_t expected_iou_1 = 1.0f / 12.0f;
    const float32_t expected_iou_2 = 0.0f;

    float32_t actual_iou_1, actual_iou_2;

    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_compute_intersection_over_union(&box1, &box2, &actual_iou_1));
    TEST_ASSERT_EQUAL(RC_SUCCESS, box2f_compute_intersection_over_union(&box1, &box3, &actual_iou_2));
    TEST_ASSERT_EQUAL_FLOAT(expected_iou_1, actual_iou_1);
    TEST_ASSERT_EQUAL_FLOAT(expected_iou_2, actual_iou_2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_box2f_init);
    RUN_TEST(test_box2f_init_from_two_point2f);
    RUN_TEST(test_box2f_init_from_width_and_height);
    RUN_TEST(test_box2f_init_from_width_height_and_pose2f);
    RUN_TEST(test_box2f_init_from_vector2f_and_pose2f);
    RUN_TEST(test_box2f_init_from_box2f);
    RUN_TEST(test_box2f_is_valid);
    RUN_TEST(test_box2f_is_equal);
    RUN_TEST(test_box2f_contains_point2f);
    RUN_TEST(test_box2f_get_corner_points);
    RUN_TEST(test_box2f_get_axis_aligned_external_box);
    RUN_TEST(test_box2f_get_area);
    RUN_TEST(test_box2f_get_center);
    RUN_TEST(test_box2f_compute_intersection_over_union);
    return UNITY_END();
}
