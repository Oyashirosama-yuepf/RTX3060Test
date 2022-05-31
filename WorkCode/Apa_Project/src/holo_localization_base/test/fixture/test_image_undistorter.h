/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_image_undistortion.cpp
 * @brief test functions for image undistortion
 * @author duyanwei@holomatic.com
 * @date 2019-12-13
 */

/**
 * @brief prepare data
 */
using ScalarType              = typename ImageUndistorterType::ScalarType;
using Point2                   = typename ImageUndistorterType::Point2Type;
using Point3                   = typename ImageUndistorterType::Point3Type;
using Model                   = typename ImageUndistorterType::Model;
using PinholeIntrinsic         = typename ImageUndistorterType::PinholeIntrinsicType;
using FisheyeIntrinsic         = typename ImageUndistorterType::FisheyeIntrinsicType;
using CameraIntrinsicBaseType  = typename ImageUndistorterType::FisheyeIntrinsicType::Base;
using OmnidirectionalIntrinsic = holo::common::OmnidirectionalIntrinsicT<ScalarType>;
using Matrix33Type            = typename ImageUndistorterType::Matrix33Type;
using CvMatType               = typename ImageUndistorterType::CvMat;
using CvPoint2f               = typename ImageUndistorterType::CvPoint2f;

class ImageUndistorterFixture : public ::testing::Test
{
public:
    /**
     * @brief constructor
     */
    ImageUndistorterFixture()
    {
    }

    /**
     * @brief destructor
     */
    virtual ~ImageUndistorterFixture() noexcept
    {
    }

    /**
     * @brief setup data
     */
    virtual void SetUp()
    {
        fx_     = 500.0;
        fy_     = 500.0;
        cx_     = 500.0;
        cy_     = 500.0;
        width_  = 1000.0;
        height_ = 1000.0;
        skew_   = 0.0;
        scale_  = 0.8;
        tRs_    = CvMatType::eye(3u, 3u, CV_32FC1);
        pinhole_without_distortion_cx_ = cx_ + 10u;
        pinhole_without_distortion_cy_ = cy_ + 10u;
        pinhole_without_distortion_width_  = width_ + 20u;
        pinhole_without_distortion_height_ = height_ + 20u;

        PinholeIntrinsic              pinhole_with_distortion;
        PinholeIntrinsic::Vector5Type pinholeD(0.2, 0.01, 0.01, 0.02, 0.004);
        pinhole_with_distortion.SetFocalLength(fx_, fy_);
        pinhole_with_distortion.SetPrinciplePoint(cx_, cy_);
        pinhole_with_distortion.SetDimension(width_, height_);
        pinhole_with_distortion.SetSkew(skew_);
        pinhole_with_distortion.SetDistortionParameter(pinholeD(0u), pinholeD(1u), pinholeD(2u), pinholeD(3u),
                                                       pinholeD(4u));
        pinhole_with_distortion_ptr_ = std::make_shared<PinholeIntrinsic>(pinhole_with_distortion);

        PinholeIntrinsic pinhole_without_distortion;
        pinhole_without_distortion.SetFocalLength(fx_, fy_);
        pinhole_without_distortion.SetPrinciplePoint(pinhole_without_distortion_cx_, pinhole_without_distortion_cy_);
        pinhole_without_distortion.SetDimension(pinhole_without_distortion_width_, pinhole_without_distortion_height_);
        pinhole_without_distortion.SetSkew(skew_);
        pinhole_without_distortion_ptr_ = std::make_shared<PinholeIntrinsic>(pinhole_without_distortion);

        FisheyeIntrinsic              fisheye_with_distortion;
        FisheyeIntrinsic::Vector4Type fisheyeD(0.2, 0.02, 0.02, 0.01);
        fisheye_with_distortion.SetFocalLength(fx_, fy_);
        fisheye_with_distortion.SetPrinciplePoint(cx_, cy_);
        fisheye_with_distortion.SetDimension(width_, height_);
        fisheye_with_distortion.SetSkew(skew_);
        fisheye_with_distortion.SetDistortionParameter(fisheyeD(0u), fisheyeD(1u), fisheyeD(2u), fisheyeD(3u));
        fisheye_with_distortion_ptr_ = std::make_shared<FisheyeIntrinsic>(fisheye_with_distortion);

        OmnidirectionalIntrinsic ocam;
        ocam_ptr_ = std::make_shared<OmnidirectionalIntrinsic>(ocam);
    }

