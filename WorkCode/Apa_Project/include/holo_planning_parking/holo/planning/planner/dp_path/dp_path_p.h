/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _DP_PATH_H_
#define _DP_PATH_H_

#include <vector>

#include <holo/core/types.h>
#include <holo/geometry/point2.h>

#include <holo/planning/common/car_road_state.h>
#include <holo/planning/common/sl_path.h>
#include <holo/planning/planner/dp_path/comparable_cost.h>
#include <holo/planning/planner/dp_path/quintic_polynomial_curve1d.h>
#include <holo/planning/planner/dp_path/trajectory_cost.h>

namespace holo
{
namespace planning
{
class DPPath
{
public:
    DPPath(config::VehicleConfig const& vehicle_cfg, config::DpConfig const& dp_cfg);
    virtual ~DPPath();

    bool GeneratePath(const common::Path&                    advice_path,
                      const std::vector<SLBoundary>& static_obstacle_sl_boundaries,
                      const geometry::Pose2&                   pose,
                      const common::PathPoint&               start_point,
                      const common::PathPoint&               end_point,
                      const float64_t&               step_dis,
                      common::Path&                          path,
                      SLPath&                        sl_path);

    bool GeneratePath(common::Path const&                      advice_path,
                      std::vector<RoadBoundary> const& boundaries,
                      geometry::Pose2 const&                     pose,
                      float64_t const                  path_length,
                      common::Path&                            path,
                      SLPath&                          sl_path);

    void GetSLObstacles(std::vector<SLBoundary>& static_obstacle_sl_boundaries)
    {
        static_obstacle_sl_boundaries = static_obstacle_sl_boundaries;
    }

private:
    struct DPRoadGraphNode
    {
        DPRoadGraphNode(){};

        DPRoadGraphNode(const SLPoint point_sl, const DPRoadGraphNode* node_prev)
          : sl_point(point_sl), min_cost_prev_node(node_prev)
        {
        }

        DPRoadGraphNode(const SLPoint point_sl, const DPRoadGraphNode* node_prev, const ComparableCost& cost)
          : sl_point(point_sl), min_cost_prev_node(node_prev), min_cost(cost)
        {
        }

        void UpdateCost(const DPRoadGraphNode*          node_prev,
                        const QuinticPolynomialCurve1d& curve,
                        const ComparableCost&           cost)
        {
            if (cost <= min_cost)
            {
                min_cost           = cost;
                min_cost_prev_node = node_prev;
                min_cost_curve     = curve;
            }
        }

        SLPoint                  sl_point;
        const DPRoadGraphNode*   min_cost_prev_node = nullptr;
        ComparableCost           min_cost           = {true, true, true, std::numeric_limits<float64_t>::infinity(),
                                   std::numeric_limits<float64_t>::infinity()};
        QuinticPolynomialCurve1d min_cost_curve;
    };

    void UpdateNode(const std::list<DPRoadGraphNode>& prev_nodes,
                    const uint32_t                    level,
                    const uint32_t                    total_level,
                    TrajectoryCost*                   trajectory_cost,
                    DPRoadGraphNode*                  front,
                    DPRoadGraphNode*                  cur_node);

    bool SamplePathWaypoints(const float64_t                    near_start_l,
                             const float64_t                    near_end_l,
                             const float64_t                    start_s,
                             const float64_t                    end_s,
                             const float64_t                    s_step,
                             const float64_t                    start_l,
                             const float64_t                    end_l,
                             const float64_t                    l_step,
                             std::vector<std::vector<SLPoint>>& points);

private:
    common::Path advice_path_;

    float64_t path_sample_start_l_;
    float64_t path_sample_end_l_;
    float64_t path_sample_l_step_;
    float64_t path_level_step_;

    config::VehicleConfig const& vehicle_cfg_;
    config::DpConfig const&      dp_cfg_;
};  // class DPPath
}  // namespace planning
}  // namespace holo

#endif  // _DP_PATH_H_