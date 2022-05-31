/*!
 * @file mpc_object.h
 * @brief This header file defines bosch mpc object raw data structure and functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_MPC_STRUCTURE_MPC_OBJECT_H_
#define HOLO_C_SENSORS_MPC_STRUCTURE_MPC_OBJECT_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/types.h>
#include <holo_c/sensors/mobileye/mobileye_dbc_output.h>
#include <holo_c/utils/serialization.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 *
 */
#define MOBILEYE_OBJECT_NUM 8

/**
 * @brief Mpc object raw data
 *
 */
struct MobileyeObjectRawData
{
    struct Timestamp timestamp;

    uint16_t angle_left;
    uint16_t motion_status;			//! @note Defines motion status of detected vehicle
    uint16_t longitudial_dist;
    uint16_t id;					//! @brief object id
    uint16_t object_class;
    uint16_t object_index;
    uint16_t sync_frame_index;		//! @note synchronizes between the messages in the same frame

    uint16_t width;					//! @brief object width
    uint16_t relative_velocity;
    uint16_t right_angle_predicted;	//! @brief right angle predicted value
    uint16_t left_angle_predicted;	//! @brief left angle predicted value
    uint16_t acceleration_abs;		//! @brief absolute acceleration
    uint16_t angle_right;

    uint16_t lateral_distance;
    uint16_t extended_id;			//! @brief object extended id
    uint16_t angle_rate_mean;		//! @brief angle rate mean value
    uint16_t cut_in_cut_out;

    uint16_t object_age;			//! @note A counter that indicates how many frames the object has been active for.
    uint16_t lateral_velocity;
    uint16_t obstacle_replaced;		//! @brief obstacle replaced indicator
    uint16_t cipv_flag;				//! @brief critical pedestrain valid flag
};
HOLO_STATIC_ASSERT(sizeof(struct MobileyeObjectRawData) == 52);

struct MobileyeObjectListRawData
{
	uint32_t                num;
    struct MobileyeObjectRawData object[MOBILEYE_OBJECT_NUM];
};
HOLO_STATIC_ASSERT(sizeof(struct MobileyeObjectListRawData) == 420);

/**
 * @{
 * Begin setter API group
 *
 */
/**
 * @brief set mobileye object raw data timestamp
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param timestamp system timestamp
 */
static inline void mobileye_object_raw_data_set_timestamp(struct MobileyeObjectRawData* object_raw_data,
                                                     const struct Timestamp*  timestamp)
{
    object_raw_data->timestamp = *timestamp;
}

/**
 * @brief set mobileye object raw data angle_left
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param angle_left
 */
static inline void mobileye_object_raw_data_set_angle_left(struct MobileyeObjectRawData* object_raw_data, uint16_t angle_left)
{
    object_raw_data->angle_left = angle_left;
}

/**
 * @brief set mobileye object raw data motion_status
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param motion_status
 */
static inline void mobileye_object_raw_data_set_motion_status(struct MobileyeObjectRawData* object_raw_data, uint16_t motion_status)
{
    object_raw_data->motion_status = motion_status;
}

/**
 * @brief set mobileye object raw data longitudial_dist
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param longitudial_dist
 */
static inline void mobileye_object_raw_data_set_longitudial_dist(struct MobileyeObjectRawData* object_raw_data, uint16_t longitudial_dist)
{
    object_raw_data->longitudial_dist = longitudial_dist;
}

/**
 * @brief set mobileye object raw data id
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param id
 */
static inline void mobileye_object_raw_data_set_id(struct MobileyeObjectRawData* object_raw_data, uint16_t id)
{
    object_raw_data->id = id;
}

/**
 * @brief set mobileye object raw data object_class
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param object_class
 */
static inline void mobileye_object_raw_data_set_object_class(struct MobileyeObjectRawData* object_raw_data, uint16_t object_class)
{
    object_raw_data->object_class = object_class;
}

/**
 * @brief set mobileye object raw data object_index
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param object_index
 */
static inline void mobileye_object_raw_data_set_object_index(struct MobileyeObjectRawData* object_raw_data, uint16_t object_index)
{
    object_raw_data->object_index = object_index;
}

/**
 * @brief set mobileye object raw data sync_frame_index
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param sync_frame_index
 */
