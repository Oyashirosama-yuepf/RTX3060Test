/*!
 * @file quaternion_float32.h
 * @brief This header file defines quaternion type in holo_c.
 * @author duyanwei@holomatic.com
 * @date 2019-08-22
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_QUATERNION_FLOAT32_H_
#define HOLO_C_GEOMETRY_QUATERNION_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/matrix_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define common float32_t quaternion struct
 *
 */
struct Quaternionf
{
    float32_t w;
    float32_t x;
    float32_t y;
    float32_t z;
};

HOLO_STATIC_ASSERT(sizeof(struct Quaternionf) == 16u);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize a quaternion from raw quaternions
 *
 * @param quaternion quaternion
 * @param w w value
 * @param x x value
 * @param y y value
 * @param z z value
 * @return retcode_t
 */
retcode_t quaternionf_init_from_scalars(struct Quaternionf* quaternion, const float32_t w, const float32_t x,
                                        const float32_t y, const float32_t z);
/**
 * @brief initialize a quaternion to unit quaternion
 *
 * @param quaternion quaternion
 * @return retcode_t
 */
retcode_t quaternionf_init(struct Quaternionf* quaternion);

/**
 * @brief init quaternion from another quaternion
 *
 * @param self quaternion
 * @param other quaternion
 * @return retcode_t
 */
retcode_t quaternionf_init_from_quaternionf(struct Quaternionf* self, const struct Quaternionf* other);

/**
 * @brief check quaternion validity
 *
 * @param quaternion quaternion
 * @return bool_t
 */
bool_t quaternionf_is_valid(const struct Quaternionf* quaternion);

/**
 * @brief check if two quaternions are equal
 *
 * @param lhs left quaternion
 * @param rhs right quaternion
 * @return bool_t
 */
bool_t quaternionf_is_equal(const struct Quaternionf* lhs, const struct Quaternionf* rhs);

/**
 * @brief convert a quaterion to matrixf for 3x3
 *
 * @param quaternion
 * @param rot
 * @return retcode_t
 */
retcode_t quaternionf_to_matrix33f(const struct Quaternionf* quaternion, struct Matrixf* mat);

/**
 * @brief dot product of two quaternions
 *
 * @param lhs left quaterion
 * @param rhs right quaternion
 * @param out dot result
 * @return retcode_t
 */
retcode_t quaternionf_dot(const struct Quaternionf* lhs, const struct Quaternionf* rhs, float32_t* out);

/**
 * @brief slerp in quaternion
 *
 * @param left left quaternion
 * @param right right quaternion
 * @param t interolation value
 * @param out interpolated quaternion
 * @return retcode_t
 */
retcode_t quaternionf_slerp(const struct Quaternionf* left, const struct Quaternionf* right, const float32_t t,
                            struct Quaternionf* out);

/**
 * @brief quaternion multiply a scalar
 *
 * @param self quaternion
 * @param scalar scale value
 * @param out quaternion
 * @return retcode_t
 */
retcode_t quaternionf_multiply_float32(const struct Quaternionf* self, const float32_t scalar, struct Quaternionf* out);

/**
 * @brief compute the norm of a quaternion
 *
 * @param quaternion quaternion
 * @return float32_t
 */
float32_t quaternionf_get_norm(const struct Quaternionf* quaternion);

/**
 * @brief normalize a quaternion
 *
 * @param quaternion quaternion
 * @return retcode_t
 */
retcode_t quaternionf_normalize(struct Quaternionf* quaternion);

/**
 * @brief check if a quaternion is normalized
 *
 * @param quaternion quaternion
 * @return bool_t
 */
bool_t quaternionf_is_normalized(const struct Quaternionf* quaternion);

/**
 * @brief set quaternion to identity
 *
 * @param quaternion
 * @return retcode_t
 */
retcode_t quaternionf_set_identity(struct Quaternionf* quaternion);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_QUATERNION_FLOAT32_H_
