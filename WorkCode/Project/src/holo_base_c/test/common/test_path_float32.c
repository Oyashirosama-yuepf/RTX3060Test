/**
 * @brief Unit test for path.
 * @author lijiawen@holomatic.com
 * @date 2019-09-27
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <unity.h>

#include <holo_c/common/path_float32.h>

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test void path_pointf_init_default(struct PathPointf* point);
 */
static void test_path_pointf_init(void)
{
    struct PathPointf pt;

    path_pointf_init_default(&pt);

    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.theta);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.curvature);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.speed);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.acceleration);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.distance);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.time);

    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.point.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.point.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, pt.point.z);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test void path_pointf_init_from_path_pointf(struct PathPointf* point, const struct PathPointf* other);
 */
static void test_path_pointf_init_from_path_pointf(void)
{
    struct PathPointf pt1;
    struct PathPointf pt2;

    path_pointf_init_default(&pt1);
    path_pointf_init_default(&pt2);

    pt1.theta        = 1.0f;
    pt1.curvature    = 2.0f;
    pt1.speed        = 3.0f;
    pt1.acceleration = 4.0f;
    pt1.point.x      = 5.0f;
    pt1.point.y      = 6.0f;
    pt1.point.z      = 7.0f;
    pt1.distance     = 8.0f;
    pt1.time         = 9.0f;

    path_pointf_init_from_path_pointf(&pt2, &pt1);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, pt2.theta);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, pt2.curvature);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, pt2.speed);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, pt2.acceleration);
    TEST_ASSERT_EQUAL_FLOAT(8.0f, pt2.distance);
    TEST_ASSERT_EQUAL_FLOAT(9.0f, pt2.time);

    TEST_ASSERT_EQUAL_FLOAT(5.0f, pt2.point.x);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, pt2.point.y);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, pt2.point.z);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test const struct Point3f* path_pointf_get_point(const struct PathPointf* point);
 */
static void test_path_pointf_get_point(void)
{
    struct PathPointf     pt1;
    const struct Point3f* pt2;

    path_pointf_init_default(&pt1);

    pt1.point.x = 5.0f;
    pt1.point.y = 6.0f;
    pt1.point.z = 7.0f;

    pt2 = path_pointf_get_point(&pt1);

    TEST_ASSERT_EQUAL_FLOAT(5.0f, pt2->x);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, pt2->y);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, pt2->z);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test void path_pointf_set_point(struct PathPointf* point, struct Point3f* pt);
 */
static void test_path_pointf_set_point(void)
{
    struct PathPointf pt1;
    struct Point3f    pt2;

    path_pointf_init_default(&pt1);

    pt2.x = 5.0f;
    pt2.y = 6.0f;
    pt2.z = 7.0f;

    path_pointf_set_point(&pt1, &pt2);

    TEST_ASSERT_EQUAL_FLOAT(5.0f, pt1.point.x);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, pt1.point.y);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, pt1.point.z);
}

