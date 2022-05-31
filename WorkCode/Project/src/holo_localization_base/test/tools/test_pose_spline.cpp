/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_pose_spline.cpp
 * @brief pose spline uint test
 * @author duyanwei@holomatic.com
 * @date April-08-2020
 */

#include <gtest/gtest.h>

#include <holo/localization/tools/pose_spline.h>

namespace holo
{
namespace localization
{
namespace spline_test
{
/**
 * @brief define ground truth data
 *
 */
struct GroundTruthData
{
    using Timestamp = holo::common::Timestamp;
    using Pose3d    = holo::geometry::Pose3d;
    using Vector3d  = holo::numerics::Vector3d;
    Timestamp timestamp;
    Pose3d    pose;
    Vector3d  linear_velocity;
    Vector3d  linear_acceleration;
    Vector3d  angular_velocity_body;

    GroundTruthData(const float64_t t, const float64_t x, const float64_t y, const float64_t z, const float64_t vx,
                    const float64_t vy, const float64_t vz, const float64_t ax, const float64_t ay, const float64_t az,
                    const float64_t angle, const Vector3d& axis, const Vector3d w_body)
      : timestamp(t)
      , pose(Rot3d(AngleAxisd(angle, axis).ToRotationMatrix()), Point3d(x, y, z))
      , linear_velocity(vx, vy, vz)
      , linear_acceleration(ax, ay, az)
      , angular_velocity_body(w_body)
    {
    }
};

/**
 * @brief generate ground truth data
 *
 * @param start
 * @param num
 * @param dt
 * @return std::vector<GroundTruthData>
 */
std::vector<GroundTruthData> GenerateDataset(const float64_t start, const uint32_t num, const float64_t dt,
                                             const float64_t start_angle = 0.0, const float64_t delta_angle = -0.01)
{
    std::vector<GroundTruthData> results;

    /**
     * @brief define a 3d smooth curve
     * x(t) = 2*t^2 + 3;
     * y(t) = 3*t^3 + 1.5*t^2 + 0.1;
     * z(t) = t;
     */

    /**
     * @brief define rotation axis and start angle
     */
    holo::numerics::Vector3d axis(0.1, 0.2, 0.3);
    axis            = axis / axis.GetNorm();
    float64_t angle = start_angle;  // rad

    // create data
    float64_t t = start - dt;
    for (uint32_t i = 0u; i < num; i++)
    {
        t += dt;
        const float64_t t2 = t * t;
        const float64_t t3 = t2 * t;

        // x
        const float64_t x  = 2.0 * t2 + 3.0;
        const float64_t vx = 4.0 * t;
        const float64_t ax = 4.0;

        // y
        const float64_t y  = 3.0 * t3 + 1.5 * t2 + 0.1;
        const float64_t vy = 9.0 * t2 + 3.0 * t;
        const float64_t ay = 18.0 * t + 3.0;

        // z
        const float64_t z  = t;
        const float64_t vz = 1.0;
        const float64_t az = 0.0;

        // theta
        angle += delta_angle;

        // create one piece of data
        results.emplace_back(t, x, y, z, vx, vy, vz, ax, ay, az, angle, axis, delta_angle / dt * axis);
    }

    return results;
}

/**
 * @brief Create a Input From Ground Truth Data object
 *
 * @param data
 * @return std::tuple<std::vector<Timestamp>, std::vector<Pose3d>>
 */
std::tuple<std::vector<holo::common::Timestamp>, std::vector<holo::geometry::Pose3d>>
CreateInputFromGroundTruthData(const std::vector<GroundTruthData>& data)
{
    std::vector<holo::common::Timestamp> timestamps;
    timestamps.reserve(data.size());
    std::vector<holo::geometry::Pose3d> poses;
    poses.reserve(data.size());

    for (const auto val : data)
    {
        timestamps.emplace_back(val.timestamp);
        poses.emplace_back(val.pose);
    }
    return std::make_tuple(timestamps, poses);
}

}  // namespace spline_test
}  // namespace localization
}  // namespace holo

