/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file curve_descriptor.h
 * @brief This header file defines curve_descriptor
 * @author duyanwei@holomatic.com
 * @date Sep-29-2020
 */

#ifndef HOLO_GEOMETRY_CURVE_DESCRIPTOR_H_
#define HOLO_GEOMETRY_CURVE_DESCRIPTOR_H_

#include "./details/curve_descriptor.h"

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
using CurveDescriptorT = details::CurveDescriptorT<T>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::CurveDescriptorT<T>
 *
 * @tparam T
 */
template <typename T>
using CurveDescriptorT [[deprecated]] = geometry::CurveDescriptorT<T>;

}  // namespace holo

#endif  // HOLO_GEOMETRY_CURVE_DESCRIPTOR_H_