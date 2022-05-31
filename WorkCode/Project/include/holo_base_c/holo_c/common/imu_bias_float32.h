/*!
 * @file imu_bias.h
 * @brief This header file define the bias for imu gyroscope and accelerometer.
 * @author lichao@holomatic.com
 * @date Aug 24, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_COMMON_IMU_BIAS_H_
#define HOLO_C_COMMON_IMU_BIAS_H_

#include <holo_c/common/coordinate.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/vector_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief define the bias for imu gyroscope and accelerometer
 *
 */
struct ImuBiasf
{
    struct Vectorf   angular_velocity_bias;                                     ///< angular velocity bias in radian / s
    float32_t        angular_velocity_bias_data[VECTORF_MIN_BUF_SIZE(3u)];  ///< real data for angular_velocity_bias
    struct Vectorf   linear_acceleration_bias;                              ///< linear acceleration bias in meter / s^2
    float32_t linear_acceleration_bias_data[VECTORF_MIN_BUF_SIZE(3u)];  ///< real data for linear_acceleration_bias
    struct Vectorf angular_velocity_bias_cov;  ///< angular velocity bias diagonal covariance in (radian / s)^2
    float32_t      angular_velocity_bias_cov_data[VECTORF_MIN_BUF_SIZE(3u)];  ///< real data for
                                                                                  ///< angular_velocity_bias_cov
    struct Vectorf linear_acceleration_bias_cov;  ///< linear acceleration bias diagonal covariance in (meter / s^2)^2
    float32_t      linear_acceleration_bias_cov_data[VECTORF_MIN_BUF_SIZE(3u)];  ///< real data for
                                                                                     ///< linear_acceleration_bias_cov
    struct Timestamp stamp;   ///< position stamp
    Coordinate_t coordinate;	  ///< position coordinate
};

#ifdef MATRIX_ALIGN
#define   IMU_BIAS_F32_SIZE     328UL
#else
#define   IMU_BIAS_F32_SIZE     136UL
#endif
// check the size of ImuBiasf with static assert
HOLO_STATIC_ASSERT(sizeof(struct ImuBiasf) == IMU_BIAS_F32_SIZE);

/**
 * @brief initialize ImuBias from default values
 *
 * @param self a ImuBias
 * @return retcode_t
 */
retcode_t imu_biasf_init(struct ImuBiasf* self);

/**
 * @brief get the timestamp from a ImuBias float32_t
 *
 * @param header a ImuBias float32_t
 * @return const struct Timestamp*
 */
const struct Timestamp* imu_biasf_get_timestamp(const struct ImuBiasf* self);

/**
 * @brief set timestamp to a ImuBias float32_t
 *
 * @param header a imu float32_t
 * @param stamp a timestamp
 * @return retcode_t
 */
retcode_t imu_biasf_set_timestamp(struct ImuBiasf* self, const struct Timestamp* stamp);

/**
 * @brief get coordinate from a ImuBias float32_t
 *
 * @param header a ImuBias float32_t
 * @return coordinate
 */
Coordinate_t imu_biasf_get_coordinate(const struct ImuBiasf* self);

/**
 * @brief set coordinate to a ImuBias float32_t
 *
 * @param header a ImuBias float32_t
 * @param coordinate a coordinate
 * @return retcode_t
 */
retcode_t imu_biasf_set_coordinate(struct ImuBiasf* self, Coordinate_t coordinate);

/**
 * @brief get angular velocity bias from ImuBias float32_t
 *
 * @param self a ImuBias float32_t
 * @return const struct Vectorf* angular velocity in rad/s, 3x1
 */
const struct Vectorf* imu_biasf_get_angular_velocity_bias(const struct ImuBiasf* self);

/**
 * @brief set angular velocity to ImuBias float32_t
 *
 * @param self a ImuBias float32_t
 * @param angular_velocity_bias angular velocity bias in rad/s
 * @return retcode_t
 */
retcode_t imu_biasf_set_angular_velocity_bias(struct ImuBiasf* self, const struct Vectorf* angular_velocity_bias);

/**
 * @brief get linear acceleration from ImuBias float32_t
 *
 * @param self a ImuBias float32_t
 * @return const struct Vectorf* linear acceleration in m/s^2, 3x1
 */
const struct Vectorf* imu_biasf_get_linear_acceleration_bias(const struct ImuBiasf* self);

/**
 * @brief set linear acceleration to ImuBias float32_t
 *
 * @param self a ImuBias float32_t
 * @param linear_acceleration_bias linear acceleration bias in m/s^2
 * @return retcode_t
 */
retcode_t imu_biasf_set_linear_acceleration_bias(struct ImuBiasf* self, const struct Vectorf* linear_acceleration_bias);

/**
 * @brief get angular velocity bias covariance from ImuBias float32_t
 *
 * @param self a ImuBias float32_t
 * @return const struct Vectorf* angular velocity covariance in (rad/s)^2, 3x1
 */
const struct Vectorf* imu_biasf_get_angular_velocity_bias_covariance(const struct ImuBiasf* self);

/**
 * @brief set angular velocity bias diagonal covariance to ImuBias float32_t
 *
 * @param self a ImuBias float32_t
 * @param angular_velocity_bias_cov angular velocity bias diagonal covariance in (rad/s)^2, 3x1
 * @return retcode_t
 */
retcode_t imu_biasf_set_angular_velocity_bias_covariance(struct ImuBiasf*      self,
                                                         const struct Vectorf* angular_velocity_bias_cov);

/**
 * @brief get linear acceleration from ImuBias float32_t
 *
 * @param self a ImuBias float32_t
 * @return const struct Vectorf* linear acceleration covariance in (m/s^2)^2, 3x1
 */
const struct Vectorf* imu_biasf_get_linear_acceleration_bias_covariance(const struct ImuBiasf* self);

/**
 * @brief set linear acceleration bias covariance to ImuBias float32_t
 *
 * @param self a ImuBias float32_t
 * @param linear_acceleration_bias_cov linear acceleration bias diagonal covariance in m/s^2, 3x1
 * @return retcode_t
 */
retcode_t imu_biasf_set_linear_acceleration_bias_covariance(struct ImuBiasf*      self,
                                                            const struct Vectorf* linear_acceleration_bias_cov);

/**
 * @brief get serialized buffer size for a ImuBiasf
 *
 * @param self a ImuBiasf to be serialized
 * @return buffer size
 */
uint32_t imu_biasf_get_serialized_size(const struct ImuBiasf* self);

/**
 * @brief serialize a ImuBiasf to buffer
 *
 * @param self a ImuBiasf to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 */
retcode_t imu_biasf_serialize(const struct ImuBiasf* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief deserialize a ImuBiasf to buffer
 *
 * @param self a ImuBiasf to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes deserialized info buffer.
 */
retcode_t imu_biasf_deserialize(struct ImuBiasf* self, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_COMMON_IMU_BIAS_H_
