/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file advice.h
 * @brief Advice messages.
 * @author zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#ifndef HOLO_MAP_ADVICE_H_
#define HOLO_MAP_ADVICE_H_

#include <memory>
#include <vector>

#include <holo/common/coordinate.h>
#include <holo/common/road_frame2.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point3.h>
#include <holo/map/common_def.h>
#include <holo/map/map_enum.h>
#include <holo/map/map_msg_base.h>
#include "road_speed_limits.h"

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @brief CrossingInfo
 *
 */
struct CrossingInfo
{
    ::holo::map::CrossingType crossing_type = ::holo::map::CrossingType::NO_MODEL;
    ::holo::float64_t         distance      = ::std::numeric_limits<::holo::float64_t>::max();

    /**
     * @brief Whether or not both objects are equal.
     *
     * @param[in] obj Another object.
     * @return true: Current object equals another object.
     *         false: Otherwise.
     */
    bool operator==(CrossingInfo const& obj) const
    {
        return crossing_type == obj.crossing_type && std::fabs(distance - obj.distance) < 0.000001;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(static_cast<holo::uint8_t>(crossing_type), distance);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << static_cast<holo::uint8_t>(crossing_type) << distance
                   << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        holo::uint8_t value = 0;
        deserializer >> holo::serialization::align >> value >> distance >> holo::serialization::align;
        crossing_type = static_cast<holo::map::CrossingType>(value);
    }
};

/**
 * @brief Target advice info in lane level.
 */
typedef struct TargetLaneAdviceType
{
    /**
     * @brief Format object to a JSON string.
     *
     * @param[in] obj A object of TargetLaneAdviceType.
     * @return Return a JSON string.
     */
    static std::string FormatToString(const TargetLaneAdviceType& obj)
    {
        std::stringstream stream;
        stream << "{\"valid\":" << obj.valid << ", \"lane_id\":" << obj.lane_id
               << ", \"lane_type\":" << static_cast<int>(obj.lane_type) << ", \"lane_type_str\":"
               << "\"" << CommonLaneTypeName[static_cast<int>(obj.lane_type)] << "\""
               << ", \"type_with_left\":" << static_cast<int>(obj.type_with_left) << ", \"type_with_left_desc\":"
               << "\"" << CommonLaneTransTypeName[static_cast<int>(obj.type_with_left)] << "\""
               << ", \"type_with_right\":" << static_cast<int>(obj.type_with_right) << ", \"type_with_right_desc\":"
               << "\"" << CommonLaneTransTypeName[static_cast<int>(obj.type_with_right)] << "\""
               << ", \"type_with_current\":" << static_cast<int>(obj.type_with_current)
               << ", \"type_with_current_desc\":"
               << "\"" << CommonLaneTransTypeName[static_cast<int>(obj.type_with_current)] << "\""
               << "}";
        return stream.str();
    }

    CommonLaneTransType type_with_left    = CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE;
    CommonLaneTransType type_with_right   = CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE;
    CommonLaneTransType type_with_current = CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE;

    KeyValue       lane_id   = 0UL;
    CommonLaneType lane_type = CommonLaneType::LANE_TYPE_UNDEFINED;

    /// Check if this lane is available.
    bool valid = false;

    /**
     * @brief Whether or not both objects are equal.
     *
     * @param[in] obj Another object.
     * @return true: Current object equals another object.
     *         false: Otherwise.
     */
    bool operator==(TargetLaneAdviceType const& obj) const
    {
        return type_with_left == obj.type_with_left && type_with_right == obj.type_with_right &&
               type_with_current == obj.type_with_current && lane_type == obj.lane_type && lane_id == obj.lane_id &&
               valid == obj.valid;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(
            static_cast<holo::uint8_t>(type_with_left), static_cast<holo::uint8_t>(type_with_right),
            static_cast<holo::uint8_t>(type_with_current), static_cast<holo::uint8_t>(lane_type),
            static_cast<holo::uint64_t>(lane_id), static_cast<holo::uint8_t>(valid));
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << static_cast<holo::uint8_t>(type_with_left)
                   << static_cast<holo::uint8_t>(type_with_right) << static_cast<holo::uint8_t>(type_with_current)
                   << static_cast<holo::uint8_t>(lane_type) << static_cast<holo::uint64_t>(lane_id)
                   << static_cast<holo::uint8_t>(valid) << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        holo::uint8_t  left_value    = 0;
        holo::uint8_t  right_value   = 0;
        holo::uint8_t  current_value = 0;
        holo::uint8_t  type          = 0;
        holo::uint64_t id            = 0;
        holo::uint8_t  v             = false;

        deserializer >> holo::serialization::align >> left_value >> right_value >> current_value >> type >> id >> v >>
            holo::serialization::align;

        type_with_left    = static_cast<holo::map::CommonLaneTransType>(left_value);
        type_with_right   = static_cast<holo::map::CommonLaneTransType>(right_value);
        type_with_current = static_cast<holo::map::CommonLaneTransType>(current_value);
        lane_type         = static_cast<holo::map::CommonLaneType>(type);
        lane_id           = id;
        valid             = v;
    }
} TargetLaneAdvice;

