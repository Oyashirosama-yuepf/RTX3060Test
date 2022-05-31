/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file types.h
 * @brief the definition of types
 * @author duyanwei@holomatic.com
 * @date Oct-12-2019
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_PROCESSOR_TYPES_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_PROCESSOR_TYPES_H_

#include <unordered_map>

#include <holo/common/lane_boundary2.h>
#include <holo/common/optional.h>
#include <holo/common/camera_lane_boundary.h>
#include <holo/geometry/polyfit2.h>
#include <holo/localization/common/stamped.h>
#include <holo/localization/common/types.h>
#include <holo/localization/tightly_coupled_fusion/map/map_service_client_base.h>
#include <holo/log/hololog.h>
#include <holo/map/common_object.h>
#include <holo/map/current_route_info.h>
#include <holo/map/lane_info.h>
#include <holo/map/link_info.h>
#include <holo/os/tictoc_timer.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup lane
 * @{
 *
 */

/**
 * @brief define basic types
 *
 * @note define sepcific types for lane-based localization module or types from holo::localization:: will be used
 * @author duyanwei@holomatic.com
 */

// algorithm types
using Polyfit2Type = holo::geometry::Polyfit2T<Scalar>;

// lane types
using CameraLaneBoundaryType = holo::localization::CameraLaneBoundaryType;
using CameraLaneBoundariesType = holo::localization::CameraLaneBoundariesType;

// HD Map related types
using LinkInfoType         = holo::map::LinkInfo;
using LinkInfosType        = std::vector<LinkInfoType>;
using LaneInfoType         = holo::map::LaneInfo;
using LaneInfosType        = std::vector<LaneInfoType>;
using LaneMarkInfoType     = holo::map::LaneMarkInfo;
using MapPointsType        = std::vector<Point3Type>;
using MapServiceClientBase = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase;
using MapLinkId            = MapServiceClientBase::LinkId;
using MapLaneId            = MapServiceClientBase::LaneId;
using MapMatchingResult    = MapServiceClientBase::MatchingResult;

// Semantic related types
using ObjectId      = holo::uint32_t;
using CommonObject  = holo::map::CommonObject;
using ObjectPoints  = std::vector<Point3Type>;
using ObjectsResult = std::unordered_map<ObjectId, ObjectPoints>;

/**
 * @brief definition of input odometry info
 *
 */
struct OdometryInfo
{
    std::vector<OdometryType> dr_odometry;          ///< constructed by the lastest optimized odometry and dr odometry
    std::vector<OdometryType> init_lane_odometry;   ///< constructed by init lane odometry
    std::vector<Scalar>       dr_travel_length;     ///< constructed by dr travel length
    std::vector<OdometryType> lane_match_odometry;  ///< constructed by lane match odometry
};

// /**
//  * @brief definition of raw measurement
//  *
//  */
// struct RawMeasurement
// {
//     std::vector<CameraLaneBoundariesType> detect_frames;  ///< constructed by detected frames
// };

// /**
//  * @brief Define the ego-lane estimator result including link_id, lane_id and timestamp
//  *
//  */
// struct EgoLaneResult
// {
//     uint64_t  link_id   = 0u;
//     uint64_t  lane_id   = 0u;
//     Timestamp timestamp = Timestamp();
// };

// /**
//  * @brief Define the measurement of lane preprocessor
//  *
//  */
// struct LaneMeasurement
// {
//     uint64_t     link_id   = 0u;             ///< link id
//     uint64_t     lane_id   = 0u;             ///< lane id
//     Timestamp    timestamp = Timestamp();    ///< current timestamp
//     OdometryType prior_odometry;             ///< prior odometry, which can be low precision or high precision
//     bool_t       is_high_precision = false;  ///< is prior odometry high precision or not
// };

/**
 * @brief Define the ego-lane information including link_id, lane_id and timestamp
 *
 */
struct EgoLaneInformation
{
    MapLinkId link_id = 0u;
    MapLaneId lane_id = 0u;

    /**
     * @brief Enable default constructor.
     */
    EgoLaneInformation() = default;

    /**
     * @brief Constructor
     *
     * @param[in] _link_id The link ID
     * @param[in] _lane_id The lane ID
     */
    EgoLaneInformation(MapLinkId const& _link_id, MapLaneId const& _lane_id) : link_id(_link_id), lane_id(_lane_id)
    {
    }
};

/**
 * @brief define struct to store raw measurements for lane preprocessor
 * @todo @zhangyelin please help to impl this struct
 *
 */
struct LaneRawMeasurement
{
    CameraLaneBoundariesType camera_lane_boundaries;
    EgoLaneInformation   ego_lane_information;
    AdvancedNavstateType current_navstate;
};  // LaneRawMeasurements

using LaneRawMeasurements = std::vector<LaneRawMeasurement>;

/**
 * @brief definition of map query config parameter
 *
 */
struct MapQueryConfig
{
    Scalar   range;      ///< distance of searching range
    Scalar   fov;        ///< fov of searching range
    Rot3Type rot;        ///< rotation constrain of searching range
    int32_t  direction;  ///< direction of searching range
};

/**
 * @brief definition of lane boundary id
 *
 */
enum class LaneBoundaryId : int8_t
{
    LEFT_3RD_LINE  = -5,
    LEFT_2ND_LINE  = -3,
    LEFT_1ST_LINE  = -1,
    RIGHT_1ST_LINE = 1,
    RIGHT_2ND_LINE = 3,
    RIGHT_3RD_LINE = 5,
    INVALID        = 15,
};

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_PROCESSOR_TYPES_H_
