/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common.h
 * @brief common.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-08"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_COMMON_UTILITY_H_
#define HOLO_MAP_SERVICE_CLIENT_COMMON_UTILITY_H_

#include <string>
#include <sstream>
#include <vector>

#include <holo/geometry/point3.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace common
{
namespace utility
{

template <typename T>
std::string FormatToString(holo::geometry::Point3T<T> const p)
{
    (void)p;
    return "";
}

template <typename T, typename Function, typename Container = std::vector<T>>
std::string FormatSequenceToString(Container const c, Function f)
{
    std::stringstream stream;
    stream << "[";

    std::size_t const count = c.size();
    for (std::size_t i = 0; i < count; ++i)
    {
        std::string const end = (i+1) < count ? "," : "";
        stream << f(c[i]) << end;
    }

    stream << "]";
    return stream.str();
}


} ///< namespace utility
} ///< namespace common
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_COMMON_UTILITY_H_ */