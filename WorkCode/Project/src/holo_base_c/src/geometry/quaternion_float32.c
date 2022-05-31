/*!
 * @file quaternion_float32.c
 * @brief quaternion implementation.
 * @author duyanwei@holomatic.com
 * @date 2019-08-22
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <math.h>

#include <holo_c/core/epsilon.h>
#include <holo_c/geometry/quaternion_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t quaternionf_init_from_scalars(struct Quaternionf* quaternion, const float32_t w, const float32_t x,
                                        const float32_t y, const float32_t z)
{
    assert(quaternion != NULL);

    quaternion->w = w;
    quaternion->x = x;
    quaternion->y = y;
    quaternion->z = z;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t quaternionf_init(struct Quaternionf* quaternion)
{
    return quaternionf_init_from_scalars(quaternion, 1.0f, 0.0f, 0.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t quaternionf_init_from_quaternionf(struct Quaternionf* self, const struct Quaternionf* other)
{
    assert(true == quaternionf_is_valid(other));

    return quaternionf_init_from_scalars(self, other->w, other->x, other->y, other->z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t quaternionf_is_valid(const struct Quaternionf* quaternion)
{
    assert(quaternion != NULL);

    // check nan value
    return (!isnan(quaternion->w)) && (!isnan(quaternion->x)) && (!isnan(quaternion->y)) && (!isnan(quaternion->z));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t quaternionf_is_equal(const struct Quaternionf* lhs, const struct Quaternionf* rhs)
{
    assert(true == quaternionf_is_valid(lhs));
    assert(true == quaternionf_is_valid(rhs));

    const float32_t diff_w = fabsf(lhs->w - rhs->w);
    const float32_t diff_x = fabsf(lhs->x - rhs->x);
    const float32_t diff_y = fabsf(lhs->y - rhs->y);
    const float32_t diff_z = fabsf(lhs->z - rhs->z);

    const bool_t flag = (diff_w <= holo_float32_epsilon) && (diff_x <= holo_float32_epsilon) &&
                        (diff_y <= holo_float32_epsilon) && (diff_z <= holo_float32_epsilon);
    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t quaternionf_to_matrix33f(const struct Quaternionf* quaternion, struct Matrixf* mat)
{
    assert(true == quaternionf_is_valid(quaternion));
    assert(true == matrixf_is_valid(mat));

    retcode_t rc = RC_SUCCESS;

    if (!quaternionf_is_normalized(quaternion))
    {
        rc = RC_FAIL;
    }
    else
    {
        uint16_t data_idx = 0;
        for (data_idx = 0; data_idx < mat->capacity; data_idx++)
            mat->base[data_idx] = 0.0f;
        float32_t data[9];
        data[0] = 1.0f - 2.0f * powf(quaternion->y, 2.0f) - 2.0f * powf(quaternion->z, 2.0f);
        data[1] = 2.0f * quaternion->x * quaternion->y - 2.0f * quaternion->z * quaternion->w;
        data[2] = 2.0f * quaternion->x * quaternion->z + 2.0f * quaternion->y * quaternion->w;
        data[3] = 2.0f * quaternion->x * quaternion->y + 2.0f * quaternion->z * quaternion->w;
        data[4] = 1.0f - 2.0f * powf(quaternion->x, 2.0f) - 2.0f * powf(quaternion->z, 2.0f);
        data[5] = 2.0f * quaternion->y * quaternion->z - 2.0f * quaternion->x * quaternion->w;
        data[6] = 2.0f * quaternion->x * quaternion->z - 2.0f * quaternion->y * quaternion->w;
        data[7] = 2.0f * quaternion->y * quaternion->z + 2.0f * quaternion->x * quaternion->w;
        data[8] = 1.0f - 2.0f * powf(quaternion->x, 2.0f) - 2.0f * powf(quaternion->y, 2.0f);
        matrixf_set_from_array(mat, data, 9);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t quaternionf_dot(const struct Quaternionf* lhs, const struct Quaternionf* rhs, float32_t* out)
{
    assert(true == quaternionf_is_valid(lhs));
    assert(true == quaternionf_is_valid(rhs));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (!quaternionf_is_normalized(lhs) || !quaternionf_is_normalized(rhs))
    {
        rc = RC_FAIL;
    }
    else
    {
        *out = lhs->w * rhs->w + lhs->x * rhs->x + lhs->y * rhs->y + lhs->z * rhs->z;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t quaternionf_slerp(const struct Quaternionf* left, const struct Quaternionf* right, const float32_t t,
                            struct Quaternionf* out)
{
    assert(true == quaternionf_is_valid(left));
    assert(true == quaternionf_is_valid(right));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (!quaternionf_is_normalized(left) || !quaternionf_is_normalized(right))
    {
        rc = RC_FAIL;
    }
    else if (t < holo_float32_epsilon || t + holo_float32_epsilon > 1.0f)
    {
        rc = RC_FAIL;
    }
    else
    {
        float32_t costheta = 0.0f;
        quaternionf_dot(left, right, &costheta);

        struct Quaternionf right_copy;
        quaternionf_init_from_quaternionf(&right_copy, right);

        if (costheta < 0.0f)
        {
            costheta = -costheta;
            quaternionf_multiply_float32(&right_copy, -1.0f, &right_copy);
        }

        float32_t left_scale, right_scale;
        if (costheta >= 1.0f - holo_float32_epsilon)
        {
            left_scale  = 1.0f - t;
            right_scale = t;
        }
        else
        {
            const float32_t theta    = acosf(costheta);
            const float32_t sintheta = sinf(theta);

            left_scale  = sinf(((1.0f - t) * theta)) / sintheta;
            right_scale = sinf(t * theta) / sintheta;
        }

        out->w = left->w * left_scale + right_copy.w * right_scale;
        out->x = left->x * left_scale + right_copy.x * right_scale;
        out->y = left->y * left_scale + right_copy.y * right_scale;
        out->z = left->z * left_scale + right_copy.z * right_scale;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t quaternionf_multiply_float32(const struct Quaternionf* self, const float32_t scalar, struct Quaternionf* out)
{
    assert(true == quaternionf_is_valid(self));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (fabsf(scalar) <= holo_float32_epsilon)
    {
        rc = RC_FAIL;
    }
    else
    {
        out->w = scalar * self->w;
        out->x = scalar * self->x;
        out->y = scalar * self->y;
        out->z = scalar * self->z;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t quaternionf_get_norm(const struct Quaternionf* quaternion)
{
    assert(true == quaternionf_is_valid(quaternion));

    const float32_t squared_norm = quaternion->w * quaternion->w + quaternion->x * quaternion->x +
                                   quaternion->y * quaternion->y + quaternion->z * quaternion->z;
    return sqrtf(squared_norm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t quaternionf_normalize(struct Quaternionf* quaternion)
{
    assert(true == quaternionf_is_valid(quaternion));

    const float32_t norm = quaternionf_get_norm(quaternion);

    if (norm > holo_float32_epsilon)
    {
        quaternionf_multiply_float32(quaternion, 1.0f / norm, quaternion);
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t quaternionf_is_normalized(const struct Quaternionf* quaternion)
{
    assert(true == quaternionf_is_valid(quaternion));

    const float32_t norm = quaternionf_get_norm(quaternion);
    return fabsf(norm - 1.0f) <= holo_float32_epsilon;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t quaternionf_set_identity(struct Quaternionf* quaternion)
{
    assert(quaternion != NULL);

    return quaternionf_init_from_scalars(quaternion, 1.0f, 0.0f, 0.0f, 0.0f);
}
