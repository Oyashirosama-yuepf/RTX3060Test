/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tight_fusion_obstacle_filter.h
 * @brief This header file defines obstacle filter.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-17"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_OBSTACLE_FILTER_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_OBSTACLE_FILTER_H_

#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/obstacle_fusion/tight_fusion_obstacle_id_tracker.h>
#include <holo/perception/obstacle_fusion/tight_fusion_parameter.h>
#include <holo/perception/obstacle_fusion/tight_fusion_uss_id_tracker.h>

#include <holo/perception/utils/impl/camera_group.hpp>

namespace holo
{
namespace perception
{
/**
 * @brief obstacle filter
 *
 */
class TightFusionObstacleFilter
{
public:
    using Scalar    = float32_t;
    using SensorId  = common::SensorId;
    using Timestamp = common::Timestamp;

    using UssObsPtr     = std::shared_ptr<obstacle::ObstacleUssT<Scalar>>;
    using UssMessage    = std::shared_ptr<obstacle::ObstacleUssPtrList>;
    using UssMessageMap = std::unordered_map<uint32_t, UssMessage>;

    using VisionObsPtr     = std::shared_ptr<obstacle::ObstacleVisionT<Scalar>>;
    using VisionMessage    = std::shared_ptr<obstacle::ObstacleVisionPtrList>;
    using VisionMessageMap = std::unordered_map<uint32_t, VisionMessage>;

    using Vector3f       = numerics::Vector3f;
    using MeasurementMap = std::unordered_map<SensorMeasurementKey, TrackBasePtr, SensorMeasurementKeyHash>;

    using UssMeasurementMap    = std::unordered_map<SensorMeasurementKey, UssObsPtr, SensorMeasurementKeyHash>;
    using VisionMeasurementMap = std::unordered_map<SensorMeasurementKey, VisionObsPtr, SensorMeasurementKeyHash>;
    using CameraGroupPtr       = std::shared_ptr<CameraGroup>;

    using UssObsFilterRule    = std::function<bool_t(UssObsPtr const)>;
    using VisionObsFilterRule = std::function<bool_t(VisionObsPtr const)>;

public:
    /**
     * @brief Set the Camera Group object
     *
     * @param camera_group camera group pointer
     */
    void SetCameraGroup(CameraGroupPtr const camera_group);

    /**
     * @brief do filter
     *
     * @param current_timestamp current timestamp
     * @param vel_body body linear velocity
     * @param angular_velocity body yaw velocity
     * @param uss_msg_map radar message map
     * @param vision_msg_map vision message map
     */
    void Compute(Timestamp const& current_timestamp, Vector3f const& vel_body, Scalar angular_velocity,
                 UssMessageMap const& uss_msg_map, VisionMessageMap const& vision_msg_map);

    /**
     * @brief Get the Measurement Map object
     *
     * @return MeasurementMap const& measurement map
     */
    MeasurementMap const& GetMeasurementMap()
    {
        return measurement_map_;
    }

private:
    /**
     * @brief get uss measurement map from uss message map
     *
     * @param uss_msg_map uss message map
     * @param uss_measurement_map uss measurement map
     */
    void getUssMeasurementMap(UssMessageMap const& uss_msg_map, UssMeasurementMap& uss_measurement_map);

    /**
     * @brief get vision measurement map from visioin message map
     *
     * @param vision_msg_map vision message map
     * @param vision_measurement_map vision measurement map
     */
    void getVisionMeasurementMap(VisionMessageMap const& vision_msg_map, VisionMeasurementMap& vision_measurement_map);

    /**
     * @brief construct uss measurement map according to vision message
     *
     * @param msg uss message
     * @param uss_measurement_map uss measurement map
     * @param isValid function judge whether obstacle is valid or not
     */
    void addMeasurement(UssMessage const& msg, UssMeasurementMap& uss_measurement_map,
                        std::function<bool_t(UssObsPtr const)> const& isValid);

    /**
     * @brief construct vision measurement map according to vision message
     *
     * @param msg vision message
     * @param vision_measurement_map vision measurment map
     * @param isValid function judge whether obstacle is valid or not
     */
    void addMeasurement(VisionMessage const& msg, VisionMeasurementMap& vision_measurement_map,
                        std::function<bool_t(VisionObsPtr const)> const& isValid);

    /**
     * @brief determine whether uss obstacle is valid
     *
     * @param obs uss obstacle
     * @return bool_t true if uss obstacle is valid else false
     */
    bool_t isValidUssObs(UssObsPtr const obs);

    /**
     * @brief is valid vision obs
     *
     * @param obs obstacle pointer
     * @return bool_t true if its valid
     */
    bool_t isValidVisionObs(VisionObsPtr const obs);

    /**
     * @brief append uss obstacle fileter rules
     *
     */
    void appendUssObsFilterRules();

    /**
     * @brief append vision obstacle filter rules
     *
     */
    void appendVisionObsFilterRules();

private:
    MeasurementMap measurement_map_;

    TightFusionUssObstacleTracker      uss_obs_id_tracker_;
    TightFusionVisionObstacleIdTracker vision_obs_id_tracker_;
    CameraGroupPtr                     camera_group_;

    std::list<UssObsFilterRule>    uss_obs_filter_rule_list_;
    std::list<VisionObsFilterRule> vision_obs_filter_rule_list_;

    Timestamp current_timestamp_;
    Vector3f  vel_body_;
    Scalar    angular_velocity_ = 0.0f;
};

}  // namespace perception
}  // namespace holo

#endif