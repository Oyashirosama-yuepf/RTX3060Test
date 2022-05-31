/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file commonstructtype.h
 * @brief the header of planning of parking
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-03-10
 */
#ifndef _COMMON_STRUCT_TYPE_H_
#define _COMMON_STRUCT_TYPE_H_

#include <holo/common/chassis_state.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/pose2.h>
#include <holo/planning/common/curve_point.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Eigen/Core>
#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <vector>

#define DIVIDENUM 720
#define LENGTHOFPATH 150
#define EPSLON 1e-6
#define US2S 1e-6
#define US2MS 1e-3
#define MS2S 1e-3
#define DEFAULTMAX std::numeric_limits<float64_t>::max()
#define ANG2RAD 0.01745
#define RAD2ANG 57.2958
#define TURNINGRADIUS 4.68  ///< for WM : 2.703/tan(0.523)

using Point2d = holo::geometry::Point2d;
typedef Point2d WorldPoint;

namespace holo
{
namespace planning
{
/**
 * @brief enumerate drive environment.
 */
enum DriveEnvironment
{
    DRIVE_NORMAL,
    LOOKFORSPACE,
    OUTER_FORWARD,
    OUTER_BACKWARD,
    INTER_FORWARD,
    INTER_BACKWARD,
    LAST_FORWARD_ADJUST,
    LAST_BACKWARD_ADJUST,
    FINISH_PARKING,
    PARKING_FAILED_FOR_OBSTACLE,
    PARKING_FAILED_FOR_REPLAN_LIMITS,
    PULLING_OUT,
    PULLING_OUT_COMPLETE,
    PULLING_OUT_FAILED
};

/**
 * @brief enumerate parkinglot type.
 */
enum ParkingSlotType
{
    INVALID_SPACE,
    LEFT_PARALLEL,
    LEFT_VERTICAL,
    LEFT_OBLIQUE,
    RIGHT_PARALLEL,
    RIGHT_VERTICAL,
    RIGHT_OBLIQUE
};

struct PointXY
{
    float64_t x;
    float64_t y;
    float64_t theta;
    int8_t    type;  ///< e.g. 0：default 1：human 2：vehicle 3：curb 4：others
    float64_t curvature;
    float64_t length;  ///< length from start point to current point
    PointXY()
    {
        x         = 0.0f;
        y         = 0.0f;
        theta     = 0.0f;
        type      = 0;
        curvature = 0.0001;
        length    = 0.0f;
    }

    PointXY(float64_t x_, float64_t y_)
    {
        x         = x_;
        y         = y_;
        theta     = 0.0f;
        type      = 0;
        curvature = 0.0001;
        length    = 0.0f;
    }

    PointXY operator+(PointXY const& p) const
    {
        return PointXY(x + p.x, y + p.y);
    }

    PointXY operator-(PointXY const& p) const
    {
        return PointXY(x - p.x, y - p.y);
    }

    PointXY operator*(float64_t ratio) const
    {
        return PointXY(x * ratio, y * ratio);
    }

    PointXY operator/(float64_t ratio) const
    {
        if (0 == ratio)
        {
            throw "divided by zero!";
        }
        return PointXY(x / ratio, y / ratio);
    }

    friend std::ostream& operator<<(std::ostream& os, PointXY const& p)
    {
        return os << "x = " << p.x << " y = " << p.y << std::endl;
    }

    bool_t operator<(PointXY const& p)
    {
        if (std::abs(x - p.x) > 1e-7)
        {
            return x < p.x;
        }
        else
        {
            return y < p.y;
        }
    }

    float64_t dis()
    {
        float64_t dis = std::hypot(x, y);
        return dis;
    }

    bool_t operator==(const PointXY& p) const
    {
        return ((x - p.x) > EPSLON) - ((x - p.x) < -EPSLON) == 0 && ((y - p.y) > EPSLON) - ((y - p.y) < -EPSLON) == 0;
    }
};

struct SlotData
{
    uint32_t   slotid;
    uint32_t   direction;
    uint32_t   type;
    uint32_t   available_state;
    float64_t  angle;
    float64_t  slottheta;
    uint32_t   lastpoint_availablestate;
    uint32_t   groundpin_availablestate;
    WorldPoint slotpoint0;
    WorldPoint slotpoint1;
    WorldPoint slotpoint2;
    WorldPoint slotpoint3;
    WorldPoint groundpin_point0;
    WorldPoint groundpin_point1;

    SlotData()
    {
        slotid          = 0;  ///< ID
        direction       = 0;  ///< 0:left 1:right 2:front 3: back
        type            = 0;  ///< 0:parallel 1:vertical 2:oblique
        available_state = 0;  ///< 1:available 0:unavailable
        angle           = 0;  ///< TODO:To be confirmed： from x axis anticlockwise is positive？ range ：-PI~PI？
        slottheta       = 0;  ///< TODO:To be confirmed： 车位置信度？
        lastpoint_availablestate = 0;  ///< 1:available 0:unavailable
        groundpin_availablestate = 0;  ///< 1:available 0:unavailable
    }
};

struct RectCorner
{
    PointXY  topleft;
    PointXY  topright;
    PointXY  btmleft;
    PointXY  btmright;
    int16_t  source;
    uint32_t type;

    RectCorner()
    {
        source = 0;  ///< reserved e.g. 0 :from detection 1:from map
        type   = 0;  ///< reserved
    }

