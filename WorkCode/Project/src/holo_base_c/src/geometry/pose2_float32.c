/*!
 * @brief implementation of point in 2D space.
 * @author lichao(lichao@holomaitc.com)
 * @date Aug 20, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <assert.h>
#include <holo_c/core/epsilon.h>
#include <holo_c/geometry/point2_float32.h>
#include <holo_c/geometry/pose2_float32.h>
#include <holo_c/geometry/rot2_float32.h>
#include <math.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_init(struct Pose2f* self)
{
    assert(self != NULL);

    retcode_t rc = RC_SUCCESS;

    /* initialize a zero 2D point */
    struct Point2f pt;
    rc = point2f_init(&pt);

    /* initialize an identity pose */
    rc = pose2f_init_from_angle_and_point2f(self, 0.0, &pt);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_init_from_rot2f_and_point2f(struct Pose2f* self, const struct Rot2f* rot, const struct Point2f* point)
{
    assert(self != NULL);
    assert(rot2f_is_valid(rot));
    assert(point2f_is_valid(point));

    retcode_t rc = RC_SUCCESS;

    /* set rotation and translation */
    rot2f_init_from_rot2f(&self->rotation, rot);
    point2f_init_from_point2f(&self->translation, point);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_init_from_angle_and_point2f(struct Pose2f* self, const float32_t theta, const struct Point2f* point)
{
    assert(self != NULL);
    assert(!isnan(theta));
    assert(point2f_is_valid(point));

    retcode_t rc = RC_SUCCESS;

    /* set rotation and translation */
    rot2f_init_from_angle(&self->rotation, theta);
    point2f_init_from_point2f(&self->translation, point);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_init_from_matrix33f(struct Pose2f* self, const struct Matrixf* mat)
{
    assert(self != NULL);
    assert(matrixf_is_valid(mat));

    retcode_t rc = RC_SUCCESS;

    /* get element of transformation matrix */
    float32_t x = 0.0, y = 0.0;
    matrixf_get(mat, 0, 2, &x);
    matrixf_get(mat, 1, 2, &y);

    /* get 2x2 rotation matrix for 3x3 transformation matrix
       initialize rotation matrix */
    struct Matrixf rot_mat;
    float32_t      rot_mat_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&rot_mat, 2, 2, rot_mat_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_get_top_left_corner(mat, 2, 2, &rot_mat);

    /* set rotation and translation */
    rot2f_init_from_matrix(&self->rotation, &rot_mat);
    point2f_init_from_scalars(&self->translation, x, y);

    assert(pose2f_is_valid(self));

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_init_from_pose2f(struct Pose2f* self, const struct Pose2f* in)
{
    assert(self != NULL);
    assert(pose2f_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* get rotation and translation from another 2D pose */
    struct Rot2f   rot;
    struct Point2f point;
    pose2f_get_rotation(in, &rot);
    pose2f_get_translation(in, &point);

    /* set rotation and translation to this 2D pose */
    rot2f_init_from_rot2f(&self->rotation, &rot);
    point2f_init_from_point2f(&self->translation, &point);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_compose(const struct Pose2f* self, const struct Pose2f* other, struct Pose2f* out)
{
    assert(pose2f_is_valid(self));
    assert(pose2f_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    /* get transformation matrixs from two 2D poses */
    struct Matrixf matrix_self;
    float32_t      matrix_self_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&matrix_self, 3, 3, matrix_self_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    pose2f_to_matrix33f(self, &matrix_self);

    struct Matrixf matrix_other;
    float32_t      matrix_other_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&matrix_other, 3, 3, matrix_other_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    pose2f_to_matrix33f(other, &matrix_other);

    /* multiply two matrixs */
    struct Matrixf matrix_out;
    float32_t      matrix_out_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&matrix_out, 3, 3, matrix_out_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    matrixf_multiply(&matrix_self, &matrix_other, &matrix_out);

    /* initialize 2D pose from 3x3 transformation matrix */
    pose2f_init_from_matrix33f(out, &matrix_out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_multiply_point2f(const struct Pose2f* self, const struct Point2f* in, struct Point2f* out)
{
    return pose2f_transform_from_point2f(self, in, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_multiply_vector2f(const struct Pose2f* self, const struct Vectorf* in, struct Vectorf* out)
{
    return pose2f_transform_from_vector2f(self, in, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t pose2f_is_equal(const struct Pose2f* self, const struct Pose2f* other)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(pose2f_is_valid(self));
    assert(pose2f_is_valid(other));

    bool_t flag = false;

    /* check if both rotation and translation are equals */
    if (rot2f_is_equal(&self->rotation, &other->rotation) && point2f_is_equal(&self->translation, &other->translation))
    {
        flag = true;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_inverse(const struct Pose2f* self, struct Pose2f* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    /* get rotation from 2D pose */
    struct Rot2f rot, rot_inverse;
    rot2f_init_from_rot2f(&rot, &self->rotation);
    rot2f_inverse(&rot, &rot_inverse);

    /* get translation from 2D pose */
    struct Point2f pt, pt_negative;
    point2f_init_from_point2f(&pt, &self->translation);
    point2f_negate(&pt, &pt_negative);

    /* set inversed rotation and negative translation to 2D pose */
    pose2f_init_from_rot2f_and_point2f(out, &rot_inverse, &pt_negative);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_between(const struct Pose2f* self, const struct Pose2f* other, struct Pose2f* out)
{
    assert(pose2f_is_valid(self));
    assert(pose2f_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    /* compute inverse of self pose */
    struct Pose2f pose_inv;
    pose2f_inverse(self, &pose_inv);

    /* compute relative pose: out = self^(-1) * other */
    pose2f_compose(&pose_inv, other, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_transform_to_point2f(const struct Pose2f* self, const struct Point2f* in, struct Point2f* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));
    assert(point2f_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* get translation vector from pose */
    struct Vectorf vec_self;
    float32_t      vec_self_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec_self, 2, vec_self_buf, VECTORF_MIN_BUF_SIZE(2u));
    point2f_to_vector2f(&self->translation, &vec_self);

    /* subtract two 2D points */
    struct Point2f pt;
    point2f_reverse_translate(in, &vec_self, &pt);

    /* unrotate the 2D point */
    rot2f_unrotate_point2f(&self->rotation, &pt, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_transform_to_vector2f(const struct Pose2f* self, const struct Vectorf* in, struct Vectorf* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));
    assert(vectorf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* get 2D vector from 2D pose */
    struct Vectorf vec_self;
    float32_t      vec_self_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec_self, 2, vec_self_buf, VECTORF_MIN_BUF_SIZE(2u));
    struct Point2f pt_self;
    pose2f_get_translation(self, &pt_self);
    point2f_to_vector2f(&pt_self, &vec_self);

    /* subtract two 2D vectors */
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    vectorf_sub(in, &vec_self, &vec);

    /* unrotate the 2D vector */
    rot2f_unrotate_vector2f(&self->rotation, &vec, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_transform_from_point2f(const struct Pose2f* self, const struct Point2f* in, struct Point2f* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));
    assert(point2f_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* rotate 2D point */
    struct Point2f pt;
    rot2f_rotate_point2f(&self->rotation, in, &pt);

    /* accumulate 2D translation */
    point2f_add(&self->translation, &pt, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_transform_from_vector2f(const struct Pose2f* self, const struct Vectorf* in, struct Vectorf* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));
    assert(vectorf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* rotate 2D vector */
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    rot2f_rotate_vector2f(&self->rotation, in, &vec);

    /* get 2D vector from 2D pose */
    struct Vectorf vec_self;
    float32_t      vec_self_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec_self, 2, vec_self_buf, VECTORF_MIN_BUF_SIZE(2u));
    struct Point2f pt_self;
    pose2f_get_translation(self, &pt_self);
    point2f_to_vector2f(&pt_self, &vec_self);

    /* accumulate 2D vectors */
    vectorf_add(&vec_self, &vec, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t pose2f_get_translation(const struct Pose2f* self, struct Point2f* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    /* get translation from 2D pose */
    point2f_init_from_point2f(out, &self->translation);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t pose2f_get_rotation(const struct Pose2f* self, struct Rot2f* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    /* get rotation from 2D pose */
    rot2f_init_from_rot2f(out, &self->rotation);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_set_translation(struct Pose2f* self, const struct Point2f* in)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));
    assert(point2f_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* set translation to 2D pose */
    point2f_init_from_point2f(&self->translation, in);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_set_rotation(struct Pose2f* self, const struct Rot2f* in)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));
    assert(rot2f_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* set rotation to 2D pose */
    rot2f_init_from_rot2f(&self->rotation, in);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t pose2f_get_x(const struct Pose2f* self, float32_t* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    *out = point2f_get_x(&self->translation);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t pose2f_get_y(const struct Pose2f* self, float32_t* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    *out = point2f_get_y(&self->translation);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t pose2f_get_angle(const struct Pose2f* self, float32_t* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    rot2f_get_angle(&self->rotation, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_to_matrix33f(const struct Pose2f* self, struct Matrixf* out)
{
    assert(self != NULL);
    assert(pose2f_is_valid(self));

    retcode_t rc       = RC_SUCCESS;
    uint16_t  data_idx = 0;
    for (data_idx = 0; data_idx < out->capacity; data_idx++)
        out->base[data_idx] = 0.0f;
    matrixf_set_identity(out);

    /* get rotation matrix and translation from 2D pose */
    struct Matrixf rot_mat;
    float32_t      rot_mat_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&rot_mat, 2, 2, rot_mat_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));

    rot2f_to_matrix22f(&self->rotation, &rot_mat);
    float32_t x = 0.0, y = 0.0, s = 0.0, c = 0.0;
    x = point2f_get_x(&self->translation);
    y = point2f_get_y(&self->translation);
    matrixf_get(&rot_mat, 0, 0, &c);
    matrixf_get(&rot_mat, 1, 0, &s);

    /* set rotation matrix and translation to transformation matrix
       TODO use matrix block operation (lichao@holomatic.com) */
    matrixf_set(out, 0, 0, c);
    matrixf_set(out, 0, 1, -s);
    matrixf_set(out, 0, 2, x);

    matrixf_set(out, 1, 0, s);
    matrixf_set(out, 1, 1, c);
    matrixf_set(out, 1, 2, y);

    matrixf_set(out, 2, 0, 0);
    matrixf_set(out, 2, 1, 0);
    matrixf_set(out, 2, 2, 1);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_set_identity(struct Pose2f* self)
{
    assert(pose2f_is_valid(self));
    retcode_t rc = RC_SUCCESS;

    /* initialize from zero angle */
    pose2f_init(self);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_to_string(const struct Pose2f* self, char_t* string_buf, uint32_t buffer_length)
{
    assert(pose2f_is_valid(self));
    retcode_t rc = RC_SUCCESS;

    /* get rotation and translation strings */
    const uint32_t buffer_length_rot   = buffer_length / 2u;
    const uint32_t buffer_length_trans = buffer_length / 2u;

    char_t str_rot[buffer_length_rot], str_trans[buffer_length_trans];
    rot2f_to_string(&self->rotation, str_rot, buffer_length_rot);
    point2f_to_string(&self->translation, str_trans, buffer_length_trans);

    snprintf(string_buf, buffer_length, "pose2: (%s, %s)", str_rot, str_trans);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t pose2f_is_valid(const struct Pose2f* self)
{
    assert(self != NULL);
    return rot2f_is_valid(&self->rotation) && point2f_is_valid(&self->translation);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t pose2f_get_serialized_size(const struct Pose2f* self)
{
    (void)self;
    HOLO_STATIC_ASSERT(sizeof(struct Pose2f) % 8 == 0);
    return sizeof(struct Pose2f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_serialize(const struct Pose2f* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = pose2f_get_serialized_size(self);

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += rot2f_serialize(&self->rotation, buffer, buffer_size);
        serialized_size += point2f_serialize(&self->translation, 
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);
        assert(serialized_size == expected_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose2f_deserialize(struct Pose2f* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = pose2f_get_serialized_size(self); // fixed size object.

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += rot2f_deserialize(&self->rotation, buffer, buffer_size);
        deserialized_size += point2f_deserialize(&self->translation, 
                                                 buffer + deserialized_size, 
                                                 buffer_size - deserialized_size);
        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
