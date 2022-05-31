/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_pvt.c
 * @brief This file implements GnssPvt type.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Apr 13, 2020
 */

#include <assert.h>
#include <holo_c/common/gnss_pvt.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_init(struct GnssPvt* self)
{
    assert(self != NULL);

    timestamp_init(&self->stamp);
    self->coordinate = coordinate_wgs84_create();
    self->status     = 0u;

    self->longitude = 0.0;
    self->latitude  = 0.0;
    self->height    = 0.0;

    self->velocity_east  = 0.0;
    self->velocity_north = 0.0;
    self->velocity_up    = 0.0;

    self->longitude_cov = 0.0;
    self->latitude_cov  = 0.0;
    self->height_cov    = 0.0;

    self->velocity_east_cov  = 0.0;
    self->velocity_north_cov = 0.0;
    self->velocity_up_cov    = 0.0;

    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Timestamp const* gnss_pvt_get_timestamp(struct GnssPvt const* self)
{
    assert(self != NULL);

    return &self->stamp;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_timestamp(struct GnssPvt* self, struct Timestamp const* timestamp)
{
    assert(self != NULL);
    assert(timestamp != NULL);

    return timestamp_init_from_timestamp(&self->stamp, timestamp);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Coordinate_t gnss_pvt_get_coordinate(struct GnssPvt const* self)
{
    assert(self != NULL);

    return self->coordinate;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_coordinate(struct GnssPvt* self, Coordinate_t coordinate)
{
    assert(self != NULL);

    self->coordinate = coordinate;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t gnss_pvt_is_position_valid(struct GnssPvt const* self)
{
    assert(self != NULL);

    return self->status & 0x01;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t gnss_pvt_is_velocity_valid(struct GnssPvt const* self)
{
    assert(self != NULL);

    return self->status & 0x02;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t gnss_pvt_is_position_cov_valid(struct GnssPvt const* self)
{
    assert(self != NULL);

    return self->status & 0x04;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t gnss_pvt_is_velocity_cov_valid(struct GnssPvt const* self)
{
    assert(self != NULL);

    return self->status & 0x08;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_valid_flags(struct GnssPvt* self, bool_t position, bool_t velocity, bool_t position_cov,
                                   bool_t velocity_cov)
{
    assert(self != NULL);

    self->status &= ~0x0f;
    self->status |= (position << 0u) | (velocity << 1u) | (position_cov << 2u) | (velocity_cov << 3u);

    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum GnssPvtMode gnss_pvt_get_mode(struct GnssPvt const* self)
{
    assert(self != NULL);

    return (enum GnssPvtMode)(self->status >> 8u);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_mode(struct GnssPvt* self, enum GnssPvtMode mode)
{
    assert(self != NULL);

    self->status &= ~(0xff << 8u);
    self->status |= ((uint32_t)mode) << 8u;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_longitude(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_position_valid(self));

    return self->longitude;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_longitude(struct GnssPvt* self, float64_t longitude)
{
    assert(self != NULL);

    self->longitude = longitude;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_latitude(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_position_valid(self));

    return self->latitude;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_latitude(struct GnssPvt* self, float64_t latitude)
{
    assert(self != NULL);

    self->latitude = latitude;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_height(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_position_valid(self));

    return self->height;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_height(struct GnssPvt* self, float64_t height)
{
    assert(self != NULL);

    self->height = height;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_velocity_east(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_velocity_valid(self));

    return self->velocity_east;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity_east(struct GnssPvt* self, float64_t velocity_east)
{
    assert(self != NULL);

    self->velocity_east = velocity_east;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_velocity_north(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_velocity_valid(self));

    return self->velocity_north;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity_north(struct GnssPvt* self, float64_t velocity_north)
{
    assert(self != NULL);

    self->velocity_north = velocity_north;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_velocity_up(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_velocity_valid(self));

    return self->velocity_up;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity_up(struct GnssPvt* self, float64_t velocity_up)
{
    assert(self != NULL);

    self->velocity_up = velocity_up;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_longitude_cov(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_position_cov_valid(self));

    return self->longitude_cov;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_longitude_cov(struct GnssPvt* self, float64_t longitude_cov)
{
    assert(self != NULL);

    self->longitude_cov = longitude_cov;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_latitude_cov(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_position_cov_valid(self));

    return self->latitude_cov;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_latitude_cov(struct GnssPvt* self, float64_t latitude_cov)
{
    assert(self != NULL);

    self->latitude_cov = latitude_cov;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_height_cov(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_position_cov_valid(self));

    return self->height_cov;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_height_cov(struct GnssPvt* self, float64_t height_cov)
{
    assert(self != NULL);

    self->height_cov = height_cov;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_velocity_east_cov(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_velocity_cov_valid(self));

    return self->velocity_east_cov;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity_east_cov(struct GnssPvt* self, float64_t velocity_east_cov)
{
    assert(self != NULL);

    self->velocity_east_cov = velocity_east_cov;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_velocity_north_cov(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_velocity_cov_valid(self));

    return self->velocity_north_cov;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity_north_cov(struct GnssPvt* self, float64_t velocity_north_cov)
{
    assert(self != NULL);

    self->velocity_north_cov = velocity_north_cov;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t gnss_pvt_get_velocity_up_cov(struct GnssPvt const* self)
{
    assert(self != NULL);
    assert(gnss_pvt_is_velocity_cov_valid(self));

    return self->velocity_up_cov;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity_up_cov(struct GnssPvt* self, float64_t velocity_up_cov)
{
    assert(self != NULL);

    self->velocity_up_cov = velocity_up_cov;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_position_by_values(struct GnssPvt* self, float64_t longitude, float64_t latitude,
                                          float64_t height)
{
    assert(self != NULL);

    self->longitude = longitude;
    self->latitude  = latitude;
    self->height    = height;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity_by_values(struct GnssPvt* self, float64_t velocity_east, float64_t velocity_north,
                                          float64_t velocity_up)
{
    assert(self != NULL);

    self->velocity_east  = velocity_east;
    self->velocity_north = velocity_north;
    self->velocity_up    = velocity_up;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_position_cov_by_values(struct GnssPvt* self, float64_t longitude_cov, float64_t latitude_cov,
                                              float64_t height_cov)
{
    assert(self != NULL);

    self->longitude_cov = longitude_cov;
    self->latitude_cov  = latitude_cov;
    self->height_cov    = height_cov;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity_cov_by_values(struct GnssPvt* self, float64_t velocity_east_cov,
                                              float64_t velocity_north_cov, float64_t velocity_up_cov)
{
    assert(self != NULL);

    self->velocity_east_cov  = velocity_east_cov;
    self->velocity_north_cov = velocity_north_cov;
    self->velocity_up_cov    = velocity_up_cov;
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_get_position(struct GnssPvt const* self, struct Point3d* position)
{
    assert(self != NULL);
    assert(gnss_pvt_is_position_valid(self));
    assert(point3d_is_valid(position));

    return point3d_init_from_scalars(position, self->longitude, self->latitude, self->height);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_position(struct GnssPvt* self, struct Point3d const* position)
{
    assert(self != NULL);
    assert(point3d_is_valid(position));

    self->longitude = point3d_get_x(position);
    self->latitude  = point3d_get_y(position);
    self->height    = point3d_get_z(position);
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_get_velocity(struct GnssPvt const* self, struct Point3d* velocity)
{
    assert(self != NULL);
    assert(gnss_pvt_is_velocity_valid(self));
    assert(point3d_is_valid(velocity));

    return point3d_init_from_scalars(velocity, self->velocity_east, self->velocity_north, self->velocity_up);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity(struct GnssPvt* self, struct Point3d const* velocity)
{
    assert(self != NULL);
    assert(point3d_is_valid(velocity));

    self->velocity_east  = point3d_get_x(velocity);
    self->velocity_north = point3d_get_y(velocity);
    self->velocity_up    = point3d_get_z(velocity);
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_get_position_cov(struct GnssPvt const* self, struct Point3d* position_cov)
{
    assert(self != NULL);
    assert(gnss_pvt_is_position_cov_valid(self));
    assert(point3d_is_valid(position_cov));

    return point3d_init_from_scalars(position_cov, self->longitude_cov, self->latitude_cov, self->height_cov);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_position_cov(struct GnssPvt* self, struct Point3d const* position_cov)
{
    assert(self != NULL);
    assert(point3d_is_valid(position_cov));

    self->longitude_cov = point3d_get_x(position_cov);
    self->latitude_cov  = point3d_get_y(position_cov);
    self->height_cov    = point3d_get_z(position_cov);
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_get_velocity_cov(struct GnssPvt const* self, struct Point3d* velocity_cov)
{
    assert(self != NULL);
    assert(gnss_pvt_is_velocity_cov_valid(self));
    assert(point3d_is_valid(velocity_cov));

    return point3d_init_from_scalars(velocity_cov, self->velocity_east_cov, self->velocity_north_cov,
                                     self->velocity_up_cov);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_set_velocity_cov(struct GnssPvt* self, struct Point3d const* velocity_cov)
{
    assert(self != NULL);
    assert(point3d_is_valid(velocity_cov));

    self->velocity_east_cov  = point3d_get_x(velocity_cov);
    self->velocity_north_cov = point3d_get_y(velocity_cov);
    self->velocity_up_cov    = point3d_get_z(velocity_cov);
    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t gnss_pvt_get_serialized_size(struct GnssPvt const* self)
{
    (void)self;

    return serialization_aligned_size(sizeof(struct GnssPvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_serialize(struct GnssPvt const* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0u;
    uint32_t  expected_size   = gnss_pvt_get_serialized_size(self);

    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += timestamp_serialize(&self->stamp, buffer, buffer_size);
        serialized_size += serialize_uint32(&self->coordinate, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_uint32(&self->status, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_float64(&self->longitude, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_float64(&self->latitude, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_float64(&self->height, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_float64(&self->velocity_east, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_float64(&self->velocity_north, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_float64(&self->velocity_up, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_float64(&self->longitude_cov, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_float64(&self->latitude_cov, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_float64(&self->height_cov, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_float64(&self->velocity_east_cov, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_float64(&self->velocity_north_cov, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_float64(&self->velocity_up_cov, buffer + serialized_size, buffer_size - serialized_size);

        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t gnss_pvt_deserialize(struct GnssPvt* self, uint8_t const* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = gnss_pvt_get_serialized_size(self);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += timestamp_deserialize(&self->stamp, buffer, buffer_size);
        deserialized_size +=
            deserialize_uint32(&self->coordinate, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_uint32(&self->status, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->longitude, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->latitude, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->height, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->velocity_east, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->velocity_north, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->velocity_up, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->longitude_cov, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->latitude_cov, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->height_cov, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->velocity_east_cov, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->velocity_north_cov, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float64(&self->velocity_up_cov, buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size +=
            deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}
