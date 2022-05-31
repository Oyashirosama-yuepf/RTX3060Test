/*!
 * @file dequeue.h
 * @brief This header file defines Dequeue structure.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-9-4
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_COMMON_DEQUEUE_H_
#define HOLO_C_COMMON_DEQUEUE_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief struct Dequeuef represents a dequeue holding float point data.
 */
struct Dequeuef
{
    float32_t* base;
    uint32_t   capacity;
    uint32_t   head;
    uint32_t   tail;
};

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Constructor a dequeue with buffer and buffer_size.
 *
 * @param dequeue The dequeue object.
 * @param buffer float32_t type buffer.
 * @param buffer_size Size of the buffer.
 *
 * @return RC_SUCCESS
 * @return RC_DEQUEUE_INVALID_PARAMETER
 */
retcode_t dequeuef_init(struct Dequeuef* dequeue, float32_t* buffer, uint32_t buffer_size);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Put data into front of dequeue.
 *
 * @param dequeue The dequeue object.
 * @param data Input data.
 *
 * @return RC_DEQUEUE_OVERFLOW
 * @return RC_SUCCESS
 */
retcode_t dequeuef_push_front(struct Dequeuef* dequeue, float32_t data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Put data into back of dequeue.
 *
 * @param dequeue The dequeue object.
 * @param data Input data.
 *
 * @return RC_DEQUEUE_OVERFLOW
 * @return RC_SUCCESS
 */
retcode_t dequeuef_push_back(struct Dequeuef* dequeue, float32_t data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from front of dequeue. The data will be removed from dequeue.
 *
 * @param dequeue The dequeue object.
 * @param data Output data.
 *
 * @return RC_DEQUEUE_UNDERFLOW.
 * @return RC_SUCCESS.
 */
retcode_t dequeuef_pop_front(struct Dequeuef* dequeue, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from back of dequeue. The data will be removed from dequeue.
 *
 * @param dequeue The dequeue object.
 * @param data Output data.
 *
 * @return RC_DEQUEUE_UNDERFLOW.
 * @return RC_SUCCESS.
 */
retcode_t dequeuef_pop_back(struct Dequeuef* dequeue, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from front of dequeue without removing.
 *
 * @param dequeue The dequeue object.
 * @param data Output data.
 *
 * @return RC_DEQUEUE_UNDERFLOW.
 * @return RC_SUCCESS.
 */
retcode_t dequeuef_peek_front(const struct Dequeuef* dequeue, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from back of dequeue without removing.
 *
 * @param dequeue The dequeue object.
 * @param data Output data.
 *
 * @return RC_DEQUEUE_UNDERFLOW.
 * @return RC_SUCCESS.
 */
retcode_t dequeuef_peek_back(const struct Dequeuef* dequeue, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if dequeue is full.
 *
 * @param dequeue The dequeue object.
 *
 * @return true
 * @return false
 */
bool_t dequeuef_is_full(const struct Dequeuef* dequeue);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if dequeue is empty.
 *
 * @param dequeue The dequeue object.
 *
 * @return true
 * @return false
 */
bool_t dequeuef_is_empty(const struct Dequeuef* dequeue);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get number of used elements in dequeue.
 *
 * @param dequeue The dequeue object.
 *
 * @return Number of elements.
 */
uint32_t dequeuef_get_size(const struct Dequeuef* dequeue);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get capacity of dequeue.
 *
 * @param dequeue The dequeue object.
 *
 * @return Capacity of dequeue.
 */
uint32_t dequeuef_get_capacity(const struct Dequeuef* dequeue);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from dequeue by index.
 *
 * @param dequeue The dequeue object
 * @param index Data index. Dequeue front is indexed 0.
 * @param data Output data.
 *
 * @return RC_SUCCESS
 * @return RC_DEQUEUE_INDEX_OUT_OF_RANGE
 */
retcode_t dequeuef_get_data_by_index(const struct Dequeuef* dequeue, uint32_t index, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from dequeue by reverse index.
 *
 * @param dequeue The dequeue object
 * @param index Data index. Dequeue back is indexed 0.
 * @param data Output data.
 *
 * @return RC_SUCCESS
 * @return RC_DEQUEUE_INDEX_OUT_OF_RANGE
 */
retcode_t dequeuef_get_data_by_reverse_index(const struct Dequeuef* dequeue, uint32_t index, float32_t* data);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from dequeue by index with no boundary check.
 *
 * @param dequeue The dequeue object.
 * @param index Data index. Dequeue front is indexed 0.
 *
 * @return Output data.
 */
float32_t dequeuef_get_data_by_index_unsafe(const struct Dequeuef* dequeue, uint32_t index);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get data from dequeue by reverse index with no boundary check.
 *
 * @param dequeue The dequeue object.
 * @param index Data index. Dequeue back is indexed 0.
 *
 * @return Output data.
 */
float32_t dequeuef_get_data_by_reverse_index_unsafe(const struct Dequeuef* dequeue, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif
