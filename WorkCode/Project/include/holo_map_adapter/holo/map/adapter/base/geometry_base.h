/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geometry_base.h
 * @brief geometry_base.h
 * @author wanghaiyang@holomatic.com
 * @date "2021-01-14"
 */

#ifndef HOLO_MAP_ADAPTER_BASE_GEOMETRY_BASE_H_
#define HOLO_MAP_ADAPTER_BASE_GEOMETRY_BASE_H_

#include <holo/map/adapter/common/structs.h>
#include <holo/map/common/common_type_define.h>

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

class GeometryBase
{
public:
    GeometryBase() = default;
    virtual ~GeometryBase() = default;

    holo::bool_t GetDeBiasFlag() const noexcept
    {
        return this->debias_;
    }

    void SetDeBiasFlag(holo::bool_t const flag) noexcept
    {
        this->debias_ = flag;
    }

    holo::float64_t GetXOffset() const noexcept
    {
        return this->x_offset_;
    }

    void SetXOffset(holo::float64_t const x) noexcept
    {
        this->x_offset_ = x;
    }

    holo::float64_t GetYOffset() const noexcept
    {
        return this->y_offset_;
    }

    void SetYOffset(holo::float64_t const y) noexcept
    {
        this->y_offset_ = y;
    }

    holo::bool_t GetZZeroFlag() const noexcept
    {
        return this->z_zero_flag_;
    }

    void SetZZeroFlag(holo::bool_t const z) noexcept
    {
        this->z_zero_flag_ = z;
    }

    holo::uint8_t GetUtmZoneId() const noexcept
    {
        return this->utm_zone_id_;
    }

    void SetUtmZoneId(holo::uint8_t const id) noexcept
    {
        this->utm_zone_id_ = id;
    }

    holo::bool_t GetUtmSouthFlag() const noexcept
    {
        return this->utm_south_flag_;
    }

    void SetUtmSouthFlag(holo::bool_t const flag) noexcept
    {
        this->utm_south_flag_ = flag;
    }

    holo::bool_t GetWGS84Flag() const noexcept
    {
        return this->wgs_84_;
    }

    void SetWGS84Flag(holo::bool_t const flag) noexcept
    {
        this->wgs_84_ = flag;
    }

    holo::bool_t IsWithWGS84() const
    {
        return this->wgs_84_;
    }

    holo::bool_t IsAcrossZone() const
    {
        return 0 == this->utm_zone_id_;
    }

    holo::bool_t IsHasOffset() const
    {
        return this->GetDeBiasFlag() || std::fabs(this->GetXOffset()) > 0.000001 ||
               std::fabs(this->GetYOffset()) > 0.000001;
    }

    static holo::uint8_t const CoordinateReferenceSystemInvalidUtmZoneId = 0;

    static holo::bool_t CalculateUTMZoneWithWGS84(GeoPointType const& point,
        CoordinateType& coord);

    static holo::bool_t CalculateUTMZoneWithWGS84(GeoPointVectorType const& point,
        CoordinateVectorType& coords);

    static void ConvertGeoPointToLLWithWGS84(GeoPointType const& point, LLType& ll);

    static void ConvertGeoPointToLLWithWGS84(GeoPointVectorType const& points, LLVectorType& lls);

    static void ConvertGeoBoxToLLWithWGS84(GeoBoxType const& points, LLVectorType& lls);

    static void ConvertGeoBox4ToLLWithWGS84(GeoBox4Type const& points, LLVectorType& lls);
protected:
    holo::bool_t    debias_         = false;
    holo::float64_t x_offset_       = 0.0;
    holo::float64_t y_offset_       = 0.0;
    holo::bool_t    z_zero_flag_    = true;
    holo::uint8_t   utm_zone_id_    = 0;
    holo::bool_t    utm_south_flag_ = false;
    holo::bool_t    wgs_84_         = false;
    holo::bool_t    verbose_        = true;
}; ///< End of class GeometryBase

/**
 * @}
 *
 */
} ///< namespace adapter
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_ADAPTER_BASE_GEOMETRY_BASE_H_ */
