/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_frame.h
 * @brief This header file defines RoadFrame.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-08-30
 */

#ifndef HOLO_COMMON_ROAD_FRAME_H_
#define HOLO_COMMON_ROAD_FRAME_H_

#include <holo/common/coordinate.h>
#include <holo/common/lane.h>
#include <holo/common/lane_boundary.h>
#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/serialization/serialization.h>

using holo::common::SensorId;

namespace holo
{
/**
 * @addtogroup common
 *
 * @{
 */

static const uint32_t ROAD_FRAME_MAX_LANE_NUM          = 5;  ///< max lanes a roadframe contain
static const uint32_t ROAD_FRAME_MAX_LANE_BOUNDARY_NUM = 6;  ///< max lane boundaries a roadframe contain

/**
 * @brief Roadframe type
 * @deprecated Use holo::common::RoadFrame instead. Will be removed in v0.5.0.
 *
 * @details A roadframe is comprised of lanes and lane boundaries. A roadframe has 5 lanes and lane boundaries at most.
 * The id of lane and lane boundaries are cross arrangement from left to right, boundary...lane...boundary. Lane holds
 * even id numbers and lane boundary holds odd id numbers. Roadframe also provide getter and setter API to lane and lane
 * boundaries.
 */
class [[deprecated]] RoadFrame
{
public:
    using Coordinate = holo::common::Coordinate;

    /**
     * @brief Default constructor
     */
    RoadFrame() noexcept;

    /**
     * @brief Constructor with parameters
     *
     * @param time_stamp time stamp
     * @param Coordinate coord for lane boundaries points
     * @param lanes lane array
     * @param lane_boundaries lane boundary array
     */
    RoadFrame(
        const Timestamp& time_stamp, const Coordinate coord, const SensorId& sensor_id,
        const std::array<std::shared_ptr<Lane>, ROAD_FRAME_MAX_LANE_NUM>&                  lanes,
        const std::array<std::shared_ptr<LaneBoundary>, ROAD_FRAME_MAX_LANE_BOUNDARY_NUM>& lane_boundaries) noexcept;

    /**
     * @brief Copy constructor
     *
     * @param other other road frame
     */
    RoadFrame(const RoadFrame& other) noexcept;

    /**
     * @brief Move constructor
     *
     * @param other other road frame
     */
    RoadFrame(RoadFrame&& other) noexcept;

    /**
     * @brief Copy assignment
     *
     * @param other other road frame
     * @return new road frame
     */
    RoadFrame& operator=(const RoadFrame& other) noexcept;

    /**
     * @brief Move assignment
     *
     * @param other other road frame
     * @return new road frame
     */
    RoadFrame& operator=(RoadFrame&& other) noexcept;

