/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file timestamp.h
 * @brief This header file defines Timestamp class and Duration Class
 * @author lichao@holomatic.com
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-03
 */

#ifndef HOLO_CORE_TIMESTAMP_H_
#define HOLO_CORE_TIMESTAMP_H_

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>

#include <holo/core/types.h>
#include "details/timestamp.h"

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
 * @brief This class represents a period of time
 */
using Duration = details::Duration;

/**
 * @brief This class represents a time point in nanosecond precision
 */
using Timestamp = details::Timestamp;

/**
 * @brief This class represents a overflow exception
 */
using OverflowException = details::OverflowException;

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
 * @brief This class represents a period of time.
 *
 * @deprecated holo::Duration replaced by holo::common::Duration
 */
using Duration[[deprecated]] = common::Duration;

/**
 * @brief This class represents a time point in nanosecond precision
 *
 * @deprecated holo::Timestamp replaced by holo::common::Timestamp
 */
using Timestamp[[deprecated]] = common::Timestamp;

/**
 * @}
 *
 */

}  // namespace holo

#endif /* HOLO_CORE_TIMESTAMP_H_ */
