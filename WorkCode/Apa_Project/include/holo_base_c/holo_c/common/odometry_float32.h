/*!
 * @file odometry_float32.h
 * @brief This header file define generic odometry measurement.
 * @author lichao@holomatic.com
 * @date Sep 13, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_COMMON_ODOMETRY_FLOAT32_H_
#define HOLO_C_COMMON_ODOMETRY_FLOAT32_H_

#include <holo_c/common/coordinate.h>
#include <holo_c/common/measurement_appendix.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/pose3_float32.h>
#include <holo_c/numerics/matrix_float32.h>
#include <holo_c/numerics/vector_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief define generic odometry measurement in float32_t
 *
 */
struct Odometryf
{
    struct Timestamp    stamp;
    Coordinate_t        parent_coordinate;
    Coordinate_t        child_coordinate; /* child coordinate */
    enum OdometrySource source;           /* odometry source */
    enum OdometryStatus status;           /* odometry status */
    struct Pose3f       pose;             /* 3D pose including position in meters and rotation in radians */
    struct Vectorf      velocity;         /* 3D velocity including linear velocity in meter/s
                                             and angular velocity in radian/s */
    float32_t      velocity_data[VECTORF_MIN_BUF_SIZE(6u)];
    struct Matrixf pose_covariance; /* position covariance in meter^2 and rotation covariance in radian^2 */
    float32_t      pose_covariance_data[MATRIXF_MIN_BUF_SIZE(6u, 6u)]; /* @todo, to be continue*/
    struct Matrixf velocity_covariance; /* linear velocity covariance in (meter/s)^2 and angular velocity covariance
                                           in (radian/s)^2 */
    float32_t      velocity_covariance_data[MATRIXF_MIN_BUF_SIZE(6u, 6u)]; /* @todo, to be continue*/
    struct Vectorf linear_acceleration;                                    /* 3D linear acceleration in meter/s^2 */
    float32_t      linear_acceleration_data[VECTORF_MIN_BUF_SIZE(3u)];
};

#ifdef MATRIX_ALIGN
#define ODOMETRYF_F32_SIZE 888UL
#else
#define ODOMETRYF_F32_SIZE 488UL
#endif
// check the size of odometry float32_t with static assert
HOLO_STATIC_ASSERT(sizeof(struct Odometryf) == ODOMETRYF_F32_SIZE);

/**
 * @brief initialize Odometryf from default values
 *
 * @param self a Odometryf
 * @return retcode_t
 */
retcode_t odometryf_init(struct Odometryf* self);

/**
 * @brief Initialize Odometryf from other Odometryf
 *
 * @param[in] self The odometryf to be initialized
 * @param[in] other The other odometryf
 * @return The return code
 */
retcode_t odometryf_init_from_odometryf(struct Odometryf* self, struct Odometryf const* other);

/**
 * @brief get the timestamp from a Odometryf
 *
 * @param self a Odometryf
 * @return const struct Timestamp*
 */
const struct Timestamp* odometryf_get_timestamp(const struct Odometryf* self);

/**
 * @brief get coordinate from a Odometryf
 *
 * @param self a Odometryf
 * @return coordinate
 */
Coordinate_t odometryf_get_coordinate(const struct Odometryf* self);

/**
 * @brief get child coordinate from a Odometryf
 *
 * @param self a Odometryf
 * @return enum Coord the child coordinate
 */
Coordinate_t odometryf_get_child_coordinate(const struct Odometryf* self);

/**
 * @brief get Pose3f from a Odometryf
 *
 * @param self a Odometryf
 * @return const struct Pose3f*
 */
const struct Pose3f* odometryf_get_pose(const struct Odometryf* self);

/**
 * @brief get velocity from a Odometryf
 *
 * @param self a Odometryf
 * @return const struct Vectorf* velocity, 6x1
 */
const struct Vectorf* odometryf_get_velocity(const struct Odometryf* self);

/**
 * @brief get pose covariance matrix from a Odometryf
 *
 * @param self a Odometryf
 * @return const struct Matrix66* 6x6 pose covariance matrix
 */
const struct Matrixf* odometryf_get_pose_covariance(const struct Odometryf* self);

/**
 * @brief get velocity covariance matrix from a Odometryf
 *
 * @param self a Odometryf
 * @return const struct Matrixf* 6x6 velocity covariance matrix
 */
const struct Matrixf* odometryf_get_velocity_covariance(const struct Odometryf* self);

/**
 * @brief get linear acceleration from a Odometryf
 *
 * @param self a Odometryf
 * @return const struct Vectorf* linear accelereation, 3x1
 */
const struct Vectorf* odometryf_get_linear_acceleration(const struct Odometryf* self);

/**
 * @brief get OdometryStatus from Odometryf
 *
 * @param self a Odometryf
 * @return enum OdometryStatus
 */
enum OdometryStatus odometryf_get_status(const struct Odometryf* self);

/**
 * @brief get OdometrySource from Odometryf
 *
 * @param self a Odometryf
 * @return enum OdometrySource
 */
enum OdometrySource odometryf_get_source(const struct Odometryf* self);

/**
 * @brief set timestamp to a Odometryf
 *
 * @param self a Odometryf
 * @param stamp a timestamp
 * @return retcode_t
 */
retcode_t odometryf_set_timestamp(struct Odometryf* self, const struct Timestamp* stamp);

/**
 * @brief set coordinate to a Odometryf
 *
 * @param header a Odometryf
 * @param coordinate a coordinate
 * @return retcode_t
 */
retcode_t odometryf_set_coordinate(struct Odometryf* self, Coordinate_t coordinate);