static inline void mobileye_object_raw_data_set_sync_frame_index(struct MobileyeObjectRawData* object_raw_data, uint16_t sync_frame_index)
{
    object_raw_data->sync_frame_index = sync_frame_index;
}

/**
 * @brief set mobileye object raw data width
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param width
 */
static inline void mobileye_object_raw_data_set_width(struct MobileyeObjectRawData* object_raw_data, uint16_t width)
{
    object_raw_data->width = width;
}

/**
 * @brief set mobileye object raw data relative_velocity
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param relative_velocity
 */
static inline void mobileye_object_raw_data_set_relative_velocity(struct MobileyeObjectRawData* object_raw_data, uint16_t relative_velocity)
{
    object_raw_data->relative_velocity = relative_velocity;
}

/**
 * @brief set mobileye object raw data right_angle_predicted
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param right_angle_predicted
 */
static inline void mobileye_object_raw_data_set_right_angle_predicted(struct MobileyeObjectRawData* object_raw_data, uint16_t right_angle_predicted)
{
    object_raw_data->right_angle_predicted = right_angle_predicted;
}

/**
 * @brief set mobileye object raw data left_angle_predicted
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param left_angle_predicted
 */
static inline void mobileye_object_raw_data_set_left_angle_predicted(struct MobileyeObjectRawData* object_raw_data, uint16_t left_angle_predicted)
{
    object_raw_data->left_angle_predicted = left_angle_predicted;
}

/**
 * @brief set mobileye object raw data acceleration_abs
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param acceleration_abs
 */
static inline void mobileye_object_raw_data_set_acceleration_abs(struct MobileyeObjectRawData* object_raw_data, uint16_t acceleration_abs)
{
    object_raw_data->acceleration_abs = acceleration_abs;
}

/**
 * @brief set mobileye object raw data angle_right
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param angle_right
 */
static inline void mobileye_object_raw_data_set_angle_right(struct MobileyeObjectRawData* object_raw_data, uint16_t angle_right)
{
    object_raw_data->angle_right = angle_right;
}

/**
 * @brief set mobileye object raw data lateral_distance
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param lateral_distance
 */
static inline void mobileye_object_raw_data_set_lateral_distance(struct MobileyeObjectRawData* object_raw_data, uint16_t lateral_distance)
{
    object_raw_data->lateral_distance = lateral_distance;
}

/**
 * @brief set mobileye object raw data extended_id
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param extended_id
 */
static inline void mobileye_object_raw_data_set_extended_id(struct MobileyeObjectRawData* object_raw_data, uint16_t extended_id)
{
    object_raw_data->extended_id = extended_id;
}

/**
 * @brief set mobileye object raw data angle_rate_mean
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param angle_rate_mean
 */
static inline void mobileye_object_raw_data_set_angle_rate_mean(struct MobileyeObjectRawData* object_raw_data, uint16_t angle_rate_mean)
{
    object_raw_data->angle_rate_mean = angle_rate_mean;
}

/**
 * @brief set mobileye object raw data cut_in_cut_out
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param cut_in_cut_out
 */
static inline void mobileye_object_raw_data_set_cut_in_cut_out(struct MobileyeObjectRawData* object_raw_data, uint16_t cut_in_cut_out)
{
    object_raw_data->cut_in_cut_out = cut_in_cut_out;
}

/**
 * @brief set mobileye object raw data object_age
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param object_age
 */
static inline void mobileye_object_raw_data_set_object_age(struct MobileyeObjectRawData* object_raw_data, uint16_t object_age)
{
    object_raw_data->object_age = object_age;
}

/**
 * @brief set mobileye object raw data lateral_velocity
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param lateral_velocity
 */
static inline void mobileye_object_raw_data_set_lateral_velocity(struct MobileyeObjectRawData* object_raw_data, uint16_t lateral_velocity)
{
    object_raw_data->lateral_velocity = lateral_velocity;
}

/**
 * @brief set mobileye object raw data obstacle_replaced
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param obstacle_replaced
 */
static inline void mobileye_object_raw_data_set_obstacle_replaced(struct MobileyeObjectRawData* object_raw_data, uint16_t obstacle_replaced)
{
    object_raw_data->obstacle_replaced = obstacle_replaced;
}

/**
 * @brief set mobileye object raw data cipv_flag
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param critical pedestrain valid flag cipv_flag
 */
