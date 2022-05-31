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
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>
#include <holo_c/utils/serialization.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 *
 */
#define MPC_OBJECT_NUM 16

/**
 * @brief Mpc object raw data
 *
 */
struct MpcObjectRawData
{
    struct Timestamp timestamp;

    uint16_t confidence;
    uint16_t id;
    uint16_t classification;
    uint16_t age;
    uint16_t inv_ttc;
    uint16_t lon_dist;
    uint16_t lon_velocity;
    uint16_t angle_center;
    uint16_t angle_width;
    uint16_t angle_speed;
    uint16_t angle_edge_left;
    uint16_t angle_edge_right;
    uint16_t angle_overlap_egolane_right;
    uint16_t angle_overlap_egolane_left;
};
HOLO_STATIC_ASSERT(sizeof(struct MpcObjectRawData) == 36);

struct MpcObjectListRawData
{
    uint32_t                num;
    struct MpcObjectRawData object[MPC_OBJECT_NUM];
};

/**
 * @{
 * Begin setter API group
 *
 */
/**
 * @brief set mpc object raw data timestamp
 *
 * @param object_raw_data mpc object raw data pointer
 * @param timestamp system timestamp
 */
static inline void mpc_object_raw_data_set_timestamp(struct MpcObjectRawData* object_raw_data,
                                                     const struct Timestamp*  timestamp)
{
    object_raw_data->timestamp = *timestamp;
}
/**
 * @brief set mpc object raw data confidence
 *
 * @param object_raw_data mpc object raw data pointer
 * @param confidence raw data confidence value
 */
static inline void mpc_object_raw_data_set_confidence(struct MpcObjectRawData* object_raw_data, uint16_t confidence)
{
    object_raw_data->confidence = confidence;
}

/**
 * @brief set mpc object raw data id
 *
 * @param object_raw_data mpc object raw data pointer
 * @param id raw data id value
 */
static inline void mpc_object_raw_data_set_id(struct MpcObjectRawData* object_raw_data, uint16_t id)
{
    object_raw_data->id = id;
}

/**
 * @brief set mpc object raw data classification
 *
 * @param object_raw_data mpc object raw data pointer
 * @param classification raw data classification value
 */
static inline void mpc_object_raw_data_set_classification(struct MpcObjectRawData* object_raw_data,
                                                          uint16_t                 classification)
{
    object_raw_data->classification = classification;
}

/**
 * @brief set mpc object raw data age
 *
 * @param object_raw_data mpc object raw data pointer
 * @param age raw data age value
 */
static inline void mpc_object_raw_data_set_age(struct MpcObjectRawData* object_raw_data, uint16_t age)
{
    object_raw_data->age = age;
}

/**
 * @brief set mpc object raw data inv_ttc
 *
 * @param object_raw_data mpc object raw data pointer
 * @param inv_ttc raw data inv_ttc value
 */
static inline void mpc_object_raw_data_set_inv_ttc(struct MpcObjectRawData* object_raw_data, uint16_t inv_ttc)
{
    object_raw_data->inv_ttc = inv_ttc;
}

/**
 * @brief set mpc object raw data lon_dist
 *
 * @param object_raw_data mpc object raw data pointer
 * @param lon_dist raw data lon_dist value
 */
static inline void mpc_object_raw_data_set_lon_dist(struct MpcObjectRawData* object_raw_data, uint16_t lon_dist)
{
    object_raw_data->lon_dist = lon_dist;
}

/**
 * @brief set mpc object raw data lon_velocity
 *
 * @param object_raw_data mpc object raw data pointer
 * @param lon_velocity raw data lon_velocity value
 */
static inline void mpc_object_raw_data_set_lon_velocity(struct MpcObjectRawData* object_raw_data, uint16_t lon_velocity)
{
    object_raw_data->lon_velocity = lon_velocity;
}

/**
 * @brief set mpc object raw data angle_center
 *
 * @param object_raw_data mpc object raw data pointer
 * @param angle_center raw data angle_center value
 */
static inline void mpc_object_raw_data_set_angle_center(struct MpcObjectRawData* object_raw_data, uint16_t angle_center)
{
    object_raw_data->angle_center = angle_center;
}

/**
 * @brief set mpc object raw data angle_width
 *
 * @param object_raw_data mpc object raw data pointer
 * @param angle_width raw data angle width value
 */
static inline void mpc_object_raw_data_set_angle_width(struct MpcObjectRawData* object_raw_data, uint16_t angle_width)
{
    object_raw_data->angle_width = angle_width;
}

/**
 * @brief set mpc object raw data angle speed
 *
 * @param object_raw_data mpc object raw data pointer
 * @param angle_speed raw data angle speed value
 */
