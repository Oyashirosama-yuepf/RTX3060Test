/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_projection_line_factor.cpp
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date June 20, 2020

 */

#include <gtest/gtest.h>

#include <gtsam/base/numericalDerivative.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <gtsam/slam/PriorFactor.h>

#include <holo/localization/backend/factors/projection_line_factor.h>
#include <holo/localization/sam/factors/internal/projection_line_factor_inl.h>
#include <holo/log/hololog.h>

using gtsam::symbol_shorthand::X;

using Scalar      = holo::localization::Scalar;
using Vector3Type = holo::localization::Vector3Type;
using Matrix3Type = holo::localization::Matrix3Type;
using Point2Type  = holo::localization::Point2Type;
using Point3Type  = holo::localization::Point3Type;
using Rot3Type    = holo::localization::Rot3Type;
using Pose3Type   = holo::localization::Pose3Type;
using LineFactor  = holo::localization::ProjectionLineFactor;

using Key             = gtsam::Key;
using Values          = gtsam::Values;
using GTPoint2        = gtsam::Point2;
using GTPoint3        = gtsam::Point3;
using GTPose3         = gtsam::Pose3;
using GTRot3          = gtsam::Rot3;
using PriorPoseFactor = gtsam::PriorFactor<GTPose3>;
using LMParams        = gtsam::LevenbergMarquardtParams;
using LMOptimizer     = gtsam::LevenbergMarquardtOptimizer;
using Graph           = gtsam::NonlinearFactorGraph;

/**
 * @brief map point of pole
 *
 */
struct PoleMapPoint
{
    Point3Type start;  ///< start point
    Point3Type end;    ///< end point
};

/**
 * @brief 2d point of pole in image plane
 *
 */
struct PoleImagePoint
{
    Point2Type start;  ///< start point
    Point2Type end;    ///< end point
};

TEST(TestProjectionLineFactor, Jacobian)
{
    // create camera intrinsic
    Scalar const fx = Scalar(960);
    Scalar const fy = Scalar(512);
    Scalar const s  = Scalar(0.0);
    Scalar const cx = Scalar(1920 / 2);
    Scalar const cy = Scalar(1024 / 2);

    Matrix3Type K = Matrix3Type::Identity();
    K(0u, 0u)     = fx;
    K(1u, 1u)     = fy;
    K(0u, 1u)     = s;
    K(0u, 2u)     = cx;
    K(1u, 2u)     = cy;

    // create truth wTb
    Pose3Type const truth_wTb(Rot3Type::Rz(M_PI / 2), Point3Type());
    GTPose3 const   gtsam_truth_wTb(GTRot3::Rz(M_PI / 2), GTPoint3());

    // create bTc
    Pose3Type const bTc =
        Pose3Type(Rot3Type::Rz(-M_PI / 2), Point3Type()) * Pose3Type(Rot3Type::Rx(-M_PI / 2), Point3Type());

    // create pole map point
    Point3Type              start_map_point(-5.0, 10.0, 5.0), end_map_point(5.0, 10.0, 5.0);
    std::vector<Point3Type> map_points;
    map_points.push_back(start_map_point);
    map_points.push_back(end_map_point);

    // create project point
    std::vector<Point2Type> image_points;

    for (Point3Type const& point : map_points)
    {
        Vector3Type point3 = K * ((truth_wTb * bTc).Inverse() * point).As<Vector3Type>();
        Point2Type  point2(point3[0] / point3[2], point3[1] / point3[2]);
        image_points.push_back(point2);
    }

    // create index
    uint64_t const index = 1u;

    // create noise sigma
    Scalar const sigma = 0.1;

    // create projection line factor
    holo::localization::Line2Type const line(image_points[0u], image_points[1u]);
    LineFactor                          line_factor(index, start_map_point, bTc, K, line, sigma);

    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(line_factor.GetFactor()));

    Key const key(X(index));
    Values    values;
    values.insert(key, gtsam_truth_wTb);

    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("ProjectionLineFactorJacobian", *factor, values, 1e-5, 1e-5));
}

