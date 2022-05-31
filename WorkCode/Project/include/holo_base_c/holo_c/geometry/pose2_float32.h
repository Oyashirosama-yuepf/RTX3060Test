/*!
 * @file pose2_float32.h
 * @brief This header file define pose in 2D space.
 * @author lichao@holomatic.com
 * @date Aug 20, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_GEOMETRY_POSE2_FLOAT32_H_
#define HOLO_C_GEOMETRY_POSE2_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2_float32.h>
#include <holo_c/geometry/rot2_float32.h>
#include <holo_c/numerics/matrix.h>
#include <holo_c/numerics/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief define 2D point
 *
 */
struct Pose2f
{
    struct Rot2f   rotation;     // 2D pose
    struct Point2f translation;  // 2D position
};

/* check the size of 2D pose with static assert */
HOLO_STATIC_ASSERT(sizeof(struct Pose2f) == 16);

/**
 * @brief initialize 2D pose to identity
 *
 * @param self a 2D pose
 * @return retcode_t
 */
retcode_t pose2f_init(struct Pose2f* self);

/**
 * @brief initialize 2D pose from 2D rotation and 2D point
 *
 * @param self a 2D pose
 * @param rot a 2D rotation
 * @param point a 2D point
 * @return retcode_t
 */
retcode_t pose2f_init_from_rot2f_and_point2f(struct Pose2f* self, const struct Rot2f* rot, const struct Point2f* point);

/**
 * @brief initialize 2D pose from angle in radians and 2D point in meters
 *
 * @param self a 2D pose
 * @param theta theta angle in radians
 * @param point 2D point
 * @return retcode_t
 */
retcode_t pose2f_init_from_angle_and_point2f(struct Pose2f* self, const float32_t theta, const struct Point2f* point);

/**
 * @brief initialize 2D pose from 3x3 transformation matrix
 *
 * @param self a 2D pose
 * @param mat a 3x3 transformation matrix
 * @return retcode_t
 */
retcode_t pose2f_init_from_matrix33f(struct Pose2f* self, const struct Matrixf* mat);

/**
 * @brief initialize 2D pose from angle in radians and x,y in meters
 *
 * @param self a 2D pose
 * @param in a 2D pose
 * @return retcode_t
 */
retcode_t pose2f_init_from_pose2f(struct Pose2f* self, const struct Pose2f* in);

/**
 * @brief compose two 2D poses - T_13 = T_12 * T_23
 *
 * @param self a 2D pose
 * @param other another 2D pose
 * @param out the composed 2D pose
 * @return retcode_t
 */
retcode_t pose2f_compose(const struct Pose2f* self, const struct Pose2f* other, struct Pose2f* out);

/**
 * @brief multiply by a 2D point - P_w = T_wb * P_b
 *
 * @param self a 2D pose
 * @param in a 2D point
 * @param out transformed 2D point
 * @return retcode_t
 */
retcode_t pose2f_multiply_point2f(const struct Pose2f* self, const struct Point2f* in, struct Point2f* out);

/**
 * @brief multiply by a 2D vector - V_w = T_wb * V_b
 *
 * @param self a 2D pose
 * @param in a 2D vector
 * @param out transformed 2D vector
 * @return retcode_t
 */
retcode_t pose2f_multiply_vector2f(const struct Pose2f* self, const struct Vectorf* in, struct Vectorf* out);

/**
 * @brief judge if two 2D poses are equivalent
 *
 * @param self a 2D pose
 * @param other another 2D pose
 * @return retcode_t
 */
bool_t pose2f_is_equal(const struct Pose2f* self, const struct Pose2f* other);

/**
 * @brief compute inverse 2D pose - negative angle
 *
 * @param self a 2D pose
 * @param out the inverse 2D pose
 * @return retcode_t
 */
retcode_t pose2f_inverse(const struct Pose2f* self, struct Pose2f* out);

/**
 * @brief compute ohter's relative pose using self as coordinate system
 *
 * @param self a 2D pose
 * @param other another 2D pose
 * @param out relative pose in self coordinate
 * @return retcode_t
 */
retcode_t pose2f_between(const struct Pose2f* self, const struct Pose2f* other, struct Pose2f* out);

/**
 * @brief transform a 2D point to pose coordinate frame - P_b = T_wb^(-1) * P_w
 *
 * @param self a 2D pose
 * @param in a 2D point
 * @param out transformed 2D point
 * @return retcode_t
 */
retcode_t pose2f_transform_to_point2f(const struct Pose2f* self, const struct Point2f* in, struct Point2f* out);

