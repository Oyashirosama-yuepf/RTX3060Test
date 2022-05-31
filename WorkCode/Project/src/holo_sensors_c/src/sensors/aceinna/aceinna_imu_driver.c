/*!
 * @file aceinna_imu_driver.c
 * @brief This source file implements aceinna imu sensor driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <math.h>
#include <string.h>

#include <holo_c/sensors/dbc/aceinna_imu_dbc.h>
#include <holo_c/sensors/aceinna/aceinna_imu_driver.h>
#include <holo_c/utils/serialization.h>

retcode_t aceinna_imu_raw_data_to_imuf(struct Imuf* imu, struct AceinnaImuRawData* raw_data)
{
    assert(imu != NULL);
    assert(raw_data != NULL);

    float32_t      raw_sigval_float;
    float32_t      linear_acc_buf[VECTORF_MIN_BUF_SIZE(3)], angle_rate_buf[VECTORF_MIN_BUF_SIZE(3)];
    struct Vectorf linear_acc, angle_rate;

    vectorf_init(&linear_acc, 3, linear_acc_buf, VECTORF_MIN_BUF_SIZE(3));
    vectorf_init(&angle_rate, 3, angle_rate_buf, VECTORF_MIN_BUF_SIZE(3));

    imuf_init(imu);
    imuf_set_timestamp(imu, &raw_data->timestamp);
    /* @BUG */
    /* @TODO maybe imu coord cannot be hard code to body in future */
    Coordinate_t coordinate = coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER);
    imuf_set_coordinate(imu, coordinate);

    raw_sigval_float = CALC_Aceinna_Accel_Aceinna_AccX(aceinna_imu_raw_data_get_acc_x(raw_data), 1.0);
    vectorf_set(&linear_acc, 0, raw_sigval_float);

    raw_sigval_float = CALC_Aceinna_Accel_Aceinna_AccY(aceinna_imu_raw_data_get_acc_y(raw_data), -1.0);
    vectorf_set(&linear_acc, 1, raw_sigval_float);

    raw_sigval_float = CALC_Aceinna_Accel_Aceinna_AccZ(aceinna_imu_raw_data_get_acc_z(raw_data), -1.0);
    vectorf_set(&linear_acc, 2, raw_sigval_float);

    imuf_set_linear_acceleration(imu, &linear_acc);

    raw_sigval_float = CALC_Aceinna_AngleRate_Aceinna_GyroX(aceinna_imu_raw_data_get_gyroscope_x(raw_data), 1.0);
    raw_sigval_float = raw_sigval_float / 180.0f * M_PI;
    vectorf_set(&angle_rate, 0, raw_sigval_float);

    raw_sigval_float = CALC_Aceinna_AngleRate_Aceinna_GyroY(aceinna_imu_raw_data_get_gyroscope_y(raw_data), -1.0);
    raw_sigval_float = raw_sigval_float / 180.0f * M_PI;
    vectorf_set(&angle_rate, 1, raw_sigval_float);

    raw_sigval_float = CALC_Aceinna_AngleRate_Aceinna_GyroZ(aceinna_imu_raw_data_get_gyroscope_z(raw_data), -1.0);
    raw_sigval_float = raw_sigval_float / 180.0f * M_PI;
    vectorf_set(&angle_rate, 2, raw_sigval_float);

    imuf_set_angular_velocity(imu, &angle_rate);

    imuf_set_status(imu, IMU_STATUS_ALLGOOD);

    return RC_SUCCESS;
}

retcode_t aceinna_imu_raw_data_set_timestamp(struct AceinnaImuRawData* raw_data, const struct Timestamp* timestamp)
{
    assert(raw_data != NULL);
    assert(timestamp != NULL);

    raw_data->timestamp = *timestamp;

    return RC_SUCCESS;
}

const struct Timestamp* aceinna_imu_raw_data_get_timestamp(struct AceinnaImuRawData* raw_data)
{
    assert(raw_data != NULL);

    return &raw_data->timestamp;
}

retcode_t aceinna_imu_raw_data_set_acc_x(struct AceinnaImuRawData* raw_data, uint16_t acc_x)
{
    assert(raw_data != NULL);

    raw_data->linear_acc_x = acc_x;

    return RC_SUCCESS;
}

uint16_t aceinna_imu_raw_data_get_acc_x(struct AceinnaImuRawData* raw_data)
{
    assert(raw_data != NULL);

    return raw_data->linear_acc_x;
}

retcode_t aceinna_imu_raw_data_set_acc_y(struct AceinnaImuRawData* raw_data, uint16_t acc_y)
{
    assert(raw_data != NULL);

    raw_data->linear_acc_y = acc_y;

    return RC_SUCCESS;
}

uint16_t aceinna_imu_raw_data_get_acc_y(struct AceinnaImuRawData* raw_data)
{
    assert(raw_data != NULL);

    return raw_data->linear_acc_y;
}

retcode_t aceinna_imu_raw_data_set_acc_z(struct AceinnaImuRawData* raw_data, uint16_t acc_z)
{
    assert(raw_data != NULL);

    raw_data->linear_acc_z = acc_z;

    return RC_SUCCESS;
}

