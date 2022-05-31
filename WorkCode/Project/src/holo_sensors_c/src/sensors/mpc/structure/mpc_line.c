/*!
 * @file mpc_line.c
 * @brief This source file implements mpc line raw data operation functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>

#include <holo_c/sensors/mpc/structure/mpc_line.h>

retcode_t mpc_line_raw_data_construct_partA(struct MpcLineRawData* line_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_BV1_Lin_01_A_BV_Linie_01_dx_Beginn(msg);
    mpc_line_raw_data_set_dx_begin(line_raw_data, raw_u32val);

    raw_u32val = GET_BV1_Lin_01_A_BV_Linie_01_dx_Vorausschau(msg);
    mpc_line_raw_data_set_dx_end(line_raw_data, raw_u32val);

    raw_u32val = GET_BV1_Lin_01_A_BV_Linie_01_dy(msg);
    mpc_line_raw_data_set_dy(line_raw_data, raw_u32val);

    raw_u32val = GET_BV1_Lin_01_A_BV_Linie_01_Existenzmass(msg);
    mpc_line_raw_data_set_confidence(line_raw_data, raw_u32val);

    raw_u32val = GET_BV1_Lin_01_A_BV_Linie_01_Gierw_diff(msg);
    mpc_line_raw_data_set_angle_diff(line_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mpc_line_raw_data_construct_partB(struct MpcLineRawData* line_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_BV1_Lin_01_B_BV_Linie_01_hor_Kruemmung(msg);
    mpc_line_raw_data_set_horizon_curve(line_raw_data, raw_u32val);

    raw_u32val = GET_BV1_Lin_01_B_BV_Linie_01_Linienbreite(msg);
    mpc_line_raw_data_set_width(line_raw_data, raw_u32val);

    raw_u32val = GET_BV1_Lin_01_B_BV_Linie_01_Liniennummer(msg);
    mpc_line_raw_data_set_id(line_raw_data, raw_u32val);

    raw_u32val = GET_BV1_Lin_01_B_BV_Linie_01_Typ(msg);
    mpc_line_raw_data_set_type(line_raw_data, raw_u32val);

    raw_u32val = GET_BV1_Lin_01_B_BV_Linie_01_Farbe(msg);
    mpc_line_raw_data_set_color(line_raw_data, raw_u32val);

    return RC_SUCCESS;
}

static retcode_t serialize_data(const struct MpcLineRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size +=
        timestamp_serialize(&raw_data->timestamp, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->confidence, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->id, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->type, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->width, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->color, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->dx_begin, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->dx_end, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->dy, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->angle_diff, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->horizon_curve, buffer + serialized_size, buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct MpcLineRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size +=
        timestamp_deserialize(&raw_data->timestamp, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->confidence, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->id, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->type, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->width, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->color, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->dx_begin, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->dx_end, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->dy, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_diff, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->horizon_curve, buffer + deserialized_size, buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

uint32_t mpc_lines_raw_data_get_serialized_size_4byte_aligned(const struct MpcLinesRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return 4 * serialization_4byte_aligned_size(sizeof(struct MpcLineRawData));
}

uint32_t mpc_lines_raw_data_get_serialized_size_8byte_aligned(const struct MpcLinesRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return 4 * serialization_8byte_aligned_size(sizeof(struct MpcLineRawData));
}

uint32_t mpc_lines_raw_data_get_serialized_size(const struct MpcLinesRawData* raw_data)
{
    (void)raw_data;

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mpc_lines_raw_data_get_serialized_size_4byte_aligned(raw_data);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mpc_lines_raw_data_get_serialized_size_8byte_aligned(raw_data);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t mpc_lines_raw_data_serialize_4byte_aligned(const struct MpcLinesRawData* raw_data, uint8_t* buffer,
                                                     uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = mpc_lines_raw_data_get_serialized_size_4byte_aligned(raw_data);
    retcode_t rc              = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size +=
            serialize_data(&raw_data->left_left_line, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->left_line, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->right_line, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->right_right_line, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t mpc_lines_raw_data_serialize_8byte_aligned(const struct MpcLinesRawData* raw_data, uint8_t* buffer,
                                                     uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = mpc_lines_raw_data_get_serialized_size_8byte_aligned(raw_data);
    retcode_t rc              = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size +=
            serialize_data(&raw_data->left_left_line, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->left_line, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->right_line, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->right_right_line, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t mpc_lines_raw_data_serialize(const struct MpcLinesRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mpc_lines_raw_data_serialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mpc_lines_raw_data_serialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t mpc_lines_raw_data_deserialize_4byte_aligned(struct MpcLinesRawData* raw_data, const uint8_t* buffer,
                                                       uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = mpc_lines_raw_data_get_serialized_size_4byte_aligned(raw_data);
    retcode_t rc                = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size +=
            deserialize_data(&raw_data->left_left_line, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->left_line, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->right_line, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->right_right_line, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);

        assert(expected_size == deserialized_size);

        rc = deserialized_size;
    }

    return rc;
}

retcode_t mpc_lines_raw_data_deserialize_8byte_aligned(struct MpcLinesRawData* raw_data, const uint8_t* buffer,
                                                       uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = mpc_lines_raw_data_get_serialized_size_8byte_aligned(raw_data);
    retcode_t rc                = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size +=
            deserialize_data(&raw_data->left_left_line, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->left_line, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->right_line, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->right_right_line, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);

        assert(expected_size == deserialized_size);

        rc = deserialized_size;
    }

    return rc;
}

retcode_t mpc_lines_raw_data_deserialize(struct MpcLinesRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mpc_lines_raw_data_deserialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mpc_lines_raw_data_deserialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}
