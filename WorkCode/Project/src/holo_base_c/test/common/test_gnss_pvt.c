/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_gnss_pvt.c
 * @brief This file realizes the test of the GnssPvt type
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Apr 13, 2020
 */

#include <holo_c/common/gnss_pvt.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <unity.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void test_gnss_pvt_init(void)
{
    /// Construct gnss pvt
    struct GnssPvt gnss_pvt;

    /// Generate the expected values
    struct Timestamp expected_timestamp;
    timestamp_init(&expected_timestamp);
    Coordinate_t expected_coordinate         = coordinate_wgs84_create();
    uint32_t     expected_status             = 0u;
    float64_t    expected_longitude          = 0.0;
    float64_t    expected_latitude           = 0.0;
    float64_t    expected_height             = 0.0;
    float64_t    expected_velocity_east      = 0.0;
    float64_t    expected_velocity_north     = 0.0;
    float64_t    expected_velocity_up        = 0.0;
    float64_t    expected_longitude_cov      = 0.0;
    float64_t    expected_latitude_cov       = 0.0;
    float64_t    expected_height_cov         = 0.0;
    float64_t    expected_velocity_east_cov  = 0.0;
    float64_t    expected_velocity_north_cov = 0.0;
    float64_t    expected_velocity_up_cov    = 0.0;

    retcode_t rc = gnss_pvt_init(&gnss_pvt);

    TEST_ASSERT_EQUAL(rc, RC_SUCCESS);
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_timestamp, &gnss_pvt.stamp));
    TEST_ASSERT_EQUAL_UINT32(expected_coordinate, gnss_pvt.coordinate);
    TEST_ASSERT_EQUAL_UINT32(expected_status, gnss_pvt.status);
    TEST_ASSERT_EQUAL_DOUBLE(expected_latitude, gnss_pvt.latitude);
    TEST_ASSERT_EQUAL_DOUBLE(expected_longitude, gnss_pvt.longitude);
    TEST_ASSERT_EQUAL_DOUBLE(expected_height, gnss_pvt.height);
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_east, gnss_pvt.velocity_east);
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_north, gnss_pvt.velocity_north);
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_up, gnss_pvt.velocity_up);
    TEST_ASSERT_EQUAL_DOUBLE(expected_latitude_cov, gnss_pvt.latitude_cov);
    TEST_ASSERT_EQUAL_DOUBLE(expected_longitude_cov, gnss_pvt.longitude_cov);
    TEST_ASSERT_EQUAL_DOUBLE(expected_height_cov, gnss_pvt.height_cov);
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_east_cov, gnss_pvt.velocity_east_cov);
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_north_cov, gnss_pvt.velocity_north_cov);
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_up_cov, gnss_pvt.velocity_up_cov);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_timestamp(void)
{
    /// Construct GnssPvt
    struct GnssPvt gnss_pvt;
    gnss_pvt_init(&gnss_pvt);

    /// Generate expected timestamp
    struct Timestamp expected_stamp;
    timestamp_init_from_sec(&expected_stamp, 4.6f);

    /// Test get stamp function
    gnss_pvt_set_timestamp(&gnss_pvt, &expected_stamp);
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, gnss_pvt_get_timestamp(&gnss_pvt)));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_coordinate(void)
{
    /// Construct GnssPvt
    struct GnssPvt gnss_pvt;
    gnss_pvt_init(&gnss_pvt);

    /// Generate expected coordinate
    Coordinate_t expected_coord = coordinate_default_create();

    /// Test get stamp function
    gnss_pvt_set_coordinate(&gnss_pvt, expected_coord);
    TEST_ASSERT_EQUAL_UINT32(expected_coord, gnss_pvt_get_coordinate(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_valid_flags(void)
{
    struct GnssPvt gnss_pvt;
    gnss_pvt_init(&gnss_pvt);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_valid_flags(&gnss_pvt, true, true, true, true));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_position_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_velocity_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_position_cov_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_velocity_cov_valid(&gnss_pvt));

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_valid_flags(&gnss_pvt, true, true, true, false));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_position_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_velocity_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_position_cov_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(false, gnss_pvt_is_velocity_cov_valid(&gnss_pvt));

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_valid_flags(&gnss_pvt, true, true, false, true));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_position_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_velocity_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(false, gnss_pvt_is_position_cov_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_velocity_cov_valid(&gnss_pvt));

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_valid_flags(&gnss_pvt, true, false, true, true));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_position_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(false, gnss_pvt_is_velocity_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_position_cov_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_velocity_cov_valid(&gnss_pvt));

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_valid_flags(&gnss_pvt, false, true, true, true));
    TEST_ASSERT_EQUAL(false, gnss_pvt_is_position_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_velocity_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_position_cov_valid(&gnss_pvt));
    TEST_ASSERT_EQUAL(true, gnss_pvt_is_velocity_cov_valid(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_mode(void)
{
    struct GnssPvt gnss_pvt;

    gnss_pvt_init(&gnss_pvt);
    TEST_ASSERT_EQUAL(GNSS_PVT_MODE_NO_POSITION, gnss_pvt_get_mode(&gnss_pvt));

    gnss_pvt_set_mode(&gnss_pvt, GNSS_PVT_MODE_SINGLE_FIX);
    TEST_ASSERT_EQUAL(GNSS_PVT_MODE_SINGLE_FIX, gnss_pvt_get_mode(&gnss_pvt));

    gnss_pvt_set_mode(&gnss_pvt, GNSS_PVT_MODE_DIFF_POSITION);
    TEST_ASSERT_EQUAL(GNSS_PVT_MODE_DIFF_POSITION, gnss_pvt_get_mode(&gnss_pvt));

    gnss_pvt_set_mode(&gnss_pvt, GNSS_PVT_MODE_RTK_FLOAT_FIX);
    TEST_ASSERT_EQUAL(GNSS_PVT_MODE_RTK_FLOAT_FIX, gnss_pvt_get_mode(&gnss_pvt));

    gnss_pvt_set_mode(&gnss_pvt, GNSS_PVT_MODE_RTK_INT_FIX);
    TEST_ASSERT_EQUAL(GNSS_PVT_MODE_RTK_INT_FIX, gnss_pvt_get_mode(&gnss_pvt));

    gnss_pvt_set_mode(&gnss_pvt, GNSS_PVT_MODE_TIMING_ONLY);
    TEST_ASSERT_EQUAL(GNSS_PVT_MODE_TIMING_ONLY, gnss_pvt_get_mode(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_longitude(void)
{
    float64_t const expected_longitude = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, true, false, false, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_longitude(&gnss_pvt, expected_longitude));
    TEST_ASSERT_EQUAL_DOUBLE(expected_longitude, gnss_pvt_get_longitude(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_latitude(void)
{
    float64_t const expected_latitude = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, true, false, false, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_latitude(&gnss_pvt, expected_latitude));
    TEST_ASSERT_EQUAL_DOUBLE(expected_latitude, gnss_pvt_get_latitude(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_height(void)
{
    float64_t const expected_height = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, true, false, false, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_height(&gnss_pvt, expected_height));
    TEST_ASSERT_EQUAL_DOUBLE(expected_height, gnss_pvt_get_height(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_east(void)
{
    float64_t const expected_velocity_east = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, true, false, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_velocity_east(&gnss_pvt, expected_velocity_east));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_east, gnss_pvt_get_velocity_east(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_north(void)
{
    float64_t const expected_velocity_north = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, true, false, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_velocity_north(&gnss_pvt, expected_velocity_north));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_north, gnss_pvt_get_velocity_north(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_up(void)
{
    float64_t const expected_velocity_up = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, true, false, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_velocity_up(&gnss_pvt, expected_velocity_up));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_up, gnss_pvt_get_velocity_up(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_longitude_cov(void)
{
    float64_t const expected_longitude_cov = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, true, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_longitude_cov(&gnss_pvt, expected_longitude_cov));
    TEST_ASSERT_EQUAL_DOUBLE(expected_longitude_cov, gnss_pvt_get_longitude_cov(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_latitude_cov(void)
{
    float64_t const expected_latitude_cov = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, true, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_latitude_cov(&gnss_pvt, expected_latitude_cov));
    TEST_ASSERT_EQUAL_DOUBLE(expected_latitude_cov, gnss_pvt_get_latitude_cov(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_height_cov(void)
{
    float64_t const expected_height_cov = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, true, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_height_cov(&gnss_pvt, expected_height_cov));
    TEST_ASSERT_EQUAL_DOUBLE(expected_height_cov, gnss_pvt_get_height_cov(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_east_cov(void)
{
    float64_t const expected_velocity_east_cov = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, false, true);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_velocity_east_cov(&gnss_pvt, expected_velocity_east_cov));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_east_cov, gnss_pvt_get_velocity_east_cov(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_north_cov(void)
{
    float64_t const expected_velocity_north_cov = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, false, true);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_velocity_north_cov(&gnss_pvt, expected_velocity_north_cov));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_north_cov, gnss_pvt_get_velocity_north_cov(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_up_cov(void)
{
    float64_t const expected_velocity_up_cov = 2.0;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, false, true);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_velocity_up_cov(&gnss_pvt, expected_velocity_up_cov));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_up_cov, gnss_pvt_get_velocity_up_cov(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_position_by_values(void)
{
    float64_t const expected_longitude = 1.1;
    float64_t const expected_latitude  = 2.2;
    float64_t const expected_height    = 3.3;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, true, false, false, false);

    TEST_ASSERT_EQUAL(
        RC_SUCCESS, gnss_pvt_set_position_by_values(&gnss_pvt, expected_longitude, expected_latitude, expected_height));
    TEST_ASSERT_EQUAL_DOUBLE(expected_longitude, gnss_pvt_get_longitude(&gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(expected_latitude, gnss_pvt_get_latitude(&gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(expected_height, gnss_pvt_get_height(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_by_values(void)
{
    float64_t const expected_velocity_east  = 1.1;
    float64_t const expected_velocity_north = 2.2;
    float64_t const expected_velocity_up    = 3.3;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, true, false, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_velocity_by_values(&gnss_pvt, expected_velocity_east,
                                                                  expected_velocity_north, expected_velocity_up));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_east, gnss_pvt_get_velocity_east(&gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_north, gnss_pvt_get_velocity_north(&gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_up, gnss_pvt_get_velocity_up(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_position_cov_by_values(void)
{
    float64_t const expected_longitude_cov = 1.1;
    float64_t const expected_latitude_cov  = 2.2;
    float64_t const expected_height_cov    = 3.3;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, true, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_position_cov_by_values(&gnss_pvt, expected_longitude_cov,
                                                                      expected_latitude_cov, expected_height_cov));
    TEST_ASSERT_EQUAL_DOUBLE(expected_longitude_cov, gnss_pvt_get_longitude_cov(&gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(expected_latitude_cov, gnss_pvt_get_latitude_cov(&gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(expected_height_cov, gnss_pvt_get_height_cov(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_cov_by_values(void)
{
    float64_t const expected_velocity_east_cov  = 1.1;
    float64_t const expected_velocity_north_cov = 2.2;
    float64_t const expected_velocity_up_cov    = 3.3;
    struct GnssPvt  gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, false, true);

    TEST_ASSERT_EQUAL(RC_SUCCESS,
                      gnss_pvt_set_velocity_cov_by_values(&gnss_pvt, expected_velocity_east_cov,
                                                          expected_velocity_north_cov, expected_velocity_up_cov));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_east_cov, gnss_pvt_get_velocity_east_cov(&gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_north_cov, gnss_pvt_get_velocity_north_cov(&gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(expected_velocity_up_cov, gnss_pvt_get_velocity_up_cov(&gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_position_with_point3d(void)
{
    struct Point3d expected_position;
    point3d_init_from_scalars(&expected_position, 1.1, 2.2, 3.3);

    struct GnssPvt gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, true, false, false, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_position(&gnss_pvt, &expected_position));
    struct Point3d actual_position;
    gnss_pvt_get_position(&gnss_pvt, &actual_position);
    TEST_ASSERT_TRUE(point3d_is_equal(&expected_position, &actual_position));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_with_point3d(void)
{
    struct Point3d expected_velocity;
    point3d_init_from_scalars(&expected_velocity, 1.1, 2.2, 3.3);

    struct GnssPvt gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, true, false, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_velocity(&gnss_pvt, &expected_velocity));
    struct Point3d actual_velocity;
    gnss_pvt_get_velocity(&gnss_pvt, &actual_velocity);
    TEST_ASSERT_TRUE(point3d_is_equal(&expected_velocity, &actual_velocity));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_position_cov_with_point3d(void)
{
    struct Point3d expected_position_cov;
    point3d_init_from_scalars(&expected_position_cov, 1.1, 2.2, 3.3);

    struct GnssPvt gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, true, false);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_position_cov(&gnss_pvt, &expected_position_cov));
    struct Point3d actual_position_cov;
    gnss_pvt_get_position_cov(&gnss_pvt, &actual_position_cov);
    TEST_ASSERT_TRUE(point3d_is_equal(&expected_position_cov, &actual_position_cov));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_set_and_get_velocity_cov_with_point3d(void)
{
    struct Point3d expected_velocity_cov;
    point3d_init_from_scalars(&expected_velocity_cov, 1.1, 2.2, 3.3);

    struct GnssPvt gnss_pvt;
    gnss_pvt_init(&gnss_pvt);
    gnss_pvt_set_valid_flags(&gnss_pvt, false, false, false, true);

    TEST_ASSERT_EQUAL(RC_SUCCESS, gnss_pvt_set_velocity_cov(&gnss_pvt, &expected_velocity_cov));
    struct Point3d actual_velocity_cov;
    gnss_pvt_get_velocity_cov(&gnss_pvt, &actual_velocity_cov);
    TEST_ASSERT_TRUE(point3d_is_equal(&expected_velocity_cov, &actual_velocity_cov));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_gnss_pvt_serialize_and_deserialize(void)
{
    struct GnssPvt gnss_pvt;
    uint8_t        buffer[1024];
    uint32_t       buffer_size;
    retcode_t      retcode;
    gnss_pvt_init(&gnss_pvt);

    /// Initialize the GnssPvt
    struct Timestamp expected_stamp;
    timestamp_init_from_sec_nsec(&expected_stamp, 200u, 100u);
    gnss_pvt_set_timestamp(&gnss_pvt, &expected_stamp);
    gnss_pvt_set_valid_flags(&gnss_pvt, true, true, true, true);
    gnss_pvt_set_mode(&gnss_pvt, GNSS_PVT_MODE_RTK_FLOAT_FIX);
    gnss_pvt_set_position_by_values(&gnss_pvt, 1.1, 2.2, 3.3);
    gnss_pvt_set_velocity_by_values(&gnss_pvt, 4.4, 5.5, 6.6);
    gnss_pvt_set_position_cov_by_values(&gnss_pvt, 7.7, 8.8, 9.9);
    gnss_pvt_set_velocity_cov_by_values(&gnss_pvt, 10.1, 11.2, 12.3);

    /// Call the serialize and deserialize
    buffer_size = gnss_pvt_get_serialized_size(&gnss_pvt);
    TEST_ASSERT_LESS_THAN_UINT32(sizeof(buffer), buffer_size);

    retcode = gnss_pvt_serialize(&gnss_pvt, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, retcode);
    retcode = gnss_pvt_serialize(&gnss_pvt, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(buffer_size, retcode);

    struct GnssPvt actual_gnss_pvt;
    gnss_pvt_init(&actual_gnss_pvt);
    retcode = gnss_pvt_deserialize(&actual_gnss_pvt, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, retcode);
    retcode = gnss_pvt_deserialize(&actual_gnss_pvt, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(buffer_size, retcode);

    /// Check the result
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, gnss_pvt_get_timestamp(&actual_gnss_pvt)));
    TEST_ASSERT_EQUAL_UINT32(coordinate_wgs84_create(), gnss_pvt_get_coordinate(&actual_gnss_pvt));
    TEST_ASSERT_TRUE(gnss_pvt_is_position_valid(&actual_gnss_pvt));
    TEST_ASSERT_TRUE(gnss_pvt_is_velocity_valid(&actual_gnss_pvt));
    TEST_ASSERT_TRUE(gnss_pvt_is_position_cov_valid(&actual_gnss_pvt));
    TEST_ASSERT_TRUE(gnss_pvt_is_velocity_cov_valid(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_UINT32(GNSS_PVT_MODE_RTK_FLOAT_FIX, gnss_pvt_get_mode(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(1.1, gnss_pvt_get_longitude(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(2.2, gnss_pvt_get_latitude(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(3.3, gnss_pvt_get_height(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(4.4, gnss_pvt_get_velocity_east(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(5.5, gnss_pvt_get_velocity_north(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(6.6, gnss_pvt_get_velocity_up(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(7.7, gnss_pvt_get_longitude_cov(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(8.8, gnss_pvt_get_latitude_cov(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(9.9, gnss_pvt_get_height_cov(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(10.1, gnss_pvt_get_velocity_east_cov(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(11.2, gnss_pvt_get_velocity_north_cov(&actual_gnss_pvt));
    TEST_ASSERT_EQUAL_DOUBLE(12.3, gnss_pvt_get_velocity_up_cov(&actual_gnss_pvt));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_gnss_pvt_init);
    RUN_TEST(test_gnss_pvt_set_and_get_timestamp);
    RUN_TEST(test_gnss_pvt_set_and_get_coordinate);
    RUN_TEST(test_gnss_pvt_set_and_get_valid_flags);
    RUN_TEST(test_gnss_pvt_set_and_get_mode);
    RUN_TEST(test_gnss_pvt_set_and_get_longitude);
    RUN_TEST(test_gnss_pvt_set_and_get_latitude);
    RUN_TEST(test_gnss_pvt_set_and_get_height);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_east);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_north);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_up);
    RUN_TEST(test_gnss_pvt_set_and_get_longitude_cov);
    RUN_TEST(test_gnss_pvt_set_and_get_latitude_cov);
    RUN_TEST(test_gnss_pvt_set_and_get_height_cov);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_east_cov);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_north_cov);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_up_cov);
    RUN_TEST(test_gnss_pvt_set_and_get_position_by_values);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_by_values);
    RUN_TEST(test_gnss_pvt_set_and_get_position_cov_by_values);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_cov_by_values);
    RUN_TEST(test_gnss_pvt_set_and_get_position_with_point3d);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_with_point3d);
    RUN_TEST(test_gnss_pvt_set_and_get_velocity_cov_with_point3d);
    RUN_TEST(test_gnss_pvt_set_and_get_position_cov_with_point3d);
    RUN_TEST(test_gnss_pvt_serialize_and_deserialize);

    return UNITY_END();
}
