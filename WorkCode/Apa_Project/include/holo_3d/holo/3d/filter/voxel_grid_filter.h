/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file voxel_grid_filter.h
 * @brief This header file defines voxel grid filter
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-03
 */
#ifndef HOLO_3D_FILTER_VOXEL_GRID_FILTER_H_
#define HOLO_3D_FILTER_VOXEL_GRID_FILTER_H_

#include <unordered_map>

#include <holo/3d/common/common.h>
#include <holo/3d/filter/details/voxel_grid_filter.h>
#include <holo/3d/filter/filter.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief Voxel grid filter class, will create a 3d grid over a point cloud, and downsample the data
 *
 * @tparam PointT
 * @tparam AVERAGE true for average voxel grid, false for meidan voxel grid
 */
template <typename PointT, bool_t AVERAGE = true>
class VoxelGridFilterT;

/**
 * @brief Specializaiton for average voxel grid
 *
 * @tparam PointT
 */
template <typename PointT>
class VoxelGridFilterT<PointT, true> : public FilterBaseT<PointT>
{
public:
    using Base = FilterBaseT<PointT>;
    using Base::cloud_;
    using typename Base::PointCloud;
    using typename Base::PointCloudPtr;

    /**
     * @brief Construct a new Voxel Grid Filter object
     *
     * @param vx voxel size in x direction
     * @param vy voxel size in y direction
     * @param vz voxel size in z direction
     */
    VoxelGridFilterT(float64_t vx, float64_t vy, float64_t vz);

    /**
     * @brief Empty destructor
     *
     */
    virtual ~VoxelGridFilterT();

    /**
     * @brief Calls the filtering method and return the filtered point cloud
     *
     * @return PointCloudPtr the resultant filtered point cloud
     */
    PointCloudPtr Compute() override;

protected:
    using Base::PostCompute;

    /**
     * @brief Check if an input point cloud is given, input parameters is valid
     *
     * @return bool_t
     */
    virtual bool_t PreCompute() override;

private:
    float64_t vx_;
    float64_t vy_;
    float64_t vz_;
};

/**
 * @brief Specializaiton for median voxel grid
 *
 * @tparam PointT
 */
template <typename PointT>
class VoxelGridFilterT<PointT, false> : public FilterIndicesT<PointT>
{
public:
    using Base = FilterIndicesT<PointT>;
    using Base::cloud_;
    using Base::kept_indices_;
    using Base::removed_indices_;
    using typename Base::PointCloud;
    using typename Base::PointCloudPtr;
    using ScalarType = float64_t;

    /**
     * @brief Construct a new Voxel Grid Filter object
     *
     * @param vx voxel size in x direction
     * @param vy voxel size in y direction
     * @param vz voxel size in z direction
     */
    VoxelGridFilterT(float64_t vx, float64_t vy, float64_t vz);

    /**
     * @brief Empty destructor
     *
     */
    virtual ~VoxelGridFilterT();

    /**
     * @brief Calls the voxel grid filtering method and return the filtered point cloud
     *
     * @return PointCloudPtr the resultant filtered point cloud
     */
    PointCloudPtr Compute() override;

protected:
    using Base::PostCompute;

    /**
     * @brief Check if an input point cloud is given, input parameters is valid
     *
     * @return bool_t
     */
    virtual bool_t PreCompute() override;

private:
    float64_t vx_;
    float64_t vy_;
    float64_t vz_;
};
}  // namespace pointcloud
}  // namespace holo

#endif
