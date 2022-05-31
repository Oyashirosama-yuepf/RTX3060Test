/*!
 * @brief Unit test for odometry float32_t.
 * @author lichao@holomatic.com
 * @date Sep 07, 2019
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */
#include <string.h>
#include <unity.h>

#include <holo_c/common/odometry_float32.h>
#include <holo_c/core/retcode.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_init(void)
{
    /* construct odometry float32_t */
    struct Odometryf actual_odometry;

    /* generate expected result */
    struct Timestamp expected_stamp;
    timestamp_init(&expected_stamp);
    const Coordinate_t expected_coordinate       = coordinate_default_create();
    const Coordinate_t expected_child_coordinate = coordinate_default_create();
    struct Pose3f      expected_pose;
    pose3f_init(&expected_pose);
    struct Vectorf expeceted_velocity;
    float32_t      expeceted_velocity_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&expeceted_velocity, 6, expeceted_velocity_buf, VECTORF_MIN_BUF_SIZE(6u));
    struct Matrixf expected_pose_covariance;
    float32_t      expected_pose_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    matrixf_init(&expected_pose_covariance, 6, 6, expected_pose_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_set_identity(&expected_pose_covariance);
    struct Matrixf expected_velocity_covariance;
    float32_t      expected_velocity_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    matrixf_init(&expected_velocity_covariance, 6, 6, expected_velocity_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_set_identity(&expected_velocity_covariance);
    const enum OdometryStatus expected_status = ODOMETRY_STATUS_ALLGOOD;
    const enum OdometrySource expected_source = ODOMETRY_SOURCE_UNKNOWN;

    /*test init functions*/
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, odometryf_init(&actual_odometry));
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, odometryf_get_timestamp(&actual_odometry)));
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, odometryf_get_coordinate(&actual_odometry));
    TEST_ASSERT_EQUAL_INT32(expected_child_coordinate, odometryf_get_child_coordinate(&actual_odometry));
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected_pose, odometryf_get_pose(&actual_odometry)));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expeceted_velocity, odometryf_get_velocity(&actual_odometry)));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected_pose_covariance, odometryf_get_pose_covariance(&actual_odometry)));
    TEST_ASSERT_TRUE(
        matrixf_is_equal(&expected_velocity_covariance, odometryf_get_velocity_covariance(&actual_odometry)));
    TEST_ASSERT_EQUAL_INT32(expected_status, odometryf_get_status(&actual_odometry));
    TEST_ASSERT_EQUAL_INT32(expected_source, odometryf_get_source(&actual_odometry));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_init_from_odometryf(void)
{
    /// Step 1: Generate expected result
    struct Timestamp expected_stamp;
    timestamp_init_from_sec(&expected_stamp, 20.1f);
    const Coordinate_t expected_coordinate       = coordinate_wgs84_create();
    const Coordinate_t expected_child_coordinate = coordinate_wgs84_create();

    struct Rot3f expected_rotation;
    rot3f_init(&expected_rotation);
    rot3f_from_rpy(&expected_rotation, 2.0f, 0.0f, 1.0f);
    struct Point3f expected_translation;
    point3f_init_from_scalars(&expected_translation, 1.0f, 2.0f, 3.0f);
    struct Pose3f expected_pose;
    pose3f_init_from_rot3f_and_point3f(&expected_pose, &expected_rotation, &expected_translation);

    struct Vectorf expeceted_velocity;
    float32_t      expeceted_velocity_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&expeceted_velocity, 6u, expeceted_velocity_buf, VECTORF_MIN_BUF_SIZE(6u));
    vectorf_set_ones(&expeceted_velocity);

    struct Matrixf expected_pose_covariance;
    float32_t      expected_pose_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    matrixf_init(&expected_pose_covariance, 6u, 6u, expected_pose_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_set_ones(&expected_pose_covariance);

    struct Matrixf expected_velocity_covariance;
    float32_t      expected_velocity_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    matrixf_init(&expected_velocity_covariance, 6u, 6u, expected_velocity_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_set_ones(&expected_velocity_covariance);

    struct Vectorf expected_linear_acceleration;
    float32_t      expected_linear_acceleration_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_linear_acceleration, 3u, expected_linear_acceleration_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set_ones(&expected_linear_acceleration);

    const enum OdometryStatus expected_status = ODOMETRY_STATUS_ANGULARVELOCITYINACTIVE;
    const enum OdometrySource expected_source = ODOMETRY_SOURCE_HD_MAP;

    /// Step 2: Construct the expected odometry
    struct Odometryf expected_odometry;
    odometryf_init(&expected_odometry);

    odometryf_set_status(&expected_odometry, expected_status);
    odometryf_set_source(&expected_odometry, expected_source);
    odometryf_set_timestamp(&expected_odometry, &expected_stamp);
    odometryf_set_pose(&expected_odometry, &expected_pose);
    odometryf_set_coordinate(&expected_odometry, expected_coordinate);
    odometryf_set_child_coordinate(&expected_odometry, expected_child_coordinate);
    odometryf_set_velocity(&expected_odometry, &expeceted_velocity);
    odometryf_set_pose_covariance(&expected_odometry, &expected_pose_covariance);
    odometryf_set_velocity_covariance(&expected_odometry, &expected_velocity_covariance);
    odometryf_set_linear_acceleration(&expected_odometry, &expected_linear_acceleration);

    /// Step 3: Construct the actual odoemtryf and init it from other odometry
    struct Odometryf actual_odometry;
    retcode_t        rc = odometryf_init_from_odometryf(&actual_odometry, &expected_odometry);

    /// Step 4: Check all the member
    TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, odometryf_get_timestamp(&actual_odometry)));
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, odometryf_get_coordinate(&actual_odometry));
    TEST_ASSERT_EQUAL_INT32(expected_child_coordinate, odometryf_get_child_coordinate(&actual_odometry));
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected_pose, odometryf_get_pose(&actual_odometry)));
    TEST_ASSERT_TRUE(vectorf_is_equal(&expeceted_velocity, odometryf_get_velocity(&actual_odometry)));
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected_pose_covariance, odometryf_get_pose_covariance(&actual_odometry)));
    TEST_ASSERT_TRUE(
        matrixf_is_equal(&expected_velocity_covariance, odometryf_get_velocity_covariance(&actual_odometry)));
    TEST_ASSERT_EQUAL_INT32(expected_status, odometryf_get_status(&actual_odometry));
    TEST_ASSERT_EQUAL_INT32(expected_source, odometryf_get_source(&actual_odometry));
    TEST_ASSERT_TRUE(
        vectorf_is_equal(&expected_linear_acceleration, odometryf_get_linear_acceleration(&actual_odometry)));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_timestamp(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected timestamp */
    struct Timestamp expected_stamp;
    timestamp_init_from_sec(&expected_stamp, 4.6f);

    /* test get stamp function */
    odometryf_set_timestamp(&odometry, &expected_stamp);
    TEST_ASSERT_TRUE(timestamp_is_equal(&expected_stamp, odometryf_get_timestamp(&odometry)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_coordinate(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected coordinate */
    const Coordinate_t expected_coordinate = coordinate_utm6_create(50, false, 0U, 0U);

    /* test get coordinate function */
    odometryf_set_coordinate(&odometry, expected_coordinate);
    TEST_ASSERT_EQUAL_INT32(expected_coordinate, odometryf_get_coordinate(&odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_child_coordinate(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected coordinate */
    const Coordinate_t expected_child_coordinate = coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER);

    /* test get coordinte function */
    odometryf_set_child_coordinate(&odometry, expected_child_coordinate);
    TEST_ASSERT_EQUAL_INT32(expected_child_coordinate, odometryf_get_child_coordinate(&odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_pose(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected Pose3f */
    struct Pose3f expected_pose;
    pose3f_init(&expected_pose);

    /* test get pose function */
    odometryf_set_pose(&odometry, &expected_pose);
    TEST_ASSERT_TRUE(pose3f_is_equal(&expected_pose, odometryf_get_pose(&odometry)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_velocity(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected Vector6f */
    struct Vectorf expected_velocity;
    float32_t      expected_velocity_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&expected_velocity, 6, expected_velocity_buf, VECTORF_MIN_BUF_SIZE(6u));

    /* test get velocity function */
    odometryf_set_velocity(&odometry, &expected_velocity);
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_velocity, odometryf_get_velocity(&odometry)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_pose_covariance(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected pose covariance */
    struct Matrixf expected_pose_covariance;
    float32_t      expected_pose_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    matrixf_init(&expected_pose_covariance, 6, 6, expected_pose_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));

    /* test get pose covariance function */
    odometryf_set_pose_covariance(&odometry, &expected_pose_covariance);
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected_pose_covariance, odometryf_get_pose_covariance(&odometry)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_velocity_covariance(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected velocity covariance */
    struct Matrixf expected_velocity_covariance;
    float32_t      expected_velocity_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    matrixf_init(&expected_velocity_covariance, 6, 6, expected_velocity_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));

    /* test get velocity covariance function */
    odometryf_set_velocity_covariance(&odometry, &expected_velocity_covariance);
    TEST_ASSERT_TRUE(matrixf_is_equal(&expected_velocity_covariance, odometryf_get_velocity_covariance(&odometry)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_linear_acceleration(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected Vector3f */
    struct Vectorf expected_linear_acceleration;
    float32_t      expected_linear_acceleration_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_linear_acceleration, 3, expected_linear_acceleration_buf, VECTORF_MIN_BUF_SIZE(3u));

    /* test set and get linear acceleration function */
    odometryf_set_linear_acceleration(&odometry, &expected_linear_acceleration);
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_linear_acceleration, odometryf_get_linear_acceleration(&odometry)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_status(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected status */
    const enum OdometryStatus expected_status = ODOMETRY_STATUS_ORIENTATIONINACTIVE;

    /* test get status function */
    odometryf_set_status(&odometry, expected_status);
    TEST_ASSERT_EQUAL_INT32(expected_status, odometryf_get_status(&odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_set_and_get_source(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate expected source */
    const enum OdometrySource expected_source = ODOMETRY_SOURCE_SEMANTIC;

    /* test get status function */
    odometryf_set_source(&odometry, expected_source);
    TEST_ASSERT_EQUAL_UINT32(expected_source, expected_source);
    TEST_ASSERT_EQUAL_UINT32(expected_source, odometryf_get_source(&odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_get_translation(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate Pose3f */
    struct Rot3f rot;
    rot3f_init(&rot);
    rot3f_from_rpy(&rot, 0.1f, -0.2f, 0.3f);

    struct Point3f expected_point;
    point3f_init_from_scalars(&expected_point, -0.4f, 0.5f, -0.6f);

    struct Pose3f pose;
    pose3f_init_from_rot3f_and_point3f(&pose, &rot, &expected_point);

    /* test get translation function */
    odometryf_set_pose(&odometry, &pose);
    TEST_ASSERT_TRUE(point3f_is_equal(&expected_point, odometryf_get_translation(&odometry)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_get_yaw(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate Pose3f */
    const float32_t expected_yaw = 0.3f;
    struct Rot3f    rot;
    rot3f_init(&rot);
    rot3f_from_rpy(&rot, 0.1f, -0.2f, expected_yaw);

    struct Point3f point;
    point3f_init_from_scalars(&point, -0.4f, 0.5f, -0.6f);

    struct Pose3f pose;
    pose3f_init_from_rot3f_and_point3f(&pose, &rot, &point);

    /* test get translation function */
    odometryf_set_pose(&odometry, &pose);
    TEST_ASSERT_EQUAL_FLOAT(expected_yaw, odometryf_get_yaw(&odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_get_linear_velocity_in_child_coord_orientation(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate Vector6f */
    struct Vectorf velocity;
    float32_t      velocity_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&velocity, 6u, velocity_buf, VECTORF_MIN_BUF_SIZE(6u));

    /* generate expected linear velocity in child coord orientation */
    struct Vectorf expected_linear_velocity;
    float32_t      expected_linear_velocity_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&expected_linear_velocity, 3u, expected_linear_velocity_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&expected_linear_velocity, 0u, 2.1f);
    vectorf_set(&expected_linear_velocity, 1u, 3.1f);
    vectorf_set(&expected_linear_velocity, 2u, 1.1f);
    vectorf_set_segment(&velocity, 0u, 3u, &expected_linear_velocity);

    /* test get linear velocity child coord orientation function */
    odometryf_set_velocity(&odometry, &velocity);
    struct Vectorf linear_vel;
    float32_t      linear_vel_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&linear_vel, 3u, linear_vel_buf, VECTORF_MIN_BUF_SIZE(3u));
    odometryf_get_linear_velocity_in_child_coord_orientation(&odometry, &linear_vel);
    TEST_ASSERT_TRUE(vectorf_is_equal(&expected_linear_velocity, &linear_vel));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_get_x_velocity_in_child_coord_orientation(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate Vector6f */
    struct Vectorf velocity;
    float32_t      velocity_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&velocity, 6u, velocity_buf, VECTORF_MIN_BUF_SIZE(6u));

    /* generate expected x velocity in child coord orientation frame */
    const float32_t expected_vel_x = 2.1f;
    struct Vectorf  linear_velocity;
    float32_t       linear_velocity_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&linear_velocity, 3u, linear_velocity_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&linear_velocity, 0u, expected_vel_x);
    vectorf_set(&linear_velocity, 1u, 3.1f);
    vectorf_set(&linear_velocity, 2u, 1.1f);
    vectorf_set_segment(&velocity, 0u, 3u, &linear_velocity);

    /* test get x velocity child coord orientation function */
    odometryf_set_velocity(&odometry, &velocity);
    TEST_ASSERT_TRUE(expected_vel_x == odometryf_get_x_velocity_in_child_coord_orientation(&odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_odometryf_get_y_velocity_in_child_coord_orientation(void)
{
    /* construct Odometryf */
    struct Odometryf odometry;
    odometryf_init(&odometry);

    /* generate Vector6f */
    struct Vectorf velocity;
    float32_t      velocity_buf[VECTORF_MIN_BUF_SIZE(6u)];
    vectorf_init(&velocity, 6u, velocity_buf, VECTORF_MIN_BUF_SIZE(6u));

    /* generate expected y velocity in child coord orientation frame */
    const float32_t expected_vel_y = 3.1f;
    struct Vectorf  linear_velocity;
    float32_t       linear_velocity_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&linear_velocity, 3u, linear_velocity_buf, VECTORF_MIN_BUF_SIZE(3u));
    vectorf_set(&linear_velocity, 0u, 2.1f);
    vectorf_set(&linear_velocity, 1u, expected_vel_y);
    vectorf_set(&linear_velocity, 2u, 1.1f);
    vectorf_set_segment(&velocity, 0u, 3u, &linear_velocity);

    /* test get y velocity child coord orientation function */
    odometryf_set_velocity(&odometry, &velocity);
    TEST_ASSERT_TRUE(expected_vel_y == odometryf_get_y_velocity_in_child_coord_orientation(&odometry));
}

void test_odometryf_serialize_and_deserialize_4byte_aligned(void)
{
    uint8_t          i, j;
    const uint16_t   buf_size       = 400;
    const uint16_t   error_buf_size = 300;
    uint8_t          odometry_buf[400];
    float32_t        velocity_buf[VECTORF_MIN_BUF_SIZE(6u)];
    float32_t        pose_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    float32_t        velocity_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    float32_t        linear_acceleration_buf[VECTORF_MIN_BUF_SIZE(3u)];
    float32_t        tmp_value;
    struct Timestamp timestamp;
    struct Pose3f    pose;
    struct Vectorf   velocity;
    struct Matrixf   pose_covariance;
    struct Matrixf   velocity_covariance;
    struct Vectorf   linear_acceleration;
    struct Odometryf odometry;
    struct Odometryf deserialized_odometry;

    memset(odometry_buf, 0, buf_size);
    timestamp_init_from_sec(&timestamp, 4.6f);
    pose3f_init(&pose);
    vectorf_init(&velocity, 6, velocity_buf, VECTORF_MIN_BUF_SIZE(6u));
    matrixf_init(&pose_covariance, 6, 6, pose_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_init(&velocity_covariance, 6, 6, velocity_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    vectorf_init(&linear_acceleration, 3, linear_acceleration_buf, VECTORF_MIN_BUF_SIZE(3u));
    odometryf_init(&odometry);
    odometryf_init(&deserialized_odometry);

    odometryf_set_timestamp(&odometry, &timestamp);
    odometryf_set_coordinate(&odometry, coordinate_utm6_create(50, false, 0u, 0u));
    odometryf_set_child_coordinate(&odometry, coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER));
    odometryf_set_source(&odometry, ODOMETRY_SOURCE_SEMANTIC);
    odometryf_set_status(&odometry, ODOMETRY_STATUS_ORIENTATIONINACTIVE);

    odometryf_set_pose(&odometry, &pose);
    odometryf_set_velocity(&odometry, &velocity);
    odometryf_set_pose_covariance(&odometry, &pose_covariance);
    odometryf_set_velocity_covariance(&odometry, &velocity_covariance);
    odometryf_set_linear_acceleration(&odometry, &linear_acceleration);

    vectorf_set(&velocity, 0u, 1.1f);
    vectorf_set(&velocity, 1u, -2.2f);
    vectorf_set(&velocity, 2u, 3.3f);
    vectorf_set(&velocity, 3u, -0.3f);
    vectorf_set(&velocity, 4u, 4.4f);
    vectorf_set(&velocity, 5u, -6.6f);

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_set(&velocity_covariance, i, j, 2.2f * i / 0.7f * j + 1.3f);
        }
    }

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_set(&pose_covariance, i, j, 0.3f * i / 1.4f * j + 0.1f);
        }
    }

    vectorf_set(&linear_acceleration, 0u, 3.1f);
    vectorf_set(&linear_acceleration, 1u, -2.78f);
    vectorf_set(&linear_acceleration, 2u, 0.335f);

    odometryf_set_timestamp(&odometry, &timestamp);
    odometryf_set_coordinate(&odometry, coordinate_utm6_create(50, false, 0u, 0u));
    odometryf_set_child_coordinate(&odometry, coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER));
    odometryf_set_source(&odometry, ODOMETRY_SOURCE_SEMANTIC);
    odometryf_set_status(&odometry, ODOMETRY_STATUS_ORIENTATIONINACTIVE);

    odometryf_set_pose(&odometry, &pose);

    odometryf_set_velocity(&odometry, &velocity);
    odometryf_set_pose_covariance(&odometry, &pose_covariance);
    odometryf_set_velocity_covariance(&odometry, &velocity_covariance);
    odometryf_set_linear_acceleration(&odometry, &linear_acceleration);

    TEST_ASSERT_EQUAL_UINT64(396, odometryf_get_serialized_size_4byte_aligned(&odometry));
    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             odometryf_serialize_4byte_aligned(&odometry, odometry_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(396, odometryf_serialize_4byte_aligned(&odometry, odometry_buf, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             odometryf_deserialize_4byte_aligned(&deserialized_odometry, odometry_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(396, odometryf_deserialize_4byte_aligned(&deserialized_odometry, odometry_buf, buf_size));

    vectorf_get(&deserialized_odometry.velocity, 0, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(1.1f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 1, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-2.2f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 2, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(3.3f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 3, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-0.3f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 4, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(4.4f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 5, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-6.6f, tmp_value);

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_get(&deserialized_odometry.velocity_covariance, i, j, &tmp_value);
            TEST_ASSERT_EQUAL_FLOAT(2.2f * i / 0.7f * j + 1.3f, tmp_value);
        }
    }

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_get(&deserialized_odometry.pose_covariance, i, j, &tmp_value);
            TEST_ASSERT_EQUAL_FLOAT(0.3f * i / 1.4f * j + 0.1f, tmp_value);
        }
    }

    vectorf_get(&deserialized_odometry.linear_acceleration, 0u, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(3.1f, tmp_value);
    vectorf_get(&deserialized_odometry.linear_acceleration, 1u, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-2.78f, tmp_value);
    vectorf_get(&deserialized_odometry.linear_acceleration, 2u, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(0.335f, tmp_value);
}

void test_odometryf_serialize_and_deserialize_8byte_aligned(void)
{
    uint8_t          i, j;
    const uint16_t   buf_size       = 400;
    const uint16_t   error_buf_size = 300;
    uint8_t          odometry_buf[400];
    float32_t        velocity_buf[VECTORF_MIN_BUF_SIZE(6u)];
    float32_t        pose_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    float32_t        velocity_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    float32_t        linear_acceleration_buf[VECTORF_MIN_BUF_SIZE(3u)];
    float32_t        tmp_value;
    struct Timestamp timestamp;
    struct Pose3f    pose;
    struct Vectorf   velocity;
    struct Matrixf   pose_covariance;
    struct Matrixf   velocity_covariance;
    struct Vectorf   linear_acceleration;
    struct Odometryf odometry;
    struct Odometryf deserialized_odometry;

    memset(odometry_buf, 0, buf_size);
    timestamp_init_from_sec(&timestamp, 4.6f);
    pose3f_init(&pose);
    vectorf_init(&velocity, 6, velocity_buf, VECTORF_MIN_BUF_SIZE(6u));
    matrixf_init(&pose_covariance, 6, 6, pose_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_init(&velocity_covariance, 6, 6, velocity_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    vectorf_init(&linear_acceleration, 3, linear_acceleration_buf, VECTORF_MIN_BUF_SIZE(3u));
    odometryf_init(&odometry);
    odometryf_init(&deserialized_odometry);

    vectorf_set(&velocity, 0u, 1.1f);
    vectorf_set(&velocity, 1u, -2.2f);
    vectorf_set(&velocity, 2u, 3.3f);
    vectorf_set(&velocity, 3u, -0.3f);
    vectorf_set(&velocity, 4u, 4.4f);
    vectorf_set(&velocity, 5u, -6.6f);

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_set(&velocity_covariance, i, j, 2.2f * i / 0.7f * j + 1.3f);
        }
    }

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_set(&pose_covariance, i, j, 0.3f * i / 1.4f * j + 0.1f);
        }
    }

    vectorf_set(&linear_acceleration, 0u, 3.1f);
    vectorf_set(&linear_acceleration, 1u, -2.78f);
    vectorf_set(&linear_acceleration, 2u, 0.335f);

    odometryf_set_timestamp(&odometry, &timestamp);
    odometryf_set_coordinate(&odometry, coordinate_utm6_create(50, false, 0u, 0u));
    odometryf_set_child_coordinate(&odometry, coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER));
    odometryf_set_source(&odometry, ODOMETRY_SOURCE_SEMANTIC);
    odometryf_set_status(&odometry, ODOMETRY_STATUS_ORIENTATIONINACTIVE);

    odometryf_set_pose(&odometry, &pose);

    odometryf_set_velocity(&odometry, &velocity);
    odometryf_set_pose_covariance(&odometry, &pose_covariance);
    odometryf_set_velocity_covariance(&odometry, &velocity_covariance);
    odometryf_set_linear_acceleration(&odometry, &linear_acceleration);

    TEST_ASSERT_EQUAL_UINT64(400, odometryf_get_serialized_size_8byte_aligned(&odometry));
    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             odometryf_serialize_8byte_aligned(&odometry, odometry_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(400, odometryf_serialize_8byte_aligned(&odometry, odometry_buf, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             odometryf_deserialize_8byte_aligned(&deserialized_odometry, odometry_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(400, odometryf_deserialize_8byte_aligned(&deserialized_odometry, odometry_buf, buf_size));

    vectorf_get(&deserialized_odometry.velocity, 0, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(1.1f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 1, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-2.2f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 2, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(3.3f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 3, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-0.3f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 4, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(4.4f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 5, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-6.6f, tmp_value);

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_get(&deserialized_odometry.velocity_covariance, i, j, &tmp_value);
            TEST_ASSERT_EQUAL_FLOAT(2.2f * i / 0.7f * j + 1.3f, tmp_value);
        }
    }

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_get(&deserialized_odometry.pose_covariance, i, j, &tmp_value);
            TEST_ASSERT_EQUAL_FLOAT(0.3f * i / 1.4f * j + 0.1f, tmp_value);
        }
    }

    vectorf_get(&deserialized_odometry.linear_acceleration, 0u, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(3.1f, tmp_value);
    vectorf_get(&deserialized_odometry.linear_acceleration, 1u, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-2.78f, tmp_value);
    vectorf_get(&deserialized_odometry.linear_acceleration, 2u, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(0.335f, tmp_value);
}

void test_odometryf_serialize_and_deserialize_default(void)
{
    uint8_t          i, j;
    const uint16_t   buf_size       = 400;
    const uint16_t   error_buf_size = 300;
    uint8_t          odometry_buf[400];
    float32_t        velocity_buf[VECTORF_MIN_BUF_SIZE(6u)];
    float32_t        pose_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    float32_t        velocity_covariance_buf[MATRIXF_MIN_BUF_SIZE(6u, 6u)];
    float32_t        linear_acceleration_buf[VECTORF_MIN_BUF_SIZE(3u)];
    float32_t        tmp_value;
    struct Timestamp timestamp;
    struct Pose3f    pose;
    struct Vectorf   velocity;
    struct Matrixf   pose_covariance;
    struct Matrixf   velocity_covariance;
    struct Vectorf   linear_acceleration;
    struct Odometryf odometry;
    struct Odometryf deserialized_odometry;

    memset(odometry_buf, 0, buf_size);
    timestamp_init_from_sec(&timestamp, 4.6f);
    pose3f_init(&pose);
    vectorf_init(&velocity, 6, velocity_buf, VECTORF_MIN_BUF_SIZE(6u));
    matrixf_init(&pose_covariance, 6, 6, pose_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    matrixf_init(&velocity_covariance, 6, 6, velocity_covariance_buf, MATRIXF_MIN_BUF_SIZE(6u, 6u));
    vectorf_init(&linear_acceleration, 3, linear_acceleration_buf, VECTORF_MIN_BUF_SIZE(3u));
    odometryf_init(&odometry);
    odometryf_init(&deserialized_odometry);

    odometryf_set_timestamp(&odometry, &timestamp);
    odometryf_set_coordinate(&odometry, coordinate_utm6_create(50, false, 0u, 0u));
    odometryf_set_child_coordinate(&odometry, coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER));
    odometryf_set_source(&odometry, ODOMETRY_SOURCE_SEMANTIC);
    odometryf_set_status(&odometry, ODOMETRY_STATUS_ORIENTATIONINACTIVE);

    odometryf_set_pose(&odometry, &pose);
    odometryf_set_velocity(&odometry, &velocity);
    odometryf_set_pose_covariance(&odometry, &pose_covariance);
    odometryf_set_velocity_covariance(&odometry, &velocity_covariance);
    odometryf_set_linear_acceleration(&odometry, &linear_acceleration);

    vectorf_set(&velocity, 0u, 1.1f);
    vectorf_set(&velocity, 1u, -2.2f);
    vectorf_set(&velocity, 2u, 3.3f);
    vectorf_set(&velocity, 3u, -0.3f);
    vectorf_set(&velocity, 4u, 4.4f);
    vectorf_set(&velocity, 5u, -6.6f);

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_set(&velocity_covariance, i, j, 2.2f * i / 0.7f * j + 1.3f);
        }
    }

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_set(&pose_covariance, i, j, 0.3f * i / 1.4f * j + 0.1f);
        }
    }

    vectorf_set(&linear_acceleration, 0u, 3.1f);
    vectorf_set(&linear_acceleration, 1u, -2.78f);
    vectorf_set(&linear_acceleration, 2u, 0.335f);

    odometryf_set_timestamp(&odometry, &timestamp);
    odometryf_set_coordinate(&odometry, coordinate_utm6_create(50, false, 0u, 0u));
    odometryf_set_child_coordinate(&odometry, coordinate_vehicle_create(COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER));
    odometryf_set_source(&odometry, ODOMETRY_SOURCE_SEMANTIC);
    odometryf_set_status(&odometry, ODOMETRY_STATUS_ORIENTATIONINACTIVE);

    odometryf_set_pose(&odometry, &pose);

    odometryf_set_velocity(&odometry, &velocity);
    odometryf_set_pose_covariance(&odometry, &pose_covariance);
    odometryf_set_velocity_covariance(&odometry, &velocity_covariance);
    odometryf_set_linear_acceleration(&odometry, &linear_acceleration);

    TEST_ASSERT_EQUAL_UINT64(396, odometryf_get_serialized_size(&odometry));
    TEST_ASSERT_EQUAL_UINT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                             odometryf_serialize(&odometry, odometry_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(396, odometryf_serialize(&odometry, odometry_buf, buf_size));

    TEST_ASSERT_EQUAL_UINT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                             odometryf_deserialize(&deserialized_odometry, odometry_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT64(396, odometryf_deserialize(&deserialized_odometry, odometry_buf, buf_size));

    vectorf_get(&deserialized_odometry.velocity, 0, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(1.1f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 1, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-2.2f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 2, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(3.3f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 3, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-0.3f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 4, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(4.4f, tmp_value);
    vectorf_get(&deserialized_odometry.velocity, 5, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-6.6f, tmp_value);

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_get(&deserialized_odometry.velocity_covariance, i, j, &tmp_value);
            TEST_ASSERT_EQUAL_FLOAT(2.2f * i / 0.7f * j + 1.3f, tmp_value);
        }
    }

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            matrixf_get(&deserialized_odometry.pose_covariance, i, j, &tmp_value);
            TEST_ASSERT_EQUAL_FLOAT(0.3f * i / 1.4f * j + 0.1f, tmp_value);
        }
    }

    vectorf_get(&deserialized_odometry.linear_acceleration, 0u, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(3.1f, tmp_value);
    vectorf_get(&deserialized_odometry.linear_acceleration, 1u, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(-2.78f, tmp_value);
    vectorf_get(&deserialized_odometry.linear_acceleration, 2u, &tmp_value);
    TEST_ASSERT_EQUAL_FLOAT(0.335f, tmp_value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_odometryf_init);
    RUN_TEST(test_odometryf_set_and_get_timestamp);
    RUN_TEST(test_odometryf_set_and_get_coordinate);
    RUN_TEST(test_odometryf_set_and_get_child_coordinate);
    RUN_TEST(test_odometryf_set_and_get_pose);
    RUN_TEST(test_odometryf_set_and_get_velocity);
    RUN_TEST(test_odometryf_set_and_get_pose_covariance);
    RUN_TEST(test_odometryf_set_and_get_velocity_covariance);
    RUN_TEST(test_odometryf_set_and_get_linear_acceleration);
    RUN_TEST(test_odometryf_set_and_get_status);
    RUN_TEST(test_odometryf_set_and_get_source);
    RUN_TEST(test_odometryf_get_translation);
    RUN_TEST(test_odometryf_get_yaw);
    RUN_TEST(test_odometryf_get_linear_velocity_in_child_coord_orientation);
    RUN_TEST(test_odometryf_get_x_velocity_in_child_coord_orientation);
    RUN_TEST(test_odometryf_get_y_velocity_in_child_coord_orientation);
    RUN_TEST(test_odometryf_serialize_and_deserialize_4byte_aligned);
    RUN_TEST(test_odometryf_serialize_and_deserialize_8byte_aligned);
    RUN_TEST(test_odometryf_serialize_and_deserialize_default);
    RUN_TEST(test_odometryf_init_from_odometryf);

    return UNITY_END();
}
