#ifndef HOLO_MAP_ADAPTER_COMMON_STRUCTS_H_
#define HOLO_MAP_ADAPTER_COMMON_STRUCTS_H_

#include <map>
#include <vector>

#include <holo/common/coordinate.h>
#include <holo/map/common/classes/latlon.h>
#include <holo/map/common/common_type_define.h>
#include <holo/map/format/base/geofence.h>
#include <holo/map/format/base/header.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/format/base/lane_boundary.h>
#include <holo/map/format/base/lane_group.h>
#include <holo/map/format/base/lane_width_info.h>
#include <holo/map/format/base/object_info.h>
#include <holo/map/format/base/object_linear_info.h>
#include <holo/map/format/base/object_pedestrian_crossing.h>
#include <holo/map/format/base/object_regional_info.h>
#include <holo/map/format/base/object_stop_line.h>
#include <holo/map/format/base/object_traffic_light.h>
#include <holo/map/format/base/object_traffic_light_group.h>
#include <holo/map/format/base/object_traffic_sign.h>
#include <holo/map/format/base/road.h>
#include <holo/map/format/base/sd_road.h>
#include <holo/map/format/base/sd_node.h>
#include <holo/map/format/base/tile.h>
#include <holo/map/format/common/geo_line.h>

namespace holo
{
namespace map
{
namespace adapter
{
/**
 * @addtogroup adapter
 * @{
 *
 */

using FeatureType           = holo::map::format::Base::FeatureType;
using FeatureIdType         = holo::map::MapFeatureIdType;
using FeatureIdVectorType   = holo::map::MapFeatureIdVectorType;

using HeaderType                    = holo::map::format::Header;
using RoadType                      = holo::map::format::Road;
using SdRoadType                    = holo::map::format::SdRoad;
using SdNodeType                    = holo::map::format::SdNode;
using LaneType                      = holo::map::format::Lane;
using LaneGroupType                 = holo::map::format::LaneGroup;
using LaneBoundaryType              = holo::map::format::LaneBoundary;
using ObjectInfoType                = holo::map::format::ObjectInfo;
using ObjectLinearInfoType          = holo::map::format::ObjectLinearInfo;
using ObjectPedestrianCrossingType  = holo::map::format::ObjectPedestrianCrossing;
using ObjectRegionalInfoType        = holo::map::format::ObjectRegionalInfo;
using ObjectStopLineType            = holo::map::format::ObjectStopLine;
using ObjectTrafficLightType        = holo::map::format::ObjectTrafficLight;
using ObjectTrafficLightGroupType   = holo::map::format::ObjectTrafficLightGroup;
using ObjectTrafficSignType         = holo::map::format::ObjectTrafficSign; 
using TileType                      = holo::map::format::Tile;
using GeofenceType                  = holo::map::format::Geofence;

using HeaderSPtrType                    = holo::map::format::PtrHeader;
using TileSPtrType                      = holo::map::format::PtrTile;
using RoadSPtrType                      = holo::map::format::PtrRoad;
using SdRoadSPtrType                    = holo::map::format::PtrSdRoad;
using SdNodeSPtrType                    = holo::map::format::PtrSdNode;
using LaneSPtrType                      = holo::map::format::PtrLane;
using LaneGroupSPtrType                 = holo::map::format::PtrLaneGroup;
using LaneBoundarySPtrType              = holo::map::format::PtrLaneBoundary;
using ObjectInfoSPtrType                = holo::map::format::PtrObjectInfo;
using ObjectLinearInfoSPtrType          = holo::map::format::PtrObjectLinearInfo;
using ObjectPedestrianCrossingSPtrType  = holo::map::format::PtrObjectPedestrianCrossing;
using ObjectRegionalInfoSPtrType        = holo::map::format::PtrObjectRegionalInfo;
using ObjectStopLineSPtrType            = holo::map::format::PtrObjectStopLine;
using ObjectTrafficLightSPtrType        = holo::map::format::PtrObjectTrafficLight;
using ObjectTrafficLightGroupSPtrType   = holo::map::format::PtrObjectTrafficLightGroup;
using ObjectTrafficSignSPtrType         = holo::map::format::PtrObjectTrafficSign;
using GeofenceSPtrType                  = holo::map::format::PtrGeofence;

using HeaderCSPtrType                       = holo::map::format::PtrHeader const;
using TileCSPtrType                         = holo::map::format::PtrTile const;
using RoadCSPtrType                         = holo::map::format::PtrRoad const;
using SdRoadCSPtrType                       = holo::map::format::PtrSdRoad const;
using SdNodeCSPtrType                       = holo::map::format::PtrSdNode const;
using LaneCSPtrType                         = holo::map::format::PtrLane const;
using LaneGroupCSPtrType                    = holo::map::format::PtrLaneGroup const;
using LaneBoundaryCSPtrType                 = holo::map::format::PtrLaneBoundary const;
using ObjectInfoCSPtrType                   = holo::map::format::PtrObjectInfo const;
using ObjectLinearInfoCSPtrType             = holo::map::format::PtrObjectLinearInfo const;
using ObjectPedestrianCrossingCSPtrType     = holo::map::format::PtrObjectPedestrianCrossing const;
using ObjectRegionalInfoCSPtrType           = holo::map::format::PtrObjectRegionalInfo const;
using ObjectStopLineCSPtrType               = holo::map::format::PtrObjectStopLine const;
using ObjectTrafficLightCSPtrType           = holo::map::format::PtrObjectTrafficLight const;
using ObjectTrafficLightGroupCSPtrType      = holo::map::format::PtrObjectTrafficLightGroup const;
using ObjectTrafficSignCSPtrType            = holo::map::format::PtrObjectTrafficSign const;
using GeoFenceCSPtrType                     = holo::map::format::PtrGeofence const;

using TileContainerType                         = std::map<FeatureIdType, holo::map::format::PtrTile>;
using RoadContainerType                         = std::map<FeatureIdType, holo::map::format::PtrRoad>;
using SdRoadContainerType                       = std::map<FeatureIdType, holo::map::format::PtrSdRoad>;
using SdNodeContainerType                       = std::map<FeatureIdType, holo::map::format::PtrSdNode>;
using LaneContainerType                         = std::map<FeatureIdType, holo::map::format::PtrLane>;
using LaneGroupContainerType                    = std::map<FeatureIdType, holo::map::format::PtrLaneGroup>;
using LaneBoundaryContainerType                 = std::map<FeatureIdType, holo::map::format::PtrLaneBoundary>;
using ObjectInfoContainerType                   = std::map<FeatureIdType, holo::map::format::PtrObjectInfo>;
using ObjectLinearInfoContainerType             = std::map<FeatureIdType, holo::map::format::PtrObjectLinearInfo>;
using ObjectPedestrianCrossingContainerType     = std::map<FeatureIdType, holo::map::format::PtrObjectPedestrianCrossing>;
using ObjectRegionalInfoContainerType           = std::map<FeatureIdType, holo::map::format::PtrObjectRegionalInfo>;
using ObjectStopLineContainerType               = std::map<FeatureIdType, holo::map::format::PtrObjectStopLine>;
using ObjectTrafficLightContainerType           = std::map<FeatureIdType, holo::map::format::PtrObjectTrafficLight>;
using ObjectTrafficLightGroupContainerType      = std::map<FeatureIdType, holo::map::format::PtrObjectTrafficLightGroup>;
using ObjectTrafficSignContainerType            = std::map<FeatureIdType, holo::map::format::PtrObjectTrafficSign>;
using GeofenceContainerType                     = std::map<FeatureIdType, holo::map::format::PtrGeofence>;

using TileIterator                          = TileContainerType::iterator;
using RoadIterator                          = RoadContainerType::iterator;
using SdRoadIterator                        = SdRoadContainerType::iterator;
using SdNodeIterator                        = SdNodeContainerType::iterator;
using LaneIterator                          = LaneContainerType::iterator;
using LaneGroupIterator                     = LaneGroupContainerType::iterator;
using LaneBoundaryIterator                  = LaneBoundaryContainerType::iterator;
using ObjectInfoIterator                    = ObjectInfoContainerType::iterator;
using ObjectLinearInfoIteratorType          = ObjectLinearInfoContainerType::iterator;
using ObjectPedestrianCrossingIteratorType  = ObjectPedestrianCrossingContainerType::iterator;
using ObjectRegionalInfoIteratorType        = ObjectRegionalInfoContainerType::iterator;
using ObjectStopLineIteratorType            = ObjectStopLineContainerType::iterator;
using ObjectTrafficLightIteratorType        = ObjectTrafficLightContainerType::iterator;
using ObjectTrafficLightGroupIteratorType   = ObjectTrafficLightGroupContainerType::iterator;
using ObjectTrafficSignIteratorType         = ObjectTrafficSignContainerType::iterator;
using GeoFenceIterator                      = GeofenceContainerType::iterator;

using TileVectorType            = std::vector<holo::map::format::PtrTile>;
using RoadVectorType            = std::vector<holo::map::format::PtrRoad>;
using SdRoadVectorType          = std::vector<holo::map::format::PtrSdRoad>;
using SdNodeVectorType          = std::vector<holo::map::format::PtrSdNode>;
using LaneVectorType            = std::vector<holo::map::format::PtrLane>;
using LaneGroupVectorType       = std::vector<holo::map::format::PtrLaneGroup>;
using LaneBoundaryVectorType    = std::vector<holo::map::format::PtrLaneBoundary>;
using ObjectInfoVectorType      = std::vector<holo::map::format::PtrObjectInfo>;
using ObjectLinearInfo          = std::vector<ObjectLinearInfoSPtrType>;
using ObjectPedestrianCrossing  = std::vector<ObjectPedestrianCrossingSPtrType>;
using ObjectRegionalInfo        = std::vector<ObjectRegionalInfoSPtrType>;
using ObjectStopLine            = std::vector<ObjectStopLineSPtrType>;
using ObjectTrafficLight        = std::vector<ObjectTrafficLightSPtrType>;
using ObjectTrafficLightGroup   = std::vector<ObjectTrafficLightGroupSPtrType>;
using ObjectTrafficSign         = std::vector<ObjectTrafficSignSPtrType>;
using GeofenceVectorType        = std::vector<holo::map::format::PtrGeofence>;

using LaneBoundaryInfoType           = holo::map::format::LaneBoundaryInfo;
using LaneBoundaryInfoSPtrType       = std::shared_ptr<LaneBoundaryInfoType>;
using LaneBoundaryInfoVectorType     = std::vector<format::LaneBoundaryInfo>;
using LaneBoundaryElementType        = holo::map::format::LaneBoundaryElement;
using LaneBoundaryElementSPtrType    = std::shared_ptr<LaneBoundaryElementType>;
using LaneBoundaryElementVectorType  = std::vector<holo::map::format::LaneBoundaryElement>;

using GeoPointType       = holo::map::format::GeoPoint;
using GeoPointVectorType = std::vector<GeoPointType>;

using PositionType       = holo::map::format::Position;
using PositionVectorType = std::vector<PositionType>;

using GeoBoxType        = holo::map::format::GeoBox;
using GeoBoxVectorType  = std::vector<GeoBoxType>;

using GeoBox4Type        = holo::map::format::GeoBox4;
using GeoBox4VectorType  = std::vector<GeoBox4Type>;

using CoordinateType       = holo::common::Coordinate;
using CoordinateVectorType = std::vector<CoordinateType>;

using LLType       = holo::map::LL;
using LLVectorType = std::vector<holo::map::LL>;

using SpeedLimitInfoType    = holo::map::format::SpeedLimitInfo;
using SpeedLimitInfoVecType = std::vector<SpeedLimitInfoType>;

using RoadAttributeType    = holo::map::format::RoadAttribute;
using RoadAttributeVecType = std::vector<RoadAttributeType>;

using TrafficSignType = holo::map::format::ObjectInfo::TrafficSignType;

using LaneWidthInfoType    = holo::map::format::LaneWidthInfo;
using LaneWidthInfoVecType = std::vector<LaneWidthInfoType>;

using GeoBoxType               = holo::map::format::GeoBox;
using GeoLineType              = holo::map::format::GeoLine;

using LaneSequenceType  = holo::int32_t;
using SpeedLimit        = holo::uint32_t;

template <typename T>
struct IsHeaderSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsHeaderSPtrType<HeaderSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsTileSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsTileSPtrType<TileSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsTileCSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsTileCSPtrType<TileCSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsRoadSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsRoadSPtrType<RoadSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsSdRoadSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsSdRoadSPtrType<SdRoadSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsSdNodeSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsSdNodeSPtrType<SdNodeSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsLaneSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsLaneSPtrType<LaneSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsLaneGroupSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsLaneGroupSPtrType<LaneGroupSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsLaneBoundarySPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsLaneBoundarySPtrType<LaneBoundarySPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsObjectInfoSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsObjectInfoSPtrType<ObjectInfoSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsObjectPedestrianCrossingSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsObjectPedestrianCrossingSPtrType<ObjectPedestrianCrossingSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};


template <typename T>
struct IsObjectLinearSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsObjectLinearSPtrType<ObjectLinearInfoSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsObjectTrafficSignSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsObjectTrafficSignSPtrType<ObjectTrafficSignSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsObjectRegionalSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsObjectRegionalSPtrType<ObjectRegionalInfoSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsObjectStopLineSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsObjectStopLineSPtrType<ObjectStopLineSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsObjectTrafficLightSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsObjectTrafficLightSPtrType<ObjectTrafficLightSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsObjectTrafficLightGroupSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsObjectTrafficLightGroupSPtrType<ObjectTrafficLightGroupType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

template <typename T>
struct IsGeofenceSPtrType
{
    operator holo::bool_t () const
    {
        return false;
    }
};

template<> struct IsGeofenceSPtrType<GeofenceSPtrType>
{
    operator holo::bool_t () const
    {
        return true;
    }
};

struct MapDate
{
    holo::uint32_t year     : 16;
    holo::uint32_t month    : 4;
    holo::uint32_t day      : 5;
    holo::uint32_t reserve  : 7;
};

struct MapDataRange
{
    holo::float64_t lon_min = 0.0;
    holo::float64_t lat_min = 0.0;
    holo::float64_t lon_max = 0.0;
    holo::float64_t lat_max = 0.0;

