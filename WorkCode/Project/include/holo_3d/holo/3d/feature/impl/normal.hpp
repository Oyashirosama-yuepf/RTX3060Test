/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file normal.hpp
 * @brief define NormalEstimationT class
 * @author jiangzheng(jiangzheng@holomatic.com)
 * @date 2021-10-22
 */

#include <holo/3d/common/common.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename NormalT>
bool_t NormalEstimationT<PointT, NormalT>::Compute(FeatureCloudPtrType output)
{
    std::vector<Scalar> curvatures;
    return computeWithCurvature(output, curvatures, false);
}

template <typename PointT, typename NormalT>
bool_t NormalEstimationT<PointT, NormalT>::ComputeWithCurvature(FeatureCloudPtrType output,
                                                                std::vector<Scalar> &curvatures)
{
    return computeWithCurvature(output, curvatures, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename NormalT>
bool_t NormalEstimationT<PointT, NormalT>::computeWithCurvature(FeatureCloudPtrType output,
                                                                std::vector<Scalar> &curvatures, 
                                                                bool_t enable_curvature_estimation)
{
    if (!PreCompute())
    {
        std::string s = "PreCompute failed";
        LOG(ERROR) << s;
        return false;
    }

    size_t n = indices_.size();
    output->resize(cloud_->size());
    curvatures.resize(cloud_->size(),0.0);
    Scalar nan_normal = std::numeric_limits<Scalar>::quiet_NaN();

    for (size_t i = 0; i < n; ++i)
    {
        std::vector<size_t> indices;
        std::vector<Scalar> distances;
        NormalT& normal = output->at(indices_[i]);
        normal.SetX(cloud_->at(indices_[i]).GetX());
        normal.SetY(cloud_->at(indices_[i]).GetY());
        normal.SetZ(cloud_->at(indices_[i]).GetZ());
        normal.SetNormalX(nan_normal);
        normal.SetNormalY(nan_normal);
        normal.SetNormalZ(nan_normal);

        if (search_function_(indices_[i], search_parameter_, indices, distances) == 0)
        {
            std::string s = "can not find neighbor points!";
            LOG(WARNING) << s;
            continue;
        }       

        if (!estimatePointNormalWithCurvature(i, indices, normal, curvatures[i], enable_curvature_estimation))
        {
            std::string s = "can not estimate point normal!";
            LOG(WARNING) << s;
            continue;
        }
    }

    if (!PostCompute())
    {
        std::string s = "PostCompute failed";
        LOG(ERROR) << s;
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename PointT, typename NormalT>
bool_t NormalEstimationT<PointT, NormalT>::estimatePointNormalWithCurvature(
                                         size_t index,
                                         const std::vector<size_t> &neighbors,
                                         NormalT &n, Scalar &curvature, bool_t enable_curvature_estimation) const
{
    Matrix3Type covariance_matrix;    
    Vector3Type xyz_centroid;
    size_t nn = neighbors.size();

    if (nn < 3 || ComputeMeanAndCovarianceMatrix(*cloud_, neighbors, covariance_matrix, xyz_centroid) < 3)
    {
        std::string s = "neighbor points too few!";
        LOG(ERROR) << s;
        return false;
    }    
    
    VectorXType eigen_values;
    MatrixXType eigen_vectors;

    MatrixXType covariance_matrix_;
    covariance_matrix_.Resize(3, 3);
    memcpy(covariance_matrix_.GetData(), covariance_matrix.GetData(), sizeof(Scalar) * 9u);

    if (!holo::eigen_solver::ComputeEigenValuesAndVectors(covariance_matrix_, eigen_values, eigen_vectors))
    {
        std::string s = "ComputeEigenValuesAndVectors failed!";
        LOG(ERROR) << s;
        return false;
    }

    Scalar eigen_value = eigen_values.At(0, 0);
    Vector3Type eigen_vector = eigen_vectors.GetCol(0);    

    /// eigenval for symetric positive semi-definite matrix can not be negative! Set it to 0
    if (eigen_value <= 0.0)
    {
        eigen_value = 0.0;
    }

    /// constrain the normal direction
    Vector3Type const vp(-cloud_->at(index).GetX(), -cloud_->at(index).GetY(), -cloud_->at(index).GetZ()); 
    Scalar cos_theta = vp.Dot(eigen_vector);
    if (cos_theta < 0)
    {
        eigen_vector *= -1.0;
    }
    
    n.SetNormalX(eigen_vector(0));
    n.SetNormalY(eigen_vector(1));
    n.SetNormalZ(eigen_vector(2)); 

    /// Compute the curvature surface change
    if (!enable_curvature_estimation)
    {
        curvature = std::numeric_limits<Scalar>::quiet_NaN();
        return true;
    }

    Scalar const eig_sum = covariance_matrix(0,0) + covariance_matrix(1,1) + covariance_matrix(2,2);    

    if (eig_sum != 0)
    {
        curvature = std::fabs(eigen_value / eig_sum);
    } 
    else
    {
        curvature = -1.0;
    }
    return true;
}
} // namespace pointcloud

} // namespace holo
