/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file local_map_graph.h
 * @brief Make local map graph information from map data.
 * @author Liu Qikang(liuqikang@holomaitc.com)
 * @date 2020-10-25
 */

#ifndef HOLO_MAP_LOCAL_MAP_GRAPH_LOCAL_MAP_GRAPH_H_
#define HOLO_MAP_LOCAL_MAP_GRAPH_LOCAL_MAP_GRAPH_H_

#include <map>
#include <string>

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/log/hololog.h>

#include <holo/map/feature/local_map_graph/lmg_boundary.h>
#include <holo/map/feature/local_map_graph/lmg_common.h>
#include <holo/map/feature/local_map_graph/lmg_intersection.h>
#include <holo/map/feature/local_map_graph/lmg_lane.h>
#include <holo/map/feature/local_map_graph/lmg_link.h>
#include <holo/map/feature/local_map_graph/lmg_object.h>

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
 * @brief Define local map graph.
 */
template <typename FeatureIdT>
class LocalMapGraph
{
public:
    using FeatureIdType       = FeatureIdT;
    using Coordinate          = holo::common::Coordinate;
    using FeatureBaseType     = FeatureBase<FeatureIdType>;
    using FeatureBaseSPtrType = std::shared_ptr<FeatureBase<FeatureIdType>>;
    using FeatureMapType      = std::map<FeatureIdType, FeatureBaseSPtrType>;

    using Bbox2DType                 = BirdViewBbox2D<holo::geometry::Point2f, holo::float32_t>;
    using Bbox3DType                 = Bbox3D<holo::geometry::Pose3f, holo::float32_t>;
    using Point3dAttributes          = PointAttributesT<holo::geometry::Point3d, holo::float64_t>;
    using IntervalInfoType           = IntervalInfo<FeatureIdType, holo::float64_t, holo::float64_t>;
    using BoundaryIntervalInfoType   = BoundaryIntervalInfo<FeatureIdType, holo::float64_t, holo::float64_t>;
    using LinkType                   = Link<FeatureIdType>;
    using LinkSPtrType               = std::shared_ptr<LinkType>;
    using LaneType                   = Lane<FeatureIdType, holo::geometry::Point3d>;
    using LaneSPtrType               = std::shared_ptr<LaneType>;
    using BoundaryType               = Boundary<FeatureIdType, holo::geometry::Point3d>;
    using BoundarySPtrType           = std::shared_ptr<BoundaryType>;
    using StopLineType               = StopLine<FeatureIdType, holo::geometry::Point3d>;
    using StopLineSPtrType           = std::shared_ptr<StopLineType>;
    using MarkingType                = Marking<FeatureIdType, holo::geometry::Point3f, holo::geometry::Pose3f>;
    using MarkingSPtrType            = std::shared_ptr<MarkingType>;
    using SignType                   = Sign<FeatureIdType, holo::geometry::Point3f>;
    using SignSPtrType               = std::shared_ptr<SignType>;
    using LightType                  = Light<FeatureIdType, holo::geometry::Pose3f>;
    using LightSPtrType              = std::shared_ptr<LightType>;
    using SafeIsLandType             = SafeIsLand<FeatureIdType, holo::geometry::Point2f>;
    using SafeIsLandSPtrType         = std::shared_ptr<SafeIsLandType>;
    using PedestrianCrossingType     = PedestrianCrossing<FeatureIdType, holo::geometry::Point2f>;
    using PedestrianCrossingSPtrType = std::shared_ptr<PedestrianCrossingType>;
    using IntersectionType           = Intersection<FeatureIdType, holo::geometry::Point3f>;
    using IntersectionSPtrType       = std::shared_ptr<IntersectionType>;
    using LocalMapGraphType          = LocalMapGraph<FeatureIdType>;
    using LocalMapGraphSPtrType      = std::shared_ptr<LocalMapGraphType>;

    LocalMapGraph()                     = default;
    ~LocalMapGraph()                    = default;
    LocalMapGraph(LocalMapGraph const&) = default;
    LocalMapGraph(LocalMapGraph&&)      = default;
    LocalMapGraph& operator=(LocalMapGraph const&) = default;
    LocalMapGraph& operator=(LocalMapGraph&&) = default;

