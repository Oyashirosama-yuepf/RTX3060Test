/*!
 * @file point3_float32.h
 * @brief This header file defines point in 3d.
 * @author liuya(liuya@holomaitc.com), duyanwei@holomatic.com
 * @date 2019-08-11
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_POINT3_FLOAT32_H_
#define HOLO_C_GEOMETRY_POINT3_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/vector_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define point3 struct
 */
struct Point3f
{
    float32_t x;
    float32_t y;
    float32_t z;
};

HOLO_STATIC_ASSERT(sizeof(struct Point3f) == 12u);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief return the dimension of point3
 *
 * @return uint8_t
 */
static inline uint8_t point3f_dim()
{
    return 3u;
}

/**
 * @brief init point3f from three scalars
 *
 * @param self point3f
 * @param x x value
 * @param y y value
 * @param z z value
 * @return retcode_t
 */
retcode_t point3f_init_from_scalars(struct Point3f* self, const float32_t x, const float32_t y, const float32_t z);

/**
 * @brief init point3f to zero
 *
 * @param self point3f
 * @return retcode_t
 */
retcode_t point3f_init(struct Point3f* self);

/**
 * @brief init point3f from raw data array
 *
 * @param self point3f
 * @param array raw data array
 * @param array_size array size
 * @return retcode_t
 */
retcode_t point3f_init_from_array(struct Point3f* self, const float32_t* array, const uint8_t array_size);

/**
 * @brief init point3f from vector3f
 *
 * @param self point3f
 * @param vector vector3f
 * @return retcode_t
 */
retcode_t point3f_init_from_vector3f(struct Point3f* self, const struct Vectorf* vector);

/**
 * @brief init point3f from another point3f
 *
 * @param self point3f
 * @param other point3f
 * @return retcode_t
 */
retcode_t point3f_init_from_point3f(struct Point3f* self, const struct Point3f* other);

/**
 * @brief check if the point is is_valid
 *
 * @param self point3f
 * @return bool_t
 */
bool_t point3f_is_valid(const struct Point3f* self);

/**
 * @brief check if two points are equal
 *
 * @param self point3f
 * @param other point3f
 * @return bool_t
 */
bool_t point3f_is_equal(const struct Point3f* self, const struct Point3f* other);

/**
 * @brief add two points (out = self + other)
 *
 * @param self point3f
 * @param other point3f
 * @param out point3f
 * @return retcode_t
 */
retcode_t point3f_add(const struct Point3f* self, const struct Point3f* other, struct Point3f* out);

/**
 * @brief add a point and a vector (out = self + other)
 *
 * @param self point3f
 * @param other vector3f
 * @param out point3f
 * @return retcode_t
 */
retcode_t point3f_add_vector3f(const struct Point3f* self, const struct Vectorf* other, struct Point3f* out);

/**
 * @brief subtract two points, the result is a vector (out = self - other)
 *
 * @param self point3f
 * @param other point3f
 * @param out vector3f
 * @return retcode_t
 */
retcode_t point3f_sub(const struct Point3f* self, const struct Point3f* other, struct Vectorf* out);

/**
 * @brief subtract a vector from a point, the result is a point (out = self - other)
 *
 * @param self point3f
 * @param other vector3f
 * @param out point3f
 * @return retcode_t
 */
retcode_t point3f_sub_vector3f(const struct Point3f* self, const struct Vectorf* other, struct Point3f* out);

/**
 * @brief negate a point (self =-self)
 *
 * @param self point3f
 * @return retcode_t
 */
retcode_t point3f_negate(struct Point3f* self);

/**
 * @brief multiply a scalar (out = self * s or out = s * self)
 *
 * @param self point3f
 * @param scalar scalar vaule
 * @param out point3f
 * @return retcode_t
 */
retcode_t point3f_multiply_float32(const struct Point3f* self, const float32_t scalar, struct Point3f* out);

/**
 * @brief divide a scalar (out = self / s)
 *
 * @param self point3f
 * @param scalar scalar vaule
 * @param out point3f
 * @return retcode_t
 */
retcode_t point3f_divide_float32(const struct Point3f* self, const float32_t scalar, struct Point3f* out);

/**
 * @brief convert a point3f to vector3f
 *
 * @param self point3f
 * @param out vector3f
 * @return retcode_t
 */
retcode_t point3f_to_vector3f(const struct Point3f* self, struct Vectorf* out);

