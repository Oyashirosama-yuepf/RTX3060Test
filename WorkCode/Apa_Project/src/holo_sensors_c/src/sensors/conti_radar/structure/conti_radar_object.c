/*!
 * @file conti_radar_object.c
 * @brief This source file implements conti radar object raw data operation functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <holo_c/sensors/dbc/conti_radar_dbc.h>
#include <holo_c/sensors/conti_radar/structure/conti_radar_object.h>
#include <holo_c/utils/serialization.h>

void conti_radar_object_raw_data_construct_part1(struct ContiRadarObjectRawData* raw_data, const uint8_t* msg)
{
    uint16_t raw_value;

    raw_value = GET_Object_1_General_Object_ID(msg);
    conti_radar_object_raw_data_set_id(raw_data, raw_value);

    raw_value = GET_Object_1_General_Object_DistLong(msg);
    conti_radar_object_raw_data_set_dist_lon(raw_data, raw_value);

    raw_value = GET_Object_1_General_Object_DistLat(msg);
    conti_radar_object_raw_data_set_dist_lat(raw_data, raw_value);

    raw_value = GET_Object_1_General_Object_VrelLong(msg);
    conti_radar_object_raw_data_set_vrel_lon(raw_data, raw_value);

    raw_value = GET_Object_1_General_Object_VrelLat(msg);
    conti_radar_object_raw_data_set_vrel_lat(raw_data, raw_value);

    raw_value = GET_Object_1_General_Object_DynProp(msg);
    conti_radar_object_raw_data_set_dyn_prop(raw_data, raw_value);

    raw_value = GET_Object_1_General_Object_RCS(msg);
    conti_radar_object_raw_data_set_rcs(raw_data, raw_value);
}

void conti_radar_object_raw_data_construct_part2(struct ContiRadarObjectRawData* raw_data, const uint8_t* msg)
{
    uint16_t raw_value;

    raw_value = GET_Object_2_Quality_Object_DistLong_rms(msg);
    conti_radar_object_raw_data_set_dist_lon_rms(raw_data, raw_value);

    raw_value = GET_Object_2_Quality_Object_DistLat_rms(msg);
    conti_radar_object_raw_data_set_dist_lat_rms(raw_data, raw_value);

    raw_value = GET_Object_2_Quality_Object_VrelLong_rms(msg);
    conti_radar_object_raw_data_set_vrel_lon_rms(raw_data, raw_value);

    raw_value = GET_Object_2_Quality_Object_VrelLat_rms(msg);
    conti_radar_object_raw_data_set_vrel_lat_rms(raw_data, raw_value);

    raw_value = GET_Object_2_Quality_Object_ArelLong_rms(msg);
    conti_radar_object_raw_data_set_arel_lon_rms(raw_data, raw_value);

    raw_value = GET_Object_2_Quality_Object_ArelLat_rms(msg);
    conti_radar_object_raw_data_set_arel_lat_rms(raw_data, raw_value);

    raw_value = GET_Object_2_Quality_Object_Orientation_rms(msg);
    conti_radar_object_raw_data_set_orientation_angle_rms(raw_data, raw_value);

    raw_value = GET_Object_2_Quality_Object_MeasState(msg);
    conti_radar_object_raw_data_set_meas_state(raw_data, raw_value);

    raw_value = GET_Object_2_Quality_Object_ProbOfexist(msg);
    conti_radar_object_raw_data_set_prob_of_exist(raw_data, raw_value);
}

void conti_radar_object_raw_data_construct_part3(struct ContiRadarObjectRawData* raw_data, const uint8_t* msg)
{
    uint16_t raw_value;

    raw_value = GET_Object_3_Extended_Object_ArelLong(msg);
    conti_radar_object_raw_data_set_arel_lon(raw_data, raw_value);

    raw_value = GET_Object_3_Extended_Object_ArelLat(msg);
    conti_radar_object_raw_data_set_arel_lat(raw_data, raw_value);

    raw_value = GET_Object_3_Extended_Object_Class(msg);
    conti_radar_object_raw_data_set_classification(raw_data, raw_value);

    raw_value = GET_Object_3_Extended_Object_OrientationAngle(msg);
    conti_radar_object_raw_data_set_orientation_angle(raw_data, raw_value);

    raw_value = GET_Object_3_Extended_Object_Length(msg);
    conti_radar_object_raw_data_set_length(raw_data, raw_value);

    raw_value = GET_Object_3_Extended_Object_Width(msg);
    conti_radar_object_raw_data_set_width(raw_data, raw_value);
}

static retcode_t serialize_data(const struct ContiRadarObjectRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size +=
        timestamp_serialize(&raw_data->timestamp, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->id, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->classification, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->meas_state, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->prob_of_exist, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->rcs, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->length, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->width, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->dyn_prop, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->dist_lon, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->dist_lat, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->vrel_lon, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->vrel_lat, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->arel_lon, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->arel_lat, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->orientation_angle, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->dist_lon_rms, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->dist_lat_rms, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->vrel_lon_rms, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->vrel_lat_rms, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->arel_lon_rms, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->arel_lat_rms, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->orientation_angle_rms, buffer + serialized_size, buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct ContiRadarObjectRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size +=
        timestamp_deserialize(&raw_data->timestamp, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size += deserialize_uint16(&raw_data->id, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->classification, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->meas_state, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->prob_of_exist, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->rcs, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->length, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->width, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->dyn_prop, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->dist_lon, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->dist_lat, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->vrel_lon, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->vrel_lat, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->arel_lon, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->arel_lat, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->orientation_angle, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->dist_lon_rms, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->dist_lat_rms, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->vrel_lon_rms, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->vrel_lat_rms, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->arel_lon_rms, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->arel_lat_rms, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->orientation_angle_rms, buffer + deserialized_size,
                                            buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

uint32_t
conti_radar_object_list_raw_data_get_serialized_size_4byte_aligned(const struct ContiRadarObjectListRawData* raw_data)
{
    assert(raw_data != NULL);

    return serialization_4byte_aligned_size(sizeof(uint32_t) + raw_data->num * sizeof(struct ContiRadarObjectRawData));
}

uint32_t
conti_radar_object_list_raw_data_get_serialized_size_8byte_aligned(const struct ContiRadarObjectListRawData* raw_data)
{
    assert(raw_data != NULL);

    return serialization_8byte_aligned_size(sizeof(uint32_t) + raw_data->num * sizeof(struct ContiRadarObjectRawData));
}

uint32_t conti_radar_object_list_raw_data_get_serialized_size(const struct ContiRadarObjectListRawData* raw_data)
{
    (void)raw_data;

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return conti_radar_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return conti_radar_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

int32_t conti_radar_object_list_raw_data_serialize_4byte_aligned(const struct ContiRadarObjectListRawData* raw_data,
                                                                 uint8_t* buffer, uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint32_t expected_size   = conti_radar_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);
    uint32_t serialized_size = 0;
    uint8_t  i;

    retcode_t rc = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_uint32(&raw_data->num, buffer + serialized_size, buffer_size - serialized_size);

        for (i = 0; i < raw_data->num; i++)
        {
            serialized_size +=
                serialize_data(&raw_data->objects[i], buffer + serialized_size, buffer_size - serialized_size);
        }

        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

int32_t conti_radar_object_list_raw_data_serialize_8byte_aligned(const struct ContiRadarObjectListRawData* raw_data,
                                                                 uint8_t* buffer, uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint32_t expected_size   = conti_radar_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);
    uint32_t serialized_size = 0;
    uint8_t  i;

    retcode_t rc = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_uint32(&raw_data->num, buffer + serialized_size, buffer_size - serialized_size);

        for (i = 0; i < raw_data->num; i++)
        {
            serialized_size +=
                serialize_data(&raw_data->objects[i], buffer + serialized_size, buffer_size - serialized_size);
        }

        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

int32_t conti_radar_object_list_raw_data_serialize(const struct ContiRadarObjectListRawData* raw_data, uint8_t* buffer,
                                                   uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return conti_radar_object_list_raw_data_serialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return conti_radar_object_list_raw_data_serialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

int32_t conti_radar_object_list_raw_data_deserialize_4byte_aligned(struct ContiRadarObjectListRawData* raw_data,
                                                                   const uint8_t* buffer, uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint32_t expected_size     = conti_radar_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);
    uint32_t deserialized_size = 0;
    uint8_t  i;

    retcode_t rc = RC_SUCCESS;

    deserialized_size +=
        deserialize_uint32(&raw_data->num, buffer + deserialized_size, buffer_size - deserialized_size);

    expected_size = conti_radar_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        for (i = 0; i < raw_data->num; i++)
        {
            deserialized_size +=
                deserialize_data(&raw_data->objects[i], buffer + deserialized_size, buffer_size - deserialized_size);
        }

        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);

        assert(expected_size == deserialized_size);

        rc = (retcode_t)deserialized_size;
    }

    return rc;
}

int32_t conti_radar_object_list_raw_data_deserialize_8byte_aligned(struct ContiRadarObjectListRawData* raw_data,
                                                                   const uint8_t* buffer, uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint32_t expected_size     = conti_radar_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);
    uint32_t deserialized_size = 0;
    uint8_t  i;

    retcode_t rc = RC_SUCCESS;

    deserialized_size +=
        deserialize_uint32(&raw_data->num, buffer + deserialized_size, buffer_size - deserialized_size);

    expected_size = conti_radar_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        for (i = 0; i < raw_data->num; i++)
        {
            deserialized_size +=
                deserialize_data(&raw_data->objects[i], buffer + deserialized_size, buffer_size - deserialized_size);
        }

        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);

        assert(expected_size == deserialized_size);

        rc = (retcode_t)deserialized_size;
    }

    return rc;
}

int32_t conti_radar_object_list_raw_data_deserialize(struct ContiRadarObjectListRawData* raw_data,
                                                     const uint8_t* buffer, uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return conti_radar_object_list_raw_data_deserialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return conti_radar_object_list_raw_data_deserialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}
