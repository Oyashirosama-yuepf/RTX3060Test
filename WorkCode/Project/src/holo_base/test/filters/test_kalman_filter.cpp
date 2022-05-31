/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_kalman_filter.cpp
 * @brief unit test for template class Kalman filter
 * @author Yuchao Hu (huyuchao@holomatic.com), lichao@holomatic.com
 * @date Sep 23, 2019
 */

#include <complex>
#include <random>

#include <holo/log/hololog.h>
#include <gtest/gtest.h>

#include <holo/filters/kalman_filter.h>
using holo::numerics::Vector4f;
using holo::numerics::Vector2f;
using holo::numerics::Matrix4f;
using holo::numerics::Matrix2f;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, DefaultCase)
{
    /* Create a KalmanFilter */
    ::holo::KalmanFilterT<holo::float32_t, 4> filter;

    /* Test Constructor */
    ASSERT_TRUE(Vector4f::Zero() == filter.GetState());
    ASSERT_TRUE(Matrix4f::Identity() == filter.GetCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, NormalCase)
{
    /* Generate expected values */
    const Vector4f expected_state(8.0f, 6.0f, 12.0f, 2.3f);
    const Matrix4f expected_state_covariance(1.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                                                     0.1f, 0.0f, 0.0f, 0.2f, 1.0f);

    /* Create a KalmanFilter */
    ::holo::KalmanFilterT<holo::float32_t, 4> filter(expected_state, expected_state_covariance);

    /* Test Constructor */
    ASSERT_TRUE(expected_state == filter.GetState());
    ASSERT_TRUE(expected_state_covariance == filter.GetCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ResetTest, NormalCase)
{
    /* Generate init values */
    const Vector4f init_state(8.0f, 6.0f, 12.0f, 2.3f);
    const Matrix4f init_state_covariance(1.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.1f,
                                                 0.0f, 0.0f, 0.2f, 1.0f);

    /* Create a KalmanFilter */
    ::holo::KalmanFilterT<holo::float32_t, 4> filter(init_state, init_state_covariance);

    /* Test Reset function */
    filter.Reset();
    ASSERT_TRUE(Vector4f::Zero() == filter.GetState());
    ASSERT_TRUE(Matrix4f::Zero() == filter.GetCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetStateTest, NormalCase)
{
    /* Generate init values */
    const Vector4f init_state(8.0f, 6.0f, 12.0f, 2.3f);
    const Matrix4f init_state_covariance(1.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.1f,
                                                 0.0f, 0.0f, 0.2f, 1.0f);

    /* Create a KalmanFilter */
    ::holo::KalmanFilterT<holo::float32_t, 4> filter(init_state, init_state_covariance);

    /* Generate expected value */
    const Vector4f expected_state(1.0f, 2.0f, 5.0f, 4.0f);

    /* Test Reset function */
    filter.SetState(expected_state);
    ASSERT_TRUE(expected_state == filter.GetState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetCovarianceTest, NormalCase)
{
    /* Generate init values */
    const Vector4f init_state(8.0f, 6.0f, 12.0f, 2.3f);
    const Matrix4f init_state_covariance(1.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.1f,
                                                 0.0f, 0.0f, 0.2f, 1.0f);

    /* Create a KalmanFilter */
    ::holo::KalmanFilterT<holo::float32_t, 4> filter(init_state, init_state_covariance);

    /* Generate expected value */
    const Matrix4f expected_state_covariance = Matrix4f::Identity();

    /* Test Reset function */
    filter.SetCovariance(expected_state_covariance);
    ASSERT_TRUE(expected_state_covariance == filter.GetCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetStateWithCovarianceTest, NormalCase)
{
    /* Generate init values */
    const Vector4f init_state(8.0f, 6.0f, 12.0f, 2.3f);
    const Matrix4f init_state_covariance(1.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.1f,
                                                 0.0f, 0.0f, 0.2f, 1.0f);

    /* Create a KalmanFilter */
    ::holo::KalmanFilterT<holo::float32_t, 4> filter(init_state, init_state_covariance);

    /* Generate expected value */
    const Vector4f expected_state(1.0f, 2.0f, 5.0f, 4.0f);
    const Matrix4f expected_state_covariance = Matrix4f::Identity();

    /* Test Reset function */
    filter.SetStateWithCovariance(expected_state, expected_state_covariance);
    Vector4f actual_state;
    Matrix4f actual_state_covariance;
    filter.GetStateWithCovariance(actual_state, actual_state_covariance);
    ASSERT_TRUE(expected_state == actual_state);
    ASSERT_TRUE(expected_state_covariance == actual_state_covariance);
    ASSERT_TRUE(filter.GetCovariance().IsSymmetric());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PredictionTest, NormalCase)
{
    /* Generate init values */
    const Vector4f init_state = Vector4f::Zero();
    const Matrix4f init_state_covariance(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                                 0.0f, 0.0f, 0.0f, 1.0f);

    /* Create a KalmanFilter */
    ::holo::KalmanFilterT<holo::float32_t, 4> filter(init_state, init_state_covariance);

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
    const ::holo::float32_t delta_t = 0.5;
    const Matrix4f  state_transition_model(1.0f, 0.0f, delta_t, 0.0f, 0.0f, 1.0f, 0.0f, delta_t, 0.0f, 0.0f,
                                                  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    const holo::numerics::Vector2f  control(1.0f, 0.1f);
    holo::numerics::MatrixT< ::holo::float32_t, 4, 2> control_input_model;

    control_input_model(0, 0) = 0.5f * (holo::float32_t)std::pow(delta_t, 2);
    control_input_model(0, 1) = 0.0f;
    control_input_model(1, 0) = 0.0f;
    control_input_model(1, 1) = 0.5f * (holo::float32_t)std::pow(delta_t, 2);
    control_input_model(2, 0) = delta_t;
    control_input_model(2, 1) = 0.0f;
    control_input_model(3, 0) = 0.0f;
    control_input_model(3, 1) = delta_t;

    const Matrix4f process_noise_covariance = Matrix4f::Identity();

    /* Generate expected values */
    const Vector4f expected_state(0.125f, 0.0125f, 0.5f, 0.05f);
    const Matrix4f expected_covariance(2.25f, 0.0f, 0.5f, 0.0f, 0.0f, 2.25f, 0.0f, 0.5f, 0.5f, 0.0f, 2.0f, 0.0f,
                                               0.0f, 0.5f, 0.0f, 2.0f);

    /* Test Prediction function */
    filter.Predict<2>(state_transition_model, control_input_model, control, process_noise_covariance);
    ASSERT_TRUE(expected_state == filter.GetState());
    ASSERT_TRUE(expected_covariance == filter.GetCovariance());
    ASSERT_TRUE(filter.GetCovariance().IsSymmetric());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CorrectionTest, NormalCase)
{
    /* Generate init values */
    const Vector4f init_state(0.125f, 0.0125f, 0.5f, 0.05f);
    const Matrix4f init_state_covariance(2.25f, 0.0f, 0.5f, 0.0f, 0.0f, 2.25f, 0.0f, 0.5f, 0.5f, 0.0f, 2.0f,
                                                 0.0f, 0.0f, 0.5f, 0.0f, 2.0f);

    /* Create a KalmanFilter */
    ::holo::KalmanFilterT<holo::float32_t, 4> filter(init_state, init_state_covariance);

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
     * */
    const holo::numerics::Vector2f                    observation(0.1f, 0.0f);
    holo::numerics::MatrixT< ::holo::float32_t, 2, 4> observation_model;
    observation_model(0, 0) = 1.0f;
    observation_model(0, 1) = 0.0f;
    observation_model(0, 2) = 0.0f;
    observation_model(0, 3) = 0.0f;
    observation_model(1, 0) = 0.0f;
    observation_model(1, 1) = 1.0f;
    observation_model(1, 2) = 0.0f;
    observation_model(1, 3) = 0.0f;
    const holo::numerics::Matrix2f observation_noise_covariance(0.5f, 0.0f, 0.0f, 0.3f);

    /* Generate expected values */
    const Vector4f expected_state(0.10454545f, 0.0014705872f, 0.49545455f, 0.04754902f);
    const Matrix4f expected_covariance(0.40909076f, 0.0f, 0.090909064f, 0.0f, 0.0f, 0.26470578f, 0.0f,
                                               0.0588235f, 0.090909064f, 0.0f, 1.9090909f, 0.0f, 0.0f, 0.0588235f, 0.0f,
                                               1.9019607f);

    /* Test Correction function */
    filter.Correct<2>(observation, observation_model, observation_noise_covariance);
    ASSERT_TRUE(expected_state == filter.GetState());
    /* @todo (lichao@holomatic.com) use is_approx instead */
    EXPECT_FLOAT_EQ(expected_covariance(0, 0), filter.GetCovariance()(0, 0));
    EXPECT_FLOAT_EQ(expected_covariance(0, 1), filter.GetCovariance()(0, 1));
    EXPECT_FLOAT_EQ(expected_covariance(0, 2), filter.GetCovariance()(0, 2));
    EXPECT_FLOAT_EQ(expected_covariance(0, 3), filter.GetCovariance()(0, 3));
    EXPECT_FLOAT_EQ(expected_covariance(1, 0), filter.GetCovariance()(1, 0));
    EXPECT_FLOAT_EQ(expected_covariance(1, 1), filter.GetCovariance()(1, 1));
    EXPECT_FLOAT_EQ(expected_covariance(1, 2), filter.GetCovariance()(1, 2));
    EXPECT_FLOAT_EQ(expected_covariance(1, 3), filter.GetCovariance()(1, 3));
    EXPECT_FLOAT_EQ(expected_covariance(2, 0), filter.GetCovariance()(2, 0));
    EXPECT_FLOAT_EQ(expected_covariance(2, 1), filter.GetCovariance()(2, 1));
    EXPECT_FLOAT_EQ(expected_covariance(2, 2), filter.GetCovariance()(2, 2));
    EXPECT_FLOAT_EQ(expected_covariance(2, 3), filter.GetCovariance()(2, 3));
    EXPECT_FLOAT_EQ(expected_covariance(3, 0), filter.GetCovariance()(3, 0));
    EXPECT_FLOAT_EQ(expected_covariance(3, 1), filter.GetCovariance()(3, 1));
    EXPECT_FLOAT_EQ(expected_covariance(3, 2), filter.GetCovariance()(3, 2));
    EXPECT_FLOAT_EQ(expected_covariance(3, 3), filter.GetCovariance()(3, 3));
    ASSERT_TRUE(filter.GetCovariance().IsSymmetric());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FilterStabilityTest, NormalCase)
{
    /* Simulate a car moving on 2D plane, its 2D position is predicted by acceleration and corrected by gps measurement.
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

    typedef ::holo::float32_t Scalar;
    const Scalar              t(0.1);

    const Matrix4f        state_transition_model(1, 0, t, 0, 0, 1, 0, t, 0, 0, 1, 0, 0, 0, 0, 1);
    holo::numerics::MatrixT<Scalar, 4, 2> control_input_model;
    control_input_model(0, 0) = 0.5f * t * t;
    control_input_model(0, 1) = 0.0f;
    control_input_model(1, 0) = 0.0f;
    control_input_model(1, 1) = 0.5f * t * t;
    control_input_model(2, 0) = t;
    control_input_model(2, 1) = 0.0f;
    control_input_model(3, 0) = 0.0f;
    control_input_model(3, 1) = t;
    const holo::numerics::Vector2f        control(1.0f, 1.0f);
    holo::numerics::MatrixT<Scalar, 2, 4> observation_model;
    observation_model(0, 0) = 1.0f;
    observation_model(0, 1) = 0.0f;
    observation_model(0, 2) = 0.0f;
    observation_model(0, 3) = 0.0f;
    observation_model(1, 0) = 0.0f;
    observation_model(1, 1) = 1.0f;
    observation_model(1, 2) = 0.0f;
    observation_model(1, 3) = 0.0f;

    const Vector4f initial_state(0.0f, 0.0f, 0.0f, 0.0f);
    const Matrix4f initial_state_covariance = Matrix4f::Zero();

    ::holo::KalmanFilterT<holo::float32_t, 4> kalman_filter(initial_state, initial_state_covariance);

    const Matrix4f process_noise_covariance =
        (holo::float32_t)::std::pow((0.1 * t), 2) * Matrix4f::Identity();
    const holo::numerics::Matrix2f observation_noise_covariance = holo::numerics::Matrix2f::Identity();

    Vector4f state = initial_state;

    ::std::random_device               rd;
    ::std::mt19937                     mt(rd());
    ::std::normal_distribution<Scalar> observation_noise_distribution(0, 1);
    ::std::normal_distribution<Scalar> process_noise_distribution(0, ::std::pow((0.1 * t), 2));
    for (int i = 0; i < 1000; ++i)
    {
        /* perfect transition model :*/
        state = state_transition_model * state + control_input_model * control;

        /* add gaussian white noise */
        const Vector4f transition_noise(process_noise_distribution(mt), process_noise_distribution(mt),
                                                process_noise_distribution(mt), process_noise_distribution(mt));
        const Vector4f state_with_noise = state + transition_noise;

        state = state_with_noise;

        kalman_filter.Predict<2>(state_transition_model, control_input_model, control, process_noise_covariance);
        if (i % 10 == 0)
        {
            /* perfect observation model */
            const holo::numerics::Vector2f observation = observation_model * state;

            /* add gaussian white noise */
            const holo::numerics::Vector2f observation_noise(observation_noise_distribution(mt),
                                                     observation_noise_distribution(mt));
            const holo::numerics::Vector2f observation_with_noise = observation + observation_noise;

            kalman_filter.Correct<2>(observation_with_noise, observation_model, observation_noise_covariance);
            ::std::cout << "** do correct **" << ::std::endl;
        }

        ::std::cout << "transition noise:" << ::std::endl;
        ::std::cout << transition_noise << ::std::endl;
        ::std::cout << "real state:" << ::std::endl;
        ::std::cout << state << ::std::endl;
        ::std::cout << "kalman filter state:" << ::std::endl;
        ::std::cout << kalman_filter.GetState() << ::std::endl;
        ::std::cout << "kalman filter covariance:" << ::std::endl;
        ::std::cout << kalman_filter.GetCovariance() << ::std::endl;
        ::std::cout << "==============" << ::std::endl;
    }
}

TEST(ConstructorTest, IsStable)
{
    /* Create a KalmanFilter */
    ::holo::KalmanFilterT<holo::float32_t, 4> filter;

    EXPECT_FALSE(filter.IsStable());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
