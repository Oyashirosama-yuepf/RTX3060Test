/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file normal.h
 * @brief define NormalEstimationT class
 * @author jiangzheng(jiangzheng@holomatic.com)
 * @date 2021-10-22
 */

#ifndef  HOLO_3D_FEATURE_NORMAL_H_
#define  HOLO_3D_FEATURE_NORMAL_H_

#include <holo/3d/feature/feature.h>
#include <holo/3d/common/point_types.h>
#include <holo/3d/common/point_cloud.h>
#include <holo/core/epsilon.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/numerics/eigen_solver.h>

namespace holo
{
namespace pointcloud
{
template <typename PointT, typename NormalT>
class NormalEstimationT : public FeatureBaseT<PointT, NormalT>
{
public:
    /// base type
    using Scalar   = typename PointT::ScalarType;
    using Matrix3Type  = Matrix3T<Scalar>;
    using Vector3Type  = Vector3T<Scalar>;
    using MatrixXType  = MatrixXT<Scalar>;
    using VectorXType  = VectorXT<Scalar>;
    using EpsilonType  = EpsilonT<Scalar>; 

    /// pointcloud type
    using Base                      = FeatureBaseT<PointT, NormalT>;
    using PointCloudType            = typename Base::PointCloudType;
    using PointCloudPtrType         = typename Base::PointCloudPtrType;
    using PointCloudConstPtrType    = typename Base::PointCloudConstPtrType;
    using FeatureCloudType          = typename Base::FeatureCloudType;
    using FeatureCloudPtrType       = typename Base::FeatureCloudPtrType;
    using FeatureCloudConstPtrType  = typename Base::FeatureCloudConstPtrType;

    /// base variable
    using Base::indices_;
    using Base::cloud_;
    using Base::search_function_;
    using Base::search_parameter_;

    /**
     * @brief Construct a new NormalEstimationT object
     * 
     */
    NormalEstimationT() : Base()
    {    
    }

    /**
     * @brief Destroy the Normal Estimation T object
     * 
     */
    virtual ~NormalEstimationT()
    {
    }

    /**
     * @brief Core function to compute the normal
     * 
     * @param cloud 
     * @return true or false
     */
    virtual bool_t Compute(FeatureCloudPtrType cloud);

    /**
     * @brief Compute the normal with curvature
     * 
     * @param[in] cloud input pointcloud
     * @param[out] curvatures output curvatures
     * @return bool_t 
     */
    virtual bool_t ComputeWithCurvature(FeatureCloudPtrType cloud, std::vector<Scalar>& curvatures);    
    
    /**
     * @brief Call this before computation starts. 
     * Check whether the computation condition is met or not.
     * Preparation for the actual computation step, such as allocate required memories, etc.
     * 
     * @return bool_t 
     */
    virtual bool_t PreCompute()
    {
        return Base::PreCompute();
    }

    /**
     * @brief Poset the result of computing. Call this after computation is done.
     * 
     * @return bool_t 
     */
    virtual bool_t PostCompute()
    {
        return Base::PostCompute();
    }

protected:

private:    
    /**
     * @brief Compute the normal with curvature
     * 
     * @param[in] cloud input pointcloud
     * @param[out] curvatures output curvatures
     * @param[in] enable_curvature_estimation 
     * @return bool_t 
     */
    virtual bool_t computeWithCurvature(FeatureCloudPtrType cloud, std::vector<Scalar>& curvatures,  
                                        bool_t enable_curvature_estimation);
    /**
     * @brief Estimate normal with curvature of points
     * 
     * @param[in] index index of poins
     * @param[in] neighbors index of neighbors points
     * @param[in] n normal point
     * @param[out] curvature curvature of normal point
     * @param[in] enable_curvature_estimation 
     * @return bool_t 
     */
    bool_t estimatePointNormalWithCurvature(size_t index, const std::vector<size_t> &neighbors, NormalT &n, 
                                            Scalar &curvature, bool_t enable_curvature_estimation = false) const;

};

} // namespace pointcloud

} // namespace holo
#endif   /* ----- #ifndef HOLO_3D_FEATURE_NORMAL_H_  ----- */
