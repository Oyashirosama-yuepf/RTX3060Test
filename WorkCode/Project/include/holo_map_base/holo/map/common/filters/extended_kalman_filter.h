/*!
 * \brief Extended Kalman filter
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2018-11-13
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_MAP_FEATURE_FILTERS_EXTENDED_KALMAN_FILTER_H_
#define HOLO_MAP_FEATURE_FILTERS_EXTENDED_KALMAN_FILTER_H_

#include <functional>

#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace map
{
///
/// @brief Kalman filter
///
/// @tparam T
///
template <typename T>
class ExtendedKalmanFilter
{
public:
    ExtendedKalmanFilter(const ExtendedKalmanFilter&) = delete;
    ExtendedKalmanFilter& operator=(const ExtendedKalmanFilter&) = delete;

    ///
    /// @brief Constructor
    ///
    /// @param [in] _initial_state
    /// @param [in] _initial_state_covariance
    ///
    ExtendedKalmanFilter(const ::holo::numerics::VectorT<T, -1>& _initial_state,
                         const ::holo::numerics::MatrixT<T, -1, -1>& _initial_state_covariance);

    ///
    /// @brief Destructor
    ///
    ~ExtendedKalmanFilter() = default;

    ///
    /// @brief Reset filter
    ///
    /// @return Nothing
    ///
    void Reset();

    ///
    /// @brief Set state and covariance
    ///
    /// @param [in] _state Current state
    /// @param [in] _covariance
    /// @return Nothing
    ///
    void SetStateWithCovariance(const ::holo::numerics::VectorT<T, -1>& _state,
                                const ::holo::numerics::MatrixT<T, -1, -1>& _covariance);

    ///
    /// @brief Set state
    ///
    /// @param [in] _state Current state
    /// @return Nothing
    ///
    void SetState(const ::holo::numerics::VectorT<T, -1>& _state);

    ///
    /// @brief Set covariance
    ///
    /// @param [in] _covariance
    /// @return Nothing
    ///
    void SetCovariance(const ::holo::numerics::MatrixT<T, -1, -1>& _covariance);

    ///
    /// @brief Get current state
    ///
    /// @return Current state
    ///
    const ::holo::numerics::VectorT<T, -1>& GetState() const;

    ///
    /// @brief Get current state covariance
    ///
    /// @return current state covariance
    ///
    const ::holo::numerics::MatrixT<T, -1, -1>& GetCovariance() const;

    ///
    /// @brief Get current state and covariance
    ///
    /// @param [out] _state current state
    /// @param [out] _covariance
    /// @return Nothing
    ///
    void GetStateWithCovariance(::holo::numerics::VectorT<T, -1>& _state,
                                ::holo::numerics::MatrixT<T, -1, -1>& _covariance) const;

    ///
    /// @brief Do predict
    ///
    /// @param [in] _func_predict_state
    /// @param [in] _func_transit_state
    /// @param [in] _control
    /// @param [in] _process_noise_covariance
    /// @return Nothing
    ///
    void Predict(
        const ::std::function<::holo::numerics::VectorT<T, -1>(
                const ::holo::numerics::VectorT<T, -1>&, 
                const ::holo::numerics::VectorT<T,-1>&)>& _func_predict_state,
        const ::std::function<::holo::numerics::MatrixT<T,-1,-1>(
                const ::holo::numerics::VectorT<T, -1>&)>&_func_transit_state,
        const ::holo::numerics::VectorT<T, -1>& _control,
        const ::holo::numerics::MatrixT<T, -1, -1>& _process_noise_covariance);

    ///
    /// @brief Do correct
    ///
    /// @param [in] _func_predict_observation
    /// @param [in] _func_observation_model
    /// @param [in] _observation
    /// @param [in] _observation_noise_covariance
    /// @return Nothing
    ///
    void Correct(
        const ::std::function<::holo::numerics::VectorT<T, -1>(const ::holo::numerics::VectorT<T, -1>&)>&
            _func_predict_observation,
        const ::std::function<::holo::numerics::MatrixT<T,-1,-1>(const ::holo::numerics::VectorT<T, -1>&)>&
            _func_observation_model,
        const ::holo::numerics::VectorT<T, -1>& _observation,
        const ::holo::numerics::MatrixT<T, -1, -1>& _observation_noise_covariance);

private:
    ::holo::numerics::VectorT<T, -1> current_state_;
    ::holo::numerics::MatrixT<T, -1, -1> priori_estimate_covariance_;
};  // class ExtendedKalmanFilter

}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_FILTERS_EXTENDED_KALMAN_FILTER_H_
