/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tight_fusion_vision_obstacle_track.h
 * @brief This header file defines tight fusion vision obstacle track.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-22"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_RIGHT_FUSION_VISION_OBSTACLE_TRACK_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_RIGHT_FUSION_VISION_OBSTACLE_TRACK_H_

#include <holo/perception/obstacle_fusion/fusion_strategy/strategy.h>
#include <holo/perception/utils/sensor_obstacle_track.h>

#include <array>
#include <holo/perception/utils/impl/camera_group.hpp>
#include <unordered_map>

namespace holo
{
namespace perception
{
/**
 * @brief vision obstacle track
 *
 */
class TightFusionVisionObstacleTrack : public VisionObstacleTrack
{
public:
    using Scalar         = float32_t;
    using Base2          = SensorObstacleTrack<obstacle::ObstacleVisionT<Scalar>, TrackType::VISION>;
    using Scalar4        = std::array<Scalar, 4U>;
    using Box2dMap       = std::unordered_map<uint32_t, Scalar4>;
    using CameraGroupPtr = std::shared_ptr<CameraGroup>;

public:
    /**
     * @brief Construct a new Tight Fusion Vision Obstacle Track object
     *
     * @param obs vision obstacle pointer
     * @param max_history max history
     */
    TightFusionVisionObstacleTrack(ObstaclePtr const obs, uint32_t max_history = 15U) : Base2(obs, max_history)
    {
        start_time_ = obs->GetTimestamp();
    }

    /**
     * @brief Set the Camera Group object
     *
     * @param camera_group camera group pointer
     */
    void SetCameraGroup(CameraGroupPtr const camera_group)
    {
        camera_group_ = camera_group;
    }

    /**
     * @brief predict current 3d state and project to image
     *
     * @param current_timestamp
     */
    void Predict(Timestamp const& current_timestamp) override
    {
        Base2::Predict(current_timestamp);
        ProjectToCamera();
    }

    /**
     * @brief Get the Predicted Box 2d Map object
     *
     * @return Box2dMap const& camera id -> box2d map
     */
    Box2dMap const& GetPredictedBox2dMap() const
    {
        return predicted_box2d_map_;
    }

    /**
     * @brief project box3d to camera
     *
     */
    void ProjectToCamera()
    {
        predicted_box2d_map_.clear();
        auto obs    = GetHistory().back();
        auto x      = obs->GetPosition().GetX();
        auto y      = obs->GetPosition().GetY();
        auto z      = obs->GetPosition().GetZ();
        auto length = obs->GetObstacleBBox3D().GetDepth();
        auto width  = obs->GetObstacleBBox3D().GetWidth();
        auto height = obs->GetObstacleBBox3D().GetHeight();
        auto yaw    = obs->GetObstacleBBox3D().GetPose().GetRotation().YPR()[0U];
        for (auto sid : camera_group_->SID)
        {
            Scalar4 ret;
            if (GetSensorId() == sid)
            {
                ret[0U] = obs->GetImageBBox2D().GetPose().GetX();
                ret[1U] = obs->GetImageBBox2D().GetPose().GetY();
                ret[2U] = ret[0U] + obs->GetImageBBox2D().GetWidth();
                ret[3U] = ret[1U] + obs->GetImageBBox2D().GetHeight();

                predicted_box2d_map_[sid] = ret;
            }
            else
            {
                if (camera_group_->ProjectToCamera(x, y, z, length, width, height, yaw, sid, ret))
                {
                    if (sid == camera_group_->SID[0])
                    {
                        ret[0U] = std::max<Scalar>(0.0f, std::min<Scalar>(1920.0f, ret[0U]));
                        ret[1U] = std::max<Scalar>(0.0f, std::min<Scalar>(1080.0f, ret[1U]));
                        ret[2U] = std::max<Scalar>(0.0f, std::min<Scalar>(1920.0f, ret[2U]));
                        ret[3U] = std::max<Scalar>(0.0f, std::min<Scalar>(1080.0f, ret[3U]));
                    }
                    else
                    {
                        ret[0U] = std::max<Scalar>(0.0f, std::min<Scalar>(1280.0f, ret[0U]));
                        ret[1U] = std::max<Scalar>(0.0f, std::min<Scalar>(800.0f, ret[1U]));
                        ret[2U] = std::max<Scalar>(0.0f, std::min<Scalar>(1280.0f, ret[2U]));
                        ret[3U] = std::max<Scalar>(0.0f, std::min<Scalar>(800.0f, ret[3U]));
                    }

                    predicted_box2d_map_[sid] = ret;
                }
            }
        }
    }

    Scalar GetAgeTime()
    {
        auto dt = (obstacle_property_.t - start_time_).ToSec();
        return static_cast<Scalar>(dt);
    }

private:
    void setObstacleProperty(ObstaclePtr const obs) override
    {
        TrackBase::obstacle_property_.t                    = obs->GetTimestamp();
        TrackBase::obstacle_property_.x                    = obs->GetPosition().GetX();
        TrackBase::obstacle_property_.y                    = obs->GetPosition().GetY();
        TrackBase::obstacle_property_.z                    = obs->GetPosition().GetZ();
        TrackBase::obstacle_property_.vx                   = obs->GetRelativeVelocity()[0U];
        TrackBase::obstacle_property_.vy                   = obs->GetRelativeVelocity()[1U];
        TrackBase::obstacle_property_.ax                   = obs->GetAcceleration()[0U];
        TrackBase::obstacle_property_.ay                   = obs->GetAcceleration()[1U];
        TrackBase::obstacle_property_.length               = obs->GetObstacleBBox3D().GetDepth();
        TrackBase::obstacle_property_.width                = obs->GetObstacleBBox3D().GetWidth();
        TrackBase::obstacle_property_.height               = obs->GetObstacleBBox3D().GetHeight();
        TrackBase::obstacle_property_.yaw                  = obs->GetObstacleBBox3D().GetPose().GetRotation().YPR()[0U];
        TrackBase::obstacle_property_.cls                  = obs->GetClassification();
        TrackBase::obstacle_property_.obstacle_exist_score = obs->GetObstacleExistScore();
    }

private:
    Box2dMap          predicted_box2d_map_;  // camera sensor id -> box2d
    CameraGroupPtr    camera_group_;
    common::Timestamp start_time_;
};

}  // namespace perception
}  // namespace holo

#endif
