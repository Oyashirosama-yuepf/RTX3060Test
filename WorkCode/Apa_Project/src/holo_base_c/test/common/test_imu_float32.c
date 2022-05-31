/*!
 * @brief Unit test for imu float32_t.
 * @author lichao@holomatic.com
 * @date Sep 07, 2019
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <string.h>
#include <unity.h>

#include <holo_c/common/imu_float32.h>
#include <holo_c/core/retcode.h>

#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imuf_init(void)
{
    /* construct imu float32_t */
    struct Imuf actual_imu;
    /* generate expected result */
    struct Timestamp expected_stamp;
    timestamp_init(&expected_stamp);
    const Coordinate_t expected_coordinate = coordinate_default_create();
    struct Vectorf   expected_angular_velocity;
    float32_t        expected_angular_velocity_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_angular_velocity, 3, expected_angular_velocity_buf, VECTORF_MIN_BUF_SIZE(3u));
    struct Vectorf expected_linear_acceleration;
    float32_t      expected_linear_acceleration_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_linear_acceleration, 3, expected_linear_acceleration_buf, VECTORF_MIN_BUF_SIZE(3u));

    const enum ImuStatus expected_status = IMU_STATUS_ALLGOOD;
    /*test init functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, imuf_init(&actual_imu));
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, &actual_imu.stamp));
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, actual_imu.coordinate);
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_angular_velocity, &actual_imu.angular_velocity));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_linear_acceleration, &actual_imu.linear_acceleration));
    TEST_ASSERT_EQUAL_INT32(expected_status, actual_imu.status);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imuf_get_timestamp(void)
{
    /* construct imu float32_t */
    struct Imuf imu;
    imuf_init(&imu);

    /* generate expected timestamp */
    struct Timestamp expected_stamp;
    timestamp_init_from_sec(&expected_stamp, 4.6f);

    /* test get stamp function */
    imuf_set_timestamp(&imu, &expected_stamp);
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, imuf_get_timestamp(&imu)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imuf_set_and_get_coordinate(void)
{
    /* construct imu float32_t */
    struct Imuf imu;
    imuf_init(&imu);

    /* generate expected coordinate */
    const Coordinate_t expected_coordinate = coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER);

    /* test get coordinate function */
    imuf_set_coordinate(&imu, expected_coordinate);
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, imuf_get_coordinate(&imu));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imuf_set_and_get_angular_velocity(void)
{
    /* construct imu float32_t */
    struct Imuf imu;
    imuf_init(&imu);

    /* generate expected angular velocity */
    struct Vectorf expected_angular_velocity;
    float32_t      expected_angular_velocity_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_angular_velocity, 3, expected_angular_velocity_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected_angular_velocity, 0u, 2.1f);
    vectorf_set(&expected_angular_velocity, 1u, 2.4f);
    vectorf_set(&expected_angular_velocity, 2u, 3.1f);

    /* test get angular velocity function */
    imuf_set_angular_velocity(&imu, &expected_angular_velocity);
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_angular_velocity, &imu.angular_velocity));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imuf_set_and_get_linear_acceleration(void)
{
    /* construct imu float32_t */
    struct Imuf imu;
    imuf_init(&imu);

    /* generate expected linear acceleration */
    struct Vectorf expected_linear_acceleration;
    float32_t      expected_linear_acceleration_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_linear_acceleration, 3, expected_linear_acceleration_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected_linear_acceleration, 0u, 2.1f);
    vectorf_set(&expected_linear_acceleration, 1u, 2.4f);
    vectorf_set(&expected_linear_acceleration, 2u, 9.8f);

    /* test get linear acceleration function */
    imuf_set_linear_acceleration(&imu, &expected_linear_acceleration);
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_linear_acceleration, &imu.linear_acceleration));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imuf_get_status(void)
{
    /* construct imu float32_t */
    struct Imuf imu;
    imuf_init(&imu);

    /* generate expected status */
    const enum ImuStatus expected_status = IMU_STATUS_ACCLZERROR;

    /* test get status function */
    imuf_set_status(&imu, expected_status);
    TEST_ASSERT_EQUAL_INT32(expected_status, imuf_get_status(&imu));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imuf_set_timestamp(void)
{
    /* construct imu float32_t */
    struct Imuf imu;
    imuf_init(&imu);

    /* generate expected timestamp */
    struct Timestamp expected_stamp;
    timestamp_init_from_sec(&expected_stamp, 4.6f);

    /* test set stamp function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, imuf_set_timestamp(&imu, &expected_stamp));
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, imuf_get_timestamp(&imu)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imuf_set_coordinate(void)
{
    /* construct imu float32_t */
    struct Imuf imu;
    imuf_init(&imu);

    /* generate expected coordinate */
    const Coordinate_t expected_coordinate = coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER);

    /* test set coordinate function */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, imuf_set_coordinate(&imu, expected_coordinate));
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, imuf_get_coordinate(&imu));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imuf_value_set_and_get(void)
{
    float32_t angle_rate_x, angle_rate_y, angle_rate_z, acc_x, acc_y, acc_z;

    struct Imuf imu;
    imuf_init(&imu);

    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_set_angular_velocity_value(&imu, 0.1, 0.2, 0.3));
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_set_linear_acceleration_value(&imu, 1.1, 1.2, 1.3));

    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&imu, &angle_rate_x, NULL, NULL));
    TEST_ASSERT_EQUAL_FLOAT(0.1, angle_rate_x);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&imu, NULL, &angle_rate_y, NULL));
    TEST_ASSERT_EQUAL_FLOAT(0.2, angle_rate_y);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&imu, NULL, NULL, &angle_rate_z));
    TEST_ASSERT_EQUAL_FLOAT(0.3, angle_rate_z);

    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&imu, &acc_x, NULL, NULL));
    TEST_ASSERT_EQUAL_FLOAT(1.1, acc_x);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&imu, NULL, &acc_y, NULL));
    TEST_ASSERT_EQUAL_FLOAT(1.2, acc_y);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&imu, NULL, NULL, &acc_z));
    TEST_ASSERT_EQUAL_FLOAT(1.3, acc_z);

    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_set_angular_velocity_value(&imu, 2.1, -2.2, 2.3));
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_set_linear_acceleration_value(&imu, 3.1, 3.2, -3.3));

    TEST_ASSERT_EQUAL_INT(RC_SUCCESS,
                          imuf_get_angular_velocity_value(&imu, &angle_rate_x, &angle_rate_y, &angle_rate_z));
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&imu, &acc_x, &acc_y, &acc_z));

    TEST_ASSERT_EQUAL_FLOAT(2.1, angle_rate_x);
    TEST_ASSERT_EQUAL_FLOAT(-2.2, angle_rate_y);
    TEST_ASSERT_EQUAL_FLOAT(2.3, angle_rate_z);
    TEST_ASSERT_EQUAL_FLOAT(3.1, acc_x);
    TEST_ASSERT_EQUAL_FLOAT(3.2, acc_y);
    TEST_ASSERT_EQUAL_FLOAT(-3.3, acc_z);
}

