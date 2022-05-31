/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file odometry.h
 * @brief This header file define generic odometry measurement
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date Sep 02, 2019
 */

#ifndef HOLO_COMMON_ODOMETRY_H_
#define HOLO_COMMON_ODOMETRY_H_

#include <holo/common/details/odometry.h>
#include <holo/core/types.h>

namespace holo
{
namespace common
{
template <typename ScalarType>
using OdometryT = holo::common::details::OdometryT<ScalarType>;

using Odometryd = holo::common::details::OdometryT<holo::float64_t>;
using Odometryf = holo::common::details::OdometryT<holo::float32_t>;

template <typename ScalarType, size_t SIZE_VALUE>
using LocalMapOdometryT = holo::common::details::LocalMapOdometryT<ScalarType, SIZE_VALUE>;
using LocalMapOdometryd = holo::common::details::LocalMapOdometryT<holo::float64_t, 16U>;
using LocalMapOdometryf = holo::common::details::LocalMapOdometryT<holo::float32_t, 16U>;

template <typename ScalarType>
using DrOdometryT = holo::common::details::DrOdometryT<ScalarType>;

using DrOdometryd = holo::common::details::DrOdometryT<holo::float64_t>;
using DrOdometryf = holo::common::details::DrOdometryT<holo::float32_t>;

using OdometryPrecision = holo::common::details::OdometryPrecision;

}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_ODOMETRY_H_ */
