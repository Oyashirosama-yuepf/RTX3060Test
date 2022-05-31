/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geofence_manager.h
 * @brief This header file defines the database of geofence and its addition, deletion, modification and query
 * operations.
 * @author lisong@holomatic.com
 * @date 2020-05-06
 */

#ifndef HOLO_MAP_DATABASE_GEOFENCE_MANAGER_H_
#define HOLO_MAP_DATABASE_GEOFENCE_MANAGER_H_

#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include <holo/log/hololog.h>

#include <holo/core/types.h>
#include <holo/map/common_def.h>

#include <holo/map/database/db_engine.h>
#include <holo/map/geofence/geofence_common.h>
#include <holo/map/geofence/map_geofence.h>

#define DEBUG_MAP_GEOFENCE_DATABASE 0

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
 * @brief this class defines database of geofence and its addition, deletion, modification and query operations.
 *
 */
class GeofenceManager
{
public:
    /// Typedefs
    using PreparedSqlStmtSPtrType = DBEngine::PreparedSqlStmtSPtrType;
    using PreparedSqlStmtCSPtrType = DBEngine::PreparedSqlStmtCSPtrType;

    /**
     * @brief Constructor
     */
    GeofenceManager() = default;

    /**
     * @brief Destructor
     */
    ~GeofenceManager() = default;

    /// GeofenceManager object can not be copied and moved.
    GeofenceManager(GeofenceManager const& other) = delete;
    GeofenceManager& operator=(GeofenceManager const& other) = delete;

    GeofenceManager(GeofenceManager&& other) = delete;
    GeofenceManager& operator=(GeofenceManager&& other) = delete;

public:
    /**
     * @brief Init a GeofenceManager object
     *
     * @param[in] db_path Geofence db file path
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Init(std::string const& db_path);

    /**
     * @brief Clear all records of tables from GeofenceDB.
     *
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Clear() const;

    /**
     * @brief Close GeofenceDB.
     */
    void Close()
    {
        if (nullptr == db_engine_ptr_)
        {
            LOG(ERROR) << "GeofenceManager::Close, derlying db engine pointer is null.";
            return;
        }
        db_engine_ptr_->Close();
    }

    /**
     * @brief Insert a geofence(MapGeofence object) into GeofenceDB.
     *
     * @param[in] geofence Geofence object
     * @param[out] geofence_id ID of that inserted record
     * @return True if successful,
     *         False if failed and geofence_id will be 0, which is invalid.
     */
    holo::bool_t InsertGeofence(MapGeofence const& geofence, holo::uint64_t& geofence_id) const;

    /**
     * @brief Insert a geofence(MapGeofence object) vector into GeofenceDB.
     *
     * @param[in] geofence_vec Geofence object vector
     * @param[out] geofence_id_vec IDs of those inserted records
     * @return True if successful,
     *         False if failed and geofence_id_vec will be empty.
     */
    holo::bool_t InsertGeofence(std::vector<MapGeofence> const& geofence_vec,
                                std::vector<holo::uint64_t>& geofence_id_vec) const;

    /**
     * @brief Query geofence from GeofenceDB by given ID
     *
     * @param[in] geofence_id Given geofence id
     * @param[out] result Result geofence(MapGeofence object)
     * @return True if successful,
     *         False if failed and MapGeofence.id will be invalid, which is 0.
     */
    holo::bool_t QueryGeofence(holo::uint64_t const geofence_id, MapGeofence& result) const;

    /**
     * @brief Query geofences from GeofenceDB by given IDs
     *
     * @param[in] geofence_ids Given geofence ids
     * @param[out] result Result geofences(MapGeofence object)
     * @return True if successful,
     *         False if failed and result will be empty.
     */
    holo::bool_t QueryGeofence(std::vector<holo::uint64_t> const& geofence_ids, std::vector<MapGeofence>& result) const;

    /**
     * @brief Query geofence id(s) from GeofenceDB by given tile ID.
     *
     * @param[in] tile_id Given tile ID
     * @param[out] geofence_id_vec Result ids of geofence vector query from DB.
     * @return True if successful,
     *         False if failed and geofence_id_vec will be empty.
     */
    holo::bool_t QueryGeofence(holo::uint64_t const tile_id, std::vector<holo::uint64_t>& geofence_id_vec) const;

