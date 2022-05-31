/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_lane.h
 * @brief define lane infos for local map graph.
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-07
 */

#ifndef HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_LANE_H_
#define HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_LANE_H_

#include <holo/map/feature/local_map_graph/lmg_common.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace graph
{
/**
 * @addtogroup graph
 *
 * @{
 */

/**
 * @brief Define lane speed limit interval info
 */
template <typename IdT, typename OffsetValueT>
class SpeedLimitInterval : public IntervalInfo<IdT, std::pair<holo::uint16_t, holo::uint16_t>, OffsetValueT>
{
public:
    using IntervalInfoType    = IntervalInfo<IdT, std::pair<holo::uint16_t, holo::uint16_t>, OffsetValueT>;
    using SpeedLimitValueType = holo::uint16_t;
    using SpeedLimitPairType  = std::pair<holo::uint16_t, holo::uint16_t>;

    SpeedLimitInterval()          = default;
    virtual ~SpeedLimitInterval() = default;

    SpeedLimitInterval(SpeedLimitInterval const&) = default;
    SpeedLimitInterval(SpeedLimitInterval&&)      = delete;

    SpeedLimitInterval& operator=(SpeedLimitInterval const&) = default;
    SpeedLimitInterval& operator=(SpeedLimitInterval&&) = delete;

    /**
     * @brief Set max speed.
     *
     * @param max_speed max speed, unit: km/h
     */
    void SetMaxSpeedLimit(SpeedLimitValueType const max_speed) noexcept
    {
        this->data_value_.second = max_speed;
    }

    /**
     * @brief Get max speed.
     *
     * @return Max speed, unit: km/h
     */
    SpeedLimitValueType GetMaxSpeedLimit() const noexcept
    {
        return this->data_value_.second;
    }

    /**
     * @brief Set min speed.
     *
     * @param min_speed min speed, unit: km/h
     */
    void SetMinSpeedLimit(SpeedLimitValueType const min_speed) noexcept
    {
        this->data_value_.first = min_speed;
    }

    /**
     * @brief Get min speed.
     *
     * @return Min speed, unit: km/h
     */
    SpeedLimitValueType GetMinSpeedLimit() const noexcept
    {
        return this->data_value_.first;
    }
};

/**
 * @brief Define lane width interval info
 */
template <typename IdT, typename OffsetValueT>
class WidthInterval : public IntervalInfo<IdT, holo::float32_t, OffsetValueT>
{
public:
    using IntervalInfoType              = IntervalInfo<IdT, holo::float32_t, OffsetValueT>;
    using WidthValueWithMeterType       = typename IntervalInfoType::DataType;
    using WidthValueWithCenterMeterType = holo::uint32_t;

    WidthInterval()          = default;
    virtual ~WidthInterval() = default;

    WidthInterval(WidthInterval const&) = default;
    WidthInterval(WidthInterval&&)      = delete;

    WidthInterval& operator=(WidthInterval const&) = default;
    WidthInterval& operator=(WidthInterval&&) = delete;

    /**
     * @brief Set lane width.
     *
     * @param width Lane width, unit: centermeter.
     */
    void SetWidthWithCenterMeters(WidthValueWithCenterMeterType const width) noexcept
    {
        this->data_value_ = width * 0.01f;
    }

    /**
     * @brief Get lane width.
     *
     * @return Lane width, unit: centermeter.
     */
    WidthValueWithCenterMeterType GetWidthWithCenterMeters() const noexcept
    {
        return this->data_value_ * 100;
    }

    /**
     * @brief Set lane width.
     *
     * @param width Lane width, unit: meter.
     */
    void SetWidthWithMeters(WidthValueWithMeterType const width) noexcept
    {
        this->data_value_ = width;
    }

    /**
     * @brief Get lane width.
     *
     * @return Lane width, unit: meter.
     */
    WidthValueWithMeterType GetWidthWithMeters() const noexcept
    {
        return this->data_value_;
    }
};

/**
 * @brief Define lane
 */
template <typename FeatureIdT, typename PointT, size_t LANE_ID_SIZE = 64U, size_t INTERVAL_SIZE = 1024U,
          size_t LINE_SIZE = 1024U>
class Lane : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType                = FeatureIdT;
    using PointType                    = PointT;
    using LaneIdVectorType             = holo::container::Vector<FeatureIdType, LANE_ID_SIZE>;
    using IntervalInfoType             = IntervalInfo<FeatureIdType, holo::float64_t, holo::float64_t>;
    using IntervalInfoVectorType       = holo::container::Vector<IntervalInfoType, INTERVAL_SIZE>;
    using SpeedLimitIntervalType       = SpeedLimitInterval<FeatureIdType, holo::float64_t>;
    using SpeedLimitIntervalVectorType = holo::container::Vector<SpeedLimitIntervalType, INTERVAL_SIZE>;
    using WidthIntervalType            = WidthInterval<FeatureIdType, holo::float64_t>;
    using WidthIntervalVectorType      = holo::container::Vector<WidthIntervalType, INTERVAL_SIZE>;
    using Point3dVectorType            = holo::container::Vector<PointType, LINE_SIZE>;

    /**
     * @brief Define lane type
     */
    enum class LaneType : uint8_t
    {
        LANE_TYPE_UNKNOWN                 = 0U,
        LANE_TYPE_REGULAR                 = 1U,
        LANE_TYPE_EXPRESS                 = 2U,
        LANE_TYPE_SLOW                    = 3U,
        LANE_TYPE_EMERGENCY               = 4U,
        LANE_TYPE_EMERGENCY_PARKING_STRIP = 5U,
        LANE_TYPE_CLIMBING                = 6U,
        LANE_TYPE_ESCAPE                  = 7U,
        LANE_TYPE_ENTRY                   = 8U,
        LANE_TYPE_EXIT                    = 9U,
        LANE_TYPE_ACCELERATE              = 10U,
        LANE_TYPE_DECELERATE              = 11U,
        LANE_TYPE_RAMP                    = 12U,
        LANE_TYPE_RAMP_ABORD              = 13U,
        LANE_TYPE_RAMP_ASHORE             = 14U,
        LANE_TYPE_RAMP_JCT                = 15U,
        LANE_TYPE_TOLLBOOTH               = 16U,
        LANE_TYPE_NONDRIVEWAY             = 17U,
        LANE_TYPE_DEDICATED_BUS           = 18U,
        LANE_TYPE_DEDICATED_CUSTOM        = 19U,
        LANE_TYPE_REVERSIBLE              = 20U,
        LANE_TYPE_VARIABLE                = 21U,
        LANE_TYPE_DRIVABLE_SHOULDER       = 22U,
        LANE_TYPE_DISDRIVABLE_SHOULDER    = 23U,
        LANE_TYPE_BICYCLE                 = 24U,
        LANE_TYPE_OTHERS                  = 255U
    };

    /**
     * @brief Define turn type
     */
    enum class TurnType : uint8_t
    {
        TURN_TYPE_UNKNOWN      = 0X00,
        TURN_TYPE_LEFT         = 0X01,
        TURN_TYPE_RIGHT        = 0X02,
        TURN_TYPE_LEFT_AROUND  = 0X04,
        TURN_TYPE_RIGHT_AROUND = 0X08,
        TURN_TYPE_STRAIGHT     = 0X10,
        TURN_TYPE_LEFT_AREA    = 0X20,
        TURN_TYPE_OTHERS       = 255U
    };

    /**
     * @brief Define trans type
     */
    enum class TransType : uint8_t
    {
        TRANS_TYPE_UNKNOWN             = 0U,
        TRANS_TYPE_NONE                = 1U,
        TRANS_TYPE_OPENING             = 2U,
        TRANS_TYPE_ENDING              = 3U,
        TRANS_TYPE_WIDE_STEP_BY_STEP   = 4U,
        TRANS_TYPE_NARROW_STEP_BY_STEP = 5U,
        TRANS_TYPE_OPENING_AND_ENDING  = 6U,
        TRANS_TYPE_ENDING_AND_OPENING  = 7U,
        TRANS_TYPE_OTHERS              = 255U
    };

    Lane() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LANE)
    {
    }
    ~Lane()           = default;
    Lane(Lane const&) = default;
    Lane(Lane&&)      = delete;
    Lane& operator=(Lane const&) = default;
    Lane& operator=(Lane&&) = delete;

    /**
     * @brief Set link id.
     *
     * @param link_id link id.
     */
    void SetLinkId(FeatureIdType const link_id) noexcept
    {
        this->link_id_ = link_id;
    }

    /**
     * @brief Get link id.
     *
     * @return Link id.
     */
    FeatureIdType GetLinkId() const noexcept
    {
        return this->link_id_;
    }

    /**
     * @brief Set lane type.
     *
     * @param lane_type lane type.
     */
    void SetLaneType(LaneType const lane_type) noexcept
    {
        this->lane_type_ = lane_type;
    }

    /**
     * @brief Get lane type.
     *
     * @return Lane type.
     */
    LaneType GetLaneType() const noexcept
    {
        return this->lane_type_;
    }

    /**
     * @brief Set turn type.
     *
     * @param turn_type turn type.
     */
    void SetTurnType(TurnType const turn_type) noexcept
    {
        this->turn_type_ = turn_type;
    }

    /**
     * @brief Get turn type.
     *
     * @return Turn type.
     */
    TurnType GetTurnType() const noexcept
    {
        return this->turn_type_;
    }

    /**
     * @brief Set trans type.
     *
     * @param trans_type trans type.
     */
    void SetTransType(TransType const trans_type) noexcept
    {
        this->trans_type_ = trans_type;
    }

    /**
     * @brief Get trans type.
     *
     * @return Trans type.
     */
    TransType GetTransType() const noexcept
    {
        return this->trans_type_;
    }

    /**
     * @brief Set sequence.
     *
     * @param sequence sequence.
     */
    void SetSequence(uint8_t const sequence) noexcept
    {
        this->sequence_ = sequence;
    }

    /**
     * @brief Get sequence.
     *
     * @return Sequence.
     */
    uint8_t GetSequence() const noexcept
    {
        return this->sequence_;
    }

    /**
     * @brief Set intersection id.
     *
     * @param intersection_id intersection id.
     */
    void SetIntersectionId(FeatureIdType const intersection_id) noexcept
    {
        this->intersection_id_ = intersection_id;
    }

    /**
     * @brief Get intersection id.
     *
     * @return Intersection id.
     */
    FeatureIdType GetIntersectionId() const noexcept
    {
        return this->intersection_id_;
    }

    /**
     * @brief Set left lane id.
     *
     * @param left_lane_id left lane id.
     */
    void SetLeftLaneId(FeatureIdType const left_lane_id) noexcept
    {
        this->left_lane_id_ = left_lane_id;
    }

    /**
     * @brief Get left lane id.
     *
     * @return Left lane id.
     */
    FeatureIdType GetLeftLaneId() const noexcept
    {
        return this->left_lane_id_;
    }

    /**
     * @brief Set right lane id.
     *
     * @param right_lane_id right lane id.
     */
    void SetRightLaneId(FeatureIdType const right_lane_id) noexcept
    {
        this->right_lane_id_ = right_lane_id;
    }

    /**
     * @brief Get right lane id.
     *
     * @return Right lane id.
     */
    FeatureIdType GetRightLaneId() const noexcept
    {
        return this->right_lane_id_;
    }

    /**
     * @brief Set left boundary id.
     *
     * @param left_boundary_id left boundary id.
     */
    void SetLeftBoundaryId(FeatureIdType const left_boundary_id) noexcept
    {
        this->left_boundary_id_ = left_boundary_id;
    }

    /**
     * @brief Get left boundary id.
     *
     * @return Left boundary id.
     */
    FeatureIdType GetLeftBoundaryId() const noexcept
    {
        return this->left_boundary_id_;
    }

    /**
     * @brief Set right boundary id.
     *
     * @param right_boundary_id right boundary id.
     */
    void SetRightBoundaryId(FeatureIdType const right_boundary_id) noexcept
    {
        this->right_boundary_id_ = right_boundary_id;
    }

    /**
     * @brief Get right boundary id.
     *
     * @return Right boundary id.
     */
    FeatureIdType GetRightBoundaryId() const noexcept
    {
        return this->right_boundary_id_;
    }

    /**
     * @brief Set length.
     *
     * @param length length, unit:centermeter.
     */
    void SetLength(holo::float64_t const length) noexcept
    {
        this->length_ = length;
    }

    /**
     * @brief Get length.
     *
     * @return Length, unit: centermeter.
     */
    holo::float64_t GetLength() const noexcept
    {
        return this->length_;
    }

    /**
     * @brief Set length.
     *
     * @param length length, unit:meter.
     */
    void SetLengthWithMeters(holo::float64_t const length) noexcept
    {
        this->length_ = length * 100.0f;
    }

    /**
     * @brief Get length.
     *
     * @return Length, unit: meter.
     */
    holo::float64_t GetLengthWithMeters() const noexcept
    {
        return this->length_ * 0.01f;
    }

    /**
     * @brief Set preceding lane ids.
     *
     * @param preceding_lane_ids preceding lane ids.
     */
    void SetPrecedingLaneIds(LaneIdVectorType const& preceding_lane_ids) noexcept
    {
        this->preceding_lane_ids_ = preceding_lane_ids;
    }

    /**
     * @brief Get preceding lane ids.
     *
     * @return Preceding lane ids.
     */
    LaneIdVectorType const& GetPrecedingLaneIds() const noexcept
    {
        return this->preceding_lane_ids_;
    }

    /**
     * @brief Set succeeding lane ids.
     *
     * @param succeeding_lane_ids succeeding lane ids.
     */
    void SetSucceedingLaneIds(LaneIdVectorType const& succeeding_lane_ids) noexcept
    {
        this->succeeding_lane_ids_ = succeeding_lane_ids;
    }

    /**
     * @brief Get succeeding lane ids.
     *
     * @return Succeeding lane ids.
     */
    LaneIdVectorType const& GetSucceedingLaneIds() const noexcept
    {
        return this->succeeding_lane_ids_;
    }

    /**
     * @brief Set widths.
     *
     * @param widths widths.
     */
    void SetWidths(WidthIntervalVectorType const& widths) noexcept
    {
        this->widths_ = widths;
    }

    /**
     * @brief Get widths.
     *
     * @return Widths.
     */
    WidthIntervalVectorType const& GetWidths() const noexcept
    {
        return this->widths_;
    }

    /**
     * @brief Set speed limits.
     *
     * @param speed_limits speed limits.
     */
    void SetSpeedLimits(SpeedLimitIntervalVectorType const& speed_limits) noexcept
    {
        this->speed_limits_ = speed_limits;
    }

    /**
     * @brief Get speed limits.
     *
     * @return Speed limits.
     */
    SpeedLimitIntervalVectorType const& GetSpeedLimits() const noexcept
    {
        return this->speed_limits_;
    }

    /**
     * @brief Set stoplines.
     *
     * @param stoplines stoplines.
     */
    void SetStopLineIds(IntervalInfoVectorType const& stoplines) noexcept
    {
        this->stoplines_ = stoplines;
    }

    /**
     * @brief Get stoplines.
     *
     * @return Stoplines.
     */
    IntervalInfoVectorType const& GetStopLineIds() const noexcept
    {
        return this->stoplines_;
    }

    /**
     * @brief Set markings.
     *
     * @param markings markings.
     */
    void SetMarkingIds(IntervalInfoVectorType const& markings) noexcept
    {
        this->markings_ = markings;
    }

    /**
     * @brief Get markings.
     *
     * @return Markings.
     */
    IntervalInfoVectorType const& GetMarkingIds() const noexcept
    {
        return this->markings_;
    }

    /**
     * @brief Set lights.
     *
     * @param lights lights.
     */
    void SetLightIds(IntervalInfoVectorType const& lights) noexcept
    {
        this->lights_ = lights;
    }

    /**
     * @brief Get lights.
     *
     * @return Lights.
     */
    IntervalInfoVectorType const& GetLightIds() const noexcept
    {
        return this->lights_;
    }

    /**
     * @brief Set signs.
     *
     * @param signs signs.
     */
    void SetSignIds(IntervalInfoVectorType const& signs) noexcept
    {
        this->signs_ = signs;
    }

    /**
     * @brief Get signs.
     *
     * @return Signs.
     */
    IntervalInfoVectorType const& GetSignIds() const noexcept
    {
        return this->signs_;
    }

    /**
     * @brief Set safe islands.
     *
     * @param safe_islands safe islands.
     */
    void SetSafeIslandIds(IntervalInfoVectorType const& safe_islands) noexcept
    {
        this->safe_islands_ = safe_islands;
    }

    /**
     * @brief Get safe islands.
     *
     * @return Safe islands.
     */
    IntervalInfoVectorType const& GetSafeIslandIds() const noexcept
    {
        return this->safe_islands_;
    }

    /**
     * @brief Set pedestrian crossings.
     *
     * @param pedestrian_crossings pedestrian crossings.
     */
    void SetPedestrianCrossingIds(IntervalInfoVectorType const& pedestrian_crossings) noexcept
    {
        this->pedestrian_crossings_ = pedestrian_crossings;
    }

    /**
     * @brief Get pedestrian crossings.
     *
     * @return Pedestrian crossings.
     */
    IntervalInfoVectorType const& GetPedestrianCrossingIds() const noexcept
    {
        return this->pedestrian_crossings_;
    }

    /**
     * @brief Set center line.
     *
     * @param center_line center line.
     */
    void SetCenterLine(Point3dVectorType const& center_line) noexcept
    {
        this->center_line_ = center_line;
    }

    /**
     * @brief Get center line.
     *
     * @return Center line.
     */
    Point3dVectorType const& GetCenterLine() const noexcept
    {
        return this->center_line_;
    }

