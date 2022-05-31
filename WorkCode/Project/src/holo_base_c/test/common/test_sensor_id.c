/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_sensor_id.h
 * @brief Unit test for sensor id object.
 * @author ZhangJiannan (zhangjiannan@holomatic.com)
 * @date 2019-12-10
 */

#include <holo_c/common/sensor_id.h>
#include <holo_c/core/types.h>
#include <unity.h>

static void test_sensor_id(void)
{
    SensorId_t id = sensor_id_create(SENSOR_CLASS_UNKNOWN, 
                                     SENSOR_MODEL_UNKNOWN, 
                                     vehicle_location_create(VEHICLE_LOCATION_PLANE_UNKNOWN, 0, 0));
    TEST_ASSERT_EQUAL_UINT32(0U, id);
    TEST_ASSERT_EQUAL_UINT32(SENSOR_CLASS_UNKNOWN, sensor_id_get_class(&id));
    TEST_ASSERT_EQUAL_UINT32(SENSOR_MODEL_UNKNOWN, sensor_id_get_model(&id));
    TEST_ASSERT_EQUAL_UINT32(
            vehicle_location_create(VEHICLE_LOCATION_PLANE_UNKNOWN, 0, 0), sensor_id_get_location(&id));

    id = sensor_id_create(SENSOR_CLASS_CAMERA, SENSOR_MODEL_CAMERA_UNKNOWN, 
                          vehicle_location_create(VEHICLE_LOCATION_PLANE_UNKNOWN, 0, 0));
    TEST_ASSERT_EQUAL_UINT32(SENSOR_CLASS_CAMERA, sensor_id_get_class(&id));
    TEST_ASSERT_EQUAL_UINT32(SENSOR_MODEL_CAMERA_UNKNOWN, sensor_id_get_model(&id));
    TEST_ASSERT_EQUAL_UINT32(
            vehicle_location_create(VEHICLE_LOCATION_PLANE_UNKNOWN, 0, 0), sensor_id_get_location(&id));


    id = sensor_id_create(SENSOR_CLASS_LIDAR, SENSOR_MODEL_LIDAR_IBEO_SCALAR, 
                          vehicle_location_create(VEHICLE_LOCATION_PLANE_FRONT, 
                              VEHICLE_LOCATION_COORDINATE_MIDDLE, 
                              VEHICLE_LOCATION_COORDINATE_BOTTOM));
    TEST_ASSERT_EQUAL_UINT32(SENSOR_CLASS_LIDAR, sensor_id_get_class(&id));
    TEST_ASSERT_EQUAL_UINT32(SENSOR_MODEL_LIDAR_IBEO_SCALAR, sensor_id_get_model(&id));
    TEST_ASSERT_EQUAL_UINT32(
            vehicle_location_create(VEHICLE_LOCATION_PLANE_FRONT, 
                VEHICLE_LOCATION_COORDINATE_MIDDLE, 
                VEHICLE_LOCATION_COORDINATE_BOTTOM), sensor_id_get_location(&id));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_sensor_id);
    return UNITY_END();
}
