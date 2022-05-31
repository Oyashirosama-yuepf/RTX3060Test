/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file base.h
 * @brief base.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-11"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_BASE_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_BASE_H_

#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/map/common/types.h>
#include <holo/map/format/base/base.h>
#include <holo/map/service/client/common/geometry.h>
#include <holo/map/service/client/common/types.h>
#include <holo/map/service/session/utility.h>

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

using ProfileIdType         = holo::uint64_t;
using ProfileIdVectorType   = std::vector<ProfileIdType>;

using ProfileTypeValue = holo::uint8_t;

enum class ProfileType : ProfileTypeValue
{
    kUNKNOWN            = 0,
    kTILE,
    kROAD,
    kLANE,
    kLANE_GROUP,
    kLANE_BOUNDARY,
    kINTERSECTION,
    kOBJECT,
    kROUTING_PATH,
    kGEOFENCE,
    kQUASI_DYNAMIC_LANE,
    kQUASI_DYNAMIC_LANE_GROUP,
    kQUASI_DYNAMIC_REGION,
    kSD_ROAD,
    kMAX,
};

enum class ProfileObjectType : ProfileTypeValue
{
    kOBJECT_TYPE_UNKNOWN            = 0,
    kOBJECT_TYPE_SIGN,
    kOBJECT_TYPE_POLE,
    kOBJECT_TYPE_LINEAR_INFO,
    kOBJECT_TYPE_REGIONAL_INFO,
    kOBJECT_TYPE_STOP_LINE,
    kOBJECT_TYPE_TRAFFIC_LIGHT,
    kOBJECT_TYPE_TRAFFIC_LIGHT_GROUP,
    kOBJECT_TYPE_PEDESTRIAN_CROSSING,
    kOBJECT_TYPE_TRAFFIC_SIGN,
    kOBJECT_TYPE_PARKING_LOT,
    kOBJECT_TYPE_PARKING_FLOOR,
    kOBJECT_TYPE_PARKING_BACKGROUND,
    kOBJECT_TYPE_PARKING_POI,
    kOBJECT_TYPE_PARKING_SPACE,
    kOBJECT_TYPE_MAX,
};

class ProfileBase
{
public:
    using RawFeatureType        = holo::map::format::Base::FeatureType;
    using RawProfileType        = holo::map::format::Base;
    using RawProfileSPtrType    = std::shared_ptr<RawProfileType>;

    using PatternType           = holo::map::service::session::SessionType::PatternType;

    /// Define distance types for Profiles.
    using Distance      = holo::map::service::client::common::DistanceMeterType;
    using DistanceM     = holo::map::service::client::common::DistanceMeterType;
    using DistanceCM    = holo::map::service::client::common::DistanceCentermeterType;

    using GeometryType = holo::map::service::client::geometry::GeoBase;

    using ProfileTypeEnumType = std::vector<ProfileType>;

    ProfileBase() = default;
    virtual ~ProfileBase() = default;

    ProfileBase(ProfileBase const&) = delete;
    ProfileBase(ProfileBase &&) = delete;

    ProfileBase& operator = (ProfileBase const&) = delete;
    ProfileBase& operator = (ProfileBase&&) = delete;

    explicit ProfileBase(ProfileType const t);

    virtual ProfileType GetType() const;

    virtual ProfileIdType GetId() const;

    virtual void SetId(ProfileIdType const id);

    virtual ProfileIdVectorType const& GetTileIds() const;
    
    virtual void SetReferenceIds(ProfileIdVectorType const& ids);
    virtual ProfileIdVectorType GetReferenceIds() const;

    virtual void SetPatternType(PatternType const t);
    virtual PatternType GetPatternType() const;

    static std::string const& Name();

    virtual std::string const& GetName() const;

    virtual GeometryType const& GetGeometry() const;
    virtual void SetGeometry(GeometryType const& g);
    virtual void SetGeometry(GeometryType&& g);

    virtual RawProfileSPtrType GetRawPtr() const;
    virtual void SetRawPtr(RawProfileSPtrType ptr);

    static ProfileTypeEnumType const& GetAvailableProfileTypes();

protected:
    RawProfileSPtrType raw_ptr_ = nullptr;

    ProfileType type_         = ProfileType::kUNKNOWN;
    ProfileIdType id_         = 0;
    PatternType pattern_type_ = PatternType::PATTERN_REGION;

    /// Reference ids is the common feature base on reference feature(like: tile, path).
    ProfileIdVectorType reference_ids_;
};

/// Define a raw pointer type for class of ProfileBase.
using ProfileBasePtrType    = ProfileBase*;
/// Define a shared pointer type for class of ProfileBase.
using ProfileBaseSPtrType   = std::shared_ptr<ProfileBase>;
/// Define a const shared pointer type for class of ProfileBase.
using ProfileBaseCSPtrType  = std::shared_ptr<ProfileBase const>;

