/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date 2017-08-29
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_PLAN_ROUTE_H_
#define _HOLO_PLANNING_PLAN_ROUTE_H_

#include <vector>

#include <holo/common/light_signal_request.h>
#include <holo/common/odometry.h>
#include <holo/common/path.h>
#include <holo/core/types.h>
#include <holo/geometry/pose2.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/prediction/intentions.h>

#include <holo/planning/common/curve_point.h>
#include <holo/planning/common/published_path.h>
#include <holo/planning/math/curve/curve_1d.h>

namespace holo
{
namespace planning
{
/**
 * @brief      ObstacleInfo is the information of obstacles for planning
 */
class ObstacleInfo
{
public:
    /**
     * @brief      Constructor
     *
     * @param[in]  ob    The origin obstacle.
     */
    ObstacleInfo(std::shared_ptr<obstacle::ObstacleGeneralT<float32_t>> ob);

    /**
     * @brief      Destroys the object.
     */
    ~ObstacleInfo();

    /**
     * @brief      Gets the max s value corner point.
     *
     * @return     The corner point position.
     */
    const float64_t& MaxS() const;

    /**
     * @brief      Gets the max s value corner point.
     *
     * @return     The corner point position.
     */
    float64_t& MaxS();

    /**
     * @brief      Set the max s value corner point.
     *
     * @return     none
     */
    void SetMaxS(float64_t x);

    /**
     * @brief      Gets the min s value corner point.
     *
     * @return     The corner point position.
     */
    const float64_t& MinS() const;

    /**
     * @brief      Gets the min s value corner point.
     *
     * @return     The corner point position.
     */
    float64_t& MinS();

    /**
     * @brief      Set the min s value corner point.
     *
     * @return     none
     */
    void SetMinS(float64_t x);

    /**
     * @brief      Gets the max l value corner point.
     *
     * @return     The corner point position.
     */
    const float64_t& MaxL() const;

    /**
     * @brief      Gets the max l value corner point.
     *
     * @return     The corner point position.
     */
    float64_t& MaxL();

    /**
     * @brief      Set the max l value corner point.
     *
     * @return     none
     */
    void SetMaxL(float64_t x);

    /**
     * @brief      Gets the min l value corner point.
     *
     * @return     The corner point position.
     */
    const float64_t& MinL() const;

    /**
     * @brief      Gets the min l value corner point.
     *
     * @return     The corner point position.
     */
    float64_t& MinL();

    /**
     * @brief      Set the min l value corner point.
     *
     * @return     none
     */
    void SetMinL(float64_t x);

    /**
     * @brief      Gets the s value of velocity which is in frenet coordinate.
     *
     * @return     The vel_frenet_s_.
     */
    const float64_t& VelFrenetS() const;

    /**
     * @brief      Gets the s value of velocity which is in frenet coordinate.
     *
     * @return     The vel_frenet_s_.
     */
    float64_t& VelFrenetS();

    /**
     * @brief      Set the s value of velocity which is in frenet coordinate.
     *
     * @return     none
     */
    void SetVelFrenetS(float64_t x);

    /**
     * @brief      Gets the s value of accerleration which is in frenet coordinate.
     *
     * @return     The acc_frenet_s_.
     */
    const float64_t& AccFrenetS() const;

    /**
     * @brief      Gets the s value of accerleration which is in frenet coordinate.
     *
     * @return     The acc_frenet_s_.
     */
    float64_t& AccFrenetS();

    /**
     * @brief      Set the s value of accerleration which is in frenet coordinate.
     *
     * @return     none
     */
    void SetAccFrenetS(float64_t x);

    /**
     * @brief      Gets the s value of absolute velocity which is in frenet coordinate.
     *
     * @return     The vel_frenet_s_.
     */
    float64_t AbsVelFrenetS() const;

    /**
     * @brief      Gets the s value of absolute accerleration which is in frenet coordinate.
     *
     * @return     The vel_frenet_s_.
     */
    float64_t AbsAccFrenetS() const;

