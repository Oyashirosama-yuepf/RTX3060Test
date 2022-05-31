/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lattice_evaluator_base.h
 * @brief the header of Base Lattice Evaluator class
 * @author wangchantong(wangchantong@holomatic.com)
 * @date 2020-09-07
 */

#ifndef _HOLO_PLANNING_LATTICE_LATTICE_EVALUATOR_BASE_H_
#define _HOLO_PLANNING_LATTICE_LATTICE_EVALUATOR_BASE_H_

#include <queue>

#include <holo/core/types.h>

#include <holo/planning/common/box/normal_box.h>
#include <holo/planning/common/car_road_state.h>
#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief Base class for lattice evaluate curve set for longitudinal and lateral respectively
 */
class LatticeEvaluatorBase
{
public:
    using State                  = std::array<float64_t, 3>;
    using Curve1dSet             = std::vector<std::shared_ptr<math::Curve1d>>;
    using PtrCurve1dPair         = std::pair<std::shared_ptr<math::Curve1d>, std::shared_ptr<math::Curve1d>>;
    using PairWithTotalCost      = std::pair<PtrCurve1dPair, float64_t>;
    using PairWithRespectiveCost = std::pair<PtrCurve1dPair, std::pair<float64_t, float64_t>>;

    /**
     * @brief Construct a new Base Lattice Evaluator object
     *
     * @param init_lon_state Initial longitudinal state in frenet state
     * @param init_lat_state Initial lateral state in frenet state
     * @param ego_box Box of ego car
     */
    LatticeEvaluatorBase(State const& init_lon_state, State const& init_lat_state, NormalBox const& ego_box)
      : init_lon_state_(init_lon_state), init_lat_state_(init_lat_state), ego_box_(ego_box){};

    /**
     * @brief Destroy the Base Lattice Evaluator object
     */
    virtual ~LatticeEvaluatorBase() = default;

    /**
     * @brief pair longitudinal and lateral curve, evaluate all the pairs and sort them
     *
     * @param lon_curve_set longitudinal curves set
     * @param lat_curve_set lateral curves set
     */
    virtual void Evaluate(Curve1dSet const& lon_curve_set, Curve1dSet const& lat_curve_set) = 0;

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
    PtrCurve1dPair PopBestTrajectoryPair()
    {
        if (cost_queue_.empty())
        {
            LOG(ERROR) << "trajectory pair queue empty";
            PtrCurve1dPair empty_pair(std::make_pair(nullptr, nullptr));
            return empty_pair;
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
    inline const std::pair<float64_t, float64_t>& GetBestTrajectoryPairCost() const
    {
        return cost_queue_.top().second;
    }

protected:
    /**
     * @brief calculate curve pair's longitudinal cost
     *
     * @param ptr_lon_curve pointer of the longitudinal curve
     * @param ptr_lat_curve pointer of the lateral curve
     *
     * @return float64_t the cost
     */
    virtual float64_t CalLonCost(std::shared_ptr<math::Curve1d> const& ptr_lon_curve,
                                 std::shared_ptr<math::Curve1d> const& ptr_lat_curve) const = 0;

    /**
     * @brief calculate curve pair's lateral cost
     *
     * @param ptr_lon_curve pointer of the longitudinal curve
     * @param ptr_lat_curve pointer of the lateral curve
     *
     * @return float64_t the cost
     */
    virtual float64_t CalLatCost(std::shared_ptr<math::Curve1d> const& ptr_lon_curve,
                                 std::shared_ptr<math::Curve1d> const& ptr_lat_curve) const = 0;

    /**
     * @brief struct of cost comparator
     */
    struct CostComparator
      : public std::binary_function<PairWithRespectiveCost const&, PairWithRespectiveCost const&, bool_t>
    {
        bool_t operator()(PairWithRespectiveCost const& left, PairWithRespectiveCost const& right) const
        {
            return left.second.first + left.second.second > right.second.first + right.second.second;
        }
    };

    /**
     * @brief queue to save curves pair and its cost
     */
    std::priority_queue<PairWithRespectiveCost, std::vector<PairWithRespectiveCost>, CostComparator> cost_queue_;

protected:
    /**
     * @brief initial longitudinal frenet state
     */
    State init_lon_state_;

    /**
     * @brief initial lateral frenet state
     */
    State init_lat_state_;

    /**
     * @brief the config of vehicle
     */
    NormalBox ego_box_;
};

}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif