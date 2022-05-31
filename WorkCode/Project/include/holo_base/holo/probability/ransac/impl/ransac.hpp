/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac.hpp
 * @brief ransac
 * @author luo pei (), luopei@holomatic.com
 * @date 2018-03-27
 */

#include <assert.h>
#include <cmath>
#include <limits>

#include <holo/log/hololog.h>
#include <holo/probability/ransac/ransac.h>

namespace holo
{
/**
 * @brief perform iteration of the ransac algorithm
 *
 * @return success or not
 */
template <typename _ProblemType>
bool_t Ransac<_ProblemType>::Compute()
{
    assert(problem_ != nullptr);

    uint64_t const max_skipped_count    = 10u;
    uint64_t const required_sample_size = problem_->GetRequiredSampleSize();
    uint64_t const total_sample_size    = problem_->GetIndices()->size();

    /* estimate of the required number of iterations */
    uint64_t upper_bound_required_iterations = params_.max_iterations;

    uint64_t skipped_count = 0u;

    std::vector<uint64_t> current_selection(required_sample_size);

    ModelType current_model;

    /* Iterate until done */
    while ((state_.iteration < upper_bound_required_iterations) && (skipped_count < max_skipped_count))
    {
        /* Get X samples which satisfy the model criteria */
        problem_->DrawSamples(state_.iteration, current_selection);

        /** if no data, we can terminate immediately */
        if (current_selection.size() < required_sample_size)
        {
            LOG(WARNING) << "ransac.iterate(): failed to DrawSamples";
            break;
        }

        /* check if selected sample is vaild for the model. */
        if (!problem_->ComputeModel(current_selection, current_model))
        {
            ++skipped_count;
            continue;
        }

        std::vector<uint64_t> current_inliers = problem_->SelectWithinDistance(current_model, params_.threshold);

        /* Is it a better model? */
        if (current_inliers.size() > state_.GetBestInlierCount())
        {
            /* Save the current model/inlier selection as being the best so far */
            state_.best_model                    = current_model;
            state_.best_model_hypothesis_indices = current_selection;
            state_.best_model_inlier_indices     = current_inliers;

            /* estimate the required number of iterations ( log(1-confidence) / log(1-w^n) ) where w is the inlier rate,
             * n is the model complexity */
            float64_t w =
                static_cast<float64_t>(state_.GetBestInlierCount()) / static_cast<float64_t>(total_sample_size);
            float64_t p_no_outliers = 1.0 - std::pow(w, static_cast<float64_t>(required_sample_size));

            /* bounded this value between 0 and 1 */
            p_no_outliers = (std::max)(std::numeric_limits<float64_t>::epsilon(), p_no_outliers);
            p_no_outliers = (std::min)(1.0 - std::numeric_limits<float64_t>::epsilon(), p_no_outliers);

            /* Avoid division by 0. */
            upper_bound_required_iterations = (size_t)(std::log(1.0 - params_.confidence) / std::log(p_no_outliers));
        }

        DLOG(INFO) << "ransac.iterate: trial " << state_.iteration << "/" << upper_bound_required_iterations
                   << ", current inlier proportion is: "
                   << 100.0 * current_inliers.size() / (float64_t)total_sample_size
                   << " (best inlier proportion so far is: "
                   << 100.0 * state_.GetBestInlierCount() / (float64_t)total_sample_size << ").";

        /* increment iteration count */
        ++state_.iteration;

        /* check for stopping criterion */
        if (state_.iteration >= params_.max_iterations)
        {
            LOG(WARNING) << "ransac.iterate: RANSAC reached the maximum number of trials.";
            break;
        }
    }

    LOG(INFO) << "ransac.Compute: best model with "
              << 100.0 * state_.best_model_inlier_indices.size() / (float64_t)total_sample_size << "% inliers";

    if (state_.GetBestInlierCount() < required_sample_size)
    {
        return false;
    }

    /* Refine the model over a given inliers */
    if (params_.enable_optimizer)
    {
        optimized_model_ = problem_->OptimizeModel(state_.best_model_inlier_indices, state_.best_model);
    }
    else
    {
        optimized_model_ = state_.best_model;
    }

    return true;
}

}  // namespace holo
