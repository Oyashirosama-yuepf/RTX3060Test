/**
 * @file path_float32.c
 * @brief This header file define pathf.
 * @author lijiawen@holomatic.com
 * @date 2019-09-11
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <assert.h>

#include <holo_c/common/path_float32.h>
#include <holo_c/utils/serialization.h>

void path_pointf_init_default(struct PathPointf* point)
{
    assert(point != NULL);

    (void)point3f_init(&(point->point));
    point->theta        = 0.0f;
    point->curvature    = 0.0f;
    point->speed        = 0.0f;
    point->acceleration = 0.0f;
    point->distance     = 0.0f;
    point->time         = 0.0f;
}

void path_pointf_init_from_path_pointf(struct PathPointf* point, const struct PathPointf* other)
{
    assert(point != NULL);
    assert(other != NULL);

    (void)point3f_init_from_point3f(&(point->point), &(other->point));
    point->theta        = other->theta;
    point->curvature    = other->curvature;
    point->speed        = other->speed;
    point->acceleration = other->acceleration;
    point->distance     = other->distance;
    point->time         = other->time;
}

const struct Point3f* path_pointf_get_point(const struct PathPointf* point)
{
    assert(point != NULL);

    return &(point->point);
}

void path_pointf_set_point(struct PathPointf* point, struct Point3f* pt)
{
    assert(point != NULL);
    assert(pt != NULL);

    (void)point3f_init_from_point3f(&(point->point), pt);
}

float32_t path_pointf_get_theta(const struct PathPointf* point)
{
    assert(point != NULL);

    return point->theta;
}

void path_pointf_set_theta(struct PathPointf* point, float32_t theta)
{
    assert(point != NULL);

    /* TODO: check input or use normalization-function */
    point->theta = theta;
}

float32_t path_pointf_get_curvature(const struct PathPointf* point)
{
    assert(point != NULL);

    return point->curvature;
}

void path_pointf_set_curvature(struct PathPointf* point, float32_t curvature)
{
    assert(point != NULL);

    point->curvature = curvature;
}

float32_t path_pointf_get_speed(const struct PathPointf* point)
{
    assert(point != NULL);

    return point->speed;
}

void path_pointf_set_speed(struct PathPointf* point, float32_t speed)
{
    assert(point != NULL);

    point->speed = speed;
}

float32_t path_pointf_get_acceleration(const struct PathPointf* point)
{
    assert(point != NULL);

    return point->acceleration;
}

void path_pointf_set_acceleration(struct PathPointf* point, float32_t acceleration)
{
    assert(point != NULL);

    point->acceleration = acceleration;
}

float32_t path_pointf_get_distance(const struct PathPointf* point)
{
    assert(point != NULL);

    return point->distance;
}

void path_pointf_set_distance(struct PathPointf* point, float32_t distance)
{
    assert(point != NULL);

    /* TODO: check input or use normalization-function */
    point->distance = distance;
}

float32_t path_pointf_get_time(const struct PathPointf* point)
{
    assert(point != NULL);

    return point->time;
}

void path_pointf_set_time(struct PathPointf* point, float32_t time)
{
    assert(point != NULL);

    /* TODO: check input or use normalization-function */
    point->time = time;
}

uint32_t path_pointf_get_serialized_size(const struct PathPointf* point)
{
    assert(point != NULL);

    uint32_t size = 0;

    size += point3f_get_serialized_size(&point->point);
    size += 6 * sizeof(float32_t);

    return serialization_aligned_size(size);
}

retcode_t path_pointf_serialize(const struct PathPointf* point, uint8_t* buffer, uint32_t buffer_size)
{
    assert(point != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  expected_size   = path_pointf_get_serialized_size(point);
    uint32_t  serialized_size = 0;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += point3f_serialize(&(point->point), buffer + serialized_size, buffer_size - serialized_size);

        serialized_size += serialize_float32(&(point->theta), buffer + serialized_size, buffer_size - serialized_size);

        serialized_size +=
            serialize_float32(&(point->curvature), buffer + serialized_size, buffer_size - serialized_size);

        serialized_size += serialize_float32(&(point->speed), buffer + serialized_size, buffer_size - serialized_size);

        serialized_size +=
            serialize_float32(&(point->acceleration), buffer + serialized_size, buffer_size - serialized_size);

        serialized_size +=
            serialize_float32(&(point->distance), buffer + serialized_size, buffer_size - serialized_size);

        serialized_size += serialize_float32(&(point->time), buffer + serialized_size, buffer_size - serialized_size);

        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(serialized_size == expected_size);

        rc = serialized_size;
    }

    return rc;
}

