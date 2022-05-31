/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geographical_transformation.h
 * @brief Conversion between lon/lat and utm.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-4-3
 */

#ifndef HOLO_UTILS_INTERNAL_GEOGRAPHICAL_TRANSFORMATION_H_
#define HOLO_UTILS_INTERNAL_GEOGRAPHICAL_TRANSFORMATION_H_

#include <holo/core/exception.h>
#include <holo/core/types.h>

namespace holo
{
namespace exception
{
class BadGeographicalTransformationException : public std::exception
{
};
}  // namespace exception

namespace utils
{
/**
 * @brief longitude/latitude to utm easting/northing in utm zone(zone_id, south_flag)
 *
 * @param[in] lon longitude
 * @param[in] lat latitude
 * @param[in] zone_id utm zone id
 * @param[in] south_flag utm south flag
 * @param[out] easting utm coordinate easting
 * @param[out] northing utm coordinate northing
 */
void LonLatToUtm(float64_t lon, float64_t lat, uint8_t zone_id, bool_t south_flag, float64_t& easting,
                 float64_t& northing);

/**
 * @brief utm easting/northing to longitude/latitude.
 *
 * @param[in] zone_id utm zone id
 * @param[in] south_flag utm south flag
 * @param[in] easting utm coordinate easting
 * @param[in] northing utm coordinate northing
 * @param[out] lon longitude
 * @param[out] lat latitude
 */
void UtmToLonLat(uint8_t zone_id, bool_t south_flag, float64_t easting, float64_t northing, float64_t& lon,
                 float64_t& lat);

/**
 * @brief Get utm zone id longitude/latitude lays in.
 *
 * @param[in] lon longitude
 * @param[in] lat latitude
 *
 * @return utm zone id
 */
uint8_t LonLatGetUtmZoneId(float64_t lon, float64_t lat);

/**
 * @brief Get utm zone longitude/latitude lays in.
 * @details UTM zone is consist of two parts: zone_id and south_flag.
 * @f[
 * \begin{bytefield}{8}
 *   \bitheader{0-7} \\
 *   \bitbox{1}{S} & \bitbox{7}{zone\_id}
 * \end{bytefield}
 * @f]
 *
 * @param[in] lon longitude
 * @param[in] lat latitude
 *
 * @return utm zone.
 */
uint8_t LonLatGetUtmZone(float64_t lon, float64_t lat);

/**
 * @brief Calculate distance between a utm zone and a lon/lat point
 * @details This algorithm assumes the earth is a sphere of radius 6378137m.
 * - If lon lays inside the utm zone_id, distance is 0.
 * - If lon is closer to west meridian of utm zone_id, return distance between lon/lat and west meridian.
 * - If lon is closer to east meridian of utm zone_id, return distance between lon/lat and east meridian.
 *
 * The distance between a lon/lat point and a meridian line is calculated as following:
 * - @f$\lambda@f$ denotes longitude. 
 * - @f$\varphi@f$ denotes latitude. 
 * - @f$O@f$ denotes center of sphere.
 * - @f$\lambda_0@f$ denotes longitude of meridian.
 * - @f$P=(\lambda_1,\varphi_1)@f$ denotes the lon/lat point.
 *
 * The distance between meridian and lon/lat point is the lengh of a arc passing the lon/lat point and prependicular to
 * the meridian. @n
 * To get the arc. Mark point @f$P^{'}=(\lambda_2,\varphi_2)@f$ is the mirror of point @f$P@f$ through plane the meridian
 * lays in. @n
 * It is obviously Plane @f$(P, P^{'}, O)@f$ is prependicular to the meridian. @f$\varphi_1=\varphi_2@f$ and
 * @f$\lambda_1+\lambda_2=2\times \lambda_0@f$.So the lengh of arc @f$PP^{'}@f$ in great circle
 * @f$(P,P^{'},O)@f$ is twice of distance between @f$P@f$ and the meridian.
 *
 * Denote @f$\Delta\lambda=\lambda_2-\lambda_1@f$, @f$\varphi=\varphi_1=\varphi_2@f$. Chord length of @f$PP^{'}@f$ is
 * @f$d@f$. Earth radius is @f$R@f$
 *
 * @f{align*}{
 *   d^2 &= {(R \cos(\varphi) \sin(\Delta\lambda))}^2 + {(R \cos(\varphi)(1- \cos(\Delta\lambda)))}^2 \\
 *   d^2 &= {(R \sin(\angle{POP^{'}}))}^2 + {(R (1- \cos(\angle{POP^{'}})))}^2 \\
 *   \angle{POP^{'}} &= \arccos(1-{\cos}^2(\varphi)(1-\cos(\Delta\lambda))) \\
 *   Distance &= \frac{\angle{POP^{'}}}{2 \pi \times 2} R
 * @f}
 *
 * @param lon Longitude
 * @param lat Latitude
 * @param zone_id utm zone id.
 *
 * @return distance between zone id and lon/lat point.
 */
float64_t LonLatGetDistanceToZoneId(float64_t lon, float64_t lat, uint8_t zone_id);

}  // namespace utils
}  // namespace holo

#endif
