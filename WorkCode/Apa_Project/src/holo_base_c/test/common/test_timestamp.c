/*!
 *  \brief Unit test for Timestamp and Duration.
 *  \author zhangjiannan(zhangjiannan@holomaitc.com)
 *  \date 2019-8-13
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <holo_c/common/timestamp.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <unity.h>

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_init(struct Duration * duration)
 */
static void test_duration_init(void)
{
    struct Duration d;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_init_from_sec_nsec(struct Duration *duration, int32_t sec, int32_t nsec);
 */
static void test_duration_init_from_sec_nsec(void)
{
    struct Duration d;

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec_nsec(&d, 0, 0));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));

    /* Normal case - positive value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec_nsec(&d, 100, 100));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_nsec(&d));
    /* Normal case - negtive value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec_nsec(&d, -100, 100));
    TEST_ASSERT_EQUAL_INT32(-100, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_nsec(&d));

    /* Normalize */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec_nsec(&d, 100, 2000000001));
    TEST_ASSERT_EQUAL_INT32(102, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec_nsec(&d, -100, -100));
    TEST_ASSERT_EQUAL_INT32(-101, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(999999900, duration_get_nsec(&d));

    /* Max and min value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec_nsec(&d, INT32_MAX, 999999999));
    TEST_ASSERT_EQUAL_INT32(INT32_MAX, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec_nsec(&d, INT32_MIN, 0));
    TEST_ASSERT_EQUAL_INT32(INT32_MIN, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));

    /* Overflow and underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_OVERFLOW, duration_init_from_sec_nsec(&d, INT32_MAX, 1000000000));
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_UNDERFLOW, duration_init_from_sec_nsec(&d, INT32_MIN, -1));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_init_from_sec(struct Duration *duration, float64_t sec);
 */
static void test_duration_init_from_sec(void)
{
    /* TODO pay attention to rounding error */
    struct Duration d;

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec(&d, 0.0));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));

    /* Normal case - positive value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec(&d, 123.123456789));
    TEST_ASSERT_EQUAL_INT32(123, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(123456789, duration_get_nsec(&d));
    /* Normal case - negtive value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec(&d, -123.123456789));
    TEST_ASSERT_EQUAL_INT32(-124, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(876543211, duration_get_nsec(&d));

    /* Normalize */
    /* See normal case - negtive value */

    /* Max and min value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec(&d, 2147483647.999900000));
    TEST_ASSERT_EQUAL_INT32(INT32_MAX, duration_get_sec(&d));
    TEST_ASSERT_INT32_WITHIN(100000, 999900000, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_sec(&d, -2147483648.0));
    TEST_ASSERT_EQUAL_INT32(INT32_MIN, duration_get_sec(&d));
    TEST_ASSERT_INT32_WITHIN(100000, 0, duration_get_nsec(&d));

    /* Overflow and underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_OVERFLOW, duration_init_from_sec(&d, 2147483648.0));
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_UNDERFLOW, duration_init_from_sec(&d, -2147483648.000100000));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_init_from_nsec(struct Duration *duration, int64_t nsec);
 */
