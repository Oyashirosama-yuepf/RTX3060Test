/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_line_projection_factor.cpp
 * @brief This file defines test of line projection factor.
 * @author MaYufei(mayufei@holomatic.com)
 * @author Wenzhi Liu (liuwenzhi@holomatic.com)
 * @date "2022-01-18"
 */

#include <gtsam/nonlinear/NonlinearFactor.h>
#include <gtsam/nonlinear/factorTesting.h>

#include <gtest/gtest.h>
#include <holo/localization/sam/factors/line_projection_factor.h>
#include <holo/localization/sam/sam.h>
#include <holo/log/hololog.h>

using namespace holo;
using namespace localization;
using namespace internal;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GTPluckerLine GeneratePluckerLineFromEndpoints(GTVector4 const& endpoint1, GTVector4 const& endpoint2)
{
    GTMatrix4 const plucker_matrix = endpoint1 * endpoint2.transpose() - endpoint2 * endpoint1.transpose();
    GTVector3 const normal_vector(-plucker_matrix(1u, 2u), plucker_matrix(0u, 2u), -plucker_matrix(0u, 1u));
    GTVector3 const direction_vector = GTVector3(plucker_matrix.block<3u, 1u>(0u, 3u));
    GTPluckerLine   plucker_line     = GTPluckerLine(normal_vector, direction_vector);
    return plucker_line;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineProjectionFactor::Measurement GenerateMeasurementFromPoseAndEndpoints(GTPose3 const&   pose,
                                                                          GTVector4 const& endpoint1,
                                                                          GTVector4 const& endpoint2)
{
    GTPoint3 const endpoint_a_in_camera_frame = pose.transform_to(GTPoint3(endpoint1(0), endpoint1(1), endpoint1(2)));
    GTPoint3 const endpoint_b_in_camera_frame = pose.transform_to(GTPoint3(endpoint2(0), endpoint2(1), endpoint2(2)));

    gtsam::Unit3                      measured_ray1 = gtsam::Unit3::FromPoint3(endpoint_a_in_camera_frame);
    gtsam::Unit3                      measured_ray2 = gtsam::Unit3::FromPoint3(endpoint_b_in_camera_frame);
    LineProjectionFactor::Measurement measurement;
    measurement.rays[0] = measured_ray1;
    measurement.rays[1] = measured_ray2;
    return measurement;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ScaleFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3>
{
public:
    using Ptr      = boost::shared_ptr<ScaleFactor>;
    using ConstPtr = boost::shared_ptr<const ScaleFactor>;
    using Base     = gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3>;

    ScaleFactor(const gtsam::Key& pose1_key, const gtsam::Key& pose2_key, const GTScalar measurement,
                const gtsam::SharedNoiseModel& model);

    virtual gtsam::Vector evaluateError(const gtsam::Pose3& T1, const gtsam::Pose3& T2,
                                        boost::optional<gtsam::Matrix&> H1 = boost::none,
                                        boost::optional<gtsam::Matrix&> H2 = boost::none) const override;

private:
    GTScalar measurement_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScaleFactor::ScaleFactor(const gtsam::Key& pose1_key, const gtsam::Key& pose2_key, const GTScalar measurement,
                         const gtsam::SharedNoiseModel& model)
  : Base(model, pose1_key, pose2_key), measurement_(measurement)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector ScaleFactor::evaluateError(const gtsam::Pose3& T1, const gtsam::Pose3& T2,
                                         boost::optional<gtsam::Matrix&> H1, boost::optional<gtsam::Matrix&> H2) const
{
    GTPoint3 const t1         = T1.translation();
    GTPoint3 const t2         = T2.translation();
    GTScalar       prediction = t1.dist(t2);
    prediction                = std::pow(prediction, 2);

    if (H1)
    {
        gtsam::Matrix13 J_e_p =
            (gtsam::Matrix13() << 2.0 * (t1.x() - t2.x()), 2.0 * (t1.y() - t2.y()), 2.0 * (t1.z() - t2.z())).finished();

        gtsam::Matrix13 J_e_t = J_e_p * T1.rotation().matrix();

        *H1 = (gtsam::Matrix16() << 0.0, 0.0, 0.0, J_e_t(0u, 0u), J_e_t(0u, 1u), J_e_t(0u, 2u)).finished();
    }

    if (H2)
    {
        gtsam::Matrix13 J_e_p =
            (gtsam::Matrix13() << -2.0 * (t1.x() - t2.x()), -2.0 * (t1.y() - t2.y()), -2.0 * (t1.z() - t2.z()))
                .finished();

        gtsam::Matrix13 J_e_t = J_e_p * T2.rotation().matrix();

        *H2 = (gtsam::Matrix16() << 0.0, 0.0, 0.0, J_e_t(0u, 0u), J_e_t(0u, 1u), J_e_t(0u, 2u)).finished();
    }

    // @brief return error vector
    return gtsam::Vector1(prediction - measurement_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GTScalar GetRandData(GTScalar const value = 0.0, GTScalar const th = 0.0)
{
    GTScalar norm = static_cast<GTScalar>(rand() % 10000) / 10000.0 - 0.5;
    return value + th * norm;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LineProjectionFactor, JacobianMatrixOfPlaneError)
{
    // construct two endpoint of line in world frame
    GTVector4 const endpoint_a(0.0, 0.5, -0.5, 1.0);
    GTVector4 const endpoint_b(0.0, 0.5, -1.0, 1.0);

    // construct actual space line landmark
    GTMatrix4 const         plucker_matrix = endpoint_a * endpoint_b.transpose() - endpoint_b * endpoint_a.transpose();
    GTVector3 const         normal_vector(-plucker_matrix(1u, 2u), plucker_matrix(0u, 2u), -plucker_matrix(0u, 1u));
    GTVector3 const         direction_vector = GTVector3(plucker_matrix.block<3u, 1u>(0u, 3u));
    GTPluckerLine           plucker_line     = GTPluckerLine(normal_vector, direction_vector);
    GTOrthonormalLine const orthonormal_line(plucker_line);

    // construct pose of camera to world
    GTRot3 const   wTc_rotation    = GTRot3::Ypr(0.0, M_PI / 2, M_PI / 2);
    GTPoint3 const wTc_translation = GTPoint3(1.0, 0.5, 0.5);
    GTPose3 const  wTc             = GTPose3(wTc_rotation.inverse(), wTc_translation);
    // construct pose of body to world
    GTRot3 const   wTb_rotation    = GTRot3::Ypr(0.0, M_PI, M_PI / 2);
    GTPoint3 const wTb_translation = GTPoint3(0.0, 1.0, 0.5);
    GTPose3 const  wTb             = GTPose3(wTb_rotation.inverse(), wTb_translation);

    // compute pose of camera to body
    GTPose3 const bTc = wTb.inverse() * wTc;

    // construct camera intrinsic matrix
    gtsam::Cal3_S2::shared_ptr K = nullptr;

    // transform two endpoints to camera frame
    GTPoint3 const endpoint_a_in_camera_frame =
        wTc.inverse().transform_from(GTPoint3(endpoint_a(0), endpoint_a(1), endpoint_a(2)));
    GTPoint3 const endpoint_b_in_camera_frame =
        wTc.inverse().transform_from(GTPoint3(endpoint_b(0), endpoint_b(1), endpoint_b(2)));

    // construct two detected rays
    gtsam::Unit3 measured_ray1 = gtsam::Unit3::FromPoint3(endpoint_a_in_camera_frame);
    gtsam::Unit3 measured_ray2 = gtsam::Unit3::FromPoint3(endpoint_b_in_camera_frame);

    // construct line projection factor and add to factor graph
    gtsam::Key                        pose_key             = symbol_shorthand::X(0u);
    gtsam::Key                        orthonormal_line_key = symbol_shorthand::O(0u);
    LineProjectionFactor::Measurement measurement;
    measurement.rays[0] = measured_ray1;
    measurement.rays[1] = measured_ray2;
    GTVector2 sigmas;
    sigmas << 1.0, 1.0;
    gtsam::SharedNoiseModel const noise_model = GTDiagonal::Sigmas(sigmas);
    LineProjectionFactor line_projection_factor(pose_key, orthonormal_line_key, noise_model, measurement, bTc, K);

    // add initial values to factor graph
    GTValues values;
    values.insert<GTPose3>(pose_key, wTb);
    values.insert<GTOrthonormalLine>(orthonormal_line_key, orthonormal_line);

    ASSERT_TRUE(
        gtsam::internal::testFactorJacobians("jacobian of error to pose", line_projection_factor, values, 1e-8, 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LineProjectionFactor, JacobianMatrixOfPointToLineError)
{
    // construct two endpoint of line in world frame
    GTVector4 const endpoint_a(0.0, 0.5, -0.5, 1.0);
    GTVector4 const endpoint_b(0.0, 0.5, -1.0, 1.0);

    // construct actual space line landmark
    GTMatrix4 const         plucker_matrix = endpoint_a * endpoint_b.transpose() - endpoint_b * endpoint_a.transpose();
    GTVector3 const         normal_vector(-plucker_matrix(1u, 2u), plucker_matrix(0u, 2u), -plucker_matrix(0u, 1u));
    GTVector3 const         direction_vector = GTVector3(plucker_matrix.block<3u, 1u>(0u, 3u));
    GTPluckerLine           plucker_line     = GTPluckerLine(normal_vector, direction_vector);
    GTOrthonormalLine const orthonormal_line(plucker_line);

    // construct pose of camera to world
    GTRot3 const   wTc_rotation    = GTRot3::Ypr(0.0, M_PI / 2, M_PI / 2);
    GTPoint3 const wTc_translation = GTPoint3(1.0, 0.5, 0.5);
    GTPose3 const  wTc             = GTPose3(wTc_rotation.inverse(), wTc_translation);
    // construct pose of body to world
    GTRot3 const   wTb_rotation    = GTRot3::Ypr(0.0, M_PI, M_PI / 2);
    GTPoint3 const wTb_translation = GTPoint3(0.0, 1.0, 0.5);
    GTPose3 const  wTb             = GTPose3(wTb_rotation.inverse(), wTb_translation);

    // compute pose of camera to body
    GTPose3 const bTc = wTb.inverse() * wTc;

    // construct camera intrinsic matrix
    gtsam::Cal3_S2::shared_ptr K = boost::make_shared<gtsam::Cal3_S2>(1200.0, 1200.0, 0.0, 960.0, 540.0);

    // project two endpoints to image plane
    GTPoint3 const endpoint_a_in_camera_frame =
        wTc.inverse().transform_from(GTPoint3(endpoint_a(0), endpoint_a(1), endpoint_a(2)));
    GTPoint3 const endpoint_b_in_camera_frame =
        wTc.inverse().transform_from(GTPoint3(endpoint_b(0), endpoint_b(1), endpoint_b(2)));

    // construct two detected rays
    gtsam::Unit3 measured_ray1 = gtsam::Unit3::FromPoint3(endpoint_a_in_camera_frame);
    gtsam::Unit3 measured_ray2 = gtsam::Unit3::FromPoint3(endpoint_b_in_camera_frame);

    // construct line projection factor and add to factor graph
    gtsam::Key                        pose_key             = symbol_shorthand::X(0u);
    gtsam::Key                        orthonormal_line_key = symbol_shorthand::O(0u);
    LineProjectionFactor::Measurement measurement;
    measurement.rays[0] = measured_ray1;
    measurement.rays[1] = measured_ray2;
    GTVector2 sigmas;
    sigmas << 1.0, 1.0;
    gtsam::SharedNoiseModel const noise_model = GTDiagonal::Sigmas(sigmas);
    LineProjectionFactor line_projection_factor(pose_key, orthonormal_line_key, noise_model, measurement, bTc, K);

    // add initial values to factor graph
    GTValues values;
    values.insert<GTPose3>(pose_key, wTb);
    values.insert<GTOrthonormalLine>(orthonormal_line_key, orthonormal_line);
    // the tolerence of jacobian error is 1e-3!!!
    ASSERT_TRUE(
        gtsam::internal::testFactorJacobians("jacobian of error to pose", line_projection_factor, values, 1e-8, 1e-3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LineProjectionFactor, OptimizePlaneError)
{
    // confirm value number
    uint16_t camera_number      = 3u;
    uint16_t line_number        = 6u;
    bool_t   add_all_pose_prior = false;

    // construct space line value
    gtsam::Vector4 endpoint_a[line_number];
    gtsam::Vector4 endpoint_b[line_number];
    gtsam::Vector4 endpoint_a_obs[line_number];
    gtsam::Vector4 endpoint_b_obs[line_number];
    gtsam::Key     line_key[line_number];

    std::vector<GTPluckerLine>     plucker_line;
    std::vector<GTOrthonormalLine> orthonormal_line;
    GTValues                       initial_values;

    for (uint16_t i = 0u; i < line_number; i++)
    {
        // construct space line ground truth
        endpoint_a[i] = GTVector4(GetRandData(0.0, 20.0), GetRandData(0.0, 20.0), GetRandData(10.0, 1.5), 1.0);
        endpoint_b[i] = GTVector4(GetRandData(0.0, 20.0), GetRandData(0.0, 20.0), GetRandData(10.0, 1.5), 1.0);
        plucker_line.push_back(GeneratePluckerLineFromEndpoints(endpoint_a[i], endpoint_b[i]));
        orthonormal_line.push_back(GTOrthonormalLine(plucker_line[i]));
        line_key[i] = symbol_shorthand::O(i);

        // construct space line initial value
        GTVector4 endpoint_a_initial =
            endpoint_a[i] + GTVector4(GetRandData(0., 5.0), GetRandData(0., 5.0), GetRandData(0., 1.5), 0.0);
        GTVector4 endpoint_b_initial =
            endpoint_b[i] + GTVector4(GetRandData(0., 5.0), GetRandData(0., 5.0), GetRandData(0., 1.5), 0.0);
        GTPluckerLine initial_plucker_line = GeneratePluckerLineFromEndpoints(endpoint_a_initial, endpoint_b_initial);
        GTOrthonormalLine const initial_orthonormal_line(initial_plucker_line);

        // add line initial values
        initial_values.insert<GTOrthonormalLine>(line_key[i], initial_orthonormal_line);

        // construct space line observations
        endpoint_a_obs[i] =
            endpoint_a[i] + GTVector4(GetRandData(0., 0.1), GetRandData(0., 0.1), GetRandData(0., 0.1), 0.0);
        endpoint_b_obs[i] =
            endpoint_b[i] + GTVector4(GetRandData(0., 0.1), GetRandData(0., 0.1), GetRandData(0., 0.1), 0.0);
    }

    GTPose3       wTb[camera_number];
    GTPose3       wTc[camera_number];
    GTPose3       wTb_initial[camera_number];
    GTPose3       wTb_obs[camera_number];
    GTPose3       wTc_obs[camera_number];
    gtsam::Key    pose_key[camera_number];
    GTPose3 const bTc = GTPose3::identity();

    // construct pose value
    for (uint16_t i = 0u; i < camera_number; i++)
    {
        // construct pose ground truth
        GTScalar yaw   = GetRandData(0.0, 1.5);
        GTScalar pitch = GetRandData(0.0, 0.2);
        GTScalar roll  = GetRandData(0.0, 0.3);
        GTScalar tx    = GetRandData(0.0, 10.0);
        GTScalar ty    = GetRandData(0.0, 10.0);
        GTScalar tz    = GetRandData(0.0, 2.0);
        wTb[i]         = GTPose3(GTRot3::Ypr(yaw, pitch, roll), GTPoint3(tx, ty, tz));
        wTc[i]         = wTb[i] * bTc;
        pose_key[i]    = symbol_shorthand::X(i);

        // construct pose initial value
        GTScalar yaw_initial   = yaw + GetRandData(0.0, 0.2);
        GTScalar pitch_initial = pitch + GetRandData(0.0, 0.2);
        GTScalar roll_initial  = roll + GetRandData(0.0, 0.2);
        GTScalar tx_initial    = tx + GetRandData(0.0, 5.0);
        GTScalar ty_initial    = ty + GetRandData(0.0, 5.0);
        GTScalar tz_initial    = tz + GetRandData(0.0, 2.0);
        wTb_initial[i]         = GTPose3(GTRot3::Ypr(yaw_initial, pitch_initial, roll_initial),
                                 GTPoint3(tx_initial, ty_initial, tz_initial));

        // add pose initial values
        initial_values.insert<GTPose3>(pose_key[i], wTb_initial[i]);

        // construct pose observation value
        GTScalar yaw_obs   = yaw + GetRandData(0.0, 0.01);
        GTScalar pitch_obs = pitch + GetRandData(0.0, 0.01);
        GTScalar roll_obs  = roll + GetRandData(0.0, 0.01);
        GTScalar tx_obs    = tx + GetRandData(0.0, 0.05);
        GTScalar ty_obs    = ty + GetRandData(0.0, 0.05);
        GTScalar tz_obs    = tz + GetRandData(0.0, 0.02);
        wTb_obs[i]         = GTPose3(GTRot3::Ypr(yaw_obs, pitch_obs, roll_obs), GTPoint3(tx_obs, ty_obs, tz_obs));
        wTc_obs[i]         = wTb_obs[i] * bTc;
    }

    // construct factor graph
    GTNonlinearFactorGraph factor_graph;

    // construct prior factor
    GTVector6 sigmas_for_prior;
    sigmas_for_prior << 0.001, 0.001, 0.001, 0.001, 0.001, 0.001;
    gtsam::SharedNoiseModel const noise_model_for_prior = GTDiagonal::Sigmas(sigmas_for_prior);

    std::vector<gtsam::PriorFactor<GTPose3>> priors;

    if (add_all_pose_prior)
    {
        for (int i = 0; i < camera_number; i++)
        {
            priors.push_back(gtsam::PriorFactor<GTPose3>(pose_key[i], wTb[i], noise_model_for_prior));
            factor_graph.add(priors[i]);
        }
    }
    else
    {
        gtsam::PriorFactor<GTPose3> pose_prior_factor =
            gtsam::PriorFactor<GTPose3>(symbol_shorthand::X(0), wTb[0], noise_model_for_prior);
        factor_graph.add(pose_prior_factor);
    }

    // construct line projection factor
    gtsam::Cal3_S2::shared_ptr K = nullptr;
    GTVector2                  projection_sigmas;
    projection_sigmas << 0.001, 0.001;
    gtsam::SharedNoiseModel const projection_noise_model = GTDiagonal::Sigmas(projection_sigmas);

    for (int i = 0; i < camera_number; i++)
    {
        for (int j = 0; j < line_number; j++)
        {
            LineProjectionFactor::Measurement measurement =
                GenerateMeasurementFromPoseAndEndpoints(wTc_obs[i], endpoint_a_obs[j], endpoint_b_obs[j]);
            LineProjectionFactor line_projection_factor(pose_key[i], line_key[j], projection_noise_model, measurement,
                                                        bTc, K);
            factor_graph.add(line_projection_factor);
        }
    }

    // construct scale factor
    gtsam::Vector1 sigmas_for_scale_factor;
    sigmas_for_scale_factor << 0.001;
    gtsam::SharedNoiseModel const noise_model_for_scale_factor = GTDiagonal::Sigmas(sigmas_for_scale_factor);
    GTScalar const                distance                     = wTb[0].translation().dist(wTb[1].translation());
    ScaleFactor                   scale_factor =
        ScaleFactor(pose_key[0], pose_key[1], std::pow(distance, 2), noise_model_for_scale_factor);
    factor_graph.add(scale_factor);

    // start optimize
    gtsam::LevenbergMarquardtOptimizer optimizer(factor_graph, initial_values);
    gtsam::Values                      result = optimizer.optimize();

    // compare expected and estimated
    for (uint16_t i = 0u; i < camera_number; i++)
    {
        /* code */
        GTPose3 estimated_pose = result.at<GTPose3>(pose_key[i]);
    }

    for (uint16_t i = 0u; i < line_number; i++)
    {
        OrthonormalLine estimated_line = result.at<GTOrthonormalLine>(line_key[i]);
        ASSERT_EQ(estimated_line.equals(orthonormal_line[i], 1e-2), true);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LineProjectionFactor, OptimizePointToLineError)
{
    // confirm value number
    uint16_t camera_number      = 6u;
    uint16_t line_number        = 10u;
    bool_t   add_all_pose_prior = false;

    // construct space line value
    gtsam::Vector4 endpoint_a[line_number];
    gtsam::Vector4 endpoint_b[line_number];
    gtsam::Vector4 endpoint_a_obs[line_number];
    gtsam::Vector4 endpoint_b_obs[line_number];
    gtsam::Key     line_key[line_number];

    std::vector<GTPluckerLine>     plucker_line;
    std::vector<GTOrthonormalLine> orthonormal_line;
    GTValues                       initial_values;

    for (uint16_t i = 0u; i < line_number; i++)
    {
        // construct space line ground truth
        endpoint_a[i] = GTVector4(GetRandData(0.0, 20.0), GetRandData(0.0, 20.0), GetRandData(10.0, 1.5), 1.0);
        endpoint_b[i] = GTVector4(GetRandData(0.0, 20.0), GetRandData(0.0, 20.0), GetRandData(10.0, 1.5), 1.0);
        plucker_line.push_back(GeneratePluckerLineFromEndpoints(endpoint_a[i], endpoint_b[i]));
        orthonormal_line.push_back(GTOrthonormalLine(plucker_line[i]));
        line_key[i] = symbol_shorthand::O(i);

        // construct space line initial value
        GTVector4 endpoint_a_initial =
            endpoint_a[i] + GTVector4(GetRandData(0., 5.0), GetRandData(0., 5.0), GetRandData(0., 1.5), 0.0);
        GTVector4 endpoint_b_initial =
            endpoint_b[i] + GTVector4(GetRandData(0., 5.0), GetRandData(0., 5.0), GetRandData(0., 1.5), 0.0);
        GTPluckerLine initial_plucker_line = GeneratePluckerLineFromEndpoints(endpoint_a_initial, endpoint_b_initial);
        GTOrthonormalLine const initial_orthonormal_line(initial_plucker_line);

        // add line initial values
        initial_values.insert<GTOrthonormalLine>(line_key[i], initial_orthonormal_line);

        // construct space line observations
        endpoint_a_obs[i] =
            endpoint_a[i] + GTVector4(GetRandData(0., 0.01), GetRandData(0., 0.01), GetRandData(0., 0.01), 0.0);
        endpoint_b_obs[i] =
            endpoint_b[i] + GTVector4(GetRandData(0., 0.01), GetRandData(0., 0.01), GetRandData(0., 0.01), 0.0);
    }

    GTPose3       wTb[camera_number];
    GTPose3       wTc[camera_number];
    GTPose3       wTb_initial[camera_number];
    GTPose3       wTb_obs[camera_number];
    GTPose3       wTc_obs[camera_number];
    gtsam::Key    pose_key[camera_number];
    GTPose3 const bTc = GTPose3::identity();

    // construct pose value
    for (uint16_t i = 0u; i < camera_number; i++)
    {
        // construct pose ground truth
        GTScalar yaw   = GetRandData(0.0, 1.5);
        GTScalar pitch = GetRandData(0.0, 0.2);
        GTScalar roll  = GetRandData(0.0, 0.3);
        GTScalar tx    = GetRandData(0.0, 10.0);
        GTScalar ty    = GetRandData(0.0, 10.0);
        GTScalar tz    = GetRandData(0.0, 2.0);
        wTb[i]         = GTPose3(GTRot3::Ypr(yaw, pitch, roll), GTPoint3(tx, ty, tz));
        wTc[i]         = wTb[i] * bTc;
        pose_key[i]    = symbol_shorthand::X(i);

        // construct pose initial value
        GTScalar yaw_initial   = yaw + GetRandData(0.0, 0.2);
        GTScalar pitch_initial = pitch + GetRandData(0.0, 0.2);
        GTScalar roll_initial  = roll + GetRandData(0.0, 0.2);
        GTScalar tx_initial    = tx + GetRandData(0.0, 5.0);
        GTScalar ty_initial    = ty + GetRandData(0.0, 5.0);
        GTScalar tz_initial    = tz + GetRandData(0.0, 2.0);
        wTb_initial[i]         = GTPose3(GTRot3::Ypr(yaw_initial, pitch_initial, roll_initial),
                                 GTPoint3(tx_initial, ty_initial, tz_initial));

        // add pose initial values
        initial_values.insert<GTPose3>(pose_key[i], wTb_initial[i]);

        // construct pose observation value
        GTScalar yaw_obs   = yaw + GetRandData(0.0, 0.01);
        GTScalar pitch_obs = pitch + GetRandData(0.0, 0.01);
        GTScalar roll_obs  = roll + GetRandData(0.0, 0.01);
        GTScalar tx_obs    = tx + GetRandData(0.0, 0.05);
        GTScalar ty_obs    = ty + GetRandData(0.0, 0.05);
        GTScalar tz_obs    = tz + GetRandData(0.0, 0.02);
        wTb_obs[i]         = GTPose3(GTRot3::Ypr(yaw_obs, pitch_obs, roll_obs), GTPoint3(tx_obs, ty_obs, tz_obs));
        wTc_obs[i]         = wTb_obs[i] * bTc;
    }

    // construct factor graph
    GTNonlinearFactorGraph factor_graph;

    // construct prior factor
    GTVector6 sigmas_for_prior;
    sigmas_for_prior << 0.001, 0.001, 0.001, 0.001, 0.001, 0.001;
    gtsam::SharedNoiseModel const noise_model_for_prior = GTDiagonal::Sigmas(sigmas_for_prior);

    std::vector<gtsam::PriorFactor<GTPose3>> priors;

    if (add_all_pose_prior)
    {
        for (int i = 0; i < camera_number; i++)
        {
            priors.push_back(gtsam::PriorFactor<GTPose3>(pose_key[i], wTb[i], noise_model_for_prior));
            factor_graph.add(priors[i]);
        }
    }
    else
    {
        gtsam::PriorFactor<GTPose3> pose_prior_factor =
            gtsam::PriorFactor<GTPose3>(symbol_shorthand::X(0), wTb[0], noise_model_for_prior);
        factor_graph.add(pose_prior_factor);
    }

    // construct line projection factor
    gtsam::Cal3_S2::shared_ptr K = boost::make_shared<gtsam::Cal3_S2>(1200.0, 1200.0, 0.0, 960.0, 540.0);
    GTVector2                  projection_sigmas;
    projection_sigmas << 0.01, 0.01;
    gtsam::SharedNoiseModel const projection_noise_model = GTDiagonal::Sigmas(projection_sigmas);

    for (int i = 0; i < camera_number; i++)
    {
        for (int j = 0; j < line_number; j++)
        {
            LineProjectionFactor::Measurement measurement =
                GenerateMeasurementFromPoseAndEndpoints(wTc_obs[i], endpoint_a_obs[j], endpoint_b_obs[j]);
            LineProjectionFactor line_projection_factor(pose_key[i], line_key[j], projection_noise_model, measurement,
                                                        bTc, K);
            factor_graph.add(line_projection_factor);
        }
    }

    // construct scale factor
    gtsam::Vector1 sigmas_for_scale_factor;
    sigmas_for_scale_factor << 0.001;
    gtsam::SharedNoiseModel const noise_model_for_scale_factor = GTDiagonal::Sigmas(sigmas_for_scale_factor);
    GTScalar const                distance                     = wTb[0].translation().dist(wTb[1].translation());
    ScaleFactor                   scale_factor =
        ScaleFactor(pose_key[0], pose_key[1], std::pow(distance, 2), noise_model_for_scale_factor);
    factor_graph.add(scale_factor);

    // start optimize
    gtsam::LevenbergMarquardtOptimizer optimizer(factor_graph, initial_values);
    gtsam::Values                      result = optimizer.optimize();

    // compare expected and estimated
    for (uint16_t i = 0u; i < camera_number; i++)
    {
        /* code */
        GTPose3 estimated_pose = result.at<GTPose3>(pose_key[i]);
    }

    for (uint16_t i = 0u; i < line_number; i++)
    {
        OrthonormalLine estimated_line = result.at<GTOrthonormalLine>(line_key[i]);
        ASSERT_EQ(estimated_line.equals(orthonormal_line[i], 1e-2), true);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}