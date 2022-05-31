/*!
 * \brief Kalman filter
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2018-01-15
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <numeric>
#include <cmath>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace map
{
template <typename T>
KalmanFilter<T>::KalmanFilter(
    const ::holo::numerics::VectorT<T, -1>& _initial_state,
    const ::holo::numerics::MatrixT<T, -1, -1>& _initial_state_covariance)
  : current_state_(_initial_state)
  , priori_estimate_covariance_(_initial_state_covariance)
  , max_innovation_queue_(50)
  , outlier_gamma_(1.0)
  , divergence_threshold_(3.0)
  , is_outlier_(false)
  , is_divergent_(false)
  , is_divergent_valid_(false)
{
}

template <typename T>
void KalmanFilter<T>::Reset()
{
    current_state_.SetZero();
    priori_estimate_covariance_.SetZero();
}

template <typename T>
void KalmanFilter<T>::SetStateWithCovariance(
    const ::holo::numerics::VectorT<T, -1>& _state, const ::holo::numerics::MatrixT<T, -1, -1>& _covariance)
{
    current_state_              = _state;
    priori_estimate_covariance_ = _covariance;
}

template <typename T>
void KalmanFilter<T>::SetState(const ::holo::numerics::VectorT<T, -1>& _state)
{
    current_state_ = _state;
}

template <typename T>
void KalmanFilter<T>::SetCovariance(const ::holo::numerics::MatrixT<T, -1, -1>& _covariance)
{
    priori_estimate_covariance_ = _covariance;
}

template <typename T>
const ::holo::numerics::VectorT<T, -1>& KalmanFilter<T>::GetState() const
{
    return current_state_;
}

template <typename T>
const ::holo::numerics::MatrixT<T, -1, -1>& KalmanFilter<T>::GetCovariance() const
{
    return priori_estimate_covariance_;
}

template <typename T>
void KalmanFilter<T>::GetStateWithCovariance(
    ::holo::numerics::VectorT<T, -1>& _state, ::holo::numerics::MatrixT<T, -1, -1>& _covariance) const
{
    _state      = current_state_;
    _covariance = priori_estimate_covariance_;
}

template <typename T>
void KalmanFilter<T>::SetOutlierGamma(const T _outlier_gamma)
{
    outlier_gamma_ = _outlier_gamma;
}

template <typename T>
T KalmanFilter<T>::GetOutlierGamma() const
{
    return outlier_gamma_;
}

template <typename T>
void KalmanFilter<T>::SetDivergenceThreshold(const T _divergence_threshold)
{
    divergence_threshold_ = _divergence_threshold;
}

template <typename T>
T KalmanFilter<T>::GetDivergenceThreshold() const
{
    return divergence_threshold_;
}

template <typename T>
void KalmanFilter<T>::Predict(const ::holo::numerics::MatrixT<T, -1, -1>& _state_transition_model,
                              const ::holo::numerics::MatrixT<T, -1, -1>& _control_input_model,
                              const ::holo::numerics::VectorT<T, -1>& _control,
                              const ::holo::numerics::MatrixT<T, -1, -1>& _process_noise_covariance)
{
    // predicted (a priori) state estimate
    current_state_ = _state_transition_model * current_state_ + _control_input_model * _control;
    // predicted(a priori) estimate covariance
    priori_estimate_covariance_ =
        _state_transition_model * priori_estimate_covariance_ * _state_transition_model.Transpose() +
        _process_noise_covariance;
}

template <typename T>
void KalmanFilter<T>::Predict(const ::holo::numerics::VectorT<T, -1>& _control,
                              const ::holo::numerics::MatrixT<T, -1, -1>& _process_noise_covariance)
{
    Predict(state_transition_model_, control_input_model_, _control, _process_noise_covariance);
}

template <typename T>
void KalmanFilter<T>::Correct(const ::holo::numerics::VectorT<T, -1>& _observation,
                              const ::holo::numerics::MatrixT<T, -1, -1>& _observation_model,
                              const ::holo::numerics::MatrixT<T, -1, -1>& _observation_noise_covariance)
{
    // innovation or measurement pre-fit residual
    const ::holo::numerics::VectorT<T, -1> innovation = _observation - _observation_model * current_state_;

    // innovation (or pre-fit residual) covariance
    const ::holo::numerics::MatrixT<T, -1, -1> innovation_covariance =
        _observation_model * priori_estimate_covariance_ * _observation_model.Transpose() +
        _observation_noise_covariance;

    // optimal kalman gain
    const ::holo::numerics::MatrixT<T, -1, -1> k =
        priori_estimate_covariance_ * _observation_model.Transpose() * innovation_covariance.Inverse();

    // update posteriori state estimate
    const ::holo::numerics::VectorT<T, -1> dx = k * innovation;
    current_state_ += dx;

    // update posteriori estimate covariance
    priori_estimate_covariance_ -= k * _observation_model * priori_estimate_covariance_;

    AddInnovationToDeque(innovation, innovation_covariance);

    // TODO(huyuchao@holomatic.com): add outlier rejection
    is_outlier_         = CheckOutlier(innovation, innovation_covariance);
    is_divergent_valid_ = CheckDivergence(deque_innovation_with_covariance_, is_divergent_);
}

template <typename T>
void KalmanFilter<T>::Correct(const ::holo::numerics::VectorT<T, -1>& _observation,
                              const ::holo::numerics::MatrixT<T, -1, -1>& _observation_noise_covariance)
{
    Correct(_observation, observation_model_, _observation_noise_covariance);
}

template <typename T>
void KalmanFilter<T>::AddInnovationToDeque(const ::holo::numerics::VectorT<T, -1>& _innovation,
                                           const ::holo::numerics::MatrixT<T, -1, -1>& _innovation_covariance)
{
    deque_innovation_with_covariance_.emplace_back(_innovation, _innovation_covariance);
    while (deque_innovation_with_covariance_.size() > max_innovation_queue_)
    {
        deque_innovation_with_covariance_.pop_front();
    }
}

template <typename T>
bool KalmanFilter<T>::CheckDivergence(
    const ::std::deque<::std::pair<::holo::numerics::VectorT<T, -1>,
                       ::holo::numerics::MatrixT<T, -1, -1>>>& _deque_innovation_with_covariance,
    bool&                                                                    _is_divergent) const
{
    const size_t n = _deque_innovation_with_covariance.size();
    if (n < 30)
    {
        return false;
    }

    // refer to users.isy.liu.se/en/rt/fredrik/edu/sensorfusion/lecture5.pdf
    // the sum of all the data's innovation^T * innovation_covariance^(-1) * innovation should satisfy central limit
    // theorem
    const T t =
        ::std::accumulate(_deque_innovation_with_covariance.begin(), _deque_innovation_with_covariance.end(), 0.0,
                          [this](T s, ::std::pair<::holo::numerics::VectorT<T, -1>, 
                                      ::holo::numerics::MatrixT<T, -1, -1>> _innovation_with_covariance) {
                              return s + CalculateInnovationMahalanobisDistanceSqr(_innovation_with_covariance.first,
                                                                                   _innovation_with_covariance.second) /
                                             _innovation_with_covariance.first.GetSize();
                          }) /
        n;

    const T diff =
        (t - 1) *
        ::std::sqrt(
            ::std::accumulate(_deque_innovation_with_covariance.begin(), _deque_innovation_with_covariance.end(), 0.0,
                              [](T s, ::std::pair<::holo::numerics::VectorT<T, -1>, 
                                      ::holo::numerics::MatrixT<T, -1, -1>> _innovation_with_covariance) {
                                  return s + _innovation_with_covariance.first.GetSize();
                              }) /
            2.0);

    if (diff > divergence_threshold_)
    {
        _is_divergent = true;
    }
    else
    {
        _is_divergent = false;
    }
    return true;
}

template <typename T>
bool KalmanFilter<T>::CheckOutlier(const ::holo::numerics::VectorT<T, -1>& _innovation,
                                   const ::holo::numerics::MatrixT<T, -1, -1>& _innovation_covariance) const
{
    // refer to users.isy.liu.se/en/rt/fredrik/edu/sensorfusion/lecture5.pdf
    // innovation^T * innovation_covariance^(-1) * innovation ~ chi-square distribution(dim(observation))
    return CalculateInnovationMahalanobisDistanceSqr(_innovation, _innovation_covariance) > outlier_gamma_;
}

template <typename T>
T KalmanFilter<T>::CalculateInnovationMahalanobisDistanceSqr(const ::holo::numerics::VectorT<T, -1>& _innovation,
                                            const ::holo::numerics::MatrixT<T, -1, -1>& _innovation_covariance) const
{
    return (_innovation.Transpose() * _innovation_covariance.Inverse() * _innovation)(0, 0);
}

template <typename T>
bool KalmanFilter<T>::IsOutlier() const
{
    return is_outlier_;
}

template <typename T>
bool KalmanFilter<T>::IsDivergent() const
{
    return is_divergent_;
}

template <typename T>
bool KalmanFilter<T>::IsDivergentValid() const
{
    return is_divergent_valid_;
}
}  // namespace map
}  // namespace holo
