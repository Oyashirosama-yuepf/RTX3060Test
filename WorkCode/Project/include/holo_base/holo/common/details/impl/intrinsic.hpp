/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intrinsic.hpp
 * @brief the implementation of template class intrinsic
 * @author lifeng@holomatic.com
 * @date Dec 18, 2020
 */

#ifndef HOLO_COMMON_DETAILS_IMPL_INTRINSIC_HPP_
#define HOLO_COMMON_DETAILS_IMPL_INTRINSIC_HPP_

#include <holo/common/details/intrinsic.h>

namespace holo
{
namespace common
{
namespace details
{
template <typename T>
void PinholeIntrinsicT<T>::Project(Point3Type const& input, Point2Type& output) const noexcept
{
    ScalarType z = input.GetZ();

    if (input.GetZ() < ScalarEqualT<ScalarType>().GetEpsilonValue())
    {
        // avoiding denominator equals to 0
        z = ScalarEqualT<ScalarType>().GetEpsilonValue();
    }
    // distort points
    // normalization coordinate
    const Point3Type ptn = input / z;
    const ScalarType x   = ptn.GetX();
    const ScalarType y   = ptn.GetY();

    ScalarType r2          = x * x + y * y;
    ScalarType r4          = r2 * r2;
    ScalarType r6          = r4 * r2;
    ScalarType numerator   = static_cast<ScalarType>(1.0 + GetD()(0) * r2 + GetD()(1) * r4 + GetD()(4) * r6);
    ScalarType denominator = static_cast<ScalarType>(1.0);
    ScalarType scale       = numerator / denominator;
    ScalarType xd = static_cast<ScalarType>(x * scale + 2 * GetD()(2) * x * y + GetD()(3) * (r2 + 2.0 * x * x));
    ScalarType yd = static_cast<ScalarType>(y * scale + GetD()(2) * (r2 + 2.0 * y * y) + 2.0 * GetD()(3) * x * y);
    ScalarType project2d_x = xd * GetK()(0, 0) + yd * GetK()(0, 1) + GetK()(0, 2);
    ScalarType project2d_y = yd * GetK()(1, 1) + GetK()(1, 2);

    // construct output
    output.SetX(project2d_x);
    output.SetY(project2d_y);
    return;
}

template <typename T>
void PinholeIntrinsicT<T>::Unproject(Point2Type const& input, Point3Type& output) const noexcept
{
    cv::Mat    cv_K_eye = cv::Mat::eye(3, 3, CV_32F);  // float32_t
    Point2Type undistorted_pt;
    UndistortPoint(input, undistorted_pt, cv_K_eye);
    output = Point3Type(undistorted_pt.Homogeneous());
}

template <typename T>
void PinholeIntrinsicT<T>::UndistortPoint(const Point2Type& input, Point2Type& output, const cv::Mat& cv_K) const
    noexcept
{
    // construct cv-mat type of K
    cv::Mat cam_K = cv::Mat(3, 3, CV_32F);  // float32_t
    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            cam_K.at<holo::float32_t>(i, j) = static_cast<holo::float32_t>(GetK()(i, j));
        }
    }

    // construct cv-mat type of D
    cv::Mat cam_D          = cv::Mat::zeros(4, 1, CV_64F);
    cam_D.at<float64_t>(0) = GetD()(0);  // k1
    cam_D.at<float64_t>(1) = GetD()(1);  // k2
    cam_D.at<float64_t>(2) = GetD()(2);  // p1
    cam_D.at<float64_t>(3) = GetD()(3);  // p2
    cam_D.at<float64_t>(4) = GetD()(4);  // k3

    // conver to cv type
    std::vector<cv::Point2f> cv_in, cv_out;
    cv_in.push_back(
        cv::Point2f(static_cast<holo::float32_t>(input.GetX()), static_cast<holo::float32_t>(input.GetY())));

    cv::undistortPoints(cv_in, cv_out, cam_K, cam_D, cv::Matx33d::eye(), cv_K);

