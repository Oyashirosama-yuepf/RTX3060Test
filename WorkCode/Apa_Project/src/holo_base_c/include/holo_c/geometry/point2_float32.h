/*!
 * @file point2_float32.h
 * @brief This header file define 2D point.
 * @author liuya(liuya@holomaitc.com), lichao@holomatic.com
 * @date 2018-12-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_GEOMETRY_POINT2_FLOAT32_H_
#define HOLO_C_GEOMETRY_POINT2_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief define 2D point
 *
 */
struct Point2f
{
    float32_t x;
    float32_t y;
};

/* check the size of 2D point with static assert */
HOLO_STATIC_ASSERT(sizeof(struct Point2f) == 8);

/**
 * @brief initialize a 2D point to zero
 *
 * @param self point which to be initialized
 * @return retcode_t
 */
retcode_t point2f_init(struct Point2f* self);

/**
 * @brief initialize a 2D point from x, y values in meters
 *
 * @param self point which to be initialized
 * @param x x value in meters
 * @param y y value in meters
 * @return retcode_t
 */
retcode_t point2f_init_from_scalars(struct Point2f* self, float32_t x, float32_t y);

/**
 * @brief initialize a 2D point from array
 *
 * @param self a 2D point
 * @param array raw data array
 * @param array_size array size
 * @return retcode_t RC_FAIL if array_size > 2
 * @return retcode_t RC_SUCCESS
 */
retcode_t point2f_init_from_array(struct Point2f* self, const float32_t* array, const uint8_t array_size);

/**
 * @brief initialize a 2D point from 2D vector
 *
 * @param self 2D point which to be initialized
 * @param vector 2D vector
 * @return retcode_t
 */
retcode_t point2f_init_from_vector2f(struct Point2f* self, const struct Vectorf* vector);

/**
 * @brief initialize a 2D point from another 2D point
 *
 * @param self
 * @param in
 * @return retcode_t
 */
retcode_t point2f_init_from_point2f(struct Point2f* self, const struct Point2f* other);

/**
 * @brief a 2D point add another 2D point
 *
 * @param self the first point to be added
 * @param other the second point to be added
 * @param out combined point
 * @return retcode_t
 */
retcode_t point2f_add(const struct Point2f* self, const struct Point2f* other, struct Point2f* out);

/**
 * @brief add a 2D vector to 2D point
 *
 * @param self the first point to be added
 * @param vector a 2D vector
 * @param out combined point
 * @return retcode_t
 */
retcode_t point2f_add_vector2f(const struct Point2f* self, const struct Vectorf* vector, struct Point2f* out);

/**
 * @brief translate a 2D point with a 2D vector
 *
 * @param self a 2D point to be translated
 * @param in a translation vector
 * @param out a translated 2D point
 * @return retcode_t
 */
retcode_t point2f_translate(const struct Point2f* self, const struct Vectorf* in, struct Point2f* out);

/**
 * @brief translate a 2D point with a 2D vector in reverse direction
 *
 * @param self a 2D point to be translated
 * @param in a translation vector
 * @param out a translated 2D point
 * @return retcode_t
 */
retcode_t point2f_reverse_translate(const struct Point2f* self, const struct Vectorf* in, struct Point2f* out);

/**
 * @brief compute a 2D vector from two 2D points
 *
 * @param self a end point
 * @param other a start point
 * @param out a 2D vector
 * @return retcode_t
 */
retcode_t point2f_sub(const struct Point2f* self, const struct Point2f* other, struct Vectorf* out);

/**
 * @brief negate a 2D point
 *
 * @param self 2D point to be negated
 * @param out 2D negated point
 * @return retcode_t
 */
retcode_t point2f_negate(const struct Point2f* self, struct Point2f* out);

/**
 * @brief judge if two 2D points are equivalent
 *
 * @param self the first 2D point
 * @param other the second 2D point
 * @return bool_t true for equal, otherwise inequal
 */
bool_t point2f_is_equal(const struct Point2f* self, const struct Point2f* other);

/**
 * @brief multiply a 2D point with a float32_t value
 *
 * @param self 2D point to be scaled
 * @param scale the float32_t value
 * @param out 2D scaled point
 * @return retcode_t
 */
retcode_t point2f_multiply_float32(const struct Point2f* self, float32_t scale, struct Point2f* out);

/**
 * @brief divide a 2D point by a float32_t value
 *
 * @param self 2D point to be scaled
 * @param scale the float32_t value
 * @param out 2D point
 * @return retcode_t
 */
retcode_t point2f_divide_float32(const struct Point2f* self, float32_t scale, struct Point2f* out);