    /**
     * @brief      Gets the origin obstacle.
     */
    std::shared_ptr<obstacle::ObstacleGeneralT<float32_t>> GetObstacle();

    /**
     * @brief      Gets the origin obstacle.
     */
    const std::shared_ptr<obstacle::ObstacleGeneralT<float32_t>> GetObstacle() const;

    /**
     * @brief get the const reference frenet s state of obstacle
     *
     * @return the const reference frenet s state
     */
    std::array<float64_t, 3> const& GetFrenetS() const;

    /**
     * @brief get the frenet s state of obstacle
     *
     * @return the frenet s state
     */
    std::array<float64_t, 3>& GetFrenetS();

    /**
     * @brief set the frenet s state of obstacle
     */
    void SetFrenetS(std::array<float64_t, 3> const& state);

    /**
     * @brief get the const reference frenet l state of obstacle
     *
     * @return the const reference frenet l state
     */
    std::array<float64_t, 3> const& GetFrenetL() const;

    /**
     * @brief get the frenet l state of obstacle
     *
     * @return the frenet l state
     */
    std::array<float64_t, 3>& GetFrenetL();

    /**
     * @brief set the frenet l state of obstacle
     */
    void SetFrenetL(std::array<float64_t, 3> const& state);

protected:
    /**
     * @brief The origin obstacle.
     */
    std::shared_ptr<obstacle::ObstacleGeneralT<float32_t>> obstacle_;

    /**
     * @brief The maximum of s value
     */
    float64_t max_s_;

    /**
     * @brief The minimum of s value
     */
    float64_t min_s_;

    /**
     * @brief The maximum of l value
     */
    float64_t max_l_;

    /**
     * @brief The minimum of l value
     */
    float64_t min_l_;

    /**
     * @brief The s value of velocity which is in frenet coordinate
     */
    float64_t vel_frenet_s_;

    /**
     * @brief The s value of accerleration which is in frenet coordinate
     */
    float64_t acc_frenet_s_;

    /**
     * @brief The s state in frenet frame
     */
    std::array<float64_t, 3> frenet_s_state_;

    /**
     * @brief The l state in frenet frame
     */
    std::array<float64_t, 3> frenet_l_state_;
};

typedef std::shared_ptr<ObstacleInfo> ObstacleInfoPtr;

enum EgoCarIntention : uint32_t
{
    NORMAL = 0,
    PASS   = 1,
    YIELD  = 2,
    INTENTION_COUNT,
};

class ObstacleIntentionInfo
{
public:
    /**
     * @brief      Cut in obstacle classified index according to relative area to ego
     *             car.
     */
    enum Cut_In_Area : uint32_t
    {
        Cut_In_Left  = 0,
        Cut_In_Right = 1,
        Cut_In_Area_Count,
    };

public:
    ObstacleIntentionInfo(std::shared_ptr<holo::prediction::Intention> intention);

    const std::shared_ptr<holo::prediction::Intention> GetIntention() const;

    std::shared_ptr<holo::prediction::Intention> GetIntention();

    const std::shared_ptr<holo::planning::ObstacleInfo> GetObstacleInfo() const;

    std::shared_ptr<holo::planning::ObstacleInfo> GetObstacleInfo();

    void SetObstacleInfo(std::shared_ptr<holo::planning::ObstacleInfo> obstacleinfo);

    const float64_t& GetCutInDist() const;

    float64_t& GetCutInDist();

    void SetCutInDist(float64_t cutin_dist);

    const float64_t& GetCutInTime() const;

    float64_t& GetCutInTime();

    void SetCutInTime(float64_t cutin_time);

    const uint32_t& GetCutInArea() const;

    uint32_t& GetCutInArea();

    void SetCutInArea(uint32_t cutin_area);

protected:
    std::shared_ptr<holo::prediction::Intention> intention_;

    std::shared_ptr<holo::planning::ObstacleInfo> obstacle_info_;

    float64_t cutin_dist_;

    float64_t cutin_time_;

