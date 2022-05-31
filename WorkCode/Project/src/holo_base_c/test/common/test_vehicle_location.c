/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_vehicle_location.h
 * @brief Unit test for vehicle_location object.
 * @author ZhangJiannan (zhangjiannan@holomatic.com)
 * @date 2019-12-10
 */

#include <holo_c/common/vehicle_location.h>
#include <holo_c/core/types.h>
#include <unity.h>

static void test_vehicle_location(void)
{
    VehicleLocation_t location = vehicle_location_create(VEHICLE_LOCATION_PLANE_UNKNOWN, 0, 0);
    TEST_ASSERT_EQUAL_UINT16(0U, location);
    TEST_ASSERT_EQUAL_UINT16(VEHICLE_LOCATION_PLANE_UNKNOWN, vehicle_location_get_plane(&location));
    TEST_ASSERT_EQUAL_UINT16(0U, vehicle_location_get_coordinate_x(&location));
    TEST_ASSERT_EQUAL_UINT16(0U, vehicle_location_get_coordinate_y(&location));

    location = vehicle_location_create(VEHICLE_LOCATION_PLANE_FRONT, 
            VEHICLE_LOCATION_COORDINATE_MIDDLE, VEHICLE_LOCATION_COORDINATE_TOP);
    TEST_ASSERT_EQUAL_UINT16(VEHICLE_LOCATION_PLANE_FRONT, vehicle_location_get_plane(&location));
    TEST_ASSERT_EQUAL_UINT16(VEHICLE_LOCATION_COORDINATE_MIDDLE, vehicle_location_get_coordinate_x(&location));
    TEST_ASSERT_EQUAL_UINT16(VEHICLE_LOCATION_COORDINATE_TOP, vehicle_location_get_coordinate_y(&location));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_vehicle_location);
    return UNITY_END();
}
