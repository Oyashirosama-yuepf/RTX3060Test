/*!
 * @file vector_float32.h
 * @brief This header file defines vector type in holo_c.
 * @author zhangjiannan, duyanwei@holomatic.com
 * @date 2019-08-03
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_NUMERICS_VECTOR_FLOAT32_H_
#define HOLO_C_NUMERICS_VECTOR_FLOAT32_H_

#include <holo_c/numerics/matrix_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @todo add more doxygen comments on return type
 */

/**
 * @brief define float vector type
 */
struct Vectorf
{
    uint8_t    rows;
    uint8_t    cols;
    uint16_t   size;
    uint8_t    pitchx;
    uint8_t    pitchy;
    uint16_t   capacity;
    float32_t* base;
};

#ifdef MATRIX_ALIGN
#define VECTORF_MIN_BUF_SIZE(x) (MATRIXF_ELE_ALIGN_CNT(x) * MATRIXF_ELE_ALIGN_CNT(1u))
#else
#define VECTORF_MIN_BUF_SIZE(x) (x)
#endif

/**
 * @brief initialize a dynamic vector from a buffer
 *
 * @param self vector
 * @param size size
 * @param buffer data buffer
 * @param buffer_size size of the buffer
 * @return retcode_t
 */
retcode_t vectorf_init(struct Vectorf* self, const uint8_t size, float32_t* buffer, const uint16_t buffer_size);

/**
 * @brief resize vector based on present's buf
 *
 *
 * @param self vector
 * @param size
 * @return retcode_t
 *  ok,     if ELE_ALIGN_CNT(new_rows)*ELE_ALIGN_CNT(1) <= self->capacity
 *  other,  if ELE_ALIGN_CNT(new_rows)*ELE_ALIGN_CNT(1) > self->capacity
 */
retcode_t vectorf_resize(struct Vectorf* self, uint8_t size);

/**
 * @brief check the validity of a vector
 *
 * @param self vector
 * @return bool_t
 */
bool_t vectorf_is_valid(const struct Vectorf* self);

/**
 * @brief check if two vectors are equal
 *
 * @param self vector
 * @param other vector
 * @return bool_t
 */
bool_t vectorf_is_equal(const struct Vectorf* self, const struct Vectorf* other);

/**
 * @brief initialize a vector from a raw data array
 *
 * @param self vector
 * @param array raw data array
 * @param array_size array size
 * @return retcode_t
 */
retcode_t vectorf_set_from_array(struct Vectorf* self, const float32_t* array, uint16_t array_size);

/**
 * @brief initialize a vector from another vector
 *
 * @param self vector
 * @param other vector
 * @return retcode_t
 */
retcode_t vectorf_set_from_vectorf(struct Vectorf* self, const struct Vectorf* other);

/**
 * @brief get an element at idx
 *
 * @param self vector
 * @param idx index of element
 * @param out pointer of the element
 * @return retcode_t
 */
retcode_t vectorf_get(const struct Vectorf* self, uint8_t idx, float32_t* out);

/**
 * @brief get an element at idx, without bounds check
 *
 * @param self vector
 * @param idx index of element
 * @param out pointer of the element
 * @return retcode_t
 */
float32_t vectorf_get_unsafe(const struct Vectorf* self, uint8_t idx);

/**
 * @brief set an element at idx
 *
 * @param self vector
 * @param idx index of element
 * @param value pointer of the element
 * @return retcode_t
 */
retcode_t vectorf_set(struct Vectorf* self, uint8_t idx, float32_t value);

/**
 * @brief set an element at idx, without bounds check
 *
 * @param self vector
 * @param idx index of element
 * @param value pointer of the element
 * @return retcode_t
 */
retcode_t vectorf_set_unsafe(struct Vectorf* self, uint8_t idx, float32_t value);

/**
 * @brief set all the elements of vector to some constant value
 *
 * @param self vector
 * @param value constant value
 * @return retcode_t
 */
retcode_t vectorf_set_constant(struct Vectorf* self, float32_t value);

/**
 * @brief set all the elements of vector to 0
 *
 * @param self vector
 * @return retcode_t
 */
retcode_t vectorf_set_zeros(struct Vectorf* self);

/**
 * @brief set all the elemements of vector to 1
 *
 * @param self vector
 * @return retcode_t
 */
retcode_t vectorf_set_ones(struct Vectorf* self);

/**
 * @brief convert a vector to a skew symmetric matrix
 *
 * @param self vector
 * @param out skew matrix
 * @return retcode_t
 */
retcode_t vectorf_to_skew_symmetric(const struct Vectorf* self, struct Matrixf* out);

/**
 * @brief get a sub vector starts from index with a fixed length
 *
 * @param self vector
 * @param index start index of subvector
 * @param size size of the sub vector
 * @param out sub vector
 * @return retcode_t
 */
retcode_t vectorf_get_segment(const struct Vectorf* self, uint8_t index, uint8_t size, struct Vectorf* out);

/**
 * @brief set a sub vector
 *
 * @param self vector
 * @param index start index of subvector
 * @param size size of the sub vector
 * @param in sub vector
 * @return retcode_t
 */
retcode_t vectorf_set_segment(struct Vectorf* self, uint8_t index, uint8_t size, const struct Vectorf* in);

/**
 * @brief get a sub vector starts from the begining
 *
 * @param self vector
 * @param size size of the sub vector
 * @param out sub vector
 * @return retcode_t
 */
retcode_t vectorf_get_head(const struct Vectorf* self, uint8_t size, struct Vectorf* out);

