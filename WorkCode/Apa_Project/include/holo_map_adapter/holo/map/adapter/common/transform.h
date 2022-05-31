/*!
*  \brief WHAT IS THIS FILE DOING
*  \author leo(jiangdianqin@holomaitc.com)
*  \date 2018-06-14
*  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
*  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
*/
#ifndef HOLO_MAPEDITOR_COMMON_TRANSFORM_HEADER_H_
#define HOLO_MAPEDITOR_COMMON_TRANSFORM_HEADER_H_
#include "holo/map/common/common_type_define.h"
#include "holo/map/format/common/geo_point.h"
#include "holo/map/common/classes/latlon.h"
//#include "holo/mapeditor/common/common_types.h"
#include <holo/utils/geographical_transformation.h>
//2018/9/3 for matching the Navigation and positioning data minus X 0.5,minus Y 0.4
//2018/9/3 for matching the Navigation and positioning data minus X 0.3,minus Y -0.4
//2018/9/17 special for daizhen, no bias
//2018/9/25 for matching the Navigation and positioning data minus X 0.6,minus Y -0.3
// #define XMean 0.505136838912101
// #define YMean -0.212479456822014
#define XMean 0.6
#define YMean -0.3
namespace holo
{
namespace map
{
namespace transform
{

/**
 * @brief wgs to gcj
 * 
 * @param[in] wgsLat wgs 84 latitude
 * @param[in] wgsLng wgs 84 longitude
 * @param[out] gcjLat gcj latitude
 * @param[out] gcjLng gcj longitude 
 */
void wgs2gcj(double wgsLat, double wgsLng, double *gcjLat, double *gcjLng);
/**
 * @brief gcj to wgs
 * 
 * @param[in] gcjLat gcj latitude 
 * @param[in] gcjLng gcj longitude
 * @param[out] wgsLat wgs84 latitude
 * @param[out] wgsLng wgs84 longitude
 */
void gcj2wgs(double gcjLat, double gcjLng, double *wgsLat, double *wgsLng);
/**
 * @brief gcj to wgs exactly
 * 
 * @param[in] gcjLat gcj latitude
 * @param[in] gcjLng gcj longitude
 * @param[out] wgsLat wgs84 latitude
 * @param[out] wgsLng wgs84 longitude
 * @param[out] gp geopoint with xyzll
 */
void gcj2wgs_exact(double gcjLat, double gcjLng, double *wgsLat, double *wgsLng, ::holo::map::format::GeoPoint &gp);
/**
 * @brief distance between point A and point B
 * 
 * @param[in] latA point A latitude
 * @param[in] lngA point A longitude
 * @param[in] latB point B latitude
 * @param[in] lngB point B longitude
 * @return double distance between A and B
 */
double distance(double latA, double lngA, double latB, double lngB);
/**
 * @brief minus Mean in lat and lon
 * 
 * @param[in] ll ll
 * @param[in] gp geopoint with xyzll
 */
void minusMean(map::LL& ll, uint64_t zone_id, bool south_flag, map::format::GeoPoint& gp);
}  // namespace transform
} //namespace mapeditor
} //namespace holo
#endif //HOLO_MAPEDITOR_COMMON_TRANSFORM_HEADER_H_