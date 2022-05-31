/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file constant_velocity_kalman_filter.h
 * @brief This header file defines Kalman Filter using constant velocity motion model.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-07-05"
 */

#ifndef HOLO_PERCEPTION_UTILS_CONSTANT_VELOCITY_KALMAN_FILTER_H_
#define HOLO_PERCEPTION_UTILS_CONSTANT_VELOCITY_KALMAN_FILTER_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/filters/kalman_filter.h>
#include <holo/filters/impl/kalman_filter.hpp>

namespace holo
{
namespace perception
{
/**
 * @brief kalman filter using constant velocity motion model
 *
 */
class ConstantVelocityKalmanFilter
{
public:
    static const uint8_t STATE_DIM = 6U;
    static const uint8_t CTRL_DIM  = 1U;
    static const uint8_t OBSRV_DIM = 6U;

public:
    using Scalar            = float32_t;
    using StateVector       = numerics::VectorT<Scalar, STATE_DIM>;
    using TransitionMatrix  = numerics::MatrixT<Scalar, STATE_DIM, STATE_DIM>;
    using ProcessNoiseCov   = TransitionMatrix;
    using ControlVector     = numerics::VectorT<Scalar, CTRL_DIM>;
    using ControlMatrix     = numerics::MatrixT<Scalar, STATE_DIM, CTRL_DIM>;
    using ObservationVector = numerics::VectorT<Scalar, OBSRV_DIM>;
    using ObservationMatrix = numerics::MatrixT<Scalar, OBSRV_DIM, STATE_DIM>;
    using ObserveNoiseCov   = numerics::MatrixT<Scalar, OBSRV_DIM, OBSRV_DIM>;
    using KalmanFilter      = KalmanFilterT<Scalar, STATE_DIM>;
    using KalmanFilterPtr   = std::shared_ptr<KalmanFilter>;
    using Timestamp         = holo::common::details::Timestamp;

    /**
     * @brief Construct a new Constant Velocity Kalman Filter object
     *
     * @param timestmap timestamp
     * @param x position x
     * @param vx velocity x
     * @param ax acceleration x
     * @param y position y
     * @param vy velocity y
     * @param ay acceleration y
     */
    ConstantVelocityKalmanFilter(Timestamp const& timestamp, Scalar const x, Scalar const vx, Scalar const ax,
                                 Scalar const y, Scalar const vy, Scalar const ay);

    /**
     * @brief predict state at current timestamp
     *
     * @param current_timestamp current timestamp
     * @return StateVector const& predicted state
     */
    StateVector const& Predict(Timestamp const& current_timestamp);

    /**
     * @brief update state
     *
     * @param x position x
     * @param vx velocity x
     * @param ax acceleration x
     * @param y position y
     * @param vy velocity y
     * @param ay acceleration y
     * @return StateVector const& updated state
     */
    StateVector const& Update(Scalar const x, Scalar const vx, Scalar const ax, Scalar const y, Scalar const vy,
                              Scalar const ay);

    /**
     * @brief Get the State vector
     *
     * @return StateVector const& state vector
     */
    StateVector const& GetState() const
    {
        return kf_->GetState();
    }

    /**
     * @brief Get the Transition Matrix
     *
     * @return TransitionMatrix& transition_matrix_
     */
    TransitionMatrix& GetTransitionMatrix()
    {
        return transition_matrix_;
    }

    /**
     * @brief Get the Control Matrix
     *
     * @return ControlMatrix& control_matrix_
     */
    ControlMatrix& GetControlMatrix()
    {
        return control_matrix_;
    }

    /**
     * @brief Get the Process Noise Cov
     *
     * @return TransitionMatrix& process_noise_cov_
     */
    TransitionMatrix& GetProcessNoiseCov()
    {
        return process_noise_cov_;
    }

    /**
     * @brief Get the Observation Matrix
     *
     * @return ObservationMatrix& observation_matrix_
     */
    ObservationMatrix& GetObservationMatrix()
    {
        return observation_matrix_;
    }

    /**
     * @brief Get the Observe Noise Cov
     *
     * @return ObserveNoiseCov& observe_noise_cov_
     */
    ObserveNoiseCov& GetObserveNoiseCov()
    {
        return observe_noise_cov_;
    }

private:
    Timestamp         timestamp_;
    TransitionMatrix  transition_matrix_;
    ControlVector     control_;
    ControlMatrix     control_matrix_;
    TransitionMatrix  process_noise_cov_;
    ObservationVector observation_;
    ObservationMatrix observation_matrix_;
    ObserveNoiseCov   observe_noise_cov_;
    KalmanFilterPtr   kf_;
};

}  // namespace perception
}  // namespace holo

#endif
