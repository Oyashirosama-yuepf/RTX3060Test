/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file retriever.h
 * @brief retriever.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-09"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_ENGINE_RETRIEVER_H_
#define HOLO_MAP_SERVICE_CLIENT_ENGINE_RETRIEVER_H_

#include <string>

#include <holo/common/coordinate.h>
#include <holo/map/common/common_macro.h>
#include <holo/map/service/client/common/structs.h>
#include <holo/map/service/client/profile/base.h>
#include <holo/map/service/client/profile/geofence.h>
#include <holo/map/service/client/profile/lane.h>
#include <holo/map/service/client/profile/lane_boundary.h>
#include <holo/map/service/client/profile/lane_group.h>
#include <holo/map/service/client/profile/quasi_dynamic_lane.h>
#include <holo/map/service/client/profile/quasi_dynamic_lane_group.h>
#include <holo/map/service/client/profile/quasi_dynamic_region.h>
#include <holo/map/service/client/profile/road.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace engine
{
/**
 * @addtogroup engine
 * @{
 *
 */

class MapEngine;

class Retriever
{
public:
    /// Redefine coordinate reference system type.
    using CoordinateType = holo::common::Coordinate;

    using ProfileType       = holo::map::service::client::profile::ProfileType;
    using ProfileTypeValue  = holo::map::service::client::profile::ProfileTypeValue;

    using ProfileIdType         = profile::ProfileIdType;
    using ProfileIdVectorType   = std::vector<ProfileIdType>;

    using ProfileBaseType                       = holo::map::service::client::profile::ProfileBase;
    using ProfileRoadType                       = holo::map::service::client::profile::Road;
    using ProfileLaneType                       = holo::map::service::client::profile::Lane;
    using ProfileLaneGroupType                  = holo::map::service::client::profile::LaneGroup;
    using ProfileLaneBoundaryType               = holo::map::service::client::profile::LaneBoundary;
    using ProfileGeofenceType                   = holo::map::service::client::profile::Geofence;
    using ProfileQuasiDynamicLaneType           = holo::map::service::client::profile::QuasiDynamicLane;
    using ProfileQuasiDynamicLaneGroupType      = holo::map::service::client::profile::QuasiDynamicLaneGroup;

    using ProfileBaseCSPtrType                  = holo::map::service::client::profile::ProfileBaseCSPtrType;
    using ProfileRoadCSPtrType                  = holo::map::service::client::profile::RoadCSPtrType;
    using ProfileLaneCSPtrType                  = holo::map::service::client::profile::LaneCSPtrType;
    using ProfileLaneGroupCSPtrType             = holo::map::service::client::profile::LaneGroupCSPtrType;
    using ProfileLaneBoundaryCSPtrType          = holo::map::service::client::profile::LaneBoundaryCSPtrType;
    using ProfileGeofenceCSPtrType              = holo::map::service::client::profile::GeofenceCSPtrType;
    using ProfileQuasiDynamicLaneCSPtrType      = holo::map::service::client::profile::QuasiDynamicLaneCSPtrType;
    using ProfileQuasiDynamicLaneGroupCSPtrType = holo::map::service::client::profile::QuasiDynamicLaneGroupCSPtrType;

    using ProfileBaseCSPtrVectorType    = std::vector<ProfileBaseCSPtrType>;

    using ProfileBaseRawPtrType         =  holo::map::service::client::profile::ProfileBase*;
    using ProfileBaseRawPtrVectorType   = std::vector<ProfileBaseRawPtrType>;

    using ProfileSPtrType   = std::shared_ptr<ProfileBaseType>;
    using ProfileCSPtrType  = std::shared_ptr<ProfileBaseType const>;

    using ProfileSPtrVectorType     = std::vector<ProfileSPtrType>;
    using ProfileCSPtrVectorType    = std::vector<ProfileCSPtrType>;

    using BackgroundStatusType = holo::map::service::client::common::BackgroundStatus;

    holo::bool_t GetVerbose() const noexcept;
    void SetVerbose(holo::bool_t const v) noexcept;

    MapErrorCode GetStatus();

    BackgroundStatusType const& GetBackgroundStatus() const noexcept;

    MapErrorCode GetProfile(ProfileType const type, ProfileIdType const id, ProfileCSPtrType& profile);
    MapErrorCode GetProfiles(ProfileType const type, ProfileIdVectorType const& ids, ProfileCSPtrVectorType& profiles);

    /**
     * @brief Fetch all profiles with same type from Retriever cache(Map Engine).
     * 
     * @param[in] type Profile type, refer to holo::map::service::client::profile::ProfileType
     *            for more details.
     * @param[out] ids Profile ids with same type.
     * @return kOK: No error.
     *         kNONE: No error, but no one is cached in Retriever.
     *         others: An occurs in this function, please refer to logs for more details.
     */
    MapErrorCode GetProfileIds(ProfileType const type, ProfileIdVectorType& ids);

    /**
     * @brief Fetch all profiles with same type from Retriever cache(Map Engine).
     * 
     * @param[in] type Profile type, refer to holo::map::service::client::profile::ProfileType
     *            for more details.
     * @param[in] sub_type profile sub type, refer to holo::map::server::client::profile::
     *            Profile***Type(like: ProfileObjectType and etc...).
     * @param[in] tile_id Tile id calculated by a position.
     * @param[out] ids Profile ids with same type.
     * @return kOK: No error.
     *         kNONE: No error, but no one is cached in Retriever.
     *         others: An occurs in this function, please refer to logs for more details.
     */
    MapErrorCode GetProfileIds(ProfileType const type, ProfileTypeValue const sub_type, ProfileIdType const tile_id,
        ProfileIdVectorType& ids);

    MapErrorCode GetLaneGroupAndLanesByLaneGroupId(ProfileIdType const& id, ProfileCSPtrType& group,
        ProfileCSPtrVectorType& lanes);

    MapErrorCode GetLaneGroupAndLanesAndLaneBoundariesByLaneGroupId(ProfileIdType const& id,
        ProfileCSPtrType& group, ProfileCSPtrVectorType& lanes, ProfileCSPtrVectorType& boundaries);

    /**
     * @brief Get geofence profile by geofence id.
     * 
     * @param[in] id Geofence id.
     * @param[out] geofence Geofence profile.
     * @return kOK: No error;
     *         kNONE: Can not find geofence profile;
     *         kFAILED: Find geofence profile error.
     */
    HOLO_MAP_DEPRECATED("Replace by access::GetProfileById") MapErrorCode GetGeofenceById(ProfileIdType const& id,
        ProfileCSPtrType& geofence);

    /**
     * @brief Get geofence profiles by geofence ids.
     * 
     * @param[in] ids Geofence ids.
     * @param[out] geofences Geofence profiles.
     * @return kOK: No error;
     *         kNONE: Can not find geofence profiles;
     *         kFAILED: Find geofence profiles error.
     */
    HOLO_MAP_DEPRECATED("Replace by access::GetProfileByIds") MapErrorCode GetGeofencesByIds(ProfileIdVectorType const& ids,
        ProfileCSPtrVectorType& geofences);

    holo::bool_t IsProfileExist(ProfileType const type, ProfileIdType const id);

    holo::bool_t IsProfileReady(ProfileType const type, ProfileIdType const id,
        holo::bool_t& result);

    void SyncProfile(ProfileType const type, ProfileIdVectorType const ids);

    /**
     * @brief Update global coordinate reference system for all the geometry
    *         features when current location is acrossing zone. 
     * 
     * @note: This function is not thread safe, and only be used within
     *        main engine thread.
     * @param[in] crs Coordinate reference system, if the new coordinate is different
     *            with global coordinate, all the points of all the geometry features
     *            will be converted to new coordinate.
     */
    void UpdateCRS(CoordinateType const& crs);
private:
    Retriever();
    virtual ~Retriever();

    Retriever(Retriever const&) = delete;
    Retriever(Retriever&&) = delete;

    Retriever& operator = (Retriever const&) = delete;
    Retriever& operator = (Retriever&&) = delete;

    static std::shared_ptr<Retriever> NewRetriever();

    static void FreeRetriever(Retriever* ptr);

private:
    class RetrieverInner;
    std::unique_ptr<RetrieverInner> inner_;

    friend class MapEngine;
};

/// Define smart pointer type for Retriever.
using RetrieverSPtrType = std::shared_ptr<Retriever>;

namespace access
{
/**
 * @addtogroup engine
 * @{
 *
 */

/**
 * @brief Get profile by type and id from retriever.
 * 
 * @tparam Ret holo::map::service::client::engine::RetrieverSPtrType;
 * @tparam Type holo::map::service::client::profile::ProfileType;
 * @tparam Id holo::map::service::client::profile::ProfileIdType;
 * @tparam T holo::map::service::client::profile::***CSPtrType.
 * @param[in] ret A retreever shared pinter.
 * @param[in] type Profile type.
 * @param[in] id Profile id.
 * @param[in] profile A shared pointer refer to Profile.
 * @return kOK: No error.
 *         kNONE: Target map profile not exist in retriever, note: profile will be nullptr.
 *         kFAILED: An error occurs in this function, please see logs for more details.
 */
template <typename Ret, typename Type, typename Id, typename T>
MapErrorCode GetProfileById(Ret ret, Type const type, Id const id,
    typename holo::map::service::client::profile::helper::ProfileTraits<T>::CSPtrType& profile)
{
    profile = nullptr;

    holo::map::service::client::profile::ProfileBaseCSPtrType base = nullptr;
    MapErrorCode const ec = ret->GetProfile(type, id, base);
    if (MapErrorCode::kNONE == ec)
    {
        return ec;
    }

    if (MapErrorCode::kOK != ec)
    {
        LOG(ERROR) << "GetProfileById fail, GetProfile fail, ec=" << static_cast<int>(ec)
                   << " id=" << id << " type=" << static_cast<int>(type);
        return ec;
    }

    if (nullptr == base)
    {
        LOG(ERROR) << "GetProfileById fail, GetProfile fail, ec=" << static_cast<int>(ec)
                   << " id=" << id << " type=" << static_cast<int>(type);
        return MapErrorCode::kFAILED;
    }

    profile = std::dynamic_pointer_cast<typename holo::map::service::client::profile::helper::ProfileTraits<T>
        ::RawType const>(base);
    if (nullptr == profile)
    {
        LOG(ERROR) << "GetProfileById fail, invalid profile, ec=" << static_cast<int>(ec)
                   << " id=" << id << " type=" << static_cast<int>(type);
        return MapErrorCode::kFAILED;
    }

    return MapErrorCode::kOK;
}

/**
 * @}
 */
}

/**
 * @}
 */
} ///< namespace engine
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_ENGINE_RETRIEVER_H_ */
