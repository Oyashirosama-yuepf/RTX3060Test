/*!
 * \brief unit test for measurements manager vslam
 * \author luopei@holomatic.com
 * \date Dec-13-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <random>

#include <gtest/gtest.h>

#define protected public
#include <holo/localization/vision/vslam/measurements_manager_vslam.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerVSLAM, BasicTest)
{
    MeasurementsManagerVSLAM mm(MeasurementsManagerVSLAM::Parameters::Example(), CameraParameters::Example());

    holo::Timestamp query_time;
    RawMeasurement  raw_measurement;

    /* check empty measurement manager vslam */
    ASSERT_FALSE(mm.IsRawMeasurementAvailable());
    ASSERT_FALSE(mm.GetOldestAlignedPointFeaturesTimestamp());
    ASSERT_FALSE(mm.GetRawMeasurement(query_time, boost::none, raw_measurement));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerVSLAM, AdvancedTest)
{
    /// two images measurements
    Image gt_image0(640, 480, Image::Encoding::GRAYSCALE);
    Image gt_image1(640, 480, Image::Encoding::GRAYSCALE);

    /// all imu measurements between two images
    std::vector<Imu> gt_imus;

    /// all gravity-aligned odometry between two images
    std::vector<Odometry> gravity_aligned_odoms;

    /// all chassis state between two images
    std::vector<ChassisState> gt_chassis_states;

    /// two ground truth odometry measurements aligned with two images
    Odometry gt_odometry0, gt_odometry1;

    /// create random number generator
    std::default_random_engine             generator(time(0));
    std::uniform_real_distribution<Scalar> distribution(0.0, 100.0);
    auto                                   dice = std::bind(distribution, generator);

    /// generate all higher sampling-rate sensor measurements
    /// (imus, vehicle infos and odoms) between two images
    const size_t num = 50;

    for (uint64_t i = 1; i <= num; i++)
    {
        // timestamp
        holo::Timestamp timestamp(i);

        // imu
        Imu imu;
        imu.SetTimestamp(timestamp);
        imu.SetAngularVelocity(Vector3(dice(), dice(), dice()));
        imu.SetLinearAcceleration(Vector3(dice(), dice(), dice()));
        gt_imus.push_back(imu);

        // gravity-aligned odoms
        Odometry odom;
        odom.SetTimestamp(timestamp);
        odom.SetPose(Pose3(Rot3::YPR(dice(), dice(), dice()), Point3(dice(), dice(), dice())));
        Vector6 vel(dice(), dice(), dice(), dice(), dice(), dice());
        odom.SetVelocity(vel);
        gravity_aligned_odoms.push_back(odom);

        // vehicle infos
        ChassisState chassis_state;
        chassis_state.SetTimestamp(timestamp);
        chassis_state.SetRearLeftWheelSpeed(dice());
        chassis_state.SetRearRightWheelSpeed(dice());
        gt_chassis_states.push_back(chassis_state);
    }

    /// generate two images
    gt_image0.SetTriggerStamp(gt_imus.front().GetTimestamp());
    gt_image1.SetTriggerStamp(gt_imus.back().GetTimestamp());

    /// generate two ground truth odometry measurements aligned with two images
    gt_odometry0 = gravity_aligned_odoms.front();
    gt_odometry1 = gravity_aligned_odoms.back();

    const CameraParameters::Ptr camera_parameters = CameraParameters::Example();
    uint16_t                    camera_index      = 0;
    MeasurementsManagerVSLAM    mmv(MeasurementsManagerVSLAM::Parameters::Example(), camera_parameters);

    /// generate two point feature list
    PointFeaturePtrList gt_point_features0(gt_imus.front().GetTimestamp(),
                                           camera_parameters->intrinsics.at(camera_index).GetSensorId(), {});
    PointFeaturePtrList gt_point_features1(gt_imus.back().GetTimestamp(),
                                           camera_parameters->intrinsics.at(camera_index).GetSensorId(), {});

    /// @brief check AddMeasurement
    ASSERT_TRUE(mmv.AddMeasurement(gt_image1, camera_index));
    ASSERT_TRUE(mmv.AddMeasurement(gt_image0, camera_index));
    ASSERT_TRUE(mmv.AddMeasurement(gt_point_features0));
    ASSERT_TRUE(mmv.AddMeasurement(gt_point_features1));
    ASSERT_TRUE(mmv.AddMeasurement(gt_imus.back()));
    ASSERT_TRUE(mmv.AddMeasurement(gt_imus.front()));
    ASSERT_TRUE(mmv.AddGravityAlignedOdometry(gravity_aligned_odoms.back()));
    ASSERT_TRUE(mmv.AddGravityAlignedOdometry(gravity_aligned_odoms.front()));
    ASSERT_TRUE(mmv.AddMeasurement(gt_chassis_states.back()));
    ASSERT_TRUE(mmv.AddMeasurement(gt_chassis_states.front()));
    ASSERT_TRUE(mmv.AddGroundTruth(gt_odometry1));
    ASSERT_TRUE(mmv.AddGroundTruth(gt_odometry0));

    // test Reset()
    mmv.Reset();

    /* add measurement */
    // image
    ASSERT_TRUE(mmv.AddMeasurement(gt_image0, camera_index));
    ASSERT_TRUE(mmv.AddMeasurement(gt_image1, camera_index));

    // point features
    ASSERT_TRUE(mmv.AddMeasurement(gt_point_features0));
    ASSERT_TRUE(mmv.AddMeasurement(gt_point_features1));

    // imu
    for (size_t i = 0; i < gt_imus.size(); i++)
    {
        ASSERT_TRUE(mmv.AddMeasurement(gt_imus[i]));
    }

    // gravity_aligned odometry
    for (size_t i = 0; i < gravity_aligned_odoms.size(); i++)
    {
        ASSERT_TRUE(mmv.AddGravityAlignedOdometry(gravity_aligned_odoms[i]));
    }

    // vehicle infos
    for (size_t i = 0; i < gt_chassis_states.size(); i++)
    {
        ASSERT_TRUE(mmv.AddMeasurement(gt_chassis_states[i]));
    }

    // ground truth odometry
    ASSERT_TRUE(mmv.AddGroundTruth(gt_odometry0));
    ASSERT_TRUE(mmv.AddGroundTruth(gt_odometry1));

    // get vslam measurements
    RawMeasurement result;
    mmv.GetRawMeasurement(gt_image0.GetTimestamp(), boost::none, result);
    ASSERT_EQ(1u, result.multi_point_feature_list.size());

    // further check vslam measurements
    const auto& point_features = result.multi_point_feature_list.front();
    const auto& imus           = result.imus;

    // check image
    ASSERT_EQ(point_features.GetTimestamp(), gt_point_features1.GetTimestamp());
    ASSERT_EQ(point_features.GetTimestamp(), imus.back().GetTimestamp());

    // check imu
    ASSERT_EQ(imus.size(), gt_imus.size());
    ASSERT_EQ(imus.front().GetTimestamp(), gt_imus.front().GetTimestamp());
    ASSERT_EQ(imus.back().GetTimestamp(), gt_imus.back().GetTimestamp());

    // get vehicle infos before specific timestamp
    std::vector<ChassisState> chassis_states;
    ASSERT_TRUE(
        mmv.GetChassisStatesMeasurements(imus.front().GetTimestamp(), imus.back().GetTimestamp(), chassis_states));

    // check vehicle infos
    ASSERT_EQ(chassis_states.size(), gt_chassis_states.size());
    ASSERT_EQ(chassis_states.front().GetTimestamp(), gt_chassis_states.front().GetTimestamp());
    ASSERT_EQ(chassis_states.back().GetTimestamp(), gt_chassis_states.back().GetTimestamp());
    ASSERT_EQ(chassis_states.back().GetTimestamp(), point_features.GetTimestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerVSLAM, InitializeMap)
{
    MapPtr                        map_;
    MeasurementsManagerVSLAM::Ptr mmr1_;
    MeasurementsManagerVSLAM::Ptr mmr2_;

    size_t num = 100;
    map_       = std::make_shared<Map>();

    for (size_t i = 1; i < num; ++i)
    {
        MapPoint p;
        p.position       = Point3(i * i * i, i * i, i);
        p.reference_pose = Pose3(Rot3(), p.position);
        map_->push_back(std::make_shared<MapPoint>(p));
    }

    mmr1_.reset(new MeasurementsManagerVSLAM(MeasurementsManagerVSLAM::Parameters::Example(),
                                             CameraParameters::Example(), map_));
    mmr2_.reset(
        new MeasurementsManagerVSLAM(MeasurementsManagerVSLAM::Parameters::Example(), CameraParameters::Example()));

    /// @brief check result
    ASSERT_TRUE(mmr1_->kdtree_ != nullptr);
    ASSERT_TRUE(mmr2_->kdtree_ == nullptr);
    int32_t                             k = 2;
    MeasurementsManagerVSLAM::PointType query(1, 1, 1);
    std::vector<size_t>                 indices;
    std::vector<Scalar>                 distances;
    int32_t                             n = mmr1_->kdtree_->KnnSearch(query, k, indices, distances);

    /// @brief check result
    ASSERT_EQ(n, 2);
    ASSERT_EQ(indices[0], 0);
    ASSERT_EQ(indices[1], 1);
    ASSERT_NEAR(distances[0], 0.0f, 1e-6);
    ASSERT_NEAR(distances[1], 59.0f, 1e-6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerVSLAM, GetVisibleMap)
{
    MapPtr                        map_;
    MeasurementsManagerVSLAM::Ptr mmr1_;
    MeasurementsManagerVSLAM::Ptr mmr2_;

    size_t num = 100;
    map_       = std::make_shared<Map>();

    for (size_t i = 1; i < num; ++i)
    {
        MapPoint p;
        p.position       = Point3(i * i * i, i * i, i);
        p.reference_pose = Pose3(Rot3(), p.position);
        map_->push_back(std::make_shared<MapPoint>(p));
    }

    mmr1_.reset(new MeasurementsManagerVSLAM(MeasurementsManagerVSLAM::Parameters::Example(),
                                             CameraParameters::Example(), map_));
    mmr2_.reset(
        new MeasurementsManagerVSLAM(MeasurementsManagerVSLAM::Parameters::Example(), CameraParameters::Example()));

    Pose3 prior_camera_pose = Pose3::Identity();

    holo::float32_t maximum1 = 1000;
    holo::float32_t fov1     = 150.0;

    // (1,1,1),(8,4,2),(27,9,3),(64,16,4)...
    MapPtr r1 = std::make_shared<Map>();
    mmr1_->GetVisibleMap(prior_camera_pose, maximum1, fov1, mmr1_->map_, mmr1_->kdtree_, r1);

    /// @brief check result
    ASSERT_EQ(r1->size(), 3);
    ASSERT_EQ(r1->at(0)->position, Point3(1, 1, 1));
    ASSERT_EQ(r1->at(1)->position, Point3(8, 4, 2));
    ASSERT_EQ(r1->at(2)->position, Point3(27, 9, 3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
