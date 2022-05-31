/*!
 * @file ifv_object.c
 * @brief This source file implements ifv object raw data operation functions
 * @author liuya@holomatic.com
 * @date 2020-04-15
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <holo_c/core/retcode.h>
#include <holo_c/sensors/dbc/ifv300_output_dbc.h>
#include <holo_c/sensors/dbc/ifv300_input_dbc.h>
#include <holo_c/sensors/ifv300/structure/ifv300_object.h>
#include <stdio.h>

retcode_t ifv_object_raw_data_construct_partA(struct IfvObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint16_t raw_value;

    raw_value = GET_VIS_OBS_MSG_1_VIS_OBS_MESSAGE_COUNTER_MSG1(msg);
    ifv_object_raw_data_set_message_counter_msg1(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_1_VIS_OBS_COUNT_MSG1(msg);
    ifv_object_raw_data_set_count_msg1(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_1_VIS_OBS_ID_01(msg);
    ifv_object_raw_data_set_id(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_1_VIS_OBS_CLASSIFICATION_01(msg);
    ifv_object_raw_data_set_classification(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_1_VIS_OBS_PED_WAIST_UP_01(msg);
    ifv_object_raw_data_set_ped_waise_up(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_1_VIS_OBS_TURN_INDICATOR_01(msg);
    ifv_object_raw_data_set_turn_indicator(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_1_VIS_OBS_BRAKE_LIGHT_INDIC_01(msg);
    ifv_object_raw_data_set_brake_light_indicator(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_1_VIS_OBS_HEIGHT_01(msg);
    ifv_object_raw_data_set_height(object_raw_data, raw_value);

    return RC_SUCCESS;
}

retcode_t ifv_object_raw_data_construct_partB(struct IfvObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint16_t raw_value;

    raw_value = GET_VIS_OBS_MSG_2_VIS_OBS_MESSAGE_COUNTER_MSG2(msg);
    ifv_object_raw_data_set_message_counter_msg2(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_2_VIS_OBS_COUNT_MSG2(msg);
    ifv_object_raw_data_set_count_msg2(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_2_VIS_OBS_LONG_ACCEL_01(msg);
    ifv_object_raw_data_set_long_accel(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_2_VIS_OBS_TTC_CONST_ACC_MODEL_01(msg);
    ifv_object_raw_data_set_ttc_const_acc_model(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_2_VIS_OBS_CUT_IN_OUT_01(msg);
    ifv_object_raw_data_set_cut_in_cut_out(object_raw_data, raw_value);

    return RC_SUCCESS;
}

retcode_t ifv_object_raw_data_construct_partC(struct IfvObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint16_t raw_value;

    raw_value = GET_VIS_OBS_MSG_3_VIS_OBS_MESSAGE_COUNTER_MSG3(msg);
    ifv_object_raw_data_set_message_counter_msg3(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_3_VIS_OBS_COUNT_MSG3(msg);
    ifv_object_raw_data_set_count_msg3(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_3_VIS_OBS_LAT_POS_01(msg);
    ifv_object_raw_data_set_lat_pos(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_3_VIS_OBS_LAT_VEL_01(msg);
    ifv_object_raw_data_set_lat_vel(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_3_VIS_OBS_LONG_POS_01(msg);
    ifv_object_raw_data_set_long_pos(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_3_VIS_OBS_LONG_VEL_01(msg);
    ifv_object_raw_data_set_long_vel(object_raw_data, raw_value);

    raw_value = GET_VIS_OBS_MSG_3_VIS_OBS_WIDTH_01(msg);
    ifv_object_raw_data_set_width(object_raw_data, raw_value);

    return RC_SUCCESS;
}

static retcode_t serialize_data(const struct IfvObjectRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size +=
        timestamp_serialize(&raw_data->timestamp, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size += serialize_uint16(&raw_data->part_A.message_counter_msg1, buffer + serialized_size,
                                        buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_A.count_msg1, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->part_A.id, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_A.classification, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_A.ped_waise_up, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_A.turn_indicator, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->part_A.brake_light_indicator, buffer + serialized_size,
                                        buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_A.height, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size += serialize_uint16(&raw_data->part_B.message_counter_msg2, buffer + serialized_size,
                                        buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_B.count_msg2, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_B.long_accel, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->part_B.ttc_const_acc_model, buffer + serialized_size,
                                        buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_B.cut_in_cut_out, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size += serialize_uint16(&raw_data->part_C.message_counter_msg3, buffer + serialized_size,
                                        buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_C.count_msg3, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_C.lat_pos, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_C.lat_vel, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_C.long_pos, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_C.long_vel, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->part_C.width, buffer + serialized_size, buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct IfvObjectRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size +=
        timestamp_deserialize(&raw_data->timestamp, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size += deserialize_uint16(&raw_data->part_A.message_counter_msg1, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_A.count_msg1, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_A.id, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->part_A.classification, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_A.ped_waise_up, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->part_A.turn_indicator, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->part_A.brake_light_indicator, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_A.height, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size += deserialize_uint16(&raw_data->part_B.message_counter_msg2, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_B.count_msg2, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_B.long_accel, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->part_B.ttc_const_acc_model, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->part_B.cut_in_cut_out, buffer + deserialized_size,
                                            buffer_size - deserialized_size);

    deserialized_size += deserialize_uint16(&raw_data->part_C.message_counter_msg3, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_C.count_msg3, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_C.lat_pos, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_C.lat_vel, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_C.long_pos, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_C.long_vel, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->part_C.width, buffer + deserialized_size, buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

static uint32_t get_data_serialized_size(const struct IfvObjectRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return (20 * sizeof(uint16_t) + sizeof(struct Timestamp));
}

uint32_t ifv_object_list_raw_data_get_serialized_size(const struct IfvObjectListRawData* raw_data)
{
    assert(raw_data != NULL);

    return (raw_data->num * get_data_serialized_size(&raw_data->object[0]) + 2 * sizeof(uint32_t));
}

retcode_t ifv_object_list_raw_data_serialize(const struct IfvObjectListRawData* raw_data, uint8_t* buffer,
                                             uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint8_t   i;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = ifv_object_list_raw_data_get_serialized_size(raw_data);
    uint32_t  object_num      = raw_data->num;
    retcode_t rc              = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size +=
            serialize_uint32(&raw_data->vehicle_speed, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_uint32(&raw_data->num, buffer + serialized_size, buffer_size - serialized_size);

        for (i = 0; i < object_num; i++)
        {
            serialized_size +=
                serialize_data(&raw_data->object[i], buffer + serialized_size, buffer_size - serialized_size);
        }

        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t ifv_object_list_raw_data_deserialize(struct IfvObjectListRawData* raw_data, const uint8_t* buffer,
                                               uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint8_t  i;
    uint32_t deserialized_size = 0;
    uint32_t expected_size     = 0;
    uint32_t object_num;

    retcode_t rc = RC_SUCCESS;

    deserialized_size +=
        deserialize_uint32(&raw_data->vehicle_speed, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size +=
        deserialize_uint32(&raw_data->num, buffer + deserialized_size, buffer_size - deserialized_size);
    expected_size = ifv_object_list_raw_data_get_serialized_size(raw_data);

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        object_num = raw_data->num;
        for (i = 0; i < object_num; i++)
        {
            deserialized_size +=
                deserialize_data(&raw_data->object[i], buffer + deserialized_size, buffer_size - deserialized_size);
        }

        rc = (retcode_t)deserialized_size;
    }

    return rc;
}
