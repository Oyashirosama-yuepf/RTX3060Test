/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intrinsic.h
 * @brief This header file define camera intrinsic
 * @author Guo Peikai(guopeikai@holomatic.com)
 * @date 2021-12-08
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_INTRINSIC_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_INTRINSIC_H_
#include <holo/common/sensor_id.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/utils/yaml_loader.h>
#include <opencv2/opencv.hpp>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief This class to held basic intrisic parameter for camera
 */
template <typename T>
class CameraIntrinsicBaseT
{
public:
    using ScalarType = T;
    using Point3Type = holo::geometry::Point3T<ScalarType>;
    using Point2Type = holo::geometry::Point2T<ScalarType>;
    /**
     * @brief Camera model definition
     *
     */
    enum class Model : uint32_t
    {
        PINHOLE         = 0x0000,
        FISHEYE         = 0x0010,
        OMNIDIRECTIONAL = 0x0020,
        UNKNOWN         = 0xFFFF,
    };  //  enum Model

    /**
     * @brief get camera model
     *
     * @return Model
     */
    Model GetModel() const noexcept
    {
        return model_;
    }

    /**
     * @brief get camera sensor id
     *
     * @return sensor id
     */
    holo::common::SensorId GetSensorId() const noexcept
    {
        return sensor_id_;
    }

    /**
     * @brief set camera sensor id
     *
     * @param sensor_id camera sensor id
     */
    void SetSensorId(holo::common::SensorId sensor_id) noexcept
    {
        sensor_id_ = sensor_id;
    }

    /**
     * @brief set image dimention
     *
     * @param width image width
     * @param height image height
     */
    void SetDimension(size_t width, size_t height) noexcept
    {
        width_  = width;
        height_ = height;
    }

    /**
     * @brief get image width
     *
     * @return image width
     */
    size_t GetWidth() const noexcept
    {
        return width_;
    }

    /**
     * @brief get image height
     *
     * @return image height
     */
    size_t GetHeight() const noexcept
    {
        return height_;
    }

    /**
     * @brief default constructor
     */
    CameraIntrinsicBaseT(Model model) noexcept : model_{model}, sensor_id_{}, width_{0U}, height_{0U}
    {
    }

    /**
     * @brief destructor
     */
    ~CameraIntrinsicBaseT() noexcept = default;

    /**
     * @brief Project a point in 3d space to image plane
     *
     * @param input the 3d point
     * @param output 2d point in image coordinate
     */
    virtual void Project(Point3Type const& input, Point2Type& output) const noexcept = 0;

    /**
     * @brief Unproject a 2d point in image plane to 3d space.
     *
     * @param input the 2d point in image coordinate
     * @param output 3d point
     */
    virtual void Unproject(Point2Type const& input, Point3Type& output) const noexcept = 0;

    /**
     * @brief undistort point
     *
     * @param input the 2d point in image coordinate
     * @param output undistort point
     * @param cv_K  New camera matrix (3x3) or new projection matrix (3x4)
     */
    virtual void UndistortPoint(const Point2Type& input, Point2Type& output, const cv::Mat& cv_K) const noexcept = 0;

private:
    /**
     * @brief camera model
     */
    Model model_;

    /**
     * @brief camera sensor id
     */
    holo::common::SensorId sensor_id_;

    /**
     * @brief camera dimention
     */
    size_t width_;
    size_t height_;
};

