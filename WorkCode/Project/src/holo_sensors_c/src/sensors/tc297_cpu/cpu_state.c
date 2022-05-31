/*!
 * @file cpu_state.c
 * @brief This source file implements tc297 cpu state functions
 * @author liuya@holomatic.com
 * @date 2020-02-24
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <holo_c/sensors/tc297_cpu/cpu_state.h>
#include <holo_c/utils/serialization.h>

retcode_t cpu_state_set_timestamp(struct CpuState* state, const struct Timestamp* timestamp)
{
    assert(state != NULL);
    assert(timestamp != NULL);

    state->timestamp = *timestamp;

    return RC_SUCCESS;
}

retcode_t cpu_state_set_core_id(struct CpuState* state, uint16_t id)
{
    assert(state != NULL);

    state->core_id = id;

    return RC_SUCCESS;
}

retcode_t cpu_state_set_task_num(struct CpuState* state, uint16_t num)
{
    assert(state != NULL);

    state->task_num = num;

    return RC_SUCCESS;
}

retcode_t cpu_state_set_task_name(struct CpuState* state, uint16_t index, char* name)
{
    assert(state != NULL);
    assert(name != NULL);

    strcpy(state->list[index].task_name, name);

    return RC_SUCCESS;
}

retcode_t cpu_state_set_cpu_load(struct CpuState* state, uint16_t index, float32_t load)
{
    assert(state != NULL);

    state->list[index].cpu_load = load;

    return RC_SUCCESS;
}

const struct Timestamp* cpu_state_get_timestamp(struct CpuState* state)
{
    assert(state != NULL);

    return &state->timestamp;
}

uint16_t cpu_state_get_core_id(struct CpuState* state)
{
    assert(state != NULL);

    return state->core_id;
}

uint16_t cpu_state_get_task_num(struct CpuState* state)
{
    assert(state != NULL);

    return state->task_num;
}

char* cpu_state_get_task_name(struct CpuState* state, uint16_t index)
{
    assert(state != NULL);

    return state->list[index].task_name;
}

float32_t cpu_state_get_cpu_load(struct CpuState* state, uint16_t index)
{
    assert(state != NULL);

    return state->list[index].cpu_load;
}

static retcode_t serialize_data(const struct CpuState* state, uint8_t* buffer, uint32_t buffer_size)
{
    uint16_t i;
    uint32_t serialized_size = 0;

    serialized_size += timestamp_serialize(&state->timestamp, buffer, buffer_size);

    serialized_size += serialize_uint16(&state->core_id, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size += serialize_uint16(&state->task_num, buffer + serialized_size, buffer_size - serialized_size);

    for (i = 0; i < state->task_num; i++)
    {
        memcpy(buffer + serialized_size, state->list[i].task_name, TASK_NAME_MAX_LEN);
        serialized_size += TASK_NAME_MAX_LEN;

        serialized_size +=
            serialize_float32(&state->list[i].cpu_load, buffer + serialized_size, buffer_size - serialized_size);
    }

    return serialized_size;
}

static retcode_t deserialize_data(struct CpuState* state, const uint8_t* buffer, uint32_t buffer_size)
{
    uint8_t  i;
    uint32_t deserialized_size = 0;

    deserialized_size += timestamp_deserialize(&state->timestamp, buffer, buffer_size);

    deserialized_size +=
        deserialize_uint16(&state->core_id, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size +=
        deserialize_uint16(&state->task_num, buffer + deserialized_size, buffer_size - deserialized_size);

    for (i = 0; i < state->task_num; i++)
    {
        memcpy(state->list[i].task_name, buffer + deserialized_size, TASK_NAME_MAX_LEN);
        deserialized_size += TASK_NAME_MAX_LEN;

        deserialized_size +=
            deserialize_float32(&state->list[i].cpu_load, buffer + deserialized_size, buffer_size - deserialized_size);
    }

    return deserialized_size;
}

uint32_t cpu_state_get_serialized_size(const struct CpuState* state)
{
    assert(state != NULL);

    uint8_t  i;
    uint32_t size = 0;

    size += timestamp_get_serialized_size(&state->timestamp);
    size += 2 * sizeof(uint16_t);

    for (i = 0; i < state->task_num; i++)
    {
        size += TASK_NAME_MAX_LEN;
        size += sizeof(float32_t);
    }

    return serialization_aligned_size(size);
}

retcode_t cpu_state_serialize(const struct CpuState* state, uint8_t* buffer, uint32_t buffer_size)
{
    assert(state != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = cpu_state_get_serialized_size(state);

    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(state, buffer, buffer_size);

        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t cpu_state_deserialize(struct CpuState* state, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(state != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size;

    deserialized_size += deserialize_data(state, buffer, buffer_size);

    deserialized_size +=
        deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);

    expected_size = cpu_state_get_serialized_size(state);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}
