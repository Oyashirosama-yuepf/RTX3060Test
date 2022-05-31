/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sphere_point3.h
 * @brief define point3 on a sphere
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Mar-05-2021
 */

#ifndef HOLO_GEOMETRY_SPHERE_POINT3_H_
#define HOLO_GEOMETRY_SPHERE_POINT3_H_

#include "./details/sphere_point3.h"

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
using SpherePoint3T = details::SpherePoint3T<T>;

using SpherePoint3f = SpherePoint3T<float32_t>;
using SpherePoint3d = SpherePoint3T<float64_t>;
using SpherePoint3  = SpherePoint3T<float64_t>;

/**
 * @}
 *
 */

}  // namespace geometry

}  // namespace holo

#endif  // HOLO_GEOMETRY_SPHERE_POINT3_H_