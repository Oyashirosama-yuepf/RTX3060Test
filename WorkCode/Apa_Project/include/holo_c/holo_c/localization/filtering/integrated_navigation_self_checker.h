/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file integrated_navigation_self_checker.h
 * @brief This header file defines structure related to the self checker of integrated navigation and the related API.
 *
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date May 25, 2020
 */

#ifndef HOLO_C_LOCALIZATION_FILTERING_INTEGRATED_NAVIGATION_SELF_CHCEKER_H_
#define HOLO_C_LOCALIZATION_FILTERING_INTEGRATED_NAVIGATION_SELF_CHCEKER_H_

#include <assert.h>

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
 * @brief The parameter of the integrated navigation self checker
 *
 */
struct IntegratedNavigationSelfCheckerParameters
{
    /// Judge if the attitude change is small enough
    float32_t little_attitude_change_threshold;
    /// Judge if there is abnormal lateral jump, if the jump distance is over this parameter, it is abnormal
    float32_t lateral_jump_threshold;  ///< (unit: meter)
    /// Judge if there is abnormal attitude change, if the change value is over this parameter, it is abnormal
    float32_t attitude_jump_threshold;  ///< (unit: radian)
    /// Judge if the gyro bias is abnormal and too large
    float32_t gyro_bias_norm_threshold;  ///< (unit: rad/s)
    /// Judge if the acceleration bias is abnormal and too large
    float32_t acceleration_bias_norm_threshold;  ///< (unit: m/s2)
    /// Judge if the maximum horizon position covariance is too large
    float32_t max_horizon_position_cov_threshold;  ///< m^2
    /// Judge if the maximum attitude covariance is too large
    float32_t max_attitude_cov_threshold;  ///< radian^2
};

/**
 * @brief This struct is used to define the state of the integrated navigation self checker
 * @details The self-check state includes some variables which will be changes when the member functions are called.
 */
struct IntegratedNavigationSelfCheckerState
{
    struct Navstate2f last_navstate;                ///< Last navigation state
    bool_t            is_last_navstate_initialzed;  ///< The flag of if the last navstate was intialized
};

/**
 * @brief Initialized the parameter of integrated navigation self checker by default values
 *
 * @param[in, out] param The initialized parameter
 * @return The return code
 */
retcode_t integrated_navigation_self_checker_init_parameter(struct IntegratedNavigationSelfCheckerParameters* param);

/**
 * @brief Initialized the state of integrated navigation self checker by default values
 *
 * @param[in, out] state The initialized state
 * @return The return code
 */
retcode_t integrated_navigation_self_checker_init_state(struct IntegratedNavigationSelfCheckerState* state);

/**
 * @brief Diagnose if there is a lateral jump or a attitude jump in the output of the navigation system
 *
 * @param[in] last_navstate The last navigation system output
 * @param[in] current_navstate The current navigation system state
 * @param[in] param The parameter of the integrated navigation self checker
 * @param[out] is_lateral_jump Whether there is a lateral jump or not, True -- Yes, False -- No
 * @param[out] is_attitude_jump Whether there is a attitude jump or not, True -- Yes, False -- No,
 * @return The return code
 */
retcode_t integrated_navigation_self_checker_is_lateral_jump_and_attitude_jump(
    struct Navstate2f const* last_navstate, struct Navstate2f const* current_navstate,
    struct IntegratedNavigationSelfCheckerParameters const* param, bool_t* is_lateral_jump, bool_t* is_attitude_jump);

/**
 * @brief Diagnose if there is a abnormal acceleration bias in the output of the navigation system
 *
 * @param[in] current_navstate The current navigation system state
 * @param[in] param The parameter of the integrated navigation self checker
 * @return Whether there is a abnormal acceleration bias or not, True -- Yes, False -- No,
 */
bool_t integrated_navigation_self_checker_is_acceleration_bias(
    struct Navstate2f const* current_navstate, struct IntegratedNavigationSelfCheckerParameters const* param);

/**
 * @brief Diagnose if there is a abnormal gyroscope bias in the output of the navigation system
 *
 * @param[in] current_navstate The current navigation system state
 * @param[in] param The parameter of the integrated navigation self checker
 * @return Whether there is a abnormal gyroscope bias or not, True -- Yes, False -- No,
 */
bool_t integrated_navigation_self_checker_is_gyroscope_bias(
    struct Navstate2f const* current_navstate, struct IntegratedNavigationSelfCheckerParameters const* param);

/**
 * @brief Diagnose if the horizon position covariance is too large in the output of the navigation system
 *
 * @param[in] current_navstate The current navigation system state
 * @param[in] param The parameter of the integrated navigation self checker
 * @return Whether the horizon position covariance is too large or not, True -- Yes, False -- No,
 */
bool_t integrated_navigation_self_checker_is_large_position_covariance(
    struct Navstate2f const* current_navstate, struct IntegratedNavigationSelfCheckerParameters const* param);

/**
 * @brief Diagnose if the attitude covariance is too large in the output of the navigation system
 *
 * @param[in] current_navstate The current navigation system state
 * @param[in] param The parameter of the integrated navigation self checker
 * @return Whether the attitude covariance is too large or not, True -- Yes, False -- No,
 */
bool_t integrated_navigation_self_checker_is_large_attitude_covariance(
    struct Navstate2f const* current_navstate, struct IntegratedNavigationSelfCheckerParameters const* param);

/**
 * @brief  Run the integrated navigation self check for the navstate output
 *
 * @param[in] current_navstate The current navigation system state
 * @param[in] parameter The parameter of the integrated navigation self checker
 * @param[in, out] state The state of the integrated navigation self checker
 * @return the & operation result of the NavstateStatus enumeration
 */
uint32_t integrated_navigation_self_checker_run(struct Navstate2f const* current_navstate,
                                                struct IntegratedNavigationSelfCheckerParameters const* parameter,
                                                struct IntegratedNavigationSelfCheckerState*            state);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_FILTERING_INTEGRATED_NAVIGATION_SELF_CHCEKER_H_
