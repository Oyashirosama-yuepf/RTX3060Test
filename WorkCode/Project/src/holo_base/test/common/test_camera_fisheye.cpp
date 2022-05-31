/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_camera_fisheye.cpp
 * @brief This file implement unit test for CameraFisheyeT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-12-11
 */

#include <vector>

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <gtest/gtest.h>
#include <holo/common/camera_fisheye.h>

using namespace holo;

// ------------------------- camera intrinsic example --------------------------
// dataset: "20181009"
// car: "magotan2"
// coord: CAMERA_FRONT_LEFT
// model: FISHEYE
// fx: 957.1681188486876
// fy: 956.817014702859
// cx: 948.8131210491937
// cy: 552.8500669371166
// skew: 0
// k1: -0.04548213432203192
// k2: 0.01616241276716344
// p1: 0
// p2: 0
// k3: -0.01551614059536555
// k4: 0.003567287484854713
// k5: 0
// k6: 0
// width: 1920
// height : 1020
// ------------------------- /camera intrinsic example --------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const float32_t EPSILON = 10e-6;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::geometry::Point2T<float32_t> CvProjectPoint(const holo::geometry::Point3T<float32_t>& input, const MatrixT<float32_t, 3, 3>& K)
{
    cv::Vec3d      rvec(0.0f, 0.0f, 0.0f);
    cv::Vec3d      tvec(0.0f, 0.0f, 0.0f);
    cv::InputArray dist_coeffs = cv::noArray();
    cv::Mat        intrinsic_mat(3, 3, cv::DataType<float32_t>::type);
    intrinsic_mat.at<float32_t>(0, 0) = K(0U, 0U);
    intrinsic_mat.at<float32_t>(0, 1) = K(0U, 1U);
    intrinsic_mat.at<float32_t>(0, 2) = K(0U, 2U);
    intrinsic_mat.at<float32_t>(1, 0) = K(1U, 0U);
    intrinsic_mat.at<float32_t>(1, 1) = K(1U, 1U);
    intrinsic_mat.at<float32_t>(1, 2) = K(1U, 2U);
    intrinsic_mat.at<float32_t>(2, 0) = K(2U, 0U);
    intrinsic_mat.at<float32_t>(2, 1) = K(2U, 1U);
    intrinsic_mat.at<float32_t>(2, 2) = K(2U, 2U);

    std::vector<cv::Point3f> input_points;
    std::vector<cv::Point2f> output_points;
    input_points.push_back(cv::Point3f(input.GetX(), input.GetY(), input.GetZ()));

    cv::projectPoints(input_points, rvec, tvec, intrinsic_mat, dist_coeffs, output_points);

    return holo::geometry::Point2T<float32_t>(output_points[0].x, output_points[0].y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::geometry::Point3T<float32_t> CvUnprojectPoint(const holo::geometry::Point2T<float32_t>& input, const MatrixT<float32_t, 3, 3>& K_Inv)
{
    cv::Vec3f   point3(input.GetX(), input.GetY(), 1.0f);
    cv::Matx33f k_inverse_mat;
    k_inverse_mat(0, 0) = K_Inv(0U, 0U);
    k_inverse_mat(0, 1) = K_Inv(0U, 1U);
    k_inverse_mat(0, 2) = K_Inv(0U, 2U);
    k_inverse_mat(1, 0) = K_Inv(1U, 0U);
    k_inverse_mat(1, 1) = K_Inv(1U, 1U);
    k_inverse_mat(1, 2) = K_Inv(1U, 2U);
    k_inverse_mat(2, 0) = K_Inv(2U, 0U);
    k_inverse_mat(2, 1) = K_Inv(2U, 1U);
    k_inverse_mat(2, 2) = K_Inv(2U, 2U);

    cv::Vec3f output = k_inverse_mat * point3;
    return holo::geometry::Point3T<float>(output[0] / output[2], output[1] / output[2], 1.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::geometry::Point2T<float32_t> CvDistortPoint(const holo::geometry::Point2T<float32_t>& input, const MatrixT<float32_t, 3, 3>& K,
                                  const VectorT<float32_t, 8>& D)
{
    std::vector<cv::Point2f> input_points;
    std::vector<cv::Point2f> output_points;
    input_points.push_back(cv::Point2f(input.GetX(), input.GetY()));

    cv::Mat intrinsic_mat(3, 3, cv::DataType<float32_t>::type);
    cv::Mat dist_coeffs               = cv::Mat::zeros(4, 1, CV_32F);
    intrinsic_mat.at<float32_t>(0, 0) = K(0U, 0U);
    intrinsic_mat.at<float32_t>(0, 1) = K(0U, 1U);
    intrinsic_mat.at<float32_t>(0, 2) = K(0U, 2U);
    intrinsic_mat.at<float32_t>(1, 0) = K(1U, 0U);
    intrinsic_mat.at<float32_t>(1, 1) = K(1U, 1U);
    intrinsic_mat.at<float32_t>(1, 2) = K(1U, 2U);
    intrinsic_mat.at<float32_t>(2, 0) = K(2U, 0U);
    intrinsic_mat.at<float32_t>(2, 1) = K(2U, 1U);
    intrinsic_mat.at<float32_t>(2, 2) = K(2U, 2U);
    dist_coeffs.at<float32_t>(0)      = D[0U];  // k1
    dist_coeffs.at<float32_t>(1)      = D[1U];  // k2
    dist_coeffs.at<float32_t>(2)      = D[4U];  // k3
    dist_coeffs.at<float32_t>(3)      = D[5U];  // k4

    cv::fisheye::distortPoints(input_points, output_points, intrinsic_mat, dist_coeffs);

    return holo::geometry::Point2T<float32_t>(output_points[0].x, output_points[0].y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::geometry::Point2T<float32_t> CvUndistortPoint(const holo::geometry::Point2T<float32_t>& input, const MatrixT<float32_t, 3, 3>& K,
                                    const VectorT<float32_t, 8>& D, const MatrixT<float32_t, 3, 3>& new_K)
{
    std::vector<cv::Point2f> input_points;
    std::vector<cv::Point2f> output_points;
    input_points.push_back(cv::Point2f(input.GetX(), input.GetY()));

    cv::Mat intrinsic_mat(3, 3, cv::DataType<float32_t>::type);
    cv::Mat newIntrinsicMat(3, 3, cv::DataType<float32_t>::type);
    cv::Mat dist_coeffs                 = cv::Mat::zeros(4, 1, CV_32F);
    intrinsic_mat.at<float32_t>(0, 0)   = K(0U, 0U);
    intrinsic_mat.at<float32_t>(0, 1)   = K(0U, 1U);
    intrinsic_mat.at<float32_t>(0, 2)   = K(0U, 2U);
    intrinsic_mat.at<float32_t>(1, 0)   = K(1U, 0U);
    intrinsic_mat.at<float32_t>(1, 1)   = K(1U, 1U);
    intrinsic_mat.at<float32_t>(1, 2)   = K(1U, 2U);
    intrinsic_mat.at<float32_t>(2, 0)   = K(2U, 0U);
    intrinsic_mat.at<float32_t>(2, 1)   = K(2U, 1U);
    intrinsic_mat.at<float32_t>(2, 2)   = K(2U, 2U);
    newIntrinsicMat.at<float32_t>(0, 0) = new_K(0U, 0U);
    newIntrinsicMat.at<float32_t>(0, 1) = new_K(0U, 1U);
    newIntrinsicMat.at<float32_t>(0, 2) = new_K(0U, 2U);
    newIntrinsicMat.at<float32_t>(1, 0) = new_K(1U, 0U);
    newIntrinsicMat.at<float32_t>(1, 1) = new_K(1U, 1U);
    newIntrinsicMat.at<float32_t>(1, 2) = new_K(1U, 2U);
    newIntrinsicMat.at<float32_t>(2, 0) = new_K(2U, 0U);
    newIntrinsicMat.at<float32_t>(2, 1) = new_K(2U, 1U);
    newIntrinsicMat.at<float32_t>(2, 2) = new_K(2U, 2U);
    dist_coeffs.at<float32_t>(0)        = D[0U];  // k1
    dist_coeffs.at<float32_t>(1)        = D[1U];  // k2
    dist_coeffs.at<float32_t>(2)        = D[4U];  // k3
    dist_coeffs.at<float32_t>(3)        = D[5U];  // k4

    cv::fisheye::undistortPoints(input_points, output_points, intrinsic_mat, dist_coeffs, cv::Matx33d::eye(),
                                 newIntrinsicMat);

    return holo::geometry::Point2T<float32_t>(output_points[0].x, output_points[0].y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, NormalInput)
{
    MatrixT<float32_t, 3, 3> K = MatrixT<float32_t, 3, 3>::Zero();
    VectorT<float32_t, 8>    D = VectorT<float32_t, 8>::Zero();

    K(0U, 0U) = 957.1681188486876f;  // fx
    K(1U, 1U) = 956.817014702859f;   // fy
    K(0U, 2U) = 948.8131210491937f;  // cx
    K(1U, 2U) = 552.8500669371166f;  // cy
    K(2U, 2U) = 1.0f;
    D[0U]     = -0.04548213432203192f;  // k1
    D[1U]     = 0.01616241276716344f;   // k2
    D[4U]     = -0.01551614059536555f;  // k3
    D[5U]     = 0.003567287484854713f;  // k4

    uint32_t                 resolution_width  = 1920U;
    uint32_t                 resolution_height = 1020U;
    CameraModel              camera_model      = CameraModel::FISHEYE;
    MatrixT<float32_t, 3, 3> K_Inverse         = K.Inverse();

    CameraFisheyeT<float32_t> camera(resolution_width, resolution_height, K, D);

    uint32_t                 actual_resolution_width  = camera.GetResolutionWidth();
    uint32_t                 actual_resolution_height = camera.GetResolutionHeight();
    MatrixT<float32_t, 3, 3> actual_K                 = camera.GetK();
    VectorT<float32_t, 8>    actual_D                 = camera.GetD();
    MatrixT<float32_t, 3, 3> actual_K_Inverse         = camera.GetKInv();
    CameraModel              actual_camera_model      = camera.GetCameraDistortionModel();

    ASSERT_EQ(actual_resolution_width, resolution_width);
    ASSERT_EQ(actual_resolution_height, resolution_height);
    ASSERT_EQ(actual_camera_model, camera_model);
    ASSERT_EQ(actual_K, K);
    ASSERT_EQ(actual_D, D);
    ASSERT_NEAR(actual_K_Inverse(0U, 0U), K_Inverse(0U, 0U), EPSILON);
    ASSERT_NEAR(actual_K_Inverse(0U, 1U), K_Inverse(0U, 1U), EPSILON);
    ASSERT_NEAR(actual_K_Inverse(0U, 2U), K_Inverse(0U, 2U), EPSILON);
    ASSERT_NEAR(actual_K_Inverse(1U, 0U), K_Inverse(1U, 0U), EPSILON);
    ASSERT_NEAR(actual_K_Inverse(1U, 1U), K_Inverse(1U, 1U), EPSILON);
    ASSERT_NEAR(actual_K_Inverse(1U, 2U), K_Inverse(1U, 2U), EPSILON);
    ASSERT_NEAR(actual_K_Inverse(2U, 0U), K_Inverse(2U, 0U), EPSILON);
    ASSERT_NEAR(actual_K_Inverse(2U, 1U), K_Inverse(2U, 1U), EPSILON);
    ASSERT_NEAR(actual_K_Inverse(2U, 2U), K_Inverse(2U, 2U), EPSILON);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ProjectTest, NormalInput)
{
    // construct a fisheye camera
    MatrixT<float32_t, 3, 3> K = MatrixT<float32_t, 3, 3>::Zero();
    VectorT<float32_t, 8>    D = VectorT<float32_t, 8>::Zero();

    K(0U, 0U) = 957.1681188486876f;  // fx
    K(1U, 1U) = 956.817014702859f;   // fy
    K(0U, 2U) = 948.8131210491937f;  // cx
    K(1U, 2U) = 552.8500669371166f;  // cy
    K(2U, 2U) = 1.0f;
    D[0U]     = -0.04548213432203192f;  // k1
    D[1U]     = 0.01616241276716344f;   // k2
    D[4U]     = -0.01551614059536555f;  // k3
    D[5U]     = 0.003567287484854713f;  // k4

    uint32_t resolution_width  = 1920U;
    uint32_t resolution_height = 1020U;

    CameraFisheyeT<float32_t> camera(resolution_width, resolution_height, K, D);

    // project a point to image
    holo::geometry::Point3T<float32_t> input_world_point3(1.0f, 0.0f, 20.0f);
    holo::geometry::Point2T<float32_t> actual_point    = camera.Project(input_world_point3);
    holo::geometry::Point2T<float32_t> expected_points = CvProjectPoint(input_world_point3, K);

    ASSERT_NEAR(actual_point.GetX(), expected_points.GetX(), EPSILON);
    ASSERT_NEAR(actual_point.GetY(), expected_points.GetY(), EPSILON);

    MatrixT<float32_t, 3, 3> new_K = K;
    new_K(0U, 0U)                  = new_K(0U, 0U) * 0.6f;
    new_K(1U, 1U)                  = new_K(1U, 1U) * 0.6f;
    actual_point                   = camera.Project(input_world_point3, new_K);
    expected_points                = CvProjectPoint(input_world_point3, new_K);

    ASSERT_NEAR(actual_point.GetX(), expected_points.GetX(), EPSILON);
    ASSERT_NEAR(actual_point.GetY(), expected_points.GetY(), EPSILON);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(UnprojectTest, NormalInput)
{
    // construct a fisheye camera
    MatrixT<float32_t, 3, 3> K = MatrixT<float32_t, 3, 3>::Zero();
    VectorT<float32_t, 8>    D = VectorT<float32_t, 8>::Zero();

    K(0U, 0U) = 957.1681188486876f;  // fx
    K(1U, 1U) = 956.817014702859f;   // fy
    K(0U, 2U) = 948.8131210491937f;  // cx
    K(1U, 2U) = 552.8500669371166f;  // cy
    K(2U, 2U) = 1.0f;
    D[0U]     = -0.04548213432203192f;  // k1
    D[1U]     = 0.01616241276716344f;   // k2
    D[4U]     = -0.01551614059536555f;  // k3
    D[5U]     = 0.003567287484854713f;  // k4

    uint32_t resolution_width  = 1920U;
    uint32_t resolution_height = 1020U;

    CameraFisheyeT<float32_t> camera(resolution_width, resolution_height, K, D);
    MatrixT<float32_t, 3, 3>  K_Inverse = camera.GetKInv();

    // unproject a point
    holo::geometry::Point2T<float32_t> input_point(996.672f, 552.85f);
    holo::geometry::Point3T<float32_t> actual_point    = camera.Unproject(input_point);
    holo::geometry::Point3T<float32_t> expected_points = CvUnprojectPoint(input_point, K_Inverse);

    ASSERT_NEAR(actual_point.GetX(), expected_points.GetX(), EPSILON);
    ASSERT_NEAR(actual_point.GetY(), expected_points.GetY(), EPSILON);
    ASSERT_NEAR(actual_point.GetZ(), expected_points.GetZ(), EPSILON);

    actual_point    = camera.Unproject(input_point, K_Inverse);
    expected_points = CvUnprojectPoint(input_point, K_Inverse);

    ASSERT_NEAR(actual_point.GetX(), expected_points.GetX(), EPSILON);
    ASSERT_NEAR(actual_point.GetY(), expected_points.GetY(), EPSILON);
    ASSERT_NEAR(actual_point.GetZ(), expected_points.GetZ(), EPSILON);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(DistortPointTest, NormalInput)
{
    // construct a fisheye camera
    MatrixT<float32_t, 3, 3> K = MatrixT<float32_t, 3, 3>::Zero();
    VectorT<float32_t, 8>    D = VectorT<float32_t, 8>::Zero();

    K(0U, 0U) = 957.1681188486876f;  // fx
    K(1U, 1U) = 956.817014702859f;   // fy
    K(0U, 2U) = 948.8131210491937f;  // cx
    K(1U, 2U) = 552.8500669371166f;  // cy
    K(2U, 2U) = 1.0f;
    D[0U]     = -0.04548213432203192f;  // k1
    D[1U]     = 0.01616241276716344f;   // k2
    D[4U]     = -0.01551614059536555f;  // k3
    D[5U]     = 0.003567287484854713f;  // k4

    uint32_t resolution_width  = 1920U;
    uint32_t resolution_height = 1020U;

    CameraFisheyeT<float32_t> camera(resolution_width, resolution_height, K, D);

    // distort point
    holo::geometry::Point2T<float32_t> input_point(996.672f, 552.85f);
    holo::geometry::Point2T<float32_t> actual_point   = camera.DistortPoint(input_point);
    holo::geometry::Point2T<float32_t> expected_point = CvDistortPoint(input_point, K, D);

    ASSERT_NEAR(actual_point.GetX(), expected_point.GetX(), EPSILON);
    ASSERT_NEAR(actual_point.GetY(), expected_point.GetY(), EPSILON);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(UndistortPointTest, NormalInput)
{
    // construct a fisheye camera
    MatrixT<float32_t, 3, 3> K = MatrixT<float32_t, 3, 3>::Zero();
    VectorT<float32_t, 8>    D = VectorT<float32_t, 8>::Zero();

    K(0U, 0U) = 957.1681188486876f;  // fx
    K(1U, 1U) = 956.817014702859f;   // fy
    K(0U, 2U) = 948.8131210491937f;  // cx
    K(1U, 2U) = 552.8500669371166f;  // cy
    K(2U, 2U) = 1.0f;
    D[0U]     = -0.04548213432203192f;  // k1
    D[1U]     = 0.01616241276716344f;   // k2
    D[4U]     = -0.01551614059536555f;  // k3
    D[5U]     = 0.003567287484854713f;  // k4

    uint32_t resolution_width  = 1920U;
    uint32_t resolution_height = 1020U;

    CameraFisheyeT<float32_t> camera(resolution_width, resolution_height, K, D);
    MatrixT<float32_t, 3, 3>  new_K = K;
    new_K(0U, 0U)                   = K(0U, 0U) * 0.6f;
    new_K(1U, 1U)                   = K(1U, 1U) * 0.6f;

    // undistort point
    holo::geometry::Point2T<float32_t> input_point(996.672f, 552.85f);
    holo::geometry::Point2T<float32_t> actual_point   = camera.UndistortPoint(input_point, new_K);
    holo::geometry::Point2T<float32_t> expected_point = CvUndistortPoint(input_point, K, D, new_K);

    ASSERT_NEAR(actual_point.GetX(), expected_point.GetX(), EPSILON);
    ASSERT_NEAR(actual_point.GetY(), expected_point.GetY(), EPSILON);
}

TEST(UndistortPointTest, NormalInput_2)
{
    // construct a fisheye camera
    MatrixT<float32_t, 3, 3> K = MatrixT<float32_t, 3, 3>::Zero();
    VectorT<float32_t, 8>    D = VectorT<float32_t, 8>::Zero();

    K(0U, 0U) = 957.1681188486876f;  // fx
    K(1U, 1U) = 956.817014702859f;   // fy
    K(0U, 2U) = 948.8131210491937f;  // cx
    K(1U, 2U) = 552.8500669371166f;  // cy
    K(2U, 2U) = 1.0f;
    D[0U]     = -0.04548213432203192f;  // k1
    D[1U]     = 0.01616241276716344f;   // k2
    D[4U]     = -0.01551614059536555f;  // k3
    D[5U]     = 0.003567287484854713f;  // k4

    uint32_t resolution_width  = 1920U;
    uint32_t resolution_height = 1020U;

    CameraFisheyeT<float32_t> camera(resolution_width, resolution_height, K, D);
    MatrixT<float32_t, 3, 3>  new_K = K;
    new_K(0U, 0U)                   = K(0U, 0U) * 0.6f;
    new_K(1U, 1U)                   = K(1U, 1U) * 0.6f;

    // undistort point
    holo::geometry::Point2T<float32_t> input_point(996.672f, 552.85f);
    holo::geometry::Point2T<float32_t> actual_point   = camera.UndistortPoint(input_point, new_K);
    holo::geometry::Point2T<float32_t> expected_point = CvUndistortPoint(input_point, K, D, new_K);

    ASSERT_NEAR(actual_point.GetX(), expected_point.GetX(), EPSILON);
    ASSERT_NEAR(actual_point.GetY(), expected_point.GetY(), EPSILON);
}

TEST(CameraFisheyeT, Constructor)
{
    holo::Intrinsicf intrinsic;

    holo::numerics::MatrixT<holo::float32_t, 3, 3> matrix;
    holo::numerics::VectorT<holo::float32_t, 8> vector;

    CameraFisheyeT<float32_t> camera(intrinsic);
    CameraFisheyeT<float32_t> camera2(camera);
    CameraFisheyeT<float32_t> camera3(std::move(camera));
    CameraFisheyeT<float32_t> camera4(intrinsic);
    camera4 = camera;
    camera4 = std::move(camera);  
    camera4 = std::move(camera4); 

    // holo::numerics::MatrixT<float32_t, 3, 3> matrix3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    // holo::numerics::VectorT<float32_t, 8>    vector8;
    // // holo::numerics::MatrixXf matrixf;
    // // matrixf.Resize(4u, 5u);
    // // const Matrix3f matrix3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);


    // try
    // {
    //     CameraFisheyeT<float32_t> camera4(1, 2, matrix3, vector8);
    // }
    // catch(...)
    // {
    // }
}

TEST(CameraFisheyeT, UndistortImage)
{
    // construct a fisheye camera
    MatrixT<float32_t, 3, 3> K = MatrixT<float32_t, 3, 3>::Zero();
    VectorT<float32_t, 8>    D = VectorT<float32_t, 8>::Zero();

    K(0U, 0U) = 957.1681188486876f;  // fx
    K(1U, 1U) = 956.817014702859f;   // fy
    K(0U, 2U) = 948.8131210491937f;  // cx
    K(1U, 2U) = 552.8500669371166f;  // cy
    K(2U, 2U) = 1.0f;
    D[0U]     = -0.04548213432203192f;  // k1
    D[1U]     = 0.01616241276716344f;   // k2
    D[4U]     = -0.01551614059536555f;  // k3
    D[5U]     = 0.003567287484854713f;  // k4

    uint32_t resolution_width  = 1920U;
    uint32_t resolution_height = 1020U;

    CameraFisheyeT<float32_t> camera(resolution_width, resolution_height, K, D);

    holo::Image image_in, image_out;
    camera.UndistortImage(image_in, K, image_out);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