static inline void mpc_object_raw_data_set_angle_speed(struct MpcObjectRawData* object_raw_data, uint16_t angle_speed)
{
    object_raw_data->angle_speed = angle_speed;
}

/**
 * @brief set mpc object raw data angle edge left
 *
 * @param object_raw_data mpc object raw data pointer
 * @param angle_edge_left raw data angle edge left value
 */
static inline void mpc_object_raw_data_set_angle_edge_left(struct MpcObjectRawData* object_raw_data,
                                                           uint16_t                 angle_edge_left)
{
    object_raw_data->angle_edge_left = angle_edge_left;
}

/**
 * @brief set mpc object raw data angle edge right
 *
 * @param object_raw_data mpc object raw data pointer
 * @param angle_edge_right raw data angle edge right value
 */
static inline void mpc_object_raw_data_set_angle_edge_right(struct MpcObjectRawData* object_raw_data,
                                                            uint16_t                 angle_edge_right)
{
    object_raw_data->angle_edge_right = angle_edge_right;
}

/**
 * @brief set mpc object raw data angle overlap egolane left
 *
 * @param object_raw_data mpc object raw data pointer
 * @param angle_overlap_egolane_left mpc raw data angle overlap egolane left value
 */
static inline void mpc_object_raw_data_set_angle_overlap_egolane_left(struct MpcObjectRawData* object_raw_data,
                                                                      uint16_t angle_overlap_egolane_left)
{
    object_raw_data->angle_overlap_egolane_left = angle_overlap_egolane_left;
}

/**
 * @brief set mpc object raw data angle overlap egolane right
 *
 * @param object_raw_data mpc object raw data pointer
 * @param angle_overlap_egolane_right mpc raw data angle overlap egolane right value
 */
