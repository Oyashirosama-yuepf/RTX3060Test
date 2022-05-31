/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_undistorter.h
 * @brief image undistorter header file
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2021-09-26
 */

#ifndef HOLO_LOCALIZATION_VISION_COMMON_IMAGE_UNDISTORTER_H_
#define HOLO_LOCALIZATION_VISION_COMMON_IMAGE_UNDISTORTER_H_

#include <memory>

#include <holo/localization/common/types.h>
#include <holo/localization/vision/common/mat.h>

namespace holo
{
namespace localization
{
/**
 * @brief image undistorter class
 *
 * @tparam IntrinsicBaseType type of the intrinsic base
 * @details the class aims at accelerating the image undistortion speed, it undistorts points/image(undistorted by
 * source intrinsic) to points/image with target intrinsic
 * @ref https://docs.opencv.org/3.3.1/da/d54/group__imgproc__transform.html
 */
template <typename IntrinsicBaseType>
class ImageUndistorterT
{
public:
    /**
     * @brief handy tyepdef
     *
     */
    using ScalarType                   = typename IntrinsicBaseType::ScalarType;
    using Point2Type                   = typename IntrinsicBaseType::Point2Type;
    using Point3Type                   = typename IntrinsicBaseType::Point3Type;
    using Model                        = typename IntrinsicBaseType::Model;
    using PinholeIntrinsicType         = holo::common::PinholeIntrinsicT<ScalarType>;
    using FisheyeIntrinsicType         = holo::common::FisheyeIntrinsicT<ScalarType>;
    using Matrix33Type                 = typename FisheyeIntrinsicType::Matrix33Type;
    using CvPoint2f                    = cv::Point2f;
    using CvMat                        = cv::Mat;
    using CvSize                       = cv::Size;

    /**
     * @brief smart pointer
     *
     */
    using IntrinsicBaseTypePtr = std::shared_ptr<IntrinsicBaseType>;
    using Ptr                  = std::shared_ptr<ImageUndistorterT<IntrinsicBaseType>>;
    using ConstPtr             = std::shared_ptr<const ImageUndistorterT<IntrinsicBaseType>>;

    /**
     * @brief disable default constructor
     */
    ImageUndistorterT() = delete;

    /**
     * @brief disable copy constructor
     *
     */
    ImageUndistorterT(const ImageUndistorterT&) = delete;

    /**
     * @brief copy assignment operator
     *
     */
    ImageUndistorterT& operator=(ImageUndistorterT const&)=default;

    /**
     * @brief construct with source intrinsic parameter
     *
     * @details ratio would "zoom in" or "zoom out" the whole image
     * @param[in] src_intrinsic_ptr pointer of source intrinsic
     * @param[in] scale new ratio compared to original image
     * @param[in] tRs rotation of source intrinsic camera in target intrinsic camera
     *
     * @throw std::runtime_error if the model of source intrinsic is not PinHole or Fisheye
     * @throw std::bad_alloc if mapx_ or mapy_ fails to initialize
     */
    ImageUndistorterT(IntrinsicBaseTypePtr const& src_intrinsic_ptr, ScalarType const scale = 1.0,
                      CvMat const& tRs = CvMat::eye(3u, 3u, CV_32F));

    /**
     * @brief construct with source and target intrinsic
     *
     * @param[in] src_intrinsic_ptr pointer of source intrinsic
     * @param[in] tgt_intrinsic_ptr pointer of target intrinsic
     * @param[in] tRs rotation of source intrinsic camera in target intrinsic camera
     *
     * @throw std::runtime_error if src_intrinsic_ptr or tgt_intrinsic_ptr invalid
     * @throw std::bad_alloc if mapx_ or mapy_ fails to initialize
     */
    ImageUndistorterT(IntrinsicBaseTypePtr const& src_intrinsic_ptr, IntrinsicBaseTypePtr const& tgt_intrinsic_ptr,
                      CvMat const& tRs = CvMat::eye(3u, 3u, CV_32F));

    /**
     * @brief construct with map table and optional source/target intrinsic
     * @note UndistortPoints function is invalid if source or target intrinsic is nullptr
     *
     * @param[in] mapx map table for cv::remap
     * @param[in] mapy map table for cv::remap
     * @param[in] src_intrinsic_ptr pointer of source intrinsic
     * @param[in] tgt_intrinsic_ptr pointer of target intrinsic
     * @param[in] tRs rotation of source intrinsic camera in target intrinsic camera
     *
     * @throw std::runtime_error if mapx or mapy invalid
     */
    ImageUndistorterT(CvMat const& mapx, CvMat const& mapy, IntrinsicBaseTypePtr const& src_intrinsic_ptr = nullptr,
                      IntrinsicBaseTypePtr const& tgt_intrinsic_ptr = nullptr,
                      CvMat const&                tRs               = CvMat::eye(3u, 3u, CV_32F));

    /**
     * @brief destructor
     *
     * @throw std::bad_alloc if matx_ or maty_ fails to release
     */
    ~ImageUndistorterT() noexcept;

    /**
     * @brief get source intrinsic
     *
     * @return pointer of source intrinsic
     */
    IntrinsicBaseTypePtr GetSourceIntrinsic() const;

    /**
     * @brief get target intrinsic
     *
     * @return pointer of target intrinsic
     */
    IntrinsicBaseTypePtr GetTargetIntrinsic() const;