uint16_t aceinna_imu_raw_data_get_acc_z(struct AceinnaImuRawData* raw_data)
{
    assert(raw_data != NULL);

    return raw_data->linear_acc_z;
}

retcode_t aceinna_imu_raw_data_set_gyroscope_x(struct AceinnaImuRawData* raw_data, uint16_t gyroscope_x)
{
    assert(raw_data != NULL);

    raw_data->angle_rate_x = gyroscope_x;

    return RC_SUCCESS;
}

uint16_t aceinna_imu_raw_data_get_gyroscope_x(struct AceinnaImuRawData* raw_data)
{
    assert(raw_data != NULL);

    return raw_data->angle_rate_x;
}

retcode_t aceinna_imu_raw_data_set_gyroscope_y(struct AceinnaImuRawData* raw_data, uint16_t gyroscope_y)
{
    assert(raw_data != NULL);

    raw_data->angle_rate_y = gyroscope_y;

    return RC_SUCCESS;
}

uint16_t aceinna_imu_raw_data_get_gyroscope_y(struct AceinnaImuRawData* raw_data)
{
    assert(raw_data != NULL);

    return raw_data->angle_rate_y;
}

retcode_t aceinna_imu_raw_data_set_gyroscope_z(struct AceinnaImuRawData* raw_data, uint16_t gyroscope_z)
{
    assert(raw_data != NULL);

    raw_data->angle_rate_z = gyroscope_z;

    return RC_SUCCESS;
}

uint16_t aceinna_imu_raw_data_get_gyroscope_z(struct AceinnaImuRawData* raw_data)
{
    assert(raw_data != NULL);

    return raw_data->angle_rate_z;
}

/**
 * @brief Init aceinna imu raw data
 *
 * @param raw_data Imu raw data pointer
 * @return retcode_t RC_SUCCESS
 */
static retcode_t aceinna_imu_raw_data_init(struct AceinnaImuRawData* raw_data)
{
    assert(raw_data != NULL);

    timestamp_init(&raw_data->timestamp);
    aceinna_imu_raw_data_set_acc_x(raw_data, 0);
    aceinna_imu_raw_data_set_acc_y(raw_data, 0);
    aceinna_imu_raw_data_set_acc_z(raw_data, 0);
    aceinna_imu_raw_data_set_gyroscope_x(raw_data, 0);
    aceinna_imu_raw_data_set_gyroscope_y(raw_data, 0);
    aceinna_imu_raw_data_set_gyroscope_z(raw_data, 0);

    return RC_SUCCESS;
}

static retcode_t aceinna_imu_driver_set_parse_state(struct AceinnaImuDriver* driver, enum AceinnaImuParseState state)
{
    assert(driver != NULL);

    driver->parse_state = state;

    return RC_SUCCESS;
}

retcode_t aceinna_imu_driver_init(struct AceinnaImuDriver* driver)
{
    assert(driver != NULL);

    aceinna_imu_driver_set_parse_state(driver, ACEINNA_IMU_PARSE_IDLE);
    aceinna_imu_raw_data_init(&driver->imu_raw_data);

    return RC_SUCCESS;
}

retcode_t aceinna_imu_driver_process_data(struct AceinnaImuDriver* driver, const struct Timestamp* timestamp,
                                          uint32_t id, const uint8_t* data, uint8_t len)
{
    assert(driver != NULL);
    assert(data != NULL);

    retcode_t rc = RC_FAIL;

    uint32_t raw_sigval_int;

    while (len)
    {
        switch (driver->parse_state)
        {
            case ACEINNA_IMU_PARSE_IDLE:
                if (id == ID_Aceinna_Accel)
                {
                    driver->parse_state = ACEINNA_IMU_PARSE_LINEAR_ACC;
                }
                else if (id == ID_Aceinna_AngleRate)
                {
                    driver->parse_state = ACEINNA_IMU_PARSE_ERROR;
                }
                else
                {
                    len -= len;
                    rc = RC_PARSE_ACEINNA_IMU_ID_ERROR;
                }

                break;

            case ACEINNA_IMU_PARSE_LINEAR_ACC:
                if (id == ID_Aceinna_Accel)
                {
                    aceinna_imu_raw_data_set_timestamp(&driver->imu_raw_data, timestamp);

                    raw_sigval_int = GET_Aceinna_Accel_Aceinna_AccX(data);
                    aceinna_imu_raw_data_set_acc_x(&driver->imu_raw_data, raw_sigval_int);

                    raw_sigval_int = GET_Aceinna_Accel_Aceinna_AccY(data);
                    aceinna_imu_raw_data_set_acc_y(&driver->imu_raw_data, raw_sigval_int);

                    raw_sigval_int = GET_Aceinna_Accel_Aceinna_AccZ(data);
                    aceinna_imu_raw_data_set_acc_z(&driver->imu_raw_data, raw_sigval_int);

                    driver->parse_state = ACEINNA_IMU_PARSE_GYROSCOPE;
                    len -= len;
                    rc = RC_PARSE_ACEINNA_IMU_CONTINUE;
                }
                else
                {
                    driver->parse_state = ACEINNA_IMU_PARSE_ERROR;
                }

                break;

            case ACEINNA_IMU_PARSE_GYROSCOPE:
                if (id == ID_Aceinna_AngleRate)
                {
                    raw_sigval_int = GET_Aceinna_AngleRate_Aceinna_GyroX(data);
                    aceinna_imu_raw_data_set_gyroscope_x(&driver->imu_raw_data, raw_sigval_int);

                    raw_sigval_int = GET_Aceinna_AngleRate_Aceinna_GyroY(data);
                    aceinna_imu_raw_data_set_gyroscope_y(&driver->imu_raw_data, raw_sigval_int);

                    raw_sigval_int = GET_Aceinna_AngleRate_Aceinna_GyroZ(data);
                    aceinna_imu_raw_data_set_gyroscope_z(&driver->imu_raw_data, raw_sigval_int);

                    driver->parse_state = ACEINNA_IMU_PARSE_IDLE;
                    len -= len;
                    rc = RC_SUCCESS;
                }
                else
                {
                    driver->parse_state = ACEINNA_IMU_PARSE_ERROR;
                }

                break;

            case ACEINNA_IMU_PARSE_ERROR:
            default:
                driver->parse_state = ACEINNA_IMU_PARSE_IDLE;
                len -= len;
                rc = RC_PARSE_ACEINNA_IMU_DATA_ERROR;
                break;
        }
    }

    return rc;
}

