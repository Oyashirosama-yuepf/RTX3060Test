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

#include <holo_c/sensors/mobileye/structure/mobileye_object.h>

retcode_t mobileye_object_raw_data_construct_part0(struct MobileyeObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_Objects0_Signals_Message_Part0_Objects_Angle_Left_Obj0(msg);
    mobileye_object_raw_data_set_angle_left(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part0_Objects_ID_Obj0(msg);
    mobileye_object_raw_data_set_id(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part0_Objects_Longitudial_Dist_Obj0(msg);
    mobileye_object_raw_data_set_longitudial_dist(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part0_Objects_Motion_Status_Obj0(msg);
    mobileye_object_raw_data_set_motion_status(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part0_Objects_Object_Class_Obj0(msg);
    mobileye_object_raw_data_set_object_class(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part0_Objects_Object_Index_Obj0(msg);
    mobileye_object_raw_data_set_object_index(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part0_Objects_Sync_Frame_Index_Obj0(msg);
    mobileye_object_raw_data_set_sync_frame_index(object_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mobileye_object_raw_data_construct_part1(struct MobileyeObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_Objects0_Signals_Message_Part1_Objects_Acceleration_Abs_Obj0(msg);
    mobileye_object_raw_data_set_acceleration_abs(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part1_Objects_Angle_Right_Obj0(msg);
    mobileye_object_raw_data_set_angle_right(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part1_Objects_LeftAnglePredicted_Obj0(msg);
    mobileye_object_raw_data_set_left_angle_predicted(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part1_Objects_Relative_Velocity_Obj0(msg);
    mobileye_object_raw_data_set_relative_velocity(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part1_Objects_RightAnglePredicted_Obj0(msg);
    mobileye_object_raw_data_set_right_angle_predicted(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part1_Objects_Width_Obj0(msg);
    mobileye_object_raw_data_set_width(object_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mobileye_object_raw_data_construct_part2(struct MobileyeObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_Objects0_Signals_Message_Part2_Objects_Angle_Rate_Mean_Obj0(msg);
    mobileye_object_raw_data_set_angle_rate_mean(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part2_Objects_Cut_In_Cut_Out_Obj0(msg);
    mobileye_object_raw_data_set_cut_in_cut_out(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part2_Objects_Extended_ID_Obj0(msg);
    mobileye_object_raw_data_set_extended_id(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part2_Objects_Lateral_Distance_Obj0(msg);
    mobileye_object_raw_data_set_lateral_distance(object_raw_data, raw_u32val);

    return RC_SUCCESS;
}

retcode_t mobileye_object_raw_data_construct_part3(struct MobileyeObjectRawData* object_raw_data, const uint8_t* msg)
{
    uint32_t raw_u32val;

    raw_u32val = GET_Objects0_Signals_Message_Part3_Objects_CIPVFlag_Obj0(msg);
    mobileye_object_raw_data_set_cipv_flag(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part3_Objects_Lateral_Velocity_Obj0(msg);
    mobileye_object_raw_data_set_lateral_velocity(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part3_Objects_Object_Age_Obj0(msg);
    mobileye_object_raw_data_set_object_age(object_raw_data, raw_u32val);

    raw_u32val = GET_Objects0_Signals_Message_Part3_Objects_ObstacleReplaced_Obj0(msg);
    mobileye_object_raw_data_set_obstacle_replaced(object_raw_data, raw_u32val);

    return RC_SUCCESS;
}

static retcode_t serialize_data(const struct MobileyeObjectRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size +=
        timestamp_serialize(&raw_data->timestamp, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->angle_left, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->motion_status, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->longitudial_dist, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->id, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->object_class, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->object_index, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->sync_frame_index, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->width, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->relative_velocity, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->right_angle_predicted, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->left_angle_predicted, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->acceleration_abs, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->angle_right, buffer + serialized_size,buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->lateral_distance, buffer + serialized_size,buffer_size - serialized_size);
    serialized_size += 
		serialize_uint16(&raw_data->extended_id, buffer + serialized_size,buffer_size - serialized_size);
	serialized_size += 
		serialize_uint16(&raw_data->angle_rate_mean, buffer + serialized_size,buffer_size - serialized_size);
	serialized_size += 
		serialize_uint16(&raw_data->cut_in_cut_out, buffer + serialized_size,buffer_size - serialized_size);
	serialized_size += 
		serialize_uint16(&raw_data->object_age, buffer + serialized_size,buffer_size - serialized_size);
	serialized_size += 
		serialize_uint16(&raw_data->lateral_velocity, buffer + serialized_size,buffer_size - serialized_size);
	serialized_size += 
		serialize_uint16(&raw_data->obstacle_replaced, buffer + serialized_size,buffer_size - serialized_size);
	serialized_size += 
		serialize_uint16(&raw_data->cipv_flag, buffer + serialized_size,buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct MobileyeObjectRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size +=
        timestamp_deserialize(&raw_data->timestamp, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_left, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->motion_status, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->longitudial_dist, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->id, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->object_class, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->object_index, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->sync_frame_index, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->width, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->relative_velocity, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->right_angle_predicted, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->left_angle_predicted, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->acceleration_abs, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->angle_right, buffer + deserialized_size,buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->lateral_distance, buffer + deserialized_size,buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->extended_id, buffer + deserialized_size,buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->angle_rate_mean, buffer + deserialized_size,buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->cut_in_cut_out, buffer + deserialized_size,buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->object_age, buffer + deserialized_size,buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->lateral_velocity, buffer + deserialized_size,buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->obstacle_replaced, buffer + deserialized_size,buffer_size - deserialized_size);
    deserialized_size += 
		deserialize_uint16(&raw_data->cipv_flag, buffer + deserialized_size,buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

uint32_t mobileye_object_list_raw_data_get_serialized_size_4byte_aligned(const struct MobileyeObjectListRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return serialization_4byte_aligned_size(sizeof(uint32_t) + raw_data->num * sizeof(struct MobileyeObjectRawData));
}

uint32_t mobileye_object_list_raw_data_get_serialized_size_8byte_aligned(const struct MobileyeObjectListRawData* raw_data)
{
    (void)raw_data;
    assert(raw_data != NULL);

    return serialization_8byte_aligned_size(sizeof(uint32_t) + raw_data->num * sizeof(struct MobileyeObjectRawData));
}

uint32_t mobileye_object_list_raw_data_get_serialized_size(const struct MobileyeObjectListRawData* raw_data)
{
    (void)raw_data;

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mobileye_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mobileye_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t mobileye_object_list_raw_data_serialize_4byte_aligned(const struct MobileyeObjectListRawData* raw_data, uint8_t* buffer,
                                                           uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint32_t  i;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = mobileye_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);
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

retcode_t mobileye_object_list_raw_data_serialize_8byte_aligned(const struct MobileyeObjectListRawData* raw_data, uint8_t* buffer,
                                                           uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    uint32_t i;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = mobileye_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);
    uint32_t  object_num      = raw_data->num;
    retcode_t rc              = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += 
			serialize_uint32(&raw_data->num, buffer + serialized_size, buffer_size - serialized_size);

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

retcode_t mobileye_object_list_raw_data_serialize(const struct MobileyeObjectListRawData* raw_data, uint8_t* buffer,
                                             uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mobileye_object_list_raw_data_serialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mobileye_object_list_raw_data_serialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t mobileye_object_list_raw_data_deserialize_4byte_aligned(struct MobileyeObjectListRawData* raw_data,
                                                             const uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t i;
    uint32_t deserialized_size = 0;
    uint32_t expected_size     = mobileye_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);
    uint32_t object_num;

    retcode_t rc = RC_SUCCESS;

    deserialized_size +=
        deserialize_uint32(&raw_data->num, buffer + deserialized_size, buffer_size - deserialized_size);
    expected_size = mobileye_object_list_raw_data_get_serialized_size_4byte_aligned(raw_data);

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

retcode_t mobileye_object_list_raw_data_deserialize_8byte_aligned(struct MobileyeObjectListRawData* raw_data,
                                                             const uint8_t* buffer, uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

    uint32_t i;
    uint32_t deserialized_size = 0;
    uint32_t expected_size     = mobileye_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);
    uint32_t object_num;

    retcode_t rc = RC_SUCCESS;

    deserialized_size +=
        deserialize_uint32(&raw_data->num, buffer + deserialized_size, buffer_size - deserialized_size);
    expected_size = mobileye_object_list_raw_data_get_serialized_size_8byte_aligned(raw_data);

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

retcode_t mobileye_object_list_raw_data_deserialize(struct MobileyeObjectListRawData* raw_data, const uint8_t* buffer,
                                               uint32_t buffer_size)
{
    assert(buffer != NULL);
    assert(raw_data != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return mobileye_object_list_raw_data_deserialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return mobileye_object_list_raw_data_deserialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}
