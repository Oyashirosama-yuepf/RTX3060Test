/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_boundary.h
 * @brief define boundary infos for local map graph.
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-06
 */

#ifndef HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_BOUNDARY_H_
#define HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_BOUNDARY_H_

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
 * @brief Define boundary interval info
 */
template <typename IdT, typename DataT, typename OffsetValueT>
class BoundaryIntervalInfo : public IntervalInfo<IdT, DataT, OffsetValueT>
{
public:
    /**
     * @brief Define boundary type
     */
    enum class BoundaryType : uint8_t
    {
        BOUNDARY_TYPE_UNKNOWN  = 0U,
        BOUNDARY_TYPE_BOUNDARY = 1U,
        BOUNDARY_TYPE_BARRIER  = 2U,
        BOUNDARY_TYPE_CURB     = 3U,
        BOUNDARY_TYPE_VIRTUAL  = 4U,
        BOUNDARY_TYPE_WALL     = 5U,
        BOUNDARY_TYPE_CLIFF    = 6U,
        BOUNDARY_TYPE_DITCH    = 7U,
        BOUNDARY_TYPE_OTHERS   = 255U
    };

    /**
     * @brief Define line style
     */
    enum class LineStyle : uint8_t
    {
        LINE_STYLE_UNKNOWN                          = 0U,
        LINE_STYLE_SIGLE_SOLID_LINE                 = 1U,
        LINE_STYLE_DOUBLE_SOLID_LINE                = 2U,
        LINE_STYLE_SIGLE_DASHED_LINE                = 3U,
        LINE_STYLE_DOUBLE_DASHED_LINE               = 4U,
        LINE_STYLE_LEFT_DASHED_AND_RIGHT_SOLID_LINE = 5U,
        LINE_STYLE_LEFT_SOLID_AND_RIGHT_DASHED_LINE = 6U,
        LINE_STYLE_LONG_DASHED_LINE                 = 7U,
        LINE_STYLE_SHORT_DASHED_LINE                = 8U,
        LINE_STYLE_NORMAL_FISH_BONE_LINE            = 9U,
        LINE_STYLE_OTHERS                           = 255U
    };

    /**
     * @brief Define line color
     */
    enum class LineColor : uint8_t
    {
        LINE_COLOR_UNKNOWN = 0U,
        LINE_COLOR_WHITE   = 1U,
        LINE_COLOR_YELLOW  = 2U
    };

    BoundaryIntervalInfo()                            = default;
    ~BoundaryIntervalInfo()                           = default;
    BoundaryIntervalInfo(BoundaryIntervalInfo const&) = default;
    BoundaryIntervalInfo(BoundaryIntervalInfo&&)      = delete;
    BoundaryIntervalInfo& operator=(BoundaryIntervalInfo const&) = default;
    BoundaryIntervalInfo& operator=(BoundaryIntervalInfo&&) = delete;

    /**
     * @brief Set type.
     *
     * @param type boundary type, lane boundary, barrier, curb.
     */
    void SetType(BoundaryType const type) noexcept
    {
        this->type_ = type;
    }

    /**
     * @brief Get type.
     *
     * @return Boundary interval type.
     */
    BoundaryType GetType() const noexcept
    {
        return this->type_;
    }

    /**
     * @brief Set style.
     *
     * @param style style.
     */
    void SetStyle(LineStyle const style) noexcept
    {
        this->style_ = style;
    }

    /**
     * @brief Get style.
     *
     * @return Boundary interval style.
     */
    LineStyle GetStyle() const noexcept
    {
        return this->style_;
    }

    /**
     * @brief Set color.
     *
     * @param color color.
     */
    void SetColor(LineColor const color) noexcept
    {
        this->color_ = color;
    }

    /**
     * @brief Get color.
     *
     * @return Boundary interval color.
     */
    LineColor GetColor() const noexcept
    {
        return this->color_;
    }

    /**
     * @brief Set width.
     *
     * @param width width, unit: centermeter.
     */
    void SetWidth(holo::uint32_t const width) noexcept
    {
        this->width_ = width;
    }

    /**
     * @brief Get width.
     *
     * @return Boundary interval width, unit: centermeter.
     */
    holo::uint32_t GetWidth() const noexcept
    {
        return this->width_;
    }

    /**
     * @brief Set width.
     *
     * @param width Boundary interval width, unit: meter.
     */
    void SetWidthWithMeters(holo::float32_t const width) noexcept
    {
        this->width_ = width * 100;
    }

    /**
     * @brief Get width.
     *
     * @return Boundary interval width, unit: meter.
     */
    holo::uint32_t GetWidthWithMeters() const noexcept
    {
        return this->width_ * 0.01;
    }

    /**
     * @brief Set length.
     *
     * @param length length, unit: centermeter.
     */
    void SetLength(holo::uint32_t const length) noexcept
    {
        this->data_value_ = length;
    }

    /**
     * @brief Get length.
     *
     * @return Boundary interval length, uint:centermeter.
     */
    holo::uint32_t GetLength() const noexcept
    {
        return this->data_value_;
    }

