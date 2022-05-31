/**
 * @file someip.c
 * @brief This file implements SomeIP related functions.
 * @author liuya(liuya@holomaitc.com)
 * @date 2019-12-7
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <holo_c/common/someip.h>
#include <holo_c/utils/serialization.h>
#include <string.h>

retcode_t someip_packet_init_default(struct SomeipPacket* packet)
{
    someip_packet_set_service_id(packet, 0x00);
    someip_packet_set_method_id(packet, 0x00);
    someip_packet_set_message_length(packet, 0x08);
    someip_packet_set_client_id(packet, 0x00);
    someip_packet_set_session_id(packet, 0x00);
    someip_packet_set_protocol_version(packet, 0x00);
    someip_packet_set_interface_version(packet, 0x00);
    someip_packet_set_message_type(packet, 0x00);
    someip_packet_set_return_code(packet, 0x00);
    memset(packet->payload, 0, SOMEIP_PAYLOAD_MAX_LENGTH);

    return RC_SUCCESS;
}

static retcode_t serialize_data(const struct SomeipPacket* packet, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;
    uint32_t message_id      = 0;
    uint32_t request_id      = 0;

    message_id |= someip_packet_get_service_id(packet);
    message_id <<= 16;
    message_id |= someip_packet_get_method_id(packet);

    request_id = someip_packet_get_client_id(packet);
    request_id <<= 16;
    request_id |= someip_packet_get_session_id(packet);

    serialized_size += serialize_uint32(&message_id, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint32(&packet->msg_length, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint32(&request_id, buffer + serialized_size, buffer_size - serialized_size);

    memcpy(buffer + serialized_size, &packet->proto_ver, sizeof(uint32_t));
    serialized_size += sizeof(uint32_t);

    memcpy(buffer + serialized_size, &packet->payload, (packet->msg_length - 8));
    serialized_size += packet->msg_length - 8;

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct SomeipPacket* packet, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;
    uint32_t message_id        = 0;
    uint32_t request_id        = 0;

    deserialized_size += deserialize_uint32(&message_id, buffer + deserialized_size, buffer_size - deserialized_size);
    someip_packet_set_service_id(packet, (message_id >> 16));
    someip_packet_set_method_id(packet, (message_id & 0xFFFF));

    deserialized_size +=
        deserialize_uint32(&packet->msg_length, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size += deserialize_uint32(&request_id, buffer + deserialized_size, buffer_size - deserialized_size);
    someip_packet_set_client_id(packet, (request_id >> 16));
    someip_packet_set_session_id(packet, (request_id & 0xFFFF));

    memcpy(&packet->proto_ver, buffer + deserialized_size, sizeof(uint32_t));
    deserialized_size += sizeof(uint32_t);

    memcpy(packet->payload, buffer + deserialized_size, (packet->msg_length - 8));
    deserialized_size += packet->msg_length - 8;

    return (retcode_t)deserialized_size;
}

uint32_t someip_packet_get_serialized_size_4byte_aligned(const struct SomeipPacket* packet)
{
    (void)packet;

    return serialization_4byte_aligned_size(4 * sizeof(uint32_t) + packet->msg_length - 8);
}

uint32_t someip_packet_get_serialized_size_8byte_aligned(const struct SomeipPacket* packet)
{
    (void)packet;

    return serialization_8byte_aligned_size(4 * sizeof(uint32_t) + packet->msg_length - 8);
}

uint32_t someip_packet_get_serialized_size(const struct SomeipPacket* packet)
{
    (void)packet;

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return someip_packet_get_serialized_size_4byte_aligned(packet);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return someip_packet_get_serialized_size_8byte_aligned(packet);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t someip_packet_serialize_4byte_aligned(const struct SomeipPacket* packet, uint8_t* buffer,
                                                uint32_t buffer_size)
{
    assert(packet != NULL);
    assert(buffer != NULL);

    retcode_t      rc              = RC_SUCCESS;
    uint32_t       serialized_size = 0;
    const uint32_t expected_size   = someip_packet_get_serialized_size_4byte_aligned(packet);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(packet, buffer, buffer_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t someip_packet_serialize_8byte_aligned(const struct SomeipPacket* packet, uint8_t* buffer,
                                                uint32_t buffer_size)
{
    assert(packet != NULL);
    assert(buffer != NULL);

    retcode_t      rc              = RC_SUCCESS;
    uint32_t       serialized_size = 0;
    const uint32_t expected_size   = someip_packet_get_serialized_size_8byte_aligned(packet);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(packet, buffer, buffer_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t someip_packet_serialize(const struct SomeipPacket* packet, uint8_t* buffer, uint32_t buffer_size)
{
    assert(packet != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return someip_packet_serialize_4byte_aligned(packet, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return someip_packet_serialize_8byte_aligned(packet, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t someip_packet_deserialize_4byte_aligned(struct SomeipPacket* packet, const uint8_t* buffer,
                                                  uint32_t buffer_size)
{
    assert(packet != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = 0;

    deserialized_size += deserialize_data(packet, buffer, buffer_size);
    deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                           buffer_size - deserialized_size);

    expected_size = someip_packet_get_serialized_size_4byte_aligned(packet);

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

retcode_t someip_packet_deserialize_8byte_aligned(struct SomeipPacket* packet, const uint8_t* buffer,
                                                  uint32_t buffer_size)
{
    assert(packet != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = 0;

    deserialized_size += deserialize_data(packet, buffer, buffer_size);
    deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                           buffer_size - deserialized_size);

    expected_size = someip_packet_get_serialized_size_8byte_aligned(packet);

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

retcode_t someip_packet_deserialize(struct SomeipPacket* packet, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(packet != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return someip_packet_deserialize_4byte_aligned(packet, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return someip_packet_deserialize_8byte_aligned(packet, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t someip_packet_get_payload(const struct SomeipPacket* packet, uint8_t* buffer, uint8_t buffer_size)
{
    retcode_t rc = RC_SUCCESS;

    if (buffer_size < packet->msg_length - 8)
    {
        rc = RC_FAIL;
    }
    else
    {
        memcpy(buffer, packet->payload, (packet->msg_length - 8));

        rc = (retcode_t)(packet->msg_length - 8);
    }

    return rc;
}

retcode_t someip_packet_set_payload(struct SomeipPacket* packet, const uint8_t* buffer, uint32_t len)
{
    retcode_t rc = RC_SUCCESS;

    if (len > SOMEIP_PAYLOAD_MAX_LENGTH)
    {
        rc = RC_FAIL;
    }
    else
    {
        memcpy(packet->payload, buffer, len);
    }

    return rc;
}
