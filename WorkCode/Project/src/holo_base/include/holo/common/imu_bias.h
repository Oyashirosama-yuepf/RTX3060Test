/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_bias.h
 * @brief This header file define the bias of imu sensor
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-06
 */

#ifndef HOLO_COMMON_IMU_BIAS_H_
#define HOLO_COMMON_IMU_BIAS_H_

#include <holo/common/details/imu_bias.h>

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
 * @brief This class contains the bias for imu gyro and linear acceleration
 */
template <typename T>
using ImuBiasT = details::ImuBiasT<T>;

 /**
 * @brief This class contains the bias for imu gyro and linear acceleration with accuracy of float32_t
 */
using ImuBiasf =  details::ImuBiasT<float32_t>;

 /**
 * @brief This class contains the bias for imu gyro and linear acceleration with accuracy of float64_t
 */
using ImuBiasd =  details::ImuBiasT<float64_t>;

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
 * @brief This class contains the bias for imu gyro and linear acceleration
 *
 * @deprecated holo::ImuBiasT replaced by holo::common::ImuBiasT
 */
template <typename T>
using ImuBiasT[[deprecated]] = common::ImuBiasT<T>;

/**
 * @brief This class contains the bias for imu gyro and linear acceleration with accuracy of float32_t
 *
 * @deprecated holo::ImuBiasf replaced by holo::common::ImuBiasf
 */
using ImuBiasf[[deprecated]] = common::ImuBiasT<float32_t>;

/**
 * @brief This class contains the bias for imu gyro and linear acceleration with accuracy of float64_t
 *
 * @deprecated holo::ImuBiasd replaced by holo::common::ImuBiasd
 */
using ImuBiasd[[deprecated]] = common::ImuBiasT<float64_t>;

 /**
 * @}
 *
 */
}  // namespace holo

#endif /* HOLO_COMMON_IMU_BIAS_H_ */
