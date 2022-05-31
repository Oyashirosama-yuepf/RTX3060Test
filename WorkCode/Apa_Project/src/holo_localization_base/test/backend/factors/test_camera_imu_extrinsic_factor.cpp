/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_camera_imu_extrinsic_factor.cpp
 * @brief uint test for camera imu extrinsic factor
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2020-04-21"
 */

#include <gtest/gtest.h>
#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Cal3_S2.h>
#include <gtsam/geometry/Point2.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/geometry/SimpleCamera.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>

#include <holo/localization/backend/factors/camera_imu_extrinsic_factor.h>
#include <holo/localization/sam/factors/internal/camera_imu_extrinsic_factor_inl.h>
#include <holo/log/hololog.h>

using gtsam::symbol_shorthand::L;
using gtsam::symbol_shorthand::T;
using gtsam::symbol_shorthand::X;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CameraImuExtrinsicFactor, Optimize)
{
    /// @brief gtsam type ground truth
    gtsam::Cal3_S2::shared_ptr const K = boost::make_shared<gtsam::Cal3_S2>(900.0, 900.0, 0.0, 640.0, 510.0);
    std::vector<gtsam::Point3> const gt_pt3_ws{gtsam::Point3(23.0, 7.5, 9.0), gtsam::Point3(22.5, 5.0, 7.0),
                                               gtsam::Point3(25.0, 2.5, 8.0)};
    holo::float64_t                  roll  = -M_PI / 2.0;
    holo::float64_t                  pitch = 0.0;
    holo::float64_t                  yaw   = -M_PI / 2.0;
    gtsam::Vector3                   rpy(roll, pitch, yaw);
    gtsam::Rot3 const                iRc = gtsam::Rot3::RzRyRx(roll, pitch, yaw);
    gtsam::Point3 const              itc = gtsam::Point3(2.0, 0.0, 1.0);
    gtsam::Pose3 const               iTc(iRc, itc);
    holo::uint64_t                   rpy_index = 0u;
    holo::uint64_t                   itc_index = 1u;
    holo::localization::Vector2Type  sigmas{0.1, 0.1};
    holo::localization::Matrix3Type  camera_k(K->fx(), K->skew(), K->px(), 0.0, K->fy(), K->py(), 0.0, 0.0, 1.0);

    /// @brief construct factor graph
    holo::uint16_t              num_poses = 3u;
    gtsam::NonlinearFactorGraph graph;
    gtsam::Values               values;
    gtsam::Values               gt_poses;

    for (holo::uint16_t i = 0u; i < gt_pt3_ws.size(); i++)
    {
        for (holo::uint16_t j = 0u; j < num_poses; j++)
        {
            holo::float64_t                              step  = holo::float64_t(j);
            holo::float64_t const                        roll  = 0.01 * step;
            holo::float64_t const                        pitch = -0.03 * step;
            holo::float64_t const                        yaw   = 0.03 * step;
            holo::float64_t const                        x     = 4.0 + 1.0 * step;
            holo::float64_t const                        y     = 5.0 - 0.5 * step;
            holo::float64_t const                        z     = 6.0 + 0.5 * step;
            gtsam::Rot3 const                            wRi   = gtsam::Rot3::RzRyRx(roll, pitch, yaw);
            gtsam::Point3 const                          wti   = gtsam::Point3(x, y, z);
            gtsam::Pose3 const                           wTi(wRi, wti);
            gtsam::SimpleCamera                          simple_camera(wTi * iTc, *K);
            gtsam::Point2 const                          measurement = simple_camera.projectSafe(gt_pt3_ws.at(i)).first;
            holo::localization::Point2Type const         measured(measurement.x(), measurement.y());
            holo::localization::CameraImuExtrinsicFactor camera_imu_extrinsic_factor(
                sigmas, j, i, rpy_index, itc_index, camera_k, measured, false, false, false, false, false, false);
            gtsam::NoiseModelFactor::shared_ptr factor;
            factor.reset(static_cast<gtsam::NoiseModelFactor*>(camera_imu_extrinsic_factor.GetFactor()));
            graph.add(factor);
            gtsam::Key const wTi_key = X(j);

            if (!values.exists(wTi_key))
            {
                gtsam::Rot3 const noise_wRi =
                    gtsam::Rot3::RzRyRx(roll + 0.01 * step, pitch + 0.01 * step, yaw - 0.01 * step);
                gtsam::Point3 const noise_wti = wti + gtsam::Point3(0.1 * step, -0.1 * step, 0.2 * step);
                gtsam::Pose3 const  noise_wTi(noise_wRi, noise_wti);
                values.insert(wTi_key, noise_wTi);  ///< add noise values as initial values for optimization
                gt_poses.insert(wTi_key, wTi);      ///< store ground truth
            }
        }
    }

    // add prior factor for first pose and between factor for two consecutive pose
    for (holo::uint16_t i = 0u; i < num_poses; i++)
    {
        gtsam::Key const   pose_i_key = X(i);
        gtsam::Pose3 const pose_i     = gt_poses.at<gtsam::Pose3>(pose_i_key);

        if (i == 0u)
        {
            graph.add(
                gtsam::PriorFactor<gtsam::Pose3>(pose_i_key, pose_i, gtsam::noiseModel::Isotropic::Sigma(6u, 1e-6)));
        }
        else
        {
            gtsam::Key const   pose_i_1_key = X(i - 1u);
            gtsam::Pose3 const pose_i_1     = gt_poses.at<gtsam::Pose3>(pose_i_1_key);
            graph.add(gtsam::BetweenFactor<gtsam::Pose3>(pose_i_1_key, pose_i_key, pose_i_1.inverse() * pose_i,
                                                         gtsam::noiseModel::Isotropic::Sigma(6, 1e-3)));
        }
    }

    // add initial values for roll, pitch , yaw, itc and pt3_ws
    holo::float64_t const delta_roll  = 0.1;
    holo::float64_t const delta_pitch = 0.1;
    holo::float64_t const delta_yaw   = 0.1;
    gtsam::Vector3 const  initial_rpy = gtsam::Vector3(roll + delta_roll, pitch + delta_pitch, yaw + delta_yaw);
    gtsam::Vector3 const  initial_itc = itc + gtsam::Vector3(0.2, 0.2, 0.2);
    values.insert(T(rpy_index), initial_rpy);
    values.insert(T(itc_index), initial_itc);

    for (holo::uint16_t i = 0u; i < gt_pt3_ws.size(); i++)
    {
        gtsam::Point3 const noise_pt3_w = gt_pt3_ws.at(i) + gtsam::Point3(0.2 * i, -0.2 * i, 0.8 * i);
        values.insert(L(i), noise_pt3_w);
    }

    /// @brief optimize
    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, values, parameters);
    gtsam::Values                      optimized_values = optimizer.optimize();

    // check results
    ASSERT_TRUE(rpy.isApprox(optimized_values.at<gtsam::Vector3>(T(rpy_index)), 1e-5));  ///< 5e-4 degree
    ASSERT_TRUE(itc.isApprox(optimized_values.at<gtsam::Vector3>(T(itc_index)), 1e-5));

    for (holo::uint16_t i = 0u; i < gt_pt3_ws.size(); i++)
    {
        ASSERT_TRUE(gt_pt3_ws.at(i).equals(optimized_values.at<gtsam::Point3>(L(i))));
    }

    for (holo::uint16_t i = 0u; i < num_poses; i++)
    {
        gtsam::Pose3 const gt_pose        = gt_poses.at<gtsam::Pose3>(X(i));
        gtsam::Pose3 const optimized_pose = optimized_values.at<gtsam::Pose3>(X(i));
        ASSERT_TRUE(gt_pose.rotation().equals(optimized_pose.rotation()));
        ASSERT_TRUE(gt_pose.translation().equals(optimized_pose.translation()));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CameraImuExtrinsicFactor, Jacobian)
{
    /// @brief gtsam type ground truth
    gtsam::Cal3_S2::shared_ptr const K = boost::make_shared<gtsam::Cal3_S2>(900.0, 900.0, 0.0, 640.0, 510.0);
    gtsam::Point2 const              measurement(320.0, 255.0);
    holo::float64_t                  depth = 7.0;
    gtsam::Point2 const              pt2_c = K->calibrate(measurement);
    gtsam::Point3 const              pt3_c = depth * gtsam::Point3(pt2_c.x(), pt2_c.y(), 1.0);
    holo::float64_t                  roll  = -M_PI / 2.0;
    holo::float64_t                  pitch = 0.0;
    holo::float64_t                  yaw   = -M_PI / 2.0;
    gtsam::Vector3 const             rpy(roll, pitch, yaw);
    gtsam::Rot3 const                iRc = gtsam::Rot3::RzRyRx(roll, pitch, yaw);
    gtsam::Point3 const              itc = gtsam::Point3(2.0, 0.0, 1.0);
    gtsam::Pose3 const               iTc(iRc, itc);
    gtsam::Point3 const              pt3_i = iTc.transform_from(pt3_c);
    gtsam::Rot3 const                wRi   = gtsam::Rot3::RzRyRx(0.0, 0.0, 0.0);
    gtsam::Point3 const              wti   = gtsam::Point3(4.0, 5.0, 6.0);
    gtsam::Pose3 const               wTi(wRi, wti);
    gtsam::Point3 const              pt3_w = wTi.transform_from(pt3_i);

    /// @brierf holo type parameters
    holo::uint64_t                  wTi_index = 0u;
    holo::uint64_t                  ptw_index = 0u;
    holo::uint64_t                  rpy_index = 0u;
    holo::uint64_t                  itc_index = 1u;
    holo::localization::Vector2Type sigmas{0.1, 0.1};
    holo::localization::Matrix3Type camera_k(K->fx(), K->skew(), K->px(), 0.0, K->fy(), K->py(), 0.0, 0.0, 1.0);
    holo::localization::Point2Type  measured(measurement.x(), measurement.y());

    // define key
    gtsam::Key const wTi_key = X(wTi_index);
    gtsam::Key const ptw_key = L(ptw_index);
    gtsam::Key const rpy_key = T(rpy_index);
    gtsam::Key const itc_key = T(itc_index);

    // add initial values
    gtsam::Values         values;
    gtsam::Rot3 const     noise_wRi = gtsam::Rot3::RzRyRx(0.1, 0.1, 0.1);
    gtsam::Point3 const   noise_wti = gtsam::Point3(4.0, 5.0, 6.0);
    gtsam::Pose3 const    noise_wTi(noise_wRi, noise_wti);
    gtsam::Point3 const   noise_pt3_w = pt3_w + gtsam::Point3(0.1, 0.1, 0.1);
    holo::float64_t const noise_roll  = roll + 0.1;
    holo::float64_t const noise_pitch = pitch + 0.1;
    holo::float64_t const noise_yaw   = yaw + 0.1;
    gtsam::Vector3 const  noise_rpy(noise_roll, noise_pitch, noise_yaw);
    gtsam::Vector3 const  noise_itc = itc + gtsam::Vector3(0.1, 0.0, 0.1);
    values.insert(wTi_key, noise_wTi);
    values.insert(ptw_key, noise_pt3_w);
    values.insert(rpy_key, noise_rpy);
    values.insert(itc_key, noise_itc);

    /* check jacobian equal */
    holo::localization::CameraImuExtrinsicFactor camera_imu_extrinsic_factor(sigmas, wTi_index, ptw_index, rpy_index,
                                                                             itc_index, camera_k, measured, false,
                                                                             false, false, false, false, false);

    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(camera_imu_extrinsic_factor.GetFactor()));

    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("CameraImuExtrinsicFactor", *factor, values, 1e-8, 1e-4));

    /* check jacobian not equal when fix the variable */
    holo::localization::CameraImuExtrinsicFactor camera_imu_extrinsic_factor1(
        sigmas, wTi_index, ptw_index, rpy_index, itc_index, camera_k, measured, true, true, true, true, true, true);

    gtsam::NoiseModelFactor::shared_ptr factor1;
    factor1.reset(static_cast<gtsam::NoiseModelFactor*>(camera_imu_extrinsic_factor1.GetFactor()));

    // check results
    ASSERT_FALSE(gtsam::internal::testFactorJacobians("CameraImuExtrinsicFactor", *factor1, values, 1e-8, 1e-4));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CameraImuExtrinsicFactor, NormalFunction)
{
    /// @brief gtsam type ground truth
    gtsam::Cal3_S2::shared_ptr const K = boost::make_shared<gtsam::Cal3_S2>(900.0, 900.0, 0.0, 640.0, 510.0);
    gtsam::Point2 const              measurement(320.0, 255.0);
    gtsam::Vector2                   sigmas_value(1.0, 1.0);
    gtsam::SharedNoiseModel const    noise_model = gtsam::noiseModel::Diagonal::Sigmas(sigmas_value);

    /// @brierf holo type parameters
    holo::uint64_t wTi_index = 0u;
    holo::uint64_t ptw_index = 0u;
    holo::uint64_t rpy_index = 0u;
    holo::uint64_t itc_index = 1u;

    // define key
    gtsam::Key const wTi_key = X(wTi_index);
    gtsam::Key const ptw_key = L(ptw_index);
    gtsam::Key const rpy_key = T(rpy_index);
    gtsam::Key const itc_key = T(itc_index);

    holo::localization::internal::CameraImuExtrinsicFactor camera_imu_extrinsic_factor(
        noise_model, wTi_key, ptw_key, rpy_key, itc_key, K, measurement, false, false, false, false, false, false);

    /* check normal function */
    ASSERT_TRUE(camera_imu_extrinsic_factor.GetMeasurement().equals(measurement));
    ASSERT_EQ(camera_imu_extrinsic_factor.GetCalibration(), K);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CameraImuExtrinsicFactor, InternalDefaultConstructor)
{
    holo::localization::CameraImuExtrinsicFactor::TestDefaultConstructorOfInternalFactor();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
