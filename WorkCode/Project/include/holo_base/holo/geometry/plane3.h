/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file plane3.h
 * @brief define a plane in 3d
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Mar-08-2021
 */

#ifndef HOLO_GEOMETRY_PLANE3_H_
#define HOLO_GEOMETRY_PLANE3_H_

#include "./details/plane3.h"

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
using Plane3T = details::Plane3T<T>;

using Plane3f = Plane3T<float32_t>;
using Plane3d = Plane3T<float64_t>;
using Plane3  = Plane3T<float64_t>;

/**
 * @}
 *
 */

}  // namespace geometry

}  // namespace holo

#endif  // HOLO_GEOMETRY_PLANE3_H_