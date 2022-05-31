/*!
 * @brief This header file define 2f point.
 * @author liuya(liuya@holomaitc.com), lichao@holomatic.com
 * @date 2018-12-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <assert.h>
#include <holo_c/core/epsilon.h>
#include <holo_c/geometry/point2_float32.h>
#include <holo_c/utils/serialization.h>
#include <math.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_init(struct Point2f* self)
{
    return point2f_init_from_scalars(self, 0.0, 0.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_init_from_scalars(struct Point2f* self, float32_t x, float32_t y)
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
retcode_t point2f_init_from_array(struct Point2f* self, const float32_t* array, const uint8_t array_size)
{
    assert(self != NULL);
    assert(array != NULL);

    assert(!isnan(array[0]));
    assert(!isnan(array[1]));

    retcode_t rc = RC_SUCCESS;

    if (array_size < point2f_dim())
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
retcode_t point2f_init_from_vector2f(struct Point2f* self, const struct Vectorf* other)
{
    assert(self != NULL);
    assert(vectorf_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    vectorf_get(other, 0, &self->x);
    vectorf_get(other, 1, &self->y);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_init_from_point2f(struct Point2f* self, const struct Point2f* other)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(point2f_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    self->x = other->x;
    self->y = other->y;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_add(const struct Point2f* self, const struct Point2f* other, struct Point2f* out)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(point2f_is_valid(self));
    assert(point2f_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    out->x = self->x + other->x;
    out->y = self->y + other->y;

    if (!point2f_is_finite(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_add_vector2f(const struct Point2f* self, const struct Vectorf* vector, struct Point2f* out)
{
    return point2f_translate(self, vector, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_translate(const struct Point2f* self, const struct Vectorf* in, struct Point2f* out)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));
    assert(vectorf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* get first two element from 2D vector */
    float32_t dx = 0.0, dy = 0.0;
    vectorf_get(in, 0, &dx);
    vectorf_get(in, 1, &dy);

    /* translate along each axis */
    out->x = self->x + dx;
    out->y = self->y + dy;

    if (!point2f_is_finite(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_reverse_translate(const struct Point2f* self, const struct Vectorf* in, struct Point2f* out)
{
    /* negate input 2D vector */
    struct Vectorf reverse_in;
    float32_t      reverse_in_buf[VECTORF_MIN_BUF_SIZE(2)] ;
    vectorf_init(&reverse_in, 2, reverse_in_buf, VECTORF_MIN_BUF_SIZE(2)) ;
    vectorf_set_from_vectorf((struct Vectorf*)&reverse_in, (const struct Vectorf*)in);
    vectorf_negate((struct Vectorf*)&reverse_in);

    return point2f_translate(self, &reverse_in, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_sub(const struct Point2f* self, const struct Point2f* other, struct Vectorf* out)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(point2f_is_valid(self));
    assert(point2f_is_valid(other));

    retcode_t rc       = RC_SUCCESS;
    uint16_t  data_idx = 0;
    for (data_idx = 0; data_idx < out->capacity; data_idx++)
        out->base[data_idx] = 0.0f;
    vectorf_set(out, 0, self->x - other->x);
    vectorf_set(out, 1, self->y - other->y);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_negate(const struct Point2f* self, struct Point2f* out)
{
    assert(self != NULL);
    assert(out != NULL);
    assert(point2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    out->x = -self->x;
    out->y = -self->y;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point2f_is_equal(const struct Point2f* self, const struct Point2f* other)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(point2f_is_valid(self));
    assert(point2f_is_valid(other));

    bool_t flag = true;

    if ((fabsf(self->x - other->x) < holo_float32_epsilon) && (fabsf(self->y - other->y) < holo_float32_epsilon))
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
retcode_t point2f_multiply_float32(const struct Point2f* self, float32_t scale, struct Point2f* out)
{
    assert(self != NULL);
    assert(out != NULL);
    assert(point2f_is_valid(self));
    assert(!isnan(scale));

    retcode_t rc = RC_SUCCESS;

    out->x = self->x * scale;
    out->y = self->y * scale;

    if (!point2f_is_finite(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_divide_float32(const struct Point2f* self, float32_t scale, struct Point2f* out)
{
    assert(self != NULL);
    assert(out != NULL);
    assert(point2f_is_valid(self));
    assert(!isnan(scale));

    retcode_t rc = RC_SUCCESS;

    /* check if the scalar is near to zero */
    if (fabsf(scale) <= holo_float32_epsilon)
    {
        rc = RC_FAIL;
    }

    out->x = self->x / scale;
    out->y = self->y / scale;

    if (!point2f_is_finite(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_dist(const struct Point2f* self, const struct Point2f* other, float32_t* out)
{
    assert(point2f_is_valid(self));
    assert(point2f_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    float32_t distsqr = 0.0;

    rc = point2f_dist_sqr(self, other, &distsqr);

    *out = sqrt(distsqr);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_dist_sqr(const struct Point2f* self, const struct Point2f* other, float32_t* out)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(point2f_is_valid(self));
    assert(point2f_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    float32_t dx = 0.0, dy = 0.0;

    dx = self->x - other->x;
    dy = self->y - other->y;

    *out = ((dx * dx) + (dy * dy));

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float32_t point2f_get_x(const struct Point2f* self)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));

    return self->x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float32_t point2f_get_y(const struct Point2f* self)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));

    return self->y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t point2f_set_x(struct Point2f* self, float32_t in)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));
    assert(!isnan(in));

    retcode_t rc = RC_SUCCESS;

    self->x = in;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t point2f_set_y(struct Point2f* self, float32_t in)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));
    assert(!isnan(in));

    retcode_t rc = RC_SUCCESS;

    self->y = in;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_to_vector2f(const struct Point2f* self, struct Vectorf* out)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));

    retcode_t rc       = RC_SUCCESS;
    uint16_t  data_idx = 0;
    for (data_idx = 0; data_idx < out->capacity; data_idx++)
        out->base[data_idx] = 0.0f;
    vectorf_set(out, 0, self->x);
    vectorf_set(out, 1, self->y);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_homogeneous(const struct Point2f* self, struct Vectorf* out)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    /* initialize output and set elements */
    uint16_t data_idx = 0;
    for (data_idx = 0; data_idx < out->capacity; data_idx++)
        out->base[data_idx] = 0.0f;
    vectorf_set(out, 0, self->x);
    vectorf_set(out, 1, self->y);
    vectorf_set(out, 2, 1.0);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_expmap(const struct Vectorf* self, struct Point2f* out)
{
    assert(self != NULL);
    assert(vectorf_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    vectorf_get(self, 0, &out->x);
    vectorf_get(self, 1, &out->y);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_logmap(const struct Point2f* self, struct Vectorf* out)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    /* initialize output and set elements */
    uint16_t data_idx = 0;
    for (data_idx = 0; data_idx < out->capacity; data_idx++)
        out->base[data_idx] = 0.0f;
    vectorf_set(out, 0, self->x);
    vectorf_set(out, 1, self->y);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_set_zero(struct Point2f* self)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->x = 0.0;
    self->y = 0.0;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_set_unit_x(struct Point2f* self)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->x = 1.0;
    self->y = 0.0;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_set_unit_y(struct Point2f* self)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    self->x = 0.0;
    self->y = 1.0;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_to_string(const struct Point2f* self, char_t* string_buf, uint32_t buffer_length)
{
    assert(point2f_is_valid(self));
    retcode_t rc = RC_SUCCESS;

    snprintf(string_buf, buffer_length, "point2: (%f, %f)", self->x, self->y);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point2f_is_valid(const struct Point2f* self)
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
bool_t point2f_is_finite(const struct Point2f* self)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));

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
bool_t point2f_is_zero(const struct Point2f* self)
{
    assert(self != NULL);
    assert(point2f_is_valid(self));

    bool_t flag = true;

    if (fabsf(self->x) <= holo_float32_epsilon && fabsf(self->y) <= holo_float32_epsilon)
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
uint32_t point2f_get_serialized_size(const struct Point2f* self)
{
    (void)self;
    HOLO_STATIC_ASSERT(sizeof(struct Point2f) % 8 == 0);
    return sizeof(struct Point2f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_serialize(const struct Point2f* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = point2f_get_serialized_size(self);

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_float32(&self->x, buffer, buffer_size);
        serialized_size += serialize_float32(&self->y, 
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);

        assert(serialized_size == expected_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point2f_deserialize(struct Point2f* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = point2f_get_serialized_size(self); // fixed size object.

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_float32(&self->x, buffer, buffer_size);
        deserialized_size += deserialize_float32(&self->y, 
                                                 buffer + deserialized_size, 
                                                 buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
