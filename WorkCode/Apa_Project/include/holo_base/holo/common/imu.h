/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu.h
 * @brief This header file define the measurement of inertial measurement unit
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-10
 */

#ifndef HOLO_COMMON_IMU_H_
#define HOLO_COMMON_IMU_H_

#include <holo/common/details/imu.h>

namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 *
 */

 /**
 * @brief This class represents measurement of inertial measurement unit
 */
template <typename T>
using ImuT = details::ImuT<T>;

 /**
 * @brief This class represents measurement of inertial measurement unit with accuracy of float32_t
 */
using Imuf = details::ImuT<float32_t>;

 /**
 * @brief This class represents measurement of inertial measurement unit with accuracy of float64_t
 */
using Imud = details::ImuT<float64_t>;

/**
 * @}
 *
 */
}  // namespace common

/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief This class represents measurement of inertial measurement unit
 *
 * @deprecated holo::ImuT replaced by holo::common::ImuT
 */
template <typename T>
using ImuT[[deprecated]] = common::ImuT<T>;

/**
 * @brief This class represents measurement of inertial measurement unit with accuracy of float32_t
 *
 * @deprecated holo::Imuf replaced by holo::common::Imuf
 */
using Imuf[[deprecated]] = common::ImuT<float32_t>;

/**
 * @brief This class represents measurement of inertial measurement unit with accuracy of float64_t
 *
 * @deprecated holo::Imud replaced by holo::common::Imud
 */
using Imud[[deprecated]] = common::ImuT<float64_t>;

/**
 * @}
 *
 */
 
}  // namespace holo

#endif /* HOLO_COMMON_IMU_H_ */
