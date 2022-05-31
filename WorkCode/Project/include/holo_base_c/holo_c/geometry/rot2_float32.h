/*!
 * @file rot2_float32.h
 * @brief This header file define rotation in 2D space.
 * @author liuya(liuya@holomaitc.com), lichao@holomatic.com
 * @date 2018-12-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_GEOMETRY_ROT2_FLOAT32_H_
#define HOLO_C_GEOMETRY_ROT2_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/matrix.h>
#include <holo_c/numerics/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief define 2D point
 *
 */
struct Rot2f
{
    float32_t c;  // cos
    float32_t s;  // sin
};

/* check the size of 2D rotation with static assert */
HOLO_STATIC_ASSERT(sizeof(struct Rot2f) == 8);

/**
 * @brief initialize 2D rotation to identity
 *
 * @param self a 2D rotation
 * @return retcode_t
 */
retcode_t rot2f_init(struct Rot2f* self);

/**
 * @brief initialize 2D rotation from angle in radians
 *
 * @param self a 2D rotation
 * @param theta theta angle in radians
 * @return retcode_t
 */
retcode_t rot2f_init_from_angle(struct Rot2f* self, const float32_t theta);

/**
 * @brief initialize 2D rotation from 2x2 rotation matrix
 *
 * @param self a 2D rotation
 * @param in 2x2 rotation matrix
 * @return retcode_t
 */
retcode_t rot2f_init_from_matrix(struct Rot2f* self, const struct Matrixf* in);

/**
 * @brief initialize 2D rotation from another 2D rotation
 *
 * @param self a 2D rotation
 * @param in a 2D rotation
 * @return retcode_t
 */
retcode_t rot2f_init_from_rot2f(struct Rot2f* self, const struct Rot2f* in);

/**
 * @brief compute inverse 2D rotation - negative angle
 *
 * @param self a 2D rotation
 * @param out the inverse 2D rotation
 * @return retcode_t
 */
retcode_t rot2f_inverse(const struct Rot2f* self, struct Rot2f* out);

/**
 * @brief rotate 2D point from rotated coordinate to world
 *
 * @param self a 2D rotation
 * @param in a 2D point
 * @param out rotated 2D point
 * @return retcode_t
 */
retcode_t rot2f_rotate_point2f(const struct Rot2f* self, const struct Point2f* in, struct Point2f* out);

/**
 * @brief rotate 2D vector from rotated coordinate to world
 *
 * @param self a 2D rotation
 * @param in a 2D vector
 * @param out rotated 2D vector
 * @return retcode_t
 */
retcode_t rot2f_rotate_vector2f(const struct Rot2f* self, const struct Vectorf* in, struct Vectorf* out);

/**
 * @brief unrotated point from world to rotated coordinate
 * \f$ p^c = (R_c^w)^T p^w \f$
 * @param self a 2D rotation
 * @param in a 2D point
 * @param out rotated 2D point
 * @return retcode_t
 */
retcode_t rot2f_unrotate_point2f(const struct Rot2f* self, const struct Point2f* in, struct Point2f* out);

/**
 * @brief unrotated vector from world to rotated coordinate
 * \f$ v^c = (R_c^w)^T v^w \f$
 * @param self a 2D rotation
 * @param in a 2D vector
 * @param out rotated 2D vector
 * @return retcode_t
 */
retcode_t rot2f_unrotate_vector2f(const struct Rot2f* self, const struct Vectorf* in, struct Vectorf* out);

/**
 * @brief compose two 2D rotations
 *
 * @param self a 2D rotation
 * @param other another 2D rotation
 * @param out composed 2D rotation
 * @return retcode_t
 */
retcode_t rot2f_compose(const struct Rot2f* self, const struct Rot2f* other, struct Rot2f* out);

/**
 * @brief judge if two 2D rotations are equivalent
 *
 * @param self a 2D rotation
 * @param other another 2D rotation
 * @return bool_t
 */
bool_t rot2f_is_equal(const struct Rot2f* self, const struct Rot2f* other);

/**
 * @brief get 2x2 rotation matrix
 *
 * @param self a 2D rotation
 * @param out 2x2 rotation matrix
 * @return retcode_t
 */
retcode_t rot2f_to_matrix22f(const struct Rot2f* self, struct Matrixf* out);

/**
 * @brief get rotation angle in radians
 *
 * @param self a 2D rotation
 * @param out rotation angle
 * @return retcode_t
 */
retcode_t rot2f_get_angle(const struct Rot2f* self, float32_t* out);

/**
 * @brief set a 2D rotation to identity rotation
 *
 * @param self a 2D rotation
 * @return retcode_t
 */
retcode_t rot2f_set_identity(struct Rot2f* self);

/**
 * @brief get dimension of 2D rotation
 *
 * @param self a 2D rotation
 * @return dimension - 2
 */
static inline uint8_t rot2f_dim()
{
    return 2;
}

/**
 * @brief convert 2D rotation to string
 *
 * @param self a 2D rotation
 * @param string_buf string
 * @param buffer_length the length of string buffer
 * @return retcode_t
 */
retcode_t rot2f_to_string(const struct Rot2f* self, char_t* string_buf, uint32_t buffer_length);

/**
 * @brief check the validation of a 2D rotation
 *
 * @param self a 2D rotation
 * @return bool_t
 */
bool_t rot2f_is_valid(const struct Rot2f* self);

/**
 * @brief get serialized buffer size for a 2D rotation
 *
 * @param self a 2D rotation to be serialized
 * @return buffer size
 */
uint32_t rot2f_get_serialized_size(const struct Rot2f* self);

/**
 * @brief serialize a 2D rotation to buffer
 *
 * @param self a 2D rotation to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 */
retcode_t rot2f_serialize(const struct Rot2f* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief deserialize a 2D rotation to buffer
 *
 * @param self a 2D rotation to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes deserialized info buffer.
 */
retcode_t rot2f_deserialize(struct Rot2f* self, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_ROT2_FLOAT32_H_
