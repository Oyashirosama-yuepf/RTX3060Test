/*!
 * @file test_imu_preintegration.cpp
 * @brief the unit test for imu preintegration
 * @author lichao@holomatic.com
 * @date Oct 13, 2019
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <gtsam/base/numericalDerivative.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/navigation/ImuFactor.h>
#include <holo/common/imu.h>
#include <holo/geometry/angle.h>
#include <holo/localization/common/imu_preintegration.h>
#include <holo/log/hololog.h>
#include <boost/function.hpp>

using namespace holo;
using namespace holo::localization;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PreintFixture : public ::testing::Test
{
public:
    using Timestamp = holo::common::Timestamp;
    using Duration  = holo::common::Duration;
    using Pose3 = holo::geometry::Pose3;
    using Rot3   = holo::geometry::Rot3;
    using Point3 = holo::geometry::Point3;
    using Point2    = holo::geometry::Point2;
    template <typename Scalar, int32_t Row>
    using VectorT = holo::numerics::VectorT<Scalar, Row>;
    template <typename Scalar, int32_t Row, int32_t Col>
    using MatrixT = numerics::MatrixT<Scalar, Row, Col>;

    PreintFixture()
      : origin_(), omega_(holo::geometry::Radian(5.0)), radius_(10.0), init_navs(), imu_bias(), imu_queue(2000u)
    {
    }

    virtual ~PreintFixture()
    {
    }

    virtual void SetUp()
    {
        float64_t init_theta = 90.0;
        /* x = 10, y = 0, z = 0 */
        Point3                init_position(10.0, 0.0, 0.0);
        Pose3                 init_p(Rot3::Rz(holo::geometry::Radian(init_theta)), init_position);
        VectorT<float64_t, 3> init_vel = VectorT<float64_t, 3>(0.0, omega_ * radius_, 0.0);
        Navstate              fns(init_p, init_vel);
        Timestamp             stamp(0, 0);
        init_navs.SetTimestamp(stamp);
        init_navs.SetData(fns);
        Duration imu_dur(0.01);
        Duration seg(3.0);
        size_t   i = 1;

        for (Timestamp t = stamp; t <= stamp + seg; t += imu_dur)
        {
            ImuType imu;
            imu.SetTimestamp(t);
            imu.SetAngularVelocity(Point3Type(0.0, 0.0, omega_));
            imu.SetLinearAcceleration(Point3Type(0.0, std::pow(omega_, 2) * radius_, 9.81));
            imu_queue.push_back(imu);
            // DLOG(INFO) << "counter: " << i;
            i++;
        }
    }

    void GenerateImuQueue(const Timestamp& start, const Duration& range, std::vector<ImuType>& imu_queue) const
    {
        Scalar       imu_dur(0.01);
        Scalar       t;
        const Scalar end = (start + range).ToSec();
        for (t = start.ToSec(); t < end; t += imu_dur)
        {
            ImuType imu;
            imu.SetTimestamp(Timestamp(t));
            imu.SetAngularVelocity(Point3Type(0.0, 0.0, omega_));
            imu.SetLinearAcceleration(Point3Type(0.0, std::pow(omega_, 2) * radius_, 9.81));
            imu_queue.push_back(imu);

            /* synchronize imu */
            const float64_t msec = t * 1000;
            const int8_t    res  = (int64_t)msec % 10;
            if (res != 0)
            {
                t = (msec - res) / 1000;
            }
        }

        ImuType imu;
        imu.SetTimestamp(Timestamp(end));
        imu.SetAngularVelocity(Point3Type(0.0, 0.0, omega_));
        imu.SetLinearAcceleration(Point3Type(0.0, std::pow(omega_, 2) * radius_, 9.81));
        imu_queue.push_back(imu);
    }

    void GenerateNavstate(const Timestamp& stamp, Navstate& navs)
    {
        float64_t t = stamp.ToSec();
        Pose3                 p = Pose3(Rot3::Rz(holo::geometry::Radian(90.0) + omega_ * t),
                        Point3(origin_.GetX() + radius_ * std::cos(omega_ * t),
                               origin_.GetY() + radius_ * std::sin(omega_ * t), 0.0));
        VectorT<float64_t, 3> v = VectorT<float64_t, 3>(-omega_ * radius_ * std::sin(omega_ * t),  // -wrsin(wt)
                                                        omega_ * radius_ * std::cos(omega_ * t),   //  wrcos(wt)
                                                        0.0);
        navs                    = Navstate(p, v);
    }

    virtual void TearDown()
    {
    }

    Point2    origin_;
    float64_t omega_;
    float64_t radius_;

    StampedNavstate      init_navs;
    ImuBiasType          imu_bias;
    std::vector<ImuType> imu_queue;

};  // class PreintFixture

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ImuPreintegrationParameters, ConstructorForReferenceOfRightValue)
{
    const Vector3Type           acc_noise_sigmas   = Vector3Type::Constant(1e5);
    const Vector3Type           gyro_noise_sigmas  = Vector3Type::Constant(1e5);
    const Pose3Type             extrinsic_body_imu = Pose3Type();
    ImuPreintegrationParameters temp(acc_noise_sigmas, gyro_noise_sigmas, extrinsic_body_imu);
    ImuPreintegrationParameters params(std::move(temp));

    ASSERT_EQ(params.GetAccNoiseSigmas(), acc_noise_sigmas);
    ASSERT_EQ(params.GetGyroNoiseSigmas(), gyro_noise_sigmas);
    ASSERT_TRUE(params.GetExtrinsicBodyImu().IsEqual(extrinsic_body_imu));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ImuPreintegrationParameters, AssignmentForReferenceOfRightValue)
{
    const Vector3Type           acc_noise_sigmas   = Vector3Type::Constant(1e5);
    const Vector3Type           gyro_noise_sigmas  = Vector3Type::Constant(1e5);
    const Pose3Type             extrinsic_body_imu = Pose3Type();
    ImuPreintegrationParameters temp(acc_noise_sigmas, gyro_noise_sigmas, extrinsic_body_imu);
    ImuPreintegrationParameters params;
    params = std::move(temp);

    ASSERT_EQ(params.GetAccNoiseSigmas(), acc_noise_sigmas);
    ASSERT_EQ(params.GetGyroNoiseSigmas(), gyro_noise_sigmas);
    ASSERT_TRUE(params.GetExtrinsicBodyImu().IsEqual(extrinsic_body_imu));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ImuPreintegrationMeasurement, ConstructorForReferenceOfRightValue)
{
    ImuPreintegrationParameters params(1e-5, 1e-5, Pose3Type());

    /// prepare imu measurements from a motion which accelerate along x axis with a constant angular velocity in roll
    const Scalar a          = 0.1;
    const Scalar w          = M_PI / 100.0;
    const Scalar delta_time = 0.5;

    std::vector<ImuType> imus;
    const uint32_t       imu_num = (uint32_t)(3.0 / delta_time + 1);
    imus.reserve(imu_num);
    for (uint32_t i = 0u; i < imu_num; i++)
    {
        ImuType imu;
        imu.SetTimestamp(Timestamp(i * delta_time));
        imu.SetAngularVelocity(Point3Type(w, 0.0, 0.0));
        imu.SetLinearAcceleration(Point3Type(a, 0.0, 0.0));
        imus.push_back(imu);
    }

    ImuBiasType                  imu_bias;
    ImuPreintegrationMeasurement temp(params, imus, imu_bias);
    ImuPreintegrationMeasurement pim(std::move(temp));

    /// check actual pim with expected pim
    const Scalar time_length = (imu_num - 1u) * delta_time;
    EXPECT_EQ(pim.GetEndTime().ToSec() - time_length, Scalar(0.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ImuPreintegrationMeasurement, AssignmentForReferenceOfRightValue)
{
    ImuPreintegrationParameters params(1e-5, 1e-5, Pose3Type());

    /// prepare imu measurements from a motion which accelerate along x axis with a constant angular velocity in roll
    const Scalar a          = 0.1;
    const Scalar w          = M_PI / 100.0;
    const Scalar delta_time = 0.5;

    std::vector<ImuType> imus;
    const uint32_t       imu_num = (uint32_t)(3.0 / delta_time + 1);
    imus.reserve(imu_num);
    for (uint32_t i = 0u; i < imu_num; i++)
    {
        ImuType imu;
        imu.SetTimestamp(Timestamp(i * delta_time));
        imu.SetAngularVelocity(Point3Type(w, 0.0, 0.0));
        imu.SetLinearAcceleration(Point3Type(a, 0.0, 0.0));
        imus.push_back(imu);
    }

    ImuBiasType                  imu_bias;
    ImuPreintegrationMeasurement temp(params, imus, imu_bias);
    ImuPreintegrationMeasurement pim(params);
    pim = std::move(temp);

    /// check actual pim with expected pim
    const Scalar time_length = (imu_num - 1u) * delta_time;
    EXPECT_EQ(pim.GetEndTime().ToSec() - time_length, Scalar(0.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ImuPreintegrationMeasurement, Gravity)
{
    ImuPreintegrationParameters params(1e-5, 1e-5, Pose3Type());

    ASSERT_EQ(9.81, params.GetGravity());
    params.SetGravity(10.0);
    ASSERT_EQ(10.0, params.GetGravity());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ImuPreintegrationMeasurement, IntegrateMeasurement)
{
    Vector3Type       acc(0.1, 0.0, 0.0);
    Vector3Type       gyro(0.1, 0.0, 0.0);
    const Scalar      delta_time  = 0.5;
    const Vector3Type gt_rotation = delta_time * gyro;
    const Vector3Type gt_position = Scalar(0.5) * delta_time * delta_time * acc;
    const Vector3Type gt_velocity = delta_time * acc;
    // preintergrated
    ImuPreintegrationParameters  params(1e-5, 1e-5, Pose3Type());
    ImuBiasType                  imu_bias;
    ImuPreintegrationMeasurement pim(params, imu_bias);
    pim.IntegrateMeasurement(acc, gyro, delta_time);
    const Vector3Type integrated_rotation = pim.GetPreintegratedNavstate().GetHead(3u);
    const Vector3Type integrated_position = pim.GetPreintegratedNavstate().GetSegment(3u, 3u);
    const Vector3Type integrated_velocity = pim.GetPreintegratedNavstate().GetTail(3u);

    /// check results
    ASSERT_EQ(pim.GetDeltaTime(), delta_time);
    ASSERT_EQ(integrated_rotation, gt_rotation);
    ASSERT_EQ(integrated_position, gt_position);
    ASSERT_EQ(integrated_velocity, integrated_velocity);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ImuPreintegration, preintegrated)
{
    ImuPreintegration::Parameters params(1e-5, 1e-5, Pose3Type());
    ImuPreintegration*            preintegration = new ImuPreintegration(params);

    /// prepare imu measurements
    /// simulate a motion which accelerate along x axis with a constant angular
    /// velocity in roll.
    const Scalar a = 0.1, w = M_PI / 100.0;
    const Scalar delta_time  = 0.5;
    const Scalar time_length = 3.0;

    std::vector<ImuType> imus;
    imus.reserve((uint32_t)(time_length / delta_time + 1));
    for (Scalar t = 0; t <= time_length; t += delta_time)
    {
        ImuType imu;
        imu.SetTimestamp(Timestamp(t));
        imu.SetAngularVelocity(Point3Type(w, 0.0, 0.0));
        imu.SetLinearAcceleration(Point3Type(a, 0.0, 0.0));
        imus.push_back(imu);
    }

    ImuBiasType imu_bias;

    // Expected pre-integrated values
    Vector9Type expected_preintegrated = Vector9Type::Zero();
    expected_preintegrated(0)          = w * time_length;
    expected_preintegrated(3)          = 0.5 * a * time_length * time_length;
    expected_preintegrated(6)          = a * time_length;

    /// preintegrated imus then get a pim
    const ImuPreintegration::MeasurementPtr actual_pim = preintegration->Preintegrate(imus, imu_bias);
    delete preintegration;

    /// check actual pim with expected pim
    EXPECT_EQ(actual_pim->GetStartTime().ToSec() - Scalar(0.0), Scalar(0.0));
    EXPECT_EQ(actual_pim->GetEndTime().ToSec() - time_length, Scalar(0.0));
    ASSERT_EQ(actual_pim->GetDeltaTime(), time_length);
    ASSERT_TRUE(actual_pim->GetPreintegratedNavstate().IsApprox(expected_preintegrated, 1e-9));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename InScalar, uint8_t RowValue, uint8_t ColValue>
Eigen::Matrix<float64_t, RowValue, ColValue> ConvertMatrix(holo::numerics::MatrixT<InScalar, RowValue, ColValue> mat)
{
    const uint32_t array_size = mat.GetCols() * mat.GetRows();

    Eigen::Matrix<float64_t, RowValue, ColValue> result;
    memcpy(result.data(), mat.GetData(), sizeof(float64_t) * array_size);
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename OutScalar, uint8_t RowValue, uint8_t ColValue>
holo::numerics::MatrixT<OutScalar, RowValue, ColValue>
ConvertToHoloMatrix(Eigen::Matrix<float64_t, RowValue, ColValue> mat)
{
    uint32_t array_size = mat.cols() * mat.rows();

    Eigen::Matrix<OutScalar, RowValue, ColValue> tmp = mat.template cast<OutScalar>();
    holo::numerics::MatrixT<OutScalar, RowValue, ColValue> result;
    memcpy(result.GetData(), tmp.data(), sizeof(OutScalar) * array_size);
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(PreintFixture, ComputeErrorAndJacobians)
{
    ImuPreintegration::Parameters params(1e-5, 1e-5, Pose3Type());
    ImuPreintegration             preintegration(params);
    Navstate                      result;
    Navstate                      start;
    Timestamp                     st(0, 0);
    Timestamp                     et = Timestamp(3.0);
    GenerateNavstate(st, start);
    Navstate truth;
    GenerateNavstate(et, truth);

    /// create pim pointer
    const auto pim_ptr = preintegration.Preintegrate(imu_queue, imu_bias);

    /// call the function to be tested
    Matrix96Type      actual_jacobian = Matrix96Type::Zero();
    const Vector9Type actual_error    = pim_ptr->ComputeErrorAndJacobians(start, truth, imu_bias, actual_jacobian);

    /// create a function wrapper for numeric derivative calculation
    boost::function<gtsam::Vector9(const gtsam::Pose3&)> ComputeError = [=](const gtsam::Pose3& pose_i) {
        Matrix96Type jacobian = Matrix96Type::Zero();
        return ConvertMatrix<Scalar, 9, 1>(pim_ptr->ComputeErrorAndJacobians(
            NavstateType(Pose3(ConvertToHoloMatrix<float64_t, 4, 4>(pose_i.matrix())), start.GetVelocity()), truth,
            imu_bias, jacobian));
    };

    /// compute expected jacobian wrt pose_i by numeric derivative.
    gtsam::Matrix res = gtsam::numericalDerivative11(
        ComputeError, gtsam::Pose3(ConvertMatrix<float64_t, 4, 4>(start.GetPose().ToMatrix())));
    Matrix96Type expected_jacobian = ConvertToHoloMatrix<Scalar, 9, 6>(res);

    std::cout << "\nactual jacobian wrt pose_i: \n"
              << actual_jacobian(0, 0) << "\nexpected jacobian wrt pose_i: \n"
              << expected_jacobian(0, 0);

    ASSERT_NEAR(actual_error.GetNorm(), 0.0, 1e-3);
    ASSERT_TRUE(actual_jacobian.IsApprox(expected_jacobian, 1e-7));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(PreintFixture, predict_gtsam)
{
    ImuPreintegration::Parameters params(1e-5, 1e-5, Pose3Type());
    ImuPreintegration             preintegration(params);
    Navstate                      result;
    Navstate                      start;
    Timestamp                     st(0, 0);
    Timestamp                     et = Timestamp(3.0);
    GenerateNavstate(st, start);
    preintegration.Predict(start, imu_queue, imu_bias, result);
    // LOG(INFO) << "result position: " << result.pose.Translation()
    //          << "\t result orientation: " << result.pose.Rotation().RPY().transpose()
    //          << "\t result velocity: " << result.velocity.transpose();
    Navstate truth;
    GenerateNavstate(et, truth);
    // LOG(INFO) << "truth position: " << truth.pose.Translation()
    //          << "\t truth orientation: " << truth.pose.Rotation().RPY().transpose()
    //          << "\t truth velocity: " << truth.velocity.transpose();

    // EXPECT_NEAR(truth.GetPose().GetRotation().ComputeAngle(result.GetPose().GetRotation()), 0.0, 1e-9);
    // @todo (lichao@holomatic.com) precision loss in rotation
    EXPECT_NEAR(truth.GetPose().GetRotation().ComputeAngle(result.GetPose().GetRotation()), 0.0, 1e-6);
    EXPECT_NEAR(truth.GetPose().GetTranslation().Dist(result.GetPose().GetTranslation()), 0.0, 1e-3);
    EXPECT_NEAR((truth.GetVelocity() - result.GetVelocity()).GetNorm(), 0.0, 1e-3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(PreintFixture, predict_by_pim_gtsam)
{
    ImuPreintegration::Parameters params(1e-5, 1e-5, Pose3Type());
    ImuPreintegration             preintegration(params);
    Navstate                      result;
    Navstate                      start;
    Timestamp                     st(0, 0);
    Timestamp                     et = Timestamp(3.0);
    GenerateNavstate(st, start);

    /// preintegrated imus then get a pim
    const ImuPreintegration::MeasurementPtr pim = preintegration.Preintegrate(imu_queue, imu_bias);

    preintegration.Predict(start, *pim, imu_bias, result);
    // LOG(INFO) << "result position: " << result.pose.Translation()
    //          << "\t result orientation: " << result.pose.Rotation().RPY().transpose()
    //          << "\t result velocity: " << result.velocity.transpose();
    Navstate truth;
    GenerateNavstate(et, truth);
    // LOG(INFO) << "truth position: " << truth.pose.Translation()
    //          << "\t truth orientation: " << truth.pose.Rotation().RPY().transpose()
    //          << "\t truth velocity: " << truth.velocity.transpose();

    // EXPECT_NEAR(truth.GetPose().GetRotation().ComputeAngle(result.GetPose().GetRotation()), 0.0, 1e-9);
    // @todo (lichao@holomatic.com) precision loss in rotation
    EXPECT_NEAR(truth.GetPose().GetRotation().ComputeAngle(result.GetPose().GetRotation()), 0.0, 1e-6);
    EXPECT_NEAR(truth.GetPose().GetTranslation().Dist(result.GetPose().GetTranslation()), 0.0, 1e-3);
    EXPECT_NEAR((truth.GetVelocity() - result.GetVelocity()).GetNorm(), 0.0, 1e-3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(PreintFixture, predict_gtsam_with_nsync)
{
    ImuPreintegration::Parameters params(1e-5, 1e-5, Pose3Type());
    ImuPreintegration             preintegration(params);
    Navstate                      result_navs;
    StampedNavstate               start;
    start.SetTimestamp(Timestamp(0.013));
    GenerateNavstate(start.GetTimestamp(), start.GetData());
    // DLOG(INFO) << "start position: " << start.data().pose.Translation()
    //           << "\t start orientation: " << start.data().pose.Rotation().RPY().transpose()
    //           << "\t start velocity: " << start.data().velocity.transpose();

    Timestamp            end_time = Timestamp(3.025);
    std::vector<ImuType> imus;
    GenerateImuQueue(start.GetTimestamp(), end_time - start.GetTimestamp(), imus);
    preintegration.Predict(start.GetData(), imus, imu_bias, result_navs);
    // LOG(INFO) << "result position: " << result_navs.pose.Translation()
    //          << "\t result orientation: " << result_navs.pose.Rotation().RPY().transpose()
    //          << "\t result velocity: " << result_navs.velocity.transpose();

    Navstate truth_navs;
    GenerateNavstate(end_time, truth_navs);
    // LOG(INFO) << "truth position: " << truth_navs.pose.Translation()
    //          << "\t truth orientation: " << truth_navs.pose.Rotation().RPY().transpose()
    //          << "\t truth velocity: " << truth_navs.velocity.transpose();

    EXPECT_NEAR(truth_navs.GetPose().GetRotation().ComputeAngle(result_navs.GetPose().GetRotation()), 0.0, 1e-6);
    EXPECT_NEAR(truth_navs.GetPose().GetTranslation().Dist(result_navs.GetPose().GetTranslation()), 0.0, 1e-3);
    EXPECT_NEAR((truth_navs.GetVelocity() - result_navs.GetVelocity()).GetNorm(), 0.0, 1e-3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::PreintegratedImuMeasurements ConvertPimToGtsamType(const ImuPreintegrationMeasurement& pim_holo)
{
    /// 2.1.1 initialize gtsam pim2

    /* Get parameters */
    const ImuPreintegrationParameters params = pim_holo.GetParameters();

    /* Get imu bias */
    const ImuBiasType imu_bias = pim_holo.GetImuBias();

    // PreintegrationBase params
    boost::shared_ptr<gtsam::PreintegratedImuMeasurements::Params> preint_param =
        gtsam::PreintegratedImuMeasurements::Params::MakeSharedU(params.GetGravity());
    preint_param->setBodyPSensor(gtsam::Pose3(ConvertMatrix<Scalar, 4, 4>(params.GetExtrinsicBodyImu().ToMatrix())));
    // ENU navigation frame, gravity vector default is -9.81 m/s^2
    // acc white noise in continuous
    preint_param->accelerometerCovariance =
        ConvertMatrix<Scalar, 3, 3>(params.GetAccNoiseSigmas().CwiseSquare().AsDiagonal());
    // gyro white noise in continuous
    preint_param->gyroscopeCovariance =
        ConvertMatrix<Scalar, 3, 3>(params.GetGyroNoiseSigmas().CwiseSquare().AsDiagonal());
    // integration uncertainty continuous
    // TODO: hard code 1e-8 (@lichao)
    preint_param->integrationCovariance =
        ConvertMatrix<Scalar, 3, 3>((Scalar)params.GetIntegrationUncertainty() * Matrix3Type::Identity());

    /* convert holo::ImuBias to gtsam::ConstantBias */
    gtsam::imuBias::ConstantBias imubias(
        ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetLinearAccelerationBias<ImuBiasType::Vector3Type>()),
        ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetAngularVelocityBias<ImuBiasType::Vector3Type>()));

    gtsam::PreintegratedImuMeasurements pim(
        gtsam::PreintegrationType(preint_param, pim_holo.GetDeltaTime(),
                                  ConvertMatrix<Scalar, 9, 1>(pim_holo.GetPreintegratedNavstate()),
                                  ConvertMatrix<Scalar, 9, 3>(pim_holo.GetPreintegratedJacobianBiasAcc()),
                                  ConvertMatrix<Scalar, 9, 3>(pim_holo.GetPreintegratedJacobianBiasGyro()), imubias),
        ConvertMatrix<Scalar, 9, 9>(pim_holo.GetPreintegratedMeasurementCovariance()));

    return pim;
}

gtsam::PreintegratedImuMeasurements IntegratedImuChain(const ImuPreintegration::Parameters& params,
                                                       const std::vector<ImuType>& imus, const ImuBiasType& imu_bias)
{
    /// 2.1.1 initialize gtsam pim2

    // PreintegrationBase params
    boost::shared_ptr<gtsam::PreintegratedImuMeasurements::Params> preint_param =
        gtsam::PreintegratedImuMeasurements::Params::MakeSharedU(params.GetGravity());
    preint_param->setBodyPSensor(gtsam::Pose3(ConvertMatrix<Scalar, 4, 4>(params.GetExtrinsicBodyImu().ToMatrix())));
    // ENU navigation frame, gravity vector default is -9.81 m/s^2
    // acc white noise in continuous
    preint_param->accelerometerCovariance =
        ConvertMatrix<Scalar, 3, 3>(params.GetAccNoiseSigmas().CwiseSquare().AsDiagonal());
    // gyro white noise in continuous
    preint_param->gyroscopeCovariance =
        ConvertMatrix<Scalar, 3, 3>(params.GetGyroNoiseSigmas().CwiseSquare().AsDiagonal());
    // integration uncertainty continuous
    // TODO: hard code 1e-8 (@lichao)
    preint_param->integrationCovariance =
        ConvertMatrix<Scalar, 3, 3>((Scalar)params.GetIntegrationUncertainty() * Matrix3Type::Identity());

    /* convert holo::ImuBias to gtsam::ConstantBias */
    gtsam::imuBias::ConstantBias imubias(
        ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetLinearAccelerationBias<ImuBiasType::Vector3Type>()),
        ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetAngularVelocityBias<ImuBiasType::Vector3Type>()));
    gtsam::PreintegratedImuMeasurements pim(preint_param, imubias);

    /// 2.1.2 integrate imu frame by frame
    typename std::vector<ImuType>::const_iterator it     = imus.begin();
    typename std::vector<ImuType>::const_iterator itnext = it;
    itnext++;
    for (; itnext != imus.end(); it = itnext, itnext++)
    {
        /* midpoint integration */
        Duration    sample_time = itnext->GetTimestamp() - it->GetTimestamp();
        Vector3Type mid_acc =
            Scalar(0.5) * (it->GetLinearAcceleration<Vector3Type>() + itnext->GetLinearAcceleration<Vector3Type>());
        Vector3Type mid_gyr =
            Scalar(0.5) * (it->GetAngularVelocity<Vector3Type>() + itnext->GetAngularVelocity<Vector3Type>());

        pim.integrateMeasurement(ConvertMatrix<Scalar, 3, 1>(mid_acc), ConvertMatrix<Scalar, 3, 1>(mid_gyr),
                                 (sample_time).ToSec());
    }

    return pim;
}

TEST(ImuPreintegration, preintegrated_equivalent)
{
    /**
     * @brief This test case we want to check the equivalent between holo::PIM and gtsam::PIM
     *        Step1, imu vector -> holo::PIM pim_holo -> gtsam::PIM pim1
     *        Step2, imu vector -> gtsam::PIM pim2
     *        Step3, check if pim1 == pim2
     */
    ImuPreintegration::Parameters params(1e-5, 1e-5, Pose3Type());
    ImuPreintegration             preintegration(params);

    /// prepare imu measurements
    /// simulate a motion which accelerate along x axis with a constant angular
    /// velocity in roll.
    const Scalar a = 0.1, w = M_PI / 100.0;
    const Scalar delta_time  = 0.5;
    const Scalar time_length = 3.0;

    std::vector<ImuType> imus;
    imus.reserve((uint32_t)(time_length / delta_time + 1));
    for (Scalar t = 0; t <= time_length; t += delta_time)
    {
        ImuType imu;
        imu.SetTimestamp(Timestamp(t));
        imu.SetAngularVelocity(Point3Type(w, 0.0, 0.0));
        imu.SetLinearAcceleration(Point3Type(a, 0.0, 0.0));
        imus.push_back(imu);
    }

    ImuBiasType imu_bias;

    // Expected pre-integrated values
    Vector9Type expected_preintegrated = Vector9Type::Zero();
    expected_preintegrated(0)          = w * time_length;
    expected_preintegrated(3)          = 0.5 * a * time_length * time_length;
    expected_preintegrated(6)          = a * time_length;

    /// Step1,
    /// 1.1 preintegrated imus then get a holo pim
    const ImuPreintegration::MeasurementPtr pim_holo = preintegration.Preintegrate(imus, imu_bias);

    /// 1.2 convert holo pim to gtsam pim1
    gtsam::PreintegratedImuMeasurements pim1 = ConvertPimToGtsamType(*pim_holo);

    /// Step2,
    /// 2.1 preintegrated imus then get a gtsam pim2
    gtsam::PreintegratedImuMeasurements pim2 = IntegratedImuChain(params, imus, imu_bias);

    /// Step3, check if pim1 == pim2
    pim1.print();
    LOG(INFO) << "front one is generate from holo pim, back one is generate from raw imu measurements..";
    pim2.print();
    ASSERT_TRUE(pim1.equals(pim2));
    ASSERT_EQ(pim_holo->GetStartTime().ToSec() - Scalar(0.0), Scalar(0.0));
    ASSERT_EQ(pim_holo->GetEndTime().ToSec() - Scalar(time_length), Scalar(0.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
