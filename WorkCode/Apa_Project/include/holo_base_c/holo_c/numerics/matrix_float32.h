/*!
 * @file matrix_float32.h
 * @brief This header file defines matrix type in holo_c.
 * @author huangqi, duyanwei@holomatic.com
 * @date 2019-08-03
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_NUMERICS_MATRIX_FLOAT32_H_
#define HOLO_C_NUMERICS_MATRIX_FLOAT32_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/core/config.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @todo add more doxygen comments on return type
 */

/**
 * @brief define common float32_t matrix struct
 *
 */
struct Matrixf
{
    uint8_t    rows;      ///< row dimension of matrix
    uint8_t    cols;      ///< col dimension of matrix
    uint16_t   size;      ///< size (row x col) of matrix
    uint8_t    pitchx;    ///< real aligned element count each row
    uint8_t    pitchy;    ///< real aligned element count each col
    uint16_t   capacity;  ///< size of allocated memory
    float32_t* base;      ///< pointer of allocated memory
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief handy matrix memory allocation
 *
 */

#ifdef MATRIX_ALIGN
#define MATRIXF_ELE_ALIGN_CNT(x) (((x) + 3u) & 0xFCu)
#else
#define MATRIXF_ELE_ALIGN_CNT(x) (x)
#endif

#ifdef MATRIX_ALIGN
#define MATRIXF_MIN_BUF_SIZE(row, col) (MATRIXF_ELE_ALIGN_CNT(row) * MATRIXF_ELE_ALIGN_CNT(col))
#else
#define MATRIXF_MIN_BUF_SIZE(row, col) ((row) * (col))
#endif

/**
 * @brief initialize a dynamic matrix from a buffer
 *
 * @param self matrix
 * @param rows rows
 * @param cols cols
 * @param buffer data buffer
 * @param buffer_size size of the buffer
 * @return retcode_t
 */
retcode_t matrixf_init(struct Matrixf* self, uint8_t rows, uint8_t cols, float32_t* buffer, uint16_t buffer_size);

/**
 * @brief resize matrix based on present's buf
 *
 *
 * @param self matrix
 * @param rows rows
 * @param cols cols
 * @return retcode_t
 *  ok,     if ELE_ALIGN_CNT(new_rows)*ELE_ALIGN_CNT(new_rows) <= self->capacity
 *  other,  if ELE_ALIGN_CNT(new_rows)*ELE_ALIGN_CNT(new_rows) > self->capacity
 */
retcode_t matrixf_resize(struct Matrixf* self, uint8_t rows, uint8_t cols);

/**
 * @brief check matrix validity
 *
 * @param self matrix
 * @return bool_t
 */
bool_t matrixf_is_valid(const struct Matrixf* self);

/**
 * @brief check if two matrices are equal
 *
 * @param self matrix
 * @param other matrix
 * @return bool_t
 */
bool_t matrixf_is_equal(const struct Matrixf* self, const struct Matrixf* other);

/**
 * @brief set data of a matrix from raw data array
 *
 * @param self matrix
 * @param array raw data array
 * @param array_size data size
 * @return retcode_t
 */
retcode_t matrixf_set_from_array(struct Matrixf* self, const float32_t* array, uint16_t array_size);

/**
 * @brief set data of a matrix from raw data array, without bounds check
 *
 * @param self matrix
 * @param array raw data array
 * @param array_size data size
 * @return retcode_t
 */
retcode_t matrixf_set_from_array_unsafe(struct Matrixf* self, const float32_t* array, uint16_t array_size);

/**
 * @brief set data of a matrix from the other matrix
 *
 * @param self matrix
 * @param other matrix
 * @return retcode_t
 */
retcode_t matrixf_set_from_matrixf(struct Matrixf* self, const struct Matrixf* other);

/**
 * @brief set data of a matrix from the other matrix, without bounds check
 *
 * @param self matrix
 * @param other matrix
 * @return retcode_t
 */
retcode_t matrixf_set_from_matrixf_unsafe(struct Matrixf* self, const struct Matrixf* other);

/**
 * @brief get a matrix element at (row, col)
 *
 * @details *out = self(row, col)
 * @param self matrix
 * @param row element row
 * @param col element column
 * @param out pointer of element
 * @return retcode_t
 */
retcode_t matrixf_get(const struct Matrixf* self, uint8_t row, uint8_t col, float32_t* out);

/**
 * @brief get a matrix element at (row, col), without bounds check
 *
 * @details *out = self(row, col)
 * @param self matrix
 * @param row element row
 * @param col element column
 * @param out pointer of element
 * @return float32_t
 */
float32_t matrixf_get_unsafe(const struct Matrixf* self, uint8_t row, uint8_t col);

/**
 * @brief set a matrix element at (row, col)
 *
 * @details self(row, col) = value
 * @param self matrix
 * @param row element row
 * @param col element column
 * @param value element at (row, col)
 * @return retcode_t
 */
retcode_t matrixf_set(struct Matrixf* self, uint8_t row, uint8_t col, float32_t value);

/**
 * @brief set a matrix element at (row, col), without bounds check
 *
 * @details self(row, col) = value
 * @param self matrix
 * @param row element row
 * @param col element column
 * @param value element at (row, col)
 * @return retcode_t
 */
retcode_t matrixf_set_unsafe(struct Matrixf* self, uint8_t row, uint8_t col, float32_t value);

/**
 * @brief initialize all the elements of matrix to some constant value
 *
 * @param self matrix
 * @param value constant value
 * @return retcode_t
 */
retcode_t matrixf_set_constant(struct Matrixf* self, float32_t value);

/**
 * @brief initialize all the elements of matrix to "0"s
 *
 * @param self matrix
 * @return retcode_t
 */
retcode_t matrixf_set_zeros(struct Matrixf* self);

/**
 * @brief initialize all the elements of matrix to "1"s
 *
 * @param self matrix
 * @return retcode_t
 */
retcode_t matrixf_set_ones(struct Matrixf* self);

/**
 * @brief initialize an Identity matrix
 *
 * @param self matrix
 * @return retcode_t
 */
retcode_t matrixf_set_identity(struct Matrixf* self);

/**
 * @brief get sub-matrix from a specified position
 *
 * @param self matrix
 * @param i start row index
 * @param j start col index
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param out sub matrix
 * @return retcode_t
 */
retcode_t matrixf_get_block(const struct Matrixf* self, uint8_t i, uint8_t j, uint8_t rows, uint8_t cols,
                            struct Matrixf* out);

/**
 * @brief set sub-matrix from a specified position
 *
 * @param self matrix
 * @param i start row index
 * @param j start col index
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param in sub matrix
 * @return retcode_t
 */
retcode_t matrixf_set_block(struct Matrixf* self, uint8_t i, uint8_t j, uint8_t rows, uint8_t cols,
                            const struct Matrixf* in);

/**
 * @brief get sub-matrix from top left corner
 *
 * @param self matrix
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param out sub matrix
 * @return retcode_t
 */
retcode_t matrixf_get_top_left_corner(const struct Matrixf* self, uint8_t rows, uint8_t cols, struct Matrixf* out);
/**
 * @brief set sub-matrix from top left corner
 *
 * @param self matrix
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param in sub matrix
 * @return retcode_t
 */

retcode_t matrixf_set_top_left_corner(struct Matrixf* self, uint8_t rows, uint8_t cols, const struct Matrixf* in);
/**
 * @brief get sub-matrix from top right corner
 *
 * @param self matrix
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param out sub matrix
 * @return retcode_t
 */
retcode_t matrixf_get_top_right_corner(const struct Matrixf* self, uint8_t rows, uint8_t cols, struct Matrixf* out);
/**
 * @brief set sub-matrix from top right corner
 *
 * @param self matrix
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param in sub matrix
 * @return retcode_t
 */
retcode_t matrixf_set_top_right_corner(struct Matrixf* self, uint8_t rows, uint8_t cols, const struct Matrixf* in);
/**
 * @brief get sub-matrix from bottom left corner
 *
 * @param self matrix
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param out sub matrix
 * @return retcode_t
 */
retcode_t matrixf_get_bottom_left_corner(const struct Matrixf* self, uint8_t rows, uint8_t cols, struct Matrixf* out);
/**
 * @brief set sub-matrix from bottom left corner
 *
 * @param self matrix
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param in sub matrix
 * @return retcode_t
 */
retcode_t matrixf_set_bottom_left_corner(struct Matrixf* self, uint8_t rows, uint8_t cols, const struct Matrixf* in);

/**
 * @brief get sub-matrix from bottom right corner
 *
 * @param self matrix
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param out sub matrix
 * @return retcode_t
 */
retcode_t matrixf_get_bottom_right_corner(const struct Matrixf* self, uint8_t rows, uint8_t cols, struct Matrixf* out);
/**
 * @brief set sub-matrix from bottom right corner
 *
 * @param self matrix
 * @param rows rows of sub matrix
 * @param cols cols of sub matrix
 * @param in sub matrix
 * @return retcode_t
 */
retcode_t matrixf_set_bottom_right_corner(struct Matrixf* self, uint8_t rows, uint8_t cols, const struct Matrixf* in);

/**
 * @brief get a specified row of a matrix
 *
 * @param self matrix
 * @param index row
 * @param out specified row matrix
 * @return retcode_t
 */
retcode_t matrixf_get_row(const struct Matrixf* self, uint8_t index, struct Matrixf* out);

/**
 * @brief get a specified column of a matrix
 *
 * @param self matrix
 * @param index column
 * @param out specified column matrix
 */
retcode_t matrixf_get_col(const struct Matrixf* self, uint8_t index, struct Matrixf* out);

/**
 * @brief return the rows of matrix
 *
 * @param self matrix
 * @return uint8_t rows
 */
uint8_t matrixf_get_rows(const struct Matrixf* self);

/**
 * @brief return the cols of matrix
 *
 * @param self matrix
 * @return uint8_t cols
 */
uint8_t matrixf_get_cols(const struct Matrixf* self);

/**
 * @brief return the size of matrix
 *
 * @param self matrix
 * @return uint16_t size
 */
uint16_t matrixf_get_size(const struct Matrixf* self);

/**
 * @brief add two matrices
 *
 * @details out = self + other
 * @param self matrix
 * @param other matrix
 * @param out matrix
 * @return retcode_t
 */
retcode_t matrixf_add(const struct Matrixf* self, const struct Matrixf* other, struct Matrixf* out);

/**
 * @brief subtract two matrices
 *
 * @details out = self - other
 * @param self matrix
 * @param other matrix
 * @param out matrix
 * @return retcode_t
 */
retcode_t matrixf_sub(const struct Matrixf* self, const struct Matrixf* other, struct Matrixf* out);

/**
 * @brief negate matrix
 *
 * @details self = -self;
 * @param out matrix
 * @return retcode_t
 */
retcode_t matrixf_negate(struct Matrixf* self);

/**
 * @brief multiply a matrix with a scalar
 *
 * @details out = scalar * self
 * @param self matrix
 * @param scalar scalar value
 * @param out matrix
 * @return retcode_t
 */
retcode_t matrixf_multiply_float32(const struct Matrixf* self, float32_t scalar, struct Matrixf* out);

/**
 * @brief multiply two matrices
 *
 * @details out = self * other
 * @param self matrix
 * @param other matrix
 * @param out matrix
 * @return retcode_t
 */
retcode_t matrixf_multiply(const struct Matrixf* self, const struct Matrixf* other, struct Matrixf* out);

/**
 * @brief transpose a matrix
 *
 * @param self matrix
 * @param out the transpose of matrix
 * @return retcode_t
 */
retcode_t matrixf_transpose(const struct Matrixf* self, struct Matrixf* out);

/**
 * @brief take the square of F-norm of a matrix or l2-norm of a vector
 *
 * @param self matrix
 * @return squared norm
 */
float32_t matrixf_get_norm_sqr(const struct Matrixf* self);

/**
 * @brief take the F-norm of a matrix or l2-norm of a vector
 *
 * @param self matrix
 * @return norm
 */
float32_t matrixf_get_norm(const struct Matrixf* self);

/**
 * @brief take the inverse of matrix
 *
 * @param self matrix
 * @param out the inverse of matrix
 * @return retcode_t
 */
retcode_t matrixf_inverse(const struct Matrixf* self, struct Matrixf* out);

/**
 * @brief take the determinant of matrix
 *
 * @param self matrix
 * @param out pointer of matrix determinant
 * @return retcode_t
 */
retcode_t matrixf_determinant(const struct Matrixf* self, float32_t* out);

/**
 * @brief dot product, only supports mx1 matrix
 *
 * @param self matrix
 * @param other matrix
 * @param out pointer of dot product of two matrices
 * @return retcode_t
 */
retcode_t matrixf_dot(const struct Matrixf* self, const struct Matrixf* other, float32_t* out);

/**
 * @brief cross product, only supports 3x1 matrix
 *
 * @param self matrix 3x1
 * @param other matrix 3x1
 * @param out matrix 3x1
 * @return retcode_t
 */
retcode_t matrixf_cross(const struct Matrixf* self, const struct Matrixf* other, struct Matrixf* out);

/**
 * @brief get the trace of a square matrix
 *
 * @param self matrix
 * @param out pointer of trace of matrix
 * @return retcode_t
 */
retcode_t matrixf_trace(const struct Matrixf* self, float32_t* out);

/**
 * @{
 * Begin serialization/deserialization API group
 */

/**
 * @brief Serialize matrix data field. 
 *
 * @param matrix The matrix object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes serialized into buffer
 */
retcode_t matrixf_data_serialize(const struct Matrixf* matrix, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize matrix data field. 
 *
 * @param matrix The matrix object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes deserialized from buffer
 */
retcode_t matrixf_data_deserialize(struct Matrixf* matrix, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Get serialized buffer size for matrixf. 
 *
 * @param matrix The matrix object.
 *
 * @return Serialized size
 */
uint32_t matrixf_get_serialized_size(const struct Matrixf* matrix);

/**
 * @brief Serialize matrix.
 *
 * @param matrix The matrix object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes serialized into buffer
 */
retcode_t matrixf_serialize(const struct Matrixf* matrix, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize matrix object. 
 *
 * @param matrix The matrix object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes deserialized from buffer
 */
retcode_t matrixf_deserialize(struct Matrixf* matrix, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @}
 * End serialization/deserialization API group.
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_NUMERICS_MATRIX_FLOAT32_H_
