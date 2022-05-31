/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file types.h
 * @brief the definition of types
 * @author zhaojiaxing@holomatic.com
 * @date 2022-04-11
 */

#ifndef HOLO_CALIBRATION_CAMERA_EOL_PROJECT_TYPES_H_
#define HOLO_CALIBRATION_CAMERA_EOL_PROJECT_TYPES_H_

#include <holo/calibration/camera/field/types.h>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief the struct represent app error status
 */
enum class AppErrorStatus : uint32_t
{
    /**
     * @brief Whether the prerequisites for EOL activation are met
     *
     */
    EOL_ACTIVATION_CONDITIONS_READY = 0x4050,

    /**
     * @brief calibration is timeout
     *
     */
    CALIBRATION_OVERTIME = 0x1000,

    /**
     * @brief front wide camera intrinsic is error
     *
     */
    FRONT_WIDE_INTRINSIC_ERROR = 0x4004,

    /**
     * @brief front camera intrinsic is error
     *
     */
    FRONT_INTRINSIC_ERROR = 0x4042,

    /**
     * @brief left camera intrinsic is error
     *
     */
    LEFT_INTRINSIC_ERROR = 0x4043,

    /**
     * @brief rear camera intrinsic is error
     *
     */
    REAR_INTRINSIC_ERROR = 0x4044,

    /**
     * @brief right camera intrinsic is error
     *
     */
    RIGHT_INTRINSIC_ERROR = 0x4045,

    /**
     * @brief the front wide camera detect corners failed
     *
     */
    DETECTION_POINT_FAILED = 0x4005,

    /**
     * @brief the front wide camera detect two-dimensional code feature corners failed
     *
     */
    QRCODE_DETECTION_POINT_FAILED = 0x4013,

    /**
     * @brief the front camera does not detect enough corners
     *
     */
    FRONT_DETECTION_POINT_NUM_FEW = 0x4046,

    /**
     * @brief the left camera does not detect enough corners
     *
     */
    LEFT_DETECTION_POINT_NUM_FEW = 0x4047,

    /**
     * @brief the rear camera does not detect enough corners
     *
     */
    REAR_DETECTION_POINT_NUM_FEW = 0x4048,

    /**
     * @brief the right camera does not detect enough corners
     *
     */
    RIGHT_DETECTION_POINT_NUM_FEW = 0x4049,

    /**
     * @brief The deviation between the calibration result of the front
     * camera and the given value of extrinsic is too large, and the
     * default maximum tolerance deviation is 5 °
     *
     */
    FRONT_RESULT_ERROR = 0x4060,

    /**
     * @brief The deviation between the calibration result of the left
     * camera and the given value of extrinsic is too large, and the
     * default maximum tolerance deviation is 5 °
     *
     */
    LEFT_RESULT_ERROR = 0x4061,

    /**
     * @brief The deviation between the calibration result of the rear
     * camera and the given value of extrinsic is too large, and the
     * default maximum tolerance deviation is 5 °
     *
     */
    REAR_RESULT_ERROR = 0x4062,

    /**
     * @brief The deviation between the calibration result of the right
     * camera and the given value of extrinsic is too large, and the
     * default maximum tolerance deviation is 5 °
     *
     */
    RIGHT_RESULT_ERROR = 0x4063,

    /**
     * @brief roll of extrinsic is too large
     *
     */
    RESULT_ROLL_ERROR = 0x0100,

    /**
     * @brief pitch of extrinsic is too large
     *
     */
    RESULT_PITCH_ERROR = 0x0200,

    /**
     * @brief yaw of extrinsic is too large
     *
     */
    RESULT_YAW_ERROR = 0x0400,

    /**
     * @brief x of extrinsic is too large
     *
     */
    RESULT_X_ERROR = 0x4001,

    /**
     * @brief y of extrinsic is too large
     *
     */
    RESULT_Y_ERROR = 0x4002,

    /**
     * @brief z of extrinsic is too large
     *
     */
    RESULT_Z_ERROR = 0x4003,

    /**
     * @brief distance of board is too large
     *
     */
    RESULT_DISTANCE_ERROR = 0x0500,

    /**
     * @brief size of board is error
     *
     */
    BOARD_SIZE_ERROR = 0x0600,

    /**
     * @brief not find board
     *
     */
    NOT_FIND_BOARD = 0x4000,

    /**
     * @brief ECU internal error
     *
     */
    ECU_INTERNAL_ERROR = 0x2000,

    /**
     * @brief loading database failed
     *
     */
    LOADING_DATABASE_FAILED = 0x4006,

    /**
     * @brief receive image failed
     *
     */
    RECEIVE_IMAGE_FAILED = 0x4007,

    /**
     * @brief write result failed
     *
     */
    WRITE_RESULT_FAILED = 0x4008,

    /**
     * @brief the number of feature point is few
     *
     */
    FEATURE_POINT_NUM_FEW = 0x4021,

    /**
     * @brief the number of front_camera feature point is few
     *
     */
    FRONT_FEATURE_POINT_DETECTION_FAILED = 0x8000,

    /**
     * @brief the number of left_camera feature point is few
     *
     */
    LEFT_FEATURE_POINT_DETECTION_FAILED = 0x8001,

    /**
     * @brief the number of rear_camera feature point is few
     *
     */
    REAR_FEATURE_POINT_DETECTION_FAILED = 0x8002,

    /**
     * @brief the number of right_camera feature point is few
     *
     */
    RIGHT_FEATURE_POINT_DETECTION_FAILED = 0x8003,

    /**
     * @brief the feature point detected failed in left image
     *
     */
    WIDE_LEFT_IMAGE_FEATURE_POINT_DETECT_FAILED = 0x4011,

    /**
     * @brief the feature point detected failed in right image
     *
     */
    WIDE_RIGHT_IMAGE_FEATURE_POINT_DETECT_FAILED = 0x4012,

    /**
     * @brief Algorithm internal check failed
     *
     */
    ALGORITHM_INTERNAL_CHECK_FAILED = 0x4022,

};

/**
 * @}
 *
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_EOL_PROJECT_TYPES_H_
