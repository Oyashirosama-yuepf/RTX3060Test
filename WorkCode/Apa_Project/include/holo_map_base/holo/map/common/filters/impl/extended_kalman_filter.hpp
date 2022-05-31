/*!
 * \brief Extended Kalman filter
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2018-11-13
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <iostream>

#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace map
{
template <typename T>
ExtendedKalmanFilter<T>::ExtendedKalmanFilter(
    const ::holo::numerics::VectorT<T, -1>& _initial_state,
    const ::holo::numerics::MatrixT<T, -1, -1>& _initial_state_covariance)
  : current_state_(_initial_state)
  , priori_estimate_covariance_(_initial_state_covariance)
{
}

template <typename T>
void ExtendedKalmanFilter<T>::Reset()
{
    current_state_.SetZero();
    priori_estimate_covariance_.SetZero();
}

template <typename T>
void ExtendedKalmanFilter<T>::SetStateWithCovariance(
    const ::holo::numerics::VectorT<T, -1>& _state, const ::holo::numerics::MatrixT<T, -1, -1>& _covariance)
{
    current_state_ = _state;
    priori_estimate_covariance_ = _covariance;
}

template <typename T>
void ExtendedKalmanFilter<T>::SetState(const ::holo::numerics::VectorT<T, -1>& _state)
{
    current_state_ = _state;
}

template <typename T>
void ExtendedKalmanFilter<T>::SetCovariance(
    const ::holo::numerics::MatrixT<T, -1, -1>& _covariance)
{
    priori_estimate_covariance_ = _covariance;
}

template <typename T>
const ::holo::numerics::VectorT<T, -1>& ExtendedKalmanFilter<T>::GetState() const
{
    return current_state_;
}

template <typename T>
const ::holo::numerics::MatrixT<T, -1, -1>& ExtendedKalmanFilter<T>::GetCovariance() const
{
    return priori_estimate_covariance_;
}

template <typename T>
void ExtendedKalmanFilter<T>::GetStateWithCovariance(
    ::holo::numerics::VectorT<T, -1>& _state, ::holo::numerics::MatrixT<T, -1, -1>& _covariance) const
{
    _state = current_state_;
    _covariance = priori_estimate_covariance_;
}

template <typename T>
void ExtendedKalmanFilter<T>::Predict(
    const ::std::function<::holo::numerics::VectorT<T, -1>(const ::holo::numerics::VectorT<T, -1>&,
                                        const ::holo::numerics::VectorT<T, -1>&)>& _func_predict_state,
    const ::std::function<::holo::numerics::MatrixT<T,-1,-1>(
            const ::holo::numerics::VectorT<T, -1>&)>& _func_transit_state,
    const ::holo::numerics::VectorT<T, -1>& _control,
    const ::holo::numerics::MatrixT<T, -1, -1>& _process_noise_covariance)
{
    // predicted (a priori) state estimate = f(state, control)
    current_state_ = _func_predict_state(current_state_, _control);

    // Jacobian of the evolution function
    ::holo::numerics::MatrixT<T, -1, -1> state_transition_model =
        _func_transit_state(current_state_);

    // predicted(a priori) estimate covariance
    priori_estimate_covariance_ = state_transition_model *
                                      priori_estimate_covariance_ *
                                      state_transition_model.Transpose() +
                                  _process_noise_covariance;
}

template <typename T>
void ExtendedKalmanFilter<T>::Correct(
    const ::std::function<::holo::numerics::VectorT<T, -1>(const ::holo::numerics::VectorT<T, -1>&)>&
        _func_predict_observation,
    const ::std::function<::holo::numerics::MatrixT<T,-1,-1>(const ::holo::numerics::VectorT<T, -1>&)>&
        _func_observation_model,
    const ::holo::numerics::VectorT<T, -1>& _observation,
    const ::holo::numerics::MatrixT<T, -1, -1>& _observation_noise_covariance)
{
    // innovation or measurement pre-fit residual
    const ::holo::numerics::VectorT<T, -1> innovation =
        _observation - _func_predict_observation(current_state_);

    // Jacobian of the observation function
    const ::holo::numerics::MatrixT<T, -1, -1> observation_model =
        _func_observation_model(current_state_);

    // innovation (or pre-fit residual) covariance
    const ::holo::numerics::MatrixT<T, -1, -1> innovation_covariance =
        observation_model * priori_estimate_covariance_ *
            observation_model.Transpose() +
        _observation_noise_covariance;

    // optimal kalman gain
    const ::holo::numerics::MatrixT<T, -1, -1> k = priori_estimate_covariance_ *
                                 observation_model.Transpose() *
                                 innovation_covariance.Inverse();

    // update posteriori state estimate
    const ::holo::numerics::VectorT<T, -1> dx = k * innovation;
    current_state_ = current_state_ +  dx;

    // update posteriori estimate covariance
    priori_estimate_covariance_ -=
        k * observation_model * priori_estimate_covariance_;
}

}  // namespace map
}  // namespace holo
