/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file longitudinal_start_and_stop_app.h
 * @brief the header of longitudinal_start_and_stop_app
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-09-20
 */

#ifndef _CMW_APPS_LONGITUDINAL_START_AND_STOP_H_
#define _CMW_APPS_LONGITUDINAL_START_AND_STOP_H_

#include <cmw_wrapper/cmw_bus.h>
#include <holo_base_msg/traits.h>

#include <holo/hpp/longitudinal_start_and_stop.h>

namespace holo_cmw
{
class LongitudinalStartAndStopApp : public holo::tools::Listener
{
public:
    using BusType                  = cmw_wrapper::BusType;
    using LongitudinalStartAndStop = holo::tools::LongitudinalStartAndStop;

    LongitudinalStartAndStopApp(int argc, char** argv, const std::string& config_file, uint32_t domain_id);

    /**
     * @brief publish path
     *
     * @param path The path to be published.
     */
    virtual void PubPath(holo::Path& path);

    /**
     * @brief publish planning command
     *
     * @param planning_command The planning command to be published.
     */
    virtual void PubPlanningCommand(holo::planning::PlanningCommand planning_command);

    void Run();

private:
    void InitConfig(const std::string& config_file);

    void CallbackChassisState(holo::ChassisState const& chassis_state);
    void CallbackOdometry(holo::common::Odometryd const& odometry);

private:
    holo::float64_t hz_;
    std::string     lib_config_name_;
    std::string     path_topic_;
    std::string     planning_command_topic_;
    std::string     chassis_state_topic_;
    std::string     odometry_topic_;

    BusType::ReaderType<holo::ChassisState>      chassis_state_reader_;     ///< chassis state reader
    BusType::ReaderType<holo::common::Odometryd> odometry_reader_;          ///< odometry reader
    BusType::WriterType<holo::uint32_t>          planning_command_writer_;  ///< planning command reader
    BusType::WriterType<holo::Pathd>             path_writer_;              ///< path writer

    std::shared_ptr<BusType>                  bus_;                          ///< shared ptr point to control_bus
    std::shared_ptr<LongitudinalStartAndStop> longitudinal_start_and_stop_;  ///< lon test object
};

}  // namespace holo_cmw

#endif
