/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file feature_geometry_engine.h
 * @brief Data engine for obtaining map geometry data
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2022-4-21"
 */

#ifndef HOLO_MAP_NAVIGATOR_ADAPTION_DATA_ENGINE_FEATURE_GEOMETRY_HELPER_H_
#define HOLO_MAP_NAVIGATOR_ADAPTION_DATA_ENGINE_FEATURE_GEOMETRY_HELPER_H_

#include <memory>
#include <vector>

#include <type_traits>

#include <holo/map/adaptation/data_engine/data_engine.h>
#include <holo/map/format/common/coordinate.h>
#include <holo/map/service/client/engine/helper.h>
#include <holo/map/format/base/base.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace feature
{
namespace odometry
{
/**
 * @brief Traits feature types from holo::map::format::xxx.
 */
template <class T>
struct FeatureTraits
{
    using RawType   = T;                         ///< Define self type for T.
    using PtrType   = T*;                        ///< Define pointer type for T.
    using SPtrType  = std::shared_ptr<T>;        ///< Define shared smart pointer type for T.
    using CSPtrType = std::shared_ptr<T const>;  ///< Define shared smart pointer type for const T.
    using UPtrType  = std::unique_ptr<T>;        ///< Define unique smart pointer type for T.
    using CUPtrType = std::unique_ptr<T const>;  ///< Define unique smart pointer type for const T.
};                                               ///< End of struct FeatureTraits

/**
 * @brief Traits feature types from holo::map::format::xxx*;
 */
template <class T>
struct FeatureTraits<T*>
{
    using RawType   = T;                         ///< Define self type for T.
    using PtrType   = T*;                        ///< Define pointer type for T.
    using SPtrType  = std::shared_ptr<T>;        ///< Define shared smart pointer type for T.
    using CSPtrType = std::shared_ptr<T const>;  ///< Define shared smart pointer type for const T.
    using UPtrType  = std::unique_ptr<T>;        ///< Define unique smart pointer type for T.
    using CUPtrType = std::unique_ptr<T const>;  ///< Define unique smart pointer type for const T.
};                                               ///< End of struct FeatureTraits

/**
 * @brief Traits feature types from holo::map::format::Ptrxxx*;
 */
template <class T>
struct FeatureTraits<std::shared_ptr<T>>
{
    using RawType   = T;                         ///< Define self type for T.
    using PtrType   = T*;                        ///< Define pointer type for T.
    using SPtrType  = std::shared_ptr<T>;        ///< Define shared smart pointer type for T.
    using CSPtrType = std::shared_ptr<T const>;  ///< Define shared smart pointer type for const T.
    using UPtrType  = std::unique_ptr<T>;        ///< Define unique smart pointer type for T.
    using CUPtrType = std::unique_ptr<T const>;  ///< Define unique smart pointer type for const T.
};                                               ///< End of struct FeatureTraits

class FeatureGeometryHelper
{
public:
    using GeoPointType   = holo::map::format::GeoPoint;
    using CoordinateType = holo::map::format::Coordinate;
    using GeographicParameterType =
        holo::map::service::client::engine::helper::raw::RawGeographicParameterTypeV0<RawGeoPointTypeV0>;
    using GeoPointVecType    = std::vector<GeoPointType>;

    template <typename FeatureT>
    static holo::bool_t GetGeometryWithUtm6(typename FeatureTraits<FeatureT>::SPtrType feature,
                                            holo::common::Coordinate const&            target_coord,
                                            std::vector<holo::map::format::GeoPoint>&  utm_geo_pts);
};

template <typename FeatureT>
holo::bool_t FeatureGeometryHelper::GetGeometryWithUtm6(typename FeatureTraits<FeatureT>::SPtrType feature,
                                                        holo::common::Coordinate const&            target_coord,
                                                        std::vector<holo::map::format::GeoPoint>&  utm_geo_pts)
{
    utm_geo_pts.clear();
    if (nullptr == feature)
    {
        LOG(ERROR) << "GetUTMGeometryPoints fails, invalid parameters";
        return false;
    }
    holo::map::format::Coordinate const& coordiante = feature->GetCoordinate();
    if (coordiante.GetCoordinateType() == CoordinateType::CoordinateType::COORDINATE_TYPE_WGS84)
    {
        std::vector<GeoPointType> const&     geopoints  = *feature->GetPtrGeometryPoints();
        std::size_t const                    size_pts   = geopoints.size();
        for (std::size_t i = 0U; i < size_pts; ++i)
        {
            GeographicParameterType geo_pt;
            geo_pt.parameter  = geopoints[i];
            geo_pt.coordinate = holo::common::Coordinate::Wgs84Coordinate();

            GeographicParameterType utm6_pt;
            if (!holo::map::format::geometry::ConvertToUTMV2(geo_pt, target_coord, utm6_pt))
            {
                LOG(ERROR) << "getUTMGeometryPointsNeglectZone fails, ConvertToUTM fails";
                return false;
            }
            utm_geo_pts.push_back(utm6_pt.parameter);
        }
    }
    else if (coordiante.GetCoordinateType() == CoordinateType::CoordinateType::COORDINATE_TYPE_UTM6)
    {
        std::vector<GeoPointType> const& geopoints = *feature->GetPtrGeometryPoints();
        utm_geo_pts.insert(utm_geo_pts.end(), geopoints.begin(), geopoints.end());
    }
    else
    {
        LOG(ERROR) << "FeatureGeometryHelper::GetUTMGeometryPoints fails, ";
        return false;
    }

    return true;
}
}  // namespace odometry
}  // namespace feature
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_NAVIGATOR_ADAPTION_DATA_ENGINE_FEATURE_GEOMETRY_HELPER_H_ */
