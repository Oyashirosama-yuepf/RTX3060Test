/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object.h
 * @brief object.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-11"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_OBJECT_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_OBJECT_H_

#include <holo/map/service/client/common/geometry.h>
#include <holo/map/service/client/profile/base.h>

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

class ObjectBase : public ProfileBase
{
public:

    ObjectBase() : ProfileBase(ProfileType::kOBJECT)
    {}

    explicit ObjectBase(ProfileObjectType const t) : ProfileBase(ProfileType::kOBJECT), type_(t)
    {}

    virtual ~ObjectBase()
    {}
    
    virtual ProfileObjectType GetType()
    {
        return this->type_;
    }

    virtual ProfileIdVectorType const& GetTileIds() const override;

protected:
    ProfileObjectType type_;
    ProfileIdVectorType tile_ids_;
};

template <typename Point, typename Geometry>
class ObjectSign : public ObjectBase
{
public:
    using GeometryType = Geometry;

    ObjectSign() : ObjectBase(ProfileObjectType::kOBJECT_TYPE_SIGN)
    {}

    virtual ~ObjectSign()
    {}

    std::string const& GetSemanteme() const noexcept
    {
        return this->semanteme_;
    }

    void SetSemanteme(std::string const& s)
    {
        this->semanteme_ = s;
    }

    virtual GeometryType const& GetGeometry()
    {
        return this->geometry_;
    }

    virtual void SetGeometry(GeometryType const& g)
    {
        this->geometry_ = g;
    }

    virtual void SetGeometry(GeometryType && g)
    {
        this->geometry_ = g;
    }
private:
    std::string semanteme_;
    GeometryType geometry_;    
};

template <typename Point, typename Geometry>
class ObjectPole : public ObjectBase
{
public:
    using GeometryType      = Geometry;
    using RadiusType        = holo::uint32_t;
    using HeightType        = holo::uint32_t;

    ObjectPole() : ObjectBase(ProfileObjectType::kOBJECT_TYPE_POLE)
    {
    }

    virtual ~ObjectPole()
    {}

    RadiusType GetTopRadius() const noexcept
    {
        return this->top_radius_;
    }

    void SetTopRadius(RadiusType const r)
    {
        this->top_radius_ = r;
    }

    RadiusType GetBottomRadius() const noexcept
    {
        return this->bottom_radius_;
    }

    void SetBottomRadius(RadiusType const r)
    {
        this->bottom_radius_ = r;
    }

    HeightType GetHeight() const noexcept
    {
        return this->height_;
    }

    void SetHeight(HeightType const h)
    {
        this->height_ = h;
    }

    GeometryType const& GetGeometry()
    {
        return this->geometry_;
    }

    void SetGeometry(GeometryType const& g)
    {
        this->geometry_ = g;
    }

    void SetGeometry(GeometryType && g)
    {
        this->geometry_ = g;
    }

private:
    GeometryType geometry_;
    RadiusType top_radius_;
    RadiusType bottom_radius_;
    HeightType height_;
};

using ObjectBase3d = ObjectBase;

using ObjectTrafficSing3d = ObjectSign<holo::geometry::Point3d, holo::map::service::client::geometry::GeoPolygon<holo::geometry::Point3d>>;

using ObjectLightingPole3d = ObjectPole<holo::geometry::Point3d, holo::map::service::client::geometry::GeoMultiPoint<holo::geometry::Point3d>>;

} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_OBJECT_H_ */
