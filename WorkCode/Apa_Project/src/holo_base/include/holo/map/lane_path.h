/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path.h
 * @brief lane level navigation
 * @author zhouhuishuang(zhouhuishuang@holomaitc.com)
 * @date "2021-05-06"
 */

#ifndef HOLO_MAP_LANE_PATH_H_
#define HOLO_MAP_LANE_PATH_H_

#include <holo/common/road_category.h>
#include <holo/common/road_type.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>

namespace holo
{
namespace map
{
/**
 * @brief LaneItem is used to describe a lane of information
 */
class LaneItem
{
public:
    /**
     * @brief Lane mark class enum
     */
    enum class LaneMark : holo::uint8_t
    {
        UNDEFINED             = 0U,
        STRAIGHT              = 1U,
        STRAIGHT_LEFT         = 2U,
        STRAIGHT_RIGHT        = 3U,
        LEFT                  = 4U,
        RIGHT                 = 5U,
        LEFT_RIGHT            = 6U,
        STRAIGHT_LEFT_RIGHT   = 7U,
        U_TURN                = 8U,
        U_TURN_LEFT           = 9U,
        U_TURN_RIGHT          = 10U,
        U_TURN_STRAIGHT       = 11U,
        U_TURN_STRAIGHT_LEFT  = 12U,
        U_TURN_STRAIGHT_RIGHT = 13U
    };

    /**
     * @brief Lane Model class enum
     */
    enum class LaneModel : holo::uint8_t
    {
        NORMAL           = 1U,
        MERGE_TO         = 2U,
        MERGE_TO_LEFT    = 3U,
        MERGE_TO_RIGHT   = 4U,
        MERGE_FROM       = 5U,
        MERGE_FROM_LEFT  = 6U,
        MERGE_FROM_RIGHT = 7U,
        SPLIT            = 8U,
        SPLIT_LEFT       = 9U,
        SPLIT_RIGHT      = 10U
    };

    /**
     * @brief default constructor
     */
    LaneItem()
      : lane_id_{0}
      , length_{0}
      , road_category_{0}
      , lane_category_{0}
      , lane_mark_{LaneMark::UNDEFINED}
      , lane_model_{LaneModel::NORMAL}
      , is_intersection_{false}
      , start_direction_{0U, 0U}
      , end_direction_{0U, 0U} {}

    /**
     * @brief Construct a new LaneItem object
     *
     * @param lane_id lane id
     * @param length length of the lane
     * @param road_type road type
     * @param lane_type lane type
     * @param lane_mark lane mark
     * @param lane_model lane model
     * @param is_intersection intersection
     * @param start_direction start direction
     * @param end_direction end direction
     */
    [[deprecated]] LaneItem(holo::uint64_t lane_id, holo::float64_t length, holo::common::RoadType road_type,
                            holo::common::LaneType lane_type, LaneMark lane_mark, LaneModel lane_model,
                            holo::bool_t is_intersection, holo::geometry::Point2 start_direction,
                            holo::geometry::Point2 end_direction)
      : lane_id_{lane_id}
      , length_{length}
      , lane_mark_{lane_mark}
      , lane_model_{lane_model}
      , is_intersection_{is_intersection}
      , start_direction_{start_direction}
      , end_direction_{end_direction}
    {
        road_category_.SetValue(road_type.GetValue());
        lane_category_.SetValue(lane_type.GetValue());
    }

    /**
     * @brief Construct a new LaneItem object
     *
     * @param lane_id lane id
     * @param length length of the lane
     * @param road_category road category
     * @param lane_category lane category
     * @param lane_mark lane mark
     * @param lane_model lane model
     * @param is_intersection intersection
     * @param start_direction start direction
     * @param end_direction end direction
     */
    LaneItem(holo::uint64_t lane_id, holo::float64_t length, holo::common::RoadCategory road_category,
             holo::common::LaneCategory lane_category, LaneMark lane_mark, LaneModel lane_model,
             holo::bool_t is_intersection, holo::geometry::Point2 start_direction, holo::geometry::Point2 end_direction)
      : lane_id_{lane_id}
      , length_{length}
      , road_category_{road_category}
      , lane_category_{lane_category}
      , lane_mark_{lane_mark}
      , lane_model_{lane_model}
      , is_intersection_{is_intersection}
      , start_direction_{start_direction}
      , end_direction_{end_direction}
    {
    }

    /**
     * @brief Set lane id
     *
     * @param lane_id
     */
    void SetLaneId(holo::uint64_t const lane_id) noexcept
    {
        lane_id_ = lane_id;
    }

