/**
 * @file path_float32.h
 * @brief This header file define pathf.
 * @author lijiawen@holomatic.com
 * @date 2019-09-11
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_COMMON_PATH_FLOAT32_H_
#define HOLO_C_COMMON_PATH_FLOAT32_H_

#include <holo_c/common/coordinate.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point3.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PATHF_MAX_POINT_NUMBER 50

/**
 * @brief       this struct describes point on path with float scalar
 */
struct PathPointf
{
    struct Point3f point; /* the 3-D position of path point [m] */

    float32_t theta; /* the heading angle of the point [rad] */

    float32_t curvature; /* the curvature of the path on this point */

    float32_t speed; /* the tag speed of this point [m/s] */

    float32_t acceleration; /* the tag acceleration of this point [m/s2] */

    float32_t distance; /* the distance difference to ideal point along the path [m] */

    float32_t time; /* the time difference to ideal point point [s] */
};
HOLO_STATIC_ASSERT(sizeof(struct PathPointf) == 36);

/**
 * @brief       init a PathPointf
 *
 * @param       point PathPointf
 */
void path_pointf_init_default(struct PathPointf* point);

/**
 * @brief       init a PathPointf from another PathPointf
 *
 * @param       point PathPointf
 * @param       other another PathPointf
 */
void path_pointf_init_from_path_pointf(struct PathPointf* point, const struct PathPointf* other);

/**
 * @brief       get the position from a PathPointf
 *
 * @param       point PathPointf
 *
 * @return      Point3f position
 */
const struct Point3f* path_pointf_get_point(const struct PathPointf* point);

/**
 * @brief       set the position into a PathPointf
 *
 * @param       point PathPointf
 * @param       pt the position to be set in
 */
void path_pointf_set_point(struct PathPointf* point, struct Point3f* pt);

/**
 * @brief       get the theta(yaw) from a PathPointf
 *
 * @param       point PathPointf
 *
 * @return      theta
 */
float32_t path_pointf_get_theta(const struct PathPointf* point);

/**
 * @brief       set the theta(yaw) into a PathPointf
 *
 * @param       point PathPointf
 * @param       theta the yaw to be set in
 */
void path_pointf_set_theta(struct PathPointf* point, float32_t theta);

/**
 * @brief       get the curvature from a PathPointf
 *
 * @param       point PathPointf
 *
 * @return      curvature
 */
float32_t path_pointf_get_curvature(const struct PathPointf* point);

/**
 * @brief       set the curvature into a PathPointf
 *
 * @param       point PathPointf
 * @param       curvature the curvature to be set in
 */
void path_pointf_set_curvature(struct PathPointf* point, float32_t curvature);

/**
 * @brief       get the speed from a PathPointf
 *
 * @param       point PathPointf
 *
 * @return      speed
 */
float32_t path_pointf_get_speed(const struct PathPointf* point);

/**
 * @brief       set the speed into a PathPointf
 *
 * @param       point PathPointf
 * @param       speed the speed to be set in
 */
void path_pointf_set_speed(struct PathPointf* point, float32_t speed);

/**
 * @brief       get the acceleration from a PathPointf
 *
 * @param       point PathPointf
 *
 * @return      acceleration
 */
float32_t path_pointf_get_acceleration(const struct PathPointf* point);

/**
 * @brief       set the acceleration into a PathPointf
 *
 * @param       point PathPointf
 * @param       acceleration the acceleration to be set in
 */
void path_pointf_set_acceleration(struct PathPointf* point, float32_t acceleration);

/**
 * @brief       get the distance from a PathPointf
 *
 * @param       point PathPointf
 *
 * @return      distance
 */
float32_t path_pointf_get_distance(const struct PathPointf* point);

/**
 * @brief       set the distance into a PathPointf
 *
 * @param       point PathPointf
 * @param       distance the distance to be set in
 */
void path_pointf_set_distance(struct PathPointf* point, float32_t distance);

/**
 * @brief       get the time from a PathPointf
 *
 * @param       point PathPointf
 *
 * @return      time
 */
float32_t path_pointf_get_time(const struct PathPointf* point);