    /**
     * @brief Query geofence(s) from GeofenceDB by given tile ID
     *
     * @param[in] tile_id Given tile ID
     * @param[out] geofence_vec Result geofence vector query from DB.
     * @return True if successful,
     *         False if failed and geofence_vec will be empty.
     */
    holo::bool_t QueryGeofence(holo::uint64_t const tile_id, std::vector<MapGeofence>& geofence_vec) const;

    /**
     * @brief Query geofence id(s) from GeofenceDB by given tile ID.
     *
     * @param[in] tile_ids Given tile IDs
     * @param[out] tile_geofence_ids_map Result map of tiles and its geofence ids.
     * @return True if successful,
     *         False if failed and tile_geofences_map will be empty.
     */
    holo::bool_t QueryGeofence(std::vector<holo::uint64_t> const& tile_ids,
                               std::unordered_map<holo::uint64_t, std::vector<holo::uint64_t>>& tile_geofence_ids_hashmap) const;

    /**
     * @brief Query geofence(s) from GeofenceDB by given tile IDs
     *
     * @param[in] tile_ids Given tile IDs
     * @param[out] tile_geofences_map Result map of tiles and its geofences.
     * @return True if successful,
     *         False if failed and tile_geofences_map will be empty.
     */
    holo::bool_t QueryGeofence(std::vector<holo::uint64_t> const& tile_ids,
                               std::unordered_map<holo::uint64_t, std::vector<MapGeofence>>& tile_geofences_hashmap) const;

private:
    /// Enum for fields of class MapGeofence,
    /// used to map fields of class MapGeofence to columns of geofence table from GeofenceDB
    enum class GeofenceColIdx : holo::uint8_t
    {
        ID = 0,          ///< MapGeofence.id_
        Function,        ///< MapGeofence.function_
        GeofenceType,    ///< MapGeofence.type_
        Version,         ///< MapGeofence.version_
        CountryCode,     ///< MapGeofence.country_code_
        ProvinceCode,    ///< MapGeofence.province_code_
        CityCode,        ///< MapGeofence.city_code_
        CountyCode,      ///< MapGeofence.county_code_
        GeoType,         ///< MapGeofence.geo_type_
        Geometry,        ///< MapGeofence.geometry_
        MapLevel,        ///< MapGeofence.map_level_
        TileIDs,         ///< MapGeofence.tile_ids_
        FeatureType,     ///< MapGeofence.feature_type_
        FeatureIDs,      ///< MapGeofence.feature_ids_
        Enable,          ///< MapGeofence.enable_
        ValidType,       ///< MapGeofence.valid_type_
        ValidTime,       ///< MapGeofence.valid_time_
        CreateTimestamp, ///< MapGeofence.create_timestamp_
        UpdateTimestamp  ///< MapGeofence.update_timestamp_
    };

    /// Enum for fields of class MapGeofenceIndex,
    /// used to map fields of class MapGeofenceIndex to columns of geofence_index table from GeofenceDB
    enum class GeofenceIndexColIdx : holo::uint8_t
    {
        ID = 0,          ///< MapGeofenceIndex.id_
        MapLevel,        ///< MapGeofenceIndex.map_level_
        TileID,          ///< MapGeofenceIndex.tile_id_
        GeofenceIDs,     ///< MapGeofenceIndex.geofence_ids_
        CreateTimestamp, ///< MapGeofenceIndex.create_timestamp_
        UpdateTimestamp  ///< MapGeofenceIndex.update_timestamp_
    };

private:
    /**
     * @brief Bind object(maybe its related fields, if T is a class) to prepared sql stmt.
     *
     * @tparam T Type of object bind to prepared sql stmt.
     * @param[in] obj Object of type T
     * @param[in] prepared_sql_stmt_ptr Prepared sql stmt
     * @param[in] for_insert If true this function is used for prepared sql stmt of insertion
     *                       If false this function is used for prepared sql stmt of update
     * @return True if successful,
     *         False if failed.
     */
    template <typename T>
    static holo::bool_t bindPreparedSqlStmt(T const& obj, PreparedSqlStmtSPtrType const prepared_sql_stmt_ptr,
                                            holo::bool_t const for_insert = true);

