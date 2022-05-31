/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file track.h
 * @brief This header file defines a base class of track.
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-05"
 */

#ifndef HOLO_PERCEPTION_TRACKING_TRACK_H_
#define HOLO_PERCEPTION_TRACKING_TRACK_H_

#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/perception/utils/uid_generator.h>

#include <array>
#include <list>
#include <string>

namespace holo
{
namespace perception
{
/**
 * @addtogroup tracking
 *
 * @{
 */

/**
 * @brief This class defines a base class of track to describe trajectory of an object.
 * @details track_list_ save one track of a type of sensor according to sorted timestamp.
 *
 * @tparam T data type of measured object.
 */
template <typename T>
class TrackT
{
public:
    /**
     * @brief Stage represents life cycle of the track
     *
     */
    enum class Stage : uint8_t
    {
        UNCONFIRMED,  ///< Not enough confidence yet to 'confirm'
        CONFIRMED,    ///< Confirmed and tracking
        LOST,         ///< During tracking, we miss some observation
        TERMINATED,   ///< Forever lost
        RESERVED      ///< During tracking, we miss some observation, but predict it's property and output
    };

    /**
     * @brief Smart pointer
     *
     */
    using Ptr             = std::shared_ptr<TrackT<T>>;
    using ConstPtr        = std::shared_ptr<const TrackT<T>>;
    using StageUnderlying = typename std::underlying_type<Stage>::type;
    using TrackId         = uint32_t;
    using Timestamp       = holo::common::details::Timestamp;
    using SensorId        = holo::common::SensorId;

    /**
     * @brief Default constructer of Track class
     *
     * @details Constructor with no parameter. Will set track id, stage, sensorid, start time and list to default
     */
    TrackT() noexcept;

    /**
     * @brief Construct a new Track T object
     *
     * @param id track id
     * @param stage track stage
     * @param sensor_id track sensor id
     * @param timestamp track start time
     * @param object track's measured object
     * @param max_list_size max history list size
     */
    TrackT(const TrackId id, const Stage stage, const SensorId sensor_id, const Timestamp& timestamp, const T& object,
           const uint32_t max_list_size = 20U) noexcept;

    /**
     * @brief Cast enum class to underlying type
     *
     * @return StageUnderlying
     */
    StageUnderlying StageUnderLying() const noexcept
    {
        return static_cast<StageUnderlying>(stage_);
    }

    /**
     * @brief Get the track stage
     *
     * @return Stage
     */
    Stage GetStage() const noexcept
    {
        return stage_;
    }

    /**
     * @brief Set track stage
     *
     * @param stage track stage
     */
    void SetStage(const Stage stage) noexcept
    {
        stage_ = stage;
    }

    /**
     * @brief Get track stage string
     *
     * @return const std::string&
     */
    const std::string& GetStageString() const noexcept
    {
        return STAGE_STRING[this->StageUnderLying()];
    }

    /**
     * @brief Get track id
     *
     * @return const TrackId
     */
    TrackId GetId() const noexcept
    {
        return id_;
    }

    /**
     * @brief Set track id
     *
     * @param id track id
     */
    void SetId(const TrackId id) noexcept
    {
        id_ = id;
    }

    /**
     * @brief Get sensor id of track
     *
     * @return holo::SensorId
     */
    const SensorId GetSensorId() const noexcept
    {
        return sensor_id_;
    }

    /**
     * @brief Set sensor id
     *
     * @param sensor_id sensor id of track
     */
    void SetSensorId(const SensorId& sensor_id) noexcept
    {
        sensor_id_ = sensor_id;
    }

    /**
     * @brief Get track start time
     *
     * @return const TimeStamp&
     */
    const Timestamp& GetStartTime() const noexcept
    {
        return start_time_;
    }

    /**
     * @brief Set track start time
     *
     * @param time_stamp track start time
     */
    void SetStartTime(const Timestamp& time_stamp) noexcept
    {
        start_time_ = time_stamp;
    }

    /**
     * @brief Get track list
     * @details This function will return a copied list, so don't call it in a loop
     *
     * @return std::list object pointer list
     */
    const std::list<std::shared_ptr<const T>> GetTrack() const noexcept
    {
        std::list<std::shared_ptr<const T>> ret;
        for (auto iter = track_list_.begin(); iter != track_list_.end(); iter++)
        {
            ret.push_back(std::const_pointer_cast<const T>(*iter));
        }
        return ret;
    }

    /**
     * @brief Get track list
     *
     * @return std::list<std::shared_ptr<T>>
     */
    std::list<std::shared_ptr<T>>& GetTrack() noexcept
    {
        return track_list_;
    }

    /**
     * @brief Get the Newest Object Pointer
     *
     * @return const std::shared_ptr<const T>
     */
    const std::shared_ptr<const T> GetNewestObjPtr() const
    {
        return std::const_pointer_cast<const T>(*track_list_.begin());
    }

    /**
     * @brief Get the max list size
     *
     */
    uint32_t GetMaxListSize() const noexcept
    {
        return max_list_size_;
    }

    /**
     * @brief Set the max list size
     *
     * @param max_list_size
     */
    void SetMaxListSize(uint32_t max_list_size)
    {
        max_list_size_ = max_list_size;
    }

    /**
     * @brief Update and old track
     *
     * @tparam object
     */
    virtual void Update(const T& object);

    /**
     * @brief Whether track list is empty
     *
     * @return bool_t
     */
    bool_t IsEmpty() const noexcept
    {
        return track_list_.empty();
    }

protected:
    const static uint32_t                           STAGE_NUM = 5U;
    const static std::array<std::string, STAGE_NUM> STAGE_STRING;

    TrackId                       id_;
    Stage                         stage_;
    SensorId                      sensor_id_;
    Timestamp                     start_time_;
    std::list<std::shared_ptr<T>> track_list_;
    uint32_t                      max_list_size_;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_TRACK_H_