using namespace holo::localization;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PoseSpline, ConstructorAndDestructor)
{
    // s1. create ground truth
    const auto gt = spline_test::GenerateDataset(0.0, 100, 1.0);

    // s2. create input
    std::vector<holo::common::Timestamp> timestamps;
    std::vector<holo::geometry::Pose3d>  poses;
    std::tie(timestamps, poses) = spline_test::CreateInputFromGroundTruthData(gt);

    // s3. create spline
    const PoseSpline* spline = new PoseSpline(timestamps, poses);
    delete spline;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PoseSpline, NormalTest)
{
    // s1. create ground truth
    const auto gt = spline_test::GenerateDataset(0.0, 100, 1.0, 0.5, -0.01);

    // s2. create input
    std::vector<holo::common::Timestamp> timestamps;
    std::vector<holo::geometry::Pose3d>  poses;
    std::tie(timestamps, poses) = spline_test::CreateInputFromGroundTruthData(gt);

    // s3. create spline
    const PoseSpline spline(timestamps, poses);

    // check timestamp
    ASSERT_EQ(holo::common::Timestamp(0.0), spline.GetStartTime());
    ASSERT_EQ(holo::common::Timestamp(99.0), spline.GetEndTime());

    // check results
    for (uint32_t i = 0u; i < gt.size(); i++)
    {
        const auto& m = gt.at(i);

        const holo::geometry::Pose3d p = spline.GetPose(m.timestamp);

        // check position
        ASSERT_TRUE(m.pose.GetTranslation().Dist(p.GetTranslation()) < 1e-5);  // m

        // check rotation
        {
            const auto a1 = holo::geometry::Rot3d::Logmap(m.pose.GetRotation());
            const auto a2 = holo::geometry::Rot3d::Logmap(p.GetRotation());
            ASSERT_TRUE((a1 - a2).GetNorm() < 1e-5);
        }

        // check linear velocity
        const holo::numerics::Vector3d v = spline.GetLinearVelocity(m.timestamp);
        ASSERT_TRUE((m.linear_velocity - v).GetNorm() < 1e-5);

        // check linear acceleration
        const holo::numerics::Vector3d a = spline.GetLinearAcceleration(m.timestamp);
        ASSERT_TRUE((m.linear_acceleration - a).GetNorm() < 1e-5);

        // check linear angular velocity
        const holo::numerics::Vector3d w = spline.GetAngularVelocityBodyFrame(m.timestamp);
        ASSERT_TRUE((m.angular_velocity_body - w).GetNorm() < 1e-5);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PoseSpline, CornerCaseForfindNearestRotation)
{
    // s1. create ground truth
    const auto gt = spline_test::GenerateDataset(0.0, 100, 1.0, 0.0, 1e-9);

    // s2. create input
    std::vector<holo::common::Timestamp> timestamps;
    std::vector<holo::geometry::Pose3d>  poses;
    std::tie(timestamps, poses) = spline_test::CreateInputFromGroundTruthData(gt);

    // s3. create spline
    const PoseSpline spline(timestamps, poses);

    // check timestamp
    ASSERT_EQ(holo::common::Timestamp(0.0), spline.GetStartTime());
    ASSERT_EQ(holo::common::Timestamp(99.0), spline.GetEndTime());

    // check results
    for (uint32_t i = 0u; i < gt.size(); i++)
    {
        const auto& m = gt.at(i);

        const holo::geometry::Pose3d p = spline.GetPose(m.timestamp);

        // check position
        ASSERT_TRUE(m.pose.GetTranslation().Dist(p.GetTranslation()) < 1e-5);  // m

        // check rotation
        {
            const auto a1 = holo::geometry::Rot3d::Logmap(m.pose.GetRotation());
            const auto a2 = holo::geometry::Rot3d::Logmap(p.GetRotation());
            ASSERT_TRUE((a1 - a2).GetNorm() < 1e-5);
        }

        // check linear velocity
        const holo::numerics::Vector3d v = spline.GetLinearVelocity(m.timestamp);
        ASSERT_TRUE((m.linear_velocity - v).GetNorm() < 1e-5);

        // check linear acceleration
        const holo::numerics::Vector3d a = spline.GetLinearAcceleration(m.timestamp);
        ASSERT_TRUE((m.linear_acceleration - a).GetNorm() < 1e-5);

        // check linear angular velocity
        const holo::numerics::Vector3d w = spline.GetAngularVelocityBodyFrame(m.timestamp);
        ASSERT_TRUE((m.angular_velocity_body - w).GetNorm() < 1e-5);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PoseSpline, LocalPoseTest)
{
    // s1. create ground truth
    const auto gt = spline_test::GenerateDataset(10.0, 100, 1.0, 0.5, -0.01);

    // s2. create input
    std::vector<holo::common::Timestamp> timestamps;
    std::vector<holo::geometry::Pose3d>  poses;
    std::tie(timestamps, poses) = spline_test::CreateInputFromGroundTruthData(gt);

    holo::numerics::Vector3d offset(poses[0].GetX(), poses[0].GetY(), poses[0].GetZ());

    // s3. create spline
    const PoseSpline spline(timestamps, poses, offset);

    // check offset
    ASSERT_TRUE((offset - spline.GetOffset()).GetNorm() < 1e-5);

    // check timestamp
    ASSERT_EQ(holo::common::Timestamp(10.0), spline.GetStartTime());
    ASSERT_EQ(holo::common::Timestamp(109.0), spline.GetEndTime());

    // check results
    for (uint32_t i = 0u; i < gt.size(); i++)
    {
        const auto& m = gt.at(i);

        holo::geometry::Pose3d  p = spline.GetPose(m.timestamp, true);
        holo::geometry::Point3d t = p.GetTranslation() + holo::Point3d(offset(0u), offset(1u), offset(2u));
        p.SetTranslation(t);

        // check position
        ASSERT_TRUE(m.pose.GetTranslation().Dist(p.GetTranslation()) < 1e-5);  // m

        // check rotation
        {
            const auto a1 = holo::geometry::Rot3d::Logmap(m.pose.GetRotation());
            const auto a2 = holo::geometry::Rot3d::Logmap(p.GetRotation());
            ASSERT_TRUE((a1 - a2).GetNorm() < 1e-5);
        }

        // check linear velocity
        const holo::numerics::Vector3d v = spline.GetLinearVelocity(m.timestamp);
        ASSERT_TRUE((m.linear_velocity - v).GetNorm() < 1e-5);

        // check linear acceleration
        const holo::numerics::Vector3d a = spline.GetLinearAcceleration(m.timestamp);
        ASSERT_TRUE((m.linear_acceleration - a).GetNorm() < 1e-5);

        // check linear angular velocity
        const holo::numerics::Vector3d w = spline.GetAngularVelocityBodyFrame(m.timestamp);
        ASSERT_TRUE((m.angular_velocity_body - w).GetNorm() < 1e-5);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
