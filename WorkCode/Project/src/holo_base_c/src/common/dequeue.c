/*!
 * @file dequeue.c
 * @brief This file implements Dequeue structure.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-9-6
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo_c/common/dequeue.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

static const uint32_t DEQUEUEF_MAX_BUFFER_SIZE = UINT32_MAX;

retcode_t dequeuef_init(struct Dequeuef* dequeue, float32_t* buffer, uint32_t buffer_size)
{
    retcode_t rc = RC_SUCCESS;
    if (0 == buffer_size || DEQUEUEF_MAX_BUFFER_SIZE == buffer_size)
    {
        rc = RC_DEQUEUE_INVALID_PARAMETER;
    }
    else
    {
        dequeue->base     = buffer;
        dequeue->capacity = buffer_size;
        dequeue->head     = DEQUEUEF_MAX_BUFFER_SIZE;
        dequeue->tail     = 0;
    }
    return rc;
}

retcode_t dequeuef_push_back(struct Dequeuef* dequeue, float32_t data)
{
    retcode_t rc = RC_SUCCESS;
    if (dequeue->head == dequeue->tail)
    {
        rc = RC_DEQUEUE_OVERFLOW;
    }
    else
    {
        dequeue->base[dequeue->tail] = data;
        if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head)
        {
            dequeue->head = dequeue->tail;
        }
        dequeue->tail = (dequeue->tail + 1) % dequeue->capacity;
    }
    return rc;
}

retcode_t dequeuef_push_front(struct Dequeuef* dequeue, float32_t data)
{
    retcode_t rc = RC_SUCCESS;
    if (dequeue->head == dequeue->tail)
    {
        rc = RC_DEQUEUE_OVERFLOW;
    }
    else
    {
        if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head)
        {
            dequeue->head = (dequeue->tail + dequeue->capacity - 1) % dequeue->capacity;
        }
        else
        {
            dequeue->head = (dequeue->head + dequeue->capacity - 1) % dequeue->capacity;
        }
        dequeue->base[dequeue->head] = data;
    }
    return rc;
}

retcode_t dequeuef_pop_back(struct Dequeuef* dequeue, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head)
    {
        rc = RC_DEQUEUE_UNDERFLOW;
    }
    else
    {
        dequeue->tail = (dequeue->tail + dequeue->capacity - 1) % dequeue->capacity;
        if (NULL != data)
        {
            *data = dequeue->base[dequeue->tail];
        }
        if (dequeue->head == dequeue->tail)
        {
            dequeue->head = DEQUEUEF_MAX_BUFFER_SIZE;
        }
    }
    return rc;
}

retcode_t dequeuef_pop_front(struct Dequeuef* dequeue, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head)
    {
        rc = RC_DEQUEUE_UNDERFLOW;
    }
    else
    {
        if (NULL != data)
        {
            *data = dequeue->base[dequeue->head];
        }
        dequeue->head = (dequeue->head + 1) % dequeue->capacity;
        if (dequeue->head == dequeue->tail)
        {
            dequeue->head = DEQUEUEF_MAX_BUFFER_SIZE;
        }
    }
    return rc;
}

retcode_t dequeuef_peek_front(const struct Dequeuef* dequeue, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head)
    {
        rc = RC_DEQUEUE_UNDERFLOW;
    }
    else
    {
        *data = dequeue->base[dequeue->head];
    }
    return rc;
}

retcode_t dequeuef_peek_back(const struct Dequeuef* dequeue, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head)
    {
        rc = RC_DEQUEUE_UNDERFLOW;
    }
    else
    {
        *data = dequeue->base[(dequeue->tail + dequeue->capacity - 1) % dequeue->capacity];
    }
    return rc;
}

bool_t dequeuef_is_full(const struct Dequeuef* dequeue)
{
    return dequeue->head == dequeue->tail;
}

bool_t dequeuef_is_empty(const struct Dequeuef* dequeue)
{
    return dequeue->head == DEQUEUEF_MAX_BUFFER_SIZE;
}

uint32_t dequeuef_get_size(const struct Dequeuef* dequeue)
{
    return DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head ?
               0 :
               dequeue->tail <= dequeue->head ? dequeue->tail + dequeue->capacity - dequeue->head :
                                                dequeue->tail - dequeue->head;
}

uint32_t dequeuef_get_capacity(const struct Dequeuef* dequeue)
{
    return dequeue->capacity;
}

retcode_t dequeuef_get_data_by_index(const struct Dequeuef* dequeue, uint32_t index, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head || index >= dequeuef_get_size(dequeue))
    {
        rc = RC_DEQUEUE_INDEX_OUT_OF_RANGE;
    }
    else
    {
        *data = dequeue->base[(dequeue->head + index) % dequeue->capacity];
    }
    return rc;
}

retcode_t dequeuef_get_data_by_reverse_index(const struct Dequeuef* dequeue, uint32_t index, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head || index >= dequeuef_get_size(dequeue))
    {
        rc = RC_DEQUEUE_INDEX_OUT_OF_RANGE;
    }
    else
    {
        *data = dequeue->base[(dequeue->tail + dequeue->capacity - index - 1) % dequeue->capacity];
    }
    return rc;
}

float32_t dequeuef_get_data_by_index_unsafe(const struct Dequeuef* dequeue, uint32_t index)
{
    return dequeue->base[(dequeue->head + index) % dequeue->capacity];
}

float32_t dequeuef_get_data_by_reverse_index_unsafe(const struct Dequeuef* dequeue, uint32_t index)
{
    return dequeue->base[(dequeue->tail + dequeue->capacity - index - 1) % dequeue->capacity];
}
