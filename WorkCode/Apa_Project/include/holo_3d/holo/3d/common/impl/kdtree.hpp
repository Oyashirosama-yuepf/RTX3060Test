/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file kdtree.hpp
 * @brief kdtree implementation
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-10-22
 */

#ifndef HOLO_3D_COMMON_KDTREE_HPP_
#define HOLO_3D_COMMON_KDTREE_HPP_

#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>

#include <flann/flann.h>
#include <holo/log/hololog.h>

#include <holo/3d/common/kdtree.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief kdtree implementation class
 *
 * @tparam PointT
 * @tparam Scalar
 */
template <typename PointT, typename Scalar>
class KdTreeT<PointT, Scalar>::Implementation
{
public:
    using DistanceType = ::flann::L2_Simple<DistanceScalar>;
    using FlannIndex   = ::flann::Index<DistanceType>;

    /**
     * @brief Construct a new Implementation object
     *
     * @param[in] params
     */
    Implementation(Parameters const& params) : params_(params)
    {
    }

    /**
     * @brief Set the Input Point Cloud
     *
     * @param[in] cloud input point cloud
     */
    void SetInputPointCloud(PointCloudPtr const& cloud)
    {
        size_t num_points = cloud->size();

        if (num_points == 0U)
        {
            std::string msg = "cannot create a kdtree with an empty point cloud!";
            LOG(ERROR) << msg;
            throw std::runtime_error(msg);
        }

        cloud_ = cloud;
        ConvertCloudToData(*cloud_, data_);

        // build kdtree
        tree_.reset(new FlannIndex(::flann::Matrix<DistanceScalar>(data_.data(), num_points, dim_),
                                   ::flann::KDTreeSingleIndexParams(params_.leaf_max_size)));
        tree_->buildIndex();
    }

    /**
     * @brief Get the Input Point Cloud
     *
     * @return PointCloudConstPtr
     */
    PointCloudConstPtr GetInputPointCloud() const noexcept
    {
        return cloud_;
    }

    /**
     * @brief Search for k-nearest neighbors for the given point.
     *
     * @tparam QueryPointT query point type
     * @param[in] p a given query point
     * @param[in] k the number of neighbors to search for
     * @param[out] indices the resultant indices of the neighboring points
     * @param[out] distances the resultant squared distances to the neighboring points
     * @return int32_t number of neighbors found
     * @throws exception::OutOfRangeException if k is larger than total point size
     */
    template <typename QueryPointT>
    int32_t KnnSearch(QueryPointT const& p, size_t const k, std::vector<size_t>& indices,
                      std::vector<DistanceScalar>& distances) const
    {
        if (k > num_points_)
        {
            std::string msg = "k is larger than total point size !";
            LOG(ERROR) << msg;

            throw exception::OutOfRangeException(msg);
        }

        indices.resize(k);
        distances.resize(k);

        internal::PointToVector<QueryPointT, DistanceScalar, PointT::SIZE_VALUE> converter;

        std::vector<DistanceScalar> q(dim_);
        converter(p, q);

        ::flann::Matrix<size_t>         indices_mat(&indices[0], 1U, k);
        ::flann::Matrix<DistanceScalar> distances_mat(&distances[0], 1U, k);
        ::flann::SearchParams           params(::flann::SearchParams(params_.checks, params_.epsilon));

        return tree_->knnSearch(::flann::Matrix<DistanceScalar>(q.data(), 1U, dim_), indices_mat, distances_mat, k,
                                params);
    }

    /**
     * @brief Search for all the nearest neighbors of the query point in a given radius
     *
     * @tparam QueryPointT query point type
     * @param[in] p a given query point
     * @param[in] r the radius of the sphere bounding all of p's neighbors
     * @param[out] indices the resultant indices of the neighboring points
     * @param[out] distances the resulting distances to the neighboring points
     * @return int32_t number of neighbors found in radius
     */
    template <typename QueryPointT>
    int32_t RadiusSearch(QueryPointT const& p, DistanceScalar const r, std::vector<size_t>& indices,
                         std::vector<DistanceScalar>& distances) const noexcept
    {
        internal::PointToVector<QueryPointT, DistanceScalar, PointT::SIZE_VALUE> converter;

        std::vector<DistanceScalar> q(dim_);
        converter(p, q);

        std::vector<std::vector<size_t> >         indices_vec(1U);
        std::vector<std::vector<DistanceScalar> > distances_vec(1U);

        ::flann::SearchParams params(params_.checks, params_.epsilon, params_.sorted);
        params.max_neighbors = params_.max_neighbours;

        int32_t k = tree_->radiusSearch(::flann::Matrix<DistanceScalar>(q.data(), 1U, dim_), indices_vec, distances_vec,
                                        r * r, params);
        indices   = indices_vec[0];
        distances = distances_vec[0];
        return k;
    }

    /**
     * @brief Convert point cloud geometry data to vector data
     *
     * @param[in] cloud input point cloud
     * @param[out] data output data
     */
    void ConvertCloudToData(PointCloud const& cloud, std::vector<DistanceScalar>& data)
    {
        dim_        = PointT::SIZE_VALUE;
        num_points_ = cloud.size();

        data.resize(dim_ * num_points_);
        DistanceScalar* data_ptr = data.data();

        internal::PointToVector<PointT, DistanceScalar, PointT::SIZE_VALUE> converter;

        for (size_t i = 0U; i < num_points_; ++i)
        {
            PointT const& pt = cloud[i];

            converter(pt, data_ptr);
            data_ptr += dim_;
        }
    }

public:
    Parameters                  params_;
    size_t                      dim_;         ///< the number of dimensions per point
    size_t                      num_points_;  ///< number of points
    std::vector<DistanceScalar> data_;        ///< internal data
    std::shared_ptr<FlannIndex> tree_;        ///< internal search tree
    PointCloudPtr               cloud_;       ///< input point cloud

};  // class KdTree::Implementation

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename Scalar>
KdTreeT<PointT, Scalar>::KdTreeT(Parameters const& params) : impl_(new Implementation(params))
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename Scalar>
KdTreeT<PointT, Scalar>::~KdTreeT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename Scalar>
void KdTreeT<PointT, Scalar>::SetInputPointCloud(PointCloudPtr const& cloud)
{
    impl_->SetInputPointCloud(cloud);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename Scalar>
typename KdTreeT<PointT, Scalar>::PointCloudConstPtr KdTreeT<PointT, Scalar>::GetInputPointCloud() const noexcept
{
    return impl_->GetInputPointCloud();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename Scalar>
template <typename QueryPointT>
int32_t KdTreeT<PointT, Scalar>::KnnSearch(QueryPointT const& p, size_t const k, std::vector<size_t>& indices,
                                           std::vector<DistanceScalar>& distances) const
{
    return impl_->KnnSearch(p, k, indices, distances);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename Scalar>
template <typename QueryPointT>
int32_t KdTreeT<PointT, Scalar>::RadiusSearch(QueryPointT const& p, DistanceScalar const r,
                                              std::vector<size_t>&         indices,
                                              std::vector<DistanceScalar>& distances) const noexcept
{
    return impl_->RadiusSearch(p, r, indices, distances);
}
}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_COMMON_KDTREE_HPP_