void test_imuf_serialize_and_deserialize_4byte_aligned(void)
{
    const uint8_t    buf_size       = 54;
    const uint8_t    error_buf_size = 20;
    uint8_t          buffer[50];
    struct Timestamp timestamp;
    struct Imuf      imu;
    struct Imuf      deserialized_imu;
    float32_t        angle_rate_x, angle_rate_y, angle_rate_z, acc_x, acc_y, acc_z;
    float32_t        angle_rate_buf[VECTORF_MIN_BUF_SIZE(3)];
    float32_t        linear_acc_buf[VECTORF_MIN_BUF_SIZE(3)];
    struct Vectorf   angle_rate, linear_acc;

    memset(buffer, 0, 50);
    timestamp_init_from_sec(&timestamp, 4.6f);
    imuf_init(&imu);
    imuf_init(&deserialized_imu);
    vectorf_init(&angle_rate, 3, angle_rate_buf, VECTORF_MIN_BUF_SIZE(3));
    vectorf_init(&linear_acc, 3, linear_acc_buf, VECTORF_MIN_BUF_SIZE(3));

    imuf_set_timestamp(&imu, &timestamp);
    imuf_set_angular_velocity_value(&imu, 0.1, -0.2, 0.3);
    imuf_set_linear_acceleration_value(&imu, -1.1, 1.2, 1.3);

    TEST_ASSERT_EQUAL_UINT64(40, imuf_get_serialized_size_4byte_aligned(&imu));
    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             imuf_serialize_4byte_aligned(&imu, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(40, imuf_serialize_4byte_aligned(&imu, buffer, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             imuf_deserialize_4byte_aligned(&deserialized_imu, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(40, imuf_deserialize_4byte_aligned(&deserialized_imu, buffer, buf_size));

    TEST_ASSERT_TRUE(timestamp_is_equal(&timestamp, imuf_get_timestamp(&deserialized_imu)));
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&deserialized_imu, &angle_rate_x, NULL, NULL));
    TEST_ASSERT_EQUAL_FLOAT(0.1, angle_rate_x);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&deserialized_imu, NULL, &angle_rate_y, NULL));
    TEST_ASSERT_EQUAL_FLOAT(-0.2, angle_rate_y);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&deserialized_imu, NULL, NULL, &angle_rate_z));
    TEST_ASSERT_EQUAL_FLOAT(0.3, angle_rate_z);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&deserialized_imu, &acc_x, NULL, NULL));
    TEST_ASSERT_EQUAL_FLOAT(-1.1, acc_x);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&deserialized_imu, NULL, &acc_y, NULL));
    TEST_ASSERT_EQUAL_FLOAT(1.2, acc_y);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&deserialized_imu, NULL, NULL, &acc_z));
    TEST_ASSERT_EQUAL_FLOAT(1.3, acc_z);

    vectorf_set_from_vectorf(&angle_rate, imuf_get_angular_velocity(&deserialized_imu));
    TEST_ASSERT_EQUAL_FLOAT(0.1, angle_rate.base[0]);
    TEST_ASSERT_EQUAL_FLOAT(-0.2, angle_rate.base[1]);
    TEST_ASSERT_EQUAL_FLOAT(0.3, angle_rate.base[2]);

    vectorf_set_from_vectorf(&linear_acc, imuf_get_linear_acceleration(&deserialized_imu));
    TEST_ASSERT_EQUAL_FLOAT(-1.1, linear_acc.base[0]);
    TEST_ASSERT_EQUAL_FLOAT(1.2, linear_acc.base[1]);
    TEST_ASSERT_EQUAL_FLOAT(1.3, linear_acc.base[2]);
}

