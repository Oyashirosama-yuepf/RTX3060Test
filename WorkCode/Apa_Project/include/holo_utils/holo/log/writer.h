/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file writer.h
 * @brief This header defines the StreamWriter/NullWriter
 * @author moxiao@holomatic.com
 * @date 2021-09-07
 */

#ifndef HOLO_LOG_WRITER_H_
#define HOLO_LOG_WRITER_H_

#include <holo/core/types.h>
#include <functional>

#include <holo/log/common.h>

#if defined(HOLO_LOG_TYPE) && (HOLO_LOG_TYPE == HOLO_LOG_TYPE_GLOG)
#include <holo/log/glog/writer.h>
#else
#include <holo/log/log4cplus/writer.h>
#endif

namespace holo
{
namespace log
{
#if defined(HOLO_LOG_TYPE) && (HOLO_LOG_TYPE == HOLO_LOG_TYPE_GLOG)
using StreamWriter = ::holo::log::glog::StreamWriter;
using NullWriter   = ::holo::log::glog::NullWriter;
#else
using StreamWriter = ::holo::log::log4cplus::StreamWriter;
using NullWriter   = ::holo::log::log4cplus::NullWriter;
#endif

}  // namespace log

}  // namespace holo

#endif