static inline void mobileye_object_raw_data_set_cipv_flag(struct MobileyeObjectRawData* object_raw_data, uint16_t cipv_flag)
{
    object_raw_data->cipv_flag = cipv_flag;
}

/**
 * @}
 * End Setter API group
 *
 */

/**
 * @{
 * Begin Getter API group
 *
 */

/**
 * @brief get mobileye object raw data timestamp
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param timestamp timestamp pointer
 */
static inline const struct Timestamp* mobileye_object_raw_data_get_timestamp(struct MobileyeObjectRawData* object_raw_data)
{
    return &object_raw_data->timestamp;
}

/**
 * @brief get mobileye raw data angle_left
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data angle_left
 */
static inline uint16_t mobileye_object_raw_data_get_angle_left(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->angle_left;
}

/**
 * @brief get mobileye raw data motion_status
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data motion_status
 */
static inline uint16_t mobileye_object_raw_data_get_motion_status(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->motion_status;
}

/**
 * @brief get mobileye raw data longitudial_dist
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data longitudial_dist
 */
static inline uint16_t mobileye_object_raw_data_get_longitudial_dist(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->longitudial_dist;
}

/**
 * @brief get mobileye raw data id
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data id
 */
static inline uint16_t mobileye_object_raw_data_get_id(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->id;
}

/**
 * @brief get mobileye raw data object_class
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data object_class
 */
static inline uint16_t mobileye_object_raw_data_get_object_class(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->object_class;
}

/**
 * @brief get mobileye raw data object_index
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data object_index
 */
static inline uint16_t mobileye_object_raw_data_get_object_index(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->object_index;
}

/**
 * @brief get mobileye raw data sync_frame_index
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data sync_frame_index
 */
static inline uint16_t mobileye_object_raw_data_get_sync_frame_index(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->sync_frame_index;
}

/**
 * @brief get mobileye raw data width
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data width
 */
static inline uint16_t mobileye_object_raw_data_get_width(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->width;
}

/**
 * @brief get mobileye raw data relative_velocity
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data relative_velocity
 */
static inline uint16_t mobileye_object_raw_data_get_relative_velocity(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->relative_velocity;
}

/**
 * @brief get mobileye raw data right_angle_predicted
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data right_angle_predicted
 */
static inline uint16_t mobileye_object_raw_data_get_right_angle_predicted(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->right_angle_predicted;
}

/**
 * @brief get mobileye raw data left_angle_predicted
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data left_angle_predicted
 */
static inline uint16_t mobileye_object_raw_data_get_left_angle_predicted(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->left_angle_predicted;
}

/**
 * @brief get mobileye raw data acceleration_abs
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data acceleration_abs
 */
static inline uint16_t mobileye_object_raw_data_get_acceleration_abs(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->acceleration_abs;
}

/**
 * @brief get mobileye raw data angle_right
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data angle_right
 */
static inline uint16_t mobileye_object_raw_data_get_angle_right(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->angle_right;
}

/**
 * @brief get mobileye raw data lateral_distance
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data lateral_distance
 */
static inline uint16_t mobileye_object_raw_data_get_lateral_distance(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->lateral_distance;
}

/**
 * @brief get mobileye raw data extended_id
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data extended_id
 */
static inline uint16_t mobileye_object_raw_data_get_extended_id(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->extended_id;
}

/**
 * @brief get mobileye raw data angle_rate_mean
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data angle_rate_mean
 */
static inline uint16_t mobileye_object_raw_data_get_angle_rate_mean(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->angle_rate_mean;
}

/**
 * @brief get mobileye raw data cut_in_cut_out
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data cut_in_cut_out
 */
static inline uint16_t mobileye_object_raw_data_get_cut_in_cut_out(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->cut_in_cut_out;
}

/**
 * @brief get mobileye raw data object_age
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data object_age
 */
static inline uint16_t mobileye_object_raw_data_get_object_age(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->object_age;
}

/**
 * @brief get mobileye raw data lateral_velocity
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data lateral_velocity
 */
static inline uint16_t mobileye_object_raw_data_get_lateral_velocity(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->lateral_velocity;
}

/**
 * @brief get mobileye raw data obstacle_replaced
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data obstacle_replaced
 */
static inline uint16_t mobileye_object_raw_data_get_obstacle_replaced(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->obstacle_replaced;
}

/**
 * @brief get mobileye raw data cipv_flag
 *
 * @param object_raw_data mobileye object raw data pointer
 * @return uint16_t mobileye object raw data critical pedestrain valid flag cipv_flag
 */
