/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file integrated_navstate2_float32.h
 * @brief This header file defines float32 2-D integrated navigation state struct
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Mar 09, 2020
 */

#ifndef HOLO_C_LOCALIZATION_FILTERING_INTEGRATED_NAVSTATE2_FLOAT32_H_
#define HOLO_C_LOCALIZATION_FILTERING_INTEGRATED_NAVSTATE2_FLOAT32_H_

#include <assert.h>

#include <holo_c/common/coordinate.h>
#include <holo_c/filters/kalman_filter_float32.h>
#include <holo_c/localization/common/navstate2_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup localization
 * @{
 *
 */

/**
 * @brief This struct defines float32 2-D integrated navigation state struct
 * @details The struct IntegratedNavstate2f is defined for the 2-dimension integrated navigation algorithm. It is used
 * to save the filtering results and related localization results in the integrated navigation operation process.
 * Attention please, here the dimension of the kalman filter is 8 dimension.
 *
 */
struct IntegratedNavstate2f
{
    struct Timestamp timestamp;  ///< The timestamp of state
    /// The localization state includes the pose, velocity, imu bias and imu bias covariance in the navigation
    struct Navstate2f    navstate;
    struct KalmanFilterf kalman_filter;         ///< The kalman filter process
    struct Vectorf       filter_current_state;  ///< The current state of the kalman filter
    float32_t            filter_current_state_data[VECTORF_MIN_BUF_SIZE(8u)];  ///< The buffer to save the current state
    struct Matrixf       filter_priori_estimate_covariance;  ///< Priori estimated covariance of the kalman filter
    /// The buffer to save the priori covariance of the kalman filter
    float32_t filter_priori_estimate_covariance_data[MATRIXF_MIN_BUF_SIZE(8u, 8u)];
};

/// check the size of IntegratedNavstate2f with static assert
HOLO_STATIC_ASSERT(sizeof(struct IntegratedNavstate2f) == 608u);

/**
 * @brief Initialize IntegratedNavstate2f struct from default value
 *
 * @param[in, out] self The intialized IntegratedNavstate2f struct
 * @return The return code
 */
retcode_t integrated_navstate2f_init(struct IntegratedNavstate2f* self);

/**
 * @brief Get the timestamp from a IntegratedNavstate2f struct
 *
 * @param[in] self The input IntegratedNavstate2f struct
 * @return The pointer of a const Timestamp struct
 */
struct Timestamp const* integrated_navstate2f_get_timestamp(struct IntegratedNavstate2f const* self);

/**
 * @brief Set the timestamp to a IntegratedNavstate2f struct
 *
 * @param[out] self The IntegratedNavstate2f struct
 * @param[in] timestamp The timestamp wanted to be set
 * @return The return code
 */
retcode_t integrated_navstate2f_set_timestamp(struct IntegratedNavstate2f* self, struct Timestamp const* timestamp);

/**
 * @brief Get the Navstate2f from a IntegratedNavstate2f struct
 *
 * @param[in] self The input IntegratedNavstate2f struct
 * @return The pointer of a const Navstate2f struct
 */
struct Navstate2f const* integrated_navstate2f_get_navstate2f(struct IntegratedNavstate2f const* self);

/**
 * @brief Set the Navstate2f struct to a IntegratedNavstate2f struct
 *
 * @param[out] self The IntegratedNavstate2f struc
 * @param[in] navstate The Navstate2f wanted to be set
 * @return The return code
 */
retcode_t integrated_navstate2f_set_navstate2f(struct IntegratedNavstate2f* self, struct Navstate2f const* navstate);

/**
 * @brief Get the Kalman filter struct from a IntegratedNavstate2f struct
 *
 * @param[in] self The input IntegratedNavstate2f struct
 * @return The pointer of the const KalmanFilterf struct
 */
struct KalmanFilterf const* integrated_navstate2f_get_kalman_filterf(struct IntegratedNavstate2f const* self);

/**
 * @brief Set the Kalman filter struct to a IntegratedNavstate2f struct
 *
 * @param[out] self The IntegratedNavstate2f struct
 * @param[in] kalman_filter The kalman filter struct wanted to be set
 * @return The return code
 */
retcode_t integrated_navstate2f_set_kalman_filterf(struct IntegratedNavstate2f* self,
                                                   struct KalmanFilterf const*  kalman_filter);

/**
 * @brief Get the current state of the kalman filter from the IntegratedNavstate2f struct
 *
 * @param[in] self The input IntegratedNavstate2f struct
 * @return The pointer of the const current kalman filter state (Vectorf)
 */
struct Vectorf const* integrated_navstate2f_get_kalman_filterf_state(struct IntegratedNavstate2f const* self);

/**
 * @brief Set the current state of the kalman filter to the IntegratedNavstate2f struct
 *
 * @param[out] self The IntegratedNavstate2f struct
 * @param[in] kf_current_state The current state of kalman filter struct wanted to be set
 * @return The return code
 */
retcode_t integrated_navstate2f_set_kalman_filterf_state(struct IntegratedNavstate2f* self,
                                                         struct Vectorf const*        kf_current_state);

/**
 * @brief Get the priori estimated covariance of the kalman filter from the IntegratedNavstate2f struct
 *
 * @param[in] self The input IntegratedNavstate2f struct
 * @return The pointer of the const priori estimated covariance (Matrixf)
 */
struct Matrixf const* integrated_navstate2f_get_kalman_filterf_covariance(struct IntegratedNavstate2f const* self);

/**
 * @brief Set the priori estimated covariance of the kalman filter to the IntegratedNavstate2f struct
 *
 * @param[out] self The IntegratedNavstate2f struct
 * @param[in] covariance The covariance of kalman filter struct wanted to be set
 * @return The return code
 */
retcode_t integrated_navstate2f_set_kalman_filterf_covariance(struct IntegratedNavstate2f* self,
                                                              struct Matrixf const*        covariance);

/**
 * @brief Check if the IntegratedNavstate2f struct is valid
 *
 * @param[in] self The IntegratedNavstate2f struct
 * @return It returns false if it is invalid. Otherwise, it return true
 */
bool_t integrated_navstate2f_is_valid(struct IntegratedNavstate2f const* self);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_FILTERING_INTEGRATED_NAVSTATE2_FLOAT32_H_
