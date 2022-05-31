/**
 * @file serialization.h
 * @brief This header file defines utility functions for serialization and deserialization.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-11-1
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_UTILS_SERIALIZATION_H_
#define HOLO_C_UTILS_SERIALIZATION_H_

#include <holo_c/core/types.h>
#include <holo_c/core/retcode.h>
#include <holo_c/port/endian.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HOLO_CONFIG_SERIALIZATION_ALIGNMENT
#define HOLO_CONFIG_SERIALIZATION_ALIGNMENT 4
#endif

static inline uint32_t serialization_4byte_aligned_size(uint32_t size)
{
    return (size + 3) & 0xfffffffc;
}

static inline uint32_t serialization_8byte_aligned_size(uint32_t size)
{
    return (size + 7) & 0xfffffff8;
}

static inline uint32_t serialization_aligned_size(uint32_t size)
{
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return serialization_4byte_aligned_size(size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return serialization_8byte_aligned_size(size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

/**
 * @brief serialize int8_t type object to buffer.
 *
 * @param obj The int8_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_int8(const int8_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize uint8_t type object to buffer.
 *
 * @param obj The uint8_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_uint8(const uint8_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize int16_t type object to buffer.
 *
 * @param obj The int16_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_int16(const int16_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize uint16_t type object to buffer.
 *
 * @param obj The uint16_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_uint16(const uint16_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize int32_t type object to buffer.
 *
 * @param obj The int32_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_int32(const int32_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize uint32_t type object to buffer.
 *
 * @param obj The uint32_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_uint32(const uint32_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Serialize int64_t type object to buffer 4byte aligned.
 * @detail This function will first split a 8 byte int64_t type object into high 4 byte data and low 4 byte data.
 * The high 4 byte data will serialize into buffer first then the low 4 byte data. 
 * buffer must be a 4 byte aligned address
 *
 * 0x123456789abcdef0 -> 0x78563412f0debc9a
 *
 * @param obj The int64_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_int64_4byte_aligned(const int64_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize int64_t type object to buffer 8byte aligned.
 * @detail This function will serialize 8 byte data directly. 
 * buffer must be a 8 byte aligned address.
 *
 * 0x123456789abcdef0 -> 0xf0debc9a78563412
 *
 * @param obj The int64_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_int64_8byte_aligned(const int64_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize int64_t type object to buffer. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param obj The int64_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
static inline retcode_t serialize_int64(const int64_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return serialize_int64_4byte_aligned(obj, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return serialize_int64_8byte_aligned(obj, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

/**
 * @brief serialize uint64_t type object to buffer 4byte aligned.
 * @detail This function will first split a 8 byte uint64_t type object into high 4 byte data and low 4 byte data.
 * The high 4 byte data will serialize into buffer first then the low 4 byte data. 
 * buffer must be a 4 byte aligned address
 *
 * 0x123456789abcdef0 -> 0x78563412f0debc9a
 *
 * @param obj The uint64_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_uint64_4byte_aligned(const uint64_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize uint64_t type object to buffer 8byte aligned.
 * @detail This function will serialize 8 byte data directly. 
 * buffer must be a 8 byte aligned address.
 *
 * 0x123456789abcdef0 -> 0xf0debc9a78563412
 *
 * @param obj The uint64_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_uint64_8byte_aligned(const uint64_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize uint64_t type object to buffer. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param obj The uint64_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
static inline retcode_t serialize_uint64(const uint64_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return serialize_uint64_4byte_aligned(obj, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return serialize_uint64_8byte_aligned(obj, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}


/**
 * @brief serialize float32_t type object to buffer.
 *
 * @param obj The float32_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_float32(const float32_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize float64_t type object to buffer.
 * @detail This function will first split a 8 byte float64_t type object into high 4 byte data and low 4 byte data.
 * The high 4 byte data will serialize into buffer first then the low 4 byte data. 
 * buffer must be a 4 byte aligned address
 *
 * 0x123456789abcdef0 -> 0x78563412f0debc9a
 *
 * @param obj The float64_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_float64_4byte_aligned(const float64_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize float64_t type object to buffer.
 * @detail This function will serialize 8 byte data directly. 
 * buffer must be a 8 byte aligned address.
 *
 * 0x123456789abcdef0 -> 0xf0debc9a78563412
 *
 * @param obj The float64_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_float64_8byte_aligned(const float64_t* obj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief serialize float64_t type object to buffer. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param obj The float64_t type object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
static inline retcode_t serialize_float64(const float64_t* obj, uint8_t* buffer, uint32_t buffer_size)
{
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return serialize_float64_4byte_aligned(obj, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return serialize_float64_8byte_aligned(obj, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

/**
 * @brief Fill buffer with several padding bytes(0x00) to make the buffer 4 byte aligned.
 *
 * @param serialized_size Number of bytes in buffer.
 * @param buffer The buffer.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_padding_4byte_aligned(uint32_t serialized_size, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Fill buffer with several padding bytes(0x00) to make the buffer 8 byte aligned.
 *
 * @param serialized_size Number of bytes in buffer.
 * @param buffer The buffer.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
retcode_t serialize_padding_8byte_aligned(uint32_t serialized_size, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Fill buffer with several padding bytes(0x00) to make the buffer aligned. 
 * Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param serialized_size Number of bytes in buffer.
 * @param buffer The buffer.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes serialized into buffer.
 */
