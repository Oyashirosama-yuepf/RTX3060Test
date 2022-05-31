/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file kdtree.h
 * @brief This header file defines a generic type of 3D kd-tree structures
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-10-22
 */

#ifndef HOLO_3D_COMMON_KDTREE_H_
#define HOLO_3D_COMMON_KDTREE_H_

#include <holo/3d/common/point_cloud.h>
#include <holo/3d/common/point_types.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace pointcloud
{
namespace internal
{
/**
 * @brief Convert input point into a vector representation,can be of any type that implements the [] operator
 *
 * @tparam PointT point type
 * @tparam Scalar output data scalar type
 * @tparam Dim point geometry dimension
 */
template <typename PointT, typename Scalar, size_t Dim>
struct PointToVector
{
    template <typename OutputType>
    void operator()(PointT const& p, OutputType& data)
    {
        std::string msg = "The point type is not supported!";
        LOG(ERROR) << msg;
    }
};

template <typename PointT, typename Scalar>
struct PointToVector<PointT, Scalar, 3>
{
    template <typename OutputType>
    void operator()(PointT const& p, OutputType& data)
    {
        data[0] = p[0];
        data[1] = p[1];
        data[2] = p[2];
    }
};

template <typename PointT, typename Scalar>
struct PointToVector<PointT, Scalar, 2>
{
    template <typename OutputType>
    void operator()(PointT const& p, OutputType& data)
    {
        data[0] = p[0];
        data[1] = p[1];
    }
};

}  // namespace internal

/**
 * @brief KdTree related parameters
 *
 */
struct KdTreeParameters
{
    KdTreeParameters(int32_t checks_ = -1, float32_t epsilon_ = 0.0f, bool_t sorted_ = true,
                     int32_t max_neighbours_ = -1, int32_t leaf_max_size_ = 15)
      : checks(checks_)
      , epsilon(epsilon_)
      , sorted(sorted_)
      , max_neighbours(max_neighbours_)
      , leaf_max_size(leaf_max_size_)
    {
    }

    int32_t   checks;          ///< how many leafs to visit when searching for neighbors(-1 for unlimited)
    float32_t epsilon;         ///< search for eps-approximate neighbours (default: 0)
    bool_t    sorted;          ///< only for radius search, require neighbors sorted by distance
    int32_t   max_neighbours;  ///< maximum number of neighbours radius search should return (-1 for unlimited)
    int32_t   leaf_max_size;   ///< maximum number of points in leaf node
};

/**
 * @brief kD-tree class making use of FLANN project
 *
 * @tparam PointT point type
 * @tparam Scalar kdtree scalar type
 */
template <typename PointT, typename Scalar = typename PointT::ScalarType>
class KdTreeT
{
public:
    using Parameters         = KdTreeParameters;
    using DistanceScalar     = Scalar;
    using PointScalar        = typename PointT::ScalarType;
    using PointCloud         = PointCloudT<PointT>;
    using PointCloudPtr      = std::shared_ptr<PointCloud>;
    using PointCloudConstPtr = std::shared_ptr<const PointCloud>;

    using KdTree   = KdTreeT<PointT, DistanceScalar>;
    using Ptr      = std::shared_ptr<KdTree>;
    using ConstPtr = std::shared_ptr<const KdTree>;

    /**
     * @brief Construct kd-tree object
     *
     * @param[in] params
     */
    KdTreeT(Parameters const& params = Parameters());

    /**
     * @brief Disable copy constructor and assignment operator
     *
     */
    KdTreeT(KdTreeT const&) = delete;
    KdTreeT& operator=(KdTreeT const&) = delete;

    /**
     * @brief Destroy the kd-tree object
     *
     */
    ~KdTreeT();

    /**
     * @brief Set the Input Point Cloud, and build kdtree index
     *
     * @param[in] cloud
     */
    void SetInputPointCloud(PointCloudPtr const& cloud);

    /**
     * @brief Get the Input Point Cloud
     *
     * @return PointCloudConstPtr input point cloud ptr
     */
    PointCloudConstPtr GetInputPointCloud() const noexcept;

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
                      std::vector<DistanceScalar>& distances) const;

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
                         std::vector<DistanceScalar>& distances) const noexcept;

private:
    Parameters params_;  ///< kd-tree paramters

    class Implementation;  ///< PIMPL (Pointer to Implementation)
    std::unique_ptr<Implementation> impl_;
};

}  // namespace pointcloud
}  // namespace holo
#endif  // HOLO_3D_COMMON_KDTREE_H_
