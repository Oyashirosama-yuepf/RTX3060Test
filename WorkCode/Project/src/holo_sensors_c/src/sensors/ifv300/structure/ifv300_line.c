/*!
 * @file ifv300_line.c
 * @brief This source file implements ifv line raw data operation functions
 * @author liuya@holomatic.com
 * @date 2020-04-15
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <holo_c/sensors/dbc/ifv300_output_dbc.h>
#include <holo_c/sensors/dbc/ifv300_input_dbc.h>
#include <holo_c/sensors/ifv300/structure/ifv300_line.h>
#include <stdio.h>

retcode_t ifv_lines_raw_data_construct_info_head(struct IfvLineInfoHead* raw_data, const uint8_t* msg)
{
    uint16_t raw_value;

    raw_value = GET_VIS_LANE_INFORMATION_VIS_LANE_LANE_CHANGE(msg);
    ifv_line_info_head_raw_data_set_lane_change(raw_data, raw_value);

    raw_value = GET_VIS_LANE_INFORMATION_VIS_LANE_LEFT_NEIGHBOR_TYPE(msg);
    ifv_line_info_head_raw_data_set_left_left_type(raw_data, raw_value);

    raw_value = GET_VIS_LANE_INFORMATION_VIS_LANE_LEFT_INDIVID_TYPE(msg);
    ifv_line_info_head_raw_data_set_left_type(raw_data, raw_value);

    raw_value = GET_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_NEIGHBOR_TYPE(msg);
    ifv_line_info_head_raw_data_set_right_right_type(raw_data, raw_value);

    raw_value = GET_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_INDIVID_TYPE(msg);
    ifv_line_info_head_raw_data_set_right_type(raw_data, raw_value);

    raw_value = GET_VIS_LANE_INFORMATION_VIS_LANE_LEFT_NEIGHBOR_LKACONF(msg);
    ifv_line_info_head_raw_data_set_left_left_lkaconf(raw_data, raw_value);

    raw_value = GET_VIS_LANE_INFORMATION_VIS_LANE_LEFT_INDIVID_LKACONF(msg);
    ifv_line_info_head_raw_data_set_left_lkaconf(raw_data, raw_value);

    raw_value = GET_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_NEIGHBOR_LKACONF(msg);
    ifv_line_info_head_raw_data_set_right_right_lkaconf(raw_data, raw_value);

    raw_value = GET_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_INDIVID_LKACONF(msg);
    ifv_line_info_head_raw_data_set_right_lkaconf(raw_data, raw_value);

    return RC_SUCCESS;
}

retcode_t ifv_lines_raw_data_construct_info_curve(struct IfvLineInfoCurve* raw_data, const uint8_t* msg)
{
    uint16_t raw_value;

    raw_value = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_IN_MARKER_COLOR(msg);
    ifv_line_info_curve_raw_data_set_mark_color(raw_data, raw_value);

    raw_value = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A0(msg);
    ifv_line_info_curve_raw_data_set_a0(raw_data, raw_value);

    raw_value = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A1(msg);
    ifv_line_info_curve_raw_data_set_a1(raw_data, raw_value);

    raw_value = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A2(msg);
    ifv_line_info_curve_raw_data_set_a2(raw_data, raw_value);

    raw_value = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A3(msg);
    ifv_line_info_curve_raw_data_set_a3(raw_data, raw_value);

    raw_value = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_RANGE(msg);
    ifv_line_info_curve_raw_data_set_range(raw_data, raw_value);

    return RC_SUCCESS;
}

static retcode_t serialize_data(const struct IfvLinesRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size +=
        timestamp_serialize(&raw_data->timestamp, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size +=
        serialize_uint16(&raw_data->line_head.lane_change, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->line_head.left_left_type, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->line_head.left_type, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->line_head.right_right_type, buffer + serialized_size,
                                        buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->line_head.right_type, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->line_head.left_left_lkaconf, buffer + serialized_size,
                                        buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->line_head.left_lkaconf, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->line_head.right_right_lkaconf, buffer + serialized_size,
                                        buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->line_head.right_lkaconf, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size +=
        serialize_uint16(&raw_data->left_left.mark_color, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->left_left.a0, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->left_left.a1, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->left_left.a2, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->left_left.a3, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->left_left.range, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size +=
        serialize_uint16(&raw_data->left.mark_color, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->left.a0, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->left.a1, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->left.a2, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->left.a3, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->left.range, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size +=
        serialize_uint16(&raw_data->right.mark_color, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->right.a0, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->right.a1, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->right.a2, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->right.a3, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->right.range, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size +=
        serialize_uint16(&raw_data->right_right.mark_color, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->right_right.a0, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->right_right.a1, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->right_right.a2, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->right_right.a3, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->right_right.range, buffer + serialized_size, buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct IfvLinesRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size +=
        timestamp_deserialize(&raw_data->timestamp, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size += deserialize_uint16(&raw_data->line_head.lane_change, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->line_head.left_left_type, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->line_head.left_type, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->line_head.right_right_type, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->line_head.right_type, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->line_head.left_left_lkaconf, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->line_head.left_lkaconf, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->line_head.right_right_lkaconf, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->line_head.right_lkaconf, buffer + deserialized_size,
                                            buffer_size - deserialized_size);

    deserialized_size += deserialize_uint16(&raw_data->left_left.mark_color, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left_left.a0, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left_left.a1, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left_left.a2, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left_left.a3, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left_left.range, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size +=
        deserialize_uint16(&raw_data->left.mark_color, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left.a0, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left.a1, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left.a2, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left.a3, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left.range, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size +=
        deserialize_uint16(&raw_data->right.mark_color, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right.a0, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right.a1, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right.a2, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right.a3, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right.range, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size += deserialize_uint16(&raw_data->right_right.mark_color, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right_right.a0, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right_right.a1, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right_right.a2, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right_right.a3, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right_right.range, buffer + deserialized_size, buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

uint32_t ifv_lines_raw_data_get_serialized_size(const struct IfvLinesRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return (33 * sizeof(uint16_t) + sizeof(struct Timestamp));
}

retcode_t ifv_lines_raw_data_serialize(const struct IfvLinesRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = ifv_lines_raw_data_get_serialized_size(raw_data);
    retcode_t rc              = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(raw_data, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }

    return rc;
}
retcode_t ifv_lines_raw_data_deserialize(struct IfvLinesRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = ifv_lines_raw_data_get_serialized_size(raw_data);
    retcode_t rc                = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(raw_data, buffer + deserialized_size, buffer_size - deserialized_size);

        assert(expected_size == deserialized_size);

        rc = deserialized_size;
    }

    return rc;
}
