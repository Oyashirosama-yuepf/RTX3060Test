/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_geofence.h
 * @brief This header file defines in-memory structures corresponding to row model of tables from geofence database.
 * @author lisong@holomatic.com
 * @date 2020-05-06
 */

#ifndef HOLO_MAP_GEOFENCE_MAP_GEOFENCE_H_
#define HOLO_MAP_GEOFENCE_MAP_GEOFENCE_H_

#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <memory>

#include <holo/log/hololog.h>

#include <holo/core/types.h>
#include <holo/map/common_def.h>
#include <holo/map/common/common_type_define.h>

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
 * @brief this class defines in-memory structure corresponding to row model of geofence table from geofence database.
 *
 */
class MapGeofence
{
public:
    /**
     * @brief Corresponding to holo::map::Geofence::Function
     */
    enum class Function : holo::uint8_t
    {
        UNKNOWN         = 0, ///< Function with an invalid type.
        HSA,                 ///< Highway Switch Assist.
        ICP,                 ///< Intelligent Cruise Pilot.
        TJP,                 ///< Traffic Jam Pilot.
        LC,                  ///< Lane Change
        EMSS,                ///< Emergency Lane Safe Stop.
        FUNCTION_MAX         ///< Total number of function type.
    };

    /**
     * @brief Geofence type, note this is not the physical form of geofence
     */
    enum class GeofenceType : holo::uint8_t
    {
        UNKNOWN = 0,      ///< Unknown type
        REGION_COMMON,    ///< Polygonal region
        REGION_COUNTRY,   ///< National administrative region
        REGION_PROVINCE,  ///< Provincial administrative region
        REGION_COUNTY,    ///< County administrative region
        INTERVAL_COMMON,  ///< Closed road section
        GEOFENCETYPE_MAX  ///< Total number of geofence type
    };

    /**
     * @brief Geometry type of geofence
     */
    enum class GeoType : holo::uint8_t
    {
        UNKNOWN = 0,  ///< Unknown type
        POLYLINE,     ///< Poly line
        POLYGON,      ///< Polygon
        GEOTYPE_MAX   ///< Total number of geometry type of geofence

    };

    /**
     * @brief Feature type of feature that geofence fall in
     */
    enum class FeatureType : holo::uint8_t
    {
        UNKNOWN = 0,     ///< Unknown type
        ROAD,            ///< Road
        LINK,            ///< Link
        LANE,            ///< Lane
        FEATURETYPE_MAX  ///< Total number of feature
    };

    /**
     * @brief Validity type of geofence
     */
    enum class ValidType : holo::uint8_t
    {
        UNKNOWN = 0,          ///< Unknown type
        PERMANENT,            ///< Permanent
        FROM_A_CERTAIN_POINT, ///< Valid from a certain point in time
        INTERMITTENT,         ///< Intermittently
        PERIODIC,             ///< Periodic
        VALIDTYPE_MAX         ///< Total number of validity type
    };

    /**
     * @brief this struct represents infomation of validity of geofence in time.
     */
    struct ValidTime
    {
        /// Type of valid time 
        ValidType                                              valid_type = ValidType::UNKNOWN;
        
        /// Start time of validity, Unix Time, the number of seconds since 1970-01-01 00:00:00 UTC
        /// If valid type is PERMANENT, this value will be 0
        holo::uint64_t                                         start_time = 0UL;

        /// End time of validity, Unix Time, the number of seconds since 1970-01-01 00:00:00 UTC
        /// If valid type is PERMANENT, this value will be the max value of uint64_t
        /// If valid type is FROM_A_CERTAIN_POINT, this value will be the max value of uint64_t
        holo::uint64_t                                         end_time   = 0UL;

        /// If valid type is PERMANENT, this vector will be empty.
        /// If valid type is INTERMITTENT, elements of vector is time intervals, say {[start_time, end_time], [start_time, end_time]...}
        /// If valid type is PERIODIC, this vector will have one element only, say P for this element, which is a pair:
        ///                            the first element of P is period length,
        ///                            the secode element of P is length between periods
        std::vector<std::pair<holo::uint64_t, holo::uint64_t>> time_interval_vec;
    };

public:
    /**
     * @brief Constructor
     */
    MapGeofence()  = default;

