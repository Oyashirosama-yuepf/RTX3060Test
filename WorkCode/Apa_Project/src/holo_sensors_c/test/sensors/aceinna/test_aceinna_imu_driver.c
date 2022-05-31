/*!
 * @brief Unit test for aceinna imu driver.
 * @author liuya@holomaitc.com
 * @date 2019-9-25
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <time.h>
#include <unity.h>

#include <holo_c/sensors/dbc/aceinna_imu_dbc.h>
#include <holo_c/sensors/aceinna/aceinna_imu_driver.h>
#include <holo_c/utils/serialization.h>

static struct AceinnaImuDriver driver;
static float32_t               linear_acc_buf[VECTORF_MIN_BUF_SIZE(3)], angle_rate_buf[VECTORF_MIN_BUF_SIZE(3)];
struct Vectorf                 linear_acc;
struct Vectorf                 angle_rate;
struct Imuf                    aceinna_imu;

static void init_global_variables(void)
{
    vectorf_init(&linear_acc, 3, linear_acc_buf, VECTORF_MIN_BUF_SIZE(3));
    vectorf_init(&angle_rate, 3, angle_rate_buf, VECTORF_MIN_BUF_SIZE(3));
}

static void test_aceinna_imu_driver_init(void)
{
    struct Timestamp sys_time;

    TEST_ASSERT_EQUAL(RC_SUCCESS, aceinna_imu_driver_init(&driver));

    timestamp_init_from_timestamp(&sys_time, aceinna_imu_raw_data_get_timestamp(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_INT64(0, timestamp_get_sec(&sys_time));

    TEST_ASSERT_EQUAL_HEX16(0, aceinna_imu_raw_data_get_acc_x(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0, aceinna_imu_raw_data_get_acc_y(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0, aceinna_imu_raw_data_get_acc_z(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0, aceinna_imu_raw_data_get_gyroscope_x(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0, aceinna_imu_raw_data_get_gyroscope_y(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0, aceinna_imu_raw_data_get_gyroscope_z(&driver.imu_raw_data));
}

static void test_aceinna_imu_process_data(void)
{
    uint32_t         msg_id;
    uint8_t          data[8];
    uint8_t          len;
    time_t           utc_seconds;
    struct Timestamp time_stamp;
    struct Timestamp raw_data_timestamp;

    utc_seconds = time((time_t*)NULL);

    msg_id  = ID_Aceinna_Accel;
    data[0] = 0x78;
    data[1] = 0x7D;
    data[2] = 0x32;
    data[3] = 0x7D;
    data[4] = 0x46;
    data[5] = 0x7D;
    data[6] = 0x00;
    data[7] = 0x00;
    len     = 8;
    timestamp_init_from_sec(&time_stamp, utc_seconds);
    TEST_ASSERT_EQUAL(RC_PARSE_ACEINNA_IMU_CONTINUE,
                      aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));

    msg_id  = ID_Aceinna_AngleRate;
    data[0] = 0x00;
    data[1] = 0x8C;
    data[2] = 0x00;
    data[3] = 0x9B;
    data[4] = 0x00;
    data[5] = 0xAA;
    data[6] = 0x00;
    data[7] = 0x00;
    len     = 8;
    TEST_ASSERT_EQUAL(RC_SUCCESS, aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));
    TEST_ASSERT_EQUAL(RC_SUCCESS, aceinna_imu_raw_data_to_imuf(&aceinna_imu, &driver.imu_raw_data));

    vectorf_set_from_vectorf(&linear_acc, imuf_get_linear_acceleration(&aceinna_imu));
    vectorf_set_from_vectorf(&angle_rate, imuf_get_angular_velocity(&aceinna_imu));
    for (uint8_t i = 0; i < 3; i++)
    {
        vectorf_get(&linear_acc, i, &linear_acc_buf[i]);
        vectorf_get(&angle_rate, i, &angle_rate_buf[i]);
    }
    TEST_ASSERT_EQUAL_FLOAT(1.2, linear_acc_buf[0]);
    TEST_ASSERT_EQUAL_FLOAT(-0.5, linear_acc_buf[1]);
    TEST_ASSERT_EQUAL_FLOAT(-0.7, linear_acc_buf[2]);

    TEST_ASSERT_EQUAL_FLOAT(0.5235988, angle_rate_buf[0]);
    TEST_ASSERT_EQUAL_FLOAT(-1.0471976, angle_rate_buf[1]);
    TEST_ASSERT_EQUAL_FLOAT(-1.5707964, angle_rate_buf[2]);

    timestamp_init_from_timestamp(&time_stamp, imuf_get_timestamp(&aceinna_imu));
    TEST_ASSERT_EQUAL_INT64(utc_seconds, timestamp_get_sec(&time_stamp));
    TEST_ASSERT_EQUAL_HEX32(coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER), 
                            imuf_get_coordinate(&aceinna_imu));
    TEST_ASSERT_EQUAL_HEX8(IMU_STATUS_ALLGOOD, imuf_get_status(&aceinna_imu));

    timestamp_init_from_timestamp(&raw_data_timestamp, aceinna_imu_raw_data_get_timestamp(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_INT64(utc_seconds, timestamp_get_sec(&raw_data_timestamp));

    TEST_ASSERT_EQUAL_HEX16(0x7D78, aceinna_imu_raw_data_get_acc_x(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0x7D32, aceinna_imu_raw_data_get_acc_y(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0x7D46, aceinna_imu_raw_data_get_acc_z(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0x8C00, aceinna_imu_raw_data_get_gyroscope_x(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0x9B00, aceinna_imu_raw_data_get_gyroscope_y(&driver.imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(0xAA00, aceinna_imu_raw_data_get_gyroscope_z(&driver.imu_raw_data));
}

void test_aceinna_imu_serialize_and_deserialize_4byte_aligend(void)
{
    const uint8_t            buf_size       = 20;
    const uint8_t            error_buf_size = 10;
    uint8_t                  buffer[20];
    struct AceinnaImuRawData imu_raw_data;

    TEST_ASSERT_EQUAL_UINT64(buf_size, aceinna_imu_raw_data_get_serialized_size_4byte_aligned(&imu_raw_data));

    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW, aceinna_imu_raw_data_serialize_4byte_aligned(
                                                                   &driver.imu_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(buf_size,
                             aceinna_imu_raw_data_serialize_4byte_aligned(&driver.imu_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             aceinna_imu_raw_data_deserialize_4byte_aligned(&imu_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(buf_size, aceinna_imu_raw_data_deserialize_4byte_aligned(&imu_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_HEX64(driver.imu_raw_data.timestamp.nsec, imu_raw_data.timestamp.nsec);

    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_acc_x(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_acc_x(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_acc_y(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_acc_y(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_acc_z(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_acc_z(&imu_raw_data));

    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_gyroscope_x(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_gyroscope_x(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_gyroscope_y(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_gyroscope_y(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_gyroscope_z(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_gyroscope_z(&imu_raw_data));
}

void test_aceinna_imu_serialize_and_deserialize_8byte_aligend(void)
{
    const uint8_t            buf_size       = 24;
    const uint8_t            error_buf_size = 10;
    uint8_t                  buffer[24];
    struct AceinnaImuRawData imu_raw_data;

    TEST_ASSERT_EQUAL_UINT64(buf_size, aceinna_imu_raw_data_get_serialized_size_8byte_aligned(&imu_raw_data));

    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW, aceinna_imu_raw_data_serialize_8byte_aligned(
                                                                   &driver.imu_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(buf_size,
                             aceinna_imu_raw_data_serialize_8byte_aligned(&driver.imu_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             aceinna_imu_raw_data_deserialize_8byte_aligned(&imu_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(buf_size, aceinna_imu_raw_data_deserialize_8byte_aligned(&imu_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_HEX64(driver.imu_raw_data.timestamp.nsec, imu_raw_data.timestamp.nsec);

    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_acc_x(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_acc_x(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_acc_y(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_acc_y(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_acc_z(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_acc_z(&imu_raw_data));

    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_gyroscope_x(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_gyroscope_x(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_gyroscope_y(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_gyroscope_y(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_gyroscope_z(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_gyroscope_z(&imu_raw_data));
}

void test_aceinna_imu_serialize_and_deserialize_default(void)
{
    const uint8_t            buf_size       = 20;
    const uint8_t            error_buf_size = 10;
    uint8_t                  buffer[24];
    struct AceinnaImuRawData imu_raw_data;

    TEST_ASSERT_EQUAL_UINT64(buf_size, aceinna_imu_raw_data_get_serialized_size(&imu_raw_data));

    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             aceinna_imu_raw_data_serialize(&driver.imu_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(buf_size, aceinna_imu_raw_data_serialize(&driver.imu_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             aceinna_imu_raw_data_deserialize(&imu_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(buf_size, aceinna_imu_raw_data_deserialize(&imu_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_HEX64(driver.imu_raw_data.timestamp.nsec, imu_raw_data.timestamp.nsec);

    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_acc_x(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_acc_x(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_acc_y(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_acc_y(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_acc_z(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_acc_z(&imu_raw_data));

    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_gyroscope_x(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_gyroscope_x(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_gyroscope_y(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_gyroscope_y(&imu_raw_data));
    TEST_ASSERT_EQUAL_HEX16(aceinna_imu_raw_data_get_gyroscope_z(&driver.imu_raw_data),
                            aceinna_imu_raw_data_get_gyroscope_z(&imu_raw_data));
}

void test_aceinna_imu_process_data_failure_case(void)
{
    uint32_t         msg_id;
    uint8_t          data[8];
    uint8_t          len;
    time_t           utc_seconds;
    struct Timestamp time_stamp;

    utc_seconds = time((time_t*)NULL);

    msg_id  = ID_Aceinna_Accel;
    data[0] = 0x78;
    data[1] = 0x7D;
    data[2] = 0x32;
    data[3] = 0x7D;
    data[4] = 0x46;
    data[5] = 0x7D;
    data[6] = 0x00;
    data[7] = 0x00;
    len     = 8;
    timestamp_init_from_sec(&time_stamp, utc_seconds);

    TEST_ASSERT_EQUAL(RC_PARSE_ACEINNA_IMU_CONTINUE,
                      aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));

    TEST_ASSERT_EQUAL(RC_PARSE_ACEINNA_IMU_DATA_ERROR,
                      aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));

    TEST_ASSERT_EQUAL(RC_PARSE_ACEINNA_IMU_CONTINUE,
                      aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));

    msg_id = ID_Aceinna_AngleRate;
    TEST_ASSERT_EQUAL(RC_SUCCESS, aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));

    TEST_ASSERT_EQUAL(RC_PARSE_ACEINNA_IMU_DATA_ERROR,
                      aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));

    msg_id = 0xFF;
    TEST_ASSERT_EQUAL(RC_PARSE_ACEINNA_IMU_ID_ERROR,
                      aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));

    driver.parse_state = 5;
    TEST_ASSERT_EQUAL(RC_PARSE_ACEINNA_IMU_DATA_ERROR,
                      aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));

    driver.parse_state = ACEINNA_IMU_PARSE_LINEAR_ACC;
    msg_id             = ID_Aceinna_AngleRate;
    TEST_ASSERT_EQUAL(RC_PARSE_ACEINNA_IMU_DATA_ERROR,
                      aceinna_imu_driver_process_data(&driver, &time_stamp, msg_id, data, len));
}

int main(void)
{
    UNITY_BEGIN();

    init_global_variables();
    RUN_TEST(test_aceinna_imu_driver_init);
    RUN_TEST(test_aceinna_imu_process_data);
    RUN_TEST(test_aceinna_imu_serialize_and_deserialize_4byte_aligend);
    RUN_TEST(test_aceinna_imu_serialize_and_deserialize_8byte_aligend);
    RUN_TEST(test_aceinna_imu_serialize_and_deserialize_default);
    RUN_TEST(test_aceinna_imu_process_data_failure_case);

    return UNITY_END();
}
