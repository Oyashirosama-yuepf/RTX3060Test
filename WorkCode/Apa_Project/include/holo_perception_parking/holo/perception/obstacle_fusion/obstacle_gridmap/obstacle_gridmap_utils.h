/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_gridmap_parking_utils.h
 * @brief This header file defines .
 * @author zhangyuqi(zhangyuqi1@holomatic.com)
 * @date "2022-02-21"
 */

#pragma once
#include <holo/common/classification.h>
#include <holo/common/freespace.h>
#include <holo/common/grid_map.h>
#include <holo/common/odometry.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/geometry/point2.h>
#include <holo/obstacle/obstacle_list.h>

#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace holo
{
namespace perception
{
#define PI 3.1415926f
#define MAPFRONT 20.0F
#define MAPBACK -5.0F
#define MAPLEFT 5.0F
#define MAPRIGHT -5.0F

/**
 * @brief hide grid map parameters
 *
 */
class Params
{
public:
    Params(uint32_t in_height = 250, uint32_t in_width = 100, float32_t in_resolution = 0.10f)
      : height(in_height), width(in_width), resolution(in_resolution){};
    ~Params();
    Params& operator=(Params const& other);

public:
    uint32_t  height;
    uint32_t  width;
    float32_t resolution;
};

/**
 * @brief Point in map 2D
 *
 */
struct MapPoint
{
public:
    MapPoint(float32_t x = 0.0f, float32_t y = 0.0f) : x(x), y(y){};

    MapPoint& operator=(MapPoint const& point);

    bool_t operator==(MapPoint const& point);

    inline bool_t IsNull()
    {
        return x == 0.0f && y == 0.0f;
    }

public:
    float32_t x;
    float32_t y;
};

/**
 * @brief Grid Point in map
 *
 */
struct MapPointGrid
{
public:
    MapPointGrid(uint32_t x = 0, uint32_t y = 0) : x(x), y(y){};

    MapPointGrid& operator=(MapPointGrid const& point);

    bool_t operator==(MapPointGrid const& point);

    inline bool_t IsNull()
    {
        return x == 0 && y == 0;
    }

public:
    uint32_t x;
    uint32_t y;
};

/**
 * @brief Turn grid point to order
 *
 * @param index order
 * @param width width cell number
 * @return MapPointGrid
 */
MapPointGrid OrderToGridCoordinate(uint32_t index, uint32_t width);

/**
 * @brief Turn order to grid point
 *
 * @param point grid point
 * @param width width cell number
 * @return uint32_t
 */
inline uint32_t GridCoordinateToOrder(MapPointGrid point, uint32_t width)
{
    return (point.x - 1) * width + point.y - 1;
}

/**
 * @brief Turn Grid point to point
 *
 * @param point Grid point
 * @param width width cell number
 * @param height height cell number
 * @param resolution size of cell [m]
 * @return MapPoint point 2d
 */
MapPoint GridToVehicle(MapPointGrid const& point, uint32_t width, uint32_t height, float32_t resolution);

/**
 * @brief Turn point to Grid point
 *
 * @param point point 2d
 * @param width width cell number
 * @param height height cell number
 * @param resolution size of cell [m]
 * @return MapPointGrid grid point
 */
MapPointGrid VehicleToGrid(MapPoint const& point, uint32_t width, uint32_t height, float32_t resolution);

}  // namespace perception
}  // namespace holo
