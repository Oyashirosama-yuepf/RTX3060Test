/*!
 * \brief vslam test common types.cpp
 * \author Binbin. Wang, wangbinbin@holomatic.com
 * \date Feb-3-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/utils/yaml.h>

using namespace holo::localization::vision::vslam;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEST(RawMeasurement, Constructor)
// {
//     const std::vector<Image> images;
//     const std::vector<Imu>   imus{};
//     VehicleInfoAdapter       via;
//     const Scalar             vehicle_speed = 1.0;
//     via.vehicle_speed(vehicle_speed);
//     const boost::optional<Odometry> optional_odometry = boost::none;
//     const boost::optional<Map>      optional_map      = boost::none;
//     const boost::optional<Position> optional_position = boost::none;

//     const RawMeasurement raw_measurement(images, imus, via, optional_odometry, optional_map, optional_position);

//     /// @brief check result
//     ASSERT_TRUE(raw_measurement.images.empty());
//     ASSERT_EQ(0, raw_measurement.imus.size());
//     ASSERT_EQ(vehicle_speed, raw_measurement.vehicle_info.vehicle_speed());
//     ASSERT_FALSE(raw_measurement.optional_odometry);
//     ASSERT_FALSE(raw_measurement.optional_map);
//     ASSERT_FALSE(raw_measurement.optional_position);
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MapProjectionMeasurement, Constructor)
{
    const uint64_t frame_id     = 1u;
    const uint16_t camera_index = 0u;

    MapPoint mp;
    mp.position          = Point3(1.0, 1.0, 1.0);
    mp.direction         = Vector3(2.0, 2.0, 2.0);
    mp.covariance        = Matrix3::Identity();
    mp.descriptor        = cv::Mat::zeros(1, 2, CV_32FC1);
    mp.descriptor.col(0) = 1;
    mp.reference_pose    = Pose3(Rot3(), Point3(1.0, 2.0, 3.0));

    const Vector3 bearing(1.0, 1.0, 1.0);

    const MapProjectionMeasurement mpm(frame_id, camera_index, std::make_shared<MapPoint>(mp), bearing);

    /// @brief check result
    ASSERT_EQ(frame_id, mpm.frame_id);
    ASSERT_EQ(camera_index, mpm.camera_index);
    ASSERT_EQ(mp.position, mpm.map_point->position);
    ASSERT_EQ(mp.direction, mpm.map_point->direction);
    ASSERT_EQ(mp.covariance, mpm.map_point->covariance);
    ASSERT_FALSE(mpm.map_point->descriptor.empty());
    ASSERT_EQ(mp.reference_pose, mpm.map_point->reference_pose);

    ASSERT_EQ(bearing, mpm.bearing);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Feature, Constructor)
{
    const uint16_t    camera_index = 0u;
    const cv::Point2f image_point(1.0, 1.0);
    cv::Mat           optional_descriptor = cv::Mat::zeros(1, 2, CV_32FC1);
    optional_descriptor.col(0)            = 1;
    const Point3  normalized_point(1.0, 1.0, 1.0);
    const Feature feature(image_point, optional_descriptor, normalized_point, camera_index);

    /// @brief check result
    ASSERT_EQ(image_point, feature.image_point);
    ASSERT_TRUE(feature.optional_descriptor);
    ASSERT_EQ(normalized_point, feature.normalized_point);
    ASSERT_EQ(camera_index, feature.camera_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEST(VehicleState, Constructor1)
// {
//     const Rot3     R = Rot3::RzRyRx(0.1, 0.2, 0.3);
//     const Point3   t = Point3(0.4, 0.5, 0.6);
//     const Pose3    pose(R, t);
//     const Vector3  velocity(1.0, 2.0, 3.0);
//     const NavState navstate(pose, velocity);

//     ImuBias bias;
//     bias.angular_velocity_bias(Vector3(0.1, 0.1, 0.1));
//     bias.linear_acceleration_bias(Vector3(0.2, 0.2, 0.2));

//     const VehicleState vehiclestate(navstate, bias);

//     /// @brief check result
//     ASSERT_EQ(pose, vehiclestate.Pose());
//     ASSERT_EQ(velocity, vehiclestate.Velocity());
//     ASSERT_EQ(R.Transpose() * velocity, vehiclestate.VelocityInBody());
//     ASSERT_EQ(pose.Translation(), vehiclestate.Translation());
//     ASSERT_EQ(pose.Rotation(), vehiclestate.Rotation());
//     ASSERT_EQ(bias.angular_velocity_bias(), vehiclestate.GyroBias());
//     ASSERT_EQ(bias.linear_acceleration_bias(), vehiclestate.AccBias());
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VehicleState, Constructor2)
{
    const Rot3    R = Rot3::RzRyRx(0.1, 0.2, 0.3);
    const Point3  t = Point3(0.4, 0.5, 0.6);
    const Pose3   pose(R, t);
    const Vector3 velocity(1.0, 2.0, 3.0);

    ImuBias bias;
    bias.SetAngularVelocityBias(Vector3(0.1, 0.1, 0.1));
    bias.SetLinearAccelerationBias(Vector3(0.2, 0.2, 0.2));

    const VehicleState vehiclestate(pose, velocity, bias);

    /// @brief check result
    ASSERT_EQ(pose, vehiclestate.Pose());
    ASSERT_EQ(velocity, vehiclestate.Velocity());
    ASSERT_EQ(R.Transpose() * velocity, vehiclestate.VelocityInBody());
    ASSERT_EQ(pose.GetTranslation(), vehiclestate.Translation());
    ASSERT_EQ(pose.GetRotation(), vehiclestate.Rotation());
    ASSERT_EQ(bias.GetAngularVelocityBias(), vehiclestate.GyroBias());
    ASSERT_EQ(bias.GetLinearAccelerationBias(), vehiclestate.AccBias());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VehicleState, Constructor3)
{
    const Point3  t = Point3(0.4, 0.5, 0.6);
    const Rot3    R = Rot3::RzRyRx(0.1, 0.2, 0.3);
    const Pose3   pose(R, t);
    const Vector3 velocity(1.0, 2.0, 3.0);

    const Vector3 acc_bias(0.01, 0.01, 0.01);
    const Vector3 gyro_bias(0.01, 0.01, 0.01);

    const VehicleState vehiclestate(t, R, velocity, acc_bias, gyro_bias);

    /// @brief check result
    ASSERT_EQ(pose, vehiclestate.Pose());
    ASSERT_EQ(velocity, vehiclestate.Velocity());
    ASSERT_EQ(R.Transpose() * velocity, vehiclestate.VelocityInBody());
    ASSERT_EQ(t, vehiclestate.Translation());
    ASSERT_EQ(R, vehiclestate.Rotation());
    ASSERT_EQ(acc_bias, vehiclestate.GyroBias());
    ASSERT_EQ(gyro_bias, vehiclestate.AccBias());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PriorVehicleStateNoise, Constructor)
{
    const Vector6                pose_sigma(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    const Vector3                velocity_sigma(2.0, 2.0, 2.0);
    const Vector6                bias_sigma(3.0, 3.0, 3.0, 3.0, 3.0, 3.0);
    const PriorVehicleStateNoise prior_vehicle_state_noise(pose_sigma, velocity_sigma, bias_sigma);

    /// @brief check result
    ASSERT_EQ(pose_sigma, prior_vehicle_state_noise.pose_sigma);
    ASSERT_EQ(velocity_sigma, prior_vehicle_state_noise.velocity_sigma);
    ASSERT_EQ(bias_sigma, prior_vehicle_state_noise.bias_sigma);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PriorVehicleStateNoise, Example)
{
    /// @brief ground truth
    const Vector6 pose_sigma(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    const Vector3 velocity_sigma(1.0, 1.0, 1.0);
    const Vector6 bias_sigma(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

    /* Example */
    const PriorVehicleStateNoise example = PriorVehicleStateNoise::Example();

    /// @brief check result
    ASSERT_EQ(pose_sigma, example.pose_sigma);
    ASSERT_EQ(velocity_sigma, example.velocity_sigma);
    ASSERT_EQ(bias_sigma, example.bias_sigma);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ResetFlags, basic)
{
    ResetFlags reset_flags;

    /* constructor */
    ASSERT_FALSE(reset_flags);
    ASSERT_FALSE(reset_flags.is_exception);
    ASSERT_FALSE(reset_flags.is_trajectory_jump);

    /* change status */
    reset_flags.is_exception       = true;
    reset_flags.is_trajectory_jump = true;
    ASSERT_TRUE(reset_flags);
    ASSERT_TRUE(reset_flags.is_exception);
    ASSERT_TRUE(reset_flags.is_trajectory_jump);

    /* operator= */
    reset_flags = ResetFlags();
    ASSERT_FALSE(reset_flags);
    ASSERT_FALSE(reset_flags.is_exception);
    ASSERT_FALSE(reset_flags.is_trajectory_jump);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SequenceCounter, Constructor)
{
    const SequenceCounter sequence_counter;

    /// @brief check result
    ASSERT_EQ(0, sequence_counter.vslam_callback_sequence_counter);
    ASSERT_EQ(0, sequence_counter.prediction_callback_sequence_counter);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
