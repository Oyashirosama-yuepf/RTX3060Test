/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tight_fusion_radar_obstacle_track.h
 * @brief This header file defines tight fusion radar obstacle track.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-22"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_RADAR_OBSTACLE_TRACK_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_RADAR_OBSTACLE_TRACK_H_

#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/fusion/track.h>
#include <holo/perception/obstacle_fusion/fusion_strategy/strategy.h>
#include <holo/perception/utils/obstacle_property.h>
#include <holo/perception/utils/sensor_obstacle_track.h>

#include <array>
#include <deque>
#include <holo/perception/utils/impl/camera_group.hpp>
#include <unordered_map>

namespace holo
{
namespace perception
{
/**
 * @brief radar obstacle track
 *
 */
class TightFusionUssObstacleTrack
  : public Track<SensorMeasurementKey, holo::obstacle::ObstacleUssT<float32_t>, SensorMeasurementKeyHash>
{
public:
    using Scalar = float32_t;
    using Base   = Track<SensorMeasurementKey, holo::obstacle::ObstacleUssT<Scalar>, SensorMeasurementKeyHash>;
    // using Base2          = SensorObstacleTrack<holo::obstacle::ObstacleUssT<Scalar>, TrackType::USS>;
    using Scalar4        = std::array<Scalar, 4U>;
    using Box2dMap       = std::unordered_map<uint32_t, Scalar4>;
    using CameraGroupPtr = std::shared_ptr<CameraGroup>;

    using ObstacleType   = holo::obstacle::ObstacleUssT<Scalar>;
    using ObstaclePtr    = std::shared_ptr<ObstacleType>;
    using HistoryType    = std::deque<ObstaclePtr>;
    using Timestamp      = holo::common::details::Timestamp;
    using SensorId       = TrackBase::SensorId;
    using PropertyType   = TrackBase::ObstaclePropertyType;
    using MeasurementMap = typename Base::MeasurementMap;

public:
    /**
     * @brief Construct a new Tight Fusion USS Obstacle Track object
     *
     * @param obs uss obstacle pointer
     * @param max_history max history
     */
    TightFusionUssObstacleTrack(ObstaclePtr const obs, uint32_t max_history)
      : Track<SensorMeasurementKey, ObstacleType, SensorMeasurementKeyHash>(TrackType::USS)
    {
        timestamp_              = obs->GetTimestamp();
        max_history_            = max_history;
        lost_count_             = 0U;
        age_                    = 1U;
        TrackBase::sensor_id_   = obs->GetSensorId();
        TrackBase::obstacle_id_ = obs->GetObstacleId();
        setObstacleProperty(obs);
        history_.push_back(obs);
    }

    /**
     * @brief predict obstacle position/velocity at current timestamp
     *
     * @param current_timestamp current timestamp
     */
    void Predict(Timestamp const& current_timestamp)
    {
        ++lost_count_;
        auto last_obs                   = history_.back();
        TrackBase::obstacle_property_.x = last_obs->GetPosition().GetX();
        TrackBase::obstacle_property_.y = last_obs->GetPosition().GetY();
        timestamp_                      = current_timestamp;

        ProjectToCamera();
    }

    /**
     * @brief store the new incoming data
     * @details the measurement have one obstacle at most,
     * because it tracks a individual sensor obstacle
     *
     * @param measurement_map measurement
     */
    void Update(MeasurementMap const& measurement_map)
    {
        if (measurement_map.size() > 0U)
        {
            lost_count_ = 0U;
            ++age_;
            auto obs = measurement_map.begin()->second;
            setObstacleProperty(obs);
            history_.push_back(obs);
            if (history_.size() > max_history_)
            {
                history_.pop_front();
            }
        }
    }

    /**
     * @brief Get the Sensor Id object
     *
     * @return SensorId
     */
    SensorId GetSensorId() const
    {
        return TrackBase::sensor_id_;
    }

    /**
     * @brief Get the Obstacle Id object
     *
     * @return uint32_t
     */
    uint32_t GetObstacleId() const
    {
        return TrackBase::obstacle_id_;
    }

    /**
     * @brief Get the Property object
     *
     * @return PropertyType const&
     */
    PropertyType const& GetProperty() const
    {
        return TrackBase::obstacle_property_;
    }

    /**
     * @brief Get the History object
     *
     * @return HistoryType const&
     */
    HistoryType const& GetHistory() const
    {
        return history_;
    }

    uint32_t GetLostCount() const
    {
        return lost_count_;
    }

    /**
     * @brief get age of sensor obstacle
     *
     * @return uint32_t
     */
    uint32_t GetAge() const
    {
        return age_;
    }

    /**
     * @brief Set the Camera Group object
     *
     * @param camera_group camera group
     */
    void SetCameraGroup(CameraGroupPtr const camera_group)
    {
        camera_group_ = camera_group;
    }

    /**
     * @brief Get the Predicted Box 2d Map object
     *
     * @return Box2dMap const& camera sensor id -> box2d map
     */
    Box2dMap const& GetPredictedBox2dMap() const
    {
        return predicted_box2d_map_;
    }

    /**
     * @brief project to camera
     *
     */
    void ProjectToCamera()
    {
        predicted_box2d_map_.clear();
        auto obs    = GetHistory().back();
        auto shape  = Strategy::GetPriorShape(obs->GetClassification());
        auto length = shape[0U];
        auto width  = shape[1U];
        auto height = shape[2U];
        auto x      = obs->GetPosition().GetX();
        auto y      = obs->GetPosition().GetY();
        auto z      = height * 0.5f;
        for (auto sid : camera_group_->SID)
        {
            Scalar4 ret;
            if (camera_group_->ProjectToCamera(x, y, z, length, width, height, 0.0f, sid, ret))
            {
                ret[0U]                   = std::max<Scalar>(0.0f, std::min<Scalar>(1920.0f, ret[0U]));
                ret[1U]                   = std::max<Scalar>(0.0f, std::min<Scalar>(1080.0f, ret[1U]));
                ret[2U]                   = std::max<Scalar>(0.0f, std::min<Scalar>(1920.0f, ret[2U]));
                ret[3U]                   = std::max<Scalar>(0.0f, std::min<Scalar>(1080.0f, ret[3U]));
                predicted_box2d_map_[sid] = ret;
            }
        }
    }

private:
    void setObstacleProperty(ObstaclePtr const obs)
    {
        auto shape                                         = Strategy::GetPriorShape(obs->GetClassification());
        TrackBase::obstacle_property_.t                    = obs->GetTimestamp();
        TrackBase::obstacle_property_.x                    = obs->GetPosition().GetX();
        TrackBase::obstacle_property_.y                    = obs->GetPosition().GetY();
        TrackBase::obstacle_property_.z                    = obs->GetPosition().GetZ();
        TrackBase::obstacle_property_.length               = shape[0U];
        TrackBase::obstacle_property_.width                = shape[1U];
        TrackBase::obstacle_property_.height               = shape[2U];
        TrackBase::obstacle_property_.cls                  = obs->GetClassification();
        TrackBase::obstacle_property_.obstacle_exist_score = obs->GetObstacleExistScore();
    }

private:
    Box2dMap       predicted_box2d_map_;  // camera sensor id -> box2d
    CameraGroupPtr camera_group_;

    Timestamp   timestamp_;
    HistoryType history_;
    uint32_t    max_history_;
    uint32_t    lost_count_;
    uint32_t    age_;
};

}  // namespace perception
}  // namespace holo

#endif