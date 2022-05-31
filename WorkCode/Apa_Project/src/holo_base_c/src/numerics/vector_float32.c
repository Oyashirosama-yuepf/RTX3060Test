/*!
 * @file vector_float32.c
 * @brief vector implementation
 * @author zhangjiannan, duyanwei@holomatic.com
 * @date 2019-08-03
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include <holo_c/core/config.h>
#include <holo_c/core/epsilon.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/numerics/vector_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_init(struct Vectorf* self, const uint8_t size, float32_t* buffer, const uint16_t buffer_size)
{
    return matrixf_init((struct Matrixf*)self, size, 1u, buffer, buffer_size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_resize(struct Vectorf* self, uint8_t size)
{
    return matrixf_resize((struct Matrixf*)self, size, 1u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t vectorf_is_valid(const struct Vectorf* self)
{
    assert(self != NULL);

    bool_t flag = true;

    if ((self->rows > HOLO_NUMERICS_VECTOR_MAX_ROWS) || (self->rows < 1u))
    {
        // RC_NUMERICS_VECTOR_ROWS_OUT_OF_RANGE;
        flag = false;
    }
    else if (self->cols != 1u)
    {
        // RC_NUMERICS_VECTOR_COLS_OUT_OF_RANGE;
        flag = false;
    }
    else if (self->base == NULL)
    {
        // RC_NUMERICS_MATRIX_MEMORY_INVALID;
        flag = false;
    }
    else
    {
        ;
    }

    for (uint16_t i = 0u; i < self->rows; i++)
    {
        if ((NULL != self->base) && (self->base[(uint16_t)i * self->pitchx] != self->base[(uint16_t)i * self->pitchx]))
        {
            flag = false;
            break;
        }
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t vectorf_is_equal(const struct Vectorf* self, const struct Vectorf* other)
{
    return matrixf_is_equal((const struct Matrixf*)self, (const struct Matrixf*)other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set_from_array(struct Vectorf* self, const float32_t* array, uint16_t array_size)
{
    return matrixf_set_from_array((struct Matrixf*)self, array, array_size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set_from_vectorf(struct Vectorf* self, const struct Vectorf* other)
{
    return matrixf_set_from_matrixf((struct Matrixf*)self, (const struct Matrixf*)other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_get(const struct Vectorf* self, uint8_t idx, float32_t* out)
{
    return matrixf_get((const struct Matrixf*)self, idx, 0u, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t vectorf_get_unsafe(const struct Vectorf* self, uint8_t idx)
{
    return matrixf_get_unsafe((const struct Matrixf*)self, idx, 0u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set(struct Vectorf* self, uint8_t idx, float32_t value)
{
    return matrixf_set((struct Matrixf*)self, idx, 0u, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set_unsafe(struct Vectorf* self, uint8_t idx, float32_t value)
{
    return matrixf_set_unsafe((struct Matrixf*)self, idx, 0u, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set_constant(struct Vectorf* self, float32_t value)
{
    return matrixf_set_constant((struct Matrixf*)self, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set_zeros(struct Vectorf* self)
{
    return matrixf_set_zeros((struct Matrixf*)self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set_ones(struct Vectorf* self)
{
    return matrixf_set_ones((struct Matrixf*)self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_to_skew_symmetric(const struct Vectorf* self, struct Matrixf* out)
{
    assert(true == vectorf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((self->size != 3u) || (out->rows != 3u) || (out->cols != 3u))
    {
        rc = RC_NUMERICS_MATRIX_SIZE_OUT_OF_RANGE;
    }
    else
    {
        (void)matrixf_set_zeros(out);

        float32_t wx = 0.0f;
        float32_t wy = 0.0f;
        float32_t wz = 0.0f;
        (void)vectorf_get(self, 0u, &wx);
        (void)vectorf_get(self, 1u, &wy);
        (void)vectorf_get(self, 2u, &wz);
        (void)matrixf_set(out, 0u, 1u, -wz);
        (void)matrixf_set(out, 0u, 2u, wy);
        (void)matrixf_set(out, 1u, 0u, wz);
        (void)matrixf_set(out, 1u, 2u, -wx);
        (void)matrixf_set(out, 2u, 0u, -wy);
        (void)matrixf_set(out, 2u, 1u, wx);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_get_segment(const struct Vectorf* self, uint8_t index, uint8_t size, struct Vectorf* out)
{
    assert(true == vectorf_is_valid(self));
    assert(true == vectorf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((((uint16_t)index + size) > self->size) || (((uint16_t)size) != out->size))
    {
        rc = RC_FAIL;
    }
    else
    {
        for (uint8_t i = 0u; i < size; i++)
        {
            out->base[(uint16_t)i * out->pitchx] = self->base[((uint16_t)index + i) * self->pitchx];
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set_segment(struct Vectorf* self, uint8_t index, uint8_t size, const struct Vectorf* in)
{
    assert(true == vectorf_is_valid(self));
    assert(true == vectorf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    if ((((uint16_t)index + size) > self->size) || (size != in->size))
    {
        rc = RC_FAIL;
    }
    else
    {
        for (uint8_t i = 0u; i < size; i++)
        {
            self->base[((uint16_t)index + i) * self->pitchx] = in->base[(uint16_t)i * self->pitchx];
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_get_head(const struct Vectorf* self, uint8_t size, struct Vectorf* out)
{
    return vectorf_get_segment(self, 0u, size, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set_head(struct Vectorf* self, uint8_t size, const struct Vectorf* in)
{
    return vectorf_set_segment(self, 0u, size, in);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_get_tail(const struct Vectorf* self, uint8_t size, struct Vectorf* out)
{
    assert(true == vectorf_is_valid(self));
    assert(true == vectorf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((size > self->size) || (size != out->size))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = vectorf_get_segment(self, self->rows - size, size, out);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_set_tail(struct Vectorf* self, uint8_t size, const struct Vectorf* in)
{
    assert(true == vectorf_is_valid(self));
    assert(true == vectorf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    if ((size > self->size) || (size != in->size))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = vectorf_set_segment(self, self->rows - size, size, in);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint16_t vectorf_get_size(const struct Vectorf* self)
{
    assert(true == vectorf_is_valid(self));
    return self->size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_add(const struct Vectorf* self, const struct Vectorf* other, struct Vectorf* out)
{
    return matrixf_add((const struct Matrixf*)self, (const struct Matrixf*)other, (struct Matrixf*)out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_sub(const struct Vectorf* self, const struct Vectorf* other, struct Vectorf* out)
{
    return matrixf_sub((const struct Matrixf*)self, (const struct Matrixf*)other, (struct Matrixf*)out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_negate(struct Vectorf* self)
{
    return matrixf_negate((struct Matrixf*)self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_multiply_float32(const struct Vectorf* self, float32_t scalar, struct Vectorf* out)
{
    return matrixf_multiply_float32((const struct Matrixf*)self, scalar, (struct Matrixf*)out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_multiply_matrixf(const struct Vectorf* self, const struct Matrixf* other, struct Matrixf* out)
{
    assert(true == vectorf_is_valid(self));
    assert(true == matrixf_is_valid(other));

    if (other->rows != 1u)
    {
        return RC_NUMERICS_MATRIX_MIXED_SIZE;
    }

    return matrixf_multiply((const struct Matrixf*)self, other, out);
}

retcode_t vectorf_multiply_by_matrixf(const struct Vectorf* self, const struct Matrixf* other, struct Vectorf* out)
{
    assert(true == vectorf_is_valid(self));
    assert(true == matrixf_is_valid(other));

    if (other->cols != self->rows)
    {
        return RC_NUMERICS_MATRIX_MIXED_SIZE;
    }

    return matrixf_multiply(other, (const struct Matrixf*)self, (struct Matrixf*)out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_transpose(const struct Vectorf* self, struct Matrixf* out)
{
    assert(true == vectorf_is_valid(self));
    return matrixf_transpose((const struct Matrixf*)self, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_dot(const struct Vectorf* self, const struct Vectorf* other, float32_t* out)
{
    return matrixf_dot((const struct Matrixf*)self, (const struct Matrixf*)other, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_cross(const struct Vectorf* self, const struct Vectorf* other, struct Vectorf* out)
{
    return matrixf_cross((const struct Matrixf*)self, (const struct Matrixf*)other, (struct Matrixf*)out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t vectorf_get_norm_sqr(const struct Vectorf* self)
{
    return matrixf_get_norm_sqr((const struct Matrixf*)self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t vectorf_get_norm(const struct Vectorf* self)
{
    return matrixf_get_norm((const struct Matrixf*)self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t vectorf_normalize(struct Vectorf* self)
{
    assert(true == vectorf_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    const float32_t norm = vectorf_get_norm(self);
    if (norm <= holo_float32_epsilon)
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = vectorf_multiply_float32(self, 1.0f / norm, self);
    }
    return rc;
}

