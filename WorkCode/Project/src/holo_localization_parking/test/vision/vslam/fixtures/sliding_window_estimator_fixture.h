/*!
 * \brief generate sliding window estimator data for unit test in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/sliding_window_estimator.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief test fixture class to generate test data
 */
class TestFixture : public ::testing::Test
{
public:
    /**
     * @brief Construct a new Test Fixture object
     *
     */
    TestFixture()
      : camera_index_(0)
      , camera_parameters_(CameraParameters::Example())
      , estimator_(GenerateParameters(), camera_parameters_)
    {
    }

    /**
     * @brief Destroy the Test Fixture object
     *
     */
    virtual ~TestFixture()
    {
    }

    virtual void SetUp() override
    {
        raw_measurements_      = GenerateRawMeasurements();
        factor_measurements_   = GenerateFactorMeasurements();
        initial_vehicle_state_ = GenerateInitialVehicleState();
    }

    virtual void TearDown() override
    {
    }

    /**
     * @brief generate tracker parameters
     */
    Tracker::Parameters GenerateTrackerParameters() const
    {
        return Tracker::Parameters();
    }

    /**
     * @brief generate sliding window estimator parameters
     */
    SlidingWindowEstimator::Parameters GenerateParameters() const
    {
        // create imu preintegration parameters
        const auto pim_params = gtsam::PreintegrationParams::MakeSharedU();

        return SlidingWindowEstimator::Parameters(TrackStateTransition::Parameters::Example());
    }

    /**
     * @brief generate image data
     *
     * @param timestamp image timestamp
     * @return Image generated image with four black point on the white background
     */
    Image GenerateImage(const holo::Timestamp& timestamp) const
    {
        // image count
        static uint64_t count = 0;
        // intrinsic
        const Intrinsic intrinsic = camera_parameters_->intrinsics.at(camera_index_);
        // image dimension
        const uint16_t width  = static_cast<uint16_t>(intrinsic.GetWidth());
        const uint16_t height = static_cast<uint16_t>(intrinsic.GetHeight());

        cv::Point2f       xy[4];
        const cv::Point2f delta_point(static_cast<Scalar>(count) * 3.0f, static_cast<Scalar>(count) * 3.0f);
        xy[0] = cv::Point2f(120.0, 160.0) + delta_point;
        xy[1] = cv::Point2f(120.0, 320.0) + delta_point;
        xy[2] = cv::Point2f(300.0, 160.0) + delta_point;
        xy[3] = cv::Point2f(300.0, 320.0) + delta_point;

        cv::Mat img(height, width, CV_8UC1, cv::Scalar(255));
        img.at<uint8_t>(xy[0].y, xy[0].x) = 0;
        img.at<uint8_t>(xy[1].y, xy[1].x) = 0;
        img.at<uint8_t>(xy[2].y, xy[2].x) = 0;
        img.at<uint8_t>(xy[3].y, xy[3].x) = 0;

        Image          image(width, height, Image::Encoding::GRAYSCALE);
        const uint32_t buffer_size = width * height;
        image.SetData(static_cast<uint8_t*>(img.data), buffer_size, width, height, Image::Encoding::GRAYSCALE);
        image.SetTriggerStamp(timestamp);

        count++;

        return image;
    }

    /**
     * @brief generate imu data
     *
     * @param[in] start_time timestamp of the first imu data
     * @param[in] dt delta time between consective imu data (Unit[s])
     * @param[in] num number of dt between the first and last imu data i.e. there are num + 1u imu data
     * @return std::vector<Imu> generated imu data
     */
    std::vector<Imu> GenerateImus(const holo::Timestamp& start_time, const Scalar dt, const uint64_t num) const
    {
        std::vector<Imu> imus;

        for (uint64_t i = 0; i <= num; i++)
        {
            Imu             imu;
            holo::Timestamp timestamp = start_time + holo::Duration(static_cast<Scalar>(i) * dt);
            imu.SetTimestamp(timestamp);
            imu.SetLinearAcceleration(Vector3(0.1, 0.0, 0.0));
            imus.emplace_back(imu);
        }

        return imus;
    }

    /**
     * @brief generate vehicle speed
     */
    ChassisState GenerateChassisState(const holo::Timestamp& stamp) const
    {
        ChassisState chassis_state;
        chassis_state.SetTimestamp(stamp);
        chassis_state.SetVehicleSpeed(10.0);  // m/s
        return chassis_state;
    }

    /**
     * @brief generate raw measurements
     */
    std::vector<RawMeasurement> GenerateRawMeasurements() const
    {
        ///< delta time between consective imu data
        const Scalar imu_dt = 0.01;
        ///< num dt for imu in one raw measurement
        const uint64_t        num_imu  = 10;
        const Scalar          image_dt = 0.1;
        const holo::Timestamp start_time(1, 0);
        const uint64_t        num_raw_measurement = 2;

        std::vector<RawMeasurement> raw_measurements;
        raw_measurements.reserve(num_raw_measurement);

        for (uint64_t i = 0; i < num_raw_measurement; i++)
        {
            const holo::Timestamp image_timestamp = start_time + holo::Duration(static_cast<Scalar>(i) * image_dt);

            const holo::Timestamp imu_start_time =
                image_timestamp - holo::Duration(static_cast<Scalar>(num_imu) * imu_dt);

            std::vector<Image>               images(1, GenerateImage(image_timestamp));
            std::vector<PointFeaturePtrList> point_features(1, PointFeaturePtrList());
            std::vector<ChassisState>        chassis_state{GenerateChassisState(imu_start_time),
                                                    GenerateChassisState(image_timestamp)};
            raw_measurements.emplace_back(image_timestamp, images, point_features,
                                          GenerateImus(imu_start_time, imu_dt, num_imu), chassis_state, boost::none,
                                          std::make_shared<Map>(std::vector<MapPointPtr>{}), boost::none);
        }

        return raw_measurements;
    }

