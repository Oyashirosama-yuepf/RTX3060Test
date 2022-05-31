/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 10, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_CAR_ROAD_STATE_H_
#define _HOLO_PLANNING_CAR_ROAD_STATE_H_

#include <holo/common/chassis_state.h>
#include <holo/common/odometry.h>
#include <holo/common/road_frame2.h>
#include <holo/common/vehicle_body_state.h>
#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/details/polynomial_curve.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/prediction/intentions.h>

#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{
using CurveType    = holo::geometry::CurvePolynomial<holo::geometry::Point2T<holo::float64_t>, 64U, 3U>;
using BoundaryType = holo::common::LaneBoundary<CurveType>;
using LaneType     = holo::common::Lane<CurveType>;
// local road frame from fused lane boundary
using RoadFrameType = holo::common::RoadFrame<CurveType>;
using RoadFramePtr  = std::shared_ptr<RoadFrameType>;
using GraphNodeType = RoadFrameType::GraphNode;

// global road frame2 from map advice
using GlobalRoadFrameType = holo::common::RoadFrame<holo::geometry::CurvePolynomial<geometry::Point3d, 0U, 3U>, 256U>;
using GlobalRoadFramePtr  = std::shared_ptr<GlobalRoadFrameType>;
using GlobalGraphNodeType = GlobalRoadFrameType::GraphNode;

/**
 * @brief      Class for car road state. This class keeps all the information
 *             used by the following path caculation from gateway.
 */
struct CarRoadState
{
    std::shared_ptr<common::details::ChassisState>    chassis_state;
    std::shared_ptr<common::VehicleBodyState>         vehicle_body_state;
    std::shared_ptr<obstacle::ObstacleGeneralPtrList> obstacle_list;
    std::shared_ptr<prediction::Intentions>           intention_list;
    std::shared_ptr<holo::common::Odometryd>          odometry;
    RoadFramePtr                                      road_frame2;
    GlobalRoadFramePtr                                topological_graph;
};

}  // namespace planning
}  // namespace holo
#endif