/*!
 * @brief Unit test for extrinsic float32_t.
 * @author lichao@holomatic.com
 * @date Sep 03, 2019
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <unity.h>

#include <holo_c/common/extrinsic_float32.h>
#include <holo_c/core/retcode.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_extrinsicf_init(void)
{
    /* construct extrinsic float32_t */
    struct Extrinsicf actual_extrinsic;
    /* generate expected result */
    const Coordinate_t expected_parent_coordinate = coordinate_default_create();
    const Coordinate_t expected_child_coordinate  = coordinate_default_create();
    struct Pose3f    expected_pose;
    pose3f_init(&expected_pose);
    /*test init functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, extrinsicf_init(&actual_extrinsic));
    TEST_ASSERT_EQUAL_INT32(expected_parent_coordinate, extrinsicf_get_parent_coordinate(&actual_extrinsic));
    TEST_ASSERT_EQUAL_INT32(expected_child_coordinate, extrinsicf_get_child_coordinate(&actual_extrinsic));
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected_pose, extrinsicf_get_pose(&actual_extrinsic)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_extrinsicf_set_and_get_parent_coordinate(void)
{
    /* construct extrinsic float32_t */
    struct Extrinsicf extrinsic;
    extrinsicf_init(&extrinsic);

    /* generate expected result */
    const Coordinate_t expected_parent_coordinate = coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_IMU_VEHICLE);

    /*test set and get parent coordinate functions*/
    extrinsicf_set_parent_coordinate(&extrinsic, expected_parent_coordinate);
    TEST_ASSERT_TRUE(expected_parent_coordinate == extrinsicf_get_parent_coordinate(&extrinsic));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_extrinsicf_set_and_get_child_coordinate(void)
{
    /* construct extrinsic float32_t */
    struct Extrinsicf extrinsic;
    extrinsicf_init(&extrinsic);

    /* generate expected result */
    const Coordinate_t expected_child_coordinate = 
        coordinate_vehicle_create(sensor_id_create(SENSOR_CLASS_CAMERA, 0x00, 
                                                   vehicle_location_create(VEHICLE_LOCATION_PLANE_FRONT_WINDOW,
                                                                           VEHICLE_LOCATION_COORDINATE_LEFT,
                                                                           VEHICLE_LOCATION_COORDINATE_TOP_MOST)
                                                   )
                                 );

    /*test set and get child coordinate functions*/
    extrinsicf_set_child_coordinate(&extrinsic, expected_child_coordinate);
    TEST_ASSERT_TRUE(expected_child_coordinate == extrinsicf_get_child_coordinate(&extrinsic));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_extrinsicf_set_and_get_pose(void)
{
    /* construct extrinsic float32_t */
    struct Extrinsicf extrinsic;
    extrinsicf_init(&extrinsic);

    /* generate expected result */
    struct Pose3f expected_pose;
    pose3f_init(&expected_pose);

    /*test set and get pose functions*/
    extrinsicf_set_pose(&extrinsic, &expected_pose);
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected_pose, extrinsicf_get_pose(&extrinsic)));
}

static void test_extrinsicf_serialize_deserialize(void)
{
    struct Extrinsicf extrinsic;
    uint32_t expected_size;
    retcode_t retcode;
    uint8_t buffer[512];
    extrinsicf_init(&extrinsic);

    expected_size = extrinsicf_get_serialized_size(&extrinsic);
    retcode = extrinsicf_serialize(&extrinsic, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, retcode);
    retcode = extrinsicf_deserialize(&extrinsic, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, retcode);

    retcode = extrinsicf_serialize(&extrinsic, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_INT32(expected_size, retcode);
    retcode = extrinsicf_deserialize(&extrinsic, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_INT32(expected_size, retcode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_extrinsicf_init);
    RUN_TEST(test_extrinsicf_set_and_get_parent_coordinate);
    RUN_TEST(test_extrinsicf_set_and_get_child_coordinate);
    RUN_TEST(test_extrinsicf_set_and_get_pose);
    RUN_TEST(test_extrinsicf_serialize_deserialize);
    return UNITY_END();
}
