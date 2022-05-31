/*!
 * @file test_quaternion_float32.c
 * @brief unit test of quaternion
 * @author duyanwei@holomatic.com
 * @date 2019-08-24
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/geometry/quaternion_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_init_from_scalars(void)
{
    struct Quaternionf quaternion;

    const float32_t w = 0.0f;
    const float32_t x = 0.0f;
    const float32_t y = 1.0f;
    const float32_t z = 0.0f;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_init_from_scalars(&quaternion, w, x, y, z));
    TEST_ASSERT_EQUAL_FLOAT(w, quaternion.w);
    TEST_ASSERT_EQUAL_FLOAT(x, quaternion.x);
    TEST_ASSERT_EQUAL_FLOAT(y, quaternion.y);
    TEST_ASSERT_EQUAL_FLOAT(z, quaternion.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_init(void)
{
    struct Quaternionf quaternion;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_init(&quaternion));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, quaternion.w);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, quaternion.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, quaternion.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, quaternion.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_init_from_quaternionf(void)
{
    struct Quaternionf other;

    const float32_t w = 0.0f;
    const float32_t x = 0.0f;
    const float32_t y = 1.0f;
    const float32_t z = 0.0f;
    quaternionf_init_from_scalars(&other, w, x, y, z);

    struct Quaternionf quaternion;

    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_init_from_quaternionf(&quaternion, &other));
    TEST_ASSERT_EQUAL_FLOAT(w, quaternion.w);
    TEST_ASSERT_EQUAL_FLOAT(x, quaternion.x);
    TEST_ASSERT_EQUAL_FLOAT(y, quaternion.y);
    TEST_ASSERT_EQUAL_FLOAT(z, quaternion.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_is_valid(void)
{
    struct Quaternionf quaternion1;
    quaternionf_init_from_scalars(&quaternion1, 0.0f, -1.0f, 0.0f, 0.0f);

    struct Quaternionf quaternion2;
    quaternionf_init_from_scalars(&quaternion2, 0.0f, -0.5f, 0.0f, 0.5f);

    TEST_ASSERT_TRUE(quaternionf_is_valid(&quaternion1));
    TEST_ASSERT_TRUE(quaternionf_is_valid(&quaternion2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_is_equal(void)
{
    struct Quaternionf quaternion1;
    quaternionf_init(&quaternion1);

    struct Quaternionf quaternion2;
    quaternionf_init_from_scalars(&quaternion2, 1.0f, 0.0f, 0.0f, 0.0f);

    struct Quaternionf quaternion3;
    quaternionf_init_from_scalars(&quaternion3, 0.0f, -0.5f, 0.0f, 0.5f);

    TEST_ASSERT_TRUE(quaternionf_is_equal(&quaternion1, &quaternion2));
    TEST_ASSERT_FALSE(quaternionf_is_equal(&quaternion1, &quaternion3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_to_matrix33f(void)
{
    const float32_t    value = sqrtf(2.0) / 2.0f;
    struct Quaternionf quaternion;
    quaternionf_init_from_scalars(&quaternion, value, value, 0.0f, 0.0f);

    struct Matrixf expected;
    float32_t      expected_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&expected, 3, 3, expected_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    {
        matrixf_set_identity(&expected);
        matrixf_set(&expected, 1u, 1u, 0.0f);
        matrixf_set(&expected, 1u, 2u, -1.0f);
        matrixf_set(&expected, 2u, 1u, 1.0f);
        matrixf_set(&expected, 2u, 2u, 0.0f);
    }

    // call method and check results
    struct Matrixf actual;
    float32_t      actual_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&actual, 3, 3, actual_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_to_matrix33f(&quaternion, &actual));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_dot(void)
{
    struct Quaternionf quaternion1;
    quaternionf_init_from_scalars(&quaternion1, 1.0f, 0.0f, 0.0f, 0.0f);

    struct Quaternionf quaternion2;
    quaternionf_init_from_scalars(&quaternion2, 0.0f, 1.0f, 0.0f, 0.0f);

    const float32_t    value = sqrtf(2.0) / 2.0f;
    struct Quaternionf quaternion3;
    quaternionf_init_from_scalars(&quaternion3, value, 0.0f, value, 0.0f);

    // call method and check results
    float32_t actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_dot(&quaternion1, &quaternion1, &actual));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_dot(&quaternion1, &quaternion2, &actual));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_dot(&quaternion1, &quaternion3, &actual));
    TEST_ASSERT_EQUAL_FLOAT(value, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_slerp(void)
{
    struct Quaternionf quaternion1;
    quaternionf_init_from_scalars(&quaternion1, 1.0f, 0.0f, 0.0f, 0.0f);

    struct Quaternionf quaternion2;
    quaternionf_init_from_scalars(&quaternion2, 0.0f, 1.0f, 0.0f, 0.0f);

    const float32_t    value = sqrtf(2.0) / 2.0f;
    struct Quaternionf expected;
    quaternionf_init_from_scalars(&expected, value, value, 0.0f, 0.0f);

    // call method and check results
    struct Quaternionf actual;
    quaternionf_init(&actual);
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_slerp(&quaternion1, &quaternion2, 0.5f, &actual));
    TEST_ASSERT_TRUE(quaternionf_is_equal(&expected, &actual));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_multiply_float32(void)
{
    struct Quaternionf quaternion;
    const float32_t    w = 0.1f;
    const float32_t    x = 0.2f;
    const float32_t    y = 0.3f;
    const float32_t    z = 0.4f;
    quaternionf_init_from_scalars(&quaternion, w, x, y, z);

    const float32_t scale = 0.2;
    float32_t       expected_w;
    float32_t       expected_x;
    float32_t       expected_y;
    float32_t       expected_z;
    {
        expected_w = w * scale;
        expected_x = x * scale;
        expected_y = y * scale;
        expected_z = z * scale;
    }

    // check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_multiply_float32(&quaternion, scale, &quaternion));
    TEST_ASSERT_EQUAL_FLOAT(expected_w, quaternion.w);
    TEST_ASSERT_EQUAL_FLOAT(expected_x, quaternion.x);
    TEST_ASSERT_EQUAL_FLOAT(expected_y, quaternion.y);
    TEST_ASSERT_EQUAL_FLOAT(expected_z, quaternion.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_get_norm(void)
{
    struct Quaternionf quaternion1;
    quaternionf_init(&quaternion1);
    const float32_t    expected_norm1 = 1.0f;
    struct Quaternionf quaternion2;
    float32_t          expected_norm2;
    {
        const float32_t w = 0.1f;
        const float32_t x = 0.2f;
        const float32_t y = 0.3f;
        const float32_t z = 0.4f;
        quaternionf_init_from_scalars(&quaternion2, w, x, y, z);
        expected_norm2 = sqrtf(w * w + x * x + y * y + z * z);
    }

    // check results
    TEST_ASSERT_EQUAL_FLOAT(expected_norm1, quaternionf_get_norm(&quaternion1));
    TEST_ASSERT_EQUAL_FLOAT(expected_norm2, quaternionf_get_norm(&quaternion2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_normalize(void)
{
    struct Quaternionf quaternion;
    const float32_t    w = 0.1f;
    const float32_t    x = 0.2f;
    const float32_t    y = 0.3f;
    const float32_t    z = 0.4f;
    quaternionf_init_from_scalars(&quaternion, w, x, y, z);

    float32_t expected_w;
    float32_t expected_x;
    float32_t expected_y;
    float32_t expected_z;
    {
        const float32_t norm = sqrtf(w * w + x * x + y * y + z * z);
        expected_w           = w / norm;
        expected_x           = x / norm;
        expected_y           = y / norm;
        expected_z           = z / norm;
    }

    // check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_normalize(&quaternion));
    TEST_ASSERT_EQUAL_FLOAT(expected_w, quaternion.w);
    TEST_ASSERT_EQUAL_FLOAT(expected_x, quaternion.x);
    TEST_ASSERT_EQUAL_FLOAT(expected_y, quaternion.y);
    TEST_ASSERT_EQUAL_FLOAT(expected_z, quaternion.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_is_normalized(void)
{
    struct Quaternionf quaternion1;
    quaternionf_init(&quaternion1);
    struct Quaternionf quaternion2;
    quaternionf_init_from_scalars(&quaternion2, 0.1f, 0.2f, 0.3f, 0.4f);

    // call method and check results
    TEST_ASSERT_TRUE(quaternionf_is_normalized(&quaternion1));
    TEST_ASSERT_FALSE(quaternionf_is_normalized(&quaternion2));

    quaternionf_normalize(&quaternion2);
    TEST_ASSERT_TRUE(quaternionf_is_normalized(&quaternion2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_quaternionf_set_identity(void)
{
    struct Quaternionf quaternion;
    quaternionf_init_from_scalars(&quaternion, 0.0f, 1.0f, 0.0f, 0.0f);

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, quaternionf_set_identity(&quaternion));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, quaternion.w);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, quaternion.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, quaternion.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, quaternion.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_quaternionf_init_from_scalars);
    RUN_TEST(test_quaternionf_init);
    RUN_TEST(test_quaternionf_init_from_quaternionf);
    RUN_TEST(test_quaternionf_is_valid);
    RUN_TEST(test_quaternionf_is_equal);
    RUN_TEST(test_quaternionf_to_matrix33f);
    RUN_TEST(test_quaternionf_dot);
    RUN_TEST(test_quaternionf_slerp);
    RUN_TEST(test_quaternionf_multiply_float32);
    RUN_TEST(test_quaternionf_get_norm);
    RUN_TEST(test_quaternionf_normalize);
    RUN_TEST(test_quaternionf_is_normalized);
    RUN_TEST(test_quaternionf_set_identity);
    return UNITY_END();
}
