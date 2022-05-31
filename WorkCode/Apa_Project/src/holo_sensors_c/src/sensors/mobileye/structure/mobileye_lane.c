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

#include <holo_c/sensors/mobileye/structure/mobileye_lane.h>

retcode_t mobileye_lane_raw_data_construct_part0(struct MobileyeLaneRawData* lane_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_Lane0_Signals_Message_Part0_Lane0_Lane_Index(msg);
    mobileye_lane_raw_data_set_lane_index(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part0_Lane0_Lane_Location_Type(msg);
    mobileye_lane_raw_data_set_location_type(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Quality(msg);
    mobileye_lane_raw_data_set_mark_quality(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Type(msg);
    mobileye_lane_raw_data_set_mark_type(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Width(msg);
    mobileye_lane_raw_data_set_mark_width(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part0_Lane0_Lane_View_Range_Start(msg);
    mobileye_lane_raw_data_set_range_start(lane_raw_data, raw_u32val);

	raw_u32val = GET_Lane0_Signals_Message_Part0_Lane0_Sync_Frame_Index(msg);
    mobileye_lane_raw_data_set_frame_index(lane_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mobileye_lane_raw_data_construct_part1(struct MobileyeLaneRawData* lane_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_Lane0_Signals_Message_Part1_Lane0_C0_Lane_Position(msg);
    mobileye_lane_raw_data_set_c0(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part1_Lane0_C1_Heading_Angle(msg);
    mobileye_lane_raw_data_set_c1(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part1_Lane0_C2_Lane_Curvature(msg);
    mobileye_lane_raw_data_set_c2(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part1_Lane0_Lane_View_Range_End(msg);
    mobileye_lane_raw_data_set_range_end(lane_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mobileye_lane_raw_data_construct_part2(struct MobileyeLaneRawData* lane_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_Lane0_Signals_Message_Part2_Lane0_C3_Lane_Curvature_Driv(msg);
    mobileye_lane_raw_data_set_c3(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part2_Lane0_Crossing(msg);
    mobileye_lane_raw_data_set_crossing(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part2_Lane0_Lane_Mark_Color(msg);
    mobileye_lane_raw_data_set_mark_color(lane_raw_data, raw_u32val);

    raw_u32val = GET_Lane0_Signals_Message_Part2_Lane0_TLC(msg);
    mobileye_lane_raw_data_set_tlc(lane_raw_data, raw_u32val);

    return RC_SUCCESS;
}

static retcode_t serialize_data(const struct MobileyeLaneRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size += timestamp_serialize(&raw_data->timestamp, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->range_start, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->mark_width, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->mark_quality, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->mark_type, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->location_type, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->lane_index, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->frame_index, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->c2, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->range_end, buffer + serialized_size, buffer_size - serialized_size);
	serialized_size += serialize_uint16(&raw_data->c1, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->c0, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->mark_color, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->c3, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->crossing, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->tlc, buffer + serialized_size, buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct MobileyeLaneRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size += timestamp_deserialize(&raw_data->timestamp, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->range_start, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->mark_width, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->mark_quality, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->mark_type, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->location_type, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->lane_index, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->frame_index, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->c2, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->range_end, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->c1, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->c0, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->mark_color, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->c3, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->crossing, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->tlc, buffer + deserialized_size, buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

uint32_t mobileye_lanes_raw_data_get_serialized_size_4byte_aligned(const struct MobileyeLanesRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return 4 * serialization_4byte_aligned_size(sizeof(struct MobileyeLaneRawData));
}

uint32_t mobileye_lanes_raw_data_get_serialized_size_8byte_aligned(const struct MobileyeLanesRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return 4 * serialization_8byte_aligned_size(sizeof(struct MobileyeLaneRawData));
}

uint32_t mobileye_lanes_raw_data_get_serialized_size(const struct MobileyeLanesRawData* raw_data)
{
    (void)raw_data;

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mobileye_lanes_raw_data_get_serialized_size_4byte_aligned(raw_data);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mobileye_lanes_raw_data_get_serialized_size_8byte_aligned(raw_data);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t mobileye_lanes_raw_data_serialize_4byte_aligned(const struct MobileyeLanesRawData* raw_data, uint8_t* buffer,
                                                     uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = mobileye_lanes_raw_data_get_serialized_size_4byte_aligned(raw_data);
    retcode_t rc              = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size +=
            serialize_data(&raw_data->line0, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->line1, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->line2, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->line3, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t mobileye_lanes_raw_data_serialize_8byte_aligned(const struct MobileyeLanesRawData* raw_data, uint8_t* buffer,
                                                     uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = mobileye_lanes_raw_data_get_serialized_size_8byte_aligned(raw_data);
    retcode_t rc              = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size +=
            serialize_data(&raw_data->line0, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->line1, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->line2, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_data(&raw_data->line3, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t mobileye_lanes_raw_data_serialize(const struct MobileyeLanesRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mobileye_lanes_raw_data_serialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mobileye_lanes_raw_data_serialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t mobileye_lanes_raw_data_deserialize_4byte_aligned(struct MobileyeLanesRawData* raw_data, const uint8_t* buffer,
                                                       uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = mobileye_lanes_raw_data_get_serialized_size_4byte_aligned(raw_data);
    retcode_t rc                = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size +=
            deserialize_data(&raw_data->line0, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->line1, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->line2, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->line3, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);

        assert(expected_size == deserialized_size);

        rc = deserialized_size;
    }

    return rc;
}

retcode_t mobileye_lanes_raw_data_deserialize_8byte_aligned(struct MobileyeLanesRawData* raw_data, const uint8_t* buffer,
                                                       uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = mobileye_lanes_raw_data_get_serialized_size_8byte_aligned(raw_data);
    retcode_t rc                = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size +=
            deserialize_data(&raw_data->line0, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->line1, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->line2, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_data(&raw_data->line3, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);

        assert(expected_size == deserialized_size);

        rc = deserialized_size;
    }

    return rc;
}

retcode_t mobileye_lanes_raw_data_deserialize(struct MobileyeLanesRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mobileye_lanes_raw_data_deserialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mobileye_lanes_raw_data_deserialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}
