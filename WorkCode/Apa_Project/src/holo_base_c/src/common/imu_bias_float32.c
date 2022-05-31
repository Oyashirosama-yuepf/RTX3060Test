/*!
 * @brief This file implements imu bias.
 * @author lichao@holomatic.com
 * @date Sep 06, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */
#include <assert.h>
#include <holo_c/common/imu_bias_float32.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imu_biasf_init(struct ImuBiasf* self)
{
    assert(self != NULL);

    /* initialize members with default values */
    (void)timestamp_init(&self->stamp);
    self->coordinate = coordinate_default_create();
    vectorf_init(&self->angular_velocity_bias, 3, self->angular_velocity_bias_data, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_init(&self->linear_acceleration_bias, 3, self->linear_acceleration_bias_data, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_init(&self->angular_velocity_bias_cov, 3, self->angular_velocity_bias_cov_data, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_init(&self->linear_acceleration_bias_cov, 3, self->linear_acceleration_bias_cov_data,
                 VECTORF_MIN_BUF_SIZE(3u));

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Timestamp* imu_biasf_get_timestamp(const struct ImuBiasf* self)
{
    assert(self != NULL);

    return &self->stamp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imu_biasf_set_timestamp(struct ImuBiasf* self, const struct Timestamp* stamp)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->stamp = *stamp;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Coordinate_t imu_biasf_get_coordinate(const struct ImuBiasf* self)
{
    assert(self != NULL);

    return self->coordinate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imu_biasf_set_coordinate(struct ImuBiasf* self, Coordinate_t coordinate)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->coordinate = coordinate;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Vectorf* imu_biasf_get_angular_velocity_bias(const struct ImuBiasf* self)
{
    return &self->angular_velocity_bias;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imu_biasf_set_angular_velocity_bias(struct ImuBiasf* self, const struct Vectorf* angular_velocity_bias)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    vectorf_set_from_vectorf(&self->angular_velocity_bias, angular_velocity_bias);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Vectorf* imu_biasf_get_linear_acceleration_bias(const struct ImuBiasf* self)
{
    return &self->linear_acceleration_bias;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imu_biasf_set_linear_acceleration_bias(struct ImuBiasf* self, const struct Vectorf* linear_acceleration_bias)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    vectorf_set_from_vectorf(&self->linear_acceleration_bias, linear_acceleration_bias);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Vectorf* imu_biasf_get_angular_velocity_bias_covariance(const struct ImuBiasf* self)
{
    return &self->angular_velocity_bias_cov;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imu_biasf_set_angular_velocity_bias_covariance(struct ImuBiasf*      self,
                                                         const struct Vectorf* angular_velocity_bias_cov)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    vectorf_set_from_vectorf(&self->angular_velocity_bias_cov, angular_velocity_bias_cov);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Vectorf* imu_biasf_get_linear_acceleration_bias_covariance(const struct ImuBiasf* self)
{
    return &self->linear_acceleration_bias_cov;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imu_biasf_set_linear_acceleration_bias_covariance(struct ImuBiasf*      self,
                                                            const struct Vectorf* linear_acceleration_bias_cov)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    vectorf_set_from_vectorf(&self->linear_acceleration_bias_cov, linear_acceleration_bias_cov);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t imu_biasf_get_serialized_size(const struct ImuBiasf* self)
{
    (void)self;

    uint32_t size = 0;

    size += vectorf_get_serialized_size(&self->angular_velocity_bias);
    size += vectorf_get_serialized_size(&self->linear_acceleration_bias);
    size += vectorf_get_serialized_size(&self->angular_velocity_bias_cov);
    size += vectorf_get_serialized_size(&self->linear_acceleration_bias_cov);
    size += timestamp_get_serialized_size(&self->stamp);
    size += sizeof(self->coordinate);

    return serialization_aligned_size(size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imu_biasf_serialize(const struct ImuBiasf* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc;
    uint32_t serialized_size = 0;
    uint32_t expected_size = imu_biasf_get_serialized_size(self);

    if(buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += vectorf_serialize(&self->angular_velocity_bias, 
                buffer, 
                buffer_size);

        serialized_size += vectorf_serialize(&self->linear_acceleration_bias, 
                buffer + serialized_size, 
                buffer_size - serialized_size);

        serialized_size += vectorf_serialize(&self->angular_velocity_bias_cov, 
                buffer + serialized_size, 
                buffer_size - serialized_size);

        serialized_size += vectorf_serialize(&self->linear_acceleration_bias_cov, 
                buffer + serialized_size, 
                buffer_size - serialized_size);

        serialized_size += timestamp_serialize(&self->stamp, 
                buffer + serialized_size, 
                buffer_size - serialized_size);

        serialized_size += serialize_uint32(&self->coordinate, 
                buffer + serialized_size, 
                buffer_size - serialized_size);

        serialized_size += serialize_padding(serialized_size, 
                buffer + serialized_size, 
                buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t imu_biasf_deserialize(struct ImuBiasf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = imu_biasf_get_serialized_size(self);

    if(buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += vectorf_deserialize(&self->angular_velocity_bias, 
                buffer, 
                buffer_size);

        deserialized_size += vectorf_deserialize(&self->linear_acceleration_bias, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        deserialized_size += vectorf_deserialize(&self->angular_velocity_bias_cov, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        deserialized_size += vectorf_deserialize(&self->linear_acceleration_bias_cov, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        deserialized_size += timestamp_deserialize(&self->stamp, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        deserialized_size += deserialize_uint32(&self->coordinate, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        deserialized_size += deserialize_padding(deserialized_size,
                buffer + deserialized_size,
                buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
