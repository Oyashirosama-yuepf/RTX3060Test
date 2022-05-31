/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geographical_transformation.h
 * @brief Conversion between lat/lon and utm.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-4-3
 */

#ifndef HOLO_C_UTILS_GEOGRAPHICAL_TRANSFORMATION_H_
#define HOLO_C_UTILS_GEOGRAPHICAL_TRANSFORMATION_H_

#include <holo_c/common/coordinate.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2.h>
#include <holo_c/geometry/point3.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @addtogroup utils
 * @{
 */

/**
 * @brief utm easting/northing to longitude/latitude
 *
 * @param[in] zone_id utm zone id
 * @param[in] south_flag utm south flag
 * @param[in] easting utm coordinate easting
 * @param[in] northing utm coordinate northing
 * @param[out] lon longitude
 * @param[out] lat latitude
 *
 * @return RC_SUCCESS if conversion success otherwise RC_FAIL
 */
retcode_t utm_to_lonlat(uint8_t zone_id, bool_t south_flag, float64_t easting, float64_t northing, float64_t* lon,
                        float64_t* lat);

/**
 * @brief longitude/latitude to utm easting/northing in utm zone(zone_id, south_flag)
 *
 * @param[in] lon longitude
 * @param[in] lat latitude
 * @param[in] zone_id utm zone id
 * @param[in] south_flag utm south flag
 * @param[out] easting utm coordinate easting
 * @param[out] northing utm coordinate northing
 *
 * @return
 */
retcode_t lonlat_to_utm(float64_t lon, float64_t lat, uint8_t zone_id, bool_t south_flag, float64_t* easting,
                        float64_t* northing);

/**
 * @brief Get utm zone id longitude/latitude lays in.
 *
 * @param[in] lon longitude
 * @param[in] lat latitude
 *
 * @return utm zone id.
 */
uint8_t lonlat_get_utm_zone_id(float64_t lon, float64_t lat);

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
uint8_t lonlat_get_utm_zone(float64_t lon, float64_t lat);

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
 * To get the arc. Mark point @f$P^{'}=(\lambda_2,\varphi_2)@f$ is the mirror of point @f$P@f$ through plane the
 * meridian lays in. @n It is obviously Plane @f$(P, P^{'}, O)@f$ is prependicular to the meridian.
 * @f$\varphi_1=\varphi_2@f$ and
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
float64_t lonlat_get_distance_to_zone_id(float64_t lon, float64_t lat, uint8_t zone_id);

/**
 * @brief Convert lonlat point to utm point
 *
 * @param src_pt point to convert.
 * @param dst_coord target utm coordinate to convert to.
 * @param dst_pt The converted point.
 *
 * @return RC_SUCCESS if no error occurs
 */
retcode_t point2_convert_lonlat_to_utm(struct Point2d const* src_pt, Coordinate_t dst_coord, struct Point2d* dst_pt);

/**
 * @brief Convert lonlat point to utm point
 *
 * @param src_pt point to convert.
 * @param dst_coord target utm coordinate to convert to.
 * @param dst_pt The converted point.
 *
 * @return RC_SUCCESS if no error occurs
 */
retcode_t point3_convert_lonlat_to_utm(struct Point3d const* src_pt, Coordinate_t dst_coord, struct Point3d* dst_pt);

/**
 * @brief Convert lonlat point to utm point and get the coordinate with offset values.
 *
 * @param[in] src_pt Point to convert
 * @param[out] dst_coord The corresponding coordinate with the offset values
 * @param[out] dst_pt The converted utm point in the corresponding coordinate
 *
 * @return RC_SUCCESS if no error occurs
 */
retcode_t point2_convert_lonlat_to_utm_and_coord(struct Point2d const* src_pt, Coordinate_t* dst_coord,
                                                 struct Point2d* dst_pt);

/**
 * @brief Convert lonlat point to utm point and get the coordinate with offset values.
 *
 * @param[in] src_pt Point to convert
 * @param[out] dst_coord The corresponding coordinate with the offset values
 * @param[out] dst_pt The converted utm point in the corresponding coordinate
 *
 * @return RC_SUCCESS if no error occurs
 */
retcode_t point3_convert_lonlat_to_utm_and_coord(struct Point3d const* src_pt, Coordinate_t* dst_coord,
                                                 struct Point3d* dst_pt);

/**
 * @brief Convert utm point to lonlat point
 *
 * @param src_coord The coordinate utm point is in.
 * @param src_pt The utm point.
 * @param dst_pt Converted lonlat point.
 *
 * @return RC_SUCCESS if no error occurs
 */
retcode_t point2_convert_utm_to_lonlat(Coordinate_t src_coord, struct Point2d const* src_pt, struct Point2d* dst_pt);

/**
 * @brief Convert utm point to lonlat point
 *
 * @param src_coord The coordinate utm point is in.
 * @param src_pt The utm point.
 * @param dst_pt Converted lonlat point.
 *
 * @return RC_SUCCESS if no error occurs
 */
retcode_t point3_convert_utm_to_lonlat(Coordinate_t src_coord, struct Point3d const* src_pt, struct Point3d* dst_pt);

/**
 * @brief Convert utm position from source coordinate to target target coordinate
 *
 * @param[in] src_coord Source coordinate
 * @param[in] src_pt The utm position based on the source coordinate
 * @param[in] dst_coord Target coordinate
 * @param[in] dst_pt The utm position based on the target coordinate
 * @return The return code
 */
retcode_t point2_convert_utm_with_target_coord(Coordinate_t src_coord, struct Point2d const* src_pt,
                                               Coordinate_t dst_coord, struct Point2d* dst_pt);

/**
 * @brief Convert utm position from source coordinate to target target coordinate
 *
 * @param[in] src_coord Source coordinate
 * @param[in] src_pt The utm position based on the source coordinate
 * @param[in] dst_coord Target coordinate
 * @param[in] dst_pt The utm position based on the target coordinate
 * @return The return code
 */
retcode_t point3_convert_utm_with_target_coord(Coordinate_t src_coord, struct Point3d const* src_pt,
                                               Coordinate_t dst_coord, struct Point3d* dst_pt);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
