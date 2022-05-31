/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_object_builder.h
 * @brief builder for local_map_graph's object
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-27
 */

#ifndef HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_BUILDER_OBJECT_H_
#define HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_BUILDER_OBJECT_H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/feature/local_map_graph/adaptor/lmg_builder_utility.h>
#include <holo/map/feature/local_map_graph/lmg_common.h>
#include <holo/map/feature/local_map_graph/lmg_object.h>
#include <holo/map/format/base/base.h>
#include <holo/map/format/base/object_safe_island.h>
#include <holo/map/service/client/engine/helper.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace graph
{
namespace builder
{
class LmgObjectBuilder
{
public:
    using StopLineBuilderType     = holo::map::navigator::graph::StopLine<holo::uint64_t, holo::geometry::Point3d>;
    using StopLineBuilderSPtrType = std::shared_ptr<StopLineBuilderType>;
    using StopLineFormatType      = holo::map::format::ObjectStopLine;
    using StopLineFormatPtrType   = holo::map::format::PtrObjectStopLine;

    using MarkingBuilderType =
        holo::map::navigator::graph::Marking<holo::uint64_t, holo::geometry::Point3f, holo::geometry::Pose3f>;
    using MarkingBuilderSPtrType = std::shared_ptr<MarkingBuilderType>;
    using MarkingFormatType      = holo::map::format::ObjectRegionalInfo;
    using MarkingFormatPtrType   = holo::map::format::PtrObjectRegionalInfo;

    using SignBuilderType     = holo::map::navigator::graph::Sign<holo::uint64_t, holo::geometry::Point3f>;
    using SignBuilderSPtrType = std::shared_ptr<SignBuilderType>;
    using SignFormatType      = holo::map::format::ObjectTrafficSign;
    using SignFormatPtrType   = holo::map::format::PtrObjectTrafficSign;

    using LightBuilderType     = holo::map::navigator::graph::Light<holo::uint64_t, holo::geometry::Pose3f>;
    using LightBuilderSPtrType = std::shared_ptr<LightBuilderType>;
    using LightFormatType      = holo::map::format::ObjectTrafficLight;
    using LightFormatPtrType   = holo::map::format::PtrObjectTrafficLight;

    using SafeIsLandBuilderType     = holo::map::navigator::graph::SafeIsLand<holo::uint64_t, holo::geometry::Point2f>;
    using SafeIsLandBuilderSPtrType = std::shared_ptr<SafeIsLandBuilderType>;
    using SafeIsLandFormatType      = holo::map::format::ObjectSafeIsland;
    using SafeIsLandFormatPtrType   = holo::map::format::PtrObjectSafeIsland;

    using PedestrianCrossingBuilderType =
        holo::map::navigator::graph::PedestrianCrossing<holo::uint64_t, holo::geometry::Point2f>;
    using PedestrianCrossingBuilderSPtrType = std::shared_ptr<PedestrianCrossingBuilderType>;
    using PedestrianCrossingFormatType      = holo::map::format::ObjectPedestrianCrossing;
    using PedestrianCrossingFormatPtrType   = holo::map::format::PtrObjectPedestrianCrossing;

public:
    LmgObjectBuilder() = default;

    virtual ~LmgObjectBuilder() = default;

    holo::bool_t BuildStopLine(StopLineFormatPtrType const& ptr_stopline, StopLineBuilderSPtrType& stop_line);

    holo::bool_t BuildMarking(MarkingFormatPtrType const& ptr_marking, holo::common::LocalMapOdometryd const& odometry,
                              MarkingBuilderSPtrType& marking);

    holo::bool_t BuildSign(SignFormatPtrType const& ptr_sign, SignBuilderSPtrType& sign);

    holo::bool_t BuildLight(LightFormatPtrType const& ptr_light, holo::common::LocalMapOdometryd const& odometry,
                            LightBuilderSPtrType& light);

    holo::bool_t BuildSafeIsland(SafeIsLandFormatPtrType const&         ptr_safe_island,
                                 holo::common::LocalMapOdometryd const& odometry,
                                 SafeIsLandBuilderSPtrType&             safe_island);

    holo::bool_t BuildPedestrianCrossing(PedestrianCrossingFormatPtrType const& ptr_pedestrian_crossing,
                                         holo::common::LocalMapOdometryd const& odometry,
                                         PedestrianCrossingBuilderSPtrType&     pedestrian_crossing);

private:
    holo::bool_t adaptSignType(format::PtrObjectTrafficSign const& ptr_sign, SignBuilderType::SignType& sign_type);
    void         adaptMarkingType(MarkingFormatType::ObjectArrowType input, MarkingBuilderType::MarkType& output);
};
}  // namespace builder
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_BUILDER_OBJECT_H_