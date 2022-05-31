/*!
 * @file aceinna_imu_driver.h
 * @brief This header file defines aceinna imu sensor driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_ACEINNA_ACEINNA_IMU_DRIVER_H_
#define HOLO_C_SENSORS_ACEINNA_ACEINNA_IMU_DRIVER_H_

#include <holo_c/common/imu_float32.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 */

/**
 * @brief Aceinna imu data parse state machine
 *
 */
enum AceinnaImuParseState
{
    ACEINNA_IMU_PARSE_IDLE = 0,
    ACEINNA_IMU_PARSE_LINEAR_ACC,
    ACEINNA_IMU_PARSE_GYROSCOPE,
    ACEINNA_IMU_PARSE_ERROR,
};

/**
 * @brief Define aceinna imu can msg raw data struct
 *
 */
struct AceinnaImuRawData
{
    struct Timestamp timestamp;
    uint16_t         linear_acc_x;
    uint16_t         linear_acc_y;
    uint16_t         linear_acc_z;
    uint16_t         angle_rate_x;
    uint16_t         angle_rate_y;
    uint16_t         angle_rate_z;
};
HOLO_STATIC_ASSERT(sizeof(struct AceinnaImuRawData) == 20);

/**
 * @brief Define aceinna imu driver struct
 *
 */
struct AceinnaImuDriver
{
    enum AceinnaImuParseState parse_state;   ///< imu parse state
    struct AceinnaImuRawData  imu_raw_data;  ///< imu raw data
};

/**
 * @brief Construct Imuf message from aceinna can raw data
 *
 * @param imu Imuf message pointer
 * @param raw_data Aceinna can raw data
 * @return retcode_t RC_SUCCESS
 */
retcode_t aceinna_imu_raw_data_to_imuf(struct Imuf* imu, struct AceinnaImuRawData* raw_data);

/**
 * @brief Set aceinna imu raw data timestamp
 *
 * @param raw_data Aceinna imu raw data
 * @param timestamp Sys time timestamp
 * @return retcode_t RC_SUCCESS
 */
retcode_t aceinna_imu_raw_data_set_timestamp(struct AceinnaImuRawData* raw_data, const struct Timestamp* timestamp);

/**
 * @brief Get aceinna imu raw data timestamp
 *
 * @param raw_data Aceinna imu raw data
 * @param timestamp Sys time timestamp pointer
 * @return retcode_t RC_SUCCESS
 */
const struct Timestamp* aceinna_imu_raw_data_get_timestamp(struct AceinnaImuRawData* raw_data);

/**
 * @brief Set aceinna imu raw data linear acc x
 *
 * @param raw_data Aceinna imu raw data
 * @param acc_x Linear acc x raw value
 * @return retcode_t RC_SUCCESS
 */
retcode_t aceinna_imu_raw_data_set_acc_x(struct AceinnaImuRawData* raw_data, uint16_t acc_x);

/**
 * @brief Get aceinna imu raw data linear acc x
 *
 * @param raw_data Aceinna imu raw data
 * @return retcode_t Linear acc x raw data
 */
uint16_t aceinna_imu_raw_data_get_acc_x(struct AceinnaImuRawData* raw_data);

/**
 * @brief Set aceinna imu raw data linear acc y
 *
 * @param raw_data Aceinna imu raw data
 * @param acc_y Linear acc y raw value
 * @return retcode_t RC_SUCCESS
 */
retcode_t aceinna_imu_raw_data_set_acc_y(struct AceinnaImuRawData* raw_data, uint16_t acc_y);

/**
 * @brief Get aceinna imu raw data linear acc y
 *
 * @param raw_data Aceinna imu raw data
 * @return retcode_t Linear acc y raw data
 */
uint16_t aceinna_imu_raw_data_get_acc_y(struct AceinnaImuRawData* raw_data);

/**
 * @brief Set aceinna imu raw data linear acc z
 *
 * @param raw_data Aceinna imu raw data
 * @param acc_z Linear acc z raw value
 * @return retcode_t RC_SUCCESS
 */
retcode_t aceinna_imu_raw_data_set_acc_z(struct AceinnaImuRawData* raw_data, uint16_t acc_z);

/**
 * @brief Get aceinna imu raw data linear acc z
 *
 * @param raw_data Aceinna imu raw data
 * @param acc_z Linear acc z raw value pointer
 * @return retcode_t Linear acc z raw value
 */
uint16_t aceinna_imu_raw_data_get_acc_z(struct AceinnaImuRawData* raw_data);

/**
 * @brief Set aceinna imu raw data gyroscope x
 *
 * @param raw_data Aceinna imu raw data
 * @param gyroscope_x Gyroscope x raw value
 * @return retcode_t RC_SUCCESS
 */
retcode_t aceinna_imu_raw_data_set_gyroscope_x(struct AceinnaImuRawData* raw_data, uint16_t gyroscope_x);

/**
 * @brief Get imu raw data gyroscope x
 *
 * @param raw_data Aceinna imu raw data
 * @return retcode_t Gyroscope x raw value
 */
uint16_t aceinna_imu_raw_data_get_gyroscope_x(struct AceinnaImuRawData* raw_data);

/**
 * @brief Set aceinna imu raw data gyroscope y
 *
 * @param raw_data Aceinna imu raw data
 * @param gyroscope_y Gyroscope y raw value
 * @return retcode_t RC_SUCCESS
 */
