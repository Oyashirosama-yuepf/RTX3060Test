/*!
 * @brief Unit test for gnss position.
 * @author lichao@holomatic.com
 * @date Sep 13, 2019
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <string.h>
#include <unity.h>

#include <holo_c/common/gnss_position.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

static const float64_t gLatitudeBeijing  = 39.90421111f;
static const float64_t gLongitudeBeijing = 116.40741111f;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_init(void)
{
    /* construct gnss position */
    struct GnssPosition actual_position;

    /* generate expected result */
    struct Timestamp expected_stamp;
    timestamp_init(&expected_stamp);
    const Coordinate_t            expected_coordinate    = coordinate_wgs84_create();
    const float64_t               expected_latitude      = 0.0f;
    const float64_t               expected_longitude     = 0.0f;
    const float64_t               expected_altitude      = 0.0f;
    const float64_t               expected_latitude_cov  = 0.0f;
    const float64_t               expected_longitude_cov = 0.0f;
    const float64_t               expected_altitude_cov  = 0.0f;
    const enum GnssPositionStatus expected_status        = GNSS_POSITION_STATUS_ALLGOOD;

    /*test init functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, gnss_position_init(&actual_position));
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, gnss_position_get_timestamp(&actual_position)));
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, actual_position.coordinate);
    TEST_ASSERT_EQUAL_DOUBLE(expected_latitude, actual_position.latitude);
    TEST_ASSERT_EQUAL_DOUBLE(expected_longitude, actual_position.longitude);
    TEST_ASSERT_EQUAL_DOUBLE(expected_altitude, actual_position.altitude);
    TEST_ASSERT_EQUAL_DOUBLE(expected_latitude_cov, actual_position.latitude_cov);
    TEST_ASSERT_EQUAL_DOUBLE(expected_longitude_cov, actual_position.longitude_cov);
    TEST_ASSERT_EQUAL_DOUBLE(expected_altitude_cov, actual_position.altitude_cov);
    TEST_ASSERT_EQUAL_INT32(expected_status, actual_position.status);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_set_and_get_timestamp(void)
{
    /* construct GnssPosition */
    struct GnssPosition position;
    gnss_position_init(&position);

    /* generate expected timestamp */
    struct Timestamp expected_stamp;
    timestamp_init_from_sec(&expected_stamp, 4.6f);

    /* test get stamp function */
    gnss_position_set_timestamp(&position, &expected_stamp);
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, gnss_position_get_timestamp(&position)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_set_and_get_coordinate(void)
{
    /* construct GnssPosition */
    struct GnssPosition position;
    gnss_position_init(&position);

    /* generate expected coordinate */
    const Coordinate_t expected_coordinate = coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER);

    /* test get coordinate function */
    gnss_position_set_coordinate(&position, expected_coordinate);
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, gnss_position_get_coordinate(&position));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_set_and_get_status(void)
{
    /* construct GnssPosition */
    struct GnssPosition position;
    gnss_position_init(&position);

    /* generate expected status */
    const enum ImuStatus expected_status = IMU_STATUS_ACCLZERROR;

    /* test get status function */
    gnss_position_set_status(&position, expected_status);
    TEST_ASSERT_EQUAL_INT32(expected_status, gnss_position_get_status(&position));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_set_and_get_latitude(void)
{
    /* construct GnssPosition */
    struct GnssPosition position;
    gnss_position_init(&position);

    /* generate expected latitude */
    const float64_t expected_latitude = gLatitudeBeijing;

    /* test set and get latitude function */
    gnss_position_set_latitude(&position, expected_latitude);
    TEST_ASSERT_TRUE(expected_latitude == gnss_position_get_latitude(&position));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_set_and_get_longitude(void)
{
    /* construct GnssPosition */
    struct GnssPosition position;
    gnss_position_init(&position);

    /* generate expected longitude */
    const float64_t expected_longitude = gLongitudeBeijing;

    /* test set and get longitude function */
    gnss_position_set_longitude(&position, expected_longitude);
    TEST_ASSERT_TRUE(expected_longitude == gnss_position_get_longitude(&position));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_set_and_get_altitude(void)
{
    /* construct GnssPosition */
    struct GnssPosition position;
    gnss_position_init(&position);

    /* generate expected altitude */
    const float64_t expected_altitude = 10.9f;

    /* test set and get altitude function */
    gnss_position_set_altitude(&position, expected_altitude);
    TEST_ASSERT_TRUE(expected_altitude == gnss_position_get_altitude(&position));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_set_and_get_latitude_covariance(void)
{
    /* construct GnssPosition */
    struct GnssPosition position;
    gnss_position_init(&position);

    /* generate expected latitude covariance */
    const float64_t expected_latitude_covriance = 2.4f;

    /* test set and get latitude covariance function */
    gnss_position_set_latitude_covariance(&position, expected_latitude_covriance);
    TEST_ASSERT_TRUE(expected_latitude_covriance == gnss_position_get_latitude_covariance(&position));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_set_and_get_longitude_covariance(void)
{
    /* construct GnssPosition */
    struct GnssPosition position;
    gnss_position_init(&position);

    /* generate expected longitude covariance */
    const float64_t expected_longitude_covariance = 3.1f;

    /* test set and get longitude covariance function */
    gnss_position_set_longitude_covariance(&position, expected_longitude_covariance);
    TEST_ASSERT_TRUE(expected_longitude_covariance == gnss_position_get_longitude_covariance(&position));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_position_set_and_get_altitude_covariance(void)
{
    /* construct GnssPosition */
    struct GnssPosition position;
    gnss_position_init(&position);

    /* generate expected altitude covariance */
    const float64_t expected_altitude_covariance = 10.9f;

    /* test set and get altitude covariance function */
    gnss_position_set_altitude_covariance(&position, expected_altitude_covariance);
    TEST_ASSERT_TRUE(expected_altitude_covariance == gnss_position_get_altitude_covariance(&position));
}

void test_gnss_position_serialize_and_deseralize_4byte_aligned(void)
{
    const uint8_t       buf_size       = 64;
    const uint8_t       error_buf_size = 60;
    uint8_t             gnss_position_buf[64];
    struct Timestamp    timestamp;
    struct GnssPosition position;
    struct GnssPosition deserialized_position;

    memset(gnss_position_buf, 0, buf_size);
    timestamp_init_from_sec(&timestamp, 4.6f);
    gnss_position_init(&position);
    gnss_position_init(&deserialized_position);

    gnss_position_set_timestamp(&position, &timestamp);
    gnss_position_set_coordinate(&position, coordinate_utm6_create(50, false, 0u, 0u));
    gnss_position_set_status(&position, GNSS_POSITION_STATUS_ALLGOOD);
    gnss_position_set_latitude(&position, gLatitudeBeijing);
    gnss_position_set_longitude(&position, gLongitudeBeijing);
    gnss_position_set_altitude(&position, 43.5f);
    gnss_position_set_latitude_covariance(&position, 2.4f);
    gnss_position_set_longitude_covariance(&position, 3.1f);
    gnss_position_set_altitude_covariance(&position, 10.9f);

    TEST_ASSERT_EQUAL_UINT64(sizeof(struct GnssPosition), gnss_position_get_serialized_size_4byte_aligned(&position));
    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             gnss_position_serialize_4byte_aligned(&position, gnss_position_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(sizeof(struct GnssPosition),
                             gnss_position_serialize_4byte_aligned(&position, gnss_position_buf, buf_size));

    TEST_ASSERT_EQUAL_UINT64(
        RC_DESERIALIZATION_BUFFER_UNDERFLOW,
        gnss_position_deserialize_4byte_aligned(&deserialized_position, gnss_position_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(sizeof(struct GnssPosition), gnss_position_deserialize_4byte_aligned(
                                                              &deserialized_position, gnss_position_buf, buf_size));

    TEST_ASSERT_TRUE(timestamp_is_equal(&timestamp, gnss_position_get_timestamp(&deserialized_position)));
    TEST_ASSERT_EQUAL_UINT32(coordinate_utm6_create(50, false, 0u, 0u), 
            gnss_position_get_coordinate(&deserialized_position));
    TEST_ASSERT_EQUAL_UINT64(GNSS_POSITION_STATUS_ALLGOOD, gnss_position_get_status(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(gLatitudeBeijing, gnss_position_get_latitude(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(gLongitudeBeijing, gnss_position_get_longitude(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(43.5f, gnss_position_get_altitude(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(2.4f, gnss_position_get_latitude_covariance(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(3.1f, gnss_position_get_longitude_covariance(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(10.9f, gnss_position_get_altitude_covariance(&deserialized_position));
}

void test_gnss_position_serialize_and_deseralize_8byte_aligned(void)
{
    const uint8_t       buf_size       = 64;
    const uint8_t       error_buf_size = 60;
    uint8_t             gnss_position_buf[64];
    struct Timestamp    timestamp;
    struct GnssPosition position;
    struct GnssPosition deserialized_position;

    memset(gnss_position_buf, 0, buf_size);
    timestamp_init_from_sec(&timestamp, 4.6f);
    gnss_position_init(&position);
    gnss_position_init(&deserialized_position);

    gnss_position_set_timestamp(&position, &timestamp);
    gnss_position_set_coordinate(&position, coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER));
    gnss_position_set_status(&position, GNSS_POSITION_STATUS_ALLGOOD);
    gnss_position_set_latitude(&position, gLatitudeBeijing);
    gnss_position_set_longitude(&position, gLongitudeBeijing);
    gnss_position_set_altitude(&position, 43.5f);
    gnss_position_set_latitude_covariance(&position, 2.4f);
    gnss_position_set_longitude_covariance(&position, 3.1f);
    gnss_position_set_altitude_covariance(&position, 10.9f);

    TEST_ASSERT_EQUAL_UINT64(sizeof(struct GnssPosition), gnss_position_get_serialized_size_8byte_aligned(&position));
    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             gnss_position_serialize_8byte_aligned(&position, gnss_position_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(sizeof(struct GnssPosition),
                             gnss_position_serialize_8byte_aligned(&position, gnss_position_buf, buf_size));

    TEST_ASSERT_EQUAL_UINT64(
        RC_DESERIALIZATION_BUFFER_UNDERFLOW,
        gnss_position_deserialize_8byte_aligned(&deserialized_position, gnss_position_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(sizeof(struct GnssPosition), gnss_position_deserialize_8byte_aligned(
                                                              &deserialized_position, gnss_position_buf, buf_size));

    TEST_ASSERT_TRUE(timestamp_is_equal(&timestamp, gnss_position_get_timestamp(&deserialized_position)));
    TEST_ASSERT_EQUAL_UINT64(coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER), 
            gnss_position_get_coordinate(&deserialized_position));
    TEST_ASSERT_EQUAL_UINT64(GNSS_POSITION_STATUS_ALLGOOD, gnss_position_get_status(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(gLatitudeBeijing, gnss_position_get_latitude(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(gLongitudeBeijing, gnss_position_get_longitude(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(43.5f, gnss_position_get_altitude(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(2.4f, gnss_position_get_latitude_covariance(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(3.1f, gnss_position_get_longitude_covariance(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(10.9f, gnss_position_get_altitude_covariance(&deserialized_position));
}

void test_gnss_position_serialize_and_deseralize_default(void)
{
    const uint8_t       buf_size       = 64;
    const uint8_t       error_buf_size = 60;
    uint8_t             gnss_position_buf[64];
    struct Timestamp    timestamp;
    struct GnssPosition position;
    struct GnssPosition deserialized_position;

    memset(gnss_position_buf, 0, buf_size);
    timestamp_init_from_sec(&timestamp, 4.6f);
    gnss_position_init(&position);
    gnss_position_init(&deserialized_position);

    gnss_position_set_timestamp(&position, &timestamp);
    gnss_position_set_coordinate(&position, coordinate_utm6_create(50, false, 0u, 0u));
    gnss_position_set_status(&position, GNSS_POSITION_STATUS_ALLGOOD);
    gnss_position_set_latitude(&position, gLatitudeBeijing);
    gnss_position_set_longitude(&position, gLongitudeBeijing);
    gnss_position_set_altitude(&position, 43.5f);
    gnss_position_set_latitude_covariance(&position, 2.4f);
    gnss_position_set_longitude_covariance(&position, 3.1f);
    gnss_position_set_altitude_covariance(&position, 10.9f);

    TEST_ASSERT_EQUAL_UINT64(sizeof(struct GnssPosition), gnss_position_get_serialized_size(&position));
    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             gnss_position_serialize(&position, gnss_position_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(sizeof(struct GnssPosition),
                             gnss_position_serialize(&position, gnss_position_buf, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             gnss_position_deserialize(&deserialized_position, gnss_position_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(sizeof(struct GnssPosition),
                             gnss_position_deserialize(&deserialized_position, gnss_position_buf, buf_size));

    TEST_ASSERT_TRUE(timestamp_is_equal(&timestamp, gnss_position_get_timestamp(&deserialized_position)));
    TEST_ASSERT_EQUAL_UINT32(coordinate_utm6_create(50, false, 0u, 0u), 
            gnss_position_get_coordinate(&deserialized_position));
    TEST_ASSERT_EQUAL_UINT64(GNSS_POSITION_STATUS_ALLGOOD, gnss_position_get_status(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(gLatitudeBeijing, gnss_position_get_latitude(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(gLongitudeBeijing, gnss_position_get_longitude(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(43.5f, gnss_position_get_altitude(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(2.4f, gnss_position_get_latitude_covariance(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(3.1f, gnss_position_get_longitude_covariance(&deserialized_position));
    TEST_ASSERT_EQUAL_FLOAT(10.9f, gnss_position_get_altitude_covariance(&deserialized_position));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_gnss_position_init);
    RUN_TEST(test_gnss_position_set_and_get_timestamp);
    RUN_TEST(test_gnss_position_set_and_get_coordinate);
    RUN_TEST(test_gnss_position_set_and_get_status);
    RUN_TEST(test_gnss_position_set_and_get_latitude);
    RUN_TEST(test_gnss_position_set_and_get_longitude);
    RUN_TEST(test_gnss_position_set_and_get_altitude);
    RUN_TEST(test_gnss_position_set_and_get_latitude_covariance);
    RUN_TEST(test_gnss_position_set_and_get_longitude_covariance);
    RUN_TEST(test_gnss_position_set_and_get_altitude_covariance);
    RUN_TEST(test_gnss_position_serialize_and_deseralize_4byte_aligned);
    RUN_TEST(test_gnss_position_serialize_and_deseralize_8byte_aligned);
    RUN_TEST(test_gnss_position_serialize_and_deseralize_default);
    return UNITY_END();
}