    /**
     * @brief Get feature.
     *
     * @param type feature type: Lane, Link, Boundary.
     * @param id feature id.
     * @param base feature base Sptr.
     *
     * @return true or false.
     */
    holo::bool_t GetFeature(holo::map::navigator::graph::FeatureType const type, FeatureIdType const id,
                            FeatureBaseSPtrType& base) const noexcept
    {
        switch (type)
        {
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LINK:
            {
                auto it = this->link_container_.find(id);
                if (it == this->link_container_.end())
                {
                    return false;
                }
                base = it->second;
                break;
            }
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LANE:
            {
                auto it = this->lane_container_.find(id);
                if (it == this->lane_container_.end())
                {
                    return false;
                }
                base = it->second;
                break;
            }
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_BOUNDARY:
            {
                auto it = this->boundary_container_.find(id);
                if (it == this->boundary_container_.end())
                {
                    return false;
                }
                base = it->second;
                break;
            }
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_STOPLINE:
            {
                auto it = this->stopline_container_.find(id);
                if (it == this->stopline_container_.end())
                {
                    LOG(ERROR) << "Find stopline by id failed, stopline id = " << id;
                    return false;
                }
                base = it->second;
                break;
            }
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_MARKING:
            {
                auto it = this->marking_container_.find(id);
                if (it == this->marking_container_.end())
                {
                    LOG(ERROR) << "Find marking by id failed, marking id = " << id;
                    return false;
                }
                base = it->second;
                break;
            }
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LIGHT:
            {
                auto it = this->light_container_.find(id);
                if (it == this->light_container_.end())
                {
                    LOG(ERROR) << "Find light by id failed, light id = " << id;
                    return false;
                }
                base = it->second;
                break;
            }
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_SIGN:
            {
                auto it = this->sign_container_.find(id);
                if (it == this->sign_container_.end())
                {
                    LOG(ERROR) << "Find sign by id failed, sign id = " << id;
                    return false;
                }
                base = it->second;
                break;
            }
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_SAFEISLAND:
            {
                auto it = this->safe_island_container_.find(id);
                if (it == this->safe_island_container_.end())
                {
                    LOG(ERROR) << "Find safeisland by id failed, safeisalnd id = " << id;
                    return false;
                }
                base = it->second;
                break;
            }
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_PEDESTRIAN_CROSSING:
            {
                auto it = this->pedestrian_crossing_container_.find(id);
                if (it == this->pedestrian_crossing_container_.end())
                {
                    LOG(ERROR) << "Find pedestrian crossing by id failed, pedestrian crossing id = " << id;
                    return false;
                }
                base = it->second;
                break;
            }
            case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_INTERSECTION:
            {
                auto it = this->intersection_container_.find(id);
                if (it == this->intersection_container_.end())
                {
                    LOG(ERROR) << "Find intersection by id failed, intersection id = " << id;
                    return false;
                }
                base = it->second;
                break;
            }
            default:
                break;
        }
        return true;
    }

    /**
     * @brief Set links.
     *
     * @param links links.
     */
    void SetLinks(FeatureMapType const& links) noexcept
    {
        this->link_container_ = links;
    }

    /**
     * @brief Get links.
     *
     * @return Const reference of links.
     */
    FeatureMapType const& GetLinks() const noexcept
    {
        return this->link_container_;
    }

    /**
     * @brief Get links.
     *
     * @return Reference of links.
     */
    FeatureMapType& GetLinks() noexcept
    {
        return this->link_container_;
    }

    /**
     * @brief Set lanes.
     *
     * @param lanes lanes.
     */
    void SetLanes(FeatureMapType const& lanes) noexcept
    {
        this->lane_container_ = lanes;
    }

    /**
     * @brief Get lanes.
     *
     * @return Const reference of lanes.
     */
    FeatureMapType const& GetLanes() const noexcept
    {
        return this->lane_container_;
    }

    /**
     * @brief Get lanes.
     *
     * @return Reference of lanes.
     */
    FeatureMapType& GetLanes() noexcept
    {
        return this->lane_container_;
    }

    /**
     * @brief Set boundaries.
     *
     * @param boundaries boundaries.
     */
    void SetBoundaries(FeatureMapType const& boundaries) noexcept
    {
        this->boundary_container_ = boundaries;
    }

