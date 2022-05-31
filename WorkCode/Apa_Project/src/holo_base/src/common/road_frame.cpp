/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_frame.cpp
 * @brief This src file implements RoadFrame.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-06
 */

#include <assert.h>
#include <holo/common/road_frame.h>

namespace holo
{
RoadFrame::RoadFrame() noexcept : timestamp_(0U, 0U), coordinate_(Coordinate::UNKNOWN), sensor_id_()
{
    for (size_t i = 0UL; i < ROAD_FRAME_MAX_LANE_NUM; ++i)
    {
        lanes_[i] = nullptr;
    }

    for (size_t i = 0UL; i < ROAD_FRAME_MAX_LANE_BOUNDARY_NUM; ++i)
    {
        lane_boundaries_[i] = nullptr;
    }
}

RoadFrame::RoadFrame(
    const Timestamp& timestamp, const Coordinate coord, const SensorId& sensor_id,
    const std::array<std::shared_ptr<Lane>, ROAD_FRAME_MAX_LANE_NUM>&                  lanes,
    const std::array<std::shared_ptr<LaneBoundary>, ROAD_FRAME_MAX_LANE_BOUNDARY_NUM>& lane_boundaries) noexcept
  : timestamp_(timestamp), coordinate_(coord), sensor_id_(sensor_id), lanes_(lanes), lane_boundaries_(lane_boundaries)
{
}

RoadFrame::RoadFrame(const RoadFrame& other) noexcept
  : timestamp_(other.timestamp_)
  , coordinate_(other.coordinate_)
  , sensor_id_(other.sensor_id_)
  , lanes_(other.lanes_)
  , lane_boundaries_(other.lane_boundaries_)
{
}

RoadFrame::RoadFrame(RoadFrame&& other) noexcept
  : timestamp_(other.timestamp_)
  , coordinate_(other.coordinate_)
  , sensor_id_(other.sensor_id_)
  , lanes_(std::move(other.lanes_))
  , lane_boundaries_(std::move(other.lane_boundaries_))
{
}

RoadFrame& RoadFrame::operator=(const RoadFrame& other) noexcept
{
    this->timestamp_       = other.timestamp_;
    this->coordinate_      = other.coordinate_;
    this->sensor_id_       = other.sensor_id_;
    this->lanes_           = other.lanes_;
    this->lane_boundaries_ = other.lane_boundaries_;

    return *this;
}

RoadFrame& RoadFrame::operator=(RoadFrame&& other) noexcept
{
    // avoid self = std::move(self)
    if (this == &other)
    {
        return *this;
    }

    this->timestamp_       = other.timestamp_;
    this->coordinate_      = other.coordinate_;
    this->sensor_id_       = other.sensor_id_;
    this->lanes_           = std::move(other.lanes_);
    this->lane_boundaries_ = std::move(other.lane_boundaries_);

    return *this;
}

const std::array<std::shared_ptr<const Lane>, ROAD_FRAME_MAX_LANE_NUM> RoadFrame::GetLanes() const noexcept
{
    std::array<std::shared_ptr<const Lane>, ROAD_FRAME_MAX_LANE_NUM> ret;
    for (size_t i = 0UL; i < ROAD_FRAME_MAX_LANE_NUM; ++i)
    {
        if (lanes_[i] != nullptr)
        {
            ret[i] = std::const_pointer_cast<const Lane>(lanes_[i]);
        }
        else
        {
            ret[i] = nullptr;
        }
    }
    return ret;
}

const std::array<std::shared_ptr<const LaneBoundary>, ROAD_FRAME_MAX_LANE_BOUNDARY_NUM>
RoadFrame::GetLaneBoundaries() const noexcept
{
    std::array<std::shared_ptr<const LaneBoundary>, ROAD_FRAME_MAX_LANE_BOUNDARY_NUM> ret;
    for (size_t i = 0UL; i < ROAD_FRAME_MAX_LANE_BOUNDARY_NUM; ++i)
    {
        if (lane_boundaries_[i] != nullptr)
        {
            ret[i] = std::const_pointer_cast<const LaneBoundary>(lane_boundaries_[i]);
        }
        else
        {
            ret[i] = nullptr;
        }
    }
    return ret;
}

const std::shared_ptr<const Lane> RoadFrame::GetCurrentLane() const
{
    return GetLaneById(Lane::LaneId::CURRENT_LANE);
}

std::shared_ptr<Lane> RoadFrame::GetCurrentLane()
{
    return GetLaneById(Lane::LaneId::CURRENT_LANE);
}

void RoadFrame::SetCurrentLane(const std::shared_ptr<Lane>& lane)
{
    return SetLaneById(Lane::LaneId::CURRENT_LANE, lane);
}

const std::shared_ptr<const Lane> RoadFrame::GetLeft1stLane() const
{
    return GetLaneById(Lane::LaneId::LEFT_1ST_LANE);
}

std::shared_ptr<Lane> RoadFrame::GetLeft1stLane()
{
    return GetLaneById(Lane::LaneId::LEFT_1ST_LANE);
}

void RoadFrame::SetLeft1stLane(const std::shared_ptr<Lane>& lane)
{
    return SetLaneById(Lane::LaneId::LEFT_1ST_LANE, lane);
}

const std::shared_ptr<const Lane> RoadFrame::GetLeft2ndLane() const
{
    return GetLaneById(Lane::LaneId::LEFT_2ND_LANE);
}

std::shared_ptr<Lane> RoadFrame::GetLeft2ndLane()
{
    return GetLaneById(Lane::LaneId::LEFT_2ND_LANE);
}

void RoadFrame::SetLeft2ndLane(const std::shared_ptr<Lane>& lane)
{
    return SetLaneById(Lane::LaneId::LEFT_2ND_LANE, lane);
}

const std::shared_ptr<const Lane> RoadFrame::GetRight1stLane() const
{
    return GetLaneById(Lane::LaneId::RIGHT_1ST_LANE);
}

std::shared_ptr<Lane> RoadFrame::GetRight1stLane()
{
    return GetLaneById(Lane::LaneId::RIGHT_1ST_LANE);
}

void RoadFrame::SetRight1stLane(const std::shared_ptr<Lane>& lane)
{
    return SetLaneById(Lane::LaneId::RIGHT_1ST_LANE, lane);
}

const std::shared_ptr<const Lane> RoadFrame::GetRight2ndLane() const
{
    return GetLaneById(Lane::LaneId::RIGHT_2ND_LANE);
}

std::shared_ptr<Lane> RoadFrame::GetRight2ndLane()
{
    return GetLaneById(Lane::LaneId::RIGHT_2ND_LANE);
}

void RoadFrame::SetRight2ndLane(const std::shared_ptr<Lane>& lane)
{
    return SetLaneById(Lane::LaneId::RIGHT_2ND_LANE, lane);
}

const std::shared_ptr<const Lane> RoadFrame::GetLaneById(const Lane::LaneId lane_id) const
{
    switch (lane_id)
    {
        case Lane::LaneId::LEFT_2ND_LANE:
            return GetLaneByIndex(0U);
        case Lane::LaneId::LEFT_1ST_LANE:
            return GetLaneByIndex(1U);
        case Lane::LaneId::CURRENT_LANE:
            return GetLaneByIndex(2U);
        case Lane::LaneId::RIGHT_1ST_LANE:
            return GetLaneByIndex(3U);
        case Lane::LaneId::RIGHT_2ND_LANE:
            return GetLaneByIndex(4U);
        default:
            throw std::runtime_error("Can not get lane from unknown LaneId!");
            break;
    }
}

std::shared_ptr<Lane> RoadFrame::GetLaneById(const Lane::LaneId lane_id)
{
    switch (lane_id)
    {
        case Lane::LaneId::LEFT_2ND_LANE:
            return GetLaneByIndex(0U);
        case Lane::LaneId::LEFT_1ST_LANE:
            return GetLaneByIndex(1U);
        case Lane::LaneId::CURRENT_LANE:
            return GetLaneByIndex(2U);
        case Lane::LaneId::RIGHT_1ST_LANE:
            return GetLaneByIndex(3U);
        case Lane::LaneId::RIGHT_2ND_LANE:
            return GetLaneByIndex(4U);
        default:
            throw std::runtime_error("Can not get lane from unknown LaneId!");
            break;
    }
}

void RoadFrame::SetLaneById(const Lane::LaneId lane_id, const std::shared_ptr<Lane>& lane)
{
    switch (lane_id)
    {
        case Lane::LaneId::LEFT_2ND_LANE:
            SetLaneByIndex(0U, lane);
            break;
        case Lane::LaneId::LEFT_1ST_LANE:
            SetLaneByIndex(1U, lane);
            break;
        case Lane::LaneId::CURRENT_LANE:
            SetLaneByIndex(2U, lane);
            break;
        case Lane::LaneId::RIGHT_1ST_LANE:
            SetLaneByIndex(3U, lane);
            break;
        case Lane::LaneId::RIGHT_2ND_LANE:
            SetLaneByIndex(4U, lane);
            break;
        default:
            throw std::runtime_error("Can not set lane from unknown LaneId!");
            break;
    }
}

const std::shared_ptr<const Lane> RoadFrame::GetLaneByIndex(uint32_t index) const
{
    if (index >= ROAD_FRAME_MAX_LANE_NUM)
    {
        throw std::runtime_error("Invalid lane index!");
    }
    std::shared_ptr<const Lane> ret = std::const_pointer_cast<const Lane>(lanes_[index]);
    return ret;
}

std::shared_ptr<Lane> RoadFrame::GetLaneByIndex(uint32_t index)
{
    if (index >= ROAD_FRAME_MAX_LANE_NUM)
    {
        throw std::runtime_error("Invalid lane index!");
    }
    return lanes_[index];
}

void RoadFrame::SetLaneByIndex(uint32_t index, const std::shared_ptr<Lane>& lane)
{
    if (index >= ROAD_FRAME_MAX_LANE_NUM)
    {
        throw std::runtime_error("Invalid lane index!");
    }
    lanes_[index] = lane;
}

const std::shared_ptr<const LaneBoundary> RoadFrame::GetLeft3rdLaneBoundary() const
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::LEFT_3RD_LINE);
}