void test_imuf_serialize_and_deserialize_8byte_aligned(void)
{
    const uint8_t    buf_size       = 60;
    const uint8_t    error_buf_size = 20;
    uint8_t          buffer[60];
    struct Timestamp timestamp;
    struct Imuf      imu;
    struct Imuf      deserialized_imu;
    float32_t        angle_rate_x, angle_rate_y, angle_rate_z, acc_x, acc_y, acc_z;
    float32_t        angle_rate_buf[VECTORF_MIN_BUF_SIZE(3)];
    float32_t        linear_acc_buf[VECTORF_MIN_BUF_SIZE(3)];
    struct Vectorf   angle_rate, linear_acc;

    memset(buffer, 0, 60);
    timestamp_init_from_sec(&timestamp, 4.6f);
    imuf_init(&imu);
    imuf_init(&deserialized_imu);
    vectorf_init(&angle_rate, 3, angle_rate_buf, VECTORF_MIN_BUF_SIZE(3));
    vectorf_init(&linear_acc, 3, linear_acc_buf, VECTORF_MIN_BUF_SIZE(3));

    imuf_set_timestamp(&imu, &timestamp);
    imuf_set_angular_velocity_value(&imu, 0.1, -0.2, 0.3);
    imuf_set_linear_acceleration_value(&imu, -1.1, 1.2, 1.3);

    TEST_ASSERT_EQUAL_UINT64(40, imuf_get_serialized_size_8byte_aligned(&imu));
    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             imuf_serialize_8byte_aligned(&imu, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(40, imuf_serialize_8byte_aligned(&imu, buffer, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             imuf_deserialize_8byte_aligned(&deserialized_imu, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(40, imuf_deserialize_8byte_aligned(&deserialized_imu, buffer, buf_size));

    TEST_ASSERT_TRUE(timestamp_is_equal(&timestamp, imuf_get_timestamp(&deserialized_imu)));
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&deserialized_imu, &angle_rate_x, NULL, NULL));
    TEST_ASSERT_EQUAL_FLOAT(0.1, angle_rate_x);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&deserialized_imu, NULL, &angle_rate_y, NULL));
    TEST_ASSERT_EQUAL_FLOAT(-0.2, angle_rate_y);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&deserialized_imu, NULL, NULL, &angle_rate_z));
    TEST_ASSERT_EQUAL_FLOAT(0.3, angle_rate_z);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&deserialized_imu, &acc_x, NULL, NULL));
    TEST_ASSERT_EQUAL_FLOAT(-1.1, acc_x);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&deserialized_imu, NULL, &acc_y, NULL));
    TEST_ASSERT_EQUAL_FLOAT(1.2, acc_y);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&deserialized_imu, NULL, NULL, &acc_z));
    TEST_ASSERT_EQUAL_FLOAT(1.3, acc_z);

    vectorf_set_from_vectorf(&angle_rate, imuf_get_angular_velocity(&deserialized_imu));
    TEST_ASSERT_EQUAL_FLOAT(0.1, angle_rate.base[0]);
    TEST_ASSERT_EQUAL_FLOAT(-0.2, angle_rate.base[1]);
    TEST_ASSERT_EQUAL_FLOAT(0.3, angle_rate.base[2]);

    vectorf_set_from_vectorf(&linear_acc, imuf_get_linear_acceleration(&deserialized_imu));
    TEST_ASSERT_EQUAL_FLOAT(-1.1, linear_acc.base[0]);
    TEST_ASSERT_EQUAL_FLOAT(1.2, linear_acc.base[1]);
    TEST_ASSERT_EQUAL_FLOAT(1.3, linear_acc.base[2]);
}

