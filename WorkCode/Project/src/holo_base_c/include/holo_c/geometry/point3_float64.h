/*!
 * @file point3_float64.h
 * @brief This header file defines point in 3d.
 * @author liuya(liuya@holomaitc.com), duyanwei@holomatic.com
 * @date 2019-08-11
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_POINT3_FLOAT64_H_
#define HOLO_C_GEOMETRY_POINT3_FLOAT64_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define point3 struct
 */
struct Point3d
{
    float64_t x;
    float64_t y;
    float64_t z;
};

HOLO_STATIC_ASSERT(sizeof(struct Point3d) == 24u);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief return the dimension of point3
 *
 * @return uint8_t
 */
static inline uint8_t point3d_dim()
{
    return 3u;
}

/**
 * @brief init point3d from three scalars
 *
 * @param self point3d
 * @param x x value
 * @param y y value
 * @param z z value
 * @return retcode_t
 */
retcode_t point3d_init_from_scalars(struct Point3d* self, const float64_t x, const float64_t y, const float64_t z);

/**
 * @brief init point3d to zero
 *
 * @param self point3d
 * @return retcode_t
 */
retcode_t point3d_init(struct Point3d* self);

/**
 * @brief init point3d from raw data array
 *
 * @param self point3d
 * @param array raw data array
 * @param array_size array size
 * @return retcode_t
 */
retcode_t point3d_init_from_array(struct Point3d* self, const float64_t* array, const uint8_t array_size);

/**
 * @brief init point3d from another point3d
 *
 * @param self point3d
 * @param other point3d
 * @return retcode_t
 */
retcode_t point3d_init_from_point3d(struct Point3d* self, const struct Point3d* other);

/**
 * @brief check if the point is is_valid
 *
 * @param self point3d
 * @return bool_t
 */
bool_t point3d_is_valid(const struct Point3d* self);

/**
 * @brief check if two points are equal
 *
 * @param self point3d
 * @param other point3d
 * @return bool_t
 */
bool_t point3d_is_equal(const struct Point3d* self, const struct Point3d* other);

/**
 * @brief add two points (out = self + other)
 *
 * @param self point3d
 * @param other point3d
 * @param out point3d
 * @return retcode_t
 */
retcode_t point3d_add(const struct Point3d* self, const struct Point3d* other, struct Point3d* out);

/**
 * @brief negate a point (self =-self)
 *
 * @param self point3d
 * @return retcode_t
 */
retcode_t point3d_negate(struct Point3d* self);

/**
 * @brief multiply a scalar (out = self * s or out = s * self)
 *
 * @param self point3d
 * @param scalar scalar vaule
 * @param out point3d
 * @return retcode_t
 */
retcode_t point3d_multiply_float64(const struct Point3d* self, const float64_t scalar, struct Point3d* out);

/**
 * @brief divide a scalar (out = self / s)
 *
 * @param self point3d
 * @param scalar scalar vaule
 * @param out point3d
 * @return retcode_t
 */
retcode_t point3d_divide_float64(const struct Point3d* self, const float64_t scalar, struct Point3d* out);

/**
 * @brief compute the squared distance beteween two points
 *
 * @param self point3d
 * @param other point3d
 * @param dist_sqr the squared distance between two points
 * @return retcode_t
 */
retcode_t point3d_dist_sqr(const struct Point3d* self, const struct Point3d* other, float64_t* dist_sqr);

/**
 * @brief compute the distance beteween two points
 *
 * @param self point3d
 * @param other point3d
 * @param out the distance between two points
 * @return float64_t
 */
retcode_t point3d_dist(const struct Point3d* self, const struct Point3d* other, float64_t* dist);

/**
 * @brief check if a point is a finite point
 *
 * @param self point3d
 * @return bool_t
 */
bool_t point3d_is_finite(const struct Point3d* self);

/**
 * @brief check if a point is zero (all values are equal to zero)
 *
 * @param self point3d
 * @return bool_t
 */
bool_t point3d_is_zero(const struct Point3d* self);

/**
 * @brief set a point to some constant value
 *
 * @param self point3d
 * @param value constant value
 * @return retcode_t
 */
retcode_t point3d_set_constant(struct Point3d* self, const float64_t value);

/**
 * @brief set a point to zero
 *
 * @param self point3d
 * @return retcode_t
 */
retcode_t point3d_set_zero(struct Point3d* self);

/**
 * @brief return a point (1, 0, 0)
 *
 * @param self point3d
 * @return retcode_t
 */
retcode_t point3d_set_unit_x(struct Point3d* self);

/**
 * @brief return a point (0, 1, 0)
 *
 * @param self point3d
 * @return retcode_t
 */
retcode_t point3d_set_unit_y(struct Point3d* self);

/**
 * @brief return a point (0, 0, 1)
 *
 * @param self point3d
 * @return retcode_t
 */
retcode_t point3d_set_unit_z(struct Point3d* self);

/**
 * @brief get x of point3
 *
 * @param self point3
 * @return float64_t
 */
float64_t point3d_get_x(const struct Point3d* self);

/**
 * @brief get y of point3
 *
 * @param self point3
 * @return float64_t
 */
float64_t point3d_get_y(const struct Point3d* self);

/**
 * @brief get z of point3
 *
 * @param self point3
 * @return float64_t
 */
float64_t point3d_get_z(const struct Point3d* self);

/**
 * @brief set x of point3
 *
 * @param self point3
 * @param value scalar value
 * @return retcode_t
 */
retcode_t point3d_set_x(struct Point3d* self, const float64_t value);

/**
 * @brief set y of point3
 *
 * @param self point3
 * @param value scalar value
 * @return retcode_t
 */
retcode_t point3d_set_y(struct Point3d* self, const float64_t value);

/**
 * @brief set z of point3
 *
 * @param self point3
 * @param value scalar value
 * @return retcode_t
 */
retcode_t point3d_set_z(struct Point3d* self, const float64_t value);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_POINT3_FLOAT64_H_
