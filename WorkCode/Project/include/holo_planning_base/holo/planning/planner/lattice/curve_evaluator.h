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
#include <holo/planning/planner/lattice/constraint_checker.h>
#include <holo/planning/planner/lattice/lattice_planner.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief Class for generate curve set for longitudinal and lateral respectively
 */
class CurveEvaluator
{
public:
    using State                       = std::array<float64_t, 3>;
    using Curve1dSet                  = std::vector<std::shared_ptr<math::Curve1d>>;
    using PtrCurve1dPair              = std::pair<std::shared_ptr<math::Curve1d>, std::shared_ptr<math::Curve1d>>;
    using PairWithTotalCost           = std::pair<PtrCurve1dPair, float64_t>;
    using PairWithRespectiveCost      = std::pair<PtrCurve1dPair, std::pair<float64_t, float64_t>>;
    using PredictedBoxesTrajectoryPtr = std::shared_ptr<std::vector<std::vector<NormalBox>>>;
    using ConstraintPtr               = std::shared_ptr<LatticeConstraint>;
    /**
     * @brief Construct a new Curve Evaluator object
     *
     * @param init_s initial longitudinal frenet state
     * @param data data which evaluator needed
     * @param ego_box box of ego car
     * @param boxes_trajectory_ptr pointer of predicted obstacles trajectory boxs
     * @param constraint_ptr pointer of constraint
     */
    CurveEvaluator(const State&                       init_s,
                   const LatticeFrame&                data,
                   const NormalBox&                   ego_box,
                   const PredictedBoxesTrajectoryPtr& boxes_trajectory_ptr,
                   const ConstraintPtr&               constraint_ptr);

    /**
     * @brief Destroy the Curve Evaluator object
     */
    ~CurveEvaluator() = default;

    /**
     * @brief pair longitudinal and lateral curve, evaluate all the pairs and sort them
     *
     * @param lon_curve_set longitudinal curves set
     * @param lat_curve_set lateral curves set
     */
    void Evaluate(const Curve1dSet& lon_curve_set, const Curve1dSet& lat_curve_set);

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

private:
    /**
     * @brief calculate curve pair's longitudinal cost
     *
     * @param ptr_lon_curve pointer of the longitudinal curve
     * @param ptr_lat_curve pointer of the lateral curve
     *
     * @return float64_t the cost
     */
    float64_t CalLonCost(const std::shared_ptr<math::Curve1d>& ptr_lon_curve,
                         const std::shared_ptr<math::Curve1d>& ptr_lat_curve);

    /**
     * @brief calculate curve pair's lateral cost
     *
     * @param route         the route
     * @param ptr_lon_curve pointer of the longitudinal curve
     * @param ptr_lat_curve pointer of the lateral curve
     *
     * @return float64_t the cost
     */
    float64_t CalLatCost(const std::shared_ptr<math::Curve1d>& ptr_lon_curve,
                         const std::shared_ptr<math::Curve1d>& ptr_lat_curve) const;

    /**
     * @brief calculate longitudinal comfort cost
     *
     * @param ptr_lon_curve pointer of the longitudinal curve
     *
     * @return float64_t the cost
     */
    // float64_t CalLonComfortCost(const std::shared_ptr<math::Curve1d>& ptr_lon_curve) const;

    /**
     * @brief calculate longitudinal offset cost
     *
     * @param ptr_lon_curve pointer of the longitudinal curve
     *
     * @return float64_t the cost
     */
    // float64_t CalLonObjectiveCost(const std::shared_ptr<math::Curve1d>& ptr_lon_curve) const;

    /**
     * @brief calculate collision cost
     *
     * @param ptr_lon_curve pointer of the longitudinal curve
     * @param ptr_lat_curve pointer of the lateral curve
     *
     * @return float64_t the cost
     */
    float64_t CalLonCollisionCost(const std::shared_ptr<math::Curve1d>& ptr_lon_curve,
                                  const std::shared_ptr<math::Curve1d>& ptr_lat_curve);

    /**
     * @brief calculate centripetal acceleration cost
     *
     * @param route the route
     * @param ptr_lon_curve pointer of the longitudinal curve
     *
     * @return float64_t the cost
     */
    // float64_t CalCentripetalAccelerationCost(const std::vector<CurvePoint>&                  ref_path,
    //                                          const std::shared_ptr<math::Curve1d>& ptr_lon_curve) const;

    /**
     * @brief calculate lateral offset cost
     *
     * @param ptr_lon_curve pointer of the longitudinal curve
     * @param ptr_lat_curve pointer of the lateral curve
     *
     * @return float64_t the cost
     */
    // float64_t CalLatOffsetCost(const std::shared_ptr<math::Curve1d>& ptr_lon_curve,
    //                            const std::shared_ptr<math::Curve1d>& ptr_lat_curve) const;

    /**
     * @brief calculate lateral comfort cost
     *
     * @param ptr_lon_curve pointer of the longitudinal curve
     * @param ptr_lat_curve pointer of the lateral curve
     *
     * @return float64_t the cost
     */
    float64_t CalLatComfortCost(const std::shared_ptr<math::Curve1d>& ptr_lon_curve,
                                const std::shared_ptr<math::Curve1d>& ptr_lat_curve) const;

    /**
     * @brief struct of cost comparator
     */
    struct CostComparator
      : public std::binary_function<const PairWithRespectiveCost&, const PairWithRespectiveCost&, bool_t>
    {
        bool_t operator()(const PairWithRespectiveCost& left, const PairWithRespectiveCost& right) const
        {
            return left.second.first + left.second.second > right.second.first + right.second.second;
        }
    };

    /**
     * @brief queue to save curves pair and its cost
     */
    std::priority_queue<PairWithRespectiveCost, std::vector<PairWithRespectiveCost>, CostComparator> cost_queue_;

    /**
     * @brief initial longitudinal frenet state
     */
    State init_s_;

    /**
     * @brief reference longitudinal speed
     */
    float64_t ref_speed_;

    /**
     * @brief distance to stop point
     */
    float64_t stop_s_;

    /**
     * @brief the width of road
     */
    float64_t road_width_;

    /**
     * @brief the headway time
     */
    float64_t headway_time_;

    /**
     * @brief the config of vehicle
     */
    NormalBox ego_box_;

    /**
     * @brief pointer of predicted obstacles' trajectory
     */
    PredictedBoxesTrajectoryPtr boxes_trajectory_ptr_;

    /**
     * @brief pointer of constraint
     */
    ConstraintPtr constraint_ptr_;
};

}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif