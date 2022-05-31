/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file statistical_filter.hpp
 * @brief Implementation of statistical filter
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-04
 */

#ifndef HOLO_3D_FILTER_STATISTICAL_FILTER_HPP_
#define HOLO_3D_FILTER_STATISTICAL_FILTER_HPP_

#include <holo/3d/filter/statistical_filter.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
StatisticalFilterT<PointT>::StatisticalFilterT(size_t mean_k, Scalar std_mul, bool_t keep)
  : Base(), mean_k_(mean_k), stddev_multiplier_(std_mul), keep_(keep)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
StatisticalFilterT<PointT>::~StatisticalFilterT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void StatisticalFilterT<PointT>::SetInputTree(KdTreePtr const& tree)
{
    kdtree_ = tree;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
bool_t StatisticalFilterT<PointT>::PreCompute()
{
    if (!Base::PreCompute())
    {
        return false;
    }

    if (cloud_->size() <= mean_k_)
    {
        LOG(ERROR) << "point cloud size must be greater than knn number: " << mean_k_;
        return false;
    }

    if (!kdtree_)
    {
        kdtree_.reset(new KdTree);
        kdtree_->SetInputPointCloud(cloud_);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
typename StatisticalFilterT<PointT>::PointCloudPtr StatisticalFilterT<PointT>::Compute()
{
    if (!PreCompute())
    {
        LOG(ERROR) << "PreCompute failed.";
        return nullptr;
    }

    std::vector<Scalar> distances(cloud_->size());
    std::vector<size_t> nn_indices(mean_k_);
    std::vector<Scalar> nn_dists(mean_k_);

    size_t num_valid = 0;

    for (size_t i = 0U; i < cloud_->size(); ++i)
    {
        PointT const& pt = cloud_->at(i);

        if (!kdtree_->KnnSearch(pt, mean_k_ + 1, nn_indices, nn_dists))
        {
            distances[i] = 0;
            continue;
        }

        // calculate the mean distance of pt to its neighbors
        Scalar dist_sum = 0.0;

        for (size_t k = 1U; k < mean_k_ + 1; ++k)
        {
            dist_sum += std::sqrt(nn_dists[k]);
        }

        distances[i] = dist_sum / mean_k_;
        num_valid++;
    }

    assert(num_valid > 0);
    // estimate the mean and the stddev
    Scalar sum = 0, sq_sum = 0;

    for (size_t i = 0U; i < distances.size(); ++i)
    {
        sum += distances[i];
        sq_sum += distances[i] * distances[i];
    }

    Scalar mean     = sum / static_cast<Scalar>(num_valid);
    Scalar variance = (sq_sum - sum * sum / static_cast<Scalar>(num_valid)) / static_cast<Scalar>(num_valid - 1);
    Scalar stddev   = std::sqrt(variance);

    Scalar dist_threshold = mean + stddev_multiplier_ * stddev;

    // filter the points on the computed distance threshold
    PointCloudPtr output(new PointCloud());
    output->reserve(cloud_->size());

    for (size_t i = 0U; i < cloud_->size(); ++i)
    {
        // points which distances larger than threshold and keep_ is true is outlier
        if ((distances[i] > dist_threshold && keep_) || (distances[i] < dist_threshold && !keep_))
        {
            removed_indices_.push_back(i);
            continue;
        }

        output->push_back(cloud_->at(i));
        kept_indices_.push_back(i);
    }

    if (!PostCompute())
    {
        LOG(ERROR) << "PostCompute failed.";
        return nullptr;
    }

    return output;
}

}  // namespace pointcloud
}  // namespace holo

#endif
