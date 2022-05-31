/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_base.hpp
 * @brief This header file implement CameraBaseT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-12-10
 */

#ifndef HOLO_COMMON_CAMERA_BASE_HPP_
#define HOLO_COMMON_CAMERA_BASE_HPP_

#include <holo/common/camera_base.h>

namespace holo
{
template <typename T>
CameraBaseT<T>::CameraBaseT(const uint32_t width, const uint32_t height, const Matrix3Type& k, const Vector8Type& d)
  : resolution_width_(width), resolution_height_(height), d_(d)
{
    if (k.GetRows() != 3 || k.GetCols() != 3)
    {
        throw std::runtime_error("Invalid K matrix shape!");
    }
    k_ = k;
    CameraBaseT<T>::computeKInv();
}

template <typename T>
CameraBaseT<T>::CameraBaseT(const Intrinsic& intrinsic) noexcept
  : resolution_width_(intrinsic.GetDimension()[0])
  , resolution_height_(intrinsic.GetDimension()[1])
  , k_(intrinsic.GetK())
  , d_(intrinsic.GetD())
{
    CameraBaseT<T>::computeKInv();
}

template <typename T>
CameraBaseT<T>::~CameraBaseT() noexcept
{
}

template <typename T>
typename CameraBaseT<T>::Point2Type CameraBaseT<T>::Project(const Point3Type& in) const
{
    Vector3Type out = k_ * in.ToVector();

    out = out / out(2);
    return Point2Type(out.GetHead(2));
}

template <typename T>
typename CameraBaseT<T>::Point2Type CameraBaseT<T>::Project(const Point3Type& in, const Matrix3Type& new_k) const
{
    Vector3Type out = new_k * in.ToVector();

    out = out / out(2);
    return Point2Type(out.GetHead(2));
}

// Won't support until MatrixT support well
// template <typename T>
// typename CameraBaseT<T>::MatrixN2 CameraBaseT<T>::Project(const MatrixN3& in) const
// {
//     if (in.GetCols() != 3)
//     {
//         throw std::runtime_error("ERROR: Input matrix shape cols is not 3. Invalid matrix shape!");
//     }

//     if (in.GetRows() == 0)
//     {
//         throw std::runtime_error("ERROR: Empty input matrix!");
//     }

//     MatrixN3 out = (k_ * in.Transpose()).Transpose();
//     for (uint16_t i = 0; i < out.GetRows(); ++i)
//     {
//         MatrixT<T, 1, 3> row = out.GetRow(i) / out(i, 2);
//         out(i, 0)            = row(0, 0);
//         out(i, 1)            = row(0, 1);
//     }

//     return out.GetBlock(0, 0, out.GetRows(), 2);
// }

// template <typename T>
// typename CameraBaseT<T>::MatrixN2 CameraBaseT<T>::Project(const MatrixN3& in, const Matrix3Type& new_k) const
// {
//     if (in.GetCols() != 3)
//     {
//         throw std::runtime_error("ERROR: Input matrix shape cols is not 3. Invalid matrix shape!");
//     }

//     if (in.GetRows() == 0)
//     {
//         throw std::runtime_error("ERROR: Empty input matrix!");
//     }

//     MatrixN3 out = (new_k * in.Transpose()).Transpose();
//     for (uint16_t i = 0; i < out.GetRows(); ++i)
//     {
//         MatrixT<T, 1, 3> row = out.GetRow(i) / out(i, 2);
//         out(i, 0)            = row(0, 0);
//         out(i, 1)            = row(0, 1);
//     }

//     return out.GetBlock(0, 0, out.GetRows(), 2);
// }

template <typename T>
typename CameraBaseT<T>::Point3Type CameraBaseT<T>::Unproject(const Point2Type& in) const
{
    Vector3Type out;
    out(0) = in.GetX();
    out(1) = in.GetY();
    out(2) = static_cast<T>(1.0);

    out = k_inv_ * out;
    out = out / out(2);

    return Point3Type(out);
}

template <typename T>
typename CameraBaseT<T>::Point3Type CameraBaseT<T>::Unproject(const Point2Type& in, const Matrix3Type& new_k_inv) const
{
    Vector3Type out;
    out(0) = in.GetX();
    out(1) = in.GetY();
    out(2) = static_cast<T>(1.0);

    out = new_k_inv * out;
    out = out / out(2);

    return Point3Type(out);
}

// Won't support until MatrixT support well
// template <typename T>
// typename CameraBaseT<T>::MatrixN3 CameraBaseT<T>::Unproject(const MatrixN2& in) const
// {
//     if (in.GetCols() != 2)
//     {
//         throw std::runtime_error("ERROR: Input matrix shape cols is not 2. Invalid matrix shape!");
//     }

//     if (in.GetRows() == 0)
//     {
//         throw std::runtime_error("ERROR: Empty input matrix!");
//     }

//     MatrixN3 out(in.GetRows(), 3);
//     out.SetOne();
//     out.SetBlock(0, 0, in);

//     out = (k_inv_ * out.Transpose()).Transpose();
//     for (uint16_t i = 0; i < out.GetRows(); ++i)
//     {
//         MatrixT<T, 1, 3> row = out.GetRow(i) / out(i, 2);
//         out(i, 0)            = row(0, 0);
//         out(i, 1)            = row(0, 1);
//         out(i, 2)            = row(0, 2);
//     }

//     return out;
// }

// Won't support until MatrixT support well
// template <typename T>
// typename CameraBaseT<T>::MatrixN3 CameraBaseT<T>::Unproject(const MatrixN2& in, const Matrix3Type& new_k_inv) const
// {
//     if (in.GetCols() != 2)
//     {
//         throw std::runtime_error("ERROR: Input matrix shape cols is not 2. Invalid matrix shape!");
//     }

//     if (in.GetRows() == 0)
//     {
//         throw std::runtime_error("ERROR: Empty input matrix!");
//     }

//     MatrixN3 out(in.GetRows(), 3);
//     out.SetOne();
//     out.SetBlock(0, 0, in);

//     out = (new_k_inv * out.Transpose()).Transpose();
//     for (uint16_t i = 0; i < out.GetRows(); ++i)
//     {
//         MatrixT<T, 1, 3> row = out.GetRow(i) / out(i, 2);
//         out(i, 0)            = row(0, 0);
//         out(i, 1)            = row(0, 1);
//         out(i, 2)            = row(0, 2);
//     }

//     return out;
// }

template <typename T>
void CameraBaseT<T>::computeKInv()
{
    k_inv_ = k_.Inverse();
}
}  // namespace holo

#endif  // !HOLO_COMMON_CAMERA_BASE_HPP_
