/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lattice_sampler_base.h
 * @brief the header of the Base Lattice Sampler class
 * @author wangchantong(wangchantong@holomatic.com)
 * @date 2020-09-07
 */

#ifndef _HOLO_PLANNING_LATTICE_LATTICE_SAMPLER_BASE_H_
#define _HOLO_PLANNING_LATTICE_LATTICE_SAMPLER_BASE_H_

#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief Base class for lattice sample lon and lat curve end conditions
 */
class LatticeSamplerBase
{
public:
    using State        = std::array<float64_t, 3>;
    using Condition    = std::pair<State, float64_t>;
    using ObstacleList = std::vector<std::shared_ptr<ObstacleInfo>>;

    /**
     * @brief Construct a new Base Latiice Sampler object
     *
     * @param init_lon_state initial longitudinal frenet state
     * @param init_lat_state initial lateral frenet state
     */
    LatticeSamplerBase(State const& init_lon_state, State const& init_lat_state)
      : init_lon_state_(init_lon_state), init_lat_state_(init_lat_state){};

    /**
     * @brief Destroy the Base Latiice Sampler object
     */
    virtual ~LatticeSamplerBase() = default;

    /**
     * @brief sample longitudinal frenet end conditions for cruising
     *
     * @param ref_speed reference longitudinal speed
     * @param lon_end_conditions vector to save longitudinal end conditions
     */
    virtual void SampleLonEndConditionsForCruising(float64_t               ref_speed,
                                                   std::vector<Condition>& lon_end_conditions) const = 0;

    /**
     * @brief sample longitudinal frenet end conditions for stopping
     *
     * @param stop_s longitudinal distance to stop point, [0.0 - 500.0] is valid value, other values mean no certain
     *               stop point
     * @param lon_end_conditions vector to save longitudinal end conditions
     */
    virtual void SampleLonEndConditionsForStopping(float64_t               stop_s,
                                                   std::vector<Condition>& lon_end_conditions) const = 0;

    /**
     * @brief sample longitudinal frenet end conditions for following obstacle
     *
     * @param obs_list obstacle pointer list
     * @param ref_speed reference longitudinal speed
     * @param lon_end_conditions vector to save longitudinal end conditions
     */
    virtual void SampleLonEndConditionsForFollowing(ObstacleList const&     obs_list,
                                                    float64_t               ref_speed,
                                                    std::vector<Condition>& lon_end_conditions) const = 0;

    /**
     * @brief sample lateral frenet end conditions
     *
     * @param lat_end_conditions vector to save lateral end conditions
     */
    virtual void SampleLatEndConditions(std::vector<Condition>& lat_end_conditions) const = 0;

protected:
    /**
     * @brief initial longitudinal frenet state
     */
    State init_lon_state_;

    /**
     * @brief initial lateral frenet state
     */
    State init_lat_state_;
};

}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif