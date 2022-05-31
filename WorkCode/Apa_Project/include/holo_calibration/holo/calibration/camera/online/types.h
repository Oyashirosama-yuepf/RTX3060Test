/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file types.h
 * @brief the definition of types
 * @author zhaojiaxing@holomatic.com
 * @date 2020-07-28
 */

#ifndef HOLO_CALIBRATION_CAMERA_ONLINE_TYPES_H_
#define HOLO_CALIBRATION_CAMERA_ONLINE_TYPES_H_

#include <holo/log/hololog.h>
#include <holo/common/lane_boundary2.h>
#include <holo/common/optional.h>
#include <holo/common/road_frame2.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/line2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/polyfit2.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/matrix.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 * @addtogroup camera
 * @{
 *
 */

/**
 * @brief define basic types
 *
 * @note define sepcific types for camera online module or types from holo::calibration:: will be used
 * @author zhaojiaxing@holomatic.com
 */

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief  basic geometry types
 *
 */
using Scalar             = holo::float64_t;
using Scalar_32_t        = holo::float32_t;
using EpsilonType        = holo::EpsilonT<Scalar>;
using Polyfit2Type       = holo::geometry::Polyfit2T<Scalar>;
using Pose3Type          = holo::geometry::Pose3T<Scalar>;
using Point3Type         = holo::geometry::Point3T<Scalar>;
using Point2Type         = holo::geometry::Point2T<Scalar>;
using Point2Scalar32Type = holo::geometry::Point2T<Scalar_32_t>;
using Line2Type          = holo::geometry::Line2T<Scalar>;
using Vector2Type        = holo::numerics::Vector2T<Scalar>;
using Vector3Type        = holo::numerics::Vector3T<Scalar>;
using Vector6Type        = holo::numerics::Vector6T<Scalar>;
using Vector9Type        = holo::numerics::VectorT<Scalar, 9>;
using VectorXType        = holo::numerics::VectorXT<Scalar>;
using Matrix2Type        = holo::numerics::Matrix2T<Scalar>;
using Matrix3Type        = holo::numerics::Matrix3T<Scalar>;
using Matrix4Type        = holo::numerics::Matrix4T<Scalar>;
using MatrixXType        = holo::numerics::MatrixXT<Scalar>;
using Matrix36Type       = holo::numerics::MatrixT<Scalar, 3, 6>;
using Timestamp          = holo::common::Timestamp;

/**
 * @brief lane types
 *
 */
using PolynomialType   = holo::numerics::Polynomial<Scalar_32_t, 3U>;
using RoadFrameType    = holo::common::RoadFrame<PolynomialType, 4U>;
using LaneBoundaryType = holo::common::LaneBoundary<PolynomialType>;

///////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup calibration
 * @brief the wrapper of smart camera lane points in 3d
 */
struct SmartLanePoints
{
    // time stamp
    Timestamp time;

    // left lane points
    std::vector<Point3Type> left_pts;

    // right lane points
    std::vector<Point3Type> right_pts;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup calibration
 * @brief the wrapper of holo camera lane in 2D, we project smart camera lane
 *        in 3D to holo camera image that to establish constraint equation, so
 *        we need model the holo camera lane as Line2. Due to calibrate mainly
 *        the yaw angle, we just need the vehicle running in straight line.
 */
struct HoloLane2D
{
    // time stamp
    Timestamp time;

    // left lane
    OptionalT<Line2Type> left_lane;

    // right lane
    OptionalT<Line2Type> right_lane;
};

/**
 * @brief correspondence
 */
struct Correspondence
{
    std::vector<Point3Type> source_pts;   ///< smart camera interpolated 3D points
    Line2Type               target_line;  ///< holo camera detected lane in image

};  // correspondence

/**
 * @}
 *
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_ONLINE_TYPES_H_