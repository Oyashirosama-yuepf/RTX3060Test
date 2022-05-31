/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file navstate2_float32.h
 * @brief This header file defines common float32 2-D Navstate struct
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Mar 03, 2020
 */

#ifndef HOLO_C_LOCALIZATION_COMMON_NAVSTATE2_FLOAT32_H_
#define HOLO_C_LOCALIZATION_COMMON_NAVSTATE2_FLOAT32_H_

#include <assert.h>

#include <holo_c/common/imu_bias_float32.h>
#include <holo_c/common/imu_float32.h>
#include <holo_c/geometry/pose2_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup localization
 * @{
 *
 */

/**
 * @brief Define navstate status types
 */
enum NavstateStatus
{
    NAVSTATE_STATUS_ALL_GOOD                     = 0x0000,  ///< Solution is good
    NAVSTATE_STATUS_SOLUTION_NO_GOOD             = 0x0001,  ///< Solution is bad
    NAVSTATE_STATUS_POSITION_INACTIVE            = 0x0002,  ///< Position field of solution is inactive
    NAVSTATE_STATUS_ORIENTATION_INACTIVE         = 0x0004,  ///< Orientation field of solution is inactive
    NAVSTATE_STATUS_LINEAR_VELOCITY_INACTIVE     = 0x0008,  ///< Linear velocity field of solution is inactive
    NAVSTATE_STATUS_ANGULAR_VELOCITY_INACTIVE    = 0x0010,  ///< Angular velocity field of solution is inactive
    NAVSTATE_STATUS_LINEAR_ACCELERATION_INACTIVE = 0x0020,  ///< Linear acceleration field of solution is inactive
    NAVSTATE_STATUS_UNKNOWN                      = 0xFFFF,  ///< Unknow status
};

/**
 * @brief Define navstate source types
 *
 */
enum NavstateSource
{
    NAVSTATE_SOURCE_GNSS     = 0x0001,  ///< From Global Navigation Staellite System (GNSS)
    NAVSTATE_SOURCE_IMU      = 0x0002,  ///< From Inertial Measurement Unit (IMU)
    NAVSTATE_SOURCE_VISION   = 0x0004,  ///< From camera
    NAVSTATE_SOURCE_WHEEL    = 0x0008,  ///< From vehicle wheel speed sensor
    NAVSTATE_SOURCE_RADAR    = 0x0010,  ///< From Radar
    NAVSTATE_SOURCE_LIDAR    = 0x0020,  ///< From LiDAR
    NAVSTATE_SOURCE_SEMANTIC = 0x0040,  ///< From semantic measurement which provided by Machine Learning
    NAVSTATE_SOURCE_HD_MAP   = 0x0080,  ///< From High Definition Map (HD Map)
    NAVSTATE_SOURCE_RTK      = 0x0080,  ///< From RTK Base Station
    NAVSTATE_SOURCE_UNKNOWN  = 0xFFFF,  ///< From undefined source
};

/**
 * @brief This struct defines common float32 2-D Navstate struct
 * @details The struct Navstate2f is defined for the 2-dimension navigation algorithm.We assume that the carrier is
 * running on a horizontal plane, and the measured value of IMU is only the acceleration of x-axis and y-axis of the
 * carrier and the angular velocity of z-axis of the carrier.
 *
 */
struct Navstate2f
{
    enum NavstateStatus status;             ///< Navigationstate status
    enum NavstateSource source;             ///< Navigationstate source
    Coordinate_t        parent_coordinate;  ///< Parent coordinate
    Coordinate_t        child_coordinate;   ///< Child Coordinate
    struct Pose2f       pose;               ///< 2D pose including position in meters and rotation in radians
    struct Vectorf      velocity;           ///< 2D linear velocity in meter/s
    float32_t           velocity_data[VECTORF_MIN_BUF_SIZE(2u)];  ///< Buffer to keep velocity data
    struct Matrixf      pose_covariance;  ///< Position covariance in meter^2 and rotation covariance in radian^2
    float32_t           pose_covariance_data[MATRIXF_MIN_BUF_SIZE(3u, 3u)];  ///< Buffer to keep pose covariance
    struct Matrixf      velocity_covariance;  ///< Linear velocity covariance in (meter^2)
    float32_t           velocity_covariance_data[MATRIXF_MIN_BUF_SIZE(2u, 2u)];  ///< Buffer to keep velocity covariance
    float32_t           angular_velocity;                               ///< The z-axis angular velocity in radian/s
    struct Vectorf      linear_acceleration;                            ///< 2D linear acceleration in meter/s^2
    float32_t      linear_acceleration_data[VECTORF_MIN_BUF_SIZE(2u)];  ///< Buffer to keep linear acceleration data
    float32_t      angular_velocity_bias;                               ///< Imu angular velocity (z-axis) in radian/s
    float32_t      angular_velocity_bias_covariance;  ///< Imu angular velocity (z-axis) covariance in (radian/s)^2
    struct Vectorf linear_acceleration_bias;          ///< 2D linear acceleration bias in meter/s^2
    float32_t      linear_acceleration_bias_data[VECTORF_MIN_BUF_SIZE(2u)];  ///< Buffer to keep acceleration bias
    struct Matrixf linear_acceleration_bias_covariance;  ///< 2D linear acceleration bias covariance in (meter^2)^2
    /// Buffer to keep linear acceleration bias covariance
    float32_t linear_acceleration_bias_covariance_data[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
};

/// Check the size of odometry float32_t with static assert
HOLO_STATIC_ASSERT(sizeof(struct Navstate2f) == 240u);

/**
 * @brief Initialize Navstate2f from default values
 *
 * @param[in, out] self The Navstate2f struct for initialized
 * @return The return code
 */
retcode_t navstate2f_init(struct Navstate2f* self);

/**
 * @brief Initialize a Navstate2f struct from other Navstate2f struct
 *
 * @param[in] self The Navstate2f struct wanted to be initialized
 * @param[in] other The other Navstate2f struct
 * @return The return code
 */
retcode_t navstate2f_init_from_navstate2f(struct Navstate2f* self, struct Navstate2f const* other);

/**
 * @brief Get NavstateStatus from Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return enum NavstateStatus
 */
enum NavstateStatus navstate2f_get_status(struct Navstate2f const* self);

/**
 * @brief Set NavstateStatus to Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] status NavstateStatus
 * @return The return code
 */
retcode_t navstate2f_set_status(struct Navstate2f* self, enum NavstateStatus status);

/**
 * @brief Get NavstateSource from Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return enum NavstateSource
 */
enum NavstateSource navstate2f_get_source(struct Navstate2f const* self);

/**
 * @brief Set NavstateSource to Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] source NavstateSource
 * @return The return code
 */
retcode_t navstate2f_set_source(struct Navstate2f* self, enum NavstateSource source);

/**
 * @brief Get Pose2f from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return The pointer of const struct Pose2f
 */
struct Pose2f const* navstate2f_get_pose(struct Navstate2f const* self);

/**
 * @brief Set Pose2f to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] pose a Pose2f
 * @return The return code
 */
retcode_t navstate2f_set_pose(struct Navstate2f* self, struct Pose2f const* pose);

/**
 * @brief Get linear velocity from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return  The pointer of const struct Vectorf (2*1)
 */
struct Vectorf const* navstate2f_get_velocity(struct Navstate2f const* self);

/**
 * @brief Set linear velocity to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] velocity The velocity wanted to be setted
 * @return The return code
 */
retcode_t navstate2f_set_velocity(struct Navstate2f* self, struct Vectorf const* velocity);

/**
 * @brief Get pose covariance matrix from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return The pointer of const struct Matrix33 3x3 pose covariance matrix
 */
struct Matrixf const* navstate2f_get_pose_covariance(struct Navstate2f const* self);

/**
 * @brief Set 2D pose covariance matrix to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] pose_cov A 3x3 pose covariance matrix
 * @return The return code
 */
retcode_t navstate2f_set_pose_covariance(struct Navstate2f* self, struct Matrixf const* pose_cov);

/**
 * @brief Get velocity covariance matrix from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return The pointer of const struct Matrix22 2x2 velocity covariance matrix
 */
struct Matrixf const* navstate2f_get_velocity_covariance(struct Navstate2f const* self);

/**
 * @brief Set velocity covariance matrix  to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] velocity_cov A 2x2 velocity covariance matrix
 * @return The return code
 */
retcode_t navstate2f_set_velocity_covariance(struct Navstate2f* self, struct Matrixf const* velocity_cov);

/**
 * @brief Get angular velocity from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return The z-axis angular velocity
 */
float32_t navstate2f_get_angular_velocity(struct Navstate2f const* self);

/**
 * @brief Set angular velocity to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] angular_velocity The z-axis angular velocity
 * @return The return code
 */
retcode_t navstate2f_set_angular_velocity(struct Navstate2f* self, float32_t angular_velocity);

/**
 * @brief Get linear acceleration from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return The pointer of  const struct Vectorf linear acceleration, 3x1
 */
struct Vectorf const* navstate2f_get_linear_acceleration(struct Navstate2f const* self);

/**
 * @brief Set linear acceleration to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] linear_acceleration The 2D linear acceleration
 * @return The return code
 */
retcode_t navstate2f_set_linear_acceleration(struct Navstate2f* self, struct Vectorf const* linear_acceleration);

/**
 * @brief Get angular velocity bias from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return The z-axis angular velocity bias
 */
float32_t navstate2f_get_angular_velocity_bias(struct Navstate2f const* self);

/**
 * @brief Set angular velocity bias to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] angular_velocity_bias The z-axis angular velocity bias
 * @return The return code
 */
retcode_t navstate2f_set_angular_velocity_bias(struct Navstate2f* self, float32_t angular_velocity_bias);

/**
 * @brief Get linear acceleration bias from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return The pointer of const struct Vector 2*1 linear acceleration bias
 */
struct Vectorf const* navstate2f_get_linear_acceleration_bias(struct Navstate2f const* self);

/**
 * @brief Set linear acceleration bias to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] linear_acceleration_bias  struct Vector 2*1 linear acceleration bias
 * @return The return code
 */
retcode_t navstate2f_set_linear_acceleration_bias(struct Navstate2f*    self,
                                                  struct Vectorf const* linear_acceleration_bias);

/**
 * @brief Get angular velocity bias covariance from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return The z-axis angular velocity bias covariance
 */
float32_t navstate2f_get_angular_velocity_bias_covariance(struct Navstate2f const* self);

/**
 * @brief Set angular velocity bias covariance to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] angular_velocity_bias_cov The z-axis angular velocity bias covariance
 * @return The return code
 */
retcode_t navstate2f_set_angular_velocity_bias_covariance(struct Navstate2f* self, float32_t angular_velocity_bias_cov);

/**
 * @brief Get linear acceleration bias covariance from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return The pointer of const struct Matrixf22 2*2 linear acceleration bias covariance
 */
struct Matrixf const* navstate2f_get_linear_acceleration_bias_covariance(struct Navstate2f const* self);

/**
 * @brief Set linear acceleration bias covariance to a Navstate2f struct
 *
 * @param[out] self The Navstate2f struct
 * @param[in] linear_acceleration_bias_cov Matrixf22 2*2 linear acceleration bias covariance
 * @return The return code
 */
retcode_t navstate2f_set_linear_acceleration_bias_covariance(struct Navstate2f*    self,
                                                             struct Matrixf const* linear_acceleration_bias_cov);

/**
 * @brief Check if the navstate2f struct is valid
 *
 * @param[in] self The Navstate2f struct
 * @return It returns false if it is invalid. Otherwise, it return true
 */
bool_t navstate2f_is_valid(struct Navstate2f const* self);

/**
 * @brief Get the coordinate from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return Coordinate
 */
Coordinate_t navstate2f_get_coordinate(struct Navstate2f const* self);

/**
 * @brief Set the coordinate to a Navstate2f struct
 *
 * @param[in, out] self The Navstate2f struct
 * @param[in] coordinate The coordinate wanted to be set
 * @return The return code
 */
retcode_t navstate2f_set_coordinate(struct Navstate2f* self, Coordinate_t coordinate);

/**
 * @brief Get the child coordinate from a Navstate2f struct
 *
 * @param[in] self The Navstate2f struct
 * @return Child coordinate
 */
Coordinate_t navstate2f_get_child_coordinate(struct Navstate2f const* self);

/**
 * @brief Set the child coordinate to a Navstate2f struct
 *
 * @param[in, out] self The Navstate2f struct
 * @param[in] child_coordinate The child coordinate wanted to be set
 * @return The return code
 */
retcode_t navstate2f_set_child_coordinate(struct Navstate2f* self, Coordinate_t child_coordinate);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_COMMON_NAVSTATE2_FLOAT32_H_
