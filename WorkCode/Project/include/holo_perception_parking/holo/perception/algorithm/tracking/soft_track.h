/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file soft_track.h
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-09-05"
 */
#ifndef HOLO_PERCEPTION_TRACKING_SOFT_TRACK_H_
#define HOLO_PERCEPTION_TRACKING_SOFT_TRACK_H_

#include <functional>
#include <unordered_map>
#include <utility>

#include <holo/geometry/polyfit2.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>

namespace holo
{
namespace perception
{
const static size_t SOFT_PIPELINE_CAMERA_NUMBER = 3U;
const static size_t SOFT_PIPELINE_RADAR_NUMBER  = 5U;

/**
 * @brief Soft Measure
 *
 */
class SoftMeasure
{
public:
    using Scalar           = float32_t;
    using RadarObsPtr      = std::shared_ptr<ObstacleRadarT<Scalar>>;
    using RadarMessage     = std::shared_ptr<ObstacleRadarPtrList>;
    using VisionObsPtr     = std::shared_ptr<ObstacleVisionT<Scalar>>;
    using VisionMessage    = std::shared_ptr<ObstacleVisionPtrList>;
    using RadarSensorIdMap = std::array<SensorId, SOFT_PIPELINE_RADAR_NUMBER>;

    /**
     * @brief Construct a new Soft Measure object
     *
     */
    SoftMeasure()
      : x_(0.0f)
      , y_(0.0f)
      , vx_(0.0f)
      , vy_(0.0f)
      , ax_(0.0f)
      , ay_(0.0f)
      , length_(1.0f)
      , width_(1.0f)
      , yaw_(0.0f)
      , classification_(Classification(Classification::MainType::VEHICLE, Classification::SubType::CAR))
      , vision_obs_(nullptr)
      , smart_camera_obs_(nullptr)
      , weight_(1.0f)
      , matched_(false)
      , has_front_radar_obs_(false)
    {
    }

    /**
     * @brief Add radar obstacle to measure
     *
     * @param radar_obs radar obstacle
     */
    void AddRadarObstacle(RadarObsPtr const radar_obs)
    {
        radar_obs_list_.push_back(radar_obs);
    }

    /**
     * @brief Add vision obstacle to measure
     *
     * @param vision_obs vision obstacle
     */
    void AddVisionObstacle(VisionObsPtr const vision_obs)
    {
        vision_obs_ = vision_obs;
    }

    /**
     * @brief Add smart camera obstacle to measure
     *
     * @param smart_camera_obs  smart camera obstacle
     */
    void AddSmartCameraObstacle(VisionObsPtr const smart_camera_obs)
    {
        smart_camera_obs_ = smart_camera_obs;
    }

    /**
     * @brief Set the measure to be matched
     *
     */
    void SetMatched()
    {
        matched_ = true;
    }

    /**
     * @brief Set the Weight of measure
     *
     * @param weight weight of measure
     */
    void SetWeight(Scalar const weight)
    {
        weight_ = weight;
    }

    /**
     * @brief set position x
     *
     * @param x position x
     */
    void SetX(Scalar const x)
    {
        x_ = x;
    }

    /**
     * @brief set position y
     *
     * @param y position y
     */
    void SetY(Scalar const y)
    {
        y_ = y;
    }

    /**
     * @brief Get the Vision Obs object
     *
     * @return VisionObsPtr vision obs
     */
    VisionObsPtr GetVisionObs()
    {
        return vision_obs_;
    }

    /**
     * @brief Get the Smart Camera Obs object
     *
     * @return VisionObsPtr  smart camera obs
     */
    VisionObsPtr GetSmartCameraObs()
    {
        return smart_camera_obs_;
    }

    /**
     * @brief Get the measure weight
     *
     * @return Scalar measure's weight
     */
    Scalar GetWeight()
    {
        return weight_;
    }

    /**
     * @brief Get if the measure is matched
     *
     * @return bool_t true if matched
     */
    bool_t IsMatched()
    {
        return matched_;
    }

    /**
     * @brief Get the Radar Obs List Size
     *
     * @return size_t size of radar obs list
     */
    size_t GetRadarObsListSize()
    {
        return radar_obs_list_.size();
    }

    /**
     * @brief Compute properties of the measure(eg, x, y, vx, vy )
     *
     * @param sid_map radar sensor id map
     * @return bool_t true if the measure is valid
     */
    bool_t ComputeProps(RadarSensorIdMap const& sid_map);

    /**
     * @brief Get position x
     *
     * @return Scalar position x
     */
    Scalar GetX()
    {
        return x_;
    }