static void test_duration_init_from_nsec(void)
{
    struct Duration d;

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_nsec(&d, 0));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));

    /* Normal case - positive value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_nsec(&d, 123456789));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(123456789, duration_get_nsec(&d));
    /* Normal case - negtive value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_nsec(&d, -123456789));
    TEST_ASSERT_EQUAL_INT32(-1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(876543211, duration_get_nsec(&d));

    /* Normalize */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_nsec(&d, 123456789000));
    TEST_ASSERT_EQUAL_INT32(123, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(456789000, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_nsec(&d, -123456789000));
    TEST_ASSERT_EQUAL_INT32(-124, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(543211000, duration_get_nsec(&d));

    /* Max and min value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_nsec(&d, (int64_t)INT32_MAX * 1000000000 + 999999999));
    TEST_ASSERT_EQUAL_INT32(INT32_MAX, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_nsec(&d, (int64_t)INT32_MIN * 1000000000));
    TEST_ASSERT_EQUAL_INT32(INT32_MIN, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));

    /* Overflow and underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_OVERFLOW, duration_init_from_nsec(&d, ((int64_t)INT_MAX + 1) * 1000000000));
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_UNDERFLOW, duration_init_from_nsec(&d, (int64_t)INT_MIN * 1000000000 - 1));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_copy(const struct Duration *duration, struct Duration *other);
 */
static void test_duration_init_from_duration(void)
{
    struct Duration d1, d2;

    /* Zero */
    duration_init_from_sec_nsec(&d1, 0, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_duration(&d2, &d1));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d2));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d2));

    /* Normal case */
    duration_init_from_sec_nsec(&d1, 100, 100);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_init_from_duration(&d2, &d1));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_sec(&d2));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_nsec(&d2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_add(const struct Duration *duration, const struct Duration *rhs, struct Duration *
 * out)
 */
static void test_duration_add(void)
{
    struct Duration d1, d2, dout;
    duration_init_from_sec_nsec(&d1, 0, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    duration_init_from_sec_nsec(&dout, 0, 0);

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));
    duration_init_from_sec_nsec(&d1, -1, -1);
    duration_init_from_sec_nsec(&d2, 1, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    /* Normal case */
    /* positive + positive */
    duration_init_from_sec_nsec(&d1, 12345, 67890);
    duration_init_from_sec_nsec(&d2, 98765, 43210);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(111110, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(111100, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &d1));
    TEST_ASSERT_EQUAL_INT32(111110, duration_get_sec(&d1));
    TEST_ASSERT_EQUAL_INT32(111100, duration_get_nsec(&d1));

    /* negative + negative */
    duration_init_from_sec_nsec(&d1, -12345, -67890);
    duration_init_from_sec_nsec(&d2, -98765, -43210);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(-111111, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(999888900, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &d1));
    TEST_ASSERT_EQUAL_INT32(-111111, duration_get_sec(&d1));
    TEST_ASSERT_EQUAL_INT32(999888900, duration_get_nsec(&d1));

    /* positive + negative */
    duration_init_from_sec_nsec(&d1, 88888, 77777);
    duration_init_from_sec_nsec(&d2, -66666, -55555);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(22222, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(22222, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &d1));
    TEST_ASSERT_EQUAL_INT32(22222, duration_get_sec(&d1));
    TEST_ASSERT_EQUAL_INT32(22222, duration_get_nsec(&d1));

    /* with carray */
    duration_init_from_sec_nsec(&d1, 1, 999999999);
    duration_init_from_sec_nsec(&d2, 1, 2);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(3, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &d1));
    TEST_ASSERT_EQUAL_INT32(3, duration_get_sec(&d1));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_nsec(&d1));

    /* Max and min value */
    duration_init_from_sec_nsec(&d1, INT32_MAX - 1, 999999998);
    duration_init_from_sec_nsec(&d2, 1, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(INT32_MAX, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&dout));

    duration_init_from_sec_nsec(&d1, INT32_MIN + 1, 999999999);
    duration_init_from_sec_nsec(&d2, -1, -999999999);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_add(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(INT32_MIN, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    /* Overflow and underflow */
    duration_init_from_sec_nsec(&d1, INT32_MAX - 1, 999999998);
    duration_init_from_sec_nsec(&d2, 1, 2);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_OVERFLOW, duration_add(&d1, &d2, &dout));

    duration_init_from_sec_nsec(&d1, INT32_MIN + 1, 999999999);
    duration_init_from_sec_nsec(&d2, -2, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_UNDERFLOW, duration_add(&d1, &d2, &dout));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_sub(const struct Duration *duration, const struct Duration *rhs, struct Duration *out)
 */
static void test_duration_sub(void)
{
    struct Duration d1, d2, dout;
    duration_init_from_sec_nsec(&d1, 0, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    duration_init_from_sec_nsec(&dout, 0, 0);

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));
    duration_init_from_sec_nsec(&d1, 1, 1);
    duration_init_from_sec_nsec(&d2, 1, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    /* Normal case */
    /* positive - positive */
    duration_init_from_sec_nsec(&d1, 22222, 22222);
    duration_init_from_sec_nsec(&d2, 11111, 11111);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(11111, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(11111, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &d1));
    TEST_ASSERT_EQUAL_INT32(11111, duration_get_sec(&d1));
    TEST_ASSERT_EQUAL_INT32(11111, duration_get_nsec(&d1));
    /* negative - negative */
    duration_init_from_sec_nsec(&d1, -22222, 22222);
    duration_init_from_sec_nsec(&d2, -11111, 11111);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(-11111, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(11111, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &d1));
    TEST_ASSERT_EQUAL_INT32(-11111, duration_get_sec(&d1));
    TEST_ASSERT_EQUAL_INT32(11111, duration_get_nsec(&d1));
    /* positive - negative */
    duration_init_from_sec_nsec(&d1, 88888, 77777);
    duration_init_from_sec_nsec(&d2, -11111, -22222);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(99999, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(99999, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &d1));
    TEST_ASSERT_EQUAL_INT32(99999, duration_get_sec(&d1));
    TEST_ASSERT_EQUAL_INT32(99999, duration_get_nsec(&d1));
    /* with carray */
    duration_init_from_sec_nsec(&d1, 10, 1);
    duration_init_from_sec_nsec(&d2, 1, 2);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(8, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &d1));
    TEST_ASSERT_EQUAL_INT32(8, duration_get_sec(&d1));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&d1));

    /* Max and min value */
    duration_init_from_sec_nsec(&d1, INT32_MAX - 1, 999999998);
    duration_init_from_sec_nsec(&d2, -1, -1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(INT32_MAX, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&dout));

    duration_init_from_sec_nsec(&d1, INT32_MIN + 1, 999999999);
    duration_init_from_sec_nsec(&d2, 1, 999999999);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_sub(&d1, &d2, &dout));
    TEST_ASSERT_EQUAL_INT32(INT32_MIN, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    /* Overflow and underflow */
    duration_init_from_sec_nsec(&d1, INT32_MAX - 1, 999999998);
    duration_init_from_sec_nsec(&d2, -1, -2);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_OVERFLOW, duration_sub(&d1, &d2, &dout));

    duration_init_from_sec_nsec(&d1, INT32_MIN + 1, 999999999);
    duration_init_from_sec_nsec(&d2, 2, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_UNDERFLOW, duration_sub(&d1, &d2, &dout));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_multiply_int32(const struct Duration *duration, const struct Duration *rhs, struct
 * Duration *out)
 */
