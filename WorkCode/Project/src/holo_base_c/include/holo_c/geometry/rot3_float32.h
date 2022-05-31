/*!
 * @file rot3_float32.h
 * @brief This header file defines rotation in 3D.
 * @author liuya(liuya@holomaitc.com), duyanwei@holomatic.com
 * @date 2019-08-11
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_GEOMETRY_ROT3_FLOAT32_H_
#define HOLO_C_GEOMETRY_ROT3_FLOAT32_H_

#include <holo_c/core/epsilon.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point3_float32.h>
#include <holo_c/geometry/quaternion_float32.h>
#include <holo_c/numerics/matrix_float32.h>
#include <holo_c/numerics/vector_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define Rot3f struct
 *
 * @details !!! one must call rot3_init() first before any further usage !!!
 *
 */
struct Rot3f
{
    struct Matrixf m;
    float32_t      matrix_data[MATRIXF_MIN_BUF_SIZE(3u, 3u)]; /** @todo to be continue */
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize rot3 to identity matrix
 *
 * @param self rotation
 * @return retcode_t
 */
retcode_t rot3f_init(struct Rot3f* self);

/**
 * @brief initialize rotation from 9 scalars
 *
 * @param self rotation
 * @param m00 r11
 * @param m01 r01
 * @param m02 r02
 * @param m10 r10
 * @param m11 r11
 * @param m12 r12
 * @param m20 r20
 * @param m21 r21
 * @param m22 r22
 * @return retcode_t
 */
retcode_t rot3f_init_from_scalars(struct Rot3f* self, const float32_t m00, const float32_t m01, const float32_t m02,
                                  const float32_t m10, const float32_t m11, const float32_t m12, const float32_t m20,
                                  const float32_t m21, const float32_t m22);

/**
 * @brief initialize rot3 from another rot3
 *
 * @param self rotation
 * @param other rotation
 * @return retcode_t
 */
retcode_t rot3f_init_from_rot3f(struct Rot3f* self, const struct Rot3f* other);

/**
 * @brief check if rot3 is valid
 *
 * @param self rotation
 * @return bool_t
 */
bool_t rot3f_is_valid(const struct Rot3f* self);

/**
 * @brief check if two matrices are equal
 *
 * @param self rot3f
 * @param other rot3f
 * @return bool_t
 */
bool_t rot3f_is_equal(const struct Rot3f* self, const struct Rot3f* other);

/**
 * @brief convert rot3 to matrixf of 3x3
 *
 * @param self rotation
 * @param matrix matrixf
 * @return retcode_t
 */
retcode_t rot3f_to_matrix33f(const struct Rot3f* self, struct Matrixf* matrix);

/**
 * @brief transpose a rotation matrix
 *
 * @param self rotation matrix
 * @param out transposed matrix
 * @return retcode_t
 */
retcode_t rot3f_transpose(const struct Rot3f* self, struct Rot3f* out);

/**
 * @brief inverse a rotation matrix
 *
 * @param self rotation matrix
 * @param out the inverse of rotation matrix
 * @return retcode_t
 */
retcode_t rot3f_inverse(const struct Rot3f* self, struct Rot3f* out);

/**
 * @brief rotate a vector
 *
 * @param self rotation matrix
 * @param vector vector
 * @param out rotated vector
 * @return retcode_t
 */
retcode_t rot3f_rotate_vector3f(const struct Rot3f* self, const struct Vectorf* vector, struct Vectorf* out);

/**
 * @brief unrotate a vector
 *
 * @param self rotation matrix
 * @param vector vector
 * @param out unrotated vector
 * @return retcode_t
 */
retcode_t rot3f_unrotate_vector3f(const struct Rot3f* self, const struct Vectorf* vector, struct Vectorf* out);

/**
 * @brief multiply a vector
 *
 * @param self rotation matrix
 * @param vector vector
 * @param out rotated vector
 * @return retcode_t
 */
retcode_t rot3f_multiply_vector3f(const struct Rot3f* self, const struct Vectorf* vector, struct Vectorf* out);

/**
 * @brief rotate a point
 *
 * @param self rotation matrix
 * @param point point
 * @param out rotated point
 * @return retcode_t
 */
retcode_t rot3f_rotate_point3f(const struct Rot3f* self, const struct Point3f* point, struct Point3f* out);

/**
 * @brief unrotate a point
 *
 * @param self rotation matrix
 * @param point point
 * @param out unrotated point
 * @return retcode_t
 */
retcode_t rot3f_unrotate_point3f(const struct Rot3f* self, const struct Point3f* point, struct Point3f* out);

/**
 * @brief multiply a point
 *
 * @param self rotation matrix
 * @param point point
 * @param out rotated point
 * @return retcode_t
 */
retcode_t rot3f_multiply_point3f(const struct Rot3f* self, const struct Point3f* point, struct Point3f* out);

/**
 * @brief multiply a rotation matrix
 *
 * @param self rotation matrix
 * @param other rotation matrix
 * @param out rotation matrix
 * @return retcode_t
 */
retcode_t rot3f_compose(const struct Rot3f* self, const struct Rot3f* other, struct Rot3f* out);

/**
 * @brief multiply a rotation matrix
 *
 * @param self rotation matrix
 * @param other rotation matrix
 * @param out rotation matrix
 * @return retcode_t
 */
retcode_t rot3f_multiply(const struct Rot3f* self, const struct Rot3f* other, struct Rot3f* out);

/**
 * @brief expmap of rotation
 *
 * @param self rotation
 * @param vector vector
 * @return retcode_t
 */
retcode_t rot3f_expmap(struct Rot3f* self, const struct Vectorf* vector);

/**
 * @brief logmap of rotation
 *
 * @param self rotation
 * @param vector vector
 * @return retcode_t
 */
retcode_t rot3f_logmap(const struct Rot3f* self, struct Vectorf* vector);

/**
 * @brief rot3f from angle axis (vector)
 *
 * @param self rotation matrix
 * @param vector vector
 * @return retcode_t
 */
retcode_t rot3f_from_angle_axis(struct Rot3f* self, const struct Vectorf* vector);

/**
 * @brief convert rotation matrix to anagle axis
 *
 * @param self rotation
 * @param vector vector
 * @return retcode_t
 */
retcode_t rot3f_to_angle_axis(const struct Rot3f* self, struct Vectorf* vector);

/**
 * @brief compute the angle difference between two rotation matrices
 *
 * @param self rotation matrix 1
 * @param other rotation matrix 2
 * @return float32_t
 */
float32_t rot3f_compute_angle_diff(const struct Rot3f* self, const struct Rot3f* other);

/**
 * @brief construct an rotation matrix from roll, pitch, yaw in yaw-pitch-roll order
 *
 * @param self rotation matrix
 * @param roll roll angle in radian
 * @param pitch pitch angle in radian
 * @param yaw yaw angle in radian
 * @return retcode_t
 */
retcode_t rot3f_from_rpy(struct Rot3f* self, const float32_t roll, const float32_t pitch, const float32_t yaw);

/**
 * @brief construct an rotation matrix from yaw, pitch, roll in yaw-pitch-roll order
 *
 * @param self rotation matrix
 * @param yaw yaw angle in radian
 * @param pitch pitch angle in radian
 * @param roll roll angle in radian
 * @return retcode_t
 */
retcode_t rot3f_from_ypr(struct Rot3f* self, const float32_t yaw, const float32_t pitch, const float32_t roll);

/**
 * @brief construct a rotation matrix from angle around x-axis in radian
 *
 * @param self rotation matrix
 * @param roll angle around x-axis in radian
 * @return retcode_t
 */
retcode_t rot3f_from_roll(struct Rot3f* self, const float32_t roll);

/**
 * @brief construct a rotation matrix from angle around y-axis in radian
 *
 * @param self rotation matrix
 * @param pitch angle around y-axis in radian
 * @return retcode_t
 */
retcode_t rot3f_from_pitch(struct Rot3f* self, const float32_t pitch);

/**
 * @brief construct a rotation matrix from angle around z-axis in radian
 *
 * @param self rotation matrix
 * @param yaw angle around z-axis in radian
 * @return retcode_t
 */
retcode_t rot3f_from_yaw(struct Rot3f* self, const float32_t yaw);

/**
 * @brief decompose rotation matrix into yaw, pitch, roll in yaw-pitch-roll order
 *
 * @param self rotation matrix
 * @param yaw yaw in radian
 * @param pitch pitch in radian
 * @param roll roll in radian
 * @return retcode_t
 */
retcode_t rot3f_to_ypr(const struct Rot3f* self, float32_t* yaw, float32_t* pitch, float32_t* roll);

/**
 * @brief decompose rotation matrix into roll, pitch, yaw in a yaw-pitch-roll order
 *
 * @param self rotation matrix
 * @param roll roll in radian
 * @param pitch pitch in radian
 * @param yaw yaw in radian
 * @return retcode_t
 */
retcode_t rot3f_to_rpy(const struct Rot3f* self, float32_t* roll, float32_t* pitch, float32_t* yaw);

/**
 * @brief set rot3 to identity
 *
 * @param self rotation matrix
 * @return retcode_t
 */
retcode_t rot3f_set_identity(struct Rot3f* self);

/**
 * @brief return single element of rot3 matrix
 *
 * @param self rotation matrix
 * @return r00
 */
float32_t rot3f_get_r00(const struct Rot3f* self);

/**
 * @brief return single element of rot3 matrix
 *
 * @param self rotation matrix
 * @return r01
 */
float32_t rot3f_get_r01(const struct Rot3f* self);

/**
 * @brief return single element of rot3 matrix
 *
 * @param self rotation matrix
 * @return r02
 */
float32_t rot3f_get_r02(const struct Rot3f* self);

/**
 * @brief return single element of rot3 matrix
 *
 * @param self rotation matrix
 * @return r10
 */
float32_t rot3f_get_r10(const struct Rot3f* self);

/**
 * @brief return single element of rot3 matrix
 *
 * @param self rotation matrix
 * @return r11
 */
float32_t rot3f_get_r11(const struct Rot3f* self);

/**
 * @brief return single element of rot3 matrix
 *
 * @param self rotation matrix
 * @return r12
 */
float32_t rot3f_get_r12(const struct Rot3f* self);

/**
 * @brief return single element of rot3 matrix
 *
 * @param self rotation matrix
 * @return r20
 */
float32_t rot3f_get_r20(const struct Rot3f* self);

/**
 * @brief return single element of rot3 matrix
 *
 * @param self rotation matrix
 * @return r21
 */
float32_t rot3f_get_r21(const struct Rot3f* self);

/**
 * @brief return single element of rot3 matrix
 *
 * @param self rotation matrix
 * @return r22
 */
float32_t rot3f_get_r22(const struct Rot3f* self);

/**
 * @brief convert rotation matrix to quaternion
 *
 * @param self rotation matrix
 * @param quaternion quaternion
 * @return retcode_t
 */
retcode_t rot3f_to_quaternionf(const struct Rot3f* self, struct Quaternionf* quaternion);

/**
 * @brief get serialized buffer size for a 3D rotation
 *
 * @param self a 3D rotation to be serialized
 * @return buffer size
 */
uint32_t rot3f_get_serialized_size(const struct Rot3f* self);

/**
 * @brief serialize a 3D rotation to buffer
 *
 * @param self a 3D rotation to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 */
retcode_t rot3f_serialize(const struct Rot3f* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief deserialize a 3D rotation to buffer
 *
 * @param self a 3D rotation to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes deserialized info buffer.
 */
retcode_t rot3f_deserialize(struct Rot3f* self, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_GEOMETRY_ROT3_FLOAT32_H_