/**
 * @brief compute the distance between two 2D points
 *
 * @param self the first 2D point
 * @param other the second 2D point
 * @param out the distance value
 * @return retcode_t
 */
retcode_t point2f_dist(const struct Point2f* self, const struct Point2f* other, float32_t* out);

/**
 * @brief compute the squared distance between two 2D points
 *
 * @param self the first 2D point
 * @param other the second 2D point
 * @param out the squared distance
 * @return retcode_t
 */
retcode_t point2f_dist_sqr(const struct Point2f* self, const struct Point2f* other, float32_t* out);

/**
 * @brief getter for x value
 *
 * @param self a 2D point
 * @return x value in meters
 */
float32_t point2f_get_x(const struct Point2f* self);

/**
 * @brief getter for y value
 *
 * @param self a 2D point
 * @return y value in meters
 */
float32_t point2f_get_y(const struct Point2f* self);

/**
 * @brief setter for x value
 *
 * @param self a 2D point
 * @param in x value in meters
 * @return retcode_t
 */
retcode_t point2f_set_x(struct Point2f* self, float32_t in);

/**
 * @brief setter for y value
 *
 * @param self a 2D point
 * @param in y value in meters
 * @return retcode_t
 */
retcode_t point2f_set_y(struct Point2f* self, float32_t in);

/**
 * @brief convert 2D point to 2D vector
 *
 * @param self a 2D point
 * @param out the converted 2D vector
 * @return retcode_t
 */
retcode_t point2f_to_vector2f(const struct Point2f* self, struct Vectorf* out);

/**
 * @brief convert a 2D point to its homogeneous coordinate.
 *
 * @param self the 2D point
 * @param out the homogeneous coordinate vector of a 2D point
 * @return retcode_t
 */
retcode_t point2f_homogeneous(const struct Point2f* self, struct Vectorf* out);

/**
 * @brief lie group exponential map
 *
 * @param self a lie algebra of 2D point
 * @param out a lie group of 2D point
 * @return retcode_t
 */
retcode_t point2f_expmap(const struct Vectorf* self, struct Point2f* out);

/**
 * @brief lie group logarithmic map
 *
 * @param self a lie group of 2D point
 * @param out a lie algebra of 2D point
 * @return retcode_t
 */
retcode_t point2f_logmap(const struct Point2f* self, struct Vectorf* out);

/**
 * @brief return a 2D zero point
 *
 * @param self a 2D zero point
 * @return retcode_t
 */
retcode_t point2f_set_zero(struct Point2f* self);

/**
 * @brief return a 2D point on x axis with unit length
 *
 * @param self a 2D point on x axis with unit length
 * @return retcode_t
 */
retcode_t point2f_set_unit_x(struct Point2f* self);

/**
 * @brief return a 2D point on y axis with unit length
 *
 * @param self a 2D point on y axis with unit length
 * @return retcode_t
 */
retcode_t point2f_set_unit_y(struct Point2f* self);

/**
 * @brief return the dimension of 2D point
 *
 * @return dimension
 */
static inline uint8_t point2f_dim()
{
    return 2;
}

/**
 * @brief convert 2D point to string
 *
 * @param self a 2D point
 * @param string_buf string
 * @param buffer_length the length of string buffer
 * @return retcode_t
 */
retcode_t point2f_to_string(const struct Point2f* self, char_t* string_buf, uint32_t buffer_length);

/**
 * @brief check the validation of a 2D point
 *
 * @param self a 2D point to be validated
 * @return bool_t valid or not
 */
bool_t point2f_is_valid(const struct Point2f* self);

/**
 * @brief check x and y are finite
 *
 * @param self a 2D point to be checked
 * @return bool_t true for finite, otherwise false
 */
bool_t point2f_is_finite(const struct Point2f* self);

/**
 * @brief check a 2D point is a 2D zero point
 *
 * @param self a 2D point to be checked
 * @return bool_t true for zero, otherwise non-zero
 */
bool_t point2f_is_zero(const struct Point2f* self);

/**
 * @brief get serialized buffer size for a 2D point
 *
 * @param self a 2D point to be serialized
 * @return buffer size
 */
uint32_t point2f_get_serialized_size(const struct Point2f* self);

/**
 * @brief serialize a 2D point to buffer
 *
 * @param self a 2D point to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 */
retcode_t point2f_serialize(const struct Point2f* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief deserialize a 2D point to buffer
 *
 * @param self a 2D point to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes deserialized info buffer.
 */
retcode_t point2f_deserialize(struct Point2f* self, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_GEOMETRY_POINT2_FLOAT32_H_ */
