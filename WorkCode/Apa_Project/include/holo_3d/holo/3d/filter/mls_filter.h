/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mls_filter.h
 * @brief This header file defines mls filter
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-06-11
 */

#ifndef HOLO_3D_FILTER_MLS_FILTER_H_
#define HOLO_3D_FILTER_MLS_FILTER_H_

#include <queue>
#include <unordered_map>

#include <holo/3d/common/common.h>
#include <holo/3d/common/point_cloud.h>
#include <holo/3d/filter/filter.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief MlsFilter using a moving least squared surface to filter ground points and nonground points.
 *
 * @tparam PointT
 */
template <typename PointT>
class MlsFilterT : public FilterIndicesT<PointT>
{
public:
    using Scalar = float64_t;
    using Base   = FilterIndicesT<PointT>;
    using Index  = Eigen::Vector2i;

    using Base::cloud_;
    using Base::kept_indices_;
    using Base::removed_indices_;
    using typename Base::PointCloud;
    using typename Base::PointCloudPtr;

    struct Parameters
    {
        Scalar  grid_size               = 2.0;
        int32_t half_window_size        = 2;  // window = 2 * half_window + 1;
        int32_t order                   = 2;
        Scalar  max_distance_to_surface = 0.25;
        size_t  min_seed_neighbors      = 6;
    };

    struct Grid
    {
        Grid(Index const& _index) : index(_index), ground_pt(), z_sigma(std::numeric_limits<Scalar>::max())
        {
        }

        Index               index;
        PointT              ground_pt;
        Scalar              z_sigma;
        std::vector<size_t> indices;  // grid point indices in point cloud
        std::vector<Scalar> z_values;
        std::vector<Index>  neighbors;  ///> grid neighor indices
    };

    using GridPtr = std::shared_ptr<Grid>;

    /**
     * @brief Construct a new Mls Filter T object
     *
     * @param params
     */
    MlsFilterT(Parameters const& params);

    /**
     * @brief Destroy the Mls Filter T object
     *
     */
    virtual ~MlsFilterT() = default;

    /**
     * @brief Calls the mls filtering method and return the filtered point cloud
     *
     * @return PointCloudPtr the resultant filtered point cloud
     */
    PointCloudPtr Compute() override;

protected:
    using Base::PostCompute;
    using Base::PreCompute;

    /**
     * @brief Get the Voxel Index in Volume
     *
     * @param[in] pt input point
     * @return Vector3i voxel index
     */
    Index getGridIndex(const PointT& pt) const
    {
        return Index(std::floor(pt[0] * grid_res_inverse_), std::floor(pt[1] * grid_res_inverse_));
    }

    /**
     * @brief assign point to grid
     *
     */
    void computeGrids();

    /**
     * @brief compute seed and grid neighbors
     *
     * @param[out] grid_seeds
     */
    void computeSeeds(std::vector<GridPtr>& grid_seeds);

    /**
     * @brief fit polynominal surface
     *
     * @param[in] order
     * @param[in] points
     * @param[in] weight
     * @param surface_params
     */
    void fitPolynominalSurface(int32_t const order, std::vector<PointT> const& points, Eigen::VectorXd const& weight,
                               Eigen::VectorXd& surface_params);

    /**
     * @brief compute point distance to surface
     *
     * @param[in] pt
     * @param[in] order
     * @param[in] surface_params
     * @param[out] z_fit
     * @return Scalar
     */
    Scalar computeDistanceToSurface(PointT const& pt, int32_t order, Eigen::VectorXd const& surface_params,
                                    Scalar& z_fit);

private:
    Parameters params_;
    Scalar     grid_res_inverse_;

    std::unordered_map<Index, GridPtr, internal::hash_eigen::hash<Index>> grid_map_;     // index grid map
    std::unordered_map<Index, int32_t, internal::hash_eigen::hash<Index>> grid_labels_;  // index label map
};
}  // namespace pointcloud
}  // namespace holo

#endif
