/*!
 * @file endian.h
 * @brief This header file provider functions/macros for byte swap and host/network byte order convertion..
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2018-12-23
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_OS_ENDIAN_H_
#define HOLO_OS_ENDIAN_H_

#include <stdint.h>

namespace holo
{

namespace os
{

#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)
#if (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) ||                                             \
    (defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN) || (defined(_BYTE_ORDER) && _BYTE_ORDER == _BIG_ENDIAN) || \
    (defined(BYTE_ORDER) && BYTE_ORDER == BIG_ENDIAN) ||                                                               \
    (defined(__sun) && defined(__SVR4) && defined(_BIG_ENDIAN)) || defined(__ARMEB__) || defined(__THUMBEB__) ||       \
    defined(__AARCH64EB__) || defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__) || defined(_M_PPC)
/**
 * @def HOLO_PLATFORM_BIG_ENDIAN
 * @brief This macro will be defined if target platform is big endian.
 */
#define HOLO_PLATFORM_BIG_ENDIAN
#elif (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || /* gcc */                              \
    (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN) /* linux header */ ||                                   \
    (defined(_BYTE_ORDER) && _BYTE_ORDER == _LITTLE_ENDIAN) ||                                                         \
    (defined(BYTE_ORDER) && BYTE_ORDER == LITTLE_ENDIAN) /* mingw header */ ||                                         \
    (defined(__sun) && defined(__SVR4) && defined(_LITTLE_ENDIAN)) || /* solaris */                                    \
    defined(__ARMEL__) || defined(__THUMBEL__) || defined(__AARCH64EL__) || defined(_MIPSEL) || defined(__MIPSEL) ||   \
    defined(__MIPSEL__) || defined(_M_IX86) || defined(_M_X64) || defined(_M_IA64) || /* msvc for intel processors */  \
    defined(_M_ARM) /* msvc code on arm executes in little endian mode */
/**
 * @def HOLO_PLATFORM_LITTLE_ENDIAN
 * @brief This macro will be defined if target platform is little endian.
 */
#define HOLO_PLATFORM_LITTLE_ENDIAN
#endif
#endif

#if defined(bswap16) || defined(bswap32) || defined(bswap64)
#error "unexpected define!" // freebsd may define these; probably just need to undefine them
#endif

/* Define byte-swap functions, using fast processor-native built-ins where possible */
/**
 * @fn uint16_t bswap16(uint16_t x)
 * @brief Byte swap for 16 bit data. 0x1234 --> 0x3412.
 * @param x data.
 * @return Byte order swapped data.
 *
 * @fn uint32_t bswap32(uint32_t x)
 * @brief Byte swap for 32 bit data. 0x12345678 --> 0x78563412.
 * @param x data.
 * @return Byte order swapped data.
 *
 * @fn uint64_t bswap64(uint64_t x)
 * @brief Byte swap for 64 bit data. 0x123456789abcdef0 --> 0xf0debc0a78563412
 * @param x data.
 * @return Byte order swapped data.
 */
#if defined(_MSC_VER)  // needs to be first because msvc doesn't short-circuit after failing defined(__has_builtin)
static inline uint16_t bswap16(uint16_t x)
{
    return _byteswap_ushort(x);
}

static inline uint32_t bswap32(uint32_t x)
{
    return _byteswap_ulong(x);
}

static inline uint64_t bswap64(uint64_t x)
{
    return _byteswap_uint64(x);
}
#elif (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
static inline uint16_t bswap16(uint16_t x)
{
    return __builtin_bswap16(x);
}

static inline uint32_t bswap32(uint32_t x)
{
    return __builtin_bswap32(x);
}

static inline uint64_t bswap64(uint64_t x)
{
    return __builtin_bswap64(x);
}
/* for clang; gcc 5 fails on this and && shortcircuit fails; must be after GCC check */
#elif defined(__has_builtin) && __has_builtin(__builtin_bswap64)
static inline uint16_t bswap16(uint16_t x)
{
    return __builtin_bswap16(x);
}

