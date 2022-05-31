/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file freespace.h
 * @brief This header file defines freespace object
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-21
 */

#ifndef HOLO_COMMON_FREESPACE_H_
#define HOLO_COMMON_FREESPACE_H_

#include "details/freespace.h"

namespace holo
{
namespace common
{
template <typename Point, size_t POINT_SIZE, size_t INTERIOR_SIZE>
using FreespaceExterior = details::FreespaceExteriorPolygon<Point, POINT_SIZE, INTERIOR_SIZE>;

template <typename Exterior, size_t POLYGON_SIZE>
using Freespace = details::Freespace<Exterior, POLYGON_SIZE>;

template <typename Point>
using AutoFreespaceExterior = details::FreespaceExteriorPolygon<Point, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()>;

template <typename Point>
using AutoFreespace = details::Freespace<AutoFreespaceExterior<Point>, std::numeric_limits<size_t>::max()>;

}  // namespace common
}  // namespace holo

#endif
