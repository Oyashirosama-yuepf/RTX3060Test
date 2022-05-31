/*!
 * @file ifv300_object.h
 * @brief This header file defines ifv300 object raw data structure and functions
 * @author liuya@holomatic.com
 * @date 2020-04-15
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_IFV300_STRUCTURE_IFV300_OBJECT_H
#define HOLO_C_SENSORS_IFV300_STRUCTURE_IFV300_OBJECT_H

#include <holo_c/common/timestamp.h>
#include <holo_c/core/types.h>
#include <holo_c/utils/serialization.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 *
 */
#define IFV_OBJECT_NUM 15

/**
 * @brief IFV300 object raw data
 *
 */
struct IfvObjectRawData
{
    struct Timestamp timestamp;

    struct
    {
        uint16_t message_counter_msg1;
        uint16_t count_msg1;
        uint16_t id;
        uint16_t classification;
        uint16_t ped_waise_up;
        uint16_t turn_indicator;
        uint16_t brake_light_indicator;
        uint16_t height;
    } part_A;

    struct
    {
        uint16_t message_counter_msg2;
        uint16_t count_msg2;
        uint16_t long_accel;
        uint16_t ttc_const_acc_model;
        uint16_t cut_in_cut_out;
        uint16_t reserved[3];
    } part_B;

    struct
    {
        uint16_t message_counter_msg3;
        uint16_t count_msg3;
        uint16_t lat_pos;
        uint16_t lat_vel;
        uint16_t long_pos;
        uint16_t long_vel;
        uint16_t width;
        uint16_t reserved;
    } part_C;
};
HOLO_STATIC_ASSERT(sizeof(struct IfvObjectRawData) == 56);

struct IfvObjectListRawData
{
    uint32_t                vehicle_speed;
    uint32_t                num;
    struct IfvObjectRawData object[IFV_OBJECT_NUM];
};

/**
 * @{
 * Begin setter API group
 *
 */

/**
 * @brief Set ifv object timestamp
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param timestamp Timestamp pointer
 */
static inline void ifv_object_raw_data_set_timestamp(struct IfvObjectRawData* object_raw_data,
                                                     const struct Timestamp*  timestamp)
{
    object_raw_data->timestamp = *timestamp;
}

/**
 * @brief Set ifv object raw data message counter msg1
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value message counter msg1 value
 */
static inline void ifv_object_raw_data_set_message_counter_msg1(struct IfvObjectRawData* object_raw_data,
                                                                uint16_t                 value)
{
    object_raw_data->part_A.message_counter_msg1 = value;
}

/**
 * @brief Set ifv object raw data count msg1
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value count msg1 value
 */
static inline void ifv_object_raw_data_set_count_msg1(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_A.count_msg1 = value;
}

/**
 * @brief Set ifv object raw data id
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value id value
 */
static inline void ifv_object_raw_data_set_id(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_A.id = value;
}

/**
 * @brief Set ifv object raw data classification
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value classification value
 */
static inline void ifv_object_raw_data_set_classification(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_A.classification = value;
}

/**
 * @brief Set ifv object raw data ped waise up
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value ped waise up value
 */
static inline void ifv_object_raw_data_set_ped_waise_up(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_A.ped_waise_up = value;
}

/**
 * @brief Set ifv object raw data ped turn indicator
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value ped turn indicator value
 */
static inline void ifv_object_raw_data_set_turn_indicator(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_A.turn_indicator = value;
}

/**
 * @brief Set ifv object raw data brake light indicator
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value brake light indicator value
 */
static inline void ifv_object_raw_data_set_brake_light_indicator(struct IfvObjectRawData* object_raw_data,
                                                                 uint16_t                 value)
{
    object_raw_data->part_A.brake_light_indicator = value;
}

/**
 * @brief Set ifv object raw data height
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value height value
 */
static inline void ifv_object_raw_data_set_height(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_A.height = value;
}

/**
 * @brief Set ifv object raw data message counter msg2
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value message counter msg2 value
 */
static inline void ifv_object_raw_data_set_message_counter_msg2(struct IfvObjectRawData* object_raw_data,
                                                                uint16_t                 value)
{
    object_raw_data->part_B.message_counter_msg2 = value;
}

/**
 * @brief Set ifv object raw data count msg2
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value count msg2 value
 */
static inline void ifv_object_raw_data_set_count_msg2(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_B.count_msg2 = value;
}

/**
 * @brief Set ifv object raw data long accel
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value long accel value
 */
static inline void ifv_object_raw_data_set_long_accel(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_B.long_accel = value;
}

/**
 * @brief Set ifv object raw data ttc const acc model
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value ttc const acc model value
 */