static void test_duration_multiply_int32(void)
{
    struct Duration d, dout;
    duration_init_from_sec_nsec(&d, 0, 0);
    duration_init_from_sec_nsec(&dout, 0, 0);

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, 0, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, 100, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));
    duration_init_from_sec_nsec(&d, 1, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, 0, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    /* Normal case */
    duration_init_from_sec_nsec(&d, 1, 100000000);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, 1, &dout));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(100000000, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, 1, &d));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(100000000, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, 1, 100000000);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, 2, &dout));
    TEST_ASSERT_EQUAL_INT32(2, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(200000000, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, 2, &d));
    TEST_ASSERT_EQUAL_INT32(2, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(200000000, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, 1, 100000000);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, 11, &dout));
    TEST_ASSERT_EQUAL_INT32(12, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(100000000, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, 11, &d));
    TEST_ASSERT_EQUAL_INT32(12, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(100000000, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, 1, 100000000);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, -1, &dout));
    TEST_ASSERT_EQUAL_INT32(-2, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(900000000, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, -1, &d));
    TEST_ASSERT_EQUAL_INT32(-2, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(900000000, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, 1, 100000000);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, -11, &dout));
    TEST_ASSERT_EQUAL_INT32(-13, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(900000000, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_int32(&d, -11, &d));
    TEST_ASSERT_EQUAL_INT32(-13, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(900000000, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, 1, 100000000);

    /* Overflow and underflow */
    duration_init_from_sec_nsec(&d, INT32_MAX / 2 + 1, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_OVERFLOW, duration_multiply_int32(&d, 2, &dout));

    duration_init_from_sec_nsec(&d, INT32_MIN / 2 - 1, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_UNDERFLOW, duration_multiply_int32(&d, 2, &dout));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_divide_int32(const struct Duration *lhs, int32_t rhs, struct Duration *out);
 */
static void test_duration_divide_int32(void)
{
    struct Duration d, dout;
    duration_init_from_sec_nsec(&d, 0, 0);

    /* Zero */
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_divide_int32(&d, 1, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    /* Normal case */
    duration_init_from_sec_nsec(&d, 100, 100);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_divide_int32(&d, 1, &dout));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_divide_int32(&d, 1, &d));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, 100, 100);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_divide_int32(&d, 2, &dout));
    TEST_ASSERT_EQUAL_INT32(50, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(50, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_divide_int32(&d, 2, &d));
    TEST_ASSERT_EQUAL_INT32(50, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(50, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, 100, 100);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_divide_int32(&d, -2, &dout));
    TEST_ASSERT_EQUAL_INT32(-51, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(999999950, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_divide_int32(&d, -2, &d));
    TEST_ASSERT_EQUAL_INT32(-51, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(999999950, duration_get_nsec(&d));

    /* Invalid parameter*/
    duration_init_from_sec_nsec(&d, 100, 100);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_INVALID_PARAMETER, duration_divide_int32(&d, 0, &dout));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_multiply_float64(const struct Duration *lhs, float32_t scale, struct Duration *out);
 *
 * @warning scale may cause predcision loss
 */
static void test_duration_multiply_float64(void)
{
    struct Duration d, dout;

    /* Zero */
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_float64(&d, 1.0f, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_float64(&d, 0.0f, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    /* Normal case */
    duration_init_from_sec_nsec(&d, 1, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_float64(&d, 1.0f, &dout));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_nsec(&dout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_float64(&d, 1.0f, &d));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, 1, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_multiply_float64(&d, -1.0f, &d));
    TEST_ASSERT_EQUAL_INT32(-2, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&d));

    /* Overflow and Underflow */
    duration_init_from_sec_nsec(&d, INT32_MAX / 2 + 1, 999999999);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_OVERFLOW, duration_multiply_float64(&d, 2.0f, &dout));
    duration_init_from_sec_nsec(&d, INT32_MIN / 2 - 1, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_UNDERFLOW, duration_multiply_float64(&d, 2.0f, &dout));
    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_OVERFLOW, duration_multiply_float64(&d, (float64_t)INT32_MAX + 1.0001, &dout));
    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_UNDERFLOW, duration_multiply_float64(&d, (float64_t)INT32_MIN - 0.0001, &dout));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t duration_is_zero(const struct Duration *duration);
 */
