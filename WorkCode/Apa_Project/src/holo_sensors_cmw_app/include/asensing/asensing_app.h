/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file asensing_app.h
 * @brief This header file define the app of asensing
 * @author zhangtongyang@holomatic.com
 * @date May 12, 2021
 */

#ifndef _HOLO_CMW_APPS_ASENSING_APP_H
#define _HOLO_CMW_APPS_ASENSING_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/sensors/asensing/asensing_holocan.h>
#include <holo_base_msg/traits.h>
#include <holo_c/core/types.h>
#include <interface/interface_wrapper.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

namespace holo_cmw
{
using holo::common::GnssPvt;
using holo::common::GnssRawMeasurement;
using holo::common::Imud;

template <typename T>
class AsensingDriverApp
{
public:
    AsensingDriverApp(int32_t id, const std::string& ns) : bus_(id, ns)
    {
    }
    void Setup(const std::string& config_file);

private:
    bool_t GetParameters(const std::string& config_file);
    void   PositionCallback0(const holo::common::GnssPvt& msg);
    void   PositionCallback1(const holo::common::GnssPvt& msg);
    void   ImuCallback(const holo::common::Imud& msg);

    std::string                                                  gnss_pvt_topic_;
    std::string                                                  gnss_pvt_translation_topic_;
    std::string                                                  extrinsic_;
    std::string                                                  imu_topic_;
    std::shared_ptr<UdpInterface<T>>                             interface_;
    std::shared_ptr<holo::sensors::asensing::AsensingDriverT<T>> driver_;

    cmw_wrapper::BusType                      bus_;
    cmw_wrapper::BusType::WriterType<GnssPvt> asen_pos_pub_;
    cmw_wrapper::BusType::WriterType<GnssPvt> asen_pos_translation_pub_;
    cmw_wrapper::BusType::WriterType<Imud>    imu_pub_;
    bool_t                                    use_gps_stamp_;
};
}  // namespace holo_cmw

#endif