static inline void mpc_object_raw_data_set_angle_overlap_egolane_right(struct MpcObjectRawData* object_raw_data,
                                                                       uint16_t angle_overlap_egolane_right)
{
    object_raw_data->angle_overlap_egolane_right = angle_overlap_egolane_right;
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
 * @brief get mpc object raw data timestamp
 *
 * @param object_raw_data mpc object raw data pointer
 * @param timestamp timestamp pointer
 */
static inline const struct Timestamp* mpc_object_raw_data_get_timestamp(struct MpcObjectRawData* object_raw_data)
{
    return &object_raw_data->timestamp;
}

/**
 * @brief get mpc raw data confidence
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data confidence
 */
static inline uint16_t mpc_object_raw_data_get_confidence(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->confidence;
}

/**
 * @brief get mpc raw data id
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data id
 */
static inline uint16_t mpc_object_raw_data_get_id(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->id;
}

/**
 * @brief get mpc raw data classification
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data classification
 */
static inline uint16_t mpc_object_raw_data_get_classification(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->classification;
}

/**
 * @brief get mpc raw data age
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data age
 */
static inline uint16_t mpc_object_raw_data_get_age(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->age;
}

/**
 * @brief get mpc raw data inv_ttc
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data inv_ttc
 */
static inline uint16_t mpc_object_raw_data_get_inv_ttc(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->inv_ttc;
}

/**
 * @brief get mpc raw data lon dist
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data lon dist
 */
static inline uint16_t mpc_object_raw_data_get_lon_dist(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->lon_dist;
}

/**
 * @brief get mpc raw data lon velocity
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data lon velocity
 */
static inline uint16_t mpc_object_raw_data_get_lon_velocity(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->lon_velocity;
}

/**
 * @brief get mpc raw data angle center
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data angle center
 */
static inline uint16_t mpc_object_raw_data_get_angle_center(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->angle_center;
}

/**
 * @brief get mpc raw data angle width
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data angle width
 */
static inline uint16_t mpc_object_raw_data_get_angle_width(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->angle_width;
}

/**
 * @brief get mpc raw data angle speed
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data angle speed
 */
static inline uint16_t mpc_object_raw_data_get_angle_speed(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->angle_speed;
}

/**
 * @brief get mpc raw data angle edge left
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data angle edge left
 */
static inline uint16_t mpc_object_raw_data_get_angle_edge_left(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->angle_edge_left;
}

/**
 * @brief get mpc raw data angle edge right
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data angle edge right
 */
static inline uint16_t mpc_object_raw_data_get_angle_edge_right(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->angle_edge_right;
}

/**
 * @brief get mpc raw data angle overlap egolane left
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data angle overlap egolane left
 */
static inline uint16_t mpc_object_raw_data_get_angle_overlap_egolane_left(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->angle_overlap_egolane_left;
}

/**
 * @brief get mpc raw data angle overlap egolane right
 *
 * @param object_raw_data mpc object raw data pointer
 * @return uint16_t mpc object raw data angle overlap egolane right
 */
static inline uint16_t mpc_object_raw_data_get_angle_overlap_egolane_right(struct MpcObjectRawData* object_raw_data)
{
    return object_raw_data->angle_overlap_egolane_right;
}

/**
 * @}
 * End Getter API group
 *
 */
/**
 * @brief construct mpc object raw data partA
 *
 * @param object_raw_data mpc object raw data pointer
 * @param msg mpc can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mpc_object_raw_data_construct_partA(struct MpcObjectRawData* object_raw_data, const uint8_t* msg);

/**
 * @brief construct mpc object raw data partB
 *
 * @param object_raw_data mpc object raw data pointer
 * @param msg mpc can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mpc_object_raw_data_construct_partB(struct MpcObjectRawData* object_raw_data, const uint8_t* msg);

/**
 * @brief construct mpc object raw data partC
 *
 * @param object_raw_data mpc object raw data pointer
 * @param msg mpc can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mpc_object_raw_data_construct_partC(struct MpcObjectRawData* object_raw_data, const uint8_t* msg);

/**
 * @brief construct mpc object raw data partD
 *
 * @param object_raw_data mpc object raw data pointer
 * @param msg mpc can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mpc_object_raw_data_construct_partD(struct MpcObjectRawData* object_raw_data, const uint8_t* msg);

/**
 * @brief construct mpc object raw data partE
 *
 * @param object_raw_data mpc object raw data pointer
 * @param msg mpc can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mpc_object_raw_data_construct_partE(struct MpcObjectRawData* object_raw_data, const uint8_t* msg);

/**
 * @brief Get 4byte aligned mpc object list raw data serialized size.
 *
 * @param raw_data The mpc object list raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see mpc_object_list_raw_data_get_serialized_size_8byte_aligned.
 */
uint32_t mpc_object_list_raw_data_get_serialized_size_4byte_aligned(const struct MpcObjectListRawData* raw_data);

/**
 * @brief Get 8byte aligned mpc object list raw data serialized size.
 *
 * @param raw_data The mpc object list raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see mpc_object_list_raw_data_get_serialized_size_4byte_aligned.
 */
uint32_t mpc_object_list_raw_data_get_serialized_size_8byte_aligned(const struct MpcObjectListRawData* raw_data);

/**
 * @brief Default get mpc object list raw data serialized size.
 *
 * @param raw_data The mpc object list raw data.
 *
 * @return uint32_t Serialized size.
 *
 */
uint32_t mpc_object_list_raw_data_get_serialized_size(const struct MpcObjectListRawData* raw_data);

/**
 * @brief Serialize Mpc object list raw data 4byte aligned.
 *
 * @param position The Mpc object list data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see mpc_object_list_raw_data_serialize_8byte_aligned.
 */
retcode_t mpc_object_list_raw_data_serialize_4byte_aligned(const struct MpcObjectListRawData* raw_data, uint8_t* buffer,
                                                           uint32_t buffer_size);

/**
 * @brief Serialize Mpc object list raw data 8byte aligned.
 *
 * @param position The Mpc object list data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see mpc_object_list_raw_data_serialize_4byte_aligned.
 */
retcode_t mpc_object_list_raw_data_serialize_8byte_aligned(const struct MpcObjectListRawData* raw_data, uint8_t* buffer,
                                                           uint32_t buffer_size);

/**
 * @brief Default serialize Mpc object list raw data.
 *
 * @param position The Mpc object list data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 */
retcode_t mpc_object_list_raw_data_serialize(const struct MpcObjectListRawData* raw_data, uint8_t* buffer,
                                             uint32_t buffer_size);

/**
 * @brief Deserialize Mpc object list raw data 4byte aligned.
 *
 * @param position The Mpc object list raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see mpc_object_list_raw_data_deserialize_8byte_aligned.
 */
retcode_t mpc_object_list_raw_data_deserialize_4byte_aligned(struct MpcObjectListRawData* raw_data,
                                                             const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize Mpc object list raw data 8byte aligned.
 *
 * @param position The Mpc object list raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see mpc_object_list_raw_data_deserialize_4byte_aligned.
 */
retcode_t mpc_object_list_raw_data_deserialize_8byte_aligned(struct MpcObjectListRawData* raw_data,
                                                             const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Default deserialize Mpc object list raw data.
 *
 * @param position The Mpc object list raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 */
retcode_t mpc_object_list_raw_data_deserialize(struct MpcObjectListRawData* raw_data, const uint8_t* buffer,
                                               uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
