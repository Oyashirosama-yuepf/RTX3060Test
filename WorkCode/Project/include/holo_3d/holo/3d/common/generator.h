/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file generator.h
 * @brief This header file defines generator of simulated point cloud
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-04
 */

#ifndef HOLO_3D_COMMON_GENERATOR_H_
#define HOLO_3D_COMMON_GENERATOR_H_

#include <holo/3d/common/details/generator.h>
#include <holo/3d/common/point_cloud.h>
#include <holo/3d/common/point_types.h>
namespace holo
{
namespace pointcloud
{
/**
 * @brief Generate a cube point cloud centered on origin(0,0,0)
 *
 * @tparam PointT
 * @tparam PointT::ScalarType
 * @param[in] d side length
 * @param[in] r resolution
 * @return std::shared_ptr<PointCloudT<PointT>>
 */
template <typename PointT, typename Scalar = typename PointT::ScalarType>
std::shared_ptr<PointCloudT<PointT>> Cube(Scalar const d = 1.0, Scalar const r = 0.1)
{
    assert(d >= 0.0 && r >= 0.0);

    internal::CubeFunctor<PointT, Scalar> cube_generator;
    std::shared_ptr<PointCloudT<PointT>>  output(new PointCloudT<PointT>);
    cube_generator(d, r, *output);

    return output;
}

}  // namespace pointcloud
}  // namespace holo

#endif
