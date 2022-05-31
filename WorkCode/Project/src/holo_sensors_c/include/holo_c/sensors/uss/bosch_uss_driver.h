/*!
 * @file bosch_uss_driver.h
 * @brief This header file defines bosch uss sensor driver functions
 * @author liuya@holomatic.com
 * @date 2019-12-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_USS_BOSCH_USS_DRIVER_H_
#define HOLO_C_SENSORS_USS_BOSCH_USS_DRIVER_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OBJECT_LIST_NUM 12

/**
 * @addtogroup sensors
 * @{
 */

/**
 * @brief Define bosch uss object list struct
 *
 */
struct BoschUssObjectList
{
    struct Timestamp timestamp;
    uint16_t         object_list[OBJECT_LIST_NUM];
};
HOLO_STATIC_ASSERT(sizeof(struct BoschUssObjectList) == 32);

/**
 * @brief Whether bosch uss can message id is valid.
 *
 * @param id Can message id.
 * @return retcode_t RC_SUCCESS Can id is valid.
 * @return retcode_t RC_FAIL Can id is invalid.
 */
retcode_t bosch_uss_can_id_is_valid(uint32_t id);

/**
 * @brief Convert can message to bosch object list
 *
 * @param list Bosch object list
 * @param timestamp System timestamp
 * @param id Can message id
 * @param data Can message data
 * @param len Can message length
 * @return retcode_t RC_SUCCESS
 */
retcode_t bosch_uss_driver_process_data(struct BoschUssObjectList* list, const struct Timestamp* timestamp, uint32_t id,
                                        const uint8_t* data, uint8_t len);

/**
 * @brief Set bosch uss object list timestamp
 *
 * @param data Bosch uss object list
 * @param timestamp Sys time timestamp.
 * @return retcode_t RC_SUCCESS
 */
retcode_t bosch_uss_object_list_set_timestamp(struct BoschUssObjectList* data, const struct Timestamp* timestamp);

/**
 * @brief Set bosch uss object
 *
 * @param data Bosch uss object list
 * @param object Bosch uss object
 * @param index Object index
 * @return retcode_t RC_SUCCESS
 */
retcode_t bosch_uss_object_list_set_object(struct BoschUssObjectList* data, const uint16_t object, const uint8_t index);

/**
 * @brief Get bosch uss object list timestamp
 *
 * @param data Bosch uss object list
 * @return timestamp Timestamp pointer
 */
const struct Timestamp* bosch_uss_object_list_get_timestamp(struct BoschUssObjectList* data);

/**
 * @brief Get bosch uss object
 *
 * @param data Bosch uss object list
 * @param index Object index
 * @return const uint16_t Bosch uss object
 */
uint16_t bosch_uss_object_list_get_object(struct BoschUssObjectList* data, uint8_t index);

/**
 * @brief Get 4byte aligned serialized buffer size for BoschUssObjectList.
 *
 * @param data Bosch uss object list.
 *
 * @return uint32_t Serialized size.
 *
 * @see bosch_uss_object_list_get_serialized_size_8byte_aligned.
 */
uint32_t bosch_uss_object_list_get_serialized_size_4byte_aligned(const struct BoschUssObjectList* data);

/**
 * @brief Get 8byte aligned serialized buffer size for BoschUssObjectList.
 *
 * @param data Bosch uss object list.
 *
 * @return uint32_t Serialized size.
 *
 * @see bosch_uss_object_list_get_serialized_size_4byte_aligned.
 */
uint32_t bosch_uss_object_list_get_serialized_size_8byte_aligned(const struct BoschUssObjectList* data);

/**
 * @brief Default interface of getting BoschUssObjectList serialized size.
 *
 * @param data Bosch uss object list.
 *
 * @return uint32_t Serialized size.
 */
uint32_t bosch_uss_object_list_get_serialized_size(const struct BoschUssObjectList* data);

/**
 * @brief Serialize BoschUssObjectList 4byte aligned.
 *
 * @param data Bosch uss object list.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see bosch_uss_object_list_serialize_8byte_aligned
 */
retcode_t bosch_uss_object_list_serialize_4byte_aligned(const struct BoschUssObjectList* data, uint8_t* buffer,
                                                        uint32_t buffer_size);

/**
 * @brief Serialize BoschUssObjectList 8byte aligned.
 *
 * @param data Bosch uss object list.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see bosch_uss_object_list_serialize_4byte_aligned
 */
retcode_t bosch_uss_object_list_serialize_8byte_aligned(const struct BoschUssObjectList* data, uint8_t* buffer,
                                                        uint32_t buffer_size);

/**
 * @brief Default interface serialize BoschUssObjectList.
 *
 * @param data Bosch uss object list.
 * @param buffer  The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 */
retcode_t bosch_uss_object_list_serialize(const struct BoschUssObjectList* data, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize BoschUssObjectList 4byte aligned.
 *
 * @param data Bosch uss object list.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see bosch_uss_object_list_deserialize_8byte_aligned.
 */
retcode_t bosch_uss_object_list_deserialize_4byte_aligned(struct BoschUssObjectList* data, const uint8_t* buffer,
                                                          uint32_t buffer_size);

/**
 * @brief Deserialize BoschUssObjectList 8byte aligned.
 *
 * @param data Bosch uss object list.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see bosch_uss_object_list_deserialize_4byte_aligned.
 */
retcode_t bosch_uss_object_list_deserialize_8byte_aligned(struct BoschUssObjectList* data, const uint8_t* buffer,
                                                          uint32_t buffer_size);

/**
 * @brief Default deserialize BoschUssObjectList.
 *
 * @param data Bosch uss object list.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 */
retcode_t bosch_uss_object_list_deserialize(struct BoschUssObjectList* data, const uint8_t* buffer,
                                            uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_SENSORS_USS_BOSCH_USS_DRIVER_H_
