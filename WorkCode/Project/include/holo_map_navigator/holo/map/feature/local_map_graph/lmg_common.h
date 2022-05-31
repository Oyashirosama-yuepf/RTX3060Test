/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_common.h
 * @brief define common infos for local map graph.
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-06
 */

#ifndef HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_COMMON_H_
#define HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_COMMON_H_

#include <map>
#include <string>

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/log/hololog.h>

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
 * @brief Define feature type for local map graph.
 */
enum class FeatureType : uint8_t
{
    FEATURE_TYPE_UNDEFINED           = 0U,
    FEATURE_TYPE_LINK                = 1U,
    FEATURE_TYPE_LANE                = 2U,
    FEATURE_TYPE_BOUNDARY            = 3U,
    FEATURE_TYPE_STOPLINE            = 4U,
    FEATURE_TYPE_MARKING             = 5U,
    FEATURE_TYPE_LIGHT               = 6U,
    FEATURE_TYPE_SIGN                = 7U,
    FEATURE_TYPE_SAFEISLAND          = 8U,
    FEATURE_TYPE_PEDESTRIAN_CROSSING = 9U,
    FEATURE_TYPE_INTERSECTION           = 10U,
};

/**
 * @brief Define box 3D type.
 */
template <typename PoseT, typename DataT>
class Bbox3D
{
public:
    using PoseType = PoseT;
    using DataType = DataT;

    Bbox3D()              = default;
    ~Bbox3D()             = default;
    Bbox3D(Bbox3D const&) = default;
    Bbox3D(Bbox3D&&)      = delete;
    Bbox3D& operator=(Bbox3D const&) = default;
    Bbox3D& operator=(Bbox3D&&) = delete;

    /**
     * @brief Set pose.
     *
     * @param pose pose.
     */
    void SetPose(PoseType const& pose) noexcept
    {
        this->pose_ = pose;
    }

    /**
     * @brief Get pose.
     *
     * @return Pose.
     */
    PoseType GetPose() const noexcept
    {
        return this->pose_;
    }

    /**
     * @brief Set width.
     *
     * @param width width.
     */
    void SetWidth(DataType const width) noexcept
    {
        this->width_ = width;
    }

    /**
     * @brief Get width.
     *
     * @return Width.
     */
    DataType GetWidth() const noexcept
    {
        return this->width_;
    }

    /**
     * @brief Set height.
     *
     * @param height height.
     */
    void SetHeight(DataType const height) noexcept
    {
        this->height_ = height;
    }

    /**
     * @brief Get height.
     *
     * @return Height.
     */
    DataType GetHeight() const noexcept
    {
        return this->height_;
    }

    /**
     * @brief Set length.
     *
     * @param length length.
     */
    void SetLength(DataType const length) noexcept
    {
        this->length_ = length;
    }

    /**
     * @brief Get length.
     *
     * @return Length.
     */
    DataType GetLength() const noexcept
    {
        return this->length_;
    }

private:
    PoseType pose_;
    DataType width_  = 0.0;
    DataType height_ = 0.0;
    DataType length_ = 0.0;
};

/**
 * @brief Define bird view box 2D type.
 */
template <typename PointT, typename DataT>
class BirdViewBbox2D
{
public:
    using PointType = PointT;
    using DataType  = DataT;

    BirdViewBbox2D()                      = default;
    ~BirdViewBbox2D()                     = default;
    BirdViewBbox2D(BirdViewBbox2D const&) = default;
    BirdViewBbox2D(BirdViewBbox2D&&)      = delete;
    BirdViewBbox2D& operator=(BirdViewBbox2D const&) = default;
    BirdViewBbox2D& operator=(BirdViewBbox2D&&) = delete;

    /**
     * @brief Set center position.
     *
     * @param position position.
     */
    void SetCenterPosition(PointType const& position) noexcept
    {
        this->center_position_ = position;
    }

    /**
     * @brief Get center position.
     *
     * @return Center position.
     */
    PointType GetCenterPosition() const noexcept
    {
        return this->center_position_;
    }

    /**
     * @brief Set width.
     *
     * @param width width.
     */
    void SetWidth(DataType const width) noexcept
    {
        this->width_ = width;
    }

    /**
     * @brief Get width.
     *
     * @return Width.
     */
    DataType GetWidth() const noexcept
    {
        return this->width_;
    }

    /**
     * @brief Set heading.
     *
     * @param heading heading.
     */
    void SetHeading(DataType const heading) noexcept
    {
        this->heading_ = heading;
    }