    /**
     * @brief Insert a record to GeofenceDB
     *
     * @tparam T Type of object to be inserted to Geofence DB,
     *           its structure is usually similar to corresponding row from table
     *           For example: if T is MapGeofence, then its structure should similar to row of geofence table from GeofenceDB.
     *
     * @param[in] obj Object of type T to be inserted to Geofence DB
     * @param[in] insert_sql_stmt_ptr Prepared sql stmt for insertion
     * @param[in] query_sql_stmt_ptr Prepared sql stmt used to query id of that inserted record from GeofenceDB
     * @param[out] result_id Record ID of that inserted record
     * @return True if successful,
     *         False if failed.
     */
    template <typename T>
    holo::bool_t insertWithResultID(T const& obj, PreparedSqlStmtSPtrType const insert_sql_stmt_ptr,
                                    PreparedSqlStmtSPtrType const query_sql_stmt_ptr, holo::uint64_t& result_id) const
    {
        result_id = 0UL;
        if (nullptr == db_engine_ptr_)
        {
            LOG(ERROR) << "GeofenceManager::insertWithResultID failed, underlying db engine pointer is null.";
            return false;
        }
        if (!bindPreparedSqlStmt(obj, insert_sql_stmt_ptr))
        {
            LOG(ERROR) << "GeofenceManager::insertWithResultID failed, can not bind insert prepared sql stmt.";
            return false;
        }
        holo::int32_t insert_result_count = -1;
        if (!(db_engine_ptr_->Insert(insert_sql_stmt_ptr, insert_result_count) && insert_result_count == 1))
        {
            LOG(ERROR) << "GeofenceManager::insertWithResultID failed, insert count is " << insert_result_count;
            return false;
        }
#if DEBUG_MAP_GEOFENCE_DATABASE
        LOG(INFO) << "GeofenceManager::insertWithResultID, insert count is " << insert_result_count;
#endif // DEBUG_MAP_GEOFENCE_DATABASE
        auto const get_last_inserted_id = [](PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const col_idx,
                                             holo::uint64_t& id) -> holo::bool_t {
            return DBEngine::GetColumnVal(sql_stmt_ptr, col_idx, id);
        };
        std::vector<holo::uint64_t> inserted_ids;
        if (!(db_engine_ptr_->Query(query_sql_stmt_ptr, get_last_inserted_id, inserted_ids) && !inserted_ids.empty()))
        {
            LOG(ERROR) << "GeofenceManager::insertWithResultID failed, can not get last inserted id.";
            return false;
        }
        result_id = inserted_ids.back();
        return true;
    }

    /**
     * @brief Insert a record vector to GeofenceDB
     *
     * @tparam T Type of objects from vector to be inserted to Geofence DB,
     *         its structure is usually similar to corresponding row from table
     *         For example: if T is MapGeofence, then its structure should similar to row of geofence table from GeofenceDB.
     *
     * @param[in] obj_vec Object vector of type T to be inserted to Geofence DB
     * @param[in] insert_sql_stmt_ptr Prepared sql stmt for insertion
     * @param[in] query_sql_stmt_ptr Prepared sql stmt used to query id of that inserted record from GeofenceDB
     * @param[out] result_id_vec Record IDs of those inserted record vector
     * @return True if successful,
     *         False if failed.
     */
    template <typename T>
    holo::bool_t insertWithResultID(std::vector<T> const& obj_vec, PreparedSqlStmtSPtrType const insert_sql_stmt_ptr,
                                    PreparedSqlStmtSPtrType const query_sql_stmt_ptr, std::vector<holo::uint64_t>& result_id_vec) const
    {
        result_id_vec.clear();
        if (nullptr == db_engine_ptr_)
        {
            LOG(ERROR) << "GeofenceManager::insertWithResultID failed, underlying db engine pointer is null.";
            return false;
        }
        if (!db_engine_ptr_->BeginTransaction())
        {
            LOG(ERROR) << "GeofenceManager::insertWithResultID failed, BeginTransaction failed.";
            return false;
        }
        for (T const& obj : obj_vec)
        {
            holo::uint64_t result_id = 0UL;
            if (!(insertWithResultID(obj, insert_sql_stmt_ptr, query_sql_stmt_ptr, result_id) && IsIDValid(result_id)))
            {
                LOG(ERROR) << "GeofenceManager::insertWithResultID failed.";
                result_id_vec.clear();
                if (!db_engine_ptr_->RollbackTransection())
                {
                    LOG(ERROR) << "GeofenceManager::insertWithResultID failed, RollbackTransection failed.";
                    return false;
                }
                return false;
            }
            result_id_vec.push_back(result_id);
        }
        if (!db_engine_ptr_->CommitTransection())
        {
            LOG(ERROR) << "GeofenceManager::insertWithResultID failed, CommitTransection failed.";
            result_id_vec.clear();
            return false;
        }
        return true;
    }

