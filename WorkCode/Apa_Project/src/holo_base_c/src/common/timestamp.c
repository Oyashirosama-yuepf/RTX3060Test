/**
 * @file timestamp.c
 * @brief This file implements Timestamp and Duration Object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-8-20
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/utils/serialization.h>

static const int32_t NSEC_PER_SEC       = 1000000000;
static const int64_t DURATION_MAX_NSEC  = ((int64_t)INT32_MAX * 1000000000) + 999999999;
static const int64_t DURATION_MIN_NSEC  = (int64_t)INT32_MIN * 1000000000;
static const int64_t TIMESTAMP_MAX_NSEC = ((int64_t)UINT32_MAX * 1000000000) + 999999999;
static const int64_t TIMESTAMP_MIN_NSEC = 0;

retcode_t duration_init(struct Duration* duration)
{
    duration->sec = 0;
    duration->nsec = 0;
    return RC_SUCCESS;
}

static int64_t duration_to_int64(const struct Duration* duration)
{
    return (int64_t)duration->sec * NSEC_PER_SEC + duration->nsec;
}

retcode_t duration_init_from_sec_nsec(struct Duration* duration, int32_t sec, int32_t nsec)
{
    retcode_t rc    = RC_SUCCESS;
    int64_t   value = (int64_t)sec * NSEC_PER_SEC + nsec;
    if (value > DURATION_MAX_NSEC)
    {
        rc = RC_DURATION_OVERFLOW;
    }
    else if (value < DURATION_MIN_NSEC)
    {
        rc = RC_DURATION_UNDERFLOW;
    }
    else
    {
        duration->sec = value / NSEC_PER_SEC;
        duration->nsec = value % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t duration_init_from_sec(struct Duration* duration, float64_t sec)
{
    retcode_t rc  = RC_SUCCESS;
    int64_t value = (int64_t)(sec * NSEC_PER_SEC);
    if (value > DURATION_MAX_NSEC)
    {
        rc = RC_DURATION_OVERFLOW;
    }
    else if (value < DURATION_MIN_NSEC)
    {
        rc = RC_DURATION_UNDERFLOW;
    }
    else
    {
        duration->sec = value / NSEC_PER_SEC;
        duration->nsec = value % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t duration_init_from_nsec(struct Duration* duration, int64_t nsec)
{
    retcode_t rc = RC_SUCCESS;
    if (nsec > DURATION_MAX_NSEC)
    {
        rc = RC_DURATION_OVERFLOW;
    }
    else if (nsec < DURATION_MIN_NSEC)
    {
        rc = RC_DURATION_UNDERFLOW;
    }
    else
    {
        duration->sec = nsec / NSEC_PER_SEC;
        duration->nsec = nsec % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t duration_init_from_duration(struct Duration* duration, const struct Duration* other)
{
    duration->sec = other->sec;
    duration->nsec = other->nsec;
    return RC_SUCCESS;
}

retcode_t duration_add(const struct Duration* lhs, const struct Duration* rhs, struct Duration* out)
{
    retcode_t rc    = RC_SUCCESS;
    int64_t   value = duration_to_int64(lhs) + duration_to_int64(rhs);
    if (value > DURATION_MAX_NSEC)
    {
        rc = RC_DURATION_OVERFLOW;
    }
    else if (value < DURATION_MIN_NSEC)
    {
        rc = RC_DURATION_UNDERFLOW;
    }
    else
    {
        out->sec = value / NSEC_PER_SEC;
        out->nsec = value % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t duration_sub(const struct Duration* lhs, const struct Duration* rhs, struct Duration* out)
{
    retcode_t rc   = RC_SUCCESS;
    int64_t   value = duration_to_int64(lhs) - duration_to_int64(rhs);
    if (value > DURATION_MAX_NSEC)
    {
        rc = RC_DURATION_OVERFLOW;
    }
    else if (value < DURATION_MIN_NSEC)
    {
        rc = RC_DURATION_UNDERFLOW;
    }
    else
    {
        out->sec = value / NSEC_PER_SEC;
        out->nsec = value % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t duration_multiply_int32(const struct Duration* lhs, int32_t rhs, struct Duration* out)
{
    retcode_t rc = RC_SUCCESS;
    if (0 == rhs)
    {
        out->sec = 0;
        out->nsec = 0;
    }
    else
    {
        int64_t nsec = duration_to_int64(lhs);
        int64_t value = duration_to_int64(lhs) * rhs;
        if (value / rhs != nsec )
        {
            if (value < 0)
            {
                rc = RC_DURATION_UNDERFLOW;
            }
            else
            {
                rc = RC_DURATION_OVERFLOW;
            }
        }
        else
        {
            if (value > DURATION_MAX_NSEC)
            {
                rc = RC_DURATION_OVERFLOW;
            }
            else if (value < DURATION_MIN_NSEC)
            {
                rc = RC_DURATION_UNDERFLOW;
            }
            else
            {
                out->sec = value / NSEC_PER_SEC;
                out->nsec = value % NSEC_PER_SEC;
            }
        }
    }
    return rc;
}

retcode_t duration_divide_int32(const struct Duration* lhs, int32_t rhs, struct Duration* out)
{
    retcode_t rc = RC_SUCCESS;
    if (0 == rhs)
    {
        rc = RC_DURATION_INVALID_PARAMETER;
    }
    else
    {
        int64_t value = duration_to_int64(lhs) / rhs;
        out->sec = value / NSEC_PER_SEC;
        out->nsec = value % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t duration_multiply_float64(const struct Duration* lhs, float64_t rhs, struct Duration* out)
{
    retcode_t rc  = RC_SUCCESS;
    float64_t value = duration_to_int64(lhs) * rhs;
    if (value > DURATION_MAX_NSEC)
    {
        rc = RC_DURATION_OVERFLOW;
    }
    else if (value < DURATION_MIN_NSEC)
    {
        rc = RC_DURATION_UNDERFLOW;
    }
    else
    {
        out->sec = (int64_t)value / NSEC_PER_SEC;
        out->nsec = (int64_t)value % NSEC_PER_SEC;
    }
    return rc;
}

bool_t duration_is_greater(const struct Duration* lhs, const struct Duration* rhs)
{
    return duration_to_int64(lhs) > duration_to_int64(rhs);
}

bool_t duration_is_equal(const struct Duration* lhs, const struct Duration* rhs)
{
    return duration_to_int64(lhs) == duration_to_int64(rhs);
}

bool_t duration_is_less(const struct Duration* lhs, const struct Duration* rhs)
{
    return duration_to_int64(lhs) < duration_to_int64(rhs);
}

bool_t duration_is_greater_equal(const struct Duration* lhs, const struct Duration* rhs)
{
    return duration_to_int64(lhs) >= duration_to_int64(rhs);
}

bool_t duration_is_less_equal(const struct Duration* lhs, const struct Duration* rhs)
{
    return duration_to_int64(lhs) <= duration_to_int64(rhs);
}

retcode_t duration_to_sec(const struct Duration* duration, float64_t* sec)
{
    *sec = ((float64_t)(duration_to_int64(duration))) / NSEC_PER_SEC;
    return RC_SUCCESS;
}

retcode_t duration_to_nsec(const struct Duration* duration, int64_t* nsec)
{
    *nsec = duration_to_int64(duration);
    return RC_SUCCESS;
}

int32_t duration_get_sec(const struct Duration* duration)
{
    /*
     * Sec field may be a positive or negtive number. Nsec field is always positive.
     * That means if a duration is -100ns. We present this duration with sec field = -1 and nsec field = 999999900.
     *
     * If duration is negtive, the remainder duration->nsec % NSEC_PER_SEC is also a none positive number. If the
     * remainder is 0, just return sec. If the remainder is negtive number, we have to normalize sec field.
     */
    int32_t sec = duration->sec;
    if(duration->nsec < 0)
    {
        sec -= 1;
    }
    return sec;
}

