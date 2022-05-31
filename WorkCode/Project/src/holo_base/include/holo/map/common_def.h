/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_def.h
 * @brief common types.
 * @author zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#ifndef HOLO_BASE_INCLUDE_HOLO_MAP_COMMON_DEF_H_
#define HOLO_BASE_INCLUDE_HOLO_MAP_COMMON_DEF_H_

#include <holo/core/types.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @deprecated Use KeyType instead
 * @brief Map element key type
 */
[[deprecated]] typedef ::holo::uint64_t KeyValue;

/**
 * @brief Map element key type
 */
using KeyType = ::holo::uint64_t;

/**
 * @deprecated Use SeqValueType instead
 * @brief Map sequence value type
 */
[[deprecated]] typedef ::holo::int8_t SeqValue;

/**
 * @brief Map sequence value type
 */
using SeqValueType = ::holo::int8_t;

/**
 * @}
 *
 */
}  // namespace map
}  // namespace holo
#endif  // HOLO_BASE_INCLUDE_HOLO_MAP_COMMON_DEF_H_
