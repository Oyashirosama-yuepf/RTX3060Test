/*!
 * @brief This file implements imu float32_t.
 * @author lichao@holomatic.com
 * @date Sep 07, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <holo_c/common/imu_float32.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_init(struct Imuf* self)
{
    assert(self != NULL);

    /* initialize members with default values */
    (void)timestamp_init(&self->stamp);
    self->coordinate = coordinate_default_create();
    vectorf_init(&(self->angular_velocity), 3, self->angular_velocity_data, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_init(&(self->linear_acceleration), 3, self->linear_acceleration_data, VECTORF_MIN_BUF_SIZE(3u));
    self->status = IMU_STATUS_ALLGOOD;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Timestamp* imuf_get_timestamp(const struct Imuf* self)
{
    assert(self != NULL);
    return &self->stamp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Coordinate_t imuf_get_coordinate(const struct Imuf* self)
{
    assert(self != NULL);
    return self->coordinate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Vectorf* imuf_get_angular_velocity(const struct Imuf* self)
{
    assert(self != NULL);
    return &self->angular_velocity;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_get_angular_velocity_value(const struct Imuf* self, float32_t* angle_rate_x, float32_t* angle_rate_y,
                                          float32_t* angle_rate_z)
{
    assert(3 == vectorf_get_size(&self->angular_velocity));

    if (angle_rate_x != NULL)
    {
        vectorf_get(&self->angular_velocity, 0, angle_rate_x);
    }

    if (angle_rate_y != NULL)
    {
        vectorf_get(&self->angular_velocity, 1, angle_rate_y);
    }

    if (angle_rate_z != NULL)
    {
        vectorf_get(&self->angular_velocity, 2, angle_rate_z);
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Vectorf* imuf_get_linear_acceleration(const struct Imuf* self)
{
    assert(self != NULL);
    return &self->linear_acceleration;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_get_linear_acceleration_value(const struct Imuf* self, float32_t* acc_x, float32_t* acc_y,
                                             float32_t* acc_z)
{
    assert(3 == vectorf_get_size(&self->linear_acceleration));

    if (acc_x != NULL)
    {
        vectorf_get(&self->linear_acceleration, 0, acc_x);
    }

    if (acc_y != NULL)
    {
        vectorf_get(&self->linear_acceleration, 1, acc_y);
    }

    if (acc_z != NULL)
    {
        vectorf_get(&self->linear_acceleration, 2, acc_z);
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum ImuStatus imuf_get_status(const struct Imuf* self)
{
    assert(self != NULL);
    return self->status;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_set_timestamp(struct Imuf* self, const struct Timestamp* stamp)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->stamp = *stamp;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_set_coordinate(struct Imuf* self, Coordinate_t coordinate)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->coordinate = coordinate;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_set_angular_velocity(struct Imuf* self, const struct Vectorf* angular_velocity)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    vectorf_set_from_vectorf(&self->angular_velocity, angular_velocity);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_set_angular_velocity_value(struct Imuf* self, const float32_t angle_rate_x, const float32_t angle_rate_y,
                                          const float32_t angle_rate_z)
{
    assert(self != NULL);

    vectorf_set(&self->angular_velocity, 0, angle_rate_x);
    vectorf_set(&self->angular_velocity, 1, angle_rate_y);
    vectorf_set(&self->angular_velocity, 2, angle_rate_z);

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_set_linear_acceleration(struct Imuf* self, const struct Vectorf* linear_acceleration)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    vectorf_set_from_vectorf(&self->linear_acceleration, linear_acceleration);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_set_linear_acceleration_value(struct Imuf* self, const float32_t acc_x, float32_t acc_y, float32_t acc_z)
{
    assert(self != NULL);

    vectorf_set(&self->linear_acceleration, 0, acc_x);
    vectorf_set(&self->linear_acceleration, 1, acc_y);
    vectorf_set(&self->linear_acceleration, 2, acc_z);

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_set_status(struct Imuf* self, enum ImuStatus status)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->status = status;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static retcode_t serialize_data(const struct Imuf* self, uint8_t* buffer, uint32_t buffer_size)
{
    uint8_t  i;
    uint32_t serialized_size = 0;

    serialized_size += timestamp_serialize(&self->stamp, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint32(&self->coordinate, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint32((uint32_t*)&self->status, buffer + serialized_size, buffer_size - serialized_size);

    for (i = 0; i < 3; i++)
    {
        serialized_size +=
            serialize_float32(&self->angular_velocity_data[i], buffer + serialized_size, buffer_size - serialized_size);
    }

    for (i = 0; i < 3; i++)
    {
        serialized_size += serialize_float32(&self->linear_acceleration_data[i], buffer + serialized_size,
                                             buffer_size - serialized_size);
    }

    return (retcode_t)serialized_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static retcode_t deserialize_data(struct Imuf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    uint8_t  i;
    uint32_t deserialized_size = 0;

    deserialized_size += timestamp_deserialize(&self->stamp, buffer, buffer_size);
    deserialized_size += deserialize_uint32(&self->coordinate, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint32((uint32_t*)&self->status, buffer + deserialized_size, buffer_size - deserialized_size);

    for (i = 0; i < 3; i++)
    {
        deserialized_size += deserialize_float32(&self->angular_velocity_data[i], buffer + deserialized_size,
                                                 buffer_size - deserialized_size);
    }

    for (i = 0; i < 3; i++)
    {
        deserialized_size += deserialize_float32(&self->linear_acceleration_data[i], buffer + deserialized_size,
                                                 buffer_size - deserialized_size);
    }

    return (retcode_t)deserialized_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t imuf_get_serialized_size_4byte_aligned(const struct Imuf* self)
{
    (void)self;
    uint32_t serialize_size = 0;

    serialize_size += serialization_4byte_aligned_size(sizeof(struct Timestamp));
    serialize_size += serialization_4byte_aligned_size(sizeof(Coordinate_t));
    serialize_size += serialization_4byte_aligned_size(sizeof(enum ImuStatus));
    serialize_size += serialization_4byte_aligned_size(3 * sizeof(float32_t));
    serialize_size += serialization_4byte_aligned_size(3 * sizeof(float32_t));

    return serialize_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t imuf_get_serialized_size_8byte_aligned(const struct Imuf* self)
{
    (void)self;
    uint32_t serialize_size = 0;

    serialize_size += serialization_8byte_aligned_size(sizeof(struct Timestamp));
    serialize_size += serialization_8byte_aligned_size(2 * sizeof(uint32_t));
    serialize_size += serialization_8byte_aligned_size(6 * sizeof(float32_t));

    return serialize_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t imuf_get_serialized_size(const struct Imuf* self)
{
    (void)self;
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return imuf_get_serialized_size_4byte_aligned(self);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return imuf_get_serialized_size_8byte_aligned(self);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_serialize_4byte_aligned(const struct Imuf* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = imuf_get_serialized_size_4byte_aligned(self);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(self, buffer, buffer_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_serialize_8byte_aligned(const struct Imuf* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = imuf_get_serialized_size_8byte_aligned(self);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(self, buffer, buffer_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_serialize(const struct Imuf* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return imuf_serialize_4byte_aligned(self, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return imuf_serialize_8byte_aligned(self, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_deserialize_4byte_aligned(struct Imuf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = imuf_get_serialized_size_4byte_aligned(self);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(self, buffer, buffer_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_deserialize_8byte_aligned(struct Imuf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = imuf_get_serialized_size_8byte_aligned(self);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(self, buffer, buffer_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imuf_deserialize(struct Imuf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return imuf_deserialize_4byte_aligned(self, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return imuf_deserialize_8byte_aligned(self, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
