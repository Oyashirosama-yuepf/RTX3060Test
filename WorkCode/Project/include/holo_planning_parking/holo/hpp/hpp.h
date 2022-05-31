/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hpp.h
 * @brief the header of planning of hpp
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-09-20
 */

#ifndef _HOLO_PLANNING_HPP_H_
#define _HOLO_PLANNING_HPP_H_

#include <holo/hpp/gateway_hpp.h>
#include <holo/hpp/path_provider.h>
#include <holo/hpp/scenario/scenario_parking_base.h>
#include <holo/planning/common/planning_command.h>
#include <holo/planning/common/planning_state.h>
#include <holo/planning/thread/worker.h>

namespace holo
{
namespace planning
{
class Listener
{
public:
    /**
     * @brief publish path
     *
     * @param path The path
     */
    virtual void PubPath(common::Path& path) = 0;

    /**
     * @brief publish pridict path
     *
     * @param pridict_path The pridict path to be published.
     */
    virtual void PubPridictPath(common::Path& pridict_path) = 0;

    /**
     * @brief publish planning command
     *
     * @param planning_command The planning command to be published.
     */
    virtual void PubPlanningCommand(holo::planning::PlanningCommand planning_command) = 0;

    /**
     * @brief publish path attribute
     *
     * @param path_attribute The path attribute to be published.
     */
    virtual void PubPathAttribute(holo::parking::planning::PathAttribute& path_attribute) = 0;

    /**
     * @brief publish planning state
     *
     * @param planning_state The planning state to be published.
     */
    virtual void PubPlanningState(holo::planning::HPAPlanningState planning_state) = 0;

    /**
     * @brief publish planning state for AVP
     *
     * @param planning_state The planning state to be published.
     */
    virtual void PubPlanningStateAVP(holo::planning::HPAPlanningState planning_state) = 0;

    /**
     * @brief publish fault state
     *
     * @param fault_state The planning state to be published.
     */
    virtual void PubFaultState(uint32_t fault_state) = 0;
};

/**
 * @brief      hpp class
 * @details    A gaint class, hold the most important resource of planning
 *             module
 */
class Hpp : public Worker
{
public:
    /**
     * @brief Constructor
     *
     * @param hz the working frequency
     */
    Hpp(float64_t hz = 20, bool_t is_map_mode = true);

    /**
     * @brief Destroys the object.
     */
    virtual ~Hpp();

    /**
     * @brief add listener
     *
     * @param listener
     */
    void SetListener(Listener* listener);

    /**
     * @brief Sets the gateway.
     *
     * @param gateway The gateway
     */
    void SetGateway(const std::shared_ptr<GatewayHpp>& gateway);

    /**
     * @brief Gets the gateway.
     *
     * @return The gateway.
     */
    std::shared_ptr<GatewayHpp> GetGateway();

    /**
     * @brief work loop function.
     *
     * @return True if work as expectation, False otherwise.
     */
    virtual bool DoWork();

    /**
     * @brief reset function.
     *
     * @return True if reset as expectation, False otherwise.
     */
    bool Reset();

protected:
    /**
     * @brief message listener
     */
    Listener* listener_;
    /**
     * @brief      gateway.
     */
    std::shared_ptr<holo::planning::GatewayHpp> plan_gateway_;
    /**
     * @brief      scenario.
     */
    std::shared_ptr<ScenarioParkingBase> scenario_;
    /**
     * @brief      take over counter, if counter > 3 --> takeoverd, this logic happens because limit in vs
     */
    uint32_t takeover_counter_;
    /**
     * @brief      true if need stop.
     */
    bool stop_;
    /**
     * @brief      planning command
     */
    PlanningCommand planning_command_;
    /**
     * @brief      planning state
     */
    HPAPlanningState planning_state_;

    /**
     * @brief ture if is in map mode
     */
    bool_t is_map_mode_;

    /**
     * @brief history fault code
     */
    uint32_t history_fault_code_;

private:
    /**
     * @brief judge static function.
     *
     * @param hpp_car_road_state The car road state
     *
     * @return True if static, False otherwise.
     */
    bool IsStatic(const HppCarRoadState& hpp_car_road_state);

    /**
     * @brief preprocess function.
     *
     * @param hpp_car_road_state The car road state
     *
     * @return True if preprocess as expectation, False otherwise.
     */
    bool Preprocess(const HppCarRoadState& hpp_car_road_state, HppOutput& output);

    /**
     * @brief Topic publish function.
     *
     * @param hpp_car_road_state The car road state
     * @param output data output from scenario
     */
    void Publish(HppCarRoadState const& hpp_car_road_state, HppOutput& output);

    /**
     * @brief Error handle function
     */
    void ErrorHandler(HppOutput& output);
};

}  // namespace planning
}  // namespace holo

#endif
