/**
 * @file path.h
 * @brief This is used to define the path
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-10-21
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_COMMON_PATH_H_
#define HOLO_COMMON_PATH_H_

#include "details/path.h"

namespace holo
{
namespace common
{

template <typename T>
using PathPointT = details::PathPointT<T>;

template <typename T>
using PathT = details::PathT<T>;

using PathPointf = details::PathPointT<float32_t>;
using PathPointd = details::PathPointT<float64_t>;
using PathPoint = PathPointd;

using Pathf = details::PathT<float32_t>;
using Pathd = details::PathT<float64_t>;
using Path = Pathd;

}  

template <typename T>
using PathPointT[[deprecated]]  = common::PathPointT<T>;

template <typename T>
using PathT[[deprecated]]  = common::PathT<T>;

using PathPointf[[deprecated]] = common::PathPointf;
using PathPointd[[deprecated]] = common::PathPointd;
using PathPoint[[deprecated]] = common::PathPoint;

using Pathf[[deprecated]] = common::Pathf;
using Pathd[[deprecated]] = common::Pathd;
using Path[[deprecated]] = common::Path;

}  

#endif
