/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_traits.h
 * @brief This header file defines traits of point types
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-11-29
 */

#ifndef HOLO_3D_COMMON_POINT_TRAITS_H_
#define HOLO_3D_COMMON_POINT_TRAITS_H_

#include <holo/3d/common/point_types.h>
#include <holo/geometry/point3.h>

namespace holo
{
namespace pointcloud
{
namespace traits
{
template <typename PointT>
struct HasNormal
{
};

template <>
struct HasNormal<geometry::Point3f>
{
    static const bool value = false;
};

template <>
struct HasNormal<geometry::Point3d>
{
    static const bool value = false;
};

template <>
struct HasNormal<PointXYZIRSt<float32_t>>
{
    static const bool value = false;
};

template <>
struct HasNormal<PointXYZIRSt<float64_t>>
{
    static const bool value = false;
};

template <>
struct HasNormal<PointXYZNormalt<float32_t>>
{
    static const bool value = true;
};

template <>
struct HasNormal<PointXYZNormalt<float64_t>>
{
    static const bool value = true;
};

}  // namespace traits
}  // namespace pointcloud
}  // namespace holo

#endif
