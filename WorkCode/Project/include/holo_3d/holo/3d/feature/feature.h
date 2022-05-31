/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file feature.h
 * @brief define FeatureBaseT class
 * @author luopei(luopei@holomatic.com)
 * @author jiangzheng(jiangzheng@holomatic.com)
 * @date 2021-10-22
 */

#ifndef  HOLO_3D_FEATURE_FEATURE_H_
#define  HOLO_3D_FEATURE_FEATURE_H_

#include <numeric>
#include <holo/3d/common/point_cloud.h>
#include <holo/3d/common/kdtree.h>

namespace holo
{
namespace pointcloud
{
template <typename PointT, typename FeatureT>
class FeatureBaseT
{
public:
    /// base type
    using Scalar                   = typename PointT::ScalarType;

    /// pointcloud type
    using PointCloudType           = PointCloudT<PointT>;
    using PointCloudPtrType        = std::shared_ptr<PointCloudType>;
    using PointCloudConstPtrType   = std::shared_ptr<const PointCloudType>;
    using FeatureCloudType         = PointCloudT<FeatureT>;
    using FeatureCloudPtrType      = std::shared_ptr<FeatureCloudType>;
    using FeatureCloudConstPtrType = PointCloudT<const FeatureCloudType>;

    /// kd tree type
    using KdTreeType               = KdTreeT<PointT>;
    using KdTreePtrType            = std::shared_ptr<KdTreeType>;
    using KdTreeConstPtrType       = std::shared_ptr<const KdTreeType>;

    /// search function
    using SearchFunctionType = std::function<size_t (size_t, Scalar, std::vector<size_t> &, std::vector<Scalar> &)>;

    /**
     * @brief Construct a new FeatureBaseT object
     * 
     */
    FeatureBaseT()
        : search_method_(SearchMethod::UNKNOWN)
        , search_parameter_(0)
        , cloud_(nullptr)
        , tree_(nullptr)
        , search_function_()
    {
        static_assert(std::is_floating_point<Scalar>::value,
                      "PointT::Scalar must be floating-point type");
    }

    /**
     * @brief Destroy the FeatureBaseT object
     * 
     */
    virtual ~FeatureBaseT()
    {
    }  

    /**
     * @brief Set the Input Point Cloud object
     * @attention If user set indices before this function, 
     * then the user have to reset the indices again,
     * that's because we don't know whether it's a reuse case
     * or a initial case  
     * 
     * @param[in] cloud the pointer of Input Point Cloud object
     */
    void SetInputPointCloud(const PointCloudPtrType& cloud)
    {
        cloud_ = cloud;
        /// set default indices to all points
        size_t size = cloud_->size();
        /// since we reset input point cloud, we have to reset the indices too.
        indices_.resize(size);
        std::iota(indices_.begin(), indices_.end(), 0);
    }

    /**
     * @brief Set the Kd Tree object
     * 
     * @param[in] tree the pointer of Kd Tree
     */
    void SetKdTree(const KdTreePtrType& tree)
    {
        tree_ = tree;
    }

    /**
     * @brief Get the Kd Tree object
     * 
     * @return return a pointer to the search method used.
     */
    KdTreePtrType GetKdTree() const
    {
        return tree_;
    }

    /**
     * @brief Set the Indices object which is point of interest.
     * We only compute feature for points in indices
     * 
     * @param[in] indices point index of interest
     */
    void SetIndices(const std::vector<size_t>& indices)
    {
        indices_ = indices;
    }

    /**
     * @brief Get the Indices object
     * 
     * @return const std::vector<size_t>& 
     */
    const std::vector<size_t>& GetIndices() const
    {
        return indices_;
    }

    /**
     * @brief Set the Radius Search object
     * 
     * @param[in] radius search radius
     */
    void SetRadiusSearch(const Scalar& radius)
    {
        search_parameter_ = radius;
        search_method_ = SearchMethod::RADIUS;
    }

    /**
     * @brief Set the knn parameter
     * 
     * @param[in] knn search method
     */
    void SetKSearch(const size_t knn)
    {
        search_parameter_ = knn;
        search_method_ = SearchMethod::KNN;
    }

    /**
     * @brief Core function to compute the features
     * 
     * @param[in] cloud 
     * @return bool_t return the computed feature cloud
     */
    virtual bool_t Compute(FeatureCloudPtrType cloud) = 0;

    /**
     * @brief Call this before computation starts. 
     * Check whether the computation condition is met or not.
     * Preparation for the actual computation step, such as allocate required memories, etc.
     * 
     * @return bool_t 
     */
    virtual bool_t PreCompute();

    /**
     * @brief Poset the result of computing. Call this after computation is done.
     * 
     * @return bool_t 
     */
    virtual bool_t PostCompute()
    {
        return true;
    }

protected:
    /**
     * @brief wrapper function for SearchFunctionType
     * 
     * @param[in] index point index of pointcloud
     * @param[in] parameter the number of neighbors to search
     * @param[out] indices the resultant indices of the neighboring points
     * @param[out] distances the resultant squared distances to the neighboring points
     * @return size_t number of neighbors found
     */

    inline size_t
    searchKdTreeK(size_t index, Scalar parameter,
                  std::vector<size_t>& indices,
                  std::vector<Scalar>& distances) const
    {
        size_t k = size_t(parameter);
        indices.resize(k);
        distances.resize(k);
        return tree_->KnnSearch(cloud_->at(index), k, indices, distances);
    }

    /**
     * @brief wrapper function for SearchFunctionType
     * 
     * @param[in] index point index of pointcloud
     * @param[in] parameter the number of neighbors to search
     * @param[out] indices the resultant indices of the neighboring points
     * @param[out] distances the resultant squared distances to the neighboring points
     * @return size_t number of neighbors found
     */
    inline size_t
    searchKdTreeRadius(size_t index, Scalar parameter,
                       std::vector<size_t>& indices,
                       std::vector<Scalar>& distances) const
    {
        return tree_->RadiusSearch(cloud_->at(index), parameter, indices, distances);
    }

    /**
     * @brief Define search method of the Kd Tree.
     */
    enum SearchMethod : uint8_t
    {
        RADIUS  = 0,  ///< Radius Nearest Neighbors Search
        KNN     = 1,  ///< K Nearest Neighbors Search
        UNKNOWN = 2,  ///< Unknow
    };

    SearchMethod search_method_;  ///< search_method_ is KNN or RADIUS
    Scalar search_parameter_;
    std::vector<size_t> indices_;
    PointCloudPtrType cloud_;
    std::shared_ptr<KdTreeType> tree_;
    SearchFunctionType search_function_;
private:

};

} // namespace pointcloud

} // namespace holo

#endif   /* ----- #ifndef HOLO_3D_FEATURE_FEATURE_H_  ----- */