    /**
     * @brief Get boundaries.
     *
     * @return Const reference of boundaries.
     */
    FeatureMapType const& GetBoundaries() const noexcept
    {
        return this->boundary_container_;
    }

    /**
     * @brief Get boundaries.
     *
     * @return Reference of boundaries.
     */
    FeatureMapType& GetBoundaries() noexcept
    {
        return this->boundary_container_;
    }

    /**
     * @brief Set stoplines.
     *
     * @param stoplines stoplines.
     */
    void SetStopLines(FeatureMapType const& stoplines) noexcept
    {
        this->stopline_container_ = stoplines;
    }

    /**
     * @brief Get stoplines.
     *
     * @return Reference of stoplines.
     */
    FeatureMapType const& GetStopLines() const noexcept
    {
        return this->stopline_container_;
    }

    /**
     * @brief Set markings.
     *
     * @param markings markings.
     */
    void SetMarkings(FeatureMapType const& markings) noexcept
    {
        this->marking_container_ = markings;
    }

    /**
     * @brief Get markings.
     *
     * @return Reference of markings.
     */
    FeatureMapType const& GetMarkings() const noexcept
    {
        return this->marking_container_;
    }

    /**
     * @brief Set signs.
     *
     * @param signs signs.
     */
    void SetSigns(FeatureMapType const& signs) noexcept
    {
        this->sign_container_ = signs;
    }

    /**
     * @brief Get signs.
     *
     * @return Reference of signs.
     */
    FeatureMapType const& GetSigns() const noexcept
    {
        return this->sign_container_;
    }

    /**
     * @brief Set lights.
     *
     * @param lights lights.
     */
    void SetLights(FeatureMapType const& lights) noexcept
    {
        this->light_container_ = lights;
    }

    /**
     * @brief Get lights.
     *
     * @return Reference of lights.
     */
    FeatureMapType const& GetLights() const noexcept
    {
        return this->light_container_;
    }

    /**
     * @brief Set safe island.
     *
     * @param safe_islands safe islands.
     */
    void SetSafeIslands(FeatureMapType const& safe_islands) noexcept
    {
        this->safe_island_container_ = safe_islands;
    }

    /**
     * @brief Get safe islands.
     *
     * @return Reference of safe islands.
     */
    FeatureMapType const& GetSafeIslands() const noexcept
    {
        return this->safe_island_container_;
    }

    /**
     * @brief Set pedestrian crossing.
     *
     * @param pedestrian_crossing pedestrian crossing.
     */
    void SetPedestrianCrossing(FeatureMapType const& pedestrian_crossing) noexcept
    {
        this->pedestrian_crossing_container_ = pedestrian_crossing;
    }

    /**
     * @brief Get pedestrian crossing info.
     *
     * @return Reference of pedestrian crossing.
     */
    FeatureMapType const& GetPedestrianCrossing() const noexcept
    {
        return this->pedestrian_crossing_container_;
    }

    /**
     * @brief Set intersection.
     *
     * @param intersection intersection
     */
    void SetIntersection(FeatureMapType const& intersection) noexcept
    {
        this->intersection_container_ = intersection;
    }

    /**
     * @brief Get intersection
     *
     * @return Reference of intersection
     */
    FeatureMapType const& GetIntersection() const noexcept
    {
        return this->intersection_container_;
    }

    /**
     * @brief Set coordinate.
     *
     * @param coordinate coordinate.
     */
    void SetCoordinate(Coordinate const& coordinate) noexcept
    {
        this->coordinate_ = coordinate;
    }

    /**
     * @brief Get coordinate.
     *
     * @return Reference of coordinate.
     */
    Coordinate const& GetCoordinate() const noexcept
    {
        return this->coordinate_;
    }

    /**
     * @brief Set timestamp.
     *
     * @param time timestamp info.
     */
    void SetTimestamp(holo::common::Timestamp const& time) noexcept
    {
        this->timestamp_ = time;
    }

