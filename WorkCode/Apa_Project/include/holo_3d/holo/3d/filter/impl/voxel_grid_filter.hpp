/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file voxel_grid_filter.hpp
 * @brief Implementation of voxel grid filter
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-03
 */
#ifndef HOLO_3D_FILTER_VOXEL_GRID_FILTER_HPP_
#define HOLO_3D_FILTER_VOXEL_GRID_FILTER_HPP_

#include <holo/3d/filter/voxel_grid_filter.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
VoxelGridFilterT<PointT, true>::VoxelGridFilterT(float64_t vx, float64_t vy, float64_t vz) : vx_(vx), vy_(vy), vz_(vz)
{
    static_assert(PointT::SIZE_VALUE == 3U, "point must have x, y and z fields!");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
VoxelGridFilterT<PointT, true>::~VoxelGridFilterT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
bool_t VoxelGridFilterT<PointT, true>::PreCompute()
{
    if (!Base::PreCompute())
    {
        return false;
    }

    if (vx_ <= 0 || vy_ <= 0 || vz_ <= 0)
    {
        std::string msg = "invalid voxel size!";
        LOG(ERROR) << msg;
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
typename VoxelGridFilterT<PointT, true>::PointCloudPtr VoxelGridFilterT<PointT, true>::Compute()
{
    if (!PreCompute())
    {
        std::string msg = "PreCompute failed !";
        LOG(ERROR) << msg;
        return nullptr;
    }

    using VoxelGridInternalType = internal::VoxelGridInternalT<PointT>;
    using StorageType           = typename VoxelGridInternalType::StorageType;

    StorageType           voxels;
    VoxelGridInternalType vgi(cloud_);
    vgi.Compute(vx_, vy_, vz_, voxels);

    PointCloudPtr output(new PointCloud);
    output->SetTimestamp(cloud_->GetTimestamp());
    output->SetCoordinate(cloud_->GetCoordinate());
    output->SetPose(cloud_->GetPose());
    output->SetDense(cloud_->IsDense());
    output->reserve(voxels.size());

    for (auto& voxel : voxels)
    {
        output->push_back(voxel.second.GetAveragePoint());
    }

    if (!PostCompute())
    {
        std::string msg = "PostCompute failed !";
        LOG(ERROR) << msg;
        return nullptr;
    }

    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
VoxelGridFilterT<PointT, false>::VoxelGridFilterT(float64_t vx, float64_t vy, float64_t vz) : vx_(vx), vy_(vy), vz_(vz)
{
    static_assert(PointT::SIZE_VALUE == 3U, "point must have x, y and z fields!");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
VoxelGridFilterT<PointT, false>::~VoxelGridFilterT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
bool_t VoxelGridFilterT<PointT, false>::PreCompute()
{
    if (!Base::PreCompute())
    {
        return false;
    }

    if (vx_ <= 0 || vy_ <= 0 || vz_ <= 0)
    {
        std::string msg = "invalid voxel size!";
        LOG(ERROR) << msg;
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
typename VoxelGridFilterT<PointT, false>::PointCloudPtr VoxelGridFilterT<PointT, false>::Compute()
{
    if (!PreCompute())
    {
        std::string msg = "PreCompute failed !";
        LOG(ERROR) << msg;
        return nullptr;
    }

    using VoxelGridInternalType = internal::VoxelGridInternalT<PointT>;
    using StorageType           = typename VoxelGridInternalType::StorageType;

    StorageType           voxels;
    VoxelGridInternalType vgi(cloud_);
    vgi.Compute(vx_, vy_, vz_, voxels);

    PointCloudPtr output(new PointCloud);
    output->SetTimestamp(cloud_->GetTimestamp());
    output->SetCoordinate(cloud_->GetCoordinate());
    output->SetPose(cloud_->GetPose());
    output->SetDense(cloud_->IsDense());
    output->reserve(voxels.size());

    std::vector<bool_t> keep_flags(cloud_->size(), false);

    for (auto const& voxel : voxels)
    {
        size_t                     num_points = voxel.second.num_points;
        std::vector<size_t> const& indices    = voxel.second.indices;

        std::vector<ScalarType> dists(num_points, 0);

        for (size_t i = 0U; i < num_points; ++i)
        {
            for (size_t j = i + 1; j < num_points; ++j)
            {
                PointT const& pi = cloud_->at(indices[i]);
                PointT const& pj = cloud_->at(indices[j]);
                ScalarType    dx = pi[0] - pj[0];
                ScalarType    dy = pi[1] - pj[1];
                ScalarType    dz = pi[2] - pj[2];
                ScalarType    d  = dx * dx + dy * dy + dz * dz;
                dists[i] += d;
                dists[j] += d;
            }
        }

        size_t min_index = std::distance(dists.begin(), std::min_element(dists.begin(), dists.end()));
        output->push_back(cloud_->at(indices[min_index]));
        keep_flags[indices[min_index]] = true;
    }

    for (size_t i = 0U; i < keep_flags.size(); ++i)
    {
        if (keep_flags[i])
        {
            kept_indices_.push_back(i);
        }
        else
        {
            removed_indices_.push_back(i);
        }
    }

    if (!PostCompute())
    {
        std::string msg = "PostCompute failed !";
        LOG(ERROR) << msg;
        return nullptr;
    }

    return output;
}

}  // namespace pointcloud
}  // namespace holo

#endif
