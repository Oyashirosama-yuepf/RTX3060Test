/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sphere.h
 * @brief define a sphere
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Mar-05-2021
 */

#ifndef HOLO_GEOMETRY_SPHERE_H_
#define HOLO_GEOMETRY_SPHERE_H_

#include "./details/sphere.h"

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
using Sphere3T = details::Sphere3T<T>;

using Sphere3f = Sphere3T<float32_t>;
using Sphere3d = Sphere3T<float64_t>;
using Sphere3  = Sphere3T<float64_t>;

/**
 * @}
 *
 */

}  // namespace geometry

}  // namespace holo

#endif  // HOLO_GEOMETRY_SPHERE_H_