namespace helper
{
/**
 * @addtogroup helper
 * @{
 *
 */

/// Redefine feature type for namespace of profile.
using FeatureType = holo::map::format::Base::FeatureType;

/**
 * @brief Traits profile types from holo::map::service::client::profile::xxx.
 */
template <class T>
struct ProfileTraits
{
    using RawType               = T;                            ///< Define self type for T.
    using PtrType               = T*;                           ///< Define pointer type for T.
    using SPtrType              = std::shared_ptr<T>;           ///< Define shared smart pointer type for T.
    using CSPtrType             = std::shared_ptr<T const>;     ///< Define shared smart pointer type for const T.
    using UPtrType              = std::unique_ptr<T>;           ///< Define unique smart pointer type for T.
    using CUPtrType             = std::unique_ptr<T const>;     ///< Define unique smart pointer type for const T.
}; ///< End of struct ProfileTraits

/**
 * @brief Traits profile types from holo::map::service::client::profile::***SPtrType.
 */
template <class T>
struct ProfileTraits<std::shared_ptr<T>>
{
    using RawType               = T;                            ///< Define self type for T.
    using PtrType               = T*;                           ///< Define pointer type for T.
    using SPtrType              = std::shared_ptr<T>;           ///< Define shared smart pointer type for T.
    using CSPtrType             = std::shared_ptr<T const>;     ///< Define shared smart pointer type for const T.
    using UPtrType              = std::unique_ptr<T>;           ///< Define unique smart pointer type for T.
    using CUPtrType             = std::unique_ptr<T const>;     ///< Define unique smart pointer type for const T.
}; ///< End of struct ProfileTraits

/**
 * @brief Traits profile types from holo::map::service::client::profile::***CSPtrType.
 */
template <class T>
struct ProfileTraits<std::shared_ptr<T const>>
{
    using RawType               = T;                            ///< Define self type for T.
    using PtrType               = T*;                           ///< Define pointer type for T.
    using SPtrType              = std::shared_ptr<T>;           ///< Define shared smart pointer type for T.
    using CSPtrType             = std::shared_ptr<T const>;     ///< Define shared smart pointer type for const T.
    using UPtrType              = std::unique_ptr<T>;           ///< Define unique smart pointer type for T.
    using CUPtrType             = std::unique_ptr<T const>;     ///< Define unique smart pointer type for const T.
}; ///< End of struct ProfileTraits

/**
 * @brief Create a new and empty object for Profile by type.
 * 
 * @param[in] type Profile type.
 * @return A pointer point to a new Profile object. If failed, the
 *         return pointer will nullptr.
 */
ProfileBasePtrType CreateProfileByType(ProfileType const type);

/**
 * @brief Check if the feature type is an object feature type.
 * 
 * @param[in] type Feature type, refer to holo::map::format::Base::FeatureType for
 *            more details.
 * @return true: The feature type is an object.
 *         false: Otherwise.
 */
holo::bool_t IsFeatureObjectType(FeatureType const type);

/**
 * @brief Convert Feature type to Profile type.
 * 
 * @param[in] type Feature type, refer to holo::map::format::Base::FeatureType for
 *            more details.
 * @return If failed, the return type will be ProfileType::kUNKNOWN.
 */
ProfileType FeatureType2ProfileType(FeatureType const type);

/**
 * @brief Convert Profile type to feature type.
 * 
 * @param[in] type Profile type, refer to holo::map::service::client::profile::ProfileType for
 *            more details.
 * @return If failed, the return type will be FeatureType::UNKNOWN.
 */
FeatureType ProfileType2FeatureType(ProfileType const type);

/**
 * @brief Convert Feature type to Profile object type.
 * 
 * @param[in] type Feature type, refer to holo::map::format::Base::FeatureType for
 *            more details. Only supports object-like types.
 * @return If failed, the return type will be ProfileObjectType::kOBJECT_TYPE_UNKNOWN.
 */
ProfileObjectType FeatureType2ProfileObjectType(FeatureType const type);

/**
 * @brief Convert ProfileObjectType type to feature type.
 * 
 * @param[in] type Profile object type, refer to holo::map::service::client::profile::ProfileObjectType
 *            for more details.
 * @return If failed, the return type will be FeatureType::UNKNOWN, Only supports object-like types.
 */
FeatureType ProfileObjectType2FeatureType(ProfileObjectType const type);

/**
 * @brief Check if the profile type has sub profile type.
 * 
 * @param[in] type Profile type, refer to holo::map::service::client::profile::ProfileType for
 *            more details.
 * @return true: Has sub profile type.
 *         false: Otherwise.
 */
holo::bool_t HasProfileSubType(ProfileType const type);

/**
 * @brief Convert feature type to sub profile type.
 * 
 * @param[in] type Feature type, refer to holo::map::format::Base::FeatureType for
 *            more details, Only supports object-like types.
 * @return If failed, the return value will be 0.
 */
ProfileTypeValue FeatureType2ProfileSubType(FeatureType const type);

/**
 * @brief Convert profile type to feature type.
 * 
 * @param[in] type Profile type, refer to holo::map::service::client::profile::ProfileType for
 *            more details.
 * @param[in] sub_type Profile *** type, refer to holo::map::service::client::profile::Profile***Type,
 *            if no sub type, it can be 0.
 * @return If failed, the return type will be FeatureType::UNKNOWN.
 */
FeatureType ProfileSubType2FeatureType(ProfileType const type, ProfileTypeValue const sub_type = 0);

/**
 * @}
 */
} ///< namespace helper

/**
 * @}
 */
} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_BASE_H_ */
