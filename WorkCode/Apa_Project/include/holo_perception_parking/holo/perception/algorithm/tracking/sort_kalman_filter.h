/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sort_kalman_filter.h
 * @brief Kalman filter of SORT tracking algorithm.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-01-13"
 */

#ifndef HOLO_PERCEPTION_TRACKING_SORT_KALMAN_FILTER_H_
#define HOLO_PERCEPTION_TRACKING_SORT_KALMAN_FILTER_H_

#include <holo/log/hololog.h>
#include <holo/perception/common/box_object.h>

#include <cmath>

namespace holo
{
namespace perception
{
/**
 * @addtogroup tracking
 *
 * @{
 */

/**
 * @brief Kalman filter of sort tracking algorithm
 * @details
 * state [x, y, s, r, vx, vy, vs]
 * measurement [x, y, s, r]
 * where:
 * x : x coordinate of the center of the bounding box
 * y : y coordinate of the center of the bounding box
 * s : area of the bounding box
 * r : aspect ratio of the bounding box (width/height)
 * vx : velocity of x
 * vy : velocity of y
 * vs : velocity of s
 * here, 'velocity' means difference from time t to time t-1
 *
 *
 * @ref https://github.com/abewley/sort
 * @tparam T data type
 */
template <typename T>
class SORTKalmanFilterT
{
public:
    using Box2Type = Box2DT<T>;

    /**
     * @brief Construct a new SORTKalmanFilterT object
     *
     * @param bbox the bounding box
     */
    explicit SORTKalmanFilterT(const Box2Type& bbox);

    /**
     * @brief Kalman filter correct
     * @details pipline
     * 1. convert bbox to measurement
     * 2. kalman filter correct using the measurement
     *
     * @param bbox the bounding box
     */
    void Update(const Box2Type& bbox);

    /**
     * @brief Kalman filter predict
     * @details pipline
     * 1. kalman filter predict
     * 2. convert kalman filter state to bbox
     * 3. return the bbox
     *
     * @param[out] bbox the predicted bounding box
     *
     * @return bool_t true if predict a valid bbox else false
     */
    bool_t Predict(Box2Type& bbox);

    /**
     * @brief Kalman filter correct with time delta
     *
     * @param time_delta duration time from current timetamp to last timestamp
     * @param bbox bbox to measurement
     */
    void Update(const T time_delta, const Box2Type& bbox);

    /**
     * @brief Kalman filter predict
     *
     * @param time_delta duration time from current timetamp to last timestamp
     * @param[out] bbox the predicted bounding box
     *
     * @return bool_t true if predict a valid bbox else false
     */
    bool_t Predict(const T time_delta, Box2Type& bbox);

    /**
     * @brief Get the bbox of current state
     *
     * @param[out] bbox the bbox
     *
     * @return bool_t if get a valid bbox else false
     */
    bool_t GetBBoxOfState(Box2Type& bbox)
    {
        return convertStateToBBox(state_, bbox);
    }

private:
    /**
     * @brief initialize the kalman filter
     * @details pipline
     * 1. initialize transition matrix
     * 2. initialize measurement matrix
     * 3. initialize prior covariance
     * 4. initialize process noise covariance
     * 5. initialize measurement noise covariance
     */
    void initialize();

    /**
     * @brief initialize transition matrix
     * @details
     * ```
     *       1.,      0.,      0.,      0.,      1.,      0.,      0.
     *       0.,      1.,      0.,      0.,      0.,      1.,      0.
     *       0.,      0.,      1.,      0.,      0.,      0.,      1.
     *       0.,      0.,      0.,      1.,      0.,      0.,      0.
     *       0.,      0.,      0.,      0.,      1.,      0.,      0.
     *       0.,      0.,      0.,      0.,      0.,      1.,      0.
     *       0.,      0.,      0.,      0.,      0.,      0.,      1.
     * ```
     */
    void initTransitionMatrix();

    /**
     * @brief initialize measurement matrix
     * @details
     * ```
     *       1.,      0.,      0.,      0.,      0.,      0.,      0.
     *       0.,      1.,      0.,      0.,      0.,      0.,      0.
     *       0.,      0.,      1.,      0.,      0.,      0.,      0.
     *       0.,      0.,      0.,      1.,      0.,      0.,      0.
     * ```
     */
    void initMeasurementMatrix();

    /**
     * @brief initialize prior estimated covariance
     * @details
     * ```
     *      10.,      0.,      0.,      0.,      0.,      0.,      0.
     *       0.,     10.,      0.,      0.,      0.,      0.,      0.
     *       0.,      0.,     10.,      0.,      0.,      0.,      0.
     *       0.,      0.,      0.,     10.,      0.,      0.,      0.
     *       0.,      0.,      0.,      0.,  10000.,      0.,      0.
     *       0.,      0.,      0.,      0.,      0.,  10000.,      0.
     *       0.,      0.,      0.,      0.,      0.,      0.,  10000.
     * ```
     */
    void initPriorCovariance();

    /**
     * @brief initialize process noise covariance
     * @details
     * ```
     *       1.,      0.,      0.,      0.,      0.,      0.,      0.
     *       0.,      1.,      0.,      0.,      0.,      0.,      0.
     *       0.,      0.,      1.,      0.,      0.,      0.,      0.
     *       0.,      0.,      0.,      1.,      0.,      0.,      0.
     *       0.,      0.,      0.,      0.,    0.01,      0.,      0.
     *       0.,      0.,      0.,      0.,      0.,    0.01,      0.
     *       0.,      0.,      0.,      0.,      0.,      0.,   0.0001
     * ```
     */
    void initProcessNoiseCovariance();

    /**
     * @brief initialize measurement noise covaraince
     * @details
     * ```
     *       1.,      0.,      0.,      0.
     *       0.,      1.,      0.,      0.
     *       0.,      0.,     10.,      0.
     *       0.,      0.,      0.,     10.
     * ```
     */
    void initMeasurementNoiseCovariance();

    /**
     * @brief Convert state to bounding box
     *
     * @param state the kalman filter state
     * @param[out] bbox the bounding box
     *
     * @return bool_t true if convertion success else false
     */
    bool_t convertStateToBBox(const holo::numerics::VectorXT<T>& state, Box2Type& bbox);

    /**
     * @brief Convert bounding box to measurement
     *
     * @param bbox the bounding box
     * @param[out] measure the kalman filter measurement
     */
    void convertBBoxToMeasurement(const Box2Type& bbox, holo::numerics::VectorXT<T>& measure);

private:
    holo::numerics::MatrixXT<T> transition_matrix_;
    holo::numerics::MatrixXT<T> measurement_matrix_;
    holo::numerics::MatrixXT<T> process_noise_cov_;
    holo::numerics::MatrixXT<T> measurement_noise_cov_;
    holo::numerics::MatrixXT<T> prior_cov_;
    holo::numerics::VectorXT<T> state_;

    static const uint8_t STATE_DIM   = 7U;
    static const uint8_t MEASURE_DIM = 4U;
};

/**
 * @}
 *
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_SORT_KALMAN_FILTER_H_
