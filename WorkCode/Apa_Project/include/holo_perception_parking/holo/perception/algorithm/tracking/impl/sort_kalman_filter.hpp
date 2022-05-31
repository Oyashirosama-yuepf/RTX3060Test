/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sort_kalman_filter.hpp
 * @brief This header file defines SORTKalmanFilterT.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-01-13"
 */

#ifndef HOLO_PERCEPTION_TRACKING_SORT_KALMAN_FILTER_HPP_
#define HOLO_PERCEPTION_TRACKING_SORT_KALMAN_FILTER_HPP_

#include <holo/filters/kalman_filter.h>
#include <holo/perception/algorithm/tracking/sort_kalman_filter.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
SORTKalmanFilterT<T>::SORTKalmanFilterT(const Box2Type& bbox)
{
    // initialize matrices
    initialize();
    // initialize state vector
    holo::numerics::VectorXT<T> measurement;
    convertBBoxToMeasurement(bbox, measurement);
    state_.Resize(STATE_DIM);
    state_.SetZero();
    for (uint8_t i = 0U; i < MEASURE_DIM; ++i)
    {
        state_(i) = measurement(i);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SORTKalmanFilterT<T>::Update(const Box2Type& bbox)
{
    // convert bbox to measurement
    holo::numerics::VectorXT<T> measurement;
    convertBBoxToMeasurement(bbox, measurement);

    // kalman filter correct
    auto innovation     = measurement - measurement_matrix_ * state_;
    auto innovation_cov = measurement_matrix_ * prior_cov_ * measurement_matrix_.Transpose() + measurement_noise_cov_;
    holo::numerics::MatrixT<T, MEASURE_DIM, MEASURE_DIM> tmp;
    for (uint8_t i = 0U; i < MEASURE_DIM; ++i)
    {
        for (uint8_t j = 0U; j < MEASURE_DIM; ++j)
        {
            tmp(i, j) = innovation_cov(i, j);
        }
    }
    auto                        tmp_inv = tmp.Inverse();
    holo::numerics::MatrixXT<T> innovation_cov_inv;
    innovation_cov_inv.Resize(MEASURE_DIM, MEASURE_DIM);
    for (uint8_t i = 0U; i < MEASURE_DIM; ++i)
    {
        for (uint8_t j = 0U; j < MEASURE_DIM; ++j)
        {
            innovation_cov_inv(i, j) = tmp_inv(i, j);
        }
    }
    auto K = prior_cov_ * measurement_matrix_.Transpose() * innovation_cov_inv;
    state_ += K * innovation;
    prior_cov_ -= K * measurement_matrix_ * prior_cov_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t SORTKalmanFilterT<T>::Predict(Box2Type& bbox)
{
    // kalman filter predict
    state_     = transition_matrix_ * state_;
    prior_cov_ = transition_matrix_ * prior_cov_ * transition_matrix_.Transpose() + process_noise_cov_;
    // converto to bounding box
    return convertStateToBBox(state_, bbox);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SORTKalmanFilterT<T>::Update(const T time_delta, const Box2Type& bbox)
{
    // modify transition matrix
    for (uint8_t i = 0U; i < 3U; ++i)
    {
        transition_matrix_(i, i + 4U) = time_delta;
    }
    Update(bbox);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t SORTKalmanFilterT<T>::Predict(const T time_delta, Box2Type& bbox)
{
    // modify transition matrix
    for (uint8_t i = 0U; i < 3U; ++i)
    {
        transition_matrix_(i, i + 4U) = time_delta;
    }
    return Predict(bbox);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SORTKalmanFilterT<T>::initialize()
{
    initTransitionMatrix();
    initMeasurementMatrix();
    initPriorCovariance();
    initProcessNoiseCovariance();
    initMeasurementNoiseCovariance();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SORTKalmanFilterT<T>::initTransitionMatrix()
{
    transition_matrix_.Resize(STATE_DIM, STATE_DIM);
    transition_matrix_.SetZero();
    for (uint8_t i = 0U; i < STATE_DIM; ++i)
    {
        transition_matrix_(i, i) = static_cast<T>(1.0);
        if (i < 3U)
        {
            transition_matrix_(i, i + 4U) = static_cast<T>(1.0);  // velocity of this component
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SORTKalmanFilterT<T>::initMeasurementMatrix()
{
    measurement_matrix_.Resize(MEASURE_DIM, STATE_DIM);
    measurement_matrix_.SetZero();
    for (uint8_t i = 0U; i < MEASURE_DIM; ++i)
    {
        measurement_matrix_(i, i) = static_cast<T>(1.0);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SORTKalmanFilterT<T>::initPriorCovariance()
{
    prior_cov_.Resize(STATE_DIM, STATE_DIM);
    prior_cov_.SetZero();
    for (uint8_t i = 0U; i < STATE_DIM; ++i)
    {
        if (i < 4U)
        {
            prior_cov_(i, i) = static_cast<T>(10.0);
        }
        else
        {
            // give high uncertainty to the unobservable initial velocities
            prior_cov_(i, i) = static_cast<T>(10000.0);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SORTKalmanFilterT<T>::initProcessNoiseCovariance()
{
    process_noise_cov_.Resize(STATE_DIM, STATE_DIM);
    process_noise_cov_.SetZero();
    for (uint8_t i = 0; i < STATE_DIM; ++i)
    {
        if (i < 4U)
        {
            process_noise_cov_(i, i) = static_cast<T>(1.0);
        }
        else if (i < 6U)
        {
            process_noise_cov_(i, i) = static_cast<T>(0.01);
        }
        else
        {
            process_noise_cov_(i, i) = static_cast<T>(0.0001);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SORTKalmanFilterT<T>::initMeasurementNoiseCovariance()
{
    measurement_noise_cov_.Resize(MEASURE_DIM, MEASURE_DIM);
    measurement_noise_cov_.SetZero();
    for (uint8_t i = 0; i < MEASURE_DIM; ++i)
    {
        if (i < 2U)
        {
            measurement_noise_cov_(i, i) = static_cast<T>(1.0);
        }
        else
        {
            measurement_noise_cov_(i, i) = static_cast<T>(10.0);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t SORTKalmanFilterT<T>::convertStateToBBox(const holo::numerics::VectorXT<T>& state, Box2Type& bbox)
{
    T x            = state(0);
    T y            = state(1);
    T s            = state(2);
    T r            = state(3);
    T width_square = s * r;
    // negative value also invalid
    if (width_square < EpsilonT<T>::value)
    {
        return false;
    }
    // if width_square is too small, sqrt make it bigger, no need to check again.
    T width  = std::sqrt(width_square);
    T height = s / width;
    // if box is invalid the constructor will throw exception
    try
    {
        bbox = Box2DT<T>(x - width * static_cast<T>(0.5), y - height * static_cast<T>(0.5), width, height);
    }
    catch (const std::exception& e)
    {
        LOG(WARNING) << "SORT kalman filter predict a invalid bbox: " << e.what();
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SORTKalmanFilterT<T>::convertBBoxToMeasurement(const Box2Type& bbox, holo::numerics::VectorXT<T>& measurement)
{
    holo::geometry::Point2T<T> center_point = bbox.GetCenterPoint();

    T height = bbox.GetHeight();
    T width  = bbox.GetWidth();

    T r = width / height;
    T s = width * height;

    measurement.Resize(MEASURE_DIM);
    measurement(0) = center_point.GetX();
    measurement(1) = center_point.GetY();
    measurement(2) = s;
    measurement(3) = r;
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_SORT_KALMAN_FILTER_HPP_
