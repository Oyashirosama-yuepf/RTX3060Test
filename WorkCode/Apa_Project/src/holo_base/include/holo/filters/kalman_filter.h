/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file kalman_filter.h
 * @brief This header file define template class Kalman filter
 * @author Yuchao Hu (huyuchao@holomatic.com), lichao@holomatic.com
 * @date Sep 19, 2019
 */

#ifndef HOLO_FILTERS_KALMAN_FILTER_H_
#define HOLO_FILTERS_KALMAN_FILTER_H_

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
/**
 * @addtogroup core
 * @{
 *
 */

/**
 * @brief This class defines Kalman filter
 *
 * @tparam Scalar precision type
 * @tparam Dimension dimension of state
 */
template <typename Scalar, uint8_t Dimension>
class KalmanFilterT
{
public:
    using VectorType = holo::numerics::VectorT<Scalar, Dimension>;
    using MatrixType = holo::numerics::MatrixT<Scalar, Dimension, Dimension>;

    /**
     * @brief Construct a new Kalman Filter T object
     *
     * @param [in] initial_state
     * @param [in] initial_state_covariance
     */
    KalmanFilterT(const VectorType& initial_state            = VectorType::Zero(),
                  const MatrixType& initial_state_covariance = MatrixType::Identity());

    /**
     * @brief Destroy the Kalman Filter T object
     *
     */
    ~KalmanFilterT() noexcept;

    /**
     * @brief Reset filter
     *
     */
    void Reset();

    /**
     * @brief Set the State With Covariance object
     *
     * @param [in] state Current state
     * @param [in] covariance
     */
    void SetStateWithCovariance(const VectorType& state, const MatrixType& covariance);

    /**
     * @brief Set the State object
     *
     * @param [in] state Current state
     */
    void SetState(const VectorType& state);

    /**
     * @brief Set the Covariance object
     *
     * @param [in] covariance
     */
    void SetCovariance(const MatrixType& covariance);

    /**
     * @brief Get the State object
     *
     * @return const VectorType& the State
     */
    const VectorType& GetState() const;

    /**
     * @brief Get the Covariance object
     *
     * @return const MatrixType&  the state covariance
     */
    const MatrixType& GetCovariance() const;

    /**
     * @brief Get the State With Covariance object
     *
     * @param [out] state Current state
     * @param [out] covariance Current state covariance
     */
    void GetStateWithCovariance(VectorType& state, MatrixType& covariance) const;

    /**
     * @brief Do prediction
     *
     * @tparam ControlDim dimension of control
     * @param [in] state_transition_model
     * @param [in] control_input_model
     * @param [in] control
     * @param [in] process_noise_covariance
     */
    template <uint8_t ControlDim>
    void Predict(const numerics::MatrixT<Scalar, Dimension, Dimension>&  state_transition_model,
                 const numerics::MatrixT<Scalar, Dimension, ControlDim>& control_input_model,
                 const numerics::VectorT<Scalar, ControlDim>&            control,
                 const numerics::MatrixT<Scalar, Dimension, Dimension>&  process_noise_covariance);

    /**
     * @brief Do correction
     *
     * @tparam ObservationDim dimension of observation
     * @param [in] observation
     * @param [in] observation_model
     * @param [in] observation_noise_covariance
     */
    template <uint8_t ObservationDim>
    void Correct(const numerics::VectorT<Scalar, ObservationDim>&                 observation,
                 const numerics::MatrixT<Scalar, ObservationDim, Dimension>&      observation_model,
                 const numerics::MatrixT<Scalar, ObservationDim, ObservationDim>& observation_noise_covariance);

    /**
     * @brief Check if the filter stability
     *
     * @return true stable
     * @return false unstable
     */
    bool_t IsStable() const;

private:
    VectorType current_state_;              /* Current state */
    MatrixType priori_estimate_covariance_; /* Priori estimated covariance */

    Scalar stability_gamma_; /* gamma scalar */
    bool_t stability_;       /* stability flag */
};

/**
 * @}
 *
 */

}  // namespace holo

#endif  //  HOLO_FILTERS_KALMAN_FILTER_H_