/**
 * @brief Target advice group in lane level.
 */
typedef struct TargetLaneAdviceGroupType
{
    /**
     * @brief Format object to a JSON string.
     *
     * @param[in] group A object of TargetLaneAdviceGroupType.
     * @return Returns a JSON string.
     */
    static std::string FormatToString(const TargetLaneAdviceGroupType& group)
    {
        std::stringstream stream;
        stream << "{\"link_id\":" << group.link_id << ", \"link_type\":" << static_cast<int>(group.link_type)
               << ", \"link_type_str\":"
               << "\"" << CommonLinkTypeName[static_cast<int>(group.link_type)] << "\""
               << ", \"left_lane_advice\":" << TargetLaneAdvice::FormatToString(group.left_lane_advice)
               << ", \"right_lane_advice\":" << TargetLaneAdvice::FormatToString(group.right_lane_advice)
               << ", \"current_lane_advice\":" << TargetLaneAdvice::FormatToString(group.current_lane_advice) << "}";
        return stream.str();
    }

    TargetLaneAdvice left_lane_advice;
    TargetLaneAdvice right_lane_advice;
    TargetLaneAdvice current_lane_advice;

    KeyValue       link_id   = 0UL;
    CommonLinkType link_type = CommonLinkType::LINK_TYPE_UNDEFINED;

    float32_t confidence = 0.0f;

    /**
     * @brief Whether or not both objects are equal.
     *
     * @param[in] obj Another object.
     * @return true: Current object equals another object.
     *         false: Otherwise.
     */
    bool operator==(TargetLaneAdviceGroupType const& obj) const
    {
        return left_lane_advice == obj.left_lane_advice && right_lane_advice == obj.right_lane_advice &&
               current_lane_advice == obj.current_lane_advice && link_type == obj.link_type && link_id == obj.link_id &&
               std::fabs(confidence - obj.confidence) < 0.000001;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(link_id, static_cast<holo::uint8_t>(link_type), confidence) +
               left_lane_advice.GetSerializedSize<ALIGN>() + right_lane_advice.GetSerializedSize<ALIGN>() +
               current_lane_advice.GetSerializedSize<ALIGN>();
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << link_id << static_cast<holo::uint8_t>(link_type) << confidence
                   << left_lane_advice << right_lane_advice << current_lane_advice;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        holo::uint8_t value = 0;
        deserializer >> holo::serialization::align >> link_id >> value >> confidence >> left_lane_advice >>
            right_lane_advice >> current_lane_advice;
        link_type = static_cast<holo::map::CommonLinkType>(value);
    }

} TargetLaneAdviceGroup;

/**
 * @brief Target advice info in link level.
 */