    /**
     * @brief Get position y
     *
     * @return Scalar position y
     */
    Scalar GetY()
    {
        return y_;
    }

    /**
     * @brief Get the velocity x
     *
     * @return Scalar velocity x
     */
    Scalar GetVx()
    {
        return vx_;
    }

    /**
     * @brief Get the velocity y
     *
     * @return Scalar velocity y
     */
    Scalar GetVy()
    {
        return vy_;
    }

    /**
     * @brief Get the accleration x
     *
     * @return Scalar acceleration x
     */
    Scalar GetAx()
    {
        return ax_;
    }
    /**
     * @brief Get the acceleration y
     *
     * @return Scalar acceleration y
     */
    Scalar GetAy()
    {
        return ay_;
    }

    /**
     * @brief Get the Length
     *
     * @return Scalar length
     */
    Scalar GetLength()
    {
        return length_;
    }

    /**
     * @brief Get the Width
     *
     * @return Scalar width
     */
    Scalar GetWidth()
    {
        return width_;
    }

    /**
     * @brief Get the Yaw
     *
     * @return Scalar yaw
     */
    Scalar GetYaw()
    {
        return yaw_;
    }

    /**
     * @brief Get the Classification object
     *
     * @return Classification classification
     */
    Classification GetClassification()
    {
        return classification_;
    }

    /**
     * @brief if the measure has a front radar obs
     *
     * @return bool_t true if it has one
     */
    bool_t HasFrontRadarObs()
    {
        return has_front_radar_obs_;
    }

    /**
     * @brief Get the Radar Obstacle List object
     *
     * @return std::list<RadarObsPtr> const& radar obs list
     */
    std::list<RadarObsPtr> const& GetRadarObstacleList()
    {
        return radar_obs_list_;
    }

    /**
     * @brief Compute propertie with track's position and velocity
     *
     * @param x position x
     * @param y position y
     * @param vx velocity x
     * @param vy velocity y
     */
    void ComputePropsWithTrack(Scalar const x, Scalar const y, Scalar const vx, Scalar const vy);

private:
    /**
     * @brief Try to find front radar obstacle
     *
     * @param sid front radar sensor id
     * @return RadarObsPtr radar obs pointer, nullptr if not found
     */
    RadarObsPtr findFrontRadarObs(SensorId const& sid);

private:
    Scalar         x_;
    Scalar         y_;
    Scalar         vx_;
    Scalar         vy_;
    Scalar         ax_;
    Scalar         ay_;
    Scalar         length_;
    Scalar         width_;
    Scalar         yaw_;
    Classification classification_;

    std::list<RadarObsPtr> radar_obs_list_;
    VisionObsPtr           vision_obs_;
    VisionObsPtr           smart_camera_obs_;
    Scalar                 weight_;
    bool_t                 matched_;
    bool_t                 has_front_radar_obs_;
};

/**
 * @brief Soft Track
 *
 */
class SoftTrack
{
public:
    using Scalar       = float32_t;
    using MeasureType  = SoftMeasure;
    using MeasurePtr   = std::shared_ptr<MeasureType>;
    using RadarObsPtr  = MeasureType::RadarObsPtr;
    using ObstacleType = ObstacleGeneralT<Scalar>;
    using ObstaclePtr  = std::shared_ptr<ObstacleType>;
    using VisionObsPtr = std::shared_ptr<ObstacleVisionT<Scalar>>;
    using Timestamp    = holo::common::details::Timestamp;
    using Point2f      = holo::geometry::details::Point2T<float32_t>;
    using Point3f      = holo::geometry::details::Point3T<float32_t>;
    using Polyfit2f    = holo::geometry::details::Polyfit2T<float32_t>;

    /**
     * @brief Construct a new Soft Track object
     *
     * @param timestamp current timestamp
     * @param track_id track id
     * @param measure measure to initialize
     * @param max_smooth_history max smooth history time step
     */
    explicit SoftTrack(Timestamp const& timestamp, uint32_t const track_id, MeasurePtr const measure,
                       uint32_t max_smooth_history)
      : timestamp_(timestamp)
      , start_timestamp_(timestamp)
      , track_id_(track_id)
      , x_(0.0f)
      , y_(0.0f)
      , vx_(0.0f)
      , vy_(0.0f)
      , ax_(0.0f)
      , ay_(0.0f)
      , length_(1.0f)
      , width_(1.0f)
      , height_(1.0f)
      , yaw_(0.0f)
      , time_since_update_(0U)
      , age_(1U)
      , max_smooth_history_(max_smooth_history)
      , has_front_radar_obs_(false)
      , measure_(measure)
      , vision_obs_(nullptr)
      , smart_camera_obs_(nullptr)
    {
        initialize(measure);
    }

