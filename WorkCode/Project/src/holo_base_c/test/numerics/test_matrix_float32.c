/*!
 * @file test_matrix_float32.c
 * @brief unit test of matrix
 * @author duyanwei@holomatic.com
 * @date 2019-08-07
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/numerics/matrix.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_init(void)
{
    struct Matrixf mat;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(2, 3)] = {0.0f, 1.0f, 2.0f, 0.0f, 3.0f, 4.0f};
    retcode_t rc;

    rc = matrixf_init(&mat, 2, 3, buffer, MATRIXF_MIN_BUF_SIZE(2, 3));
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL(2u, matrixf_get_rows(&mat));
    TEST_ASSERT_EQUAL(3u, matrixf_get_cols(&mat));
    TEST_ASSERT_EQUAL(6u, matrixf_get_size(&mat));
    for (uint8_t i = 0u; i < 2u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrix22f_init(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&mat, 2, 2, mat_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    // check results
    TEST_ASSERT_EQUAL(2u, mat.rows);
    TEST_ASSERT_EQUAL(2u, mat.cols);
    TEST_ASSERT_EQUAL(4u, mat.size);

    const float32_t expected = 0.0f;
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrix33f_init(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    // check results
    TEST_ASSERT_EQUAL(3u, mat.rows);
    TEST_ASSERT_EQUAL(3u, mat.cols);
    TEST_ASSERT_EQUAL(9u, mat.size);

    const float32_t expected = 0.0f;
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrix44f_init(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat, 4, 4, mat_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // check results
    TEST_ASSERT_EQUAL(4u, mat.rows);
    TEST_ASSERT_EQUAL(4u, mat.cols);
    TEST_ASSERT_EQUAL(16u, mat.size);

    const float32_t expected = 0.0f;
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrix66f_init(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    matrixf_init(&mat, 6, 6, mat_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));

    // check results
    TEST_ASSERT_EQUAL(6u, mat.rows);
    TEST_ASSERT_EQUAL(6u, mat.cols);
    TEST_ASSERT_EQUAL(36u, mat.size);

    const float32_t expected = 0.0f;
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrix_resize(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    matrixf_init(&mat, 6, 6, mat_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));

    matrixf_resize(&mat, 3, 3);

    // check results
    TEST_ASSERT_EQUAL(3u, mat.rows);
    TEST_ASSERT_EQUAL(3u, mat.cols);
    TEST_ASSERT_EQUAL(9u, mat.size);
    TEST_ASSERT_EQUAL(MATRIXF_MIN_BUF_SIZE(6u, 6u), mat.capacity);

    const float32_t expected = 0.0f;
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }

    retcode_t rc = matrixf_resize(&mat, 8, 9);
    TEST_ASSERT_EQUAL_UINT(1, 0 != rc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_is_valid(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(2, 6)];
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];

    matrixf_init(&mat1, 2, 6, mat1_buf, MATRIXF_MIN_BUF_SIZE(2, 6));
    TEST_ASSERT_TRUE(matrixf_is_valid(&mat1));

    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2, 2));
    TEST_ASSERT_TRUE(matrixf_is_valid(&mat2));

    mat2.rows = 0;
    TEST_ASSERT_FALSE(matrixf_is_valid(&mat2));

    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2, 2));
    mat2.cols = 0;
    TEST_ASSERT_FALSE(matrixf_is_valid(&mat2));

    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2, 2));
    mat2.size = 0;
    TEST_ASSERT_FALSE(matrixf_is_valid(&mat2));

    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2, 2));
    mat2.size = 5;
    TEST_ASSERT_FALSE(matrixf_is_valid(&mat2));

    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2, 2));
    mat2.pitchx = 0;
    TEST_ASSERT_FALSE(matrixf_is_valid(&mat2));

    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2, 2));
    mat2.pitchy = 0;
    TEST_ASSERT_FALSE(matrixf_is_valid(&mat2));

    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2, 2));
    mat2.base = NULL;
    TEST_ASSERT_FALSE(matrixf_is_valid(&mat2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_from_array(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(6u, 5u)];
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(5u, 6u)];

    matrixf_init(&mat1, 6, 5, mat1_buf, MATRIXF_MIN_BUF_SIZE(6u, 5u));
    matrixf_init(&mat2, 5, 6, mat2_buf, MATRIXF_MIN_BUF_SIZE(5u, 6u));

    // init mat from array
    {
        float32_t sample[30];
        memset(sample, 0, 30 * sizeof(float32_t));
        for (uint8_t i = 0u; i < mat1.rows; i++)
        {
            for (uint8_t j = 0u; j < mat1.cols; j++)
            {
                sample[i * mat1.cols + j] = i * mat1.cols + j;
            }
        }

        matrixf_set_from_array(&mat1, sample, 30);
        matrixf_set_from_array(&mat2, sample, 30);
    }

    // check results
    for (uint8_t i = 0u; i < mat1.rows; i++)
    {
        for (uint8_t j = 0u; j < mat1.cols; j++)
        {
            const float32_t expected = i * mat1.cols + j;
            float32_t       actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat1, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }

    // check results
    for (uint8_t i = 0u; i < mat2.rows; i++)
    {
        for (uint8_t j = 0u; j < mat2.cols; j++)
        {
            const float32_t expected = i * mat2.cols + j;
            float32_t       actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat2, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_from_array_unsafe(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(6u, 5u)];
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(5u, 6u)];

    matrixf_init(&mat1, 6, 5, mat1_buf, MATRIXF_MIN_BUF_SIZE(6u, 5u));
    matrixf_init(&mat2, 5, 6, mat2_buf, MATRIXF_MIN_BUF_SIZE(5u, 6u));

    // init mat from array
    {
        float32_t sample[30];
        memset(sample, 0, 30 * sizeof(float32_t));
        for (uint8_t i = 0u; i < mat1.rows; i++)
        {
            for (uint8_t j = 0u; j < mat1.cols; j++)
            {
                sample[i * mat1.cols + j] = i * mat1.cols + j;
            }
        }

        matrixf_set_from_array_unsafe(&mat1, sample, 30);
        matrixf_set_from_array_unsafe(&mat2, sample, 30);
    }

    // check results
    for (uint8_t i = 0u; i < mat1.rows; i++)
    {
        for (uint8_t j = 0u; j < mat1.cols; j++)
        {
            const float32_t expected = i * mat1.cols + j;
            float32_t       actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat1, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }

    // check results
    for (uint8_t i = 0u; i < mat2.rows; i++)
    {
        for (uint8_t j = 0u; j < mat2.cols; j++)
        {
            const float32_t expected = i * mat2.cols + j;
            float32_t       actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat2, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_from_matrixf(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];

    matrixf_init(&mat1, 3, 3, mat1_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    matrixf_init(&mat2, 3, 3, mat2_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    matrixf_set_identity(&mat1);

    // check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_from_matrixf(&mat2, &mat1));
    for (uint8_t i = 0u; i < mat2.rows; i++)
    {
        for (uint8_t j = 0u; j < mat2.cols; j++)
        {
            const float32_t expected = (i == j) ? 1.0f : 0.0f;
            float32_t       actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat2, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_from_matrixf_unsafe(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];

    matrixf_init(&mat1, 3, 3, mat1_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    matrixf_init(&mat2, 3, 3, mat2_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    matrixf_set_identity(&mat1);

    // check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_from_matrixf_unsafe(&mat2, &mat1));
    for (uint8_t i = 0u; i < mat2.rows; i++)
    {
        for (uint8_t j = 0u; j < mat2.cols; j++)
        {
            const float32_t expected = (i == j) ? 1.0f : 0.0f;
            float32_t       actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat2, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_is_equal(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat1, 4, 4, mat1_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat2, 4, 4, mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    struct Matrixf mat3;
    float32_t      mat3_buf[MATRIXF_MIN_BUF_SIZE(5u, 4u)];
    matrixf_init(&mat3, 5, 4, mat3_buf, MATRIXF_MIN_BUF_SIZE(5u, 4u));

    struct Matrixf mat4;
    float32_t      mat4_buf[MATRIXF_MIN_BUF_SIZE(4u, 5u)];
    matrixf_init(&mat4, 4, 5, mat4_buf, MATRIXF_MIN_BUF_SIZE(4u, 5u));

    matrixf_set_constant(&mat1, -1.0f);
    matrixf_set_constant(&mat2, -1.0f);
    matrixf_set_constant(&mat3, -1.0f);
    matrixf_set_constant(&mat4, -1.0f);

    // check results
    TEST_ASSERT_TRUE(matrixf_is_equal(&mat1, &mat2));
    TEST_ASSERT_FALSE(matrixf_is_equal(&mat1, &mat3));
    TEST_ASSERT_FALSE(matrixf_is_equal(&mat1, &mat4));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_get(void)
{
    const float32_t value = 10.0f;
    struct Matrixf  mat;
    float32_t       mat_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat, 4, 4, mat_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    matrixf_set_constant(&mat, value);

    // call set and check
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set(&mat, i, i, i));
    }

    // call get and check results
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            const float32_t expected = (i == j) ? (float32_t)i : (float32_t)value;
            float32_t       actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_get_unsafe()
{
    const float32_t value = 10.0f;
    struct Matrixf  mat;
    float32_t       mat_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat, 4, 4, mat_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    matrixf_set_constant(&mat, value);

    // call set and check
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_unsafe(&mat, i, i, i));
    }

    // call get and check results
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            const float32_t expected = (i == j) ? i : value;
            float32_t       actual   = matrixf_get_unsafe(&mat, i, j);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_add(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat1, 3, 3, mat1_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat2, 3, 3, mat2_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    matrixf_set_ones(&mat1);
    matrixf_set_ones(&mat2);

    // call add and check results
    struct Matrixf mat3;
    float32_t      mat3_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat3, 3, 3, mat3_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_add(&mat1, &mat2, &mat3));

    const float32_t expected = 2.0f;
    for (uint8_t i = 0u; i < mat3.rows; i++)
    {
        for (uint8_t j = 0u; j < mat3.cols; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat3, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_sub(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat1, 3, 3, mat1_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat2, 3, 3, mat2_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    matrixf_set_constant(&mat1, 5.0f);
    matrixf_set_constant(&mat2, 10.0f);

    // call add and check results
    struct Matrixf mat3;
    float32_t      mat3_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat3, 3, 3, mat3_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_sub(&mat1, &mat2, &mat3));

    const float32_t expected = -5.0f;
    for (uint8_t i = 0u; i < mat3.rows; i++)
    {
        for (uint8_t j = 0u; j < mat3.cols; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat3, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_negate(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(5, 5)];
    matrixf_init(&mat, 5, 5, mat_buf, MATRIXF_MIN_BUF_SIZE(5, 5));
    matrixf_set_constant(&mat, 5.0f);

    // call scale and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_negate(&mat));

    const float32_t expected = -5.0f;
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_multiply_float32(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat1, 3, 3, mat1_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat2, 3, 3, mat2_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    matrixf_set_ones(&mat1);
    matrixf_set_ones(&mat2);

    // call and check results
    const float32_t scalar = 5.0f;
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_multiply_float32(&mat1, scalar, &mat2));
    for (uint8_t i = 0u; i < mat2.rows; i++)
    {
        for (uint8_t j = 0u; j < mat2.cols; j++)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&mat2, i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(scalar, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_multiply(void)
{
    struct Matrixf lhs;
    float32_t      lhs_buf[MATRIXF_MIN_BUF_SIZE(2, 3)];
    matrixf_init(&lhs, 2, 3, lhs_buf, MATRIXF_MIN_BUF_SIZE(2, 3));
    {
        for (uint8_t i = 0u; i < lhs.rows; i++)
        {
            for (uint8_t j = 0u; j < lhs.cols; j++)
            {
                const float32_t value = i * lhs.cols + j;
                matrixf_set(&lhs, i, j, value);
            }
        }
    }

    struct Matrixf rhs;
    float32_t      rhs_buf[MATRIXF_MIN_BUF_SIZE(3, 2)];
    matrixf_init(&rhs, 3, 2, rhs_buf, MATRIXF_MIN_BUF_SIZE(3, 2));
    {
        for (uint8_t i = 0u; i < rhs.rows; i++)
        {
            for (uint8_t j = 0u; j < rhs.cols; j++)
            {
                const float32_t value = i * rhs.cols + j;
                matrixf_set(&rhs, i, j, -value);
            }
        }
    }

    // expected
    struct Matrixf expected;
    float32_t      expected_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&expected, 2, 2, expected_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    {
        matrixf_set(&expected, 0u, 0u, -10.0f);
        matrixf_set(&expected, 0u, 1u, -13.0f);
        matrixf_set(&expected, 1u, 0u, -28.0f);
        matrixf_set(&expected, 1u, 1u, -40.0f);
    }

    // call multiply and check results
    struct Matrixf actual;
    float32_t      actual_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&actual, 2, 2, actual_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_multiply(&lhs, &rhs, &actual));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected, &actual));

    for (uint8_t i = 0u; i < lhs.rows; i++)
    {
        for (uint8_t j = 0u; j < lhs.cols; j++)
        {
            const float32_t expected_value = i * lhs.cols + j;
            float32_t       actual_value;
            matrixf_get(&lhs, i, j, &actual_value);
            TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
        }
    }

    for (uint8_t i = 0u; i < rhs.rows; i++)
    {
        for (uint8_t j = 0u; j < rhs.cols; j++)
        {
            const float32_t expected_value = -(i * rhs.cols + j);
            float32_t       actual_value;
            matrixf_get(&rhs, i, j, &actual_value);
            TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_multiply2(void)
{
    struct Matrixf lhs;
    float32_t      lhs_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&lhs, 2, 2, lhs_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    {
        for (uint8_t i = 0u; i < lhs.rows; i++)
        {
            for (uint8_t j = 0u; j < lhs.cols; j++)
            {
                const float32_t value = i * lhs.cols + j;
                matrixf_set(&lhs, i, j, value);
            }
        }
    }

    struct Matrixf rhs;
    float32_t      rhs_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&rhs, 2, 2, rhs_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    {
        for (uint8_t i = 0u; i < rhs.rows; i++)
        {
            for (uint8_t j = 0u; j < rhs.cols; j++)
            {
                const float32_t value = i * rhs.cols + j;
                matrixf_set(&rhs, i, j, -value);
            }
        }
    }

    // expected result
    struct Matrixf expected;
    float32_t      expected_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&expected, 2, 2, expected_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    {
        matrixf_set(&expected, 0u, 0u, -2.0f);
        matrixf_set(&expected, 0u, 1u, -3.0f);
        matrixf_set(&expected, 1u, 0u, -6.0f);
        matrixf_set(&expected, 1u, 1u, -11.0f);
    }

    // call multiply and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_multiply(&lhs, &rhs, &lhs));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected, &lhs));

    for (uint8_t i = 0u; i < rhs.rows; i++)
    {
        for (uint8_t j = 0u; j < rhs.cols; j++)
        {
            const float32_t expected_value = -(i * rhs.cols + j);
            float32_t       actual_value;
            matrixf_get(&rhs, i, j, &actual_value);
            TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_multiply3(void)
{
    struct Matrixf lhs;
    float32_t      lhs_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&lhs, 2, 2, lhs_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    {
        for (uint8_t i = 0u; i < lhs.rows; i++)
        {
            for (uint8_t j = 0u; j < lhs.cols; j++)
            {
                const float32_t value = i * lhs.cols + j;
                matrixf_set(&lhs, i, j, value);
            }
        }
    }

    struct Matrixf rhs;
    float32_t      rhs_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&rhs, 2, 2, rhs_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    {
        for (uint8_t i = 0u; i < rhs.rows; i++)
        {
            for (uint8_t j = 0u; j < rhs.cols; j++)
            {
                const float32_t value = i * rhs.cols + j;
                matrixf_set(&rhs, i, j, -value);
            }
        }
    }

    // expected result
    struct Matrixf expected;
    float32_t      expected_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&expected, 2, 2, expected_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    {
        matrixf_set(&expected, 0u, 0u, -2.0f);
        matrixf_set(&expected, 0u, 1u, -3.0f);
        matrixf_set(&expected, 1u, 0u, -6.0f);
        matrixf_set(&expected, 1u, 1u, -11.0f);
    }

    // call multiply and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_multiply(&lhs, &rhs, &rhs));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected, &rhs));

    for (uint8_t i = 0u; i < lhs.rows; i++)
    {
        for (uint8_t j = 0u; j < lhs.cols; j++)
        {
            const float32_t expected_value = i * lhs.cols + j;
            float32_t       actual_value;
            matrixf_get(&lhs, i, j, &actual_value);
            TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_multiply4(void)
{
    struct Matrixf lhs;
    float32_t      lhs_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&lhs, 2, 2, lhs_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    {
        for (uint8_t i = 0u; i < lhs.rows; i++)
        {
            for (uint8_t j = 0u; j < lhs.cols; j++)
            {
                const float32_t value = i * lhs.cols + j;
                matrixf_set(&lhs, i, j, value);
            }
        }
    }

    // expected result
    struct Matrixf expected;
    float32_t      expected_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&expected, 2, 2, expected_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    {
        matrixf_set(&expected, 0u, 0u, 2.0f);
        matrixf_set(&expected, 0u, 1u, 3.0f);
        matrixf_set(&expected, 1u, 0u, 6.0f);
        matrixf_set(&expected, 1u, 1u, 11.0f);
    }

    // call multiply and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_multiply(&lhs, &lhs, &lhs));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected, &lhs));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_transpose(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3, 5)];
    matrixf_init(&mat1, 3, 5, mat1_buf, MATRIXF_MIN_BUF_SIZE(3, 5));
    {
        float32_t array[15] = {0.0f};
        memset(array, 0, 15 * sizeof(float32_t));
        for (uint8_t i = 0u; i < 3u; i++)
        {
            for (uint8_t j = 0u; j < 5u; j++)
            {
                array[i * mat1.cols + j] = (float)(i * mat1.cols + j);
            }
        }
        matrixf_set_from_array(&mat1, array, 15);
    }

    // call transpose and check results
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(5, 3)];
    matrixf_init(&mat2, 5, 3, mat2_buf, MATRIXF_MIN_BUF_SIZE(5, 3));
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_transpose(&mat1, &mat2));

    for (uint8_t i = 0u; i < mat1.rows; i++)
    {
        for (uint8_t j = 0u; j < mat1.cols; j++)
        {
            float32_t expected;
            float32_t actual;
            matrixf_get(&mat1, i, j, &expected);
            matrixf_get(&mat2, j, i, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_norm_and_norm_sqr(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat, 4, 4, mat_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    matrixf_set_constant(&mat, -1.0f);

    // call scale and check results
    const float32_t expected_norm     = 4.0f;
    const float32_t expected_norm_sqr = 16.0f;

    TEST_ASSERT_EQUAL_FLOAT(expected_norm, matrixf_get_norm(&mat));
    TEST_ASSERT_EQUAL_FLOAT(expected_norm_sqr, matrixf_get_norm_sqr(&mat));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_inverse(void)
{
    // create two matrices
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat1, 4, 4, mat1_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    matrixf_set_identity(&mat1);
    for (uint8_t i = 0u; i < 2u; i++)
    {
        for (uint8_t j = 0u; j < 2u; j++)
        {
            const float32_t value = i * 2u + j + 1u;
            matrixf_set(&mat2, i, j, value);
        }
    }

    // compute two inverse matrices
    struct Matrixf inv_mat1;
    float32_t      inv_mat1_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&inv_mat1, 4, 4, inv_mat1_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    struct Matrixf inv_mat2;
    float32_t      inv_mat2_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&inv_mat2, 2, 2, inv_mat2_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    // call inverse and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_inverse(&mat1, &inv_mat1));
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_inverse(&mat2, &inv_mat2));

    // check inverse of mat1
    for (uint8_t i = 0u; i < mat1.rows; i++)
    {
        for (uint8_t j = 0u; j < mat1.cols; j++)
        {
            const float32_t expected = (i == j) ? 1.0f : 0.0f;
            float32_t       actual;
            matrixf_get(&inv_mat1, i, j, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }

    // make sure mat1 is not changed
    for (uint8_t i = 0u; i < mat1.rows; i++)
    {
        for (uint8_t j = 0u; j < mat1.cols; j++)
        {
            const float32_t expected = (i == j) ? 1.0f : 0.0f;
            float32_t       actual;
            matrixf_get(&mat1, i, j, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }

    // check inverse of mat2
    float32_t actual = 0.0f;
    matrixf_get(&inv_mat2, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, actual);
    matrixf_get(&inv_mat2, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1u, actual);
    matrixf_get(&inv_mat2, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.5f, actual);
    matrixf_get(&inv_mat2, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, actual);

    // make sure mat2 is not changed
    for (uint8_t i = 0u; i < mat2.rows; i++)
    {
        for (uint8_t j = 0u; j < mat2.cols; j++)
        {
            const float32_t expected = i * 2u + j + 1u;
            float32_t       actual;
            matrixf_get(&mat2, i, j, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_inverse_inplace(void)
{
    // create matrix
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&mat, 2u, 2u, mat_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    matrixf_set_identity(&mat);
    matrixf_set(&mat, 0u, 0u, 0.99f);
    matrixf_set(&mat, 1u, 1u, 0.98f);

    // call method and check results
    matrixf_inverse(&mat, &mat);
    float32_t actual = 0.0f;
    matrixf_get(&mat, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.010101f, actual);
    matrixf_get(&mat, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    matrixf_get(&mat, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    matrixf_get(&mat, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.020408f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_determinant(void)
{
    // create two matrics
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat1, 4, 4, mat1_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    matrixf_set_identity(&mat1);
    for (uint8_t i = 0u; i < 2u; i++)
    {
        for (uint8_t j = 0u; j < 2u; j++)
        {
            const float32_t value = i * 2u + j + 1u;
            matrixf_set(&mat2, i, j, value);
        }
    }

    // call determinant and check results
    float32_t det1, det2;
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_determinant(&mat1, &det1));
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_determinant(&mat2, &det2));
    TEST_ASSERT_EQUAL_FLOAT(1, det1);
    TEST_ASSERT_EQUAL_FLOAT(-2, det2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_dot(void)
{
    // create two matrics
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3u, 1u)];
    matrixf_init(&mat1, 3, 1, mat1_buf, MATRIXF_MIN_BUF_SIZE(3u, 1u));
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(3u, 1u)];
    matrixf_init(&mat2, 3, 1, mat2_buf, MATRIXF_MIN_BUF_SIZE(3u, 1u));
    {
        float32_t array1[3] = {0.0f};
        float32_t array2[3] = {0.0f};
        memset(array1, 0, 3 * sizeof(float32_t));
        memset(array2, 0, 3 * sizeof(float32_t));
        for (uint8_t i = 0u; i < 3u; i++)
        {
            array1[i] = i;
            array2[i] = 2.0f - i;
        }

        matrixf_set_from_array(&mat1, array1, 3);
        matrixf_set_from_array(&mat2, array2, 3);
    }

    // call dot and check results
    const float32_t expected = 1.0f;
    float32_t       actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_dot(&mat1, &mat2, &actual));
    TEST_ASSERT_EQUAL_FLOAT(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_cross(void)
{
    // create two matrics
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3u, 1u)];
    matrixf_init(&mat1, 3, 1, mat1_buf, MATRIXF_MIN_BUF_SIZE(3u, 1u));
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(3u, 1u)];
    matrixf_init(&mat2, 3, 1, mat2_buf, MATRIXF_MIN_BUF_SIZE(3u, 1u));
    {
        float32_t array1[3] = {0.0f};
        float32_t array2[3] = {0.0f};
        memset(array1, 0, 3 * sizeof(float32_t));
        memset(array2, 0, 3 * sizeof(float32_t));
        for (uint8_t i = 0u; i < 3u; i++)
        {
            array1[i] = i;
            array2[i] = 2.0f - i;
        }

        matrixf_set_from_array(&mat1, array1, 3);
        matrixf_set_from_array(&mat2, array2, 3);
    }

    struct Matrixf mat3;
    float32_t      mat3_buf[MATRIXF_MIN_BUF_SIZE(3u, 1u)];
    matrixf_init(&mat3, 3, 1, mat3_buf, MATRIXF_MIN_BUF_SIZE(3u, 1u));

    // call cross and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_cross(&mat1, &mat2, &mat3));
    float32_t actual;
    matrixf_get(&mat3, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, actual);
    matrixf_get(&mat3, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, actual);
    matrixf_get(&mat3, 2u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_trace(void)
{
    // create two matrics
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat1, 4, 4, mat1_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    matrixf_set_identity(&mat1);
    for (uint8_t i = 0u; i < 2u; i++)
    {
        for (uint8_t j = 0u; j < 2u; j++)
        {
            const float32_t value = i * 2u + j + 1u;
            matrixf_set(&mat2, i, j, value);
        }
    }

    // call determinant and check results
    float32_t trace1, trace2;
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_trace(&mat1, &trace1));
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_trace(&mat2, &trace2));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, trace1);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, trace2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_constant(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(5u, 6u)];
    matrixf_init(&mat, 5, 6, mat_buf, MATRIXF_MIN_BUF_SIZE(5u, 6u));

    const float32_t expected = 10.0f;

    // call and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_constant(&mat, expected));

    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            float32_t actual;
            matrixf_get(&mat, i, j, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_zeros(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(5u, 6u)];
    matrixf_init(&mat, 5, 6, mat_buf, MATRIXF_MIN_BUF_SIZE(5u, 6u));

    // call and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_zeros(&mat));

    const float32_t expected = 0.0f;
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            float32_t actual;
            matrixf_get(&mat, i, j, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_ones(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(5u, 6u)];
    matrixf_init(&mat, 5, 6, mat_buf, MATRIXF_MIN_BUF_SIZE(5u, 6u));

    // call and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_ones(&mat));

    const float32_t expected = 1.0f;
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            float32_t actual;
            matrixf_get(&mat, i, j, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_identity(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(5, 5)];
    matrixf_init(&mat, 5, 5, mat_buf, MATRIXF_MIN_BUF_SIZE(5, 5));

    // call and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_identity(&mat));

    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            const float32_t expected = (i == j) ? 1.0f : 0.0f;
            float32_t       actual;
            matrixf_get(&mat, i, j, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_get_block(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_block(&mat, 0u, 0u, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_block(&mat, 1u, 1u, 4u, 4u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get_block(&mat, 1u, 1u, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&sub_mat1, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, actual);
    matrixf_get(&sub_mat1, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, actual);
    matrixf_get(&sub_mat1, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, actual);
    matrixf_get(&sub_mat1, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(8.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_block(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_block(&mat, 0u, 0u, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_block(&mat, 1u, 1u, 4u, 4u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_block(&mat, 1u, 1u, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&mat, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    matrixf_get(&mat, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    matrixf_get(&mat, 0u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
    matrixf_get(&mat, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, actual);
    matrixf_get(&mat, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 1u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 2u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, actual);
    matrixf_get(&mat, 2u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 2u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_get_top_left_corner(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_top_left_corner(&mat, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_top_left_corner(&mat, 2u, 2u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get_top_left_corner(&mat, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&sub_mat1, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    matrixf_get(&sub_mat1, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    matrixf_get(&sub_mat1, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, actual);
    matrixf_get(&sub_mat1, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_top_left_corner(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_top_left_corner(&mat, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_top_left_corner(&mat, 4u, 4u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_top_left_corner(&mat, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&mat, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 0u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
    matrixf_get(&mat, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 1u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, actual);
    matrixf_get(&mat, 2u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, actual);
    matrixf_get(&mat, 2u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, actual);
    matrixf_get(&mat, 2u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(8.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_get_top_right_corner(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_top_right_corner(&mat, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_top_right_corner(&mat, 2u, 2u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get_top_right_corner(&mat, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&sub_mat1, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    matrixf_get(&sub_mat1, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
    matrixf_get(&sub_mat1, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, actual);
    matrixf_get(&sub_mat1, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_top_right_corner(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_top_right_corner(&mat, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_top_right_corner(&mat, 4u, 4u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_top_right_corner(&mat, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&mat, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    matrixf_get(&mat, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 0u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, actual);
    matrixf_get(&mat, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 1u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 2u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, actual);
    matrixf_get(&mat, 2u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, actual);
    matrixf_get(&mat, 2u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(8.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_get_bottom_left_corner(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_bottom_left_corner(&mat, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_bottom_left_corner(&mat, 2u, 2u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get_bottom_left_corner(&mat, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&sub_mat1, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, actual);
    matrixf_get(&sub_mat1, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, actual);
    matrixf_get(&sub_mat1, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, actual);
    matrixf_get(&sub_mat1, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_bottom_left_corner(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_bottom_left_corner(&mat, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_bottom_left_corner(&mat, 4u, 4u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_bottom_left_corner(&mat, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&mat, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    matrixf_get(&mat, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    matrixf_get(&mat, 0u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
    matrixf_get(&mat, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 1u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, actual);
    matrixf_get(&mat, 2u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 2u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 2u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(8.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_get_bottom_right_corner(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_bottom_right_corner(&mat, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_get_bottom_right_corner(&mat, 2u, 2u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get_bottom_right_corner(&mat, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&sub_mat1, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, actual);
    matrixf_get(&sub_mat1, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, actual);
    matrixf_get(&sub_mat1, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, actual);
    matrixf_get(&sub_mat1, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(8.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_set_bottom_right_corner(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            const float32_t value = (float32_t)i * 3.0f + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf sub_mat1;
    float32_t      sub_mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&sub_mat1, 2, 2, sub_mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_set_constant(&sub_mat1, 10.0f);

    struct Matrixf sub_mat2;
    float32_t      sub_mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&sub_mat2, 4, 4, sub_mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_bottom_right_corner(&mat, 4u, 4u, &sub_mat2));
    TEST_ASSERT_EQUAL(RC_FAIL, matrixf_set_bottom_right_corner(&mat, 4u, 4u, &sub_mat2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_set_bottom_right_corner(&mat, 2u, 2u, &sub_mat1));
    float32_t actual;
    matrixf_get(&mat, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    matrixf_get(&mat, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    matrixf_get(&mat, 0u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
    matrixf_get(&mat, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, actual);
    matrixf_get(&mat, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 1u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 2u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, actual);
    matrixf_get(&mat, 2u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    matrixf_get(&mat, 2u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_get_row(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(2, 6)];
    matrixf_init(&mat, 2, 6, mat_buf, MATRIXF_MIN_BUF_SIZE(2, 6));

    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            const float32_t value = i * mat.cols + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf out;
    float32_t      out_buf[MATRIXF_MIN_BUF_SIZE(1u, 6u)];
    matrixf_init(&out, 1, 6, out_buf, MATRIXF_MIN_BUF_SIZE(1u, 6u));

    // call method and check results
    const uint8_t data_index = 1u;
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get_row(&mat, data_index, &out));

    float32_t actual;
    float32_t expected;
    for (uint8_t i = 0u; i < mat.cols; i++)
    {
        matrixf_get(&mat, data_index, i, &expected);
        matrixf_get(&out, 0u, i, &actual);
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_get_col(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(2, 6)];
    matrixf_init(&mat, 2, 6, mat_buf, MATRIXF_MIN_BUF_SIZE(2, 6));

    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        for (uint8_t j = 0u; j < mat.cols; j++)
        {
            const float32_t value = i * mat.cols + j;
            matrixf_set(&mat, i, j, value);
        }
    }

    struct Matrixf out;
    float32_t      out_buf[MATRIXF_MIN_BUF_SIZE(2u, 1u)];
    matrixf_init(&out, 2, 1, out_buf, MATRIXF_MIN_BUF_SIZE(2u, 1u));

    // call method and check results
    const uint8_t data_index = 3u;
    TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get_col(&mat, data_index, &out));

    float32_t actual;
    float32_t expected;
    for (uint8_t i = 0u; i < mat.rows; i++)
    {
        matrixf_get(&mat, i, data_index, &expected);
        matrixf_get(&out, i, 0u, &actual);
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_matrixf_get_size(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3, 6)];
    matrixf_init(&mat1, 3, 6, mat1_buf, MATRIXF_MIN_BUF_SIZE(3, 6));

    TEST_ASSERT_EQUAL(18, matrixf_get_size(&mat1));
    TEST_ASSERT_EQUAL(3u, matrixf_get_rows(&mat1));
    TEST_ASSERT_EQUAL(6u, matrixf_get_cols(&mat1));

    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(4u, 4u)];
    matrixf_init(&mat2, 4, 4, mat2_buf, MATRIXF_MIN_BUF_SIZE(4u, 4u));
    TEST_ASSERT_EQUAL(16, matrixf_get_size(&mat2));
    TEST_ASSERT_EQUAL(4u, matrixf_get_rows(&mat2));
    TEST_ASSERT_EQUAL(4u, matrixf_get_cols(&mat2));

    struct Matrixf mat3;
    float32_t      mat3_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    matrixf_init(&mat3, 6, 6, mat3_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    TEST_ASSERT_EQUAL(36, matrixf_get_size(&mat3));
    TEST_ASSERT_EQUAL(6u, matrixf_get_rows(&mat3));
    TEST_ASSERT_EQUAL(6u, matrixf_get_cols(&mat3));
}

static void test_matrixf_get_serialized_size(void)
{
    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(3, 6)];
    matrixf_init(&mat1, 3, 6, mat1_buf, MATRIXF_MIN_BUF_SIZE(3, 6));
    TEST_ASSERT_EQUAL_UINT32(76, matrixf_get_serialized_size(&mat1));

    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(3, 3)];
    matrixf_init(&mat2, 3, 3, mat2_buf, MATRIXF_MIN_BUF_SIZE(3, 3));
    TEST_ASSERT_EQUAL_UINT32(40, matrixf_get_serialized_size(&mat2));

}

static void test_matrixf_serialize(void)
{
    // zero length
    /*
    {
        uint8_t expected_buffer[] = {
                                     0x00, 0x00, 0x00, 0x00,
                                     0x00, 0x00, 0x00, 0x00, // padding
                                    };
        uint8_t buffer[40];

        struct Matrixf mat;
        float32_t mat_buf[MATRIXF_MIN_BUF_SIZE(0, 0)];
        matrixf_init(&mat, 0, 0, mat_buf, MATRIXF_MIN_BUF_SIZE(0, 0));

        TEST_ASSERT_EQUAL_UINT32(4, matrixf_get_serialized_size_4byte_aligned(&mat));

        TEST_ASSERT_EQUAL_UINT32(4, matrixf_serialize_4byte_aligned(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);

        TEST_ASSERT_EQUAL_UINT32(0, matrixf_data_serialize_4byte_aligned(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer + 4, buffer, 0);
    }
    */
    // odd length
    {
        uint8_t expected_buffer[] = {
                                     0x04, 0x02, 0x00, 0x00,
                                     0x3f, 0x80, 0x00, 0x00, // float32 1
                                     0x40, 0x00, 0x00, 0x00, // float32 2
                                     0x40, 0x40, 0x00, 0x00, // float32 3
                                     0x40, 0x80, 0x00, 0x00, // float32 4
                                     0x40, 0xa0, 0x00, 0x00, // float32 5
                                     0x40, 0xc0, 0x00, 0x00, // float32 6
                                     0x40, 0xe0, 0x00, 0x00, // float32 7
                                     0x41, 0x00, 0x00, 0x00, // float32 8
                                     0x00, 0x00, 0x00, 0x00, // padding
                                    };
        uint8_t buffer[40];

        struct Matrixf mat;
        float32_t mat_buf[MATRIXF_MIN_BUF_SIZE(4, 2)];
        matrixf_init(&mat, 4, 2, mat_buf, MATRIXF_MIN_BUF_SIZE(4, 2));
        for(uint8_t i = 0; i < 4; ++i)
        {
            for(uint8_t j = 0; j < 2; ++j)
            {
                matrixf_set(&mat, i, j, i * 2 + j + 1);
            }
        }

        TEST_ASSERT_EQUAL_UINT32(36, matrixf_get_serialized_size(&mat));

        TEST_ASSERT_EQUAL_UINT32(36, matrixf_serialize(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 36);

        TEST_ASSERT_EQUAL_UINT32(32, matrixf_data_serialize(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer + 4, buffer, 32);
    }
    //even length
    {
        uint8_t expected_buffer[] = {
                                     0x03, 0x03, 0x00, 0x00,
                                     0x3f, 0x80, 0x00, 0x00, // float32 1
                                     0x40, 0x00, 0x00, 0x00, // float32 2
                                     0x40, 0x40, 0x00, 0x00, // float32 3
                                     0x40, 0x80, 0x00, 0x00, // float32 4
                                     0x40, 0xa0, 0x00, 0x00, // float32 5
                                     0x40, 0xc0, 0x00, 0x00, // float32 6
                                     0x40, 0xe0, 0x00, 0x00, // float32 7
                                     0x41, 0x00, 0x00, 0x00, // float32 8
                                     0x41, 0x10, 0x00, 0x00, // float32 9
                                     0x00, 0x00, 0x00, 0x00, // padding
                                    };
        uint8_t buffer[44];

        struct Matrixf mat;
        float32_t mat_buf[MATRIXF_MIN_BUF_SIZE(3, 3)];
        matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3, 3));
        for(uint8_t i = 0; i < 3; ++i)
        {
            for(uint8_t j = 0; j < 3; ++j)
            {
                matrixf_set(&mat, i, j, i * 3 + j + 1);
            }
        }

        TEST_ASSERT_EQUAL_UINT32(40, matrixf_get_serialized_size(&mat));

        TEST_ASSERT_EQUAL_UINT32(40, matrixf_serialize(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 40);

        TEST_ASSERT_EQUAL_UINT32(36, matrixf_data_serialize(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer + 4, buffer, 36);
    }

}

static void test_matrixf_deserialize(void)
{
    // zero length
    /*
    {
        uint8_t expected_buffer[] = {
                                     0x00, 0x00, 0x00, 0x00,
                                     0x00, 0x00, 0x00, 0x00, // padding
                                    };
        uint8_t buffer[40];

        struct Matrixf mat;
        float32_t mat_buf[MATRIXF_MIN_BUF_SIZE(0, 0)];
        matrixf_init(&mat, 0, 0, mat_buf, MATRIXF_MIN_BUF_SIZE(0, 0));

        TEST_ASSERT_EQUAL_UINT32(4, matrixf_get_serialized_size(&mat));

        TEST_ASSERT_EQUAL_UINT32(4, matrixf_serialize(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);

        TEST_ASSERT_EQUAL_UINT32(0, matrixf_data_serialize(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer + 4, buffer, 0);
    }
    */
    // odd length
    {
        uint8_t buffer[] = {
                                     0x04, 0x02, 0x00, 0x00,
                                     0x3f, 0x80, 0x00, 0x00, // float32 1
                                     0x40, 0x00, 0x00, 0x00, // float32 2
                                     0x40, 0x40, 0x00, 0x00, // float32 3
                                     0x40, 0x80, 0x00, 0x00, // float32 4
                                     0x40, 0xa0, 0x00, 0x00, // float32 5
                                     0x40, 0xc0, 0x00, 0x00, // float32 6
                                     0x40, 0xe0, 0x00, 0x00, // float32 7
                                     0x41, 0x00, 0x00, 0x00, // float32 8
                                     0x00, 0x00, 0x00, 0x00, // padding
                                    };

        struct Matrixf mat;
        float32_t mat_buf[MATRIXF_MIN_BUF_SIZE(4, 4)];
        matrixf_init(&mat, 1, 1, mat_buf, MATRIXF_MIN_BUF_SIZE(4, 4));

        TEST_ASSERT_EQUAL_UINT32(36, matrixf_deserialize(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8(4, matrixf_get_rows(&mat));
        TEST_ASSERT_EQUAL_UINT8(2, matrixf_get_cols(&mat));
        for(uint8_t i = 0; i < 4; ++i)
        {
            for(uint8_t j = 0; j < 2; ++j)
            {
                TEST_ASSERT_FLOAT_WITHIN(1e-6, (float32_t)(i * 2 + j + 1), matrixf_get_unsafe(&mat, i, j));
            }
        }

        matrixf_resize(&mat, 4, 2);
        TEST_ASSERT_EQUAL_UINT32(32, matrixf_data_deserialize(&mat, buffer + 4, 40));
        for(uint8_t i = 0; i < 4; ++i)
        {
            for(uint8_t j = 0; j < 2; ++j)
            {
                TEST_ASSERT_FLOAT_WITHIN(1e-6, (float32_t)(i * 2 + j + 1), matrixf_get_unsafe(&mat, i, j));
            }
        }
    }
    //even length
    {
        uint8_t buffer[] = {
                                     0x03, 0x03, 0x00, 0x00,
                                     0x3f, 0x80, 0x00, 0x00, // float32 1
                                     0x40, 0x00, 0x00, 0x00, // float32 2
                                     0x40, 0x40, 0x00, 0x00, // float32 3
                                     0x40, 0x80, 0x00, 0x00, // float32 4
                                     0x40, 0xa0, 0x00, 0x00, // float32 5
                                     0x40, 0xc0, 0x00, 0x00, // float32 6
                                     0x40, 0xe0, 0x00, 0x00, // float32 7
                                     0x41, 0x00, 0x00, 0x00, // float32 8
                                     0x41, 0x10, 0x00, 0x00, // float32 9
                                     0x00, 0x00, 0x00, 0x00, // padding
                                    };

        struct Matrixf mat;
        float32_t mat_buf[MATRIXF_MIN_BUF_SIZE(4, 4)];
        matrixf_init(&mat, 1, 1, mat_buf, MATRIXF_MIN_BUF_SIZE(4, 4));

        TEST_ASSERT_EQUAL_UINT32(40, matrixf_deserialize(&mat, buffer, 40));
        TEST_ASSERT_EQUAL_UINT8(3, matrixf_get_rows(&mat));
        TEST_ASSERT_EQUAL_UINT8(3, matrixf_get_cols(&mat));
        for(uint8_t i = 0; i < 3; ++i)
        {
            for(uint8_t j = 0; j < 3; ++j)
            {
                TEST_ASSERT_FLOAT_WITHIN(1e-6, (float32_t)(i * 3 + j + 1), matrixf_get_unsafe(&mat, i, j));
            }
        }

        matrixf_resize(&mat, 3, 3);
        TEST_ASSERT_EQUAL_UINT32(36, matrixf_data_deserialize(&mat, buffer + 4, 40));
        for(uint8_t i = 0; i < 3; ++i)
        {
            for(uint8_t j = 0; j < 3; ++j)
            {
                TEST_ASSERT_FLOAT_WITHIN(1e-6, (float32_t)(i * 3 + j + 1), matrixf_get_unsafe(&mat, i, j));
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_matrixf_init);
    RUN_TEST(test_matrix22f_init);
    RUN_TEST(test_matrix33f_init);
    RUN_TEST(test_matrix44f_init);
    RUN_TEST(test_matrix66f_init);
    RUN_TEST(test_matrix_resize);
    RUN_TEST(test_matrixf_is_valid);
    RUN_TEST(test_matrixf_set_from_array);
    RUN_TEST(test_matrixf_set_from_array_unsafe);
    RUN_TEST(test_matrixf_set_from_matrixf);
    RUN_TEST(test_matrixf_set_from_matrixf_unsafe);
    RUN_TEST(test_matrixf_is_equal);
    RUN_TEST(test_matrixf_set_get);
    RUN_TEST(test_matrixf_set_get_unsafe);
    RUN_TEST(test_matrixf_add);
    RUN_TEST(test_matrixf_sub);
    RUN_TEST(test_matrixf_negate);
    RUN_TEST(test_matrixf_multiply_float32);
    RUN_TEST(test_matrixf_multiply);
    RUN_TEST(test_matrixf_multiply2);
    RUN_TEST(test_matrixf_multiply3);
    RUN_TEST(test_matrixf_multiply4);
    RUN_TEST(test_matrixf_transpose);
    RUN_TEST(test_matrixf_norm_and_norm_sqr);
    RUN_TEST(test_matrixf_inverse);
    RUN_TEST(test_matrixf_inverse_inplace);
    RUN_TEST(test_matrixf_determinant);
    RUN_TEST(test_matrixf_dot);
    RUN_TEST(test_matrixf_cross);
    RUN_TEST(test_matrixf_trace);
    RUN_TEST(test_matrixf_set_constant);
    RUN_TEST(test_matrixf_set_zeros);
    RUN_TEST(test_matrixf_set_ones);
    RUN_TEST(test_matrixf_set_identity);
    RUN_TEST(test_matrixf_get_block);
    RUN_TEST(test_matrixf_set_block);
    RUN_TEST(test_matrixf_get_top_left_corner);
    RUN_TEST(test_matrixf_set_top_left_corner);
    RUN_TEST(test_matrixf_get_top_right_corner);
    RUN_TEST(test_matrixf_set_top_right_corner);
    RUN_TEST(test_matrixf_get_bottom_left_corner);
    RUN_TEST(test_matrixf_set_bottom_left_corner);
    RUN_TEST(test_matrixf_get_bottom_right_corner);
    RUN_TEST(test_matrixf_set_bottom_right_corner);
    RUN_TEST(test_matrixf_get_row);
    RUN_TEST(test_matrixf_get_col);
    RUN_TEST(test_matrixf_get_size);

    RUN_TEST(test_matrixf_get_serialized_size);
    RUN_TEST(test_matrixf_serialize);
    RUN_TEST(test_matrixf_deserialize);
    return UNITY_END();
}