    /**
     * @brief Update a record to GeofenceDB
     *
     * @tparam T Type of object to be updated to Geofence DB,
     *
     * @param[in] obj Object of type T to be updated to Geofence DB
     * @param[in] update_sql_stmt_ptr Prepared sql stmt for update
     * @return True if successful,
     *         False if failed.
     */
    template<typename T>
    holo::bool_t updateByObject(T const& obj, PreparedSqlStmtSPtrType const update_sql_stmt_ptr) const
    {
        if (nullptr == db_engine_ptr_)
        {
            LOG(ERROR) << "GeofenceManager::updateByObject failed, underlying db engine pointer is null.";
            return false;
        }
        if (!IsIDValid(obj.GetID()))
        {
            LOG(ERROR) << "GeofenceManager::updateByObject failed, invalid object ID.";
            return false;
        }
        if (!bindPreparedSqlStmt(obj, update_sql_stmt_ptr, false))
        {
            LOG(ERROR) << "GeofenceManager::updateByObject failed, bindPreparedSqlStmt falied.";
            return false;
        }
        holo::int32_t update_obj_count = 0;
        if (!db_engine_ptr_->Update(update_sql_stmt_ptr, update_obj_count) && update_obj_count == 1)
        {
            LOG(ERROR) << "GeofenceManager::updateByObject failed, Update falied.";
            return false;
        }
        return true;
    }

    /**
     * @brief Update records to GeofenceDB
     *
     * @tparam T Type of objects to be updated to Geofence DB,
     *
     * @param[in] obj_vec Object vector of type T to be updated to Geofence DB
     * @param[in] update_sql_stmt_ptr Prepared sql stmt for update
     * @return True if successful,
     *         False if failed.
     */
    template<typename T>
    holo::bool_t updateByObjectVector(std::vector<T> const& obj_vec, PreparedSqlStmtSPtrType const update_sql_stmt_ptr) const
    {
        if (nullptr == db_engine_ptr_)
        {
            LOG(ERROR) << "GeofenceManager::updateByObjectVector failed, underlying db engine pointer is null.";
            return false;
        }
        if (!db_engine_ptr_->BeginTransaction())
        {
            LOG(ERROR) << "GeofenceManager::updateByObjectVector failed, BeginTransaction failed.";
            return false;
        }
        for (T const& obj : obj_vec)
        {
            if (!updateByObject(obj, update_sql_stmt_ptr))
            {
                LOG(ERROR) << "GeofenceManager::updateByObjectVector failed, updateByObject failed.";
                if (!db_engine_ptr_->RollbackTransection())
                {
                    LOG(ERROR) << "GeofenceManager::updateByObjectVector failed, RollbackTransection failed.";
                    return false;
                }
                return false;
            }
        }
        if (!db_engine_ptr_->CommitTransection())
        {
            LOG(ERROR) << "GeofenceManager::updateByObjectVector failed, CommitTransection failed.";
            return false;
        }
        return true;
    }

    /**
     * @brief Delete record from GeofenceDB by ID
     *
     * @param[in] object_id Object id corresponding to record from GeofenceDB
     * @param[in] delete_sql_stmt_ptr Prepared sql stmt for delete
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t deleteObject(holo::uint64_t const object_id, PreparedSqlStmtSPtrType const delete_sql_stmt_ptr) const;

    /**
     * @brief Delete records from GeofenceDB by table_name and IDs
     *
     * @param[in] table_name Name of table
     * @param[in] object_id Object id corresponding to record from GeofenceDB
     * @param[in] delete_sql_stmt_ptr Prepared sql stmt for delete
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t deleteObjectVector(std::string const& table_name, std::vector<holo::uint64_t> const& object_ids) const;

    /**
     * @brief Check if a column index in row is valid for MapGeofence
     * @details As mentioned above, MapGeofence is used to receive row of geofence table query from GeofenceDB,
     *          so each column is corresponding to field of MapGeofence
     *
     * @tparam[in] col_idx Given column index
     * @return True if valid,
     *         False if invalid.
     */
    static holo::bool_t isColIdxValidForGeofence(holo::int32_t const col_idx)
    {
        return static_cast<holo::int32_t>(GeofenceColIdx::ID) <= col_idx &&
               col_idx <= static_cast<holo::int32_t>(GeofenceColIdx::UpdateTimestamp);
    }

    /**
     * @brief Check if a column index in row is valid for MapGeofenceIndex
     * @details As mentioned above, MapGeofenceIndex is used to receive row of geofence_index table query from GeofenceDB,
     *          so each column is corresponding to field of MapGeofenceIndex
     *
     * @tparam[in] col_idx Given column index
     * @return True if valid,
     *         False if invalid.
     */
    static holo::bool_t isColIdxValidForGeofenceIndex(holo::int32_t const col_idx)
    {
        return static_cast<holo::int32_t>(GeofenceIndexColIdx::ID) <= col_idx &&
               col_idx <= static_cast<holo::int32_t>(GeofenceIndexColIdx::UpdateTimestamp);
    }

    /**
     * @brief Populate one field for MapGeofence object
     * @details As mentioned DBEngine.h, MapGeofence is used to receive row of geofence table query from GeofenceDB,
     *          so each column is corresponding to field of MapGeofence, we use column value to populate that field
     *
     * @param[in] prepared_sql_stmt_ptr Executed prepared sql stmt with result rows in it
     * @param[in] col_idx Column index in row
     * @param[out] geofence Result MapGeofence object with field populated
     * @return True if successful,
     *         False if failed.
     */
    static holo::bool_t populateFieldforMapGeofence(PreparedSqlStmtSPtrType const prepared_sql_stmt_ptr,
                                                    holo::int32_t const col_idx, MapGeofence& geofence);

    /**
     * @brief Populate one field for MapGeofenceIndex object
     * @details As mentioned DBEngine.h, MapGeofenceIndex is used to receive row of geofence_index table query from GeofenceDB,
     *          so each column is corresponding to field of MapGeofenceIndex, we use column value to populate that field
     *
     * @param[in] prepared_sql_stmt_ptr Executed prepared sql stmt with result rows in it
     * @param[in] col_idx Column index in row
     * @param[out] mapgeofence_index Result MapGeofenceIndex object with field populated
     * @return True if successful,
     *         False if failed.
     */
    static holo::bool_t populateFieldforMapGeofenceIndex(PreparedSqlStmtSPtrType const prepared_sql_stmt_ptr,
                                                         holo::int32_t const col_idx,
                                                         MapGeofenceIndex& mapgeofence_index);

    /**
     * @brief Insert a geofence index(MapGeofenceIndex object) into GeofenceDB.
     *
     * @param[in] geofence_idx Geofence index object
     * @param[out] geofence_idx_id ID of that inserted record
     * @return True if successful,
     *         False if failed and geofence_id will be 0, which is invalid.
     */
    holo::bool_t insertGeofenceIndex(MapGeofenceIndex const& geofence_idx, holo::uint64_t& geofence_idx_id) const
    {
        return insertWithResultID(geofence_idx, insert_geofence_idx_prepared_sqlstmt_,
                                  query_last_insert_geofence_index_id_prepared_sqlstmt_, geofence_idx_id);
    }