    /**
     * @brief Destructor
     */
    ~MapGeofence() = default;

    /**
     * @brief Constructor with parameters
     *
     * @param[in] function Geofence function
     * @param[in] fence_type Geofence type
     * @param[in] map_level Map level of geofence
     * @param[in] tile_id_vec IDs of Tiles that geofence fall in
     * @param[in] feature_id_vec IDs of Features geofence fall in
     */
    MapGeofence(Function const function, GeofenceType const fence_type, holo::uint8_t const map_level,
                std::vector<holo::map::MapFeatureIdType> const& tile_id_vec, FeatureType const feature_type, 
                std::vector<holo::map::MapFeatureIdType> const& feature_id_vec, ValidTime const& valid_time)
      : function_(function)
      , type_(fence_type)
      , map_level_(map_level)
      , tile_ids_(tile_id_vec)
      , feature_type_(feature_type)
      , feature_ids_(feature_id_vec)
      , enable_(true)
      , valid_type_(valid_time.valid_type)
      , valid_time_(valid_time)
    {
    }

    /// MapGeofence object can be copied
    MapGeofence(MapGeofence const& other) = default;
    MapGeofence(MapGeofence&& other)      = default;

    /// MapGeofence object can be moved
    MapGeofence& operator=(MapGeofence const& other) = default;
    MapGeofence& operator=(MapGeofence&& other) = default;

public:
    /**
     * @brief Get ID, const version
     *
     * @return ID.
     */
    holo::uint64_t GetID() const noexcept
    {
        return id_;
    }

    /**
     * @brief Get ID
     *
     * @return ID.
     */
    holo::uint64_t& GetID() noexcept
    {
        return id_;
    }

    /**
     * @brief Set ID.
     *
     * @param[in] id ID
     */
    void SetID(holo::uint64_t const id) noexcept
    {
        id_ = id;
    }

    /**
     * @brief Get function, const version
     *
     * @return function.
     */
    Function GetFunction() const noexcept
    {
        return function_;
    }

    /**
     * @brief Get function
     *
     * @return function.
     */
    Function& GetFunction() noexcept
    {
        return function_;
    }

    /**
     * @brief Set function.
     *
     * @param[in] function Function
     */
    void SetFunction(Function const function) noexcept
    {
        function_ = function;
    }

    /**
     * @brief Get geofence type, const version
     *
     * @return geofence type.
     */
    GeofenceType GetType() const noexcept
    {
        return type_;
    }

    /**
     * @brief Get geofence type
     *
     * @return geofence type.
     */
    GeofenceType& GetType() noexcept
    {
        return type_;
    }

    /**
     * @brief Set geofence type
     *
     * @param[in] geofence_type Geofence type
     */
    void SetType(GeofenceType const geofence_type) noexcept
    {
        type_ = geofence_type;
    }

    /**
     * @brief Get version of geofence, const version
     *
     * @return version of geofence.
     */
    std::string GetVersion() const noexcept
    {
        return version_;
    }

    /**
     * @brief Get version of geofence
     *
     * @return version of geofence.
     */
    std::string& GetVersion() noexcept
    {
        return version_;
    }

    /**
     * @brief Set version of geofence
     *
     * @param[in] version Versiono of geofence
     */
    void SetVersion(std::string const& version) noexcept
    {
        version_ = version;
    }

    /**
     * @brief Get country code, const version
     *
     * @return country code.
     */
    holo::uint32_t GetCountryCode() const noexcept
    {
        return country_code_;
    }

    /**
     * @brief Get country code
     *
     * @return country code.
     */
    holo::uint32_t& GetCountryCode() noexcept
    {
        return country_code_;
    }

    /**
     * @brief Set country code
     *
     * @param[in] country_code Country code
     */
    void SetCountryCode(holo::uint32_t const country_code) noexcept
    {
        country_code_ = country_code;
    }

    /**
     * @brief Get province code, const version
     *
     * @return province code.
     */
    holo::uint32_t GetProvinceCode() const noexcept
    {
        return province_code_;
    }

    /**
     * @brief Get province code
     *
     * @return province code.
     */
    holo::uint32_t& GetProvinceCode() noexcept
    {
        return province_code_;
    }

    /**
     * @brief Set province code
     *
     * @param[in] province_code Province code
     */
    void SetProvinceCode(holo::uint32_t const province_code) noexcept
    {
        province_code_ = province_code;
    }

    /**
     * @brief Get city code, const version
     *
     * @return city code.
     */
    holo::uint32_t GetCityCode() const noexcept
    {
        return city_code_;
    }

    /**
     * @brief Get city code
     *
     * @return city code.
     */
    holo::uint32_t& GetCityCode() noexcept
    {
        return city_code_;
    }

    /**
     * @brief Set city code
     *
     * @param[in] city_code City code
     */
    void SetCityCode(holo::uint32_t const city_code) noexcept
    {
        city_code_ = city_code;
    }

    /**
     * @brief Get country code, const version
     *
     * @return country code
     */
    holo::uint32_t GetCountyCode() const noexcept
    {
        return county_code_;
    }

    /**
     * @brief Get country code
     *
     * @return country code
     */
    holo::uint32_t& GetCountyCode() noexcept
    {
        return county_code_;
    }

    /**
     * @brief Set country code
     *
     * @param[in] county_code County code
     */
    void SetCountyCode(holo::uint32_t const county_code) noexcept
    {
        county_code_ = county_code;
    }

    /**
     * @brief Get geo type, const version
     *
     * @return geo type
     */
    GeoType GetGeoType() const noexcept
    {
        return geo_type_;
    }

    /**
     * @brief Get geo type
     *
     * @return geo type
     */
    GeoType& GetGeoType() noexcept
    {
        return geo_type_;
    }

    /**
     * @brief Set geo type
     *
     * @param[in] geo_type Geo type
     */
    void SetGeoType(GeoType const geo_type) noexcept
    {
        geo_type_ = geo_type;
    }

    /**
     * @brief Get Geometry of geofence(in form of geojson string), const version
     *
     * @return geometry
     */
    std::string GetGeometry() const noexcept
    {
        return geometry_;
    }

    /**
     * @brief Get Geometry of geofence(in form of geojson string)
     *
     * @return geometry
     */
    std::string& GetGeometry() noexcept
    {
        return geometry_;
    }

    /**
     * @brief Set geometry of geofence(in form of geojson string)
     *
     * @param[in] geometry Geometry of geofence(in form of geojson string)
     */
    void SetGeometry(std::string const& geometry) noexcept
    {
        geometry_ = geometry;
    }

    /**
     * @brief Get map level, const version
     *
     * @return map level
     */
    holo::uint8_t GetMapLevel() const noexcept
    {
        return map_level_;
    }

    /**
     * @brief Get map level
     *
     * @return map level
     */
    holo::uint8_t& GetMapLevel() noexcept
    {
        return map_level_;
    }

    /**
     * @brief Set map level
     *
     * @param[in] map level Map level
     */
    void SetMapLevel(holo::uint8_t const map_level) noexcept
    {
        map_level_ = map_level;
    }

    /**
     * @brief Get tile ids, const version
     *
     * @return tile ids
     */
    std::vector<holo::map::MapFeatureIdType> const& GetTileIDs() const noexcept
    {
        return tile_ids_;
    }

    /**
     * @brief Get tile ids
     *
     * @return tile ids
     */
    std::vector<holo::map::MapFeatureIdType>& GetTileIDs() noexcept
    {
        return tile_ids_;
    }

    /**
     * @brief Set tile ids
     *
     * @param[in] tile_ids　Tile ids
     */
    void SetTileIDs(std::vector<holo::map::MapFeatureIdType> const& tile_ids) noexcept
    {
        tile_ids_ = tile_ids;
    }

    /**
     * @brief Set tile ids, move version
     *
     * @param[in] tile_ids　Tile ids
     */
    void SetTileIDs(std::vector<holo::map::MapFeatureIdType>&& tile_ids) noexcept
    {
        tile_ids_ = std::move(tile_ids);
    }

    /**
     * @brief Get feature type, const version
     *
     * @return feature type
     */
    FeatureType GetFeatureType() const noexcept
    {
        return feature_type_;
    }

    /**
     * @brief Get feature type
     *
     * @return feature type
     */
    FeatureType& GetFeatureType() noexcept
    {
        return feature_type_;
    }

    /**
     * @brief Set feature type
     *
     * @param[in] feature_type
     */
    void SetFeatureType(FeatureType const feature_type) noexcept
    {
        feature_type_ = feature_type;
    }

    /**
     * @brief Get feature IDs, const version
     *
     * @return feature IDs
     */
    std::vector<holo::map::MapFeatureIdType> const& GetFeatureIDs() const noexcept
    {
        return feature_ids_;
    }

    /**
     * @brief Get feature IDs
     *
     * @return feature IDs
     */
    std::vector<holo::map::MapFeatureIdType>& GetFeatureIDs() noexcept
    {
        return feature_ids_;
    }

    /**
     * @brief Set feature ids
     *
     * @param[in] feature_ids
     */
    void SetFeatureIDs(std::vector<holo::map::MapFeatureIdType> const& feature_ids) noexcept
    {
        feature_ids_ = feature_ids;
    }

    /**
     * @brief Set feature ids, move version
     *
     * @param[in] feature_ids
     */
    void SetFeatureIDs(std::vector<holo::map::MapFeatureIdType>&& feature_ids) noexcept
    {
        feature_ids_ = std::move(feature_ids);
    }

    /**
     * @brief Get enableness of geofence, const version
     *
     * @return enableness of geofence
     */
    bool GetEnable() const noexcept
    {
        return enable_;
    }

    /**
     * @brief Get enableness of geofence
     *
     * @return enableness of geofence
     */
    bool& GetEnable() noexcept
    {
        return enable_;
    }

    /**
     * @brief Set validity of geofence
     *
     * @param[in] valid
     */
    void SetEnable(bool const enable) noexcept
    {
        enable_ = enable;
    }

     /**
      * @brief Get valid type, const version
      *
      * @return valid type
      */
     ValidType GetValidType() const noexcept
     {
         return valid_type_;
     }

     /**
      * @brief Get valid type
      *
      * @return valid type
      */
     ValidType& GetValidType() noexcept
     {
         return valid_type_;
     }

     /**
      * @brief Set valid type
      *
      * @param[in] valid_type
      */
     void SetValidType(ValidType const valid_type) noexcept
     {
         valid_type_ = valid_type;
     }

    /**
     * @brief Get valid time, const version
     *
     * @return valid time
     */
    ValidTime GetValidTime() const noexcept
    {
        return valid_time_;
    }

    /**
     * @brief Get valid time
     *
     * @return valid time
     */
    ValidTime& GetValidTime() noexcept
    {
        return valid_time_;
    }

    /**
     * @brief Set valid time
     *
     * @param[in] valid_time
     */
    void SetValidTime(ValidTime const valid_time) noexcept
    {
        valid_time_ = valid_time;
    }

    /**
     * @brief Get create timestamp of geofence, const version
     *
     * @return create timestamp of geofence
     */
    holo::uint64_t GetCreateTimestamp() const noexcept
    {
        return create_timestamp_;
    }

    /**
     * @brief Get create timestamp of geofence
     *
     * @return create timestamp of geofence
     */
    holo::uint64_t& GetCreateTimestamp() noexcept
    {
        return create_timestamp_;
    }

    /**
     * @brief Set create timestamp of geofence
     *
     * @param[in] create_timestamp
     */
    void SetCreateTimestamp(holo::uint64_t const create_timestamp) noexcept
    {
        create_timestamp_ = create_timestamp;
    }

    /**
     * @brief Get update timestamp of geofence, const version
     *
     * @return update timestamp of geofence
     */
    holo::uint64_t GetUpdateTimestamp() const noexcept
    {
        return update_timestamp_;
    }

    /**
     * @brief Get update timestamp of geofence
     *
     * @return update timestamp of geofence
     */
    holo::uint64_t& GetUpdateTimestamp() noexcept
    {
        return update_timestamp_;
    }

