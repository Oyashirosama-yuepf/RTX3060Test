/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file adapter_base.h
 * @brief adapter_base.h
 * @author wanghaiyang@holomatic.com
 * @date "2021-01-14"
 */

#ifndef HOLO_MAP_ADAPTER_BASE_ADAPTER_BASE_H_
#define HOLO_MAP_ADAPTER_BASE_ADAPTER_BASE_H_

#include <string>

#include <holo/common/odometry.h>
#include <holo/map/adapter/base/geometry_base.h>
#include <holo/map/adapter/common/structs.h>
#include <holo/map/adapter/common/types.h>
#include <holo/map/common/common_type_define.h>
#include <holo/map/common/types.h>
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
/**
 * @addtogroup adapter
 * @{
 *
 */

/**
 * Define a structure for features which are with incomplete attributes.
 */
struct IncompleteFeatureInfo
{
    /// Feature type, only support LANE_BOUNDARY now.
    FeatureType type = FeatureType::UNKNOWN;
    /// Feature id.
    FeatureIdType id = 0;
    /// If true, traget feature is incomplete with losting preceding connections.
    holo::bool_t incomplete_preceding_topology  = false;
    /// If true, target feature is incomplete with losting succeeding connections.
    holo::bool_t incomplete_succeeding_topology = false;

    /**
     * @brief Format a IncompleteFeatureInfo to a JSON string.
     * 
     * @param[in] info An IncompleteFeatureInfo object.
     * @return A JSON string.
     */
    static std::string FormatToString(IncompleteFeatureInfo const& info);
}; /* End of struct IncompleteFeatureInfo */

class InitializerBase
{
public:
    InitializerBase() = default;
    virtual ~InitializerBase() = default;

    std::string const& GetConfig() const noexcept
    {
        return this->config_;
    }

    void SetConfig(std::string const& c)
    {
        this->config_ = c;
    }

    std::string const& GetUserName() const noexcept
    {
        return this->user_;
    }

    void SetUserName(std::string const& n)
    {
        this->user_ = n;
    }

    std::string const& GetPassword() const noexcept
    {
        return this->password_;
    }

    void SetPassword(std::string const& p)
    {
        this->password_ = p;
    }

    holo::bool_t GetVerbose() const noexcept
    {
        return this->verbose_;
    }

    void SetVerbose(holo::bool_t const v) noexcept
    {
        this->verbose_ = v;
    }

protected:
    std::string     config_;    ///< Database root directory.
    std::string     user_;      ///< Authorization for accessing database.
    std::string     password_;  ///< Authorization for accessing database.
    holo::bool_t    verbose_;   ///< If true, print debug information to log.
};

class InputerBase
{
public:
    InputerBase() = default;
    virtual ~InputerBase() = default;

    MapDataRange            range_;
};

class BaiduInputer : public InputerBase
{
public:
    using ProvinceCodeType          = std::string;
    using ProvinceCodeVectorType    = std::vector<ProvinceCodeType>;

    using OdometryType = holo::common::Odometryd;
    using RadiusType   = holo::uint64_t;

    using AlreadyExistenceHandle = std::function<holo::bool_t(FeatureType const, FeatureIdType const)>;

    /// Check if a target feature is with imcomplete topology, if with imcomplete topology, it will
    /// be re-compiled.
    /// FeatureType Feature type, only support LANE_GROUP(Baidu: Link type) when compile lane boundaries
    /// from a lane group.
    /// FeatureIdType Feature id, a lane group id(Baidu: Link id).
    /// holo::bool_t If true, check preceding topology, if false, check succeeding topology.
    using IncompleteTopologyHandle = std::function<holo::bool_t(FeatureType const, FeatureIdType const,
        holo::bool_t const)>;

    holo::bool_t IsProvinceMode() const noexcept;
    void SetProviceMode(holo::bool_t const m) noexcept;

    ProvinceCodeVectorType const& GetProvinceCodes() const noexcept;
    void SetProvinceCodes(ProvinceCodeVectorType const& codes);
    void SetProvinceCodes(ProvinceCodeVectorType&& codes);
    void AddProvinceCode(ProvinceCodeType const& code);

    OdometryType const& GetOdometry() const noexcept;
    void SetOdometry(OdometryType const& odo);

    RadiusType GetRadius() const noexcept;
    void SetRadius(RadiusType const r);

    /**
     * @brief Assign a hook to check if a feature has been cached.
     * 
     * @param[in] f A handle of AlreadyExistenceHandle.
     */
    void SetAlreadyExistenceCallback(AlreadyExistenceHandle& f);

    /**
     * @brief Assign a hool to check if a feature with incomplete topology.
     * 
     * @param[in] f A handle of IncompleteTopologyHandle.
     */
    void SetIncompleteTopologyCallback(IncompleteTopologyHandle& f);

    /**
     * @brief Check if a feature has been cached by retriever in outside.
     * 
     * @note If a feature has been cached, it will be not compiled again.
     * @param[in] t Feature type, refer to holo::map::format::Base::FeatureType for
     *              more details.
     * @param[in] id Feature id.
     * @return true: Target feature has been cached.
     *         false: Target feature has not been cached.
     */
    virtual holo::bool_t IsExist(FeatureType const t, FeatureIdType const id) const;

    /**
     * @brief Check if a feature with incomplete topology.
     * 
     * @param[in] t Feature type, only supprt LANE_GROUP now, because of only boundaries 
     *              maybe with incomplete topology when they are compiled from a lane group
     *              (Baidu: Link).
     * @param[in] id Feature id.
     * @param[in] pre_or_suc true: Check the preceding topology;
     *                       false: Check the succeeding topology.
     * @return true: Target feature be with incomplete topology.
     *         false: Target feature be with complete topology or doesn't set handle.
     */
    virtual holo::bool_t IsTopologyIncomplete(FeatureType const t, FeatureIdType const id,
        holo::bool_t const pre_or_suc) const;

    void Clear();

protected:
    /// Province mode. If true, we fetch data by province code.
    /// if false, we fetch data by current position.
    holo::bool_t            province_data_mode_ = false;
    /// Province codes for fetching data.
    ProvinceCodeVectorType  province_codes_;

    /// A position used to update local cache for HD map engine.
    OdometryType            odometry_;
    /// A search radius used for updating local cache for HD map engine.
    /// Unit: m.
    RadiusType              radius_ = 3000;

    /// A handle used to check if a feature has been cached.
    AlreadyExistenceHandle   existence_handle_ = nullptr;
    /// A handle used to check if a feature with incomplete topology.
    IncompleteTopologyHandle topology_handle_ = nullptr;
};

class OutputerBase
{
public:
    /// Redefine map server error code.
    using MapServiceErrorCodeType = holo::map::MapServiceErrorCode;

    OutputerBase() = default;
    virtual ~OutputerBase() = default;

    MapDataGroup data_;
    MapEngineStatus status_                  = MapEngineStatus::MAP_ENGINE_STATUS_OK;
    /// Used to return the error code of HD map engine to LMS.
    MapServiceErrorCodeType error_code_ = MapServiceErrorCodeType::kNO_ERROR;
};

/**
 * @brief Define output structure for Baidu adapter.
 */
class BaiduOutputer : public OutputerBase
{
public:
    /// Redefine a container to cache all the incomplete topology features.
    using IncompleteFeatureInfoCacheType = std::map<FeatureIdType, IncompleteFeatureInfo>;

    /**
     * @brief Default constructor.
     */
    BaiduOutputer() = default;

    /**
     * @brief Default destructor.
     */
    virtual ~BaiduOutputer() = default;

    /**
     * @brief Add a new incomplete feature..
     * 
     * @param[in] feature An IncompleteFeatureInfo object.
     */
    void AddIncompleteFeatureInfo(IncompleteFeatureInfo const& feature);

    /**
     * @brief Access all the incomplete features.
     * 
     * @return An incomplete features container.
     */
    IncompleteFeatureInfoCacheType const& GetIncompleteFeatureInfoCache() const;

    /**
     * @brief Clear all the incomplete features.
     */
    void ClearIncompleteFeautreInfos();

protected:
    /// Define a container storing features with incomplete topology.
    IncompleteFeatureInfoCacheType cache_;
}; /* End of class BaiduOutputer */

class AdapterBase
{
public:
    /// Redefine map server error code.
    using MapServiceErrorCodeType = holo::map::MapServiceErrorCode;

    AdapterBase() = default;
    virtual ~AdapterBase() = default;

    virtual AdapterType GetType() const = 0;

    virtual GeometryBase& GetGeometryConfig() = 0;

    virtual const GeometryBase& GetGeometryConfig() const = 0;

    /**
     * @brief Init adapter.
     * 
     * @param[in] base Initializer info.
     * @param[out] ec Hd map engine error code.
     * @return true: No error;
     *         false: An error occurs in this function, refer to log for more details.
     */
    virtual holo::bool_t Init(InitializerBase const& base, MapServiceErrorCode& ec) = 0;

    virtual holo::bool_t Run(InputerBase const& input, OutputerBase& output) = 0;

    class TileIdBase
    {
    public:
        TileIdBase() = default;
        virtual ~TileIdBase() = default;
    };
    virtual holo::bool_t AdaptTile(TileIdBase const& id, TileContainerType& tiles) = 0;

    class RoadIdBase
    {
    public:
        RoadIdBase() = default;
        virtual ~RoadIdBase() = default;
    };
    virtual holo::bool_t AdaptRoad(RoadIdBase const& id, RoadContainerType& roads) = 0;

    // class SdRoadIdBase
    // {
    // public:
    //     SdRoadIdBase() = default;
    //     virtual ~SdRoadIdBase() = default;
    // };
    // virtual holo::bool_t AdaptSdRoad(SdRoadIdBase const& id, SdRoadContainerType& roads) = 0;

    class LaneIdBase
    {
    public:
        LaneIdBase() = default;
        virtual ~LaneIdBase() = default;
    };
    virtual holo::bool_t AdaptLane(LaneIdBase const& id, LaneContainerType& lanes) = 0;

    class LaneGroupIdBase
    {
    public:
        LaneGroupIdBase() = default;
        virtual ~LaneGroupIdBase() = default;
    };
    virtual holo::bool_t AdaptLaneGroup(LaneGroupIdBase const& id, LaneGroupContainerType& groups) = 0;

    class LaneBoundaryIdBase
    {
    public:
        LaneBoundaryIdBase() = default;
        virtual ~LaneBoundaryIdBase() = default;
    };
    virtual holo::bool_t AdaptLaneBoundary(LaneBoundaryIdBase const& id, LaneBoundaryContainerType& boundaies) = 0;

    class ObjectIdBase
    {
    public: 
        ObjectIdBase() = default;
        virtual ~ObjectIdBase() = default;
    };
    virtual holo::bool_t AdaptObjectInfo(ObjectIdBase const& id, ObjectInfoContainerType& objects) = 0;
}; ///< End of class AdapterBase

/**
 * @}
 *
 */
} ///< namespace adapter
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_ADAPTER_BASE_ADAPTER_BASE_H_ */