    /**
     * @brief Set length.
     *
     * @param length Boundary interval length, unit: meter.
     */
    void SetLengthWithMeters(holo::float32_t const length) noexcept
    {
        this->data_value_ = length * 100;
    }

    /**
     * @brief Get length.
     *
     * @return Boundary interval length, uint:meter.
     */
    holo::float32_t GetLengthWithMeters() const noexcept
    {
        return this->data_value_ * 0.01;
    }

    /**
     * @brief Set confidence.
     *
     * @param confidence confidence.
     */
    void SetCondfidence(uint8_t const confidence) noexcept
    {
        this->confidence_ = confidence;
    }

    /**
     * @brief Get confidence.
     *
     * @return Boundary interval confidence.
     */
    uint8_t GetConfidence() const noexcept
    {
        return this->confidence_;
    }

private:
    BoundaryType type_ = BoundaryType::BOUNDARY_TYPE_UNKNOWN;    /// boundary type: unknown, lane boundary, barrier, curb.
    LineStyle    style_        = LineStyle::LINE_STYLE_UNKNOWN;  /// line style: unknown, solid, virtual.
    LineColor    color_        = LineColor::LINE_COLOR_UNKNOWN;  /// line color: unknown, white, yellow.
    holo::uint32_t width_      = 0U;                             /// boundary interval width, unit: cm.
    holo::uint8_t  confidence_ = 0U;
};

/**
 * @brief Define boundary
 */
template <typename FeatureIdT, typename PointT, size_t BOUNDARY_ID_SIZE = 128U, size_t INTERVAL_SIZE = 255U,
          size_t LINE_SIZE = 1024U>
class Boundary : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType                  = FeatureIdT;
    using PointType                      = PointT;
    using BoundaryIdVectorType           = holo::container::Vector<FeatureIdT, BOUNDARY_ID_SIZE>;
    using BoundaryIntervalInfoType       = BoundaryIntervalInfo<FeatureIdType, holo::float64_t, holo::float64_t>;
    using BoundaryIntervalInfoVectorType = holo::container::Vector<BoundaryIntervalInfoType, INTERVAL_SIZE>;
    using Point3dVectorType              = holo::container::Vector<PointType, LINE_SIZE>;

    Boundary() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_BOUNDARY)
    {
    }
    ~Boundary()               = default;
    Boundary(Boundary const&) = default;
    Boundary(Boundary&&)      = delete;
    Boundary& operator=(Boundary const&) = default;
    Boundary& operator=(Boundary&&) = delete;

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
     * @brief Set preceding boundary ids.
     *
     * @param preceding_boundary_ids oreceding boundary ids.
     */
    void SetPrecedingBoundaryIds(BoundaryIdVectorType const& preceding_boundary_ids) noexcept
    {
        this->preceding_boundary_ids_ = preceding_boundary_ids;
    }

    /**
     * @brief Get preceding boundary ids.
     *
     * @return Preceding boundary ids.
     */
    BoundaryIdVectorType GetPrecedingBoundaryIds() const noexcept
    {
        return this->preceding_boundary_ids_;
    }

    /**
     * @brief Set succeeding boundary ids.
     *
     * @param succeeding_boundary_ids succeeding boundary ids.
     */
    void SetSucceedingBoundaryIds(BoundaryIdVectorType const& succeeding_boundary_ids) noexcept
    {
        this->succeeding_boundary_ids_ = succeeding_boundary_ids;
    }

    /**
     * @brief Get succeeding boundary ids.
     *
     * @return Succeeding boundary ids.
     */
    BoundaryIdVectorType GetSucceedingBoundaryIds() const noexcept
    {
        return this->succeeding_boundary_ids_;
    }

    /**
     * @brief Set boundary interval info.
     *
     * @param boundary_interval boundary interval.
     */
    void AddBoundaryInterval(BoundaryIntervalInfoType const& boundary_interval) noexcept
    {
        this->boundary_intervals_.push_back(boundary_interval);
    }

    /**
     * @brief Get boundary interval infos.
     *
     * @return Boundary interval infos.
     */
    BoundaryIntervalInfoVectorType const& GetBoundaryIntervals() const noexcept
    {
        return this->boundary_intervals_;
    }

    /**
     * @brief Clear boundary interval infos.
     *
     * @return
     */
    void Clear() noexcept
    {
        this->boundary_intervals_.clear();
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
    FeatureIdType        link_id_       = static_cast<FeatureIdType>(0);  /// link id, invalid link id: 0.
    FeatureIdType        left_lane_id_  = static_cast<FeatureIdType>(0);  /// left lane id, invalid lane id: 0.
    FeatureIdType        right_lane_id_ = static_cast<FeatureIdType>(0);  /// right lane id, invalid lane id: 0.
    BoundaryIdVectorType preceding_boundary_ids_;                         /// preceding boundary ids.
    BoundaryIdVectorType succeeding_boundary_ids_;                        /// succeeding boundary ids.
    BoundaryIntervalInfoVectorType boundary_intervals_;                   /// boundary intervals.
    Point3dVectorType              center_line_;                          /// center line points.
};

/**
 * @}
 */
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_BOUNDARY_H_