    /**
     * @brief get map table
     *
     * @return std::pair<mapx, mapy>
     */
    std::pair<CvMat, CvMat> GetMap() const;

    /**
     * @brief get rotation of source intrinsic camera in target intrinsic camera
     *
     * @return 3*3 rotation matrix
     */
    CvMat const& GetRotation() const;

    /**
     * @brief main undistort function
     *
     * @param[in] in original image corresponding to source intrinsic
     * @param[in][out] out undistorted image corresponding to target intrinsic
     */
    void Undistort(const Mat& in, Mat& out) const noexcept;

    /**
     * @brief main undistort function
     *
     * @param[in] in original image corresponding to source intrinsic
     * @param[in][out] out undistorted image corresponding to target intrinsic
     */
    void Undistort(const CvMat& in, CvMat& out) const noexcept;

    /**
     * @brief undistort points
     *
     * @param[in] in distorted points corresponding to source intrinsic
     * @param[in][out] out undistorted points corresponding to target intrinsic
     */
    void UndistortPoints(const std::vector<Point2Type>& in, std::vector<Point2Type>& out) const;

    /**
     * @brief undistort points
     *
     * @param[in] in distorted points corresponding to source intrinsic
     * @param[in][out] out undistorted points corresponding to target intrinsic
     */
    void UndistortPoints(const std::vector<CvPoint2f>& in, std::vector<CvPoint2f>& out) const;

    /**
     * @brief generate map table with source and target intrinsic
     *
     * @param[in] src_intrinsic_ptr pointer of source intrinsic
     * @param[in] tgt_intrinsic_ptr pointer of target intrinsic
     * @param[in] tRs rotation of source intrinsic camera in target intrinsic camera
     *
     * @return map table std::pair<CvMat(CV_32FC1), CvMat(CV_32FC1)>
     */
    static std::pair<CvMat, CvMat> GenerateMapTable(IntrinsicBaseTypePtr const& src_intrinsic_ptr,
                                                    IntrinsicBaseTypePtr const& tgt_intrinsic_ptr,
                                                    CvMat const&                tRs = CvMat::eye(3u, 3u, CV_32F));

protected:
    /**
     * @brief generate map table with source and target intrinsic
     *
     * @param[in] src_intrinsic_ptr pointer of source intrinsic
     * @param[in] tgt_intrinsic_ptr pointer of target intrinsic
     * @param[in] tRs rotation of source intrinsic camera in target intrinsic camera
     *
     * @return map table std::pair<CvMat(CV_16SC2), CvMat(CV_16UC1)>
     */
    std::pair<CvMat, CvMat> generateMapTable(IntrinsicBaseTypePtr const& src_intrinsic_ptr,
                                             IntrinsicBaseTypePtr const& tgt_intrinsic_ptr,
                                             CvMat const&                tRs = CvMat::eye(3u, 3u, CV_32F)) const;

    /**
     * @brief generate map table with source fisheye intnrisnic and target pinhole intrisnic(without distortion)
     *
     * @param[in] src_intrinsic source intrinsic(with distortion)
     * @param[in] tgt_intrinsic target intrisnic(without distortion)
     * @param[in] tRs rotation of source intrinsic camera in target intrinsic camera
     *
     * @return map table std::pair<CvMat(CV_16SC2), CvMat(CV_16UC1)>
     */
    std::pair<CvMat, CvMat> generateFisheyeMapTable(FisheyeIntrinsicType const& src_intrinsic,
                                                    PinholeIntrinsicType const& tgt_intrinsic, CvMat const& tRs) const;

    /**
     * @brief generate map table with source pinhole intnrisnic and target pinhole intrisnic(without distortion)
     *
     * @param[in] src_intrinsic source intrinsic(with distortion)
     * @param[in] tgt_intrinsic target intrisnic(without distortion)
     * @param[in] tRs rotation of source intrinsic camera in target intrinsic camera
     *
     * @return map table std::pair<CvMat(CV_16SC2), CvMat(CV_16UC1)>
     */
    std::pair<CvMat, CvMat> generatePinholeMapTable(PinholeIntrinsicType const& src_intrinsic,
                                                    PinholeIntrinsicType const& tgt_intrinsic, CvMat const& tRs) const;

    /**
     * @brief convert holo matrix to cv matrix
     *
     * @param[in] holo_K camera matrix in holo type
     * @param[in][out] cv_K camera matrix in holo type
     */
    void constructK(Matrix33Type const& holo_K, CvMat& cv_K) const;

private:
    CvMat                mapx_;  ///< map table for cv::remap with type CV_16SC2
    CvMat                mapy_;  ///< map table for cv::remap with type CV_16UC1
    CvMat                tRs_;   ///< rotation of camera with source intrinsic in camera with target intrinsic CV32FC1
    IntrinsicBaseTypePtr src_intrinsic_ptr_;  ///< base pointer of source intrinsic
    IntrinsicBaseTypePtr tgt_intrinsic_ptr_;  ///< base pointer of target intrinsic
    bool_t has_distortion_;  ///< whether the source intrinsic has distortion, false -> Undistort and UndistortPoints do
                             ///< nothing

};  // class ImageUndistorterT
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_COMMON_IMAGE_UNDISTORTER_H_
