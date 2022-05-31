/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_geofence_cache.h
 * @brief This header file defines local cache of map geofences to improve access performance.
 * @author lisong@holomatic.com
 * @date 2020-05-12
 */

#ifndef HOLO_MAP_FEATURE_GEOFENCE_MAP_GEOFENCE_CACHE_H_
#define HOLO_MAP_FEATURE_GEOFENCE_MAP_GEOFENCE_CACHE_H_

#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/common/geometry.h>
#include <holo/map/common/match_info.h>
#include <holo/map/feature/navigator/navigator_config.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/geofence.h>
#include <holo/map/retriever/retriever.h>

#include <holo/map/database/geofence_manager.h>

namespace holo
{
/**
 * @addtogroup holo
 *
 * @{
 */
namespace map
{
/**
 * @addtogroup map
 *
 * @{
 */

namespace geofence
{
/**
 * @addtogroup geofence
 *
 * @{
 */

/**
 * @brief Check if given MatchInfo object is valid.
 * @details If MatchInfo.link_id = 0UL, we think it is invalid.
 *
 * @param[in] match_info Given Match info object.
 * @return True if given Match info object is valid,
 *         False if not.
 */
holo::bool_t IsMatchInfoValid(holo::map::MapMatchInfo const& match_info);

/**
 * @brief Check if given RouteInfo2 object is valid.
 * @details If RouteInfo2.IsAvailable() is false, we think it is  invalid.
 *
 * @param[in] route_info Given RouteInfo2 object.
 * @return True if given RouteInfo2 object is valid,
 *         False if not.
 */
holo::bool_t IsRouteInfoValid(holo::map::RouteInfo2 const& route_info);

/**
 * @brief this class defines local cache of map geofences.
 *
 */
class MapGeofenceCache
{
public:
    /**
     * @brief Constructor
     */
    MapGeofenceCache() = default;

    /**
     * @brief Destructor
     */
    ~MapGeofenceCache() = default;

    /// MapGeofenceCache object can not be copied and moved.
    MapGeofenceCache(MapGeofenceCache const& other) = delete;
    MapGeofenceCache& operator=(MapGeofenceCache const& other) = delete;

    MapGeofenceCache(MapGeofenceCache&& other) = delete;
    MapGeofenceCache& operator=(MapGeofenceCache&& other) = delete;

public:
    /**
     * @brief Init a MapGeofenceCache object
     *
     * @param[in] ptr_ret Retriever pointer
     * @param[in] ptr_config Config pointer
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Init(RetrieverSPType const ptr_ret, navigator::config::NavigatorConfigSPtr const& ptr_config);

    /**
     * @brief Get enabled geofences that fall in given tile.
     *
     * @param[in] tile_id Tile ID
     * @param[in] match_info Match info
     * @param[in] route_info Route info
     * @param[out] geofence_vec Result geofence vector
     * @return True if successful,
     *         False if failed, and geofence_vec will be empty.
     */
    holo::bool_t GetEnabledGeofences(holo::map::IdType const tile_id, holo::map::MapMatchInfo const& match_info,
                                     holo::map::RouteInfo2 const&                     route_info,
                                     std::vector<std::shared_ptr<MapGeofence const>>& geofence_vec);

    /**
     * @brief Reset geofence cache
     *
     */
    void Reset()
    {
        last_geofence_ids_.clear();
        geofence_map_.clear();
        last_tile_ids_.clear();
        incoming_tile_geofence_ids_map_.clear();
        tile_geofence_map_.clear();
    }

private:
    /// Map of ID and geofence
    using GeofenceMapType = std::unordered_map<holo::map::IdType, std::shared_ptr<MapGeofence const>>;
    /// Map of tile ID and IDs of geofences it has
    using TileGeofenceIDMapType = std::unordered_map<holo::map::IdType, std::vector<holo::map::IdType>>;
    /// Map of tile and geofences it has
    using TileGeofenceMapType =
        std::unordered_map<holo::map::IdType, std::vector<std::shared_ptr<MapGeofence const>>>;

private:
    /**
     * @brief Get tile ids by link id
     *
     * @param[in] link_id Given link ID
     * @param[out] tile_ids Result tile ids
     * @return True if successful,
     *         False if failed and tile_ids will be empty.
     */
    holo::bool_t getTileIDsByLinkID(holo::map::IdType const         link_id,
                                    std::vector<holo::map::IdType>& tile_ids) const;

    /**
     * @brief Get tile ids that incoming route items in
     *
     * @param[in] current_idx_in_route_path Index of current route item in current route info
     * @param[in] route_info Given route info
     * @param[out] incoming_tile_ids Result tile ids
     * @return True if successful,
     *         False if failed and incoming_tile_ids will be empty.
     */
    holo::bool_t getIncomingTileIDs(std::size_t const                        current_idx_in_route_path,
                                    holo::map::RouteInfo2 const&             route_info,
                                    std::unordered_set<holo::map::IdType>& incoming_tile_ids);

    /**
     * @brief Get incoming geofence ids
     *
     * @param[in] incoming_tile_ids Incoming tile ids
     * @param[out] incoming_geofence_ids Result Incoming geofence ids
     * @return True if successful,
     *         False if failed and incoming_geofence_ids will be empty.
     */
    holo::bool_t getIncomingGeofenceIDs(std::unordered_set<holo::map::IdType> const& incoming_tile_ids,
                                        std::unordered_set<holo::map::IdType>&       incoming_geofence_ids);

    /**
     * @brief Remove geofences from geofence map
     *
     * @param[in] geofences_to_remove Tiles to remove
     * @param[in, out] result Geofence remove from
     * @return True if successful,
     *         False if failed and result will not change.
     */
    static holo::bool_t removeGeofences(std::vector<holo::map::IdType> const& geofences_to_remove,
                                        GeofenceMapType&                        result);

    /**
     * @brief Add geofences to geofence map
     *
     * @param[in] geofences_to_add Geofences to add
     * @param[in, out] result Geofences add to
     * @return True if successful,
     *         False if failed and result will not change.
     */
    holo::bool_t addGeofences(std::vector<holo::map::IdType> const& geofences_to_add, GeofenceMapType& result);

    /**
     * @brief Update geofence map
     *
     * @param[in] new_geofence_ids Geofence ids used to update geofence_map_
     * @return True if successful,
     *         False if failed and geofence_map_ will not change.
     */
    holo::bool_t updateGeofenceMap(std::unordered_set<holo::map::IdType> const& new_geofence_ids);

    /**
     * @brief Remove tiles for given map of tile and its geofences
     *
     * @param[in] tiles_to_remove Tiles to remove
     * @param[in, out] result Map of tile and its geofences that tiles remove from
     * @return True if successful,
     *         False if failed and result will not change.
     */
    static holo::bool_t removeTiles(std::vector<holo::map::IdType> const& tiles_to_remove,
                                    TileGeofenceMapType&                    result);

    /**
     * @brief Add tiles for map of tile and its geofences
     *
     * @param[in] tiles_to_add Tiles to add
     * @param[in, out] result Map of tile and its geofences that tiles add to
     * @return True if successful,
     *         False if failed and result will not change.
     */
    holo::bool_t addTiles(std::vector<holo::map::IdType> const& tiles_to_add, TileGeofenceMapType& result);

    /**
     * @brief Update map of map of tile and its geofences
     *
     * @param[in] new_tile_ids Tile ids used to update tile_geofence_map_
     * @return True if successful,
     *         False if failed and tile_geofence_map_ will not change.
     */
    holo::bool_t updateTileGeofenceMap(std::unordered_set<holo::map::IdType> const& new_tile_ids);

    /**
     * @brief Update geofences cache
     *
     * @param[in] match_info Given match info
     * @param[in] route_info Given route info
     * @return True if successful,
     *         False if failed and tile_geofence_map_ will not change.
     */
    holo::bool_t updateCache(holo::map::MapMatchInfo const& match_info, holo::map::RouteInfo2 const& route_info);

private:
    /// Internal GeofenceManager pointer
    GeofenceManagerUPtrType geofence_manager_ptr_ = nullptr;

    /// Retriever pointer
    RetrieverSPType ret_ptr_ = nullptr;

    /// Geofence ids from latest running.
    std::unordered_set<holo::map::IdType> last_geofence_ids_;

    /// Map of ID and geofence, to reduce DB accessing
    GeofenceMapType geofence_map_;

    /// Tile ids from latest running.
    std::unordered_set<holo::map::IdType> last_tile_ids_;

    /// Map of incoming tiles on route and IDs of its geofences
    TileGeofenceIDMapType incoming_tile_geofence_ids_map_;

    /// Map of tile and its geofences, which is the cache
    TileGeofenceMapType tile_geofence_map_;

};  ///< Class MapGeofenceCache

/// Handy typedefs
using MapGeofenceCacheUPtrType  = std::unique_ptr<MapGeofenceCache>;
using MapGeofenceCacheCUPtrType = std::unique_ptr<MapGeofenceCache const>;

/**
 * @}
 */
}  // namespace geofence
/**
 * @}
 */
}  // namespace map
/**
 * @}
 */
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_GEOFENCE_MAP_GEOFENCE_CACHE_H_ */
