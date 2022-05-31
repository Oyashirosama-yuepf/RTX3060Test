/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file types.h
 * @brief the definition of types
 * @author zhaojiaxing@holomatic.com
 * @date 2020-09-03
 */

#ifndef HOLO_CALIBRATION_WHEELSPEED_TYPES_H_
#define HOLO_CALIBRATION_WHEELSPEED_TYPES_H_

#include <holo/log/hololog.h>
#include <holo/common/chassis_state.h>
#include <holo/common/gnss_pvt.h>
#include <holo/common/lane_boundary2.h>
#include <holo/common/optional.h>
#include <holo/common/road_frame2.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/line2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/polyfit2.h>
#include <holo/geometry/pose3.h>
#include <holo/localization/common/navstate.h>
#include <holo/localization/common/stamped.h>
#include <holo/numerics/matrix.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace calibration
{
namespace wheelspeed
{
/**
 * @addtogroup wheelspeed
 * @{
 *
 */

/**
 * @brief define basic types
 *
 * @note define sepcific types for wheelspeed online module or types from holo::calibration:: will be used
 * @author zhaojiaxing@holomatic.com
 */

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief  basic geometry types
 *
 */
using Scalar                  = holo::float64_t;
using EpsilonType             = holo::EpsilonT<Scalar>;
using Rot3Type                = holo::geometry::Rot3T<Scalar>;
using Pose3Type               = holo::geometry::Pose3T<Scalar>;
using Point3Type              = holo::geometry::Point3T<Scalar>;
using Point2Type              = holo::geometry::Point2T<Scalar>;
using Vector2Type             = holo::numerics::Vector2T<Scalar>;
using Vector3Type             = holo::numerics::Vector3T<Scalar>;
using VectorXType             = holo::numerics::VectorXT<Scalar>;
using Matrix2Type             = holo::numerics::Matrix2T<Scalar>;
using Matrix3Type             = holo::numerics::Matrix3T<Scalar>;
using Matrix4Type             = holo::numerics::Matrix4T<Scalar>;
using MatrixXType             = holo::numerics::MatrixXT<Scalar>;
using Matrix36Type            = holo::numerics::MatrixT<Scalar, 3, 6>;
using GnssPvtType             = holo::common::GnssPvt;
using NavstateType            = holo::localization::NavstateT<Scalar>;
using AdvancedNavstateType    = holo::localization::AdvancedNavstateT<Scalar>;
using StampedAdvancedNavstate = holo::localization::StampedT<AdvancedNavstateType>;
using ChassisState            = holo::common::ChassisState;

/**
 * @brief The wheel speed correction coefficients: real_value = a * measurement + b
 *
 */
struct WheelSpeedCorrectionCoefficient
{
    Scalar a = Scalar(1.0);
    Scalar b = Scalar(0.0);
};

/**
 * @brief This struct is used to save the data for computing the wheel speed correction parameters.
 * @details The data includes average gps velocity, average corresponding wheel velocity and the counter
 *          how much the measurements have been getted.
 */
struct WheelSpeedData
{
    Scalar   average_wheel_speed = Scalar(0.0);  ///< The input wheel speed prepared for calibration
    Scalar   average_gnss_speed  = Scalar(0.0);  ///< The corresponding gps velocity as the ground truth
    uint64_t counter             = 0u;           ///< The counter to record how many calibration data has bee used
};

/**
 * @brief The process state when to calibrate the wheel speed
 *
 */
struct State
{
    /// The data saved for the wheel speed calibration, the key of this map is the speed segment number
    std::map<uint16_t, WheelSpeedData> data;
    bool_t                             is_finished = false;  ///< The flag of if the calibration is finished
};

/**
 * @}
 *
 */
}  // namespace wheelspeed
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_WHEELSPEED_TYPES_H_