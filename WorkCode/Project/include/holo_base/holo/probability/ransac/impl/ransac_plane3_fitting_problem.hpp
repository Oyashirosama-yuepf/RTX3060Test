/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_plane3_fitting_problem.hpp
 * @brief this class represents ransac solving specific fitting plane3 problem
 * @author luopei(luopei@holomaitc.com)
 * @date "2022-01-12"
 */

#include <holo/numerics/eigen_solver.h>

namespace holo
{
/**
 * @brief Construct with adapter and random_seed
 *
 * @param adapter data container adapter
 * @param random_seed random_seed
 */
template <typename T>
RansacPlane3FittingProblemT<T>::RansacPlane3FittingProblemT(AdapterType const& adapter, bool random_seed)
  : Base(adapter.GetSampleSize(), random_seed), adapter_(adapter)
{
    static_assert(std::is_floating_point<ScalarType>::value, "");
}

/**
 * @brief Destructor
 */
template <typename T>
RansacPlane3FittingProblemT<T>::~RansacPlane3FittingProblemT() noexcept
{
}

/**
 * @brief Check if a set of samples for model generation is degenerate
 *
 * @param sample The indices of the samples we attempt to use for
 *            model instantiation.
 * @return Is this set of samples ok?
 */
template <typename T>
bool_t RansacPlane3FittingProblemT<T>::IsSampleGood(std::vector<uint64_t> const& sample) const
{
    (void)sample;
    return true;
}

/**
 * @brief Compute a model from a set of samples.
 *
 * @param[in] indices The indices of the samples we use for the hypothesis
 * @param[out] out_model The computed model.
 */
template <typename T>
bool_t RansacPlane3FittingProblemT<T>::ComputeModel(std::vector<size_t> const& indices, ModelType& out_model) const
{
    /// check of input cardinality
    if (indices.size() < GetRequiredSampleSize())
    {
        LOG(WARNING) << "insufficient";
        return false;
    }

    /// fit a plane
    try
    {
        out_model =
            ModelType(adapter_.GetSample(indices[0]), adapter_.GetSample(indices[1]), adapter_.GetSample(indices[2]));
    }
    catch (...)
    {
        return false;
    }
    return true;
}

/**
 * @brief Refine the model over a given set (inliers)
 * @ref
 https://math.stackexchange.com/questions/3869/what-is-the-intuitive-relationship-between-svd-and-pca/3871#3871

 * @param inliers The indices of the inlier samples supporting the model.
 * @param model current estimated model
 * @return optimized model
 */
template <typename T>
typename RansacPlane3FittingProblemT<T>::ModelType
RansacPlane3FittingProblemT<T>::OptimizeModel(std::vector<size_t> const& inliers, ModelType const& model) const
{
    if (inliers.empty())
    {
        LOG(WARNING) << "number of inliers is zero";
        return model;
    }

    /// calculation covariance matrix
    holo::numerics::MatrixXT<ScalarType> mat_inliers(inliers.size(), 3U);
    holo::numerics::VectorXT<ScalarType> vec_mean(3U);

    /// load samples data to  matrix
    for (size_t i = 0; i < inliers.size(); i++)
    {
        mat_inliers(i, 0) = (adapter_.GetSample(inliers[i])).GetX();
        mat_inliers(i, 1) = (adapter_.GetSample(inliers[i])).GetY();
        mat_inliers(i, 2) = (adapter_.GetSample(inliers[i])).GetZ();

        vec_mean(0u) += mat_inliers(i, 0u);
        vec_mean(1u) += mat_inliers(i, 1u);
        vec_mean(2u) += mat_inliers(i, 2u);
    }

    /// each column mean value
    vec_mean /= (ScalarType)inliers.size();

    /// The corresponding value of each column subtracts the mean
    for (size_t i = 0; i < mat_inliers.GetRows(); i++)
    {
        mat_inliers(i, 0u) -= vec_mean(0u);
        mat_inliers(i, 1u) -= vec_mean(1u);
        mat_inliers(i, 2u) -= vec_mean(2u);
    }

    /// mat_covar = u * diag(s) * v
    holo::numerics::MatrixXT<ScalarType> u;
    holo::numerics::VectorXT<ScalarType> s;
    holo::numerics::MatrixXT<ScalarType> v;

    /// minimum eigenvalue corresponds eigenvector is line model.
    (void)eigen_solver::SVD(mat_inliers, u, s, v);
    DLOG(INFO) << "u: " << std::endl
               << u << std::endl
               << "s: " << std::endl
               << s << std::endl
               << "v: " << std::endl
               << v;

    /// get the optimal parameters after optimization
    /// para_a * x + para_b * y + para_c * z + para_d = 0
    ScalarType para_a = static_cast<ScalarType>(0.0);
    ScalarType para_b = static_cast<ScalarType>(0.0);
    ScalarType para_c = static_cast<ScalarType>(0.0);
    ScalarType para_d = static_cast<ScalarType>(0.0);
    para_a            = v(0u, 2u);
    para_b            = v(1u, 2u);
    para_c            = v(2u, 2u);
    para_d            = -(para_a * vec_mean(0u) + para_b * vec_mean(1u) + para_c * vec_mean(2u));
    DLOG(INFO) << "optimized:" << para_a << "," << para_b << "," << para_c << "," << para_d;
    return ModelType(para_a, para_b, para_c, para_d);
}

/**
 * @brief Compute the distances of all samples whith respect to given model.
 *
 * @param model The model hypothesis.
 * @param indices The indices of the samples of which we compute distances.
 * @return scores The resultant distances of the selected samples. Low distances mean a good fit.
 */
template <typename T>
float64_t RansacPlane3FittingProblemT<T>::GetDistanceToModel(ModelType const& model, size_t const index) const
{
    return model.Dist(adapter_.GetSample(index));
}

}  // namespace holo