retcode_t path_pointf_deserialize(struct PathPointf* point, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(point != NULL);
    assert(buffer != NULL);

    uint32_t expected_size     = path_pointf_get_serialized_size(point);
    uint32_t deserialized_size = 0;

    retcode_t rc = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size +=
            point3f_deserialize(&(point->point), buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size +=
            deserialize_float32(&(point->theta), buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size +=
            deserialize_float32(&(point->curvature), buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size +=
            deserialize_float32(&(point->speed), buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size +=
            deserialize_float32(&(point->acceleration), buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size +=
            deserialize_float32(&(point->distance), buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size +=
            deserialize_float32(&(point->time), buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size +=
            deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);

        rc = deserialized_size;
    }

    return rc;
}

void pathf_init_default(struct Pathf* path)
{
    assert(path != NULL);

    (void)timestamp_init(&(path->stamp));
    path->coordinate     = coordinate_default_create();
    path->point_num      = 0;
    path->planning_state = PLANNING_STATE_UNKNOWN;

    pathf_set_path_value_valid(path, PATH_VALID_POSITION, false);
    pathf_set_path_value_valid(path, PATH_VALID_THETA, false);
    pathf_set_path_value_valid(path, PATH_VALID_CURVATURE, false);
    pathf_set_path_value_valid(path, PATH_VALID_SPEED, false);
    pathf_set_path_value_valid(path, PATH_VALID_ACCELERATION, false);
    pathf_set_path_value_valid(path, PATH_VALID_DISTANCE, false);
    pathf_set_path_value_valid(path, PATH_VALID_TIME, false);
}

const struct Timestamp* pathf_get_timestamp(const struct Pathf* path)
{
    assert(path != NULL);

    return &(path->stamp);
}

void pathf_set_timestamp(struct Pathf* path, const struct Timestamp* stamp)
{
    assert(path != NULL);
    assert(stamp != NULL);

    timestamp_init_from_timestamp(&path->stamp, stamp);
}

Coordinate_t pathf_get_coordinate(const struct Pathf* path)
{
    assert(path != NULL);

    return path->coordinate;
}

void pathf_set_coordinate(struct Pathf* path, Coordinate_t coordinate)
{
    assert(path != NULL);

    path->coordinate = coordinate;
}

enum PlanningState pathf_get_planning_state(const struct Pathf* path)
{
    assert(path != NULL);

    return path->planning_state;
}

void pathf_set_planning_state(struct Pathf* path, enum PlanningState planning_state)
{
    assert(path != NULL);

    path->planning_state = planning_state;
}

retcode_t pathf_push_back_point(struct Pathf* path, const struct PathPointf* point)
{
    assert(path != NULL);
    assert(point != NULL);

    if (path->point_num >= PATHF_MAX_POINT_NUMBER)
    {
        return RC_PATH_BUFFER_OVERFLOW;
    }

    (void)path_pointf_init_from_path_pointf(&(path->point_list[path->point_num]), point);
    ++path->point_num;

    return RC_SUCCESS;
}

retcode_t pathf_get_point(const struct Pathf* path, uint32_t index, struct PathPointf* output_point)
{
    assert(path != NULL);
    assert(path->point_num <= PATHF_MAX_POINT_NUMBER);

    if (index < path->point_num)
    {
        path_pointf_init_from_path_pointf(output_point, &(path->point_list[index]));

        return RC_SUCCESS;
    }
    else
    {
        output_point = NULL;

        return RC_PATH_INVALID_INDEX_DURING_GET_POINT;
    }
}

const struct PathPointf* pathf_get_point_unsafe(const struct Pathf* path, uint32_t index)
{
    assert(path != NULL);
    assert(index < path->point_num);

    return &(path->point_list[index]);
}

uint32_t pathf_get_point_list_size(const struct Pathf* path)
{
    assert(path != NULL);

    return path->point_num;
}

void pathf_clear_path_list(struct Pathf* path)
{
    assert(path != NULL);

    path->point_num = 0;
}

retcode_t pathf_find_closest_point(const struct Pathf* path, const struct Point3f* target_point, uint32_t start_idx,
                                   uint32_t* closest_idx)
{
    uint32_t  idx = start_idx;
    float32_t closest_dis_sqr;
    float32_t dis_sqr            = 0.0f;
    bool_t    find_closest_point = false;

    assert(path != NULL);
    assert(target_point != NULL);
    assert(closest_idx != NULL);

    if (path->point_num == 0)
    {
        return RC_PATH_IS_EMPTY;
    }

    if (start_idx >= path->point_num)
    {
        return RC_PATH_INVALID_START_INDEX;
    }

    (void)point3f_dist_sqr(target_point, path_pointf_get_point(pathf_get_point_unsafe(path, idx)), &closest_dis_sqr);
    for (idx = idx + 1; idx < path->point_num; ++idx)
    {
        (void)point3f_dist_sqr(target_point, path_pointf_get_point(pathf_get_point_unsafe(path, idx)), &dis_sqr);

        if (dis_sqr < closest_dis_sqr)
        {
            closest_dis_sqr = dis_sqr;
        }
        else
        {
            find_closest_point = true;
            break;
        }
    }

    if ((!find_closest_point) && (idx != 0))
    {
        idx--;
    }

    /* Sometimes, the closest index(which index is idx-1) may be behind of us, but we only care the point ahead of us.
       So we are going to move ahead to make sure that the point we choose is ahead of us. */
    *closest_idx = idx;

    return RC_SUCCESS;
}

uint32_t pathf_get_serialized_size(const struct Pathf* path)
{
    uint32_t serialized_size = 0U;
    serialized_size += timestamp_get_serialized_size(&path->stamp);
    serialized_size += sizeof(Coordinate_t);
    serialized_size += sizeof(uint32_t) * 2;
    serialized_size += sizeof(enum PlanningState);
    serialized_size += path->point_num * sizeof(struct PathPointf);
    return serialization_aligned_size(serialized_size);
}

retcode_t pathf_serialize(const struct Pathf* path, uint8_t* buffer, uint32_t buffer_size)
{
    assert(path != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  expected_size   = pathf_get_serialized_size(path);
    uint32_t  serialized_size = 0;
    uint32_t  idx;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += timestamp_serialize(&path->stamp, buffer, buffer_size);
        serialized_size += serialize_uint32(&path->coordinate, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_uint32((uint32_t*)(&(path->value_valid)), buffer + serialized_size,
                                            buffer_size - serialized_size);
        serialized_size +=
            serialize_uint32((uint32_t*)&path->planning_state, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_uint32(&path->point_num, buffer + serialized_size, buffer_size - serialized_size);

        for (idx = 0; idx < path->point_num; idx++)
        {
            serialized_size += path_pointf_serialize(&(path->point_list[idx]), buffer + serialized_size,
                                                     buffer_size - serialized_size);
        }

        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(serialized_size == expected_size);

        rc = serialized_size;
    }

    return rc;
}

retcode_t pathf_deserialize(struct Pathf* path, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(path != NULL);
    assert(buffer != NULL);

    retcode_t rc           = RC_SUCCESS;
    uint32_t expected_size = timestamp_get_serialized_size(&path->stamp) + sizeof(Coordinate_t) + sizeof(uint32_t) * 2 +
                             sizeof(enum PlanningState);
    uint32_t deserialized_size = 0;
    uint32_t idx;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size +=
            timestamp_deserialize(&path->stamp, buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size +=
            deserialize_uint32(&path->coordinate, buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size += deserialize_uint32((uint32_t*)(&(path->value_valid)), buffer + deserialized_size,
                                                buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_uint32((uint32_t*)&path->planning_state, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_uint32(&path->point_num, buffer + deserialized_size, buffer_size - deserialized_size);

        expected_size += path->point_num * path_pointf_get_serialized_size(&path->point_list[0U]);
        if (expected_size > buffer_size)
        {
            rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
        }
        else
        {
            for (idx = 0; idx < path->point_num; idx++)
            {
                deserialized_size += path_pointf_deserialize(&path->point_list[idx], buffer + deserialized_size,
                                                             buffer_size - deserialized_size);
            }

            assert(deserialized_size == expected_size);

            rc = deserialized_size;
        }
    }

    return rc;
}

bool_t pathf_get_position_valid(struct Pathf* path)
{
    return path->value_valid.position_valid;
}

bool_t pathf_get_theata_valid(struct Pathf* path)
{
    return path->value_valid.theata_valid;
}

bool_t pathf_get_curvature_valid(struct Pathf* path)
{
    return path->value_valid.curvature_valid;
}

bool_t pathf_get_speed_valid(struct Pathf* path)
{
    return path->value_valid.speed_valid;
}

bool_t pathf_get_acceleration_valid(struct Pathf* path)
{
    return path->value_valid.acceleration_valid;
}

bool_t pathf_get_distance_valid(struct Pathf* path)
{
    return path->value_valid.distance_valid;
}

bool_t pathf_get_time_valid(struct Pathf* path)
{
    return path->value_valid.time_valid;
}

void pathf_set_path_value_valid(struct Pathf* path, enum PathValueValid value, bool_t is_valid)
{
    switch (value)
    {
        case PATH_VALID_POSITION:
            path->value_valid.position_valid = is_valid;
            break;

        case PATH_VALID_THETA:
            path->value_valid.theata_valid = is_valid;
            break;

        case PATH_VALID_CURVATURE:
            path->value_valid.curvature_valid = is_valid;
            break;

        case PATH_VALID_SPEED:
            path->value_valid.speed_valid = is_valid;
            break;

        case PATH_VALID_ACCELERATION:
            path->value_valid.acceleration_valid = is_valid;
            break;

        case PATH_VALID_DISTANCE:
            path->value_valid.distance_valid = is_valid;
            break;

        case PATH_VALID_TIME:
            path->value_valid.time_valid = is_valid;
            break;

        default:
            break;
    }
}
