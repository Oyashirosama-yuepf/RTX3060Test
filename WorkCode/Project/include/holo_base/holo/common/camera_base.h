/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_base.h
 * @brief This header file defines CameraBaseT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-12-04
 */

#ifndef HOLO_COMMON_CAMERA_BASE_H_
#define HOLO_COMMON_CAMERA_BASE_H_

#include <holo/common/image.h>
#include <holo/common/intrinsic.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/angle.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/rot3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/utils/holo_root.h>

namespace holo
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief This class describe a virtual base camera.
 *
 * @details This class describe a virtual base camera. User can construct different camera by derived this class.
 * It provides utility APIs related to camera projection/unprojection point,and distort/undistort image. And it also
 * provide APIs to access camera basic intrinsic properties, like camera K/K_inv matrix, image reoslution, etc.
 *
 * @tparam T Support float32_t and float64_t.
 */
template <typename T>
class CameraBaseT
{
public:
    using Matrix3[[deprecated]]   = holo::numerics::MatrixT<T, 3, 3>;
    using Vector2[[deprecated]]   = holo::numerics::VectorT<T, 2>;
    using Vector3[[deprecated]]   = holo::numerics::VectorT<T, 3>;
    using Vector8[[deprecated]]   = holo::numerics::VectorT<T, 8>;
    using Point2[[deprecated]]    = holo::geometry::Point2T<T>;
    using Point3[[deprecated]]    = holo::geometry::Point3T<T>;
    using Intrinsic[[deprecated]] = holo::IntrinsicT<T>;

    using Matrix3Type   = holo::numerics::MatrixT<T, 3, 3>;
    using Vector2Type   = holo::numerics::VectorT<T, 2>;
    using Vector3Type   = holo::numerics::VectorT<T, 3>;
    using Vector8Type   = holo::numerics::VectorT<T, 8>;
    using Point2Type    = holo::geometry::Point2T<T>;
    using Point3Type    = holo::geometry::Point3T<T>;
    using IntrinsicType = holo::IntrinsicT<T>;

    /**
     * @brief Default constructor
     */
    CameraBaseT() = delete;

    /**
     * @brief Construct a new Camera Device object with params
     *
     * @param width camera image resolution width
     * @param height camera image resolution height
     * @param k camera K matrix, shape 3x3
     * @param d camera distortion parameters
     *
     * @throw throw std::runtime_error when K matix shape is not 3x3
     */
    CameraBaseT(const uint32_t width, const uint32_t height, const Matrix3Type& k, const Vector8Type& d);

    /**
     * @brief Construct a new Camera Device with intrinsic object
     *
     * @param intrinsic camera intrinsic object
     */
    explicit CameraBaseT(const Intrinsic& intrinsic) noexcept;

    /**
     * @brief Default destructor
     */
    virtual ~CameraBaseT() noexcept;

    /**
     * @brief Get camera distortion model
     *
     * @return camera distortion model
     */
    virtual CameraModel GetCameraDistortionModel() const noexcept = 0;

    /**
     * @brief Get camera resolution width
     *
     * @return camera resolution width
     */
    uint32_t GetResolutionWidth() const noexcept
    {
        return resolution_width_;
    }

    /**
     * @brief get camera resolution height
     *
     * @return camera resolution height
     */
    uint32_t GetResolutionHeight() const noexcept
    {
        return resolution_height_;
    }

    /**
     * @brief Get camera K matrix
     *
     * @return camera K matrix
     */
    const Matrix3Type& GetK() const noexcept
    {
        return k_;
    }

    /**
     * @brief Get camera distortion parameters
     *
     * @return camera distortion parameters
     */
    const Vector8Type& GetD() const noexcept
    {
        return d_;
    }

    /**
     * @brief Get camera inverse K matrix
     *
     * @return inverse camera K matrix
     */
    const Matrix3Type& GetKInv() const noexcept
    {
        return k_inv_;
    }

    /**
     * @brief Project a 3d point in camera coordinate to image with camera intrinsic K matrix, without
     * distortion in image
     *
     * @param in point in camera coordinate to project
     *
     * @return projected point in image, pixel level
     */
    virtual Point2Type Project(const Point3Type& in) const;

    /**
     * @brief Project a 3d point in camera coordinate to image with given K matrix, without distortion in image
     *
     * @param in point in camera coordinate to project
     * @param new_k new K matrix used to projection
     *
     * @return projected point in image, pixel level, same shape with input
     */
    virtual Point2Type Project(const Point3Type& in, const Matrix3Type& new_k) const;

