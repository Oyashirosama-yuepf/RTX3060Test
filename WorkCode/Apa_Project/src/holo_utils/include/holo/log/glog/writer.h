/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file writer.h
 * @brief This header defines the StreamWriter/NullWriter class
 * @author moxiao@holomatic.com
 * @date 2021-09-06
 */

#ifndef HOLO_LOG_GLOG_WRITER_H_
#define HOLO_LOG_GLOG_WRITER_H_

#include <glog/logging.h>
#include <holo/core/types.h>

namespace holo
{
namespace log
{
namespace glog
{
using StreamWriter = ::google::LogMessage;
using NullWriter   = ::google::NullStream;
}  // namespace glog

}  // namespace log

}  // namespace holo

#endif
