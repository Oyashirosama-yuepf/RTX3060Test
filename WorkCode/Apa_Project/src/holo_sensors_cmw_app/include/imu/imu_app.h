/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_app.h
 * @brief This header file define the app of imu driver
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/17
 */

#ifndef HOLO_CMW_APPS_IMU_IMU_APP_H
#define HOLO_CMW_APPS_IMU_IMU_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/imu/aceinna/aceinna_holocan.h>
#include <holo/sensors/imu/aceinna/aceinna_someip.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>
#include <interface/interface_wrapper.h>

namespace holo_cmw
{
using holo::common::Imud;
using holo::sensors::ImuDriverT;

template <typename Td, typename Ti>
class ImuDriverApp
{
public:
    /**
     * @brief Construct a new Aceinna Driver object
     *
     * @param argc
     * @param argv
     * @param name
     */
    ImuDriverApp(int32_t id, const std::string& ns) : bus_(id, ns)
    {
    }

    /**
     * @brief setup this node
     *
     * @param config_file
     */
    void Setup(const std::string& config_file);

private:
    /**
     * @brief      Gets the parameters.
     *
     * @param[in]  config_file  The configuration file
     *
     * @return     The parameters.
     */
    bool_t GetParameters(const std::string& config_file);

    /**
     * @brief      callback service for ...
     *
     * @param[in]  msg   the message comes from the ... driver
     *
     * @note       this routine fetch and publish the ... messages
     */
    void ImuCallback(const holo::common::Imud& msg);

private:
    std::string                            extrinsic_;
    std::string                            imu_topic_;
    bool_t                                 use_gps_stamp_;
    cmw_wrapper::BusType                   bus_;
    cmw_wrapper::BusType::WriterType<Imud> imu_pub_;
    std::shared_ptr<Ti>                    interface_;
    std::shared_ptr<Td>                    driver_;
};

}  // namespace holo_cmw

#endif
