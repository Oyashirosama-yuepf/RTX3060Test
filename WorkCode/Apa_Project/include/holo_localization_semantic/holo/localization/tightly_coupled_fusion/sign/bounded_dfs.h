/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bounded_dfs.h
 * @brief A class which do bounded dfs
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date Dec 16, 2019
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_BOUNDED_DFS_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_BOUNDED_DFS_H_

#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <holo/localization/tightly_coupled_fusion/sign/data_association_problem.h>
#include <holo/localization/tightly_coupled_fusion/sign/types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace sign
{
/**
 * @addtogroup sign
 * @{
 *
 */

/**
 * @brief The result of DFS.
 *
 * @tparam Problem a problem that have finite solutions.
 */
template <class Problem>
class Result
{
public:
    using Solution = Correspondence;

    /**
     * @brief Construct a new result.
     *
     */
    Result() noexcept : num_considered(0u)
    {
    }

    /**
     * @brief Operator ==.
     *
     * @param other A result.
     * @return Return false if not equal.
     */
    bool_t operator==(const Result& other) const
    {
        return solution == other.solution && num_considered == other.num_considered;
    }

    Solution solution;        ///< The solution.
    uint32_t num_considered;  ///< The number of considered.

};  // class result

//********************************************************************
// ALGORITHM
//********************************************************************
/**
 * Depth first search with bounds.
 * From "Heuristic Search: theory and applications", 2012
 * Chapter by Edelkamp & Schrödl, preview at
 * https://www.sciencedirect.com/topics/computer-science/branch-and-bound-algorithm-design
 *
 * The algorithm above is a graph search, but we instead assume a Solution type
 * that is incrementally expanded until it forms a solution.
 *
 * Template argument Problem needs:
 *  - Solution type, with default constructor
 *  - a function `Guess()` which returns a guess for the solution.
 *  - a function `Cost(Solution)` which returns the cost of a solution.
 *  - a predicate `Goal(Solution)` which is true if solution complete
 *  - a function `Expand(Solution)` which returns a multimap<Scalar,Solution>,
 *    where the Scalar is a heuristic for the cost-to-go for this solution.
 */
template <class Problem>
class BoundedDFS
{
public:
    using Solution   = Correspondence;
    using Successors = typename Problem::Successors;

    /**
     * @brief Params of bounded DFS.
     *
     */
    struct Params
    {
        uint32_t verbose = {0u};
    };

    /**
     * @brief Construct a new bounded DFS.
     *
     * @param problem The problem.
     * @param params The parameters of bounded DFS.
     */
    BoundedDFS(const Problem& problem, const Params& params) noexcept : problem_(problem), params_(params)
    {
    }

    /**
     * @brief Run the DFS search.
     *
     * @return The result.
     */
    Result<Problem> Run() const
    {
        // Get a solution guess.
        Solution guess = problem_.Guess();

        // Initialize upper bound from initial guess.
        Scalar upper_bound = problem_.Cost(guess);

        // Call recursive search.
        Result<Problem> result;
        dFBnB(result.solution, 0.0, &upper_bound, &result);

        return result;
    }

    /**
     * @brief Output stream.
     *
     * @param os Output stream.
     * @param result The result.
     *
     * @return Output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Result<Problem>& result)
    {
        os << "solution: " << result.solution << std::endl;
        os << "num_considered: " << result.num_considered << std::endl;
        return os;
    }

private:
    /**
     * @brief Recursive dfs with bounds, algorithm 5.4 in reference.
     *
     * @param partial The solution type.
     * @param cost The coat of partial.
     * @param upper_bound The upper bound on all solution costs, might be updated.
     * @param result Might be updated.
     */
    void dFBnB(const Solution& partial, Scalar cost, Scalar* upper_bound, Result<Problem>* result) const
    {
        result->num_considered += 1u;
        logEntry(partial, cost, *upper_bound, *result);

        if (problem_.Goal(partial))
        {
            // We found a goal: if better, update upper bound and result.
            if (cost < *upper_bound)
            {
                result->solution = partial;
                *upper_bound     = cost;
            }
        }
        else
        {
            // Expand partial solution into more complete solutions.
            Successors successors = problem_.Expand(partial);
            logSuccessors(successors);
            for (const std::pair<Scalar, Solution>& kv : successors)
            {
                Scalar heuristic  = kv.first;
                Scalar lowerBound = cost + heuristic;

                const Solution& successor = kv.second;
                if (lowerBound < *upper_bound)
                {
                    // This solution has a chance at beating the current best solution,
                    // so we recurse to keep expanding it.
                    dFBnB(successor, problem_.Cost(successor), upper_bound, result);
                }
            }
        }
    }

    /**
     * @brief Log entry into DFBnB if verbose >= 1.
     *
     * @param partial The solution type.
     * @param cost The cost of partial.
     * @param upper_bound The upper bound on all solution costs, might be updated.
     * @param result Might be updated.
     */
    void logEntry(const Solution& partial, Scalar cost, Scalar upper_bound, const Result<Problem> result) const
    {
        if (params_.verbose >= 1u)
        {
            LOG(INFO) << result.num_considered << "\t" << cost << "\t" << upper_bound << "\t" << result.solution << "\t"
                      << partial << std::endl;
        }
    }

    /**
     * @brief Log successors into DFBnB if verbose >= 2.
     *
     * @param successors Successors.
     */
    void logSuccessors(const Successors& successors) const
    {
        if (params_.verbose >= 2u)
        {
            for (const std::pair<Scalar, Solution>& s : successors)
            {
                LOG(INFO) << "(" << s.first << ", " << s.second << ")";
            }
            LOG(INFO) << std::endl;
        }
    }

    Problem problem_;  ///< The problem instance
    Params  params_;   ///< The parameters
};

/**
 * @}
 *
 */

}  // namespace sign

}  // namespace tightly_coupled_fusion

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_SEMANTIC_SIGN_BOUNDED_DFS_H_