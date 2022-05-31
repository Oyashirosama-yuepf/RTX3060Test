/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file preprocess.hpp
 * @brief Preprocessing functions for holo::map::format::***
 * @author wanghaiyang@holomatic.com
 * @date "2021-05-20"
 */

#ifndef HOLO_MAP_COMMON_DETAILS_PREPROCESS_HPP_
#define HOLO_MAP_COMMON_DETAILS_PREPROCESS_HPP_

#include <type_traits>

#include <holo/log/hololog.h>

#include <holo/map/common/types.h>
#include <holo/map/format/base/base.h>
#include <holo/map/format/base/intersection.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/format/base/lane_group.h>
#include <holo/map/format/base/lane_boundary.h>
#include <holo/map/format/base/object_info.h>
#include <holo/map/format/base/object_linear_info.h>
#include <holo/map/format/base/object_pedestrian_crossing.h>
#include <holo/map/format/base/object_regional_info.h>
#include <holo/map/format/base/object_stop_line.h>
#include <holo/map/format/base/object_traffic_light.h>
#include <holo/map/format/base/object_traffic_light_group.h>
#include <holo/map/format/base/object_traffic_sign.h>
#include <holo/map/format/base/road.h>
#include <holo/map/format/hfl/quasi_dynamic_lane.h>
#include <holo/map/format/hfl/quasi_dynamic_lane_group.h>
#include <holo/map/format/hfl/quasi_dynamic_region.h>
#include <holo/map/format/parking/object_parking_background.h>
#include <holo/map/format/parking/object_parking_floor.h>
#include <holo/map/format/parking/object_parking_lot.h>
#include <holo/map/format/parking/object_parking_poi.h>
#include <holo/map/format/parking/object_parking_space.h>
#include <holo/utils/geographical_transformation.h>

