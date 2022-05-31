/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for intrinsic class
 * @author lifeng@holomatic.com
 * @date Dec 23, 2020
 */

#include <gtest/gtest.h>
#include <holo/common/intrinsic.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PinholeIntrinsic, Project_Unproject)
{
    // create a pinhole intrinsic
    holo::common::PinholeIntrinsicf intrinsic;

    // set parameters
    intrinsic.SetDimension(1920, 1020);
    intrinsic.SetFocalLength(957.1681188486876, 956.817014702859);
    intrinsic.SetPrinciplePoint(948.8131210491937, 552.8500669371166);
    intrinsic.SetSkew(0.0);
    intrinsic.SetDistortionParameter(-0.04548213432203192, 0.01616241276716344, 0.0, 0.0);

    // create a 2d point in image coordiante
    holo::common::PinholeIntrinsicf::Point2Type gts_image_pt(500.0, 500.0);
    holo::common::PinholeIntrinsicf::Point2Type ess_image_pt;

    // test unproject and project
    holo::common::PinholeIntrinsicf::Point3Type ptw;
    intrinsic.Unproject(gts_image_pt, ptw);
    intrinsic.Project(ptw, ess_image_pt);

    // check result.
    static const holo::float32_t EPSILON = 1e-4;
    ASSERT_NEAR(gts_image_pt.GetX(), ess_image_pt.GetX(), EPSILON);
    ASSERT_NEAR(gts_image_pt.GetY(), ess_image_pt.GetY(), EPSILON);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FisheyeIntrinsic, Project_Unproject)
{
    // create a fisheye camera intrinsic
    holo::common::FisheyeIntrinsicf intrinsic;

    // set parameters
    intrinsic.SetDimension(1920, 1020);
    intrinsic.SetFocalLength(957.1681188486876, 956.817014702859);
    intrinsic.SetPrinciplePoint(948.8131210491937, 552.8500669371166);
    intrinsic.SetSkew(0.0);
    intrinsic.SetDistortionParameter(-0.04548213432203192, 0.01616241276716344, 0.0, 0.0);

    // create a 2d point in image coordiante
    holo::common::FisheyeIntrinsicf::Point2Type gts_image_pt(500.0, 500.0);
    holo::common::FisheyeIntrinsicf::Point2Type ess_image_pt;

    // test unproject and project
    holo::common::FisheyeIntrinsicf::Point3Type ptw;
    intrinsic.Unproject(gts_image_pt, ptw);
    intrinsic.Project(ptw, ess_image_pt);

    // check result.
    static const holo::float32_t EPSILON = 1e-4;
    ASSERT_NEAR(gts_image_pt.GetX(), ess_image_pt.GetX(), EPSILON);
    ASSERT_NEAR(gts_image_pt.GetY(), ess_image_pt.GetY(), EPSILON);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OmnidirectionalIntrinsic, GetSetPrinciplePointAndAffineTransformation)
{
    // create an omnidirectional camera intrinsic
    holo::common::OmnidirectionalIntrinsicf intrinsic;
    intrinsic.SetPrinciplePoint(1.1, 2.2);
    intrinsic.SetAffineTransformation(3.3, 4.4, 5.5);

    static const holo::float32_t EPSILON = 1e-4;
    ASSERT_NEAR(intrinsic.GetCX(), 1.1, EPSILON);
    ASSERT_NEAR(intrinsic.GetCY(), 2.2, EPSILON);
    ASSERT_NEAR(intrinsic.GetC(), 3.3, EPSILON);
    ASSERT_NEAR(intrinsic.GetD(), 4.4, EPSILON);
    ASSERT_NEAR(intrinsic.GetE(), 5.5, EPSILON);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OmnidirectionalIntrinsic, Project_Unproject)
{
    using ScalarType = holo::common::OmnidirectionalIntrinsicf::ScalarType;

    // affine transformation parameters
    ScalarType c = 0.9993998663918573;
    ScalarType d = 0.001523210247993539;
    ScalarType e = -0.001335533256780942;

    // principal point
    ScalarType cx = 643.2474851182744;
    ScalarType cy = 539.136484111158;

    // dimention
    ScalarType width  = 1280;
    ScalarType height = 1080;

    // coefficient of unproject polynomial
    ScalarType a0 = -267.3970657311719;
    ScalarType a1 = 0;
    ScalarType a2 = 0.002779849413747013;
    ScalarType a3 = -8.331573516227267e-06;
    ScalarType a4 = 1.54992261345046e-08;

    // coefficient of project polynomial
    ScalarType p0  = 379.9983179664686;
    ScalarType p1  = 199.5704456423882;
    ScalarType p2  = -35.92860675855289;
    ScalarType p3  = 32.27481626606091;
    ScalarType p4  = 24.97996825327351;
    ScalarType p5  = -10.85321816153431;
    ScalarType p6  = 10.6190692739202;
    ScalarType p7  = -8.806349248236376;
    ScalarType p8  = -17.92243926092452;
    ScalarType p9  = 26.91072582034472;
    ScalarType p10 = 16.73692296983121;
    ScalarType p11 = -16.47359006263313;
    ScalarType p12 = -8.052233176340769;
    ScalarType p13 = 3.802667681430336;
    ScalarType p14 = 1.837192705710058;

    // create an omnidirectional camera intrinsic
    holo::common::OmnidirectionalIntrinsicf intrinsic;

    // set parameters
    intrinsic.SetDimension(1280, 1080);
    std::initializer_list<holo::common::OmnidirectionalIntrinsicf::ScalarType> unproject_poly = {a0, a1, a2, a3, a4};
    std::initializer_list<holo::common::OmnidirectionalIntrinsicf::ScalarType> project_poly   = {
        p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14};
    intrinsic.SetUnprojectPolynomial(unproject_poly, project_poly);
    intrinsic.SetPrinciplePoint(cx, cy);
    intrinsic.SetAffineTransformation(c, d, e);

    // create a 2d point in image coordiante
    holo::common::FisheyeIntrinsicf::Point2Type gts_image_pt(50.0, 70.0);
    holo::common::FisheyeIntrinsicf::Point2Type ess_image_pt;

    // test unproject and project
    holo::common::FisheyeIntrinsicf::Point3Type ptw;
    intrinsic.Unproject(gts_image_pt, ptw);
    intrinsic.Project(ptw, ess_image_pt);

    // check result.
    static const holo::float32_t EPSILON = 5e-2;
    ASSERT_NEAR(gts_image_pt.GetX(), ess_image_pt.GetX(), EPSILON);
    ASSERT_NEAR(gts_image_pt.GetY(), ess_image_pt.GetY(), EPSILON);
}