    /**
     * @brief Set update timestamp of geofence
     *
     * @param[in] update_timestamp
     */
    void SetUpdateTimestamp(holo::uint64_t const update_timestamp) noexcept
    {
        update_timestamp_ = update_timestamp;
    }

private:
    /// ID, 0 is invalid ID
    holo::uint64_t              id_       = 0UL;

    /// Function
    Function                    function_ = Function::UNKNOWN;

    /// Type, physical form
    GeofenceType                type_     = GeofenceType::UNKNOWN;

    /// Version
    std::string                 version_;

    /// Country code
    holo::uint32_t              country_code_  = 0UL;

    /// Privince code
    holo::uint32_t              province_code_ = 0UL;

    /// City code
    holo::uint32_t              city_code_     = 0UL;

    /// County code
    holo::uint32_t              county_code_   = 0UL;

    /// Geometry type
    GeoType                     geo_type_      = GeoType::UNKNOWN;

    /// Geojson string of geometry of geofence
    std::string                 geometry_;

    /// Map level
    std::uint8_t                map_level_ = 13;

    /// Tile ids that geofence fall in
    std::vector<holo::map::MapFeatureIdType> tile_ids_;

    /// Feature type
    FeatureType                 feature_type_ = FeatureType::UNKNOWN;

    /// Feature ids that geofence fall in
    std::vector<holo::map::MapFeatureIdType> feature_ids_;

    /// If true, geofence is enabled, else not
    holo::bool_t                enable_      = false;

    /// Valid type
    ValidType                   valid_type_ = ValidType::UNKNOWN;

    /// Valid time
    ValidTime                   valid_time_;

    /// Timestamp that geofence created
    holo::uint64_t              create_timestamp_ = 0UL;

    /// Timestamp that geofence update
    holo::uint64_t              update_timestamp_ = 0UL;

};  ///< Class MapGeofence

/// Handy typedefs
using MapGeofenceSPtrType  = std::shared_ptr<MapGeofence>;
using MapGeofenceCSPtrType = std::shared_ptr<MapGeofence const>;

/**
 * @brief this class defines in-memory structure corresponding to row model of geofence_index table from geofence database.
 *
 */
class MapGeofenceIndex
{
public:
    /**
     * @brief Constructor
     */
    MapGeofenceIndex()  = default;

    /**
     * @brief Destructor
     */
    ~MapGeofenceIndex() = default;

    /**
     * @brief Constructor with parameters
     *
     * @param[in] function Geofence function
     * @param[in] map_level Map level of geofence
     * @param[in] tile_id ID of Tile that geofences fall in
     * @param[in] geofence_id_vec IDs of geofences
     */
    MapGeofenceIndex(holo::uint8_t const map_level, holo::map::MapFeatureIdType const& tile_id,
                     std::vector<holo::map::MapFeatureIdType> const& geofence_id_vec)
      : map_level_(map_level), tile_id_(tile_id), geofence_ids_(geofence_id_vec)
    {
    }

    /// MapGeofenceIndex object can be copied
    MapGeofenceIndex(MapGeofenceIndex const& other) = default;
    MapGeofenceIndex(MapGeofenceIndex&& other)      = default;

    /// MapGeofenceIndex object can be moved
    MapGeofenceIndex& operator=(MapGeofenceIndex const& other) = default;
    MapGeofenceIndex& operator=(MapGeofenceIndex&& other) = default;

public:
    /**
     * @brief Get ID, const version
     *
     * @return ID.
     */
    holo::uint64_t GetID() const noexcept
    {
        return id_;
    }

    /**
     * @brief Get ID.
     *
     * @return ID.
     */
    holo::uint64_t& GetID() noexcept
    {
        return id_;
    }

    /**
     * @brief Set ID.
     *
     * @param[in] id ID
     */
    void SetID(holo::uint64_t const id) noexcept
    {
        id_ = id;
    }

    /**
     * @brief Get map level, const version
     *
     * @return map level
     */
    holo::uint8_t GetMapLevel() const noexcept
    {
        return map_level_;
    }

    /**
     * @brief Get map level
     *
     * @return map level
     */
    holo::uint8_t& GetMapLevel() noexcept
    {
        return map_level_;
    }