static inline uint16_t mobileye_object_raw_data_get_cipv_flag(struct MobileyeObjectRawData* object_raw_data)
{
    return object_raw_data->cipv_flag;
}

/**
 * @}
 * End Getter API group
 *
 */
/**
 * @brief construct mobileye object raw data part0
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param msg mobileye can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mobileye_object_raw_data_construct_part0(struct MobileyeObjectRawData* object_raw_data, 
													const uint8_t* msg);

/**
 * @brief construct mobileye object raw data part1
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param msg mobileye can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mobileye_object_raw_data_construct_part1(struct MobileyeObjectRawData* object_raw_data, 
													const uint8_t* msg);

/**
 * @brief construct mobileye object raw data part2
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param msg mobileye can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mobileye_object_raw_data_construct_part2(struct MobileyeObjectRawData* object_raw_data, 
													const uint8_t* msg);

/**
 * @brief construct mobileye object raw data part3
 *
 * @param object_raw_data mobileye object raw data pointer
 * @param msg mobileye can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mobileye_object_raw_data_construct_part3(struct MobileyeObjectRawData* object_raw_data, 
													const uint8_t* msg);

/**
 * @brief Get 4byte aligned mobileye object list raw data serialized size.
 *
 * @param raw_data The mobileye object list raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see mobileye_object_list_raw_data_get_serialized_size_8byte_aligned.
 */
uint32_t mobileye_object_list_raw_data_get_serialized_size_4byte_aligned(const struct MobileyeObjectListRawData* raw_data);

/**
 * @brief Get 8byte aligned mobileye object list raw data serialized size.
 *
 * @param raw_data The mobileye object list raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see mobileye_object_list_raw_data_get_serialized_size_4byte_aligned.
 */
uint32_t mobileye_object_list_raw_data_get_serialized_size_8byte_aligned(const struct MobileyeObjectListRawData* raw_data);

/**
 * @brief Default get mobileye object list raw data serialized size.
 *
 * @param raw_data The mobileye object list raw data.
 *
 * @return uint32_t Serialized size.
 *
 */
uint32_t mobileye_object_list_raw_data_get_serialized_size(const struct MobileyeObjectListRawData* raw_data);

/**
 * @brief Serialize mobileye object list raw data 4byte aligned.
 *
 * @param raw_data The mobileye object list data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see mobileye_object_list_raw_data_serialize_8byte_aligned.
 */
retcode_t mobileye_object_list_raw_data_serialize_4byte_aligned(const struct MobileyeObjectListRawData* raw_data, uint8_t* buffer,
                                                           uint32_t buffer_size);

/**
 * @brief Serialize mobileye object list raw data 8byte aligned.
 *
 * @param raw_data The mobileye object list data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see mobileye_object_list_raw_data_serialize_4byte_aligned.
 */
retcode_t mobileye_object_list_raw_data_serialize_8byte_aligned(const struct MobileyeObjectListRawData* raw_data, uint8_t* buffer,
                                                           uint32_t buffer_size);

/**
 * @brief Default serialize mobileye object list raw data.
 *
 * @param raw_data The mobileye object list data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 */
retcode_t mobileye_object_list_raw_data_serialize(const struct MobileyeObjectListRawData* raw_data, uint8_t* buffer,
                                             uint32_t buffer_size);

/**
 * @brief Deserialize mobileye object list raw data 4byte aligned.
 *
 * @param raw_data The mobileye object list raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see mobileye_object_list_raw_data_deserialize_8byte_aligned.
 */
retcode_t mobileye_object_list_raw_data_deserialize_4byte_aligned(struct MobileyeObjectListRawData* raw_data,
                                                             const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize mobileye object list raw data 8byte aligned.
 *
 * @param raw_data The mobileye object list raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see mobileye_object_list_raw_data_deserialize_4byte_aligned.
 */
retcode_t mobileye_object_list_raw_data_deserialize_8byte_aligned(struct MobileyeObjectListRawData* raw_data,
                                                             const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Default deserialize mobileye object list raw data.
 *
 * @param raw_data The mobileye object list raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 */
retcode_t mobileye_object_list_raw_data_deserialize(struct MobileyeObjectListRawData* raw_data, const uint8_t* buffer,
                                               uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