    /**
     * @brief Insert a geofence index(MapGeofenceIndex object) vector into GeofenceDB.
     *
     * @param[in] geofence_idx_vec Geofence index object vector
     * @param[out] geofence_idx_id_vec IDs of those inserted records
     * @return True if successful,
     *         False if failed and geofence_idx_id_vec will be empty.
     */
    holo::bool_t insertGeofenceIndex(std::vector<MapGeofenceIndex> const& geofence_idx_vec,
                                     std::vector<holo::uint64_t>& geofence_idx_id_vec) const
    {
        return insertWithResultID(geofence_idx_vec, insert_geofence_idx_prepared_sqlstmt_,
                                  query_last_insert_geofence_index_id_prepared_sqlstmt_, geofence_idx_id_vec);
    }

    /**
     * @brief Query geofence index from GeofenceDB by given tile ID
     *
     * @param[in] tile_id Given tile ID
     * @param[out] result Result geofence index(MapGeofenceIndex object).
     * @return True if successful,
     *         False if failed and MapGeofenceIdex.id will be invalid, which is 0.
     */
    holo::bool_t queryGeofenceIndex(holo::uint64_t const tile_id, MapGeofenceIndex& result) const;

    /**
     * @brief Query geofence index from GeofenceDB by given tile IDs
     *
     * @param[in] tile_ids Given tile IDs
     * @param[out] result Result geofence indexs(MapGeofenceIndex object).
     * @return True if successful,
     *         False if failed and result will be empty.
     */
    holo::bool_t queryGeofenceIndex(std::vector<holo::uint64_t> const& tile_ids, std::vector<MapGeofenceIndex>& result) const;

    /**
     * @brief Update geofence index to GeofenceDB
     * @note if MapGeofenceIndex.id 0(which is invalid), this operation will not success.
     *
     * @param[in] new_geofence_index Given geofence index(MapGeofenceIndex object)
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t updataGeofenceIndex(MapGeofenceIndex const& new_geofence_index) const
    {
        return updateByObject(new_geofence_index, update_geofence_idx_prepared_sqlstmt_);
    }

    /**
     * @brief Update geofence index vector to GeofenceDB
     * @note if MapGeofenceIndex.id 0(which is invalid), this operation will not success.
     *
     * @param[in] new_geofence_index_vec Given geofence index(MapGeofenceIndex object) vector
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t updataGeofenceIndex(std::vector<MapGeofenceIndex> const& new_geofence_index_vec) const
    {
        return updateByObjectVector(new_geofence_index_vec, update_geofence_idx_prepared_sqlstmt_);
    }

private:
    /// Underlying DBEngine pointer
    DBEngineUPtrType db_engine_ptr_ = nullptr;

    /// Prepared sql stmt of record insertion of geofence table
    PreparedSqlStmtSPtrType insert_geofence_prepared_sqlstmt_;

    /// Prepared sql stmt of record insertion of geofence_index table
    PreparedSqlStmtSPtrType insert_geofence_idx_prepared_sqlstmt_;

    /// Prepared sql stmt of record query of geofence table
    PreparedSqlStmtSPtrType query_geofence_prepared_sqlstmt_;

    /// Prepared sql stmt of id query for last insert record of geofence table
    PreparedSqlStmtSPtrType query_last_insert_geofence_id_prepared_sqlstmt_;

    /// Prepared sql stmt of record query of geofence_index table
    PreparedSqlStmtSPtrType query_geofence_idx_prepared_sqlstmt_;

    /// Prepared sql stmt of id query for last insert record of geofence_index table
    PreparedSqlStmtSPtrType query_last_insert_geofence_index_id_prepared_sqlstmt_;

    /// Prepared sql stmt of record update of geofence table
    PreparedSqlStmtSPtrType update_geofence_prepared_sqlstmt_;

    /// Sql of record update of geofence_index table
    PreparedSqlStmtSPtrType update_geofence_idx_prepared_sqlstmt_;

    /// Prepared sql stmt of record deletion of geofence table
    PreparedSqlStmtSPtrType delete_geofence_prepared_sqlstmt_;

    /// Prepared sql stmt of record deletion of geofence_index table
    PreparedSqlStmtSPtrType delete_geofence_idx_prepared_sqlstmt_;

};  // Class GeofenceManager

/// Handy typedefs
using GeofenceManagerUPtrType  = std::unique_ptr<GeofenceManager>;
using GeofenceManagerCUPtrType = std::unique_ptr<GeofenceManager const>;

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

#endif /* HOLO_MAP_DATABASE_GEOFENCE_MANAGER_H_ */