/**
 * @brief set a sub vector from the begining
 *
 * @param self vector
 * @param size size of the sub vector
 * @param in sub vector
 * @return retcode_t
 */
retcode_t vectorf_set_head(struct Vectorf* self, uint8_t size, const struct Vectorf* in);

/**
 * @brief get a sub vector starts from the end
 *
 * @param self vector
 * @param size size of the sub vector
 * @param out sub vector
 * @return retcode_t
 */
retcode_t vectorf_get_tail(const struct Vectorf* self, uint8_t size, struct Vectorf* out);

/**
 * @brief set a sub vector from the end
 *
 * @param self vector
 * @param size size of the sub vector
 * @param in sub vector
 * @return retcode_t
 */
retcode_t vectorf_set_tail(struct Vectorf* self, uint8_t size, const struct Vectorf* in);

/**
 * @brief return the size of matrix
 *
 * @param self matrix
 * @return uint16_t size
 */
uint16_t vectorf_get_size(const struct Vectorf* self);

/**
 * @brief add two vectors
 *
 * @param self vector
 * @param other vector
 * @param out vector
 * @return retcode_t
 */
retcode_t vectorf_add(const struct Vectorf* self, const struct Vectorf* other, struct Vectorf* out);

/**
 * @brief subtract two vetors
 *
 * @param self vector
 * @param other vector
 * @param out vector
 * @return retcode_t
 */
retcode_t vectorf_sub(const struct Vectorf* self, const struct Vectorf* other, struct Vectorf* out);

/**
 * @brief negate a vector
 *
 * @param self vector
 * @return retcode_t
 */
retcode_t vectorf_negate(struct Vectorf* self);

/**
 * @brief multiply a vector with a scalar
 *
 * @param self vector
 * @param scalar scalar value
 * @param out vector
 * @return retcode_t
 */
retcode_t vectorf_multiply_float32(const struct Vectorf* self, float32_t scalar, struct Vectorf* out);

/**
 * @brief multiply a matrix (1xn)
 *
 * @details out = self * other
 * @param self vector (mx1)
 * @param other matrix (1xn)
 * @param out matrix (mxn)
 * @return retcode_t
 */
retcode_t vectorf_multiply_matrixf(const struct Vectorf* self, const struct Matrixf* other, struct Matrixf* out);

/**
 * @brief multiply by a matrix (mxn)
 *
 * @details out = other x self
 * @param other matrix (mxn)
 * @param self vector (nx1)
 * @param out vector (mx1)
 * @return retcode_t
 */
retcode_t vectorf_multiply_by_matrixf(const struct Vectorf* self, const struct Matrixf* other, struct Vectorf* out);

/**
 * @brief transpose a vector
 *
 * @param self vector  (nx1)
 * @param out matrix (1xn)
 * @return retcode_t
 */
retcode_t vectorf_transpose(const struct Vectorf* self, struct Matrixf* out);

/**
 * @brief dot product
 *
 * @param self vector
 * @param other vector
 * @param out pointer of dot value
 * @return retcode_t
 */
retcode_t vectorf_dot(const struct Vectorf* self, const struct Vectorf* other, float32_t* out);

/**
 * @brief cross product of two vectors
 *
 * @param self vector
 * @param other vector
 * @param out vector
 * @return retcode_t
 */
retcode_t vectorf_cross(const struct Vectorf* self, const struct Vectorf* other, struct Vectorf* out);

/**
 * @brief take the squared l2-norm of a vector
 *
 * @param self vector
 * @return squared norm
 */
float32_t vectorf_get_norm_sqr(const struct Vectorf* self);

/**
 * @brief take the l2-norm of a vector
 *
 * @param self vector
 * @return norm
 */
float32_t vectorf_get_norm(const struct Vectorf* self);

/**
 * @brief normalize a vector
 *
 * @param self vector
 * @return retcode_t
 */
retcode_t vectorf_normalize(struct Vectorf* self);

/**
 * @{
 * Begin serialization/deserialization API group
 */

/**
 * @brief Serialize vector data field. 
 *
 * @param self The vector object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes serialized into buffer
 */
static inline 
retcode_t vectorf_data_serialize(const struct Vectorf* self, uint8_t* buffer, uint32_t buffer_size)
{
    return matrixf_data_serialize((const struct Matrixf*)self, buffer, buffer_size);
}

/**
 * @brief Deserialize vector data field. 
 *
 * @param self The vector object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes deserialized from buffer
 */
static inline 
retcode_t vectorf_data_deserialize(struct Vectorf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    return matrixf_data_deserialize((struct Matrixf*)self, buffer, buffer_size);
}

/**
 * @brief Get serialized buffer size for vectorf. 
 *
 * @param self The vector object.
 *
 * @return Serialized size
 */
static inline 
uint32_t vectorf_get_serialized_size(const struct Vectorf* self)
{
    return matrixf_get_serialized_size((const struct Matrixf*)self);
}

/**
 * @brief Serialize vector. 
 *
 * @param self The vector object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes serialized into buffer
 */
static inline 
retcode_t vectorf_serialize(const struct Vectorf* self, uint8_t* buffer, uint32_t buffer_size)
{
    return matrixf_serialize((const struct Matrixf*)self, buffer, buffer_size);
}

/**
 * @brief Deserialize vector. 
 *
 * @param self The vector object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed. 
 * @return Positive integer Number of bytes deserialized from buffer
 */
static inline 
retcode_t vectorf_deserialize(struct Vectorf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    return matrixf_deserialize((struct Matrixf*)self, buffer, buffer_size);
}


#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_NUMERICS_VECTOR_FLOAT32_H_
