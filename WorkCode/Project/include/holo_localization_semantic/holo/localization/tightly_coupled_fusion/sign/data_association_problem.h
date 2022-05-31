/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file data_association_problem.h
 * @brief The define of data association problem
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date Dec 08, 2019
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_DATA_ASSOCIATION_PROBLEM_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_DATA_ASSOCIATION_PROBLEM_H_

#include <holo/localization/common/types.h>
#include <holo/numerics/matrix.h>

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
 * @brief Data association solution.
 *
 */
class Correspondence : public std::vector<uint32_t>
{
public:
    /**
     * @brief Default construct function.
     *
     */
    Correspondence() noexcept
    {
    }

    /**
     * @brief Construct a new correspondence object.
     *
     * @param ks The matched index.
     */
    explicit Correspondence(const std::vector<uint32_t>& ks) : std::vector<uint32_t>(ks)
    {
    }

    /**
     * @brief Overload output stream operator.
     *
     * @param os Output stream.
     * @param correspondence The correspondence.
     * @return Output operator.
     */
    friend std::ostream& operator<<(std::ostream& os, const Correspondence& correspondence)
    {
        for (const uint32_t k_j : correspondence)
        {
            os << k_j << ' ';
        }

        return os;
    }
};

/**
 * Abstract base class for problems.
 */
class Problem
{
public:
    /**
     * @brief Return cost of a (possibly partial) correspondence.
     *
     * @param correspondence The correspondence.
     * @return The cost.
     */
    virtual Scalar Cost(const Correspondence& correspondence) const = 0;

    /**
     * @brief Return lower-bound estimate on cost-to-complete.
     *
     * @param correspondence The correspondence.
     * @return The cost.
     */
    virtual Scalar Heuristic(const Correspondence& correspondence) const = 0;

    /**
     * @brief Lower bound f = g + h.
     *
     * @param correspondence The correspondence.
     * @return The cost.
     */
    Scalar LowerBound(const Correspondence& correspondence) const
    {
        return Cost(correspondence) + Heuristic(correspondence);
    }
};

/**
 * Data association problem for sign semantic matching.
 */
class DataAssociationProblem : public Problem
{
public:
    using Successors = std::multimap<Scalar, Correspondence>;

    /**
     * @brief Construct a new data association problem.
     *
     * @param costs
     * @param alpha
     */
    DataAssociationProblem(const MatrixXType& costs, Scalar alpha) : costs_(costs), alpha_(alpha)
    {
    }

    /**
     * @brief Return an easy guess, in our case just all spurious.
     *
     * @return The correspondence.
     */
    Correspondence Guess() const
    {
        return Correspondence(std::vector<uint32_t>(costs_.GetRows(), 0u));
    }

    /**
     * @brief Return cost of a (possibly partial) correspondence.
     *
     * @param correspondence The correspondence.
     * @return The cost of correspondence.
     */
    Scalar Cost(const Correspondence& correspondence) const override
    {
        Scalar result = 0.0;
        for (uint32_t j = 0u; j < correspondence.size(); j++)
        {
            const uint32_t k_j = correspondence[j];
            result += (k_j == 0u) ? alpha_ : costs_(j, k_j - 1u);
        }
        return result;
    }

    /**
     * @brief Return true if correspondence is of size N.
     *
     * @param correspondence The correspondence.
     * @return False if correspondence isn't of size N.
     */
    bool_t Goal(const Correspondence& correspondence) const
    {
        return (uint32_t)correspondence.size() == costs_.GetRows();
    }

    /**
     * @brief Dijstra heuristic h=0.
     *
     * @param partial The correspondence.
     * @return Scalar.
     */
    Scalar Heuristic(const Correspondence& partial) const override
    {
        (void)partial;
        return Scalar(0);
    }

    /**
     * @brief Expand partial correspondence by assigning next k[j].
     *
     * @param partial The correspondence.
     * @return The successors.
     */
    Successors Expand(const Correspondence& partial) const
    {
        assert(!Goal(partial));
        Successors successors;
        for (uint32_t k = 0u; k <= costs_.GetCols(); k++)
        {
            Correspondence v = partial;
            v.push_back(k);
            const Scalar h = Heuristic(partial);
            successors.emplace(h, v);
        }

        return successors;
    }

protected:
    MatrixXType costs_;  ///< The costs of sign j, segment k.
    Scalar      alpha_;  ///< The cost of clutter assignment k=0.
};

/**
 * Data association problem with better heuristic.
 */
class SmarterDataAssociationProblem : public DataAssociationProblem
{
public:
    SmarterDataAssociationProblem(const MatrixXType& costs, Scalar alpha) : DataAssociationProblem(costs, alpha)
    {
        min_cost_ = std::min(costs_.MinCoeff(), alpha_);
    }

    /**
     * @brief Heuristic that returns minimum cost.
     *
     * @param partial Correspondence.
     * @return The cost of correspondence.
     */
    Scalar Heuristic(const Correspondence& partial) const override
    {
        const uint32_t numUnfilledSlots = costs_.GetRows() - partial.size();
        return numUnfilledSlots * min_cost_;
    }

private:
    Scalar min_cost_;  ///< The min cost.
};

/**
 * @}
 *
 */
}  // namespace sign

}  // namespace tightly_coupled_fusion

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_SEMANTIC_SIGN_DATA_ASSOCIATION_PROBLEM_H_