    /**
     * @brief Get the lane id
     *
     * @return uint64_t
     */
    holo::uint64_t GetLaneId() const noexcept
    {
        return lane_id_;
    }

    /**
     * @brief Set length of the lane
     *
     * @param length
     */
    void SetLength(holo::float64_t const length) noexcept
    {
        length_ = length;
    }

    /**
     * @brief Get length of the lane
     *
     * @return float64_t
     */
    holo::float64_t GetLength() const noexcept
    {
        return length_;
    }

    /**
     * @brief Set road type
     *
     * @deprecated Deprecated soon, please use xxx
     *
     * @param road_type
     */
    [[deprecated]] void SetRoadType(holo::common::RoadType const road_type) noexcept
    {
        road_category_.SetValue(road_type.GetValue());
    }

    /**
     * @brief Set road category
     *
     * @param road_category
     */
    void SetRoadCategory(holo::common::RoadCategory const road_category) noexcept
    {
        road_category_ = road_category;
    }

    /**
     * @brief Get road type
     *
     * @deprecated Deprecated soon, please use GetRoadCategory()

     * @return holo::common::RoadType
     */
    [[deprecated]] holo::common::RoadType GetRoadType() const noexcept
    {
        return holo::common::RoadType(road_category_.GetValue());
    }

    /**
     * @brief Get road category
     *
     * @return holo::common::RoadCategory
     */
    holo::common::RoadCategory GetRoadCategory() const noexcept
    {
        return road_category_;
    }

    /**
     * @brief Set lane type
     *
     * @deprecated Deprecated soon, please use SetLaneCategory(LaneCategory const lane_category)
     *
     * @param lane_type
     */
    [[deprecated]] void SetLaneType(holo::common::LaneType const lane_type) noexcept
    {
        lane_category_.SetValue(lane_type.GetValue());
    }

    /**
     * @brief Set lane category
     *
     * @param lane_category
     */
    void SetLaneCategory(holo::common::LaneCategory const lane_category) noexcept
    {
        lane_category_ = lane_category;
    }

    /**
     * @brief Get lane type
     *
     * @deprecated Deprecated soon, please use GetLaneCategory()
     *
     * @return holo::common::LaneType
     */
    [[deprecated]] holo::common::LaneType GetLaneType() const noexcept
    {
        return holo::common::LaneType(lane_category_.GetValue());
    }

    /**
     * @brief Get lane category
     *
     * @return holo::common::LaneCategory
     */
    holo::common::LaneCategory GetLaneCategory() const noexcept
    {
        return lane_category_;
    }

    /**
     * @brief Set lane mark
     *
     * @param lane_mark
     */
    void SetLaneMark(LaneMark const lane_mark) noexcept
    {
        lane_mark_ = lane_mark;
    }

    /**
     * @brief Get lane mark
     *
     * @return LaneMark
     */
    LaneMark GetLaneMark() const noexcept
    {
        return lane_mark_;
    }

    /**
     * @brief Set lane model
     *
     * @param lane_model
     */
    void SetLaneModel(LaneModel const lane_model) noexcept
    {
        lane_model_ = lane_model;
    }

    /**
     * @brief Get lane model
     *
     * @return LaneModel
     */
    LaneModel GetLaneModel() const noexcept
    {
        return lane_model_;
    }

    /**
     * @brief Set start direction
     *
     * @param start_direction
     */
    void SetStartDirection(holo::geometry::Point2 const start_direction) noexcept
    {
        start_direction_ = start_direction;
    }

    /**
     * @brief Get start direction
     *
     * @return holo::geometry::Point2
     */
    holo::geometry::Point2 GetStartDirection() const noexcept
    {
        return start_direction_;
    }

    /**
     * @brief Set end direction
     *
     * @param end_direction
     */
    void SetEndDirection(holo::geometry::Point2 const end_direction) noexcept
    {
        end_direction_ = end_direction;
    }

    /**
     * @brief Get end direction
     *
     * @return holo::geometry::Point2
     */
    holo::geometry::Point2 GetEndDirection() const noexcept
    {
        return end_direction_;
    }