    // convert back to holo type
    output.SetX(cv_out.at(0).x);
    output.SetY(cv_out.at(0).y);
}

template <typename T>
void FisheyeIntrinsicT<T>::Project(Point3Type const& input, Point2Type& output) const noexcept
{
    ScalarType z = input.GetZ();

    if (input.GetZ() < ScalarEqualT<ScalarType>().GetEpsilonValue())
    {
        // avoiding denominator equals to 0
        z = ScalarEqualT<ScalarType>().GetEpsilonValue();
    }

    // distort points
    // normalization coordinate
    const Point3Type ptn = input / z;
    const ScalarType a   = ptn.GetX();
    const ScalarType b   = ptn.GetY();

    ScalarType r2 = a * a + b * b;

    ScalarType r = std::sqrt(r2);

    if (r < ScalarEqualT<ScalarType>().GetEpsilonValue())
    {
        // avoiding denominator equals to 0
        r = std::sqrt(r2) + ScalarEqualT<ScalarType>().GetEpsilonValue();
    }

    ScalarType theta  = std::atan(r);
    ScalarType theta2 = theta * theta;
    ScalarType theta4 = theta2 * theta2;
    ScalarType theta6 = theta2 * theta4;
    ScalarType theta8 = theta4 * theta4;
    ScalarType rd     = static_cast<ScalarType>(
        theta * (1.0 + GetD()(0) * theta2 + GetD()(1) * theta4 + GetD()(2) * theta6 + GetD()(3) * theta8));
    ScalarType xd          = rd * (a / r);
    ScalarType yd          = rd * (b / r);
    ScalarType project2d_x = xd * GetK()(0, 0) + yd * GetK()(0, 1) + GetK()(0, 2);
    ScalarType project2d_y = yd * GetK()(1, 1) + GetK()(1, 2);

    // construct output
    output.SetX(project2d_x);
    output.SetY(project2d_y);
    return;
}

template <typename T>
void FisheyeIntrinsicT<T>::Unproject(Point2Type const& input, Point3Type& output) const noexcept
{
    cv::Mat    cv_K_eye = cv::Mat::eye(3, 3, CV_32F);  // float32_t
    Point2Type undistorted_pt;
    UndistortPoint(input, undistorted_pt, cv_K_eye);
    output = Point3Type(undistorted_pt.Homogeneous());
}

template <typename T>
void FisheyeIntrinsicT<T>::UndistortPoint(const Point2Type& input, Point2Type& output, const cv::Mat& cv_K) const
    noexcept
{
    // construct cv-mat type of K
    cv::Mat cam_K = cv::Mat(3, 3, CV_32F);  // float32_t
    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            cam_K.at<holo::float32_t>(i, j) = static_cast<holo::float32_t>(GetK()(i, j));
        }
    }

    cv::Mat cam_D          = cv::Mat::zeros(4, 1, CV_64F);
    cam_D.at<float64_t>(0) = GetD()(0);  // k1
    cam_D.at<float64_t>(1) = GetD()(1);  // k2
    cam_D.at<float64_t>(2) = GetD()(2);  // k3
    cam_D.at<float64_t>(3) = GetD()(3);  // k4

    // conver to cv type
    std::vector<cv::Point2f> cv_in, cv_out;
    cv_in.push_back(
        cv::Point2f(static_cast<holo::float32_t>(input.GetX()), static_cast<holo::float32_t>(input.GetY())));

    cv::fisheye::undistortPoints(cv_in, cv_out, cam_K, cam_D, cv::Matx33d::eye(), cv_K);

    // convert back to holo type
    output.SetX(cv_out.at(0).x);
    output.SetY(cv_out.at(0).y);
}

