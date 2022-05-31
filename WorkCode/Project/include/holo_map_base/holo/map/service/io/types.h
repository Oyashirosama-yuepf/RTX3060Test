/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file types.h
 * @brief Define common types for map local service.
 * @author wanghaiyang@holomatic.com
 * @date "2020-12-24"
 */

#ifndef HOLO_MAP_SERVICE_IO_TYPES_H_
#define HOLO_MAP_SERVICE_IO_TYPES_H_

#include <holo/core/types.h>
#include <holo/map/service/io/data_package.h>

namespace holo
{
namespace map
{
namespace service
{
namespace io
{

/**
 * @addtogroup session
 * @{
 *
 */

/// Max data buffer size, map data must not larger than this value.
static std::size_t constexpr FIX_SIZE_VALUE = 1024*10;

/// Redefine data package type for map local server, the capacity should same with FIX_SIZE_VALUE.
using FixDataPackageType = holo::map::service::io::DataPackage<FIX_SIZE_VALUE>;

/// Redefine fix buffer type for map local server, the capacity should same with FIX_SIZE_VALUE.
using FixBufferType = holo::container::Vector<holo::uint8_t, FIX_SIZE_VALUE>;

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_TYPES_H_ */