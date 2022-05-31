/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_pvt.h
 * @brief This header file defines GnssPvt type.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Apr 13, 2020
 */

#ifndef HOLO_C_COMMON_GNSS_PVT_H_
#define HOLO_C_COMMON_GNSS_PVT_H_

#include <holo_c/common/coordinate.h>
#include <holo_c/common/measurement_appendix.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point3.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup common
 * @{
 */

/**
 * @brief Enumerate GNSS system mode.
 *
 */
enum GnssPvtMode
{
    GNSS_PVT_MODE_NO_POSITION   = 0x00,
    GNSS_PVT_MODE_TIMING_ONLY   = 0x01,
    GNSS_PVT_MODE_SINGLE_FIX    = 0x02,
    GNSS_PVT_MODE_DIFF_POSITION = 0x03,
    GNSS_PVT_MODE_RTK_FLOAT_FIX = 0x04,
    GNSS_PVT_MODE_RTK_INT_FIX   = 0x05,
};

/**
 * @brief Define measurement of GNSS position, velocity and time information in WGS84 coordinate
 *
 */
struct GnssPvt
{
    struct Timestamp stamp;       ///< Timestamp
    Coordinate_t     coordinate;  ///< GNSS coordinate
    uint32_t         status;      ///< The status of the GnssPvt type

    float64_t longitude;  ///< Longitude (Unit: degree)
    float64_t latitude;   ///< Latitude (Unit: degree)
    float64_t height;     ///< Height (Unit: meter)

    float64_t velocity_east;   ///< East velocity (Unit: degree)
    float64_t velocity_north;  ///< North velocity (Unit: m/s)
    float64_t velocity_up;     ///< Up velocity (Unit: m/s)

    float64_t longitude_cov;  ///< Longitude covariance (Unit: m^2)
    float64_t latitude_cov;   ///< Latitude covariance (Unit: m^2)
    float64_t height_cov;     ///< Height covariance (Unit: m^2)

    float64_t velocity_east_cov;   ///< East velocity covariance (Unit: (m/s)^2)
    float64_t velocity_north_cov;  ///< North velocity covariance (Unit: (m/s)^2)
    float64_t velocity_up_cov;     ///< Up velocity covariance (Unit: (m/s)^2)
};

/// Check the size of GnssPosition with static assert
HOLO_STATIC_ASSERT(sizeof(struct GnssPvt) == 112UL);

/**
 * @brief Initialize GnssPvt from default values
 *
 * @param[in] self A GnssPvt struct
 * @return The return code
 */
retcode_t gnss_pvt_init(struct GnssPvt* self);

/**
 * @brief Get the timestamp from a GnssPvt struct
 *
 * @param[in] self The input GnssPvt struct
 * @return The pointer of a const Navstate2f struct
 */
struct Timestamp const* gnss_pvt_get_timestamp(struct GnssPvt const* self);

/**
 * @brief Get coordinate from a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] timestamp The timestamp wanted to be set
 * @return The return code
 */
retcode_t gnss_pvt_set_timestamp(struct GnssPvt* self, struct Timestamp const* timestamp);

/**
 * @brief Get the coordiante from a GnssPvt struct
 *
 * @param[in] self The input GnssPvt struct
 * @return The coordiante
 */
Coordinate_t gnss_pvt_get_coordinate(struct GnssPvt const* self);

/**
 * @brief Set the coordiante to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] coordinate The coordinate wanted to be set
 * @return The return code
 */
retcode_t gnss_pvt_set_coordinate(struct GnssPvt* self, Coordinate_t coordinate);

/**
 * @brief Test if position is valid
 *
 * @param[in] self The input GnssPvt struct
 * @return It returns true if position is valid, otherwise false.
 */
bool_t gnss_pvt_is_position_valid(struct GnssPvt const* self);

/**
 * @brief Test if velocity is valid
 *
 * @param[in] self The input GnssPvt struct
 * @return It returns true if velocity is valid, otherwise false.
 */
bool_t gnss_pvt_is_velocity_valid(struct GnssPvt const* self);

/**
 * @brief Test if position covariance is valid
 *
 * @param[in] self The input GnssPvt struct
 * @return It returns true if position covariance is  valid, otherwise false.
 */
bool_t gnss_pvt_is_position_cov_valid(struct GnssPvt const* self);

/**
 * @brief Test if velocity covariance is valid
 *
 * @param[in] self The input GnssPvt struct
 * @return It returns true if velocity covariance is  valid, otherwise false.
 */
bool_t gnss_pvt_is_velocity_cov_valid(struct GnssPvt const* self);

/**
 * @brief Set flags to indicate which part of GnssPvt is valid.
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] position Position is valid.
 * @param[in] velocity Velocity is valid.
 * @param[in] position_cov Position covariance is valid.
 * @param[in] velocity_cov Velocity covariance is valid.
 * @return The return code
 */
retcode_t gnss_pvt_set_valid_flags(struct GnssPvt* self, bool_t position, bool_t velocity, bool_t position_cov,
                                   bool_t velocity_cov);

/**
 * @brief Get the mode from a GnssPvt struct
 *
 * @param[in] self The input GnssPvt struct
 * @return GnssPvtMode
 */
enum GnssPvtMode gnss_pvt_get_mode(struct GnssPvt const* self);

/**
 * @brief Set the mode to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] mode GnssPvtMode
 * @return The return code
 */
retcode_t gnss_pvt_set_mode(struct GnssPvt* self, enum GnssPvtMode mode);

/**
 * @brief Get longitude value from a GnssPvt struct. Unit: degree. Range: [-180, 180)
 *
 * @param[in] self The input GnssPvt struct
 * @return The longitude value
 */
float64_t gnss_pvt_get_longitude(struct GnssPvt const* self);

/**
 * @brief Set longitude value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] longitude The longitude wanted to be set. Unit: degree. Range: [-180, 180)
 * @return The return code
 */
retcode_t gnss_pvt_set_longitude(struct GnssPvt* self, float64_t longitude);

/**
 * @brief Get latitude value from a GnssPvt struct. Unit: degree. Range: [-90, 90)
 *
 * @param[in] self The input GnssPvt struct
 * @return The latitude value
 */
float64_t gnss_pvt_get_latitude(struct GnssPvt const* self);

/**
 * @brief Set latitude value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] latitude The latitude wanted to be set. Unit: degree. Range: [-90, 90)
 * @return The return code
 */
retcode_t gnss_pvt_set_latitude(struct GnssPvt* self, float64_t latitude);

/**
 * @brief Get height value from a GnssPvt struct. Unit: meter
 *
 * @param[in] self The input GnssPvt struct
 * @return The height value
 */
float64_t gnss_pvt_get_height(struct GnssPvt const* self);

/**
 * @brief Set height value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] height The height wanted to be set. Unit: meter
 * @return The return code
 */
retcode_t gnss_pvt_set_height(struct GnssPvt* self, float64_t height);

/**
 * @brief Get east velocity value from a GnssPvt struct. Unit: m/s
 *
 * @param[in] self The input GnssPvt struct
 * @return The east velocity value
 */
float64_t gnss_pvt_get_velocity_east(struct GnssPvt const* self);

/**
 * @brief Set east velocity value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] velocity_east The east velocity wanted to be set. Unit: m/s
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity_east(struct GnssPvt* self, float64_t velocity_east);

/**
 * @brief Get north velocity value from a GnssPvt struct. Unit: m/s
 *
 * @param[in] self The input GnssPvt struct
 * @return The north velocity value
 */
float64_t gnss_pvt_get_velocity_north(struct GnssPvt const* self);

/**
 * @brief Set north velocity value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] velocity_north The north velocity wanted to be set. Unit: m/s
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity_north(struct GnssPvt* self, float64_t velocity_north);

/**
 * @brief Get up velocity value from a GnssPvt struct. Unit: m/s
 *
 * @param[in] self The input GnssPvt struct
 * @return The up velocity value
 */
float64_t gnss_pvt_get_velocity_up(struct GnssPvt const* self);

/**
 * @brief Set up velocity value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] velocity_up The up velocity wanted to be set. Unit: m/s
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity_up(struct GnssPvt* self, float64_t velocity_up);

/**
 * @brief Get longitude covariance value from a GnssPvt struct. Unit: meter^2
 *
 * @param[in] self The input GnssPvt struct
 * @return The longitude covariance value
 */
float64_t gnss_pvt_get_longitude_cov(struct GnssPvt const* self);

/**
 * @brief Set longitude covariance value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] longitude_cov The longitude covariance wanted to be set. Unit: meter^2
 * @return The return code
 */
retcode_t gnss_pvt_set_longitude_cov(struct GnssPvt* self, float64_t longitude_cov);

/**
 * @brief Get latitude covariance value from a GnssPvt struct. Unit: meter^2
 *
 * @param[in] self The input GnssPvt struct
 * @return The latitude covariance value
 */
float64_t gnss_pvt_get_latitude_cov(struct GnssPvt const* self);

/**
 * @brief Set latitude covariance value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] latitude_cov The latitude covariance wanted to be set. Unit: meter^2
 * @return The return code
 */
retcode_t gnss_pvt_set_latitude_cov(struct GnssPvt* self, float64_t latitude_cov);

/**
 * @brief Get height covariance value from a GnssPvt struct. Unit: meter^2
 *
 * @param[in] self The input GnssPvt struct
 * @return The height covariance value
 */
float64_t gnss_pvt_get_height_cov(struct GnssPvt const* self);

/**
 * @brief Set height covariance value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] height_cov The height covariance wanted to be set. Unit: meter^2
 * @return The return code
 */
retcode_t gnss_pvt_set_height_cov(struct GnssPvt* self, float64_t height_cov);

/**
 * @brief Get east velocity covariance value from a GnssPvt struct. Unit: (m/s)^2
 *
 * @param[in] self The input GnssPvt struct
 * @return The east velocity covariance value
 */
float64_t gnss_pvt_get_velocity_east_cov(struct GnssPvt const* self);

/**
 * @brief Set east velocity covariance value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] velocity_east_cov The east velocity covariance wanted to be set. Unit: (m/s)^2
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity_east_cov(struct GnssPvt* self, float64_t velocity_east_cov);

/**
 * @brief Get north velocity covariance value from a GnssPvt struct. Unit: (m/s)^2
 *
 * @param[in] self The input GnssPvt struct
 * @return The north velocity covariance value
 */
float64_t gnss_pvt_get_velocity_north_cov(struct GnssPvt const* self);

/**
 * @brief Set north velocity covariance value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] velocity_north_cov The north velocity covariance wanted to be set. Unit: (m/s)^2
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity_north_cov(struct GnssPvt* self, float64_t velocity_north_cov);

/**
 * @brief Get up velocity covariance value from a GnssPvt struct. Unit: m/s
 *
 * @param[in] self The input GnssPvt struct
 * @return The up velocity covariance value
 */
float64_t gnss_pvt_get_velocity_up_cov(struct GnssPvt const* self);

/**
 * @brief Set up velocity covariance value to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] velocity_up_cov The up velocity covariance wanted to be set. Unit: m/s
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity_up_cov(struct GnssPvt* self, float64_t velocity_up_cov);

/**
 * @brief Set position values to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] longitude Longitude value Unit: degree. Range: [-180, 180)
 * @param[in] latitude Latitude value Unit: degree. Range: [-180, 180)
 * @param[in] height Height value  Unit: meter
 * @return The return code
 */
retcode_t gnss_pvt_set_position_by_values(struct GnssPvt* self, float64_t longitude, float64_t latitude,
                                          float64_t height);

/**
 * @brief Set velocity values to a GnssPvt struct
 *
 * @param[in] self The input GnssPvt struct
 * @param[in] velocity_east East velocity value Unit: m/s
 * @param[in] velocity_north North velocity value Unit: m/s
 * @param[in] velocity_up Height velocity value Unit: m/s
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity_by_values(struct GnssPvt* self, float64_t velocity_east, float64_t velocity_north,
                                          float64_t velocity_up);

/**
 * @brief Set position covariance values to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] longitude_cov Longitude covariance value Unit: meter^2
 * @param[in] latitude_cov Latitude covariance value Unit: meter^2
 * @param[in] height_cov Height covariance value  Unit: meter^2
 * @return The return code
 */
retcode_t gnss_pvt_set_position_cov_by_values(struct GnssPvt* self, float64_t longitude_cov, float64_t latitude_cov,
                                              float64_t height_cov);

/**
 * @brief Set velocity covariance values to a GnssPvt struct
 *
 * @param[in] self The input GnssPvt struct
 * @param[in] velocity_east_cov East velocity covariance value Unit: (m/s)^2
 * @param[in] velocity_north_cov North velocity covariance value Unit: (m/s)^2
 * @param[in] velocity_up Height_cov velocity covariance value Unit: (m/s)^2
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity_cov_by_values(struct GnssPvt* self, float64_t velocity_east_cov,
                                              float64_t velocity_north_cov, float64_t velocity_up_cov);

/**
 * @brief Get position values from a GnssPvt struct
 *
 * @param[in] self The input GnssPvt struct
 * @param[out] position The Point3dType position values (Longitude, Latitude, Height)
 * @return The return code
 */
retcode_t gnss_pvt_get_position(struct GnssPvt const* self, struct Point3d* position);

/**
 * @brief Set position values to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] position The PointType position values (Longitude, Latitude, Height)
 * @return The return code
 */
retcode_t gnss_pvt_set_position(struct GnssPvt* self, struct Point3d const* position);

/**
 * @brief Get velocity values from a GnssPvt struct
 *
 * @param[in] self The input GnssPvt struct
 * @param[out] velocity The Point3dType velocity values (East velocity, North velocity, Up velocity)
 * @return The return code
 */
retcode_t gnss_pvt_get_velocity(struct GnssPvt const* self, struct Point3d* velocity);

/**
 * @brief Set velocity values to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] velocity The PointType velocity values (East velocity, North velocity, Up velocity)
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity(struct GnssPvt* self, struct Point3d const* velocity);

/**
 * @brief Get position covariance values from a GnssPvt struct
 *
 * @param[in] self The input GnssPvt struct
 * @param[out] position_cov The Point3dType position covariance values (Longitude covariance, Latitude covariance,
 * Height covariance)
 * @return The return code
 */
retcode_t gnss_pvt_get_position_cov(struct GnssPvt const* self, struct Point3d* position_cov);

/**
 * @brief Set position covariance values to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] position_cov The PointType position covariance values (Longitude covariance, Latitude covariance, Height
 * covariance)
 * @return The return code
 */
retcode_t gnss_pvt_set_position_cov(struct GnssPvt* self, struct Point3d const* position_cov);

/**
 * @brief Get velocity covariance values from a GnssPvt struct
 *
 * @param[in] self The input GnssPvt struct
 * @param[out] velocity_cov The Point3dType velocity covariance values (East velocity covariance, North velocity
 * covariance, Up velocity covariance)
 * @return The return code
 */
retcode_t gnss_pvt_get_velocity_cov(struct GnssPvt const* self, struct Point3d* velocity_cov);

/**
 * @brief Set velocity covariance values to a GnssPvt struct
 *
 * @param[in, out] self The input GnssPvt struct
 * @param[in] velocity_cov The PointType velocity covariance values (East velocity covariance, North velocity
 * covariance, Up velocity covariance)
 * @return The return code
 */
retcode_t gnss_pvt_set_velocity_cov(struct GnssPvt* self, struct Point3d const* velocity_cov);

/**
 * @brief Get serialized buffer size
 *
 * @param[in] self The input GnssPvt struct
 * @return Serialized size
 */
uint32_t gnss_pvt_get_serialized_size(struct GnssPvt const* self);

/**
 * @brief Serialize GnssPvt object to buffer
 *
 * @param[in] self The input GnssPvt struct
 * @param[in] buffer The buffer to serialize to
 * @param[in] buffer_size Size of buffer
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return Positive interger Number of bytes serialized into buffer.
 */
retcode_t gnss_pvt_serialize(struct GnssPvt const* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize GnssPvt object from buffer
 *
 * @param[in] self The input GnssPvt struct
 * @param[in] buffer The buffer to deserialize from
 * @param[in] buffer_size Size of buffer
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer.
 */
retcode_t gnss_pvt_deserialize(struct GnssPvt* self, uint8_t const* buffer, uint32_t buffer_size);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_COMMON_COORDINATE_H */