    holo::float64_t GetRotation() const noexcept
    {
        holo::float64_t dot_product =
            start_direction_.GetX() * end_direction_.GetX() + start_direction_.GetY() * end_direction_.GetY();
        holo::float64_t cross_product =
            start_direction_.GetX() * end_direction_.GetY() - start_direction_.GetY() * end_direction_.GetX();
        holo::float64_t start_magnitude =
            std::sqrt(std::pow(start_direction_.GetX(), 2) + std::pow(start_direction_.GetY(), 2));
        holo::float64_t end_magnitude =
            std::sqrt(std::pow(end_direction_.GetX(), 2) + std::pow(end_direction_.GetY(), 2));

        return cross_product > 0 ? std::acos(dot_product / (start_magnitude * end_magnitude)) :
                                   -std::acos(dot_product / (start_magnitude * end_magnitude));
    }

    /**
     * @brief Set intersection flag
     *
     * @param flag
     */
    void SetIntersectionFlag(holo::bool_t const flag)
    {
        is_intersection_ = flag;
    }

    /**
     * @brief is in the intersection or not
     *
     * @return holo::bool_t
     */
    holo::bool_t IsIntersection() const noexcept
    {
        return is_intersection_;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        holo::uint32_t aligned_size = holo::serialization::SerializedSize<ALIGN>(
            lane_id_, length_, static_cast<holo::uint32_t>(road_category_), static_cast<holo::uint32_t>(lane_category_),
            static_cast<holo::uint8_t>(lane_mark_), static_cast<holo::uint8_t>(lane_model_), is_intersection_);
        aligned_size += start_direction_.GetSerializedSize<ALIGN>() + end_direction_.GetSerializedSize<ALIGN>();
        return aligned_size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << lane_id_ << length_ << road_category_ << lane_category_
                   << static_cast<holo::uint8_t>(lane_mark_) << static_cast<holo::uint8_t>(lane_model_)
                   << is_intersection_ << start_direction_ << end_direction_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        holo::uint8_t lane_mark, lane_model;
        deserializer >> holo::serialization::align >> lane_id_ >> length_ >> road_category_ >> lane_category_ >>
            lane_mark >> lane_model >> is_intersection_ >> start_direction_ >> end_direction_;

        lane_mark_  = static_cast<LaneMark>(lane_mark);
        lane_model_ = static_cast<LaneModel>(lane_model);
    }

private:
    holo::uint64_t             lane_id_;
    holo::float64_t            length_;
    holo::common::RoadCategory road_category_;
    holo::common::LaneCategory lane_category_;
    LaneMark                   lane_mark_;
    LaneModel                  lane_model_;
    holo::bool_t               is_intersection_;
    holo::geometry::Point2     start_direction_;
    holo::geometry::Point2     end_direction_;
};

template <size_t LANE_ITEM_SIZE, size_t SEGS = 32U>
class LanePathT : public holo::container::details::VectorBase<LaneItem, LANE_ITEM_SIZE>
{
public:
    static size_t const SEGMENT_SIZE_VALUE = SEGS;
    using Base                             = holo::container::details::VectorBase<LaneItem, LANE_ITEM_SIZE>;

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

    using LaneSpeedLimits = holo::container::Vector<SpeedLimitSegment, SEGMENT_SIZE_VALUE>;

    /**
     * @brief Lane path termination type class enum
     */
    enum class TerminationType : holo::uint8_t
    {
        UNDEFINED        = 0U,
        OUT_SEARCH_RANGE = 1U,
        EXTEND_ROUTE     = 2U,
        NO_SUCCEEDINGS   = 3U
    };

    /**
     * @brief default constructor
     */
    LanePathT()
      : Base{}, id_{0}, sequence_number_{0}, termination_type_{TerminationType::UNDEFINED}, lane_speed_limits_{}
    {
    }

    /**
     * @brief Construct a new LanePath object
     *
     * @param id path id
     * @param sequence_number path sequence number
     * @param termination_type path termination type
     */
    LanePathT(holo::uint64_t const id, holo::int64_t const sequence_number, TerminationType termination_type)
      : Base{}, id_{id}, sequence_number_{sequence_number}, termination_type_{termination_type}, lane_speed_limits_{}
    {
    }

    /**
     * @brief Set id
     *
     * @param id
     */
    void SetId(holo::uint64_t const id) noexcept
    {
        id_ = id;
    }

    /**
     * @brief Get id
     *
     * @return holo::uint64_t
     */
    holo::uint64_t GetId() const noexcept
    {
        return id_;
    }

    /**
     * @brief Set path sequence number
     *
     * @param seq
     */
    void SetSequenceNumber(holo::int64_t const seq) noexcept
    {
        sequence_number_ = seq;
    }