typedef struct TargetLinkAdviceType
{
    /**
     * @brief Format object to a JSON string.
     *
     * @param[in] obj A object of TargetLinkAdviceType.
     * @return Returns a JSON string.
     */
    static std::string FormatToString(const TargetLinkAdviceType& obj)
    {
        std::stringstream stream;
        stream << "{\"type\":" << static_cast<int>(obj.type) << ", \"description\":"
               << "\"" << CrossingTypeName[static_cast<int>(obj.type)] << "\""
               << ", \"distance_to_start\":" << obj.distance_to_start << ", \"distance_to_end\":" << obj.distance_to_end
               << ", \"link_id\":" << obj.link_id << "}";
        return stream.str();
    }

    CrossingType type = CrossingType::NO_MODEL;

    /// It's the distance between current position and start or end point of the target crossing type.
    /// |[1]-------------[2]-----------[3]|
    /// If [1] is current position, [2] and [3] are start point and end point, distance_to_start and distance_to_end
    /// are both positive.
    /// If [2] is current position, [1] and [3] are start point and end point, the distance_to_start is negative,
    /// the distance_to_end is positive.
    /// If [3] is current position, [1] and [2] are start point and end point, distance_to_start and distance_to_end
    /// are both negative.
    float64_t distance_to_start = 0.0f;
    float64_t distance_to_end   = 0.0f;
    /// This parameter is not used now, always be 1.0.
    float32_t confidence = 0.0f;

    KeyValue link_id = 0UL;

    /**
     * @brief Whether or not both objects are equal.
     *
     * @param[in] obj Another object.
     * @return true: Current object equals another object.
     *         false: Otherwise.
     */
    bool operator==(TargetLinkAdviceType const& obj) const
    {
        return type == obj.type && link_id == obj.link_id &&
               std::fabs(distance_to_start - obj.distance_to_start) < 0.000001 &&
               std::fabs(distance_to_end - obj.distance_to_end) < 0.000001 &&
               std::fabs(confidence - obj.confidence) < 0.000001;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(static_cast<holo::uint8_t>(type), distance_to_start,
                                                          distance_to_end, confidence, link_id);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << static_cast<holo::uint8_t>(type) << distance_to_start
                   << distance_to_end << confidence << link_id << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        holo::uint8_t value;
        deserializer >> holo::serialization::align >> value >> distance_to_start >> distance_to_end >> confidence >>
            link_id >> holo::serialization::align;
        type = static_cast<holo::map::CrossingType>(value);
    }
} TargetLinkAdvice;

/**
 * @brief Target advice group in link level.
 */
typedef struct TargetLinkAdviceGroupType
{
    /**
     * @brief Format a object to a JSON string.
     *
     * @param[in] group A object of TargetLinkAdviceGroupType.
     * @return Returns a JSON string.
     */
    static std::string FormatToString(const TargetLinkAdviceGroupType& group)
    {
        std::stringstream stream;
        stream << "[";
        const std::size_t count = group.advices.size();
        for (std::size_t i = 0; i < count; ++i)
        {
            const std::string end = (i + 1) < count ? ", " : "";
            stream << TargetLinkAdvice::FormatToString(group.advices[i]) << end;
        }
        stream << "]";
        return stream.str();
    }

    std::vector<TargetLinkAdvice> advices;

    /**
     * @brief Whether or not both objects are equal.
     *
     * @param[in] obj Another object.
     * @return true: Current object equals another object.
     *         false: Otherwise.
     */
    bool operator==(TargetLinkAdviceGroupType const& obj) const
    {
        if (advices.size() != obj.advices.size())
        {
            return false;
        }

        std::size_t const count = advices.size();
        for (std::size_t i = 0; i < count; ++i)
        {
            if (advices[i] == obj.advices[i])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        size_t size           = advices.size();
        size_t serialize_size = holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(size));
        if (size > 0)
        {
            serialize_size += size * advices[0].GetSerializedSize<ALIGN>();
        }
        return serialize_size;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        uint32_t count = advices.size();
        serializer << holo::serialization::align << count << holo::serialization::align;

        for (std::size_t i = 0; i < count; ++i)
        {
            serializer << advices[i];
        }
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t count;
        deserializer >> holo::serialization::align >> count >> holo::serialization::align;

        advices.resize(count);
        for (std::size_t i = 0; i < count; ++i)
        {
            deserializer >> advices[i];
        }
    }
} TargetLinkAdviceGroup;

/**
 * @brief Advice message
 *
 */