template <typename T>
void OmnidirectionalIntrinsicT<T>::SetUnprojectPolynomial(std::initializer_list<ScalarType> unproject_poly,
                                                          std::initializer_list<ScalarType> project_poly)
{
    // validity checking
    if (unproject_poly.size() > 5)
    {
        throw std::runtime_error("OmnidirectionalIntrinsicT --- invalid unproject poly.");
    }

    if (project_poly.size() > 15)
    {
        throw std::runtime_error("OmnidirectionalIntrinsicT --- invalid project poly.");
    }

    // assign to unproject_poly
    size_t index = 0;

    for (const auto& element : unproject_poly)
    {
        unproject_poly_[index++] = element;
    }

    // assign to proj_poly
    index = 0;

    for (const auto& element : project_poly)
    {
        proj_poly_[index++] = element;
    }
}

template <typename T>
void OmnidirectionalIntrinsicT<T>::SetUnprojectPolynomial(ScalarType a0, ScalarType a1, ScalarType a2, ScalarType a3,
                                                          ScalarType a4) noexcept
{
    unproject_poly_ = {a0, a1, a2, a3, a4};
    computeProjectPoly();
}

template <typename T>
void OmnidirectionalIntrinsicT<T>::computeProjectPoly()
{
    /// @todo(Feng. Li lifeng@holomatic.com 2020-12-18) implementing this function in future.
    throw std::runtime_error("OmnidirectionalIntrinsicT --- calling unimplemented function.");
}

template <typename T>
void OmnidirectionalIntrinsicT<T>::Project(Point3Type const& input, Point2Type& output) const noexcept
{
    ScalarType norm    = std::sqrt(input.GetX() * input.GetX() + input.GetY() * input.GetY());
    ScalarType theta   = std::atan2(-input.GetZ(), norm);
    ScalarType rho     = 0.0;
    ScalarType theta_i = static_cast<ScalarType>(1.0);

    for (size_t i = 0; i < proj_poly_.size(); ++i)
    {
        rho += theta_i * proj_poly_[i];
        theta_i *= theta;
    }

    ScalarType  inv_norm = static_cast<ScalarType>(1.0 / norm);
    Vector2Type xn(input.GetX() * inv_norm * rho, input.GetY() * inv_norm * rho);

    output.SetX(xn[0] * c_ + xn[1] * d_ + cx_);
    output.SetY(xn[0] * e_ + xn[1] + cy_);
}

template <typename T>
void OmnidirectionalIntrinsicT<T>::Unproject(Point2Type const& input, Point3Type& output) const noexcept
{
    // affine transformation
    ScalarType             inv_scale = static_cast<ScalarType>(1.0 / (c_ - d_ * e_));
    holo::geometry::Point2 xc(input.GetX() - cx_, input.GetY() - cy_);
    Point2Type             p(static_cast<ScalarType>(inv_scale * (xc.GetX() - d_ * xc.GetY())),
                 static_cast<ScalarType>(inv_scale * (-e_ * xc.GetX() + c_ * xc.GetY())));

    // comput z
    ScalarType phi   = std::sqrt(p.GetX() * p.GetX() + p.GetY() * p.GetY());
    ScalarType phi_i = static_cast<ScalarType>(1.0);
    ScalarType z     = 0.0;

    for (size_t i = 0; i < unproject_poly_.size(); ++i)
    {
        z += phi_i * unproject_poly_[i];
        phi_i *= phi;
    }

    output.SetX(p.GetX());
    output.SetY(p.GetY());
    output.SetZ(-z);
}

template <typename T>
void OmnidirectionalIntrinsicT<T>::UndistortPoint(const Point2Type& input, Point2Type& output,
                                                  const cv::Mat& cv_K) const noexcept
{
    Point3Type point_ray;
    Unproject(input, point_ray);
    const auto z = point_ray.GetZ();
    cv::Mat    cv_k_float32;
    cv_K.convertTo(cv_k_float32, CV_32F);
    const cv::Mat project_point =
        cv_k_float32 * cv::Mat(cv::Point3f(static_cast<holo::float32_t>(point_ray.GetX() / z),
                                           static_cast<holo::float32_t>(point_ray.GetY() / z), 1));
    output.SetX(project_point.at<float32_t>(0));
    output.SetY(project_point.at<float32_t>(1));
}

}  // namespace details
}  // namespace common
}  // namespace holo

#endif