    /**
     * @brief generate factor measurements
     */
    std::vector<FactorMeasurements> GenerateFactorMeasurements() const
    {
        std::vector<FactorMeasurements> factor_measurements;
        factor_measurements.reserve(raw_measurements_.size());

        // create imu preintegration parameters
        const Scalar gravity(9.81);
        auto         pim_params_example = gtsam::PreintegrationParams::MakeSharedU(gravity);
        {
            const gtsam::Matrix3 cov = 1e-8 * gtsam::Matrix3::Identity();
            pim_params_example->setGyroscopeCovariance(cov);
            pim_params_example->setAccelerometerCovariance(cov);
            pim_params_example->setIntegrationCovariance(cov);
        }

        // generate factor measurements
        FactorMeasurements fm;

        for (uint64_t i = 0; i < raw_measurements_.size(); i++)
        {
            // generate new frame index
            const uint64_t new_frame_index = i;
            const auto     raw_measurement = raw_measurements_.at(i);
            fm.vm.velocity                 = Vector3(raw_measurement.chassis_states.back().GetVehicleSpeed(), 0.0, 0.0);
            fm.vm.reliability              = VelocityMeasurementReliability::HIGH;

            // generate factor measurement
            if (factor_measurements.empty())
            {
                // initial vehicle state
                const auto           initial_vehicle_state = GenerateInitialVehicleState();
                const gtsam::Pose3   prior_pose = holo::localization::HoloGtsam::Convert(initial_vehicle_state.Pose());
                const gtsam::Vector3 prior_velocity =
                    holo::localization::HoloGtsam::Convert(initial_vehicle_state.Velocity());
                const gtsam::imuBias::ConstantBias prior_bias(
                    holo::localization::HoloGtsam::Convert(initial_vehicle_state.AccBias()),
                    holo::localization::HoloGtsam::Convert(initial_vehicle_state.GyroBias()));
                fm.predicted_values.insert(X(new_frame_index), prior_pose);
                fm.predicted_values.insert(V(new_frame_index), prior_velocity);
                fm.predicted_values.insert(B(new_frame_index), prior_bias);
            }
            else
            {
                // retrieve newest vehicle state from old values
                const auto                         old_values      = factor_measurements.back().predicted_values;
                const uint64_t                     old_frame_index = new_frame_index - 1;
                const gtsam::imuBias::ConstantBias old_bias(
                    old_values.at(B(old_frame_index)).cast<gtsam::imuBias::ConstantBias>());

                // generate imus
                const auto imus = raw_measurement.imus;

                // create new pim by new imus
                PreintegratedImuMeasurements new_pim(pim_params_example, old_bias);

                for (uint16_t i = 0; i < (uint16_t)(imus.size() - 1); i++)
                {
                    const Scalar dt = (imus.at(i + 1).GetTimestamp() - imus.at(i).GetTimestamp()).ToSec();

                    // calculate average linear_acceleration and angular_velocity
                    // @todo(Feng. Li 2020-01-10) should we rotate imus.at(i + 1) with Quatation(angular_velocity * dt)
                    // ?
                    const auto linear_acceleration =
                        0.5 * imus.at(i).GetLinearAcceleration() + 0.5 * imus.at(i + 1).GetLinearAcceleration();

                    const auto angular_velocity =
                        0.5 * imus.at(i).GetAngularVelocity() + 0.5 * imus.at(i + 1).GetAngularVelocity();

                    new_pim.integrateMeasurement(holo::localization::HoloGtsam::Convert(linear_acceleration),
                                                 holo::localization::HoloGtsam::Convert(angular_velocity), dt);
                }

                fm.pim = new_pim;

                // predicte current state by new pim
                const gtsam::NavState old_navstate(old_values.at(X(old_frame_index)).cast<gtsam::Pose3>(),
                                                   old_values.at(V(old_frame_index)).cast<gtsam::Vector3>());

                // predict new vehicle state with pim(IMU)
                const auto new_navstate = new_pim.predict(old_navstate, old_bias);

                // insert to new values
                fm.predicted_values.insert(X(new_frame_index), new_navstate.pose());
                fm.predicted_values.insert(V(new_frame_index), new_navstate.velocity());
                fm.predicted_values.insert(B(new_frame_index), old_bias);
            }

            factor_measurements.emplace_back(fm);
        }

        return factor_measurements;
    }

    /**
     * @brief generate initial vehicle state
     */
    VehicleState GenerateInitialVehicleState() const
    {
        return VehicleState(Pose3::Identity(), Vector3::Zero(), ImuBias());
    }

protected:
    uint16_t                        camera_index_;
    CameraParameters::Ptr           camera_parameters_;
    SlidingWindowEstimator          estimator_;
    std::vector<RawMeasurement>     raw_measurements_;
    std::vector<FactorMeasurements> factor_measurements_;
    VehicleState                    initial_vehicle_state_;
};  // TestFixture
