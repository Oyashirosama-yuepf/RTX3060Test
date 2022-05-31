/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file kalman_filter.hpp
 * @brief The implementation of template class Kalman filter
 * @author Yuchao Hu (huyuchao@holomatic.com), lichao@holomatic.com
 * @date Sep 19, 2019
 */

#ifndef HOLO_FILTERS_IMPL_KALMAN_FILTER_HPP_
#define HOLO_FILTERS_IMPL_KALMAN_FILTER_HPP_

namespace holo
{
template <typename Scalar, uint8_t Dimension>
KalmanFilterT<Scalar, Dimension>::KalmanFilterT(const VectorType& initial_state,
                                                const MatrixType& initial_state_covariance)
  : current_state_(initial_state)
  , priori_estimate_covariance_(initial_state_covariance)
  , stability_gamma_(static_cast<Scalar>(1.0))
  , stability_(false)
{
}

template <typename Scalar, uint8_t Dimension>
KalmanFilterT<Scalar, Dimension>::~KalmanFilterT() noexcept
{
}

template <typename Scalar, uint8_t Dimension>
void KalmanFilterT<Scalar, Dimension>::Reset()
{
    current_state_.SetZero();
    priori_estimate_covariance_.SetZero();
}

template <typename Scalar, uint8_t Dimension>
void KalmanFilterT<Scalar, Dimension>::SetStateWithCovariance(const VectorType& state, const MatrixType& covariance)
{
    current_state_              = state;
    priori_estimate_covariance_ = covariance;
}

template <typename Scalar, uint8_t Dimension>
void KalmanFilterT<Scalar, Dimension>::SetState(const VectorType& state)
{
    current_state_ = state;
}

template <typename Scalar, uint8_t Dimension>
void KalmanFilterT<Scalar, Dimension>::SetCovariance(const MatrixType& _covariance)
{
    priori_estimate_covariance_ = _covariance;
}

template <typename Scalar, uint8_t Dimension>
const typename KalmanFilterT<Scalar, Dimension>::VectorType& KalmanFilterT<Scalar, Dimension>::GetState() const
{
    return current_state_;
}

template <typename Scalar, uint8_t Dimension>
const typename KalmanFilterT<Scalar, Dimension>::MatrixType& KalmanFilterT<Scalar, Dimension>::GetCovariance() const
{
    return priori_estimate_covariance_;
}

template <typename Scalar, uint8_t Dimension>
void KalmanFilterT<Scalar, Dimension>::GetStateWithCovariance(VectorType& state, MatrixType& covariance) const
{
    state      = current_state_;
    covariance = priori_estimate_covariance_;
}

template <typename Scalar, uint8_t Dimension>
template <uint8_t ControlDim>
void KalmanFilterT<Scalar, Dimension>::Predict(const numerics::MatrixT<Scalar, Dimension, Dimension>&  state_transition_model,
                                               const numerics::MatrixT<Scalar, Dimension, ControlDim>& control_input_model,
                                               const numerics::VectorT<Scalar, ControlDim>&            control,
                                               const numerics::MatrixT<Scalar, Dimension, Dimension>&  process_noise_covariance)
{
    /* predicted (a priori) state estimate, x_j = F * x_i + B * u */
    current_state_ = state_transition_model * current_state_ + control_input_model * control;

    /* predicted(a priori) estimate covariance, P_j = F * P_i * F^T + Q */
    priori_estimate_covariance_ =
        state_transition_model * priori_estimate_covariance_ * state_transition_model.Transpose() +
        process_noise_covariance;
}

template <typename Scalar, uint8_t Dimension>
template <uint8_t ObservationDim>
void KalmanFilterT<Scalar, Dimension>::Correct(
    const numerics::VectorT<Scalar, ObservationDim>&                 observation,
    const numerics::MatrixT<Scalar, ObservationDim, Dimension>&      observation_model,
    const numerics::MatrixT<Scalar, ObservationDim, ObservationDim>& observation_noise_covariance)
{
    /* Step1, innovation or measurement pre-fit residual, y = z - H * x_j */
    const numerics::VectorT<Scalar, ObservationDim> innovation = observation - observation_model * current_state_;

    /* Step2, innovation (or pre-fit residual) covariance, S = H * P * H^T + R */
    const numerics::MatrixT<Scalar, ObservationDim, ObservationDim> innovation_covariance =
        observation_model * priori_estimate_covariance_ * observation_model.Transpose() + observation_noise_covariance;

    /* check if the filter is stable, innovation^T * innovation > gamma * tr{E(innovation * innovation^T)}
     * @todo (lichao@holomatic.com) check correctness of this formula */
    stability_ = (innovation.Transpose() * innovation)(0, 0) > stability_gamma_ * innovation_covariance.GetTrace();

    /* Step3, optimal kalman gain, K = P_j * H^T * S^(-1) */
    const numerics::MatrixT<Scalar, Dimension, ObservationDim> k =
        priori_estimate_covariance_ * observation_model.Transpose() * innovation_covariance.Inverse();

    /* Step4, update posteriori state estimate, x_k = x_j + K * y */
    current_state_ += (k * innovation);

    /* Step5, update posteriori estimate covariance, P_k = (I - K * H ) * P_j */
    priori_estimate_covariance_ -= k * observation_model * priori_estimate_covariance_;
    priori_estimate_covariance_ = Scalar(0.5) * (priori_estimate_covariance_ + priori_estimate_covariance_.Transpose());
}

template <typename Scalar, uint8_t Dimension>
bool_t KalmanFilterT<Scalar, Dimension>::IsStable() const
{
    return stability_;
}

}  // namespace holo
#endif  // HOLO_FILTERS_IMPL_KALMAN_FILTER_HPP_
