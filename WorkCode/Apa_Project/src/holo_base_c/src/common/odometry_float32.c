/*!
 * @brief This file implements odometry.
 * @author lichao@holomatic.com
 * @date Sep 07, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/utils/serialization.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_init(struct Odometryf* self)
{
    assert(self != NULL);

    /* initialize members with default values */
    (void)timestamp_init(&self->stamp);
    self->parent_coordinate = coordinate_default_create();
    self->child_coordinate  = coordinate_default_create();
    pose3f_init(&self->pose);

    vectorf_init(&(self->velocity), 6u, self->velocity_data, VECTORF_MIN_BUF_SIZE(6u));
    matrixf_init(&(self->pose_covariance), 6u, 6u, self->pose_covariance_data, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_init(&(self->velocity_covariance), 6u, 6u, self->velocity_covariance_data, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    vectorf_init(&(self->linear_acceleration), 3u, self->linear_acceleration_data, VECTORF_MIN_BUF_SIZE(3u));

    /* initialize covariance matrix to identity matrix */
    matrixf_set_identity(&(self->pose_covariance));
    matrixf_set_identity(&(self->velocity_covariance));

    self->status = ODOMETRY_STATUS_ALLGOOD;
    self->source = ODOMETRY_SOURCE_UNKNOWN;

    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_init_from_odometryf(struct Odometryf* self, struct Odometryf const* other)
{
    assert(self != NULL);
    assert(other != NULL);

    timestamp_init_from_timestamp(&self->stamp, &other->stamp);
    self->parent_coordinate = other->parent_coordinate;
    self->child_coordinate  = other->child_coordinate;
    pose3f_init_from_pose3f(&self->pose, &other->pose);

    vectorf_init(&self->velocity, 6u, self->velocity_data, VECTORF_MIN_BUF_SIZE(6u));
    vectorf_set_from_vectorf(&self->velocity, &other->velocity);
    matrixf_init(&self->pose_covariance, 6u, 6u, self->pose_covariance_data, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_set_from_matrixf(&self->pose_covariance, &other->pose_covariance);
    matrixf_init(&self->velocity_covariance, 6u, 6u, self->velocity_covariance_data, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_set_from_matrixf(&self->velocity_covariance, &other->velocity_covariance);
    vectorf_init(&self->linear_acceleration, 3u, self->linear_acceleration_data, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set_from_vectorf(&self->linear_acceleration, &other->linear_acceleration);

    self->status = other->status;
    self->source = other->source;

    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Timestamp* odometryf_get_timestamp(const struct Odometryf* self)
{
    assert(self != NULL);
    return &self->stamp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Coordinate_t odometryf_get_coordinate(const struct Odometryf* self)
{
    assert(self != NULL);
    return self->parent_coordinate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Coordinate_t odometryf_get_child_coordinate(const struct Odometryf* self)
{
    assert(self != NULL);
    return self->child_coordinate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Pose3f* odometryf_get_pose(const struct Odometryf* self)
{
    assert(self != NULL);
    return &self->pose;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Vectorf* odometryf_get_velocity(const struct Odometryf* self)
{
    assert(self != NULL);
    return &self->velocity;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Matrixf* odometryf_get_pose_covariance(const struct Odometryf* self)
{
    assert(self != NULL);
    return &self->pose_covariance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Matrixf* odometryf_get_velocity_covariance(const struct Odometryf* self)
{
    assert(self != NULL);
    return &self->velocity_covariance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Vectorf* odometryf_get_linear_acceleration(const struct Odometryf* self)
{
    assert(self != NULL);
    return &self->linear_acceleration;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum OdometryStatus odometryf_get_status(const struct Odometryf* self)
{
    assert(self != NULL);
    return self->status;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum OdometrySource odometryf_get_source(const struct Odometryf* self)
{
    assert(self != NULL);
    return self->source;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_timestamp(struct Odometryf* self, const struct Timestamp* stamp)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->stamp = *stamp;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_coordinate(struct Odometryf* self, Coordinate_t coordinate)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->parent_coordinate = coordinate;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_child_coordinate(struct Odometryf* self, Coordinate_t coordinate)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->child_coordinate = coordinate;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_pose(struct Odometryf* self, const struct Pose3f* pose)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    pose3f_init_from_pose3f(&self->pose, pose);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_velocity(struct Odometryf* self, const struct Vectorf* velocity)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    vectorf_set_from_vectorf(&self->velocity, velocity);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_pose_covariance(struct Odometryf* self, const struct Matrixf* pose_cov)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    matrixf_set_from_matrixf(&self->pose_covariance, pose_cov);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_velocity_covariance(struct Odometryf* self, const struct Matrixf* velocity_cov)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    matrixf_set_from_matrixf(&self->velocity_covariance, velocity_cov);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_linear_acceleration(struct Odometryf* self, const struct Vectorf* linear_acceleration)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    rc = vectorf_set_from_vectorf(&self->linear_acceleration, linear_acceleration);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_status(struct Odometryf* self, enum OdometryStatus status)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->status = status;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_set_source(struct Odometryf* self, enum OdometrySource source)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->source = source;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Point3f* odometryf_get_translation(const struct Odometryf* self)
{
    assert(self != NULL);
    return pose3f_get_translation(&self->pose);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t odometryf_get_yaw(const struct Odometryf* self)
{
    assert(self != NULL);
    return pose3f_get_yaw(&self->pose);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t odometryf_get_linear_velocity_in_child_coord_orientation(const struct Odometryf* self, struct Vectorf* out)
{
    assert(self != NULL);

    /* 1. get 3D rotation R_wb from 3D pose */
    struct Rot3f rot_wb;
    rot3f_init_from_rot3f(&rot_wb, pose3f_get_rotation(&self->pose));

    /* 2. get 3D linear velocity V_w in world frame from odometry */
    struct Vectorf vel;
    float32_t      vel_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&vel, 6u, vel_buf, VECTORF_MIN_BUF_SIZE(6u));
    vectorf_set_from_vectorf(&vel, odometryf_get_velocity(self));

    /* 3. transform 3D linear velocity from world frame to child coord orientation
     *    V_b = R_bw * V_w */
    struct Vectorf vel_w;
    float32_t      vel_w_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vel_w, 3u, vel_w_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_get_segment(&vel, 0u, 3u, &vel_w);
    rot3f_unrotate_vector3f(&rot_wb, &vel_w, out);

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t odometryf_get_x_velocity_in_child_coord_orientation(const struct Odometryf* self)
{
    float32_t      out = 0.0f;
    struct Vectorf linear_vel;
    float32_t      linear_vel_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&linear_vel, 3u, linear_vel_buf, VECTORF_MIN_BUF_SIZE(3u));
    odometryf_get_linear_velocity_in_child_coord_orientation(self, &linear_vel);
    vectorf_get(&linear_vel, 0u, &out);
    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t odometryf_get_y_velocity_in_child_coord_orientation(const struct Odometryf* self)
{
    float32_t      out = 0.0f;
    struct Vectorf linear_vel;
    float32_t      linear_vel_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&linear_vel, 3, linear_vel_buf, VECTORF_MIN_BUF_SIZE(3u));
    odometryf_get_linear_velocity_in_child_coord_orientation(self, &linear_vel);
    vectorf_get((const struct Vectorf*)&linear_vel, 1u, &out);
    return out;
}

static retcode_t serialize_data(const struct Odometryf* self, uint8_t* buffer, uint32_t buffer_size)
{
    uint8_t  i;
    uint32_t serialized_size = 0;

    serialized_size += timestamp_serialize(&self->stamp, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size +=
        serialize_uint32(&self->parent_coordinate, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint32(&self->child_coordinate, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint32((uint32_t*)&self->source, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint32((uint32_t*)&self->status, buffer + serialized_size, buffer_size - serialized_size);

    for (i = 0; i < MATRIXF_MIN_BUF_SIZE(3u, 3u); i++)
    {
        serialized_size += serialize_float32(&self->pose.rotation.matrix_data[i], buffer + serialized_size,
                                             buffer_size - serialized_size);
    }
    serialized_size +=
        serialize_float32(&self->pose.translation.x, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&self->pose.translation.y, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&self->pose.translation.z, buffer + serialized_size, buffer_size - serialized_size);

    for (i = 0; i < VECTORF_MIN_BUF_SIZE(6u); i++)
    {
        serialized_size +=
            serialize_float32(&self->velocity_data[i], buffer + serialized_size, buffer_size - serialized_size);
    }

    for (i = 0; i < MATRIXF_MIN_BUF_SIZE(6u, 6u); i++)
    {
        serialized_size +=
            serialize_float32(&self->pose_covariance_data[i], buffer + serialized_size, buffer_size - serialized_size);
    }

    for (i = 0; i < MATRIXF_MIN_BUF_SIZE(6u, 6u); i++)
    {
        serialized_size += serialize_float32(&self->velocity_covariance_data[i], buffer + serialized_size,
                                             buffer_size - serialized_size);
    }

    for (i = 0; i < VECTORF_MIN_BUF_SIZE(3u); i++)
    {
        serialized_size += serialize_float32(&self->linear_acceleration_data[i], buffer + serialized_size,
                                             buffer_size - serialized_size);
    }

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct Odometryf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    uint8_t  i;
    uint32_t deserialized_size = 0;

    deserialized_size += timestamp_deserialize(&self->stamp, buffer, buffer_size);

    deserialized_size +=
        deserialize_uint32(&self->parent_coordinate, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint32(&self->child_coordinate, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint32((uint32_t*)&self->source, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint32((uint32_t*)&self->status, buffer + deserialized_size, buffer_size - deserialized_size);

    for (i = 0; i < MATRIXF_MIN_BUF_SIZE(3u, 3u); i++)
    {
        deserialized_size += deserialize_float32(&self->pose.rotation.matrix_data[i], buffer + deserialized_size,
                                                 buffer_size - deserialized_size);
    }
    deserialized_size +=
        deserialize_float32(&self->pose.translation.x, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_float32(&self->pose.translation.y, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_float32(&self->pose.translation.z, buffer + deserialized_size, buffer_size - deserialized_size);

    for (i = 0; i < VECTORF_MIN_BUF_SIZE(6u); i++)
    {
        deserialized_size +=
            deserialize_float32(&self->velocity_data[i], buffer + deserialized_size, buffer_size - deserialized_size);
    }

    for (i = 0; i < MATRIXF_MIN_BUF_SIZE(6u, 6u); i++)
    {
        deserialized_size += deserialize_float32(&self->pose_covariance_data[i], buffer + deserialized_size,
                                                 buffer_size - deserialized_size);
    }

    for (i = 0; i < MATRIXF_MIN_BUF_SIZE(6u, 6u); i++)
    {
        deserialized_size += deserialize_float32(&self->velocity_covariance_data[i], buffer + deserialized_size,
                                                 buffer_size - deserialized_size);
    }

    for (i = 0; i < VECTORF_MIN_BUF_SIZE(3u); i++)
    {
        deserialized_size += deserialize_float32(&self->linear_acceleration_data[i], buffer + deserialized_size,
                                                 buffer_size - deserialized_size);
    }

    return (retcode_t)deserialized_size;
}

uint32_t odometryf_get_serialized_size_4byte_aligned(const struct Odometryf* self)
{
    (void)self;
    uint32_t serialize_size = 0;

    // timesamp
    serialize_size += serialization_4byte_aligned_size(sizeof(struct Timestamp));
    // parent_coord + child_coord + source + status
    serialize_size += serialization_4byte_aligned_size(4 * sizeof(uint32_t));
    // pose.rotation + pose.translation data
    serialize_size += serialization_4byte_aligned_size(12 * sizeof(float32_t));
    // velocity_data
    serialize_size += serialization_4byte_aligned_size(6 * sizeof(float32_t));
    // pose_covariance_data
    serialize_size += serialization_4byte_aligned_size(36 * sizeof(float32_t));
    // velocity_covariance_data
    serialize_size += serialization_4byte_aligned_size(36 * sizeof(float32_t));
    // linear_acceleration_data
    serialize_size += serialization_4byte_aligned_size(3 * sizeof(float32_t));

    return serialize_size;
}

uint32_t odometryf_get_serialized_size_8byte_aligned(const struct Odometryf* self)
{
    (void)self;
    uint32_t serialize_size = 0;

    // timesamp
    serialize_size += serialization_8byte_aligned_size(sizeof(struct Timestamp));
    // parent_coord + child_coord + source + status
    serialize_size += serialization_8byte_aligned_size(4 * sizeof(uint32_t));
    // pose.rotation + pose.translation data
    serialize_size += serialization_8byte_aligned_size(12 * sizeof(float32_t));
    // velocity_data
    serialize_size += serialization_8byte_aligned_size(6 * sizeof(float32_t));
    // pose_covariance_data
    serialize_size += serialization_8byte_aligned_size(36 * sizeof(float32_t));
    // velocity_covariance_data
    serialize_size += serialization_8byte_aligned_size(36 * sizeof(float32_t));
    // linear_acceleration_data
    serialize_size += serialization_8byte_aligned_size(3 * sizeof(float32_t));

    return serialize_size;
}

uint32_t odometryf_get_serialized_size(const struct Odometryf* self)
{
    (void)self;

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return odometryf_get_serialized_size_4byte_aligned(self);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return odometryf_get_serialized_size_8byte_aligned(self);
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t odometryf_serialize_4byte_aligned(const struct Odometryf* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t      rc              = RC_SUCCESS;
    uint32_t       serialized_size = 0;
    const uint32_t expected_size   = odometryf_get_serialized_size_4byte_aligned(self);
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

retcode_t odometryf_serialize_8byte_aligned(const struct Odometryf* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t      rc              = RC_SUCCESS;
    uint32_t       serialized_size = 0;
    const uint32_t expected_size   = odometryf_get_serialized_size_8byte_aligned(self);
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

retcode_t odometryf_serialize(const struct Odometryf* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return odometryf_serialize_4byte_aligned(self, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return odometryf_serialize_8byte_aligned(self, buffer, buffer_size);
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t odometryf_deserialize_4byte_aligned(struct Odometryf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t      rc                = RC_SUCCESS;
    uint32_t       deserialized_size = 0;
    const uint32_t expected_size     = odometryf_get_serialized_size_4byte_aligned(self);

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

retcode_t odometryf_deserialize_8byte_aligned(struct Odometryf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t      rc                = RC_SUCCESS;
    uint32_t       deserialized_size = 0;
    const uint32_t expected_size     = odometryf_get_serialized_size_8byte_aligned(self);

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

retcode_t odometryf_deserialize(struct Odometryf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return odometryf_deserialize_4byte_aligned(self, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return odometryf_deserialize_8byte_aligned(self, buffer, buffer_size);
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
