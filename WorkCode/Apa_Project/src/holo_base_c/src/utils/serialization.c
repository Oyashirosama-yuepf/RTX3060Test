/**
 * @file serialization.c
 * @brief This header file implement utility functions for serialization and deserialization.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-11-1
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <string.h>
#include <holo_c/core/types.h>
#include <holo_c/core/retcode.h>
#include <holo_c/port/endian.h>
#include <holo_c/utils/serialization.h>

retcode_t serialize_int8(const int8_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int8_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint8_t*)buffer) = *((uint8_t*)obj);
        rc = sizeof(int8_t);
    }
    return rc;
}

retcode_t serialize_uint8(const uint8_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint8_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint8_t*)buffer) = *((uint8_t*)obj);
        rc = sizeof(uint8_t);
    }
    return rc;
}

retcode_t serialize_int16(const int16_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int16_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint16_t*)buffer) = hton16(*((uint16_t*)obj));
        rc = sizeof(int16_t);
    }
    return rc;
}

retcode_t serialize_uint16(const uint16_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint16_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint16_t*)buffer) = hton16(*((uint16_t*)obj));
        rc = sizeof(uint16_t);
    }
    return rc;
}

retcode_t serialize_int32(const int32_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int32_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint32_t*)buffer) = hton32(*((uint32_t*)obj));
        rc = sizeof(int32_t);
    }
    return rc;
}

retcode_t serialize_uint32(const uint32_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint32_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint32_t*)buffer) = hton32(*((uint32_t*)obj));
        rc = sizeof(uint32_t);
    }
    return rc;
}

retcode_t serialize_int64_4byte_aligned(const int64_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int64_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint32_t*)buffer) = hton32((uint32_t)((*obj) >> 32));
        *((uint32_t*)(buffer + sizeof(uint32_t))) = hton32((uint32_t)((*obj)));
        rc = sizeof(int64_t);
    }
    return rc;
}

retcode_t serialize_uint64_4byte_aligned(const uint64_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint64_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint32_t*)buffer) = hton32((uint32_t)((*obj) >> 32));
        *((uint32_t*)(buffer + sizeof(uint32_t))) = hton32((uint32_t)((*obj)));
        rc = sizeof(uint64_t);
    }
    return rc;
}

retcode_t serialize_int64_8byte_aligned(const int64_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int64_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint64_t*)buffer) = hton64(*((uint64_t*)obj));
        rc = sizeof(int64_t);
    }
    return rc;
}

retcode_t serialize_uint64_8byte_aligned(const uint64_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint64_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint64_t*)buffer) = hton64(*((uint64_t*)obj));
        rc = sizeof(uint64_t);
    }
    return rc;
}

retcode_t serialize_float32(const float32_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(float32_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint32_t*)buffer) = hton32(*((uint32_t*)obj));
        rc = sizeof(float32_t);
    }
    return rc;
}

retcode_t serialize_float64_4byte_aligned(const float64_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(float64_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint32_t*)buffer) = hton32((uint32_t)(*((uint64_t*)obj) >> 32));
        *((uint32_t*)(buffer + sizeof(uint32_t))) = hton32((uint32_t)(*((uint64_t*)obj)));
        rc = sizeof(float64_t);
    }
    return rc;
}

retcode_t serialize_float64_8byte_aligned(const float64_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(float64_t) > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        *((uint64_t*)buffer) = hton64(*((uint64_t*)obj));
        rc = sizeof(float64_t);
    }
    return rc;
}

retcode_t serialize_padding_4byte_aligned(uint32_t serialized_size, uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS; 
    uint32_t pad_size = (~serialized_size + 1) & 0x03;
    if(pad_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        memset(buffer, 0x00, pad_size);
        rc = (retcode_t)pad_size;
    }
    return rc;
}

retcode_t serialize_padding_8byte_aligned(uint32_t serialized_size, uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS; 
    uint32_t pad_size = (~serialized_size + 1) & 0x07;
    if(pad_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        memset(buffer, 0x00, pad_size);
        rc = (retcode_t)pad_size;
    }
    return rc;
}

retcode_t deserialize_int8(int8_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int8_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint8_t*)obj) = *buffer;
        rc = sizeof(int8_t);
    }
    return rc;
}

retcode_t deserialize_uint8(uint8_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint8_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint8_t*)obj) = *buffer;
        rc = sizeof(uint8_t);
    }
    return rc;
}

retcode_t deserialize_int16(int16_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int16_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint16_t*)obj) = ntoh16(*((uint16_t*)buffer));
        rc = sizeof(int16_t);
    }
    return rc;
}

retcode_t deserialize_uint16(uint16_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint16_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint16_t*)obj) = ntoh16(*((uint16_t*)buffer));
        rc = sizeof(uint16_t);
    }
    return rc;
}

retcode_t deserialize_int32(int32_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int32_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint32_t*)obj) = ntoh32(*((uint32_t*)buffer));
        rc = sizeof(int32_t);
    }
    return rc;
}

retcode_t deserialize_uint32(uint32_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint32_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint32_t*)obj) = ntoh32(*((uint32_t*)buffer));
        rc = sizeof(uint32_t);
    }
    return rc;
}

retcode_t deserialize_int64_4byte_aligned(int64_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int64_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint64_t*)obj) = (uint64_t)ntoh32(*(uint32_t*)buffer) << 32 | 
                            ntoh32(*(uint32_t*)(buffer + sizeof(uint32_t)));
        rc = sizeof(int64_t);
    }
    return rc;
}

retcode_t deserialize_uint64_4byte_aligned(uint64_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint64_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint64_t*)obj) = (uint64_t)ntoh32(*(uint32_t*)buffer) << 32 | 
                            ntoh32(*(uint32_t*)(buffer + sizeof(uint32_t)));
        rc = sizeof(uint64_t);
    }
    return rc;
}

retcode_t deserialize_int64_8byte_aligned(int64_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(int64_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint64_t*)obj) = ntoh64(*(uint64_t*)buffer);
        rc = sizeof(int64_t);
    }
    return rc;
}

retcode_t deserialize_uint64_8byte_aligned(uint64_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(uint64_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint64_t*)obj) = ntoh64(*(uint64_t*)buffer);
        rc = sizeof(uint64_t);
    }
    return rc;
}

retcode_t deserialize_float32(float32_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(float32_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint32_t*)obj) = ntoh32(*((uint32_t*)buffer));
        rc = sizeof(float32_t);
    }
    return rc;
}

retcode_t deserialize_float64_4byte_aligned(float64_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(float64_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint64_t*)obj) = (uint64_t)ntoh32(*(uint32_t*)buffer) << 32 | 
                            ntoh32(*(uint32_t*)(buffer + sizeof(uint32_t)));
        rc = sizeof(float64_t);
    }
    return rc;
}

retcode_t deserialize_float64_8byte_aligned(float64_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(obj != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    if(sizeof(float64_t) > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        *((uint64_t*)obj) = ntoh64(*(uint64_t*)buffer);
        rc = sizeof(float64_t);
    }
    return rc;
}

retcode_t deserialize_padding_4byte_aligned(uint32_t deserialized_size, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    (void)buffer;

    retcode_t rc = RC_SUCCESS; 
    uint32_t pad_size = (~deserialized_size + 1) & 0x03;
    if(pad_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        rc = (retcode_t)pad_size;
    }
    return rc;
}

retcode_t deserialize_padding_8byte_aligned(uint32_t deserialized_size, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    (void)buffer;

    retcode_t rc = RC_SUCCESS; 
    uint32_t pad_size = (~deserialized_size + 1) & 0x07;
    if(pad_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        rc = (retcode_t)pad_size;
    }
    return rc;
}


