#ifndef HOLO_MAP_ADAPTER_CORE_WRITER_H_
#define HOLO_MAP_ADAPTER_CORE_WRITER_H_

#include <memory>
#include <vector>

#include <holo/map/adapter/common/structs.h>
#include <holo/map/adapter/common/types.h>
#include <holo/map/database/db.h>
#include <holo/map/format/base/header.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/format/base/lane_boundary.h>
#include <holo/map/format/base/lane_group.h>
#include <holo/map/format/base/object_info.h>
#include <holo/map/format/base/road.h>
#include <holo/map/format/base/sd_road.h>
#include <holo/map/format/base/tile.h>

namespace holo
{
namespace map
{
namespace adapter
{

class Writer
{
public:
    Writer();
    virtual ~Writer();

    void SetName(std::string const& name);
    void SetTileLevel(holo::uint64_t const level);
    void SetDate(MapDate const& date);
    void SetMapStatusFlag(MapStatusFlag const s);
    void SetMapVersionFlag(MapVersionFlag const v);
    void SetVersion(holo::uint64_t const major, holo::uint64_t const minor);
    void SetRelease(std::string const& release);
    
    std::string GetDatabaseName() const;
    holo::uint64_t GetDatabaseVersion() const;

    holo::bool_t Open(std::string const& output);
    void Close();

    holo::bool_t Write(MapDataGroup const& data);

    holo::bool_t WriteFeatures(TileContainerType const& tiles, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(RoadContainerType const& roads, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(SdRoadContainerType const& sd_roads, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(LaneContainerType const& lanes, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(LaneGroupContainerType const& groups, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(LaneBoundaryContainerType const& boundaries, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(ObjectInfoContainerType const& objects, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(ObjectLinearInfoContainerType const& objects, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(ObjectRegionalInfoContainerType const& objects, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(ObjectPedestrianCrossingContainerType const& objects, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(ObjectStopLineContainerType const& objects, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(ObjectTrafficLightContainerType const& objects, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(ObjectTrafficLightGroupContainerType const& objects, holo::bool_t const exist = true);

    holo::bool_t WriteFeatures(ObjectTrafficSignContainerType const& objects, holo::bool_t const exist = true);

    holo::bool_t WriteFeature(TileSPtrType const& tile, holo::bool_t const exist);

    holo::bool_t WriteFeature(RoadSPtrType const& road, holo::bool_t const exist);

    holo::bool_t WriteFeature(SdRoadSPtrType const& road, holo::bool_t const exist);

    holo::bool_t WriteFeature(LaneSPtrType const& lane, holo::bool_t const exist);

    holo::bool_t WriteFeature(LaneGroupSPtrType const& group, holo::bool_t const exist);

    holo::bool_t WriteFeature(LaneBoundarySPtrType const& boundary, holo::bool_t const exist);

    holo::bool_t WriteFeature(ObjectInfoSPtrType const& object, holo::bool_t const exist);

    holo::bool_t WriteFeature(ObjectLinearInfoSPtrType const& object, holo::bool_t const exist);

    holo::bool_t WriteFeature(ObjectRegionalInfoSPtrType const& object, holo::bool_t const exist);

    holo::bool_t WriteFeature(ObjectPedestrianCrossingSPtrType const& object, holo::bool_t const exist);

    holo::bool_t WriteFeature(ObjectStopLineSPtrType const& object, holo::bool_t const exist);

    holo::bool_t WriteFeature(ObjectTrafficLightSPtrType const& object, holo::bool_t const exist);

    holo::bool_t WriteFeature(ObjectTrafficLightGroupSPtrType const& object, holo::bool_t const exist);

    holo::bool_t WriteFeature(ObjectTrafficSignSPtrType const& object, holo::bool_t const exist);

private:
    holo::bool_t WriteHeader();

private:
    using HeaderWriterUPtrType                      = std::unique_ptr<holo::map::DB<holo::map::format::Header>>;
    using TileWriterUPtrType                        = std::unique_ptr<holo::map::DB<holo::map::format::Tile>>;
    using RoadWriterUPtrType                        = std::unique_ptr<holo::map::DB<holo::map::format::Road>>;
    using SdRoadWriterUPtrType                      = std::unique_ptr<holo::map::DB<holo::map::format::SdRoad>>;
    using LaneWriterUPtrType                        = std::unique_ptr<holo::map::DB<holo::map::format::Lane>>;
    using LaneGroupWriterUPtrType                   = std::unique_ptr<holo::map::DB<holo::map::format::LaneGroup>>;
    using LaneBoundaryWriterUPtrType                = std::unique_ptr<holo::map::DB<holo::map::format::LaneBoundary>>;
    using ObjectInfoWriterUPtrType                  = std::unique_ptr<holo::map::DB<holo::map::format::ObjectInfo>>;
    using ObjectLinearInfoWriterUPtrType            = std::unique_ptr<holo::map::DB<holo::map::format::ObjectLinearInfo>>;
    using ObjectRegionalInfoWriterUPtrType          = std::unique_ptr<holo::map::DB<holo::map::format::ObjectRegionalInfo>>;
    using ObjectPedestrianCrossingWriterUPtrType    = std::unique_ptr<holo::map::DB<holo::map::format::ObjectPedestrianCrossing>>;
    using ObjectStopLineWriterUPtrType              = std::unique_ptr<holo::map::DB<holo::map::format::ObjectStopLine>>;
    using ObjectTrafficLightWriterUPtrType          = std::unique_ptr<holo::map::DB<holo::map::format::ObjectTrafficLight>>;
    using ObjectTrafficLightGroupWriterUPtrType     = std::unique_ptr<holo::map::DB<holo::map::format::ObjectTrafficLightGroup>>;
    using ObjectTrafficSignWriterUPtrType           = std::unique_ptr<holo::map::DB<holo::map::format::ObjectTrafficSign>>;

    HeaderWriterUPtrType                    header_                     = nullptr;
    TileWriterUPtrType                      tile_                       = nullptr;
    RoadWriterUPtrType                      road_                       = nullptr;
    SdRoadWriterUPtrType                    sd_road_                    = nullptr;
    LaneWriterUPtrType                      lane_                       = nullptr;
    LaneGroupWriterUPtrType                 group_                      = nullptr;
    LaneBoundaryWriterUPtrType              boundary_                   = nullptr;
    ObjectInfoWriterUPtrType                object_                     = nullptr;
    ObjectLinearInfoWriterUPtrType          object_linear_              = nullptr;
    ObjectRegionalInfoWriterUPtrType        object_regional_            = nullptr;
    ObjectPedestrianCrossingWriterUPtrType  object_pedestrian_crossing_ = nullptr;
    ObjectStopLineWriterUPtrType            object_stop_line_           = nullptr;
    ObjectTrafficLightWriterUPtrType        object_light_               = nullptr;
    ObjectTrafficLightGroupWriterUPtrType   object_light_group_         = nullptr;
    ObjectTrafficSignWriterUPtrType         object_traffic_sign_        = nullptr;

    std::string name_       = "Data";
    std::string release_    = "xxx";
    
    MapDate         date_;
    MapStatusFlag   status_flag_;
    MapVersionFlag  version_flag_;

    holo::uint64_t version_major_;
    holo::uint64_t version_minor_;

    holo::uint64_t tile_level_;

    std::set<holo::map::MapFeatureIdType> tile_ids_;
};

} ///< namespace adapter
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_ADAPTER_CORE_WRITER_H_ */
