/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file planning_hpp_app.h
 * @brief the header of planning hpp
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-11-26
 */

#ifndef _HOLO_CMW_APPS_PLANNING_HPP_H_
#define _HOLO_CMW_APPS_PLANNING_HPP_H_

#include <signal.h>
#include <cmw_wrapper/cmw_bus.h>
#include <holo_base_msg/traits.h>
#include <holo_parking_msg/traits.h>

#include <holo/hpp/hpp_builder.h>

namespace holo_cmw
{
class PlanningHppApp : public holo::planning::Listener
{
public:
    using BusType                = cmw_wrapper::BusType;
    using Hpp                    = holo::planning::Hpp;
    using PathAttribute          = holo::parking::planning::PathAttribute;
    using ObstacleGeneralPtrList = holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>;

    PlanningHppApp(int argc, char** argv, const std::string& config_file, uint32_t domain_id);

    /**
     * @brief publish path
     *
     * @param path The path to be published.
     */
    virtual void PubPath(holo::Path& path) override;

    /**
     * @brief publish pridict path
     *
     * @param pridict_path The pridict path to be published.
     */
    virtual void PubPridictPath(holo::Path& pridict_path) override;

    /**
     * @brief publish planning command
     *
     * @param planning_command The planning command to be published.
     */
    virtual void PubPlanningCommand(holo::planning::PlanningCommand planning_command) override;

    /**
     * @brief publish path attribute
     *
     * @param path_attribute The path attribute to be published.
     */
    virtual void PubPathAttribute(PathAttribute& path_attribute) override;

    /**
     * @brief publish planning state
     *
     * @param planning_state The planning state to be published.
     */
    virtual void PubPlanningState(holo::planning::HPAPlanningState planning_state) override;

    /**
     * @brief publish fault state
     *
     * @param fault_state The planning state to be published.
     */
    virtual void PubFaultState(uint32_t fault_state);

    /**
     * @brief publish planning state for AVP
     *
     * @param planning_state The planning state to be published.
     */
    virtual void PubPlanningStateAVP(holo::planning::HPAPlanningState planning_state);
    void Run();

private:
    void InitConfig(const std::string& config_file);

    void CallbackChassisState(holo::ChassisState const& chassis_state);
    void CallbackFreeSpace(holo::common::AutoFreespace<holo::geometry::Point3f> const& free_space);
    // void CallbackObstacleListState(const CMW::ObstacleGeneralListTopicType& msg);
    void CallbackDetection(ObstacleGeneralPtrList const& detection);
    void CallbackOdometry(holo::common::Odometryd const& odometry);
    void CallbackRecovery(holo::uint32_t recovery_status);
    void CallbackHppParkingCommand(holo::uint32_t hpp_parking_command);
    void CallbackHeartbeat(holo::uint32_t heartbeat);
    void CallbackHpaCommand(holo::uint32_t hpa_command);

private:
    holo::float64_t hz_;
    std::string     file_name_;
    std::string     path_topic_;
    std::string     pridict_path_topic_;
    std::string     planning_command_topic_;
    std::string     path_attribute_topic_;
    std::string     chassis_state_topic_;
    std::string     obstacle_list_topic_;
    std::string     free_space_topic_;
    std::string     detection_topic_;
    std::string     odometry_topic_;
    std::string     recovery_topic_;
    std::string     hpp_parking_command_topic_;
    std::string     heartbeat_topic_;
    std::string     hpa_command_topic_;
    std::string     planning_state_topic_;
    std::string     fault_state_topic_;

    BusType::ReaderType<holo::ChassisState> chassis_state_reader_;  ///< chassis state reader
    BusType::ReaderType<holo::common::AutoFreespace<holo::geometry::Point3f>> free_space_reader_;  ///< free space
                                                                                                   ///< reader
    BusType::ReaderType<ObstacleGeneralPtrList> detection_reader_;                           ///< detection reader
    BusType::ReaderType<holo::common::Odometryd>      odometry_reader_;                            ///< odometry reader
    BusType::ReaderType<holo::uint32_t>               recovery_status_reader_;      ///< recovery status reader
    BusType::ReaderType<holo::uint32_t>               hpp_parking_command_reader_;  ///< parking command reader
    BusType::ReaderType<holo::uint32_t>               heartbeat_reader_;            ///< heartbeat reader
    BusType::ReaderType<holo::uint32_t>               hpa_command_reader_;          ///< hpa command reader
    BusType::WriterType<holo::uint32_t>               planning_command_writer_;     ///< planning command reader
    BusType::WriterType<holo::Pathd>                  path_writer_;                 ///< path writer
    BusType::WriterType<holo::Pathd>                  pridict_path_writer_;         ///< pridict path writer
    BusType::WriterType<PathAttribute>                path_attribute_writer_;       ///< path attribute writer
    BusType::WriterType<holo::uint32_t>               planning_state_writer_;  ///< planning state writer
    BusType::WriterType<holo::uint32_t>               fault_state_writer_;     ///< fault state writer

    std::shared_ptr<BusType> bus_;  ///< shared ptr point to control_bus
    std::shared_ptr<Hpp>     hpp_;  ///< hpp interface
};

}  // namespace holo_cmw

#endif