class Advice : public MapMsgBase
{
public:
    using PtrAdvice = ::std::shared_ptr<Advice>;

    static size_t const MAX_KNOT_NUMBER   = 0U;    ///< Maximum knot number of a curve
    static size_t const ROAD_FRAME_DEGREE = 3U;    ///< Curve dimension
    static size_t const MAX_CURVE_NUMBER  = 256U;  ///< Maximum graph node number of a RoadFrame.

    using RoadFrameCurveType =
        ::holo::geometry::CurvePolynomial<holo::geometry::Point3d, MAX_KNOT_NUMBER, ROAD_FRAME_DEGREE>;
    using RoadFrameType = ::holo::common::RoadFrame<RoadFrameCurveType, MAX_CURVE_NUMBER>;

public:
    /**
     * @brief Constructor
     */
    Advice() noexcept
      : MapMsgBase(static_cast<::holo::uint8_t>(AdviceInfoIndicatorType::ADVICE_INFO_INDICATOR_MAX),
                   static_cast<::holo::uint8_t>(AdviceValuesUint32::ADVICE_VALUES_UINT32_MAX),
                   static_cast<::holo::uint8_t>(AdviceValuesFloat32::ADVICE_VALUES_FLOAT_MAX))
      , timestamp_{}
      , crossing_sequence_list_{}
      , current_lane_seq_list_{}
      , vec_crossing_info_{}
      , link_advices_{}
      , lane_advices_{}
      , road_speed_limits_{}
      , logic_graph_{}
    {
    }

    /**
     * @brief Destructor
     */
    ~Advice() = default;

    /**
     * @brief Copy constructor
     *
     * @param[in] other
     */
    Advice(const Advice& other) = default;

    /**
     * @brief Copy constructor as right value
     *
     * @param[in] other
     */
    Advice(Advice&& other) = default;

    /**
     * @brief Operator assignment
     *
     * @param[in] other
     * @return Advice&
     */
    Advice& operator=(const Advice& other) = default;

    /**
     * @brief Operator assignment as rvalue
     *
     * @param[in] other
     * @return Advice&
     */
    Advice& operator=(Advice&& other) = default;

    /**
     * @brief Clear advice
     */
    void Clear()
    {
        MapMsgBase::Clear();
        this->timestamp_.SetSec(0U);
        this->timestamp_.SetNsec(0U);
        this->crossing_sequence_list_.clear();
        this->current_lane_seq_list_.clear();
        this->vec_crossing_info_.clear();
        this->link_advices_.advices.clear();
        this->lane_advices_ = TargetLaneAdviceGroup();
    }

