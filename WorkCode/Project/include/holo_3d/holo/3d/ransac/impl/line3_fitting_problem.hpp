/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line3_fitting_problem.hpp
 * @brief This implementation file of RansacLine3FittingProblem class
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2022-04-07
 */
#include <holo/3d/ransac/line3_fitting_problem.h>
#include <holo/numerics/eigen_solver.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t RansacLine3FittingProblem<T>::IsSampleGood(std::vector<uint64_t> const& sample) const
{
    ///@brief Check samples size
    if (sample.size() < GetRequiredSampleSize())
    {
        LOG(WARNING) << "RansacLine3FittingProblem::IsSampleGood() --- Wrong number of samples (is " << sample.size()
                     << " , should be " << GetRequiredSampleSize() << ")!";
        return false;
    }

    ///@brief Make sure that the two sample points are not identical.
    if (std::fabs(adapter_.GetSample(sample[0u]).GetX() - adapter_.GetSample(sample[1u]).GetX()) <=
            holo::EpsilonT<Scalar>::value &&
        std::fabs(adapter_.GetSample(sample[0u]).GetY() - adapter_.GetSample(sample[1u]).GetY()) <=
            holo::EpsilonT<Scalar>::value &&
        std::fabs(adapter_.GetSample(sample[0u]).GetZ() - adapter_.GetSample(sample[1u]).GetZ()) <=
            holo::EpsilonT<Scalar>::value)
    {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t RansacLine3FittingProblem<T>::ComputeModel(std::vector<uint64_t> const& indices, ModelType& model) const
{
    ///@brief Need 2 samples
    if (indices.size() != GetRequiredSampleSize())
    {
        LOG(WARNING) << "Line3 model needs at least " << GetRequiredSampleSize() << " sample points!";
        return false;
    }

    model = ModelType(adapter_.GetSample(indices[0u]), adapter_.GetSample(indices[1u]));

    return model.IsValid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename RansacLine3FittingProblem<T>::ModelType
RansacLine3FittingProblem<T>::OptimizeModel(std::vector<uint64_t> const& inliers, ModelType const& model) const
{
    ///@brief Need more than the minimum sample size to make a difference
    if (inliers.empty())
    {
        LOG(WARNING) << "Not enough inliers to refine/optimize the model's coefficients";
        return model;
    }

    ///@brief Load samples data to compute 3*3 covariance matrix
    holo::numerics::MatrixXT<Scalar> covariance_matrix(3u, 3u);
    covariance_matrix.SetZero();
    holo::numerics::VectorXT<Scalar> vec_mean(3u);         ///< mean value of all points
    holo::numerics::VectorXT<Scalar> vec_square_mean(6u);  ///< mean value of x^2, x*y, x*z, y^2, y*z, z^2

    for (uint64_t row_index = 0u; row_index < inliers.size(); row_index++)
    {
        Scalar const x = adapter_.GetSample(inliers[row_index]).GetX();
        Scalar const y = adapter_.GetSample(inliers[row_index]).GetY();
        Scalar const z = adapter_.GetSample(inliers[row_index]).GetZ();
        vec_mean(0u) += x;
        vec_mean(1u) += y;
        vec_mean(2u) += z;
        vec_square_mean(0u) += x * x;
        vec_square_mean(1u) += x * y;
        vec_square_mean(2u) += x * z;
        vec_square_mean(3u) += y * y;
        vec_square_mean(4u) += y * z;
        vec_square_mean(5u) += z * z;
    }

    ///@brief Calculate mean value
    vec_mean /= static_cast<Scalar>(inliers.size());
    vec_square_mean /= static_cast<Scalar>(inliers.size());

    covariance_matrix(0u) = vec_square_mean(0u) - vec_mean(0u) * vec_mean(0u);
    covariance_matrix(1u) = vec_square_mean(1u) - vec_mean(0u) * vec_mean(1u);
    covariance_matrix(2u) = vec_square_mean(2u) - vec_mean(0u) * vec_mean(2u);
    covariance_matrix(4u) = vec_square_mean(3u) - vec_mean(1u) * vec_mean(1u);
    covariance_matrix(5u) = vec_square_mean(4u) - vec_mean(1u) * vec_mean(2u);
    covariance_matrix(8u) = vec_square_mean(5u) - vec_mean(2u) * vec_mean(2u);
    covariance_matrix(3u) = covariance_matrix(1u);
    covariance_matrix(6u) = covariance_matrix(2u);
    covariance_matrix(7u) = covariance_matrix(5u);

    /**
     * @brief Extract eigenvalues and eigenvectors
     *
     * @note The maximum eigenvalue corresponds eigenvector (in V) is line direction.
     */
    holo::numerics::MatrixXT<Scalar> U;
    holo::numerics::VectorXT<Scalar> S;
    holo::numerics::MatrixXT<Scalar> V;
    holo::eigen_solver::SVD(covariance_matrix, U, S, V);
    Point3Type line_direction(V.GetCol(0u));  ///< Get line direction
    Point3Type start_point(vec_mean(0u), vec_mean(1u), vec_mean(2u));

    /**
     * @note The parameter function of line is
     *       x = start_point(0) - line_direction(0) * t
     *       y = start_point(1) - line_direction(1) * t
     *       z = start_point(2) - line_direction(2) * t
     *       Let t=1, we can get a point (end point).
     */
    Point3Type end_points = start_point - line_direction;

    return ModelType(start_point, end_points);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
float64_t RansacLine3FittingProblem<T>::GetDistanceToModel(ModelType const& model, uint64_t const index) const
{
    /***
     * @brief The norm of cross product of two vectors is equal to the parallelogram's area that they span out.
     *
     * @note Vector a = line_pt - pt, vector b is the unit direction vector of the line.
     *       We have the equation ||a X b|| = ||b|| * D, where D is the distance from point pt to line_pt,
     *       and b is an unit vector. So D = ||a X b||.
     */
    holo::geometry::Point3T<T> const a = model.GetStartPoint() - adapter_.GetSample(index);
    holo::numerics::Vector3d const   a_vec(a.GetX(), a.GetY(), a.GetZ());
    holo::numerics::Vector3d line_vec(model.GetDirection()[0u], model.GetDirection()[1u], model.GetDirection()[2u]);
    line_vec.Normalize();
    float64_t const distance = a_vec.Cross(line_vec).GetNorm();

    return distance;
}
}  // namespace pointcloud
}  // namespace holo