/**
 * @brief This class to held intrisic parameter for a pinhole camera
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class PinholeIntrinsicT : public CameraIntrinsicBaseT<T>
{
public:
    using Base         = CameraIntrinsicBaseT<T>;
    using ScalarType   = T;
    using Matrix33Type = holo::numerics::MatrixT<ScalarType, 3U, 3U>;
    using Vector5Type  = holo::numerics::VectorT<ScalarType, 5U>;
    using Point3Type   = holo::geometry::Point3T<ScalarType>;
    using Vector3Type  = holo::numerics::Vector3T<ScalarType>;
    using Point2Type   = holo::geometry::Point2T<ScalarType>;

    /**
     * @brief default constructor
     */
    PinholeIntrinsicT() noexcept : Base{Base::Model::PINHOLE}, k_{0, 0, 0, 0, 0, 0, 0, 0, 1}, d_{0, 0, 0, 0}
    {
    }

    /**
     * @brief set focal length
     *
     * @param fx focal length in x direction
     * @param fy focal length in y direction
     */
    void SetFocalLength(ScalarType fx, ScalarType fy) noexcept
    {
        k_(0, 0) = fx;
        k_(1, 1) = fy;
    }

    /**
     * @brief set principle point
     *
     * @param cx coordinate of principle point in x direction
     * @param cy coordinate of principle point in y direction
     */
    void SetPrinciplePoint(ScalarType cx, ScalarType cy) noexcept
    {
        k_(0, 2) = cx;
        k_(1, 2) = cy;
    }

    /**
     * @brief set skew
     *
     * @param skew skew parameters
     */
    void SetSkew(ScalarType skew) noexcept
    {
        k_(0, 1) = skew;
    }

    /**
     * @brief set distortion parameters
     *
     * @param k1 radial distortion k1
     * @param k2 radial distortion k2
     * @param p1 tangential distortion p1
     * @param p2 tangential distortion p2
     * @param k3 radial distortion k3
     */
    void SetDistortionParameter(ScalarType k1, ScalarType k2, ScalarType p1, ScalarType p2,
                                ScalarType k3 = 0.0) noexcept
    {
        d_ = {k1, k2, p1, p2, k3};
    }

    /**
     * @brief Project a point in 3d space to image plane
     * @note this function does NOT check whether the projected point is out of image boundary
     *
     * @param input the 3d point
     * @param output 2d point in image coordinate
     */
    void Project(Point3Type const& input, Point2Type& output) const noexcept;

    /**
     * @brief Unproject a 2d point in image plane to 3d space.
     * @note 1. this function assume that the input 2d point has been well undistorted.
     *       2. he returned point has a depth of 1.0 (that is: z = 1)
     *
     * @param input the 2d point in image coordinate
     * @param output 3d point
     */
    void Unproject(Point2Type const& input, Point3Type& output) const noexcept;

    /**
     * @brief undistort point
     *
     * @param input the 2d point in image coordinate
     * @param output undistort point
     * @param cv_K  New camera matrix (3x3) or new projection matrix (3x4)
     */
    virtual void UndistortPoint(const Point2Type& input, Point2Type& output,
                                const cv::Mat& cv_K) const noexcept override;

    /**
     * @brief distort points
     *
     * @param in undistorted points
     * @param out distorted points
     */
    void DistortPoints(const std::vector<Point2Type>& in, std::vector<Point2Type>& out) const noexcept;

    /**
     * @brief get camera intrinsic matrix
     */
    const Matrix33Type& GetK() const noexcept
    {
        return k_;
    }

    /**
     * @brief get distortion parameters
     */
    const Vector5Type& GetD() const noexcept
    {
        return d_;
    }

    /**
     * @brief declare friend class
     */
    friend holo::utils::YamlLoader<PinholeIntrinsicT>;

private:
    /**
     * @brief camera intrinsic matrix
     */
    Matrix33Type k_;

    /**
     * @brief distortion parameters
     */
    Vector5Type d_;
};  // class PinholeIntrinsicT