    /**
     * @brief Get Timestamp
     *
     * @return timestamp
     */
    const holo::common::Timestamp& GetTimestamp() const noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Set timestamp
     *
     * @param[in] timestamp timestamp
     */
    void SetTimestamp(const holo::common::Timestamp& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief set remaining distance to crossing, unit is metre
     * @param[in] dis remaining distance
     */
    void SetDistanceToNextCrossing(const ::holo::float32_t dis) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(AdviceValuesFloat32::REMAINING_DISTANCE)] = dis;
    }

    /**
     * @brief get remaining distance to crossing
     * @return remaining distance to crossing
     */
    ::holo::float32_t GetDistanceToNextCrossing() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(AdviceValuesFloat32::REMAINING_DISTANCE)];
    }

    /**
     * @brief set sequence of next crossing
     * Current lane sequence id constant equal to zero, left lanes allways less than zero, right lanes allways more than
     * zero.
     * @param[in] sequence_list
     */
    void SetSequenceOfNextCrossing(const ::std::vector<SeqValue>& sequence_list) noexcept
    {
        this->crossing_sequence_list_ = sequence_list;
    }

    /**
     * @brief set sequence of next crossing as rvalue
     * Current lane sequence id constant equal to zero, left lanes allways less than zero, right lanes allways more than
     * zero.
     * @param[in] sequence_list
     */
    void SetSequenceOfNextCrossing(::std::vector<SeqValue>&& sequence_list) noexcept
    {
        ::std::swap(this->crossing_sequence_list_, sequence_list);
    }

    /**
     * @brief get sequence of next crossing as const reference
     * Current lane sequence id constant equal to zero, left lanes allways less than zero, right lanes allways more than
     * zero.
     * @return sequence of next crossing as const reference
     */
    const ::std::vector<SeqValue>& GetSequenceOfNextCrossing() const noexcept
    {
        return this->crossing_sequence_list_;
    }
    /**
     * @brief get sequence of next crossing as  reference
     * Current lane sequence id constant equal to zero, left lanes allways less than zero, right lanes allways more than
     * zero.
     * @return sequence of next crossing as  reference
     */
    ::std::vector<SeqValue>& GetSequenceOfNextCrossing() noexcept
    {
        return this->crossing_sequence_list_;
    }

    /**
     * @brief Set current lane sequence list on current link.
     *      Current lane sequence id constant equal to zero, left lanes allways less than zero, right lanes allways more
     *      than zero.
     * @param[in] seq_list
     */
    void SetCurrentLaneSequence(const ::std::vector<SeqValue>& seq_list) noexcept
    {
        this->current_lane_seq_list_ = seq_list;
    }

    /**
     * @brief Set current lane sequence list on current link as rvalue
     * Current lane sequence id constant equal to zero, left lanes allways less than zero, right lanes allways more than
     * zero.
     * @param[in] seq_list
     */
    void SetCurrentLaneSequence(::std::vector<SeqValue>&& seq_list) noexcept
    {
        ::std::swap(this->current_lane_seq_list_, seq_list);
    }

    /**
     * @brief Get current lane sequence list on current link as const reference
     * Current lane sequence id constant equal to zero, left lanes allways less than zero, right lanes allways more than
     * zero.
     * @return current lane sequence list on current link as const reference
     */
    const ::std::vector<SeqValue>& GetCurrentLaneSequence() const noexcept
    {
        return this->current_lane_seq_list_;
    }

    /**
     * @brief Get current lane sequence list on current link as reference
     * Current lane sequence id constant equal to zero, left lanes seq allways less than zero, right lanes seq allways
     * more than zero.
     * @return current lane sequence list on current link as reference
     */
    ::std::vector<SeqValue>& GetCurrentLaneSequence() noexcept
    {
        return this->current_lane_seq_list_;
    }

    [[deprecated]] ::holo::float32_t GetSpeedLimitOfCurrentLane() const noexcept
    {
        /// @todo fix default speed limit
        return road_speed_limits_.HasLane(0U) ? road_speed_limits_[0U].size() > 0U ?
                                                road_speed_limits_[0U][0U].max_speed :
                                                std::numeric_limits<holo::float32_t>::max() :
                                                std::numeric_limits<holo::float32_t>::max();
    }

    [[deprecated]] ::holo::float32_t GetCrossingSpeedAhead() const noexcept
    {
        if (!road_speed_limits_.HasLane(0U))
        {
            return std::numeric_limits<holo::float32_t>::max();
        }
        size_t segs = road_speed_limits_[0U].size();
        if (segs < 2U)
        {
            return std::numeric_limits<holo::float32_t>::max();
        }
        holo::float32_t current_limit = road_speed_limits_[0U][0U].max_speed;
        for (size_t i = 1U; i < segs; ++i)
        {
            if (ScalarEqualT<holo::float32_t>()(road_speed_limits_[0U][i].max_speed, current_limit))
            {
                return road_speed_limits_[0U][i].max_speed;
            }
        }
        return std::numeric_limits<holo::float32_t>::max();
    }

    [[deprecated]] ::holo::float32_t GetDistanceToSpeedLimitChange() const noexcept
    {
        if (!road_speed_limits_.HasLane(0U))
        {
            return std::numeric_limits<holo::float32_t>::max();
        }
        size_t segs = road_speed_limits_[0U].size();
        if (segs < 2U)
        {
            return std::numeric_limits<holo::float32_t>::max();
        }
        holo::float32_t current_limit = road_speed_limits_[0U][0U].max_speed;
        for (size_t i = 1U; i < segs; ++i)
        {
            if (ScalarEqualT<holo::float32_t>()(road_speed_limits_[0U][i].max_speed, current_limit))
            {
                return road_speed_limits_[0U][i].start_distance;
            }
        }
        return std::numeric_limits<holo::float32_t>::max();
    }

    /**
     * @brief Set current lane width, unit is m.
     * @param[in] width current lane width
     */
    void SetCurrentLaneWidth(const ::holo::float32_t width) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(AdviceValuesFloat32::CURRENT_LANE_WIDTH)] = width;
    }

    /**
     * @brief Get current lane width, unit is m.
     * @return current lane width
     */
    ::holo::float32_t GetCurrentLaneWidth() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(AdviceValuesFloat32::CURRENT_LANE_WIDTH)];
    }

    /**
     * @brief add new crossing info and sort by distance in ascending order
     * @param[in] ci crossing info
     */
    void AddCrossingInfo(const CrossingInfo& ci) noexcept
    {
        bool inserted = false;
        for (auto it = this->vec_crossing_info_.begin(); it < this->vec_crossing_info_.end() && !inserted; it++)
        {
            if (ci.distance < (*it).distance)
            {
                inserted = true;
                (void)this->vec_crossing_info_.insert(it, ci);
            }
        }
        if (!inserted)
        {
            this->vec_crossing_info_.push_back(ci);
        }
    }

    /**
     * @brief Set crossing info list
     * @param[in] crossing_info
     */
    void SetCrossingInfoList(const ::std::vector<CrossingInfo>& crossing_info) noexcept
    {
        this->vec_crossing_info_ = crossing_info;
    }

    /**
     * @brief Set crossing info list as rvalue
     * @param[in] crossing_info
     */
    void SetCrossingInfoList(::std::vector<CrossingInfo>&& crossing_info) noexcept
    {
        ::std::swap(this->vec_crossing_info_, crossing_info);
    }

    /**
     * @brief Get crossing info list as const reference
     * @return crossing info list as const reference
     */
    const ::std::vector<CrossingInfo>& GetCrossingInfoList() const noexcept
    {
        return this->vec_crossing_info_;
    }

    /**
     * @brief check is on route
     * @return true/false
     */
    bool IsOnRoute() const noexcept
    {
        return this->indicators_.test(static_cast<::std::size_t>(AdviceInfoIndicatorType::IS_ON_ROUTE));
    }

    /**
     * @brief set is on the route
     * @param[in] a is on the route
     */
    void SetIsOnRoute(const bool a) noexcept
    {
        (void)this->indicators_.set(static_cast<::std::size_t>(AdviceInfoIndicatorType::IS_ON_ROUTE), a);
    }

    /**
     * @brief check ego car is on bifurcation
     * @param[in] a ego car is on bifurcation
     */
    void SetIsOnBifurcation(const bool a) noexcept
    {
        (void)this->indicators_.set(static_cast<::std::size_t>(AdviceInfoIndicatorType::IS_ON_BIFURCATION_AREA), a);
    }

    /**
     * @brief check ego car is on bifurcation
     * @return true/false
     */
    bool IsOnBifurcation() const noexcept
    {
        return this->indicators_.test(static_cast<::std::size_t>(AdviceInfoIndicatorType::IS_ON_BIFURCATION_AREA));
    }

    /**
     * @brief Check if the current position is on the HD map or not
     *
     * @return True if is on HD map, false if not
     */
    ::holo::bool_t IsOnHDMap() const noexcept
    {
        return this->indicators_.test(static_cast<::std::size_t>(AdviceInfoIndicatorType::IS_ON_HDMAP));
    }

    /**
     * @brief Set flag that indicates whether the current position is on the HD map or not
     *
     * @param[in] is_on_hdmap
     */
    void SetIsOnHDMap(const ::holo::bool_t is_on_hdmap) noexcept
    {
        (void)this->indicators_.set(static_cast<::std::size_t>(AdviceInfoIndicatorType::IS_ON_HDMAP), is_on_hdmap);
    }

    /**
     * @brief Access lane target info.
     *
     * @return Returns lane target info.
     */
    const TargetLaneAdviceGroup& GetTargetLaneAdviceGroup() const noexcept
    {
        return this->lane_advices_;
    }

    /**
     * @brief Assigns new group to the container.
     *
     * @param[in] group A object with type of TargetLaneAdviceGroup.
     * @return Return nothing.
     */
    void SetTargetLaneAdviceGroup(const TargetLaneAdviceGroup& group) noexcept
    {
        this->lane_advices_ = group;
    }

    /**
     * @brief Access link target info.
     *
     * @return Returns link target info.
     */
    const TargetLinkAdviceGroup& GetTargetLinkAdviceGroup() const noexcept
    {
        return this->link_advices_;
    }

    /**
     * @brief Assigns new group to the container.
     *
     * @param[in] group A object with type of TargetLinkAdviceGroup.
     * @return Returns nothing.
     */
    void SetTargetLinkAdviceGroup(const TargetLinkAdviceGroup& group) noexcept
    {
        this->link_advices_ = group;
    }

    /**
     * @brief Moves the elements of group into the container.
     *
     * @param[in] group A object with type TargetLinkAdviceGroup.
     * @return Returns nothing.
     */
    void SetTargetLinkAdviceGroup(TargetLinkAdviceGroup&& group) noexcept
    {
        this->link_advices_.advices.swap(group.advices);
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        uint32_t size       = 0;
        size_t   align_size = MapMsgBase::GetSerializedSize<ALIGN>() + timestamp_.GetSerializedSize<ALIGN>();
        align_size +=
            holo::serialization::AlignedSize<ALIGN>(sizeof(size) + crossing_sequence_list_.size() * sizeof(SeqValue));
        align_size +=
            holo::serialization::AlignedSize<ALIGN>(sizeof(size) + current_lane_seq_list_.size() * sizeof(SeqValue));
        align_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(vec_crossing_info_.size()));
        if (vec_crossing_info_.size() > 0)
        {
            align_size += vec_crossing_info_[0].GetSerializedSize<ALIGN>() * vec_crossing_info_.size();
        }
        align_size += link_advices_.GetSerializedSize<ALIGN>() + lane_advices_.GetSerializedSize<ALIGN>() +
                      road_speed_limits_.GetSerializedSize<ALIGN>() + logic_graph_.GetSerializedSize<ALIGN>();
        return align_size;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        uint32_t count;

        MapMsgBase::Serialize(serializer);
        serializer << timestamp_;

        count = static_cast<uint32_t>(crossing_sequence_list_.size());
        serializer << count;

        for (size_t i = 0U; i < count; ++i)
        {
            serializer << crossing_sequence_list_[i];
        }
        serializer << holo::serialization::align;

        count = current_lane_seq_list_.size();
        serializer << count;
        for (size_t i = 0U; i < count; ++i)
        {
            serializer << current_lane_seq_list_[i];
        }
        serializer << holo::serialization::align;

        count = vec_crossing_info_.size();
        serializer << count;
        serializer << holo::serialization::align;

        for (size_t i = 0U; i < count; ++i)
        {
            serializer << vec_crossing_info_[i];
        }
        serializer << link_advices_ << lane_advices_ << road_speed_limits_ << logic_graph_;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t count;

        MapMsgBase::Deserialize(deserializer);
        deserializer >> timestamp_;

        deserializer >> count;
        crossing_sequence_list_.resize(count);
        for (size_t i = 0U; i < count; ++i)
        {
            deserializer >> crossing_sequence_list_[i];
        }
        deserializer >> holo::serialization::align;

        deserializer >> count;
        current_lane_seq_list_.resize(count);
        for (size_t i = 0U; i < count; ++i)
        {
            deserializer >> current_lane_seq_list_[i];
        }
        deserializer >> holo::serialization::align;

        deserializer >> count >> holo::serialization::align;
        vec_crossing_info_.resize(count);
        for (size_t i = 0U; i < count; ++i)
        {
            deserializer >> vec_crossing_info_[i];
        }

        deserializer >> link_advices_ >> lane_advices_ >> road_speed_limits_ >> logic_graph_;
    }

    /**
     * @brief Output advice content as string
     * @return serialized string
     */
    ::std::string ToString() const noexcept
    {
        std::ostringstream oss;
        oss << "CurSeq: [ ";
        for (const auto& s : GetCurrentLaneSequence())
        {
            oss << s << " ";
        }
        oss << "] ";
        oss << "; TarSeq = [";
        for (const auto& s : this->crossing_sequence_list_)
        {
            oss << s << " ";
        }
        oss << "]; ";

        if (IsOnRoute())
        {
            oss << " On Route";
        }
        else
        {
            oss << " Off Route";
        }

        oss << "; \n Crossings: ";
        for (const CrossingInfo& ci : this->vec_crossing_info_)
        {
            const holo::uint16_t delta = static_cast<holo::uint16_t>(ci.crossing_type) -
                                         static_cast<holo::uint16_t>(::holo::map::CrossingType::DESTINATION);
            const std::string name = ::holo::map::CrossingTypeName[delta];
            oss << "(" << name << ",: " << ci.distance << ")";
        }
        return oss.str();
    }

    /**
     * @brief Get road speed limits
     *
     * @return Reference to road speed limits
     */
    RoadSpeedLimits& GetRoadSpeedLimits() noexcept
    {
        return road_speed_limits_;
    }

    /**
     * @brief Get road speed limits
     *
     * @return Reference to road speed limits
     */
    RoadSpeedLimits const& GetRoadSpeedLimits() const noexcept
    {
        return road_speed_limits_;
    }

    /**
     * @brief Get road logic graph.
     *
     * @return Using RoadFrame for road logic graph.
     */
    RoadFrameType& GetRoadLogicGraph() noexcept
    {
        return logic_graph_;
    }

    /**
     * @brief Get road logic graph.
     *
     * @return Using RoadFrame for road logic graph.
     */
    RoadFrameType const& GetRoadLogicGraph() const noexcept
    {
        return logic_graph_;
    }