TEST(TestProjectionLineFactor, Optimize)
{
    // create camera intrinsic
    Scalar const fx = Scalar(960);
    Scalar const fy = Scalar(512);
    Scalar const s  = Scalar(0.0);
    Scalar const cx = Scalar(1920 / 2);
    Scalar const cy = Scalar(1024 / 2);

    Matrix3Type K = Matrix3Type::Identity();
    K(0u, 0u)     = fx;
    K(1u, 1u)     = fy;
    K(0u, 1u)     = s;
    K(0u, 2u)     = cx;
    K(1u, 2u)     = cy;

    // create truth wTb
    Pose3Type const truth_wTb(Rot3Type::Rz(M_PI / 2), Point3Type());
    GTPose3 const   gtsam_truth_wTb(GTRot3::Rz(M_PI / 2), GTPoint3());
    GTPose3 const   gtsam_init_wTb(GTRot3::Rz(M_PI / 2.1), GTPoint3(0.1, 0.1, 0.0));

    // create bTc
    Pose3Type const bTc =
        Pose3Type(Rot3Type::Rz(-M_PI / 2), Point3Type()) * Pose3Type(Rot3Type::Rx(-M_PI / 2), Point3Type());

    // create pole map point
    // there are 6 poles placed in the road. ego car is on the middle of road. o is pole, D is car.
    // ---------o--------o--------o----
    // D
    // ---------o--------o--------o----
    std::vector<PoleMapPoint> map_points;

    Scalar       left_x = -5.0, right_x = 5.0;
    Scalar const y = 10.0;
    Scalar const z = 5.0;

    for (uint16_t i = 0u; i < 3u; i++)
    {
        PoleMapPoint pole_map_point;
        Point3Type   start_map_point(left_x, y + 5.0 * i, 0.0);
        pole_map_point.start = start_map_point;
        Point3Type end_map_point(left_x, y + 5.0 * i, z);
        pole_map_point.end = end_map_point;
        map_points.push_back(pole_map_point);
    }

    for (uint16_t i = 0u; i < 3u; i++)
    {
        PoleMapPoint pole_map_point;
        Point3Type   start_map_point(right_x, y + 5.0 * i, 0.0);
        pole_map_point.start = start_map_point;
        Point3Type end_map_point(right_x, y + 5.0 * i, z);
        pole_map_point.end = end_map_point;
        map_points.push_back(pole_map_point);
    }

    // create project point
    std::vector<PoleImagePoint> image_points;

    for (PoleMapPoint const& point : map_points)
    {
        PoleImagePoint point2;

        Vector3Type start_point3 = K * ((truth_wTb * bTc).Inverse() * point.start).As<Vector3Type>();
        Point2Type  start_point2(start_point3[0u] / start_point3[2u], start_point3[1u] / start_point3[2u]);
        point2.start = start_point2;

        Vector3Type end_point3 = K * ((truth_wTb * bTc).Inverse() * point.end).As<Vector3Type>();
        Point2Type  end_point2(end_point3[0u] / end_point3[2u], end_point3[1u] / end_point3[2u]);
        point2.end = end_point2;

        image_points.push_back(point2);
    }

    GTPose3 est_pose;

    // factor optimize pose
    {
        // create index
        uint64_t const index = 1u;
        Key const      key(X(index));

        // create graph
        Graph graph;

        // add projection line factor
        Scalar const sigma = 0.1;

        for (uint16_t i = 0u; i < map_points.size(); i++)
        {
            holo::localization::Line2Type const line =
                holo::localization::Line2Type(image_points[i].start, image_points[i].end);

            LineFactor                          start_line_factor(index, map_points[i].start, bTc, K, line, sigma);
            gtsam::NoiseModelFactor::shared_ptr start_line_factor_ptr;
            start_line_factor_ptr.reset(static_cast<gtsam::NoiseModelFactor*>(start_line_factor.GetFactor()));
            graph.add(start_line_factor_ptr);

            LineFactor                          end_line_factor(index, map_points[i].end, bTc, K, line, sigma);
            gtsam::NoiseModelFactor::shared_ptr end_line_factor_ptr;
            end_line_factor_ptr.reset(static_cast<gtsam::NoiseModelFactor*>(end_line_factor.GetFactor()));
            graph.add(end_line_factor_ptr);
        }

        // add values
        Values values;
        values.insert(key, gtsam_init_wTb);

        // optimize
        LMParams const param;
        LMOptimizer    optimizer(graph, values, param);
        Values const   results = optimizer.optimize();

        // convert result
        est_pose = results.at<GTPose3>(key);
    }

    GTPoint3 est_rpy;

    // factor only optimize translation
    {
        // create index
        uint64_t const index = 1u;
        Key const      key(X(index));

        // create graph
        Graph graph;

        // add projection line factor
        Scalar const sigma = 0.1;

        for (uint16_t i = 0u; i < map_points.size(); i++)
        {
            holo::localization::Line2Type const line =
                holo::localization::Line2Type(image_points[i].start, image_points[i].end);

            LineFactor start_line_factor(index, map_points[i].start, bTc, K, line, sigma, -1.0, false);
            gtsam::NoiseModelFactor::shared_ptr start_line_factor_ptr;
            start_line_factor_ptr.reset(static_cast<gtsam::NoiseModelFactor*>(start_line_factor.GetFactor()));
            graph.add(start_line_factor_ptr);

            LineFactor end_line_factor(index, map_points[i].end, bTc, K, line, sigma, -1.0, false);
            gtsam::NoiseModelFactor::shared_ptr end_line_factor_ptr;
            end_line_factor_ptr.reset(static_cast<gtsam::NoiseModelFactor*>(end_line_factor.GetFactor()));
            graph.add(end_line_factor_ptr);
        }

        // add values
        Values values;
        values.insert(key, gtsam_init_wTb);

        // optimize
        LMParams const param;
        LMOptimizer    optimizer(graph, values, param);
        Values const   results = optimizer.optimize();

        // convert result
        est_rpy = results.at<GTPose3>(key).rotation().rpy();
    }

    ASSERT_TRUE(assert_equal(GTPoint3(est_pose.translation()), GTPoint3(gtsam_truth_wTb.translation()), 1e-5));
    ASSERT_TRUE(assert_equal(GTPoint3(est_pose.rotation().rpy()), GTPoint3(gtsam_truth_wTb.rotation().rpy()), 1e-5));
    ASSERT_TRUE(assert_equal(est_rpy, GTPoint3(gtsam_init_wTb.rotation().rpy()), 1e-5));
}