/**
 * @brief This class to held intrisic parameter for a fisheye camera
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class FisheyeIntrinsicT : public CameraIntrinsicBaseT<T>
{
public:
    using Base         = CameraIntrinsicBaseT<T>;
    using ScalarType   = T;
    using Matrix33Type = holo::numerics::MatrixT<ScalarType, 3U, 3U>;
    using Vector4Type  = holo::numerics::VectorT<ScalarType, 4U>;
    using Point3Type   = holo::geometry::Point3T<ScalarType>;
    using Vector3Type  = holo::numerics::Vector3T<ScalarType>;
    using Point2Type   = holo::geometry::Point2T<ScalarType>;

    /**
     * @brief default constructor
     */
    FisheyeIntrinsicT() noexcept : Base{Base::Model::FISHEYE}, k_{0, 0, 0, 0, 0, 0, 0, 0, 1}, d_{0, 0, 0, 0}
    {
        // construct cv-mat type of K
        cv_k_                           = cv::Mat(3, 3, CV_32F);  // float32_t
        cv_k_.at<holo::float32_t>(2, 2) = 1;
        cv_d_                           = cv::Mat::zeros(4, 1, CV_64F);
    }

    /**
     * @brief set focal length
     *
     * @param fx focal length in x direction
     * @param fy focal length in y direction
     */
    void SetFocalLength(ScalarType fx, ScalarType fy) noexcept
    {
        k_(0, 0)                        = fx;
        k_(1, 1)                        = fy;
        cv_k_.at<holo::float32_t>(0, 0) = fx;
        cv_k_.at<holo::float32_t>(1, 1) = fy;
    }

    /**
     * @brief set principle point
     *
     * @param cx coordinate of principle point in x direction
     * @param cy coordinate of principle point in y direction
     */
    void SetPrinciplePoint(ScalarType cx, ScalarType cy) noexcept
    {
        k_(0, 2)                        = cx;
        k_(1, 2)                        = cy;
        cv_k_.at<holo::float32_t>(0, 2) = cx;
        cv_k_.at<holo::float32_t>(1, 2) = cy;
    }

    /**
     * @brief set skew
     *
     * @param skew skew parameters
     */
    void SetSkew(ScalarType skew) noexcept
    {
        k_(0, 1)                        = skew;
        cv_k_.at<holo::float32_t>(0, 1) = skew;
    }

    /**
     * @brief set distortion parameters
     *
     * @param k1 radial distortion k1
     * @param k2 radial distortion k2
     * @param k3 radial distortion k3
     * @param k4 radial distortion k4
     */
    void SetDistortionParameter(ScalarType k1, ScalarType k2, ScalarType k3, ScalarType k4)
    {
        d_                     = {k1, k2, k3, k4};
        cv_d_.at<float64_t>(0) = k1;  // k1
        cv_d_.at<float64_t>(1) = k2;  // k2
        cv_d_.at<float64_t>(2) = k3;  // k3
        cv_d_.at<float64_t>(3) = k4;  // k4
    }

    /**
     * @brief Project a point in 3d space to image plane
     * @note this function does NOT check whether the projected point is out of image boundary
     *
     * @param input the 3d point
     * @param output 2d point in image coordinate
     */
    void Project(Point3Type const& input, Point2Type& output) const noexcept;

    /**
     * @brief Unproject a 2d point in image plane to 3d space.
     * @note 1. this function assume that the input 2d point has been well undistorted.
     *       2. he returned point has a depth of 1.0 (that is: z = 1)
     *
     * @param input the 2d point in image coordinate
     * @param output 3d point
     */
    void Unproject(Point2Type const& input, Point3Type& output) const noexcept;

    /**
     * @brief undistort point
     *
     * @param input the 2d point in image coordinate
     * @param output undistort point
     * @param cv_K  New camera matrix (3x3) or new projection matrix (3x4)
     */
    virtual void UndistortPoint(const Point2Type& input, Point2Type& output,
                                const cv::Mat& cv_K) const noexcept override;

    /**
     * @brief distort points
     *
     * @param in undistorted points
     * @param out distorted points
     */
    void DistortPoints(const std::vector<Point2Type>& in, std::vector<Point2Type>& out) const noexcept;

    /**
     * @brief get camera intrinsic matrix
     */
    const Matrix33Type& GetK() const noexcept
    {
        return k_;
    }

    /**
     * @brief get distortion parameters
     */
    const Vector4Type& GetD() const noexcept
    {
        return d_;
    }

    /**
     * @brief declare friend class
     */
    friend holo::utils::YamlLoader<FisheyeIntrinsicT>;

private:
    /**
     * @brief camera intrinsic matrix
     */
    Matrix33Type k_;
    cv::Mat      cv_k_;

    /**
     * @brief distortion parameters
     */
    Vector4Type d_;
    cv::Mat     cv_d_;
};  // class FisheyeIntrinsicT