    /**
     * @brief Predict a new state
     *
     * @param timestamp current timestamp
     */
    void Predict(Timestamp const& timestamp);

    /**
     * @brief Update state
     *
     */
    void Update();

    /**
     * @brief Add measure
     *
     * @param measure matched measure
     */
    void AddMeasure(MeasurePtr const measure)
    {
        measure_ = measure;
    }

    /**
     * @brief Set the Age object
     *
     * @param age age
     */
    void SetAge(uint32_t age)
    {
        age_ = age;
    }

    /**
     * @brief Set the track to be matched
     *
     */
    void SetMatched()
    {
        matched_ = true;
    }

    /**
     * @brief Get the Track Id
     *
     * @return uint32_t track id
     */
    uint32_t GetTrackId()
    {
        return track_id_;
    }

    /**
     * @brief Get position x
     *
     * @return Scalar position x
     */
    Scalar GetX()
    {
        return x_;
    }

    /**
     * @brief Get Position y
     *
     * @return Scalar position y
     */
    Scalar GetY()
    {
        return y_;
    }

    /**
     * @brief Get the velocity x
     *
     * @return Scalar velocity x
     */
    Scalar GetVx()
    {
        return vx_;
    }

    /**
     * @brief Get the velocity y
     *
     * @return Scalar velocity y
     */
    Scalar GetVy()
    {
        return vy_;
    }

    /**
     * @brief Get the Length
     *
     * @return Scalar length
     */
    Scalar GetLength()
    {
        return length_;
    }

    /**
     * @brief Get the Width
     *
     * @return Scalar width
     */
    Scalar GetWidth()
    {
        return width_;
    }

    /**
     * @brief Get the Time Since Update
     *
     * @return uint32_t time since update
     */
    uint32_t GetTimeSinceUpdate()
    {
        return time_since_update_;
    }

    /**
     * @brief Get the Age
     *
     * @return uint32_t track's age
     */
    uint32_t GetAge()
    {
        return age_;
    }

    /**
     * @brief Get the Vision Obs
     *
     * @return VisionObsPtr vision obstacle pointer
     */
    VisionObsPtr GetVisionObs()
    {
        return vision_obs_;
    }

    /**
     * @brief Get the Smart Camera Obs
     *
     * @return VisionObsPtr smart camera obs
     */
    VisionObsPtr GetSmartCameraObs()
    {
        return smart_camera_obs_;
    }

    /**
     * @brief Judge if the track has front radar obs
     *
     * @return bool_t true if it has one
     */
    bool_t HasFrontRadarObs()
    {
        return has_front_radar_obs_;
    }

    /**
     * @brief Judge if the track has been matched
     *
     * @return bool_t true if it is matched
     */
    bool_t IsMatched()
    {
        return matched_;
    }

    /**
     * @brief Get the Obstacle pointer to output
     *
     * @param vel_body velocity of body
     * @return ObstaclePtr obstacle pointer to output
     */
    ObstaclePtr GetObstaclePtr(Vector3f const& vel_body);

private:
    /**
     * @brief initialize the track
     *
     * @param measure initial measure
     */
    void initialize(MeasurePtr const measure);

    /**
     * @brief smooth position
     *
     * @param point_list point list of (time, position)
     * @return Scalar smoothed value
     */
    Scalar smooth(std::list<Point2f> const& point_list);

private:
    Timestamp      timestamp_;
    Timestamp      start_timestamp_;
    uint32_t       track_id_;
    Scalar         x_;
    Scalar         y_;
    Scalar         vx_;
    Scalar         vy_;
    Scalar         ax_;
    Scalar         ay_;
    Scalar         length_;
    Scalar         width_;
    Scalar         height_;
    Scalar         yaw_;
    Classification classification_;
    uint32_t       time_since_update_;
    uint32_t       age_;
    uint32_t       max_smooth_history_;
    bool_t         has_front_radar_obs_;
    bool_t         matched_;

    MeasurePtr   measure_;
    VisionObsPtr vision_obs_;
    VisionObsPtr smart_camera_obs_;

    std::list<Point2f> x_point_list_;
    std::list<Point2f> y_point_list_;
};

}  // namespace perception
}  // namespace holo

#endif  //! HOLO_PERCEPTION_TRACKING_SOFT_TRACK_H
