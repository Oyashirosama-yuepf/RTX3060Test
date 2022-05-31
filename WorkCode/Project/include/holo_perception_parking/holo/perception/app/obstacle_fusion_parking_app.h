/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_fusion_parking_app.h
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-08-03"
 */

#ifndef _HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_APP_H_
#define _HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_APP_H_

#include <holo/common/odometry.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/obstacle_fusion/obstacle_freespace/parking_obstacle_freespace_fusion_pipeline.h>
#include <holo/perception/obstacle_fusion/parking_obstacle_fusion_pipeline.h>
#include <holo/perception/utils/worker.h>
//#include <holo/perception/obstacle_fusion/obstacle_gridmap/obstacle_gridmap_parking_pipline.h>
//#include <holo/perception/obstacle_fusion/tight_fusion_pipeline.h>

#include <deque>
#include <mutex>
#include <unordered_map>

namespace holo
{
namespace perception
{
/**
 * @addtogroup fusion
 *
 * @{
 */

/**
 * @brief obstacle fusion interface for parking
 * @details defined fusion application controled derived from Worker

 */
class ObstacleFusionParkingApp : public Worker
{
public:
    using Scalar       = holo::float32_t;
    using OdometryType = holo::common::Odometryf;
    using ObstacleGeneralPtrList =
        holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>;
    using ObstacleUssPtrList    = holo::obstacle::ObstacleUssPtrList;
    using ObstacleVisionPtrList = holo::obstacle::ObstacleVisionPtrList;
    using OdometryMessage       = std::shared_ptr<OdometryType>;
    using OdometryCache         = std::deque<OdometryMessage>;
    using GeneralMessage        = std::shared_ptr<ObstacleGeneralPtrList>;
    using GeneralMessageMap     = std::unordered_map<uint32_t, GeneralMessage>;
    using GeneralObsCache       = std::deque<GeneralMessage>;
    using GeneralObsCacheMap    = std::unordered_map<uint32_t, GeneralObsCache>;
    using UssMessage            = std::shared_ptr<obstacle::ObstacleUssPtrList>;
    using UssMessageMap         = std::unordered_map<uint32_t, UssMessage>;
    using UssObsCache           = std::deque<UssMessage>;
    using UssObsCacheMap        = std::unordered_map<uint32_t, UssObsCache>;
    using VisionMessage         = std::shared_ptr<obstacle::ObstacleVisionPtrList>;
    using VisionMessageMap      = std::unordered_map<uint32_t, VisionMessage>;
    using VisionObsCache        = std::deque<VisionMessage>;
    using VisionObsCacheMap     = std::unordered_map<uint32_t, VisionObsCache>;
    using Freespace             = holo::common::AutoFreespace<holo::Point3f>;
    using FreespaceMessage      = std::shared_ptr<Freespace>;
    using FreespaceCache        = std::deque<FreespaceMessage>;
    // using GridMapCell           = holo::common::GridMapCell;
    // using GridMap               = holo::common::GridMap<GridMapCell, 100U, 250U>;

    using AppStatusCallback = std::function<void(holo::uint32_t const&)>;
    // using PublishCallbackGridMap   = std::function<void(GridMap const&)>;
    using PublishCallbackObstacle  = std::function<void(ObstacleGeneralPtrList const&)>;
    using PublishCallbackFreespace = std::function<void(Freespace const&)>;
    /**
     * @brief Construct a fusion app
     * @details initialize using default cache size, and frame_id
     *
     * @param hz default worker frequency
     */
    ObstacleFusionParkingApp(float32_t hz = 10.0f);

    /**
     * @brief Setup configurationfile
     *
     * @param config_file configuration file address
     * @param use_gridmap whether use grid map
     */
    void Setup(std::string const& config_file, bool_t use_gridmap);

    // /**
    //  * @brief Setup Publisher Callback function of gridmap
    //  *
    //  * @param callback callback object
    //  */
    // void SetPublishCallback(PublishCallbackGridMap const& callback);

    /**
     * @brief Setup Publisher Callback function of obstacle list
     *
     * @param callback callback object
     */
    void SetPublishCallback(PublishCallbackObstacle const& callback);