    /**
     * @brief Get heading.
     *
     * @return Heading.
     */
    DataType GetHeading() const noexcept
    {
        return this->heading_;
    }

    /**
     * @brief Set length.
     *
     * @param length length.
     */
    void SetLength(DataType const length) noexcept
    {
        this->length_ = length;
    }

    /**
     * @brief Get length.
     *
     * @return Length.
     */
    DataType GetLength() const noexcept
    {
        return this->length_;
    }

private:
    PointType center_position_;
    DataType  width_   = 0.0;
    DataType  heading_ = 0.0;
    DataType  length_  = 0.0;
};

/**
 * @brief Define hist info type.
 */
class HistInfo
{
public:
    HistInfo()                = default;
    ~HistInfo()               = default;
    HistInfo(HistInfo const&) = default;
    HistInfo(HistInfo&&)      = delete;
    HistInfo& operator=(HistInfo const&) = default;
    HistInfo& operator=(HistInfo&&) = delete;

    /**
     * @brief Set sensor id.
     *
     * @param sensor_id sensor id.
     */
    void SetSensorId(holo::uint64_t const sensor_id) noexcept
    {
        this->sensor_id_ = sensor_id;
    }

    /**
     * @brief Get sensor id.
     *
     * @return Sensor id.
     */
    holo::uint64_t GetSensorId() const noexcept
    {
        return this->sensor_id_;
    }

    /**
     * @brief Set obstacle id.
     *
     * @param obstacle_id obstacle id.
     */
    void SetObstacleId(holo::uint64_t const obstacle_id) noexcept
    {
        this->obstacle_id_ = obstacle_id;
    }

    /**
     * @brief Get obstacle id.
     *
     * @return Obstacle id.
     */
    holo::uint64_t GetObstacleId() const noexcept
    {
        return this->obstacle_id_;
    }

    /**
     * @brief Set raw sensor capture timestamp.
     *
     * @param raw_sensor_capture_timestamp raw sensor capture timestamp.
     */
    void SetRawSensorCaptureTimestamp(holo::common::Timestamp const raw_sensor_capture_timestamp) noexcept
    {
        this->raw_sensor_capture_timestamp_ = raw_sensor_capture_timestamp;
    }

    /**
     * @brief Get raw sensor capture timestamp.
     *
     * @return Raw sensor capture timestamp.
     */
    holo::common::Timestamp GetRawSensorCaptureTimestamp() const noexcept
    {
        return this->raw_sensor_capture_timestamp_;
    }

    /**
     * @brief Set sensor perception capture timestamp.
     *
     * @param sensor_perception_capture_timestamp sensor perception capture timestamp.
     */
    void SetSensorPerceptionCaptureTimestamp(holo::common::Timestamp const sensor_perception_capture_timestamp) noexcept
    {
        this->sensor_perception_capture_timestamp_ = sensor_perception_capture_timestamp;
    }

    /**
     * @brief Get sensor perception capture timestamp.
     *
     * @return Sensor perception capture timestamp.
     */
    holo::common::Timestamp GetSensorPerceptionCaptureTimestamp() const noexcept
    {
        return this->sensor_perception_capture_timestamp_;
    }

    /**
     * @brief Set sensor perception output timestamp.
     *
     * @param sensor_perception_output_timestamp sensor perception output timestamp.
     */
    void SetSensorPerceptionOutputTimestamp(holo::common::Timestamp const sensor_perception_output_timestamp) noexcept
    {
        this->sensor_perception_output_timestamp_ = sensor_perception_output_timestamp;
    }

    /**
     * @brief Get sensor perception output timestamp.
     *
     * @return Sensor perception output timestamp.
     */
    holo::common::Timestamp GetSensorPerceptionOutputTimestamp() const noexcept
    {
        return this->sensor_perception_output_timestamp_;
    }

    /**
     * @brief Set fusion capture timestamp.
     *
     * @param fusion_capture_timestamp fusion capture timestamp.
     */
    void SetFusionCaptureTimestamp(holo::common::Timestamp const fusion_capture_timestamp) noexcept
    {
        this->fusion_capture_timestamp_ = fusion_capture_timestamp;
    }

    /**
     * @brief Get fusion capture timestamp.
     *
     * @return Fusion capture timestamp.
     */
    holo::common::Timestamp GetFusionCaptureTimestamp() const noexcept
    {
        return this->fusion_capture_timestamp_;
    }

    /**
     * @brief Set fusion output timestamp.
     *
     * @param fusion_output_timestamp fusion output timestamp.
     */
    void SetFusionOutputTimestamp(holo::common::Timestamp const fusion_output_timestamp) noexcept
    {
        this->fusion_output_timestamp_ = fusion_output_timestamp;
    }

