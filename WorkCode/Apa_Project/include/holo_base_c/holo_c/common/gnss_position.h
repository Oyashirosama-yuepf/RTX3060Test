/*!
 * @file gnss_position.h
 * @brief This header file define measurement of generic WGS84 position from GPS.
 * @author lichao@holomatic.com
 * @date Aug 24, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_COMMON_GNSS_POSITION_H_
#define HOLO_C_COMMON_GNSS_POSITION_H_

#include <holo_c/common/coordinate.h>
#include <holo_c/common/measurement_appendix.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief define measurement of generic WGS84 postion from GPS
 *
 */
struct GnssPosition
{
    struct Timestamp stamp;   ///< position stamp
    Coordinate_t coordinate;	///< position coordinate
    enum GnssPositionStatus status;         ///< position status
    float64_t               latitude;       ///< latitude in degrees
    float64_t               longitude;      ///< longitude in degrees
    float64_t               altitude;       ///< WGS84 ellipsold altitude in degrees
    float64_t               latitude_cov;   ///< latitude covariance in degree^2
    float64_t               longitude_cov;  ///< longitude covariance in degree^2
    float64_t               altitude_cov;   ///< WGS84 ellipsold altitude covariance in degree^2
};

// check the size of GnssPosition with static assert
HOLO_STATIC_ASSERT(sizeof(struct GnssPosition) == 64UL);

/**
 * @brief initialize GnssPosition from default values
 *
 * @param self a GnssPosition
 * @return retcode_t
 */
retcode_t gnss_position_init(struct GnssPosition* self);

/**
 * @brief get the timestamp from a GnssPosition
 *
 * @param self a GnssPosition
 * @return const struct Timestamp*
 */
const struct Timestamp* gnss_position_get_timestamp(const struct GnssPosition* self);

/**
 * @brief get coordinate from a GnssPosition
 *
 * @param self a GnssPosition
 * @return struct Coordinate the coordinate
 */
Coordinate_t gnss_position_get_coordinate(const struct GnssPosition* self);

/**
 * @brief get GnssPositionStatus from GnssPosition
 *
 * @param self a GnssPosition
 * @return enum GnssPositionStatus
 */
enum GnssPositionStatus gnss_position_get_status(const struct GnssPosition* self);

/**
 * @brief get latitude from a GnssPosition
 *
 * @param self a GnssPosition
 * @return latitude
 */
float64_t gnss_position_get_latitude(const struct GnssPosition* self);

/**
 * @brief get longitude from a GnssPosition
 *
 * @param self a GnssPosition
 * @return longitude
 */
float64_t gnss_position_get_longitude(const struct GnssPosition* self);

/**
 * @brief get altitude from a GnssPosition
 *
 * @param self a GnssPosition
 * @return altitude
 */
float64_t gnss_position_get_altitude(const struct GnssPosition* self);

/**
 * @brief get latitude covariance from a GnssPosition
 *
 * @param self a GnssPosition
 * @return latitude covariance
 */
float64_t gnss_position_get_latitude_covariance(const struct GnssPosition* self);

/**
 * @brief get longitude covariance from a GnssPosition
 *
 * @param self a GnssPosition
 * @return longitude covariance
 */
float64_t gnss_position_get_longitude_covariance(const struct GnssPosition* self);

/**
 * @brief get altitude covariance from a GnssPosition
 *
 * @param self a GnssPosition
 * @return altitude covariance
 */
float64_t gnss_position_get_altitude_covariance(const struct GnssPosition* self);

/**
 * @brief set timestamp to a GnssPosition
 *
 * @param self a GnssPosition
 * @param stamp a timestamp
 * @return retcode_t
 */
retcode_t gnss_position_set_timestamp(struct GnssPosition* self, const struct Timestamp* stamp);

/**
 * @brief set coordinate to a GnssPosition
 *
 * @param header a GnssPosition
 * @param coordinate a coordinate
 * @return retcode_t
 */
retcode_t gnss_position_set_coordinate(struct GnssPosition* self, Coordinate_t coordinate);

/**
 * @brief set GnssPositionStatus to GnssPosition
 *
 * @param self a GnssPosition
 * @param status GnssPositionStatus
 * @return retcode_t
 */
retcode_t gnss_position_set_status(struct GnssPosition* self, enum GnssPositionStatus status);

