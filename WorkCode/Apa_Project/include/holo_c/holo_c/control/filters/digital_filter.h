/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file digital_filter.h
 * @brief the header of digital filter
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-09-04
 */

#ifndef HOLO_C_CONTROL_FILTERS_DIGITAL_FILTER_H_
#define HOLO_C_CONTROL_FILTERS_DIGITAL_FILTER_H_

#include <holo_c/common/dequeue.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DIGITAL_FILTER_MAX_BUFFER 3

/**
 * @brief digital filter
 *
 * @details It is used to pass signals with a frequency lower than a certain cutoff frequency and attenuates signals with
 *          frequencies higher than the cutoff frequency.
 */
struct DigitalFilter
{
    float32_t       x_values[DIGITAL_FILTER_MAX_BUFFER];
    struct Dequeuef x_values_dequeue;  ///< the container of x_values, front is latest, back is oldest.

    float32_t       y_values[DIGITAL_FILTER_MAX_BUFFER];
    struct Dequeuef y_values_dequeue;  ///< the container of y_values, front is latest, back is oldest.

    float32_t denominators[DIGITAL_FILTER_MAX_BUFFER];  ///< Coefficients with y values

    float32_t numerators[DIGITAL_FILTER_MAX_BUFFER];  ///< Coefficients with x values

    float32_t dead_zone;  ///< threshold of updating last-filtered value

    float32_t last;  ///< last-filtered value
};

/**
 * @brief initializes a DigitalFilter with given parameters
 *
 * @param filter The DigitalFilter's pointer.
 * @param deadzone The value of deadzone.
 * @param hz The frequency of the filter.
 * @param cutoff_freq The frequency which is going to be cut off.
 *
 * @return RC_SUCCESS init successfully
 * @return RC_DIGITAL_FILTER_INVALID_HZ hz is a negative value
 * @return RC_DIGITAL_FILTER_INVALID_CUTOFF_FREQUENCY cutoff_freq is a negative value
 */
retcode_t digital_filter_init(struct DigitalFilter* filter, float32_t dead_zone, float32_t hz, float32_t cutoff_freq);

/**
 * @brief put a data into DigitalFilter
 *
 * @param filter The DigitalFilter's pointer.
 * @param data The input data.
 */
void digital_filter_put(struct DigitalFilter* filter, float32_t data);

/**
 * @brief Get the output data from the digital filter
 *
 * @details Filter by the input value, x[n - 1], insert x_insert into x[0], Remove y[n - 1].
 *          Solve den[0] * y + den[1] * y[0] + ... + den[n - 1]*y[n - 2] =
 *              num[0] * x[0] + num[1] * x[1] + ... + num[n - 1] * x[n - 1] for y. Insert y into y[0], output y[0].
 *
 * @param filter The DigitalFilter's pointer
 *
 * @retun the filterd value
 */
float32_t digital_filter_get_result(struct DigitalFilter* filter);

/**
 * @brief Reset the DigitalFilter
 *
 * @param filter The DigitalFilter's pointer
 */
void digital_filter_reset(struct DigitalFilter* filter);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_FILTERS_DIGITAL_FILTER_H_ */
