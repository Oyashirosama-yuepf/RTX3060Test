/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_obstacle_filter.h
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-08-17"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_OBSTACLE_FILTER_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_OBSTACLE_FILTER_H_

#include <glog/logging.h>
#include <holo/perception/obstacle_fusion/parking_general_obstacle_id_tracker.h>
#include <holo/perception/obstacle_fusion/parking_kd_tree.h>
#include <holo/perception/obstacle_fusion/parking_obstacle_fuser.h>
#include <holo/perception/obstacle_fusion/parking_obstacle_input_preprocess.h>
#include <holo/perception/obstacle_fusion/parking_uss_obstacle_tracking_pipeline.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/sensor_obstacle_track.h>
#include <holo/utils/yaml.h>

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
 * @brief get measurements from sensor obstacle list
 *
 */
class ParkingObstacleFilter
{
public:
    using Timestamp = holo::common::Timestamp;
    using Scalar    = float32_t;
    using Vector3f  = holo::numerics::Vector3f;
    using ObstacleGeneralPtrList =
        holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>;
    using ObstacleVisionPtrList = holo::obstacle::ObstacleVisionPtrList;
    using ObstacleUssPtrList    = holo::obstacle::ObstacleUssPtrList;
    using Zone                  = holo::geometry::Box3f;
    using Corners               = std::vector<holo::geometry::Point3f>;
    using KeyPoints3D           = holo::container::Vector<holo::vision::KeyPoint3f, 8UL>;
    using GeneralObsType        = holo::obstacle::ObstacleGeneralT<Scalar>;
    using VisionObsType         = holo::obstacle::ObstacleVisionT<Scalar>;
    using UssObsType            = holo::obstacle::ObstacleUssT<Scalar>;

    using GeneralObsPtr = std::shared_ptr<GeneralObsType>;
    using VisionObsPtr  = std::shared_ptr<VisionObsType>;
    using UssObsPtr     = std::shared_ptr<UssObsType>;

    using GeneralMessage = std::shared_ptr<ObstacleGeneralPtrList>;
    using VisionMessage  = std::shared_ptr<ObstacleVisionPtrList>;
    using UssMessage     = std::shared_ptr<ObstacleUssPtrList>;

    using GeneralMessageMap = std::unordered_map<uint32_t, GeneralMessage>;
    using VisionMessageMap  = std::unordered_map<uint32_t, VisionMessage>;
    using UssMessageMap     = std::unordered_map<uint32_t, UssMessage>;

    using MeasurementMap        = std::unordered_map<SensorMeasurementKey, TrackBasePtr, SensorMeasurementKeyHash>;
    using GeneralMeasurementMap = std::unordered_map<SensorMeasurementKey, GeneralObsPtr, SensorMeasurementKeyHash>;
    using VisionMeasurementMap  = std::unordered_map<SensorMeasurementKey, VisionObsPtr, SensorMeasurementKeyHash>;
    using UssMeasurementMap     = std::unordered_map<SensorMeasurementKey, UssObsPtr, SensorMeasurementKeyHash>;

    using UssKdTreePtr = std::shared_ptr<KdTree>;
    using UssVector    = std::vector<holo::geometry::Point2f>;

    using OdometryType    = holo::common::Odometryf;
    using OdometryMessage = std::shared_ptr<OdometryType>;
    using OdometryCache   = std::deque<OdometryMessage>;

    /**
     * @brief Setup configurationfile
     *
     * @param config_file configuration file address
     */
    void Setup(holo::yaml::Node const& node);

    /**
     * @brief using id tracking pipeline to update obstacle tracks
     * @details filter the measurement_map_ by associate measurement and track using <sensor_id, obstacle_id> as key
     *
     * @param current_timestamp current timestamp
     * @param vel_body velocity info from odeometry
     * @param general_msg_map general message map
     * @param uss_msg_map uss message map
     * @param vision_msg_map vision message map from front camera
     */
    void Compute(Timestamp const& current_timestamp, Vector3f const& vel_body, GeneralMessageMap const& general_msg_map,
                 UssMessageMap const& uss_msg_map, VisionMessageMap const& vision_msg_map,
                 OdometryCache const& odo_cache);

    /**
     * @brief return measurement_map_
     *
     * @return private member measurement_map_
     */
    MeasurementMap const& GetMeasurementMap()
    {
        return measurement_map_;
    }

private:
    /**
     * @brief read vision measurements from vision message
     *
     * @param vision_msg_map vision meassage map
     * @param vision_measurement_map current measurement map read from vision message
     */
    void getVisionMeasurementMap(Timestamp const& timestamp, VisionMessageMap const& vision_msg_map,
                                 VisionMeasurementMap& vision_measurement_map);

    /**
     * @brief read uss measurements from uss message
     *
     * @param uss_msg_map uss meassage map
     * @param uss_measurement_map current measurement map read from uss message
     */
    void getUssMeasurementMap(Timestamp const& timestamp, UssMessageMap const& uss_msg_map,
                              UssMeasurementMap& uss_measurement_map);

    void getUssKdTree(Timestamp const& timestamp, UssMessageMap const& uss_msg_map, UssVector& uss_measurements,
                      UssKdTreePtr& uss_kd_tree);

    /**
     * @brief preprocess measurements from vision message
     *
     * @param vision_obstacle pointer to vision obstacle
     */
    bool_t validateVisionObstacle(VisionObsPtr& vision_obstacle);

    /**
     * @brief preprocess measurements from uss message
     *
     * @param uss_obstacle pointer to uss obstacle
     */
    bool_t validateUssObstacle(UssObsPtr const& uss_obstacle);

    void correctSensorId(VisionObsPtr& vision_obs, uint32_t const& sid);

    bool_t checkKptsPosition(Zone const& zone, Corners const& kpts);

    bool_t checkKptsVisiable(bool_t is_srv, KeyPoints3D const& kpts);

private:
    Timestamp                          current_timestamp_;
    Vector3f                           vel_body_;
    MeasurementMap                     measurement_map_;
    ParkingVisionObstacleIdTracker     vision_obs_id_tracker_;
    ParkingUssObstacleTrackingPipeline uss_obs_tracker_;
    ParkingObstacleInputPreprocess     input_preprocess_;
    ParkingObstacleFuser               input_fuser_;
    Scalar                             uss_dist_thres_lhs_;
    Scalar                             uss_dist_thres_rhs_;
    Scalar                             uss_exist_prob_trhes_;
    Scalar                             front_;
    Scalar                             rear_;
    Scalar                             left_;
    Scalar                             right_;
    Scalar                             front_srv_;
    Scalar                             rear_srv_;
    Scalar                             left_srv_;
    Scalar                             right_srv_;
    Scalar                             abnormal_obstacle_distance_;
    Scalar                             abnormal_obstacle_srv_distance_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