/**
 * @brief This class to held intrisic parameter for a omnidirectional camera
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class OmnidirectionalIntrinsicT : public CameraIntrinsicBaseT<T>
{
public:
    using Base        = CameraIntrinsicBaseT<T>;
    using ScalarType  = T;
    using Vector3Type = holo::numerics::VectorT<ScalarType, 3U>;
    using Vector2Type = holo::numerics::VectorT<ScalarType, 2U>;
    using Point3Type  = holo::geometry::Point3T<ScalarType>;
    using Point2Type  = holo::geometry::Point2T<ScalarType>;

    /**
     * @brief default constructor
     */
    OmnidirectionalIntrinsicT() noexcept
      : Base{Base::Model::OMNIDIRECTIONAL}, unproject_poly_{0}, cx_{0}, cy_{0}, c_{0}, d_{0}, e_{0}, proj_poly_{0}
    {
    }

    /**
     * @brief set principle point
     *
     * @param cx coordinate of principle point in x direction
     * @param cy coordinate of principle point in y direction
     */
    void SetPrinciplePoint(ScalarType cx, ScalarType cy) noexcept
    {
        cx_ = cx;
        cy_ = cy;
    }

    /**
     * @brief set coefficients of unproject polynomial.
     * @note 1. The coefficients of projetion polynomial will be computed automatically inside this function.
     *       2. User should call this funtion AFTER properly setting the image dimention and principle point.
     * @param coefficients of unproject polynomial
     */
    void SetUnprojectPolynomial(ScalarType a0, ScalarType a1, ScalarType a2, ScalarType a3, ScalarType a4) noexcept;

    /**
     * @brief set coefficients of unproject polynomial. meanwhile set the coefficients of project polynomial
     * @note the project polynomial can be fitted offline.
     * @exception runtime_error thrown if the size of unproject_poly is not equals to 5 or the size of project_poly is
     * larger than 15.
     *
     * @param unproject_poly the coefficients of unproject polynomial.
     * @param project_poly the coefficients of project polynomial.
     */
    void SetUnprojectPolynomial(std::initializer_list<ScalarType> unproject_poly,
                                std::initializer_list<ScalarType> project_poly);

    /**
     * @brief set affine transformation parameters
     *
     * @param c
     * @param d
     * @param e
     */
    void SetAffineTransformation(ScalarType c, ScalarType d, ScalarType e) noexcept
    {
        c_ = c;
        d_ = d;
        e_ = e;
    }

    /**
     * @brief Project a point in 3d space to image plane
     * @note this function does NOT check whether the projected point is out of image boundary
     *
     * @param input the 3d point
     * @param output 2d point in image coordinate
     */
    void Project(Point3Type const& input, Point2Type& output) const noexcept;

    /**
     * @brief Unproject a 2d point in image plane to 3d space.
     *
     * @param input the 2d point in image coordinate
     * @param output 3d point
     */
    void Unproject(Point2Type const& input, Point3Type& output) const noexcept;

    /**
     * @brief undistort point
     *
     * @param input the 2d point in image coordinate
     * @param output undistort point
     * @param cv_K  New camera matrix (3x3) or new projection matrix (3x4)
     */
    virtual void UndistortPoint(const Point2Type& input, Point2Type& output,
                                const cv::Mat& cv_K) const noexcept override;

    /**
     * @brief get principle point
     *
     */
    Point2Type GetPrinciplePoint() const noexcept
    {
        return Point2Type(cx_, cy_);
    }

    /**
     * @brief declare friend class
     */
    friend holo::utils::YamlLoader<OmnidirectionalIntrinsicT>;

private:
    /**
     * @brief fitting the projection polynomial
     * @exception always throwing runtime_error because this funtion was not implement yet.
     *
     */
    void computeProjectPoly();

    /**
     * @brief coefficients of unproject polynomial
     */
    std::array<ScalarType, 5U> unproject_poly_;

    /**
     * @brief principle point
     */
    ScalarType cx_;
    ScalarType cy_;

    /**
     * @brief affine transformation paramters
     */
    ScalarType c_;
    ScalarType d_;
    ScalarType e_;

    /**
     * @brief coefficients of project polynomial
     */
    std::array<ScalarType, 15U> proj_poly_;
};  // class OmnidirectionalIntrinsicT

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif
