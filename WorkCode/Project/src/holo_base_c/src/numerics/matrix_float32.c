/*!
 * @file matrix_float32.c
 * @brief implementation of matrix in holo_c
 * @author huangqi, duyanwei@holomatic.com
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
#include <holo_c/numerics/matrix_float32.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_init(struct Matrixf* self, uint8_t rows, uint8_t cols, float32_t* buffer, uint16_t buffer_size)
{
    // init check
    assert(self != NULL);
    assert(buffer != NULL);
    assert(MATRIXF_ELE_ALIGN_CNT(rows) <= HOLO_NUMERICS_MATRIX_MAX_ROWS);
    assert(MATRIXF_ELE_ALIGN_CNT(cols) <= HOLO_NUMERICS_MATRIX_MAX_COLS);
    assert(buffer_size >= MATRIXF_MIN_BUF_SIZE(rows, cols));
    assert(buffer_size <= HOLO_NUMERICS_MATRIX_MAX_SIZE);

    retcode_t rc = RC_SUCCESS;

    const uint16_t size = (uint16_t)(rows) * (cols);
    if (buffer_size < MATRIXF_MIN_BUF_SIZE((uint16_t)(rows), (uint16_t)(cols)))
    {
        rc = RC_NUMERICS_MATRIX_SIZE_OUT_OF_RANGE;
    }
    else
    {
        self->rows     = rows;
        self->cols     = cols;
        self->size     = size;
        self->pitchx   = MATRIXF_ELE_ALIGN_CNT(cols);
        self->pitchy   = MATRIXF_ELE_ALIGN_CNT(rows);
        self->capacity = buffer_size;
        self->base     = buffer;

        // initialize all the elements to zero
        for (uint16_t i = 0u; i < self->capacity; i++)
        {
            self->base[i] = 0.0f;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_resize(struct Matrixf* self, uint8_t rows, uint8_t cols)
{
    assert(self != NULL);
    assert(MATRIXF_ELE_ALIGN_CNT(rows) <= HOLO_NUMERICS_MATRIX_MAX_ROWS);
    assert(MATRIXF_ELE_ALIGN_CNT(cols) <= HOLO_NUMERICS_MATRIX_MAX_COLS);

    retcode_t rc = RC_SUCCESS;

    if (MATRIXF_MIN_BUF_SIZE((uint16_t)(rows), (uint16_t)(cols)) <= self->capacity)
    {
        self->rows   = rows;
        self->cols   = cols;
        self->size   = (uint16_t)rows * cols;
        self->pitchx = MATRIXF_ELE_ALIGN_CNT(cols);
        self->pitchy = MATRIXF_ELE_ALIGN_CNT(rows);
        for (uint16_t data_idx = 0; data_idx < self->capacity; ++data_idx)
        {
            self->base[data_idx] = 0.0f;
        }
    }
    else
    {
        rc = RC_NUMERICS_MATRIX_SIZE_OUT_OF_RANGE;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t matrixf_is_valid(const struct Matrixf* self)
{
    assert(self != NULL);

    bool_t flag = true;

    if (self->rows > HOLO_NUMERICS_MATRIX_MAX_ROWS || self->rows < 1u)
    {
        // RC_NUMERICS_MATRIX_ROWS_OUT_OF_RANGE;
        flag = false;
    }
    else if (self->cols > HOLO_NUMERICS_MATRIX_MAX_COLS || self->cols < 1u)
    {
        // RC_NUMERICS_MATRIX_COLS_OUT_OF_RANGE;
        flag = false;
    }
    else if (self->size > HOLO_NUMERICS_MATRIX_MAX_SIZE || self->size < 1u)
    {
        // RC_NUMERICS_MATRIX_SIZE_OUT_OF_RANGE;
        flag = false;
    }
    else if (self->size != ((uint16_t)(self->rows) * self->cols))
    {
        flag = false;
    }
    else if ((self->pitchx != MATRIXF_ELE_ALIGN_CNT(self->cols)) || (0 == self->pitchx))
    {
        flag = false;
    }
    else if (self->pitchy != MATRIXF_ELE_ALIGN_CNT(self->rows) || (0 == self->pitchy))
    {
        flag = false;
    }
    else if (self->base == NULL)
    {
        // RC_NUMERICS_MATRIX_MEMORY_INVALID;
        flag = false;
    }
    else
    {
        for (uint8_t i = 0u; i < self->rows; ++i)
        {
            for (uint8_t j = 0u; j < self->cols; ++j)
            {
                if (isnan(self->base[((uint16_t)i * self->pitchx) + j]))
                {
                    flag = false;
                    break;
                }
            }
            for (uint8_t j = self->cols; j < self->pitchx; ++j)
            {
                if (self->base[((uint16_t)i * self->pitchx) + j] != 0.0f)
                {
                    flag = false;
                    break;
                }
            }
        }
        for (uint8_t i = self->rows; i < self->pitchy; ++i)
        {
            for (uint8_t j = 0u; j < self->pitchx; ++j)
            {
                if (self->base[((uint16_t)i * self->pitchx) + j] != 0.0f)
                {
                    flag = false;
                    break;
                }
            }
        }
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t matrixf_is_equal(const struct Matrixf* self, const struct Matrixf* other)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(other));

    bool_t flag = true;

    if (self->rows != other->rows)
    {
        // RC_NUMERICS_MATRIX_MIXED_ROWS;
        flag = false;
    }
    else if (self->cols != other->cols)
    {
        // RC_NUMERICS_MATRIX_MIXED_COLS;
        flag = false;
    }
    else
    {
        for (uint8_t i = 0u; i < self->rows; i++)
        {
            for (uint8_t j = 0u; j < self->cols; j++)
            {
                const float32_t diff = fabsf(self->base[((uint16_t)i * self->pitchx) + j] -
                                             other->base[((uint16_t)i * other->pitchx) + j]);
                if (diff > holo_float32_epsilon)
                {
                    flag = false;
                    break;
                }
            }
        }
    }
    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_from_array(struct Matrixf* self, const float32_t* array, uint16_t array_size)
{
    assert(self != NULL);
    assert(self->base != NULL);
    assert(array != NULL);

    retcode_t rc = RC_SUCCESS;

    for (uint16_t m = 0u; m < self->capacity; m++)
    {
        self->base[m] = 0.0f;
    }

    uint16_t data_idx = 0;
    for (uint8_t i = 0u; i < self->rows; i++)
    {
        for (uint8_t j = 0u; j < self->cols; j++)
        {
            if (array_size > data_idx)
            {
                self->base[((uint16_t)i * self->pitchx) + j] = array[data_idx];
            }
            data_idx++;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_from_array_unsafe(struct Matrixf* self, const float32_t* array, uint16_t array_size)
{
    for (uint16_t m = 0u; m < self->capacity; m++)
    {
        self->base[m] = 0.0f;
    }

    uint16_t data_idx = 0;
    for (uint8_t i = 0u; i < self->rows; i++)
    {
        for (uint8_t j = 0u; j < self->cols; j++)
        {
            if (array_size > data_idx)
            {
                self->base[((uint16_t)i * self->pitchx) + j] = array[data_idx];
            }
            data_idx++;
        }
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_from_matrixf(struct Matrixf* self, const struct Matrixf* other)
{
    assert(self != NULL);
    assert(self->base != NULL);
    assert(true == matrixf_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    if ((self->rows != other->rows) || (self->cols != other->cols))
    {
        rc = RC_NUMERICS_MATRIX_MIXED_SIZE;
    }
    else
    {
        for (uint16_t data_idx = 0u; data_idx < self->capacity; data_idx++)
        {
            self->base[data_idx] = 0;
        }

        for (uint8_t i = 0u; i < self->rows; i++)
        {
            for (uint8_t j = 0u; j < self->cols; j++)
            {
                self->base[((uint16_t)i * self->pitchx) + j] = other->base[((uint16_t)i * other->pitchx) + j];
            }
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_from_matrixf_unsafe(struct Matrixf* self, const struct Matrixf* other)
{
    for (uint16_t data_idx = 0u; data_idx < self->capacity; data_idx++)
    {
        self->base[data_idx] = 0;
    }

    for (uint16_t i = 0u; i < self->capacity; i++)
    {
        self->base[i] = other->base[i];
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_get(const struct Matrixf* self, uint8_t row, uint8_t col, float32_t* out)
{
    assert(true == matrixf_is_valid(self));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (row >= self->rows)
    {
        rc = RC_NUMERICS_MATRIX_ROWS_OUT_OF_RANGE;
    }
    else if (col >= self->cols)
    {
        rc = RC_NUMERICS_MATRIX_COLS_OUT_OF_RANGE;
    }
    else
    {
        *out = self->base[((uint16_t)row * self->pitchx) + col];
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t matrixf_get_unsafe(const struct Matrixf* self, uint8_t row, uint8_t col)
{
    return self->base[((uint16_t)row * self->pitchx) + col];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set(struct Matrixf* self, uint8_t row, uint8_t col, float32_t value)
{
    assert(true == matrixf_is_valid(self));
    retcode_t rc = RC_SUCCESS;

    if (row >= self->rows)
    {
        rc = RC_NUMERICS_MATRIX_ROWS_OUT_OF_RANGE;
    }
    else if (col >= self->cols)
    {
        rc = RC_NUMERICS_MATRIX_COLS_OUT_OF_RANGE;
    }
    else
    {
        self->base[((uint16_t)row * self->pitchx) + col] = value;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_unsafe(struct Matrixf* self, uint8_t row, uint8_t col, float32_t value)
{
    self->base[((uint16_t)row * self->pitchx) + col] = value;
    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_constant(struct Matrixf* self, float32_t value)
{
    assert(true == matrixf_is_valid(self));

    for (uint8_t i = 0u; i < self->rows; i++)
    {
        for (uint8_t j = 0u; j < self->cols; j++)
        {
            self->base[((uint16_t)i * self->pitchx) + j] = value;
        }
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_zeros(struct Matrixf* self)
{
    return matrixf_set_constant(self, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_ones(struct Matrixf* self)
{
    return matrixf_set_constant(self, 1.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_identity(struct Matrixf* self)
{
    assert(true == matrixf_is_valid(self));

    for (uint8_t i = 0; i < self->rows; i++)
    {
        for (uint8_t j = 0; j < self->cols; j++)
        {
            const float32_t value = (i == j) ? 1.0f : 0.0f;

            self->base[((uint16_t)i * self->pitchx) + j] = value;
        }
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_get_block(const struct Matrixf* self, uint8_t i, uint8_t j, uint8_t rows, uint8_t cols,
                            struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if (((i + rows) > self->rows) || ((j + cols) > self->cols) || (rows != out->rows) || (cols != out->cols))
    {
        rc = RC_FAIL;
    }
    else
    {
        for (uint8_t m = 0u; m < rows; m++)
        {
            const uint16_t out_index  = (uint16_t)m * out->pitchx;
            const uint16_t self_index = ((uint16_t)m + i) * (uint16_t)self->pitchx;
            for (uint8_t n = 0u; n < cols; n++)
            {
                out->base[out_index + n] = self->base[self_index + n + j];
            }
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_block(struct Matrixf* self, const uint8_t i, const uint8_t j, const uint8_t rows,
                            const uint8_t cols, const struct Matrixf* in)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    if (((i + rows) > self->rows) || ((j + cols) > self->cols) || (rows != in->rows) || (cols != in->cols))
    {
        rc = RC_FAIL;
    }
    else
    {
        for (uint8_t m = 0u; m < rows; m++)
        {
            const uint16_t in_index   = (uint16_t)m * in->pitchx;
            const uint16_t self_index = ((uint16_t)m + i) * self->pitchx;
            for (uint8_t n = 0u; n < cols; n++)
            {
                self->base[self_index + n + j] = in->base[in_index + n];
            }
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_get_top_left_corner(const struct Matrixf* self, uint8_t rows, uint8_t cols, struct Matrixf* out)
{
    return matrixf_get_block(self, 0u, 0u, rows, cols, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_top_left_corner(struct Matrixf* self, uint8_t rows, uint8_t cols, const struct Matrixf* in)
{
    return matrixf_set_block(self, 0u, 0u, rows, cols, in);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_get_top_right_corner(const struct Matrixf* self, uint8_t rows, uint8_t cols, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((rows > self->rows) || (cols > self->cols) || (rows != out->rows) || (cols != out->cols))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = matrixf_get_block(self, 0u, self->cols - cols, rows, cols, out);
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_top_right_corner(struct Matrixf* self, uint8_t rows, uint8_t cols, const struct Matrixf* in)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    if ((rows > self->rows) || (cols > self->cols) || (rows != in->rows) || (cols != in->cols))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = matrixf_set_block(self, 0u, self->cols - cols, rows, cols, in);
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_get_bottom_left_corner(const struct Matrixf* self, uint8_t rows, uint8_t cols, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((rows > self->rows) || (cols > self->cols) || (rows != out->rows) || (cols != out->cols))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = matrixf_get_block(self, self->rows - rows, 0u, rows, cols, out);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_bottom_left_corner(struct Matrixf* self, uint8_t rows, uint8_t cols, const struct Matrixf* in)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    if ((rows > self->rows) || (cols > self->cols) || (rows != in->rows) || (cols != in->cols))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = matrixf_set_block(self, self->rows - rows, 0u, rows, cols, in);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_get_bottom_right_corner(const struct Matrixf* self, uint8_t rows, uint8_t cols, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((rows > self->rows) || (cols > self->cols) || (rows != out->rows) || (cols != out->cols))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = matrixf_get_block(self, self->rows - rows, self->cols - cols, rows, cols, out);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_set_bottom_right_corner(struct Matrixf* self, uint8_t rows, uint8_t cols, const struct Matrixf* in)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    if ((rows > self->rows) || (cols > self->cols) || (rows != in->rows) || (cols != in->cols))
    {
        rc = RC_FAIL;
    }
    else
    {
        rc = matrixf_set_block(self, self->rows - rows, self->cols - cols, rows, cols, in);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_get_row(const struct Matrixf* self, uint8_t index, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((index >= self->rows) || (out->cols != self->cols) || (out->rows != 1u))
    {
        rc = RC_FAIL;
    }
    else
    {
        for (uint8_t i = 0u; i < self->cols; i++)
        {
            const uint16_t idx = ((uint16_t)index * self->pitchx) + i;
            out->base[i]       = self->base[idx];
        }
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_get_col(const struct Matrixf* self, uint8_t index, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((index >= self->cols) || (out->rows != self->rows) || (out->cols != 1u))
    {
        rc = RC_FAIL;
    }
    else
    {
        for (uint8_t i = 0u; i < self->rows; i++)
        {
            const uint16_t idx         = ((uint16_t)i * self->pitchx) + index;
            out->base[i * out->pitchx] = self->base[idx];
        }
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t matrixf_get_rows(const struct Matrixf* self)
{
    assert(true == matrixf_is_valid(self));
    return self->rows;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t matrixf_get_cols(const struct Matrixf* self)
{
    assert(true == matrixf_is_valid(self));
    return self->cols;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint16_t matrixf_get_size(const struct Matrixf* self)
{
    assert(true == matrixf_is_valid(self));
    return self->size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_add(const struct Matrixf* self, const struct Matrixf* other, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(other));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((self->rows == other->rows) && (self->cols == other->cols) && (self->rows == out->rows) &&
        (self->cols == out->cols))
    {
        for (uint16_t i = 0u; i < out->rows; i++)
        {
            for (uint16_t j = 0u; j < out->cols; j++)
            {
                out->base[((uint16_t)i * out->pitchx) + j] =
                    self->base[((uint16_t)i * self->pitchx) + j] + other->base[((uint16_t)i * other->pitchx) + j];
            }
        }
    }
    else
    {
        if ((out->rows != self->rows) || (out->rows != other->rows))
            rc = RC_NUMERICS_MATRIX_MIXED_ROWS;
        else if ((out->cols != self->cols) || (out->cols != other->cols))
            rc = RC_NUMERICS_MATRIX_MIXED_COLS;
        else
            rc = RC_NUMERICS_MATRIX_MIXED_SIZE;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_sub(const struct Matrixf* self, const struct Matrixf* other, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(other));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((self->rows == other->rows) && (self->cols == other->cols) && (self->rows == out->rows) &&
        (self->cols == out->cols))
    {
        for (uint16_t i = 0u; i < out->rows; i++)
        {
            for (uint16_t j = 0u; j < out->cols; j++)
            {
                out->base[((uint16_t)i * out->pitchx) + j] =
                    self->base[((uint16_t)i * self->pitchx) + j] - other->base[((uint16_t)i * other->pitchx) + j];
            }
        }
    }
    else
    {
        if ((out->rows != self->rows) || (out->rows != other->rows))
        {
            rc = RC_NUMERICS_MATRIX_MIXED_ROWS;
        }
        else if ((out->cols != self->cols) || (out->cols != other->cols))
        {
            rc = RC_NUMERICS_MATRIX_MIXED_COLS;
        }
        else
        {
            rc = RC_NUMERICS_MATRIX_MIXED_SIZE;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_negate(struct Matrixf* self)
{
    assert(true == matrixf_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    for (uint16_t i = 0u; i < self->rows; i++)
    {
        for (uint16_t j = 0u; j < self->cols; j++)
        {
            self->base[((uint16_t)i * self->pitchx) + j] = -self->base[((uint16_t)i * self->pitchx) + j];
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_multiply_float32(const struct Matrixf* self, float32_t scalar, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((self->rows == out->rows) && (self->cols == out->cols))
    {
        for (uint16_t i = 0u; i < out->rows; i++)
        {
            for (uint16_t j = 0u; j < out->cols; j++)
            {
                out->base[((uint16_t)i * out->pitchx) + j] = self->base[((uint16_t)i * self->pitchx) + j] * scalar;
            }
        }
    }
    else
    {
        if ((out->rows != self->rows) && (out->cols != self->cols))
        {
            rc = RC_NUMERICS_MATRIX_MIXED_SIZE;
        }
        else if (out->rows != self->rows)
        {
            rc = RC_NUMERICS_MATRIX_MIXED_ROWS;
        }
        else
        {
            rc = RC_NUMERICS_MATRIX_MIXED_COLS;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void matrixf_internal_multiply(const struct Matrixf* lhs, const struct Matrixf* rhs, struct Matrixf* out)
{
    for (uint8_t i = 0u; i < out->rows; i++)
    {
        for (uint8_t j = 0u; j < out->cols; j++)
        {
            const uint16_t out_idx = ((uint16_t)i * out->pitchx) + j;

            out->base[out_idx] = 0.0f;

            for (uint8_t k = 0u; k < lhs->cols; k++)
            {
                const uint16_t self_idx  = ((uint16_t)i * lhs->pitchx) + k;
                const uint16_t other_idx = ((uint16_t)k * rhs->pitchx) + j;
                out->base[out_idx] += lhs->base[self_idx] * rhs->base[other_idx];
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_multiply(const struct Matrixf* self, const struct Matrixf* other, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(other));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((out->rows == self->rows) && (out->cols == other->cols) && (self->cols == other->rows))
    {
        if (self == out || other == out)
        {
            if (self == out && other == out)
            {
                const uint8_t  rows0 = self->rows;
                const uint8_t  cols0 = self->cols;
                struct Matrixf tmp_mat0;
                float32_t      tmp_mat0_buf[MATRIXF_MIN_BUF_SIZE(rows0, cols0)];
                matrixf_init(&tmp_mat0, rows0, cols0, tmp_mat0_buf,
                             MATRIXF_MIN_BUF_SIZE(((uint16_t)rows0), ((uint16_t)cols0)));
                matrixf_set_from_matrixf(&tmp_mat0, self);

                const uint8_t  rows1 = other->rows;
                const uint8_t  cols1 = other->cols;
                struct Matrixf tmp_mat1;
                float32_t      tmp_mat1_buf[MATRIXF_MIN_BUF_SIZE(rows1, cols1)];
                matrixf_init(&tmp_mat1, rows1, cols1, tmp_mat1_buf,
                             MATRIXF_MIN_BUF_SIZE(((uint16_t)rows1), ((uint16_t)cols1)));
                matrixf_set_from_matrixf(&tmp_mat1, other);

                matrixf_internal_multiply(&tmp_mat0, &tmp_mat1, out);
            }
            else if (self == out)
            {
                struct Matrixf tmp_mat;
                const uint8_t  rows = self->rows;
                const uint8_t  cols = self->cols;
                float32_t      tmp_mat_buf[MATRIXF_MIN_BUF_SIZE(rows, cols)];
                matrixf_init(&tmp_mat, rows, cols, tmp_mat_buf,
                             MATRIXF_MIN_BUF_SIZE(((uint16_t)rows), ((uint16_t)cols)));
                matrixf_set_from_matrixf(&tmp_mat, self);
                matrixf_internal_multiply(&tmp_mat, other, out);
            }
            else
            {
                struct Matrixf tmp_mat;
                const uint8_t  rows = other->rows;
                const uint8_t  cols = other->cols;
                float32_t      tmp_mat_buf[MATRIXF_MIN_BUF_SIZE(rows, cols)];
                matrixf_init(&tmp_mat, rows, cols, tmp_mat_buf,
                             MATRIXF_MIN_BUF_SIZE(((uint16_t)rows), ((uint16_t)cols)));
                matrixf_set_from_matrixf(&tmp_mat, other);
                matrixf_internal_multiply(self, &tmp_mat, out);
            }
        }
        else
        {
            matrixf_internal_multiply(self, other, out);
        }
    }
    else
    {
        rc = RC_NUMERICS_MATRIX_MIXED_SIZE;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void matrixf_internal_transpose(const struct Matrixf* self, struct Matrixf* out)
{
    for (uint8_t i = 0u; i < out->rows; i++)
    {
        for (uint8_t j = 0u; j < out->cols; j++)
        {
            const uint16_t out_index  = ((uint16_t)i * out->pitchx) + j;
            const uint16_t self_index = ((uint16_t)j * out->pitchy) + i;

            out->base[out_index] = self->base[self_index];
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_transpose(const struct Matrixf* self, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((out->rows != self->cols) || (out->cols != self->rows))
    {
        rc = RC_NUMERICS_MATRIX_MIXED_SIZE;
    }
    else if (self == out)
    {
        // copy self
        const uint8_t  rows = self->rows;
        const uint8_t  cols = self->cols;
        struct Matrixf lhs;
        float32_t      lhs_buf[MATRIXF_MIN_BUF_SIZE(rows, cols)];
        matrixf_init(&lhs, rows, cols, lhs_buf, MATRIXF_MIN_BUF_SIZE(((uint16_t)rows), ((uint16_t)cols)));
        matrixf_set_from_matrixf(&lhs, self);
        matrixf_internal_transpose(&lhs, out);
    }
    else
    {
        matrixf_internal_transpose(self, out);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t matrixf_get_norm_sqr(const struct Matrixf* self)
{
    assert(true == matrixf_is_valid(self));

    float32_t value = 0.0f;
    for (uint8_t i = 0u; i < self->rows; i++)
    {
        for (uint8_t j = 0u; j < self->cols; j++)
        {
            const uint16_t idx = ((uint16_t)i * self->pitchx) + j;
            value += self->base[idx] * self->base[idx];
        }
    }

    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t matrixf_get_norm(const struct Matrixf* self)
{
    const float32_t value = matrixf_get_norm_sqr(self);
    return sqrtf(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_inverse(const struct Matrixf* self, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if ((out->rows != out->cols) || (self->rows != self->cols))
    {
        rc = RC_NUMERICS_MATRIX_NOT_SQUARE;
    }
    else if ((out->rows != self->rows))
    {
        rc = RC_NUMERICS_MATRIX_MIXED_SIZE;
    }
    else
    {
        /**
         * @brief we have three methods to compute the inverse of a matrix
         * a. gauss-jordan elimination
         * b. forward elimination and backward substitution
         * c. determinant and its adjugate matrix
         * here we choose option a
         */

        // copy self matrix to a new mat to avoid in-place value change (when self == out)
        const uint8_t  self_rows = self->rows;
        const uint8_t  self_cols = self->cols;
        struct Matrixf mat;
        float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(self_rows, self_cols)];
        matrixf_init(&mat, self_rows, self_cols, mat_buf,
                     MATRIXF_MIN_BUF_SIZE(((uint16_t)self_rows), ((uint16_t)self_cols)));
        matrixf_set_from_matrixf(&mat, self);

        // set out matrix to identity
        matrixf_set_identity(out);

        uint8_t   i = 0, j = 0, k = 0;
        float32_t max = 0.0f, tmp = 0.0f;
        for (i = 0; i < self_cols; i++)
        {
            max = mat.base[((uint16_t)i * mat.pitchx) + i];
            k   = i;
            for (j = i + 1; j < self_rows; j++)
            {
                if (fabsf(mat.base[((uint16_t)j * mat.pitchx) + i]) > fabsf(max))
                {
                    max = mat.base[((uint16_t)j * mat.pitchx) + i];
                    k   = j;
                }
            }

            if (k != i)
            {
                for (j = 0; j < self_rows; j++)
                {
                    const uint16_t idx1 = ((uint16_t)i * mat.pitchx) + j;
                    const uint16_t idx2 = ((uint16_t)k * mat.pitchx) + j;
                    tmp                 = mat.base[idx1];
                    mat.base[idx1]      = mat.base[idx2];
                    mat.base[idx2]      = tmp;

                    tmp             = out->base[idx1];
                    out->base[idx1] = out->base[idx2];
                    out->base[idx2] = tmp;
                }
            }

            if (fabsf(mat.base[((uint16_t)i * mat.pitchx) + i]) <= holo_float32_epsilon)
            {
                return RC_NUMERICS_MATRIX_SINGULAR;
            }

            tmp = mat.base[((uint16_t)i * mat.pitchx) + i];
            for (j = 0; j < self_rows; j++)
            {
                const uint16_t idx = ((uint16_t)i * mat.pitchx) + j;
                mat.base[idx]      = mat.base[idx] / tmp;
                out->base[idx]     = out->base[idx] / tmp;
            }
            for (j = 0; j < self_rows; j++)
            {
                if (j != i)
                {
                    tmp = mat.base[((uint16_t)j * mat.pitchx) + i];
                    for (k = 0; k < self_rows; k++)
                    {
                        const uint16_t idx1 = ((uint16_t)j * mat.pitchx) + k;
                        const uint16_t idx2 = ((uint16_t)i * mat.pitchx) + k;
                        mat.base[idx1]      = mat.base[idx1] - mat.base[idx2] * tmp;
                        out->base[idx1]     = out->base[idx1] - out->base[idx2] * tmp;
                    }
                }
            }
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_determinant(const struct Matrixf* self, float32_t* out)
{
    assert(true == matrixf_is_valid(self));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (self->rows != self->cols)
    {
        rc = RC_NUMERICS_MATRIX_NOT_SQUARE;
    }
    else
    {
        /**
         * @brief we have two methods to compute the determinant of a matrix
         * a. recursive to expand determinant
         * b. convert matrix to an upper diagonal matrix by determinant properties
         * here we choose option b
         */

        // copy self matrix to a new mat to avoid in-place value change
        const uint8_t  self_rows = self->rows;
        const uint8_t  self_cols = self->cols;
        struct Matrixf mat;
        float32_t      mat_buf[MATRIXF_MIN_BUF_SIZE(self_rows, self_cols)];
        matrixf_init(&mat, self_rows, self_cols, mat_buf,
                     MATRIXF_MIN_BUF_SIZE(((uint16_t)self_rows), ((uint16_t)self_cols)));
        matrixf_set_from_matrixf(&mat, self);

        float32_t sign   = 1.0f;
        float32_t factor = 1.0f;

        for (uint8_t row = 0u; row < self->rows; row++)
        {
            // make sure current diagonal element is max
            uint8_t   pivot_row = row;
            float32_t max       = mat.base[((uint16_t)row * self->pitchx) + row];
            for (uint8_t i = row + 1u; i < self->rows; i++)
            {
                const float32_t value = mat.base[((uint16_t)i * self->pitchx) + row];
                if (fabsf(value) > fabs(max))
                {
                    pivot_row = i;
                    max       = value;
                }
            }

            if (fabsf(max) <= holo_float32_epsilon)
            {
                *out = 0.0f;
                return rc;
            }

            // swap two rows if necessary
            if (pivot_row != row)
            {
                for (uint8_t j = 0u; j < self->cols; j++)
                {
                    const uint16_t idx1 = ((uint16_t)row * self->pitchx) + j;
                    const uint16_t idx2 = ((uint16_t)pivot_row * self->pitchx) + j;

                    float32_t value = mat.base[idx1];
                    mat.base[idx1]  = mat.base[idx2];
                    mat.base[idx2]  = value;
                }
                // toggle sign
                sign *= -1.0f;
            }

            // zero out other values that are below current diagonal value
            const float32_t pivot_value = mat.base[row * self->pitchx + row];
            for (uint8_t i = row + 1u; i < self->rows; i++)
            {
                const float32_t value = mat.base[i * self->pitchx + row];
                if (fabsf(value) > holo_float32_epsilon)
                {
                    for (uint8_t j = 0u; j < self->cols; j++)
                    {
                        const uint16_t idx1 = ((uint16_t)i * self->pitchx) + j;
                        const uint16_t idx2 = ((uint16_t)row * self->pitchx) + j;

                        mat.base[idx1] = pivot_value * mat.base[idx1] - value * mat.base[idx2];
                    }

                    // increase factor
                    factor *= pivot_value;
                }
            }
        }

        // recover the determiant of input matrix from upper diagonal matrix
        *out = 1.0f;
        for (uint8_t i = 0u; i < self->rows; i++)
        {
            *out *= mat.base[((uint16_t)i * self->pitchx) + i];
        }

        *out = (*out) / factor * sign;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_dot(const struct Matrixf* self, const struct Matrixf* other, float32_t* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(other));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if ((self->cols != 1u) || (other->cols != 1u))
    {
        rc = RC_NUMERICS_MATRIX_COLS_OUT_OF_RANGE;
    }
    else if (self->rows != other->rows)
    {
        rc = RC_NUMERICS_MATRIX_MIXED_ROWS;
    }
    else
    {
        *out = 0.0f;
        for (uint8_t i = 0u; i < self->rows; i++)
        {
            *out += self->base[(uint16_t)i * self->pitchx] * other->base[(uint16_t)i * other->pitchx];
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void matrixf_internal_cross(const struct Matrixf* self, const struct Matrixf* other, struct Matrixf* out)
{
    out->base[0] = self->base[self->pitchx] * other->base[2u * other->pitchx] -
                   self->base[2u * self->pitchx] * other->base[other->pitchx];
    out->base[out->pitchx] =
        self->base[2u * self->pitchx] * other->base[0] - self->base[0] * other->base[2u * other->pitchx];
    out->base[2u * out->pitchx] =
        self->base[0] * other->base[other->pitchx] - self->base[self->pitchx] * other->base[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_cross(const struct Matrixf* self, const struct Matrixf* other, struct Matrixf* out)
{
    assert(true == matrixf_is_valid(self));
    assert(true == matrixf_is_valid(other));
    assert(true == matrixf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    if (((out->rows == 3u) && (out->cols == 1u)) && ((self->rows == 3u) && (self->cols == 1u)) &&
        ((other->rows == 3u) && (other->cols == 1u)))
    {
        if ((self == out) || (other == out))
        {
            if ((self == out) && (other == out))
            {
                // copy self
                uint8_t        rows = self->rows;
                uint8_t        cols = self->cols;
                struct Matrixf lhs;
                float32_t      lhs_buf[MATRIXF_MIN_BUF_SIZE(rows, cols)];
                matrixf_init(&lhs, rows, cols, lhs_buf, MATRIXF_MIN_BUF_SIZE(((uint16_t)rows), ((uint16_t)cols)));
                matrixf_set_from_matrixf(&lhs, self);

                // copy other
                rows = other->rows;
                cols = other->cols;
                struct Matrixf rhs;
                float32_t      rhs_buf[MATRIXF_MIN_BUF_SIZE(rows, cols)];
                matrixf_init(&rhs, rows, cols, rhs_buf, MATRIXF_MIN_BUF_SIZE(((uint16_t)rows), ((uint16_t)cols)));
                matrixf_set_from_matrixf(&rhs, other);
                matrixf_internal_cross(&lhs, &rhs, out);
            }
            else if (self == out)
            {
                // copy self
                const uint8_t  rows = self->rows;
                const uint8_t  cols = self->cols;
                struct Matrixf lhs;
                float32_t      lhs_buf[MATRIXF_MIN_BUF_SIZE(rows, cols)];
                matrixf_init(&lhs, rows, cols, lhs_buf, MATRIXF_MIN_BUF_SIZE(((uint16_t)rows), ((uint16_t)cols)));
                matrixf_set_from_matrixf(&lhs, self);
                matrixf_internal_cross(&lhs, other, out);
            }
            else
            {
                // copy other
                const uint8_t  rows = other->rows;
                const uint8_t  cols = other->cols;
                struct Matrixf rhs;
                float32_t      rhs_buf[MATRIXF_MIN_BUF_SIZE(rows, cols)];
                matrixf_init(&rhs, rows, cols, rhs_buf, MATRIXF_MIN_BUF_SIZE(((uint16_t)rows), ((uint16_t)cols)));
                matrixf_set_from_matrixf(&rhs, other);
                matrixf_internal_cross(self, &rhs, out);
            }
        }
        else
        {
            matrixf_internal_cross(self, other, out);
        }
    }
    else
    {
        rc = RC_NUMERICS_MATRIX_SIZE_OUT_OF_RANGE;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_trace(const struct Matrixf* self, float32_t* out)
{
    assert(true == matrixf_is_valid(self));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (self->rows != self->cols)
    {
        rc = RC_NUMERICS_MATRIX_NOT_SQUARE;
    }
    else
    {
        *out = 0.0f;
        for (uint8_t i = 0u; i < self->rows; i++)
        {
            *out += self->base[(uint16_t)i * self->pitchx + i];
        }
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline retcode_t m_matrixf_data_serialize(const struct Matrixf* matrix, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;
    for(uint8_t row = 0; row < matrix->rows; ++row)
    {
        for(uint8_t col = 0; col < matrix->cols; ++col)
        {
            serialized_size += serialize_float32(&matrix->base[((uint16_t)row * matrix->pitchx) + col],
                                                 buffer + serialized_size,
                                                 buffer_size - serialized_size);
        }
    }
    return serialized_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline retcode_t m_matrixf_data_deserialize(struct Matrixf* matrix, const uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;
    for(uint8_t row = 0; row < matrix->rows; ++row)
    {
        for(uint8_t col = 0; col < matrix->cols; ++col)
        {
            deserialized_size += deserialize_float32(&matrix->base[((uint16_t)row * matrix->pitchx) + col],
                                                     buffer + deserialized_size,
                                                     buffer_size - deserialized_size);
        }
    }
    return deserialized_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_data_serialize(const struct Matrixf* matrix, uint8_t* buffer, uint32_t buffer_size)
{
    assert(matrixf_is_valid(matrix));
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = (uint32_t)matrix->rows * matrix->cols * sizeof(float32_t);

    if(expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += m_matrixf_data_serialize(matrix, 
                buffer, 
                buffer_size);
        serialized_size += serialize_padding(serialized_size,
                buffer + serialized_size,
                buffer_size - serialized_size);

        assert(serialized_size == expected_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_data_deserialize(struct Matrixf* matrix, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(matrixf_is_valid(matrix));
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = (uint32_t)matrix->rows * matrix->cols * sizeof(float32_t);

    if(expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += m_matrixf_data_deserialize(matrix, buffer, buffer_size);
        deserialized_size += deserialize_padding(deserialized_size, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t matrixf_get_serialized_size(const struct Matrixf* matrix)
{
    assert(matrixf_is_valid(matrix));

    uint32_t size1 = 0, size2 = 0;

    size1 += sizeof(matrixf_get_rows(matrix));
    size1 += sizeof(matrixf_get_cols(matrix));

    size2 += matrixf_get_size(matrix) * sizeof(float32_t);

    return serialization_aligned_size(size1) + serialization_aligned_size(size2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_serialize(const struct Matrixf* matrix, uint8_t* buffer, uint32_t buffer_size)
{
    assert(matrixf_is_valid(matrix));
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = matrixf_get_serialized_size(matrix);

    if(expected_size > buffer_size)
    {
        return RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_uint8(&matrix->rows, 
                buffer, 
                buffer_size);
        serialized_size += serialize_uint8(&matrix->cols, 
                buffer + serialized_size, 
                buffer_size - serialized_size);

        serialized_size += serialize_padding(serialized_size, 
                buffer + serialized_size, 
                buffer_size - serialized_size);

        serialized_size += m_matrixf_data_serialize(matrix, 
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t matrixf_deserialize(struct Matrixf* matrix, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(matrixf_is_valid(matrix));
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = serialization_4byte_aligned_size(sizeof(uint8_t) + sizeof(uint8_t)); // matrix row and col
    uint8_t row = 0;
    uint8_t col = 0;

    if(expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_uint8(&row, 
                buffer, 
                buffer_size);

        deserialized_size += deserialize_uint8(&col, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        deserialized_size += deserialize_padding(deserialized_size, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        if(RC_SUCCESS != matrixf_resize(matrix, row, col))
        {
            rc = RC_DESERIALIZATION_ERROR;
        }
        else
        {
            deserialized_size += matrixf_data_deserialize(matrix, 
                    buffer + deserialized_size, 
                    buffer_size - deserialized_size);

            deserialized_size += deserialize_padding(deserialized_size, 
                    buffer + deserialized_size, 
                    buffer_size - deserialized_size);

            assert(deserialized_size == expected_size + (uint32_t)row * col * sizeof(float32_t));
            rc = (retcode_t)deserialized_size;
        }
    }

    return rc;
}