std::shared_ptr<LaneBoundary> RoadFrame::GetLeft3rdLaneBoundary()
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::LEFT_3RD_LINE);
}

void RoadFrame::SetLeft3rdLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary)
{
    return SetLaneBoundaryById(LaneBoundary::LaneBoundaryId::LEFT_3RD_LINE, lane_boundary);
}

bool_t RoadFrame::IsLaneBoundaryValid(const LaneBoundary::LaneBoundaryId lane_boundary_id) const noexcept
{
    try
    {
        const auto lane_boundary = GetLaneBoundaryById(lane_boundary_id);
        if (lane_boundary == nullptr || lane_boundary->GetConfidence() < 1e-6)
        {
            return false;
        }
    }
    catch (const std::runtime_error& e)
    {
        return false;
    }

    return true;
}

const std::shared_ptr<const LaneBoundary> RoadFrame::GetLeft2ndLaneBoundary() const
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::LEFT_2ND_LINE);
}

std::shared_ptr<LaneBoundary> RoadFrame::GetLeft2ndLaneBoundary()
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::LEFT_2ND_LINE);
}

void RoadFrame::SetLeft2ndLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary)
{
    return SetLaneBoundaryById(LaneBoundary::LaneBoundaryId::LEFT_2ND_LINE, lane_boundary);
}

