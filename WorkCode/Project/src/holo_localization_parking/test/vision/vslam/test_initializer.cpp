/*!
 * \brief Unit test for initializer in vslam
 * \author Binbin. Wang, wangbinbin@holomatic.com
 * \date Dec-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <vision/vslam/fixtures/initializer_fixture.h>

#include <random>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(InitializerParameters, Constructor)
{
    const std::string source_to_compute_initial_pose           = "stationary";
    bool              checking_solved_pose_by_path_start_point = true;
    Vector3           maximum_acceptable_diff_ypr(15.0, 2.0, 2.0);
    Scalar            maximum_acceptable_diff_z    = 0.5;
    Scalar            maximum_acceptable_diff_dist = 2.0;
    const ImuBias     initial_bias;

    const Initializer::Parameters params(source_to_compute_initial_pose, checking_solved_pose_by_path_start_point,
                                         maximum_acceptable_diff_ypr, maximum_acceptable_diff_z,
                                         maximum_acceptable_diff_dist, initial_bias);

    /// @brief check result
    ASSERT_TRUE(source_to_compute_initial_pose == params.source_to_compute_initial_pose);
    ASSERT_TRUE(checking_solved_pose_by_path_start_point == params.checking_solved_pose_by_path_start_point);
    ASSERT_TRUE(maximum_acceptable_diff_ypr[0] == params.maximum_acceptable_diff_ypr[0]);
    ASSERT_TRUE(maximum_acceptable_diff_ypr[1] == params.maximum_acceptable_diff_ypr[1]);
    ASSERT_TRUE(maximum_acceptable_diff_ypr[2] == params.maximum_acceptable_diff_ypr[2]);
    ASSERT_TRUE(maximum_acceptable_diff_z == params.maximum_acceptable_diff_z);
    ASSERT_TRUE(maximum_acceptable_diff_dist == params.maximum_acceptable_diff_dist);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Initializer, GetInitPriorPoseFromGravityAlignedOdometry)
{
    Initializer initializer(Initializer::Parameters::Example(), CameraParameters::Example());

    Odometry odom;
    odom.SetTimestamp(holo::Timestamp(static_cast<uint64_t>(1)));
    odom.SetPose(Pose3(Rot3::Identity(), Point3(1.0, 1.0, 1.0)));
    Vector6 vel(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    odom.SetVelocity(vel);

    auto pose = initializer.GetInitPriorPoseFromGravityAlignedOdometry(odom);

    /// @brief check result
    ASSERT_TRUE(pose);
    ASSERT_TRUE(odom.GetPose().IsEqual(*pose));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
