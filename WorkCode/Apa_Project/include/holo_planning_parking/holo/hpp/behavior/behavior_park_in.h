/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file behavior_park_in.h
 * @brief the header of behavior of parkin
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-10-30
 */

#ifndef _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PARKIN_H_
#define _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PARKIN_H_

#include <holo/hpp/behavior/behavior.h>
#include <holo/hpp/parkingplan/parkingplan.h>

namespace holo
{
namespace planning
{
class BehaviorParkIn : public Behavior
{
public:
    /**
     * @brief   Constructor
     */
    BehaviorParkIn();

    /**
     * @brief   Destroy object
     */
    virtual ~BehaviorParkIn() = default;

    /**
     * @brief      Calculate virtual lot coordinates
     *
     * @param[out] tm_parkinglot the output parkinglot
     * @param[in]  length  lot length
     * @param[in]  width  lot width
     * @param[in]  x_translate  x coordinate offset
     * @param[in]  y_translate y coordinate offset
     * @param[in]  theta_rotate rotation angle
     */
    void CarculateLotCoordinate(ParkinglotData& tm_parkinglot,
                                float64_t       length,
                                float64_t       width,
                                float64_t       x_translate,
                                float64_t       y_translate,
                                float64_t       theta_rotate);

    void UpdateSlot(ParkinglotData& tm_parkinglot, RoadInfo const& info);

    /**
     * @brief      Park in behavior execution
     *
     * @param[in]  state  The car road state
     * @param[in]  info The road info from loc and per
     * @param[out] output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    virtual bool_t Perform(HppCarRoadState const& state, RoadInfo const& info, HppOutput& output);

private:
    bool_t    enable_detect_slot_           = false;
    float64_t x_translate_                  = 2.0;
    float64_t y_translate_                  = 2.0;
    bool_t    first_run_in_for_virtualslot_ = true;
    bool_t    virtual_slot_left_            = true;  // true:left, false:right
    float64_t end_zero_speed_path_length_   = 5.0;
    float64_t smooth_step_                  = 0.1;
};
}  // namespace planning
}  // namespace holo

#endif
