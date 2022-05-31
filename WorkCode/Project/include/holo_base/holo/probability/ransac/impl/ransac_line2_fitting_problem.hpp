/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_line2_fitting_problem.hpp
 * @brief ransac_line2_fitting_problem.hpp
 * @author luopei (), luopei@holomatic.com
 * @date 2018-03-28
 */

#include <holo/numerics/eigen_solver.h>

namespace holo
{
/**
 * @brief Construct a new Ransac Line 2 Fitting Problem T object
 *
 * @param adapter data container adapter
 * @param random_seed random_seed
 */
template <typename T>
RansacLine2FittingProblemT<T>::RansacLine2FittingProblemT(AdapterType const& adapter, bool random_seed)
  : Base(adapter.GetSampleSize(), random_seed), adapter_(adapter)
{
    static_assert(std::is_floating_point<Scalar>::value, "");
}

/**
 * @brief Destroy the Ransac Line 2 Fitting Problem T object
 *
 */
template <typename T>
RansacLine2FittingProblemT<T>::~RansacLine2FittingProblemT() noexcept
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
bool_t RansacLine2FittingProblemT<T>::IsSampleGood(std::vector<uint64_t> const& sample) const
{
    (void)sample;
    return true;
}

/**
 * @brief Compute a model from a set of samples.
 * @param[in] indices The indices of the samples we use for the hypothesis.
 * @param[out] out The computed model.
 * @return Success?
 */
template <typename T>
bool_t RansacLine2FittingProblemT<T>::ComputeModel(std::vector<uint64_t> const& indices, ModelType& out) const
{
    /* check of input cardinality */
    if (indices.size() < GetRequiredSampleSize())
    {
        LOG(WARNING) << "insufficient indices";
        return false;
    }

    /* fit a line */
    try
    {
        out = ModelType(adapter_.GetSample(indices[0]), adapter_.GetSample(indices[1]));
    }
    catch (...)
    {
        return false;
    }
    return true;
}

/**
 * @brief Refine the model over a given set (inliers).
 * @ref
 * https://math.stackexchange.com/questions/3869/what-is-the-intuitive-relationship-between-svd-and-pca/3871#3871
 * @param inliers The indices of the inlier samples supporting the model.
 * @param model current estimated model
 * @return optimized model
 */
template <typename T>
typename RansacLine2FittingProblemT<T>::ModelType
RansacLine2FittingProblemT<T>::OptimizeModel(std::vector<size_t> const& inliers, ModelType const& model) const
{
    if (inliers.empty())
    {
        LOG(WARNING) << "number of inliers is zero";
        return model;
    }

    /* compute coefficient matrix */
    holo::numerics::MatrixXT<Scalar> mat_inliers(inliers.size(), 2u);

    holo::numerics::VectorXT<Scalar> vec_mean(2u);

    /* load samples data to  matrix */
    for (uint64_t i = 0u; i < inliers.size(); i++)
    {
        mat_inliers(i, 0u) = (adapter_.GetSample(inliers[i])).GetX();
        mat_inliers(i, 1u) = (adapter_.GetSample(inliers[i])).GetY();
        vec_mean(0u) += mat_inliers(i, 0u);
        vec_mean(1u) += mat_inliers(i, 1u);
    }

    /* each column mean value */
    vec_mean /= (Scalar)inliers.size();

    /** The corresponding value of each column subtracts the mean of each column */
    for (uint8_t i = 0u; i < mat_inliers.GetRows(); i++)
    {
        mat_inliers(i, 0u) -= vec_mean(0u);
        mat_inliers(i, 1u) -= vec_mean(1u);
    }

    /* SVD to decompose coefficient matrix: mat = u * diag(s) * v */
    holo::numerics::MatrixXT<Scalar> U;
    holo::numerics::VectorXT<Scalar> S;
    holo::numerics::MatrixXT<Scalar> V;

    /**
     * maximum eigenvalue corresponds eigenvector(in v) is line direction,
     * minimum eigenvalue corresponds eigenvector is line normal.
     */
    (void)eigen_solver::SVD(mat_inliers, U, S, V);

    /* get the optimal parameters after optimization */
    /* para_a * x + para_b * y + para_c = 0 */
    Scalar para_a = static_cast<Scalar>(0.0);
    Scalar para_b = static_cast<Scalar>(0.0);
    Scalar para_c = static_cast<Scalar>(0.0);
    para_a        = V(0u, 1u);
    para_b        = V(1u, 1u);
    para_c        = -(para_a * vec_mean(0u) + para_b * vec_mean(1u));
    Vector3Type vector3(para_a, para_b, para_c);
    return ModelType(vector3);
}

/**
 * @brief Compute the distances of all samples whith respect to given model.
 * @param model The model hypothesis.
 * @param index The index of the samples of which we compute distances.
 * @return scores The resultant distances of the selected samples. Low distances mean a good fit.
 */
template <typename T>
float64_t RansacLine2FittingProblemT<T>::GetDistanceToModel(ModelType const& model, uint64_t const index) const
{
    return model.Dist(adapter_.GetSample(index));
}

}  // namespace holo
