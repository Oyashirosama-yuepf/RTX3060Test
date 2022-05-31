/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane2.h
 * @brief This header file defines Lane object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-07
 */

#ifndef HOLO_COMMON_LANE2_H_
#define HOLO_COMMON_LANE2_H_

#include <holo/common/lane_boundary2.h>
#include <holo/common/road_category.h>
#include <holo/common/road_type.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <array>

namespace holo
{
namespace common
{
/**
 * @brief Lane object
 *
 * @tparam Curve curve type
 */
template <typename Curve>
class Lane
{
public:
    using CurveType                = Curve;
    using BoundaryType             = holo::common::LaneBoundary<CurveType>;
    using PointType                = typename CurveType::PointType;
    using ScalarType               = typename CurveType::ScalarType;
    static size_t const SIZE_VALUE = CurveType::SIZE_VALUE;

    struct MapAttributes
    {
        MapAttributes() : center_points{}, conflict_path_indexes{}, crosswalks{}, stop_lines{} {};

        ~MapAttributes() noexcept {};

        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            uint32_t count;

            size_t aligned_size = center_points.template GetSerializedSize<ALIGN>() +
                                  conflict_path_indexes.template GetSerializedSize<ALIGN>();

            count = crosswalks.size();
            aligned_size += holo::serialization::AlignedSize<ALIGN>(
                sizeof(count) + crosswalks[0][0].template GetSerializedSize<ALIGN>() * 4 * count);

            count = stop_lines.size();
            aligned_size += holo::serialization::AlignedSize<ALIGN>(
                sizeof(count) + stop_lines[0][0].template GetSerializedSize<ALIGN>() * 2 * count);

            return aligned_size;
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << center_points << conflict_path_indexes;

            uint32_t count = crosswalks.size();
            serializer << count;
            for (size_t i = 0; i < count; ++i)
            {
                for (size_t j = 0; j < 4U; ++j)
                {
                    serializer << crosswalks[i][j];
                }
            }

            count = stop_lines.size();
            serializer << count;
            for (size_t i = 0; i < count; ++i)
            {
                for (size_t j = 0; j < 2U; ++j)
                {
                    serializer << stop_lines[i][j];
                }
            }
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            uint32_t count = 0;
            deserializer >> center_points >> conflict_path_indexes;

            deserializer >> count;
            crosswalks.clear();
            crosswalks.resize(count);
            for (size_t i = 0; i < count; ++i)
            {
                for (size_t j = 0; j < 4U; ++j)
                {
                    deserializer >> crosswalks[i][j];
                }
            }

            deserializer >> count;
            stop_lines.clear();
            stop_lines.resize(count);
            for (size_t i = 0; i < count; ++i)
            {
                for (size_t j = 0; j < 2U; ++j)
                {
                    deserializer >> stop_lines[i][j];
                }
            }
        }

        holo::container::Vector<PointType, SIZE_VALUE>                        center_points;
        holo::container::Vector<holo::uint8_t, 16U>                           conflict_path_indexes;
        holo::container::Vector<std::array<holo::geometry::Point2d, 4U>, 16U> crosswalks;
        holo::container::Vector<std::array<holo::geometry::Point2d, 2U>, 16U> stop_lines;
    };

    /**
     * @brief Default constructor
     */
    Lane(uint32_t index)
      : left_bound_{}
      , right_bound_{}
      , index_{index}
      , external_id_{}
      , speed_limit_min_{}
      , speed_limit_max_{}
      , length_{}
      , road_category_{}
      , lane_category_{}
      , map_attributes_{}
    {
    }

    /**
     * @brief Default constructor
     */
    Lane(uint32_t index, std::shared_ptr<BoundaryType> left, std::shared_ptr<BoundaryType> right)
      : left_bound_{left}
      , right_bound_{right}
      , index_{index}
      , external_id_{}
      , speed_limit_min_{}
      , speed_limit_max_{}
      , length_{}
      , road_category_{}
      , lane_category_{}
      , map_attributes_{}
    {
    }

    /**
     * @brief Set left boundary
     *
     * @param bound Reference to boundary object.
     */
    void SetLeftBoundary(std::shared_ptr<BoundaryType> bound) noexcept
    {
        left_bound_ = bound;
    }

    /**
     * @brief Reset left boundary
     */
    void ResetLeftBoundary() noexcept
    {
        left_bound_ = nullptr;
    }

