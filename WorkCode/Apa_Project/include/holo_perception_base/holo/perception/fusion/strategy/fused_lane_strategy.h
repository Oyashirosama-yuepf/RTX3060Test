/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fused_lane_strategy.h
 * @brief This header file defines fusion strategy using fused lane.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-10-15"
 */

#ifndef HOLO_PERCEPTION_FUSION_STRATEGY_FUSED_LANE_STRATEGY_H_
#define HOLO_PERCEPTION_FUSION_STRATEGY_FUSED_LANE_STRATEGY_H_

#include <holo/common/road_frame2.h>
#include <holo/geometry/curve.h>
#include <holo/log/hololog.h>
#include <holo/perception/utils/obstacle_property.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup fusion
 *
 * @{
 */

class FusedLaneStrategy
{
public:
    using Scalar                  = float32_t;
    using Point2d                 = holo::geometry::details::Point2T<float64_t>;
    using LocalMapFusionCurveType = holo::geometry::CurvePolynomial<Point2d, 64U, 3U>;
    using BoundaryTypeFused       = holo::common::LaneBoundary<LocalMapFusionCurveType>;
    using FusedBoundaryPtr        = std::shared_ptr<BoundaryTypeFused>;
    using LaneTypeFused           = holo::common::Lane<LocalMapFusionCurveType>;
    using LocalMapFusionType      = holo::common::RoadFrame<LocalMapFusionCurveType, 128U>;
    using RoadFramePtr            = std::shared_ptr<LocalMapFusionType>;

    /**
     * @brief Set the Side Noise Params
     *
     * @param min_x min x
     * @param max_x max x
     */
    void SetSideNoiseParams(Scalar min_x, Scalar max_x);

    /**
     * @brief Set the Lateral Adjust Params
     *
     * @param min_x min x
     * @param max_x max x
     * @param max_abs_y max |y|
     * @param max_abs_vy max |vy|
     * @param left_max_abs_diff left max |diff|
     * @param right_max_abs_diff right max |diff|
     * @param left_shift left shift
     * @param right_shift right shift
     */
    void SetLateralAdjustParams(Scalar min_x, Scalar max_x, Scalar max_abs_y, Scalar max_abs_vy,
                                Scalar left_max_abs_diff, Scalar right_max_abs_diff, Scalar left_shift,
                                Scalar right_shift);

    /**
     * @brief Set the Current Fused Lane
     *
     * @param fused_lane fused lane message
     */
    void SetCurrentFusedLane(RoadFramePtr const fused_lane);

    /**
     * @brief determine if the obstacle is a side noise (often comes from a corner radar)
     * @details need SetSideNoiseParams before call this method
     *
     * @param x obstacle's x coordinate in body frame
     * @param y obstacle's y coordinate in body frame
     * @param width obstacle_width * 0.5
     * @return bool_t true if it is a noise
     */
    bool_t IsSideNoise(Scalar x, Scalar y, Scalar half_width);

    /**
     * @brief determine if the obstacle is out of road
     *
     * @param x obstacle's x coordinate in body frame
     * @param y obstacle's y coordinate in body frame
     * @return bool_t true if it is out of road
     */
    bool_t IsOutOfRoad(Scalar x, Scalar y);

    /**
     * @brief adjust obstacle's y coordinate of adjacent lane
     * @details need SetLateralAdjustParams before call this method
     *
     * @param props obstacle property
     * @return Scalar y after adjust
     */
    Scalar AdjustOutputObstacleYIfNecessary(ObstacleProperty<Scalar> const& props);

    /**
     * @brief find yaw of obstacle according to current lane
     *
     * @param x obstacle's x coordinate in body frame
     * @return Scalar yaw, default is zero
     */
    Scalar FindYawFromFusedLane(Scalar x);

private:
    /**
     * @brief find left and right road boundary's Y coordinate in body frame
     *
     */
    void findLeftAndRightBoundaryY();

    /**
     * @brief determine if the position(x, y) is out of road
     *
     * @param fused_lane fused lane
     * @param x x coordinate
     * @param y y coordinate
     * @return bool_t true if it is out of road
     */
    bool_t isOutOfRoad(RoadFramePtr const fused_lane, Scalar x, Scalar y);

    /**
     * @brief determine if the position(x, y) is out of left road boundary
     *
     * @param boundary left road boundary
     * @param x x coordinate
     * @param y y coordinate
     * @return bool_t true if it is out of left road boundary
     */
    bool_t leftBoundaryCheck(FusedBoundaryPtr boundary, Scalar x, Scalar y);

    /**
     * @brief determine if the position(x, y) is out of right road boundary
     *
     * @param boundary right road boundary
     * @param x x coordinate
     * @param y y cooridnate
     * @return bool_t true if it is out of road boundary
     */
    bool_t rightBoundaryCheck(FusedBoundaryPtr boundary, Scalar x, Scalar y);

    /**
     * @brief Get the Current Lane Boundary Y
     *
     * @param fused_lane fused lane
     * @param left_boundary_y left boundary y
     * @param right_boundary_y right boundary y
     * @param has_left_boundary true if has left boundary
     * @param has_right_boundary true if has right boundary
     */
    void getCurrentLaneBoundaryY(RoadFramePtr const fused_lane, Scalar& left_boundary_y, Scalar& right_boundary_y,
                                 bool_t& has_left_boundary, bool_t& has_right_boundary);

    /**
     * @brief find yaw from fused lane
     *
     * @param x obstacle's x coordinate in body frame
     * @param fused_lane fused lane
     * @return Scalar yaw [radius]
     */
    Scalar findYawFromFusedLane(Scalar x, RoadFramePtr fused_lane);

private:
    /* state variables */
    RoadFramePtr fused_lane_                      = nullptr;
    Scalar       outermost_left_lane_boundary_y_  = 1e8f;
    Scalar       outermost_right_lane_boundary_y_ = -1e8f;

    /* hyper parameters */
    Scalar side_noise_min_x_                  = -3.0f;
    Scalar side_noise_max_x_                  = 8.0f;
    Scalar lateral_adjust_min_x_              = -3.0f;
    Scalar lateral_adjust_max_x_              = 8.0f;
    Scalar lateral_adjust_max_abs_y_          = 4.0f;
    Scalar lateral_adjust_max_abs_vy_         = 2.0f;
    Scalar lateral_adjust_left_max_abs_diff_  = 1.1f;
    Scalar lateral_adjust_right_max_abs_diff_ = 1.1f;
    Scalar lateral_adjust_left_shift_         = 0.2f;
    Scalar lateral_adjust_right_shift_        = 0.2f;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
