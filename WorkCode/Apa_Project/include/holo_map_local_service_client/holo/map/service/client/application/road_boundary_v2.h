/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_boundary_v2.h
 * @brief lane_boundary_v2.h
 * @author wanghaiyang@holomatic.com
 * @date "2021-03-25"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_ROAD_BOUNDARY_V2_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_ROAD_BOUNDARY_V2_H_

#include <memory>
#include <sstream>
#include <vector>

#include <holo/geometry/point3.h>
#include <holo/map/service/client/common/common.h>
#include <holo/map/service/client/common/geometry.h>
#include <holo/map/service/client/common/types.h>
#include <holo/map/service/client/profile/base.h>
#include <holo/map/service/client/profile/lane.h>
#include <holo/map/service/client/profile/segment.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace application
{
/**
 * @addtogroup application
 * @{
 *
 */

/**
 * @brief Define boundary type for roads and lanes.
 */
enum class RoadBoundaryType : holo::uint8_t
{
    kBOUNDARY_TYPE_UNKNOWN = 0, ///< Placeholder.
    kBOUNDARY_TYPE_REGULAR,     ///< Boundary type for lane, painted line on the both sides of lane.
    kBOUNDARY_TYPE_BARRIER,     ///< Boundary type for road.
    kBOUNDARY_TYPE_CURB,        ///< Boundary type for road.
}; ///< End of enum RoadBoundaryType.

/**
 * @brief Define boundary style for boundaries.
 */
enum class RoadBoundaryStyle : holo::uint8_t
{
    kBOUNDARY_STYLE_UNKNOWN             = 0, ///< Placeholder.
    kBOUNDARY_STYLE_SINGLE_SOLID_LINE,       ///< Single solid boundary.
    kBOUNDARY_STYLE_DOUBLE_SOLID_LINE,       ///< Double solid boundary.
    kBOUNDARY_STYLE_SINGLE_DASHED_LINE,      ///< Single dashed boundary.
    kBOUNDARY_STYLE_DOUBLE_DASHED_LINE,      ///< Double dashed boundary.
    kBOUNDARY_STYLE_OTHER,                   ///< Other styles.
}; ///< End of enum RoadBoundaryStyle.

/**
 * @brief Define boundary color for boundaries.
 */
enum class RoadBoundaryColor : holo::uint8_t
{
    kBOUNDARY_COLOR_UNKNOWN = 0,    ///< Placeholder.
    kBOUNDARY_COLOR_YELLOW,         ///< Yellow.
    kBOUNDARY_COLOR_WHITE,          ///< White.
}; ///< End of enum RoadBoundaryColor.

/**
 * @brief Define lane type.
 */
enum class RoadLaneType : holo::uint8_t
{
    kLANE_TYPE_UNKNOWN = 0,
    kLANE_TYPE_EXPRESS,
    kLANE_TYPE_EMERGENCY,
    kLANE_TYPE_ENTRY,
    kLANE_TYPE_EXIT,
    kLANE_TYPE_ACCELERATE,
    kLANE_TYPE_DECELERATE,
    kLANE_TYPE_HARD_SHOULDER,
}; ///< End of enum RoadLaneType.

/**
 * @brief Define an attribute type for road boundary.
 * 
 * @tparam Distance DistanceMeterType, DistanceCentermeterType.
 */
template<typename Distance>
struct RoadBoundaryAttribute
{
    /// Redefine Distance type for inner members.
    using DistanceType = Distance;

    /// Boundary style.
    RoadBoundaryStyle style = RoadBoundaryStyle::kBOUNDARY_STYLE_UNKNOWN;
    /// Boundary color.
    RoadBoundaryColor color = RoadBoundaryColor::kBOUNDARY_COLOR_UNKNOWN;

    /// Boundary width.
    DistanceType      width  = static_cast<DistanceType>(0.0);
    /// Boundary attribute offset from the start of a boundary.
    DistanceType      offset = static_cast<DistanceType>(0.0);

    /**
     * @brief Format a RoadBoundaryAttribute to a JSON string.
     * 
     * @param[in] attribute A RoadBoundaryAttribute object.
     * @return A JSON string.
     */
    static std::string FormatToString(RoadBoundaryAttribute<Distance> const& attribute)
    {
        std::stringstream stream;
        stream << "{\"style\":" << static_cast<int>(attribute.style)
               << ",\"color\":" << static_cast<int>(attribute.color)
               << ",\"width\":" << attribute.width
               << "}";
        return stream.str();
    }
};

/**
 * @brief Define a structure for road boundary.
 * 
 * @tparam Id ProfileIdType.
 * @tparam Length Length type for a RoadBoundary, like: DistanceMeterType, DistanceCentermeterType.
 * @tparam Width Width type for a RoadBoundary, like: DistanceMeterType, DistanceCentermeterType.
 * @tparam Attribute Attribute type, like: IndexSegment, PercentSegment, DistanceSegment.
 * @tparam Geometry Geometry type, must be GeoLine or other derived object of GeoBase.
 */
template <typename Id, typename Length, typename Width, typename Attribute, typename Geometry>
class RoadBoundaryV2
{
public:
    /// Redefine width type for inner members.
    using WidthType      = Width;
    /// Redefine length type for inner members.
    using LengthType     = Length;
    
    /// Redefine RoadBoundary id type.
    using RoadBoundaryIdType = Id;
    /// Redefine Lane id type.
    using RoadLaneIdType    = Id;

    /// Redefine base type for Geometry.
    using GeometryType         = holo::map::service::client::geometry::GeoBase;
    /// Redefine concrete type for Geometry.
    using ConcreteGeometryType = Geometry;

    /// Redefine attribute type.
    using AttributeType       = Attribute;
    /// Redefine attribute vector type.
    using AttributeVectorType = std::vector<AttributeType>;

    /// Define boundary type.
    using BoundaryType  = RoadBoundaryType;
    /// Define boundary style.
    using BoundaryStyle = RoadBoundaryStyle;
    /// Define boundary color.
    using BoundaryColor = RoadBoundaryColor;

    /// Define lane type.
    using LaneType      = RoadLaneType;

    /**
     * @brief Format a RoadBoundary attribute to a JSON string.
     * 
     * @param[in] attribute An attribute object.
     * @return A JSON string.
     */
    static std::string FormatToString(AttributeType const& attribute)
    {
        return AttributeType::FormatToString(attribute);
    }

    /**
     * @brief Format an array of RoadBoundary attributes to a JSON string.
     * 
     * @param[in] attributes An array of RoadBoundary attributes.
     * @return A JSON string.
     */
    static std::string FormatToString(AttributeVectorType const& attributes)
    {
        return holo::map::service::client::common::utility::FormatSequenceToString<AttributeType>(attributes,
            [](AttributeType const& attribute) -> std::string {
                return AttributeType::FormatToString(attribute, AttributeType::ValueType::FormatToString);
        });
    }

    /**
     * @brief Default constructor.
     */
    RoadBoundaryV2() = default;

    /**
     * @brief Default destructor.
     */
    virtual ~RoadBoundaryV2() = default;
    
    /**
     * @brief Access road boundary id.
     * @return Road boundary id.
     */
    RoadBoundaryIdType GetId() const noexcept
    {
        return this->id_;
    }

    /**
     * @brief Assign road boundary id.
     * 
     * @param[in] id Road boundary id.
     */
    void SetId(RoadBoundaryIdType const id) noexcept
    {
        this->id_ = id;
    }
    
    /**
     * @brief Access road boundary type.
     * 
     * @return Road boundary type.
     */
    BoundaryType GetBoundaryType() const noexcept
    {
        return this->boundary_type_;
    }

    /**
     * @brief Assign road boundary type.
     * 
     * @param[t] Road boundary type.
     */
    void SetBoundaryType(BoundaryType const t) noexcept
    {
        this->boundary_type_ = t;
    }

    /**
     * @brief Access road boundary length.
     * 
     * @return Road boundary length.
     */
    LengthType GetLength() const noexcept
    {
        return this->length_;
    }

    /**
     * @brief Assign road boundary length.
     * 
     * @param[in] d Road boundary length.
     */
    void SetLength(LengthType const d) noexcept
    {
        this->length_ = d;
    }

    /**
     * @brief Check if the road boundary has left available lane.
     * 
     * @return true: Has left available lane.
     *         false: Otherwise.
     */
    holo::bool_t HasLeftLane() const noexcept
    {
        return 0 != this->left_lane_id_;
    }

    /**
     * @brief Access left lane type.
     * 
     * @return Left lane type.
     */
    LaneType GetLeftLaneType() const
    {
        return this->left_lane_type_;
    }

    /**
     * @brief Assign right lane type.
     * 
     * @param[in] t Right lane type.
     */
    void SetLeftLaneType(LaneType const t)
    {
        this->left_lane_type_ = t;
    }

    /**
     * @brief Access left lane id.
     * 
     * @return Left lane id.
     */
    RoadLaneIdType GetLeftLaneId() const
    {
        return this->left_lane_id_;
    }

    /**
     * @brief Assign left lane id.
     * 
     * @param[in] Left lane id.
     */
    void SetLeftLaneId(RoadLaneIdType const id)
    {
        this->right_lane_id_ = id;
    }

    /**
     * @brief Check if the road boundary has right available lane.
     * 
     * @return true: Has right available lane.
     *         false: Otherwise.
     */
    holo::bool_t HasRightLane() const
    {
        return 0 != this->right_lane_id_;
    }
    
    /**
     * @brief Access right lane type.
     * 
     * @return Right lane type.
     */
    LaneType GetRightLaneType() const
    {
        return this->right_lane_type_;
    }

    /**
     * @brief Assign right lane type.
     * 
     * @param[in] t Right lane type.
     */
    void SetRightLaneType(LaneType const t)
    {
        this->right_lane_type_ = t;
    }

    /**
     * @brief Access right lane id.
     * 
     * @return Right lane id.
     */
    RoadLaneIdType GetRightLaneId() const
    {
        return this->right_lane_id_;
    }

    /**
     * @brief Set right lane id.
     * 
     * @param[in] id Right lane id.
     */
    void SetRightLaneId(RoadLaneIdType const id)
    {
        this->right_lane_id_ = id;
    }

    /**
     * @brief Access geometry.
     * 
     * @return A geometry base reference.
     */
    GeometryType const& GetGeometry() const
    {
        return this->geometry_;
    }

    /**
     * @brief Assign geometry.
     * 
     * @param[in] geometry A geometry base reference.
     */
    void SetGeometry(GeometryType const& geometry)
    {
        ConcreteGeometryType const& g = dynamic_cast<ConcreteGeometryType const&>(geometry);
        this->geometry_ = g;
    }

    /**
     * @brief Assign geometry.
     * 
     * @param[in] geometry A geometry base r-value reference.
     */
    void SetGeometry(GeometryType&& geometry)
    {
        ConcreteGeometryType& g = dynamic_cast<ConcreteGeometryType&>(geometry);
        this->geometry_ = std::move(g);
    }

    /**
     * @brief Access attributes.
     * 
     * @return Attributes..
     */
    AttributeVectorType const& GetAttributes() const
    {
        return this->attributes_;
    }

    /**
     * @brief Assign attributes.
     * 
     * @param[in] attributes Attributes.
     */
    void SetAttributes(AttributeVectorType const& attributes)
    {
        this->attributes_ = attributes;
    }

    /**
     * @brief Assign attributes.
     * 
     * @param[in] attributes Attributes.
     */
    void SetAttributes(AttributeVectorType&& attributes)
    {
        this->attributes_ = std::move(attributes);
    }

private:
    /// Boundary Id.
    RoadBoundaryIdType id_           = 0;
    
    /// Left lane id, if not exist, it should be 0.
    RoadLaneIdType left_lane_id_     = 0;
    /// Right lane id, if not exist, it should be 0.
    RoadLaneIdType right_lane_id_    = 0;

    /// Boundary type.
    BoundaryType boundary_type_ = BoundaryType::kBOUNDARY_TYPE_UNKNOWN;

    /// Left lane type.
    LaneType left_lane_type_    = LaneType::kLANE_TYPE_UNKNOWN;
    /// Right lane type.
    LaneType right_lane_type_   = LaneType::kLANE_TYPE_UNKNOWN;

    /// Boundary length.
    LengthType length_ = 0.0;

    /// Geometry of current boundary.
    ConcreteGeometryType geometry_;

    /// Attributes of current boundary.
    AttributeVectorType attributes_;
}; ///< End of class RoadBoundaryV2.

/// Define a normal boundary type for lanes.
using NormalRoadBoundaryType = RoadBoundaryV2<
    holo::map::service::client::profile::ProfileIdType,
    holo::map::service::client::common::DistanceMeterType,
    holo::map::service::client::common::DistanceMeterType,
    holo::map::service::client::profile::DistanceSegment<
        holo::map::service::client::common::DistanceMeterType,
        RoadBoundaryAttribute<holo::map::service::client::common::DistanceMeterType>>,
    holo::map::service::client::geometry::GeoLine<holo::geometry::Point3d>>;

/// Define a special boundary type for roads.
using SpecialRoadBoundaryType = RoadBoundaryV2<
    holo::map::service::client::profile::ProfileIdType,
    holo::map::service::client::common::DistanceMeterType,
    holo::map::service::client::common::DistanceMeterType,
    holo::map::service::client::profile::IndexSegment<
        holo::map::service::client::common::IndexType,
        RoadBoundaryAttribute<holo::map::service::client::common::DistanceMeterType>>,
    holo::map::service::client::geometry::GeoLine<holo::geometry::Point3d>>;

/// Define smart pointer for NormalRoadBoundaryType.
using NormalRoadBoundarySPtrType = std::shared_ptr<NormalRoadBoundaryType>;
using NormalRoadBoundaryCSPtrType = std::shared_ptr<NormalRoadBoundaryType const>;

/// Define smart pointer for SpecialRoadBoundaryType.
using SpecialRoadBoundarySPtrType = std::shared_ptr<SpecialRoadBoundaryType>;
using SpecialRoadBoundaryCSPtrType = std::shared_ptr<SpecialRoadBoundaryType const>;

namespace marshal
{
/**
 * @addtogroup marshal
 * @{
 *
 */

/**
 * @brief Format a RoadBoundary attribute to a JSON string.
 * 
 * @param[in] rb A special road boundary object.
 * @return A JSON string.
 */
std::string FormatToString(SpecialRoadBoundaryType const& rb);

/**
 * @}
 */
} ///< namespace marshal

/**
 * @}
 */
} ///< namespace application
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_ROAD_BOUNDARY_V2_H_ */