/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ublox.h
 * @brief This header file define the function of ublox ark
 * @author houyujian@holomatic.com
 * @date Dec 12, 2019
 */

#ifndef _HOLO_SENSORS_GNSS_UBLOX_UBLOX_H
#define _HOLO_SENSORS_GNSS_UBLOX_UBLOX_H

#include <holo/common/gnss_pvt.h>
#include <holo/common/gnss_raw_measurement.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/geometry/geographical_transformation.h>
#include <holo/sensors/common/device.h>
#include <holo/sensors/common/interface.h>
#include <holo/sensors/gnss/ublox/ublox_structure.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/yaml.h>
#include <atomic>
#include <functional>

namespace holo
{
namespace sensors
{
namespace ublox
{
using holo::common::GnssPvt;
using holo::common::GnssRawMeasurement;
using holo::sensors::common::Device;

template <typename T>
class UbloxDriverBaseT : public Device
{
public:
    using RawMeasurementCallback = std::function<void(const GnssRawMeasurement&)>;
    using PositionCallback       = std::function<void(const GnssPvt&)>;

    UbloxDriverBaseT(const SensorId& sensor_id = 0)
      : Device(sensor_id)
      , ubx_raw_callback_(nullptr)
      , ubx_pos_callback_(nullptr)
      , ubx_pos_translation_callback_(nullptr)
      , p_dop_(0)
      , gps_week_(0)
    {
    }

    virtual ~UbloxDriverBaseT() = default;

    void InstallGnssRawCallback(const RawMeasurementCallback& callback) noexcept
    {
        ubx_raw_callback_ = callback;
    }
    void InstallPositionCallback(const PositionCallback& callback) noexcept
    {
        ubx_pos_callback_ = callback;
    }
    void InstallPositionTranslationCallback(const PositionCallback& callback) noexcept
    {
        ubx_pos_translation_callback_ = callback;
    }

    bool_t ParseNavPvt(const uint8_t* payload, uint16_t length)
    {
        struct UbxNavPvtMessage data;
        uint32_t                des_size = data.Deserialize(payload, length);
        if (des_size != sizeof(struct UbxNavPvtMessage))
        {
            LOG(ERROR) << "failed to deserialize ubx-nav-pvt message";
            return false;
        }
        p_dop_ = static_cast<float32_t>(data.pDop / 1e2);
        /* Position */
        GnssPvt                 pos;
        float32_t               temp = static_cast<float32_t>(gps_week_ * SEC_PER_WEEK + data.itow / 1e3);
        holo::common::Timestamp gps_stamp(static_cast<uint32_t>(temp), 0);
        holo::common::Timestamp utc_stamp;
        (void)holo::common::Timestamp::GpsToUtc(gps_stamp, utc_stamp);
        pos.SetTimestamp(utc_stamp);
        if ((data.fixType < PvtFixType::FIX_3D) || (gps_week_ < GPS_WEEK_MINIMAL))
        {
            pos.SetMode(GnssPvt::Mode::NO_POSITION);
            pos.SetValidFlags(false, false, false, false);
        }
        else
        {
            pos.SetMode(GnssPvt::Mode::SINGLE_FIX);
            pos.SetValidFlags(true, true, true, true);
        }

        float64_t lat = static_cast<float64_t>(data.lat) / 1e7;
        float64_t lon = static_cast<float64_t>(data.lon) / 1e7;
        pos.SetCoordinate(holo::common::Coordinate::Wgs84Coordinate());
        pos.SetLatitude(lat);
        pos.SetLongitude(lon);
        pos.SetHeight(static_cast<float64_t>(data.height) / 1e3);
        pos.SetVelocityEast(static_cast<float64_t>(data.velE) / 1e3);
        pos.SetVelocityNorth(static_cast<float64_t>(data.velN) / 1e3);
        pos.SetVelocityUp(-static_cast<float64_t>(data.velD) / 1e3);
        pos.SetLatitudeCov(static_cast<float64_t>(data.hAcc) / 1e3);
        pos.SetLongitudeCov(static_cast<float64_t>(data.hAcc) / 1e3);
        pos.SetHeightCov(static_cast<float64_t>(data.vAcc) / 1e3);
        pos.SetVelocityEastCov(static_cast<float64_t>(data.sAcc) / 1e3);
        pos.SetVelocityNorthCov(static_cast<float64_t>(data.sAcc) / 1e3);
        pos.SetVelocityUpCov(static_cast<float64_t>(data.sAcc) / 1e3);

        /* callback */
        if (ubx_pos_callback_)
        {
            ubx_pos_callback_(pos);
        }

        if (ubx_pos_translation_callback_)
        {
            if (ConvertWgs84ToGcj02(lat, lon))
            {
                pos.SetCoordinate(holo::common::Coordinate::Gcj02Coordinate());
                pos.SetLatitude(lat);
                pos.SetLongitude(lon);
                ubx_pos_translation_callback_(pos);
            }
        }

        return true;
    }

    bool_t ParseRxmRawx(const uint8_t* payload, uint16_t length)
    {
        struct UbxRxmRawxMessageHeader header;
        uint32_t                       des_size = header.Deserialize(payload, length);
        if (des_size != sizeof(struct UbxRxmRawxMessageHeader))
        {
            LOG(ERROR) << "failed to deserialize ubx-rxm-rawx message header";
            return false;
        }

        gps_week_ = header.week;

        GnssRawMeasurement raw;
        raw.SetGpsWeek(header.week);
        raw.SetGpsSec(header.rcvTow);
        raw.SetLeapSec(header.leapS);
        raw.SetSatelliteNumber(header.numMeas);
        raw.SetPDop(p_dop_);
        UbxRxmRawxMessageBlock                  block;
        GnssRawMeasurement::RawMeasurementBlock raw_block;
        uint8_t real_meas = (length - sizeof(UbxRxmRawxMessageHeader)) / sizeof(UbxRxmRawxMessageBlock);
        real_meas         = std::min<uint8_t>(real_meas, header.numMeas);
        for (uint8_t i = 0; i < real_meas; i++)
        {
            des_size += block.Deserialize(payload + des_size, length - des_size);
            raw_block.pseudorange_measurement          = block.pr_mes;
            raw_block.carrier_phase_measurement        = block.cp_mes;
            raw_block.doppler_measurement              = block.do_mes;
            raw_block.gnss_identifier                  = block.gnss_id;
            raw_block.satellite_identifier             = block.sv_id;
            raw_block.frequence_identifier             = block.freq_id;
            raw_block.carrier_phase_locktime           = block.locktime;
            raw_block.carrier_noise_ratio              = block.cno;
            raw_block.pseudorange_standard_deviation   = block.pr_stdev;
            raw_block.carrier_phase_standard_deviation = block.cp_stdev;
            raw_block.doppler_standard_deviation       = block.do_stdev;
            raw_block.tracking_status                  = block.trk_stat;
            raw.SetRawMeasurementBlock(raw_block, i);
        }

        if (ubx_raw_callback_)
        {
            ubx_raw_callback_(raw);
        }

        return true;
    }

    virtual void ParseData(const T&) = 0;

protected:
    /* callbacks */
    RawMeasurementCallback ubx_raw_callback_;
    PositionCallback       ubx_pos_callback_;
    PositionCallback       ubx_pos_translation_callback_;
    /* parsing data */
    float32_t             p_dop_;
    std::atomic<uint16_t> gps_week_;
};

template <typename T>
class UbloxDriverT
{
public:
    UbloxDriverT() = 0;
};

}  // namespace ublox
}  // namespace sensors
}  // namespace holo

#endif