    /**
     * @brief Get fusion output timestamp.
     *
     * @return Fusion output timestamp.
     */
    holo::common::Timestamp GetFusionOutputTimestamp() const noexcept
    {
        return this->fusion_output_timestamp_;
    }

private:
    holo::uint64_t          sensor_id_   = 0U;
    holo::uint64_t          obstacle_id_ = 0U;
    holo::common::Timestamp raw_sensor_capture_timestamp_;
    holo::common::Timestamp sensor_perception_capture_timestamp_;
    holo::common::Timestamp sensor_perception_output_timestamp_;
    holo::common::Timestamp fusion_capture_timestamp_;
    holo::common::Timestamp fusion_output_timestamp_;
};

/**
 * @brief Define point attributes type.
 */
template <typename PointT, typename AttributeT>
class PointAttributesT
{
public:
    using PointType     = PointT;
    using AttributeType = AttributeT;

    PointAttributesT()                        = default;
    ~PointAttributesT()                       = default;
    PointAttributesT(PointAttributesT const&) = default;
    PointAttributesT(PointAttributesT&&)      = delete;
    PointAttributesT& operator=(PointAttributesT const&) = default;
    PointAttributesT& operator=(PointAttributesT&&) = delete;

    /**
     * @brief Set heading.
     *
     * @param heading heading, unit:degree.
     */
    void SetHeading(AttributeType const heading) noexcept
    {
        this->heading_ = heading;
    }

    /**
     * @brief Get heading.
     *
     * @return Heading.
     */
    AttributeType GetHeading() const noexcept
    {
        return this->heading_;
    }

    /**
     * @brief Set lateral slope.
     *
     * @param lateral_slope lateral slope, unit:degree.
     */
    void SetLateralSlope(AttributeType const lateral_slope) noexcept
    {
        this->lateral_slope_ = lateral_slope;
    }

    /**
     * @brief Get lateral slope.
     *
     * @return Lateral slope.
     */
    AttributeType GetLateralSlope() const noexcept
    {
        return this->lateral_slope_;
    }

    /**
     * @brief Set longitudinal slope.
     *
     * @param longitudinal_slope longitudinal slope, unit:degree.
     */
    void SetLongitudinalSlope(AttributeType const longitudinal_slope) noexcept
    {
        this->longitudinal_slope_ = longitudinal_slope;
    }

    /**
     * @brief Get longitudinal slope.
     *
     * @return Longitudinal slope.
     */
    AttributeType GetLongitudinalSlope() const noexcept
    {
        return this->longitudinal_slope_;
    }

    /**
     * @brief Set curvature radius.
     *
     * @param curvature_radius curvature radius, unit:cm.
     */
    void SetCurvatureRadius(AttributeType const curvature_radius) noexcept
    {
        this->curvature_radius_ = curvature_radius;
    }

    /**
     * @brief Get curvature radius.
     *
     * @return Curvature radius.
     */
    AttributeType GetCurvatureRadius() const noexcept
    {
        return this->curvature_radius_;
    }

    /**
     * @brief Set point.
     *
     * @param point point.
     */
    void SetPoint(PointType const& point) noexcept
    {
        this->point_ = point;
    }

    /**
     * @brief Get point.
     *
     * @return Point.
     */
    PointType GetPoint() const noexcept
    {
        return this->point_;
    }

private:
    AttributeType heading_            = 0.0;  /// course angle, unit:degree.
    AttributeType lateral_slope_      = 0.0;  /// lateral slope, unit:degree.
    AttributeType longitudinal_slope_ = 0.0;  /// longitudinal slope, unit:degree.
    AttributeType curvature_radius_   = 0.0;  /// curvature radius, unit:cm.
    PointType     point_;
};

/**
 * @brief Define interval info.
 */
template <typename IdT, typename DataT, typename OffsetValueT>
class IntervalInfo
{
public:
    using IdType          = IdT;
    using DataType        = DataT;
    using OffsetValueType = OffsetValueT;

    /**
     * @brief Define interval type.
     */
    enum class Type : uint8_t
    {
        UNKNOWN             = 0U,
        STOPLINE            = 1U,
        MARKING             = 2U,
        TRAFFIC_SIGN        = 3U,
        TRAFFIC_LIGHT       = 4U,
        SAFE_IS_LAND        = 5U,
        PEDESTRIAN_CROSSING = 6U
    };

