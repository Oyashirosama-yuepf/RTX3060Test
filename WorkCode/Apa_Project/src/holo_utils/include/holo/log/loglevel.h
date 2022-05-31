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

#ifndef HOLO_LOG_LOG_LEVEL_H_
#define HOLO_LOG_LOG_LEVEL_H_

#include <holo/core/types.h>
#include <functional>

#include <holo/log/common.h>

#if defined(HOLO_LOG_TYPE) && (HOLO_LOG_TYPE == HOLO_LOG_TYPE_GLOG)
#include <holo/log/glog/loglevel.h>
#else
#include <holo/log/log4cplus/loglevel.h>
#endif

namespace holo
{
namespace log
{
#if defined(HOLO_LOG_TYPE) && (HOLO_LOG_TYPE == HOLO_LOG_TYPE_GLOG)
using LogLevel = ::holo::log::glog::LogLevel;
#else
using LogLevel = ::holo::log::log4cplus::LogLevel;
#endif

}  // namespace log

}  // namespace holo

namespace std
{
template <>
struct hash<::holo::log::LogLevel>
{
    using result_type   = std::size_t;
    using argument_type = ::holo::log::LogLevel;

    result_type operator()(argument_type const& level) const
    {
        return static_cast<result_type>(level);
    }
};

}  // namespace std

#endif