private:
    FeatureIdType    link_id_         = static_cast<FeatureIdType>(0);   /// link id, invalid link id: 0.
    LaneType         lane_type_       = LaneType::LANE_TYPE_UNKNOWN;     /// lane type: common, acceleration, deceleration.
    TurnType         turn_type_       = TurnType::TURN_TYPE_UNKNOWN;     /// turn type: common, left, right, U-shaped.
    TransType        trans_type_      = TransType::TRANS_TYPE_UNKNOWN;   /// trans type: new, disappear.
    uint8_t          sequence_        = 0U;                              /// lane sequence.
    FeatureIdType    intersection_id_ = static_cast<FeatureIdType>(0);   /// intersection id.
    FeatureIdType    left_lane_id_    = static_cast<FeatureIdType>(0);   /// left lane id.
    FeatureIdType    right_lane_id_   = static_cast<FeatureIdType>(0);   /// right lane id.
    FeatureIdType    left_boundary_id_  = static_cast<FeatureIdType>(0);  /// left boundary id.
    FeatureIdType    right_boundary_id_ = static_cast<FeatureIdType>(0);  /// right boundary id.
    holo::uint32_t   length_            = 0U;                             /// lane length, unit: cm.
    LaneIdVectorType preceding_lane_ids_;                                 /// preceding lane ids.
    LaneIdVectorType succeeding_lane_ids_;                                /// succeeding lane ids.
    WidthIntervalVectorType      widths_;                                 /// lane interval widths, unit: cm.
    SpeedLimitIntervalVectorType speed_limits_;                           /// lane interval speed limits, unit: km/h.
    IntervalInfoVectorType       stoplines_;                              /// interval stoplines info.
    IntervalInfoVectorType       lights_;                                 /// interval lights info.
    IntervalInfoVectorType       markings_;                               /// interval markings info.
    IntervalInfoVectorType       pedestrian_crossings_;                   /// interval pedestrian crossings info.
    IntervalInfoVectorType       signs_;                                  /// interval signs info.
    IntervalInfoVectorType       safe_islands_;                           /// interval safe lands info.
    Point3dVectorType            center_line_;                            /// lane center line points.
};

/**
 * @}
 */
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_LANE_H_