    /**
     * @brief Teardowm data
     *
     */
    virtual void TearDown()
    {
    }

protected:
    ScalarType                                    fx_;
    ScalarType                                    fy_;
    ScalarType                                    cx_;
    ScalarType                                    cy_;
    ScalarType                                    width_;
    ScalarType                                    height_;
    ScalarType                                    skew_;
    ScalarType                                    scale_;
    CvMatType                                     tRs_;
    ScalarType                                    pinhole_without_distortion_cx_;
    ScalarType                                    pinhole_without_distortion_cy_;
    ScalarType                                    pinhole_without_distortion_width_;
    ScalarType                                    pinhole_without_distortion_height_;
    std::shared_ptr<PinholeIntrinsic>             pinhole_with_distortion_ptr_;
    std::shared_ptr<PinholeIntrinsic>             pinhole_without_distortion_ptr_;
    std::shared_ptr<FisheyeIntrinsic>             fisheye_with_distortion_ptr_;
    std::shared_ptr<OmnidirectionalIntrinsic>     ocam_ptr_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImageUndistorterFixture, Constructor)
{
    /// constructor1
    ImageUndistorterType image_undistorter1(pinhole_with_distortion_ptr_);
    ImageUndistorterType image_undistorter2(pinhole_with_distortion_ptr_, 1.0, tRs_);
    ImageUndistorterType image_undistorter3(fisheye_with_distortion_ptr_);
    ImageUndistorterType image_undistorter4(fisheye_with_distortion_ptr_, 1.0, tRs_);

    /// constructor2
    ImageUndistorterType image_undistorter5(fisheye_with_distortion_ptr_, pinhole_without_distortion_ptr_);
    ImageUndistorterType image_undistorter6(pinhole_with_distortion_ptr_, pinhole_without_distortion_ptr_);
    ImageUndistorterType image_undistorter7(pinhole_without_distortion_ptr_, pinhole_with_distortion_ptr_);

    /// constuctor3
    CvMatType mapx;
    CvMatType mapy;
    std::tie(mapx, mapy) = image_undistorter7.GetMap();
    ImageUndistorterType image_undistorter8(mapx, mapy, pinhole_without_distortion_ptr_, pinhole_with_distortion_ptr_,
                                            tRs_);
    ImageUndistorterType image_undistorter9(mapx, mapy);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImageUndistorterFixture, ConstructorThrow)
{
    /* check constructor1 */
    ASSERT_THROW(ImageUndistorterType(nullptr), std::runtime_error);
    ASSERT_THROW(ImageUndistorterType(ocam_ptr_, 1.0), std::runtime_error);

    /* check constructor2 */
    ASSERT_THROW(ImageUndistorterType(nullptr, nullptr), std::runtime_error);
    ASSERT_THROW(ImageUndistorterType(fisheye_with_distortion_ptr_, nullptr), std::runtime_error);

    /* check constructor3 */
    ASSERT_THROW(ImageUndistorterType(CvMatType(), CvMatType()), std::runtime_error);
    ASSERT_THROW(ImageUndistorterType(CvMatType(3u, 3u, CV_32FC1), CvMatType(2u, 2u, CV_32FC1)), std::runtime_error);
    ASSERT_THROW(ImageUndistorterType(CvMatType(3u, 3u, CV_32FC3), CvMatType()), std::runtime_error);
    ASSERT_THROW(ImageUndistorterType(CvMatType(3u, 3u, CV_16SC2), CvMatType(3u, 3u, CV_16SC2)), std::runtime_error);
    ASSERT_THROW(ImageUndistorterType(CvMatType(3u, 3u, CV_32FC1), CvMatType(3u, 3u, CV_32FC2)), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImageUndistorterFixture, UndistortNoDistortion)
{
    ImageUndistorterType image_undistorter(pinhole_without_distortion_ptr_);
    CvMatType            in(height_, width_, CV_8UC1);
    CvMatType            out(height_ + 20u, width_ + 20u, CV_8UC1);
    image_undistorter.Undistort(in, out);

    /* check result */
    ASSERT_EQ(in.cols, out.cols);
    ASSERT_EQ(in.rows, out.rows);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImageUndistorterFixture, UndistortPointsNoDistortion)
{
    ImageUndistorterType   image_undistorter(pinhole_without_distortion_ptr_);
    std::vector<CvPoint2f> in({CvPoint2f(1.0, 1.0), CvPoint2f(1000.0, 1000.0)});
    std::vector<CvPoint2f> out;
    image_undistorter.UndistortPoints(in, out);

    /* check result */
    ASSERT_EQ(in.size(), out.size());

    for (uint16_t i = 0u; i < in.size(); i++)
    {
        ASSERT_EQ(in.at(i).x, out.at(i).x);
        ASSERT_EQ(in.at(i).y, out.at(i).y);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImageUndistorterFixture, UndistortNormal)
{
    ///< points in pinhole_without_distortion_ptr_
    std::vector<Point2> undistorted_points({Point2(250.0, 250.0), Point2(500.0, 500.0)});

    ///< project to pinhole_with_distortion_ptr_
    std::vector<Point2> distorted_points;
    for (Point2 const& undistorted_point : undistorted_points)
    {
        Point3 ray3d;
        pinhole_without_distortion_ptr_->Unproject(undistorted_point, ray3d);
        Point2 distorted_point;
        pinhole_with_distortion_ptr_->Project(ray3d, distorted_point);
        distorted_points.emplace_back(distorted_point);
    }

    ImageUndistorterType image_undistorter(pinhole_with_distortion_ptr_, pinhole_without_distortion_ptr_);

    CvMatType in = CvMatType::zeros(height_, width_, CV_8UC1);
    CvMatType out;
    image_undistorter.Undistort(in, out);

    CvMatType mapx, mapy;
    std::tie(mapx, mapy) = image_undistorter.GetMap();
    CvMatType mapx_float32, mapy_float32;
    cv::convertMaps(mapx, mapy, mapx_float32, mapy_float32, CV_32FC1);

    /* check result */
    ASSERT_EQ(pinhole_without_distortion_width_, out.cols);
    ASSERT_EQ(pinhole_without_distortion_height_, out.rows);

    for (uint16_t i = 0u; i < undistorted_points.size(); i++)
    {
        ASSERT_NEAR(distorted_points.at(i).GetX(),
                    mapx_float32.at<holo::float32_t>(undistorted_points.at(i).GetY(), undistorted_points.at(i).GetX()),
                    0.3);
        ASSERT_NEAR(distorted_points.at(i).GetY(),
                    mapy_float32.at<holo::float32_t>(undistorted_points.at(i).GetY(), undistorted_points.at(i).GetX()),
                    0.3);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImageUndistorterFixture, UndistortPointsNormal)
{
    ///< points in pinhole_without_distortion_ptr_
    std::vector<Point2> undistorted_points({Point2(250.0, 250.0), Point2(500.0, 500.0)});

    ///< project to pinhole_with_distortion_ptr_
    std::vector<Point2> in;
    for (Point2 const& undistorted_point : undistorted_points)
    {
        Point3 ray3d;
        pinhole_without_distortion_ptr_->Unproject(undistorted_point, ray3d);
        Point2 distorted_point;
        pinhole_with_distortion_ptr_->Project(ray3d, distorted_point);
        in.emplace_back(distorted_point);
    }

    ImageUndistorterType image_undistorter(pinhole_with_distortion_ptr_, pinhole_without_distortion_ptr_);

    std::vector<Point2> out;
    image_undistorter.UndistortPoints(in, out);

    /* check result */
    ASSERT_EQ(undistorted_points.size(), out.size());

    for (uint16_t i = 0u; i < undistorted_points.size(); i++)
    {
        ASSERT_NEAR(undistorted_points.at(i).GetX(), out.at(i).GetX(), 0.3);
        ASSERT_NEAR(undistorted_points.at(i).GetY(), out.at(i).GetY(), 0.3);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImageUndistorterFixture, NormalMethod)
{
    ImageUndistorterType image_undistorter(fisheye_with_distortion_ptr_, pinhole_without_distortion_ptr_, tRs_);

    /* check results */
    ASSERT_EQ(fisheye_with_distortion_ptr_, image_undistorter.GetSourceIntrinsic());
    ASSERT_EQ(pinhole_without_distortion_ptr_, image_undistorter.GetTargetIntrinsic());
    ASSERT_EQ(pinhole_without_distortion_width_, image_undistorter.GetMap().first.cols);
    ASSERT_EQ(tRs_.at<holo::float32_t>(0u, 0u), image_undistorter.GetRotation().at<holo::float32_t>(0u, 0u));
}
