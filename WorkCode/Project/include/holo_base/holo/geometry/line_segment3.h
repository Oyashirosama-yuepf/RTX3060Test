/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_segment3.h
 * @brief define a line segment in 3d
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Mar-10-2021
 */

#ifndef HOLO_GEOMETRY_LINE_SEGMENT3_H_
#define HOLO_GEOMETRY_LINE_SEGMENT3_H_

#include "./details/line_segment3.h"

namespace holo
{
namespace geometry
{
/**
 * @addtogroup geometry
 * @{
 *
 */

template <typename T>
using LineSegment3T = details::LineSegment3T<T>;

using LineSegment3f = LineSegment3T<float32_t>;
using LineSegment3d = LineSegment3T<float64_t>;
using LineSegment3  = LineSegment3T<float64_t>;

/**
 * @}
 *
 */

}  // namespace geometry

}  // namespace holo

#endif  // HOLO_GEOMETRY_LINE_SEGMENT3_H_