static inline void ifv_object_raw_data_set_ttc_const_acc_model(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_B.ttc_const_acc_model = value;
}

/**
 * @brief Set ifv object raw data cut in cut out
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value cut in cut out value
 */
static inline void ifv_object_raw_data_set_cut_in_cut_out(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_B.cut_in_cut_out = value;
}

/**
 * @brief Set ifv object raw data message counter msg3
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value message counter msg3 value
 */
static inline void ifv_object_raw_data_set_message_counter_msg3(struct IfvObjectRawData* object_raw_data,
                                                                uint16_t                 value)
{
    object_raw_data->part_C.message_counter_msg3 = value;
}

/**
 * @brief Set ifv object raw data count msg3
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value count msg3 value
 */
static inline void ifv_object_raw_data_set_count_msg3(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_C.count_msg3 = value;
}

/**
 * @brief Set ifv object raw data lat pos
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value lat pos value
 */
static inline void ifv_object_raw_data_set_lat_pos(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_C.lat_pos = value;
}

/**
 * @brief Set ifv object raw data lat vel
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value lat vel value
 */
static inline void ifv_object_raw_data_set_lat_vel(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_C.lat_vel = value;
}

/**
 * @brief Set ifv object raw data long pos
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value long pos value
 */
static inline void ifv_object_raw_data_set_long_pos(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_C.long_pos = value;
}

/**
 * @brief Set ifv object raw data long vel
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value long vel value
 */
static inline void ifv_object_raw_data_set_long_vel(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_C.long_vel = value;
}

/**
 * @brief Set ifv object raw data width
 *
 * @param object_raw_data Ifv object raw data pointer
 * @param value width value
 */
static inline void ifv_object_raw_data_set_width(struct IfvObjectRawData* object_raw_data, uint16_t value)
{
    object_raw_data->part_C.width = value;
}

/**
 * @brief Set ifv object list raw data vehicle speed
 *
 * @param raw_data ifv object list raw data pointer
 * @param value vehicle speed value
 */
static inline void ifv_object_list_raw_data_set_vehicle_speed(struct IfvObjectListRawData* raw_data, uint16_t value)
{
    raw_data->vehicle_speed = value;
}

/**
 * @brief Set ifv object list raw data object number
 *
 * @param raw_data ifv object list raw data pointer
 * @param value object number
 */