    uint32_t cutin_area_;
};
// DecisionAPI is the official api between decision and planning which provides boundary and deterministic info.
struct DecisionInfo
{
    // target point velocity API
    std::array<float64_t, 2> velocity_boundary;
    std::array<float64_t, 2> distance_boundary;
    // planning time period API
    std::array<float64_t, 2> time_period;
    // planning headway time API
    float64_t headway_time;
    // flag for pass or yield: true if pass, false otherwise
    bool_t pass_flag;
    // most significant cut-in object ptr
    std::shared_ptr<holo::planning::ObstacleIntentionInfo> cut_in_obs;
};

struct DescritilizedCurve
{
    enum class Type : uint8_t
    {
        UNKNOWN             = 0,
        DOT_LANE_BOUNDARY   = 1,
        SOLID_LANE_BOUNDARY = 2,
        REFERENCE_PATH      = 3,
    };

    std::vector<CurvePoint> curve;
    uint8_t                 confidence;
    Type                    type;
    float64_t               length;
};

struct PlanRoute
{
    typedef std::vector<std::shared_ptr<ObstacleInfo>> ObstacleList;

    typedef std::vector<std::shared_ptr<ObstacleIntentionInfo>> ObstacleIntentionList;
    /**
     * @brief      Obstacle classified index according to relative area to ego
     *             car.
     */
    enum Obstacle_Area
    {
        Obstacle_Area_LeftFront   = 0,
        Obstacle_Area_LeftCenter  = 1,
        Obstacle_Area_LeftBack    = 2,
        Obstacle_Area_CenterFront = 3,
        Obstacle_Area_CenterBack  = 4,
        Obstacle_Area_RightFront  = 5,
        Obstacle_Area_RightCenter = 6,
        Obstacle_Area_RightBack   = 7,
        Obstacle_Area_Ignore      = 8,
        Obstacle_Area_Count,
    };

    float32_t accelerate;
    float32_t max_velocity;
    float32_t next_distance;

    /**
     * @brief       Lane Boundaries
     *
     * @details     Lane Boundaries calculated from action_pilot
     */
    float64_t y1;
    float64_t y2;
    float64_t y3;
    float64_t y4;

    DecisionInfo cut_in_info;

    geometry::Pose2d   pose_car;
    LightSignalRequest light_signal_request;
    // lon curve
    std::shared_ptr<math::Curve1d> lon_curve;
    // lat curve
    std::shared_ptr<math::Curve1d> lat_curve;

    std::shared_ptr<DescritilizedCurve> left_line;
    std::shared_ptr<DescritilizedCurve> right_line;
    std::shared_ptr<DescritilizedCurve> left_2nd_line;
    std::shared_ptr<DescritilizedCurve> right_2nd_line;

    std::vector<std::array<float64_t, 3>> max_velocity_smooth_array;

    holo::common::Path      path;
    holo::common::Path      body_path;
    holo::common::Path      ref_path;
    std::vector<CurvePoint> reference_path;
    // tjp path
    std::shared_ptr<holo::common::Path> tjp_path;
    // advice path
    std::vector<geometry::Point2f> advice_path_points;
    // published path
    PublishedPath published_path_;

    // leading obstacle
    ObstacleInfoPtr leading_obs;

    // obstacle list array
    ObstacleList obstacles[Obstacle_Area_Count];
    // obstacle list aggregate
    ObstacleList obstacles_aggregate;
    // obstacle lattice planner considered
    ObstacleList obstacles_lattice_consider;
    // obstacle intention list
    ObstacleIntentionList obstacles_intention;

    uint32_t main_state;

    // first is tag, second is obs id
    std::vector<std::pair<uint32_t, uint32_t>> obs_id_list;

    PlanRoute() : accelerate(0.0)
    {
    }

    PlanRoute(std::shared_ptr<holo::common::Odometryd> odometry_state)
      : accelerate(0.0)
      , pose_car(odometry_state->GetPose().GetRotation().RPY()[2],
                 geometry::Point2d(odometry_state->GetPose().GetX(), odometry_state->GetPose().GetY()))
    {
    }
};

void ClearObsInfoInPlanRoute(PlanRoute& route);

}  // namespace planning
}  // namespace holo

#endif
