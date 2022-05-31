/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_group.h
 * @brief lane_group.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-11"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_LANE_GROUP_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_LANE_GROUP_H_

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

class LaneGroup : public ProfileBase
{
public:
    using ConcreteGeometryType  = geometry::GeoLine<holo::geometry::Point3d>;

    LaneGroup();
    virtual ~LaneGroup();

    static std::string const& Name();

    virtual std::string const& GetName() const override;

    virtual ProfileIdVectorType const& GetTileIds() const;

    virtual Distance GetLength() const;

    ProfileIdVectorType const& GetLaneIds() const;

    ProfileIdVectorType const& GetLaneBoundaryIds() const;

    ProfileIdType GetRoadId() const;
    ProfileIdType GetLeftLaneBoundaryId() const;
    ProfileIdType GetRightLaneBoundaryId() const;

    ProfileIdVectorType const& GetSucceedingIds() const;
    ProfileIdVectorType const& GetPrecedingIds() const;

    virtual GeometryType const& GetGeometry() const override;
    virtual void SetGeometry(GeometryType const& g) override;
    virtual void SetGeometry(GeometryType&& g) override;

private:
    class LaneGroupInner;
    std::unique_ptr<LaneGroupInner> inner_;
};

using LaneGroupSPtrType = std::shared_ptr<LaneGroup>;
using LaneGroupCSPtrType = std::shared_ptr<LaneGroup const>;

} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_LANE_GROUP_H_ */