/**
 * @brief set latitude to a GnssPosition
 *
 * @param self a GnssPosition
 * @param lat latitude
 * @return retcode_t
 */
retcode_t gnss_position_set_latitude(struct GnssPosition* self, float64_t lat);

/**
 * @brief set longitude to a GnssPosition
 *
 * @param self a GnssPosition
 * @param lon longitude
 * @return retcode_t
 */
retcode_t gnss_position_set_longitude(struct GnssPosition* self, float64_t lon);

/**
 * @brief set altitude to a GnssPosition
 *
 * @param self a GnssPosition
 * @param alt altitude
 * @return retcode_t
 */
retcode_t gnss_position_set_altitude(struct GnssPosition* self, float64_t alt);

/**
 * @brief set latitude covariance to a GnssPosition
 *
 * @param self a GnssPosition
 * @param lat_cov latitude covariance
 * @return retcode_t
 */
retcode_t gnss_position_set_latitude_covariance(struct GnssPosition* self, float64_t lat_cov);

/**
 * @brief set longitude covariance to a GnssPosition
 *
 * @param self a GnssPosition
 * @param lon_cov longitude covariance
 * @return retcode_t
 */
retcode_t gnss_position_set_longitude_covariance(struct GnssPosition* self, float64_t lon_cov);

/**
 * @brief set altitude covariance to a GnssPosition
 *
 * @param self a GnssPosition
 * @param alt_cov altitude covariance
 * @return retcode_t
 */
retcode_t gnss_position_set_altitude_covariance(struct GnssPosition* self, float64_t alt_cov);

/**
 * @brief Get 4byte aligned serialized buffer size for GnssPosition.
 *
 * @param position The GnssPosition object.
 *
 * @return uint32_t Serialized size.
 *
 * @see gnss_position_get_serialized_size_8byte_aligned.
 */
uint32_t gnss_position_get_serialized_size_4byte_aligned(const struct GnssPosition* position);

/**
 * @brief Get 8byte aligned serialized buffer size for GnssPosition.
 *
 * @param position The GnssPosition object.
 *
 * @return uint32_t Serialized size.
 *
 * @see gnss_position_get_serialized_size_4byte_aligned.
 */
uint32_t gnss_position_get_serialized_size_8byte_aligned(const struct GnssPosition* position);

/**
 * @brief Default interface of getting GnssPosition serialize size.
 *
 * @param position The GnssPosition object.
 *
 * @return uint32_t Serialized size.
 */
uint32_t gnss_position_get_serialized_size(const struct GnssPosition* position);

/**
 * @brief Serialize GnssPosition 4byte aligned.
 *
 * @param position The GnssPosition object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see gnss_position_serialize_8byte_aligned.
 */
retcode_t gnss_position_serialize_4byte_aligned(const struct GnssPosition* position, uint8_t* buffer,
                                                uint32_t buffer_size);

/**
 * @brief Serialize GnssPosition 8byte aligned.
 *
 * @param position The GnssPosition object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see gnss_position_serialize_4byte_aligned.
 */
retcode_t gnss_position_serialize_8byte_aligned(const struct GnssPosition* position, uint8_t* buffer,
                                                uint32_t buffer_size);

/**
 * @brief Default interface serialize gnss position to buffer.
 *
 * @param position The GnssPosition object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 */
retcode_t gnss_position_serialize(const struct GnssPosition* position, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize GnssPosition 4byte aligned.
 *
 * @param position The GnssPosition object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see gnss_position_deserialize_8byte_aligned.
 */
retcode_t gnss_position_deserialize_4byte_aligned(struct GnssPosition* position, const uint8_t* buffer,
                                                  uint32_t buffer_size);

/**
 * @brief Deserialize GnssPosition 8byte aligned.
 *
 * @param position The GnssPosition object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 */
retcode_t gnss_position_deserialize_8byte_aligned(struct GnssPosition* position, const uint8_t* buffer,
                                                  uint32_t buffer_size);

/**
 * @brief Default interface deserialize gnss position from buffer.
 *
 * @param position The GnssPosition object.
 * @param buffer The buffer serialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes deserialized from buffer.
 */
retcode_t gnss_position_deserialize(struct GnssPosition* position, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_COMMON_GNSS_POSITION_H_