    // /**
    //  * @brief Project multi 3d points in camera coordinate to image with camera intrinsic K matrix, without
    //  * distortion in image
    //  *
    //  * @details Input matrix's shape must be Nx3. If not, throw exception
    //  *
    //  * @param in input points to project
    //  *
    //  * @return projected points in image, pixel level, shape Nx2
    //  *
    //  * @throw std::runtime_error throw when input matrix is not a specified shape Nx3 or is empty
    //  */
    // Won't support until MatrixT support well
    // virtual MatrixN2 Project(const MatrixN3& in) const;

    // /**
    //  * @brief Project multi 3d points in camera coordinate to image with given K matrix, without distortion in image
    //  *
    //  * @details Input matrix's shape must be Nx3. If not, throw exception
    //  *
    //  * @param in input points to project
    //  * @param new_k new K matrix used to projection
    //  *
    //  * @return projected points in image, pixel level, shape Nx2
    //  *
    //  * @throw std::runtime_error throw when input matrix is not a specified shape Nx3 or is empty
    //  */
    // Won't support until MatrixT support well
    // virtual MatrixN2 Project(const MatrixN3& in, const Matrix3Type& new_k) const;

    /**
     * @brief Unproject a 2d point in image to 3d point in camera coordinate which is in identity plane with intrinsic
     * inverse K matrix
     *
     * @param in point in image to unproject
     *
     * @return identity 3d point in camera coordinate, unit: m
     */
    virtual Point3Type Unproject(const Point2Type& in) const;

    /**
     * @brief Unproject a 2d point in image to 3d point in camera coordinate which is in identity plane with a given
     * inverse K matrix
     *
     * @param in point in image to unproject
     * @param new_k_inv given inverse K matrix
     *
     * @return 3d point in camera coordinate within identity plane, unit: m
     */
    virtual Point3Type Unproject(const Point2Type& in, const Matrix3Type& new_k_inv) const;

    // /**
    //  * @brief Unproject N 2d points in image to 3d point in camera coordinate which is in identity plane with
    //  intrinsic
    //  * inverse K matrix, return Nx3 shape matrix
    //  *
    //  * @details Input matrix's shape must be Nx2. If not, throw exception
    //  *
    //  * @param in points in image to unproject
    //  *
    //  * @return identity 3d points in camera coordinate, unit: m, shape Nx3
    //  *
    //  * @throw std::runtime_error throw when input matrix is not a specified shape Nx2 or is empty
    //  */
    // Won't support until MatrixT support well
    // virtual MatrixN3 Unproject(const MatrixN2& in) const;

    // /**
    //  * @brief Unproject multi 2d point in image to 3d point in camera coordinate which is in identity plane with a
    //  given
    //  * inverse K matrix
    //  *
    //  * @details Input matrix's shape must be Nx2. If not, throw exception
    //  *
    //  * @param in points in image to unproject
    //  * @param k_inv given inverse K matrix
    //  *
    //  * @return 3d point in camera coordinate within identity plane, unit: m, shape Nx3
    //  *
    //  * @throw std::runtime_error throw when input matrix is not a specified shape Nx2 or is empty
    //  */
    // Won't support until MatrixT support well
    // virtual MatrixN3 Unproject(const MatrixN2& in, const Matrix3Type& new_k_inv) const;

    /**
     * @brief Add distortion for a pixel point
     *
     * @param in point to distort in identity plane
     * @return distorted point
     */
    virtual Point2Type DistortPoint(const Point2Type& in) const = 0;

    /**
     * @brief Undistort for a pixel point
     *
     * @param in point to undistort
     * @param new_k K matrix used to undistort
     *
     * @return undistorted point
     */
    virtual Point2Type UndistortPoint(const Point2Type& in, const Matrix3Type& new_k) const = 0;

    /**
     * @brief Undistort image
     *
     * @param[in] in input distorted image
     * @param[in] new_k new K matrix used to undistort image
     * @param[out] out output undistorted image
     */
    virtual void UndistortImage(const holo::Image& in, const Matrix3Type& new_k, holo::Image& out) const = 0;

protected:
    /**
     * @brief Compute camera inverse K matrix according K matrix
     */
    virtual void computeKInv();

protected:
    // intrinsic params
    uint32_t    resolution_width_;   ///< image width
    uint32_t    resolution_height_;  ///< image height
    Matrix3Type k_;                  ///< k matirx of camera
    Vector8Type d_;                  ///< camera distortion coeffs
    Matrix3Type k_inv_;              ///< inverse k matrix of camera
};

/**
 * @}
 */

}  // namespace holo

#endif  // !HOLO_COMMON_CAMERA_BASE_H_