/**
 * @brief return the homogeneous form a point3
 *
 * @param self point3f
 * @param out vectorf,  4x1
 * @return retcode_t
 */
retcode_t point3f_homogeneous(const struct Point3f* self, struct Vectorf* out);

/**
 * @brief compute the squared distance beteween two points
 *
 * @param self point3f
 * @param other point3f
 * @param dist_sqr the squared distance between two points
 * @return retcode_t
 */
retcode_t point3f_dist_sqr(const struct Point3f* self, const struct Point3f* other, float32_t* dist_sqr);

/**
 * @brief compute the distance beteween two points
 *
 * @param self point3f
 * @param other point3f
 * @param out the distance between two points
 * @return float32_t
 */
retcode_t point3f_dist(const struct Point3f* self, const struct Point3f* other, float32_t* dist);

/**
 * @brief check if a point is a finite point
 *
 * @param self point3f
 * @return bool_t
 */
bool_t point3f_is_finite(const struct Point3f* self);

/**
 * @brief check if a point is zero (all values are equal to zero)
 *
 * @param self point3f
 * @return bool_t
 */
bool_t point3f_is_zero(const struct Point3f* self);

/**
 * @brief set a point to some constant value
 *
 * @param self point3f
 * @param value constant value
 * @return retcode_t
 */
retcode_t point3f_set_constant(struct Point3f* self, const float32_t value);

/**
 * @brief set a point to zero
 *
 * @param self point3f
 * @return retcode_t
 */
retcode_t point3f_set_zero(struct Point3f* self);

/**
 * @brief return a point (1, 0, 0)
 *
 * @param self point3f
 * @return retcode_t
 */
retcode_t point3f_set_unit_x(struct Point3f* self);

/**
 * @brief return a point (0, 1, 0)
 *
 * @param self point3f
 * @return retcode_t
 */
retcode_t point3f_set_unit_y(struct Point3f* self);

/**
 * @brief return a point (0, 0, 1)
 *
 * @param self point3f
 * @return retcode_t
 */
retcode_t point3f_set_unit_z(struct Point3f* self);

/**
 * @brief expmap
 *
 * @param self point3f
 * @param vector vectorf, 3x1
 * @return retcode_t
 */
retcode_t point3f_expmap(struct Point3f* self, const struct Vectorf* vector);

/**
 * @brief logmap
 *
 * @param self point3f
 * @param vector vector3f,3x1
 * @return retcode_t
 */
retcode_t point3f_logmap(const struct Point3f* self, struct Vectorf* vector);

/**
 * @brief get x of point3
 *
 * @param self point3
 * @return float32_t
 */
float32_t point3f_get_x(const struct Point3f* self);

/**
 * @brief get y of point3
 *
 * @param self point3
 * @return float32_t
 */
float32_t point3f_get_y(const struct Point3f* self);

/**
 * @brief get z of point3
 *
 * @param self point3
 * @return float32_t
 */
float32_t point3f_get_z(const struct Point3f* self);

/**
 * @brief set x of point3
 *
 * @param self point3
 * @param value scalar value
 * @return retcode_t
 */
retcode_t point3f_set_x(struct Point3f* self, const float32_t value);

/**
 * @brief set y of point3
 *
 * @param self point3
 * @param value scalar value
 * @return retcode_t
 */
retcode_t point3f_set_y(struct Point3f* self, const float32_t value);

/**
 * @brief set z of point3
 *
 * @param self point3
 * @param value scalar value
 * @return retcode_t
 */
retcode_t point3f_set_z(struct Point3f* self, const float32_t value);

/**
 * @{
 * Begin serialization/deserialization API group
 */

/**
 * @brief Get serialized buffer size for Point3f. Alignment is base on project configuration.
 * @detail Alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param self The Point3f object.
 *
 * @return Serialized size
 */
uint32_t point3f_get_serialized_size(const struct Point3f* self);

/**
 * @brief Serialize Point3f. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param self The Point3f object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes serialized into buffer
 */
retcode_t point3f_serialize(const struct Point3f* self,
                            uint8_t* buffer,
                            uint32_t buffer_size);

/**
 * @brief Deserialize Point3f object. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param self The Point3f object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes deserialized from buffer
 */
retcode_t point3f_deserialize(struct Point3f* self,
                              const uint8_t* buffer,
                              uint32_t buffer_size);

/**
 * @}
 * End serialization/deserialization API group.
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_POINT3_FLOAT32_H_
