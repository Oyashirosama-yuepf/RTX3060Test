/*!
 * * \brief Conversion between lat/lon and UTM
 * * \author Huang Qi
 * * \date Jan 7, 2019
 * * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice. */

#ifndef HOLO_C_GEOMETRY_GEOGRAPHICAL_TRANSFORMATION_H_
#define HOLO_C_GEOMETRY_GEOGRAPHICAL_TRANSFORMATION_H_

#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Convert UTM to lat/lon
 * 
 * @param[in] UTMNorthing Given in meters
 * @param[in] UTMEasting  Given in meters
 * @param[in] UTMZone
 * @param[out] Lat lat longitude to be calculated in units of degrees
 * @param[out] Long lon longitude to be calculated in units of degrees
 * 
 * @return RC_SUCCESS: conversion ok
 *         RC_FAIL: conversion failed
 */
extern retcode_t UTM2LL(const float64_t UTMNorthing, const float64_t UTMEasting, int UTMZone,
                       float64_t *Lat, float64_t *Long);

/**
 * @brief Convert lat/lon to UTM
 * 
 * @param[in] Lat lat longitude in units of degrees
 * @param[in] Long lon longitude in units of degrees
 * @param[out] UTMNorthing Given in meters
 * @param[out] UTMEasting Given in meters
 * @param[out] UTMZone 
 * 
 * @return RC_SUCCESS: conversion ok
 *         RC_FAIL: conversion failed
 */
extern retcode_t LL2UTM(const float64_t Lat, const float64_t Long,
                       float64_t *UTMNorthing, float64_t *UTMEasting, int *UTMZone);


#ifdef __cplusplus
}
#endif

#endif