/**
 * @brief set child coordinate to a Odometryf
 *
 * @param header a Odometryf
 * @param coordinate a child coordinate
 * @return retcode_t
 */
retcode_t odometryf_set_child_coordinate(struct Odometryf* self, Coordinate_t coordinate);

/**
 * @brief set Pose3f to a Odometryf
 *
 * @param self a Odometryf
 * @param pose a Pose3f
 * @return retcode_t
 */
retcode_t odometryf_set_pose(struct Odometryf* self, const struct Pose3f* pose);

/**
 * @brief set velocity to a Odometryf
 *
 * @param self a Odometryf
 * @param velocity a velocity
 * @return retcode_t
 */
retcode_t odometryf_set_velocity(struct Odometryf* self, const struct Vectorf* velocity);

/**
 * @brief set pose covariance matrix to a Odometryf
 *
 * @param self a Odometryf
 * @param pose_cov a 6x6 pose covariance matrix
 * @return retcode_t
 */
retcode_t odometryf_set_pose_covariance(struct Odometryf* self, const struct Matrixf* pose_cov);

/**
 * @brief set velocity covariance matrix to a Odometryf
 *
 * @param self a Odometryf
 * @param velocity a 6x6 velocity covariance matrix
 * @return retcode_t
 */
retcode_t odometryf_set_velocity_covariance(struct Odometryf* self, const struct Matrixf* velocity_cov);

/**
 * @brief set linear acceleration to a Odometryf
 *
 * @param self a Odometryf
 * @param linear_acceleration a linear acceleration
 * @return retcode_t
 */
retcode_t odometryf_set_linear_acceleration(struct Odometryf* self, const struct Vectorf* linear_accelereation);

/**
 * @brief set OdometryStatus to Odometryf
 *
 * @param self a Odometryf
 * @param status OdometryStatus
 * @return retcode_t
 */
retcode_t odometryf_set_status(struct Odometryf* self, enum OdometryStatus status);

/**
 * @brief set OdometrySource to Odometryf
 *
 * @param self a Odometryf
 * @param status OdometrySource
 * @return retcode_t
 */
retcode_t odometryf_set_source(struct Odometryf* self, enum OdometrySource source);

/**
 * @brief get 3D translation (position) from a Odometryf
 *
 * @param self a Odometryf
 * @return const struct Point3f*
 */
const struct Point3f* odometryf_get_translation(const struct Odometryf* self);

/**
 * @brief get yaw angle from a Odometryf
 *
 * @param self a Odometryf
 * @return yaw angle in radian
 */
float32_t odometryf_get_yaw(const struct Odometryf* self);

/**
 * @brief get linear velocity in child coordinate orientation from a Odometryf
 *
 * @param self a Odometryf
 * @param out linear velocity in body frame
 * @return retcode_t
 */
retcode_t odometryf_get_linear_velocity_in_child_coord_orientation(const struct Odometryf* self, struct Vectorf* out);

/**
 * @brief get velocity x in child coord orientation from a Odometryf
 *
 * @param self a Odometryf
 * @return velocity x in body frame in m/s
 */
float32_t odometryf_get_x_velocity_in_child_coord_orientation(const struct Odometryf* self);

/**
 * @brief get velocity y in child coord orientation from a Odometryf
 *
 * @param self a Odometryf
 * @return velocity y in body frame in m/s
 */
float32_t odometryf_get_y_velocity_in_child_coord_orientation(const struct Odometryf* self);

/**
 * @brief Get 4byte aligned serialized buffer size for Odometryf.
 *
 * @param position The Odometryf object.
 *
 * @return uint32_t Serialized size.
 *
 * @see odometryf_get_serialized_size_8byte_aligned.
 */
uint32_t odometryf_get_serialized_size_4byte_aligned(const struct Odometryf* self);

/**
 * @brief Get 8byte aligned serialized buffer size for Odometryf.
 *
 * @param position The Odometryf object.
 *
 * @return uint32_t Serialized size.
 *
 * @see odometryf_get_serialized_size_4byte_aligned.
 */
uint32_t odometryf_get_serialized_size_8byte_aligned(const struct Odometryf* self);

/**
 * @brief Default interface of getting Odometryf serialized size.
 *
 * @param position The Odometryf object.
 *
 * @return uint32_t Serialized size.
 *
 */
uint32_t odometryf_get_serialized_size(const struct Odometryf* self);

/**
 * @brief Serialize Odometryf 4byte aligned.
 *
 * @param position The Odometryf object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see gnss_position_serialize_8byte_aligned.
 */
retcode_t odometryf_serialize_4byte_aligned(const struct Odometryf* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Serialize Odometryf 8byte aligned.
 *
 * @param position The Odometryf object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see odometryf_serialize_4byte_aligned.
 */
retcode_t odometryf_serialize_8byte_aligned(const struct Odometryf* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Default interface serialize Odometryf.
 *
 * @param position The Odometryf object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 */
retcode_t odometryf_serialize(const struct Odometryf* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize Odometryf 4byte aligned.
 *
 * @param position The Odometryf object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see gnss_position_deserialize_8byte_aligned.
 */
retcode_t odometryf_deserialize_4byte_aligned(struct Odometryf* self, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize Odometryf 8byte aligned.
 *
 * @param position The Odometryf object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see odometryf_deserialize_4byte_aligned.
 */
retcode_t odometryf_deserialize_8byte_aligned(struct Odometryf* self, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Default interface deserialize Odometryf.
 *
 * @param position The Odometryf object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 */
retcode_t odometryf_deserialize(struct Odometryf* self, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_COMMON_ODOMETY_H_
