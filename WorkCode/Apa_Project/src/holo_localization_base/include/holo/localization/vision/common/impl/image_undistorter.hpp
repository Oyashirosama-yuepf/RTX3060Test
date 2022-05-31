/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_undistorter.h
 * @brief image undistorter impl file
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2021-09-26
 */

#ifndef HOLO_LOCALIZATION_VISION_COMMON_IMPL_IMAGE_UNDISTORTER_HPP_
#define HOLO_LOCALIZATION_VISION_COMMON_IMPL_IMAGE_UNDISTORTER_HPP_

#include <holo/localization/vision/common/image_undistorter.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
ImageUndistorterT<IntrinsicBaseType>::ImageUndistorterT(IntrinsicBaseTypePtr const& src_intrinsic_ptr,
                                                        ScalarType const scale, CvMat const& tRs)
  : tRs_(tRs), src_intrinsic_ptr_(src_intrinsic_ptr), has_distortion_(true)
{
    /// check whether the intrisnic is valid
    if (!src_intrinsic_ptr_ ||
        ((src_intrinsic_ptr_->GetModel() != Model::FISHEYE) && (src_intrinsic_ptr_->GetModel() != Model::PINHOLE)))
    {
        LOG(ERROR) << "ImageUndistorterT --- the input source intrinsic is invalid! model: "
                   << (src_intrinsic_ptr_ ? static_cast<uint16_t>(src_intrinsic_ptr_->GetModel()) :
                                            static_cast<uint16_t>(Model::UNKNOWN));
        throw std::runtime_error("ImageUndistorterT --- invalid intrinsic");
    }

    /// generate target intrinsic with source intrinsic and scale
    PinholeIntrinsicType tgt_pinhole;
    tgt_pinhole.SetSensorId(src_intrinsic_ptr_->GetSensorId());
    tgt_pinhole.SetDimension(src_intrinsic_ptr_->GetWidth(), src_intrinsic_ptr_->GetHeight());

    bool_t const is_fisheye = (src_intrinsic_ptr_->GetModel() == Model::FISHEYE);

    Matrix33Type K;

    if (is_fisheye)
    {
        FisheyeIntrinsicType const* src_fisheye = dynamic_cast<FisheyeIntrinsicType const*>(src_intrinsic_ptr_.get());

        if (!src_fisheye)
        {
            LOG(ERROR) << "ImageUndistorterT --- failed to cast source intrinsic to fisheye type";
            throw std::runtime_error("ImageUndistorterT --- failed to cast source intrinsic to pinhole type");
        }

        K = src_fisheye->GetK();
    }
    else
    {
        PinholeIntrinsicType const* src_pinhole = dynamic_cast<PinholeIntrinsicType const*>(src_intrinsic_ptr_.get());

        if (!src_pinhole)
        {
            LOG(ERROR) << "ImageUndistorterT --- failed to cast source intrinsic to pinhole type";
            throw std::runtime_error("ImageUndistorterT --- failed to cast source intrinsic to pinhole type");
        }

        K = src_pinhole->GetK();

        /// there is no distortion if and only if the source intrinsic is PINHOLE and distortion is zero
        has_distortion_ = (src_pinhole->GetD().GetNorm() > holo::EpsilonT<ScalarType>::value);
    }

    tgt_pinhole.SetPrinciplePoint(K(0u, 2u), K(1u, 2u));
    tgt_pinhole.SetFocalLength(scale * K(0u, 0u), scale * K(1u, 1u));
    tgt_intrinsic_ptr_ = std::make_shared<PinholeIntrinsicType>(tgt_pinhole);

    /// generate map table
    std::tie(mapx_, mapy_) = generateMapTable(src_intrinsic_ptr_, tgt_intrinsic_ptr_, tRs_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
ImageUndistorterT<IntrinsicBaseType>::ImageUndistorterT(IntrinsicBaseTypePtr const& src_intrinsic_ptr,
                                                        IntrinsicBaseTypePtr const& tgt_intrinsic_ptr, CvMat const& tRs)
  : tRs_(tRs), src_intrinsic_ptr_(src_intrinsic_ptr), tgt_intrinsic_ptr_(tgt_intrinsic_ptr), has_distortion_(true)
{
    /// check whether the intrinsic is valid
    if (!src_intrinsic_ptr_ || !tgt_intrinsic_ptr_)
    {
        LOG(ERROR) << "ImageUndistorterT --- the input source intrinsic or target intrinsic is invalid!";
        throw std::runtime_error("ImageUndistorterT --- invalid intrinsic");
    }

    /// there is no distortion if and only if the source intrinsic is PINHOLE and distortion is zero
    if (src_intrinsic_ptr_->GetModel() == Model::PINHOLE)
    {
        PinholeIntrinsicType const* src_pinhole = dynamic_cast<PinholeIntrinsicType const*>(src_intrinsic_ptr_.get());

        if (!src_pinhole)
        {
            LOG(ERROR) << "ImageUndistorterT --- failed to cast source intrinsic to pinhole type";
            throw std::runtime_error("ImageUndistorterT --- failed to cast source intrinsic to pinhole type");
        }

        has_distortion_ = (src_pinhole->GetD().GetNorm() > holo::EpsilonT<ScalarType>::value);
    }

    /// generate map table
    std::tie(mapx_, mapy_) = generateMapTable(src_intrinsic_ptr_, tgt_intrinsic_ptr_, tRs_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
ImageUndistorterT<IntrinsicBaseType>::ImageUndistorterT(CvMat const& mapx, CvMat const& mapy,
                                                        IntrinsicBaseTypePtr const& src_intrinsic_ptr,
                                                        IntrinsicBaseTypePtr const& tgt_intrinsic_ptr, CvMat const& tRs)
  : mapx_(mapx)
  , mapy_(mapy)
  , tRs_(tRs)
  , src_intrinsic_ptr_(src_intrinsic_ptr)
  , tgt_intrinsic_ptr_(tgt_intrinsic_ptr)
  , has_distortion_(true)
{
    /// 1. check mapx is not empty
    /// 2. mapx size equals mapy size if mapy is not empty
    bool_t const is_good_size = (mapx_.cols != 0u && mapx_.rows != 0u) &&
                                (mapy_.cols != 0u ? ((mapx_.cols == mapy_.cols) && (mapx_.rows == mapy_.rows)) : true);
    bool_t const is_good_type =
        ((mapx_.type() == CV_32FC2) || ((mapx_.type() == CV_16SC2) && (mapy_.type() == CV_16UC1)) ||
         ((mapx_.type() == CV_32FC1) && (mapy_.type() == CV_32FC1)));

    if (!is_good_size || !is_good_type)
    {
        LOG(ERROR) << "ImageUndistorterT --- the input map table is invalid! is_good_size: " << is_good_size
                   << ", is_good_type: " << is_good_type;
        throw std::runtime_error("ImageUndistorterT --- invalid map table");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
ImageUndistorterT<IntrinsicBaseType>::~ImageUndistorterT() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
typename ImageUndistorterT<IntrinsicBaseType>::IntrinsicBaseTypePtr
ImageUndistorterT<IntrinsicBaseType>::GetSourceIntrinsic() const
{
    return src_intrinsic_ptr_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
typename ImageUndistorterT<IntrinsicBaseType>::IntrinsicBaseTypePtr
ImageUndistorterT<IntrinsicBaseType>::GetTargetIntrinsic() const
{
    return tgt_intrinsic_ptr_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
std::pair<typename ImageUndistorterT<IntrinsicBaseType>::CvMat, typename ImageUndistorterT<IntrinsicBaseType>::CvMat>
ImageUndistorterT<IntrinsicBaseType>::GetMap() const
{
    return std::make_pair(mapx_, mapy_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
typename ImageUndistorterT<IntrinsicBaseType>::CvMat const& ImageUndistorterT<IntrinsicBaseType>::GetRotation() const
{
    return tRs_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
void ImageUndistorterT<IntrinsicBaseType>::Undistort(const Mat& in, Mat& out) const noexcept
{
    Undistort(in.GetCvType(), out.GetCvType());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
void ImageUndistorterT<IntrinsicBaseType>::Undistort(const CvMat& in, CvMat& out) const noexcept
{
    if (!has_distortion_)
    {
        out = in;
        LOG(WARNING) << "ImageUndistorterT --- there is not distortion, do nothing";
        return;
    }

    cv::remap(in, out, mapx_, mapy_, cv::INTER_LINEAR, cv::BORDER_CONSTANT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
void ImageUndistorterT<IntrinsicBaseType>::UndistortPoints(const std::vector<Point2Type>& in,
                                                           std::vector<Point2Type>&       out) const
{
    if (!has_distortion_)
    {
        out = in;
        LOG(WARNING) << "ImageUndistorterT --- there is not distortion, do nothing";
        return;
    }

    if (!src_intrinsic_ptr_ || !tgt_intrinsic_ptr_)
    {
        LOG(ERROR) << "ImageUndistorterT --- please set source and target intrinsic if UndistortPoints is needed!!!";
        throw std::runtime_error("UndistortPoints is called but source or target intrinsic is not set");
    }

    out.clear();
    out.reserve(in.size());

    for (Point2Type const& distorted_point : in)
    {
        /// Step1: unproject distorted point to get 3d ray in source camera frame
        Point3Type source_ray3d;
        src_intrinsic_ptr_->Unproject(distorted_point, source_ray3d);

        /// Step2: rotate 3d ray from source camera frame to target frame
        CvMat cv_source_ray3d(3u, 1u, CV_32F);
        cv_source_ray3d.at<float32_t>(0u, 0u) = static_cast<float32_t>(source_ray3d.GetX());
        cv_source_ray3d.at<float32_t>(1u, 0u) = static_cast<float32_t>(source_ray3d.GetY());
        cv_source_ray3d.at<float32_t>(2u, 0u) = static_cast<float32_t>(source_ray3d.GetZ());
        CvMat cv_target_ray3d(3u, 1u, CV_32F);
        cv_target_ray3d = tRs_ * cv_source_ray3d;

        /// Step3: project 3d ray to target image
        Point3Type target_ray3d(cv_target_ray3d.at<float32_t>(0u, 0u), cv_target_ray3d.at<float32_t>(1u, 0u),
                                cv_target_ray3d.at<float32_t>(2u, 0u));
        Point2Type undistorted_point;
        tgt_intrinsic_ptr_->Project(target_ray3d, undistorted_point);
        out.emplace_back(undistorted_point);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
void ImageUndistorterT<IntrinsicBaseType>::UndistortPoints(const std::vector<CvPoint2f>& in,
                                                           std::vector<CvPoint2f>&       out) const
{
    if (!has_distortion_)
    {
        out = in;
        LOG(WARNING) << "ImageUndistorterT --- there is not distortion, do nothing";
        return;
    }

    if (!src_intrinsic_ptr_ || !tgt_intrinsic_ptr_)
    {
        LOG(ERROR) << "ImageUndistorterT --- please set source and target intrinsic if UndistortPoints is needed!!!";
        throw std::runtime_error("UndistortPoints is called but source or target intrinsic is not set");
    }

    /// Step1: convert input point from cv to holo
    std::vector<Point2Type> holo_in;
    holo_in.reserve(in.size());

    for (CvPoint2f const& cv_distorted_point : in)
    {
        holo_in.emplace_back(Point2Type(cv_distorted_point.x, cv_distorted_point.y));
    }

    /// Step2: undistort points
    std::vector<Point2Type> holo_out;
    holo_out.reserve(holo_in.size());
    UndistortPoints(holo_in, holo_out);

    /// Step3: convert form holo to cv type
    out.clear();
    out.reserve(holo_out.size());

    for (Point2Type const& holo_undistorted_point : holo_out)
    {
        out.emplace_back(CvPoint2f(static_cast<float32_t>(holo_undistorted_point.GetX()),
                                   static_cast<float32_t>(holo_undistorted_point.GetY())));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
std::pair<typename ImageUndistorterT<IntrinsicBaseType>::CvMat, typename ImageUndistorterT<IntrinsicBaseType>::CvMat>
ImageUndistorterT<IntrinsicBaseType>::GenerateMapTable(IntrinsicBaseTypePtr const& src_intrinsic_ptr,
                                                       IntrinsicBaseTypePtr const& tgt_intrinsic_ptr, CvMat const& tRs)
{
    uint16_t const width  = tgt_intrinsic_ptr->GetWidth();
    uint16_t const height = tgt_intrinsic_ptr->GetHeight();
    CvMat          mapx(height, width, CV_32F);
    CvMat          mapy(height, width, CV_32F);
    CvMat          sRt(3u, 3u, CV_32F);
    (void)cv::invert(tRs, sRt);

    for (uint16_t row = 0u; row < height; row++)
    {
        for (uint16_t col = 0u; col < width; col++)
        {
            /// Step1: unproject target point to get 3d ray in target camera frame
            Point3Type target_ray3d;
            tgt_intrinsic_ptr->Unproject(Point2Type(col, row), target_ray3d);

            /// Step2: rotate 3d ray from target camera frame to source frame
            CvMat cv_target_ray3d(3u, 1u, CV_32F);
            cv_target_ray3d.at<float32_t>(0u, 0u) = static_cast<float32_t>(target_ray3d.GetX());
            cv_target_ray3d.at<float32_t>(1u, 0u) = static_cast<float32_t>(target_ray3d.GetY());
            cv_target_ray3d.at<float32_t>(2u, 0u) = static_cast<float32_t>(target_ray3d.GetZ());
            CvMat cv_source_ray3d(3u, 1u, CV_32F);
            cv_source_ray3d = sRt * cv_target_ray3d;

            /// Step3: project 3d ray to source image
            Point3Type source_ray3d(cv_source_ray3d.at<float32_t>(0u, 0u), cv_source_ray3d.at<float32_t>(1u, 0u),
                                    cv_source_ray3d.at<float32_t>(2u, 0u));
            Point2Type distorted_point;
            src_intrinsic_ptr->Project(source_ray3d, distorted_point);
            mapx.at<float32_t>(row, col) = static_cast<float32_t>(distorted_point.GetX());
            mapy.at<float32_t>(row, col) = static_cast<float32_t>(distorted_point.GetY());
        }
    }

    return std::make_pair(mapx, mapy);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
std::pair<typename ImageUndistorterT<IntrinsicBaseType>::CvMat, typename ImageUndistorterT<IntrinsicBaseType>::CvMat>
ImageUndistorterT<IntrinsicBaseType>::generateMapTable(IntrinsicBaseTypePtr const& src_intrinsic_ptr,
                                                       IntrinsicBaseTypePtr const& tgt_intrinsic_ptr,
                                                       CvMat const&                tRs) const
{
    if ((src_intrinsic_ptr->GetModel() == Model::FISHEYE || src_intrinsic_ptr->GetModel() == Model::PINHOLE) &&
        tgt_intrinsic_ptr->GetModel() == Model::PINHOLE)
    {
        PinholeIntrinsicType const* tgt_pinhole = dynamic_cast<PinholeIntrinsicType const*>(tgt_intrinsic_ptr.get());

        if (!tgt_pinhole)
        {
            LOG(ERROR) << "ImageUndistorterT --- failed to cast target intrinsic to pinhole type";
            throw std::runtime_error("ImageUndistorterT --- failed to cast target intrinsic to pinhole type");
        }

        if (tgt_pinhole->GetD().GetNorm() < holo::EpsilonT<ScalarType>::value)
        {
            bool_t const is_fisheye = (src_intrinsic_ptr->GetModel() == Model::FISHEYE);

            if (is_fisheye)
            {
                FisheyeIntrinsicType const* src_fisheye =
                    dynamic_cast<FisheyeIntrinsicType const*>(src_intrinsic_ptr.get());

                if (!src_fisheye)
                {
                    LOG(ERROR) << "ImageUndistorterT --- failed to cast source intrinsic to fisheye type";
                    throw std::runtime_error("ImageUndistorterT --- failed to cast source intrinsic to fisheye type");
                }

                return generateFisheyeMapTable(*src_fisheye, *tgt_pinhole, tRs);
            }
            else
            {
                PinholeIntrinsicType const* src_pinhole =
                    dynamic_cast<PinholeIntrinsicType const*>(src_intrinsic_ptr.get());

                if (!src_pinhole)
                {
                    LOG(ERROR) << "ImageUndistorterT --- failed to cast source intrinsic to pinhole type";
                    throw std::runtime_error("ImageUndistorterT --- failed to cast source intrinsic to pinhole type");
                }

                return generatePinholeMapTable(*src_pinhole, *tgt_pinhole, tRs);
            }
        }
    }

    CvMat mapx_float32;
    CvMat mapy_float32;
    std::tie(mapx_float32, mapy_float32) = GenerateMapTable(src_intrinsic_ptr, tgt_intrinsic_ptr, tRs);
    CvMat mapx;
    CvMat mapy;
    cv::convertMaps(mapx_float32, mapy_float32, mapx, mapy, CV_16SC2);
    return std::make_pair(mapx, mapy);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
std::pair<typename ImageUndistorterT<IntrinsicBaseType>::CvMat, typename ImageUndistorterT<IntrinsicBaseType>::CvMat>
ImageUndistorterT<IntrinsicBaseType>::generateFisheyeMapTable(FisheyeIntrinsicType const& src_intrinsic,
                                                              PinholeIntrinsicType const& tgt_intrinsic,
                                                              CvMat const&                tRs) const
{
    /// Step1: convert source camera matrix from holo to cv
    Matrix33Type const holo_K = src_intrinsic.GetK();
    CvMat              cv_K(3u, 3u, CV_32F);
    constructK(holo_K, cv_K);

    /// Step2: convert source distortion coefficients from holo to cv
    typename FisheyeIntrinsicType::Vector4Type const holo_D = src_intrinsic.GetD();
    CvMat                                            cv_D(4u, 1u, CV_32F);

    for (uint8_t row = 0u; row < 4u; row++)
    {
        cv_D.at<float32_t>(row) = static_cast<float32_t>(holo_D(row));
    }

    /// Step3: convert target camera matrix from holo to cv
    Matrix33Type const new_holo_K = tgt_intrinsic.GetK();
    CvMat              new_cv_K(3u, 3u, CV_32F);
    constructK(new_holo_K, new_cv_K);

    /// Step4: convert target image size form holo to cv
    CvSize cv_size(tgt_intrinsic.GetWidth(), tgt_intrinsic.GetHeight());

    /// Step5: generate map table
    CvMat mapx, mapy;

    try
    {
        cv::fisheye::initUndistortRectifyMap(cv_K, cv_D, tRs, new_cv_K, cv_size, CV_16SC2, mapx, mapy);
    }
    catch (std::exception const& e)
    {
        LOG(ERROR) << "ImageUndistorterT --- failed to generate map table! error: " << e.what();
        throw std::runtime_error(e.what());
    }

    return std::make_pair(mapx, mapy);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
std::pair<typename ImageUndistorterT<IntrinsicBaseType>::CvMat, typename ImageUndistorterT<IntrinsicBaseType>::CvMat>
ImageUndistorterT<IntrinsicBaseType>::generatePinholeMapTable(PinholeIntrinsicType const& src_intrinsic,
                                                              PinholeIntrinsicType const& tgt_intrinsic,
                                                              CvMat const&                tRs) const
{
    /// Step1: convert source camera matrix from holo to cv
    Matrix33Type const holo_K = src_intrinsic.GetK();
    CvMat              cv_K(3u, 3u, CV_32F);
    constructK(holo_K, cv_K);

    /// Step2: convert source distortion coefficients from holo to cv
    typename PinholeIntrinsicType::Vector5Type const holo_D = src_intrinsic.GetD();
    CvMat                                            cv_D(5u, 1u, CV_32F);

    for (uint8_t row = 0u; row < 5u; row++)
    {
        cv_D.at<float32_t>(row) = static_cast<float32_t>(holo_D(row));
    }

    /// Step3: convert target camera matrix from holo to cv
    Matrix33Type const new_holo_K = tgt_intrinsic.GetK();
    CvMat              new_cv_K(3u, 3u, CV_32F);
    constructK(new_holo_K, new_cv_K);

    /// Step4: convert target image size form holo to cv
    CvSize cv_size(tgt_intrinsic.GetWidth(), tgt_intrinsic.GetHeight());

    /// Step5: generate map table
    CvMat mapx, mapy;

    try
    {
        cv::initUndistortRectifyMap(cv_K, cv_D, tRs, new_cv_K, cv_size, CV_16SC2, mapx, mapy);
    }
    catch (std::exception const& e)
    {
        LOG(ERROR) << "ImageUndistorterT --- failed to generate map table! error: " << e.what();
        throw std::runtime_error(e.what());
    }

    return std::make_pair(mapx, mapy);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename IntrinsicBaseType>
void ImageUndistorterT<IntrinsicBaseType>::constructK(Matrix33Type const& holo_K, CvMat& cv_K) const
{
    for (uint8_t row = 0u; row < 3u; row++)
    {
        for (uint8_t col = 0u; col < 3u; col++)
        {
            cv_K.at<float32_t>(row, col) = static_cast<float32_t>(holo_K(row, col));
        }
    }
}

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_COMMON_IMPL_IMAGE_UNDISTORTER_HPP_
