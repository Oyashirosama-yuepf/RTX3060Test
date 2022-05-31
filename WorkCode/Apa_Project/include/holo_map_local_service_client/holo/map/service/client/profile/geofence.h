/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geofence.h
 * @brief geofence.h
 * @author hulingjia@holomatic.com
 * @date "2021-03-18"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_GEOFENCE_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_GEOFENCE_H_

#include <string>

#include <holo/map/service/client/common/types.h>
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
/**
 * @addtogroup profile
 * @{
 *
 */

/**
 * @brief Geofence profile, used to get geofence data info.
 *
 */
class Geofence : public ProfileBase
{
public:
    /// Define persent type.
    using PersentPosType               = holo::float64_t;
    ///Redefine Concrete SegmentInfo.
    using ConcreteSegmentInfoType      = PersentSegment<PersentPosType,ProfileIdType>;
    
    ///Redefine UTC time,the number of seconds since 1970-01-01 00:00:00.
    using UTCTime      = holo::uint64_t;
    ///Redefine geofence FunctionType.
    using FunctionType = holo::uint32_t;
    ///Redefine geofence level.
    using Level        = holo::uint32_t;

    /**
     * @brief Define geofence feature type.
     */
    enum GeofenceFeatureType : holo::uint8_t
    {
        kGEOFENCE_FEATURE_TYPE_UNKNOWN = 0,     ///< Unknown Feature Type.
        kGEOFENCE_FEATURE_TYPE_LANE,            ///< Lane Feature Type.
        kGEOFENCE_FEATURE_TYPE_LINK,            ///< Link Feature Type.
        kGEOFENCE_FEATURE_TYPE_ROAD,            ///< Road Feature Type.
    };

    /**
     * @brief Constructor.
     */
    Geofence();

    /**
     * @brief Destructor.
     */
    virtual ~Geofence();

    /**
     * @brief Get geofence name.
     * 
     * @return Geofence name string.
     */
    static std::string const& Name();

    /**
     * @brief Get geofence name.
     * 
     * @return Geofence name string.
     */
    virtual std::string const& GetName() const override;

    /**
     * @brief Get geofence tile ids.
     * 
     * @return Geofence tile ids vector.
     */
    virtual ProfileIdVectorType const& GetTileIds() const;

    /**
     * @brief Get geofence function type value.
     * 
     * @return GeofenceFunctionType.
     */
    FunctionType GetGeofenceFunctionType() const;

    /**
     * @brief Get geofence level.
     * 
     * @return Geofence level.
     */
    Level GetGeofenceLevel() const;

    /**
     * @brief Judge time is in geofence valid.
     * 
     * @param[in] currtime AN UTC time.
     * @return true: Geofence is valid;
     *         false: Geofence is not valid.
     */    
    holo::bool_t IsValidTime(UTCTime const currtime) const;

    /**
     * @brief Get valid geofence percent start pos abd end pos on feature.
     * 
     * @param[in] type Geofence featureType type.
     * @param[in] id Feature id.
     * @param[out] segment SegmentInfo.
     * @return kOK: No error,find geofence feature;
     *         kNONE: No error,but can not find geofence feature with type or id;
     *         kFAILED: An error occurs in this function, refer to log for more details.
     */
    MapErrorCode GetGeofenceFeatureInfo(GeofenceFeatureType const& type, ProfileIdType const& id, ConcreteSegmentInfoType& segment) const;

    /**
     * @brief Get geofence feature type.
     * 
     * @return Geofence feature type enum.
     */
    GeofenceFeatureType GetGeofenceFeatureType() const;

    /**
     * @brief Get geofence contain feature ids.
     * 
     * @param[out] data Geofence contain feature ids.
     * @return true: No error;
     *         false: An error occurs in this function, refer to log for more details.
     */
    holo::bool_t GetGeofenceFeatureIds(ProfileIdVectorType& ids) const;

private:
    class GeofenceInner;
    std::unique_ptr<GeofenceInner> inner_;
};

using GeofenceSPtrType = std::shared_ptr<Geofence>;
using GeofenceCSPtrType = std::shared_ptr<Geofence const>;

/**
 * @}
 *
 */
} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_GEOFENCE_H_ */