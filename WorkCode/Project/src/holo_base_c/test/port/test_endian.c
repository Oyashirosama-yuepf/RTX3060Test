/*!
 * \brief unit test of endian
 * \author zhangjiannan@holomatic.com
 * \date 2019-08-23
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/port/endian.h>

static void test_bswap16(void)
{
    uint16_t in, out;

    /* Zero */
    in  = 0U;
    out = bswap16(in);
    TEST_ASSERT_EQUAL_UINT16(0U, out);

    /* Normal case */
    in  = 0x1234U;
    out = bswap16(in);
    TEST_ASSERT_EQUAL_UINT16(0x3412U, out);

    /* Max */
    in  = 0xffffU;
    out = bswap16(in);
    TEST_ASSERT_EQUAL_UINT16(0xffffU, out);
}

static void test_bswap32(void)
{
    uint32_t in, out;

    /* Zero */
    in  = 0U;
    out = bswap32(in);
    TEST_ASSERT_EQUAL_UINT32(0U, out);

    /* Normal case */
    in  = 0x12345678U;
    out = bswap32(in);
    TEST_ASSERT_EQUAL_UINT32(0x78563412U, out);

    /* Max */
    in  = 0xffffffffU;
    out = bswap32(in);
    TEST_ASSERT_EQUAL_UINT32(0xffffffffU, out);
}

static void test_bswap64(void)
{
    uint64_t in, out;

    /* Zero */
    in  = 0UL;
    out = bswap64(in);
    TEST_ASSERT_EQUAL_UINT64(0U, out);

    /* Normal case */
    in  = 0x123456789abcdef0UL;
    out = bswap64(in);
    TEST_ASSERT_EQUAL_UINT64(0xf0debc9a78563412UL, out);

    /* Max */
    in  = 0xffffffffffffffffUL;
    out = bswap64(in);
    TEST_ASSERT_EQUAL_UINT64(0xffffffffffffffffUL, out);
}

static void test_hton16_ntoh16(void)
{
    uint16_t in;

#if defined(HOLO_PLATFORM_LITTLE_ENDIAN)
    /* Zero */
    in = 0U;
    TEST_ASSERT_EQUAL_UINT16(0U, hton16(in));
    in = hton16(in);
    TEST_ASSERT_EQUAL_UINT16(0U, ntoh16(in));

    /* Normal case */
    in = 0x1234U;
    TEST_ASSERT_EQUAL_UINT16(0x3412U, hton16(in));
    in = hton16(in);
    TEST_ASSERT_EQUAL_UINT16(0x1234U, ntoh16(in));

    /* Max */
    in = 0xffffU;
    TEST_ASSERT_EQUAL_UINT16(0xffffU, hton16(in));
    in = hton16(in);
    TEST_ASSERT_EQUAL_UINT16(0xffffU, ntoh16(in));
#endif
#if defined(HOLO_PLATFORM_BIG_ENDIAN)
    /* Zero */
    in = 0U;
    TEST_ASSERT_EQUAL_UINT16(0U, hton16(in));
    in = hton16(in);
    TEST_ASSERT_EQUAL_UINT16(0U, ntoh16(in));

    /* Normal case */
    in = 0x1234U;
    TEST_ASSERT_EQUAL_UINT16(0x1234U, hton16(in));
    in = hton16(in);
    TEST_ASSERT_EQUAL_UINT16(0x1234U, ntoh16(in));

    /* Max */
    in = 0xffffU;
    TEST_ASSERT_EQUAL_UINT16(0xffffU, hton16(in));
    in = hton16(in);
    TEST_ASSERT_EQUAL_UINT16(0xffffU, ntoh16(in));
#endif
}

static void test_hton32_ntoh32(void)
{
    uint32_t in;

#if defined(HOLO_PLATFORM_LITTLE_ENDIAN)
    /* Zero */
    in = 0U;
    TEST_ASSERT_EQUAL_UINT32(0U, hton32(in));
    in = hton32(in);
    TEST_ASSERT_EQUAL_UINT32(0U, ntoh32(in));

    /* Normal case */
    in = 0x12345678U;
    TEST_ASSERT_EQUAL_UINT32(0x78563412U, hton32(in));
    in = hton32(in);
    TEST_ASSERT_EQUAL_UINT32(0x12345678U, ntoh32(in));

    /* Max */
    in = 0xffffffffU;
    TEST_ASSERT_EQUAL_UINT32(0xffffffffU, hton32(in));
    in = hton32(in);
    TEST_ASSERT_EQUAL_UINT32(0xffffffffU, ntoh32(in));
#endif
#if defined(HOLO_PLATFORM_BIG_ENDIAN)
    /* Zero */
    in = 0U;
    TEST_ASSERT_EQUAL_UINT32(0U, hton32(in));
    in = hton32(in);
    TEST_ASSERT_EQUAL_UINT32(0U, ntoh32(in));

    /* Normal case */
    in = 0x12345678U;
    TEST_ASSERT_EQUAL_UINT32(0x12345678U, hton32(in));
    in = hton32(in);
    TEST_ASSERT_EQUAL_UINT32(0x12345678U, ntoh32(in));

    /* Max */
    in = 0xffffffffU;
    TEST_ASSERT_EQUAL_UINT32(0xffffffffU, hton32(in));
    in = hton32(in);
    TEST_ASSERT_EQUAL_UINT32(0xffffffffU, ntoh32(in));
#endif
}

static void test_hton64_ntoh64(void)
{
    uint64_t in;

#if defined(HOLO_PLATFORM_LITTLE_ENDIAN)
    /* Zero */
    in = 0UL;
    TEST_ASSERT_EQUAL_UINT64(0UL, hton64(in));
    in = hton64(in);
    TEST_ASSERT_EQUAL_UINT64(0UL, ntoh64(in));

    /* Normal case */
    in = 0x123456789abcdef0UL;
    TEST_ASSERT_EQUAL_UINT64(0xf0debc9a78563412U, hton64(in));
    in = hton64(in);
    TEST_ASSERT_EQUAL_UINT64(0x123456789abcdef0U, ntoh64(in));

    /* Max */
    in = 0xffffffffffffffffUL;
    TEST_ASSERT_EQUAL_UINT64(0xffffffffffffffffUL, hton64(in));
    in = hton64(in);
    TEST_ASSERT_EQUAL_UINT64(0xffffffffffffffffUL, ntoh64(in));
#endif
#if defined(HOLO_PLATFORM_BIG_ENDIAN)
    /* Zero */
    in = 0UL;
    TEST_ASSERT_EQUAL_UINT64(0UL, hton64(in));
    in = hton64(in);
    TEST_ASSERT_EQUAL_UINT64(0UL, ntoh64(in));

    /* Normal case */
    in = 0x123456789abcdef0UL;
    TEST_ASSERT_EQUAL_UINT64(0x123456789abcdef0UL, hton64(in));
    in = hton64(in);
    TEST_ASSERT_EQUAL_UINT64(0x123456789abcdef0UL, ntoh64(in));

    /* Max */
    in = 0xffffffffffffffffUL;
    TEST_ASSERT_EQUAL_UINT64(0xffffffffffffffffUL, hton64(in));
    in = hton64(in);
    TEST_ASSERT_EQUAL_UINT64(0xffffffffffffffffUL, ntoh64(in));
#endif
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_bswap16);
    RUN_TEST(test_bswap32);
    RUN_TEST(test_bswap64);
    RUN_TEST(test_hton16_ntoh16);
    RUN_TEST(test_hton32_ntoh32);
    RUN_TEST(test_hton64_ntoh64);
    return UNITY_END();
}
