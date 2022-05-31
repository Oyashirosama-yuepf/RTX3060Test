/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file types.h
 * @brief types.h
 * @author wanghaiyang@holomatic.com
 * @date "2021-03-18"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_COMMON_TYPES_H_
#define HOLO_MAP_SERVICE_CLIENT_COMMON_TYPES_H_

#include <holo/core/types.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace common
{
/**
 * @addtogroup common
 * @{
 *
 */

/// Define index type.
using IndexType = std::size_t;

/// Define distance with unit of meter.
using DistanceMeterType = holo::float64_t;

/// Define distance type with unit of centermeter.
using DistanceCentermeterType = holo::int64_t;

/**
 * @}
 */
} ///< namespace common
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_COMMON_TYPES_H_ */