    /**
     * @brief Get timestamp.
     *
     * @return Reference of timestamp.
     */
    holo::common::Timestamp const& GetTimestamp() const noexcept
    {
        return this->timestamp_;
    }

private:
    FeatureMapType          link_container_;                 /// link map
    FeatureMapType          lane_container_;                 /// lane map
    FeatureMapType          boundary_container_;             /// boundary map
    FeatureMapType          stopline_container_;             /// stopline map
    FeatureMapType          light_container_;                /// light map
    FeatureMapType          sign_container_;                 /// sign map
    FeatureMapType          marking_container_;              /// marking map
    FeatureMapType          safe_island_container_;          /// safe is land map
    FeatureMapType          pedestrian_crossing_container_;  /// pedestrian crossing
    FeatureMapType          intersection_container_;
    holo::common::Timestamp timestamp_;       /// timestamp
    Coordinate              coordinate_;      /// coordinate:WGS84
    holo::uint8_t           sensor_id_ = 0U;  /// sensor info
};

using LocalMapGraphType     = LocalMapGraph<holo::uint64_t>;
using LocalMapGraphSPtrType = std::shared_ptr<LocalMapGraphType>;

using Bbox2DType                 = LocalMapGraphType::Bbox2DType;
using Bbox3DType                 = LocalMapGraphType::Bbox3DType;
using Point3dAttributes          = LocalMapGraphType::Point3dAttributes;
using IntervalInfoType           = LocalMapGraphType::IntervalInfoType;
using BoundaryIntervalInfoType   = LocalMapGraphType::BoundaryIntervalInfoType;
using FeatureBaseType            = LocalMapGraphType::FeatureBaseType;
using FeatureBaseSPtrType        = LocalMapGraphType::FeatureBaseSPtrType;
using BoundaryType               = LocalMapGraphType::BoundaryType;
using BoundarySPtrType           = LocalMapGraphType::BoundarySPtrType;
using LaneType                   = LocalMapGraphType::LaneType;
using LaneSPtrType               = LocalMapGraphType::LaneSPtrType;
using LinkType                   = LocalMapGraphType::LinkType;
using LinkSPtrType               = LocalMapGraphType::LinkSPtrType;
using StopLineType               = LocalMapGraphType::StopLineType;
using StopLineSPtrType           = LocalMapGraphType::StopLineSPtrType;
using MarkingType                = LocalMapGraphType::MarkingType;
using MarkingSPtrType            = LocalMapGraphType::MarkingSPtrType;
using SignType                   = LocalMapGraphType::SignType;
using SignSPtrType               = LocalMapGraphType::SignSPtrType;
using LightType                  = LocalMapGraphType::LightType;
using LightSPtrType              = LocalMapGraphType::LightSPtrType;
using SafeIsLandType             = LocalMapGraphType::SafeIsLandType;
using SafeIsLandSPtrType         = LocalMapGraphType::SafeIsLandSPtrType;
using PedestrianCrossingType     = LocalMapGraphType::PedestrianCrossingType;
using PedestrianCrossingSPtrType = LocalMapGraphType::PedestrianCrossingSPtrType;
using IntersectionType           = LocalMapGraphType::IntersectionType;
using IntersectionSPtrType       = LocalMapGraphType::IntersectionSPtrType;

using BoundaryIntervalType       = BoundaryType::BoundaryIntervalInfoType;
using BoundaryIntervalVectorType = BoundaryType::BoundaryIntervalInfoVectorType;

using SpeedLimitIntervalType       = LaneType::SpeedLimitIntervalType;
using SpeedLimitIntervalVectorType = LaneType::SpeedLimitIntervalVectorType;

using WidthIntervalType       = LaneType::WidthIntervalType;
using WidthIntervalVectorType = LaneType::WidthIntervalVectorType;

/**
 * @brief Traits feature types from local map.
 */
template <typename T>
struct FeatureTraits
{
    using RawType     = T;
    using PointerType = T*;
    using SPtrType    = std::shared_ptr<T>;
};

/**
 * @brief Traits feature types from local map.
 */
template <typename T>
struct FeatureTraits<std::shared_ptr<T>>
{
    using RawType     = T;
    using PointerType = T*;
    using SPtrType    = std::shared_ptr<T>;
};

/**
 * @brief Get concrete feature.
 *
 * @param base feature base Sptr.
 * @param result output feature result.
 *
 * @return true or false.
 */
