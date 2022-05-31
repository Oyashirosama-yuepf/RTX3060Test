/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_imu_body_extrinsic_factor.h
 * @brief define test for imu body extrinsic factor
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-10-12
 */

#include <gtest/gtest.h>

#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>

#include <holo/localization/backend/factors/imu_body_extrinsic_factor.h>
#include <holo/log/hololog.h>

using gtsam::symbol_shorthand::E;
using gtsam::symbol_shorthand::X;

using namespace holo;
using namespace holo::localization;
using WheelPreintegrationParams = WheelPreintegrationMeasurement::WheelPreintegrationParams;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ImuBodyFixture : public ::testing::Test
{
public:
    template <typename Scalar, int32_t Row>
    using VectorT = holo::numerics::VectorT<Scalar, Row>;
    /**
     * @brief Construct a new Imu Body Fixture object
     *
     */
    ImuBodyFixture()
      : origin_(Point3Type(0.0, 0.0, 0.0))
      , omega_z_(holo::geometry::Radian(5.0))
      , radius_(10.0)
      , imu_dur_(0.01)
      , pose_dur_(0.1)
    {
    }

    /**
     * @brief Destroy the Imu Body Fixture object
     *
     */
    virtual ~ImuBodyFixture()
    {
    }

    virtual void SetUp()
    {
        // generate ground truth iTb
        Scalar           roll  = 0.0;  // radian
        Scalar           pitch = 1.0;
        Scalar           yaw   = 1.0;
        Rot3Type const   iRb   = Rot3Type::RzRyRx(roll, pitch, yaw);
        Point3Type const itb   = Point3Type(0.0, 0.0, 0.0);
        gt_iTb_                = Pose3Type(iRb, itb);
    }

    /**
     * @brief generate navstate(body pose and velocity in body frame)
     *
     * @param stamp timestamp
     * @return Navstate
     */
    Navstate GenerateNavstate(Timestamp const& stamp) const
    {
        Scalar const    t    = stamp.ToSec();
        Pose3Type const pose = Pose3Type(Rot3Type::Rz(holo::geometry::Radian(90.0) + omega_z_ * t),
                                         Point3Type(origin_.GetX() + radius_ * std::cos(omega_z_ * t),
                                                    origin_.GetY() + radius_ * std::sin(omega_z_ * t), 0.0));

        // generate velocity in body frame
        VectorT<Scalar, 3u> const velocity_body = VectorT<Scalar, 3u>(omega_z_ * radius_, 0.0, 0.0);

        return Navstate(pose, velocity_body);
    }

    /**
     * @brief convert holo type pose to gtsam type
     *
     * @param pose holo type pose
     * @return gtsam::Pose3
     */
    gtsam::Pose3 ConvertHoloPoseToGtsamType(Pose3Type const& pose) const
    {
        Matrix4Type const             mat        = pose.ToMatrix();
        uint32_t const                array_size = mat.GetCols() * mat.GetRows();
        Eigen::Matrix<Scalar, 4u, 4u> result;
        memcpy(result.data(), mat.GetData(), sizeof(Scalar) * array_size);
        return gtsam::Pose3(result);
    }

    /**
     * @brief give start time, end time and initial imu pose compute new wheel preintegration measurement
     *        |  |  |  |  |  |  |  |  |  |
     *       imu
     *        |  |  |  |  |  |  |  |  |  |
     *       vel                                vel(velocity in body frame)
     *
     * @param start_t start timestamp
     * @param end_t end timestamp
     * @param Ri rotation of first imu
     * @return WheelPreintegrationMeasurement
     */
    WheelPreintegrationMeasurement ComputeNewPwm(Timestamp const& start_t, Timestamp const& end_t,
                                                 Rot3Type const& Ri) const
    {
        WheelPreintegrationParams      pwm_params = WheelPreintegrationParams();
        WheelPreintegrationMeasurement new_pwm(pwm_params, gt_iTb_);

        for (Timestamp t = start_t; t <= end_t; t += imu_dur_)
        {
            // generate body navstate
            Navstate const body_nav = GenerateNavstate(t);

            // get imu pose by iTb
            Pose3Type const imu_pose = body_nav.GetPose() * gt_iTb_.Inverse();

            // compute delta_Ril of imu
            Rot3Type const R_il = Ri.Inverse() * imu_pose.GetRotation();

            new_pwm.IntegrateMeasurement(body_nav.GetVelocity(), R_il, imu_dur_.ToSec());
        }

        return new_pwm;
    }

    /**
     * @brief Get the First Imu Pose And Pwm when given start time and end time
     *
     * @param start_t start timestamp
     * @param end_t end timestamp
     * @return std::pair<Pose3Type, WheelPreintegrationMeasurement>
     */
    std::pair<Pose3Type, WheelPreintegrationMeasurement> GetImuPoseAndPwm(Timestamp const& start_t,
                                                                          Timestamp const& end_t) const
    {
        // generate body navstate
        Navstate const body_nav = GenerateNavstate(start_t);

        // imu pose
        Pose3Type const imu_pose = body_nav.GetPose() * gt_iTb_.Inverse();

        WheelPreintegrationMeasurement const new_pwm = ComputeNewPwm(start_t, end_t, imu_pose.GetRotation());

        return std::make_pair(imu_pose, new_pwm);
    }

    /**
     * @brief Get the Ground Truth iTb
     *
     * @return const Pose3Type&
     */
    const Pose3Type& GetGroundTruthiTb() const
    {
        return gt_iTb_;
    }

    /**
     * @brief Get the Pose Duration object
     *
     * @return const Duration&
     */
    const Duration& GetPoseDuration() const
    {
        return pose_dur_;
    }

    virtual void TearDown()
    {
    }

private:
    ///@brief origin
    Point3Type origin_;

    ///@brief angular velocity of uniform circular motion
    Scalar omega_z_;

    ///@brief circumference radius
    Scalar radius_;

    ///@brief interval time of imu
    Duration imu_dur_;

    ///@brief interval time of pose
    Duration pose_dur_;

    ///@brief ground truth body pose in imu frame
    Pose3Type gt_iTb_;
};  // class ImuBodyFixture

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImuBodyFixture, Optimize)
{
    // get ground truth iTb
    Pose3Type const   iTb = GetGroundTruthiTb();
    Vector3Type const rpy = iTb.GetRotation().RPY();
    Point3Type const  itb = iTb.GetTranslation();

    // gtsam type rpy
    gtsam::Vector3 const rpy_gtsam(rpy.At(0u), rpy.At(1u), rpy.At(2u));

    // construct factor graph
    uint16_t                    num_poses = 4u;
    gtsam::NonlinearFactorGraph graph;
    gtsam::Values               values;
    gtsam::Values               gt_poses;

    // start timestamp
    Timestamp const t(0, 0);
    Duration const  seg       = GetPoseDuration();
    uint64_t const  iRb_index = 1u;

    for (uint16_t i = 0u; i < num_poses; i++)
    {
        Duration const dur(seg * Scalar(i));

        Timestamp const start_t = t + dur;
        Timestamp const end_t   = start_t + seg;

        Pose3Type                      imu_pose;
        WheelPreintegrationMeasurement new_pwm;
        std::tie(imu_pose, new_pwm) = GetImuPoseAndPwm(start_t, end_t);

        gtsam::Pose3 const wTi = ConvertHoloPoseToGtsamType(imu_pose);

        gtsam::Key const wTi_key = X(i);

        if (!values.exists(wTi_key))
        {
            gtsam::Vector3    imu_rpy = wTi.rotation().rpy();
            gtsam::Point3     wti     = wTi.translation();
            gtsam::Rot3 const noise_wRi =
                gtsam::Rot3::RzRyRx(imu_rpy(0u) + 0.01, imu_rpy(1u) + 0.01, imu_rpy(2u) - 0.01);
            gtsam::Point3 const noise_wti = wti + gtsam::Point3(0.1, -0.1, 0.2);
            gtsam::Pose3 const  noise_wTi(noise_wRi, noise_wti);

            values.insert(wTi_key, noise_wTi);  ///< add noise values as initial values for optimization
            gt_poses.insert(wTi_key, wTi);      ///< store ground truth
        }

        // create imu body extrinsic factors
        if (i < num_poses - 1u)
        {
            ImuBodyExtrinsicFactor              imu_body_extrinsic_factor(i, i + 1u, iRb_index, itb, new_pwm);
            gtsam::NoiseModelFactor::shared_ptr factor;
            factor.reset(static_cast<gtsam::NoiseModelFactor*>(imu_body_extrinsic_factor.GetFactor()));
            graph.add(factor);
        }
    }

    // add prior factor for first pose and between factor for two consecutive pose
    for (uint16_t i = 0u; i < num_poses; i++)
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
                                                         gtsam::noiseModel::Isotropic::Sigma(6, 1e-6)));
        }
    }

    // add iRb value
    Scalar const delta_roll  = 0.0;
    Scalar const delta_pitch = 0.2;
    Scalar const delta_yaw   = 0.2;
    values.insert(E(iRb_index),
                  gtsam::Rot3::RzRyRx(rpy.At(0) + delta_roll, rpy.At(1) + delta_pitch, rpy.At(2) + delta_yaw));

    /// @brief optimize
    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, values, parameters);
    gtsam::Values                      results = optimizer.optimize();

    gtsam::Rot3 const est_iRb = results.at<gtsam::Rot3>(E(iRb_index));

    // check results
    ASSERT_NEAR(rpy_gtsam(0u), est_iRb.rpy()(0u), 1);  // roll has no constraints
    ASSERT_NEAR(rpy_gtsam(1u), est_iRb.rpy()(1u), 1e-3);
    ASSERT_NEAR(rpy_gtsam(2u), est_iRb.rpy()(2u), 1e-3);

    for (uint16_t i = 0u; i < num_poses; i++)
    {
        gtsam::Pose3 const gt_pose        = gt_poses.at<gtsam::Pose3>(X(i));
        gtsam::Pose3 const optimized_pose = results.at<gtsam::Pose3>(X(i));
        ASSERT_TRUE(gt_pose.rotation().equals(optimized_pose.rotation(), 1e-5));
        ASSERT_TRUE(gt_pose.translation().equals(optimized_pose.translation(), 1e-5));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImuBodyFixture, Jacobian)
{
    // get ground truth iTb
    Pose3Type const   iTb = GetGroundTruthiTb();
    Vector3Type const rpy = iTb.GetRotation().RPY();
    Point3Type const  itb = iTb.GetTranslation();

    gtsam::Rot3 const iRb_gt = gtsam::Rot3::RzRyRx(rpy.At(0u), rpy.At(1u), rpy.At(2u));

    // start timestamp and end timestamp
    Timestamp const start_t(0, 0);
    Timestamp const end_t = start_t + GetPoseDuration();

    Pose3Type                      imu_pose;
    WheelPreintegrationMeasurement new_pwm;
    std::tie(imu_pose, new_pwm) = GetImuPoseAndPwm(start_t, end_t);

    // imu pose1
    gtsam::Pose3 const wTi1 = ConvertHoloPoseToGtsamType(imu_pose);

    // imu pose2
    Navstate const     end_nav   = GenerateNavstate(end_t);
    Pose3Type const    imu_pose2 = end_nav.GetPose() * iTb.Inverse();
    gtsam::Pose3 const wTi2      = ConvertHoloPoseToGtsamType(imu_pose2);

    /// @brief pose and iRb index
    uint64_t const pose1_index = 1u;
    uint64_t const pose2_index = 2u;
    uint64_t const iRb_index   = 1u;

    /// @brief create factor graph and symbols
    gtsam::NonlinearFactorGraph graph;
    gtsam::Key const            x1 = X(pose1_index);
    gtsam::Key const            x2 = X(pose2_index);
    gtsam::Key const            e1 = E(iRb_index);

    /// @brief create imu body extrinsic factor
    ImuBodyExtrinsicFactor              imu_body_extrinsic_factor(pose1_index, pose2_index, iRb_index, itb, new_pwm);
    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(imu_body_extrinsic_factor.GetFactor()));
    graph.add(factor);

    /// @brief initial values
    gtsam::Values values;
    values.insert(x1, wTi1);
    values.insert(x2, wTi2);
    values.insert(e1, iRb_gt);

    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("ImuBodyExtrinsicFactorJacobian", *factor, values, 1e-5, 1e-6));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ImuBodyExtrinsicFactor, InternalDefaultConstructor)
{
    holo::localization::ImuBodyExtrinsicFactor::TestDefaultConstructorOfInternalFactor();
}

///////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
