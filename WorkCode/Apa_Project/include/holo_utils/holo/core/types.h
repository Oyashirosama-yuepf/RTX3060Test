/**
 *  @brief This header file defines basic data types
 *  @author zhangjiannan(zhangjiannan@holomaitc.ai)
 *  @date 2019-8-27
 *  @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 *  @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_CORE_TYPES_H_
#define HOLO_CORE_TYPES_H_

#include <stdint.h>

namespace holo
{
using float32_t = float;
using float64_t = double;
using int8_t = ::int8_t;
using int16_t = ::int16_t;
using int32_t = ::int32_t;
using int64_t = ::int64_t;
using uint8_t = ::uint8_t;
using uint16_t = ::uint16_t;
using uint32_t = ::uint32_t;
using uint64_t = ::uint64_t;
using bool_t = bool;
using char_t = char;
}  // namespace holo

static_assert(1 == sizeof(holo::uint8_t), "sizeof holo::uint8_t != 1");
static_assert(1 == sizeof(holo::int8_t), "sizeof holo::int8_t != 1");
static_assert(2 == sizeof(holo::uint16_t), "sizeof holo::uint16_t != 2");
static_assert(2 == sizeof(holo::int16_t), "sizeof holo::int16_t != 2");
static_assert(4 == sizeof(holo::uint32_t), "sizeof holo::uint32_t != 4");
static_assert(4 == sizeof(holo::int32_t), "sizeof holo::int32_t != 4");
static_assert(8 == sizeof(holo::uint64_t), "sizeof holo::uint64_t != 8");
static_assert(8 == sizeof(holo::int64_t), "sizeof holo::int64_t != 8");
static_assert(4 == sizeof(holo::float32_t), "sizeof holo::float32_t != 4");
static_assert(8 == sizeof(holo::float64_t), "sizeof holo::float64_t != 8");
static_assert(1 == sizeof(holo::bool_t), "sizeof holo::bool_t != 4");
static_assert(1 == sizeof(holo::char_t), "sizeof holo::char_t != 8");

#endif