    /**
     * @brief Set map level
     *
     * @param[in] map level Map level
     */
    void SetMapLevel(holo::uint8_t const map_level) noexcept
    {
        map_level_ = map_level;
    }

    /**
     * @brief Get tile id, const version
     *
     * @return tile id
     */
    holo::map::MapFeatureIdType GetTileID() const noexcept
    {
        return tile_id_;
    }

    /**
     * @brief Get tile id
     *
     * @return tile id
     */
    holo::map::MapFeatureIdType& GetTileID() noexcept
    {
        return tile_id_;
    }

    /**
     * @brief Set tile id
     *
     * @param[in] tile_id Tile id
     */
    void SetTileID(holo::map::MapFeatureIdType const& tile_id) noexcept
    {
        tile_id_ = tile_id;
    }

    /**
     * @brief Get geofence IDs, const version
     *
     * @return geofence IDs
     */
    std::vector<holo::map::MapFeatureIdType> const& GetGeofenceIDs() const noexcept
    {
        return geofence_ids_;
    }

    /**
     * @brief Get geofence IDs
     *
     * @return geofence IDs
     */
    std::vector<holo::map::MapFeatureIdType>& GetGeofenceIDs() noexcept
    {
        return geofence_ids_;
    }

    /**
     * @brief Set geofence IDs
     *
     * @param[in] geofence_ids
     */
    void SetGeofenceIDs(std::vector<holo::map::MapFeatureIdType> const& geofence_ids) noexcept
    {
        geofence_ids_ = geofence_ids;
    }

    /**
     * @brief Set geofence IDs, move version
     *
     * @param[in] geofence_ids
     */
    void SetGeofenceIDs(std::vector<holo::map::MapFeatureIdType>&& geofence_ids) noexcept
    {
        geofence_ids_ = std::move(geofence_ids);
    }

    /**
     * @brief Get create timestamp of geofence_index, const version
     *
     * @return create timestamp of geofence_index
     */
    holo::uint64_t GetCreateTimestamp() const noexcept
    {
        return create_timestamp_;
    }

    /**
     * @brief Get create timestamp of geofence_index
     *
     * @return create timestamp of geofence_index
     */
    holo::uint64_t& GetCreateTimestamp() noexcept
    {
        return create_timestamp_;
    }

    /**
     * @brief Set create timestamp of geofence_index
     *
     * @param[in] create_timestamp
     */
    void SetCreateTimestamp(holo::uint64_t const create_timestamp) noexcept
    {
        create_timestamp_ = create_timestamp;
    }

    /**
     * @brief Get update timestamp of geofence_index, const version
     *
     * @return update timestamp of geofence_index
     */
    holo::uint64_t GetUpdateTimestamp() const noexcept
    {
        return update_timestamp_;
    }

    /**
     * @brief Get update timestamp of geofence_index
     *
     * @return update timestamp of geofence_index
     */
    holo::uint64_t& GetUpdateTimestamp() noexcept
    {
        return update_timestamp_;
    }

    /**
     * @brief Set update timestamp of geofence_index
     *
     * @param[in] update_timestamp
     */
    void SetUpdateTimestamp(holo::uint64_t const update_timestamp) noexcept
    {
        update_timestamp_ = update_timestamp;
    }

private:
    /// ID, 0 is invalid ID
    holo::uint64_t               id_        = 0UL;

    /// Map level
    std::uint8_t                 map_level_ = 13;

    /// Tile id
    holo::map::MapFeatureIdType  tile_id_   = 0UL;

    /// IDs of geofences fall in tile
    std::vector<holo::map::MapFeatureIdType> geofence_ids_;

    /// Timestamp that geofence index created
    holo::uint64_t               create_timestamp_ = 0UL;

    /// Timestamp that geofence index update
    holo::uint64_t               update_timestamp_ = 0UL;
};  ///< Class MapGeofenceIndex

/// Handy typedefs
using MapGeofenceIndexSPtrType  = std::shared_ptr<MapGeofenceIndex>;
using MapGeofenceIndexCSPtrType = std::shared_ptr<MapGeofenceIndex const>;

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

#endif /* HOLO_MAP_GEOFENCE_MAP_GEOFENCE_H_ */
