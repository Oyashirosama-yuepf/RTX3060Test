/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ublox_driver_app.h
 * @brief This header file define the app of ublox in ark
 * @author houyujian@holomatic.com
 * @date Dec 16, 2019
 */
#ifndef _HOLO_CMW_APPS_GNSS_UBLOX_APP_H
#define _HOLO_CMW_APPS_GNSS_UBLOX_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/sensors/gnss/ublox/ublox_rawbuf.h>
#include <holo/sensors/gnss/ublox/ublox_someip.h>
#include <holo_base_msg/traits.h>
#include <holo_c/core/types.h>
#include <interface/interface_wrapper.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

namespace holo_cmw
{
using holo::common::GnssPvt;
using holo::common::GnssRawMeasurement;

template <typename T>
class UbloxDriverApp
{
public:
    /**
     * @brief Construct a new Ublox Driver App object
     *
     */
    UbloxDriverApp(int32_t id, const std::string& ns) : bus_(id, ns)
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
     * @brief Get the Parameters object
     *
     * @param config_file
     * @return true
     * @return false
     */
    bool_t GetParameters(const std::string& config_file);
    /**
     * @brief gnss raw measurement callback service
     *
     * @param msg
     */
    void GnssRawMeasurementCallback(const GnssRawMeasurement& msg);
    /**
     * @brief position callback service
     *
     * @param msg
     */
    void PositionCallback0(const holo::common::GnssPvt& msg);
    /**
     * @brief position callback service
     *
     * @param msg
     */
    void PositionCallback1(const holo::common::GnssPvt& msg);

private:
    cmw_wrapper::BusType                                   bus_;
    std::string                                            gnss_raw_measurement_topic_;
    std::string                                            gnss_pvt_topic_;
    std::string                                            gnss_pvt_translation_topic_;
    std::shared_ptr<UdpInterface<T>>                       interface_;
    std::shared_ptr<holo::sensors::ublox::UbloxDriverT<T>> driver_;
    cmw_wrapper::BusType::WriterType<GnssRawMeasurement>   ubx_raw_pub_;
    cmw_wrapper::BusType::WriterType<GnssPvt>              ubx_pos_pub_;
    cmw_wrapper::BusType::WriterType<GnssPvt>              ubx_pos_translation_pub_;
};

}  // namespace holo_cmw

#endif