static void test_duration_is_zero(void)
{
    struct Duration d;
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_TRUE(duration_is_zero(&d));
    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_FALSE(duration_is_zero(&d));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t duration_is_greater(const struct Duration *lhs, const struct Duration *rhs);
 */
static void test_duration_is_greater(void)
{
    struct Duration d1, d2;

    /* Zero */
    duration_init_from_sec_nsec(&d1, 0, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_FALSE(duration_is_greater(&d1, &d2));

    /* Normal case */
    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_TRUE(duration_is_greater(&d1, &d2));

    duration_init_from_sec_nsec(&d1, -1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_FALSE(duration_is_greater(&d1, &d2));

    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 1, 0);
    TEST_ASSERT_FALSE(duration_is_greater(&d1, &d2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t duration_is_equal(const struct Duration *lhs, const struct Duration *rhs);
 */
static void test_duration_is_equal(void)
{
    struct Duration d1, d2;

    /* Zero */
    duration_init_from_sec_nsec(&d1, 0, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_TRUE(duration_is_equal(&d1, &d2));

    /* Normal case */
    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_FALSE(duration_is_equal(&d1, &d2));

    duration_init_from_sec_nsec(&d1, -1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_FALSE(duration_is_equal(&d1, &d2));

    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 1, 0);
    TEST_ASSERT_TRUE(duration_is_equal(&d1, &d2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t duration_is_less(const struct Duration *lhs, const struct Duration *rhs);
 */
static void test_duration_is_less(void)
{
    struct Duration d1, d2;

    /* Zero */
    duration_init_from_sec_nsec(&d1, 0, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_FALSE(duration_is_less(&d1, &d2));

    /* Normal case */
    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_FALSE(duration_is_less(&d1, &d2));

    duration_init_from_sec_nsec(&d1, -1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_TRUE(duration_is_less(&d1, &d2));

    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 1, 0);
    TEST_ASSERT_FALSE(duration_is_less(&d1, &d2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t duration_is_greater_equal(const struct Duration *lhs, const struct Duration *rhs);
 */
static void test_duration_is_greater_equal(void)
{
    struct Duration d1, d2;

    /* Zero */
    duration_init_from_sec_nsec(&d1, 0, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_TRUE(duration_is_greater_equal(&d1, &d2));

    /* Normal case */
    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_TRUE(duration_is_greater_equal(&d1, &d2));

    duration_init_from_sec_nsec(&d1, -1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_FALSE(duration_is_greater_equal(&d1, &d2));

    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 1, 0);
    TEST_ASSERT_TRUE(duration_is_greater_equal(&d1, &d2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t duration_is_less_equal(const struct Duration *lhs, const struct Duration *rhs);
 */
static void test_duration_is_less_equal(void)
{
    struct Duration d1, d2;

    /* Zero */
    duration_init_from_sec_nsec(&d1, 0, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_TRUE(duration_is_less_equal(&d1, &d2));

    /* Normal case */
    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_FALSE(duration_is_less_equal(&d1, &d2));

    duration_init_from_sec_nsec(&d1, -1, 0);
    duration_init_from_sec_nsec(&d2, 0, 0);
    TEST_ASSERT_TRUE(duration_is_less_equal(&d1, &d2));

    duration_init_from_sec_nsec(&d1, 1, 0);
    duration_init_from_sec_nsec(&d2, 1, 0);
    TEST_ASSERT_TRUE(duration_is_less_equal(&d1, &d2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_to_sec(const struct Duration *duration, float64_t *sec);
 */
static void test_duration_to_sec(void)
{
    struct Duration d;
    float64_t       res;

    /* Zero */
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_sec(&d, &res));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res);

    /* Normal case */
    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_sec(&d, &res));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, res);
    duration_init_from_sec_nsec(&d, -1, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_sec(&d, &res));
    TEST_ASSERT_EQUAL_DOUBLE(-1.0, res);

    /* Max and min */
    duration_init_from_sec_nsec(&d, INT32_MAX, 999999999);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_sec(&d, &res));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, (float64_t)INT32_MAX + 0.999999999, res);
    duration_init_from_sec_nsec(&d, INT32_MIN, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_sec(&d, &res));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, (float64_t)INT32_MIN, res);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_to_nsec(const struct Duration *duration, int64_t *nsec);
 */
static void test_duration_to_nsec(void)
{
    struct Duration d;
    int64_t         res;

    /* Zero */
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_nsec(&d, &res));
    TEST_ASSERT_EQUAL_INT64(0, res);

    /* Normal case */
    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_nsec(&d, &res));
    TEST_ASSERT_EQUAL_INT64(1000000000, res);
    duration_init_from_sec_nsec(&d, -1, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_nsec(&d, &res));
    TEST_ASSERT_EQUAL_INT64(-1000000000, res);
    duration_init_from_sec_nsec(&d, 1, 123456789);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_nsec(&d, &res));
    TEST_ASSERT_EQUAL_INT64(1123456789, res);
    duration_init_from_sec_nsec(&d, -1, -123456789);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_nsec(&d, &res));
    TEST_ASSERT_EQUAL_INT64(-1123456789, res);

    /* Max and min */
    duration_init_from_sec_nsec(&d, INT32_MAX, 999999999);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_nsec(&d, &res));
    TEST_ASSERT_EQUAL_INT64((int64_t)INT32_MAX * 1000000000 + 999999999, res);
    duration_init_from_sec_nsec(&d, INT32_MIN, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, duration_to_nsec(&d, &res));
    TEST_ASSERT_EQUAL_INT64((int64_t)INT32_MIN * 1000000000, res);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test int32_t duration_get_sec(const struct Duration *duration);
 */
static void test_duration_get_sec(void)
{
    struct Duration d;

    /* Normal case */
    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_EQUAL_INT32(1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, 1, 100);
    TEST_ASSERT_EQUAL_INT32(1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, -1, 0);
    TEST_ASSERT_EQUAL_INT32(-1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, -1, 100);
    TEST_ASSERT_EQUAL_INT32(-1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_nsec(&d));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test int32_t duration_get_nsec(const struct Duration *duration);
 */
static void test_duration_get_nsec(void)
{
    struct Duration d;

    /* Normal case */
    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_EQUAL_INT32(1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, -1, 0);
    TEST_ASSERT_EQUAL_INT32(-1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    duration_init_from_sec_nsec(&d, -1, 100);
    TEST_ASSERT_EQUAL_INT32(-1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(100, duration_get_nsec(&d));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_set_sec(struct Duration *duration, int32_t sec);
 */
static void test_duration_set_sec(void)
{
    struct Duration d;

    /* Normal case */
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_set_sec(&d, 1));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_set_sec(&d, -1));
    TEST_ASSERT_EQUAL_INT32(-1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_set_sec(&d, INT32_MAX));
    TEST_ASSERT_EQUAL_INT32(INT32_MAX, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_set_sec(&d, INT32_MIN));
    TEST_ASSERT_EQUAL_INT32(INT32_MIN, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t duration_set_nsec(struct Duration *duration, int32_t nsec);
 */
static void test_duration_set_nsec(void)
{
    struct Duration d;

    /* Normal case */
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_set_nsec(&d, 1));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, duration_set_nsec(&d, 999999999));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&d));

    /* Invalid parameter */
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_INVALID_PARAMETER, duration_set_nsec(&d, -1));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_INVALID_PARAMETER, duration_set_nsec(&d, 1000000000));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test uint32_t duration_get_serialized_size(const struct Duration *duration);
 */
static void test_duration_get_serialized_size(void)
{
    struct Duration d;

    TEST_ASSERT_EQUAL_UINT32(8, duration_get_serialized_size(&d));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test int32_t duration_serialize(const struct Duration *duration, uint8_t *buffer, uint32_t buffer_size);
 */
static void test_duration_serialize(void)
{
    uint8_t         buffer[8];
    struct Duration d;

    /* Zero */
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_EQUAL_INT32(8, duration_serialize(&d, buffer, 8));
    uint8_t expected1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected1, buffer, 8);

    /* Normal case */
    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_EQUAL_INT32(8, duration_serialize(&d, buffer, 8));
    uint8_t expected2[8] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected2, buffer, 8);

    duration_init_from_sec_nsec(&d, -1, 0);
    TEST_ASSERT_EQUAL_INT32(8, duration_serialize(&d, buffer, 8));
    uint8_t expected3[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected3, buffer, 8);

    /* Overflow */
    duration_init_from_sec_nsec(&d, 1, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, duration_serialize(&d, buffer, 7));
}

static void test_duration_deserialize(void)
{
    uint8_t         buffer1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t         buffer2[8] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
    uint8_t         buffer3[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00};
    struct Duration d;

    /* Zero */
    duration_init_from_sec_nsec(&d, 0, 0);
    TEST_ASSERT_EQUAL_INT32(8, duration_deserialize(&d, buffer1, 8));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));

    /* Normal case */
    TEST_ASSERT_EQUAL_INT32(8, duration_deserialize(&d, buffer2, 8));
    TEST_ASSERT_EQUAL_INT32(1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));
    TEST_ASSERT_EQUAL_INT32(8, duration_deserialize(&d, buffer3, 8));
    TEST_ASSERT_EQUAL_INT32(-1, duration_get_sec(&d));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&d));

    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, duration_deserialize(&d, buffer2, 7));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_init(struct Timestamp *timestamp);
 */
static void test_timestamp_init(void)
{
    struct Timestamp t;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_init_from_sec_nsec(struct Timestamp *timestamp, int32_t sec, int32_t nsec);
 */
static void test_timestamp_init_from_sec_nsec(void)
{
    struct Timestamp t;

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_sec_nsec(&t, 0, 0));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));

    /* Normal case */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_sec_nsec(&t, 100, 100));
    TEST_ASSERT_EQUAL_UINT32(100, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(100, timestamp_get_nsec(&t));

    /* Normalize */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_sec_nsec(&t, 100, 2000000001));
    TEST_ASSERT_EQUAL_UINT32(102, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_nsec(&t));

    /* Max value */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_sec_nsec(&t, UINT32_MAX, 999999999));
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(999999999, timestamp_get_nsec(&t));

    /* Overflow */
    TEST_ASSERT_EQUAL_UINT32(RC_TIMESTAMP_OVERFLOW, timestamp_init_from_sec_nsec(&t, UINT32_MAX, 1000000000));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_init_from_sec(struct Timestamp *timestamp, float64_t sec);
 */
static void test_timestamp_init_from_sec(void)
{
    /* TODO pay attention to rounding error */
    struct Timestamp t;

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_sec(&t, 0.0));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));

    /* Normal case */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_sec(&t, 123.123456789));
    TEST_ASSERT_EQUAL_UINT32(123, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(123456789, timestamp_get_nsec(&t));

    /* Max */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_sec(&t, 4294967295.999900000));
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, timestamp_get_sec(&t));
    TEST_ASSERT_UINT32_WITHIN(100000, 999900000, timestamp_get_nsec(&t));

    /* Overflow and underflow */
    TEST_ASSERT_EQUAL_INT32(RC_TIMESTAMP_OVERFLOW, timestamp_init_from_sec(&t, 4294967296.0001));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_init_from_nsec(struct Timestamp *timestamp, int64_t nsec);
 */