const std::shared_ptr<const LaneBoundary> RoadFrame::GetLeft1stLaneBoundary() const
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::LEFT_1ST_LINE);
}

std::shared_ptr<LaneBoundary> RoadFrame::GetLeft1stLaneBoundary()
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::LEFT_1ST_LINE);
}

void RoadFrame::SetLeft1stLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary)
{
    return SetLaneBoundaryById(LaneBoundary::LaneBoundaryId::LEFT_1ST_LINE, lane_boundary);
}

const std::shared_ptr<const LaneBoundary> RoadFrame::GetRight1stLaneBoundary() const
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::RIGHT_1ST_LINE);
}

std::shared_ptr<LaneBoundary> RoadFrame::GetRight1stLaneBoundary()
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::RIGHT_1ST_LINE);
}

void RoadFrame::SetRight1stLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary)
{
    return SetLaneBoundaryById(LaneBoundary::LaneBoundaryId::RIGHT_1ST_LINE, lane_boundary);
}

const std::shared_ptr<const LaneBoundary> RoadFrame::GetRight2ndLaneBoundary() const
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::RIGHT_2ND_LINE);
}

std::shared_ptr<LaneBoundary> RoadFrame::GetRight2ndLaneBoundary()
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::RIGHT_2ND_LINE);
}

void RoadFrame::SetRight2ndLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary)
{
    return SetLaneBoundaryById(LaneBoundary::LaneBoundaryId::RIGHT_2ND_LINE, lane_boundary);
}

const std::shared_ptr<const LaneBoundary> RoadFrame::GetRight3rdLaneBoundary() const
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::RIGHT_3RD_LINE);
}

std::shared_ptr<LaneBoundary> RoadFrame::GetRight3rdLaneBoundary()
{
    return GetLaneBoundaryById(LaneBoundary::LaneBoundaryId::RIGHT_3RD_LINE);
}

