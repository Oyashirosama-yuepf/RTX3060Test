/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file curve_evaluator.h
 * @brief the header of the curve evaluator in lattice
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_LATTICE_CURVE_EVALUATOR_H_
#define _HOLO_PLANNING_LATTICE_CURVE_EVALUATOR_H_

#include <queue>

#include <holo/core/types.h>

#include <holo/planning/common/box/normal_box.h>
#include <holo/planning/common/plan_route.h>
#include <holo/planning/planner/lattice_simple/lattice_planner.h>

namespace holo
{
namespace planning
{
/**
 * @brief Class for generate curve set for longitudinal and lateral respectively
 */
class CurveEvaluator
{
public:
    using State                  = std::array<float64_t, 3>;
    using Curve1dSet             = std::vector<std::shared_ptr<math::Curve1d>>;
    using PtrCurve1d             = std::shared_ptr<math::Curve1d>;
    using PairWithTotalCost      = std::pair<Curve1dSet, float64_t>;
    using PairWithRespectiveCost = std::pair<PtrCurve1d, float64_t>;

    /**
     * @brief Construct the Curve Evaluator object
     */
    CurveEvaluator() = default;

    /**
     * @brief Destroy the Curve Evaluator object
     */
    ~CurveEvaluator() = default;

    /**
     * @brief lateral curve, evaluate all the pairs and sort them
     *
     * @param lat_curve_set lateral curves set
     */
    void Evaluate(const Curve1dSet& lat_curve_set);

    /**
     * @brief judge whether sorted queue of saving pairs has pair
     *
     * @return bool_t true if queue has pair, false if queue is empty
     */
    inline bool_t HasTrajectoryPairs() const
    {
        return !cost_queue_.empty();
    }

    /**
     * @brief return the size of the queue
     *
     * @return size_t the size of the queue
     */
    inline size_t GetSize() const
    {
        return cost_queue_.size();
    }

    /**
     * @brief get the first pair of the queue and then pop it
     *
     * @return PtrCurve1dPair the first pair of the queue
     */
    PtrCurve1d PopBestTrajectory()
    {
        if (cost_queue_.empty())
        {
            LOG(ERROR) << "trajectory queue empty";
            PtrCurve1d empty_curve(nullptr);
            return empty_curve;
        }
        PairWithRespectiveCost top = cost_queue_.top();
        cost_queue_.pop();
        return top.first;
    }

    /**
     * @brief get the first pair's cost of the queue
     *
     * @return const std::pair<float64_t, float64_t>& the reference of cost pair of the first curves pair
     */
    inline const float64_t& GetBestTrajectoryPairCost() const
    {
        return cost_queue_.top().second;
    }

private:
    /**
     * @brief calculate curve lateral cost
     *
     * @param ptr_lat_curve pointer of the lateral curve
     *
     * @return float64_t the cost
     */
    float64_t CalLatCost(const std::shared_ptr<math::Curve1d>& ptr_lat_curve) const;

    /**
     * @brief struct of cost comparator
     */
    struct CostComparator
      : public std::binary_function<const PairWithRespectiveCost&, const PairWithRespectiveCost&, bool_t>
    {
        bool_t operator()(const PairWithRespectiveCost& left, const PairWithRespectiveCost& right) const
        {
            return left.second > right.second;
        }
    };

    /**
     * @brief queue to save curves pair and its cost
     */
    std::priority_queue<PairWithRespectiveCost, std::vector<PairWithRespectiveCost>, CostComparator> cost_queue_;
};

}  // namespace planning
}  // namespace holo

#endif