/**
 * @brief transform a 2D vector to pose coordinate frame - V_b = T_wb^(-1) * V_w
 *
 * @param self a 2D pose
 * @param in a 2D vector
 * @param out transformed 2D vector
 * @return retcode_t
 */
retcode_t pose2f_transform_to_vector2f(const struct Pose2f* self, const struct Vectorf* in, struct Vectorf* out);

/**
 * @brief transform a 2D point to global coordinate frame - P_w = T_wb * P_b
 *
 * @param self a 2D pose
 * @param in a 2D point
 * @param out transformed 2D point
 * @return retcode_t
 */
retcode_t pose2f_transform_from_point2f(const struct Pose2f* self, const struct Point2f* in, struct Point2f* out);

/**
 * @brief transform a 2D vector to global coordinate frame - V_w = T_wb * V_b
 *
 * @param self a 2D pose
 * @param in a 2D vector
 * @param out transformed 2D vector
 * @return retcode_t
 */
retcode_t pose2f_transform_from_vector2f(const struct Pose2f* self, const struct Vectorf* in, struct Vectorf* out);

/**
 * @brief get translation in a 2D pose
 *
 * @param self a 2D pose
 * @param out a 2D point
 * @return retcode_t
 */
retcode_t pose2f_get_translation(const struct Pose2f* self, struct Point2f* out);

/**
 * @brief get rotation in a 2D pose
 *
 * @param self a 2D pose
 * @param out a 2D rotation
 * @return retcode_t
 */
retcode_t pose2f_get_rotation(const struct Pose2f* self, struct Rot2f* out);

/**
 * @brief set translation in a 2D pose
 *
 * @param self a 2D pose
 * @param in a 2D point
 * @return retcode_t
 */
retcode_t pose2f_set_translation(struct Pose2f* self, const struct Point2f* in);

/**
 * @brief set rotation in a 2D pose
 *
 * @param self a 2D pose
 * @param in a 2D rotation
 * @return retcode_t
 */
retcode_t pose2f_set_rotation(struct Pose2f* self, const struct Rot2f* in);

/**
 * @brief get x value in a 2D pose
 *
 * @param self a 2D pose
 * @param out x value in meters
 * @return retcode_t
 */
retcode_t pose2f_get_x(const struct Pose2f* self, float32_t* out);

/**
 * @brief get y value in a 2D pose
 *
 * @param self a 2D pose
 * @param out y value in meters
 * @return retcode_t
 */
retcode_t pose2f_get_y(const struct Pose2f* self, float32_t* out);

/**
 * @brief get theta angle in a 2D pose
 *
 * @param self a 2D pose
 * @param out theta angle in radians
 * @return retcode_t
 */
retcode_t pose2f_get_angle(const struct Pose2f* self, float32_t* out);

/**
 * @brief convert 2D pose to 3x3 transformation matrix
 *
 * @param self a 2D pose
 * @param out 3x3 transformation matrix
 * @return retcode_t
 */
retcode_t pose2f_to_matrix33f(const struct Pose2f* self, struct Matrixf* out);

/**
 * @brief set a 2D pose to identity pose
 *
 * @param self a 2D pose
 * @return retcode_t
 */
retcode_t pose2f_set_identity(struct Pose2f* self);

/**
 * @brief convert 2D pose to string
 *
 * @param self a 2D pose
 * @param string_buf string
 * @param buffer_length the length of string buffer
 * @return retcode_t
 */
retcode_t pose2f_to_string(const struct Pose2f* self, char_t* string_buf, uint32_t buffer_length);

/**
 * @brief get dimension of 2D pose
 *
 * @param self a 2D pose
 * @return dimension - 2
 */
static inline uint8_t pose2f_dim()
{
    return 2;
}

/**
 * @brief check the validation of a 2D pose
 *
 * @param self a 2D pose
 * @return retcode_t
 */
bool_t pose2f_is_valid(const struct Pose2f* self);

/**
 * @brief get serialized buffer size for a 2D pose
 *
 * @param self a 2D pose to be serialized
 * @return buffer size
 */
uint32_t pose2f_get_serialized_size(const struct Pose2f* self);

/**
 * @brief serialize a 2D pose to buffer
 *
 * @param self a 2D pose to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 */
retcode_t pose2f_serialize(const struct Pose2f* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief deserialize a 2D pose to buffer
 *
 * @param self a 2D pose to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes deserialized info buffer.
 */
retcode_t pose2f_deserialize(struct Pose2f* self, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_GEOMETRY_POSE2_FLOAT32_H_ */