static void test_path_pointf_serialize_deserialize(void)
{
    struct PathPointf point;
    uint32_t          expected_size = 0;
    uint8_t           buffer[512];
    retcode_t         retcode;

    path_pointf_init_default(&point);

    expected_size = path_pointf_get_serialized_size(&point);

    retcode = path_pointf_serialize(&point, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, retcode);
    retcode = path_pointf_deserialize(&point, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, retcode);

    retcode = path_pointf_serialize(&point, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_INT32(expected_size, retcode);
    retcode = path_pointf_deserialize(&point, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_INT32(expected_size, retcode);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test getter
 */
static void test_getter(void)
{
    struct PathPointf pt1;

    path_pointf_init_default(&pt1);

    pt1.theta        = 1.0f;
    pt1.curvature    = 2.0f;
    pt1.speed        = 3.0f;
    pt1.acceleration = 4.0f;
    pt1.distance     = 5.0f;
    pt1.time         = 6.0f;

    TEST_ASSERT_EQUAL_FLOAT(1.0f, path_pointf_get_theta(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, path_pointf_get_curvature(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, path_pointf_get_speed(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, path_pointf_get_acceleration(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, path_pointf_get_distance(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(6.0f, path_pointf_get_time(&pt1));

    struct Pathf path_1;
    pathf_init_default(&path_1);

    pathf_set_path_value_valid(&path_1, PATH_VALID_POSITION, true);
    pathf_set_path_value_valid(&path_1, PATH_VALID_THETA, true);
    pathf_set_path_value_valid(&path_1, PATH_VALID_CURVATURE, true);
    pathf_set_path_value_valid(&path_1, PATH_VALID_SPEED, true);
    pathf_set_path_value_valid(&path_1, PATH_VALID_ACCELERATION, true);
    pathf_set_path_value_valid(&path_1, PATH_VALID_DISTANCE, true);
    pathf_set_path_value_valid(&path_1, PATH_VALID_TIME, true);

    TEST_ASSERT_TRUE(pathf_get_position_valid(&path_1));
    TEST_ASSERT_TRUE(pathf_get_theata_valid(&path_1));
    TEST_ASSERT_TRUE(pathf_get_curvature_valid(&path_1));
    TEST_ASSERT_TRUE(pathf_get_speed_valid(&path_1));
    TEST_ASSERT_TRUE(pathf_get_acceleration_valid(&path_1));
    TEST_ASSERT_TRUE(pathf_get_distance_valid(&path_1));
    TEST_ASSERT_TRUE(pathf_get_time_valid(&path_1));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test setter
 */
static void test_setter(void)
{
    struct PathPointf pt1;

    path_pointf_init_default(&pt1);

    path_pointf_set_theta(&pt1, 1.0f);
    path_pointf_set_curvature(&pt1, 2.0f);
    path_pointf_set_speed(&pt1, 3.0f);
    path_pointf_set_acceleration(&pt1, 4.0f);
    path_pointf_set_distance(&pt1, 5.0f);
    path_pointf_set_time(&pt1, 6.0f);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, path_pointf_get_theta(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, path_pointf_get_curvature(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, path_pointf_get_speed(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, path_pointf_get_acceleration(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, path_pointf_get_distance(&pt1));
    TEST_ASSERT_EQUAL_FLOAT(6.0f, path_pointf_get_time(&pt1));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test void pathf_init_default(struct Pathf* path);
 */
static void test_pathf_init(void)
{
    struct Pathf path;

    pathf_init_default(&path);

    TEST_ASSERT_EQUAL_INT32(0, path.point_num);
}

static void test_pathf_timestamp(void)
{
    struct Pathf     path;
    struct Timestamp stamp;
    retcode_t        retcode;

    retcode = timestamp_init_from_sec_nsec(&stamp, 100, 1000);
    TEST_ASSERT_NOT_EQUAL(RC_TIMESTAMP_OVERFLOW, retcode);
    TEST_ASSERT_NOT_EQUAL(RC_TIMESTAMP_UNDERFLOW, retcode);

    pathf_set_timestamp(&path, &stamp);
    TEST_ASSERT_EQUAL_UINT32(100, timestamp_get_sec(pathf_get_timestamp(&path)));
    TEST_ASSERT_EQUAL_UINT32(1000, timestamp_get_nsec(pathf_get_timestamp(&path)));
}

static void test_pathf_coordinate(void)
{
    struct Pathf path;
    Coordinate_t coordinate;

    coordinate_set_type(&coordinate, COORDINATE_TYPE_VEHICLE);
    coordinate_set_param(&coordinate, 0xAA55);
    pathf_set_coordinate(&path, coordinate);

    coordinate = pathf_get_coordinate(&path);
    TEST_ASSERT_EQUAL_UINT32(COORDINATE_TYPE_VEHICLE, coordinate_get_type(&coordinate));
    TEST_ASSERT_EQUAL_UINT32(0xAA55, coordinate_get_param(&coordinate));
}

static void test_pathf_planning_state(void)
{
    struct Pathf       path;
    enum PlanningState state;
    state = PLANNING_STATE_BACKWARD;

    pathf_set_planning_state(&path, state);
    TEST_ASSERT_EQUAL_UINT32(PLANNING_STATE_BACKWARD, pathf_get_planning_state(&path));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t pathf_push_back_point(struct Pathf* path, const struct PathPointf* point);
 */
static void test_pathf_push_back_point(void)
{
    struct Pathf      path;
    struct PathPointf pt;

    path_pointf_init_default(&pt);
    pathf_init_default(&path);

    for (size_t i = 0; i < PATHF_MAX_POINT_NUMBER; ++i)
    {
        TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    }
    TEST_ASSERT_EQUAL_INT32(RC_PATH_BUFFER_OVERFLOW, pathf_push_back_point(&path, &pt));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test const struct PathPointf* pathf_get_point_unsafe(const struct Pathf* path, uint32_t index);
 */
static void test_pathf_get_point(void)
{
    struct Pathf             path;
    struct PathPointf        pt;
    struct PathPointf        pt2;
    const struct PathPointf* output_pt;

    path_pointf_init_default(&pt);
    path_pointf_init_default(&pt2);
    pathf_init_default(&path);

    pt2.point.x = 1.0f;

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt2));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));

    output_pt = pathf_get_point_unsafe(&path, 3);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output_pt->point.x);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test void pathf_clear_path_list(struct Pathf* path);
 */
static void test_pathf_clear_path_list(void)
{
    struct Pathf      path;
    struct PathPointf pt;

    path_pointf_init_default(&pt);
    pathf_init_default(&path);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));

    TEST_ASSERT_EQUAL_INT32(20, path.point_num);
    pathf_clear_path_list(&path);
    TEST_ASSERT_EQUAL_INT32(0, path.point_num);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test uint32_t pathf_get_point_list_size(struct Pathf* path);
 */
static void test_pathf_get_point_list_size(void)
{
    struct Pathf      path;
    struct PathPointf pt;

    path_pointf_init_default(&pt);
    pathf_init_default(&path);
    TEST_ASSERT_EQUAL_UINT32(0, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(1, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(2, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(3, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(4, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(5, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(6, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(7, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(8, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(9, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(10, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(11, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(12, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(13, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(14, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(15, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(16, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(17, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(18, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(19, pathf_get_point_list_size(&path));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    TEST_ASSERT_EQUAL_UINT32(20, pathf_get_point_list_size(&path));

    TEST_ASSERT_EQUAL_INT32(20, path.point_num);
    pathf_clear_path_list(&path);
    TEST_ASSERT_EQUAL_INT32(0, path.point_num);
    TEST_ASSERT_EQUAL_UINT32(0, pathf_get_point_list_size(&path));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t pathf_find_closest_point(const struct Pathf* path, const struct Point3f* target_point,
                                  uint32_t start_idx, uint32_t* closest_idx);
 */
static void test_pathf_find_closest_point(void)
{
    struct Pathf      path;
    struct PathPointf pt;
    struct Point3f    target_point1;
    uint32_t          result;
    retcode_t         retcode;

    point3f_init(&target_point1);
    target_point1.x = 0.0f;

    pathf_init_default(&path);

    retcode = pathf_get_point(&path, 0, &pt);
    TEST_ASSERT_EQUAL_INT32(RC_PATH_INVALID_INDEX_DURING_GET_POINT, retcode);
    retcode = pathf_find_closest_point(&path, &target_point1, 0, &result);
    TEST_ASSERT_EQUAL_INT32(RC_PATH_IS_EMPTY, retcode);

    path_pointf_init_default(&pt);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    pt.point.x = 1.0f;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    pt.point.x = 2.0f;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    pt.point.x = 3.0f;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    pt.point.x = 4.0f;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    pt.point.x = 5.0f;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    pt.point.x = 6.0f;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    pt.point.x = 7.0f;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    pt.point.x = 8.0f;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));
    pt.point.x = 9.0f;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, pathf_push_back_point(&path, &pt));

    retcode = pathf_find_closest_point(&path, &target_point1, 0, &result);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, retcode);
    TEST_ASSERT_EQUAL_INT32(1, result);

    retcode = pathf_find_closest_point(&path, &target_point1, 1, &result);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, retcode);
    TEST_ASSERT_EQUAL_INT32(2, result);

    retcode = pathf_find_closest_point(&path, &target_point1, 5, &result);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, retcode);
    TEST_ASSERT_EQUAL_INT32(6, result);

    retcode = pathf_find_closest_point(&path, &target_point1, 100, &result);
    TEST_ASSERT_EQUAL_INT32(RC_PATH_INVALID_START_INDEX, retcode);

    retcode = pathf_get_point(&path, 0, &pt);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, retcode);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 *          uint32_t pathf_get_serialized_size(const struct Pathf* path);
 */
static void test_pathf_get_serialized_size(void)
{
    struct Pathf path;
    pathf_init_default(&path);

    TEST_ASSERT_EQUAL_UINT32(24, pathf_get_serialized_size(&path));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 *          retcode_t pathf_serialize(const struct Pathf* path, uint8_t* buffer, uint32_t buffer_size)
 */
static void test_pathf_serialize_deserialize(void)
{
    struct Pathf path1;
    struct Pathf path2;
    uint8_t      buffer[16 + 32 * PATHF_MAX_POINT_NUMBER];

    struct Timestamp stamp;
    retcode_t        retcode;
    retcode = timestamp_init_from_sec_nsec(&stamp, 100, 1000);
    pathf_set_timestamp(&path1, &stamp);

    Coordinate_t coordinate;
    coordinate_set_type(&coordinate, COORDINATE_TYPE_VEHICLE);
    coordinate_set_param(&coordinate, 0xAA55);
    pathf_set_coordinate(&path1, coordinate);

    pathf_set_path_value_valid(&path1, PATH_VALID_POSITION, true);
    pathf_set_path_value_valid(&path1, PATH_VALID_THETA, true);
    pathf_set_path_value_valid(&path1, PATH_VALID_CURVATURE, true);
    pathf_set_path_value_valid(&path1, PATH_VALID_SPEED, true);
    pathf_set_path_value_valid(&path1, PATH_VALID_ACCELERATION, true);
    pathf_set_path_value_valid(&path1, PATH_VALID_DISTANCE, true);
    pathf_set_path_value_valid(&path1, PATH_VALID_TIME, true);

    enum PlanningState state;
    state = PLANNING_STATE_BACKWARD;
    pathf_set_planning_state(&path1, state);

    path1.point_num                  = 5;
    path1.point_num                  = 5;
    path1.point_num                  = 5;
    path1.point_num                  = 5;
    path1.point_list[0].acceleration = 1.0f;
    path1.point_list[0].curvature    = 2.0f;
    path1.point_list[0].speed        = 3.0f;
    path1.point_list[0].theta        = 4.0f;
    path1.point_list[0].distance     = 5.0f;
    path1.point_list[0].time         = 6.0f;
    path1.point_list[0].point.x      = 5.0f;
    path1.point_list[0].point.y      = 6.0f;
    path1.point_list[0].point.z      = 7.0f;

    path1.point_list[1].acceleration = 1.1f;
    path1.point_list[1].curvature    = 2.1f;
    path1.point_list[1].speed        = 3.1f;
    path1.point_list[1].theta        = 4.1f;
    path1.point_list[1].distance     = 5.1f;
    path1.point_list[1].time         = 6.1f;
    path1.point_list[1].point.x      = 5.1f;
    path1.point_list[1].point.y      = 6.1f;
    path1.point_list[1].point.z      = 7.1f;

    retcode = pathf_serialize(&path1, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, retcode);
    retcode = pathf_deserialize(&path1, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, retcode);

    retcode = pathf_serialize(&path1, buffer, 20 + 28 * PATHF_MAX_POINT_NUMBER);
    TEST_ASSERT_GREATER_THAN_INT32(0, retcode);
    retcode = pathf_deserialize(&path2, buffer, 20 + 28 * PATHF_MAX_POINT_NUMBER);
    TEST_ASSERT_GREATER_THAN_INT32(0, retcode);

    TEST_ASSERT_EQUAL_UINT32(100, timestamp_get_sec(pathf_get_timestamp(&path2)));
    TEST_ASSERT_EQUAL_UINT32(1000, timestamp_get_nsec(pathf_get_timestamp(&path2)));

    coordinate = pathf_get_coordinate(&path2);
    TEST_ASSERT_EQUAL_UINT32(COORDINATE_TYPE_VEHICLE, coordinate_get_type(&coordinate));
    TEST_ASSERT_EQUAL_UINT32(0xAA55, coordinate_get_param(&coordinate));

    TEST_ASSERT_TRUE(pathf_get_position_valid(&path2));
    TEST_ASSERT_TRUE(pathf_get_theata_valid(&path2));
    TEST_ASSERT_TRUE(pathf_get_curvature_valid(&path2));
    TEST_ASSERT_TRUE(pathf_get_speed_valid(&path2));
    TEST_ASSERT_TRUE(pathf_get_acceleration_valid(&path2));
    TEST_ASSERT_TRUE(pathf_get_distance_valid(&path2));
    TEST_ASSERT_TRUE(pathf_get_time_valid(&path2));

    TEST_ASSERT_EQUAL_UINT32(PLANNING_STATE_BACKWARD, pathf_get_planning_state(&path2));

    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[0].acceleration, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[0].curvature, 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[0].speed, 3.0f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[0].theta, 4.0f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[0].distance, 5.0f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[0].time, 6.0f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[0].point.x, 5.0f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[0].point.y, 6.0f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[0].point.z, 7.0f);

    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[1].acceleration, 1.1f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[1].curvature, 2.1f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[1].speed, 3.1f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[1].theta, 4.1f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[1].distance, 5.1f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[1].time, 6.1f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[1].point.x, 5.1f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[1].point.y, 6.1f);
    TEST_ASSERT_EQUAL_FLOAT(path2.point_list[1].point.z, 7.1f);

    TEST_ASSERT_EQUAL_INT32(path2.point_num, 5);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_path_pointf_init);
    RUN_TEST(test_path_pointf_init_from_path_pointf);
    RUN_TEST(test_pathf_timestamp);
    RUN_TEST(test_pathf_planning_state);
    RUN_TEST(test_pathf_coordinate);
    RUN_TEST(test_path_pointf_get_point);
    RUN_TEST(test_path_pointf_set_point);
    RUN_TEST(test_path_pointf_serialize_deserialize);
    RUN_TEST(test_getter);
    RUN_TEST(test_setter);
    RUN_TEST(test_pathf_init);
    RUN_TEST(test_pathf_push_back_point);
    RUN_TEST(test_pathf_get_point);
    RUN_TEST(test_pathf_get_point_list_size);
    RUN_TEST(test_pathf_clear_path_list);
    RUN_TEST(test_pathf_find_closest_point);
    RUN_TEST(test_pathf_get_serialized_size);
    RUN_TEST(test_pathf_serialize_deserialize);

    return UNITY_END();
}
