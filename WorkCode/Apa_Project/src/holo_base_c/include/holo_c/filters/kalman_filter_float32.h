/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file kalman_filter_float32.h
 * @brief This header file defines common float32 Kalman filter struct
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Feb 10, 2020
 */

#ifndef HOLO_C_FILTERS_KALMAN_FILTER_FLOAT32_H_
#define HOLO_C_FILTERS_KALMAN_FILTER_FLOAT32_H_

#include <assert.h>

#include <holo_c/numerics/matrix_float32.h>
#include <holo_c/numerics/vector_float32.h>
#include <holo_c/utils/serialization.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup filters
 * @{
 *
 */

/**
 * @brief This struct defines common float32 Kalman filter struct
 *
 */
struct KalmanFilterf
{
    struct Vectorf current_state;               ///< Current filter state
    struct Matrixf priori_estimate_covariance;  ///< Priori estimated covariance
    float32_t      stability_gamma;             ///< Gamma scalar
    bool_t         stability;                   ///< Stability flag
};

/// Check the size of KalmanFilterf with static assert
HOLO_STATIC_ASSERT(sizeof(struct KalmanFilterf) == 40u);

/**
 * @brief Initialize a Kalman filter struct from the state and priori covariance
 *
 * @param[in, out] self The initialized kalman filter struct
 * @param[in] state The pointer to initial state
 * @param[in] priori_covariance The pointer to initial priori covariance
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_init(struct KalmanFilterf* self, struct Vectorf const* state,
                              struct Matrixf const* priori_covariance);

/**
 * @brief Set a Kalman filter struct from other Kalman filter struct
 *
 * @param[in, out] self The kalman filter struct
 * @param[in] other The other kalman filter for setting
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_set_from_kalman_filterf(struct KalmanFilterf* self, struct KalmanFilterf const* other);

/**
 * @brief Check the validity of the kalman filter struct
 *
 * @param[in] self The checked kalman fitter struct
 * @return bool_t It return false when it is invalid
 */
bool_t kalman_filterf_is_valid(struct KalmanFilterf const* self);

/**
 * @brief Reset filter
 *
 * @param[in, out] self The reset filter
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_reset(struct KalmanFilterf* self);

/**
 * @brief Set the state with corresponding covariance
 *
 * @param[in, out] self The set Kalman filter struct
 * @param[in] state The current state
 * @param[in] priori_covariance The corresponding priori covariance
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_set_state_with_covariance(struct KalmanFilterf* self, struct Vectorf const* state,
                                                   struct Matrixf const* priori_covariance);

/**
 * @brief Set the state
 *
 * @param[in, out] self The set Kalman filter struct
 * @param[in] state The current state
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_set_state(struct KalmanFilterf* self, struct Vectorf const* state);

/**
 * @brief Set covariance matrix
 *
 * @param[in, out] self The set Kalman filter struct
 * @param[in] Matrixf The current priori covariance matrix
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_set_covariance(struct KalmanFilterf* self, struct Matrixf const* covariance);
/**
 * @brief Get the state from Kalman filter
 *
 * @param[in] self The kalman filter
 * @param[out] state The state
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_get_state(struct KalmanFilterf const* self, struct Vectorf* state);

/**
 * @brief Get the covariance matrix from Kalman filter
 *
 * @param[in] self The kalman filter
 * @param[out] covariance The priori covariance matrix
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_get_covariance(struct KalmanFilterf const* self, struct Matrixf* covariance);

/**
 * @brief Get the state With covariance
 *
 * @param[in] self The kalman filter
 * @param[out] state The state
 * @param[out] covariance  The priori covariance matrix
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_get_state_with_covariance(struct KalmanFilterf const* self, struct Vectorf* state,
                                                   struct Matrixf* covariance);

/**
 * @brief Do kalman prediction
 *
 * @param[in, out] self The kalman filter struct
 * @param[in] state_transition_model The state transition model
 * @param[in] control_input_model The input control model
 * @param[in] control The control value
 * @param[in] process_noise_covariance The process noise covariance
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_predict(struct KalmanFilterf* self, struct Matrixf const* state_transition_model,
                                 struct Matrixf const* control_input_model, struct Vectorf const* control,
                                 struct Matrixf const* process_noise_covariance);

/**
 * @brief Do kalman correction
 *
 * @param[in, out] self The kalman filter struct
 * @param[in] observation The observation vector
 * @param[in] observation_model The observation model
 * @param[in] observation_noise_covariance The observation noise covariance
 * @return retcode_t The return code
 */
retcode_t kalman_filterf_correct(struct KalmanFilterf* self, struct Vectorf const* observation,
                                 struct Matrixf const* observation_model,
                                 struct Matrixf const* observation_noise_covariance);

/**
 * @brief Check if the filter is stable
 *
 * @param[in] self The kalman filter
 * @return bool_t It return false if the filter is not stable
 */
bool_t kalman_filterf_is_stable(struct KalmanFilterf const* self);

/**
 * @brief Default interface of getting float32_t Kalman filter serialized size.
 *
 * @param[in] self The float32_t kalman filter
 * @return uint32_t Serialized size
 */
uint32_t kalman_filterf_get_serialized_size(struct KalmanFilterf const* self);

/**
 * @brief Default interface serialize float32_t Kalman filter
 *
 * @param[in] self The float32_t kalman filter
 * @param[out] buffer The buffer to serialize to
 * @param[in] buffer_size The size of buffer
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 */
retcode_t kalman_filterf_serialize(struct KalmanFilterf const* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Default interface deserialize float32_t kalman filter
 *
 * @param[out] self The float32_t kalman filter
 * @param[in] buffer The buffer to deserialize from
 * @param[in] buffer_size The size of buffer
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 */
retcode_t kalman_filterf_deserialize(struct KalmanFilterf* self, uint8_t const* buffer, uint32_t buffer_size);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_FILTERS_KALMAN_FILTER_FLOAT32_H_