    /**
     * @brief Setup Publisher Callback function
     * @brief Setup Publisher Callback function of freespace
     *
     * @param callback callback object
     */
    void SetPublishCallback(PublishCallbackFreespace const& callback);

    /**
     * @brief Setup App Status Callback function
     *
     * @param callback callback object
     */
    void SetAppStatusCallback(AppStatusCallback const& callback);

    /**
     * @brief Worker state setter
     * @details control the worker state such as Init(), Suspend(),...
     *
     * @param worker_state_id worker state index for control
     */
    void SetWorkerState(uint8_t const& worker_state_id);

    /**
     * @brief store odometry message in cache
     *
     * @param msg odometry message
     */
    void CacheOdometry(OdometryType const& msg);

    /**
     * @brief store freespace message in cache
     *
     * @param msg freespace message
     */
    void CacheFreespace(Freespace const& msg);

    /**
     * @brief store general obstacle message in cache
     *
     * @param id general obstacle topic id
     * @param msg general obstacle message
     */
    void CacheGeneralObsList(uint32_t id, ObstacleGeneralPtrList const& msg);

    /**
     * @brief store uss obstacle message in cache
     *
     * @param id uss obstacle topic id
     * @param msg uss obstacle message
     */
    void CacheUssObsList(uint32_t id, ObstacleUssPtrList const& msg);

    /**
     * @brief store vision obstacle message in cache
     *
     * @param id vision obstacle topic id
     * @param msg vision obstacle message
     */
    void CacheVisionObsList(uint32_t id, ObstacleVisionPtrList const& msg);

    /**
     * @brief work execution function
     * @details get obstacle messages ready and feed them into fusion pipeline
     */
    bool_t DoWork() override;

    /**
     * @brief work execution function
     * @details get obstacle messages ready and feed them into fusion pipeline
     */
    uint32_t GetAppStates()
    {
        return fusion_app_status_;
    }

private:
    /**
     * @brief store obstacle messages in cache
     * @details template function to deal with different sensor types
     *
     * @tparam ObsList Obstacle list type for different sensors
     * @tparam Cache cache container for different sensors
     * @tparam CacheMap cache map for different sensor's cache
     *
     * @param id obstacle topic id
     * @param msg obstacle message from sensor
     * @param cache_map  cache map
     */
    template <typename ObsList, typename Cache, typename CacheMap>
    void cacheObsList(uint32_t id, ObsList const& msg, CacheMap& cache_map);

    /**
     * @brief get message from cache
     *
     * @param odo_msg odometry message
     * @param general_msg_map general message map
     * @param uss_msg_map uss message map
     */
    void getMessage(OdometryMessage& odo_msg, FreespaceMessage& free_msg, GeneralMessageMap& general_msg_map,
                    UssMessageMap& uss_msg_map, VisionMessageMap& vision_msg_map, OdometryCache& odo_cache);

private:
    std::mutex         mutex_;
    size_t             frame_id_;
    size_t             max_obstacle_cache_size_;
    size_t             max_odometry_cache_size_;
    size_t             max_freespace_cache_size_;
    Scalar             hz_;
    bool_t             use_gridmap_;
    OdometryCache      odometry_cache_;
    FreespaceCache     freespace_cache_;
    GeneralObsCacheMap general_obs_cache_map_;
    UssObsCacheMap     uss_obs_cache_map_;
    VisionObsCacheMap  vision_obs_cache_map_;

    PublishCallbackObstacle  fused_obs_publish_callback_;
    PublishCallbackFreespace freespace_publish_callback_;
    // PublishCallbackGridMap   gridmap_publish_callback_;

    AppStatusCallback app_status_publish_callback_;
    uint32_t          fusion_app_status_;
    uint32_t          freespace_obstacle_;

    ParkingObstacleFusionPipeline    obstacle_fusion_pipeline_;
    ObstacleFreespaceParkingPipeline obstacle_freespace_pipeline_;
    // ObstacleGridMapParkingPipline    obstacle_gridmap_pipeline_;
    // TightFusionPipeline              tight_obstacle_fusion_pipeline_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