    /**
     * @brief Get path sequence number
     *
     * @return holo::int64_t
     */
    holo::int64_t GetSequenceNumber() const noexcept
    {
        return sequence_number_;
    }

    /**
     * @brief Set termination type
     *
     * @param termination_type
     */
    void SetTerminationType(TerminationType const termination_type) noexcept
    {
        termination_type_ = termination_type;
    }

    /**
     * @brief Get termination type
     *
     * @return TerminationType
     */
    TerminationType GetTerminationType() const noexcept
    {
        return termination_type_;
    }

    /**
     * @brief Get lane speed limits
     *
     * @return const reference to Lane speed limits object
     */
    LaneSpeedLimits const& GetLaneSpeedLimits() const noexcept
    {
        return lane_speed_limits_;
    }

    /**
     * @brief Get lane speed limits
     *
     * @return reference to Lane speed limits object
     */
    LaneSpeedLimits& GetLaneSpeedLimits() noexcept
    {
        return lane_speed_limits_;
    }

    /**
     * @brief Set lane speed limits
     *
     * @param lane_speed_limits lane speed limits object
     */
    void SetLaneSpeedLimits(LaneSpeedLimits const& lane_speed_limits) noexcept
    {
        lane_speed_limits_ = lane_speed_limits;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        uint32_t size = this->lane_speed_limits_.size();
        return Base::template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(id_, sequence_number_, termination_type_, size) +
               holo::serialization::AlignedSize<ALIGN>(size * sizeof(SpeedLimitSegment));
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        Base::template Serialize(serializer);
        serializer << id_ << sequence_number_ << static_cast<uint8_t>(termination_type_)
                   << static_cast<uint32_t>(lane_speed_limits_.size()) << holo::serialization::align;
        for (size_t i = 0U; i < lane_speed_limits_.size(); ++i)
        {
            serializer << lane_speed_limits_[i].start_distance << lane_speed_limits_[i].end_distance
                       << lane_speed_limits_[i].min_speed << lane_speed_limits_[i].max_speed;
        }
        serializer << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t size             = 0U;
        uint8_t  termination_type = 0U;
        Base::template Deserialize(deserializer);
        deserializer >> id_ >> sequence_number_ >> termination_type >> size >> holo::serialization::align;

        this->lane_speed_limits_.clear();
        this->lane_speed_limits_.resize(size);
        for (size_t i = 0U; i < size; ++i)
        {
            deserializer >> lane_speed_limits_[i].start_distance >> lane_speed_limits_[i].end_distance >>
                lane_speed_limits_[i].min_speed >> lane_speed_limits_[i].max_speed;
        }
        termination_type_ = static_cast<TerminationType>(termination_type);
        deserializer >> holo::serialization::align;
    }

private:
    holo::uint64_t  id_;
    holo::int64_t   sequence_number_;
    TerminationType termination_type_;
    LaneSpeedLimits lane_speed_limits_;
};

template <size_t LANE_PATH_SIZE, size_t LANE_ITEM_SIZE, size_t SEGS = 32U>
class AdviceT
{
public:
    using LanePathType = LanePathT<LANE_ITEM_SIZE, SEGS>;

    /**
     * @brief default constructor
     */
    AdviceT() : lane_paths_{}
    {
    }

    /**
     * @brief Clear lane paths
     *
     * @return none
     */
    void ClearLanePaths() const noexcept
    {
        lane_paths_.clear();
    }

    /**
     * @brief Get lane paths size
     *
     * @return size_t
     */
    size_t GetLanePathSize() const noexcept
    {
        return lane_paths_.size();
    }

    /**
     * @brief PushBack lane path
     *
     * @param lane_path
     */
    void PushBackLanePath(LanePathType const& lane_path)
    {
        lane_paths_.push_back(lane_path);
    }

    /**
     * @brief Get lane path
     * @param index lane paths index
     * @return LanePathType
     */
    LanePathType const& GetLanePath(size_t index) const noexcept
    {
        return lane_paths_.at(index);
    }

    /**
     * @brief Get lane paths
     *
     * @return holo::container::Vector<LanePathType, LANE_PATH_SIZE> const& reference oflane_paths
     */
    holo::container::Vector<LanePathType, LANE_PATH_SIZE> const& GetLanePaths() const noexcept
    {
        return lane_paths_;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return lane_paths_.template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        lane_paths_.template Serialize(serializer);
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        lane_paths_.template Deserialize(deserializer);
    }

private:
    holo::container::Vector<LanePathType, LANE_PATH_SIZE> lane_paths_;
};
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_LANE_PATH_H_ */
