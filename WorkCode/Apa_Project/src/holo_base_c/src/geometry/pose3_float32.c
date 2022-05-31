/*!
 * @file pose3_float32.c
 * @brief pose implementation
 * @author duyanwei@holomatic.com
 * @date 2019-08-11
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <holo_c/geometry/pose3_float32.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_init(struct Pose3f* self)
{
    assert(self != NULL);

    retcode_t rc = RC_SUCCESS;
    rc           = point3f_init(&self->translation);
    rc           = rot3f_init(&self->rotation);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_init_from_pose3f(struct Pose3f* self, const struct Pose3f* other)
{
    assert(self != NULL);
    assert(true == pose3f_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    rc = point3f_init_from_point3f(&self->translation, &other->translation);
    rc = rot3f_init_from_rot3f(&self->rotation, &other->rotation);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_init_from_rot3f_and_point3f(struct Pose3f* self, const struct Rot3f* rotation,
                                             const struct Point3f* translation)
{
    assert(self != NULL);
    assert(true == rot3f_is_valid(rotation));
    assert(true == point3f_is_valid(translation));

    retcode_t rc = RC_SUCCESS;

    rc = rot3f_init_from_rot3f(&self->rotation, rotation);
    rc = point3f_init_from_point3f(&self->translation, translation);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_init_from_matrix44f(struct Pose3f* self, const struct Matrixf* matrix)
{
    assert(self != NULL);
    assert(true == matrixf_is_valid(matrix));

    retcode_t rc = RC_SUCCESS;

    if (matrix->rows != 4u || matrix->cols != 4u)
    {
        rc = RC_FAIL;
    }
    else
    {
        pose3f_init(self);

        float32_t tx, ty, tz;
        matrixf_get(matrix, 0u, 3u, &tx);
        matrixf_get(matrix, 1u, 3u, &ty);
        matrixf_get(matrix, 2u, 3u, &tz);
        self->translation.x = tx;
        self->translation.y = ty;
        self->translation.z = tz;

        float32_t r00, r01, r02, r10, r11, r12, r20, r21, r22;
        matrixf_get(matrix, 0u, 0u, &r00);
        matrixf_get(matrix, 0u, 1u, &r01);
        matrixf_get(matrix, 0u, 2u, &r02);
        matrixf_get(matrix, 1u, 0u, &r10);
        matrixf_get(matrix, 1u, 1u, &r11);
        matrixf_get(matrix, 1u, 2u, &r12);
        matrixf_get(matrix, 2u, 0u, &r20);
        matrixf_get(matrix, 2u, 1u, &r21);
        matrixf_get(matrix, 2u, 2u, &r22);
        rc = rot3f_init_from_scalars(&self->rotation, r00, r01, r02, r10, r11, r12, r20, r21, r22);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t pose3f_is_valid(const struct Pose3f* self)
{
    assert(self != NULL);

    return point3f_is_valid(&self->translation) && rot3f_is_valid(&self->rotation);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t pose3f_is_equal(const struct Pose3f* self, const struct Pose3f* other)
{
    assert(true == pose3f_is_valid(self));
    assert(true == pose3f_is_valid(other));

    return point3f_is_equal(&self->translation, &other->translation) &&
           rot3f_is_equal(&self->rotation, &other->rotation);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_to_matrix44f(const struct Pose3f* self, struct Matrixf* matrix)
{
    assert(true == pose3f_is_valid(self));
    assert(true == matrixf_is_valid(matrix));

    retcode_t rc = RC_SUCCESS;
    if ((matrix->rows != 4u) || (matrix->cols != 4u))
    {
        rc = RC_FAIL;
    }
    else
    {
        // translation
        rc = matrixf_set_identity(matrix);
        rc = matrixf_set(matrix, 0u, 3u, self->translation.x);
        rc = matrixf_set(matrix, 1u, 3u, self->translation.y);
        rc = matrixf_set(matrix, 2u, 3u, self->translation.z);

        // rotation
        rc = matrixf_set(matrix, 0u, 0u, rot3f_get_r00(&self->rotation));
        rc = matrixf_set(matrix, 0u, 1u, rot3f_get_r01(&self->rotation));
        rc = matrixf_set(matrix, 0u, 2u, rot3f_get_r02(&self->rotation));
        rc = matrixf_set(matrix, 1u, 0u, rot3f_get_r10(&self->rotation));
        rc = matrixf_set(matrix, 1u, 1u, rot3f_get_r11(&self->rotation));
        rc = matrixf_set(matrix, 1u, 2u, rot3f_get_r12(&self->rotation));
        rc = matrixf_set(matrix, 2u, 0u, rot3f_get_r20(&self->rotation));
        rc = matrixf_set(matrix, 2u, 1u, rot3f_get_r21(&self->rotation));
        rc = matrixf_set(matrix, 2u, 2u, rot3f_get_r22(&self->rotation));
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_inverse(const struct Pose3f* self, struct Pose3f* out)
{
    assert(true == pose3f_is_valid(self));
    assert(true == pose3f_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    rc = rot3f_unrotate_point3f(&self->rotation, &self->translation, &out->translation);
    rc = point3f_multiply_float32(&out->translation, -1, &out->translation);
    rc = rot3f_inverse(&self->rotation, &out->rotation);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_compose(const struct Pose3f* self, const struct Pose3f* other, struct Pose3f* out)
{
    assert(true == pose3f_is_valid(self));
    assert(true == pose3f_is_valid(other));
    assert(true == pose3f_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    // translation
    {
        struct Point3f point;
        point3f_init(&point);
        rc = rot3f_rotate_point3f(&(self->rotation), &other->translation, &point);
        rc = point3f_add(&point, &self->translation, &out->translation);
    }

    // rotation
    {
        rc = rot3f_compose(&self->rotation, &other->rotation, &out->rotation);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_multiply(const struct Pose3f* self, const struct Pose3f* other, struct Pose3f* out)
{
    return pose3f_compose(self, other, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_transform_from_point3f(const struct Pose3f* self, const struct Point3f* point, struct Point3f* out)
{
    assert(true == pose3f_is_valid(self));
    assert(true == point3f_is_valid(point));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    rc = rot3f_rotate_point3f(&self->rotation, point, out);
    rc = point3f_add(out, &self->translation, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_transform_to_point3f(const struct Pose3f* self, const struct Point3f* point, struct Point3f* out)
{
    assert(true == pose3f_is_valid(self));
    assert(true == point3f_is_valid(point));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    struct Vectorf out_vec;
    float32_t      out_vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&out_vec, 3, out_vec_buf, VECTORF_MIN_BUF_SIZE(3u));

    rc = point3f_sub(point, &self->translation, &out_vec);
    rc = point3f_init_from_vector3f(out, &out_vec);
    rc = rot3f_unrotate_point3f(&self->rotation, out, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_multiply_point3f(const struct Pose3f* self, const struct Point3f* point, struct Point3f* out)
{
    assert(true == pose3f_is_valid(self));
    assert(true == point3f_is_valid(point));
    assert(out != NULL);

    return pose3f_transform_from_point3f(self, point, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_transform_from_vector3f(const struct Pose3f* self, const struct Vectorf* vector, struct Vectorf* out)
{
    assert(true == pose3f_is_valid(self));
    assert(true == vectorf_is_valid(vector));
    assert(true == vectorf_is_valid(out));

    retcode_t rc = RC_SUCCESS;
    if ((vector->size != 3u) || (out->size != 3u))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = rot3f_rotate_vector3f(&self->rotation, vector, out);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_transform_to_vector3f(const struct Pose3f* self, const struct Vectorf* vector, struct Vectorf* out)
{
    assert(true == pose3f_is_valid(self));
    assert(true == vectorf_is_valid(vector));
    assert(true == vectorf_is_valid(out));

    retcode_t rc = RC_SUCCESS;
    if ((vector->size != 3u) || (out->size != 3u))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = rot3f_unrotate_vector3f(&self->rotation, vector, out);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_multiply_vector3f(const struct Pose3f* self, const struct Vectorf* vector, struct Vectorf* out)
{
    return pose3f_transform_from_vector3f(self, vector, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_dist(const struct Pose3f* self, const struct Pose3f* other, float32_t* out)
{
    assert(true == pose3f_is_valid(self));
    assert(true == pose3f_is_valid(other));
    assert(out != NULL);

    return point3f_dist(&self->translation, &other->translation, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_between(const struct Pose3f* self, const struct Pose3f* other, struct Pose3f* out)
{
    assert(true == pose3f_is_valid(self));
    assert(true == pose3f_is_valid(other));
    assert(true == pose3f_is_valid(out));

    struct Pose3f self_inv;
    pose3f_init(&self_inv);

    retcode_t rc = pose3f_inverse(self, &self_inv);

    rc = pose3f_compose(&self_inv, other, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_expmap(struct Pose3f* self, const struct Vectorf* vector)
{
    assert(true == pose3f_is_valid(self));
    assert(true == vectorf_is_valid(vector));

    retcode_t rc = RC_SUCCESS;

    if (vector->size != 6u)
    {
        rc = RC_FAIL;
    }
    else
    {
        {
            struct Vectorf rot_vec;
            float32_t      rot_vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
            vectorf_init(&rot_vec, 3, rot_vec_buf, VECTORF_MIN_BUF_SIZE(3u));
            float32_t value;
            for (uint8_t i = 0u; i < 3u; i++)
            {
                rc = vectorf_get(vector, i, &value);
                vectorf_set(&rot_vec, i, value);
            }

            rc = rot3f_expmap(&self->rotation, &rot_vec);
        }

        {
            struct Vectorf trans_vec;
            float32_t      trans_vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
            vectorf_init(&trans_vec, 3, trans_vec_buf, VECTORF_MIN_BUF_SIZE(3u));

            float32_t value;
            for (uint8_t i = 0u; i < 3u; i++)
            {
                rc = vectorf_get(vector, i + 3u, &value);
                vectorf_set(&trans_vec, i, value);
            }

            rc = point3f_expmap(&self->translation, &trans_vec);
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_logmap(const struct Pose3f* self, struct Vectorf* vector)
{
    assert(true == pose3f_is_valid(self));
    assert(true == vectorf_is_valid(vector));

    retcode_t rc = RC_SUCCESS;

    if (vector->size != 6u)
    {
        rc = RC_FAIL;
    }
    else
    {
        {
            struct Vectorf rot_vec;
            float32_t      rot_vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
            vectorf_init(&rot_vec, 3, rot_vec_buf, VECTORF_MIN_BUF_SIZE(3u));

            rc = rot3f_logmap(&self->rotation, &rot_vec);

            float32_t value;
            for (uint8_t i = 0u; i < 3u; i++)
            {
                rc = vectorf_get(&rot_vec, i, &value);
                rc = vectorf_set(vector, i, value);
            }
        }

        {
            struct Vectorf trans_vec;
            float32_t      trans_vec_buf[VECTORF_MIN_BUF_SIZE(3u)];
            vectorf_init(&trans_vec, 3, trans_vec_buf, VECTORF_MIN_BUF_SIZE(3u));

            rc = point3f_logmap(&self->translation, &trans_vec);

            float32_t value;
            for (uint8_t i = 0u; i < 3u; i++)
            {
                rc = vectorf_get(&trans_vec, i, &value);
                rc = vectorf_set(vector, i + 3u, value);
            }
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t pose3f_set_identity(struct Pose3f* self)
{
    assert(true == pose3f_is_valid(self));

    retcode_t rc = point3f_set_zero(&self->translation);

    rc = rot3f_set_identity(&self->rotation);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Point3f* pose3f_get_translation(const struct Pose3f* self)
{
    assert(self != NULL);
    assert(pose3f_is_valid(self));

    return &self->translation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Rot3f* pose3f_get_rotation(const struct Pose3f* self)
{
    assert(self != NULL);
    assert(pose3f_is_valid(self));

    return &self->rotation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t pose3f_get_yaw(const struct Pose3f* self)
{
    /* get yaw angle from 3D rotation */
    float32_t roll, pitch, yaw;

    /* this interface is never return error code */
    (void)rot3f_to_rpy(&self->rotation, &roll, &pitch, &yaw);

    return yaw;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t pose3f_get_serialized_size(const struct Pose3f* self)
{
    (void) self;

    uint32_t size = 0;

    size += rot3f_get_serialized_size(&self->rotation);
    size += point3f_get_serialized_size(&self->translation);

    return serialization_aligned_size(size);
}

retcode_t pose3f_serialize(const struct Pose3f* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = pose3f_get_serialized_size(self);

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += rot3f_serialize(&self->rotation, 
                                           buffer, 
                                           buffer_size);
        serialized_size += point3f_serialize(&self->translation, 
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);

        serialized_size += serialize_padding(serialized_size,
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);

        assert(serialized_size == expected_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t pose3f_deserialize(struct Pose3f* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = pose3f_get_serialized_size(self);

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += rot3f_deserialize(&self->rotation, 
                buffer, 
                buffer_size);

        deserialized_size += point3f_deserialize(&self->translation, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        deserialized_size += deserialize_padding(deserialized_size,
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }

    return rc;
}