    void Clear()
    {
        memset(&topleft, 0, sizeof(topleft));
        memset(&topright, 0, sizeof(topright));
        memset(&btmleft, 0, sizeof(btmleft));
        memset(&btmright, 0, sizeof(btmright));
        source = 0;
        type   = 0;
    }
};

struct ParkinglotData
{
    int64_t                 timemsec;  ///< millisecond
    uint32_t                slotnum;
    uint32_t                reserved;
    SlotData                data[16];
    std::vector<RectCorner> value;
    RectCorner              current_rectcorner;
    ParkinglotData()
    {
        timemsec = 0;  ///< unit:ms
        slotnum  = 0;  ///< maximum 16
        reserved = 0;
        value.resize(1);
    }
};

struct Designedlot
{
    float64_t lot_x;
    float64_t lot_y;
    float64_t lot_theta;
    int8_t    lot_type;
    float64_t lot_angle;
    uint8_t   lot_direction;
    float64_t lot_width;
    float64_t lot_length;
    float64_t lot_lambda;

    Designedlot()
    {
        lot_x         = 0.0f;
        lot_y         = 0.0f;
        lot_theta     = 0.0f;
        lot_type      = 0;
        lot_direction = 0;
        lot_angle     = 0.0f;
        lot_width     = 0.0f;
        lot_length    = 0.0f;
        lot_lambda    = 0.0f;
    }
};

struct SingleParkingLot
{
    RectCorner  single_lot;
    Designedlot single_obj;
};

#define DIVIDENUM 720

struct FreeSpaceData
{
    int16_t              counter;
    int64_t              timestamp;
    uint32_t             segment_num;
    std::vector<PointXY> value;

    FreeSpaceData()
    {
        counter     = 0;
        timestamp   = 0;
        segment_num = 720;
    }
};

struct PathData
{
    std::vector<CurvePoint>            path;
    float64_t                          f_obstacle_speed;
    common::ChassisState::GearPosition gear;
    DriveEnvironment                   drive_environment;
    bool_t                             stopinend;
    PathData()
    {
        f_obstacle_speed  = 0;
        gear              = common::ChassisState::GearPosition::UNKNOWN;
        drive_environment = DRIVE_NORMAL;
        stopinend         = false;
    }
};

struct OperateState
{
    bool_t parkinglot_valid;
    bool_t ready_to_pullout;
    bool_t in_pullingout_process;
    bool_t pullout_failed;
    bool_t pullout_adjust;
    bool_t pullout_complete;

    bool_t ready_to_reverse;
    bool_t ready_to_park;
    bool_t finish_parking;
    bool_t parking_failed;

    OperateState()
    {
        parkinglot_valid      = false;
        ready_to_pullout      = false;
        in_pullingout_process = false;
        pullout_failed        = false;
        pullout_adjust        = false;
        pullout_complete      = false;

        ready_to_reverse = false;
        ready_to_park    = false;
        finish_parking   = false;
        parking_failed   = false;
    }
};

struct ExecuteTrajectory
{
    int16_t   point_size;
    float64_t steering_angle;
    float64_t speed_limit;
    float64_t desired_speed;
    float64_t desired_acc;
    float64_t trajectory_length;
    float64_t x[100];
    float64_t y[100];
    float64_t theta[100];
    float64_t kappa[100];
    float64_t roadfollow_error;
    int8_t    drive_environment;
    int8_t    gear;

    ExecuteTrajectory()
    {
        point_size        = 0;
        steering_angle    = 0;
        speed_limit       = 0;
        desired_speed     = 0;
        desired_acc       = 0;
        trajectory_length = 0;
        roadfollow_error  = 0;
        drive_environment = 1;
        gear              = 0;
        memset(&x, 0, sizeof(x));
        memset(&y, 0, sizeof(y));
        memset(&theta, 0, sizeof(theta));
        memset(&kappa, 0, sizeof(kappa));
    }
};

struct PullingoutLotData
{
    int8_t    status;
    float64_t init_angle;
    float64_t lot_angle;
    int8_t    direction;
    int8_t    lot_type;

    PullingoutLotData()
    {
        status     = 0;
        init_angle = 0.0f;
        lot_angle  = 0.0f;
        direction  = 0;
        lot_type   = 0;
    }
    void Clear()
    {
        status     = 0;
        init_angle = 0.0f;
        lot_angle  = 0.0f;
        direction  = 0;
        lot_type   = 0;
    }
};

struct ReckonData
{
    float64_t reck_dx;
    float64_t reck_dy;
    float64_t reck_dtheta;
    float64_t reck_y;
    float64_t reck_x;
    float64_t reck_theta;

    float64_t sv_adjust_theta;
    float64_t sv_adjust_x;
    float64_t sv_adjust_y;
    float64_t sv_tracking_counter;
    float64_t reckon_adjust_ratio;

    int64_t current_timestamp;
    int64_t last_timestamp;

    ReckonData()
    {
        reck_dx     = 0.0f;
        reck_dy     = 0.0f;
        reck_dtheta = 0.0f;
        reck_y      = 0.0f;
        reck_x      = 0.0f;
        reck_theta  = 0.0f;

        sv_adjust_theta     = 0.0f;
        sv_adjust_x         = 0.0f;
        sv_adjust_y         = 0.0f;
        sv_tracking_counter = 0.0f;
        reckon_adjust_ratio = 0.0f;

        current_timestamp = 0;
        last_timestamp    = 0;
    }
};
}  // namespace planning
}  // namespace holo
#endif
