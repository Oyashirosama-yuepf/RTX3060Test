/*!
 * @brief This file implements gnss position.
 * @author lichao@holomatic.com
 * @date Sep 06, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <holo_c/common/gnss_position.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_init(struct GnssPosition* self)
{
    assert(self != NULL);

    /* initialize members with default values */
    (void)timestamp_init(&self->stamp);
    self->coordinate    = coordinate_wgs84_create();
    self->latitude      = 0.0f;
    self->longitude     = 0.0f;
    self->altitude      = 0.0f;
    self->latitude_cov  = 0.0f;
    self->longitude_cov = 0.0f;
    self->altitude_cov  = 0.0f;
    self->status        = GNSS_POSITION_STATUS_ALLGOOD;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Timestamp* gnss_position_get_timestamp(const struct GnssPosition* self)
{
    assert(self != NULL);
	
    return &self->stamp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Coordinate_t gnss_position_get_coordinate(const struct GnssPosition* self)
{
    assert(self != NULL);
    return self->coordinate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum GnssPositionStatus gnss_position_get_status(const struct GnssPosition* self)
{
    assert(self != NULL);
    return self->status;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_position_get_latitude(const struct GnssPosition* self)
{
    assert(self != NULL);
    return self->latitude;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_position_get_longitude(const struct GnssPosition* self)
{
    assert(self != NULL);
    return self->longitude;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_position_get_altitude(const struct GnssPosition* self)
{
    assert(self != NULL);
    return self->altitude;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_position_get_latitude_covariance(const struct GnssPosition* self)
{
    assert(self != NULL);
    return self->latitude_cov;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_position_get_longitude_covariance(const struct GnssPosition* self)
{
    assert(self != NULL);
    return self->longitude_cov;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_position_get_altitude_covariance(const struct GnssPosition* self)
{
    assert(self != NULL);
    return self->altitude_cov;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_set_timestamp(struct GnssPosition* self, const struct Timestamp* stamp)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;
	
    self->stamp = *stamp;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_set_coordinate(struct GnssPosition* self, Coordinate_t coordinate)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->coordinate = coordinate;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_set_status(struct GnssPosition* self, enum GnssPositionStatus status)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->status = status;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_set_latitude(struct GnssPosition* self, float64_t lat)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->latitude = lat;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_set_longitude(struct GnssPosition* self, float64_t lon)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->longitude = lon;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_set_altitude(struct GnssPosition* self, float64_t alt)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->altitude = alt;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_set_latitude_covariance(struct GnssPosition* self, float64_t lat_cov)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->latitude_cov = lat_cov;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_set_longitude_covariance(struct GnssPosition* self, float64_t lon_cov)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->longitude_cov = lon_cov;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_set_altitude_covariance(struct GnssPosition* self, float64_t alt_cov)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->altitude_cov = alt_cov;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static retcode_t serialize_data(const struct GnssPosition* position, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size += timestamp_serialize(&position->stamp, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint32(&position->coordinate, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint32((uint32_t*)&position->status, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_float64(&position->latitude, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_float64(&position->longitude, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_float64(&position->altitude, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float64(&position->latitude_cov, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float64(&position->longitude_cov, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float64(&position->altitude_cov, buffer + serialized_size, buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static retcode_t deserialize_data(struct GnssPosition* position, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size += timestamp_deserialize(&position->stamp, buffer, buffer_size);
    deserialized_size +=
        deserialize_uint32(&position->coordinate, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint32((uint32_t*)&position->status, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_float64(&position->latitude, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_float64(&position->longitude, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_float64(&position->altitude, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_float64(&position->latitude_cov, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_float64(&position->longitude_cov, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_float64(&position->altitude_cov, buffer + deserialized_size, buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t gnss_position_get_serialized_size_4byte_aligned(const struct GnssPosition* position)
{
    (void)position;
    return serialization_4byte_aligned_size(sizeof(struct GnssPosition));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t gnss_position_get_serialized_size_8byte_aligned(const struct GnssPosition* position)
{
    (void)position;
    return serialization_8byte_aligned_size(sizeof(struct GnssPosition));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t gnss_position_get_serialized_size(const struct GnssPosition* position)
{
    (void)position;
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return gnss_position_get_serialized_size_4byte_aligned(position);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return gnss_position_get_serialized_size_8byte_aligned(position);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_serialize_4byte_aligned(const struct GnssPosition* position, uint8_t* buffer,
                                                uint32_t buffer_size)
{
    assert(position != NULL);
    assert(buffer != NULL);

    retcode_t      rc              = RC_SUCCESS;
    uint32_t       serialized_size = 0;
    const uint32_t expected_size   = gnss_position_get_serialized_size_4byte_aligned(position);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(position, buffer, buffer_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_serialize_8byte_aligned(const struct GnssPosition* position, uint8_t* buffer,
                                                uint32_t buffer_size)
{
    assert(position != NULL);
    assert(buffer != NULL);

    retcode_t      rc              = RC_SUCCESS;
    uint32_t       serialized_size = 0;
    const uint32_t expected_size   = gnss_position_get_serialized_size_8byte_aligned(position);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(position, buffer, buffer_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_serialize(const struct GnssPosition* position, uint8_t* buffer, uint32_t buffer_size)
{
    assert(position != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return gnss_position_serialize_4byte_aligned(position, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return gnss_position_serialize_8byte_aligned(position, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_deserialize_4byte_aligned(struct GnssPosition* position, const uint8_t* buffer,
                                                  uint32_t buffer_size)
{
    assert(position != NULL);
    assert(buffer != NULL);

    retcode_t      rc                = RC_SUCCESS;
    uint32_t       deserialized_size = 0;
    const uint32_t expected_size     = gnss_position_get_serialized_size_4byte_aligned(position);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(position, buffer, buffer_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_deserialize_8byte_aligned(struct GnssPosition* position, const uint8_t* buffer,
                                                  uint32_t buffer_size)
{
    assert(position != NULL);
    assert(buffer != NULL);

    retcode_t      rc                = RC_SUCCESS;
    uint32_t       deserialized_size = 0;
    const uint32_t expected_size     = gnss_position_get_serialized_size_8byte_aligned(position);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(position, buffer, buffer_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_position_deserialize(struct GnssPosition* position, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(position != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return gnss_position_deserialize_4byte_aligned(position, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return gnss_position_deserialize_8byte_aligned(position, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}