TEST(TestProjectionLineFactor, Optimize_Cheirality_Exception)
{
    // create camera intrinsic
    Scalar const fx = Scalar(960);
    Scalar const fy = Scalar(512);
    Scalar const s  = Scalar(0.0);
    Scalar const cx = Scalar(1920 / 2);
    Scalar const cy = Scalar(1024 / 2);

    Matrix3Type K = Matrix3Type::Identity();
    K(0u, 0u)     = fx;
    K(1u, 1u)     = fy;
    K(0u, 1u)     = s;
    K(0u, 2u)     = cx;
    K(1u, 2u)     = cy;

    // create truth wTb
    Pose3Type const truth_wTb(Rot3Type::Rz(M_PI / 2), Point3Type());
    GTPose3 const   gtsam_truth_wTb(GTRot3::Rz(M_PI / 2), GTPoint3());
    GTPose3 const   gtsam_init_wTb(GTRot3::Rz(M_PI / 2), GTPoint3(0.1, 0.1, 0.0));

    // create bTc
    Pose3Type const bTc =
        Pose3Type(Rot3Type::Rz(-M_PI / 2), Point3Type()) * Pose3Type(Rot3Type::Rx(-M_PI / 2), Point3Type());

    // create pole map point
    // there are 6 poles placed in the road. ego car is on the middle of road. o is pole, D is car.
    // ---------o--------o--------o----
    // D
    // ---------o--------o--------o----
    std::vector<PoleMapPoint> map_points;

    Scalar       left_x = -5.0, right_x = 5.0;
    Scalar const y = -10.0;
    Scalar const z = 5.0;

    for (uint16_t i = 0u; i < 3u; i++)
    {
        PoleMapPoint pole_map_point;
        Point3Type   start_map_point(left_x, y + 5.0 * i, 0.0);
        pole_map_point.start = start_map_point;
        Point3Type end_map_point(left_x, y + 5.0 * i, z);
        pole_map_point.end = end_map_point;
        map_points.push_back(pole_map_point);
    }

    for (uint16_t i = 0u; i < 3u; i++)
    {
        PoleMapPoint pole_map_point;
        Point3Type   start_map_point(right_x, y + 5.0 * i, 0.0);
        pole_map_point.start = start_map_point;
        Point3Type end_map_point(right_x, y + 5.0 * i, z);
        pole_map_point.end = end_map_point;
        map_points.push_back(pole_map_point);
    }

    // create project point
    std::vector<PoleImagePoint> image_points;

    for (PoleMapPoint const& point : map_points)
    {
        PoleImagePoint point2;

        Vector3Type start_point3 = K * ((truth_wTb * bTc).Inverse() * point.start).As<Vector3Type>();
        Point2Type  start_point2(start_point3[0u] / start_point3[2u], start_point3[1u] / start_point3[2u]);
        point2.start = start_point2;

        Vector3Type end_point3 = K * ((truth_wTb * bTc).Inverse() * point.end).As<Vector3Type>();
        Point2Type  end_point2(end_point3[0u] / end_point3[2u], end_point3[1u] / end_point3[2u]);
        point2.end = end_point2;

        image_points.push_back(point2);
    }

    // create index
    uint64_t const index = 1u;
    Key const      key(X(index));

    // create graph
    Graph graph;

    // add projection line factor
    Scalar const sigma = 0.1;

    for (uint16_t i = 0u; i < map_points.size(); i++)
    {
        holo::localization::Line2Type const line =
            holo::localization::Line2Type(image_points[i].start, image_points[i].end);

        LineFactor                          start_line_factor(index, map_points[i].start, bTc, K, line, sigma);
        gtsam::NoiseModelFactor::shared_ptr start_line_factor_ptr;
        start_line_factor_ptr.reset(static_cast<gtsam::NoiseModelFactor*>(start_line_factor.GetFactor()));
        graph.add(start_line_factor_ptr);

        LineFactor                          end_line_factor(index, map_points[i].end, bTc, K, line, sigma);
        gtsam::NoiseModelFactor::shared_ptr end_line_factor_ptr;
        end_line_factor_ptr.reset(static_cast<gtsam::NoiseModelFactor*>(end_line_factor.GetFactor()));
        graph.add(end_line_factor_ptr);
    }

    // add values
    Values values;
    values.insert(key, gtsam_init_wTb);

    // optimize
    LMParams const param;
    LMOptimizer    optimizer(graph, values, param);
    Values const   results = optimizer.optimize();

    // convert result
    GTPose3 const est_pose = results.at<GTPose3>(key);

    ASSERT_TRUE(assert_equal(GTPoint3(est_pose.translation()), gtsam_init_wTb.translation(), 1e-5));
    ASSERT_TRUE(assert_equal(GTPoint3(est_pose.rotation().rpy()), GTPoint3(gtsam_init_wTb.rotation().rpy()), 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TestProjectionLineFactor, HuberLossAndCheiralityExceptionInEvaluateError)
{
    // create camera intrinsic
    Scalar const fx = Scalar(960);
    Scalar const fy = Scalar(512);
    Scalar const s  = Scalar(0.0);
    Scalar const cx = Scalar(1920 / 2);
    Scalar const cy = Scalar(1024 / 2);

    Matrix3Type K = Matrix3Type::Identity();
    K(0u, 0u)     = fx;
    K(1u, 1u)     = fy;
    K(0u, 1u)     = s;
    K(0u, 2u)     = cx;
    K(1u, 2u)     = cy;

    // create truth wTb
    Pose3Type const truth_wTb(Rot3Type::Rz(M_PI / 2), Point3Type());
    GTPose3 const   gtsam_truth_wTb(GTRot3::Rz(M_PI / 2), GTPoint3());

    // create bTc
    Pose3Type const bTc =
        Pose3Type(Rot3Type::Rz(-M_PI / 2), Point3Type()) * Pose3Type(Rot3Type::Rx(-M_PI / 2), Point3Type());

    // create pole map point
    Point3Type map_point(-5.0, -10.0, 5.0);
    // create project point
    std::vector<Point2Type> image_points{Point2Type(0.0, 0.0), Point2Type(1.0, 1.0)};

    // create index
    uint64_t const index = 1u;

    // create noise sigma
    Scalar const sigma = 0.1;

    // create huber loss
    Scalar const huber_loss_threshold = 0.1;

    // create projection line factor and initial values
    holo::localization::Line2Type const line(image_points[0u], image_points[1u]);
    LineFactor                          line_factor(index, map_point, bTc, K, line, sigma, huber_loss_threshold);
    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(line_factor.GetFactor()));
    Key const key(X(index));
    Values    values;
    values.insert(key, gtsam_truth_wTb);

    // evaluate error
    std::vector<gtsam::Matrix> H;
    H.resize(1u);
    gtsam::Vector e;
    e = factor->unwhitenedError(values, H);

    // check results
    ASSERT_EQ(e(0u), 0.0);
    ASSERT_EQ(H.at(0u), gtsam::Matrix::Zero(1u, 6u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TestProjectionLineFactor, DefaultConstructor)
{
    holo::localization::internal::ProjectionLineFactor();
}

/*****************************************************************************/
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
