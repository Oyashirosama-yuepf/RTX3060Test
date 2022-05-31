/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_type_converter.cpp
 * @brief unit test for TypeConverter
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-03-13"
 */

#include <gtest/gtest.h>

#include <holo/localization/sam/type_converter.h>

using namespace holo;
using namespace holo::localization;
using Scalar = holo::float64_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Vector3GtsamToHolo)
{
    // case: gtsam to holo
    GTVector3                        src(1.0, 2.0, 3.0);
    holo::numerics::Vector3T<Scalar> tgt(4.0, 5.0, 6.0);
    TypeConverter::Convert(src, tgt);

    /** check result **/
    for (uint16_t i = 0u; i < 3u; i++)
    {
        ASSERT_EQ(src[i], tgt[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Vector3HoloToGtsam)
{
    // case: holo to gtsam
    holo::numerics::Vector3T<Scalar> src(1.0, 2.0, 3.0);
    GTVector3                        tgt(4.0, 5.0, 6.0);
    TypeConverter::Convert(src, tgt);

    /** check result **/
    for (uint16_t i = 0u; i < 3u; i++)
    {
        ASSERT_EQ(src[i], tgt[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Matrix3GtsamToHolo)
{
    // case: gtsam to holo
    GTMatrix3                        src = GTMatrix3::Identity();
    holo::numerics::Matrix3T<Scalar> tgt = holo::numerics::Matrix3T<Scalar>::Zero();
    TypeConverter::Convert(src, tgt);

    /** check result **/
    for (uint16_t i = 0u; i < 3u; i++)
    {
        for (uint16_t j = 0u; j < 3u; j++)
        {
            ASSERT_EQ(src(i, j), tgt(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Matrix3HoloToGtsam)
{
    // case: holo to gtsam
    holo::numerics::Matrix3T<Scalar> src = holo::numerics::Matrix3T<Scalar>::Zero();
    GTMatrix3                        tgt = GTMatrix3::Identity();
    TypeConverter::Convert(src, tgt);

    /** check result **/
    for (uint16_t i = 0u; i < 3u; i++)
    {
        for (uint16_t j = 0u; j < 3u; j++)
        {
            ASSERT_EQ(src(i, j), tgt(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Matrix6GtsamToHolo)
{
    // case: gtsam to holo
    GTMatrix6                        src = GTMatrix6::Identity();
    holo::numerics::Matrix6T<Scalar> tgt = holo::numerics::Matrix6T<Scalar>::Zero();
    TypeConverter::Convert(src, tgt);

    /** check result **/
    for (uint16_t i = 0u; i < 6u; i++)
    {
        for (uint16_t j = 0u; j < 6u; j++)
        {
            ASSERT_EQ(src(i, j), tgt(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Matrix6HoloToGtsam)
{
    // case: holo to gtsam
    holo::numerics::Matrix6T<Scalar> src = holo::numerics::Matrix6T<Scalar>::Zero();
    GTMatrix6                        tgt = GTMatrix6::Identity();
    TypeConverter::Convert(src, tgt);

    /** check result **/
    for (uint16_t i = 0u; i < 6u; i++)
    {
        for (uint16_t j = 0u; j < 6u; j++)
        {
            ASSERT_EQ(src(i, j), tgt(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Point3GtsamToHolo)
{
    // case: gtsam to holo
    GTPoint3                        src(1.0, 2.0, 3.0);
    holo::geometry::Point3T<Scalar> tgt(0.0, 0.0, 0.0);
    TypeConverter::Convert(src, tgt);

    /** check result **/
    for (uint16_t i = 0u; i < 3u; i++)
    {
        ASSERT_EQ(src[i], tgt[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Point3HoloToGtsam)
{
    // case: holo to gtsam
    holo::geometry::Point3T<Scalar> src(0.0, 0.0, 0.0);
    GTPoint3                        tgt(1.0, 2.0, 3.0);
    TypeConverter::Convert(src, tgt);

    /** check result **/
    for (uint16_t i = 0u; i < 3u; i++)
    {
        ASSERT_EQ(src[i], tgt[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Rot3GtsamToHolo)
{
    // case: gtsam to holo
    GTRot3                        src = GTRot3::identity();
    holo::geometry::Rot3T<Scalar> tgt = holo::geometry::Rot3T<Scalar>::Yaw(0.1);
    TypeConverter::Convert(src, tgt);

    GTMatrix3                        src_matrix = src.matrix();
    holo::numerics::Matrix3T<Scalar> tgt_matrix = tgt.ToMatrix();

    /** check result **/
    for (uint16_t i = 0u; i < 3u; i++)
    {
        for (uint16_t j = 0u; j < 3u; j++)
        {
            ASSERT_EQ(src_matrix(i, j), tgt_matrix(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Rot3HoloToGtsam)
{
    // case: holo to gtsam
    holo::geometry::Rot3T<Scalar> src = holo::geometry::Rot3T<Scalar>::Yaw(0.1);
    GTRot3                        tgt = GTRot3::identity();
    TypeConverter::Convert(src, tgt);

    holo::numerics::Matrix3T<Scalar> src_matrix = src.ToMatrix();
    GTMatrix3                        tgt_matrix = tgt.matrix();

    /** check result **/
    for (uint16_t i = 0u; i < 3u; i++)
    {
        for (uint16_t j = 0u; j < 3u; j++)
        {
            ASSERT_EQ(src_matrix(i, j), tgt_matrix(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Pose3GtsamToHolo)
{
    // case: gtsam to holo
    GTPose3                        src = GTPose3::identity();
    holo::geometry::Pose3T<Scalar> tgt(holo::geometry::Rot3T<Scalar>::Yaw(0.1),
                                       holo::geometry::Point3T<Scalar>(1.0, 2.0, 3.0));
    TypeConverter::Convert(src, tgt);

    GTMatrix4                        src_matrix = src.matrix();
    holo::numerics::Matrix4T<Scalar> tgt_matrix = tgt.ToMatrix();

    /** check result **/
    for (uint16_t i = 0u; i < 4u; i++)
    {
        for (uint16_t j = 0u; j < 4u; j++)
        {
            ASSERT_EQ(src_matrix(i, j), tgt_matrix(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, Pose3HoloToGtsam)
{
    // case: holo to gtsam
    holo::geometry::Pose3T<Scalar> src(holo::geometry::Rot3T<Scalar>::Yaw(0.1),
                                       holo::geometry::Point3T<Scalar>(1.0, 2.0, 3.0));
    GTPose3                        tgt = GTPose3::identity();
    TypeConverter::Convert(src, tgt);

    holo::numerics::Matrix4T<Scalar> src_matrix = src.ToMatrix();
    GTMatrix4                        tgt_matrix = tgt.matrix();

    /** check result **/
    for (uint16_t i = 0u; i < 4u; i++)
    {
        for (uint16_t j = 0u; j < 4u; j++)
        {
            ASSERT_EQ(src_matrix(i, j), tgt_matrix(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, NavStateGtsamToHolo)
{
    // case: gtsam to holo
    GTNavState                            src = GTNavState();
    holo::localization::NavstateT<Scalar> tgt(
        holo::geometry::Pose3T<Scalar>(holo::geometry::Rot3T<Scalar>::Yaw(0.1),
                                       holo::geometry::Point3T<Scalar>(1.0, 2.0, 3.0)),
        holo::numerics::Vector3T<Scalar>(10.0, 20.0, 30.0));
    TypeConverter::Convert(src, tgt);

    GTMatrix4                        src_pose_matrix = src.pose().matrix();
    GTVector3                        src_velocity    = src.v();
    holo::numerics::Matrix4T<Scalar> tgt_pose_matrix = tgt.GetPose().ToMatrix();
    holo::numerics::Vector3T<Scalar> tgt_velocity    = tgt.GetVelocity();

    /** check result **/
    for (uint16_t i = 0u; i < 4u; i++)
    {
        for (uint16_t j = 0u; j < 4u; j++)
        {
            ASSERT_EQ(src_pose_matrix(i, j), tgt_pose_matrix(i, j));
        }
    }

    for (uint16_t j = 0u; j < 3u; j++)
    {
        ASSERT_EQ(src_velocity(j), tgt_velocity(j));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, NavStateHoloToGtsam)
{
    // case: holo to gtsam
    holo::localization::NavstateT<Scalar> src(
        holo::geometry::Pose3T<Scalar>(holo::geometry::Rot3T<Scalar>::Yaw(0.1),
                                       holo::geometry::Point3T<Scalar>(1.0, 2.0, 3.0)),
        holo::numerics::Vector3T<Scalar>(10.0, 20.0, 30.0));
    GTNavState tgt = GTNavState();
    TypeConverter::Convert(src, tgt);

    holo::numerics::Matrix4T<Scalar> src_pose_matrix = src.GetPose().ToMatrix();
    holo::numerics::Vector3T<Scalar> src_velocity    = src.GetVelocity();
    GTMatrix4                        tgt_pose_matrix = tgt.pose().matrix();
    GTVector3                        tgt_velocity    = tgt.v();

    /** check result **/
    for (uint16_t i = 0u; i < 4u; i++)
    {
        for (uint16_t j = 0u; j < 4u; j++)
        {
            ASSERT_EQ(src_pose_matrix(i, j), tgt_pose_matrix(i, j));
        }
    }

    for (uint16_t j = 0u; j < 3u; j++)
    {
        ASSERT_EQ(src_velocity(j), tgt_velocity(j));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, ImuBiasGtsamToHolo)
{
    // case: gtsam to holo
    GTConstantBias                 src(GTVector3(0.1, 0.2, 0.3), GTVector3(0.4, 0.5, 0.6));
    holo::common::ImuBiasT<Scalar> tgt;
    tgt.SetAngularVelocityBias(1.0, 2.0, 3.0);
    tgt.SetLinearAccelerationBias(4.0, 5.0, 6.0);
    TypeConverter::Convert(src, tgt);

    GTVector3                        src_acc  = src.accelerometer();
    GTVector3                        src_gyro = src.gyroscope();
    holo::numerics::Vector3T<Scalar> tgt_acc =
        tgt.template GetLinearAccelerationBias<holo::numerics::Vector3T<Scalar>>();
    holo::numerics::Vector3T<Scalar> tgt_gyro = tgt.template GetAngularVelocityBias<holo::numerics::Vector3T<Scalar>>();

    /** check result **/
    for (uint16_t i = 0; i < 3; i++)
    {
        ASSERT_EQ(src_acc[i], tgt_acc[i]);
        ASSERT_EQ(src_gyro[i], tgt_gyro[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TypeConverter, ImuBiasHoloToGtsam)
{
    // case: holo to gtsam
    holo::common::ImuBiasT<Scalar> src;
    src.SetAngularVelocityBias(1.0, 2.0, 3.0);
    src.SetLinearAccelerationBias(4.0, 5.0, 6.0);
    GTConstantBias tgt(GTVector3(0.1, 0.2, 0.3), GTVector3(0.4, 0.5, 0.6));
    TypeConverter::Convert(src, tgt);

    holo::numerics::Vector3T<Scalar> src_acc =
        src.template GetLinearAccelerationBias<holo::numerics::Vector3T<Scalar>>();
    holo::numerics::Vector3T<Scalar> src_gyro = src.template GetAngularVelocityBias<holo::numerics::Vector3T<Scalar>>();
    GTVector3                        tgt_acc  = tgt.accelerometer();
    GTVector3                        tgt_gyro = tgt.gyroscope();

    /** check result **/
    for (uint16_t i = 0; i < 3; i++)
    {
        ASSERT_EQ(src_acc[i], tgt_acc[i]);
        ASSERT_EQ(src_gyro[i], tgt_gyro[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
