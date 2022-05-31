/*!
 * \brief Kalman filter
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2018-01-15
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_MAP_FEATURE_FILTERS_KALMAN_FILTER_H_
#define HOLO_MAP_FEATURE_FILTERS_KALMAN_FILTER_H_

#include <deque>

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
class KalmanFilter
{
public:
    KalmanFilter(const KalmanFilter&) = delete;
    KalmanFilter& operator=(const KalmanFilter&) = delete;

    ///
    /// @brief Constructor
    ///
    /// @param [in] _initial_state
    /// @param [in] _initial_state_covariance
    ///
    KalmanFilter(const ::holo::numerics::VectorT<T, -1>& _initial_state,
                 const ::holo::numerics::MatrixT<T, -1, -1>& _initial_state_covariance);

    ///
    /// @brief Destructor
    ///
    ~KalmanFilter() = default;

    ///
    /// @brief Reset filter
    ///
    /// @return Nothing
    ///
    void Reset();

    ///
    /// @brief Set models
    ///
    /// @param [in] _state_transition_model
    /// @param [in] _control_input_model
    /// @param [in] _observation_model
    /// @return Nothing
    ///
    void SetModels(const ::holo::numerics::MatrixT<T, -1, -1>& _state_transition_model,
                   const ::holo::numerics::MatrixT<T, -1, -1>& _control_input_model,
                   const ::holo::numerics::MatrixT<T, -1, -1>& _observation_model);

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
    /// @brief Set outlier gamma
    ///
    /// @param[in] _outlier_gamma
    /// @return Nothing
    ///
    void SetOutlierGamma(const T _outlier_gamma);

    ///
    /// @brief Get outlier gamma
    ///
    /// @return Outlier gamma
    ///
    T GetOutlierGamma() const;

    ///
    /// @brief Set divergence threshold
    ///
    /// @param[in] _divergence_threshold
    /// @return Nothing
    ///
    void SetDivergenceThreshold(const T _divergence_threshold);

    ///
    /// @brief Get divergence threshold
    ///
    /// @return Divergence threshold
    ///
    T GetDivergenceThreshold() const;

    ///
    /// @brief Do predict
    ///
    /// @param [in] _state_transition_model
    /// @param [in] _control_input_model
    /// @param [in] _control
    /// @param [in] _process_noise_covariance
    /// @return Nothing
    ///
    void Predict(const ::holo::numerics::MatrixT<T, -1, -1>& _state_transition_model,
                 const ::holo::numerics::MatrixT<T, -1, -1>& _control_input_model,
                 const ::holo::numerics::VectorT<T, -1>& _control,
                 const ::holo::numerics::MatrixT<T, -1, -1>& _process_noise_covariance);

    ///
    /// @brief Do predict
    ///
    /// @param [in] _control
    /// @param [in] _process_noise_covariance
    /// @return Nothing
    ///
    void Predict(const ::holo::numerics::VectorT<T, -1>& _control,
                 const ::holo::numerics::MatrixT<T, -1, -1>& _process_noise_covariance);

    ///
    /// @brief Do correct
    ///
    /// @param [in] _observation
    /// @param [in] _observation_model
    /// @param [in] _observation_noise_covariance
    /// @return Nothing
    ///
    void Correct(const ::holo::numerics::VectorT<T, -1>& _observation,
                 const ::holo::numerics::MatrixT<T, -1, -1>& _observation_model,
                 const ::holo::numerics::MatrixT<T, -1, -1>& _observation_noise_covariance);

    ///
    /// @brief Do correct
    ///
    /// @param [in] _observation
    /// @param [in] _observation_noise_covariance
    /// @return Nothing
    ///
    void Correct(const ::holo::numerics::VectorT<T, -1>& _observation,
                 const ::holo::numerics::MatrixT<T, -1, -1>& _observation_noise_covariance);

    ///
    /// @brief If the last observation is outlier
    ///
    /// @return True if the observation is outlier, vice versa
    ///
    bool IsOutlier() const;

    ///
    /// @brief If the filter is divergent
    ///
    /// @return True if the filter is divergent, vice versa
    ///
    bool IsDivergent() const;

    ///
    /// @brief If the filter's divergence state is valid
    ///
    /// @return True if valid, vice versa
    ///
    bool IsDivergentValid() const;

private:
    void AddInnovationToDeque(const ::holo::numerics::VectorT<T, -1>& _innovation,
                              const ::holo::numerics::MatrixT<T, -1, -1>& _innovation_covariance);

    ///
    /// @brief Check divergence based on current and historic trend of innovation
    ///
    /// @param [in] _deque_innovation
    /// @param [in] _innovation
    /// @param [out] _is_divergent
    /// @return True if data valid, vice versa
    ///
    bool CheckDivergence(
        const ::std::deque<::std::pair<::holo::numerics::VectorT<T, -1>,
              ::holo::numerics::MatrixT<T, -1, -1>>>& _deque_innovation_with_covariance,
        bool& _is_divergent) const;
    ///
    /// @brief Check outlier based on innovation with covariance
    ///
    /// @param [in] _innovation
    /// @param [in] _innovation_covariance
    /// @return True if outlier, vice versa
    ///
    bool CheckOutlier(const ::holo::numerics::VectorT<T, -1>& _innovation,
                      const ::holo::numerics::MatrixT<T, -1, -1>& _innovation_covariance) const;

    ///
    /// @brief Calculate innovation mahalanobis distance squired
    ///
    /// @param[in] _innovation
    /// @param[in] _innovation_covariance
    /// @return Innovation mahalanobis distance squired
    ///
    T CalculateInnovationMahalanobisDistanceSqr(const ::holo::numerics::VectorT<T, -1>& _innovation,
                                            const ::holo::numerics::MatrixT<T, -1, -1>& _innovation_covariance) const;

private:
    ::holo::numerics::VectorT<T, -1> current_state_;
    ::holo::numerics::MatrixT<T, -1, -1> priori_estimate_covariance_;

    ::holo::numerics::MatrixT<T, -1, -1> state_transition_model_;
    ::holo::numerics::MatrixT<T, -1, -1> control_input_model_;
    ::holo::numerics::MatrixT<T, -1, -1> observation_model_;

    ::std::deque<::std::pair<::holo::numerics::VectorT<T, -1>,
                             ::holo::numerics::MatrixT<T, -1, -1>>> deque_innovation_with_covariance_;

    ::std::size_t max_innovation_queue_;

    T outlier_gamma_;
    T divergence_threshold_;

    bool is_outlier_;
    bool is_divergent_;
    bool is_divergent_valid_;
};  // class KalmanFilter
}  // namespace map
}  // namespace holo

#endif  //  HOLO_MAP_FEATURE_FILTERS_KALMAN_FILTER_H_