void test_imuf_serialize_and_deserialize_default(void)
{
    const uint8_t    buf_size       = 54;
    const uint8_t    error_buf_size = 20;
    uint8_t          buffer[50];
    struct Timestamp timestamp;
    struct Imuf      imu;
    struct Imuf      deserialized_imu;
    float32_t        angle_rate_x, angle_rate_y, angle_rate_z, acc_x, acc_y, acc_z;
    float32_t        angle_rate_buf[VECTORF_MIN_BUF_SIZE(3)];
    float32_t        linear_acc_buf[VECTORF_MIN_BUF_SIZE(3)];
    struct Vectorf   angle_rate, linear_acc;

    memset(buffer, 0, 50);
    timestamp_init_from_sec(&timestamp, 4.6f);
    imuf_init(&imu);
    imuf_init(&deserialized_imu);
    vectorf_init(&angle_rate, 3, angle_rate_buf, VECTORF_MIN_BUF_SIZE(3));
    vectorf_init(&linear_acc, 3, linear_acc_buf, VECTORF_MIN_BUF_SIZE(3));

    imuf_set_timestamp(&imu, &timestamp);
    imuf_set_angular_velocity_value(&imu, 0.1, -0.2, 0.3);
    imuf_set_linear_acceleration_value(&imu, -1.1, 1.2, 1.3);

    TEST_ASSERT_EQUAL_UINT64(40, imuf_get_serialized_size(&imu));
    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW, imuf_serialize(&imu, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(40, imuf_serialize(&imu, buffer, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             imuf_deserialize(&deserialized_imu, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(40, imuf_deserialize(&deserialized_imu, buffer, buf_size));

    TEST_ASSERT_TRUE(timestamp_is_equal(&timestamp, imuf_get_timestamp(&deserialized_imu)));
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&deserialized_imu, &angle_rate_x, NULL, NULL));
    TEST_ASSERT_EQUAL_FLOAT(0.1, angle_rate_x);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&deserialized_imu, NULL, &angle_rate_y, NULL));
    TEST_ASSERT_EQUAL_FLOAT(-0.2, angle_rate_y);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_angular_velocity_value(&deserialized_imu, NULL, NULL, &angle_rate_z));
    TEST_ASSERT_EQUAL_FLOAT(0.3, angle_rate_z);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&deserialized_imu, &acc_x, NULL, NULL));
    TEST_ASSERT_EQUAL_FLOAT(-1.1, acc_x);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&deserialized_imu, NULL, &acc_y, NULL));
    TEST_ASSERT_EQUAL_FLOAT(1.2, acc_y);
    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, imuf_get_linear_acceleration_value(&deserialized_imu, NULL, NULL, &acc_z));
    TEST_ASSERT_EQUAL_FLOAT(1.3, acc_z);

    vectorf_set_from_vectorf(&angle_rate, imuf_get_angular_velocity(&deserialized_imu));
    TEST_ASSERT_EQUAL_FLOAT(0.1, angle_rate.base[0]);
    TEST_ASSERT_EQUAL_FLOAT(-0.2, angle_rate.base[1]);
    TEST_ASSERT_EQUAL_FLOAT(0.3, angle_rate.base[2]);

    vectorf_set_from_vectorf(&linear_acc, imuf_get_linear_acceleration(&deserialized_imu));
    TEST_ASSERT_EQUAL_FLOAT(-1.1, linear_acc.base[0]);
    TEST_ASSERT_EQUAL_FLOAT(1.2, linear_acc.base[1]);
    TEST_ASSERT_EQUAL_FLOAT(1.3, linear_acc.base[2]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_imuf_init);
    RUN_TEST(test_imuf_get_timestamp);
    RUN_TEST(test_imuf_set_and_get_coordinate);
    RUN_TEST(test_imuf_set_and_get_angular_velocity);
    RUN_TEST(test_imuf_set_and_get_linear_acceleration);
    RUN_TEST(test_imuf_get_status);
    RUN_TEST(test_imuf_set_timestamp);
    RUN_TEST(test_imuf_set_coordinate);
    RUN_TEST(test_imuf_value_set_and_get);
    RUN_TEST(test_imuf_serialize_and_deserialize_4byte_aligned);
    RUN_TEST(test_imuf_serialize_and_deserialize_8byte_aligned);
    RUN_TEST(test_imuf_serialize_and_deserialize_default);
    return UNITY_END();
}
