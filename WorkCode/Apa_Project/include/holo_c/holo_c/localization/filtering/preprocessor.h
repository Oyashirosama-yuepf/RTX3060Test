/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file preprocessor.h
 * @brief This header file defines structure related to the preprocessor of integrated navigation and the related API.
 * @details In current preprocessor, we only check the GNSS measurement and reject the invalid measurements.
 *
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date May 14, 2020
 */

#ifndef HOLO_C_LOCALIZATION_FILTERING_PREPROCESSOR_H_
#define HOLO_C_LOCALIZATION_FILTERING_PREPROCESSOR_H_

#include <assert.h>

#include <holo_c/localization/filtering/gnss_validity_checker.h>
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
 * @brief The parameters of the preprocessor
 *
 */
struct PreprocessorParameters
{
    struct GnssValidityCheckerParameters gnss_validity_checker_param;  ///< The parameter of the GNSS validity checker
};

/**
 * @brief The state of the preprocessor
 *
 */
struct PreprocessorState
{
    struct GnssValidityCheckerState gnss_validity_checker_state;  ///< The state of the GNSS validity checker
};

/**
 * @brief Initialize the parameter by default value
 *
 * @param[in, out] param The initialized parameter
 * @return The return code
 */
retcode_t preprocessor_init_parameter(struct PreprocessorParameters* param);

/**
 * @brief Initialize the state by default value
 *
 * @param[in, out] state The initialized state
 * @return The return code
 */
retcode_t preprocessor_init_state(struct PreprocessorState* state);

/**
 * @brief Run the preprocessor
 * @details In current preprocessor, we only check the GNSS measurement and reject the invalid measurements.
 *
 * @param[in] param The parameter of preprocessor
 * @param[in, out] raw_measurement The raw measurements which will be processed
 * @param[in, out] state The state of preprocessor
 * @return The return code
 */
retcode_t preprocessor_run(struct PreprocessorParameters const* param, struct RawMeasurementf* raw_measurement,
                           struct PreprocessorState* state);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_FILTERING_PREPROCESSOR_H_