    /**
     * @brief Get timestamp of road frame
     *
     * @return timestamp
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set time stamp of road frame
     *
     * @param timestamp timestmap
     */
    void SetTimestamp(const Timestamp& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief Get coordinate of road frame
     *
     * @return coordinate of lane
     */
    Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Set coordinate of road frame
     *
     * @param coord coordinate of road frame
     */
    void SetCoordinate(const Coordinate coord) noexcept
    {
        this->coordinate_ = coord;
    }

    /**
     * @brief Get sensor id of road frame
     *
     * @return sensor id of road frame
     */
    const SensorId& GetSensorId() const noexcept
    {
        return sensor_id_;
    }

    /**
     * @brief Set sensor id of road frame
     *
     * @param sensor_id sensor id of road frame
     */
    void SetSensorId(const SensorId& sensor_id) noexcept
    {
        this->sensor_id_ = sensor_id;
    }

    /**
     * @brief Get a copy of lanes whose content have been const qualified
     *
     * @return lanes
     */
    const std::array<std::shared_ptr<const Lane>, ROAD_FRAME_MAX_LANE_NUM> GetLanes() const noexcept;

    /**
     * @brief Get non-const reference of lanes
     *
     * @return lanes
     */
    std::array<std::shared_ptr<Lane>, ROAD_FRAME_MAX_LANE_NUM>& GetLanes() noexcept
    {
        return lanes_;
    }

    /**
     * @brief Set lanes for road frame one by one
     *
     * @param lanes lanes container
     */
    void SetLanes(const std::array<std::shared_ptr<Lane>, ROAD_FRAME_MAX_LANE_NUM>& lanes) noexcept
    {
        this->lanes_ = lanes;
    }

    /**
     * @brief Set lanes for road frame in efficient way
     *
     * @param lanes lanes container
     */
    void SetLanes(std::array<std::shared_ptr<Lane>, ROAD_FRAME_MAX_LANE_NUM>&& lanes) noexcept
    {
        std::swap(this->lanes_, lanes);
    }

    /**
     * @brief Get a copy of lane boundaries whose content have been const qualified
     *
     * @return lane boundaries container
     */
    const std::array<std::shared_ptr<const LaneBoundary>, ROAD_FRAME_MAX_LANE_BOUNDARY_NUM> GetLaneBoundaries() const
        noexcept;

    /**
     * @brief Get non const reference lane boundaries
     *
     * @return lane boundaries container
     */
    std::array<std::shared_ptr<LaneBoundary>, ROAD_FRAME_MAX_LANE_BOUNDARY_NUM>& GetLaneBoundaries() noexcept
    {
        return lane_boundaries_;
    }

    /**
     * @brief Set lane boundaries one by one
     *
     * @param lane_boundaries lane boundaries container
     */
    void SetLaneBoundaries(
        const std::array<std::shared_ptr<LaneBoundary>, ROAD_FRAME_MAX_LANE_BOUNDARY_NUM>& lane_boundaries) noexcept
    {
        this->lane_boundaries_ = lane_boundaries;
    }

    /**
     * @brief Set lane boundaries in efficient way
     *
     * @param lane_boudnaries lane boundaries container
     */
    void SetLaneBoundaries(
        std::array<std::shared_ptr<LaneBoundary>, ROAD_FRAME_MAX_LANE_BOUNDARY_NUM>&& lane_boundaries) noexcept
    {
        std::swap(this->lane_boundaries_, lane_boundaries);
    }

    /**
     * @brief Get current lane the object in
     *
     * @return current lane
     *
     * @throws runtime_error when lane id is invalid
     */
    const std::shared_ptr<const Lane> GetCurrentLane() const;

    /**
     * @brief Get current lane the object in
     *
     * @return current lane
     *
     * @throws runtime_error when lane id is invalid
     */
    std::shared_ptr<Lane> GetCurrentLane();

    /**
     * @brief Set current lane the object in
     *
     * @param lane current lane
     *
     * @throws runtime_error when lane id is invalid
     */
    void SetCurrentLane(const std::shared_ptr<Lane>& lane);

    /**
     * @brief Get left 1st lane
     *
     * @return left 1st lane
     *
     * @throws runtime_error when lane id is invalid
     */
    const std::shared_ptr<const Lane> GetLeft1stLane() const;

    /**
     * @brief Get left 1st lane
     *
     * @return left 1st lane
     *
     * @throws runtime_error when lane id is invalid
     */
    std::shared_ptr<Lane> GetLeft1stLane();

    /**
     * @brief Set left 1st lane
     *
     * @param lane left 1st lane
     *
     * @throws runtime_error when lane id is invalid
     */
    void SetLeft1stLane(const std::shared_ptr<Lane>& lane);

    /**
     * @brief Get left 2nd lane
     *
     * @return left 2nd lane
     *
     * @throws runtime_error when lane id is invalid
     */
    const std::shared_ptr<const Lane> GetLeft2ndLane() const;

    /**
     * @brief Get left 2nd lane
     *
     * @return left 2nd lane
     *
     * @throws runtime_error when lane id is invalid
     */
    std::shared_ptr<Lane> GetLeft2ndLane();

    /**
     * @brief Set left 2nd lane
     *
     * @param lane left 2nd lane
     *
     * @throws runtime_error when lane id is invalid
     */
    void SetLeft2ndLane(const std::shared_ptr<Lane>& lane);

    /**
     * @brief Get right 1st lane
     *
     * @return right 1st lane
     *
     * @throws runtime_error when lane id is invalid
     */
    const std::shared_ptr<const Lane> GetRight1stLane() const;

    /**
     * @brief Get right 1st lane
     *
     * @return right 1st lane
     *
     * @throws runtime_error when lane id is invalid
     */
    std::shared_ptr<Lane> GetRight1stLane();

    /**
     * @brief Set right 1st lane
     *
     * @param lane right 1st lane
     *
     * @throws runtime_error when lane id is invalid
     */
    void SetRight1stLane(const std::shared_ptr<Lane>& lane);

    /**
     * @brief Get right 2nd lane
     *
     * @return right 2nd lane
     *
     * @throws runtime_error when lane id is invalid
     */
    const std::shared_ptr<const Lane> GetRight2ndLane() const;

    /**
     * @brief Get right 2nd lane
     *
     * @return right 2nd lane
     *
     * @throws runtime_error when lane id is invalid
     */
    std::shared_ptr<Lane> GetRight2ndLane();

    /**
     * @brief Set right 2nd lane
     *
     * @param lane right 2nd lane
     *
     * @throws runtime_error when lane id is invalid
     */
    void SetRight2ndLane(const std::shared_ptr<Lane>& lane);

    /**
     * @brief Get lane with lane id
     *
     * @param lane_id lane id
     * @return specified lane
     *
     * @throws runtime_error when lane id is invalid
     */
    const std::shared_ptr<const Lane> GetLaneById(const Lane::LaneId lane_id) const;

    /**
     * @brief Get lane with lane id
     *
     * @param lane_id lane id
     * @return specified lane
     *
     * @throws runtime_error when lane id is invalid
     */
    std::shared_ptr<Lane> GetLaneById(const Lane::LaneId lane_id);

    /**
     * @brief Set lane with lane id
     *
     * @param lane_id lane id
     * @param lane lane
     *
     * @throws runtime_error when lane id is invalid
     */
    void SetLaneById(const Lane::LaneId lane_id, const std::shared_ptr<Lane>& lane);

    /**
     * @brief Judge if lane boundary is valid
     * @details Now, we only judge whether pointer is null and confidence is zero.
     *
     * @param lane_boundary_id lane boundary id
     * @return true Valid, otherwise invalid
     */
    bool_t IsLaneBoundaryValid(const LaneBoundary::LaneBoundaryId lane_boundary_id) const noexcept;

    /**
     * @brief Get left 3rd lane boundary
     *
     * @return left 3rd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    const std::shared_ptr<const LaneBoundary> GetLeft3rdLaneBoundary() const;

    /**
     * @brief Get left 3rd lane boundary
     *
     * @return left 3rd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    std::shared_ptr<LaneBoundary> GetLeft3rdLaneBoundary();

    /**
     * @brief Set left 3rd lane boundary
     *
     * @param lane_boundary left 3rd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    void SetLeft3rdLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary);

    /**
     * @brief Get left 2nd lane boundary
     *
     * @return left 2nd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    const std::shared_ptr<const LaneBoundary> GetLeft2ndLaneBoundary() const;

    /**
     * @brief Get left 2nd lane boundary
     *
     * @return left 2nd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    std::shared_ptr<LaneBoundary> GetLeft2ndLaneBoundary();

    /**
     * @brief Set left 2nd lane boundary
     *
     * @param lane_boundary left 2nd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    void SetLeft2ndLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary);

    /**
     * @brief Get left 1st lane boundary
     *
     * @return left 1st lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    const std::shared_ptr<const LaneBoundary> GetLeft1stLaneBoundary() const;

    /**
     * @brief Get left 1st lane boundary
     *
     * @return left 1st lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    std::shared_ptr<LaneBoundary> GetLeft1stLaneBoundary();

    /**
     * @brief Set left 1st lane boundary
     *
     * @param lane_boundary left 1st lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    void SetLeft1stLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary);

    /**
     * @brief Get right 1st lane boundary
     *
     * @return right 1st lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    const std::shared_ptr<const LaneBoundary> GetRight1stLaneBoundary() const;

    /**
     * @brief Get right 1st lane boundary
     *
     * @return right 1st lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    std::shared_ptr<LaneBoundary> GetRight1stLaneBoundary();

    /**
     * @brief Set right 1st lane boundary
     *
     * @param lane_boundary right 1st lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    void SetRight1stLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary);

    /**
     * @brief Get right 2nd lane boundary
     *
     * @return right 2nd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    const std::shared_ptr<const LaneBoundary> GetRight2ndLaneBoundary() const;

    /**
     * @brief Get right 2nd lane boundary
     *
     * @return right 2nd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    std::shared_ptr<LaneBoundary> GetRight2ndLaneBoundary();

    /**
     * @brief Set right 2nd lane boundary
     *
     * @param lane_boundary right 2nd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    void SetRight2ndLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary);

    /**
     * @brief Get right 3rd lane boundary
     *
     * @return right 3rd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    const std::shared_ptr<const LaneBoundary> GetRight3rdLaneBoundary() const;

    /**
     * @brief Get right 3rd lane boundary
     *
     * @return right 3rd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    std::shared_ptr<LaneBoundary> GetRight3rdLaneBoundary();

    /**
     * @brief Set right 3rd lane boundary
     *
     * @param lane_boundary right 3rd lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    void SetRight3rdLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary);

    /**
     * @brief Get lane boundary with lane boundary id
     *
     * @param lane_boundary_id lane boundary id
     *
     * @return lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    const std::shared_ptr<const LaneBoundary>
    GetLaneBoundaryById(const LaneBoundary::LaneBoundaryId lane_boundary_id) const;

    /**
     * @brief Get lane boundary with lane boundary id
     *
     * @param lane_boundary_id lane boundary id
     *
     * @return lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    std::shared_ptr<LaneBoundary> GetLaneBoundaryById(const LaneBoundary::LaneBoundaryId lane_boundary_id);

    /**
     * @brief Set lane boundary with lane boundary id
     *
     * @param lane_boundary_id lane boundary id
     * @param lane_boundary lane boundary
     *
     * @throws runtime_error when lane boundary id is invalid
     */
    void SetLaneBoundaryById(const LaneBoundary::LaneBoundaryId   lane_boundary_id,
                             const std::shared_ptr<LaneBoundary>& lane_boundary);

    /**
     * @brief Auto construct lane and lane boundary topological relationship
     *
     * @details Every lane should bind two lane boundaries, we store lanes and lane boundaries in road frame, road frame
     * holds the lief cycle of lane and lane boundaries. When we init a road frame and feed lanes and lane boundaries to
     * related containers in road frame, lane and lane boundaries have no topological relation, this function do this
     * step automatically.
     *
     * @note This function must be called after lanes_ and lane_boundaries_ have been filled with content.
     */
    void AutoBinding() noexcept;

    /**
     * @brief serialize content to string
     *
     * @return std::string
     */
    std::string ToString() const noexcept;

private:
    /**
     * @brief Get lane with index in array
     *
     * @param index index in array
     *
     * @return lane
     */
    const std::shared_ptr<const Lane> GetLaneByIndex(uint32_t index) const;

    /**
     * @brief Get lane with index in array
     *
     * @param index index in array
     *
     * @return lane
     */
    std::shared_ptr<Lane> GetLaneByIndex(uint32_t index);

    /**
     * @brief Set lane with index in array
     *
     * @param index index in array
     * @param lane lane
     */
    void SetLaneByIndex(uint32_t index, const std::shared_ptr<Lane>& lane);

    /**
     * @brief Get lane boundary with index
     *
     * @param index lane boundary index in array
     *
     * @return lane boundary
     */
    const std::shared_ptr<const LaneBoundary> GetLaneBoundaryByIndex(uint32_t index) const;

    /**
     * @brief Get lane boundary with index
     *
     * @param index lane boundary index in array
     *
     * @return lane boundary
     */
    std::shared_ptr<LaneBoundary> GetLaneBoundaryByIndex(uint32_t index);

    /**
     * @brief Set lane boundary with index in array
     *
     * @param index index in array
     * @param lane_boundary lane boundary
     */
    void SetLaneBoundaryByIndex(uint32_t index, const std::shared_ptr<LaneBoundary>& lane_boundary);

    /**
     * @brief get idx of lanes_ from lane_id
     *
     * @param lane_id the id defined in lane
     * @return lane idx
     */
    static uint8_t FromLaneIDToIdx(Lane::LaneId lane_id) noexcept;

    /**
     * @brief get index of lanes from lane_boundary_id
     *
     * @param lane_boundary_id the id defined in lane boundary
     * @return lane boundary index
     */
    static uint8_t FromLaneBoundaryIDToIdx(LaneBoundary::LaneBoundaryId lane_boundary_id) noexcept;

private:
    Timestamp                                                                   timestamp_;
    Coordinate                                                                  coordinate_;
    SensorId                                                                    sensor_id_;
    std::array<std::shared_ptr<Lane>, ROAD_FRAME_MAX_LANE_NUM>                  lanes_;
    std::array<std::shared_ptr<LaneBoundary>, ROAD_FRAME_MAX_LANE_BOUNDARY_NUM> lane_boundaries_;
};  // RoadFrame

/**
 * @}
 */

}  // namespace holo
#endif  //! HOLO_COMMON_ROAD_FRAME_H_