namespace holo
{
namespace map
{
namespace format
{
namespace geometry
{
/**
 * @addtogroup geometry
 * @{
 *
 */

/**
 * @brief Convert coordinate from WGS84 to UTM with no exception.
 *
 * @param[in] lon Longitude.
 * @param[in] lat Latitude.
 * @param[in] zone_id Zone id.
 * @param[in] south_flag If in south earth is true, otherwise is false.
 * @param[out] easting Easting of UTM.
 * @param[out] easting Northing of UTM.
 *
 * @return true: No error;
 *         false: An error occurs in this function, please see logs for more details.
 */
holo::bool_t LonLatToUtmWithNoException(holo::float64_t const lon, holo::float64_t const lat,
                                        holo::uint8_t const zone_id, holo::bool_t const south_flag,
                                        holo::float64_t& easting, holo::float64_t& northing);

/**
 * @brief Convert coordinate from UTM to WGS84 with no exception.
 *
 * @param[in] zone_id Zone id.
 * @param[in] south_flag If in south earth is true, otherwise is false.
 * @param[in] easting Easting of UTM.
 * @param[in] easting Northing of UTM.
 * @param[out] lon Longitude.
 * @param[out] lat Latitude.
 *
 * @return true: No error;
 *         false: An error occurs in this function, please see logs for more details.
 */
holo::bool_t UtmToLonLatWithNoException(holo::uint8_t const zone_id, holo::bool_t const south_flag,
                                        holo::float64_t const easting, holo::float64_t const northing,
                                        holo::float64_t& lon, holo::float64_t& lat);

/**
 * @brief Get zone id by coordinate of WGS84 with no exception.
 *
 * @param[in] lon Longitude.
 * @param[in] lat Latitude.
 *
 * @return zone id.
 */
holo::uint8_t LonLatGetUtmZoneIdWithNoException(holo::float64_t const lon, holo::float64_t const lat);

/**
 * @brief Convert from holo::commmon::coordinate type to holo::map::format::coordinate type.
 *
 * @param[in] type A holo::commmon::coordinate type
 * @return A holo::map::format::coordinate type.
 */
holo::map::format::Coordinate::CoordinateType CovertCoordinateType(holo::common::Coordinate::Type const type);

/**
 * @brief Convert from holo::map::format::coordinate type to holo::commmon::coordinate type.
 *
 * @param[in] type A holo::map::format::coordinate type.
 * @return A holo::commmon::coordinate type.
 */
holo::common::Coordinate::Type CovertCoordinateType(holo::map::format::Coordinate::CoordinateType const type);

template <typename T>
holo::bool_t IsValidGCSPoint(T const& p)
{
    holo::float64_t const lon = p.GetX();
    holo::float64_t const lat = p.GetY();
    if (std::isnan(lon) || std::isnan(lat))
    {
        return false;
    }
    return (lon >= -180.0) && (lon < 180.0) && (lat >= -85.06) && (lat <= 85.06);
}

template <typename T>
struct IsFeatureWithLinearGeoPointInternal : public std::false_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::Road> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::Lane> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::LaneGroup> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::LaneBoundary> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::ObjectInfo> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::ObjectLinearInfo> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::ObjectParkingLot> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::ObjectParkingFloor> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::ObjectParkingBackground> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::ObjectParkingPoi> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::ObjectParkingSpace> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::QuasiDynamicLane> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::QuasiDynamicLaneGroup> : public std::true_type {};
template<>
struct IsFeatureWithLinearGeoPointInternal<holo::map::format::QuasiDynamicRegion> : public std::true_type {};
template <typename T>
struct IsFeatureWithLinearGeoPoint : public IsFeatureWithLinearGeoPointInternal<typename std::remove_cv<T>> {};

template <typename T>
struct IsFeatureWithGeoBoxPointInternal : public std::false_type {};
template<>
struct IsFeatureWithGeoBoxPointInternal<holo::map::format::ObjectTrafficLight> : public std::true_type {};
template <typename T>
struct IsFeatureWithGeoBox : public IsFeatureWithGeoBoxPointInternal<typename std::remove_cv<T>> {};

template <typename T>
struct IsFeatureWithGeoBox4PointInternal : public std::false_type {};
template<>
struct IsFeatureWithGeoBox4PointInternal<holo::map::format::ObjectRegionalInfo> : public std::true_type {};
template<>
struct IsFeatureWithGeoBox4PointInternal<holo::map::format::ObjectPedestrianCrossing> : public std::true_type {};
template<>
struct IsFeatureWithGeoBox4PointInternal<holo::map::format::ObjectTrafficSign> : public std::true_type {};
template <typename T>
struct IsFeatureWithGeoBox4 : public IsFeatureWithGeoBox4PointInternal<typename std::remove_cv<T>> {};

template <typename T>
struct IsFeatureWithPolygonGeoPointInternal : public std::false_type {};
template<>
struct IsFeatureWithPolygonGeoPointInternal<holo::map::format::Intersection> : public std::true_type {};

template <typename T>
struct IsSameGeoPointTypeInternal: public std::false_type {};
template<>
struct IsSameGeoPointTypeInternal<holo::map::format::GeoPoint> : public std::true_type {};
template<typename T>
struct IsSameGeoPointType : public IsSameGeoPointTypeInternal<typename std::remove_cv<T>::type> {};

template <typename T>
struct IsSameGeoBoxTypeInternal: public std::false_type {};
template<>
struct IsSameGeoBoxTypeInternal<holo::map::format::GeoBox> : public std::true_type {};
template<typename T>
struct IsSameGeoBoxType : public IsSameGeoBoxTypeInternal<typename std::remove_cv<T>::type> {};

using CoordinateType = holo::common::Coordinate;

template <typename T>
using GeographicParameterType = GeographicParameter<T, CoordinateType>;

template <typename T>
using GeographicParameterRefType = GeographicParameter<T&, CoordinateType&>;

template <typename T>
using GeographicParameterCRefType = GeographicParameter<T const&, CoordinateType const&>;

template <typename T>
using GeographicParameterVectorType = GeographicParameter<std::vector<T>, CoordinateType>;

template <typename T>
using GeographicParameterVectorRefType = GeographicParameter<std::vector<T>&, CoordinateType&>;

template <typename T>
using GeographicParameterVectorCRefType = GeographicParameter<std::vector<T> const&, CoordinateType const&>;

template <typename T, typename = typename std::enable_if<IsSameGeoBoxType<T>::value>::type>
holo::bool_t ConvertWGS84ToUTM(GeographicParameterType<T> const& in, GeographicParameterType<T>& out)
{
    holo::float64_t min_x = 0.0;
    holo::float64_t min_y = 0.0;
    holo::float64_t max_x = 0.0;
    holo::float64_t max_y = 0.0;

    holo::bool_t ok = true;
    ok = ok && LonLatToUtmWithNoException(in.parameter.GetLeftBackBottom().GetX(), in.parameter.GetLeftBackBottom().GetY(),
                    in.coordinate.GetUtmZoneId(), in.coordinate.GetUtmSouthFlag(), min_x, min_y);
    ok = ok && LonLatToUtmWithNoException(in.parameter.GetRightForwardTop().GetX(), in.parameter.GetRightForwardTop().GetY(),
                    in.coordinate.GetUtmZoneId(), in.coordinate.GetUtmSouthFlag(), max_x, max_y);
    if (!ok)
    {
        LOG(ERROR) << "ConvertWGS84ToUTM fail, LonLatToUtmWithNoException fail";
        return false;
    }

    holo::map::format::GeoPoint const left_bottom(in.parameter.GetLeftBackBottom().GetHeightCm(), min_x, min_y);
    holo::map::format::GeoPoint const right_top(in.parameter.GetRightForwardTop().GetHeightCm(), max_x, max_y);

    out.parameter.SetLeftBackBottom(left_bottom);
    out.parameter.SetRightForwardTop(right_top);
    return true;
}

template <typename T>
holo::bool_t ConvertToUTM(GeographicParameterType<T> const& in, GeographicParameterType<T>& out)
{
    typename GeographicParameterType<T>::CoordinateType const& c = in.coordinate;

    if (GeographicParameterType<T>::CoordinateType::Type::UTM6 == c.GetType() 
        ||
        GeographicParameterType<T>::CoordinateType::Type::UTM3 == c.GetType())
    {
        out = in;
        return true;
    }

    if (GeographicParameterType<T>::CoordinateType::Type::WGS84 == c.GetType())
    {
        holo::uint8_t const zone_id = LonLatGetUtmZoneIdWithNoException(in.parameter.GetX(), in.parameter.GetY());
        if (255 == zone_id)
        {
            LOG(ERROR) << "ConvertToUTM fail, LonLatGetUtmZoneIdWithNoException fail";
            return false;
        }

        holo::bool_t const south_flag = in.parameter.GetY() >= 0.0 ? false : true;

        holo::float64_t x = 0.0;
        holo::float64_t y = 0.0;
        if (!LonLatToUtmWithNoException(in.parameter.GetX(), in.parameter.GetY(), zone_id, south_flag, x, y))
        {
            LOG(ERROR) << "ConvertToUTM fail, LonLatToUtmWithNoException fail";
            return false;
        }

        out.coordinate.SetType(GeographicParameterType<T>::CoordinateType::Type::UTM6);
        out.coordinate.SetUtmZoneId(zone_id);
        out.coordinate.SetUtmSouthFlag(south_flag);

        out.parameter.SetX(x);
        out.parameter.SetY(y);
    }
    else
    {
        LOG(ERROR) << "ConvertToUTM fail, invalid parameter, type=" << static_cast<int>(c.GetType());
        return false;
    }
    return true;
}

template <typename T, typename C>
holo::bool_t ConvertToUTMV2(GeographicParameterType<T> const& in, C const& c, GeographicParameterType<T>& out)
{
    if (c.GetType() != C::Type::UTM6)
    {
        LOG(ERROR) << "ConvertToUTMV2 fail, invalid parameter, type=" << static_cast<int>(c.GetType());
        return false;
    }

    if (in.coordinate.GetType()         == c.GetType()      && 
        in.coordinate.GetUtmZoneId()    == c.GetUtmZoneId() &&
        in.coordinate.GetUtmSouthFlag() == c.GetUtmSouthFlag())
    {
        out = in;
        return true;
    }

    holo::float64_t lon = 0.0;
    holo::float64_t lat = 0.0;

    if (in.coordinate.GetType() == C::Type::WGS84)
    {
        lon = in.parameter.GetX();
        lat = in.parameter.GetY();
    }
    else
    {
        if (in.coordinate.GetType() != C::Type::UTM6)
        {
            LOG(ERROR) << "ConvertToUTMV2 fail, invalid paramter, type=" 
                       << static_cast<int>(in.coordinate.GetType());
            return false;
        }

        if (!UtmToLonLatWithNoException(in.coordinate.GetUtmZoneId(), in.coordinate.GetUtmSouthFlag(),
                                       in.parameter.GetX(), in.parameter.GetY(), lon, lat))
        {
            LOG(ERROR) << "ConvertToUTMV2 fail, UtmToLonLatWithNoException fail";
            return false;
        }
    }

    holo::float64_t x = 0.0;
    holo::float64_t y = 0.0;
    if (!LonLatToUtmWithNoException(lon, lat, c.GetUtmZoneId(), c.GetUtmSouthFlag(), x, y))
    {
        LOG(ERROR) << "ConvertToUTMV2 fail, LonLatToUtmWithNoException fail";
        return false;
    }
        
    out.parameter.SetX(x);
    out.parameter.SetY(y);
    out.coordinate = c;

    return true;
}

template <typename T>
holo::bool_t ConvertToWGS84(GeographicParameterType<T> const& in, GeographicParameterType<T>& out)
{
    typename GeographicParameterType<T>::CoordinateType const& c = in.coordinate;
    if (GeographicParameterType<T>::CoordinateType::Type::WGS84 == c.GetType())
    {
        out = in;
        return true;
    }

    if (GeographicParameterType<T>::CoordinateType::Type::UTM6 == c.GetType())
    {
        holo::uint8_t const zone_id = in.coordinate.GetUtmZoneId();
        if (0 == zone_id || zone_id > 60)
        {
            LOG(ERROR) << "ConvertToWGS84 fail, invalid zone id, zone_id=" << static_cast<int>(zone_id);
            return false;
        }

        holo::bool_t const south_flag = in.coordinate.GetUtmSouthFlag();

        holo::float64_t x = 0.0;
        holo::float64_t y = 0.0;
        if (!UtmToLonLatWithNoException(zone_id, south_flag, in.parameter.GetX(), in.parameter.GetY(), x, y))
        {
            LOG(ERROR) << "ConvertToWGS84 fail, UtmToLonLatWithNoException fail";
            return false;
        }

        out.coordinate.SetType(GeographicParameterType<T>::CoordinateType::Type::WGS84);

        out.parameter.SetX(x);
        out.parameter.SetY(y);
    }
    else
    {
        LOG(ERROR) << "ConvertToWGS84 fail, invalid parameter, type=" << static_cast<int>(c.GetType());
        return false;
    }
    return true;
}

template <typename T, typename = typename std::enable_if<IsSameGeoPointType<T>::value>::type>
holo::bool_t CalculateBoundingBox2D(std::vector<T> const& ts, holo::map::format::GeoBox& box)
{
    T left_bottom(0.0, std::numeric_limits<holo::float64_t>::max(),
        std::numeric_limits<holo::float64_t>::max());
    T right_top(0.0, std::numeric_limits<holo::float64_t>::min(),
        std::numeric_limits<holo::float64_t>::min());

    box.SetLeftBackBottom(left_bottom);
    box.SetRightForwardTop(right_top);
    
    if (ts.empty())
    {
        LOG(ERROR) << "CalculateBoundingBox2D fail, invalid parameters";
        return false;
    }

    for (T const& p : ts)
    {
        left_bottom.SetX((p.GetX() < left_bottom.GetX() ? p.GetX() : left_bottom.GetX()));
        left_bottom.SetY((p.GetY() < left_bottom.GetY() ? p.GetY() : left_bottom.GetY()));
        right_top.SetX((p.GetX() > right_top.GetX() ? p.GetX() : right_top.GetX()));
        right_top.SetY((p.GetY() > right_top.GetY() ? p.GetY() : right_top.GetY()));
    }

    box.SetLeftBackBottom(left_bottom);
    box.SetRightForwardTop(right_top);
    return true;
}

template <typename T, typename B>
holo::bool_t CalculateBoundingBox2DInner(T& t, B& b);

template <typename T>
holo::bool_t CalculateBoundingBox2DInner(T& t, holo::map::format::GeoBox& box);

template <typename T, typename std::enable_if<IsFeatureWithLinearGeoPointInternal<
    typename holo::map::format::helper::FeatureTraits<T>::RawType>::value, holo::bool_t>::type = true>
holo::bool_t CalculateBoundingBox2DInner(typename holo::map::format::helper::FeatureTraits<T>::SPtrType& ptr,
                                         holo::map::format::GeoBox& box)
{
    if (nullptr == ptr)
    {
        LOG(ERROR) << "CalculateBoundingBox2DInner fail, invalid parameters";
        return false;
    }

    std::vector<holo::map::format::GeoPoint> const& points = *ptr->GetPtrGeometryPoints();

    holo::bool_t const ok = CalculateBoundingBox2D(points, box);
    if (!ok)
    {
        LOG(ERROR) << "CalculateBoundingBox2DInner fail, CalculateBoundingBox2D fail, points_size=" << points.size();
    }
    return ok;
}

template <typename T, typename std::enable_if<IsFeatureWithPolygonGeoPointInternal<
    typename holo::map::format::helper::FeatureTraits<T>::RawType>::value, holo::bool_t>::type = true>
holo::bool_t CalculateBoundingBox2DInner(typename holo::map::format::helper::FeatureTraits<T>::SPtrType& ptr,
                                         holo::map::format::GeoBox& box)
{
    if (nullptr == ptr)
    {
        LOG(ERROR) << "CalculateBoundingBox2DInner fail, invalid parameters";
        return false;
    }

    holo::map::format::GeoPolygon const& polygon = ptr->GetGeometryPoints();
    std::vector<holo::map::format::GeoPoint> const& points = *polygon.GetPtrVertices();

    holo::bool_t const ok = CalculateBoundingBox2D(points, box);
    if (!ok)
    {
        LOG(ERROR) << "CalculateBoundingBox2DInner fail, CalculateBoundingBox2D fail, points_size=" << points.size();
    }
    return ok;
}

template <typename T, typename std::enable_if<IsFeatureWithGeoBoxPointInternal<
    typename holo::map::format::helper::FeatureTraits<T>::RawType>::value, holo::bool_t>::type = true>
holo::bool_t CalculateBoundingBox2DInner(typename holo::map::format::helper::FeatureTraits<T>::SPtrType& ptr,
                                         holo::map::format::GeoBox& box)
{
    if (nullptr == ptr)
    {
        LOG(ERROR) << "CalculateBoundingBox2DInner fail, invalid paramters";
        return false;
    }
    
    box = ptr->GetGeometry();
    return true;
}

template <typename T, typename std::enable_if<IsFeatureWithGeoBox4PointInternal<
    typename holo::map::format::helper::FeatureTraits<T>::RawType>::value, holo::bool_t>::type = true>
holo::bool_t CalculateBoundingBox2DInner(typename holo::map::format::helper::FeatureTraits<T>::SPtrType& ptr,
                                         holo::map::format::GeoBox& box)
{
    if (nullptr == ptr)
    {
        LOG(ERROR) << "CalculateBoundingBox2DInner fail, invalid paramters";
        return false;
    }

    if (!CalculateBoundingBox2D<holo::map::format::GeoBox4>(ptr->GetGeometry(), box))
    {
        LOG(ERROR) << "CalculateBoundingBox2DInner fail, CalculateBoundingBox2D fail";
        return false;
    }
    return true;
}

template <typename T>
holo::bool_t CalculateBoundingBox2DInnerFromBase(holo::map::format::helper::FeatureBaseSPtrType& base, 
    holo::map::format::GeoBox& box)
{
    typename holo::map::format::helper::FeatureTraits<T>::SPtrType feature = 
        std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(base);
    if (nullptr == feature)
    {
        LOG(ERROR) << "CalculateBoundingBox2DInnerFromBase fail, invalid pointer";
        return false;
    }

    holo::bool_t const ok = CalculateBoundingBox2DInner<T>(feature, box);
    if (!ok)
    {
        LOG(ERROR) << "CalculateBoundingBox2DInnerFromBase fail, CalculateBoundingBox2DInner fail";
        return false;
    }
    return ok;
}

template <typename T>
holo::bool_t CalculateBoundingBox2D(typename holo::map::format::helper::FeatureTraits<T>::SPtrType& feature,
    holo::map::format::GeoBox& box)
{
    return CalculateBoundingBox2DInner<T>(feature, box);
}

template <typename B, typename = typename std::enable_if<IsSameGeoBoxType<B>::value>::type>
holo::bool_t AreBoundingBoxesOverlapped2DInner(B const& box1, B const& box2)
{
    return !(box1.GetLeftBackBottom().GetX() > box2.GetRightForwardTop().GetX() ||
             box1.GetRightForwardTop().GetX() < box2.GetLeftBackBottom().GetX() ||
             box1.GetLeftBackBottom().GetY() > box2.GetRightForwardTop().GetY() ||
             box1.GetRightForwardTop().GetY() < box2.GetLeftBackBottom().GetY());
}

template <typename B>
holo::bool_t AreBoundingBoxesOverlapped2D(B const& box1, B const& box2)
{
    return AreBoundingBoxesOverlapped2DInner<B>(box1, box2);
}

/**
 * @}
 *
 */
} ///< namespace geometry
} ///< namespace format
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_COMMON_DETAILS_PREPROCESS_HPP_ */