    /**
     * @brief Check if a lane has left boundary
     *
     * @return True if left boundary is set.
     */
    bool_t HasLeftBoundary() const noexcept
    {
        return (left_bound_ != nullptr);
    }

    /**
     * @brief Get left boundary
     *
     * @return Reference to left boundary
     */
    BoundaryType& GetLeftBoundary() noexcept
    {
        return *left_bound_;
    }

    /**
     * @brief Get left boundary
     *
     * @return Reference to left boundary
     */
    BoundaryType const& GetLeftBoundary() const noexcept
    {
        return *left_bound_;
    }

    /**
     * @brief Set right boundary
     *
     * @param bound Reference to boundary object.
     */
    void SetRightBoundary(std::shared_ptr<BoundaryType> bound) noexcept
    {
        right_bound_ = bound;
    }

    /**
     * @brief Reset right boundary
     */
    void ResetRightBoundary() noexcept
    {
        right_bound_ = nullptr;
    }

    /**
     * @brief Check if a lane has right boundary
     *
     * @return True if right boundary is set.
     */
    bool_t HasRightBoundary() const noexcept
    {
        return (right_bound_ != nullptr);
    }

    /**
     * @brief Get right boundary
     *
     * @return Reference to left boundary
     */
    BoundaryType& GetRightBoundary() noexcept
    {
        return *right_bound_;
    }

    /**
     * @brief Get right boundary
     *
     * @return Reference to left boundary
     */
    BoundaryType const& GetRightBoundary() const noexcept
    {
        return *right_bound_;
    }

    /**
     * @brief Set external id
     *
     * @param id External id.
     */
    void SetExternalId(uint64_t id) noexcept
    {
        external_id_ = id;
    }

    /**
     * @brief Get external id
     *
     * @return External id
     */
    uint64_t GetExternalId() const noexcept
    {
        return external_id_;
    }

    /**
     * @brief Get lane speed limit
     *
     * @return min_speed and max_speed pair
     */
    std::pair<uint16_t, uint16_t> GetSpeedLimit() const noexcept
    {
        return std::pair<uint16_t, uint16_t>(speed_limit_min_, speed_limit_max_);
    }

    /**
     * @brief Get lane min speed limit
     *
     * @return min_speed
     */
    uint16_t GetMinSpeedLimit() const noexcept
    {
        return speed_limit_min_;
    }

    /**
     * @brief Get lane max speed limit
     *
     * @return max_speed
     */
    uint16_t GetMaxSpeedLimit() const noexcept
    {
        return speed_limit_max_;
    }

    /**
     * @brief Set speed limits in km/h
     *
     * @param min min speed limit
     * @param max max speed limit
     */
    void SetSpeedLimit(uint16_t min, uint16_t max) noexcept
    {
        speed_limit_min_ = min;
        speed_limit_max_ = max;
    }

    /**
     * @brief Get lane length. unit: m
     *
     * @return length
     */
    ScalarType GetLength() const noexcept
    {
        return length_;
    }

    /**
     * @brief Set lane length. unit: m
     *
     * @param length lane length
     */
    void SetLength(ScalarType length) noexcept
    {
        length_ = length;
    }

    /**
     * @brief Get road type.
     *
     * @deprecated Deprecated soon, please use GetRoadCategory()
     *
     * @return road type
     */
    [[deprecated]] RoadType GetRoadType() const noexcept
    {
        return RoadType(road_category_.GetValue());
    }

    /**
     * @brief Get road category.
     *
     * @return road category
     */
    RoadCategory GetRoadCategory() const noexcept
    {
        return road_category_;
    }

    /**
     * @brief Set road type.
     *
     * @deprecated Deprecated soon, please use SetRoadCategory(RoadCategory road_category)
     *
     * @param road_type road type.
     */
    [[deprecated]] void SetRoadType(RoadType road_type) noexcept
    {
        road_category_.SetValue(road_type.GetValue());
    }

    /**
     * @brief Set road category.
     *
     * @param road_category road category.
     */
    void SetRoadCategory(RoadCategory road_category) noexcept
    {
        road_category_ = road_category;
    }

    /**
     * @brief Get lane type.
     *
     * @deprecated Deprecated soon, please use GetLaneCategory()
     *
     * @return lane type
     */
    [[deprecated]] LaneType GetLaneType() const noexcept
    {
        return LaneType(lane_category_.GetValue());
    }

