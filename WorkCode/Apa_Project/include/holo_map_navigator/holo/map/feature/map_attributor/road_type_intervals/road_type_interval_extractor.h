/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_type_interval_extractor.h
 * @brief extract road type intervals
 * @author lisong(lisong@holomatic.com)
 * @date "2020-08-10"
 */

#ifndef HOLO_MAP_FEATURE_ROAD_TYPE_INTERVAL_EXREACTOR_ROAD_TYPE_INTERVAL_EXREACTOR_H_
#define HOLO_MAP_FEATURE_ROAD_TYPE_INTERVAL_EXREACTOR_ROAD_TYPE_INTERVAL_EXREACTOR_H_

#include <deque>
#include <memory>
#include <utility>
#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/common/geometry.h>
#include <holo/map/common/match_info.h>
#include <holo/map/feature/navigator/navigator_config.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/retriever/retriever.h>
#include <holo/map/service/client/engine/helper.h>
#include <holo/map/service/client/matcher/matcher.h>

namespace holo
{

namespace map
{

namespace attribute
{

namespace road_type
{

/**
 * @brief This calss defines a extractor to extract road type intervals for HD Map.
 */
class RoadTypeIntervalExtractor
{
public:
    /**
     * @brief this class defines road type interval
     */
    struct RoadTypeInterval  
    {   
        /**
         * The first element is distance from its start point to car position, 
         * second is end point to car position.
         */
        std::pair<holo::float32_t, holo::float32_t>                              road_type_interval;
        holo::map::service::client::engine::helper::raw::RawRoadTypeV0::RoadType road_type;     ///< Road type
        holo::map::service::client::engine::helper::raw::RawRoadAttributeTypeV0  road_attribute; ///< Road attribute related to this interval
    };

    /**
     * @brief this class defines output of RoadTypeIntervalExtractor
     *
     */
    struct Output
    {
        std::vector<RoadTypeInterval> road_type_intervals;
        static std::string FormatToString(Output const& obj);
    };

public:
    /**
     * @brief Constructor
     */
    RoadTypeIntervalExtractor() = default;

    /**
     * @brief Destructor
     */
    ~RoadTypeIntervalExtractor() = default;

    // RoadTypeIntervalExtractor object can not be copied and moved.
    RoadTypeIntervalExtractor(RoadTypeIntervalExtractor const& other) = delete;
    RoadTypeIntervalExtractor& operator=(RoadTypeIntervalExtractor const& other) = delete;

    RoadTypeIntervalExtractor(RoadTypeIntervalExtractor&& other) = delete;
    RoadTypeIntervalExtractor& operator=(RoadTypeIntervalExtractor&& other) = delete;

public:
    /**
     * @brief Init a RoadTypeIntervalExtractor object
     *
     * @param[in] ptr_ret Retriever pointer
     * @param[in] ptr_config Config pointer
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Init(RetrieverSPType const& ptr_ret, navigator::config::NavigatorConfigSPtr const& ptr_config);

    /**
     * @brief Run mian process pipeline to generate output.
     *
     * @param[in] match_info Given match info
     * @param[in] route_info Given route info
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Run(holo::map::MapMatchInfo const& match_info, holo::map::RouteInfo2 const& route_info);

    /**
     * @brief Calculate road type intervals by road ids and start point.
     * @details Start with start_point(should in range of geometry points from the first road in road_ids) and walk through road from road_ids sequentially.
     * @param[in] road_ids Vector of road id
     * @param[in] start_point Point this process start with, should on the first road from road_ids.
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t CalculateRoadTypeIntervalsByRoadIDs(holo::map::service::client::engine::helper::raw::RawFeatureIdVectorTypeV0 const& road_ids, holo::map::service::client::engine::helper::raw::RawGeoPointTypeV0 const& start_point);

    /**
     * @brief Get result output of road type interval extractor
     *
     * @return Result road type intervals
     */
    Output const& GetOutput() const
    {
        return output_;
    }

    /**
     * @brief Reset road type interval extractor.
     *
     * @return Nothing
     */
    void Reset()
    {
        output_ = Output();
    }

private:
    // Retriver pointer
    RetrieverSPType ret_ptr_ = nullptr;

    // Search range to extract road type intervals
    holo::float32_t search_range_ = 3000.0f;

    // Internal result road type intervals of extractor
    Output output_;
};  // end for class RoadTypeIntervalExtractor

// Handy typedefs
using RoadTypeIntervalExtractorSPtrType  = std::shared_ptr<RoadTypeIntervalExtractor>;
using RoadTypeIntervalExtractorCSPtrType = std::shared_ptr<RoadTypeIntervalExtractor const>;

}  // end for road_type
}  // end for attribute
}  // end for namespace map
}  // end for namespace holo

#endif  // end for HOLO_MAP_FEATURE_ROAD_TYPE_INTERVAL_EXREACTOR_ROAD_TYPE_INTERVAL_EXREACTOR_H_
