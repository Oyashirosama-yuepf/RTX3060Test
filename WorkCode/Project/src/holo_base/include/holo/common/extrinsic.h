/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file extrinsic.h
 * @brief A class to held extrinsic parameters between coordinates (sensors)
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-13
 */

#ifndef HOLO_COMMON_EXTRINSIC_H_
#define HOLO_COMMON_EXTRINSIC_H_

#include <holo/common/details/extrinsic.h>

namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 *
 */

template <typename T>
using ExtrinsicT = details::ExtrinsicT<T>;

using Extrinsicf = details::ExtrinsicT<float32_t>;

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

template <typename T>
using ExtrinsicT[[deprecated]] = common::ExtrinsicT<T>;

using Extrinsicf[[deprecated]] = common::ExtrinsicT<float32_t>;


/**
 * @}
 *
 */

}  // namespace holo

#endif /* HOLO_COMMON_EXTRINSIC_H_ */
