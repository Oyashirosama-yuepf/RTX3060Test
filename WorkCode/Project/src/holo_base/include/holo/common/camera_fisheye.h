/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_fisheye.h
 * @brief This header file defines CameraFisheyeT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-12-10
 */

#ifndef HOLO_COMMON_CAMERA_FISHEYE_H_
#define HOLO_COMMON_CAMERA_FISHEYE_H_

#include <cmath>

#include <holo/common/camera_base.h>

namespace holo
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief This class describes a fisheye model camera.
 *
 * @tparam T Support float32_t and float64_t
 */
template <typename T>
class CameraFisheyeT : public CameraBaseT<T>
{
public:
    using Base = CameraBaseT<T>;
    using typename Base::Intrinsic;
    using typename Base::Matrix3;
    using typename Base::Point2;
    using typename Base::Point3;
    using typename Base::Vector2;
    using typename Base::Vector3;
    using typename Base::Vector8;

    using typename Base::IntrinsicType;
    using typename Base::Matrix3Type;
    using typename Base::Point2Type;
    using typename Base::Point3Type;
    using typename Base::Vector2Type;
    using typename Base::Vector3Type;
    using typename Base::Vector8Type;

public:
    /**
     * @brief Delete default constructor
     */
    CameraFisheyeT() = delete;

    /**
     * @brief Constructor with params
     *
     * @param width camera image resolution width
     * @param height camera image resolution height
     * @param k camera K matrix
     * @param d camera distortion parameters
     */
    CameraFisheyeT(const uint32_t widht, const uint32_t height, const Matrix3Type& k, const Vector8Type& d) noexcept;

    /**
     * @brief Constructor with intrinsic
     *
     * @param intrinsic camera intrinsic
     */
    explicit CameraFisheyeT(const IntrinsicType& intrinsic) noexcept;

    /**
     * @brief Copy constructor
     *
     * @param other other fisheye camera
     */
    CameraFisheyeT(const CameraFisheyeT& other) noexcept;

    /**
     * @brief Move constructor
     *
     * @param other other fisheye camera
     */
    CameraFisheyeT(CameraFisheyeT&& other) noexcept;

    /**
     * @brief Copy assignment
     *
     * @param other other fisheye camera
     * @return new fisheye camera
     */
    CameraFisheyeT& operator=(const CameraFisheyeT& other) noexcept;

    /**
     * @brief Move assignment
     *
     * @param other other fisheye camera
     * @return new fisheye camera
     */
    CameraFisheyeT& operator=(CameraFisheyeT&& other) noexcept;

    /**
     * @brief Get camera distortion model
     *
     * @return camera model
     */
    CameraModel GetCameraDistortionModel() const noexcept override
    {
        return CameraModel::FISHEYE;
    }

    /**
     * @brief Distort a point in image frame with
     *
     * @param in input point
     * @param new_k new K matrix
     * @return distorted point
     *
     * @ref https://github.com/opencv/opencv/blob/3.3.1/modules/calib3d/src/fisheye.cpp
     */
    Point2Type DistortPoint(const Point2Type& in) const override;

    /**
     * @brief Undistort point
     *
     * @param in input point
     * @param new_k new K matrix
     * @return undistorted point
     *
     * @ref https://github.com/opencv/opencv/blob/3.3.1/modules/calib3d/src/fisheye.cpp
     */
    Point2Type UndistortPoint(const Point2Type& in, const Matrix3Type& new_k) const override;

    /**
     * @brief Undistort image
     *
     * @param in[in] input image with distortion
     * @param new_k[in] new K matrix
     * @param out[out] output image without distortion
     *
     * @todo Not implement now
     */
    void UndistortImage(const holo::Image& in, const Matrix3Type& new_k, holo::Image& out) const override;
};

/**
 * @}
 */
}  // namespace holo

#endif  // !HOLO_COMMON_CAMERA_FISHEYE_H_
