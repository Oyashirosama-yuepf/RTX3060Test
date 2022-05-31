/**
 * @file light_signal_request.c
 * @brief the implementation of the light signal request
 * @author lijiawen@holomatic.com
 * @date 2019-11-28
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>

#include <holo_c/common/light_signal_request.h>
#include <holo_c/utils/serialization.h>

void light_signal_request_init_default(struct LightSignalRequest* request)
{
    assert(request != NULL);

    (void)timestamp_init(&(request->stamp));

    request->light_command.left_turn_signal  = 0;
    request->light_command.right_turn_signal = 0;
    request->light_command.hazard_flasher    = 0;
    request->light_command.brake_light       = 0;
}

const struct Timestamp* light_signal_request_get_timestamp(const struct LightSignalRequest* request)
{
    assert(request != NULL);

    return &(request->stamp);
}

void light_signal_request_set_timestamp(struct LightSignalRequest* request, const struct Timestamp* stamp)
{
    assert(request != NULL);
    assert(stamp != NULL);

    timestamp_init_from_timestamp(&request->stamp, stamp);
}

uint16_t light_signal_request_get_light_command(const struct LightSignalRequest* request)
{
    return request->light_command.brake_light << 2 | request->light_command.hazard_flasher << 5 |
           request->light_command.right_turn_signal << 6 | request->light_command.left_turn_signal << 7;
}

void light_signal_request_set_light_command(struct LightSignalRequest* request, uint16_t value)
{
    request->light_command.brake_light       = value >> 2;
    request->light_command.hazard_flasher    = value >> 5;
    request->light_command.right_turn_signal = value >> 6;
    request->light_command.left_turn_signal  = value >> 7;
}

bool_t light_signal_request_get_left_turn_signal(const struct LightSignalRequest* request)
{
    assert(request != NULL);

    return request->light_command.left_turn_signal;
}

void light_signal_request_set_left_turn_signal(struct LightSignalRequest* request, bool_t value)
{
    assert(request != NULL);

    request->light_command.left_turn_signal = value;
}

bool_t light_signal_request_get_right_turn_signal(const struct LightSignalRequest* request)
{
    assert(request != NULL);

    return request->light_command.right_turn_signal;
}

void light_signal_request_set_right_turn_signal(struct LightSignalRequest* request, bool_t value)
{
    assert(request != NULL);

    request->light_command.right_turn_signal = value;
}

bool_t light_signal_request_get_hazard_flasher(const struct LightSignalRequest* request)
{
    assert(request != NULL);

    return request->light_command.hazard_flasher;
}

void light_signal_request_set_hazard_flasher(struct LightSignalRequest* request, bool_t value)
{
    assert(request != NULL);

    request->light_command.hazard_flasher = value;
}

bool_t light_signal_request_get_brake_light(const struct LightSignalRequest* request)
{
    assert(request != NULL);

    return request->light_command.brake_light;
}

void light_signal_request_set_brake_light(struct LightSignalRequest* request, bool_t value)
{
    assert(request != NULL);

    request->light_command.brake_light = value;
}

uint32_t light_signal_request_get_serialized_size(const struct LightSignalRequest* request)
{
    (void)request;

    uint32_t size = 0;

    size += timestamp_get_serialized_size(&request->stamp);
    size += sizeof(request->light_command);
    size += 6 * sizeof(uint8_t);

    return serialization_aligned_size(size);
}

retcode_t light_signal_request_serialize(const struct LightSignalRequest* request, 
                                         uint8_t* buffer, 
                                         uint32_t buffer_size)
{
    assert(request != NULL);
    assert(buffer != NULL);

    uint32_t idx;
    uint32_t expected_size   = light_signal_request_get_serialized_size(request);
    uint32_t serialized_size = 0;

    retcode_t rc = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += timestamp_serialize(&request->stamp, 
                buffer, 
                buffer_size);

        serialized_size += serialize_uint16((const uint16_t*)&request->light_command, 
                buffer + serialized_size,
                buffer_size - serialized_size);

        for (idx = 0; idx < 6; idx++)
        {
            serialized_size += serialize_uint8(request->reserved + idx,
                    buffer + serialized_size,
                    buffer_size - serialized_size);
        }

        serialized_size += serialize_padding(serialized_size,
                buffer + serialized_size,
                buffer_size - serialized_size);

        assert(serialized_size == expected_size);

        rc = serialized_size;
    }

    return rc;
}

retcode_t light_signal_request_deserialize(struct LightSignalRequest* request, 
                                           const uint8_t* buffer,
                                           uint32_t buffer_size)
{
    assert(request != NULL);
    assert(buffer != NULL);

    light_signal_request_init_default(request);

    uint32_t idx;
    uint32_t expected_size     = light_signal_request_get_serialized_size(request);
    uint32_t deserialized_size = 0;

    retcode_t rc = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += timestamp_deserialize(&request->stamp, 
                buffer,
                buffer_size);

        deserialized_size += deserialize_uint16((uint16_t*)&request->light_command, 
                buffer + deserialized_size,
                buffer_size - deserialized_size);

        for (idx = 0; idx < 6; idx++)
        {
            deserialized_size += deserialize_uint8(&request->reserved[idx],
                    buffer + deserialized_size,
                    buffer_size - deserialized_size);
        }

        deserialized_size += deserialize_padding(deserialized_size,
                buffer + deserialized_size,
                buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);

        rc = deserialized_size;
    }

    return rc;
}

