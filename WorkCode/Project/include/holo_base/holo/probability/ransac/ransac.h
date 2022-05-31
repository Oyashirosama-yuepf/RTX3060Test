/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac.h
 * @brief this class defines RANSAC algorithm
 * @author jiaxing.zhao, duyanwei
 * @date 2019-09-04
 */

#ifndef HOLO_NUMERICS_RANSAC_H_
#define HOLO_NUMERICS_RANSAC_H_

#include <holo/core/types.h>
#include <iostream>
#include <memory>
#include <vector>

namespace holo
{
/**
 * @addtogroup numerics
 * @{
 */

/**
 * @brief ransac class
 *
 * @details the ransac algorithm is templated on a problem type, such as line fitting, triangulation, fundamental matrix
 *          computation, or pnp pose estimation.
 *
 * @tparam _ProblemType, a correct ProblemType must be derived from class RansacProblemT, it must provide a defined
 *         ModelType and implement the algorithm to compute and optimize the model with selected samples, it must also
 *         provide a model evaluation method
 */
template <typename _ProblemType>
class Ransac
{
public:
    using ProblemType = _ProblemType;
    using ModelType   = typename ProblemType::ModelType;

    /**
     * @brief define parameters for Ransac
     */
    struct Parameters
    {
        /**
         * @brief the threshold to classify inliers / outliers, this can be further
         *        specialized by putting a classification functor in the Problem
         */
        float64_t threshold;

        /**
         * @brief confidence level [0.0 - 1.0] that the result is the best model
         */
        float64_t confidence;

        /**
         * @brief maximum number of ransac iterations
         */
        uint64_t max_iterations;

        /**
         * @brief enable optimizer
         *
         * @details sometimes we disable optimizer to save time
         */
        bool_t enable_optimizer;

        /**
         * @brief Construct a new Ransac Parameters object
         *
         * @param _threshold threshold
         * @param _confidence  confidence
         * @param _max_iterations max iteration
         * @param _enable_optimizer enable optimizer
         */
        Parameters(float64_t const _threshold = 0.01, float64_t const _confidence = 0.95,
                   uint64_t const _max_iterations = 1000u, bool_t const _enable_optimizer = true)
          : threshold(_threshold)
          , confidence(_confidence)
          , max_iterations(_max_iterations)
          , enable_optimizer(_enable_optimizer)
        {
        }
    };

    /**
     * @brief disable default constructor, copy constructor and assignment operator
     *
     */
    Ransac() = delete;

    Ransac(Ransac const&) = delete;

    Ransac& operator=(Ransac const&) = delete;

    /**
     * @brief Construct a new Ransac object
     *
     * @param problem ransac problem
     * @param params ransac parameters
     */
    Ransac(std::shared_ptr<ProblemType> const& problem, Parameters const& params = Parameters())
      : state_(), problem_(problem), params_(params), optimized_model_()
    {
    }

    /**
     * @brief return the best model so far
     */
    ModelType const& GetBestModel() const
    {
        return state_.best_model;
    }

    /**
     * @brief return the best model inlier indices so far
     */
    std::vector<uint64_t> const& GetInliers() const
    {
        return state_.best_model_inlier_indices;
    }

    /**
     * @brief return all the inliers to refine the model.
     */
    ModelType const& GetOptimizedModel() const
    {
        return optimized_model_;
    }

    /**
     * @brief perform iteration of the ransac algorithm
     *
     * @return success or not
     */
    bool_t Compute();

private:
    /**
     * @brief define ransan internal state
     *
     */
    struct State
    {
        /**
         * @brief the current iteration
         */
        uint64_t iteration;

        /**
         * @brief best model so far
         */
        ModelType best_model;

        /**
         * @brief the data indices used to compute the best_model so far
         */
        std::vector<uint64_t> best_model_hypothesis_indices;

        /**
         * @brief the indices for inliers for the best model so far
         */
        std::vector<uint64_t> best_model_inlier_indices;

        /**
         * @brief Construct a new State object
         *
         */
        State() : iteration(0u)
        {
        }

        /**
         * @brief return best inlier count so far
         */
        uint64_t GetBestInlierCount() const
        {
            return static_cast<uint64_t>(best_model_inlier_indices.size());
        }
    };

    /**
     * @brief ransac state
     */
    State state_;

    /**
     * @brief the problem to be solved
     */
    std::shared_ptr<ProblemType> problem_;

    /**
     * @brief ransac parameters
     */
    Parameters params_;

    /**
     * @brief optimized model
     */
    ModelType optimized_model_;

};  // Ransac

/**
 * @}
 *
 */

}  // namespace holo

#endif  // HOLO_NUMERICS_RANSAC_H_
