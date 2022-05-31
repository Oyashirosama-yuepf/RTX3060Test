/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file engine.h
 * @brief engine.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-09"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_ENGINE_H_
#define HOLO_MAP_SERVICE_CLIENT_ENGINE_H_

#include <holo/common/odometry.h>
#include <holo/map/service/client/engine/retriever.h>
#include <holo/map/service/io/reader.h>
#include <holo/map/service/io/writer.h>
#include <holo/map/service/session/utility.h>

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

class MapEngine
{
public:
    enum class MapEngineType : uint8_t
    {
        UNKNOWN = 0,
        HOLONDS = 1,
        BAIDUEHP = 2
    };

    enum class BackgroundType : uint8_t
    {
        UNKNOWN                = 0,
        REGION_ACTIVE          = 1,
        RESERVE_1              = 2,
        RESERVE_2              = 3,
        ROUTING_ACTIVE         = 4,
        RESERVE_4              = 5,
        RESERVE_5              = 6,
        RESERVE_6              = 7,
        EHP_PASSTIVE           = 8,
        MIXED_REGION_ROUTING   = 9,
    };

public:
    /// Redefine odometry type for inner members.
    using OdometryType      = holo::common::Odometryd;
    /// Redefine coordinate reference system type.
    using CoordinateType    = OdometryType::CoordinateType;

    using DistanceType = holo::float64_t;
    using DistanceCMType = holo::int32_t;

    using ProfileIdType = holo::map::service::client::profile::ProfileIdType;

    using ReaderType = holo::map::service::io::ReaderBase;
    using WriterType = holo::map::service::io::WriterBase;

    using RetrieverType = holo::map::service::client::engine::Retriever;
    using RetrieverSPtrType = std::shared_ptr<RetrieverType>;

    using TokenType = holo::uint64_t;

    /// Redefine pattern type for update db from LMS.
    using PatternType = holo::map::service::session::SessionType::PatternType;

    MapEngine();
    virtual ~MapEngine();

    MapEngine(MapEngine const&) = delete;
    MapEngine(MapEngine&&) = delete;

    MapEngine& operator = (MapEngine const&) = delete;
    MapEngine& operator = (MapEngine&&) = delete;

    void RegistReader(ReaderType* r);
    void RegistWriter(WriterType* w);

    MapEngineType GetEngineType() const noexcept;
    void SetEngineType(MapEngineType type);

    holo::bool_t GetVerbose() const noexcept;
    void SetVerbose(holo::bool_t const v) noexcept;

    /// Note: When background for pattern routing is split ok, delete pattern_type_ and these interface.
    PatternType GetPatternType() const noexcept;
    void SetPatternType(PatternType const t) noexcept;

    BackgroundType GetBackgroundType() const noexcept;

    /**
     * @brief Set the background type. If not set background type, it default value is unknow.
     *        We choose background type by pattern type.
     * 
     * @param[in] t Background type: (default: UNKNOWN).
     */
    void SetBackgroundType(BackgroundType const t) noexcept;

    void SetTokenId(TokenType const token);

    /**
     * @brief Update cache range, the range value more larger, the cache more larger.
     * 
     * @param[in] range Option: 1, 2, 3, 4, 5(default: 2).
     */
    void SetCacheRange(holo::uint32_t const r) noexcept;

    MapErrorCode Init();

    RetrieverSPtrType GetRetriever() const;

    /**
     * @brief Update current location for upgating surrounding map features.
     *
     * @note This function is thread safe, and the execute frequency must not be 
     *       less than 3HZ.
     * @param[in] odo Current position with valid point and coordiante.
     */
    void Update(OdometryType const& odo);

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

    MapErrorCode Run();

    void Stop();

    holo::bool_t HasStopped() const;
private:
    class MapEngineInner;
    std::unique_ptr<MapEngineInner> inner_;
};

} ///< namespace engine
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_ENGINE_H_ */
