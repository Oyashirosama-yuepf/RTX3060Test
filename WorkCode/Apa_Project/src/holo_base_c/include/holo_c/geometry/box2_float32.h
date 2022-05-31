/*!
 * @file box2_float32.h
 * @brief This header file defines box in 2D.
 * @author duyanwei@holomatic.com
 * @date 2019-08-23
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_BOX2_FLOAT32_H_
#define HOLO_C_GEOMETRY_BOX2_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/pose2_float32.h>
#include <holo_c/numerics/vector_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define Box2f struct
 *
 */
struct Box2f
{
    float32_t     width;
    float32_t     height;
    struct Pose2f pose;
};

// @todo HOLO_STATIC_ASSERT(sizeof(struct Box2f) == ?u)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize a box2, creating an unit box
 *
 * @param self box2
 * @return retcode_t
 */
retcode_t box2f_init(struct Box2f* self);

/**
 * @brief initialize a box2 from two diagonal points
 *
 * @param self box2
 * @param pt1 point1
 * @param pt2 point2
 * @return retcode_t
 */
retcode_t box2f_init_from_two_point2f(struct Box2f* self, const struct Point2f* pt1, const struct Point2f* pt2);

/**
 * @brief init box2 with width and height
 *
 * @details the pose is set to identity
 * @param self box3
 * @param width width
 * @param height height
 * @return retcode_t
 */
retcode_t box2f_init_from_width_and_height(struct Box2f* self, const float32_t width, const float32_t height);

/**
 * @brief initialize a box2 from width, height and pose2
 *
 * @param self box2
 * @param width width of the box
 * @param height height of the box
 * @param pose pose of the box
 * @return retcode_t
 */
retcode_t box2f_init_from_width_height_and_pose2f(struct Box2f* self, const float32_t width, const float32_t height,
                                                  const struct Pose2f* pose);

/**
 * @brief initialize a box2 from vector2f and pose2, vector2f contains width and height of the box
 *
 * @param self box2
 * @param dimension dimension of the box
 * @param pose pose of the box
 * @return retcode_t
 */
retcode_t box2f_init_from_vector2f_and_pose2f(struct Box2f* self, const struct Vectorf* dimension,
                                              const struct Pose2f* pose);

/**
 * @brief initialize box2 from another box2
 *
 * @param self box2
 * @param other box2
 * @return retcode_t
 */
retcode_t box2f_init_from_box2f(struct Box2f* self, const struct Box2f* other);

/**
 * @brief check if a box is valid
 *
 * @param self box2
 * @return bool_t
 */
bool_t box2f_is_valid(const struct Box2f* self);

/**
 * @brief check if two boxes are equal
 *
 * @param self box
 * @param other box
 * @return bool_t
 */
bool_t box2f_is_equal(const struct Box2f* self, const struct Box2f* other);

/**
 * @brief check if a box2 contains a point
 *
 * @param self box2
 * @param point point2
 * @return bool_t
 */
bool_t box2f_contains_point2f(const struct Box2f* self, const struct Point2f* point);

/**
 * @brief return the four corner points of the box in world coordinate
 *
 * @note  A box in local frame:
 *        bottom boundary is aligned with x-axis,
 *        left boundary is aligned with y-axis
 *
 *           y
 *           ^
 *           |
 *
 *         (tl)  top (tr)
 *           ***********
 *     left  *         *  right
 *           *         *
 *           ***********    --->x
 *        (bl) bottom (br)
 *
 * @param bl bottom left point
 * @param br bottom left point
 * @param tr bottom left point
 * @param tl bottom left point
 * @return retcode_t
 */
retcode_t box2f_get_corner_points(const struct Box2f* self, struct Point2f* bl, struct Point2f* br, struct Point2f* tr,
                                  struct Point2f* tl);

/**
 * @brief return the minimum and maximum corner points of a box in world coordinate, completely and uniquely enclosed
 *        the box by coordinates parallel to the axis
 *
 * @param self box
 * @param min_pt minimum point
 * @param max_pt maximum point
 * @return retcode_t
 */
retcode_t box2f_get_axis_aligned_external_box(const struct Box2f* self, struct Point2f* min_pt, struct Point2f* max_pt);

/**
 * @brief get the area of the box
 *
 * @param self box
 * @return float32_t area
 */
float32_t box2f_get_area(const struct Box2f* self);

/**
 * @brief return the center of the box
 *
 * @param self box
 * @param center center of the box
 * @return retcode_t
 */
retcode_t box2f_get_center(const struct Box2f* self, struct Point2f* center);

/**
 * @brief compute IOU(Intersection Over Union) of two boxes
 *
 * @Ref http://www.pyimagesearch.com/2016/11/07/intersection-over-union-iou-for-object-detection/
 * @note currently this function only supports box2 with identity rotation matrix
 * @param self box
 * @param other box
 * @return retcode_t
 */
retcode_t box2f_compute_intersection_over_union(const struct Box2f* self, const struct Box2f* other, float32_t* value);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_BOX2_FLOAT32_H_
