/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file types.h
 * @brief define common types
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#ifndef HOLO_LOCALIZATION_COMMON_TYPES_H_
#define HOLO_LOCALIZATION_COMMON_TYPES_H_

#include <holo/common/chassis_state.h>
#include <holo/common/coordinate.h>
#include <holo/common/extrinsic.h>
#include <holo/common/gnss_position.h>
#include <holo/common/gnss_pvt.h>
#include <holo/common/image.h>
#include <holo/common/imu.h>
#include <holo/common/imu_bias.h>
#include <holo/common/intrinsic.h>
#include <holo/common/odometry.h>
#include <holo/common/camera_lane_boundary.h>
#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/box2.h>
#include <holo/geometry/line2.h>
#include <holo/geometry/line_segment2.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/quaternion.h>
#include <holo/geometry/rot2.h>
#include <holo/geometry/rot3.h>
#include <holo/localization/common/navstate.h>
#include <holo/localization/common/stamped.h>
#include <holo/map/current_route_info.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief define localization basic core types
 */
using Scalar      = holo::float64_t;
using EpsilonType = holo::EpsilonT<Scalar>;

/**
 * @brief define localization basic geometry types
 */
using Box2Type         = holo::geometry::Box2T<Scalar>;
using Line2Type        = holo::geometry::Line2T<Scalar>;
using LineSegment2Type = holo::geometry::LineSegment2T<Scalar>;
using Point2Type       = holo::geometry::Point2T<Scalar>;
using Point3Type       = holo::geometry::Point3T<Scalar>;
using Pose2Type        = holo::geometry::Pose2T<Scalar>;
using Pose3Type        = holo::geometry::Pose3T<Scalar>;
using QuaternionType   = holo::geometry::QuaternionT<Scalar>;
using Rot2Type         = holo::geometry::Rot2T<Scalar>;
using Rot3Type         = holo::geometry::Rot3T<Scalar>;
using CameraLaneBoundaryType   = holo::common::CameraLaneBoundaryT<holo::float32_t, 3U>;
using CameraLaneBoundariesType = holo::common::CameraLaneBoundariesT<CameraLaneBoundaryType, 4U>;

/**
 * @brief define localization basic numerics types
 */
using Matrix2Type  = holo::numerics::Matrix2T<Scalar>;
using Matrix3Type  = holo::numerics::Matrix3T<Scalar>;
using Matrix4Type  = holo::numerics::Matrix4T<Scalar>;
using Matrix5Type  = holo::numerics::Matrix5T<Scalar>;
using Matrix6Type  = holo::numerics::Matrix6T<Scalar>;
using MatrixXType  = holo::numerics::MatrixXT<Scalar>;
using Vector2Type  = holo::numerics::Vector2T<Scalar>;
using Vector3Type  = holo::numerics::Vector3T<Scalar>;
using Vector4Type  = holo::numerics::Vector4T<Scalar>;
using Vector5Type  = holo::numerics::Vector5T<Scalar>;
using Vector6Type  = holo::numerics::Vector6T<Scalar>;
using Vector9Type  = holo::numerics::VectorT<Scalar, 9>;
using VectorXType  = holo::numerics::VectorXT<Scalar>;
using Matrix93Type = holo::numerics::MatrixT<Scalar, 9, 3>;
using Matrix96Type = holo::numerics::MatrixT<Scalar, 9, 6>;
using Matrix99Type = holo::numerics::MatrixT<Scalar, 9, 9>;

/**
 * @brief define localization basic common types
 *
 * @todo uncomment the followings and remove this line when float64_t types are available
 */
using Timestamp                    = holo::common::Timestamp;
using Duration                     = holo::common::Duration;
using ExtrinsicType                = holo::common::ExtrinsicT<holo::float32_t>;
using ImuType                      = holo::common::ImuT<Scalar>;
using ImuBiasType                  = holo::common::ImuBiasT<Scalar>;
using CameraIntrinsicBaseType      = holo::common::details::CameraIntrinsicBaseT<Scalar>;
using CameraIntrinsicBaseTypePtr   = std::shared_ptr<CameraIntrinsicBaseType>;
using PinholeIntrinsicType         = holo::common::PinholeIntrinsicT<Scalar>;
using FisheyeIntrinsicType         = holo::common::FisheyeIntrinsicT<Scalar>;
using OmnidirectionalIntrinsicType = holo::common::OmnidirectionalIntrinsicT<Scalar>;
using IntrinsicType                = FisheyeIntrinsicType;
using GnssPositionType             = holo::GnssPosition;
using GnssPvtType                  = holo::common::GnssPvt;
using CoordinateType               = holo::common::Coordinate;
using OdometryType                 = holo::common::OdometryT<Scalar>;
using NavstateType                 = holo::localization::NavstateT<Scalar>;
using AdvancedNavstateType         = holo::localization::AdvancedNavstateT<Scalar>;
using StampedRouteInfoType         = StampedT<holo::map::CurrentRouteInfo>;
using ImageType                    = holo::Image;
using ChassisState                 = holo::common::ChassisState;

/**
 * @brief definition of lane correspondences
 *
 */
struct LaneCorrespondences
{
    Timestamp               timestamp;  ///< timestamp of lanecorrespondences
    Line2Type               line;       ///< line 2d, it can be in world coordinate or body coordinate frame
    std::vector<Point3Type> points;     ///< vector of points, it can be in world coordinate or body coordinate frame
    std::vector<Scalar>     sigmas;     ///< sigma of each correspondence, unit(m)

    enum class Type
    {
        PROJECT_TO_BODY  = 0,  ///< which means line in body coordinate frame, points in world coordinate frame
        PROJECT_TO_WORLD = 1,  ///< which means line in world coordinate frame, points in body coordinate frame
    };

    Type   type                          = Type::PROJECT_TO_WORLD;  ///< type of lane correspondences
    bool_t disable_rotation_optimization = false;                   ///< disable rotation optimization flag
};

/**
 * @brief This struct is used to define sign correspondence between 2d semantic keypoint and map point of sign in 3d.
 *
 */
struct SignCorrespondences
{
    Timestamp                                      timestamp;        ///< The timestamp.
    std::vector<std::pair<Point2Type, Point3Type>> correspondences;  ///< The correspondence of 2d semantic keypoint
                                                                     ///< and 3d map point.
};

/**
 * @brief Define struct to store Point correspondence
 *
 */
struct PointCorrespondence
{
    Point2Type point_2d;       // 2d point
    Point3Type point_3d;       // 3d point
    Scalar     u_sigma = 5.0;  // sigma of point in u direction (unit: pixel)
    Scalar     v_sigma = 5.0;  // sigma of point in v direction (unit: pixel)
};

/**
 * @brief Define struct to store correspondences including line and point correspondences
 *
 */
struct VisionSemanticCorrespondences
{
    Timestamp                        timestamp;              ///< current timestamp
    Pose3Type                        bTc;                    ///< extrinsic of camera in body
    Matrix3Type                      K;                      ///< camera matrix
    std::vector<PointCorrespondence> point_correspondences;  ///< sign contour point 2D-3D correspondences
    std::vector<LaneCorrespondences> line_correspondences;   ///< pole line 2D-3D correspondences
};

/**
 * @}
 *
 */

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_COMMON_TYPES_H_
