/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file format_marshal.hpp
 * @brief map format to json string. 
 * @author hulingjia(hulingjia@holomaitc.com)
 * @date 2022-04-13
 */

#ifndef HOLO_MAP_COMMON_FORMAT_MARSHAL_HPP_
#define HOLO_MAP_COMMON_FORMAT_MARSHAL_HPP_

#include <string>

#include <holo/map/format/base/road.h>

namespace holo
{
namespace map
{
namespace format
{
namespace marshal
{

/**
 * @brief Format holo::map::format::Base::FeatureType to json string.
 * @param [in] type holo::map::format::Base::FeatureType.
 * @return Json string.
 */
std::string FormatToString(holo::map::format::Base::FeatureType const type);

} // namespace marshal
} // namespace format
} // namespace map
} // namespace holo

#endif //HOLO_MAP_COMMON_FORMAT_MARSHAL_HPP_