static inline retcode_t serialize_padding(uint32_t serialized_size, uint8_t* buffer, uint32_t buffer_size)
{
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return serialize_padding_4byte_aligned(serialized_size, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return serialize_padding_8byte_aligned(serialized_size, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

/**
 * @brief Deserialize int8_t type object from buffer.
 *
 * @param obj The int8_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_int8(int8_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize uint8_t type object from buffer.
 *
 * @param obj The uint8_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_uint8(uint8_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize int16_t type object from buffer.
 *
 * @param obj The int16_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_int16(int16_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize uint16_t type object from buffer.
 *
 * @param obj The uint16_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_uint16(uint16_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize int32_t type object from buffer.
 *
 * @param obj The int32_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_int32(int32_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize uint32_t type object from buffer.
 *
 * @param obj The uint32_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_uint32(uint32_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize int64_t type object from buffer 4 byte aligned.
 *
 * @param obj The int64_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_int64_4byte_aligned(int64_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize int64_t type object from buffer 8 byte aligned.
 *
 * @param obj The int64_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_int64_8byte_aligned(int64_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize int64_t type object from buffer. Alignment is based on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param obj The int64_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
static inline retcode_t deserialize_int64(int64_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return deserialize_int64_4byte_aligned(obj, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return deserialize_int64_8byte_aligned(obj, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

/**
 * @brief Deserialize uint64_t type object from buffer 4 byte aligned.
 *
 * @param obj The uint64_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_uint64_4byte_aligned(uint64_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize uint64_t type object from buffer 8 byte aligned.
 *
 * @param obj The uint64_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_uint64_8byte_aligned(uint64_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize uint64_t type object from buffer. Alignment is based on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param obj The uint64_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
static inline retcode_t deserialize_uint64(uint64_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return deserialize_uint64_4byte_aligned(obj, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return deserialize_uint64_8byte_aligned(obj, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

/**
 * @brief Deserialize float32_t type object from buffer.
 *
 * @param obj The float32_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_float32(float32_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize float64_t type object from buffer 4 byte aligned.
 *
 * @param obj The float64_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_float64_4byte_aligned(float64_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize float64_t type object from buffer 8 byte aligned.
 *
 * @param obj The float64_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
retcode_t deserialize_float64_8byte_aligned(float64_t* obj, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize float64_t type object from buffer. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param obj The float64_t type object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes deserialized from buffer.
 */
static inline retcode_t deserialize_float64(float64_t* obj, const uint8_t* buffer, uint32_t buffer_size)
{
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return deserialize_float64_4byte_aligned(obj, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return deserialize_float64_8byte_aligned(obj, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

/**
 * @brief Skip 4 byte aligned buffer padding bytes.
 *
 * @param deserialized_size Number of bytes deserialized.
 * @param buffer The deserialization buffer.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes skipped.
 */
retcode_t deserialize_padding_4byte_aligned(uint32_t serialized_size, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Skip 8 byte aligned buffer padding bytes.
 *
 * @param deserialized_size Number of bytes deserialized.
 * @param buffer The deserialization buffer.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes skipped.
 */
retcode_t deserialize_padding_8byte_aligned(uint32_t deserialized_size, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Skip aligned buffer padding bytes. Alignment is based on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param deserialized_size Number of bytes deserialized.
 * @param buffer The deserialization buffer.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive number Number of bytes skipped.
 */
static inline retcode_t deserialize_padding(uint32_t deserialized_size, const uint8_t* buffer, uint32_t buffer_size)
{
#if HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 4
    return deserialize_padding_4byte_aligned(deserialized_size, buffer, buffer_size);
#elif HOLO_CONFIG_SERIALIZATION_ALIGNMENT == 8
    return deserialize_padding_8byte_aligned(deserialized_size, buffer, buffer_size);
#else
#error "Alignment not supported. Please check HOLO_CONFIG_SERIALIZATION_ALIGNEMNT macro!"
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_UTILS_SERIALIZATION_H_ */
