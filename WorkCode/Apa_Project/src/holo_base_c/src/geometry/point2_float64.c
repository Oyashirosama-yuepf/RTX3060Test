/*!
 * @file point2_float64.c
 * @brief This header file define 2f point.
 * @author liuya(liuya@holomaitc.com), lichao@holomatic.com
 * @date 2018-12-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include <holo_c/core/epsilon.h>
#include <holo_c/geometry/point2_float64.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_init(struct Point2d* self)
{
    return point2d_init_from_scalars(self, 0.0, 0.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_init_from_scalars(struct Point2d* self, float64_t x, float64_t y)
{
    assert(self != NULL);
    assert(!isnan(x));
    assert(!isnan(y));

    retcode_t rc = RC_SUCCESS;

    self->x = x;
    self->y = y;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_init_from_array(struct Point2d* self, const float64_t* array, const uint8_t array_size)
{
    assert(self != NULL);
    assert(array != NULL);

    assert(!isnan(array[0]));
    assert(!isnan(array[1]));

    retcode_t rc = RC_SUCCESS;

    if (array_size < point2d_dim())
    {
        rc = RC_FAIL;
    }
    else
    {
        self->x = array[0];
        self->y = array[1];
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_init_from_point2d(struct Point2d* self, const struct Point2d* other)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(point2d_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    self->x = other->x;
    self->y = other->y;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_add(const struct Point2d* self, const struct Point2d* other, struct Point2d* out)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(point2d_is_valid(self));
    assert(point2d_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    out->x = self->x + other->x;
    out->y = self->y + other->y;

    if (!point2d_is_finite(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_negate(const struct Point2d* self, struct Point2d* out)
{
    assert(self != NULL);
    assert(out != NULL);
    assert(point2d_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    out->x = -self->x;
    out->y = -self->y;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point2d_is_equal(const struct Point2d* self, const struct Point2d* other)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(point2d_is_valid(self));
    assert(point2d_is_valid(other));

    bool_t flag = true;

    if ((fabsf(self->x - other->x) < holo_float64_epsilon) && (fabsf(self->y - other->y) < holo_float64_epsilon))
    {
        flag = true;
    }
    else
    {
        flag = false;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_multiply_float64(const struct Point2d* self, float64_t scale, struct Point2d* out)
{
    assert(self != NULL);
    assert(out != NULL);
    assert(point2d_is_valid(self));
    assert(!isnan(scale));

    retcode_t rc = RC_SUCCESS;

    out->x = self->x * scale;
    out->y = self->y * scale;

    if (!point2d_is_finite(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_divide_float64(const struct Point2d* self, float64_t scale, struct Point2d* out)
{
    assert(self != NULL);
    assert(out != NULL);
    assert(point2d_is_valid(self));
    assert(!isnan(scale));

    retcode_t rc = RC_SUCCESS;

    /* check if the scalar is near to zero */
    if (fabsf(scale) <= holo_float64_epsilon)
    {
        rc = RC_FAIL;
    }

    out->x = self->x / scale;
    out->y = self->y / scale;

    if (!point2d_is_finite(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_dist(const struct Point2d* self, const struct Point2d* other, float64_t* out)
{
    assert(point2d_is_valid(self));
    assert(point2d_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    float64_t distsqr = 0.0;

    rc = point2d_dist_sqr(self, other, &distsqr);

    *out = sqrt(distsqr);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_dist_sqr(const struct Point2d* self, const struct Point2d* other, float64_t* out)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(point2d_is_valid(self));
    assert(point2d_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    float64_t dx = 0.0, dy = 0.0;

    dx = self->x - other->x;
    dy = self->y - other->y;

    *out = ((dx * dx) + (dy * dy));

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float64_t point2d_get_x(const struct Point2d* self)
{
    assert(self != NULL);
    assert(point2d_is_valid(self));

    return self->x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float64_t point2d_get_y(const struct Point2d* self)
{
    assert(self != NULL);
    assert(point2d_is_valid(self));

    return self->y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t point2d_set_x(struct Point2d* self, float64_t in)
{
    assert(self != NULL);
    assert(point2d_is_valid(self));
    assert(!isnan(in));

    retcode_t rc = RC_SUCCESS;

    self->x = in;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t point2d_set_y(struct Point2d* self, float64_t in)
{
    assert(self != NULL);
    assert(point2d_is_valid(self));
    assert(!isnan(in));

    retcode_t rc = RC_SUCCESS;

    self->y = in;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_set_zero(struct Point2d* self)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->x = 0.0;
    self->y = 0.0;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_set_unit_x(struct Point2d* self)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->x = 1.0;
    self->y = 0.0;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_set_unit_y(struct Point2d* self)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->x = 0.0;
    self->y = 1.0;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_to_string(const struct Point2d* self, char_t* string_buf, uint64_t buffer_length)
{
    assert(point2d_is_valid(self));
    retcode_t rc = RC_SUCCESS;

    snprintf(string_buf, buffer_length, "point2: (%f, %f)", self->x, self->y);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point2d_is_valid(const struct Point2d* self)
{
    assert(self != NULL);
    bool_t flag = true;

    if (isnan(self->x) || isnan(self->y))
    {
        flag = false;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point2d_is_finite(const struct Point2d* self)
{
    assert(self != NULL);
    assert(point2d_is_valid(self));

    bool_t flag = true;

    if (isfinite(fabsf(self->x)) && isfinite(fabsf(self->y)))
    {
        flag = true;
    }
    else
    {
        flag = false;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point2d_is_zero(const struct Point2d* self)
{
    assert(self != NULL);
    assert(point2d_is_valid(self));

    bool_t flag = true;

    if (fabsf(self->x) <= holo_float64_epsilon && fabsf(self->y) <= holo_float64_epsilon)
    {
        flag = true;
    }
    else
    {
        flag = false;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t point2d_get_serialized_size(const struct Point2d* self)
{
    (void)self;
    return serialization_aligned_size(sizeof(struct Point2d));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_serialize(const struct Point2d* self, uint8_t* buffer, uint64_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = point2d_get_serialized_size(self);

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_float64(&self->x, buffer, buffer_size);
        serialized_size += serialize_float64(&self->y, 
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);

        assert(serialized_size == expected_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2d_deserialize(struct Point2d* self, const uint8_t* buffer, uint64_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = point2d_get_serialized_size(self); // fixed size object.

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_float64(&self->x, buffer, buffer_size);
        deserialized_size += deserialize_float64(&self->y, 
                                                 buffer + deserialized_size, 
                                                 buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