/**
 * @brief       set the time into a PathPointf
 *
 * @param       point PathPointf
 * @param       time the time to be set in
 */
void path_pointf_set_time(struct PathPointf* point, float32_t time);

/**
 * @brief Get serialized buffer size for PathPointf.
 *
 * @param point The PathPointf object.
 *
 * @return Serialized size
 */
uint32_t path_pointf_get_serialized_size(const struct PathPointf* point);

/**
 * @brief Serialize PathPointf.
 *
 * @param point The PathPointf object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes serialized into buffer
 */
retcode_t path_pointf_serialize(const struct PathPointf* point, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize PathPointf object.
 *
 * @param point The PathPointf object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer
 */
retcode_t path_pointf_deserialize(struct PathPointf* point, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief       this struct describes the path which is a set of pathpoint
 */
enum PathValueValid
{
    PATH_VALID_POSITION     = 0x01,
    PATH_VALID_THETA        = 0x02,
    PATH_VALID_CURVATURE    = 0x04,
    PATH_VALID_SPEED        = 0x08,
    PATH_VALID_ACCELERATION = 0x10,
    PATH_VALID_DISTANCE     = 0x20,
    PATH_VALID_TIME         = 0x40,
};

/**
 * @brief       this struct describes the planning state which is a set of pathpoint
 */
enum PlanningState
{
    PLANNING_STATE_UNKNOWN  = 0U,
    PLANNING_STATE_FORWARD  = 1U,
    PLANNING_STATE_BACKWARD = 2U,
    PLANNING_STATE_HOLD     = 3U,
    PLANNING_STATE_PARK     = 4U,
};

/**
 * @brief       this struct describes the path which is a set of pathpoint
 */
struct Pathf
{
    struct Timestamp stamp;      /** timestamp */
    Coordinate_t     coordinate; /** coordinate which sensor data reference to */

    struct
    {
        uint32_t position_valid : 1;
        uint32_t theata_valid : 1;
        uint32_t curvature_valid : 1;
        uint32_t speed_valid : 1;
        uint32_t acceleration_valid : 1;
        uint32_t distance_valid : 1;
        uint32_t time_valid : 1;
        uint32_t reserves : 25;
    } value_valid; /* path which info is valid */

    enum PlanningState planning_state;

    uint32_t          point_num;                          /* the size of point_list */
    struct PathPointf point_list[PATHF_MAX_POINT_NUMBER]; /* the array of PathPointf */
};
HOLO_STATIC_ASSERT(sizeof(struct Pathf) == (24 + 36 * PATHF_MAX_POINT_NUMBER));

/**
 * @brief       init a Pathf
 *
 * @param       path Pathf
 */
void pathf_init_default(struct Pathf* path);

/**
 * @brief       get the timestamp from Pathf
 *
 * @param       path Pathf
 *
 * @return      Timestamp
 */
const struct Timestamp* pathf_get_timestamp(const struct Pathf* path);

/**
 * @brief       set the timestamp from Pathf
 *
 * @param       path Pathf
 * @param       stamp input timestamp
 */
void pathf_set_timestamp(struct Pathf* path, const struct Timestamp* stamp);

/**
 * @brief       get the coordinate from Pathf
 *
 * @param       path Pathf
 *
 * @return      coordinate
 */
Coordinate_t pathf_get_coordinate(const struct Pathf* path);

/**
 * @brief       set the coordinate from Pathf
 *
 * @param       path Pathf
 * @param       coordinate input coordinate
 */
void pathf_set_coordinate(struct Pathf* path, Coordinate_t coordinate);

/**
 * @brief       get the planning state from Pathf
 *
 * @param       path Pathf
 *
 * @return      planning_state
 */
enum PlanningState pathf_get_planning_state(const struct Pathf* path);

/**
 * @brief       set the planning state from Pathf
 *
 * @param       path Pathf
 * @param       planning_state input planning_state
 */
void pathf_set_planning_state(struct Pathf* path, enum PlanningState coordinate);

/**
 * @brief       push a PathPointf into the Pathf
 *
 * @param       path Pathf
 * @param       point the PathPointf which is going to be put in
 *
 * @return      RC_PATH_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return      RC_SUCCESS
 */
retcode_t pathf_push_back_point(struct Pathf* path, const struct PathPointf* point);

/**
 * @brief       get a PathPointf from a Pathf by index with bound check
 *
 * @param       path Pathf
 * @param       index the index of point
 * @param       output_point the output point
 *
 * @return      RC_SUCCESS
 */
retcode_t pathf_get_point(const struct Pathf* path, uint32_t index, struct PathPointf* output_point);

/**
 * @brief       get a PathPointf from a Pathf by index without bound check
 *
 * @param       path Pathf
 * @param       index the index of point
 *
 * @return      PathPointf
 */
const struct PathPointf* pathf_get_point_unsafe(const struct Pathf* path, uint32_t index);

/**
 * @brief       Get the size of Pathf's point_list
 *
 * @param       path Pathf
 *
 * @return      the size of the Pathf's point_list
 */
uint32_t pathf_get_point_list_size(const struct Pathf* path);

/**
 * @brief       clear the Pathf's point_list
 *
 * @param       path Pathf
 */
void pathf_clear_path_list(struct Pathf* path);

/**
 * @brief       this function is used find the closest point on the path
 *
 * @param       path the pointer of Pathf
 * @param       target_point the target point needs to find the closest point
 * @param       start_idx from which idx finding starts
 * @param       closest_idx the closest point idx on the path
 *
 * @return      RC_PATH_IS_EMPTY path is empty
 * @return      RC_PATH_INVALID_START_INDEX start_idx is too large
 * @return      RC_SUCCESS
 */
retcode_t pathf_find_closest_point(const struct Pathf* path, const struct Point3f* target_point, uint32_t start_idx,
                                   uint32_t* closest_idx);

/**
 * @brief Get serialized buffer size for Pathf.
 *
 * @param path The Pathf object.
 *
 * @return Serialized size
 */
uint32_t pathf_get_serialized_size(const struct Pathf* path);

/**
 * @brief Serialize Pathf.
 *
 * @param path The Pathf object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes serialized into buffer
 */
retcode_t pathf_serialize(const struct Pathf* path, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize Pathf object.
 *
 * @param path The Pathf object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer
 */
retcode_t pathf_deserialize(struct Pathf* path, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief       Get the size of Pathf's position is vaild
 *
 * @param       path Pathf
 *
 * @return      whether position is valid
 */
bool_t pathf_get_position_valid(struct Pathf* path);

/**
 * @brief       Get the size of Pathf's theata is vaild
 *
 * @param       path Pathf
 *
 * @return      whether theata is valid
 */
bool_t pathf_get_theata_valid(struct Pathf* path);

/**
 * @brief       Get the size of Pathf's curvature is vaild
 *
 * @param       path Pathf
 *
 * @return      whether curvature is valid
 */
bool_t pathf_get_curvature_valid(struct Pathf* path);

/**
 * @brief       Get the size of Pathf's speed is vaild
 *
 * @param       path Pathf
 *
 * @return      whether speed is valid
 */
bool_t pathf_get_speed_valid(struct Pathf* path);

/**
 * @brief       Get the size of Pathf's acceleration is vaild
 *
 * @param       path Pathf
 *
 * @return      whether acceleration is valid
 */
bool_t pathf_get_acceleration_valid(struct Pathf* path);

/**
 * @brief       Get the size of Pathf's distance is vaild
 *
 * @param       path Pathf
 *
 * @return      whether distance is valid
 */
bool_t pathf_get_distance_valid(struct Pathf* path);

/**
 * @brief       Get the size of Pathf's time is vaild
 *
 * @param       path Pathf
 *
 * @return      whether time is valid
 */
bool_t pathf_get_time_valid(struct Pathf* path);

/**
 * @brief       Set the size of Pathf's acceleration is vaild
 *
 * @param       path Pathf
 * @param       PathValueValid value
 * @param       true or false
 */
void pathf_set_path_value_valid(struct Pathf* path, enum PathValueValid value, bool_t is_valid);

/**
 * @}
 * End serialization/deserialization API group.
 */

#ifdef __cplusplus
}
#endif

#endif