static retcode_t serialize_data(const struct AceinnaImuRawData* raw_data, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size +=
        timestamp_serialize(&raw_data->timestamp, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->linear_acc_x, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->linear_acc_y, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->linear_acc_z, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->angle_rate_x, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->angle_rate_y, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint16(&raw_data->angle_rate_z, buffer + serialized_size, buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct AceinnaImuRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size +=
        timestamp_deserialize(&raw_data->timestamp, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->linear_acc_x, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->linear_acc_y, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->linear_acc_z, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_rate_x, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_rate_y, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_uint16(&raw_data->angle_rate_z, buffer + deserialized_size, buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

uint32_t aceinna_imu_raw_data_get_serialized_size_4byte_aligned(const struct AceinnaImuRawData* raw_data)
{
    (void)raw_data;
    return serialization_4byte_aligned_size(sizeof(struct AceinnaImuRawData));
}

uint32_t aceinna_imu_raw_data_get_serialized_size_8byte_aligned(const struct AceinnaImuRawData* raw_data)
{
    (void)raw_data;
    return serialization_8byte_aligned_size(sizeof(struct AceinnaImuRawData));
}

uint32_t aceinna_imu_raw_data_get_serialized_size(const struct AceinnaImuRawData* raw_data)
{
    (void)raw_data;

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return aceinna_imu_raw_data_get_serialized_size_4byte_aligned(raw_data);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return aceinna_imu_raw_data_get_serialized_size_8byte_aligned(raw_data);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t aceinna_imu_raw_data_serialize_4byte_aligned(const struct AceinnaImuRawData* raw_data, uint8_t* buffer,
                                                       uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = aceinna_imu_raw_data_get_serialized_size_4byte_aligned(raw_data);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(raw_data, buffer, buffer_size);
        serialized_size +=
            serialize_padding_4byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

retcode_t aceinna_imu_raw_data_serialize_8byte_aligned(const struct AceinnaImuRawData* raw_data, uint8_t* buffer,
                                                       uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = aceinna_imu_raw_data_get_serialized_size_8byte_aligned(raw_data);
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(raw_data, buffer, buffer_size);
        serialized_size +=
            serialize_padding_8byte_aligned(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);

        rc = (retcode_t)serialized_size;
    }
    return rc;
}

retcode_t aceinna_imu_raw_data_serialize(const struct AceinnaImuRawData* raw_data, uint8_t* buffer,
                                         uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return aceinna_imu_raw_data_serialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return aceinna_imu_raw_data_serialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

retcode_t aceinna_imu_raw_data_deserialize_4byte_aligned(struct AceinnaImuRawData* raw_data, const uint8_t* buffer,
                                                         uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = aceinna_imu_raw_data_get_serialized_size_4byte_aligned(raw_data);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(raw_data, buffer, buffer_size);
        deserialized_size += deserialize_padding_4byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

retcode_t aceinna_imu_raw_data_deserialize_8byte_aligned(struct AceinnaImuRawData* raw_data, const uint8_t* buffer,
                                                         uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = aceinna_imu_raw_data_get_serialized_size_8byte_aligned(raw_data);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(raw_data, buffer, buffer_size);
        deserialized_size += deserialize_padding_8byte_aligned(deserialized_size, buffer + deserialized_size,
                                                               buffer_size - deserialized_size);
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

retcode_t aceinna_imu_raw_data_deserialize(struct AceinnaImuRawData* raw_data, const uint8_t* buffer,
                                           uint32_t buffer_size)
{
    assert(raw_data != NULL);
    assert(buffer != NULL);

#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return aceinna_imu_raw_data_deserialize_4byte_aligned(raw_data, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return aceinna_imu_raw_data_deserialize_8byte_aligned(raw_data, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}
