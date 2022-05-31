/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_gridmap_parking_pipeline.h
 * @brief This header file defines .
 * @author zhangyuqi(zhangyuqi1@holomatic.com)
 * @date "2022-02-21"
 */

#include <holo/perception/obstacle_fusion/obstacle_gridmap/obstacle_gridmap_parking.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{

/**
 * @brief Class for grid map generation
 *
 */
class ObstacleGridMapParkingPipline
{
public:
    using Scalar    = holo::float32_t;
    using Bool      = bool_t;
    using Timestamp = holo::common::Timestamp;

    using Obstacle = holo::obstacle::ObstacleGeneralT<float32_t>;
    using ObstacleGeneralPtrList =
        holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>;
    using ObstacleGeneralPtrListMessage = std::shared_ptr<ObstacleGeneralPtrList>;

    using Point2f          = holo::geometry::Point2f;
    using Point3f          = holo::geometry::Point3f;
    using Freespace        = holo::common::AutoFreespace<Point3f>;
    using FreeSpaceMessage = std::shared_ptr<Freespace>;

    using OdometryType    = holo::common::Odometryf;
    using OdometryMessage = std::shared_ptr<OdometryType>;

    using GridMapCell = holo::common::GridMapCell;
    using GridMap     = holo::common::GridMap<GridMapCell, 100, 250>;

    using PublishCallback = std::function<void(GridMap const&)>;

    /**
     * @brief Construct a new Obstacle Grid Map Parking Pipline object
     *
     */
    ObstacleGridMapParkingPipline();

    /**
     * @brief Destroy the Obstacle Grid Map Parking Pipline object
     *
     */
    ~ObstacleGridMapParkingPipline();

    /**
     * @brief Set the Params object
     *
     * @param config_file Path to configuration file
     */
    void SetParams();

    /**
     * @brief Set the Timestamp object
     *
     * @param timestamp
     */
    void SetTimestamp(Timestamp const& timestamp);

    /**
     * @brief Update the main function of grid map
     *
     * @param odo_msg odometyr
     * @param free_msg freespace
     * @param obs_msg obstacle list
     * @return Bool
     */
    Bool UpdateMap(ObstacleGeneralPtrList const& obs_msg);

    /**
     * @brief Get the Map object
     *
     * @return GridMap Return to grid map
     */
    inline GridMap& GetMap()
    {
        return master_layer_;
    }

private:
    HideGridMap hide_layer_;
    GridMap     master_layer_;  // master gridmap layer
};
}  // namespace perception
}  // namespace holo
