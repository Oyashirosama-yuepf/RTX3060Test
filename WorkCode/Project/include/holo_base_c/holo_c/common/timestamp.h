/*!
 * @file timestamp.h
 * @brief This header file defines TimeStamp and Duration Object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-8-12
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_COMMON_TIMESTAMP_H_
#define HOLO_C_COMMON_TIMESTAMP_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup common
 * @{
 *
 */

/*
 * @brief struct Duration represents a period of time.
 *
 */
struct Duration
{
    int32_t sec;
    int32_t nsec;
};
HOLO_STATIC_ASSERT(sizeof(struct Duration) == 8);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief The default constructor. Set duration to default value.
 *
 * @param duration The duration object.
 *
 * @return RC_SUCCESS
 */
retcode_t duration_init(struct Duration* duration);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Initialize duration from second and nanosecond parameter.
 *
 * @param duration The duration object.
 * @param sec Second.
 * @param nsec Nano second.
 *
 * @return RC_DURATION_OVERFLOW if duration > max duration.
 * @return RC_DURATION_UNDERFLOW if duration < min duration.
 * @return RC_SUCCESS
 */
retcode_t duration_init_from_sec_nsec(struct Duration* duration, int32_t sec, int32_t nsec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Initialize duration from float64 type second.
 *
 * @param duration The duration object.
 * @param sec Second.
 *
 * @return RC_DURATION_OVERFLOW if second > max duration.
 * @return RC_DURATION_UNDERFLOW if second < min duration.
 * @return RC_SUCCESS
 *
 * @warning float64 type has only 15 significant decimal digit. This conversion may cause precision loss.
 */
retcode_t duration_init_from_sec(struct Duration* duration, float64_t sec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Initialize duration from nano second.
 *
 * @param duration The duration object.
 * @param nsec Nano second.
 *
 * @return RC_DURATION_OVERFLOW if duration > max duration.
 * @return RC_DURATION_UNDERFLOW if duration < min duration.
 * @return RC_SUCCESS
 */
retcode_t duration_init_from_nsec(struct Duration* duration, int64_t nsec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Initialize duration from other duration structure.
 *
 * @param duration The duration object to initialize.
 * @param other The other duration object.
 *
 * @return RC_SUCCESS
 */
retcode_t duration_init_from_duration(struct Duration* duration, const struct Duration* other);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Add two durations. out = lhs + rhs.
 *
 * @param lhs Left hand side duration object.
 * @param rhs Right hand side duration object.
 * @param out Output duration object.
 *
 * @return RC_DURATION_OVERFLOW if out > max duration.
 * @return RC_DURATION_UNDERFLOW if out < min duration.
 * @return RC_SUCCESS
 */
retcode_t duration_add(const struct Duration* lhs, const struct Duration* rhs, struct Duration* out);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Substract two durations. out = lhs - rhs.
 *
 * @param lhs Left hand side duration object.
 * @param rhs Right hand side duration object.
 * @param out Output duration object.
 *
 * @return RC_DURATION_OVERFLOW if out > max duration.
 * @return RC_DURATION_UNDERFLOW if out < min duration.
 * @return RC_SUCCESS
 */
retcode_t duration_sub(const struct Duration* lhs, const struct Duration* rhs, struct Duration* out);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Multiply duration by a integer. out = lhs * rhs.
 *
 * @param lhs Left hand side duration object.
 * @param rhs Right hand side muliply factor.
 * @param out Output duration object.
 *
 * @return RC_DURATION_OVERFLOW if output > max duration.
 * @return RC_DURATION_UNDERFLOW if output < min duration.
 * @return RC_SUCCESS
 */
retcode_t duration_multiply_int32(const struct Duration* lhs, int32_t rhs, struct Duration* out);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Divide duration by a integer. out = lhs / rhs
 *
 * @param lhs Left hand side duration object.
 * @param rhs Right hand size divider.
 * @param out Output duration object.
 *
 * @return RC_DURATION_INVALID_PARAMETER if rhs == 0;
 * @return RC_SUCCESS
 */

retcode_t duration_divide_int32(const struct Duration* lhs, int32_t rhs, struct Duration* out);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Multiply duration by a float64. out = lhs * rhs.
 *
 * @param lhs Left hand size duration object.
 * @param rhs Right hand size float64 type scale factor.
 * @param out Ouput duration object.
 *
 * @return RC_DURATION_OVERFLOW if output > max duration.
 * @return RC_DURATION_UNDERFLOW if output < min duration.
 * @return RC_SUCCESS
 */
retcode_t duration_multiply_float64(const struct Duration* lhs, float64_t rhs, struct Duration* out);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if duration is zero
 *
 * @param duration The duration object
 *
 * @return true
 * @return false
 */
static inline bool_t duration_is_zero(const struct Duration* duration)
{
    return (duration->sec) == 0 && (duration->nsec == 0);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs > rhs.
 *
 * @param lhs Left hand side duration object.
 * @param rhs Right hand side duration object.
 *
 * @return true
 * @return false
 */
bool_t duration_is_greater(const struct Duration* lhs, const struct Duration* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs == rhs.
 *
 * @param lhs Left hand side duration object.
 * @param rhs Right hand side duration object.
 *
 * @return true
 * @return false
 */
bool_t duration_is_equal(const struct Duration* lhs, const struct Duration* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs < rhs.
 *
 * @param lhs Left hand side duration object.
 * @param rhs Right hand side duration object.
 *
 * @return true
 * @return false
 */
bool_t duration_is_less(const struct Duration* lhs, const struct Duration* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs >= rhs.
 *
 * @param lhs Left hand side duration object.
 * @param rhs Right hand side duration object.
 *
 * @return true
 * @return false
 */
bool_t duration_is_greater_equal(const struct Duration* lhs, const struct Duration* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs <= rhs.
 *
 * @param lhs Left hand side duration object.
 * @param rhs Right hand side duration object.
 *
 * @return true
 * @return false
 */
bool_t duration_is_less_equal(const struct Duration* lhs, const struct Duration* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Convert duration to float64 type second.
 *
 * @param duration The duration object.
 * @param sec Output float64 type second.
 *
 * @return RC_SUCCESS.
 *
 * @warning float64 type has only 15 significant decimal digit. This conversion may cause precision loss.
 */
retcode_t duration_to_sec(const struct Duration* duration, float64_t* sec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Convert duration to nano second.
 *
 * @param duration The duration object.
 * @param nsec Output int64 type nano second.
 *
 * @return RC_SUCCESS
 */
retcode_t duration_to_nsec(const struct Duration* duration, int64_t* nsec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get second field of duration object.
 *
 * @param duration The duration object.
 *
 * @return second.
 */
int32_t duration_get_sec(const struct Duration* duration);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get nano second field of duration object.
 *
 * @param duration The duration object.
 *
 * @return nano second.
 */
int32_t duration_get_nsec(const struct Duration* duration);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get second field of duration object.
 *
 * @param duration The duration object.
 * @param sec Second.
 *
 * @return RC_SUCCESS
 */
retcode_t duration_set_sec(struct Duration* duration, int32_t sec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Set nano second field of duration object.
 *
 * @param duration The duration object.
 * @param nsec Nano second. Valid input range is [0, 999999999]
 *
 * @return RC_DURATION_INVALID_PARAMETER Invlid input parameter.
 * @return RC_SUCCESS
 */
retcode_t duration_set_nsec(struct Duration* duration, int32_t nsec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get serialized size of duration object.
 *
 * @param duration The duration object.
 *
 * @return Serialized size.
 */
uint32_t duration_get_serialized_size(const struct Duration* duration);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Serialize duration object to buffer.
 *
 * @param duration The duration object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return Positive integer Number of bytes serialized into buffer.
 */
retcode_t duration_serialize(const struct Duration* duration, uint8_t* buffer, uint32_t buffer_size);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Deserialize duration object from buffer.
 *
 * @param duration The duration object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is less than needed.
 * @return RC_DESERIALIZATION_FAIL Failed to deserialize from buffer due to internal error.
 * @return Positive integer Number of bytes deserialized from buffer.
 */
retcode_t duration_deserialize(struct Duration* duration, const uint8_t* buffer, uint32_t buffer_size);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Struct Timestamp represents a time point.
 */
struct Timestamp
{
    uint32_t sec;
    uint32_t nsec;
};
HOLO_STATIC_ASSERT(sizeof(struct Timestamp) == 8);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief The default constructor. Set timestamp to default value(sec = 0, nsec=0).
 *
 * @param timestamp The timestamp object.
 *
 * @return RC_SUCCESS.
 */
retcode_t timestamp_init(struct Timestamp* timestamp);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Initialize timestamp from second and nano second.
 *
 * @param timestamp Timestamp object to initialize.
 * @param sec Second.
 * @param nsec Nano second.
 *
 * @return RC_TIMESTAMP_OVERFLOW if nomalized timestamp > max timestamp.
 * @return RC_SUCCESS
 */
retcode_t timestamp_init_from_sec_nsec(struct Timestamp* timestamp, uint32_t sec, uint32_t nsec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Initialize timestamp from float64 type second.
 *
 * @param timestamp Timestamp object to initialize.
 * @param sec Second.
 *
 * @return RC_TIMESTAMP_OVERFLOW if sec > max timestamp.
 * @return RC_TIMESTAMP_UNDERFLOW if sec < 0.
 * @return RC_SUCCESS
 *
 * @warning float64 type has only 15 significant decimal digit. This conversion may cause precision loss.
 */
retcode_t timestamp_init_from_sec(struct Timestamp* timestamp, float64_t sec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Initialize timestamp from nano second.
 *
 * @param timestamp Timestamp object to initialize.
 * @param nsec Nano second.
 *
 * @return RC_SUCCESS
 */
retcode_t timestamp_init_from_nsec(struct Timestamp* timestamp, int64_t nsec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Initialize timestamp from another timestamp object.
 *
 * @param timestamp Timestamp object to initialize.
 * @param other The other timestamp object.
 *
 * @return RC_SUCCESS
 */
retcode_t timestamp_init_from_timestamp(struct Timestamp* timestamp, const struct Timestamp* other);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Timestamp add duration.
 *
 * @param lhs Left hand side timestamp object.
 * @param rhs Right hand side duration object.
 * @param out Output timestamp object.
 *
 * @return RC_TIMESTAMP_OVERFLOW if lhs + rhs > max timestamp.
 * @return RC_TIMESTMAP_UNDERFLOW if lhs + rhs < 0;
 * @return RC_SUCCESS
 */
retcode_t timestamp_add_duration(const struct Timestamp* lhs, const struct Duration* rhs, struct Timestamp* out);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Timestamp subtract duration.
 *
 * @param lhs Left hand side timestamp object.
 * @param rhs Right hand side duration object.
 * @param out Output timestamp object.
 *
 * @return RC_TIMESTAMP_OVERFLOW if lhs - rhs > max timestamp.
 * @return RC_TIMESTMAP_UNDERFLOW if lhs - rhs < 0;
 * @return RC_SUCCESS
 */
retcode_t timestamp_sub_duration(const struct Timestamp* lhs, const struct Duration* rhs, struct Timestamp* out);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Timestamp subtract timestamp.
 *
 * @param lhs Left hand side timestamp object.
 * @param rhs Right hand side timestamp object.
 * @param out Output duration object.
 *
 * @return RC_DURATION_OVERFLOW if lhs - rhs > max duration.
 * @return RC_DURATION_UNDERFLOW if lhs - rhs < min duration.
 * @return RC_SUCCESS
 */
retcode_t timestamp_sub(const struct Timestamp* lhs, const struct Timestamp* rhs, struct Duration* out);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if timestamp is zero.
 *
 * @param timestamp The timestamp object.
 *
 * @return true
 * @return false
 */
static inline bool_t timestamp_is_zero(const struct Timestamp* timestamp)
{
    return (timestamp->sec) == 0 && (timestamp->nsec == 0);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs > rhs.
 *
 * @param lhs Left hand side timestamp object.
 * @param rhs Right hand side timestamp object.
 *
 * @return true
 * @return false
 */
bool_t timestamp_is_greater(const struct Timestamp* lhs, const struct Timestamp* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs == rhs.
 *
 * @param lhs Left hand side timestamp object.
 * @param rhs Right hand side timestamp object.
 *
 * @return true
 * @return false
 */
bool_t timestamp_is_equal(const struct Timestamp* lhs, const struct Timestamp* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs < rhs.
 *
 * @param lhs Left hand side timestamp object.
 * @param rhs Right hand side timestamp object.
 *
 * @return true
 * @return false
 */
bool_t timestamp_is_less(const struct Timestamp* lhs, const struct Timestamp* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs >= rhs.
 *
 * @param lhs Left hand side timestamp object.
 * @param rhs Right hand side timestamp object.
 *
 * @return true
 * @return false
 */
bool_t timestamp_is_greater_equal(const struct Timestamp* lhs, const struct Timestamp* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Check if lhs <= rhs.
 *
 * @param lhs Left hand side timestamp object.
 * @param rhs Right hand side timestamp object.
 *
 * @return true
 * @return false
 */
bool_t timestamp_is_less_equal(const struct Timestamp* lhs, const struct Timestamp* rhs);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Convert timestamp object to float64 type second.
 *
 * @param timestamp The timestamp object.
 * @param sec Output float64 type second.
 *
 * @return RC_SUCCESS.
 *
 * @warning float64 type has only 15 significant decimal digit. This conversion may cause precision loss.
 */
retcode_t timestamp_to_sec(const struct Timestamp* timestamp, float64_t* sec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Convert timestamp object to int64 type nano second.
 *
 * @param timestamp The timestamp object.
 * @param nsec Output int64 type nano second.
 *
 * @return RC_SUCCESS
 */
retcode_t timestamp_to_nsec(const struct Timestamp* timestamp, int64_t* nsec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get second field of timestamp.
 *
 * @param timestamp The timestamp object
 *
 * @return Second field of timestamp.
 */
uint32_t timestamp_get_sec(const struct Timestamp* timestamp);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get nano second field of timestamp.
 *
 * @param timestamp The timestamp object.
 *
 * @return Nano second field of timestamp.
 */
uint32_t timestamp_get_nsec(const struct Timestamp* timestamp);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Set second field of timestamp.
 *
 * @param timestamp The timestamp object.
 * @param sec Second to set.
 *
 * @return RC_SUCCESS Update timestamp success.
 */
retcode_t timestamp_set_sec(struct Timestamp* timestamp, uint32_t sec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Set nano second field of timestamp.
 *
 * @param timestamp The timestamp object.
 * @param nsec Nano second to set. Valid input range is [0, 999999999].
 *
 * @return RC_TIMESTMAP_INVALID_PARAMETER If input parameter is invalid.
 * @return RC_SUCCESS Update timestamp success.
 */
retcode_t timestamp_set_nsec(struct Timestamp* timestamp, uint32_t nsec);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Get serialized buffer size for timestamp.
 *
 * @param timestamp The input object.
 *
 * @return Serialized size
 */
uint32_t timestamp_get_serialized_size(const struct Timestamp* timestamp);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Serialize Timestamp object to buffer.
 *
 * @param timestamp The timestamp object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return Positive integer Number of bytes serialized into buffer.
 */
retcode_t timestamp_serialize(const struct Timestamp* timestamp, uint8_t* buffer, uint32_t buffer_size);

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Deserialized Timestamp object from buffer.
 *
 * @param timestamp The timestamp object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is less than needed.
 * @return RC_DESERIALIZATION_FAIL Failed to deserialize from buffer due to internal error.
 * @return Positive integer Number of bytes deserialized from buffer.
 */
retcode_t timestamp_deserialize(struct Timestamp* timestamp, const uint8_t* buffer, uint32_t buffer_size);

// retcode_t timestamp_utc_to_gps(struct Timestamp* out, const struct Timestamp* in);
// retcode_t timestamp_ntp_to_gps(struct Timestamp* out, const struct Timestamp* in);
// retcode_t timestamp_gps_to_ntp(struct Timestamp* out, const struct Timestamp* in);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