int32_t duration_get_nsec(const struct Duration* duration)
{
    /*
     * Sec field may be a positive or negtive number. Nsec field is always positive.
     * That means if a duration is -100ns. We present this duration with sec field = -1 and nsec field = 999999900.
     *
     * If duration is negtive, the remainder duration->nsec % NSEC_PER_SEC is also a none positive number. If the
     * remainder is 0, just return 0. If the remainder is negtive number, we have to normalize nsec field.
     */
    int32_t nsec = duration->nsec;
    if (nsec < 0)
    {
        nsec += NSEC_PER_SEC;
    }
    return nsec;
}

retcode_t duration_set_sec(struct Duration* duration, int32_t sec)
{
    retcode_t rc   = RC_SUCCESS;
    if(duration->nsec < 0)
    {
        duration->nsec += NSEC_PER_SEC;
    }
    duration->sec = sec;
    return rc;
}

retcode_t duration_set_nsec(struct Duration* duration, int32_t nsec)
{
    retcode_t rc = RC_SUCCESS;
    if (nsec > (NSEC_PER_SEC - 1) || nsec < 0)
    {
        rc = RC_DURATION_INVALID_PARAMETER;
    }
    else
    {
        duration->nsec = nsec;
    }
    return rc;
}

uint32_t duration_get_serialized_size(const struct Duration* duration)
{
    (void)duration;
    return sizeof(struct Duration);
}

