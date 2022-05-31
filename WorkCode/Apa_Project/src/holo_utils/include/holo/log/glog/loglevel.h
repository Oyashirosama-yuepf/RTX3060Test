/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file loglevel.h
 * @brief This header defines Log Level
 * @author moxiao@holomatic.com
 * @date 2021-09-07
 */

#ifndef HOLO_LOG_GLOG_LOG_LEVEL_H_
#define HOLO_LOG_GLOG_LOG_LEVEL_H_

#include <holo/core/types.h>
#include <functional>

namespace holo
{
namespace log
{
namespace glog
{
/**
 * @brief Log Level class enum
 */
enum class LogLevel : holo::uint32_t
{
    ALL     = 0U,
    TRACE   = 0U,
    DEBUG   = 0U,
    INFO    = 0U,
    WARNING = 1U,
    ERROR   = 2U,
    FATAL   = 3U,
    OFF     = 4U,
};

}  // namespace glog

}  // namespace log

}  // namespace holo

#endif