    /**
     * @brief Define offset style
     */
    enum class OffsetStyle : uint8_t
    {
        UNKNOWN = 0U,
        PERSENT = 1U,  // [0,100]
        INDEX   = 2U   //[0, count - 1]
    };

public:
    IntervalInfo()                    = default;
    virtual ~IntervalInfo()           = default;
    IntervalInfo(IntervalInfo const&) = default;
    IntervalInfo(IntervalInfo&&)      = delete;
    IntervalInfo& operator=(IntervalInfo const&) = default;
    IntervalInfo& operator=(IntervalInfo&&) = delete;

    /**
     * @brief Set data id.
     *
     * @param data_id data id.
     */
    void SetDataId(IdType const data_id) noexcept
    {
        this->data_id_ = data_id;
    }

    /**
     * @brief Get data id.
     *
     * @return Data id.
     */
    IdType GetDataId() const noexcept
    {
        return this->data_id_;
    }

    /**
     * @brief Set interval type.
     *
     * @param type interval type.
     */
    void SetDataType(Type const type) noexcept
    {
        this->type_ = type;
    }

    /**
     * @brief Get interval type.
     *
     * @return Interval type.
     */
    Type GetDatatype() const noexcept
    {
        return this->type_;
    }

    /**
     * @brief Set data value.
     *
     * @param data_value data value.
     */
    void SetDataValue(DataType const data_value) noexcept
    {
        this->data_value_ = data_value;
    }

    /**
     * @brief Get data value.
     *
     * @return Data value.
     */
    DataType GetDataValue() const noexcept
    {
        return this->data_value_;
    }

    /**
     * @brief Set offset style.
     *
     * @param offset_style offset style.
     */
    void SetOffsetStyle(OffsetStyle const offset_style) noexcept
    {
        this->offset_style_ = offset_style;
    }

    /**
     * @brief Get offset style.
     *
     * @return Offset style.
     */
    OffsetStyle GetOffsetStyle() const noexcept
    {
        return this->offset_style_;
    }

    /**
     * @brief Set start offset.
     *
     * @param start_offset start offset.
     */
    void SetStartOffset(OffsetValueType const start_offset) noexcept
    {
        this->start_offset_ = start_offset;
    }

    /**
     * @brief Get start offset.
     *
     * @return Start offset.
     */
    OffsetValueType GetStartOffset() const noexcept
    {
        return this->start_offset_;
    }

    /**
     * @brief Set end offset.
     *
     * @param end_offset end offset.
     */
    void SetEndOffset(OffsetValueType const end_offset) noexcept
    {
        this->end_offset_ = end_offset;
    }

    /**
     * @brief Get end offset.
     *
     * @return End offset.
     */
    OffsetValueType GetEndOffset() const noexcept
    {
        return this->end_offset_;
    }

protected:
    IdType          data_id_ = static_cast<IdType>(0U);
    Type            type_    = Type::UNKNOWN;
    DataType        data_value_;
    OffsetStyle     offset_style_ = OffsetStyle::UNKNOWN;               /// offet style: unknown, persent, index
    OffsetValueType start_offset_ = static_cast<OffsetValueType>(0.0);  /// start offset of interval
    OffsetValueType end_offset_   = static_cast<OffsetValueType>(0.0);  /// end offset of interval
};

/**
 * @brief Define local map graph base
 */
template <typename IdT>
class FeatureBase
{
public:
    using FeatureIdType = IdT;
    using FeatureType   = holo::map::navigator::graph::FeatureType;

    FeatureBase()                   = default;
    virtual ~FeatureBase()          = default;
    FeatureBase(FeatureBase const&) = default;
    FeatureBase(FeatureBase&&)      = delete;
    FeatureBase& operator=(FeatureBase const&) = default;
    FeatureBase& operator=(FeatureBase&&) = delete;

    FeatureBase(FeatureType type) : type_(type)
    {
    }

    /**
     * @brief Get feature type.
     *
     * @return feature type.
     */
    FeatureType GetType() const noexcept
    {
        return this->type_;
    }

    /**
     * @brief Set feature id.
     *
     * @param feature_id feature id.
     */
    void SetId(FeatureIdType const feature_id) noexcept
    {
        this->feature_id_ = feature_id;
    }

    /**
     * @brief Get feature id.
     *
     * @return feature id.
     */
    FeatureIdType GetId() const noexcept
    {
        return this->feature_id_;
    }

private:
    FeatureIdType feature_id_ = static_cast<FeatureIdType>(0);
    FeatureType   type_       = FeatureType::FEATURE_TYPE_UNDEFINED;
};

/**
 * @}
 */
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_COMMON_H_