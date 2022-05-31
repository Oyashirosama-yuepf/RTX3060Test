/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geofence_extractor.h
 * @brief This header file defines geofence extractor for extracting geofences from geofence database.
 * @author lisong@holomatic.com
 * @date 2020-05-11
 */

#ifndef HOLO_MAP_FEATURE_GEOFENCE_EXTRACTOR_H_
#define HOLO_MAP_FEATURE_GEOFENCE_EXTRACTOR_H_

#include <sstream>
#include <string>
#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/common/geometry.h>
#include <holo/map/feature/map_attributor/geofence/map_geofence_cache.h>
#include <holo/map/geofence.h>
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
 * @brief this class defines geofence extractor for extracting geofences from geofence database.
 *
 */
class GeofenceExtractor
{
public:
    /**
     * @brief this class defines output of GeofenceExtractor
     *
     */
    struct Output
    {
        holo::map::Geofences geofences;  ///< Geofences
        static std::string   FormatToString(Output const& output);
    };

public:
    /**
     * @brief Constructor
     */
    GeofenceExtractor() = default;

    /**
     * @brief Destructor
     */
    ~GeofenceExtractor() = default;

    /// GeofenceExtractor object can not be copied and moved.
    GeofenceExtractor(GeofenceExtractor const& other) = delete;
    GeofenceExtractor& operator=(GeofenceExtractor const& other) = delete;

    GeofenceExtractor(GeofenceExtractor&& other) = delete;
    GeofenceExtractor& operator=(GeofenceExtractor&& other) = delete;

public:
    /**
     * @brief Init a GeofenceExtractor object
     *
     * @param[in] ptr_ret Retriever pointer
     * @param[in] ptr_config Config pointer
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Init(RetrieverSPType const ptr_ret, navigator::config::NavigatorConfigSPtr const& ptr_config);

    /**
     * @brief Run mian process pipeline to generate output.
     *
     * @param[in] match_info Given match info
     * @param[in] route_info Given route info
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Run(holo::map::MapMatchInfo const& match_info, holo::map::RouteInfo2 const& route_info,
                     holo::common::Timestamp const& current_time);

    /**
     * @brief Reset geofence extractor.
     *
     * @return Nothing
     */
    void Reset()
    {
        if (local_geofence_cache_ptr_ == nullptr)
        {
            LOG(ERROR) << "GeofenceExtractor::Reset failed, local geofence cache pointer is null.";
            return;
        }
        local_geofence_cache_ptr_->Reset();
        geofence_vec_.SetGeofences({});
    }

    /**
     * @brief Get result output of geofence extractor
     *
     * @return Result geofences
     */
    holo::map::Geofences const& GetOutput() const
    {
        return geofence_vec_;
    }

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
     * @brief Check if given link is in geofence(s)
     *
     * @param[in] link_id Given link ID
     * @param[in] match_info Given match info
     * @param[in] route_info Given route info
     * @param[out] geofence_vec Geofences given link fall in
     * @return True if successful,
     *         False if failed and geofence_vec will be empty.
     */
    holo::bool_t isLinkInEnabledGeofences(holo::map::IdType const link_id, holo::map::MapMatchInfo const& match_info,
                                          holo::map::RouteInfo2 const& route_info, holo::common::Timestamp const& current_time,
                                          std::vector<MapGeofence>& geofence_vec);

    /**
     * @brief Get geofence vector for all Functions
     *
     * @param[in] match_info Given match info
     * @param[in] route_info Given route info
     * @return True if successful and result will be stored in geofence_vec_
     *         False if failed.
     */
    holo::bool_t getGeofences(holo::map::MapMatchInfo const& match_info, holo::map::RouteInfo2 const& route_info,
                              holo::common::Timestamp const& current_time);

private:
    /// Retriver pointer
    RetrieverSPType ret_ptr_ = nullptr;

    /// Local geofence cache pointer
    MapGeofenceCacheUPtrType local_geofence_cache_ptr_ = nullptr;

    /// Search range to extract geofences
    holo::float32_t search_range_ = 3000.0f;

    /// Internal result geofences of extractor
    holo::map::Geofences geofence_vec_;
};  ///< Class GeofenceExtractor

/// Handy typedefs
using GeofenceExtractorUPtrType  = std::unique_ptr<GeofenceExtractor>;
using GeofenceExtractorCUPtrType = std::unique_ptr<GeofenceExtractor const>;

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

#endif /* HOLO_MAP_FEATURE_GEOFENCE_EXTRACTOR_H_ */
