/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file BaseTypedefs.h
 * @brief This header file defines base data element and typedef of all adasis
 * v3 enums.
 * @author zhengshulei@holomatic.com
 * @date 2021-09-28
 */
#ifndef HOLO_MAP_ADASIS_V3_BASETYPEDEFS_H_
#define HOLO_MAP_ADASIS_V3_BASETYPEDEFS_H_

#include <holo/core/types.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace map
{
namespace adasis
{
namespace v3_1_1
{
#define VERSION_MAJOR 1
#define VERSION_MINOR 0

using Angle            = holo::float32_t;
using Distance         = holo::uint32_t;
using InstanceId       = holo::uint32_t;
using LaneIdx          = holo::uint8_t;
using LinearObjId      = holo::uint32_t;
using Offset           = holo::uint32_t;
using PathId           = holo::uint32_t;
using Probability      = holo::float32_t;
using SignLocationMask = holo::uint16_t;
using Timestamp        = holo::uint64_t;
using VehicleSpeed     = holo::float32_t;

} // namespace v3_1_1
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_V3_BASETYPEDEFS_H_ */