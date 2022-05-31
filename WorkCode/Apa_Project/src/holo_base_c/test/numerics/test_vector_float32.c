/*!
 * @file test_vector_float32.c
 * @brief unit test of vector
 * @author duyanwei@holomatic.com
 * @date 2019-08-07
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/numerics/vector.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_init_default(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&vec, 6, vec_buf, VECTORF_MIN_BUF_SIZE(6u));

    // check results
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        float32_t value = 1.0f;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &value));
        TEST_ASSERT_EQUAL_FLOAT(0.0f, value);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_init(void)
{
    struct Vectorf vec;

    const uint16_t buffer_size                      = 6u;
    float32_t      buffer[VECTORF_MIN_BUF_SIZE(6u)] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    // call method and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_init(&vec, buffer_size, buffer, VECTORF_MIN_BUF_SIZE(6u)));
    TEST_ASSERT_EQUAL(buffer_size, vectorf_get_size(&vec));
    for (uint8_t i = 0u; i < buffer_size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vector2f_init(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));

    // check results
    const float32_t expected = 0.0f;
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vector3f_init(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));

    // check results
    const float32_t expected = 0.0f;
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vector4f_init(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&vec, 4, vec_buf, VECTORF_MIN_BUF_SIZE(4u));

    // check results
    const float32_t expected = 0.0f;
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vector5f_init(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[MATRIXF_MIN_BUF_SIZE(5, 1)];
    vectorf_init(&vec, 5, vec_buf, MATRIXF_MIN_BUF_SIZE(5, 1));

    // check results
    const float32_t expected = 0.0f;
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vector6f_init(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&vec, 6, vec_buf, VECTORF_MIN_BUF_SIZE(6u));

    // check results
    const float32_t expected = 0.0f;
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vector_resize(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&vec, 6, vec_buf, VECTORF_MIN_BUF_SIZE(6u));

    vectorf_resize(&vec, 3);

    // check results
    TEST_ASSERT_EQUAL(3u, vec.rows);
    TEST_ASSERT_EQUAL(3u, vec.size);
    TEST_ASSERT_EQUAL(VECTORF_MIN_BUF_SIZE(6u), vec.capacity);

    const float32_t expected = 0.0f;
    for (uint8_t i = 0u; i < vec.rows; i++)
    {
        float32_t actual = 0.0f ;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }

    retcode_t rc = vectorf_resize(&vec, 8) ;
#ifdef MATRIX_ALIGN
    TEST_ASSERT_EQUAL_UINT(RC_SUCCESS, rc);
#else
    TEST_ASSERT_FALSE(RC_SUCCESS == rc);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_is_valid(void)
{
    struct Vectorf vec1;
    float32_t      vec1_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec1, 2, vec1_buf, VECTORF_MIN_BUF_SIZE(2u));

    struct Vectorf vec2;
    float32_t      vec2_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec2, 2, vec2_buf, VECTORF_MIN_BUF_SIZE(2u));

    // check results
    TEST_ASSERT_TRUE(vectorf_is_valid(&vec1));
    TEST_ASSERT_TRUE(vectorf_is_valid(&vec2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_from_array(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&vec, 6, vec_buf, VECTORF_MIN_BUF_SIZE(6u));

    // init vector from array
    {
        float32_t sample[6] = {0.0f};
        for (uint16_t i = 0; i < 6u; i++)
        {
            sample[i] = i;
        }

        vectorf_set_from_array(&vec, sample, 6);
    }

    // check results
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        const float32_t expected = i;
        float32_t       actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_from_vectorf(void)
{
    struct Vectorf vec1;
    float32_t      vec1_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec1, 3, vec1_buf, VECTORF_MIN_BUF_SIZE(3u));
    struct Vectorf vec2;
    float32_t      vec2_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec2, 3, vec2_buf, VECTORF_MIN_BUF_SIZE(3u));

    vectorf_set_constant(&vec1, 1.0f);
    vectorf_set_constant(&vec2, -1.0f);

    // check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_set_from_vectorf(&vec2, &vec1));
    for (uint16_t i = 0u; i < vec2.size; i++)
    {
        float32_t expected;
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec1, i, &expected));
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec2, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_is_equal(void)
{
    struct Vectorf vec1;
    float32_t      vec1_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&vec1, 4, vec1_buf, VECTORF_MIN_BUF_SIZE(4u));
    struct Vectorf vec2;
    float32_t      vec2_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&vec2, 4, vec2_buf, VECTORF_MIN_BUF_SIZE(4u));

    vectorf_set_constant(&vec1, -1.0f);
    vectorf_set_constant(&vec2, -1.0f);

    // check results
    TEST_ASSERT_TRUE(vectorf_is_equal(&vec1, &vec2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_get(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&vec, 4, vec_buf, VECTORF_MIN_BUF_SIZE(4u));
    vectorf_set_constant(&vec, 10.0f);

    // call set and check
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_set(&vec, i, i));
    }

    // call get and check results
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        const float32_t expected = i;
        float32_t       actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_get_unsafe()
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&vec, 4, vec_buf, VECTORF_MIN_BUF_SIZE(4u));
    vectorf_set_constant(&vec, 10.0f);

    // call set and check
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_set_unsafe(&vec, i, i));
    }

    // call get and check results
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        const float32_t expected = i;
        float32_t       actual   = vectorf_get_unsafe(&vec, i);
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_add(void)
{
    struct Vectorf vec1;
    float32_t      vec1_buf[MATRIXF_MIN_BUF_SIZE(10, 1)];
    vectorf_init(&vec1, 10, vec1_buf, MATRIXF_MIN_BUF_SIZE(10, 1));
    struct Vectorf vec2;
    float32_t      vec2_buf[MATRIXF_MIN_BUF_SIZE(10, 1)];
    vectorf_init(&vec2, 10, vec2_buf, MATRIXF_MIN_BUF_SIZE(10, 1));

    vectorf_set_constant(&vec1, 1.0f);
    vectorf_set_constant(&vec2, 1.0f);

    // call add and check results
    struct Vectorf vec3;
    float32_t      vec3_buf[MATRIXF_MIN_BUF_SIZE(10, 1)];
    vectorf_init(&vec3, 10, vec3_buf, MATRIXF_MIN_BUF_SIZE(10, 1));

    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_add(&vec1, &vec2, &vec3));

    const float32_t expected = 2.0f;
    for (uint16_t i = 0u; i < vec3.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec3, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_sub(void)
{
    struct Vectorf vec1;
    float32_t      vec1_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec1, 3, vec1_buf, VECTORF_MIN_BUF_SIZE(3u));
    struct Vectorf vec2;
    float32_t      vec2_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec2, 3, vec2_buf, VECTORF_MIN_BUF_SIZE(3u));

    vectorf_set_constant(&vec1, 5.0f);
    vectorf_set_constant(&vec2, 10.0f);

    // call add and check results
    struct Vectorf vec3;
    float32_t      vec3_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec3, 3, vec3_buf, VECTORF_MIN_BUF_SIZE(3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_sub(&vec1, &vec2, &vec3));

    const float32_t expected = -5.0f;
    for (uint16_t i = 0u; i < vec3.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec3, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_negate(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[MATRIXF_MIN_BUF_SIZE(5, 1)];
    vectorf_init(&vec, 5, vec_buf, MATRIXF_MIN_BUF_SIZE(5, 1));
    vectorf_set_constant(&vec, 5.0f);

    // call scale and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_negate(&vec));

    const float32_t expected = -5.0f;
    for (uint16_t i = 0; i < vec.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_multiply_float32(void)
{
    struct Vectorf vec1;
    float32_t      vec1_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec1, 3, vec1_buf, VECTORF_MIN_BUF_SIZE(3u));
    struct Vectorf vec2;
    float32_t      vec2_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec2, 3, vec2_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set_ones(&vec1);
    vectorf_set_ones(&vec2);

    // call and check results
    const float32_t scalar = 5.0f;
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_multiply_float32(&vec1, scalar, &vec2));
    for (uint16_t i = 0u; i < vec2.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec2, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(scalar, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_multiply_matrixf(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&vec, 6, vec_buf, VECTORF_MIN_BUF_SIZE(6u));
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(1, 5)];
    matrixf_init(&mat, 1, 5, mat_buf, MATRIXF_MIN_BUF_SIZE(1, 5));

    matrixf_set_constant(&mat, 5.0f);
    vectorf_set_constant(&vec, 5.0f);

    // call multiply and check results
    struct Matrixf out;
    float32_t      out_buf[MATRIXF_MIN_BUF_SIZE(6u, 5u)];
    matrixf_init(&out, 6, 5, out_buf, MATRIXF_MIN_BUF_SIZE(6u, 5u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_multiply_matrixf(&vec, &mat, &out));

    const float32_t expected = 25.0f;
    for (uint8_t i = 0u; i < out.rows; i++)
    {
        for (uint8_t j = 0u; j < out.cols; j++)
        {
            float32_t actual;
            matrixf_get(&out, i, j, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_multiply_by_matrixf(void)
{
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(5u, 6u)];
    matrixf_init(&mat, 5, 6, mat_buf, MATRIXF_MIN_BUF_SIZE(5u, 6u));
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&vec, 6, vec_buf, VECTORF_MIN_BUF_SIZE(6u));

    matrixf_set_constant(&mat, 5.0f);
    vectorf_set_constant(&vec, 5.0f);

    // call multiply and check results
    struct Vectorf out;
    float32_t      out_buf[MATRIXF_MIN_BUF_SIZE(5, 1)];
    vectorf_init(&out, 5, out_buf, MATRIXF_MIN_BUF_SIZE(5, 1));
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_multiply_by_matrixf(&vec, &mat, &out));

    const float32_t expected = 150.0f;
    for (uint16_t i = 0u; i < out.size; i++)
    {
        float32_t actual;
        vectorf_get(&out, i, &actual);
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_transpose(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    {
        float32_t array[3];
        for (uint16_t i = 0u; i < 3u; i++)
        {
            array[i] = i;
        }
        vectorf_set_from_array(&vec, array, 3u);
    }

    // call transpose and check results
    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(1u, 3u)];
    matrixf_init(&mat, 1, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(1u, 3u));
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_transpose(&vec, &mat));

    for (uint8_t j = 0u; j < mat.cols; j++)
    {
        float32_t expected;
        float32_t actual;
        vectorf_get(&vec, j, &expected);
        matrixf_get(&mat, 0u, j, &actual);
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_norm_and_norm_sqr(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&vec, 4, vec_buf, VECTORF_MIN_BUF_SIZE(4u));
    vectorf_set_constant(&vec, -1.0f);

    // call scale and check results
    const float32_t expected_norm     = 2.0f;
    const float32_t expected_norm_sqr = 4.0f;

    TEST_ASSERT_EQUAL_FLOAT(expected_norm, vectorf_get_norm(&vec));
    TEST_ASSERT_EQUAL_FLOAT(expected_norm_sqr, vectorf_get_norm_sqr(&vec));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_normalize(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&vec, 4, vec_buf, VECTORF_MIN_BUF_SIZE(4u));
    vectorf_set_constant(&vec, -1.0f);

    // call normalize and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_normalize(&vec));

    const float32_t expected = -0.5f;
    for (uint8_t i = 0u; i < vec.size; i++)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&vec, i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_dot(void)
{
    // create two matrics
    struct Vectorf vec1;
    float32_t      vec1_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec1, 3, vec1_buf, VECTORF_MIN_BUF_SIZE(3u));
    struct Vectorf vec2;
    float32_t      vec2_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec2, 3, vec2_buf, VECTORF_MIN_BUF_SIZE(3u));

    {
        float32_t array1[3];
        float32_t array2[3];

        for (uint16_t i = 0u; i < 3u; i++)
        {
            array1[i] = i;
            array2[i] = 2.0f - i;
        }

        vectorf_set_from_array(&vec1, array1, 3);
        vectorf_set_from_array(&vec2, array2, 3);
    }

    // call dot and check results
    const float32_t expected = 1.0f;
    float32_t       actual;
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_dot(&vec1, &vec2, &actual));
    TEST_ASSERT_EQUAL_FLOAT(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_cross(void)
{
    // create two matrics
    struct Vectorf vec1;
    float32_t      vec1_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec1, 3, vec1_buf, VECTORF_MIN_BUF_SIZE(3u));
    struct Vectorf vec2;
    float32_t      vec2_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec2, 3, vec2_buf, VECTORF_MIN_BUF_SIZE(3u));

    {
        float32_t array1[3] = {0.0f};
        float32_t array2[3] = {0.0f};

        for (uint16_t i = 0u; i < 3u; i++)
        {
            array1[i] = i;
            array2[i] = 2.0f - i;
        }

        vectorf_set_from_array(&vec1, array1, 3);
        vectorf_set_from_array(&vec2, array2, 3);
    }

    struct Vectorf vec3;
    float32_t      vec3_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec3, 3, vec3_buf, VECTORF_MIN_BUF_SIZE(3u));

    // call cross and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_cross(&vec1, &vec2, &vec3));
    float32_t actual;
    vectorf_get(&vec3, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, actual);
    vectorf_get(&vec3, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, actual);
    vectorf_get(&vec3, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_constant(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[MATRIXF_MIN_BUF_SIZE(5, 1)];
    vectorf_init(&vec, 5, vec_buf, MATRIXF_MIN_BUF_SIZE(5, 1));

    const float32_t expected = 10.0f;

    // call and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_set_constant(&vec, expected));

    for (uint16_t i = 0u; i < vec.size; i++)
    {
        float32_t actual;
        vectorf_get(&vec, i, &actual);
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_zeros(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[MATRIXF_MIN_BUF_SIZE(5, 1)];
    vectorf_init(&vec, 5, vec_buf, MATRIXF_MIN_BUF_SIZE(5, 1));

    // call and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_set_zeros(&vec));

    const float32_t expected = 0.0f;
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        float32_t actual;
        vectorf_get(&vec, i, &actual);
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_ones(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[MATRIXF_MIN_BUF_SIZE(5, 1)];
    vectorf_init(&vec, 5, vec_buf, MATRIXF_MIN_BUF_SIZE(5, 1));

    // call and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_set_ones(&vec));

    const float32_t expected = 1.0f;
    for (uint16_t i = 0u; i < vec.size; i++)
    {
        float32_t actual;
        vectorf_get(&vec, i, &actual);
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_to_skew_symmetric(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));

    const float32_t wx = 1.0f;
    const float32_t wy = 2.0f;
    const float32_t wz = 3.0f;

    vectorf_set(&vec, 0u, wx);
    vectorf_set(&vec, 1u, wy);
    vectorf_set(&vec, 2u, wz);

    struct Matrixf mat;
    float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&mat, 3, 3, mat_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    // call and check results
    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_to_skew_symmetric(&vec, &mat));

    float32_t actual;
    matrixf_get(&mat, 0u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    matrixf_get(&mat, 0u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-wz, actual);
    matrixf_get(&mat, 0u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(wy, actual);
    matrixf_get(&mat, 1u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(wz, actual);
    matrixf_get(&mat, 1u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    matrixf_get(&mat, 1u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-wx, actual);
    matrixf_get(&mat, 2u, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(-wy, actual);
    matrixf_get(&mat, 2u, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(wx, actual);
    matrixf_get(&mat, 2u, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_get_segment(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 0.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 2.0f);

    struct Vectorf sub_vec1;
    float32_t      sub_vec1_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&sub_vec1, 2, sub_vec1_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set_constant(&sub_vec1, 10.0f);

    struct Vectorf sub_vec2;
    float32_t      sub_vec2_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&sub_vec2, 4, sub_vec2_buf, VECTORF_MIN_BUF_SIZE(4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_get_segment(&vec, 1u, 3u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_get_segment(&vec, 4u, 3u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_get_segment(&vec, 5u, 3u, &sub_vec2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get_segment(&vec, 1u, 2u, &sub_vec1));
    float32_t actual;
    vectorf_get(&sub_vec1, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    vectorf_get(&sub_vec1, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_segment(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 0.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 2.0f);

    struct Vectorf sub_vec1;
    float32_t      sub_vec1_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&sub_vec1, 2, sub_vec1_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set_constant(&sub_vec1, 10.0f);

    struct Vectorf sub_vec2;
    float32_t      sub_vec2_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&sub_vec2, 4, sub_vec2_buf, VECTORF_MIN_BUF_SIZE(4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_set_segment(&vec, 1u, 3u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_set_segment(&vec, 4u, 3u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_set_segment(&vec, 5u, 3u, &sub_vec2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_set_segment(&vec, 1u, 2u, &sub_vec1));
    float32_t actual;
    vectorf_get(&vec, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    vectorf_get(&vec, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    vectorf_get(&vec, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_get_head(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 0.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 2.0f);

    struct Vectorf sub_vec1;
    float32_t      sub_vec1_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&sub_vec1, 2, sub_vec1_buf, VECTORF_MIN_BUF_SIZE(2u));

    struct Vectorf sub_vec2;
    float32_t      sub_vec2_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&sub_vec2, 4, sub_vec2_buf, VECTORF_MIN_BUF_SIZE(4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_get_head(&vec, 1u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_get_head(&vec, 4u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_get_head(&vec, 5u, &sub_vec2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get_head(&vec, 2u, &sub_vec1));
    float32_t actual;
    vectorf_get(&sub_vec1, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    vectorf_get(&sub_vec1, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_head(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 0.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 2.0f);

    struct Vectorf sub_vec1;
    float32_t      sub_vec1_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&sub_vec1, 2, sub_vec1_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set_constant(&sub_vec1, 10.0f);

    struct Vectorf sub_vec2;
    float32_t      sub_vec2_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&sub_vec2, 4, sub_vec2_buf, VECTORF_MIN_BUF_SIZE(4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_set_head(&vec, 1u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_set_head(&vec, 4u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_set_head(&vec, 5u, &sub_vec2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_set_head(&vec, 2, &sub_vec1));
    float32_t actual;
    vectorf_get(&vec, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    vectorf_get(&vec, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    vectorf_get(&vec, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_get_tail(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 0.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 2.0f);

    struct Vectorf sub_vec1;
    float32_t      sub_vec1_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&sub_vec1, 2, sub_vec1_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set_zeros(&sub_vec1);

    struct Vectorf sub_vec2;
    float32_t      sub_vec2_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&sub_vec2, 4, sub_vec2_buf, VECTORF_MIN_BUF_SIZE(4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_get_tail(&vec, 1u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_get_tail(&vec, 4u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_get_tail(&vec, 5u, &sub_vec2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get_tail(&vec, 2u, &sub_vec1));
    float32_t actual;
    vectorf_get(&sub_vec1, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual);
    vectorf_get(&sub_vec1, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_set_tail(void)
{
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec, 3, vec_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&vec, 0u, 0.0f);
    vectorf_set(&vec, 1u, 1.0f);
    vectorf_set(&vec, 2u, 2.0f);

    struct Vectorf sub_vec1;
    float32_t      sub_vec1_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&sub_vec1, 2, sub_vec1_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_set_constant(&sub_vec1, 10.0f);

    struct Vectorf sub_vec2;
    float32_t      sub_vec2_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&sub_vec2, 4, sub_vec2_buf, VECTORF_MIN_BUF_SIZE(4u));

    // call methods and check results
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_set_tail(&vec, 1u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_set_tail(&vec, 4u, &sub_vec2));
    TEST_ASSERT_EQUAL(RC_FAIL, vectorf_set_tail(&vec, 5u, &sub_vec2));

    TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_set_tail(&vec, 2, &sub_vec1));
    float32_t actual;
    vectorf_get(&vec, 0u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, actual);
    vectorf_get(&vec, 1u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
    vectorf_get(&vec, 2u, &actual);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_vectorf_get_size(void)
{
    struct Vectorf vec1;
    float32_t      vec1_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec1, 3, vec1_buf, VECTORF_MIN_BUF_SIZE(3u));

    struct Vectorf vec2;
    float32_t      vec2_buf[VECTORF_MIN_BUF_SIZE(4u)];
    vectorf_init(&vec2, 4, vec2_buf, VECTORF_MIN_BUF_SIZE(4u));

    struct Vectorf vec3;
    float32_t      vec3_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&vec3, 6, vec3_buf, VECTORF_MIN_BUF_SIZE(6u));

    TEST_ASSERT_EQUAL(3u, vectorf_get_size(&vec1));
    TEST_ASSERT_EQUAL(4u, vectorf_get_size(&vec2));
    TEST_ASSERT_EQUAL(6u, vectorf_get_size(&vec3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_vectorf_init_default);
    RUN_TEST(test_vectorf_init);
    RUN_TEST(test_vector2f_init);
    RUN_TEST(test_vector3f_init);
    RUN_TEST(test_vector4f_init);
    RUN_TEST(test_vector5f_init);
    RUN_TEST(test_vector6f_init);
    RUN_TEST(test_vector_resize);
    RUN_TEST(test_vectorf_is_valid);
    RUN_TEST(test_vectorf_set_from_array);
    RUN_TEST(test_vectorf_set_from_vectorf);
    RUN_TEST(test_vectorf_is_equal);
    RUN_TEST(test_vectorf_set_get);
    RUN_TEST(test_vectorf_set_get_unsafe);
    RUN_TEST(test_vectorf_add);
    RUN_TEST(test_vectorf_sub);
    RUN_TEST(test_vectorf_negate);
    RUN_TEST(test_vectorf_multiply_float32);
    RUN_TEST(test_vectorf_multiply_matrixf);
    RUN_TEST(test_vectorf_multiply_by_matrixf);
    RUN_TEST(test_vectorf_transpose);
    RUN_TEST(test_vectorf_norm_and_norm_sqr);
    RUN_TEST(test_vectorf_normalize);
    RUN_TEST(test_vectorf_dot);
    RUN_TEST(test_vectorf_cross);
    RUN_TEST(test_vectorf_set_constant);
    RUN_TEST(test_vectorf_set_zeros);
    RUN_TEST(test_vectorf_set_ones);
    RUN_TEST(test_vectorf_to_skew_symmetric);
    RUN_TEST(test_vectorf_get_segment);
    RUN_TEST(test_vectorf_set_segment);
    RUN_TEST(test_vectorf_get_head);
    RUN_TEST(test_vectorf_set_head);
    RUN_TEST(test_vectorf_get_tail);
    RUN_TEST(test_vectorf_set_tail);
    RUN_TEST(test_vectorf_get_size);
    return UNITY_END();
}
