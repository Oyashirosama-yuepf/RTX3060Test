/*!
 *  \brief
 *  \author panhu (panhu@holomatic.com)
 *  \date 2019-04-15
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HYBRID_A_STAR_H_
#define _HYBRID_A_STAR_H_

#include <queue>
#include <unordered_map>
#include <utility>

#include <holo/planning/planner/hybrid_astar/rs_path.h>

namespace holo
{
namespace planning
{
struct HybridAStartResult
{
    std::vector<float64_t> x;
    std::vector<float64_t> y;
    std::vector<float64_t> phi;
    std::vector<float64_t> v;
    std::vector<float64_t> a;
    std::vector<float64_t> steer;
    std::vector<bool>      gear;
};

class HybridAStar
{
public:
    HybridAStar(config::VehicleConfig const& vehicle_cfg, config::HybridAstarConfig const& hybrid_astar_cfg);
    virtual ~HybridAStar();
    bool Plan(Node3d&                                start_node,
              Node3d&                                end_node,
              std::vector<float64_t>&                XYbounds,
              const std::vector<std::vector<Vec2d>>& obstacles,
              HybridAStartResult*                    result);

private:
    /*
     * @brief      Check if a node collide with obstacles
     *
     * @param      node The vehicle box
     * @param      obstacles The obstacles
     *
     * @return     Ture if no collision happens
     */
    bool ValidityCheck(std::shared_ptr<Node3d> node, const std::vector<std::vector<Vec2d>>& obstacles);
    bool AnalyticExpansion(std::shared_ptr<Node3d> current_node, const std::vector<std::vector<Vec2d>>& obstacles);
    bool ReedSheppHeuristic(std::shared_ptr<Node3d> current_node, std::shared_ptr<ReedSheppPath> reeds_shepp_to_end);
    // check Reeds Shepp path collision and validity
    bool RSPCheck(const std::shared_ptr<ReedSheppPath>   reeds_shepp_to_end,
                  const std::vector<std::vector<Vec2d>>& obstacles);
    // load the whole RSP as nodes and add to the close set
    std::shared_ptr<Node3d> LoadRSPinCS(const std::shared_ptr<ReedSheppPath> reeds_shepp_to_end,
                                        std::shared_ptr<Node3d>              current_node);
    std::shared_ptr<Node3d> NextNodeGenerator(std::shared_ptr<Node3d> current_node, size_t next_node_index);
    void                    CalculateNodeCost(std::shared_ptr<Node3d>              current_node,
                                              std::shared_ptr<Node3d>              next_node,
                                              const std::shared_ptr<ReedSheppPath> reeds_shepp_to_end);
    float64_t               TrajCost(std::shared_ptr<Node3d> current_node, std::shared_ptr<Node3d> next_node);
    float64_t               CalculateRSPCost(const std::shared_ptr<ReedSheppPath> reeds_shepp_to_end);
    bool                    GetResult(HybridAStartResult* result);
    bool                    RegulateAngle(HybridAStartResult* result);
    bool                    GenerateSpeedAcceleration(HybridAStartResult* result);

private:
    std::vector<float64_t>  XYbounds_;
    std::shared_ptr<Node3d> start_node_;
    std::shared_ptr<Node3d> end_node_;
    std::shared_ptr<Node3d> final_node_;
    struct cmp
    {
        bool operator()(const std::pair<std::string, float64_t>& left, const std::pair<std::string, float64_t>& right) const
        {
            return left.second >= right.second;
        }
    };
    std::priority_queue<std::pair<std::string, float64_t>, std::vector<std::pair<std::string, float64_t>>, cmp> open_pq_;
    std::unordered_map<std::string, std::shared_ptr<Node3d>>                                               open_set_;
    std::unordered_map<std::string, std::shared_ptr<Node3d>>                                               close_set_;
    std::unordered_map<std::string, std::shared_ptr<ReedSheppPath>> ReedSheppPath_cache_;
    std::unique_ptr<ReedShepp>                                 reed_shepp_generator_;

    config::VehicleConfig const&     vehicle_cfg_;
    config::HybridAstarConfig const& hybrid_astar_cfg_;
};

}  // namespace planning
}  // namespace holo
#endif
