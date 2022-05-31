/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file types.h
 * @brief the definition of types
 * @author chenbin@holomatic.com
 * @date 2020-09-01
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_TYPES_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_TYPES_H_

#include <holo/calibration/common/field/apriltag_database.h>
#include <holo/calibration/common/field/chessboard_database.h>
#include <holo/common/coordinate.h>
#include <holo/common/details/intrinsic.h>
#include <holo/common/extrinsic.h>
#include <holo/common/image.h>
#include <holo/common/optional.h>
#include <holo/geometry/details/point2.h>
#include <holo/geometry/details/point3.h>
#include <holo/geometry/details/pose3.h>
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
 * @brief  basic geometry types
 *
 */
using bool_t      = holo::bool_t;
using char_t      = holo::char_t;
using Scalar      = holo::float64_t;
using Scalar_32_t = holo::float32_t;
using Point2      = holo::geometry::details::Point2T<Scalar>;
using Point3      = holo::geometry::details::Point3T<Scalar>;
using Rot3        = holo::geometry::details::Rot3T<Scalar>;
using Pose3       = holo::geometry::details::Pose3T<Scalar>;
using Vector2     = holo::numerics::Vector2T<Scalar>;
using Vector3     = holo::numerics::Vector3T<Scalar>;
using Vector4     = holo::numerics::Vector4T<Scalar>;
using Vector5     = holo::numerics::Vector5T<Scalar>;
using Vector6     = holo::numerics::Vector6T<Scalar>;
using Vector8     = holo::numerics::Vector8T<Scalar>;
using Matrix2     = holo::numerics::Matrix2T<Scalar>;
using Matrix3     = holo::numerics::Matrix3T<Scalar>;
using Matrix4     = holo::numerics::Matrix4T<Scalar>;

using Extrinsic                = holo::common::ExtrinsicT<Scalar_32_t>;
using CameraIntrinsicBase      = holo::common::details::CameraIntrinsicBaseT<Scalar>;
using OmnidirectionalIntrinsic = holo::common::details::OmnidirectionalIntrinsicT<Scalar>;
using FisheyeIntrinsic         = holo::common::details::FisheyeIntrinsicT<Scalar>;
using PinholeIntrinsic         = holo::common::details::PinholeIntrinsicT<Scalar>;
using Image                    = holo::Image;
using CameraModel              = holo::common::details::CameraIntrinsicBaseT<Scalar>::Model;

using AprilTagDatabase      = holo::calibration::AprilTagDatabase;
using AprilTagDatabasePtr   = AprilTagDatabase::Ptr;
using ChessboardDatabase    = holo::calibration::ChessboardDatabase;
using ChessboardDatabasePtr = ChessboardDatabase::Ptr;
using ChArUcobDatabase      = ChessboardDatabase;  ///< At present, we can reuse checkerboardatabase
using ChArUcobDatabasePtr   = ChessboardDatabase::Ptr;
using Coordinate            = holo::common::Coordinate;

/**
 * @brief tag type
 */
enum class TagType : uint8_t
{
    AprilTag   = 0U,
    ChArUcob   = 1U,
    Chessboard = 2U,
    UNKNOWN    = 255U,
};

/**
 * @}
 *
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_FIELD_TYPES_H_