retcode_t aceinna_imu_raw_data_set_gyroscope_y(struct AceinnaImuRawData* raw_data, uint16_t gyroscope_y);

/**
 * @brief Get imu raw data gyroscope y
 *
 * @param raw_data Aceinna imu raw data
 * @return retcode_t Gyroscope y raw value
 */
uint16_t aceinna_imu_raw_data_get_gyroscope_y(struct AceinnaImuRawData* raw_data);

/**
 * @brief Set aceinna imu raw data gyroscope z
 *
 * @param raw_data Aceinna imu raw data
 * @param gyroscope_z Gyroscope z raw value
 * @return retcode_t RC_SUCCESS
 */
retcode_t aceinna_imu_raw_data_set_gyroscope_z(struct AceinnaImuRawData* raw_data, uint16_t gyroscope_z);

/**
 * @brief Get imu raw data gyroscope z
 *
 * @param raw_data Aceinna imu raw data
 * @return retcode_t Gyroscope z raw value
 */
uint16_t aceinna_imu_raw_data_get_gyroscope_z(struct AceinnaImuRawData* raw_data);

/**
 * @brief Init aceinna imu driver
 *
 * @param driver Aceinna imu driver pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t aceinna_imu_driver_init(struct AceinnaImuDriver* driver);

/**
 * @brief Construct Imuf msg
 *
 * @param driver Aceinna imu driver pointer
 * @param id CAN msg id
 * @param data CAN msg data
 * @param len CAN msg data length
 * @return retcode_t RC_SUCCESS(complete), RC_PARSE_ACEINNA_IMU_CONTINUE(got linear acc, wait angle rate)
 *                   RC_PARSE_ACEINNA_IMU_DATA_ERROR(data error), RC_PARSE_ACEINNA_IMU_ID_ERROR(msg id error)
 */
retcode_t aceinna_imu_driver_process_data(struct AceinnaImuDriver* driver, const struct Timestamp* timestamp,
                                          uint32_t id, const uint8_t* data, uint8_t len);

/**
 * @brief Get 4byte aligned serialized buffer size for AceinnaImuRawData.
 *
 * @param raw_data Aceinna imu can raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see aceinna_imu_raw_data_get_serialized_size_8byte_aligned.
 */
uint32_t aceinna_imu_raw_data_get_serialized_size_4byte_aligned(const struct AceinnaImuRawData* raw_data);

/**
 * @brief Get 8byte aligned serialized buffer size for AceinnaImuRawData.
 *
 * @param raw_data Aceinna imu can raw data.
 *
 * @return uint32_t Deserialized size.
 *
 * @see aceinna_imu_raw_data_get_serialized_size_4byte_aligned.
 */
uint32_t aceinna_imu_raw_data_get_serialized_size_8byte_aligned(const struct AceinnaImuRawData* raw_data);

/**
 * @brief Default interface of getting AceinnaImuRawData serialized size.
 *
 * @param raw_data Aceinna imu can raw data.
 *
 * @return uint32_t Serialized size.
 */
uint32_t aceinna_imu_raw_data_get_serialized_size(const struct AceinnaImuRawData* raw_data);

/**
 * @brief Serialize AceinnaImuRawData 4byte aligned.
 *
 * @param raw_data Aceinna imu raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see aceinna_imu_raw_data_serialize_8byte_aligned
 */
retcode_t aceinna_imu_raw_data_serialize_4byte_aligned(const struct AceinnaImuRawData* raw_data, uint8_t* buffer,
                                                       uint32_t buffer_size);

/**
 * @brief Serialize AceinnaImuRawData 8byte aligned.
 *
 * @param raw_data Aceinna imu raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see aceinna_imu_raw_data_serialize_4byte_aligned
 */
retcode_t aceinna_imu_raw_data_serialize_8byte_aligned(const struct AceinnaImuRawData* raw_data, uint8_t* buffer,
                                                       uint32_t buffer_size);

/**
 * @brief Default interface serialize AceinnaImuRawData.
 *
 * @param raw_data Aceinna imu raw data.
 * @param buffer  The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 */
retcode_t aceinna_imu_raw_data_serialize(const struct AceinnaImuRawData* raw_data, uint8_t* buffer,
                                         uint32_t buffer_size);

/**
 * @brief Deserialize AceinnaImuRawData 4byte aligned.
 *
 * @param raw_data Aceinna imu raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see aceinna_imu_raw_data_deserialize_8byte_aligned.
 */
retcode_t aceinna_imu_raw_data_deserialize_4byte_aligned(struct AceinnaImuRawData* raw_data, const uint8_t* buffer,
                                                         uint32_t buffer_size);

/**
 * @brief Deserialize AceinnaImuRawData 8byte aligned.
 *
 * @param raw_data Aceinna imu raw data.
 * @param buffer The buffer to serialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see aceinna_imu_raw_data_deserialize_4byte_aligned.
 */
retcode_t aceinna_imu_raw_data_deserialize_8byte_aligned(struct AceinnaImuRawData* raw_data, const uint8_t* buffer,
                                                         uint32_t buffer_size);

/**
 * @brief Default deserialize AceinnaImuRawData.
 *
 * @param raw_data Aceinna imu raw data.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 */
retcode_t aceinna_imu_raw_data_deserialize(struct AceinnaImuRawData* raw_data, const uint8_t* buffer,
                                           uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_SENSORS_ACEINNA_ACEINNA_IMU_DRIVER_H_
