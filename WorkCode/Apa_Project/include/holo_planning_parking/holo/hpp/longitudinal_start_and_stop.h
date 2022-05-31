/**
 * @file longitudinal_start_and_stop.h
 * @brief longitudinal_start_and_stop
 * @author Zhang Chun(zhangchun@holomatic.com)
 * @date 2020-11-11
 */

#ifndef _LONGITUDINAL_START_AND_STOP_H_
#define _LONGITUDINAL_START_AND_STOP_H_

#include <holo/planning/common/headers.h>
#include <holo/planning/common/planning_command.h>
#include <holo/planning/framework/gateway_base.h>
#include <holo/planning/planner/velocity_planner/trapezoid_velocity_planner.h>
#include <holo/planning/thread/worker.h>

namespace holo
{
namespace tools
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
     * @brief publish planning command
     *
     * @param planning_command The planning command to be published.
     */
    virtual void PubPlanningCommand(holo::planning::PlanningCommand planning_command) = 0;
};

class LongitudinalStartAndStop : public holo::planning::Worker
{
public:
    /**
     * @brief Mode class enum
     */
    enum class Mode
    {
        IDLE,                ///< IDLE
        PRECISE_STOP,        ///< PRECISE_STOP
        SHORT_DISPLACEMENT,  ///< SHORT_DISPLACEMENT
    };

public:
    /**
     * @brief Constructor
     *
     * @param hz the working frequency
     * @param lib_config_name the yaml file path
     */
    LongitudinalStartAndStop(float64_t const& hz, std::string const& lib_config_name);

    /**
     * @brief add listener
     *
     * @param listener
     */
    void SetListener(Listener* listener);

    /**
     * @brief      Sets the gateway.
     *
     * @param[in]  gateway  The gateway
     */
    void SetGateway(std::shared_ptr<holo::planning::GatewayBase> const& gateway);

    /**
     * @brief      Gets the gateway.
     *
     * @return     The gateway.
     */
    std::shared_ptr<holo::planning::GatewayBase> GetGateway();

    /**
     * @brief      work loop function.
     *
     * @return     True if work as expectation, False otherwise.
     */
    virtual bool DoWork() override;

private:
    void loadYamlFile(std::string const& yaml_path);
    void shortDisplace(common::Path& path, geometry::Point2 const& current_point, float64_t current_speed);
    void preciseStop(common::Path& path, geometry::Point2 const& current_point, float64_t current_speed);

private:
    /**
     * @brief message listener
     */
    Listener* listener_;

    /**
     * @brief gateway
     */
    std::shared_ptr<holo::planning::GatewayBase> gateway_;

    /**
     * @brief mode
     */
    Mode mode_;

    /**
     * @brief max speed
     */
    float64_t max_speed_;

    /**
     * @brief target displacement
     */
    float64_t target_displacement_;

    /**
     * @brief average speed window
     */
    uint8_t average_speed_window_;

    /**
     * @brief path step
     */
    float64_t path_step_;

    /**
     * @brief path length
     */
    float64_t path_length_;

    /**
     * @brief average speed
     */
    float64_t average_speed_;

    /**
     * @brief accumulate displacement
     */
    float64_t accumulate_displacement_;

    /**
     * @brief start point
     */
    std::shared_ptr<geometry::Point2> start_point_;

    /**
     * @brief default speed planner
     */
    holo::planning::TrapezoidVelocityPlanner velocity_planner_;
};

}  // namespace tools
}  // namespace holo

#endif  //_HOLO_PCTOOLKITS_LATERAL_PATH_FOLLOWER_H_
