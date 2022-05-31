/*!
 * @file mpc_object.c
 * @brief This source file implements mpc object raw data operation functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <stdio.h>

#include <holo_c/sensors/mpc/structure/mpc_object.h>

retcode_t mpc_object_raw_data_construct_partA(struct MpcObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_BV_Obj_01_A_BV1_Obj_01_LongitudinalDist(msg);
    mpc_object_raw_data_set_lon_dist(object_raw_data, raw_u32val);

    raw_u32val = GET_BV_Obj_01_A_BV1_Obj_01_WnklMitte(msg);
    mpc_object_raw_data_set_angle_center(object_raw_data, raw_u32val);

    raw_u32val = GET_BV_Obj_01_A_BV1_Obj_01_Klasse(msg);
    mpc_object_raw_data_set_classification(object_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mpc_object_raw_data_construct_partB(struct MpcObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_BV_Obj_01_B_BV1_Obj_01_WnklBreite(msg);
    mpc_object_raw_data_set_angle_width(object_raw_data, raw_u32val);

    raw_u32val = GET_BV_Obj_01_B_BV1_Obj_01_ExistenzMass(msg);
    mpc_object_raw_data_set_confidence(object_raw_data, raw_u32val);

    raw_u32val = GET_BV_Obj_01_B_BV1_Obj_01_WnklGeschw(msg);
    mpc_object_raw_data_set_angle_speed(object_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mpc_object_raw_data_construct_partC(struct MpcObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_BV_Obj_01_C_BV1_Obj_01_InvTTCBildeb(msg);
    mpc_object_raw_data_set_inv_ttc(object_raw_data, raw_u32val);

    raw_u32val = GET_BV_Obj_01_C_BV1_Obj_01_UeberdWnklEgoSpurR(msg);
    mpc_object_raw_data_set_angle_overlap_egolane_right(object_raw_data, raw_u32val);

    raw_u32val = GET_BV_Obj_01_C_BV1_Obj_01_UeberdWnklEgoSpurL(msg);
    mpc_object_raw_data_set_angle_overlap_egolane_left(object_raw_data, raw_u32val);

    raw_u32val = GET_BV_Obj_01_C_BV1_Obj_01_Alter(msg);
    mpc_object_raw_data_set_age(object_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mpc_object_raw_data_construct_partD(struct MpcObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_BV_Obj_01_D_BV_Objekt_01_phi_right(msg);
    mpc_object_raw_data_set_angle_edge_right(object_raw_data, raw_u32val);

    raw_u32val = GET_BV_Obj_01_D_BV_Objekt_01_phi_left(msg);
    mpc_object_raw_data_set_angle_edge_left(object_raw_data, raw_u32val);

    raw_u32val = GET_BV_Obj_01_D_BV1_Obj_01_ID(msg);
    mpc_object_raw_data_set_id(object_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mpc_object_raw_data_construct_partE(struct MpcObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_BV_Obj_01_E_BV1_Obj_01_RadialGeschw(msg);
    mpc_object_raw_data_set_lon_velocity(object_raw_data, raw_u32val);

    return RC_SUCCESS;
}

static retcode_t serialize_data(const struct MpcObjectRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size +=
        timestamp_serialize(&raw_data->timestamp, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size += serialize_uint16(&raw_data->confidence, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->id, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->classification, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->age, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->inv_ttc, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->lon_dist, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->lon_velocity, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->angle_center, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->angle_width, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->angle_speed, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->angle_edge_left, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->angle_edge_right, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->angle_overlap_egolane_right, buffer + serialized_size,
                                        buffer_size - serialized_size);
    serialized_size += serialize_uint16(&raw_data->angle_overlap_egolane_left, buffer + serialized_size,
                                        buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct MpcObjectRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size +=
        timestamp_deserialize(&raw_data->timestamp, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->confidence, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->id, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->classification, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->age, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->inv_ttc, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->lon_dist, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->lon_velocity, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_center, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_width, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_speed, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_edge_left, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_edge_right, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->angle_overlap_egolane_right, buffer + deserialized_size,
                                            buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16(&raw_data->angle_overlap_egolane_left, buffer + deserialized_size,
                                            buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

uint32_t mpc_object_list_raw_data_get_serialized_size_4byte_aligned(const struct MpcObjectListRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return serialization_4byte_aligned_size(sizeof(uint32_t) + raw_data->num * sizeof(struct MpcObjectRawData));
}

uint32_t mpc_object_list_raw_data_get_serialized_size_8byte_aligned(const struct MpcObjectListRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return serialization_8byte_aligned_size(sizeof(uint32_t) + raw_data->num * sizeof(struct MpcObjectRawData));
}

uint32_t mpc_object_list_raw_data_get_serialized_size(const struct MpcObjectListRawData* raw_data)
{
    (void)raw_data;

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mpc_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mpc_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t mpc_object_list_raw_data_serialize_4byte_aligned(const struct MpcObjectListRawData* raw_data, uint8_t* buffer,
                                                           uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint8_t   i;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = mpc_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);
    uint32_t  object_num      = raw_data->num;
    retcode_t rc              = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_uint32(&raw_data->num, buffer + serialized_size, buffer_size - serialized_size);

        for (i = 0; i < object_num; i++)
        {
            serialized_size +=
                serialize_data(&raw_data->object[i], buffer + serialized_size, buffer_size - serialized_size);
        }

        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t mpc_object_list_raw_data_serialize_8byte_aligned(const struct MpcObjectListRawData* raw_data, uint8_t* buffer,
                                                           uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint8_t   i;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = mpc_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);
    uint32_t  object_num      = raw_data->num;
    retcode_t rc              = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_uint32(&raw_data->num, buffer + serialized_size, buffer_size - serialized_size);

        for (i = 0; i < object_num; i++)
        {
            serialized_size +=
                serialize_data(&raw_data->object[i], buffer + serialized_size, buffer_size - serialized_size);
        }

        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t mpc_object_list_raw_data_serialize(const struct MpcObjectListRawData* raw_data, uint8_t* buffer,
                                             uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mpc_object_list_raw_data_serialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mpc_object_list_raw_data_serialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t mpc_object_list_raw_data_deserialize_4byte_aligned(struct MpcObjectListRawData* raw_data,
                                                             const uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint8_t  i;
    uint32_t deserialized_size = 0;
    uint32_t expected_size     = mpc_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);
    uint32_t object_num;

    retcode_t rc = RC_SUCCESS;

    deserialized_size +=
        deserialize_uint32(&raw_data->num, buffer + deserialized_size, buffer_size - deserialized_size);
    expected_size = mpc_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);

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

        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);

        rc = (retcode_t)deserialized_size;
    }

    return rc;
}

retcode_t mpc_object_list_raw_data_deserialize_8byte_aligned(struct MpcObjectListRawData* raw_data,
                                                             const uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint8_t  i;
    uint32_t deserialized_size = 0;
    uint32_t expected_size     = mpc_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);
    uint32_t object_num;

    retcode_t rc = RC_SUCCESS;

    deserialized_size +=
        deserialize_uint32(&raw_data->num, buffer + deserialized_size, buffer_size - deserialized_size);
    expected_size = mpc_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);

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

        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);

        rc = (retcode_t)deserialized_size;
    }

    return rc;
}

retcode_t mpc_object_list_raw_data_deserialize(struct MpcObjectListRawData* raw_data, const uint8_t* buffer,
                                               uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mpc_object_list_raw_data_deserialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mpc_object_list_raw_data_deserialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}
