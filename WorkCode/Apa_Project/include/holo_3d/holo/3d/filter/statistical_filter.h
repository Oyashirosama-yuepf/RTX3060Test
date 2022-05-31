/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file statistical_filter.h
 * @brief This header file defines statistics filter class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-04
 */

#ifndef HOLO_3D_FILTER_STATISTICAL_FILTER_H
#define HOLO_3D_FILTER_STATISTICAL_FILTER_H

#include <holo/3d/common/kdtree.h>
#include <holo/3d/filter/filter.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief StatisticalFilter uses point neighborhood statistics to filter outlier data.
 *
 * @details The algorithm iterates through the entire input twice: During the first iteration it'll compute the average
 * distance that each point has to its nearest k neighbors. Next, the mean and standard deviation of all these distances
 * are computed the distance theshold is : mean + stddev_multi * stddev. During the next iteration the points will be
 * classified based on their distance.
 * @note the point in the point cloud should be unique
 * @tparam PointT
 */
template <typename PointT>
class StatisticalFilterT : public FilterIndicesT<PointT>
{
public:
    using Scalar    = float64_t;
    using Base      = FilterIndicesT<PointT>;
    using KdTree    = KdTreeT<PointT, Scalar>;
    using KdTreePtr = typename KdTree::Ptr;

    using Base::cloud_;
    using Base::kept_indices_;
    using Base::removed_indices_;
    using typename Base::PointCloud;
    using typename Base::PointCloudPtr;

    /**
     * @brief Constructor
     *
     * @param[in] mean_k the number of nearest neighbors to use for mean distance estimation
     * @param[in] std_mul the standard deviation multiplier for the distance threshold calculation
     * @param[in] keep true = normal filter vehavior(default), false = inverted behavior
     */
    StatisticalFilterT(size_t mean_k, Scalar std_mul, bool_t keep = true);

    /**
     * @brief Empty destructor
     *
     */
    virtual ~StatisticalFilterT();

    /**
     * @brief Set kdtree of the input point cloud, if not set, the kdtree will be created internally
     *
     * @param[in] tree
     */
    void SetInputTree(KdTreePtr const& tree);

    /**
     * @brief Calls the statistical filtering method and return the filtered point cloud
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
    KdTreePtr kdtree_;             ///< kdtree of intput point cloud
    size_t    mean_k_;             ///< the number of nearest neighbors
    Scalar    stddev_multiplier_;  ///< the standard deviation multiplier
    bool_t    keep_;  ///< true to remove points that are outliers, otherwise remove points that are inliners.
};
}  // namespace pointcloud
}  // namespace holo

#endif
