/*!
 * @file point3_float32.c
 * @brief This header file defines 3f point.
 * @author liuya(liuya@holomaitc.com)
 * @date 2018-12-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <math.h>

#include <holo_c/core/epsilon.h>
#include <holo_c/geometry/point3_float32.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_init_from_scalars(struct Point3f* self, const float32_t x, const float32_t y, const float32_t z)
{
    assert(self != NULL);

    self->x = x;
    self->y = y;
    self->z = z;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_init(struct Point3f* self)
{
    return point3f_init_from_scalars(self, 0.0f, 0.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_init_from_array(struct Point3f* self, const float32_t* array, const uint8_t array_size)
{
    assert(self != NULL);
    assert(array != NULL);

    retcode_t rc = RC_SUCCESS;

    if (array_size < point3f_dim())
    {
        rc = RC_FAIL;
    }
    else
    {
        self->x = array[0];
        self->y = array[1];
        self->z = array[2];

        rc = RC_SUCCESS;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_init_from_vector3f(struct Point3f* self, const struct Vectorf* vector)
{
    assert(self != NULL);
    assert(true == vectorf_is_valid(vector));

    retcode_t rc = RC_SUCCESS;

    if (vector->size != point3f_dim())
    {
        rc = RC_FAIL;
    }
    else
    {
        vectorf_get(vector, 0u, &(self->x));
        vectorf_get(vector, 1u, &(self->y));
        vectorf_get(vector, 2u, &(self->z));
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point3f_is_valid(const struct Point3f* self)
{
    assert(self != NULL);

    bool_t flag = true;

    if (isnan(self->x) || isnan(self->y) || isnan(self->z))
    {
        flag = false;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point3f_is_equal(const struct Point3f* self, const struct Point3f* other)
{
    assert(true == point3f_is_valid(self));
    assert(true == point3f_is_valid(other));

    bool_t flag = true;

    const float32_t diff_x = self->x - other->x;
    const float32_t diff_y = self->y - other->y;
    const float32_t diff_z = self->z - other->z;

    if ((fabsf(diff_x) > holo_float32_epsilon) || (fabsf(diff_y) > holo_float32_epsilon) ||
        (fabsf(diff_z) > holo_float32_epsilon))
    {
        flag = false;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_init_from_point3f(struct Point3f* self, const struct Point3f* other)
{
    assert(self != NULL);
    assert(true == point3f_is_valid(other));

    self->x = other->x;
    self->y = other->y;
    self->z = other->z;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_add(const struct Point3f* self, const struct Point3f* other, struct Point3f* out)
{
    assert(true == point3f_is_valid(self));
    assert(true == point3f_is_valid(other));
    assert(out != NULL);

    out->x = self->x + other->x;
    out->y = self->y + other->y;
    out->z = self->z + other->z;

    retcode_t rc = RC_SUCCESS;

    if (!point3f_is_valid(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_add_vector3f(const struct Point3f* self, const struct Vectorf* other, struct Point3f* out)
{
    assert(true == point3f_is_valid(self));
    assert(true == vectorf_is_valid(other));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (other->size != point3f_dim())
    {
        rc = RC_FAIL;
    }
    else
    {
        out->x = self->x + other->base[0];
        out->y = self->y + other->base[other->pitchx];
        out->z = self->z + other->base[2 * other->pitchx];

        if (!point3f_is_valid(out))
        {
            rc = RC_FAIL;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_sub(const struct Point3f* self, const struct Point3f* other, struct Vectorf* out)
{
    assert(true == point3f_is_valid(self));
    assert(true == point3f_is_valid(other));
    assert(true == vectorf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if (out->size != point3f_dim())
    {
        rc = RC_FAIL;
    }
    else
    {
        out->base[0]               = self->x - other->x;
        out->base[out->pitchx]     = self->y - other->y;
        out->base[2 * out->pitchx] = self->z - other->z;

        if (!vectorf_is_valid(out))
        {
            rc = RC_FAIL;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_sub_vector3f(const struct Point3f* self, const struct Vectorf* other, struct Point3f* out)
{
    assert(true == point3f_is_valid(self));
    assert(true == vectorf_is_valid(other));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (other->size != point3f_dim())
    {
        rc = RC_FAIL;
    }
    else
    {
        out->x = self->x - other->base[0];
        out->y = self->y - other->base[other->pitchx];
        out->z = self->z - other->base[2 * other->pitchx];

        if (!point3f_is_valid(out))
        {
            rc = RC_FAIL;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_negate(struct Point3f* self)
{
    return point3f_multiply_float32(self, -1.0f, self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_multiply_float32(const struct Point3f* self, const float32_t scalar, struct Point3f* out)
{
    assert(true == point3f_is_valid(self));
    assert(out != NULL);

    out->x = self->x * scalar;
    out->y = self->y * scalar;
    out->z = self->z * scalar;

    retcode_t rc = RC_SUCCESS;

    if (!point3f_is_valid(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_divide_float32(const struct Point3f* self, const float32_t scalar, struct Point3f* out)
{
    assert(true == point3f_is_valid(self));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (fabsf(scalar) <= holo_float32_epsilon)
    {
        rc = RC_FAIL;
    }
    else
    {
        out->x = self->x / scalar;
        out->y = self->y / scalar;
        out->z = self->z / scalar;

        if (!point3f_is_valid(out))
        {
            rc = RC_FAIL;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_to_vector3f(const struct Point3f* self, struct Vectorf* out)
{
    assert(true == point3f_is_valid(self));
    assert(true == vectorf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if (out->size != point3f_dim())
    {
        rc = RC_FAIL;
    }
    else
    {
        out->base[0]               = self->x;
        out->base[out->pitchx]     = self->y;
        out->base[2 * out->pitchx] = self->z;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_homogeneous(const struct Point3f* self, struct Vectorf* out)
{
    assert(true == point3f_is_valid(self));
    assert(true == vectorf_is_valid(out));

    retcode_t rc = RC_SUCCESS;
    if (out->size != point3f_dim() + 1u)
    {
        rc = RC_FAIL;
    }
    else
    {
        out->base[0]               = self->x;
        out->base[out->pitchx]     = self->y;
        out->base[2 * out->pitchx] = self->z;
        out->base[3 * out->pitchx] = 1.0;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_dist_sqr(const struct Point3f* self, const struct Point3f* other, float32_t* dist_sqr)
{
    assert(true == point3f_is_valid(self));
    assert(true == point3f_is_valid(other));
    assert(dist_sqr != NULL);

    const float32_t diff_x = self->x - other->x;
    const float32_t diff_y = self->y - other->y;
    const float32_t diff_z = self->z - other->z;

    *dist_sqr = diff_x * diff_x + diff_y * diff_y + diff_z * diff_z;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_dist(const struct Point3f* self, const struct Point3f* other, float32_t* dist)
{
    const retcode_t rc = point3f_dist_sqr(self, other, dist);
    if (rc == RC_SUCCESS)
    {
        *dist = sqrtf(*dist);
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point3f_is_finite(const struct Point3f* self)
{
    assert(true == point3f_is_valid(self));

    return (!isnan(self->x)) && (!isnan(self->y)) && (!isnan(self->z));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point3f_is_zero(const struct Point3f* self)
{
    assert(true == point3f_is_valid(self));

    return (fabsf(self->x) <= holo_float32_epsilon) && (fabsf(self->y) <= holo_float32_epsilon) &&
           (fabsf(self->z) <= holo_float32_epsilon);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_set_constant(struct Point3f* self, const float32_t value)
{
    assert(self != NULL);

    self->x = value;
    self->y = value;
    self->z = value;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_set_zero(struct Point3f* self)
{
    return point3f_set_constant(self, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_set_unit_x(struct Point3f* self)
{
    return point3f_init_from_scalars(self, 1.0f, 0.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_set_unit_y(struct Point3f* self)
{
    return point3f_init_from_scalars(self, 0.0f, 1.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_set_unit_z(struct Point3f* self)
{
    return point3f_init_from_scalars(self, 0.0f, 0.0f, 1.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_expmap(struct Point3f* self, const struct Vectorf* vector)
{
    return point3f_init_from_vector3f(self, vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_logmap(const struct Point3f* self, struct Vectorf* vector)
{
    return point3f_to_vector3f(self, vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t point3f_get_x(const struct Point3f* self)
{
    assert(true == point3f_is_valid(self));

    return self->x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t point3f_get_y(const struct Point3f* self)
{
    assert(true == point3f_is_valid(self));

    return self->y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t point3f_get_z(const struct Point3f* self)
{
    assert(true == point3f_is_valid(self));

    return self->z;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_set_x(struct Point3f* self, const float32_t value)
{
    assert(true == point3f_is_valid(self));

    self->x = value;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_set_y(struct Point3f* self, const float32_t value)
{
    assert(true == point3f_is_valid(self));

    self->y = value;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_set_z(struct Point3f* self, const float32_t value)
{
    assert(true == point3f_is_valid(self));

    self->z = value;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t point3f_get_serialized_size(const struct Point3f* self)
{
    (void) self;

    return serialization_aligned_size(sizeof(struct Point3f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_serialize(const struct Point3f* self,
                            uint8_t* buffer,
                            uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    uint32_t expected_size   = point3f_get_serialized_size(self);
    uint32_t serialized_size = 0;

    retcode_t rc = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_float32(&self->x, 
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);

        serialized_size += serialize_float32(&self->y, 
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);

        serialized_size += serialize_float32(&self->z, 
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);

        serialized_size += serialize_padding(serialized_size,
                                             buffer + serialized_size,
                                             buffer_size - serialized_size);

        assert(serialized_size == expected_size);

        rc = serialized_size;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3f_deserialize(struct Point3f* self,
                              const uint8_t* buffer,
                              uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    uint32_t expected_size   = point3f_get_serialized_size(self);
    uint32_t deserialized_size = 0;

    retcode_t rc = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_float32(&self->x, 
                                                 buffer + deserialized_size, 
                                                 buffer_size - deserialized_size);

        deserialized_size += deserialize_float32(&self->y, 
                                                 buffer + deserialized_size, 
                                                 buffer_size - deserialized_size);

        deserialized_size += deserialize_float32(&self->z, 
                                                 buffer + deserialized_size, 
                                                 buffer_size - deserialized_size);

        deserialized_size += deserialize_padding(deserialized_size,
                                                 buffer + deserialized_size, 
                                                 buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);

        rc = deserialized_size;
    }

    return rc;
}

