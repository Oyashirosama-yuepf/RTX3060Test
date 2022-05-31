/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intrinsic.cpp
 * @brief the implementation of template class intrinsic
 * @author Guo Peikai(guopeikai@holomatic.com)
 * @date 2021-12-08
 */

#include <holo/localization/vision/vslam/intrinsic.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void PinholeIntrinsicT<T>::Project(Point3Type const& input, Point2Type& output) const noexcept
{
    // project to normalize plane
    const Point3Type ptn = input / input.GetZ();

    // project to image plane by pinhole camera model
    const Vector3Type pt_img_vec = k_ * Vector3Type(ptn[0], ptn[1], ptn[2]);

    // construct output
    output.SetX(pt_img_vec[0]);
    output.SetY(pt_img_vec[1]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void PinholeIntrinsicT<T>::Unproject(Point2Type const& input, Point3Type& output) const noexcept
{
    output = Point3Type((k_.Inverse() * input.Homogeneous()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void PinholeIntrinsicT<T>::UndistortPoint(const Point2Type& input, Point2Type& output,
                                          const cv::Mat& cv_K) const noexcept
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void PinholeIntrinsicT<T>::DistortPoints(const std::vector<Point2Type>& in, std::vector<Point2Type>& out) const noexcept
{
    // K^-1 = [1/fx 0 -cx/fx; 0 1/fy -cy/fy; 0 0 1]
    Matrix33Type k_inv = GetK();
    {
        k_inv(0, 0) = 1.0f / GetK()(0, 0);
        k_inv(0, 2) *= -k_inv(0, 0);
        k_inv(1, 1) = 1.0f / GetK()(1, 1);
        k_inv(1, 2) *= -k_inv(1, 1);
    }

    // distort points
    for (uint64_t i = 0u; i < in.size(); i++)
    {
        // normalization coordinate
        const Point2Type& p_in        = in.at(i);
        const ScalarType  x_in        = p_in.GetX() * k_inv(0u, 0u) + k_inv(0u, 2u);
        const ScalarType  y_in        = p_in.GetY() * k_inv(1u, 1u) + k_inv(1u, 2u);
        const ScalarType  xy          = x_in * y_in;
        const ScalarType  x2          = x_in * x_in;
        const ScalarType  y2          = y_in * y_in;
        const ScalarType  r2          = x2 + y2;
        const ScalarType  r4          = r2 * r2;
        const ScalarType  r6          = r4 * r2;
        const ScalarType  numerator   = static_cast<ScalarType>(1.0 + GetD()(0) * r2 + GetD()(1) * r4 + GetD()(4) * r6);
        const ScalarType  denominator = static_cast<ScalarType>(1.0);
        const ScalarType  scale       = numerator / denominator;
        ScalarType        x_out       = x_in * scale + 2 * GetD()(2) * xy + GetD()(3) * (r2 + 2.0 * x2);
        ScalarType        y_out       = y_in * scale + GetD()(2) * (r2 + 2.0 * y2) + 2.0 * GetD()(3u) * xy;

        x_out = x_out * GetK()(0u, 0u) + y_out * GetK()(0, 1) + GetK()(0u, 2u);
        y_out = y_out * GetK()(1u, 1u) + GetK()(1u, 2u);
        out.emplace_back(x_out, y_out);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void FisheyeIntrinsicT<T>::Project(Point3Type const& input, Point2Type& output) const noexcept
{
    // project to normalize plane
    const Point3Type ptn = input / input.GetZ();

    // project to image plane by pinhole camera model
    const Vector3Type pt_img_vec = k_ * Vector3Type(ptn[0], ptn[1], ptn[2]);

    // construct output
    output.SetX(pt_img_vec[0]);
    output.SetY(pt_img_vec[1]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void FisheyeIntrinsicT<T>::Unproject(Point2Type const& input, Point3Type& output) const noexcept
{
    output = Point3Type((k_.Inverse() * input.Homogeneous()));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void FisheyeIntrinsicT<T>::UndistortPoint(const Point2Type& input, Point2Type& output,
                                          const cv::Mat& cv_K) const noexcept
{
    // conver to cv type
    std::vector<cv::Point2f> cv_in, cv_out;
    cv_in.push_back(
        cv::Point2f(static_cast<holo::float32_t>(input.GetX()), static_cast<holo::float32_t>(input.GetY())));

    cv::fisheye::undistortPoints(cv_in, cv_out, cv_k_, cv_d_, cv::Matx33d::eye(), cv_K);

    // convert back to holo type
    output.SetX(cv_out.at(0).x);
    output.SetY(cv_out.at(0).y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void FisheyeIntrinsicT<T>::DistortPoints(const std::vector<Point2Type>& in, std::vector<Point2Type>& out) const noexcept
{
    // K^-1 = [1/fx 0 -cx/fx; 0 1/fy -cy/fy; 0 0 1]
    Matrix33Type k_inv = GetK();
    {
        k_inv(0, 0) = 1.0f / GetK()(0, 0);
        k_inv(0, 2) *= -k_inv(0, 0);
        k_inv(1, 1) = 1.0f / GetK()(1, 1);
        k_inv(1, 2) *= -k_inv(1, 1);
    }

    // distort points
    for (uint64_t i = 0u; i < in.size(); i++)
    {
        // normalization coordinate
        const Point2Type& p_in   = in.at(i);
        const ScalarType  x_in   = p_in.GetX() * k_inv(0u, 0u) + k_inv(0u, 2u);
        const ScalarType  y_in   = p_in.GetY() * k_inv(1u, 1u) + k_inv(1u, 2u);
        const ScalarType  r2     = x_in * x_in + y_in * y_in;
        const ScalarType  r      = std::sqrt(r2);
        const ScalarType  theta  = std::atan(r);
        const ScalarType  theta2 = theta * theta;
        const ScalarType  theta4 = theta2 * theta2;
        const ScalarType  theta6 = theta2 * theta4;
        const ScalarType  theta8 = theta4 * theta4;

        const ScalarType theta_d =
            theta * (1.0 + GetD()(0) * theta2 + GetD()(1) * theta4 + GetD()(2) * theta6 + GetD()(3) * theta8);
        const ScalarType scale = r > 1e-8 ? 1.0 / r : 1.0;
        ScalarType       x_out = theta_d * (x_in * scale);
        ScalarType       y_out = theta_d * (y_in * scale);
        x_out                  = x_out * GetK()(0, 0) + y_out * GetK()(0, 1) + GetK()(0, 2);
        y_out                  = y_out * GetK()(1u, 1u) + GetK()(1u, 2u);
        out.emplace_back(x_out, y_out);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void OmnidirectionalIntrinsicT<T>::SetUnprojectPolynomial(ScalarType a0, ScalarType a1, ScalarType a2, ScalarType a3,
                                                          ScalarType a4) noexcept
{
    unproject_poly_ = {a0, a1, a2, a3, a4};
    computeProjectPoly();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void OmnidirectionalIntrinsicT<T>::computeProjectPoly()
{
    /// @todo(Feng. Li lifeng@holomatic.com 2020-12-18) implementing this function in future.
    throw std::runtime_error("OmnidirectionalIntrinsicT --- calling unimplemented function.");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void OmnidirectionalIntrinsicT<T>::Project(Point3Type const& input, Point2Type& output) const noexcept
{
    ScalarType norm    = std::sqrt(input.GetX() * input.GetX() + input.GetY() * input.GetY());
    ScalarType theta   = std::atan2(-input.GetZ(), norm);
    ScalarType rho     = 0.0;
    ScalarType theta_i = 1.0;

    for (size_t i = 0; i < proj_poly_.size(); ++i)
    {
        rho += theta_i * proj_poly_[i];
        theta_i *= theta;
    }

    ScalarType  inv_norm = 1.0 / norm;
    Vector2Type xn(input.GetX() * inv_norm * rho, input.GetY() * inv_norm * rho);

    output.SetX(xn[0] * c_ + xn[1] * d_ + cx_);
    output.SetY(xn[0] * e_ + xn[1] + cy_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void OmnidirectionalIntrinsicT<T>::Unproject(Point2Type const& input, Point3Type& output) const noexcept
{
    // affine transformation
    ScalarType             inv_scale = 1.0 / (c_ - d_ * e_);
    holo::geometry::Point2 xc(input.GetX() - cx_, input.GetY() - cy_);
    Point2Type             p(inv_scale * (xc.GetX() - d_ * xc.GetY()), inv_scale * (-e_ * xc.GetX() + c_ * xc.GetY()));

    // comput z
    ScalarType phi   = std::sqrt(p.GetX() * p.GetX() + p.GetY() * p.GetY());
    ScalarType phi_i = 1.0;
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

template class PinholeIntrinsicT<float32_t>;
template class PinholeIntrinsicT<float64_t>;

template class FisheyeIntrinsicT<float32_t>;
template class FisheyeIntrinsicT<float64_t>;

template class OmnidirectionalIntrinsicT<float32_t>;
template class OmnidirectionalIntrinsicT<float64_t>;
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