static void test_timestamp_init_from_nsec(void)
{
    struct Timestamp t;

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_nsec(&t, 0));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));

    /* Normal case */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_nsec(&t, 123456789));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(123456789, timestamp_get_nsec(&t));

    /* Normalize */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_nsec(&t, 123456789000));
    TEST_ASSERT_EQUAL_UINT32(123, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(456789000, timestamp_get_nsec(&t));

    /* Max */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_nsec(&t, (uint64_t)UINT32_MAX * 1000000000 + 999999999));
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(999999999, timestamp_get_nsec(&t));

    /* Overflow and underflow */
    TEST_ASSERT_EQUAL_INT32(RC_TIMESTAMP_OVERFLOW, timestamp_init_from_nsec(&t, ((uint64_t)UINT_MAX + 1) * 1000000000));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_copy(const struct Timestamp *timestamp, struct Timestamp *other);
 */
static void test_timestamp_init_from_timestamp(void)
{
    struct Timestamp t1, t2;

    /* Zero */
    timestamp_init_from_sec_nsec(&t1, 0, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_timestamp(&t2, &t1));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t2));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t2));

    /* Normal case */
    timestamp_init_from_sec_nsec(&t1, 100, 100);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_init_from_timestamp(&t2, &t1));
    TEST_ASSERT_EQUAL_UINT32(100, timestamp_get_sec(&t2));
    TEST_ASSERT_EQUAL_UINT32(100, timestamp_get_nsec(&t2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_add_duration(const struct Timestamp *lhs, const struct Duration *rhs,
 *                                              struct Timestamp *out);
 */
static void test_timestamp_add_duration(void)
{
    struct Timestamp t, tout;
    struct Duration  d;
    timestamp_init_from_sec_nsec(&t, 0, 0);
    duration_init_from_sec_nsec(&d, 0, 0);
    timestamp_init_from_sec_nsec(&tout, 0, 0);

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_add_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&tout));

    timestamp_init_from_sec_nsec(&t, 1, 1);
    duration_init_from_sec_nsec(&d, -1, -1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_add_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&tout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_add_duration(&t, &d, &t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));

    /* Normal case */
    timestamp_init_from_sec_nsec(&t, 12345, 67890);
    duration_init_from_sec_nsec(&d, 98765, 43210);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_add_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(111110, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(111100, timestamp_get_nsec(&tout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_add_duration(&t, &d, &t));
    TEST_ASSERT_EQUAL_UINT32(111110, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(111100, timestamp_get_nsec(&t));

    /* with carray */
    timestamp_init_from_sec_nsec(&t, 1, 999999999);
    duration_init_from_sec_nsec(&d, 1, 2);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_add_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(3, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_nsec(&tout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_add_duration(&t, &d, &t));
    TEST_ASSERT_EQUAL_UINT32(3, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_nsec(&t));

    /* Max */
    timestamp_init_from_sec_nsec(&t, UINT32_MAX - 1, 999999998);
    duration_init_from_sec_nsec(&d, 1, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_add_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(999999999, timestamp_get_nsec(&tout));

    /* Overflow and underflow */
    timestamp_init_from_sec_nsec(&t, UINT32_MAX - 1, 999999998);
    duration_init_from_sec_nsec(&d, 1, 2);
    TEST_ASSERT_EQUAL_INT32(RC_TIMESTAMP_OVERFLOW, timestamp_add_duration(&t, &d, &tout));

    timestamp_init_from_sec_nsec(&t, 1, 999999999);
    duration_init_from_sec_nsec(&d, -2, 0);
    TEST_ASSERT_EQUAL_INT32(RC_TIMESTAMP_UNDERFLOW, timestamp_add_duration(&t, &d, &tout));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_sub_duration(const struct Timestamp *lhs, const struct Duration *rhs,
 *                                              struct Timestamp *out);
 */
static void test_timestamp_sub_duration(void)
{
    struct Timestamp t, tout;
    struct Duration  d;
    timestamp_init_from_sec_nsec(&t, 0, 0);
    duration_init_from_sec_nsec(&d, 0, 0);
    timestamp_init_from_sec_nsec(&tout, 0, 0);

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&tout));
    timestamp_init_from_sec_nsec(&t, 1, 1);
    duration_init_from_sec_nsec(&d, 1, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&tout));

    /* Normal case */
    /* timestamp - positive duration */
    timestamp_init_from_sec_nsec(&t, 22222, 22222);
    duration_init_from_sec_nsec(&d, 11111, 11111);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(11111, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(11111, timestamp_get_nsec(&tout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub_duration(&t, &d, &t));
    TEST_ASSERT_EQUAL_UINT32(11111, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(11111, timestamp_get_nsec(&t));
    /* timestamp - negtive duration */
    timestamp_init_from_sec_nsec(&t, 88888, 77777);
    duration_init_from_sec_nsec(&d, -11111, -22222);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(99999, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(99999, timestamp_get_nsec(&tout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub_duration(&t, &d, &t));
    TEST_ASSERT_EQUAL_UINT32(99999, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(99999, timestamp_get_nsec(&t));
    /* with carray */
    timestamp_init_from_sec_nsec(&t, 10, 1);
    duration_init_from_sec_nsec(&d, 1, 2);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(8, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(999999999, timestamp_get_nsec(&tout));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub_duration(&t, &d, &t));
    TEST_ASSERT_EQUAL_UINT32(8, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(999999999, timestamp_get_nsec(&t));

    /* Max */
    timestamp_init_from_sec_nsec(&t, UINT32_MAX - 1, 999999998);
    duration_init_from_sec_nsec(&d, -1, -1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub_duration(&t, &d, &tout));
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, timestamp_get_sec(&tout));
    TEST_ASSERT_EQUAL_UINT32(999999999, timestamp_get_nsec(&tout));

    /* Overflow and underflow */
    timestamp_init_from_sec_nsec(&t, UINT32_MAX - 1, 999999998);
    duration_init_from_sec_nsec(&d, -1, -2);
    TEST_ASSERT_EQUAL_INT32(RC_TIMESTAMP_OVERFLOW, timestamp_sub_duration(&t, &d, &tout));

    timestamp_init_from_sec_nsec(&t, 1, 999999999);
    duration_init_from_sec_nsec(&d, 2, 0);
    TEST_ASSERT_EQUAL_INT32(RC_TIMESTAMP_UNDERFLOW, timestamp_sub_duration(&t, &d, &tout));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_sub(const struct Timestamp *lhs, const struct *Timestamp *rhs, struct Duration *out)
 */
static void test_timestamp_sub(void)
{
    struct Timestamp t1, t2;
    struct Duration  dout;
    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    duration_init_from_sec_nsec(&dout, 0, 0);

    /* Zero */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub(&t1, &t2, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));
    timestamp_init_from_sec_nsec(&t1, 1, 1);
    timestamp_init_from_sec_nsec(&t2, 1, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub(&t1, &t2, &dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    /* Normal case */
    /* large - small */
    timestamp_init_from_sec_nsec(&t1, 22222, 22222);
    timestamp_init_from_sec_nsec(&t2, 11111, 11111);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub(&t1, &t2, &dout));
    TEST_ASSERT_EQUAL_INT32(11111, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(11111, duration_get_nsec(&dout));
    /* small - large */
    timestamp_init_from_sec_nsec(&t1, 11111, 11111);
    timestamp_init_from_sec_nsec(&t2, 22222, 22222);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub(&t1, &t2, &dout));
    TEST_ASSERT_EQUAL_INT32(-11112, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(999988889, duration_get_nsec(&dout));
    /* with carray */
    timestamp_init_from_sec_nsec(&t1, 10, 1);
    timestamp_init_from_sec_nsec(&t2, 1, 2);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub(&t1, &t2, &dout));
    TEST_ASSERT_EQUAL_INT32(8, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&dout));

    /* Max and min value */
    timestamp_init_from_sec_nsec(&t1, (uint32_t)INT32_MAX + 1, 999999999);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub(&t1, &t2, &dout));
    TEST_ASSERT_EQUAL_INT32(INT32_MAX, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(999999999, duration_get_nsec(&dout));

    timestamp_init_from_sec_nsec(&t1, 1, 999999999);
    timestamp_init_from_sec_nsec(&t2, (uint32_t)INT32_MAX + 2, 999999999);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_sub(&t1, &t2, &dout));
    TEST_ASSERT_EQUAL_INT32(INT32_MIN, duration_get_sec(&dout));
    TEST_ASSERT_EQUAL_INT32(0, duration_get_nsec(&dout));

    /* Overflow and underflow */
    timestamp_init_from_sec_nsec(&t1, (uint32_t)INT32_MAX + 1, 999999999);
    timestamp_init_from_sec_nsec(&t2, 0, 999999999);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_OVERFLOW, timestamp_sub(&t1, &t2, &dout));

    timestamp_init_from_sec_nsec(&t1, 0, 999999998);
    timestamp_init_from_sec_nsec(&t2, (uint32_t)INT32_MAX + 1, 999999999);
    TEST_ASSERT_EQUAL_INT32(RC_DURATION_UNDERFLOW, timestamp_sub(&t1, &t2, &dout));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t timestamp_is_zero(const struct Timestamp *timestamp);
 */
static void test_timestamp_is_zero(void)
{
    struct Timestamp t;
    timestamp_init_from_sec_nsec(&t, 0, 0);
    TEST_ASSERT_TRUE(timestamp_is_zero(&t));
    timestamp_init_from_sec_nsec(&t, 1, 0);
    TEST_ASSERT_FALSE(timestamp_is_zero(&t));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t timestamp_is_greater(const struct Timestamp *lhs, const struct Timestamp *rhs);
 */
static void test_timestamp_is_greater(void)
{
    struct Timestamp t1, t2;

    /* Zero */
    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_FALSE(timestamp_is_greater(&t1, &t2));

    /* Normal case */
    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_TRUE(timestamp_is_greater(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_FALSE(timestamp_is_greater(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_FALSE(timestamp_is_greater(&t1, &t2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t timestamp_is_equal(const struct Timestamp *lhs, const struct Timestamp *rhs);
 */
static void test_timestamp_is_equal(void)
{
    struct Timestamp t1, t2;

    /* Zero */
    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_TRUE(timestamp_is_equal(&t1, &t2));

    /* Normal case */
    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_FALSE(timestamp_is_equal(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_FALSE(timestamp_is_equal(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_TRUE(timestamp_is_equal(&t1, &t2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t timestamp_is_less(const struct Timestamp *lhs, const struct Timestamp *rhs);
 */
static void test_timestamp_is_less(void)
{
    struct Timestamp t1, t2;

    /* Zero */
    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_FALSE(timestamp_is_less(&t1, &t2));

    /* Normal case */
    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_FALSE(timestamp_is_less(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_TRUE(timestamp_is_less(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_FALSE(timestamp_is_less(&t1, &t2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t timestamp_is_greater_equal(const struct Timestamp *lhs, const struct Timestamp *rhs);
 */
static void test_timestamp_is_greater_equal(void)
{
    struct Timestamp t1, t2;

    /* Zero */
    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_TRUE(timestamp_is_greater_equal(&t1, &t2));

    /* Normal case */
    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_TRUE(timestamp_is_greater_equal(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_FALSE(timestamp_is_greater_equal(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_TRUE(timestamp_is_greater_equal(&t1, &t2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test bool_t timestamp_is_less_equal(const struct Timestamp *lhs, const struct Timestamp *rhs);
 */
static void test_timestamp_is_less_equal(void)
{
    struct Timestamp t1, t2;

    /* Zero */
    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_TRUE(timestamp_is_less_equal(&t1, &t2));

    /* Normal case */
    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 0, 0);
    TEST_ASSERT_FALSE(timestamp_is_less_equal(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 0, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_TRUE(timestamp_is_less_equal(&t1, &t2));

    timestamp_init_from_sec_nsec(&t1, 1, 0);
    timestamp_init_from_sec_nsec(&t2, 1, 0);
    TEST_ASSERT_TRUE(timestamp_is_less_equal(&t1, &t2));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_to_sec(const struct Timestamp *timestamp, float64_t *sec);
 */
static void test_timestamp_to_sec(void)
{
    struct Timestamp t;
    float64_t        res;

    /* Zero */
    timestamp_init_from_sec_nsec(&t, 0, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, timestamp_to_sec(&t, &res));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res);

    /* Normal case */
    timestamp_init_from_sec_nsec(&t, 1, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, timestamp_to_sec(&t, &res));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, res);

    /* Max and min */
    timestamp_init_from_sec_nsec(&t, UINT32_MAX, 999999999);
    TEST_ASSERT_EQUAL(RC_SUCCESS, timestamp_to_sec(&t, &res));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, (float64_t)UINT32_MAX + 0.999999999, res);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_to_nsec(const struct Timestamp *timestamp, int64_t *res);
 */
static void test_timestamp_to_nsec(void)
{
    struct Timestamp t;
    int64_t          res;

    /* Zero */
    timestamp_init_from_sec_nsec(&t, 0, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, timestamp_to_nsec(&t, &res));
    TEST_ASSERT_EQUAL_UINT64(0, res);

    /* Normal case */
    timestamp_init_from_sec_nsec(&t, 1, 0);
    TEST_ASSERT_EQUAL(RC_SUCCESS, timestamp_to_nsec(&t, &res));
    TEST_ASSERT_EQUAL_UINT64(1000000000, res);
    timestamp_init_from_sec_nsec(&t, 1, 123456789);
    TEST_ASSERT_EQUAL(RC_SUCCESS, timestamp_to_nsec(&t, &res));
    TEST_ASSERT_EQUAL_UINT64(1123456789, res);

    /* Max and min */
    timestamp_init_from_sec_nsec(&t, UINT32_MAX, 999999999);
    TEST_ASSERT_EQUAL(RC_SUCCESS, timestamp_to_nsec(&t, &res));
    TEST_ASSERT_EQUAL_UINT64((uint64_t)UINT32_MAX * 1000000000 + 999999999, res);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test int32_t timestamp_get_sec(const struct Timestamp *timestamp);
 */
static void test_timestamp_get_sec(void)
{
    struct Timestamp t;

    /* Normal case */
    timestamp_init_from_sec_nsec(&t, 1, 0);
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));
    timestamp_init_from_sec_nsec(&t, 1, 100);
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(100, timestamp_get_nsec(&t));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test int32_t timestamp_get_nsec(const struct Timestamp *timestamp);
 */
static void test_timestamp_get_nsec(void)
{
    struct Timestamp t;

    /* Normal case */
    timestamp_init_from_sec_nsec(&t, 1, 0);
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));
    timestamp_init_from_sec_nsec(&t, 1, 100);
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(100, timestamp_get_nsec(&t));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_set_sec(struct Timestamp *timestamp, int32_t sec);
 */
static void test_timestamp_set_sec(void)
{
    struct Timestamp t;

    /* Normal case */
    timestamp_init_from_sec_nsec(&t, 0, 0);
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_set_sec(&t, 1));
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_set_sec(&t, UINT32_MAX));
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t timestamp_set_nsec(struct Timestamp *timestamp, int32_t nsec);
 */
static void test_timestamp_set_nsec(void)
{
    struct Timestamp t;

    /* Normal case */
    timestamp_init_from_sec_nsec(&t, 0, 0);
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_set_nsec(&t, 1));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_nsec(&t));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, timestamp_set_nsec(&t, 999999999));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(999999999, timestamp_get_nsec(&t));

    /* Invalid parameter */
    timestamp_init_from_sec_nsec(&t, 0, 0);
    TEST_ASSERT_EQUAL_INT32(RC_TIMESTAMP_INVALID_PARAMETER, timestamp_set_nsec(&t, 1000000000));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test uint32_t timestamp_get_serialized_size(const struct Timestamp *timestamp);
 */
static void test_timestamp_get_serialized_size(void)
{
    struct Timestamp t;

    TEST_ASSERT_EQUAL_UINT32(8, timestamp_get_serialized_size(&t));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test int32_t timestamp_serialize(const struct Timestamp *timestamp, uint8_t *buffer, uint32_t buffer_size);
 */
static void test_timestamp_serialize(void)
{
    uint8_t          buffer[8];
    struct Timestamp t;

    /* Zero */
    timestamp_init_from_sec_nsec(&t, 0, 0);
    TEST_ASSERT_EQUAL_INT32(8, timestamp_serialize(&t, buffer, 8));
    uint8_t expected1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected1, buffer, 8);

    /* Normal case */
    timestamp_init_from_sec_nsec(&t, 1, 0);
    TEST_ASSERT_EQUAL_INT32(8, timestamp_serialize(&t, buffer, 8));
    uint8_t expected2[8] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected2, buffer, 8);

    timestamp_init_from_sec_nsec(&t, UINT32_MAX, 999999999);
    TEST_ASSERT_EQUAL_INT32(8, timestamp_serialize(&t, buffer, 8));
    uint8_t expected3[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0x3B, 0x9A, 0xC9, 0xFF};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected3, buffer, 8);

    /* Overflow */
    timestamp_init_from_sec_nsec(&t, 1, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, timestamp_serialize(&t, buffer, 7));
}

static void test_timestamp_deserialize(void)
{
    uint8_t          buffer1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t          buffer2[8] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
    uint8_t          buffer3[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0x3B, 0x9A, 0xC9, 0xFF};
    struct Timestamp t;

    /* Zero */
    timestamp_init_from_sec_nsec(&t, 0, 0);
    TEST_ASSERT_EQUAL_INT32(8, timestamp_deserialize(&t, buffer1, 8));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));

    /* Normal case */
    TEST_ASSERT_EQUAL_INT32(8, timestamp_deserialize(&t, buffer2, 8));
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&t));
    TEST_ASSERT_EQUAL_INT32(8, timestamp_deserialize(&t, buffer3, 8));
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, timestamp_get_sec(&t));
    TEST_ASSERT_EQUAL_UINT32(999999999, timestamp_get_nsec(&t));

    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, timestamp_deserialize(&t, buffer2, 7));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_duration_init);
    RUN_TEST(test_duration_init_from_sec_nsec);
    RUN_TEST(test_duration_init_from_sec);
    RUN_TEST(test_duration_init_from_nsec);
    RUN_TEST(test_duration_init_from_duration);
    RUN_TEST(test_duration_add);
    RUN_TEST(test_duration_sub);
    RUN_TEST(test_duration_multiply_int32);
    RUN_TEST(test_duration_divide_int32);
    RUN_TEST(test_duration_multiply_float64);
    RUN_TEST(test_duration_is_zero);
    RUN_TEST(test_duration_is_greater);
    RUN_TEST(test_duration_is_equal);
    RUN_TEST(test_duration_is_less);
    RUN_TEST(test_duration_is_greater_equal);
    RUN_TEST(test_duration_is_less_equal);
    RUN_TEST(test_duration_to_sec);
    RUN_TEST(test_duration_to_nsec);
    RUN_TEST(test_duration_get_sec);
    RUN_TEST(test_duration_get_nsec);
    RUN_TEST(test_duration_set_sec);
    RUN_TEST(test_duration_set_nsec);
    RUN_TEST(test_duration_get_serialized_size);
    RUN_TEST(test_duration_serialize);
    RUN_TEST(test_duration_deserialize);

    RUN_TEST(test_timestamp_init);
    RUN_TEST(test_timestamp_init_from_sec_nsec);
    RUN_TEST(test_timestamp_init_from_sec);
    RUN_TEST(test_timestamp_init_from_nsec);
    RUN_TEST(test_timestamp_init_from_timestamp);
    RUN_TEST(test_timestamp_add_duration);
    RUN_TEST(test_timestamp_sub_duration);
    RUN_TEST(test_timestamp_sub);
    RUN_TEST(test_timestamp_is_zero);
    RUN_TEST(test_timestamp_is_greater);
    RUN_TEST(test_timestamp_is_equal);
    RUN_TEST(test_timestamp_is_less);
    RUN_TEST(test_timestamp_is_greater_equal);
    RUN_TEST(test_timestamp_is_less_equal);
    RUN_TEST(test_timestamp_to_sec);
    RUN_TEST(test_timestamp_to_nsec);
    RUN_TEST(test_timestamp_get_sec);
    RUN_TEST(test_timestamp_get_nsec);
    RUN_TEST(test_timestamp_set_sec);
    RUN_TEST(test_timestamp_set_nsec);
    RUN_TEST(test_timestamp_get_serialized_size);
    RUN_TEST(test_timestamp_serialize);
    RUN_TEST(test_timestamp_deserialize);
    return UNITY_END();
}