static inline uint32_t bswap32(uint32_t x)
{
    return __builtin_bswap32(x);
}

static inline uint64_t bswap64(uint64_t x)
{
    return __builtin_bswap64(x);
}
#else
/* even in this case, compilers often optimize by using native instructions */
static inline uint16_t bswap16(uint16_t x)
{
    return (((x >> 8) & 0xffu) | ((x & 0xffu) << 8));
}

static inline uint32_t bswap32(uint32_t x)
{
    return (((x & 0xff000000u) >> 24) | ((x & 0x00ff0000u) >> 8) | ((x & 0x0000ff00u) << 8) |
            ((x & 0x000000ffu) << 24));
}

static inline uint64_t bswap64(uint64_t x)
{
    return (((x & 0xff00000000000000ull) >> 56) | ((x & 0x00ff000000000000ull) >> 40) |
            ((x & 0x0000ff0000000000ull) >> 24) | ((x & 0x000000ff00000000ull) >> 8) |
            ((x & 0x00000000ff000000ull) << 8) | ((x & 0x0000000000ff0000ull) << 24) |
            ((x & 0x000000000000ff00ull) << 40) | ((x & 0x00000000000000ffull) << 56));
}
#endif

/* Defines network - host byte swaps as needed depending upon platform endianness */
/* note that network order is big endian) */
/**
 * @fn uint16_t ntoh16(uint16_t x)
 * @brief Convert 16 bit network byte order data to host byte order.
 * @param x data.
 * @return Host byte order data
 *
 * @fn uint16_t hton16(uint16_t x)
 * @brief Convert 16 bit host byte order data to network byte order.
 * @param x data.
 * @return Network byte order data
 *
 * @fn uint32_t ntoh32(uint32_t x)
 * @brief Convert 32 bit network byte order data to host byte order.
 * @param x data.
 * @return Host byte order data
 *
 * @fn uint32_t hton32(uint32_t x)
 * @brief Convert 32 bit host byte order data to network byte order.
 * @param x data.
 * @return Network byte order data
 *
 * @fn uint64_t ntoh64(uint64_t x)
 * @brief Convert 64 bit network byte order data to host byte order.
 * @param x data.
 * @return Host byte order data
 *
 * @fn uint64_t hton64(uint64_t x)
 * @brief Convert 64 bit host byte order data to network byte order.
 * @param x data.
 * @return Network byte order data
 *
 */

#if defined(HOLO_PLATFORM_LITTLE_ENDIAN)
static inline uint16_t ntoh16(uint16_t x)
{
    return bswap16(x);
}

static inline uint16_t hton16(uint16_t x)
{
    return bswap16(x);
}

static inline uint32_t ntoh32(uint32_t x)
{
    return bswap32(x);
}

static inline uint32_t hton32(uint32_t x)
{
    return bswap32(x);
}

static inline uint64_t ntoh64(uint64_t x)
{
    return bswap64(x);
}

static inline uint64_t hton64(uint64_t x)
{
    return bswap64(x);
}
#elif defined(HOLO_PLATFORM_BIG_ENDIAN)
static inline uint16_t ntoh16(uint16_t x)
{
    return x;
}

static inline uint16_t hton16(uint16_t x)
{
    return x;
}

static inline uint32_t ntoh32(uint32_t x)
{
    return x;
}

static inline uint32_t hton32(uint32_t x)
{
    return x;
}

static inline uint64_t ntoh64(uint64_t x)
{
    return x;
}

static inline uint64_t hton64(uint64_t x)
{
    return x;
}
#else
#error "UNKNOWN Platform / endianness; network / host byte swaps not defined."
#endif


} /* namespace os */

} /* namespace holo */

#endif /* HOLO_OS_ENDIAN_H_ */
