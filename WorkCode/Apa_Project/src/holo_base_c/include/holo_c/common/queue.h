/*!
 * @file queue.h
 * @brief This header file defines Queue structure.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-9-4
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_COMMON_QUEUE_H_
#define HOLO_C_COMMON_QUEUE_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief struct Queuef represents a queue holding float point data.
 */
struct Queuef
{
    float32_t* base;
    uint32_t   capacity;
    uint32_t   head;
    uint32_t   tail;
};

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Constructor a queue with buffer and buffer_size.
 *
 * @param queue The queue object.
 * @param buffer float32_t type buffer.
 * @param buffer_size Size of the buffer.
 *
 * @return RC_SUCCESS
 * @return RC_QUEUE_INVALID_PARAMETER
 */
retcode_t queuef_init(struct Queuef* queue, float32_t* buffer, uint32_t buffer_size);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Push data into queue.
 *
 * @param queue The queue object.
 * @param data Input data.
 *
 * @return RC_QUEUE_OVERFLOW
 * @return RC_SUCCESS
 */
retcode_t queuef_push(struct Queuef* queue, float32_t data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Pop data from queue. The data will be removed from queue.
 *
 * @param queue The queue object.
 * @param data Output data.
 *
 * @return RC_QUEUE_UNDERFLOW.
 * @return RC_SUCCESS.
 */
retcode_t queuef_pop(struct Queuef* queue, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from queue without removing.
 *
 * @param queue The queue object.
 * @param data Output data.
 *
 * @return RC_QUEUE_UNDERFLOW.
 * @return RC_SUCCESS.
 */
retcode_t queuef_peek(const struct Queuef* queue, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if queue is full.
 *
 * @param queue The queue object.
 *
 * @return true
 * @return false
 */
bool_t queuef_is_full(const struct Queuef* queue);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if queue is empty.
 *
 * @param queue The queue object.
 *
 * @return true
 * @return false
 */
bool_t queuef_is_empty(const struct Queuef* queue);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get number of used elements in queue.
 *
 * @param queue The queue object.
 *
 * @return Number of elements.
 */
uint32_t queuef_get_size(const struct Queuef* queue);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get capacity of queue.
 *
 * @param queue The queue object.
 *
 * @return Capacity of queue.
 */
uint32_t queuef_get_capacity(const struct Queuef* queue);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from queue by index.
 *
 * @param queue The queue object.
 * @param index Data index. Queue head is indexed 0.
 * @param data Output data.
 *
 * @return RC_SUCCESS
 * @return RC_QUEUE_INDEX_OUT_OF_RANGE
 */
retcode_t queuef_get_data_by_index(const struct Queuef* queue, uint32_t index, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from queue by reverse index.
 *
 * @param queue The queue object.
 * @param index Data index. Queue tail is indexed 0.
 * @param data Output data.
 *
 * @return RC_SUCCESS
 * @return RC_QUEUE_INDEX_OUT_OF_RANGE
 */
retcode_t queuef_get_data_by_reverse_index(const struct Queuef* queue, uint32_t index, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from queue by index with no boundary check.
 *
 * @param queue The queue object.
 * @param index Data index. Queue head is indexed 0.
 *
 * @return Output data.
 */
float32_t queuef_get_data_by_index_unsafe(const struct Queuef* queue, uint32_t index);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from queue by reverse index with no boundary check.
 *
 * @param queue The queue object.
 * @param index Data index. Queue tail is indexed 0.
 *
 * @return Output data.
 */
float32_t queuef_get_data_by_reverse_index_unsafe(const struct Queuef* queue, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif
