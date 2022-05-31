/*!
 * @file imu_float32.h
 * @brief This header file define measurement of generic inertial measurement unit.
 * @author lichao@holomatic.com
 * @date Aug 24, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_COMMON_IMU_FLOAT32_H_
#define HOLO_C_COMMON_IMU_FLOAT32_H_

#include <holo_c/common/coordinate.h>
#include <holo_c/common/measurement_appendix.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/vector_float32.h>
#include <holo_c/utils/serialization.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup common
 * @{
 */

/**
 * @brief define measurement of generic inertial measurement unit
 *
 */
struct Imuf
{
    struct Timestamp stamp;   ///< position stamp
    Coordinate_t coordinate;	///< position coordinate
    enum ImuStatus   status;                                              ///< imu status
    struct Vectorf   angular_velocity;  ///< angular velocities from 3-axis gyroscope in radian / s
    float32_t        angular_velocity_data[VECTORF_MIN_BUF_SIZE(3u)];  ///< real data for angular velocities
    struct Vectorf   linear_acceleration;  ///< linear acceleration from 3-axis accelerometer in meter / s^2
    float32_t        linear_acceleration_data[VECTORF_MIN_BUF_SIZE(3u)];  ///< real data for linear acceleration
};

// check the size of Imuf with static assert
#ifdef MATRIX_ALIGN
HOLO_STATIC_ASSERT(sizeof(struct Imuf) == 184UL);
#else
HOLO_STATIC_ASSERT(sizeof(struct Imuf) == 80UL);
#endif

/**
 * @brief initialize Imu from default values
 *
 * @param self a Imu
 * @return retcode_t
 */
retcode_t imuf_init(struct Imuf* self);

/**
 * @brief get the timestamp from a imu float32_t
 *
 * @param self a imu float32_t
 * @return const struct Timestamp*
 */
const struct Timestamp* imuf_get_timestamp(const struct Imuf* self);

/**
 * @brief get coordinate from a imu float32_t
 *
 * @param self a imu float32_t
 * @return coordinate
 */
Coordinate_t imuf_get_coordinate(const struct Imuf* self);

/**
 * @brief get angular velocity from imu float32_t
 *
 * @param self a imu float32_t
 * @return const struct Vectorf* angular velocity in rad/s
 */
const struct Vectorf* imuf_get_angular_velocity(const struct Imuf* self);

/**
 * @brief get imu angular velocity value directly
 *
 * @param self imu pointer
 * @param angle_rate_x angular velocity x value in radian/s
 * @param angle_rate_y angular velocity y value in radian/s
 * @param angle_rate_z angular velocity z value in radian/s
 * @return retcode_t RC_SUCCESS
 */
retcode_t imuf_get_angular_velocity_value(const struct Imuf* self, float32_t* angle_rate_x, float32_t* angle_rate_y,
                                          float32_t* angle_rate_z);

/**
 * @brief get linear acceleration from imu float32_t
 *
 * @param self a imu float32_t
 * @return const struct Vectorf* linear acceleration in m/s^2
 */
const struct Vectorf* imuf_get_linear_acceleration(const struct Imuf* self);

/**
 * @brief get imu linear acc value directly
 *
 * @param self imu pointer
 * @param acc_x linear acc x value in m/s^2
 * @param acc_y linear acc y value in m/s^2
 * @param acc_z linear acc z value in m/s^2
 * @return retcode_t RC_SUCCESS
 */
retcode_t imuf_get_linear_acceleration_value(const struct Imuf* self, float32_t* acc_x, float32_t* acc_y,
                                             float32_t* acc_z);

/**
 * @brief get imu status from imu float32_t
 *
 * @param self a imu float32_t
 * @return const enum ImuStatus* imu status
 */
enum ImuStatus imuf_get_status(const struct Imuf* self);

/**
 * @brief set timestamp to a imu float32_t
 *
 * @param self a imu float32_t
 * @param stamp a timestamp
 * @return retcode_t
 */
retcode_t imuf_set_timestamp(struct Imuf* self, const struct Timestamp* stamp);

/**
 * @brief set coordinate to a imu float32_t
 *
 * @param self a imu float32_t
 * @param coordinate The coordinate object
 * @return retcode_t
 */
retcode_t imuf_set_coordinate(struct Imuf* self, Coordinate_t coordinate);

/**
 * @brief set angular velocity to imu float32_t
 *
 * @param self a imu float32_t
 * @param angular_velocity angular velocity in rad/s
 * @return retcode_t
 */
retcode_t imuf_set_angular_velocity(struct Imuf* self, const struct Vectorf* angular_velocity);

/**
 * @brief set imu angular velocity value directly
 *
 * @param self imu pointer
 * @param angle_rate_x angular velocity x in radian/s
 * @param angle_rate_y angular velocity y in radian/s
 * @param angle_rate_z angular velocity z in radian/s
 * @return retcode_t RC_SUCCESS
 */
retcode_t imuf_set_angular_velocity_value(struct Imuf* self, const float32_t angle_rate_x, const float32_t angle_rate_y,
                                          const float32_t angle_rate_z);

/**
 * @brief set linear acceleration to imu float32_t
 *
 * @param self a imu float32_t
 * @param linear_acceleration linear acceleration in m/s^2
 * @return retcode_t
 */
retcode_t imuf_set_linear_acceleration(struct Imuf* self, const struct Vectorf* linear_acceleration);

/**
 * @brief set linear acc value directly
 *
 * @param self Imuf pointer
 * @param acc_x linear acc x value in m/s^2
 * @param acc_y linear acc y value in m/s^2
 * @param acc_z linear acc z value in m/s^2
 * @return retcode_t RC_SUCCESS
 */
retcode_t imuf_set_linear_acceleration_value(struct Imuf* self, const float32_t acc_x, float32_t acc_y,
                                             float32_t acc_z);

/**
 * @brief set status to imu float32_t
 *
 * @param self a imu float32_t
 * @param status imu status
 * @return retcode_t
 */
retcode_t imuf_set_status(struct Imuf* self, enum ImuStatus status);

/**
 * @brief Get 4byte aligned serialized buffer size for Imuf.
 *
 * @param self The Imuf object.
 *
 * @return uint32_t Serialized size.
 *
 * @see imuf_get_serialized_size_8byte_aligned.
 */
uint32_t imuf_get_serialized_size_4byte_aligned(const struct Imuf* self);

/**
 * @brief Get 8byte aligned serialized buffer size for Imuf.
 *
 * @param self The Imuf object.
 *
 * @return uint32_t Serialized size.
 *
 * @see imuf_get_serialized_size_4byte_aligned.
 */
uint32_t imuf_get_serialized_size_8byte_aligned(const struct Imuf* self);

/**
 * @brief Default interface of getting imuf serialize size.
 *
 * @param self The Imuf object.
 *
 * @return uint32_t Serialized size.
 */
uint32_t imuf_get_serialized_size(const struct Imuf* self);

/**
 * @brief Serialize Imuf 4byte aligned.
 *
 * @param self The Imuf object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see imuf_serialize_8byte_aligned
 */
retcode_t imuf_serialize_4byte_aligned(const struct Imuf* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Serialize Imuf 8byte aligned.
 *
 * @param self The Imuf object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see imuf_serialize_4byte_aligned.
 */
retcode_t imuf_serialize_8byte_aligned(const struct Imuf* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Default interface serialize Imuf to buffer.
 *
 * @param self The Imuf object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 */
retcode_t imuf_serialize(const struct Imuf* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize Imuf 4byte aligned.
 *
 * @param self The Imuf object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see imuf_deserialize_8byte_aligned
 */
retcode_t imuf_deserialize_4byte_aligned(struct Imuf* self, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize Imuf 8byte aligned.
 *
 * @param self The Imuf object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see imuf_deserialize_4byte_aligned
 */
retcode_t imuf_deserialize_8byte_aligned(struct Imuf* self, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Default interface deserialize Imuf from buffer.
 *
 * @param self The Imuf object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 */
retcode_t imuf_deserialize(struct Imuf* self, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_COMMON_IMU_FLOAT32_H_