TEST(OmnidirectionalIntrinsic, SetUnprojectPolynomial)
{
    using ScalarType = holo::common::OmnidirectionalIntrinsicf::ScalarType;

    // affine transformation parameters
    ScalarType c = 0.9993998663918573;
    ScalarType d = 0.001523210247993539;
    ScalarType e = -0.001335533256780942;

    // principal point
    ScalarType cx = 643.2474851182744;
    ScalarType cy = 539.136484111158;

    // dimention
    ScalarType width  = 1280;
    ScalarType height = 1080;

    // coefficient of unproject polynomial
    ScalarType a0 = -267.3970657311719;
    ScalarType a1 = 0;
    ScalarType a2 = 0.002779849413747013;
    ScalarType a3 = -8.331573516227267e-06;
    ScalarType a4 = 1.54992261345046e-08;
    ScalarType a5 = 1.54992261345046e-08;

    // coefficient of project polynomial
    ScalarType p0  = 379.9983179664686;
    ScalarType p1  = 199.5704456423882;
    ScalarType p2  = -35.92860675855289;
    ScalarType p3  = 32.27481626606091;
    ScalarType p4  = 24.97996825327351;
    ScalarType p5  = -10.85321816153431;
    ScalarType p6  = 10.6190692739202;
    ScalarType p7  = -8.806349248236376;
    ScalarType p8  = -17.92243926092452;
    ScalarType p9  = 26.91072582034472;
    ScalarType p10 = 16.73692296983121;
    ScalarType p11 = -16.47359006263313;
    ScalarType p12 = -8.052233176340769;
    ScalarType p13 = 3.802667681430336;
    ScalarType p14 = 1.837192705710058;
    ScalarType p15 = 1.837192705710058;

    // create an omnidirectional camera intrinsic
    holo::common::OmnidirectionalIntrinsicf intrinsic;

    // set parameters
    intrinsic.SetDimension(1280, 1080);
    std::initializer_list<holo::common::OmnidirectionalIntrinsicf::ScalarType> unproject_poly = {a0, a1, a2,
                                                                                                 a3, a4, a5};
    std::initializer_list<holo::common::OmnidirectionalIntrinsicf::ScalarType> project_poly   = {
        p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14};

    std::initializer_list<holo::common::OmnidirectionalIntrinsicf::ScalarType> unproject_poly2 = {a0, a1, a2, a3, a4};
    std::initializer_list<holo::common::OmnidirectionalIntrinsicf::ScalarType> project_poly2   = {
        p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15};

    EXPECT_THROW(intrinsic.SetUnprojectPolynomial(unproject_poly, project_poly), std::runtime_error);
    EXPECT_THROW(intrinsic.SetUnprojectPolynomial(unproject_poly2, project_poly2), std::runtime_error);
}

