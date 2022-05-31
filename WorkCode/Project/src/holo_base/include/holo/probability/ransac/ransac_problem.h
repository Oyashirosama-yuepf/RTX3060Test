/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_problem.h
 * @brief this is a base class of ransac problem
 * @author jiaxing.zhao, duyanwei
 * @date 2019-09-04
 */

#ifndef HOLO_NUMERICS_RANSAC_PROBLEM_H_
#define HOLO_NUMERICS_RANSAC_PROBLEM_H_

#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include <holo/core/types.h>

namespace holo
{
/**
 * @addtogroup numerics
 * @{
 */

/**
 * @brief define ransac problem
 *
 * @tparam _ModelType, could be Point3, Matrix3, etc
 */
template <typename _ModelType>
class RansacProblemT
{
public:
    using ModelType = _ModelType;

    /**
     * @brief disable default constructor, copy constructor and assignment operator
     *
     */
    RansacProblemT() = delete;

    /**
     * @brief disable default copy constructor
     *
     */
    RansacProblemT(RansacProblemT const&) = delete;

    /**
     * @brief distable assignment operator
     */
    RansacProblemT& operator=(RansacProblemT const&) = delete;

    /**
     * @brief constructor
     *
     * @param sample_size the size of samples
     * @param random_seed seed for sampling
     */
    RansacProblemT(uint64_t const sample_size, bool_t const random_seed = true);

    /**
     * @brief destructor
     *
     */
    virtual ~RansacProblemT() noexcept;

    /**
     * @brief Get samples for hypothesis generation.
     *
     * @param[in] iterations We won't try forever to get a good sample, this
     *            parameter keeps track of the iterations.
     * @param[out] samples The indices of the samples we attempt to use.
     */
    virtual void DrawSamples(uint64_t& iterations, std::vector<uint64_t>& samples);

    /**
     * @brief Check if a set of samples for model generation is degenerate
     *
     * @param sample The indices of the samples we attempt to use for
     *            model instantiation.
     * @return Is this set of samples ok?
     */
    virtual bool_t IsSampleGood(std::vector<uint64_t> const& sample) const = 0;

    /**
     * @brief Get a pointer to the vector of indices used.
     *
     * @return A pointer to the vector of indices used.
     */
    std::shared_ptr<std::vector<uint64_t> > GetIndices() const
    {
        return indices_;
    }

    /**
     * @brief Get the number of samples needed for a hypothesis generation.
     *
     * @details Needs implementation in the child class.
     * @return The number of samples needed for hypothesis generation.
     */
    virtual uint64_t GetRequiredSampleSize() const = 0;

    /**
     * @brief Compute a model from a set of samples. Needs implementation in the child-class.
     *
     * @param[in] indices The indices of the samples we use for the hypothesis.
     * @param[out] out_model The computed model.
     */
    virtual bool_t ComputeModel(std::vector<uint64_t> const& indices, ModelType& out_model) const = 0;

    /**
     * @brief Compute the distances of all samples whith respect to given model.
     *        Needs implementation in the child-class.
     *
     * @param model The model hypothesis.
     * @param index The index of the samples of which we compute distances.
     * @return scores The resultant distances of the selected samples. Low distances mean a good fit.
     */
    virtual float64_t GetDistanceToModel(ModelType const& model, uint64_t const index) const = 0;

    /**
     * @brief Select all the inlier samples whith respect to given model.
     *
     * @param model The model hypothesis.
     * @param threshold A maximum admissible distance threshold for determining the inliers and outliers.
     * @return inliers The resultant indices of inlier samples.
     */
    virtual std::vector<uint64_t> SelectWithinDistance(ModelType const& model, float64_t const threshold) const;

    /**
     * @brief Refine the model over a given set (inliers).
     *
     * @details Needs implementation in the child-class.
     * @param inliers The indices of the inlier samples supporting the model.
     * @param model The initial guess for the model.
     * @return optimized_model The resultant refined model.
     */
    virtual ModelType OptimizeModel(std::vector<uint64_t> const& inliers, ModelType const& model) const = 0;

    /**
     * @brief set indices of sample.
     *
     * @param indices is constant that indicates indices vector of sample.
     */
    void SetIndices(std::vector<uint64_t> const& indices);

    /**
     * @brief Get a random number.
     */
    uint64_t GetRandomNumber()
    {
        return ((*rg_)());
    }

protected:
    /**
     * @brief Sub-function for getting samples for hypothesis generation.
     *
     * @param sample_size required sample size
     * @return sample The indices of the samples we attempt to use.
     */
    std::vector<uint64_t> DrawIndexSample(uint64_t const sample_size);

    /**
     * @brief Compute the distances of all samples which respect to given model.
     *
     * @param model The model hypothesis.
     * @return distances The resultant distances of all samples. Low distances mean a good fit.
     */
    virtual std::vector<float64_t> GetDistancesToModel(ModelType const& model) const
    {
        return GetSelectedDistancesToModel(model, *indices_);
    }

    /**
     * @brief compute the distance of a sample w.r.t a given model
     */
    std::vector<float64_t> GetSelectedDistancesToModel(ModelType const&             model,
                                                       std::vector<uint64_t> const& indices) const;

    /**
     * @brief Use this method if you want to use all samples.
     *
     * @param num The number of samples.
     */
    void SetUniformIndices(uint64_t const num);

    /**
     * @brief The maximum number of times we try to extract a valid set of samples
     */
    uint64_t const maximum_sample_checks_;

    /**
     * @brief The indices of the samples we are using for solving the entire problem.
     *
     * @details These are not the indices for generating a hypothesis, but all indices
     *          for model verification
     */
    std::shared_ptr<std::vector<uint64_t> > indices_;

    /**
     * @brief A shuffled version of the indices used for random sample drawing
     */
    std::vector<uint64_t> shuffled_indices_;

    /**
     * @brief std-based random number generator algorithm.
     */
    std::mt19937 rg_algorithm_;

    /**
     * @brief std-based random number generator distribution.
     */
    std::shared_ptr<std::uniform_int_distribution<uint64_t> > rg_distribution_;

    /**
     * @brief std-based random number generator.
     */
    std::shared_ptr<std::function<uint64_t()> > rg_;

};  // class RansacProblem

/**
 * @}
 *
 */

}  // namespace holo

#endif  // HOLO_NUMERICS_RANSAC_PROBLEM_H_
