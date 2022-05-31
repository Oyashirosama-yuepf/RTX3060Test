/**
 * @file mean_filter.h
 * @brief the header of mean filter
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-09-03
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_CONTROL_FILTER_MEAN_FILTER_H_
#define HOLO_C_CONTROL_FILTER_MEAN_FILTER_H_

#include <holo_c/common/dequeue.h>
#include <holo_c/common/queue.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MEANFILTER_MAX_BUFFER 20

/**
 * @brief
 *
 * @detail The MeanFilter is used to smoothen a series of noisy numbers, such as sensor data or the output of a function
 *         that we wish to be smoother. This is achieved by keeping track of the last k measurements (where k is the
 *         window size), and returning the average of all but the minimum and maximum measurements, which are likely to
 *         be outliers.
 */
struct MeanFilter
{
    float32_t values[MEANFILTER_MAX_BUFFER];  ///< values' buffer

    struct Queuef values_queue;  ///< queue for values

    float32_t min_candidates[MEANFILTER_MAX_BUFFER];  ///< min_candidates' buffer

    struct Dequeuef min_candidates_dequeue;  ///< dequeue for min candidates

    float32_t max_candidates[MEANFILTER_MAX_BUFFER];  ///< max_candidates' buffer

    struct Dequeuef max_candidates_dequeue;  ///< dequeue for max candidates

    float32_t sum;  ///< sum of available candidates

    uint8_t window_size;  ///< size of mean filter's window
};

/**
 * @brief Initializes a MeanFilter with a given window size.
 *
 * @param filter The filter's pointer.
 * @param window_size The window size of the MeanFilter.
 *
 * @return RC_SUCCESS: init successfully.
 * @return RC_MEAN_FILTER_NOT_ENOUGH_BUFFER: window_size is larger than MEANFILTER_MAX_BUFFER.
 * @return RC_MEAN_FILTER_INVALID_WINDOW_SIZE: window_size is less than 2.
 */
retcode_t mean_filter_init(struct MeanFilter* filter, uint8_t window_size);

/**
 * @brief Put a new measurement into mean filter.
 *
 * @param filter The filter's pointer.
 * @param measurement The measurement to be processed by the filter.
 */
void mean_filter_put(struct MeanFilter* filter, float32_t measurement);

/**
 * @brief Get the output from mean filter, the maximum and minimum have been ignored during filtering.
 *
 * @param filter The filter's pointer.
 *
 * @return output of mean filter
 */
float32_t mean_filter_get_result(struct MeanFilter* filter);

/**
 * @brief Reset the mean filter, the values will be clear.
 *
 * @param filter The filter's pointer.
 */
void mean_filter_reset(struct MeanFilter* filter);

/**
 * @brief Check if the measurement should be inserted into the min dequeue.
 *
 * @param filter The filter's pointer.
 * @param measurement The measurement to be processed by the filter.
 */
void mean_filter_check_min_dequeue(struct MeanFilter* filter, float32_t measurement);

/**
 * @brief Check if the measurement should be inserted into the max dequeue.
 *
 * @param filter The filter's pointer.
 * @param measurement The measurement to be processed by the filter.
 */
void mean_filter_check_max_dequeue(struct MeanFilter* filter, float32_t measurement);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_FILTER_MEAN_FILTER_H_ */
