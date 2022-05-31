/*!
 *  \brief
 *  \author panhu (panhu@holomatic.com)
 *  \date 2019-04-15
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _RS_PATH_H_
#define _RS_PATH_H_

#include <holo/planning/planner/hybrid_astar/3dnode.h>

namespace holo
{
namespace planning
{
struct ReedSheppPath
{
    std::vector<float64_t> segs_lengths;
    std::vector<char>      segs_types;
    float64_t              total_length = 0.0;
    std::vector<float64_t> x;
    std::vector<float64_t> y;
    std::vector<float64_t> phi;
    std::vector<bool>      gear;
};

struct RSPParam
{
    bool      flag = false;
    float64_t t    = 0.0;
    float64_t u    = 0.0;
    float64_t v    = 0.0;
};

class ReedShepp
{
public:
    ReedShepp(config::VehicleConfig const& vehicle_cfg, config::HybridAstarConfig const& hybrid_astar_cfg);
    virtual ~ReedShepp();
    // Pick the shortest path from all possible combination of movement primitives
    // by Reed Shepp
    bool ShortestRSP(const std::shared_ptr<Node3d>  start_node,
                     const std::shared_ptr<Node3d>  end_node,
                     std::shared_ptr<ReedSheppPath> optimal_path);

private:
    std::pair<float64_t, float64_t> Cartesian2Polar(float64_t x, float64_t y);

    // Generate all possible combination of movement primitives by Reed Shepp and
    // interpolate them
    bool GenerateRSPs(const std::shared_ptr<Node3d> start_node,
                      const std::shared_ptr<Node3d> end_node,
                      std::vector<ReedSheppPath>*   all_possible_paths);
    // Set the general profile of the movement primitives
    bool GenerateRSP(const std::shared_ptr<Node3d> start_node,
                     const std::shared_ptr<Node3d> end_node,
                     std::vector<ReedSheppPath>*   all_possible_paths);
    // Set local exact configurations profile of each movement primitive
    bool GenerateLocalConfigurations(const std::shared_ptr<Node3d> start_node, ReedSheppPath* shortest_path);
    // Interpolation used in GenetateLocalConfiguration
    void Interpolation(const int&              index,
                       const float64_t&        pd,
                       const char&             m,
                       const float64_t&        ox,
                       const float64_t&        oy,
                       const float64_t&        ophi,
                       std::vector<float64_t>* px,
                       std::vector<float64_t>* py,
                       std::vector<float64_t>* pphi,
                       std::vector<bool>*      pgear);
    // motion primitives combination setup function
    bool SetRSP(const int&                  size,
                const float64_t*            lengths,
                const char*                 types,
                std::vector<ReedSheppPath>* all_possible_paths);
    // Six different combination of motion primitive in Reed Shepp path used in
    // GenerateRSP()
    bool
    SCS(const float64_t& x, const float64_t& y, const float64_t& phi, std::vector<ReedSheppPath>* all_possible_paths);
    bool
    CSC(const float64_t& x, const float64_t& y, const float64_t& phi, std::vector<ReedSheppPath>* all_possible_paths);
    bool
    CCC(const float64_t& x, const float64_t& y, const float64_t& phi, std::vector<ReedSheppPath>* all_possible_paths);
    bool
    CCCC(const float64_t& x, const float64_t& y, const float64_t& phi, std::vector<ReedSheppPath>* all_possible_paths);
    bool
    CCSC(const float64_t& x, const float64_t& y, const float64_t& phi, std::vector<ReedSheppPath>* all_possible_paths);
    bool
    CCSCC(const float64_t& x, const float64_t& y, const float64_t& phi, std::vector<ReedSheppPath>* all_possible_paths);
    // different options for different combination of motion primitives
    void LSL(const float64_t& x, const float64_t& y, const float64_t& phi, RSPParam* param);
    void LSR(const float64_t& x, const float64_t& y, const float64_t& phi, RSPParam* param);
    void LRL(const float64_t& x, const float64_t& y, const float64_t& phi, RSPParam* param);
    void SLS(const float64_t& x, const float64_t& y, const float64_t& phi, RSPParam* param);
    void LRLRn(const float64_t& x, const float64_t& y, const float64_t& phi, RSPParam* param);
    void LRLRp(const float64_t& x, const float64_t& y, const float64_t& phi, RSPParam* param);
    void LRSR(const float64_t& x, const float64_t& y, const float64_t& phi, RSPParam* param);
    void LRSL(const float64_t& x, const float64_t& y, const float64_t& phi, RSPParam* param);
    void LRSLR(const float64_t& x, const float64_t& y, const float64_t& phi, RSPParam* param);
    std::pair<float64_t, float64_t> calc_tau_omega(const float64_t& u,
                                                   const float64_t& v,
                                                   const float64_t& xi,
                                                   const float64_t& eta,
                                                   const float64_t& phi);

private:
    float64_t max_kappa_;
    float64_t step_size_;
};
}  // namespace planning
}  // namespace holo
#endif