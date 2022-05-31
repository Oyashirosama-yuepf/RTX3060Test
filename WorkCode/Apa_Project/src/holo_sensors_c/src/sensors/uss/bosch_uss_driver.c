/*!
 * @file bosch_uss_driver.c
 * @brief This source file defines bosch uss driver functions
 * @author liuya@holomatic.com
 * @date 2019-12-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <holo_c/sensors/dbc/bosch_uss_dbc.h>
#include <holo_c/sensors/uss/bosch_uss_driver.h>
#include <holo_c/utils/serialization.h>

retcode_t bosch_uss_object_list_set_timestamp(struct BoschUssObjectList* data, const struct Timestamp* timestamp)
{
    data->timestamp = *timestamp;

    return RC_SUCCESS;
}

retcode_t bosch_uss_object_list_set_object(struct BoschUssObjectList* data, const uint16_t object, const uint8_t index)
{
    data->object_list[index] = object;

    return RC_SUCCESS;
}

const struct Timestamp* bosch_uss_object_list_get_timestamp(struct BoschUssObjectList* data)
{
    return &data->timestamp;
}

uint16_t bosch_uss_object_list_get_object(struct BoschUssObjectList* data, uint8_t index)
{
    return data->object_list[index];
}

static retcode_t serialize_data(const struct BoschUssObjectList* data, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;
    uint8_t  i;

    serialized_size += timestamp_serialize(&data->timestamp, buffer + serialized_size, buffer_size - serialized_size);

    for (i = 0; i < OBJECT_LIST_NUM; i++)
    {
        serialized_size +=
            serialize_uint16(&data->object_list[i], buffer + serialized_size, buffer_size - serialized_size);
    }

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct BoschUssObjectList* data, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;
    uint8_t  i;

    deserialized_size +=
        timestamp_deserialize(&data->timestamp, buffer + deserialized_size, buffer_size - deserialized_size);

    for (i = 0; i < OBJECT_LIST_NUM; i++)
    {
        deserialized_size +=
            deserialize_uint16(&data->object_list[i], buffer + deserialized_size, buffer_size - deserialized_size);
    }

    return (retcode_t)deserialized_size;
}

uint32_t bosch_uss_object_list_get_serialized_size_4byte_aligned(const struct BoschUssObjectList* data)
{
    (void)data;

    return serialization_4byte_aligned_size(sizeof(struct BoschUssObjectList));
}

uint32_t bosch_uss_object_list_get_serialized_size_8byte_aligned(const struct BoschUssObjectList* data)
{
    (void)data;

    return serialization_8byte_aligned_size(sizeof(struct BoschUssObjectList));
}

uint32_t bosch_uss_object_list_get_serialized_size(const struct BoschUssObjectList* data)
{
    (void)data;

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return bosch_uss_object_list_get_serialized_size_4byte_aligned(data);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return bosch_uss_object_list_get_serialized_size_8byte_aligned(data);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t bosch_uss_object_list_serialize_4byte_aligned(const struct BoschUssObjectList* data, uint8_t* buffer,
                                                        uint32_t buffer_size)
{
    assert(data != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = bosch_uss_object_list_get_serialized_size_4byte_aligned(data);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(data, buffer, buffer_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

retcode_t bosch_uss_object_list_serialize_8byte_aligned(const struct BoschUssObjectList* data, uint8_t* buffer,
                                                        uint32_t buffer_size)
{
    assert(data != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = bosch_uss_object_list_get_serialized_size_8byte_aligned(data);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(data, buffer, buffer_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }
    return rc;
}

retcode_t bosch_uss_object_list_serialize(const struct BoschUssObjectList* data, uint8_t* buffer, uint32_t buffer_size)
{
    assert(data != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return bosch_uss_object_list_serialize_4byte_aligned(data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return bosch_uss_object_list_serialize_8byte_aligned(data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t bosch_uss_object_list_deserialize_4byte_aligned(struct BoschUssObjectList* data, const uint8_t* buffer,
                                                          uint32_t buffer_size)
{
    assert(data != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = bosch_uss_object_list_get_serialized_size_4byte_aligned(data);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(data, buffer, buffer_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

retcode_t bosch_uss_object_list_deserialize_8byte_aligned(struct BoschUssObjectList* data, const uint8_t* buffer,
                                                          uint32_t buffer_size)
{
    assert(data != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = bosch_uss_object_list_get_serialized_size_8byte_aligned(data);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(data, buffer, buffer_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

retcode_t bosch_uss_object_list_deserialize(struct BoschUssObjectList* data, const uint8_t* buffer,
                                            uint32_t buffer_size)
{
    assert(data != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return bosch_uss_object_list_deserialize_4byte_aligned(data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return bosch_uss_object_list_deserialize_8byte_aligned(data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t bosch_uss_can_id_is_valid(uint32_t id)
{
    retcode_t rc = RC_FAIL;

    if (id == ID_PAS_Olo_F_DE || id == ID_PAS_Olo_R_DE)
    {
        rc = RC_SUCCESS;
    }

    return rc;
}

retcode_t bosch_uss_driver_process_data(struct BoschUssObjectList* list, const struct Timestamp* timestamp, uint32_t id,
                                        const uint8_t* data, uint8_t len)
{
    (void)len;

    retcode_t      rc           = RC_FAIL;
    static uint8_t received_fde = 0;
    uint16_t       object       = 0;

    switch (id)
    {
        case ID_PAS_Olo_F_DE:
        {
            object = (CALC_PAS_Olo_F_DE_USS_DE_1(GET_PAS_Olo_F_DE_USS_DE_1(data), 1));
            bosch_uss_object_list_set_object(list, object, 0);

            object = (CALC_PAS_Olo_F_DE_USS_DE_2(GET_PAS_Olo_F_DE_USS_DE_2(data), 1));
            bosch_uss_object_list_set_object(list, object, 1);

            object = (CALC_PAS_Olo_F_DE_USS_DE_3(GET_PAS_Olo_F_DE_USS_DE_3(data), 1));
            bosch_uss_object_list_set_object(list, object, 2);

            object = (CALC_PAS_Olo_F_DE_USS_DE_4(GET_PAS_Olo_F_DE_USS_DE_4(data), 1));
            bosch_uss_object_list_set_object(list, object, 3);

            object = (CALC_PAS_Olo_F_DE_USS_DE_5(GET_PAS_Olo_F_DE_USS_DE_5(data), 1));
            bosch_uss_object_list_set_object(list, object, 4);

            object = (CALC_PAS_Olo_F_DE_USS_DE_6(GET_PAS_Olo_F_DE_USS_DE_6(data), 1));
            bosch_uss_object_list_set_object(list, object, 5);

            received_fde = 1;
            rc           = RC_BOSCH_USS_PARSE_CONTINUE;

            break;
        }

        case ID_PAS_Olo_R_DE:
        {
            if (received_fde == 1)
            {
                bosch_uss_object_list_set_timestamp(list, timestamp);

                object = (CALC_PAS_Olo_R_DE_USS_DE_7(GET_PAS_Olo_R_DE_USS_DE_7(data), 1));
                bosch_uss_object_list_set_object(list, object, 6);

                object = (CALC_PAS_Olo_R_DE_USS_DE_8(GET_PAS_Olo_R_DE_USS_DE_8(data), 1));
                bosch_uss_object_list_set_object(list, object, 7);

                object = (CALC_PAS_Olo_R_DE_USS_DE_9(GET_PAS_Olo_R_DE_USS_DE_9(data), 1));
                bosch_uss_object_list_set_object(list, object, 8);

                object = (CALC_PAS_Olo_R_DE_USS_DE_10(GET_PAS_Olo_R_DE_USS_DE_10(data), 1));
                bosch_uss_object_list_set_object(list, object, 9);

                object = (CALC_PAS_Olo_R_DE_USS_DE_11(GET_PAS_Olo_R_DE_USS_DE_11(data), 1));
                bosch_uss_object_list_set_object(list, object, 10);

                object = (CALC_PAS_Olo_R_DE_USS_DE_12(GET_PAS_Olo_R_DE_USS_DE_12(data), 1));
                bosch_uss_object_list_set_object(list, object, 11);

                received_fde = 0;

                rc = RC_BOSCH_USS_PARSE_OK;
            }
            else
            {
                rc = RC_BOSCH_USS_PARSE_ERROR;
            }

            break;
        }

        default:
            break;
    }

    return rc;
}
