/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file curve_1d_generator.h
 * @brief the header of the 1d curve generator in lattice
 * @author lizhao(lizhao@holomatic.com)
 * @date 2022-2-14
 */

#ifndef _HOLO_PLANNING_LATTICE_CURVE_1D_GENERATOR_H_
#define _HOLO_PLANNING_LATTICE_CURVE_1D_GENERATOR_H_

#include <holo/core/types.h>

#include <holo/planning/math/curve/curve_1d.h>

namespace holo
{
namespace planning
{
/**
 * @brief Class for generate curve set for longitudinal and lateral respectively
 */
class Curve1dGenerator
{
public:
    using Curve1dSet = std::vector<std::shared_ptr<math::Curve1d>>;
    using State      = std::array<float64_t, 3>;
    using Condition  = std::pair<State, float64_t>;
    /**
     * @brief Construct a new Curve 1d Generator object
     *
     * @param init_lon_state initial longitudinal frenet state
     * @param init_lat_state initial lateral frenet state
     */
    Curve1dGenerator(const State& init_lon_state, const State& init_lat_state);

    /**
     * @brief Destroy the Curve 1d Generator object
     */
    ~Curve1dGenerator() = default;

    /**
     * @brief generate longitudinal and lateral curve sets
     *
     * @param left_road_width left road width
     * @param right_road_width right road width
     * @param vehicle_width vehicle width
     * @param lat_curve_set set to save lateral curves
     */
    void GenerateCurveSet(const float64_t left_road_width,
                          const float64_t right_road_width,
                          const float64_t interval,
                          const float64_t vehicle_width,
                          const float64_t lattice_length,
                          Curve1dSet&     lat_curve_set);

private:
    /**
     * @brief sample lateral end conditions
     *
     * @param lat_curve_set set to save lateral curves
     * @param left_road_width right road width
     * @param right_road_width road width
     * @param vehicle_width ego car width
     */
    void SampleLateralEndConditions(const float64_t         left_road_width,
                                    const float64_t         right_road_width,
                                    const float64_t         interval,
                                    const float64_t         vehicle_width,
                                    const float64_t         target_s,
                                    std::vector<Condition>& LatEndConditions);
    /**
     * @brief generate lateral curve set
     *
     * @param lat_curve_set set to save lateral curves
     * @param left_road_width right road width
     * @param right_road_width road width
     * @param vehicle_width ego car width
     */
    void GenerateLatCurveSet(Curve1dSet&     lat_curve_set,
                             const float64_t left_road_width,
                             const float64_t right_road_width,
                             const float64_t interval,
                             const float64_t vehicle_width,
                             const float64_t lattice_length);

    /**
     * @brief initial longitudinal frenet state
     */
    State init_lon_state_;

    /**
     * @brief initial lateral frenet state
     */
    State init_lat_state_;
};

}  // namespace planning
}  // namespace holo

#endif