    /**
     * @brief Get lane category.
     *
     * @return lane category
     */
    LaneCategory GetLaneCategory() const noexcept
    {
        return lane_category_;
    }

    /**
     * @brief Set lane type.
     *
     * @deprecated Deprecated soon, please use SetLaneCategory(LaneCategory lane_category)
     *
     * @param lane_type lane type.
     */
    [[deprecated]] void SetLaneType(LaneType lane_type) noexcept
    {
        lane_category_.SetValue(lane_type.GetValue());
    }

    /**
     * @brief Set lane category.
     *
     * @param lane_category lane category.
     */
    void SetLaneCategory(LaneCategory lane_category) noexcept
    {
        lane_category_ = lane_category;
    }

    /**
     * @brief Get map attributes size
     *
     * @return map attributes size
     */
    const MapAttributes& GetMapAttributes() const noexcept
    {
        return map_attributes_;
    }

    /**
     * @brief Set map attributes
     *
     * @param map_attributes map attributes
     */
    void SetMapAttributes(MapAttributes const& map_attributes) noexcept
    {
        map_attributes_ = map_attributes;
    }

    /**
     * @brief Get required buffer size to serialize this object
     *
     * @tparam S Class that used to serializing this object
     * @param serializer the instance of Serializer
     *
     * @return Required buffer size
     */
    template <typename S>
    size_t GetSerializedAttributesSize(S const& serializer) const noexcept
    {
        constexpr size_t Alignment = S::GetAlignment();

        size_t aligned_size =
            sizeof(external_id_) + sizeof(speed_limit_min_) + sizeof(speed_limit_max_) + sizeof(length_);
        aligned_size += road_category_.GetSerializedSize(serializer);
        aligned_size += lane_category_.GetSerializedSize(serializer);
        aligned_size += map_attributes_.GetSerializedSize(serializer);
        return holo::serialization::AlignedSize<Alignment>(aligned_size);
    }

    template <size_t ALIGN>
    size_t GetSerializedAttributesSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(sizeof(external_id_) + sizeof(speed_limit_min_) +
                                                       sizeof(speed_limit_max_) + sizeof(length_)) +
               road_category_.GetSerializedSize<ALIGN>() + lane_category_.GetSerializedSize<ALIGN>() +
               map_attributes_.template GetSerializedSize<ALIGN>();
    }

    template <typename S>
    void SerializeAttributes(S& serializer) const
    {
        serializer << external_id_ << speed_limit_min_ << speed_limit_max_ << length_ << road_category_
                   << lane_category_ << map_attributes_ << holo::serialization::align;
    }

    template <typename D>
    void DeserializeAttributes(D& deserializer)
    {
        deserializer >> external_id_ >> speed_limit_min_ >> speed_limit_max_ >> length_ >> road_category_ >>
            lane_category_ >> map_attributes_ >> holo::serialization::align;
    }

    /**
     * @brief Get left boundary
     *
     * @return Reference to left boundary
     */
    std::shared_ptr<BoundaryType> GetLeftBoundaryPtr() noexcept
    {
        return left_bound_;
    }

    /**
     * @brief Get left boundary
     *
     * @return Reference to left boundary
     */
    std::shared_ptr<BoundaryType const> GetLeftBoundaryPtr() const noexcept
    {
        return left_bound_;
    }

    /**
     * @brief Get right boundary
     *
     * @return Reference to left boundary
     */
    std::shared_ptr<BoundaryType> GetRightBoundaryPtr() noexcept
    {
        return right_bound_;
    }

    /**
     * @brief Get right boundary
     *
     * @return Reference to left boundary
     */
    std::shared_ptr<BoundaryType const> GetRightBoundaryPtr() const noexcept
    {
        return right_bound_;
    }

    uint32_t GetIndex() const noexcept
    {
        return index_;
    }

    void SetIndex(uint32_t index) noexcept
    {
        index_ = index;
    }

private:
    std::shared_ptr<BoundaryType> left_bound_;
    std::shared_ptr<BoundaryType> right_bound_;

    uint32_t index_;

    uint64_t external_id_;
    uint16_t speed_limit_min_;
    uint16_t speed_limit_max_;

    ScalarType length_;

    RoadCategory road_category_;
    LaneCategory lane_category_;

    MapAttributes map_attributes_;

    // TODO Add lane marks
};

}  // namespace common
}  // namespace holo
#endif
