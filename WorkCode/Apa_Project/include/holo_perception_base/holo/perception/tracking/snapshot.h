/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file snapshot.h
 * @brief This header file defines a base class of snapshot to save a frame of a track
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-06"
 */

#ifndef HOLO_PERCEPTION_TRACKING_SNAPSHOT_H_
#define HOLO_PERCEPTION_TRACKING_SNAPSHOT_H_

#include <holo/log/hololog.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/box3.h>
#include <holo/obstacle/obstacle_base.h>
#include <holo/perception/tracking/filter_state.h>

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
 * @brief Representation a snapshot of a track at a particular time
 *
 * @tparam T data type of measured object.
 */
template <typename T>
class TrackSnapshotT
{
public:
    using Ptr       = std::shared_ptr<TrackSnapshotT<T> >;
    using ConstPtr  = std::shared_ptr<const TrackSnapshotT<T> >;
    using TrackId   = uint32_t;
    using Point3f   = holo::geometry::details::Point3T<float32_t>;
    using Timestamp = holo::common::details::Timestamp;

    /**
     * @brief Delete default constructer, because the null pointer will make coredump
     *
     */
    TrackSnapshotT() = delete;

    /**
     * @brief Construct a new track snapshot and delete default constructer
     *
     * @param object measured object
     */
    explicit TrackSnapshotT(const T& object)
    {
        object_ptr_   = std::make_shared<T>(object);
        filter_state_ = holo::perception::FilterState::PASSED;
    }

    /**
     * @brief Get object id
     *
     * @return TrackId
     */
    TrackId GetObjectId() const noexcept
    {
        return object_ptr_->GetObstacleId();
    }

    /**
     * @brief Get object ptr
     *
     * @return const ObjectPtr
     */
    const std::shared_ptr<T>& GetObjectPtr() const noexcept
    {
        return object_ptr_;
    }

    /**
     * @brief Set object ptr
     *
     * @param object measured object
     */
    void SetObjectPtr(const T& object) noexcept
    {
        object_ptr_ = std::shared_ptr<T>(object);
    }

    /**
     * @brief Get the timestamp of object
     *
     * @return const Timestamp
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return object_ptr_->GetTimestamp();
    }

    /**
     * @brief Get the filter state of object
     *
     * @return FilterState
     */
    FilterState GetFilterState() const noexcept
    {
        return filter_state_;
    }

    /**
     * @brief Set filter state of object
     *
     * @param filter_state filter state
     */
    void SetFilterState(const FilterState filter_state) noexcept
    {
        filter_state_ = filter_state;
    }

    /**
     * @brief Get view point of different sensors
     *
     * @return Point3f
     */
    Point3f GetViewPoint() const
    {
        auto    x = object_ptr_->GetObstacleBBox3D().GetPose().GetX();
        auto    y = object_ptr_->GetObstacleBBox3D().GetPose().GetY();
        auto    z = object_ptr_->GetObstacleBBox3D().GetPose().GetZ();
        Point3f pos(x, y, z);
        return pos;
    }

private:
    std::shared_ptr<T> object_ptr_;
    FilterState        filter_state_;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_SNAPSHOT_H_
