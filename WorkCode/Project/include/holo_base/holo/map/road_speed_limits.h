/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_speed_limits.h
 * @brief This file defines RoadSpeedLimits class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-05
 */

#ifndef HOLO_MAP_ROAD_SPEED_LIMITS_H_
#define HOLO_MAP_ROAD_SPEED_LIMITS_H_

#include <holo/container/details/fixed_size_vector.h>
#include <holo/core/types.h>

namespace holo
{
namespace map
{
namespace details
{
/**
 * @brief Road speed limit information
 *
 * @tparam LANES Max number of lanes
 * @tparam SEGS Max number of speed limit segments of each lane
 */
template <size_t LANES, size_t SEGS>
class RoadSpeedLimits
{
public:
    static size_t const       LANE_SIZE_VALUE    = LANES;
    static size_t const       SEGMENT_SIZE_VALUE = SEGS;
    static holo::int8_t const INDEX_OFFSET       = static_cast<holo::uint8_t>(LANE_SIZE_VALUE - 1) / 2;

    class LaneSpeedLimits;

    using ContainerType          = holo::container::details::FixedSizeVector<LaneSpeedLimits, LANE_SIZE_VALUE>;
    using iterator               = typename ContainerType::iterator;
    using const_iterator         = typename ContainerType::const_iterator;
    using reverse_iterator       = typename ContainerType::reverse_iterator;
    using const_reverse_iterator = typename ContainerType::const_reverse_iterator;

    /**
     * @brief Type of lane index. 0 means current lane; -1 means first left lane; +1 means first right lane; etc...
     */
    using LaneIndexType = holo::int8_t;

    /**
     * @brief This struct represents speed limit infomation of one lane segment
     */
    struct SpeedLimitSegment
    {
        holo::float32_t start_distance;
        holo::float32_t end_distance;
        holo::float32_t min_speed;
        holo::float32_t max_speed;
    };

    /**
     * @brief This class represents all speed limit segment infomation in a lane.
     */
    class LaneSpeedLimits : public holo::container::details::FixedSizeVectorBase<SpeedLimitSegment, SEGMENT_SIZE_VALUE>
    {
    public:
        using Base = holo::container::details::FixedSizeVectorBase<SpeedLimitSegment, SEGMENT_SIZE_VALUE>;
        LaneSpeedLimits(LaneIndexType idx) : Base{}, lane_index_{idx}
        {
        }

        /**
         * @brief Get lane index
         *
         * @return
         */
        LaneIndexType GetLaneIndex() const noexcept
        {
            return lane_index_;
        }

    private:
        LaneIndexType lane_index_;
    };

    RoadSpeedLimits() : start_{}, end_{}, lanes_{}
    {
    }

    void SetLaneIndexRange(LaneIndexType min, LaneIndexType max)
    {
        if (max - min + 1U > LANE_SIZE_VALUE)
        {
            throw std::bad_alloc();
        }
        if (lanes_.empty() || max < lanes_.front().GetLaneIndex() || min > lanes_.back().GetLaneIndex())
        {
            lanes_.clear();
            for (LaneIndexType idx = min; idx <= max; ++idx)
            {
                lanes_.emplace_back(idx);
            }
        }
        else
        {
            if (max > lanes_.back().GetLaneIndex())
            {
                for (LaneIndexType idx = lanes_.back().GetLaneIndex() + 1U; idx <= max; ++idx)
                {
                    lanes_.emplace_back(idx);
                }
            }
            else
            {
                lanes_.erase(lanes_.end() - (lanes_.back().GetLaneIndex() - max), lanes_.end());
            }
            if (min < lanes_.front().GetLaneIndex())
            {
                for (LaneIndexType idx = lanes_.front().GetLaneIndex() - 1U; idx >= min; --idx)
                {
                    lanes_.insert(lanes_.begin(), {idx});
                }
            }
            else
            {
                lanes_.erase(lanes_.begin(), lanes_.begin() + (min - lanes_.front().GetLaneIndex()));
            }
        }
        start_ = min;
        end_ = max + 1U;
    }

    /**
     * @brief Get lane speed limits. If lane index not exists, throw out of range exception.
     *
     * @param index lane index
     *
     * @return Lane speed limits
     *
     * @throws std::out_of_range if lane index not exists
     */
    LaneSpeedLimits const& operator[](LaneIndexType index) const noexcept
    {
        return lanes_[index - start_];
    }

    /**
     * @brief Get or insert lane speed limits
     *
     * @param index lane index
     *
     * @return Lane speed limits
     *
     * @throws std::bad_alloc if lane size > LANE_SIZE_VALUE
     */
    LaneSpeedLimits& operator[](LaneIndexType index)
    {
        return lanes_[index - start_];
    }

    /**
     * @brief Get lane speed limits.
     *
     * @param index lane index
     *
     * @return Lane speed limits
     */
    LaneSpeedLimits const& at(LaneIndexType index) const
    {
        return lanes_.at(index - start_);
    }

    /**
     * @brief Get lane speed limits.
     *
     * @param index lane index
     *
     * @return Lane speed limits
     */
    LaneSpeedLimits& at(LaneIndexType index)
    {
        return lanes_.at(index - start_);
    }

    /**
     * @brief Get number of lanes
     *
     * @return lane number
     */
    size_t size() const noexcept
    {
        return lanes_.size();
    }

    /**
     * @brief Clear all lane speed limit info
     */
    void clear() noexcept
    {
        lanes_.clear();
    }

    iterator begin() noexcept
    {
        return lanes_.begin();
    }

    const_iterator begin() const noexcept
    {
        return lanes_.begin();
    }

    const_iterator cbegin() const noexcept
    {
        return lanes_.begin();
    }

    iterator end() noexcept
    {
        return lanes_.end();
    }

    const_iterator end() const noexcept
    {
        return lanes_.end();
    }

    const_iterator cend() const noexcept
    {
        return lanes_.end();
    }

    reverse_iterator rbegin() noexcept
    {
        return lanes_.rbegin();
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return lanes_.rbegin();
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return lanes_.rbegin();
    }

    reverse_iterator rend() noexcept
    {
        return lanes_.rend();
    }

    const_reverse_iterator rend() const noexcept
    {
        return lanes_.rend();
    }

    const_reverse_iterator crend() const noexcept
    {
        return lanes_.rend();
    }

    LaneIndexType GetMinIndex() const noexcept
    {
        return start_;
    }

    LaneIndexType GetMaxIndex() const noexcept
    {
        return end_ - 1U;
    }

    holo::bool_t HasLane(LaneIndexType idx) const noexcept
    {
        return (idx >= start_ && idx < end_);
    }

    /**
     * @brief Get serialized size with given alignment value
     *
     * @tparam ALIGN Buffer alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        size_t serialized_size = holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t));
        for (size_t i = 0U; i < lanes_.size(); ++i)
        {
            serialized_size += holo::serialization::AlignedSize<ALIGN>(sizeof(LaneIndexType) + sizeof(uint8_t)) +
                               holo::serialization::AlignedSize<ALIGN>(lanes_[i].size() * sizeof(SpeedLimitSegment));
        }
        return serialized_size;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << static_cast<holo::uint32_t>(lanes_.size()) << holo::serialization::align;
        for (size_t i = 0U; i < lanes_.size(); ++i)
        {
            serializer << lanes_[i].GetLaneIndex() << static_cast<uint8_t>(lanes_[i].size()) << holo::serialization::align;
            for (size_t j = 0U; j < lanes_[i].size(); ++j)
            {
                serializer << lanes_[i][j].start_distance << lanes_[i][j].end_distance << lanes_[i][j].min_speed
                           << lanes_[i][j].max_speed;
            }
            serializer << holo::serialization::align;
        }
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        clear();
        uint32_t lane_number;
        deserializer >> lane_number >> holo::serialization::align;
        for (size_t i = 0U; i < lane_number; ++i)
        {
            LaneIndexType idx;
            uint8_t       segment_number;
            deserializer >> idx >> segment_number >> holo::serialization::align;

            lanes_.emplace_back(idx);
            LaneSpeedLimits& lane = lanes_.back();
            for (size_t j = 0U; j < segment_number; ++j)
            {
                lane.resize(segment_number);
                deserializer >> lane[j].start_distance >> lane[j].end_distance >> lane[j].min_speed >>
                    lane[j].max_speed;
            }
            deserializer >> holo::serialization::align;
        }
        start_ = lane_number ? lanes_.front().GetLaneIndex() : 0U;
        end_ = lane_number ? lanes_.back().GetLaneIndex() + 1U : 0U;
    }

private:
    LaneIndexType start_;
    LaneIndexType end_;
    ContainerType lanes_;
};

}  // namespace details

using RoadSpeedLimits = details::RoadSpeedLimits<9U, 4U>;

}  // namespace map
}  // namespace holo
#endif