private:
    /**
     * @brief Enumerate some advice indicators
     *
     */
    enum class AdviceInfoIndicatorType : ::holo::uint8_t
    {
        IS_ON_ROUTE            = 0,  ///< if ego car is on route
        HAS_GUIDE_LINE         = 1,  ///< if advice has guide line
        IS_ON_BIFURCATION_AREA = 2,  ///< if ego car is on bifurcation area
        IS_ON_HDMAP            = 3,  ///< if ego car is on hd map

        ADVICE_INFO_INDICATOR_MAX  ///< max value of "AdviceInfoIndicatorType" used to resize the vector in constructor
    };
    /**
     * @brief Enumerate some uint32 type values
     *
     */
    enum class AdviceValuesUint32 : ::holo::uint8_t
    {

        ADVICE_VALUES_UINT32_MAX  ///< max size of the "uint32_values_" used to resize the vector in constructor

    };

    /**
     * @brief Enumerate some float32 type values
     *
     */
    enum class AdviceValuesFloat32 : ::holo::uint8_t
    {
        CURRENT_LANE_WIDTH = 0,          ///< current lane width
        DISTANCE_TO_SPEED_LIMIT_CHANGE,  ///< distance ahead (0~200m)
        REMAINING_DISTANCE,              ///< remaining distance to crossing
        CURRENT_SPEED_LIMIT,             ///< current lane speed limit
        TARGET_SPEED_AHEAD,              ///< crossing speed ahead

        ADVICE_VALUES_FLOAT_MAX  ///< max size of the "float32_values_" used to resize the vector in constructor
    };

private:
    /// Message stamp
    holo::common::Timestamp timestamp_;
    /// Lane sequence list, which connected to next crossing
    ::std::vector<SeqValue> crossing_sequence_list_;
    /// sequence list in current link
    ::std::vector<SeqValue> current_lane_seq_list_;
    /// list of crossing info
    ::std::vector<CrossingInfo> vec_crossing_info_;
    /// Target advice info in link level
    ::holo::map::TargetLinkAdviceGroup link_advices_;
    /// Target advice info in lane level
    ::holo::map::TargetLaneAdviceGroup lane_advices_;
    /// Speed limits of current road
    RoadSpeedLimits road_speed_limits_;

    RoadFrameType logic_graph_;  ///< Road logic graph
};

/**
 * @}
 */
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_ADVICE_H_ */
