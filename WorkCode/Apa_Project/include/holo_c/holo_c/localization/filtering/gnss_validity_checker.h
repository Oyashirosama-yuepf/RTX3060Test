/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_validity_checker.h
 * @brief This header file defines structure related to the GNSS validity checker and the related API.
 * @details We check the validity of the GNSS measurements based on its covariance.
 *
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date May 13, 2020
 */

#ifndef HOLO_C_LOCALIZATION_FILTERING_GNSS_VALIDITY_CHECKER_H_
#define HOLO_C_LOCALIZATION_FILTERING_GNSS_VALIDITY_CHECKER_H_

#include <assert.h>

#include <holo_c/common/gnss_pvt.h>
#include <holo_c/localization/filtering/raw_measurement_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup localization
 * @{
 *
 */

/**
 * @brief GNSS covariance validity parameters for position and velocity based on the adaptive covariance method
 */
struct GnssAdaptiveCovThreshold
{
    float32_t covariance_threshold_max;  ///< Upper limit of GNSS cov threshold
    float32_t covariance_threshold_min;  ///< Lower limit of GNSS cov threshold
    float32_t threshold_reduction_rate;  ///< Reduction rate for adaptive threshold
    float32_t threshold_expansion_rate;  ///< Expansion rate for adaptive threshold
    float32_t lowest_multiple;           ///< The multiple = current_cov_threshold / actual_threshold
};

/**
 * @brief The parameter struct of the GNSS validity checker
 */
struct GnssValidityCheckerParameters
{
    /// The threshold for the velocity validity judgement
    struct GnssAdaptiveCovThreshold gnss_velocity_parameter;
    /// The threshold for the position validity judgement
    struct GnssAdaptiveCovThreshold gnss_position_parameter;
};

/**
 * @brief The state struct of the GNSS validity checker
 */
struct GnssValidityCheckerState
{
    float32_t velocity_cov_scaling_parameter;  ///< The adaptive coefficient for velocity
    float32_t position_cov_scaling_parameter;  ///< The adaptive coefficient for position
};

/**
 * @brief Initialize the parameter of the GNSS validity checker by default value
 *
 * @param[in, out] param The initialized parameter
 * @return The return code
 */
retcode_t gnss_validity_checker_init_parameter(struct GnssValidityCheckerParameters* param);

/**
 * @brief Initialize the state of the GNSS validity checker by default value
 *
 * @param[in, out] state The initialized state
 * @return The return code
 */
retcode_t gnss_validity_checker_init_state(struct GnssValidityCheckerState* state);

/**
 * @brief Judge the gnss validity with the adaptive scaling coefficient.
 * @details The scaling coefficient will be changed according to the judgement result. If the measurement covariance
 * is lower than the threshold, the coefficient will reduce. Otherwise, It will increase.
 *
 * @param[in] covariance The velocity covariance or position covariance
 * @param[in] threshold The corresponding adaptive covariance threshold struct
 * @param[in, out] scaling_coefficient  The last corresponding scaling parameter
 * @return It returns false if the GNSS is invalid, otherwise, it returns true
 */
bool_t gnss_validity_checker_check_covariance_adaptively(struct Point3d const*                  covariance,
                                                         struct GnssAdaptiveCovThreshold const* threshold,
                                                         float32_t*                             scaling_coefficient);

/**
 * @brief Judge the gnss validity based on the GNSS covariance
 * @details Judge the validity with the adaptive scaling parameter. The scaling parameter will be changed according
 * to the judgement result. If the measurement covariance is lower than the threshold, the parameter will reduce.
 * Otherwise, It will increase.
 *
 * @param[in] gnss_measurement The Gnss measurement
 * @param[in] parameter The parameter of the GNSS validity checker
 * @param[in] state The state of the GNSS validity checker, it will be updated
 * @return It returns false if the GNSS is invalid, otherwise, it returns true.
 */
bool_t gnss_validity_checker_run(struct GnssPvt const*                       gnss_measurement,
                                 struct GnssValidityCheckerParameters const* parameter,
                                 struct GnssValidityCheckerState*            state);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_FILTERING_GNSS_VALIDITY_CHECKER_H_
