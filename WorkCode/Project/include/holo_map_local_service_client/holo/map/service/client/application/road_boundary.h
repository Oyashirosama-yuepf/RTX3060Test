/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_boundary.h
 * @brief lane_boundary.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-11"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_ROAD_BOUNDARY_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_ROAD_BOUNDARY_H_

#include <holo/geometry/point3.h>
#include <holo/map/service/client/common/geometry.h>
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

class RoadBoundary
{
public:
    using Scalar    = holo::float64_t;
    using Distance  = Scalar;

    using ProfileType   = holo::map::service::client::profile::ProfileType;
    using ProfileIdType = holo::map::service::client::profile::ProfileIdType;

    using GeometryType 		    = holo::map::service::client::geometry::GeoBase;
    using ConcreteGeometryType  = holo::map::service::client::geometry::GeoLine<holo::geometry::Point3d>;

    enum class BoundaryType : holo::uint8_t
    {
        kBOUNDARY_TYPE_UNKNOWN = 0,
        kBOUNDARY_TYPE_REGULAR,
        kBOUNDARY_TYPE_BARRIER,
        kBOUNDARY_TYPE_CURB,
    };

    enum class BoundaryStyle : holo::uint8_t
    {
        kBOUNDARY_STYLE_UNKNOWN = 0,
        kBOUNDARY_STYLE_SINGLE_SOLID_LINE,
        kBOUNDARY_STYLE_DOUBLE_SOLID_LINE,
        kBOUNDARY_STYLE_SINGLE_DASHED_LINE,
        kBOUNDARY_STYLE_DOUBLE_DASHED_LINE,
        kBOUNDARY_STYLE_OTHER,
    };
    
    enum class BoundaryColor : holo::uint8_t
    {
        kBOUNDARY_COLOR_UNKNOWN = 0,
        kBOUNDARY_COLOR_YELLOW,
        kBOUNDARY_COLOR_WHITE,
    };

    enum class LaneType : holo::uint8_t
    {
        kLANE_TYPE_UNKNOWN = 0,
        kLANE_TYPE_EXPRESS,
        kLANE_TYPE_EMERGENCY,
        kLANE_TYPE_ENTRY,
        kLANE_TYPE_EXIT,
        kLANE_TYPE_ACCELERATE,
        kLANE_TYPE_DECELERATE,
        kLANE_TYPE_HARD_SHOULDER,
        kLANE_TYPE_RAMP,
        kLANE_TYPE_OTHER,
    };

    struct Attribute
    {
        BoundaryStyle style = BoundaryStyle::kBOUNDARY_STYLE_UNKNOWN;
        BoundaryColor color = BoundaryColor::kBOUNDARY_COLOR_UNKNOWN;
        Distance      width = 0.0;
    };

    using AttributeType = holo::map::service::client::profile::DistanceSegment<Scalar, Attribute>;
    using AttributeVectorType = std::vector<AttributeType>;

    static std::string FormatToString(AttributeType const& attribute);
    static std::string FormatToString(AttributeVectorType const& attributes);

    RoadBoundary();
    virtual ~RoadBoundary();
    
    ProfileIdType GetId() const;
    
    BoundaryType GetBoundaryType() const;

    virtual Distance GetLength() const;
    virtual void SetLength(Distance const d);

    holo::bool_t HasLeftLane() const;

    LaneType GetLeftLaneType() const;
    void SetLeftLaneType(LaneType const t);

    ProfileIdType GetLeftLaneId() const;
    void SetLeftLaneId(ProfileIdType const id);

    holo::bool_t HasRightLane() const;
    
    LaneType GetRightLaneType() const;
    void SetRightLaneType(LaneType const t);

    ProfileIdType GetRightLaneId() const;
    void SetRightLaneId(ProfileIdType const id);

    virtual GeometryType const& GetGeometry() const;
    virtual void SetGeometry(GeometryType const& g);
    virtual void SetGeometry(GeometryType&& g);

    AttributeVectorType const& GetAttributes() const;
    void SetAttributes(AttributeVectorType const& attributes);
    void SetAttributes(AttributeVectorType&& attributes);

private:
    class RoadBoundaryInner;
    std::unique_ptr<RoadBoundaryInner> inner_;

    friend class RoadStructureBuilder;
};

using RoadBoundarySPtrType = std::shared_ptr<RoadBoundary>;
using RoadBoundaryCSPtrType = std::shared_ptr<RoadBoundary const>;

} ///< namespace application
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_ROAD_BOUNDARY_H_ */
