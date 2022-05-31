/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hpp.h
 * @brief the header of path process
 * @author lizhao(lizhao@holomatic.com)
 * @date 2021-01-27
 */

#ifndef _HOLO_PLANNING_PATH_PROCESS_H_
#define _HOLO_PLANNING_PATH_PROCESS_H_

#include <holo/hpp/gateway_hpp.h>
#include <holo/hpp/path_preprocess/path_preprocess.h>
#include <holo/planning/common/planning_state.h>
#include <holo/planning/thread/worker.h>

namespace holo
{
namespace planning
{
class Monitor
{
public:
    /**
     * @brief publish path process state
     *
     * @param planning_state The path process state to be published.
     */
    virtual void PubPathOptimizationState(holo::planning::PathProcessState path_process_state) = 0;

    /**
     * @brief publish path process fault code
     *
     * @param fault_state The fault state.
     */
    virtual void PubFaultState(uint32_t fault_state) = 0;
};

/**
 * @brief      hpp class
 * @details    A gaint class, hold the most important resource of planning
 *             module
 */
class PathProcess : public Worker
{
public:
    /**
     * @brief Constructor
     *
     * @param hz the working frequency
     */
    PathProcess(float64_t hz = 20);

    /**
     * @brief Destroys the object.
     */
    virtual ~PathProcess();

    /**
     * @brief add monitor
     *
     * @param monitor
     */
    void SetMonitor(Monitor* monitor);

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
     * @brief message monitor
     */
    Monitor* monitor_;

    /**
     * @brief      gateway.
     */
    std::shared_ptr<holo::planning::GatewayHpp> plan_gateway_;

    /**
     * @brief      path preprocess.
     */
    std::shared_ptr<PathPreprocess> path_preprocess_;

    /**
     * @brief      path process state
     */
    PathProcessState path_process_state_;

    /**
     * @brief      route id
     */
    uint8_t route_id_;

private:
};

}  // namespace planning
}  // namespace holo

#endif
