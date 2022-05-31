/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane.h
 * @brief lane.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-11"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_LANE_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_LANE_H_

#include <string>

#include <holo/map/service/client/profile/base.h>
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

class Lane : public ProfileBase
{
public:
    using ScalarType = holo::float64_t;

    using DistanceType = ScalarType;
    using SequenceType = holo::int8_t;

    using WidthValueType = ScalarType;

    using ConcreteGeometryType  = geometry::GeoLine<holo::geometry::Point3d>;



    enum LaneTransType
    {
        kLANE_TRANS_TYPE_UNKNOWN = 0,
    };

    using WidthType = DistanceSegment<DistanceType, WidthValueType>;
    using WidthVectorType = std::vector<WidthType>;

    static std::string FormatToString(WidthType const& width);
    static std::string FormatToString(WidthVectorType const& widths);

    Lane();
    virtual ~Lane();

    static std::string const& Name();

    virtual std::string const& GetName() const override;

    virtual ProfileIdVectorType const& GetTileIds() const;

    LaneTransType GetLaneTransType() const
    {
        return LaneTransType::kLANE_TRANS_TYPE_UNKNOWN;
    }

    ScalarType GetLength() const;

    SequenceType GetSequence() const;

    ProfileIdType GetLaneGroupId() const;

    ProfileIdType GetLeftLaneBoundaryId() const;
    ProfileIdType GetRightLaneBoundaryId() const;

    ProfileIdVectorType const& GetSucceedingIds() const;
    ProfileIdVectorType const& GetPrecedingIds() const;

    virtual GeometryType const& GetGeometry() const override;
    virtual void SetGeometry(GeometryType const& g) override;
    virtual void SetGeometry(GeometryType&& g) override;

private:
    class LaneInner;
    std::unique_ptr<LaneInner> inner_;
};

using LaneSPtrType = std::shared_ptr<Lane>;
using LaneCSPtrType = std::shared_ptr<Lane const>;

} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_LANE_H_ */