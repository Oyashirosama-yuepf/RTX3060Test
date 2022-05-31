/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file voxel_grid_filter.h
 * @brief This header file defines voxel grid internal class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-03
 */

#ifndef HOLO_3D_FILTER_DETAILS_VOXEL_GRID_FILTER_H_
#define HOLO_3D_FILTER_DETAILS_VOXEL_GRID_FILTER_H_

#include <Eigen/Dense>
#include <unordered_map>

#include <holo/3d/common/common.h>
#include <holo/3d/filter/filter.h>

namespace holo
{
namespace pointcloud
{
namespace internal
{
/**
 * @brief Voxel grid internal class
 *
 * @tparam PointT
 */
template <typename PointT>
class VoxelGridInternalT
{
public:
    using PointCloud    = PointCloudT<PointT>;
    using PointCloudPtr = std::shared_ptr<PointCloud>;

    using ScalarType      = float64_t;
    using PointScalarType = typename PointT::ScalarType;
    using Vector3         = numerics::Vector3T<ScalarType>;
    using Index           = Eigen::Vector3i;  ///< @todo using holo::Vector3T<int32> when is ready
    using Hash            = internal::hash_eigen::hash<Index>;

    class Voxel
    {
    public:
        Voxel() : num_points(0)
        {
        }

        void AddPoint(PointT const& pt, size_t idx)
        {
            point += pt;
            num_points++;
            indices.push_back(idx);
        }

        PointT GetAveragePoint()
        {
            assert(num_points > 0);
            return point / static_cast<PointScalarType>(num_points);
        }

    public:
        size_t              num_points;  ///> number of points in voxel
        PointT              point;       ///> accumulated point
        std::vector<size_t> indices;     ///> indices of points in voxel
    };

    using StorageType = std::unordered_map<Index, Voxel, Hash>;

    /**
     * @brief Constructor the Voxel Grid Internal object from point cloud
     *
     * @param[in] cloud
     */
    VoxelGridInternalT(PointCloudPtr const& cloud) : cloud_(cloud)
    {
    }

    /**
     * @brief Destroy the Voxel Grid Internal object
     *
     */
    ~VoxelGridInternalT()
    {
    }

    /**
     * @brief voxelize point cloud
     *
     * @param[in] vx voxel size in x direction
     * @param[in] vy voxel size in y direction
     * @param[in] vz voxel size in z direction
     * @param[out] voxels unordered_map voxels
     */
    void Compute(float64_t vx, float64_t vy, float64_t vz, StorageType& voxels)
    {
        PointT min_pt, max_pt;
        BBox<PointT, 3>()(*cloud_, min_pt, max_pt);

        Vector3 voxel_min_bound(min_pt[0] - 0.5 * vx, min_pt[1] - 0.5 * vy, min_pt[2] - 0.5 * vz);
        Vector3 voxel_max_bound(max_pt[0] + 0.5 * vx, max_pt[1] + 0.5 * vy, max_pt[2] + 0.5 * vz);

        Vector3 voxel_size_inv(1 / vx, 1 / vy, 1 / vz);
        Index   voxel_index;

        for (size_t i = 0U; i < cloud_->size(); ++i)
        {
            PointT const& pt = cloud_->at(i);

            ScalarType cx = (pt[0] - voxel_min_bound[0]) * voxel_size_inv[0];
            ScalarType cy = (pt[1] - voxel_min_bound[1]) * voxel_size_inv[1];
            ScalarType cz = (pt[2] - voxel_min_bound[2]) * voxel_size_inv[2];

            voxel_index[0] = static_cast<int32_t>(std::floor(cx));
            voxel_index[1] = static_cast<int32_t>(std::floor(cy));
            voxel_index[2] = static_cast<int32_t>(std::floor(cz));

            voxels[voxel_index].AddPoint(pt, i);
        }
    }

private:
    PointCloudPtr cloud_;
};
}  // namespace internal
}  // namespace pointcloud
}  // namespace holo

#endif
