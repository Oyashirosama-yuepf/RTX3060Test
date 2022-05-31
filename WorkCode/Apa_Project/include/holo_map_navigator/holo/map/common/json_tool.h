/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file  marshal.h
 * @brief Verbose
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-12-28"
 */

#ifndef HOLO_MAP_NAVIGATOR_COMMON_JSON_TOOL_H_
#define HOLO_MAP_NAVIGATOR_COMMON_JSON_TOOL_H_

#include <memory>

#include <holo/map/base/feature_id/feature_id.h>
#include <holo/map/common/common_define.h>
#include <holo/common/odometry.h>
#include <holo/map/common/match_info.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace common
{
/**
 * @addtogroup navigator
 * @{
 *
 */
/**
 * @breif Tool for generate JSON string
 */
class JsonTool
{
public:
    using LocalMapOdometryType = ::holo::common::LocalMapOdometryT<holo::float64_t, 16U>;
    using MatchingResultType  = LocalMapOdometryType::MatchingResult;
    using MatchingResultsType = holo::container::Vector<MatchingResultType, 16U>;

public:
    static std::string FormatToString(std::vector<holo::uint64_t> const& values)
    {
        std::stringstream ss;
        ss << "[";
        std::size_t size_values = values.size();
        for (std::size_t i = 0U; i < size_values; ++i)
        {
            ss << "\"" << values[i] << "\"";
            if (size_values - 1 != i)
            {
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }

    static std::string FormatToString(MatchingResultsType const& match_results)
    {
        std::stringstream ss;
        ss << "[";
        std::size_t const size_results = match_results.size();
        for (std::size_t i = 0U; i < size_results; ++i)
        {
            MatchingResultType const& result = match_results[i];
            ss << FormatToString(result);
            if (size_results - 1 != i)
            {
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }

    static std::string FormatToString(MatchingResultType const& match_result)
    {
        std::stringstream ss;
        ss << "{";
        ss << " \"link_id\": \"" << match_result.link_id;
        ss << "\", \"lane_id\": \"" << match_result.lane_id;
        ss << "\", \"lateral_off_middle\": \"" << match_result.lateral_off_middle;
        ss << "\", \"longitudinal_off_start\": \"" << match_result.longitudinal_off_start;
        ss << "\", \"longitudinal_off_end\": \"" << match_result.longitudinal_off_end;
        ss << "\", \"lateral_off_right\": \"" << match_result.lateral_off_right;
        ss << "\", \"lateral_off_left\": \"" << match_result.lateral_off_left;
        ss << "\"}";
        return ss.str();
    }

    static std::string FormatToString(MapMatchInfo const& info)
    {
        std::stringstream ss;
        ss << "{";
        ss << " \"lane_id\": \"" << info.lane_id;
        ss << "\", \"link_id\": \"" << info.link_id;
        ss << "\", \"distance\": \"" << info.distance;
        ss << "\", \"dist_to_middle\": \"" << info.dist_to_middle;
        ss << "\", \"link_length\": \"" << info.link_length;
        ss << "\"}";
        return ss.str();
    }

    static std::string FormatToString(std::vector<MapMatchInfo> const& infos)
    {
        std::size_t const size_infos = infos.size();
        std::stringstream ss;
        ss << "[";
        for (std::size_t i = 0U; i < size_infos; ++i)
        {
            ss << FormatToString(infos[i]);
            if (i != size_infos - 1)
            {
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }
};
}  // namespace common
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_NAVIGATOR_COMMON_JSON_TOOL_H_ */