static inline void ifv_object_list_raw_data_set_obj_num(struct IfvObjectListRawData* raw_data, uint16_t value)
{
    raw_data->num = value;
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
 * @brief Get ifv object raw data timestamp
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return struct Timestamp* Timestamp pointer
 */
static inline struct Timestamp* ifv_object_raw_data_get_timestamp(struct IfvObjectRawData* object_raw_data)
{
    return &object_raw_data->timestamp;
}

/**
 * @brief Get ifv object raw data message counter msg1
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t message counter msg1
 */
static inline uint16_t ifv_object_raw_data_get_message_counter_msg1(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_A.message_counter_msg1;
}

/**
 * @brief Get ifv object raw data count msg1
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t count msg1
 */
static inline uint16_t ifv_object_raw_data_get_count_msg1(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_A.count_msg1;
}

/**
 * @brief Get ifv object raw data id
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t id
 */
static inline uint16_t ifv_object_raw_data_get_id(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_A.id;
}

/**
 * @brief Get ifv object raw data classification
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t classification
 */
static inline uint16_t ifv_object_raw_data_get_classification(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_A.classification;
}

/**
 * @brief Get ifv object raw data ped waise up
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t ped waise up
 */
static inline uint16_t ifv_object_raw_data_get_ped_waise_up(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_A.ped_waise_up;
}

/**
 * @brief Get ifv object raw data ped turn indicator
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t ped turn indicator
 */
static inline uint16_t ifv_object_raw_data_get_turn_indicator(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_A.turn_indicator;
}

/**
 * @brief Get ifv object raw data brake light indicator
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t brake light indicator
 */
static inline uint16_t ifv_object_raw_data_get_brake_light_indicator(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_A.brake_light_indicator;
}

/**
 * @brief Get ifv object raw data height
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t height
 */
static inline uint16_t ifv_object_raw_data_get_height(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_A.height;
}

/**
 * @brief Get ifv object raw data message counter msg2
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t message counter msg2
 */
static inline uint16_t ifv_object_raw_data_get_message_counter_msg2(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_B.message_counter_msg2;
}

/**
 * @brief Get ifv object raw data count msg2
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t count msg2
 */
static inline uint16_t ifv_object_raw_data_get_count_msg2(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_B.count_msg2;
}

/**
 * @brief Get ifv object raw data long accel
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t long accel
 */
static inline uint16_t ifv_object_raw_data_get_long_accel(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_B.long_accel;
}

/**
 * @brief Get ifv object raw data tcc const acc model
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t tcc const acc model
 */
static inline uint16_t ifv_object_raw_data_get_ttc_const_acc_model(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_B.ttc_const_acc_model;
}

/**
 * @brief Get ifv object raw data cut in cut out
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t cut in cut out
 */
static inline uint16_t ifv_object_raw_data_get_cut_in_cut_out(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_B.cut_in_cut_out;
}

/**
 * @brief Get ifv object raw data message counter msg3
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t message counter msg3
 */
static inline uint16_t ifv_object_raw_data_get_message_counter_msg3(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_C.message_counter_msg3;
}

/**
 * @brief Get ifv object raw data count msg3
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t count msg3
 */
static inline uint16_t ifv_object_raw_data_get_count_msg3(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_C.count_msg3;
}

/**
 * @brief Get ifv object raw data lat pos
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t lat pos
 */
static inline uint16_t ifv_object_raw_data_get_lat_pos(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_C.lat_pos;
}

/**
 * @brief Get ifv object raw data lat vel
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t lat vel
 */
static inline uint16_t ifv_object_raw_data_get_lat_vel(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_C.lat_vel;
}

/**
 * @brief Get ifv object raw data long pos
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t long pos
 */
static inline uint16_t ifv_object_raw_data_get_long_pos(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_C.long_pos;
}

/**
 * @brief Get ifv object raw data long vel
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t long vel
 */
static inline uint16_t ifv_object_raw_data_get_long_vel(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_C.long_vel;
}

/**
 * @brief Get ifv object raw data width
 *
 * @param object_raw_data Ifv object raw data pointer
 * @return uint16_t width
 */
static inline uint16_t ifv_object_raw_data_get_width(struct IfvObjectRawData* object_raw_data)
{
    return object_raw_data->part_C.width;
}

/**
 * @brief Get ifv object raw data vehicle speed
 *
 * @param IfvObjectRawData ifv object list raw data pointer
 * @return uint32_t vehicle speed
 */
static inline uint32_t ifv_object_list_raw_data_get_vehicle_speed(const struct IfvObjectListRawData* raw_data)
{
    return raw_data->vehicle_speed;
}

/**
 * @brief Get ifv object raw data object number
 *
 * @param object_raw_data ifv object list raw data pointer
 * @return uint32_t object number
 */
static inline uint32_t ifv_object_list_raw_data_get_obj_num(const struct IfvObjectListRawData* raw_data)
{
    return raw_data->num;
}

/**
 * @}
 * End Getter API group
 *
 */

/**
 * @brief Consturct ifv object raw data partA
 *
 * @param object_raw_data ifv object raw data pointer
 * @param msg ifv can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t ifv_object_raw_data_construct_partA(struct IfvObjectRawData* object_raw_data, const uint8_t* msg);

/**
 * @brief Consturct ifv object raw data partB
 *
 * @param object_raw_data ifv object raw data pointer
 * @param msg ifv can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t ifv_object_raw_data_construct_partB(struct IfvObjectRawData* object_raw_data, const uint8_t* msg);

/**
 * @brief Consturct ifv object raw data partC
 *
 * @param object_raw_data ifv object raw data pointer
 * @param msg ifv can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t ifv_object_raw_data_construct_partC(struct IfvObjectRawData* object_raw_data, const uint8_t* msg);

/**
 * @brief Get ifv object raw data serialized size
 *
 * @param raw_data ifv object raw data pointer
 * @return uint32_t serialized size
 */
uint32_t ifv_object_list_raw_data_get_serialized_size(const struct IfvObjectListRawData* raw_data);

/**
 * @brief Serialize ifv object raw data to buffer
 *
 * @param raw_data ifv object raw data pointer
 * @param buffer buffer to store serialized content
 * @param buffer_size buffer size
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return retcode_t Positive interger Number of bytes serialized into buffer
 */
retcode_t ifv_object_list_raw_data_serialize(const struct IfvObjectListRawData* raw_data, uint8_t* buffer,
                                             uint32_t buffer_size);

/**
 * @brief Deserialize ifv object raw data from buffer
 *
 * @param raw_data ifv object raw data pointer
 * @param buffer the buffer to deserialize from
 * @param buffer_size size of buffer
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed
 * @return retcode_t Positive integer Number of bytes deserialized from buffer
 */
retcode_t ifv_object_list_raw_data_deserialize(struct IfvObjectListRawData* raw_data, const uint8_t* buffer,
                                               uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