void RoadFrame::SetRight3rdLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary)
{
    return SetLaneBoundaryById(LaneBoundary::LaneBoundaryId::RIGHT_3RD_LINE, lane_boundary);
}

const std::shared_ptr<const LaneBoundary>
RoadFrame::GetLaneBoundaryById(const LaneBoundary::LaneBoundaryId lane_boundary_id) const
{
    switch (lane_boundary_id)
    {
        case LaneBoundary::LaneBoundaryId::LEFT_3RD_LINE:
            return GetLaneBoundaryByIndex(0U);
        case LaneBoundary::LaneBoundaryId::LEFT_2ND_LINE:
            return GetLaneBoundaryByIndex(1U);
        case LaneBoundary::LaneBoundaryId::LEFT_1ST_LINE:
            return GetLaneBoundaryByIndex(2U);
        case LaneBoundary::LaneBoundaryId::RIGHT_1ST_LINE:
            return GetLaneBoundaryByIndex(3U);
        case LaneBoundary::LaneBoundaryId::RIGHT_2ND_LINE:
            return GetLaneBoundaryByIndex(4U);
        case LaneBoundary::LaneBoundaryId::RIGHT_3RD_LINE:
            return GetLaneBoundaryByIndex(5U);
        default:
            throw std::runtime_error("Can not get lane boundary from unknown LaneBoundaryId!");
            break;
    }
}

std::shared_ptr<LaneBoundary> RoadFrame::GetLaneBoundaryById(LaneBoundary::LaneBoundaryId lane_boundary_id)
{
    switch (lane_boundary_id)
    {
        case LaneBoundary::LaneBoundaryId::LEFT_3RD_LINE:
            return GetLaneBoundaryByIndex(0U);
        case LaneBoundary::LaneBoundaryId::LEFT_2ND_LINE:
            return GetLaneBoundaryByIndex(1U);
        case LaneBoundary::LaneBoundaryId::LEFT_1ST_LINE:
            return GetLaneBoundaryByIndex(2U);
        case LaneBoundary::LaneBoundaryId::RIGHT_1ST_LINE:
            return GetLaneBoundaryByIndex(3U);
        case LaneBoundary::LaneBoundaryId::RIGHT_2ND_LINE:
            return GetLaneBoundaryByIndex(4U);
        case LaneBoundary::LaneBoundaryId::RIGHT_3RD_LINE:
            return GetLaneBoundaryByIndex(5U);
        default:
            throw std::runtime_error("Can not get lane boundary from unknown LaneBoundaryId!");
            break;
    }
}

void RoadFrame::SetLaneBoundaryById(const LaneBoundary::LaneBoundaryId   lane_boundary_id,
                                    const std::shared_ptr<LaneBoundary>& lane_boundary)
{
    switch (lane_boundary_id)
    {
        case LaneBoundary::LaneBoundaryId::LEFT_3RD_LINE:
            SetLaneBoundaryByIndex(0U, lane_boundary);
            break;
        case LaneBoundary::LaneBoundaryId::LEFT_2ND_LINE:
            SetLaneBoundaryByIndex(1U, lane_boundary);
            break;
        case LaneBoundary::LaneBoundaryId::LEFT_1ST_LINE:
            SetLaneBoundaryByIndex(2U, lane_boundary);
            break;
        case LaneBoundary::LaneBoundaryId::RIGHT_1ST_LINE:
            SetLaneBoundaryByIndex(3U, lane_boundary);
            break;
        case LaneBoundary::LaneBoundaryId::RIGHT_2ND_LINE:
            SetLaneBoundaryByIndex(4U, lane_boundary);
            break;
        case LaneBoundary::LaneBoundaryId::RIGHT_3RD_LINE:
            SetLaneBoundaryByIndex(5U, lane_boundary);
            break;
        default:
            throw std::runtime_error("Can not set lane boundary from unknown LaneBoundaryId!");
            break;
    }
}

const std::shared_ptr<const LaneBoundary> RoadFrame::GetLaneBoundaryByIndex(uint32_t index) const
{
    if (index >= ROAD_FRAME_MAX_LANE_BOUNDARY_NUM)
    {
        throw std::runtime_error("Invalid lane boundary index!");
    }
    std::shared_ptr<const LaneBoundary> ret = std::const_pointer_cast<const LaneBoundary>(lane_boundaries_[index]);
    return ret;
}

std::shared_ptr<LaneBoundary> RoadFrame::GetLaneBoundaryByIndex(uint32_t index)
{
    if (index >= ROAD_FRAME_MAX_LANE_BOUNDARY_NUM)
    {
        throw std::runtime_error("Invalid lane boundary index!");
    }
    return lane_boundaries_[index];
}

