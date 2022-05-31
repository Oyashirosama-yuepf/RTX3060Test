/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file source_checker_helper.h
 * @brief This header file define source checker unique paramters and functions.
 * @author Wenzhi Liu(liuwenzhi@holomatic.com)
 * @date 2020-09-09
 */

#ifndef HOLO_LOCALIZATION_TOOLS_SOURCE_CHECKER_HELPER_H_
#define HOLO_LOCALIZATION_TOOLS_SOURCE_CHECKER_HELPER_H_

#include <holo/localization/common/types.h>

namespace holo
{
namespace localization
{
namespace internal
{
/**
 * @brief define the configuration of odometry unique checker
 */
struct OdometryCheckerUniqueParameters
{
    Scalar  translation_x_cov_threshold;  /* odometry translation x covariance threshold unit(m^2) */
    Scalar  translation_y_cov_threshold;  /* odometry translation y covariance threshold unit(m^2) */
    Scalar  translation_z_cov_threshold;  /* odometry translation z covariance threshold unit(m^2) */
    Scalar  rotation_x_cov_threshold;     /* odometry rotation x covariance threshold unit(rad^2) */
    Scalar  rotation_y_cov_threshold;     /* odometry rotation y covariance threshold unit(rad^2) */
    Scalar  rotation_z_cov_threshold;     /* odometry rotation z covariance threshold unit(rad^2) */
};

/**
 * @brief define the configuration of CameraLaneBoundaries unique checker
 */
struct CameraLaneBoundariesCheckerUniqueParameters
{
    Scalar  detected_lane_confidence_threshold;  /* lane boundary confidence threshold in CameraLaneBoundaries */
    Scalar  detected_lane_too_narrow_threshold;  /* road narrowest threshold unit(m) */
    Scalar  detected_lane_too_wide_threshold;    /* road widest threshold unit(m) */
};

/**
 * @brief check odometry unique state
 * @param params odometry unique checker configuration
 * @param odometry measurment of odometry
 * @return true if the measured value meets the requirements
 */
bool_t CheckOdometryUniqueState(const OdometryCheckerUniqueParameters& params, const OdometryType& odometry);

/**
 * @brief check CameraLaneBoundaries unique state
 * @param params CameraLaneBoundaries unique checker configuration
 * @param camera_lane_boundaries measurment of CameraLaneBoundaries
 * @return true if the measured value meets the requirements
 */
bool_t CheckCameraLaneBoundariesUniqueState(const CameraLaneBoundariesCheckerUniqueParameters& params, 
                                            const CameraLaneBoundariesType& camera_lane_boundaries);

} /* namespace internal */
} /* namespace localization */
} /* namespace holo */

#endif  // HOLO_LOCALIZATION_TOOLS_SOURCE_CHECKER_HELPER_H_
