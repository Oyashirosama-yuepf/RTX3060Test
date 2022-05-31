/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_problem.h
 * @brief ransac problem
 * @author luopei (), luopei@holomatic.com
 * @date 2018-03-28
 */

#include <holo/log/hololog.h>
#include <holo/probability/ransac/ransac_problem.h>
#include <cassert>

namespace holo
{
/**
 * @brief constructor
 *
 * @param sample_size the size of samples
 * @param random_seed seed for sampling
 */
template <typename _ModelType>
RansacProblemT<_ModelType>::RansacProblemT(uint64_t const sample_size, bool_t const random_seed)
  : maximum_sample_checks_(10u)
{
    rg_distribution_ =
        std::make_shared<std::uniform_int_distribution<uint64_t> >(0u, std::numeric_limits<uint64_t>::max());

    if (random_seed)
    {
        rg_algorithm_.seed(static_cast<uint32_t>(std::time(0)));
    }
    else
    {
        rg_algorithm_.seed(12345u);
    }

    rg_ = std::make_shared<std::function<uint64_t()> >(std::bind(*rg_distribution_, rg_algorithm_));

    SetUniformIndices(sample_size);
}

/**
 * @brief destructor
 *
 */
template <typename _ModelType>
RansacProblemT<_ModelType>::~RansacProblemT() noexcept
{
}

/**
 * @brief Get samples for hypothesis generation.
 *
 * @param[in] iterations We won't try forever to get a good sample, this
 *            parameter keeps track of the iterations.
 * @param[out] samples The indices of the samples we attempt to use.
 */
template <typename _ModelType>
void RansacProblemT<_ModelType>::DrawSamples(uint64_t& iterations, std::vector<uint64_t>& samples)
{
    if (!indices_)
    {
        LOG(WARNING) << "ransac_problem.DrawSamples: cannot succeed because the indices is not assigned yet ";
        return;
    }

    if ((uint64_t)indices_->size() < GetRequiredSampleSize())
    {
        LOG(WARNING) << "ransac_problem.GetSamples: cannot get " << GetRequiredSampleSize() << " samples out of "
                     << indices_->size();
        samples.clear();

        /* set a maximum value to make ransac stop */
        iterations = std::numeric_limits<uint64_t>::max();
        return;
    }

    /* Get a second point which is different than the first */
    for (uint64_t iter = 0u; iter < maximum_sample_checks_; ++iter)
    {
        samples = DrawIndexSample(GetRequiredSampleSize());

        /* If it's a good sample, stop here */
        if (IsSampleGood(samples))
        {
            return;
        }
    }

    LOG(WARNING) << "ransac_problem.GetSamples: Could not select " << GetRequiredSampleSize() << " sample points in "
                 << maximum_sample_checks_ << " iterations!";

    samples.clear();
}

/**
 * @brief Select all the inlier samples whith respect to given model.
 *
 * @param model The model hypothesis.
 * @param threshold A maximum admissible distance threshold for determining the inliers and outliers.
 * @return inliers The resultant indices of inlier samples.
 */
template <typename _ModelType>
std::vector<uint64_t> RansacProblemT<_ModelType>::SelectWithinDistance(ModelType const& model,
                                                                       float64_t const  threshold) const
{
    std::vector<float64_t> const dist = GetDistancesToModel(model);

    std::vector<uint64_t> inliers;
    inliers.reserve(indices_->size());

    for (uint64_t i = 0u; i < (uint64_t)dist.size(); ++i)
    {
        if (dist[i] < threshold)
        {
            inliers.push_back((*indices_)[i]);
        }
    }
    return inliers;
}

/**
 * @brief set indices of sample.
 *
 * @param indices is constant that indicates indices vector of sample.
 */
template <typename _ModelType>
void RansacProblemT<_ModelType>::SetIndices(std::vector<uint64_t> const& indices)
{
    /* indices_ is a deep copy of indices.*/
    indices_ = std::make_shared<std::vector<uint64_t> >(indices);

    /* shuffled_induces is variable in order to obtain random sample */
    shuffled_indices_ = *indices_;
}

/**
 * @brief Sub-function for getting samples for hypothesis generation.
 *
 * @param sample_size required sample size
 * @return sample The indices of the samples we attempt to use.
 */
template <typename _ModelType>
std::vector<uint64_t> RansacProblemT<_ModelType>::DrawIndexSample(uint64_t const sample_size)
{
    uint64_t const index_size = shuffled_indices_.size();
    assert(index_size);

    for (uint64_t i = 0u; i < sample_size; ++i)
    {
        /* get random number in [i,index_size -i), if only the index is different, can ensure first i indices different.
         */
        std::swap(shuffled_indices_[i], shuffled_indices_[i + (GetRandomNumber() % (index_size - i))]);
    }
    std::vector<uint64_t> sample(sample_size);
    (void)std::copy(shuffled_indices_.begin(), shuffled_indices_.begin() + sample_size, sample.begin());
    return sample;
}

/**
 * @brief Compute the distances of all samples which respect to given model.
 *
 * @param model The model hypothesis.
 * @return distances The resultant distances of all samples. Low distances mean a good fit.
 */
template <typename _ModelType>
std::vector<float64_t> RansacProblemT<_ModelType>::GetSelectedDistancesToModel(
    ModelType const& model, std::vector<uint64_t> const& indices) const
{
    std::vector<float64_t> scores(indices.size());
    for (uint64_t i = 0u; i < (uint64_t)indices.size(); ++i)
    {
        scores[i] = GetDistanceToModel(model, indices[i]);
    }
    return scores;
}

/**
 * @brief Use this method if you want to use all samples.
 *
 * @param num The number of samples.
 */
template <typename _ModelType>
void RansacProblemT<_ModelType>::SetUniformIndices(uint64_t const num)
{
    indices_ = std::make_shared<std::vector<uint64_t> >(num);
    std::iota(indices_->begin(), indices_->end(), 0u);
    shuffled_indices_ = *indices_;
}

}  // namespace holo
