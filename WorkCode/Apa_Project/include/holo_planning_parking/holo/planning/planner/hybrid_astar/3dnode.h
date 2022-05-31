/*!
 *  \brief
 *  \author panhu (panhu@holomatic.com)
 *  \date 2019-04-15
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _3D_NODE_H_
#define _3D_NODE_H_

#include <memory>

#include <holo/planning/common/config/hybrid_astar_config.h>
#include <holo/planning/common/config/vehicle_config.h>
#include <holo/planning/planner/hybrid_astar/box2d.h>

namespace holo
{
namespace planning
{
class Node3d
{
public:
    Node3d(float64_t x, float64_t y, float64_t phi);
    Node3d(float64_t                        x,
           float64_t                        y,
           float64_t                        phi,
           std::vector<float64_t> const&    XYbounds,
           config::HybridAstarConfig const& hybrid_astar_cfg);
    Node3d(std::vector<float64_t>           traversed_x,
           std::vector<float64_t>           traversed_y,
           std::vector<float64_t>           traversed_phi,
           std::vector<bool>                traversed_gear,
           std::vector<float64_t> const&    XYbounds,
           config::HybridAstarConfig const& hybrid_astar_cfg);
    bool  operator==(const std::shared_ptr<Node3d> right) const;
    bool  operator==(const Node3d& right) const;
    Box2d GetBoundingBox(config::VehicleConfig const& vehicle_cfg, config::HybridAstarConfig const& hybrid_astar_cfg);
    static Box2d
    GetBoundingBox(config::VehicleConfig const& vehicle_cfg, const float64_t x, const float64_t y, const float64_t phi);
    size_t GetSize();

    float64_t GetX() const
    {
        return x_;
    }

    float64_t GetY() const
    {
        return y_;
    }

    float64_t GetPhi() const
    {
        return phi_;
    }

    bool GetDire() const
    {
        return gear_;
    }

    std::vector<float64_t> GetXs() const
    {
        return traversed_x_;
    }

    std::vector<float64_t> GetYs() const
    {
        return traversed_y_;
    }

    std::vector<float64_t> GetPhis() const
    {
        return traversed_phi_;
    }

    std::vector<bool> GetDires() const
    {
        return traversed_gear_;
    }

    size_t GetGridX() const
    {
        return x_grid_;
    }

    size_t GetGridY() const
    {
        return y_grid_;
    }

    size_t GetGridPhi() const
    {
        return phi_grid_;
    }

    std::string GetIndex() const
    {
        return index_;
    }

    float64_t GetTrajCost() const
    {
        return traj_cost_;
    }

    float64_t GetHeuCost() const
    {
        return heuristic_cost_;
    }

    float64_t GetCost() const
    {
        return traj_cost_ + heuristic_cost_;
    }

    std::shared_ptr<Node3d> GetPreNode() const
    {
        return pre_node_;
    }

    float64_t GetSteer() const
    {
        return steering_;
    }

    void SetX(float64_t x)
    {
        x_ = x;
    }

    void SetY(float64_t y)
    {
        y_ = y;
    }

    void SetPhi(float64_t p)
    {
        phi_ = p;
    }

    void SetDire(bool gear)
    {
        gear_ = gear;
    }

    void SetTrajCost(float64_t cost)
    {
        traj_cost_ = cost;
    }

    void SetHeuCost(float64_t cost)
    {
        heuristic_cost_ = cost;
    }

    void SetPre(std::shared_ptr<Node3d> pre_node)
    {
        pre_node_ = pre_node;
    }

    void SetSteer(float64_t steering)
    {
        steering_ = steering;
    }

private:
    float64_t               x_    = 0.0;
    float64_t               y_    = 0.0;
    float64_t               phi_  = 0.0;
    bool                    gear_ = true;
    std::vector<float64_t>  traversed_x_;
    std::vector<float64_t>  traversed_y_;
    std::vector<float64_t>  traversed_phi_;
    std::vector<bool>       traversed_gear_;
    size_t                  x_grid_   = 0;
    size_t                  y_grid_   = 0;
    size_t                  phi_grid_ = 0;
    std::string             index_;
    float64_t               traj_cost_      = 0.0;
    float64_t               heuristic_cost_ = 0.0;
    std::shared_ptr<Node3d> pre_node_       = nullptr;
    float64_t               steering_       = 0.0;
};

}  // namespace planning
}  // namespace holo
#endif