template <typename Feature>
holo::bool_t GetConcreteFeature(FeatureBaseSPtrType const& base, typename FeatureTraits<Feature>::SPtrType& result)
{
    if (!base)
    {
        LOG(ERROR) << "base pointer is null.";
        return false;
    }

    holo::map::navigator::graph::FeatureType type = base->GetType();
    result                                        = nullptr;
    switch (type)
    {
        case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LINK:
        {
            result = std::dynamic_pointer_cast<typename FeatureTraits<Feature>::RawType>(base);
            break;
        }
        case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LANE:
        {
            result = std::dynamic_pointer_cast<typename FeatureTraits<Feature>::RawType>(base);
            break;
        }
        case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_BOUNDARY:
        {
            result = std::dynamic_pointer_cast<typename FeatureTraits<Feature>::RawType>(base);
            break;
        }
        case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_STOPLINE:
        {
            result = std::dynamic_pointer_cast<typename FeatureTraits<Feature>::RawType>(base);
            break;
        }
        case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_MARKING:
        {
            result = std::dynamic_pointer_cast<typename FeatureTraits<Feature>::RawType>(base);
            break;
        }
        case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LIGHT:
        {
            result = std::dynamic_pointer_cast<typename FeatureTraits<Feature>::RawType>(base);
            break;
        }
        case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_SIGN:
        {
            result = std::dynamic_pointer_cast<typename FeatureTraits<Feature>::RawType>(base);
            break;
        }
        case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_SAFEISLAND:
        {
            result = std::dynamic_pointer_cast<typename FeatureTraits<Feature>::RawType>(base);
            break;
        }
        case holo::map::navigator::graph::FeatureType::FEATURE_TYPE_PEDESTRIAN_CROSSING:
        {
            result = std::dynamic_pointer_cast<typename FeatureTraits<Feature>::RawType>(base);
            break;
        }
        default:
            break;
    }
    if (result == nullptr)
    {
        LOG(ERROR) << "Feature init failed!";
        return false;
    }
    return true;
}

/**
 * @brief Traverse feature to get feature id vector.
 *
 * @param feature_map feature map: lane_map, link_map, boundary_map, .etc
 *
 * @return std::vector<FeatureId>, feature id sequence.
 */
template <typename FeatureId, typename FeatureMap>
holo::bool_t TraverseFeature(FeatureMap const& feature_map, std::vector<FeatureId>& ids)
{
    if (feature_map.empty())
    {
        LOG(ERROR) << "Traverse feature failed, feature map is empty!";
        return false;
    }
    for (auto& feature : feature_map)
    {
        ids.push_back(feature.first);
    }
    return true;
}

/**
 * @brief Get feature.
 *
 * @param local_map_graph local map graph ptr.
 * @param type feature type: LaneType, LinkType, BoundaryType, StopLineType, LightType, SignType, MarkingType,
 * SafeIsLandType, PedestrianCrossingType
 * @param id feature id.
 * @param feature output feature: Lane, Link, Boundary, StopLine, Light, Sign, Marking, SafeIsLand, PedestrianCrossing.
 *
 * @return true or false.
 *
 * @example holo::map::navigator::graph::LocalMapGraphSPtrType graph = nullptr;
    holo::map::navigator::graph::FeatureType           type  =
 holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LANE; holo::uint64_t                          id    = 1U;
    holo::map::navigator::graph::FeatureTraits<holo::map::navigator::graph::LaneType>::SPtrType traits = nullptr;
    holo::map::navigator::graph::GetFeature<holo::map::navigator::graph::FeatureType, holo::uint64_t,
    holo::map::navigator::graph::LaneType>(graph, type, id, traits);
 */
template <typename FeatureType, typename FeatureId, typename Feature>
holo::bool_t GetFeature(LocalMapGraphSPtrType local_map_graph, FeatureType const type, FeatureId const id,
                        typename FeatureTraits<Feature>::SPtrType& feature)
{
    feature                                                       = nullptr;
    typename FeatureTraits<FeatureBase<FeatureId>>::SPtrType base = nullptr;
    local_map_graph->GetFeature(type, id, base);

    if (!GetConcreteFeature<Feature>(base, feature))
    {
        LOG(ERROR) << "Get concrete feature failed, feature id = " << id;
        return false;
    }
    return true;
}

/**
 * @}
 */
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_NAVIGATOR_SERVICE_LOCAL_MAP_GRAPH_H_ */