void RoadFrame::SetLaneBoundaryByIndex(uint32_t index, const std::shared_ptr<LaneBoundary>& lane_boundary)
{
    if (index >= ROAD_FRAME_MAX_LANE_BOUNDARY_NUM)
    {
        throw std::runtime_error("Invalid lane boundary index!");
    }
    lane_boundaries_[index] = lane_boundary;
}

uint8_t RoadFrame::FromLaneIDToIdx(Lane::LaneId lane_id) noexcept
{
    uint8_t lane_arr_idx = 0U;
    switch (lane_id)
    {
        case Lane::LaneId::LEFT_2ND_LANE:
            lane_arr_idx = 0U;
            break;
        case Lane::LaneId::LEFT_1ST_LANE:
            lane_arr_idx = 1U;
            break;
        case Lane::LaneId::CURRENT_LANE:
            lane_arr_idx = 2U;
            break;
        case Lane::LaneId::RIGHT_1ST_LANE:
            lane_arr_idx = 3U;
            break;
        case Lane::LaneId::RIGHT_2ND_LANE:
            lane_arr_idx = 4U;
            break;
        case Lane::LaneId::INVALID:
            lane_arr_idx = 255U;
            break;
    }
    return lane_arr_idx;
}

/**
 * @brief get idx of lanes_ from lane_boundary_id
 *
 * @param lane_boundary_id the id defined in LaneBoundary
 * @return lane_boundary idx
 */
uint8_t RoadFrame::FromLaneBoundaryIDToIdx(LaneBoundary::LaneBoundaryId lane_boundary_id) noexcept
{
    uint8_t lane_boundary_arr_idx = 0U;
    switch (lane_boundary_id)
    {
        case LaneBoundary::LaneBoundaryId::LEFT_3RD_LINE:
            lane_boundary_arr_idx = 0U;
            break;
        case LaneBoundary::LaneBoundaryId::LEFT_2ND_LINE:
            lane_boundary_arr_idx = 1U;
            break;
        case LaneBoundary::LaneBoundaryId::LEFT_1ST_LINE:
            lane_boundary_arr_idx = 2U;
            break;
        case LaneBoundary::LaneBoundaryId::RIGHT_1ST_LINE:
            lane_boundary_arr_idx = 3U;
            break;
        case LaneBoundary::LaneBoundaryId::RIGHT_2ND_LINE:
            lane_boundary_arr_idx = 4U;
            break;
        case LaneBoundary::LaneBoundaryId::RIGHT_3RD_LINE:
            lane_boundary_arr_idx = 4U;
            break;
        case LaneBoundary::LaneBoundaryId::INVALID:
            lane_boundary_arr_idx = 255U;
            break;
    }
    return lane_boundary_arr_idx;
}

void RoadFrame::AutoBinding() noexcept
{
    for (uint32_t i = 0U; i < ROAD_FRAME_MAX_LANE_NUM; ++i)
    {
        if (lanes_[i] != nullptr)
        {
            lanes_[i]->SetLeftLaneBoundary(lane_boundaries_[i]);
            lanes_[i]->SetRightLaneBoundary(lane_boundaries_[i + 1U]);
        }
    }
}

std::string RoadFrame::ToString() const noexcept
{
    std::stringstream ss;
    ss << "RoadFrame: ("
       << "timestamp_: " << timestamp_.ToString()
       << ", coordinate_: " << static_cast<uint32_t>(coordinate_) << ", lanes_: " << std::endl;
    for (uint32_t i = 0U; i < ROAD_FRAME_MAX_LANE_NUM; ++i)
    {
        if (lanes_[i] != nullptr)
        {
            ss << "lanes_[" << i << "]: " << lanes_[i]->ToString();
        }
        else
        {
            ss << "lanes_[" << i << "]: is empty." << std::endl;
        }
    }

    ss << "lane_boundaries_: " << std::endl;
    for (uint32_t i = 0U; i < ROAD_FRAME_MAX_LANE_BOUNDARY_NUM; ++i)
    {
        if (lane_boundaries_[i] != nullptr)
        {
            ss << "lane_boundaries_[" << i << "]: " << lane_boundaries_[i]->ToString();
        }
        else
        {
            ss << "lane_boundaries_[" << i << "]: is empty" << std::endl;
        }
    }

    ss << ")" << std::endl;

    return ss.str();
}

}  // namespace holo
