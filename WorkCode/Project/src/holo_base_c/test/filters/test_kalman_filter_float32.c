/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_kalman_filter_float32.c
 * @brief The unit test for kalman filter float32
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Feb 11, 2020
 */

#include <unity.h>

#include <holo_c/core/retcode.h>
#include <holo_c/filters/kalman_filter_float32.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_init(void)
{
    /// Step 1: Prepare the relative values
    const uint8_t  state_dimension = 2u;
    struct Matrixf priori_covariance;
    struct Matrixf cov_with_wrong_dimension;
    struct Matrixf cov_no_square;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    float32_t      buffer_with_wrong_dimension[MATRIXF_MIN_BUF_SIZE(state_dimension + 1u, state_dimension + 1u)];
    float32_t      buffer_no_square[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension + 1u)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    matrixf_init(&cov_with_wrong_dimension, state_dimension + 1u, state_dimension + 1u, buffer_with_wrong_dimension,
                 MATRIXF_MIN_BUF_SIZE(state_dimension + 1u, state_dimension + 1u));
    matrixf_init(&cov_no_square, state_dimension, state_dimension + 1u, buffer_no_square,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension + 1u));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, state_dimension);
    for (uint8_t i = 0u; i < MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension); ++i)
    {
        buffer[i] = i;
    }
    for (uint8_t i = 0u; i < VECTORF_MIN_BUF_SIZE(state_dimension); ++i)
    {
        state_buffer[i] = i;
    }

    /// Step 2: Initialize the KalmanFilterf struct and check
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &cov_with_wrong_dimension);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);

    rc = kalman_filterf_init(&kalman_filter, &state, &cov_no_square);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_NOT_SQUARE, rc);

    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    for (uint8_t i = 0u; i < state_dimension; ++i)
    {
        for (uint8_t j = 0u; j < state_dimension; ++j)
        {
            float32_t actual;
            TEST_ASSERT_EQUAL(RC_SUCCESS, matrixf_get(&(kalman_filter.priori_estimate_covariance), i, j, &actual));
            TEST_ASSERT_EQUAL_FLOAT(i * state_dimension + j, actual);
        }
    }

    for (uint8_t i = 0u; i < state_dimension; ++i)
    {
        float32_t actual;
        TEST_ASSERT_EQUAL(RC_SUCCESS, vectorf_get(&(kalman_filter.current_state), i, &actual));
        TEST_ASSERT_EQUAL_FLOAT(i, actual);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_set_from_kalman_filterf(void)
{
    const uint8_t state_dimension = 3u;
    /// Step 1: Initialize the original KalmanFilterf struct
    struct Matrixf priori_covariance;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));

    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    /// Step 2: Initialize other KalmanFilterf struct
    struct Matrixf other_priori_covariance;
    float32_t      other_buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&other_priori_covariance, state_dimension, state_dimension, other_buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));

    struct Vectorf other_state;
    float32_t      other_state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&other_state, state_dimension, other_state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));

    struct KalmanFilterf other_kalman_filter;
    rc = kalman_filterf_init(&other_kalman_filter, &other_state, &other_priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    matrixf_set_ones(&other_priori_covariance);
    vectorf_set_ones(&other_state);
    other_kalman_filter.stability       = true;
    other_kalman_filter.stability_gamma = 2.0f;

    /// Step 3: Call the kalman_filterf_set_from_kalman_filterf function
    rc = kalman_filterf_set_from_kalman_filterf(&kalman_filter, &other_kalman_filter);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    /// Step 4: Compare the two kalman filter
    TEST_ASSERT_TRUE(vectorf_is_equal(&state, &other_state));
    TEST_ASSERT_TRUE(matrixf_is_equal(&priori_covariance, &other_priori_covariance));
    TEST_ASSERT_EQUAL(kalman_filterf_is_stable(&kalman_filter), kalman_filterf_is_stable(&other_kalman_filter));
    TEST_ASSERT_EQUAL_FLOAT(kalman_filter.stability_gamma, other_kalman_filter.stability_gamma);

    /// Step 5: Test the invalid other kalman filter input
    vectorf_resize(&other_state, state_dimension - 1u);
    matrixf_resize(&other_priori_covariance, state_dimension - 1u, state_dimension - 1u);
    kalman_filterf_init(&other_kalman_filter, &other_state, &other_priori_covariance);

    rc = kalman_filterf_set_from_kalman_filterf(&kalman_filter, &other_kalman_filter);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_is_valid(void)
{
    /// Step 1: Prepare the relative values
    const uint8_t  state_dimension = 2u;
    struct Matrixf priori_covariance;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    /// Step 3: Modify the kalman filter struct and check
    TEST_ASSERT_TRUE(kalman_filterf_is_valid(&kalman_filter));
    /// case 1: The covariance matrix is invalid
    kalman_filter.priori_estimate_covariance.rows = 0u;
    TEST_ASSERT_FALSE(kalman_filterf_is_valid(&kalman_filter));
    /// case 2: The state vector is invalid
    kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    kalman_filter.current_state.size = 0u;
    TEST_ASSERT_FALSE(kalman_filterf_is_valid(&kalman_filter));
    /// case 3: The covariance matrix is not a square
    kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    kalman_filter.priori_estimate_covariance.rows = state_dimension + 1u;
    TEST_ASSERT_FALSE(kalman_filterf_is_valid(&kalman_filter));
    /// case 4: The dimensions of the state and covariance are not equal
    kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    kalman_filter.current_state.size = state_dimension + 1u;
    TEST_ASSERT_FALSE(kalman_filterf_is_valid(&kalman_filter));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_reset(void)
{
    /// Step 1: Prepare the relative values
    const uint8_t  state_dimension = 5u;
    struct Matrixf priori_covariance;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    /// Step 3: Modify the state and covariance of the kalman filter struct
    vectorf_set_ones(&kalman_filter.current_state);
    matrixf_set_ones(&kalman_filter.priori_estimate_covariance);
    kalman_filter.stability       = true;
    kalman_filter.stability_gamma = 2.0f;

    /// Step 4: Call reset() and check
    rc = kalman_filterf_reset(&kalman_filter);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    const float32_t expected = 0.0f;
    for (uint8_t i = 0u; i < kalman_filter.priori_estimate_covariance.rows; ++i)
    {
        for (uint8_t j = 0u; j < kalman_filter.priori_estimate_covariance.cols; ++j)
        {
            float32_t actual;
            matrixf_get(&kalman_filter.priori_estimate_covariance, i, j, &actual);
            TEST_ASSERT_EQUAL_FLOAT(expected, actual);
        }
    }
    for (uint8_t i = 0u; i < kalman_filter.current_state.size; ++i)
    {
        float32_t actual;
        vectorf_get(&kalman_filter.current_state, i, &actual);
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);
    }
    TEST_ASSERT_EQUAL_FLOAT(1.0f, kalman_filter.stability_gamma);
    TEST_ASSERT_FALSE(kalman_filter.stability);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_set_state_with_covariance(void)
{
    /// Step 1: Prepare the relative values
    /// Kalman filter matrixf and vectorf
    const uint8_t  state_dimension = 5u;
    struct Matrixf priori_covariance;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    /// The matrixf and vectorf for setting
    struct Matrixf temp_cov;
    float32_t      temp_buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&temp_cov, state_dimension, state_dimension, temp_buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf temp_state;
    float32_t      temp_state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&temp_state, state_dimension, temp_state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    vectorf_set_ones(&temp_state);
    matrixf_set_ones(&temp_cov);

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    /// Step 3: Call the kalman_filterf_set_state_with_covariance()
    /// case 1: normal input
    rc = kalman_filterf_set_state_with_covariance(&kalman_filter, &temp_state, &temp_cov);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_TRUE(matrixf_is_equal(&kalman_filter.priori_estimate_covariance, &temp_cov));
    TEST_ASSERT_TRUE(vectorf_is_equal(&kalman_filter.current_state, &temp_state));

    /// case 2: the input state is invalid
    temp_state.size = state_dimension + 1u;
    rc              = kalman_filterf_set_state_with_covariance(&kalman_filter, &temp_state, &temp_cov);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);

    /// case 3: the input covariance is invalid
    vectorf_init(&temp_state, state_dimension, temp_state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    temp_cov.cols = state_dimension + 1u;
    rc            = kalman_filterf_set_state_with_covariance(&kalman_filter, &temp_state, &temp_cov);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_set_state(void)
{
    /// Step 1: Prepare the relative values
    /// Kalman filter matrixf and vectorf
    const uint8_t  state_dimension = 3u;
    struct Matrixf priori_covariance;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    /// The state vectorf for setting
    struct Vectorf temp_state;
    float32_t      temp_state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&temp_state, state_dimension, temp_state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    vectorf_set_ones(&temp_state);

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    /// Step 3: Call the kalman_filterf_set_state()
    /// case 1: normal input
    rc = kalman_filterf_set_state(&kalman_filter, &temp_state);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_TRUE(vectorf_is_equal(&kalman_filter.current_state, &temp_state));

    /// case 2: the input state is invalid
    vectorf_resize(&temp_state, state_dimension - 1u);
    rc = kalman_filterf_set_state(&kalman_filter, &temp_state);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_set_covariance(void)
{
    /// Step 1: Prepare the relative values
    /// Kalman filter matrixf and vectorf
    const uint8_t  state_dimension = 5u;
    struct Matrixf priori_covariance;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    /// The covariance matrixf for setting
    struct Matrixf temp_cov;
    float32_t      temp_buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&temp_cov, state_dimension, state_dimension, temp_buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    matrixf_set_ones(&temp_cov);

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    /// Step 3: Call the kalman_filterf_set_state_with_covariance()
    /// case 1: normal input
    rc = kalman_filterf_set_covariance(&kalman_filter, &temp_cov);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_TRUE(matrixf_is_equal(&kalman_filter.priori_estimate_covariance, &temp_cov));

    /// case 2: the input covariance is invalid
    matrixf_resize(&temp_cov, state_dimension - 1u, state_dimension - 1u);
    rc = kalman_filterf_set_covariance(&kalman_filter, &temp_cov);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_get_state(void)
{
    /// Step 1: Prepare the relative values
    /// Kalman filter matrixf and vectorf
    const uint8_t  state_dimension = 15u;
    struct Matrixf priori_covariance;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    /// The state vectorf for getting
    struct Vectorf getted_state;
    float32_t      getted_state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&getted_state, state_dimension, getted_state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    vectorf_set_ones(&kalman_filter.current_state);

    /// Step 3: Call the kalman_filterf_get_state()
    /// case 1: normal input
    rc = kalman_filterf_get_state(&kalman_filter, &getted_state);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_TRUE(vectorf_is_equal(&kalman_filter.current_state, &getted_state));

    /// case 2: the input state is invalid
    vectorf_resize(&getted_state, state_dimension - 1u);
    rc = kalman_filterf_get_state(&kalman_filter, &getted_state);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_get_covariance(void)
{
    /// Step 1: Prepare the relative values
    /// Kalman filter matrixf and vectorf
    const uint8_t  state_dimension = 5u;
    struct Matrixf priori_covariance;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    /// The covariance matrixf for getting
    struct Matrixf getted_cov;
    float32_t      getted_buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&getted_cov, state_dimension, state_dimension, getted_buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    matrixf_set_ones(&kalman_filter.priori_estimate_covariance);

    /// Step 3: Call the kalman_filterf_get_state_with_covariance()
    /// case 1: normal input
    rc = kalman_filterf_get_covariance(&kalman_filter, &getted_cov);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_TRUE(matrixf_is_equal(&kalman_filter.priori_estimate_covariance, &getted_cov));

    /// case 2: the input covariance is invalid
    matrixf_resize(&getted_cov, state_dimension - 1u, state_dimension - 1u);
    rc = kalman_filterf_get_covariance(&kalman_filter, &getted_cov);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_get_state_with_covariance(void)
{
    /// Step 1: Prepare the relative values
    /// Kalman filter matrixf and vectorf
    const uint8_t  state_dimension = 9u;
    struct Matrixf priori_covariance;
    float32_t      buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    /// The matrixf and vectorf for getting
    struct Matrixf getted_cov;
    float32_t      getted_buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&getted_cov, state_dimension, state_dimension, getted_buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    struct Vectorf getted_state;
    float32_t      getted_state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&getted_state, state_dimension, getted_state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    vectorf_set_ones(&kalman_filter.current_state);
    matrixf_set_ones(&kalman_filter.priori_estimate_covariance);

    /// Step 3: Call the kalman_filterf_set_state_with_covariance()
    /// case 1: normal input
    rc = kalman_filterf_get_state_with_covariance(&kalman_filter, &getted_state, &getted_cov);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_TRUE(matrixf_is_equal(&kalman_filter.priori_estimate_covariance, &getted_cov));
    TEST_ASSERT_TRUE(vectorf_is_equal(&kalman_filter.current_state, &getted_state));

    /// case 2: the input state is invalid
    vectorf_resize(&getted_state, state_dimension - 1u);
    rc = kalman_filterf_get_state_with_covariance(&kalman_filter, &getted_state, &getted_cov);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
    vectorf_resize(&getted_state, state_dimension);

    /// case 3: the input covariance is invalid
    vectorf_init(&getted_state, state_dimension, getted_state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    matrixf_resize(&getted_cov, state_dimension - 1u, state_dimension - 1u);
    rc = kalman_filterf_get_state_with_covariance(&kalman_filter, &getted_state, &getted_cov);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_predict(void)
{
    /* Generate state transition model, control and control model
     * Simulate a car moving on 2D plane, its 2D position is predicted by acceleration.
     * state is [x, y, Vz, Vy], control vector [ax, ay] can given by accelerometer of the car.
     *
     * F = [1  0  dt  0
     *      0  1  0   dt
     *      0  0  1   0
     *      0  0  0   1]
     *
     * u = [ax ay]^T
     *
     * B = [(dt^2)/2    0
     *       0         (dt^2)/2
     *       t          0
     *       0          t      ] */

    /// Step 1: Prepare the relative values
    /// 1) Create Kalman filter initial covariance matrixf and state vectorf
    const uint8_t  state_dimension = 4u;
    struct Matrixf priori_covariance;
    float32_t      cov_buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, cov_buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    matrixf_set_identity(&priori_covariance);

    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    /// 2) Create state transition model matrixf
    struct Matrixf state_transition_model;
    float32_t      state_transition_model_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&state_transition_model, state_dimension, state_dimension, state_transition_model_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    const float32_t delta_t = 0.5f;
    matrixf_set_identity(&state_transition_model);
    matrixf_set(&state_transition_model, 0u, 2u, delta_t);
    matrixf_set(&state_transition_model, 1u, 3u, delta_t);

    /// 3) Create control vectorf and control_input_model matrixf
    const uint8_t  control_dimension = 2u;
    struct Vectorf control;
    float32_t      control_buff[VECTORF_MIN_BUF_SIZE(control_dimension)];
    vectorf_init(&control, control_dimension, control_buff, VECTORF_MIN_BUF_SIZE(control_dimension));
    vectorf_set(&control, 0u, 1.0f);
    vectorf_set(&control, 1u, 0.1f);

    struct Matrixf control_input_model;
    float32_t      control_input_model_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, control_dimension)];
    matrixf_init(&control_input_model, state_dimension, control_dimension, control_input_model_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, control_dimension));
    matrixf_set(&control_input_model, 0u, 0u, 0.5f * delta_t * delta_t);
    matrixf_set(&control_input_model, 1u, 1u, 0.5f * delta_t * delta_t);
    matrixf_set(&control_input_model, 2u, 0u, delta_t);
    matrixf_set(&control_input_model, 3u, 1u, delta_t);

    /// 4) Create process noise covariance matrix
    struct Matrixf process_noise_covariance;
    float32_t      process_noise_covariance_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&process_noise_covariance, state_dimension, state_dimension, process_noise_covariance_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    matrixf_set_identity(&process_noise_covariance);

    /// Step 2: Generate expected values
    struct Vectorf expected_state;
    float32_t      expected_state_buff[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&expected_state, state_dimension, expected_state_buff, VECTORF_MIN_BUF_SIZE(state_dimension));
    vectorf_set(&expected_state, 0u, 0.125f);
    vectorf_set(&expected_state, 1u, 0.0125f);
    vectorf_set(&expected_state, 2u, 0.5f);
    vectorf_set(&expected_state, 3u, 0.05f);

    struct Matrixf expected_covariance;
    float32_t      expected_covariance_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&expected_covariance, state_dimension, state_dimension, expected_covariance_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    matrixf_set(&expected_covariance, 0u, 0u, 2.25f);
    matrixf_set(&expected_covariance, 0u, 2u, 0.5f);
    matrixf_set(&expected_covariance, 1u, 1u, 2.25f);
    matrixf_set(&expected_covariance, 1u, 3u, 0.5f);
    matrixf_set(&expected_covariance, 2u, 0u, 0.5f);
    matrixf_set(&expected_covariance, 2u, 2u, 2.0f);
    matrixf_set(&expected_covariance, 3u, 1u, 0.5f);
    matrixf_set(&expected_covariance, 3u, 3u, 2.0f);

    /// Step 3: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    /// Step 4: Call the kalman_filterf_predict()
    /// case 1: normal input
    rc = kalman_filterf_predict(&kalman_filter, &state_transition_model, &control_input_model, &control,
                                &process_noise_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_TRUE(matrixf_is_equal(&kalman_filter.priori_estimate_covariance, &expected_covariance));
    TEST_ASSERT_TRUE(vectorf_is_equal(&kalman_filter.current_state, &expected_state));

    /// case 2: the input state_transition_model is invalid
    matrixf_resize(&state_transition_model, state_dimension - 1u, state_dimension - 1u);
    rc = kalman_filterf_predict(&kalman_filter, &state_transition_model, &control_input_model, &control,
                                &process_noise_covariance);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
    matrixf_resize(&state_transition_model, state_dimension, state_dimension);

    /// case 3: the input control_input_model is invalid
    matrixf_resize(&control_input_model, state_dimension - 1u, control_dimension - 1u);
    rc = kalman_filterf_predict(&kalman_filter, &state_transition_model, &control_input_model, &control,
                                &process_noise_covariance);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
    matrixf_resize(&control_input_model, state_dimension, state_dimension);

    /// case 4: the control is invalid
    vectorf_resize(&control, control_dimension - 1u);
    rc = kalman_filterf_predict(&kalman_filter, &state_transition_model, &control_input_model, &control,
                                &process_noise_covariance);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
    vectorf_resize(&control, control_dimension);

    /// case 5: the process_noise_covairance is invalid
    matrixf_resize(&process_noise_covariance, state_dimension - 1u, state_dimension - 1u);
    rc = kalman_filterf_predict(&kalman_filter, &state_transition_model, &control_input_model, &control,
                                &process_noise_covariance);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
    matrixf_resize(&process_noise_covariance, state_dimension, state_dimension);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_correct(void)
{
    /* Generate observation, observation model and observation noise covariance
     * Simulate a car moving on 2D plane, its 2D position is corrected by gps measurement.
     * state is [x, y, Vz, Vy], gps measurement is [x_gps, y_gps] can given by gnss receiver of the car.
     *
     * z_gps = [x_gps y_gps]^T
     *
     * H_gps = [1 0 0 0
     *          0 1 0 0]
     *
     * R_gps = [cov_xx  cov_xy   = [0.5  0
     *          cov_yx  cov_yy]     0    0.3]
     */

    /// Step 1: Prepare the relative values
    /// 1) Create Kalman filter initial covariance matrixf and state vectorf
    const uint8_t  state_dimension = 4u;
    struct Matrixf priori_covariance;
    float32_t      cov_buffer[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, cov_buffer,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    matrixf_set(&priori_covariance, 0u, 0u, 2.25f);
    matrixf_set(&priori_covariance, 0u, 2u, 0.5f);
    matrixf_set(&priori_covariance, 1u, 1u, 2.25f);
    matrixf_set(&priori_covariance, 1u, 3u, 0.5f);
    matrixf_set(&priori_covariance, 2u, 0u, 0.5f);
    matrixf_set(&priori_covariance, 2u, 2u, 2.0f);
    matrixf_set(&priori_covariance, 3u, 1u, 0.5f);
    matrixf_set(&priori_covariance, 3u, 3u, 2.0f);

    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    vectorf_set(&state, 0u, 0.125f);
    vectorf_set(&state, 1u, 0.0125f);
    vectorf_set(&state, 2u, 0.5f);
    vectorf_set(&state, 3u, 0.05f);

    /// 2) Create observation_model matrixf
    const uint8_t  obs_dimension = 2u;  ///< The dimension of observation
    struct Matrixf observation_model;
    float32_t      observation_model_buff[MATRIXF_MIN_BUF_SIZE(obs_dimension, state_dimension)];
    matrixf_init(&observation_model, obs_dimension, state_dimension, observation_model_buff,
                 MATRIXF_MIN_BUF_SIZE(obs_dimension, state_dimension));
    matrixf_set(&observation_model, 0u, 0u, 1.0f);
    matrixf_set(&observation_model, 1u, 1u, 1.0f);

    /// 3) Create observation vectorf
    struct Vectorf observation;
    float32_t      observation_buff[VECTORF_MIN_BUF_SIZE(obs_dimension)];
    vectorf_init(&observation, obs_dimension, observation_buff, VECTORF_MIN_BUF_SIZE(obs_dimension));
    vectorf_set(&observation, 0u, 0.1f);

    /// 4) Create observation noise covariance matrix
    struct Matrixf observation_noise_covariance;
    float32_t      observation_noise_covariance_buff[MATRIXF_MIN_BUF_SIZE(obs_dimension, obs_dimension)];
    matrixf_init(&observation_noise_covariance, obs_dimension, obs_dimension, observation_noise_covariance_buff,
                 MATRIXF_MIN_BUF_SIZE(obs_dimension, obs_dimension));
    matrixf_set(&observation_noise_covariance, 0u, 0u, 0.5f);
    matrixf_set(&observation_noise_covariance, 1u, 1u, 0.3f);

    /// Step 2: Generate expected values
    struct Vectorf expected_state;
    float32_t      expected_state_buff[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&expected_state, state_dimension, expected_state_buff, VECTORF_MIN_BUF_SIZE(state_dimension));
    vectorf_set(&expected_state, 0u, 0.10454545f);
    vectorf_set(&expected_state, 1u, 0.0014705872f);
    vectorf_set(&expected_state, 2u, 0.49545455f);
    vectorf_set(&expected_state, 3u, 0.04754902f);

    struct Matrixf expected_covariance;
    float32_t      expected_covariance_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&expected_covariance, state_dimension, state_dimension, expected_covariance_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    matrixf_set(&expected_covariance, 0u, 0u, 0.40909076f);
    matrixf_set(&expected_covariance, 0u, 2u, 0.090909064f);
    matrixf_set(&expected_covariance, 1u, 1u, 0.26470578f);
    matrixf_set(&expected_covariance, 1u, 3u, 0.0588235f);
    matrixf_set(&expected_covariance, 2u, 0u, 0.090909064f);
    matrixf_set(&expected_covariance, 2u, 2u, 1.9090909f);
    matrixf_set(&expected_covariance, 3u, 1u, 0.0588235f);
    matrixf_set(&expected_covariance, 3u, 3u, 1.9019607f);

    /// Step 3: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    /// Step 4: Call the kalman_filterf_predict()
    /// case 1: normal input
    rc = kalman_filterf_correct(&kalman_filter, &observation, &observation_model, &observation_noise_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_TRUE(matrixf_is_equal(&kalman_filter.priori_estimate_covariance, &expected_covariance));
    TEST_ASSERT_TRUE(vectorf_is_equal(&kalman_filter.current_state, &expected_state));

    /// case 2: the input observation_model is invalid
    matrixf_resize(&observation_model, obs_dimension - 1u, state_dimension - 1u);
    rc = kalman_filterf_correct(&kalman_filter, &observation, &observation_model, &observation_noise_covariance);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
    matrixf_resize(&observation_model, obs_dimension, state_dimension);

    /// case 3: the input observation is invalid
    vectorf_resize(&observation, obs_dimension - 1u);
    rc = kalman_filterf_correct(&kalman_filter, &observation, &observation_model, &observation_noise_covariance);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
    vectorf_resize(&observation, obs_dimension);

    /// case 4: the observation_noise_covairance is invalid
    matrixf_resize(&observation_noise_covariance, obs_dimension - 1u, obs_dimension - 1u);
    rc = kalman_filterf_correct(&kalman_filter, &observation, &observation_model, &observation_noise_covariance);
    TEST_ASSERT_EQUAL(RC_NUMERICS_MATRIX_MIXED_SIZE, rc);
    matrixf_resize(&observation_noise_covariance, obs_dimension, obs_dimension);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_is_stable(void)
{
    /* Simulate a car moving on 2D plane, its 2D position is predicted by acceleration and corrected by gps
    measurement.
     * state is [x, y, Vz, Vy], control vector is [ax, ay] can given by accelerometer of the car.
     * gps measurement is [x_gps, y_gps] can given by gnss receiver of the car.
     *
     *  for example, we have a perfect model, which is
     *  x(k) = F(k) * x(k-1) + B(k) * u(k)
     *  z(k) = H(k) * x(k)
     *  where
     * x(k) = [x(k) y(k) Vx(k) Vy(k)]^T
     *
     * F(k) = [1  0  dt  0
     *         0  1  0   dt
     *         0  0  1   0
     *         0  0  0   1]
     *
     * u(k) = [ax ay]^T
     *
     * B(k) = [(dt^2)/2    0
     *       0         (dt^2)/2
     *       t          0
     *       0          t      ]
     *
     * z_gps(k) = [x_gps y_gps]^T
     *
     * H_gps(k) = [1 0 0 0
     *             0 1 0 0]
     *
     * Then add white noise, we get new model
     * x(k) = F(k) * x(k-1) + B(k) * u(k) + w(k)
     * z(k) = H(k) * x(k) + v(k)
     * where
     * w(k) ~ N(0, Q[k])
     * v(k) ~ N(0, R[k])
     *
     * Q(k) = [1, 0, 0, 0;
     *         0, 1, 0, 0;
     *         0, 0, 1, 0;
     *         0, 0, 0, 1] * (0.1*t)^2
     *
     * R_gps(k) = [cov_xx  cov_xy   = [1  0
     *             cov_yx  cov_yy]     0  1]
     */
    const float32_t delta_t           = 0.1f;
    const uint8_t   state_dimension   = 4u;
    const uint8_t   obs_dimension     = 2u;  ///< Observation dimension
    const uint8_t   control_dimension = 2u;

    /// Step 1: Prepare the relative values
    /// 1) Create Kalman filter initial covariance matrixf and state vectorf
    struct Matrixf priori_covariance;
    float32_t      priori_covariance_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, priori_covariance_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));

    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));

    /// 2) Create state transition model matrixf
    struct Matrixf state_transition_model;
    float32_t      state_transition_model_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&state_transition_model, state_dimension, state_dimension, state_transition_model_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    matrixf_set_identity(&state_transition_model);
    matrixf_set(&state_transition_model, 0u, 2u, delta_t);
    matrixf_set(&state_transition_model, 1u, 3u, delta_t);

    /// 3) Create control vectorf and control_input_model matrixf
    struct Vectorf control;
    float32_t      control_buff[VECTORF_MIN_BUF_SIZE(control_dimension)];
    vectorf_init(&control, control_dimension, control_buff, VECTORF_MIN_BUF_SIZE(control_dimension));
    vectorf_set(&control, 0u, 1.0f);
    vectorf_set(&control, 1u, 1.0f);

    struct Matrixf control_input_model;
    float32_t      control_input_model_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, control_dimension)];
    matrixf_init(&control_input_model, state_dimension, control_dimension, control_input_model_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, control_dimension));
    matrixf_set(&control_input_model, 0u, 0u, 0.5f * delta_t * delta_t);
    matrixf_set(&control_input_model, 1u, 1u, 0.5f * delta_t * delta_t);
    matrixf_set(&control_input_model, 2u, 0u, delta_t);
    matrixf_set(&control_input_model, 3u, 1u, delta_t);

    /// 4) Create observation_model matrixf
    struct Matrixf observation_model;
    float32_t      observation_model_buff[MATRIXF_MIN_BUF_SIZE(obs_dimension, state_dimension)];
    matrixf_init(&observation_model, obs_dimension, state_dimension, observation_model_buff,
                 MATRIXF_MIN_BUF_SIZE(obs_dimension, state_dimension));
    matrixf_set(&observation_model, 0u, 0u, 1.0f);
    matrixf_set(&observation_model, 1u, 1u, 1.0f);

    /// 5) Create process noise covariance matrix
    struct Matrixf process_noise_covariance;
    float32_t      process_noise_covariance_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&process_noise_covariance, state_dimension, state_dimension, process_noise_covariance_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    matrixf_set_identity(&process_noise_covariance);
    matrixf_multiply_float32(&process_noise_covariance, 0.1f * delta_t * 0.1f * delta_t, &process_noise_covariance);

    /// 6) Create observation noise covariance matrix
    struct Matrixf observation_noise_covariance;
    float32_t      observation_noise_covariance_buff[MATRIXF_MIN_BUF_SIZE(obs_dimension, obs_dimension)];
    matrixf_init(&observation_noise_covariance, obs_dimension, obs_dimension, observation_noise_covariance_buff,
                 MATRIXF_MIN_BUF_SIZE(obs_dimension, obs_dimension));
    matrixf_set_identity(&observation_noise_covariance);

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_get_serialized_size(void)
{
    uint8_t const state_dimension = 3u;
    /// Step 1: Create Kalman filter initial covariance matrixf and state vectorf
    struct Matrixf priori_covariance;
    float32_t      priori_covariance_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, priori_covariance_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));

    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);

    TEST_ASSERT_EQUAL_UINT32(64u, kalman_filterf_get_serialized_size(&kalman_filter));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_kalman_filterf_serialize_and_deserialize(void)
{
    uint8_t const state_dimension = 3u;
    /// Step 1: Create Kalman filter initial covariance matrixf and state vectorf
    struct Matrixf priori_covariance;
    float32_t      priori_covariance_buff[MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension)];
    matrixf_init(&priori_covariance, state_dimension, state_dimension, priori_covariance_buff,
                 MATRIXF_MIN_BUF_SIZE(state_dimension, state_dimension));
    for (uint8_t i = 0u; i < state_dimension; ++i)
    {
        for (uint8_t j = 0u; j < state_dimension; ++j)
        {
            matrixf_set(&priori_covariance, i, j, 2.1f * i + j + 1.1f);
        }
    }

    struct Vectorf state;
    float32_t      state_buffer[VECTORF_MIN_BUF_SIZE(state_dimension)];
    vectorf_init(&state, state_dimension, state_buffer, VECTORF_MIN_BUF_SIZE(state_dimension));
    for (uint8_t i = 0u; i < state_dimension; ++i)
    {
        vectorf_set(&state, i, 0.3f * i + 0.1f);
    }

    /// Step 2: Initialize the KalmanFilterf struct
    struct KalmanFilterf kalman_filter;
    retcode_t            rc;
    rc = kalman_filterf_init(&kalman_filter, &state, &priori_covariance);
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    kalman_filter.stability       = true;
    kalman_filter.stability_gamma = 2.3f;

    /// Step 3: Create the serialized buffer
    uint8_t        serialized_buff[100u];
    uint16_t const buff_size       = 100u;
    uint16_t const wrong_buff_size = 50u;

    /// Step 4: Run serialize and deserialize
    TEST_ASSERT_EQUAL_UINT32(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             kalman_filterf_serialize(&kalman_filter, serialized_buff, wrong_buff_size));
    TEST_ASSERT_EQUAL_UINT32(64u, kalman_filterf_serialize(&kalman_filter, serialized_buff, buff_size));
    kalman_filterf_reset(&kalman_filter);
    TEST_ASSERT_EQUAL_UINT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             kalman_filterf_deserialize(&kalman_filter, serialized_buff, wrong_buff_size));
    TEST_ASSERT_EQUAL_UINT32(64u, kalman_filterf_deserialize(&kalman_filter, serialized_buff, buff_size));

    /// Step 5: Check every variable
    for (uint8_t i = 0u; i < state_dimension; ++i)
    {
        for (uint8_t j = 0u; j < state_dimension; ++j)
        {
            const float32_t expected_result = 2.1f * i + j + 1.1f;
            float32_t       result;
            matrixf_get(&kalman_filter.priori_estimate_covariance, i, j, &result);
            TEST_ASSERT_EQUAL_FLOAT(expected_result, result);
        }
    }

    for (uint8_t i = 0u; i < state_dimension; ++i)
    {
        const float32_t expected_result = 0.3f * i + 0.1f;
        float32_t       result;
        vectorf_get(&kalman_filter.current_state, i, &result);
        TEST_ASSERT_EQUAL_FLOAT(expected_result, result);
    }

    TEST_ASSERT_EQUAL_FLOAT(2.3f, kalman_filter.stability_gamma);
    TEST_ASSERT_TRUE(kalman_filter.stability);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_kalman_filterf_init);
    RUN_TEST(test_kalman_filterf_is_valid);
    RUN_TEST(test_kalman_filterf_reset);
    RUN_TEST(test_kalman_filterf_set_state_with_covariance);
    RUN_TEST(test_kalman_filterf_set_state);
    RUN_TEST(test_kalman_filterf_set_covariance);
    RUN_TEST(test_kalman_filterf_get_state);
    RUN_TEST(test_kalman_filterf_get_covariance);
    RUN_TEST(test_kalman_filterf_get_state_with_covariance);
    RUN_TEST(test_kalman_filterf_predict);
    RUN_TEST(test_kalman_filterf_correct);
    RUN_TEST(test_kalman_filterf_is_stable);
    RUN_TEST(test_kalman_filterf_get_serialized_size);
    RUN_TEST(test_kalman_filterf_serialize_and_deserialize);
    RUN_TEST(test_kalman_filterf_set_from_kalman_filterf);

    return UNITY_END();
}