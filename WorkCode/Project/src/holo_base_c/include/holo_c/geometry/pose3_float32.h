/*!
 * @file pose3_float32.h
 * @brief This header file defines pose in 3D.
 * @author duyanwei@holomatic.com
 * @date 2019-08-11
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_POSE3_FLOAT32_H_
#define HOLO_C_GEOMETRY_POSE3_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point3_float32.h>
#include <holo_c/geometry/rot3_float32.h>
#include <holo_c/numerics/matrix_float32.h>
#include <holo_c/numerics/vector_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define pose3 struct
 *
 */
struct Pose3f
{
    struct Rot3f   rotation;
    struct Point3f translation;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize a pose3
 *
 * @param self pose3
 * @return retcode_t
 */
retcode_t pose3f_init(struct Pose3f* self);

/**
 * @brief initialize a pose3 from another pose3
 *
 * @param self pose3
 * @param other pose3
 * @return retcode_t
 */
retcode_t pose3f_init_from_pose3f(struct Pose3f* self, const struct Pose3f* other);

/**
 * @brief initialize pose3 from rotation and translation
 *
 * @param self pose3
 * @param rotation rotation
 * @param translation translation
 * @return retcode_t
 */
retcode_t pose3f_init_from_rot3f_and_point3f(struct Pose3f* self, const struct Rot3f* rotation,
                                             const struct Point3f* translation);

/**
 * @brief initialize pose3 from matrix44f
 *
 * @param self pose3
 * @param matrix matrix
 * @return retcode_t
 */
retcode_t pose3f_init_from_matrix44f(struct Pose3f* self, const struct Matrixf* matrix);

/**
 * @brief check if a pose is valid
 *
 * @param self pose3
 * @return bool_t
 */
bool_t pose3f_is_valid(const struct Pose3f* self);

/**
 * @brief check if two poses are equal
 *
 * @param self pose3
 * @param other pose3
 * @return bool_t
 */
bool_t pose3f_is_equal(const struct Pose3f* self, const struct Pose3f* other);

/**
 * @brief convert pose3 to matrix
 *
 * @param self pose
 * @param matrix matrix
 * @return retcode_t
 */
retcode_t pose3f_to_matrix44f(const struct Pose3f* self, struct Matrixf* matrix);

/**
 * @brief take the inversse of pose
 *
 * @param self pose3
 * @param out the inverse of pose3
 * @return retcode_t
 */
retcode_t pose3f_inverse(const struct Pose3f* self, struct Pose3f* out);

/**
 * @brief compose
 *
 * @param self pose3
 * @param other pose3
 * @param out pose3
 * @return retcode_t
 */
retcode_t pose3f_compose(const struct Pose3f* self, const struct Pose3f* other, struct Pose3f* out);

/**
 * @brief multiply a pose3
 *
 * @param self pose3
 * @param other pose3
 * @param out pose3
 * @return retcode_t
 */
retcode_t pose3f_multiply(const struct Pose3f* self, const struct Pose3f* other, struct Pose3f* out);

/**
 * @brief transform a point from body to world
 *
 * @param self pose3f
 * @param point point
 * @param out transformed point
 * @return retcode_t
 */
retcode_t pose3f_transform_from_point3f(const struct Pose3f* self, const struct Point3f* point, struct Point3f* out);

/**
 * @brief transform a point from world to body
 *
 * @param self pose3f
 * @param point point
 * @param out transformed point
 * @return retcode_t
 */
retcode_t pose3f_transform_to_point3f(const struct Pose3f* self, const struct Point3f* point, struct Point3f* out);

/**
 * @brief multiply a point3
 *
 * @param self pose3
 * @param point point
 * @param out transformed point
 * @return retcode_t
 */
retcode_t pose3f_multiply_point3f(const struct Pose3f* self, const struct Point3f* point, struct Point3f* out);

/**
 * @brief transform a vector from body to world
 *
 * @param self pose3f
 * @param vector vector
 * @param out transformed vector
 * @return retcode_t
 */
retcode_t pose3f_transform_from_vector3f(const struct Pose3f* self, const struct Vectorf* vector, struct Vectorf* out);

/**
 * @brief transform a vector from world to body
 *
 * @param self pose3f
 * @param vector vector
 * @param out transformed vector
 * @return retcode_t
 */
retcode_t pose3f_transform_to_vector3f(const struct Pose3f* self, const struct Vectorf* vector, struct Vectorf* out);

/**
 * @brief multiply a vector
 *
 * @param self pose3
 * @param vector point
 * @param out transformed point
 * @return retcode_t
 */
retcode_t pose3f_multiply_vector3f(const struct Pose3f* self, const struct Vectorf* vector, struct Vectorf* out);

/**
 * @brief compute distance between two poses
 *
 * @param self first pose
 * @param other second pose
 * @param out pointer of distance
 * @return retcode_t
 */
retcode_t pose3f_dist(const struct Pose3f* self, const struct Pose3f* other, float32_t* out);

/**
 * @brief compute the difference between two poses
 *
 * @param self the first pose
 * @param other the second pose
 * @param out the difference pose
 * @return retcode_t
 */
retcode_t pose3f_between(const struct Pose3f* self, const struct Pose3f* other, struct Pose3f* out);

/**
 * @brief convert lie algebra to lie group
 *
 * @param self pose3
 * @param vector vector
 * @return retcode_t
 */
retcode_t pose3f_expmap(struct Pose3f* self, const struct Vectorf* vector);

/**
 * @brief convert lie group to lie algebra
 *
 * @param self pose3
 * @param vector vector
 * @return retcode_t
 */
retcode_t pose3f_logmap(const struct Pose3f* self, struct Vectorf* vector);

/**
 * @brief set pose to identity
 *
 * @param self pose3
 * @return retcode_t
 */
retcode_t pose3f_set_identity(struct Pose3f* self);

/**
 * @brief get translation in a 3D pose
 *
 * @param self a 3D pose
 * @return const struct Point3f*
 */
const struct Point3f* pose3f_get_translation(const struct Pose3f* self);

/**
 * @brief get rotation in a 3D pose
 *
 * @param self a 3D pose
 * @return const struct Rot3f*
 */
const struct Rot3f* pose3f_get_rotation(const struct Pose3f* self);

/**
 * @brief get yaw angle in a 3D pose
 *
 * @param self a 3D pose
 * @return yaw angle in radian
 */
float32_t pose3f_get_yaw(const struct Pose3f* self);

/**
 * @brief get serialized buffer size for a 3D pose
 *
 * @param self a 3D pose to be serialized
 * @return buffer size
 */
uint32_t pose3f_get_serialized_size(const struct Pose3f* self);

/**
 * @brief serialize a 3D pose to buffer
 *
 * @param self a 3D pose to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 */
retcode_t pose3f_serialize(const struct Pose3f* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief deserialize a 3D pose to buffer
 *
 * @param self a 3D pose to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes deserialized info buffer.
 */
retcode_t pose3f_deserialize(struct Pose3f* self, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_POSE3_FLOAT32_H_
