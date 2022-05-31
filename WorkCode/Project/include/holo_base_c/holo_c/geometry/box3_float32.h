/*!
 * @file box3_float32.h
 * @brief This header file defines box in 3D.
 * @author duyanwei@holomatic.com
 * @date 2019-08-12
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_BOX3_FLOAT32_H_
#define HOLO_C_GEOMETRY_BOX3_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/pose3_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define Box3f struct
 *
 */
struct Box3f
{
    float32_t     width;
    float32_t     height;
    float32_t     depth;
    struct Pose3f pose;
};

// @todo HOLO_STATIC_ASSERT(sizeof(struct Box3f) == ?u)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize a box3, creating an unit box
 *
 * @param self box3
 * @return retcode_t
 */
retcode_t box3f_init(struct Box3f* self);

/**
 * @brief initialize a box3 from two diagonal points
 *
 * @param self box3
 * @param pt1 point1
 * @param pt2 point2
 * @return retcode_t
 */
retcode_t box3f_init_from_two_point3f(struct Box3f* self, const struct Point3f* pt1, const struct Point3f* pt2);

/**
 * @brief init box3 with width, height and depth, the pose is set to identity
 *
 * @param self box3
 * @param width width
 * @param height height
 * @param depth depth
 * @return retcode_t
 */
retcode_t box3f_init_from_width_height_and_depth(struct Box3f* self, const float32_t width, const float32_t height,
                                                 const float32_t depth);

/**
 * @brief initialize a box3 from width, height, depth and pose3
 *
 * @param self box3
 * @param width width of the box
 * @param height height of the box
 * @param depth depth of the box
 * @param pose pose of the box
 * @return retcode_t
 */
retcode_t box3f_init_from_width_height_depth_and_pose3f(struct Box3f* self, const float32_t width,
                                                        const float32_t height, const float32_t depth,
                                                        const struct Pose3f* pose);

/**
 * @brief initialize a box3 from vector3f and pose3, vector3f contains width, height and depth of the box
 *
 * @param self box3
 * @param dimension dimension of the box
 * @param pose pose of the box
 * @return retcode_t
 */
retcode_t box3f_init_from_vector3f_and_pose3f(struct Box3f* self, const struct Vectorf* dimension,
                                              const struct Pose3f* pose);

/**
 * @brief initialize box3 from another box3
 *
 * @param self box3
 * @param other box3
 * @return retcode_t
 */
retcode_t box3f_init_from_box3f(struct Box3f* self, const struct Box3f* other);

/**
 * @brief check if a box is valid
 *
 * @param self box3
 * @return bool_t
 */
bool_t box3f_is_valid(const struct Box3f* self);

/**
 * @brief check if two boxes are equal
 *
 * @param self box
 * @param other box
 * @return bool_t
 */
bool_t box3f_is_equal(const struct Box3f* self, const struct Box3f* other);

/**
 * @brief check if a box3 contains a point
 *
 * @param self box3
 * @param point point3
 * @return bool_t
 */
bool_t box3f_contains_point3f(const struct Box3f* self, const struct Point3f* point);

/**
 * @brief return the minimum and maximum corner points of a box in world coordinate, completely and uniquely enclosed
 *        the box by coordinates parallel to the axis
 *
 * @param self box
 * @param min_pt minimum point
 * @param max_pt maximum point
 * @return retcode_t
 */
retcode_t box3f_get_axis_aligned_external_box(const struct Box3f* self, struct Point3f* min_pt, struct Point3f* max_pt);

/**
 * @brief get the volume of the box
 *
 * @param self box
 * @return float32_t
 */
float32_t box3f_get_volume(const struct Box3f* self);

/**
 * @brief return the center of the box
 *
 * @param self box
 * @param center center of the box
 * @return retcode_t
 */
retcode_t box3f_get_center(const struct Box3f* self, struct Point3f* center);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_BOX3_FLOAT32_H_
