/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file source_checker.cpp
 * @brief The instantiation of source state check.
 * @author lichao@holomatic.com
 * @author Wenzhi Liu(liuwenzhi@holomatic.com)
 * @date Sep 24, 2019
 */

#include <holo/localization/tools/source_checker.h>
#include <holo/localization/tools/impl/source_checker.hpp>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SourceCheckerParameters SourceCheckerParameters::LoadYaml(const holo::yaml::Node& yaml_node)
{
    SourceCheckerParameters params;

    try
    {
        params.enable_checker                              = yaml_node["enable_checker"].as<bool_t>();
        params.frequency                                   = yaml_node["frequency"].as<float32_t>();
        params.status_counter_threshold                    = yaml_node["status_counter_threshold"].as<int32_t>();
        params.max_timestamp_gap_tolerance                 = yaml_node["max_timestamp_gap_tolerance"].as<float32_t>();
        params.min_period_multiple_in_normal_consistency   = yaml_node["min_period_multiple_in_normal_consistency"].as<float32_t>();
        params.max_period_multiple_in_normal_consistency   = yaml_node["max_period_multiple_in_normal_consistency"].as<float32_t>();
        params.min_period_multiple_in_low_obstruction      = yaml_node["min_period_multiple_in_low_obstruction"].as<float32_t>();
        params.source_actual_frequency_statistics_interval = yaml_node["source_actual_frequency_statistics_interval"].as<float32_t>();
        params.enable_log                                  = yaml_node["enable_log"].as<bool_t>();
        const std::string coord_string                     = yaml_node["coordinate"].as<std::string>();

        if (!coord_string.empty())
        {
            params.coord = CoordinateType(std::stoi(coord_string, NULL, 16));
        }
    }
    catch(const std::exception& e)
    {
        LOG(ERROR) << e.what();
        throw std::runtime_error("Can not load yaml node, please recheck the yaml file for missing parameters!");
    }

    return params;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template class SourceCheckerT<GnssPositionType>;
template class SourceCheckerT<GnssPvtType>;
template class SourceCheckerT<OdometryType>;
template class SourceCheckerT<ImuType>;
template class SourceCheckerT<ChassisState>;
template class SourceCheckerT<RoadFrame>;
}  // namespace localization
}  // namespace holo
