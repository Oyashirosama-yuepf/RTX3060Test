/*!
 * @brief Unit test for ImuBias float32_t.
 * @author lichao@holomatic.com
 * @date Sep 12, 2019
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <unity.h>

#include <holo_c/common/imu_bias_float32.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imu_bias_init(void)
{
    /* construct imu bias */
    struct ImuBiasf actual_imu_bias;

    /* generate expected result */
    struct Timestamp expected_stamp;
    timestamp_init(&expected_stamp);
    Coordinate_t expected_coordinate = coordinate_default_create();
    
    struct Vectorf   expected_angular_velocity_bias;
    float32_t        expected_angular_velocity_bias_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_angular_velocity_bias, 3, expected_angular_velocity_bias_buf, VECTORF_MIN_BUF_SIZE(3u));
    struct Vectorf expected_linear_acceleration_bias;
    float32_t      expected_linear_acceleration_bias_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_linear_acceleration_bias, 3, expected_linear_acceleration_bias_buf,
                 VECTORF_MIN_BUF_SIZE(3u));
    struct Vectorf expected_angular_velocity_bias_cov;
    float32_t      expected_angular_velocity_bias_cov_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_angular_velocity_bias_cov, 3, expected_angular_velocity_bias_cov_buf,
                 VECTORF_MIN_BUF_SIZE(3u));
    struct Vectorf expected_linear_acceleration_bias_cov;
    float32_t      expected_linear_acceleration_bias_cov_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_linear_acceleration_bias_cov, 3, expected_linear_acceleration_bias_cov_buf,
                 VECTORF_MIN_BUF_SIZE(3u));

    /*test init functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, imu_biasf_init(&actual_imu_bias));
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, &actual_imu_bias.stamp));
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, imu_biasf_get_coordinate(&actual_imu_bias));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_angular_velocity_bias, &actual_imu_bias.angular_velocity_bias));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_linear_acceleration_bias, &actual_imu_bias.linear_acceleration_bias));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_angular_velocity_bias_cov, &actual_imu_bias.angular_velocity_bias_cov));
    TEST_ASSERT_TRUE(
        vectorf_is_equal(&expected_linear_acceleration_bias_cov, &actual_imu_bias.linear_acceleration_bias_cov));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imu_biasf_get_timestamp(void)
{
    /* construct Imubias float32_t */
    struct ImuBiasf imu_bias;
    imu_biasf_init(&imu_bias);

    /* generate expected timestamp */
    struct Timestamp expected_stamp;
    timestamp_init_from_sec(&expected_stamp, 4.6f);

    /* test get stamp function */
    imu_biasf_set_timestamp(&imu_bias, &expected_stamp);
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, imu_biasf_get_timestamp(&imu_bias)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imu_biasf_set_and_get_coordinate(void)
{
    /* construct ImuBias float32_t */
    struct ImuBiasf imu_bias;
    imu_biasf_init(&imu_bias);

    /* generate expected coordinate */
    Coordinate_t expected_coordinate = coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER);

    /* test get coordinate function */
    imu_biasf_set_coordinate(&imu_bias, expected_coordinate);
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, imu_biasf_get_coordinate(&imu_bias));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imu_biasf_set_and_get_angular_velocity_bias(void)
{
    /* construct ImuBias float32_t */
    struct ImuBiasf imu_bias;
    imu_biasf_init(&imu_bias);

    /* generate expected angular velocity bias */
    struct Vectorf expected_angular_velocity_bias;
    float32_t      expected_angular_velocity_bias_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_angular_velocity_bias, 3, expected_angular_velocity_bias_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected_angular_velocity_bias, 0u, 2.1f);
    vectorf_set(&expected_angular_velocity_bias, 1u, 2.4f);
    vectorf_set(&expected_angular_velocity_bias, 2u, 3.1f);

    /* test get angular velocity bias function */
    imu_biasf_set_angular_velocity_bias(&imu_bias, &expected_angular_velocity_bias);
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_angular_velocity_bias, imu_biasf_get_angular_velocity_bias(&imu_bias)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imu_biasf_set_and_get_linear_acceleration_bias(void)
{
    /* construct ImuBias float32_t */
    struct ImuBiasf imu_bias;
    imu_biasf_init(&imu_bias);

    /* generate expected linear acceleration bias */
    struct Vectorf expected_linear_acceleration_bias;
    float32_t      expected_linear_acceleration_bias_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_linear_acceleration_bias, 3, expected_linear_acceleration_bias_buf,
                 VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected_linear_acceleration_bias, 0u, 2.1f);
    vectorf_set(&expected_linear_acceleration_bias, 1u, 2.4f);
    vectorf_set(&expected_linear_acceleration_bias, 2u, 9.8f);

    /* test get linear acceleration bias function */
    imu_biasf_set_linear_acceleration_bias(&imu_bias, &expected_linear_acceleration_bias);
    TEST_ASSERT_TRUE(
        vectorf_is_equal(&expected_linear_acceleration_bias, imu_biasf_get_linear_acceleration_bias(&imu_bias)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imu_biasf_set_and_get_angular_velocity_bias_cov(void)
{
    /* construct ImuBias float32_t */
    struct ImuBiasf imu_bias;
    imu_biasf_init(&imu_bias);

    /* generate expected angular velocity bias cov */
    struct Vectorf expected_angular_velocity_bias_cov;
    float32_t      expected_angular_velocity_bias_cov_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_angular_velocity_bias_cov, 3, expected_angular_velocity_bias_cov_buf,
                 VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected_angular_velocity_bias_cov, 0u, 2.1f);
    vectorf_set(&expected_angular_velocity_bias_cov, 1u, 2.4f);
    vectorf_set(&expected_angular_velocity_bias_cov, 2u, 3.1f);

    /* test get angular velocity bias cov function */
    imu_biasf_set_angular_velocity_bias_covariance(&imu_bias, &expected_angular_velocity_bias_cov);
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_angular_velocity_bias_cov,
                                      imu_biasf_get_angular_velocity_bias_covariance(&imu_bias)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_imu_biasf_set_and_get_linear_acceleration_bias_cov(void)
{
    /* construct ImuBias float32_t */
    struct ImuBiasf imu_bias;
    imu_biasf_init(&imu_bias);

    /* generate expected linear acceleration bias cov */
    struct Vectorf expected_linear_acceleration_bias_cov;
    float32_t      expected_linear_acceleration_bias_cov_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_linear_acceleration_bias_cov, 3, expected_linear_acceleration_bias_cov_buf,
                 VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected_linear_acceleration_bias_cov, 0u, 2.1f);
    vectorf_set(&expected_linear_acceleration_bias_cov, 1u, 2.4f);
    vectorf_set(&expected_linear_acceleration_bias_cov, 2u, 9.8f);

    /* test get linear acceleration bias cov function */
    imu_biasf_set_linear_acceleration_bias_covariance(&imu_bias, &expected_linear_acceleration_bias_cov);
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_linear_acceleration_bias_cov,
                                      imu_biasf_get_linear_acceleration_bias_covariance(&imu_bias)));
}

void test_imu_biasf_serialize_deserialize(void)
{
    struct ImuBiasf imu_bias;
    uint32_t expected_size;
    uint8_t buffer[512];
    retcode_t retcode;

    imu_biasf_init(&imu_bias);
    expected_size = imu_biasf_get_serialized_size(&imu_bias);

    retcode = imu_biasf_serialize(&imu_bias, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, retcode);
    retcode = imu_biasf_deserialize(&imu_bias, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, retcode);

    retcode = imu_biasf_serialize(&imu_bias, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(expected_size, retcode);

    retcode = imu_biasf_deserialize(&imu_bias, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(expected_size, retcode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_imu_bias_init);
    RUN_TEST(test_imu_biasf_get_timestamp);
    RUN_TEST(test_imu_biasf_set_and_get_coordinate);
    RUN_TEST(test_imu_biasf_set_and_get_angular_velocity_bias);
    RUN_TEST(test_imu_biasf_set_and_get_linear_acceleration_bias);
    RUN_TEST(test_imu_biasf_set_and_get_angular_velocity_bias_cov);
    RUN_TEST(test_imu_biasf_set_and_get_linear_acceleration_bias_cov);
    RUN_TEST(test_imu_biasf_serialize_deserialize);
    return UNITY_END();
}
