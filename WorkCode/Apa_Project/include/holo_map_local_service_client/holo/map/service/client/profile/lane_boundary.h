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

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_LANE_BOUNDARY_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_LANE_BOUNDARY_H_

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
namespace profile
{

class LaneBoundary : public ProfileBase
{
public:
    using Scalar                = holo::float64_t;
    using Distance              = holo::float64_t;
    using ConcreteGeometryType  = geometry::GeoLine<holo::geometry::Point3d>;
    using SequenceType          = holo::uint64_t;

    enum class Style : holo::uint8_t
    {
        kSTYLE_UNKNOWN = 0,
        kSTYLE_SINGLE_SOLID_LINE,
        kSTYLE_DOUBLE_SOLID_LINE,
        kSTYLE_SINGLE_DASHED_LINE,
        kSTYLE_DOUBLE_DASHED_LINE,
        kSTYLE_OTHERS,
    };

    enum class Color : holo::uint8_t
    {
        kCOLOR_UNKNOWN = 0,
        kCOLOR_WHITE,
        kCOLOR_YELLOW,
    };

    struct Attribute
    {
        Style style;
        Color color;
        Scalar width;
    };

    enum class Type : holo::uint8_t
    {
        kTYPE_UNKNOWN = 0,
        kTYPE_REGULAR,         ///< Lane boundary painted on the ground.
        kTYPE_BARRIER,         ///< Guardrail both side of road.
        kTYPE_CURB,            ///< Curb both side of road, lower than barrier usually.
    };

    using AttributeType = DistanceSegment<Scalar, Attribute>;
    using AttributeVectorType = std::vector<AttributeType>;

    static std::string FormatToString(AttributeType const& attribute);
    static std::string FormatToString(AttributeVectorType const& attributes);

    LaneBoundary();
    virtual ~LaneBoundary();

    static std::string const& Name();

    virtual std::string const& GetName() const override;

    virtual ProfileIdVectorType const& GetTileIds() const;
    
    Type GetBoundaryType() const;

    void SetBoundaryType(Type const t);

    virtual Distance GetLength() const;
    virtual void SetLength(Distance const d);

    ProfileIdType GetLeftLaneId() const;
    void SetLeftLaneId(ProfileIdType const id);

    ProfileIdType GetRightLaneId() const;
    void SetRightLaneId(ProfileIdType const id);

    ProfileIdType GetLaneGroupId() const;
    void SetLaneGroupId(ProfileIdType const id);

    SequenceType GetBoundarySeq() const;
    void SetBoundarySeq(SequenceType const seq);

    ProfileIdVectorType const& GetSucceedingIds() const;
    void SetSucceedingIds(ProfileIdVectorType const& ids);

    ProfileIdVectorType const& GetPrecedingIds() const;
    void SetPrecedingIds(ProfileIdVectorType const& ids);

    virtual GeometryType const& GetGeometry() const override;
    virtual void SetGeometry(GeometryType const& g) override;
    virtual void SetGeometry(GeometryType&& g) override;

    AttributeVectorType const& GetAttributes() const;
    void SetAttributes(AttributeVectorType const& attributes);
    void SetAttributes(AttributeVectorType&& attributes);

    /**
     * @brief Check if the current boundary is a virtual lane boundary,
     *        in other words the boundary type is NO_MARKING.
     * 
     * @detail The virtual boundary is an imaginary boundary, which does not
     *         actually exist.
     * @return true: Is virtual boundary.
     *         false: Isn't virtual boundary.
     */
    holo::bool_t IsVirtualBoundary() const;

    /**
     * @brief Check if the current boundary has painted lane boundary info.
     *
     * @return true: Has painted boundary info.
     *         false: Hasn't painted boundary info.
     */
    holo::bool_t HasPaintedBoundary() const;

    static holo::bool_t CheckLaneBoundaryAttributes(AttributeVectorType const& attributes);

private:
    class LaneBoundaryInner;
    std::unique_ptr<LaneBoundaryInner> inner_;
};

using LaneBoundarySPtrType = std::shared_ptr<LaneBoundary>;
using LaneBoundaryCSPtrType = std::shared_ptr<LaneBoundary const>;

} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_LANE_BOUNDARY_H_ */
