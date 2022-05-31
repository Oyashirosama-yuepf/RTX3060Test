#ifndef HOLO_IO_COMMON_GNSS_RAW_MEASUREMENT_H_
#define HOLO_IO_COMMON_GNSS_RAW_MEASUREMENT_H_

#include <holo/utils/yaml.h>
#include <holo/io/utils/utils.h>
#include <holo/common/gnss_raw_measurement.h>

namespace YAML
{
template <>
struct convert<holo::common::GnssRawMeasurement::RawMeasurementBlock>
{
    using ValueType = holo::common::GnssRawMeasurement::RawMeasurementBlock;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["pseudorange_measurement"]          = rhs.pseudorange_measurement;
        node["carrier_phase_measurement"]        = rhs.carrier_phase_measurement;
        node["doppler_measurement"]              = rhs.doppler_measurement;
        node["gnss_identifier"]                  = static_cast<uint16_t>(rhs.gnss_identifier);
        node["satellite_identifier"]             = static_cast<uint16_t>(rhs.satellite_identifier);
        node["frequence_identifier"]             = static_cast<uint16_t>(rhs.frequence_identifier);
        node["carrier_phase_locktime"]           = rhs.carrier_phase_locktime;
        node["carrier_noise_ratio"]              = static_cast<uint16_t>(rhs.carrier_noise_ratio);
        node["pseudorange_standard_deviation"]   = static_cast<uint16_t>(rhs.pseudorange_standard_deviation);
        node["carrier_phase_standard_deviation"] = static_cast<uint16_t>(rhs.carrier_phase_standard_deviation);
        node["doppler_standard_deviation"]       = static_cast<uint16_t>(rhs.doppler_standard_deviation);
        node["tracking_status"]                  = static_cast<uint16_t>(rhs.tracking_status);
        return node;
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.pseudorange_measurement          = node["pseudorange_measurement"].as<holo::float64_t>();
            rhs.carrier_phase_measurement        = node["carrier_phase_measurement"].as<holo::float64_t>();
            rhs.doppler_measurement              = node["doppler_measurement"].as<holo::float64_t>();
            rhs.gnss_identifier                  = node["gnss_identifier"].as<holo::uint16_t>();
            rhs.satellite_identifier             = node["satellite_identifier"].as<holo::uint16_t>();
            rhs.frequence_identifier             = node["frequence_identifier"].as<holo::uint16_t>();
            rhs.carrier_phase_locktime           = node["carrier_phase_locktime"].as<holo::uint16_t>();
            rhs.carrier_noise_ratio              = node["carrier_noise_ratio"].as<holo::uint16_t>();
            rhs.pseudorange_standard_deviation   = node["pseudorange_standard_deviation"].as<holo::uint16_t>();
            rhs.carrier_phase_standard_deviation = node["carrier_phase_standard_deviation"].as<holo::uint16_t>();
            rhs.doppler_standard_deviation       = node["doppler_standard_deviation"].as<holo::uint16_t>();
            rhs.tracking_status                  = node["tracking_status"].as<holo::uint16_t>();
            return true;
        }
        catch (...)
        {
            return false;
        }
    };
};

template <>
struct convert<holo::common::GnssRawMeasurement>
{
    using ValueType           = holo::common::GnssRawMeasurement;
    using RawMeasurementBlock = ValueType::RawMeasurementBlock;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["gps_second"]       = rhs.GetGpsSec();
        node["gps_week"]         = rhs.GetGpsWeek();
        node["leap_second"]      = static_cast<holo::int16_t>(rhs.GetLeapSec());
        node["pdop"]             = rhs.GetPDop();
        node["satellite_number"] = static_cast<holo::uint16_t>(rhs.GetSatelliteNumber());
        for (size_t i = 0; i < rhs.GetSatelliteNumber(); ++i)
        {
            RawMeasurementBlock block;
            rhs.GetRawMeasurementBlock(block, i);
            node["raw_block"].push_back(block);
        }
        return node;
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetGpsSec(node["gps_second"].as<holo::float64_t>());
            rhs.SetGpsWeek(node["gps_week"].as<holo::float64_t>());
            rhs.SetLeapSec(node["leap_second"].as<holo::int16_t>());
            rhs.SetPDop(node["pdop"].as<holo::float32_t>());
            rhs.SetSatelliteNumber(node["satellite_number"].as<holo::uint16_t>());

            size_t i = 0U;
            for (YAML::const_iterator it = node["raw_block"].begin(); it != node["raw_block"].end(); ++it)
            {
                RawMeasurementBlock block = it->as<RawMeasurementBlock>();
                rhs.SetRawMeasurementBlock(block, i++);
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    };
};

}  // namespace YAML

#endif