retcode_t duration_serialize(const struct Duration* duration, uint8_t* buffer, uint32_t buffer_size)
{
    assert(duration != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = duration_get_serialized_size(duration);
    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_int32(&duration->sec, buffer, buffer_size);
        serialized_size += serialize_int32(&duration->nsec, buffer + serialized_size, buffer_size - serialized_size);

        assert(serialized_size == expected_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

retcode_t duration_deserialize(struct Duration* duration, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(duration != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = duration_get_serialized_size(duration); //fixed size object.
    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_int32(&duration->sec, buffer, buffer_size);
        deserialized_size += deserialize_int32(&duration->nsec, 
                                               buffer + deserialized_size, 
                                               buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

static int64_t timestamp_to_int64(const struct Timestamp* timestamp)
{
    return (int64_t)timestamp->sec * NSEC_PER_SEC + timestamp->nsec;
}

retcode_t timestamp_init(struct Timestamp* timestamp)
{
    timestamp->sec = 0;
    timestamp->nsec = 0;
    return RC_SUCCESS;
}

retcode_t timestamp_init_from_sec_nsec(struct Timestamp* timestamp, uint32_t sec, uint32_t nsec)
{
    retcode_t rc    = RC_SUCCESS;
    int64_t   value = (int64_t)sec * NSEC_PER_SEC + nsec;
    if (value > TIMESTAMP_MAX_NSEC)
    {
        rc = RC_TIMESTAMP_OVERFLOW;
    }
    else if (value < TIMESTAMP_MIN_NSEC)
    {
        rc = RC_TIMESTAMP_UNDERFLOW;
    }
    else
    {
        timestamp->sec = value / NSEC_PER_SEC;
        timestamp->nsec = value % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t timestamp_init_from_sec(struct Timestamp* timestamp, float64_t sec)
{
    retcode_t rc = RC_SUCCESS;
    if (sec > (float64_t)UINT32_MAX + 0.999990000)
    {
        rc = RC_TIMESTAMP_OVERFLOW;
    }
    else if (sec < (float64_t)TIMESTAMP_MIN_NSEC)
    {
        rc = RC_TIMESTAMP_UNDERFLOW;
    }
    else
    {
        timestamp->sec = (int64_t)(sec * NSEC_PER_SEC) / NSEC_PER_SEC;
        timestamp->nsec = (int64_t)(sec * NSEC_PER_SEC) % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t timestamp_init_from_nsec(struct Timestamp* timestamp, int64_t nsec)
{
    retcode_t rc = RC_SUCCESS;
    if (nsec > TIMESTAMP_MAX_NSEC)
    {
        rc = RC_TIMESTAMP_OVERFLOW;
    }
    else
    {
        timestamp->sec = nsec / NSEC_PER_SEC;
        timestamp->nsec = nsec % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t timestamp_init_from_timestamp(struct Timestamp* timestamp, const struct Timestamp* other)
{
    timestamp->sec = other->sec;
    timestamp->nsec = other->nsec;
    return RC_SUCCESS;
}

retcode_t timestamp_add_duration(const struct Timestamp* lhs, const struct Duration* rhs, struct Timestamp* out)
{
    retcode_t rc    = RC_SUCCESS;
    int64_t   value = timestamp_to_int64(lhs) + duration_to_int64(rhs);
    if (value > TIMESTAMP_MAX_NSEC)
    {
        rc = RC_TIMESTAMP_OVERFLOW;
    }
    else if (value < TIMESTAMP_MIN_NSEC)
    {
        rc = RC_TIMESTAMP_UNDERFLOW;
    }
    else
    {
        out->sec = value / NSEC_PER_SEC;
        out->nsec = value % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t timestamp_sub_duration(const struct Timestamp* lhs, const struct Duration* rhs, struct Timestamp* out)
{
    retcode_t rc    = RC_SUCCESS;
    int64_t   value = timestamp_to_int64(lhs) - duration_to_int64(rhs);
    if (value > TIMESTAMP_MAX_NSEC)
    {
        rc = RC_TIMESTAMP_OVERFLOW;
    }
    else if (value < TIMESTAMP_MIN_NSEC)
    {
        rc = RC_TIMESTAMP_UNDERFLOW;
    }
    else
    {
        out->sec = value / NSEC_PER_SEC;
        out->nsec = value % NSEC_PER_SEC;
    }
    return rc;
}

retcode_t timestamp_sub(const struct Timestamp* lhs, const struct Timestamp* rhs, struct Duration* out)
{
    retcode_t rc    = RC_SUCCESS;
    int64_t   value = timestamp_to_int64(lhs) - timestamp_to_int64(rhs);
    if (value > DURATION_MAX_NSEC)
    {
        rc = RC_DURATION_OVERFLOW;
    }
    else if (value < DURATION_MIN_NSEC)
    {
        rc = RC_DURATION_UNDERFLOW;
    }
    else
    {
        out->sec = value / NSEC_PER_SEC;
        out->nsec = value % NSEC_PER_SEC;
    }
    return rc;
}

bool_t timestamp_is_greater(const struct Timestamp* lhs, const struct Timestamp* rhs)
{
    return timestamp_to_int64(lhs) > timestamp_to_int64(rhs);
}

bool_t timestamp_is_equal(const struct Timestamp* lhs, const struct Timestamp* rhs)
{
    return timestamp_to_int64(lhs) == timestamp_to_int64(rhs);
}

bool_t timestamp_is_less(const struct Timestamp* lhs, const struct Timestamp* rhs)
{
    return timestamp_to_int64(lhs) < timestamp_to_int64(rhs);
}

bool_t timestamp_is_greater_equal(const struct Timestamp* lhs, const struct Timestamp* rhs)
{
    return timestamp_to_int64(lhs) >= timestamp_to_int64(rhs);
}

bool_t timestamp_is_less_equal(const struct Timestamp* lhs, const struct Timestamp* rhs)
{
    return timestamp_to_int64(lhs) <= timestamp_to_int64(rhs);
}

retcode_t timestamp_to_sec(const struct Timestamp* timestamp, float64_t* sec)
{
    *sec = ((float64_t)(timestamp_to_int64(timestamp))) / NSEC_PER_SEC;
    return RC_SUCCESS;
}

retcode_t timestamp_to_nsec(const struct Timestamp* timestamp, int64_t* nsec)
{
    *nsec = timestamp_to_int64(timestamp);
    return RC_SUCCESS;
}

uint32_t timestamp_get_sec(const struct Timestamp* timestamp)
{
    /*
     * Timestamp is always positive. No need to normalize output.
     */
    return timestamp->sec;
}

uint32_t timestamp_get_nsec(const struct Timestamp* timestamp)
{
    /*
     * Timestamp is always positive. No need to normalize output.
     */
    return timestamp->nsec;
}

retcode_t timestamp_set_sec(struct Timestamp* timestamp, uint32_t sec)
{
    timestamp->sec = sec;
    return RC_SUCCESS;
}

retcode_t timestamp_set_nsec(struct Timestamp* timestamp, uint32_t nsec)
{
    retcode_t rc = RC_SUCCESS;
    if (nsec >= (uint32_t)NSEC_PER_SEC)
    {
        rc = RC_TIMESTAMP_INVALID_PARAMETER;
    }
    else
    {
        timestamp->nsec = nsec;
    }
    return rc;
}

uint32_t timestamp_get_serialized_size(const struct Timestamp* timestamp)
{
    (void)timestamp;

    return serialization_aligned_size(sizeof(struct Timestamp));
}

retcode_t timestamp_serialize(const struct Timestamp* timestamp, 
                              uint8_t* buffer, 
                              uint32_t buffer_size)
{
    assert(timestamp != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = timestamp_get_serialized_size(timestamp);
    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_uint32(&timestamp->sec, 
                buffer, 
                buffer_size);

        serialized_size += serialize_uint32(&timestamp->nsec, 
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

retcode_t timestamp_deserialize(struct Timestamp* timestamp, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(timestamp != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = timestamp_get_serialized_size(timestamp); //fixed size object.
    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_uint32(&timestamp->sec, 
                buffer, 
                buffer_size);

        deserialized_size += deserialize_uint32(&timestamp->nsec, 
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        deserialized_size += deserialize_padding(deserialized_size,
                buffer + deserialized_size, 
                buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }

    return rc;
}
