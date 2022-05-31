/*!
 * @file queue.c
 * @brief This file implements Queue structure.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-9-4
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo_c/common/queue.h>

static const uint32_t QUEUEF_MAX_BUFFER_SIZE = UINT32_MAX;

retcode_t queuef_init(struct Queuef* queue, float32_t* buffer, uint32_t buffer_size)
{
    retcode_t rc = RC_SUCCESS;
    if (0 == buffer_size || QUEUEF_MAX_BUFFER_SIZE == buffer_size)
    {
        rc = RC_QUEUE_INVALID_PARAMETER;
    }
    else
    {
        queue->base     = buffer;
        queue->capacity = buffer_size;
        queue->head     = QUEUEF_MAX_BUFFER_SIZE;
        queue->tail     = 0;
    }
    return rc;
}

retcode_t queuef_push(struct Queuef* queue, float32_t data)
{
    retcode_t rc = RC_SUCCESS;
    if (queue->head == queue->tail)
    {
        rc = RC_QUEUE_OVERFLOW;
    }
    else
    {
        queue->base[queue->tail] = data;
        if (QUEUEF_MAX_BUFFER_SIZE == queue->head)
        {
            queue->head = queue->tail;
        }
        queue->tail = (queue->tail + 1U) % queue->capacity;
    }
    return rc;
}

retcode_t queuef_pop(struct Queuef* queue, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (QUEUEF_MAX_BUFFER_SIZE == queue->head)
    {
        rc = RC_QUEUE_UNDERFLOW;
    }
    else
    {
        if (NULL != data)
        {
            *data = queue->base[queue->head];
        }
        queue->head = (queue->head + 1U) % queue->capacity;
        if (queue->head == queue->tail)
        {
            queue->head = QUEUEF_MAX_BUFFER_SIZE;
        }
    }
    return rc;
}

retcode_t queuef_peek(const struct Queuef* queue, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (QUEUEF_MAX_BUFFER_SIZE == queue->head)
    {
        rc = RC_QUEUE_UNDERFLOW;
    }
    else
    {
        *data = queue->base[queue->head];
    }
    return rc;
}

bool_t queuef_is_full(const struct Queuef* queue)
{
    return queue->head == queue->tail;
}

bool_t queuef_is_empty(const struct Queuef* queue)
{
    return queue->head == QUEUEF_MAX_BUFFER_SIZE;
}

uint32_t queuef_get_size(const struct Queuef* queue)
{
    return QUEUEF_MAX_BUFFER_SIZE == queue->head ?
               0U :
               queue->tail <= queue->head ? queue->tail + queue->capacity - queue->head : queue->tail - queue->head;
}

uint32_t queuef_get_capacity(const struct Queuef* queue)
{
    return queue->capacity;
}

retcode_t queuef_get_data_by_index(const struct Queuef* queue, uint32_t index, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (QUEUEF_MAX_BUFFER_SIZE == queue->head || index >= queuef_get_size(queue))
    {
        rc = RC_QUEUE_INDEX_OUT_OF_RANGE;
    }
    else
    {
        *data = queue->base[(queue->head + index) % queue->capacity];
    }
    return rc;
}

retcode_t queuef_get_data_by_reverse_index(const struct Queuef* queue, uint32_t index, float32_t* data)
{
    retcode_t rc = RC_SUCCESS;
    if (QUEUEF_MAX_BUFFER_SIZE == queue->head || index >= queuef_get_size(queue))
    {
        rc = RC_QUEUE_INDEX_OUT_OF_RANGE;
    }
    else
    {
        *data = queue->base[(queue->tail + queue->capacity - index - 1U) % queue->capacity];
    }
    return rc;
}

float32_t queuef_get_data_by_index_unsafe(const struct Queuef* queue, uint32_t index)
{
    return queue->base[(queue->head + index) % queue->capacity];
}

float32_t queuef_get_data_by_reverse_index_unsafe(const struct Queuef* queue, uint32_t index)
{
    return queue->base[(queue->tail + queue->capacity - index - 1U) % queue->capacity];
}
