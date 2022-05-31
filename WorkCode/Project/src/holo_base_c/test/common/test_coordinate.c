/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file coordinate.h
 * @brief This header file defines coordinate system.
 * @author ZhangJiannan (zhangjiannan@holomatic.com)
 * @date 2019-11-26
 */

#include <holo_c/common/coordinate.h>
#include <holo_c/core/types.h>
#include <holo_c/core/retcode.h>
#include <unity.h>


static void test_coordinate_default_create(void)
{
    Coordinate_t coordinate = coordinate_default_create();
    TEST_ASSERT_EQUAL_UINT32(COORDINATE_TYPE_UNKNOWN, coordinate_get_type(&coordinate));
    TEST_ASSERT_EQUAL_UINT32(0U, coordinate_get_param(&coordinate));
}

static void test_coordinate_vehicle_create(void)
{
    Coordinate_t coordinate = coordinate_vehicle_create(0U);
    TEST_ASSERT_EQUAL_UINT32(COORDINATE_TYPE_VEHICLE, coordinate_get_type(&coordinate));
    TEST_ASSERT_EQUAL_UINT32(0U, coordinate_get_param(&coordinate));
}

static void test_coordinate_wgs84_create(void)
{
    Coordinate_t coordinate = coordinate_wgs84_create();
    TEST_ASSERT_EQUAL_UINT32(COORDINATE_TYPE_WGS84, coordinate_get_type(&coordinate));
    TEST_ASSERT_EQUAL_UINT32(0U, coordinate_get_param(&coordinate));
}

static void test_coordinate_utm6_create(void)
{
    Coordinate_t coordinate = coordinate_utm6_create(0, false, 0, 0);
    TEST_ASSERT_EQUAL_UINT32(COORDINATE_TYPE_UTM6, coordinate_get_type(&coordinate));
    TEST_ASSERT_EQUAL_UINT32(0U, coordinate_get_param(&coordinate));
}

static void test_coordinate_utm3_create(void)
{
    Coordinate_t coordinate = coordinate_utm3_create(0, false, 0, 0);
    TEST_ASSERT_EQUAL_UINT32(COORDINATE_TYPE_UTM3, coordinate_get_type(&coordinate));
    TEST_ASSERT_EQUAL_UINT32(0U, coordinate_get_param(&coordinate));
}

static void test_coordinate_dr_create(void)
{
    Coordinate_t coordinate = coordinate_dr_create(0);
    TEST_ASSERT_EQUAL_UINT32(COORDINATE_TYPE_DR, coordinate_get_type(&coordinate));
    TEST_ASSERT_EQUAL_UINT32(0U, coordinate_dr_get_version(&coordinate));
}

static void test_coordinate_set_get_type(void)
{
    Coordinate_t coordinate = coordinate_default_create();
    coordinate_set_type(&coordinate, COORDINATE_TYPE_UTM6);
    TEST_ASSERT_EQUAL_UINT32(COORDINATE_TYPE_UTM6, coordinate_get_type(&coordinate));
}

static void test_coordinate_set_get_param(void)
{
    Coordinate_t coordinate = coordinate_default_create();
    coordinate_set_param(&coordinate, 0x12345678);
    TEST_ASSERT_EQUAL_UINT32(0x02345678, coordinate_get_param(&coordinate));
}

static void test_coordinate_vehicle_set_get_sensor_id()
{
    Coordinate_t coordinate = coordinate_vehicle_create(0U);
    SensorId_t sensor_id = sensor_id_create(SENSOR_CLASS_IMU, SENSOR_MODEL_IMU_NOVATEL, 
                                            vehicle_location_create(VEHICLE_LOCATION_PLANE_TRUNK, 
                                                                    VEHICLE_LOCATION_COORDINATE_CENTER, 
                                                                    VEHICLE_LOCATION_COORDINATE_CENTER));
    coordinate_vehicle_set_sensor_id(&coordinate, sensor_id);
    TEST_ASSERT_EQUAL_UINT32(sensor_id, coordinate_get_param(&coordinate));
    TEST_ASSERT_EQUAL_UINT32(sensor_id, coordinate_vehicle_get_sensor_id(&coordinate));
}

static void test_coordinate_utm_set_get_zone(void)
{
    Coordinate_t coordinate = coordinate_utm6_create(0, false, 0, 0);
    coordinate_utm_set_zone(&coordinate, 50);
    TEST_ASSERT_EQUAL_UINT32(50, coordinate_utm_get_zone(&coordinate));

    coordinate_utm_set_zone(&coordinate, 60);
    TEST_ASSERT_EQUAL_UINT32(60, coordinate_utm_get_zone(&coordinate));

    coordinate = coordinate_utm3_create(0, false, 0, 0);
    coordinate_utm_set_zone(&coordinate, 1);
    TEST_ASSERT_EQUAL_UINT32(1, coordinate_utm_get_zone(&coordinate));

    coordinate_utm_set_zone(&coordinate, 120);
    TEST_ASSERT_EQUAL_UINT32(120, coordinate_utm_get_zone(&coordinate));
}

static void test_coordinate_utm_set_reset_south_flag(void)
{
    Coordinate_t coordinate = coordinate_utm6_create(0, false, 0, 0);
    coordinate_utm_set_south_flag(&coordinate);
    TEST_ASSERT_TRUE(coordinate_utm_get_south_flag(&coordinate));
    coordinate_utm_reset_south_flag(&coordinate);
    TEST_ASSERT_FALSE(coordinate_utm_get_south_flag(&coordinate));
}

static void test_coordinate_utm_set_get_offset_x(void)
{
    Coordinate_t coordinate = coordinate_utm6_create(0, false, 0, 0);
    coordinate_utm_set_offset_x(&coordinate, 50);
    TEST_ASSERT_EQUAL_UINT32(50, coordinate_utm_get_offset_x(&coordinate));
}

static void test_coordinate_utm_set_get_offset_y(void)
{
    Coordinate_t coordinate = coordinate_utm6_create(0, false, 0, 0);
    coordinate_utm_set_offset_y(&coordinate, 50);
    TEST_ASSERT_EQUAL_UINT32(50, coordinate_utm_get_offset_y(&coordinate));
}

static void test_coordinate_dr_set_get_version(void)
{
    Coordinate_t coordinate = coordinate_dr_create(0);
    coordinate_dr_set_version(&coordinate, 100U);
    TEST_ASSERT_EQUAL_UINT32(100U, coordinate_dr_get_version(&coordinate));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_coordinate_default_create);
    RUN_TEST(test_coordinate_vehicle_create);
    RUN_TEST(test_coordinate_wgs84_create);
    RUN_TEST(test_coordinate_utm6_create);
    RUN_TEST(test_coordinate_utm3_create);
    RUN_TEST(test_coordinate_dr_create);
    RUN_TEST(test_coordinate_set_get_type);
    RUN_TEST(test_coordinate_set_get_param);
    RUN_TEST(test_coordinate_vehicle_set_get_sensor_id);
    RUN_TEST(test_coordinate_utm_set_get_zone);
    RUN_TEST(test_coordinate_utm_set_reset_south_flag);
    RUN_TEST(test_coordinate_utm_set_get_offset_x);
    RUN_TEST(test_coordinate_utm_set_get_offset_y);
    RUN_TEST(test_coordinate_dr_set_get_version);
    return UNITY_END();
}