    MapDataRange()
    {}

    MapDataRange(holo::float64_t const xMin, holo::float64_t const yMin,
        holo::float64_t const xMax, holo::float64_t const yMax)
        : lon_min(xMin), lat_min(yMin), lon_max(xMax), lat_max(yMax)
    {}
};

struct MapDataGroup
{
    TileContainerType                       tiles;
    RoadContainerType                       roads;
    SdRoadContainerType                     sd_roads;
    LaneContainerType                       lanes;
    LaneGroupContainerType                  groups;
    LaneBoundaryContainerType               boundaries;
    ObjectInfoContainerType                 objects;
    ObjectLinearInfoContainerType           object_linear_infos;
    ObjectRegionalInfoContainerType         object_regional_infos;
    ObjectPedestrianCrossingContainerType   object_pedestrian_crossings;
    ObjectStopLineContainerType             object_stop_lines;
    ObjectTrafficLightContainerType         object_lights;
    ObjectTrafficLightGroupContainerType    object_light_groups;
    ObjectTrafficSignContainerType          object_traffic_signs;
    GeofenceContainerType                   geofences;
};

namespace utility
{
/**
 * @addtogroup utility
 * @{
 *
 */
std::string FormatToString(MapDataRange const& range);

/**
 * @}
 *
 */
} ///< namespace utility

/**
 * @}
 *
 */
} ///< namespace apapter
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_ADAPTER_COMMON_STRUCTS_H_ */
