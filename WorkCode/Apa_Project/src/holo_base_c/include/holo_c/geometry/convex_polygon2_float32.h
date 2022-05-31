/*!
 * @file convex_polygon2_float32.h
 * @brief This header file defines convex polygon in 2d.
 * @author duyanwei@holomatic.com
 * @date 2019-08-22
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_CONVEX_POLYGON2_FLOAT32_H_
#define HOLO_C_GEOMETRY_CONVEX_POLYGON2_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define convex polygon2 in 2D
 */
struct ConvexPolygon2f
{
    struct Point2f vertices[10u];
    uint8_t        size;
};

HOLO_STATIC_ASSERT(sizeof(struct ConvexPolygon2f) == 84u);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief convex polygon2f vertex maximum size
 *
 * @return uint8_t
 */
static inline uint8_t convex_polygon2f_get_vertex_maximum_size()
{
    return 10u;
}

/**
 * @brief convex polygon2f vertex minimum size
 *
 * @return uint8_t
 */
static inline uint8_t convex_polygon2f_get_vertex_minimum_size()
{
    return 3u;
}

/**
 * @brief init a convex polygon2
 *
 * @param self convex polygon
 * @return retcode_t
 */
retcode_t convex_polygon2f_init(struct ConvexPolygon2f* self);

/**
 * @brief init a convex polygon2 from multiple points in an array
 *
 * @param self convex polygon
 * @param buffer point2f array
 * @param buffer_size the number of point2f in array
 * @return retcode_t
 */
retcode_t convex_polygon2f_init_from_point2f_array(struct ConvexPolygon2f* self, const struct Point2f* buffer,
                                                   const uint8_t buffer_size);

/**
 * @brief init a polygon2 from the other polygon2
 *
 * @param self polygon
 * @param other polygon
 * @return retcode_t
 */
retcode_t convex_polygon2f_init_from_convex_polygon2f(struct ConvexPolygon2f*       self,
                                                      const struct ConvexPolygon2f* other);

/**
 * @brief check if a convex polygon2 is valid
 *
 * @param self polygon
 * @return bool_t
 */
bool_t convex_polygon2f_is_valid(const struct ConvexPolygon2f* self);

/**
 * @brief check if two polygons are equal
 *
 * @param lhs left convex polygon
 * @param rhs right convex polygon
 * @return bool_t
 */
bool_t convex_polygon2f_is_equal(const struct ConvexPolygon2f* lhs, const struct ConvexPolygon2f* rhs);

/**
 * @brief check if a point is within a convex polygon
 *
 * @param self polygon
 * @param point point
 * @return bool_t
 */
bool_t convex_polygon2f_if_contains_point2f(const struct ConvexPolygon2f* self, const struct Point2f* point);

/**
 * @brief add a vertex/point to polygon
 *
 * @param self polygon
 * @param point vertex/point
 * @return retcode_t
 */
retcode_t convex_polygon2f_add_vertex(struct ConvexPolygon2f* self, const struct Point2f* point);

/**
 * @brief set a vertex/point of polygon
 *
 * @param self polygon
 * @param index index of point
 * @param point vertex/point
 * @return retcode_t
 */
retcode_t convex_polygon2f_set_vertex(struct ConvexPolygon2f* self, const uint8_t index, const struct Point2f* point);

/**
 * @brief get a vertex/point of polygon
 *
 * @param self polygon
 * @param index index of point
 * @param point vertex/point
 * @return retcode_t
 */
retcode_t convex_polygon2f_get_vertex(const struct ConvexPolygon2f* self, const uint8_t index, struct Point2f* point);

/**
 * @brief get polygon vertex size
 *
 * @param self polygon
 * @return uint8_t
 */
uint8_t convex_polygon2f_get_vertex_size(const struct ConvexPolygon2f* self);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_CONVEX_POLYGON2_FLOAT32_H_
