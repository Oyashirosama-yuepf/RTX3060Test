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

#ifndef HOLO_LOG_LOG4CPLUS_LOG_LEVEL_H_
#define HOLO_LOG_LOG4CPLUS_LOG_LEVEL_H_

#include <holo/core/types.h>
#include <functional>

namespace holo
{
namespace log
{
namespace log4cplus
{
/**
 * @brief Log Level class enum
 */
enum class LogLevel : holo::uint32_t
{
    ALL     = 0U,
    TRACE   = 0U,
    DEBUG   = 10000U,
    INFO    = 20000U,
    WARNING = 30000U,
    ERROR   = 40000U,
    FATAL   = 50000U,
    OFF     = 60000U,
};

}  // namespace log4cplus

}  // namespace log

}  // namespace holo

#endif
