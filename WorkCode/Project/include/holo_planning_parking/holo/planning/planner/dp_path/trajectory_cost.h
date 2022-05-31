/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _TRAJECTORY_COST_H_
#define _TRAJECTORY_COST_H_

#include <vector>

#include <holo/core/types.h>
#include <holo/planning/common/config/dp_config.h>
#include <holo/planning/common/config/vehicle_config.h>
#include <holo/planning/common/road_boundary.h>
#include <holo/planning/common/sl_boundary.h>
#include <holo/planning/common/sl_path.h>
#include <holo/planning/planner/dp_path/comparable_cost.h>
#include <holo/planning/planner/dp_path/quintic_polynomial_curve1d.h>

namespace holo
{
namespace planning
{
// Base type for various types of 1-dimensional curves
class TrajectoryCost
{
public:
    TrajectoryCost(SLPath const&                  history_sl_path,
                   std::vector<SLBoundary> const& static_obstacle_sl_boundaries,
                   config::VehicleConfig const&   vehicle_cfg,
                   config::DpConfig const&        dp_cfg);
    TrajectoryCost(std::shared_ptr<RoadBoundary> boundary,
                   config::VehicleConfig const&  vehicle_cfg,
                   config::DpConfig const&       dp_cfg);
    void           SetConfig(config::VehicleConfig const& vehicle_cfg, config::DpConfig const& dp_cfg);
    ComparableCost Calculate(const QuinticPolynomialCurve1d& curve,
                             const float64_t                    start_s,
                             const float64_t                    end_s,
                             const uint32_t                  curr_level,
                             const uint32_t                  total_level);

private:
    enum ObstacleForm
    {
        BOUNDING_BOX = 0,
        BOUNDARY     = 1,
    };

    ComparableCost CalculatePathCost(const QuinticPolynomialCurve1d& curve,
                                     const float64_t                    start_s,
                                     const float64_t                    end_s,
                                     const uint32_t                  curr_level,
                                     const uint32_t                  total_level);

    ComparableCost CalculateStaticObstacleCost(const QuinticPolynomialCurve1d& curve,
                                               const float64_t                    start_s,
                                               const float64_t                    end_s);

    ComparableCost GetCostFromObsSL(const float64_t adc_s, const float64_t adc_l, const SLBoundary& obs_sl_boundary);

    ComparableCost GetCostFromRoadBoundary(float64_t const adc_s, float64_t const adc_l);

    float64_t Sigmoid(const float64_t x)
    {
        return 1.0 / (1.0 + std::exp(-x));
    }

private:
    std::vector<SLBoundary>       static_obstacle_sl_boundaries_;
    SLPath                        history_sl_path_;
    std::shared_ptr<RoadBoundary> boundary_;
    ObstacleForm                  obstacle_form_;

    float64_t vehicle_front_edge_to_center_;
    float64_t vehicle_back_edge_to_center_;
    float64_t vehicle_side_edge_to_center_;

    bool use_obs_avoid_;

    float64_t path_cost_l_quasi_softmax_l0_;
    float64_t path_cost_l_quasi_softmax_b_;
    float64_t path_cost_l_quasi_softmax_k_;

    float64_t path_cost_resolution_;
    float64_t path_cost_l_cost_;
    float64_t path_cost_his_l_cost_;
    float64_t path_cost_dl_cost_;
    float64_t path_cost_ddl_cost_;
    float64_t path_cost_endl_cost_;

    float64_t obstacle_collision_distance_;
    float64_t obstacle_collision_cost_;
    float64_t obstacle_static_nudge_l_;
    float64_t obstacle_static_safe_l_dist_;
    float64_t obstacle_lateral_ignore_dist_;
};

}  // namespace planning
}  // namespace holo

#endif  // _TRAJECTORY_COST_H_