TEST(OmnidirectionalIntrinsic, SetAndGetProjectPolynomial)
{
    using ScalarType = holo::common::OmnidirectionalIntrinsicf::ScalarType;

    // affine transformation parameters
    ScalarType c = 0.9993998663918573;
    ScalarType d = 0.001523210247993539;
    ScalarType e = -0.001335533256780942;

    // principal point
    ScalarType cx = 643.2474851182744;
    ScalarType cy = 539.136484111158;

    // dimention
    ScalarType width  = 1280;
    ScalarType height = 1080;

    // coefficient of unproject polynomial
    ScalarType a0 = -267.3970657311719;
    ScalarType a1 = 0;
    ScalarType a2 = 0.002779849413747013;
    ScalarType a3 = -8.331573516227267e-06;
    ScalarType a4 = 1.54992261345046e-08;
    ScalarType a5 = 1.54992261345046e-08;

    // coefficient of project polynomial
    ScalarType p0  = 379.9983179664686;
    ScalarType p1  = 199.5704456423882;
    ScalarType p2  = -35.92860675855289;
    ScalarType p3  = 32.27481626606091;
    ScalarType p4  = 24.97996825327351;
    ScalarType p5  = -10.85321816153431;
    ScalarType p6  = 10.6190692739202;
    ScalarType p7  = -8.806349248236376;
    ScalarType p8  = -17.92243926092452;
    ScalarType p9  = 26.91072582034472;
    ScalarType p10 = 16.73692296983121;
    ScalarType p11 = -16.47359006263313;
    ScalarType p12 = -8.052233176340769;
    ScalarType p13 = 3.802667681430336;
    ScalarType p14 = 1.837192705710058;
    ScalarType p15 = 1.837192705710058;

    // create an omnidirectional camera intrinsic
    holo::common::OmnidirectionalIntrinsicf intrinsic;

    std::initializer_list<holo::common::OmnidirectionalIntrinsicf::ScalarType> unproject_poly = {a0, a1, a2, a3, a4};
    std::initializer_list<holo::common::OmnidirectionalIntrinsicf::ScalarType> project_poly   = {
        p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14};

    intrinsic.SetUnprojectPolynomial(unproject_poly, project_poly);
    std::array<ScalarType, 15U> project_poly_value;
    std::array<ScalarType, 5U>  unproject_poly_value;
    project_poly_value = intrinsic.GetProjectPolynomial();

    for (const auto& element : project_poly)
    {
        static size_t num = 0;
        EXPECT_EQ(project_poly_value[num++], element);
    }

    std::vector<ScalarType> project_poly_v{p0, p1, p2, p3, p4, p5, p6, p7, p1, p2, p3, p4, p5, p6, p7};
    intrinsic.SetProjectPolynomial(project_poly_v.begin(), 15U);
    project_poly_value = intrinsic.GetProjectPolynomial();

    for (size_t i = 0; i < 15; i++)
    {
        project_poly_value[i] = project_poly_v[i];
    }

    std::vector<ScalarType> unproject_poly_v{p3, p4, p5, p6, p7};
    intrinsic.SetUnprojectPolynomial(project_poly_v.begin(), 5U);
    unproject_poly_value = intrinsic.GetUnprojectPolynomial();

    for (size_t i = 0; i < 5; i++)
    {
        unproject_poly_value[i] = unproject_poly_v[i];
    }

    std::vector<ScalarType> unproject_poly_v2{1.1, 2.2, 3.3};
    intrinsic.SetUnprojectPolynomial(unproject_poly_v2.begin(), 2U);
    unproject_poly_value = intrinsic.GetUnprojectPolynomial();

    unproject_poly_value[0] = 1.1;
    unproject_poly_value[1] = 2.2;
    unproject_poly_value[2] = 3.3;
    unproject_poly_value[3] = p6;
    unproject_poly_value[4] = p7;

    EXPECT_THROW(intrinsic.SetUnprojectPolynomial(project_poly_v.begin(), 6U), std::runtime_error);
    EXPECT_THROW(intrinsic.SetProjectPolynomial(project_poly_v.begin(), 16U), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
