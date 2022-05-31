/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_measurements_manager_base.cpp
 * @brief measurements_manager unit test
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <gtest/gtest.h>
#include <holo/localization/common/measurements_manager_base.h>

using namespace holo::localization;
using holo::bool_t;
using holo::float32_t;
using holo::float64_t;
using ChassisState = holo::common::ChassisState;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, ConstructorAndDestructor)
{
    MeasurementsManagerBase* mm = new MeasurementsManagerBase();

    /* check results */
    ASSERT_EQ(0u, mm->GetGroundTruthNum());
    ASSERT_EQ(0u, mm->GetImuNum());
    ASSERT_EQ(0u, mm->GetOdometryNum());
    ASSERT_EQ(0u, mm->GetPositionNum());
    ASSERT_EQ(0u, mm->GetChassisStateNum());
    ASSERT_EQ(0u, mm->GetImageNum());
    delete mm;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddGroundTruthOdometry)
{
    MeasurementsManagerBase mm;

    /* zero buffer at beginning */
    {
        ASSERT_EQ(0u, mm.GetGroundTruthNum());
        OdometryType odo;
        ASSERT_FALSE(mm.GetLatestGroundTruth(odo));
        ASSERT_FALSE(mm.GetNearestGroundTruth(holo::common::Timestamp(0.0), odo));
        ASSERT_FALSE(mm.GetCurrentGroundTruth(holo::common::Timestamp(0.0), odo));
    }

    /* add measurement */
    const uint64_t  num = 10u;
    const float64_t dt  = 0.01;  // seconds
    for (uint64_t i = 0u; i < num; i++)
    {
        OdometryType odo;

        /* set timestamp */
        odo.SetTimestamp(holo::common::Timestamp(static_cast<float64_t>(i) * dt));

        /* set pose */
        odo.SetPose(Pose3Type(Rot3Type::Identity(), Point3Type(i, i + 1.0, i + 2.0)));

        /* set velocity */
        odo.SetVelocity(Vector6Type(i, i - 1.0, i - 2.0, i - 3.0, i - 4.0, i - 5.0));

        /* insert to buffer */
        mm.AddGroundTruth(odo);
    }

    /* check buffer size after inserting */
    {
        ASSERT_EQ(num, mm.GetGroundTruthNum());
        OdometryType odo;
        ASSERT_TRUE(mm.GetLatestGroundTruth(odo));
        ASSERT_EQ(0.09, odo.GetTimestamp().ToSec());
        ASSERT_EQ(Point3Type(9.0, 10.0, 11.0), odo.GetPose().GetTranslation());
        ASSERT_EQ(Vector6Type(9.0, 8.0, 7.0, 6.0, 5.0, 4.0), odo.GetVelocity());
    }

    /* get nearest measurement */
    for (uint64_t i = 0u; i < num; i++)
    {
        const holo::common::Timestamp timestamp(static_cast<float64_t>(i) * dt);

        /* call method and check results */
        OdometryType odo;
        ASSERT_TRUE(mm.GetNearestGroundTruth(timestamp, odo));
        ASSERT_EQ(timestamp, odo.GetTimestamp());
        ASSERT_EQ(Point3Type(i, i + 1.0, i + 2.0), odo.GetPose().GetTranslation());
        ASSERT_EQ(Vector6Type(i, i - 1.0, i - 2.0, i - 3.0, i - 4.0, i - 5.0), odo.GetVelocity());
    }

    /* get current measurement */
    for (uint64_t i = 0u; i < num - 1u; i++)
    {
        const holo::common::Timestamp left_t(static_cast<float64_t>(i) * dt);
        const holo::common::Timestamp right_t(static_cast<float64_t>(i + 1u) * dt);

        /* call method and check results */
        OdometryType left_odo, right_odo;
        ASSERT_TRUE(mm.GetNearestGroundTruth(left_t, left_odo));
        ASSERT_TRUE(mm.GetNearestGroundTruth(right_t, right_odo));

        /* create ground truth value of interpolated odo */
        const holo::common::Timestamp current_t((i + i + 1u) / 2.0 * dt);
        const Point3Type      current_translation =
            (left_odo.GetPose().GetTranslation() + right_odo.GetPose().GetTranslation()) / 2.0;
        const Vector6Type current_velocity = (left_odo.GetVelocity() + right_odo.GetVelocity()) / 2.0;

        /* call method and check results */
        OdometryType odo;
        ASSERT_TRUE(mm.GetCurrentGroundTruth(current_t, odo));
        ASSERT_EQ(current_t, odo.GetTimestamp());
        ASSERT_EQ(current_translation, odo.GetPose().GetTranslation());
        ASSERT_EQ(current_velocity, odo.GetVelocity());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddImu)
{
    MeasurementsManagerBase mm;

    /* zero buffer at beginning */
    {
        ASSERT_EQ(0u, mm.GetImuNum());
        ImuType imu;
        ASSERT_FALSE(mm.GetLatestMeasurement(imu));
    }

    /* add measurement */
    const uint64_t  imu_num = 10u;
    const float64_t dt      = 0.001;  // seconds
    for (uint64_t i = 0u; i < imu_num; i++)
    {
        ImuType imu;

        /* set timestamp */
        imu.SetTimestamp(holo::common::Timestamp(static_cast<float64_t>(i) * dt));

        /* set acc */
        imu.SetLinearAcceleration(Point3Type(i, i + 1.0, i + 2.0));

        /* set omega */
        imu.SetAngularVelocity(Point3Type(i, i - 1.0, i - 2.0));

        /* insert to buffer */
        mm.AddMeasurement(imu);
    }

    /* check buffer size after inserting */
    {
        ASSERT_EQ(imu_num, mm.GetImuNum());
        ImuType imu;
        ASSERT_TRUE(mm.GetLatestMeasurement(imu));
        ASSERT_EQ(0.009, imu.GetTimestamp().ToSec());
        ASSERT_EQ(Vector3Type(9.0, 10.0, 11.0), imu.GetLinearAcceleration<Vector3Type>());
        ASSERT_EQ(Vector3Type(9.0, 8.0, 7.0), imu.GetAngularVelocity<Vector3Type>());
    }

    /* get nearest measurement */
    for (uint64_t i = 0u; i < imu_num; i++)
    {
        const holo::common::Timestamp timestamp(static_cast<float64_t>(i) * dt);

        /* call method and check results */
        ImuType imu;
        ASSERT_TRUE(mm.GetNearestMeasurement(timestamp, imu));
        ASSERT_EQ(timestamp, imu.GetTimestamp());
        ASSERT_EQ(Vector3Type(i, i + 1.0, i + 2.0), imu.GetLinearAcceleration<Vector3Type>());
        ASSERT_EQ(Vector3Type(i, i - 1.0, i - 2.0), imu.GetAngularVelocity<Vector3Type>());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddPosition)
{
    MeasurementsManagerBase mm;

    /* zero buffer at beginning */
    {
        ASSERT_EQ(0u, mm.GetPositionNum());
        GnssPositionType position;
        ASSERT_FALSE(mm.GetLatestMeasurement(position));
    }

    /* add measurement */
    const uint64_t  position_num = 10u;
    const float64_t dt           = 1.0;  // seconds
    for (uint64_t i = 0u; i < position_num; i++)
    {
        GnssPositionType position;

        /* set timestamp */
        position.SetTimestamp(holo::common::Timestamp(static_cast<float64_t>(i) * dt));

        /* set values */
        position.SetLongitude(i);
        position.SetLatitude(i + 1.0);
        position.SetAltitude(i + 2.0);

        /* insert to buffer */
        mm.AddMeasurement(position);
    }

    /* check buffer size after inserting */
    {
        ASSERT_EQ(position_num, mm.GetPositionNum());
        GnssPositionType position;
        ASSERT_TRUE(mm.GetLatestMeasurement(position));
        ASSERT_EQ(9.0, position.GetTimestamp().ToSec());
        ASSERT_EQ(9.0, position.GetLongitude());
        ASSERT_EQ(10.0, position.GetLatitude());
        ASSERT_EQ(11.0, position.GetAltitude());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddGnssPvtAndGetMeasurement)
{
    MeasurementsManagerBase mm;

    /* zero buffer at beginning */
    {
        ASSERT_EQ(0u, mm.GetGnssPvtNum());
        GnssPvtType gnss_pvt;
        ASSERT_FALSE(mm.GetLatestMeasurement(gnss_pvt));
        ASSERT_FALSE(mm.GetNearestMeasurement(holo::common::Timestamp(), gnss_pvt));
        ASSERT_FALSE(mm.GetCurrentMeasurement(holo::common::Timestamp(), gnss_pvt));
    }

    /* add measurement */
    const uint64_t  gnss_pvt_num = 10u;
    const float64_t dt           = 1.0;  /// seconds
    for (uint64_t i = 1u; i < gnss_pvt_num; i++)
    {
        GnssPvtType gnss_pvt;

        /* set timestamp */
        gnss_pvt.SetTimestamp(holo::common::Timestamp(static_cast<float64_t>(i) * dt));

        /* set values */
        gnss_pvt.SetCoordinate(holo::common::Coordinate::Wgs84Coordinate());
        gnss_pvt.SetMode(GnssPvtType::Mode::RTK_INT_FIX);
        gnss_pvt.SetVelocity(i, i + 1.0, i + 2.0);
        gnss_pvt.SetPosition(i + 3.0, i + 4.0, i + 5.0);
        gnss_pvt.SetVelocityCov(i + 6.0, i + 7.0, i + 8.0);
        gnss_pvt.SetPositionCov(i + 9.0, i + 10.0, i + 11.0);
        gnss_pvt.SetValidFlags(true, false, true, false);

        /* insert to buffer */
        mm.AddMeasurement(gnss_pvt);
    }

    /* check buffer size after inserting */
    {
        ASSERT_EQ(gnss_pvt_num - 1u, mm.GetGnssPvtNum());
        GnssPvtType gnss_pvt;
        ASSERT_TRUE(mm.GetLatestMeasurement(gnss_pvt));
        ASSERT_EQ(gnss_pvt_num - 1.0, gnss_pvt.GetTimestamp().ToSec());
        ASSERT_EQ(holo::common::Coordinate::Wgs84Coordinate(), gnss_pvt.GetCoordinate());
        ASSERT_EQ(GnssPvtType::Mode::RTK_INT_FIX, gnss_pvt.GetMode());
        ASSERT_EQ(Vector3Type(gnss_pvt_num - 1.0, gnss_pvt_num, gnss_pvt_num + 1.0),
                  gnss_pvt.GetVelocity<Vector3Type>());
        ASSERT_EQ(Vector3Type(gnss_pvt_num + 2.0, gnss_pvt_num + 3.0, gnss_pvt_num + 4.0),
                  gnss_pvt.GetPosition<Vector3Type>());
        ASSERT_EQ(Vector3Type(gnss_pvt_num + 5.0, gnss_pvt_num + 6.0, gnss_pvt_num + 7.0),
                  gnss_pvt.GetVelocityCov<Vector3Type>());
        ASSERT_EQ(Vector3Type(gnss_pvt_num + 8.0, gnss_pvt_num + 9.0, gnss_pvt_num + 10.0),
                  gnss_pvt.GetPositionCov<Vector3Type>());
        ASSERT_TRUE(gnss_pvt.IsPositionValid());
        ASSERT_FALSE(gnss_pvt.IsVelocityValid());
        ASSERT_TRUE(gnss_pvt.IsPositionCovValid());
        ASSERT_FALSE(gnss_pvt.IsVelocityCovValid());
    }
    /* get nearest measurement */
    {
        GnssPvtType gnss_pvt;
        for (uint64_t i = 0u; i < gnss_pvt_num; i++)
        {
            /* case: the target time is earlier than all the measurement*/
            uint64_t j = i;
            if (i == 0u)
            {
                j = 1u;
            }

            /* get the target timestamp */
            holo::common::Timestamp timestamp(static_cast<float64_t>(i) * dt + 1e-1);

            /* call method and check results */
            mm.GetNearestMeasurement(timestamp, gnss_pvt);
            ASSERT_EQ(static_cast<float64_t>(j) * dt, gnss_pvt.GetTimestamp().ToSec());
            ASSERT_EQ(holo::common::Coordinate::Wgs84Coordinate(), gnss_pvt.GetCoordinate());
            ASSERT_EQ(GnssPvtType::Mode::RTK_INT_FIX, gnss_pvt.GetMode());
            ASSERT_EQ(Vector3Type(j, j + 1.0, j + 2.0), gnss_pvt.GetVelocity<Vector3Type>());
            ASSERT_EQ(Vector3Type(j + 3.0, j + 4.0, j + 5.0), gnss_pvt.GetPosition<Vector3Type>());
            ASSERT_EQ(Vector3Type(j + 6.0, j + 7.0, j + 8.0), gnss_pvt.GetVelocityCov<Vector3Type>());
            ASSERT_EQ(Vector3Type(j + 9.0, j + 10.0, j + 11.0), gnss_pvt.GetPositionCov<Vector3Type>());
            ASSERT_TRUE(gnss_pvt.IsPositionValid());
            ASSERT_FALSE(gnss_pvt.IsVelocityValid());
            ASSERT_TRUE(gnss_pvt.IsPositionCovValid());
            ASSERT_FALSE(gnss_pvt.IsVelocityCovValid());
        }
    }
    /* get current measurement */
    {
        /* test interpolation case */
        for (uint64_t i = 1u; i < gnss_pvt_num - 1u; i++)
        {
            /* Get the target time and the ground truth */
            const holo::common::Timestamp left_t(static_cast<float64_t>(i) * dt);
            const holo::common::Timestamp right_t(static_cast<float64_t>(i + 1u) * dt);

            GnssPvtType left_gnss, right_gnss;
            ASSERT_TRUE(mm.GetNearestMeasurement(left_t, left_gnss));
            ASSERT_TRUE(mm.GetNearestMeasurement(right_t, right_gnss));

            /* create ground truth value of interpolated odo */
            const holo::common::Timestamp current_time((i + i + 1u) / 2.0 * dt);
            const Vector3Type     current_velocity =
                (left_gnss.GetVelocity<Vector3Type>() + right_gnss.GetVelocity<Vector3Type>()) / 2.0;
            const Vector3Type current_position =
                (left_gnss.GetPosition<Vector3Type>() + right_gnss.GetPosition<Vector3Type>()) / 2.0;
            const Vector3Type current_velocity_cov = left_gnss.GetVelocityCov<Vector3Type>();
            const Vector3Type current_position_cov = left_gnss.GetPositionCov<Vector3Type>();

            /* call method and check results */
            GnssPvtType gnss_pvt;
            mm.GetCurrentMeasurement(current_time, gnss_pvt);
            ASSERT_EQ(current_time.ToSec(), gnss_pvt.GetTimestamp().ToSec());
            ASSERT_EQ(holo::common::Coordinate::Wgs84Coordinate(), gnss_pvt.GetCoordinate());
            ASSERT_EQ(GnssPvtType::Mode::RTK_INT_FIX, gnss_pvt.GetMode());
            ASSERT_EQ(current_velocity, gnss_pvt.GetVelocity<Vector3Type>());
            ASSERT_EQ(current_position, gnss_pvt.GetPosition<Vector3Type>());
            ASSERT_EQ(current_velocity_cov, gnss_pvt.GetVelocityCov<Vector3Type>());
            ASSERT_EQ(current_position_cov, gnss_pvt.GetPositionCov<Vector3Type>());
            ASSERT_TRUE(gnss_pvt.IsPositionValid());
            ASSERT_FALSE(gnss_pvt.IsVelocityValid());
            ASSERT_TRUE(gnss_pvt.IsPositionCovValid());
            ASSERT_FALSE(gnss_pvt.IsVelocityCovValid());
        }

        /* test exterpolation case */
        {
            /* Get the target time */
            const holo::common::Timestamp left_t(static_cast<float64_t>(0.5) * dt);
            const holo::common::Timestamp right_t(static_cast<float64_t>(gnss_pvt_num) * dt);

            /* call method and check results */
            GnssPvtType gnss_pvt;
            mm.GetCurrentMeasurement(left_t, gnss_pvt);
            ASSERT_EQ(0.5 * dt, gnss_pvt.GetTimestamp().ToSec());
            ASSERT_EQ(holo::common::Coordinate::Wgs84Coordinate(), gnss_pvt.GetCoordinate());
            ASSERT_EQ(GnssPvtType::Mode::RTK_INT_FIX, gnss_pvt.GetMode());
            ASSERT_EQ(Vector3Type(0.5, 0.5 + 1.0, 0.5 + 2.0), gnss_pvt.GetVelocity<Vector3Type>());
            ASSERT_EQ(Vector3Type(0.5 + 3.0, 0.5 + 4.0, 0.5 + 5.0), gnss_pvt.GetPosition<Vector3Type>());
            ASSERT_EQ(Vector3Type(7.0, 8.0, 9.0), gnss_pvt.GetVelocityCov<Vector3Type>());
            ASSERT_EQ(Vector3Type(10.0, 11.0, 12.0), gnss_pvt.GetPositionCov<Vector3Type>());
            ASSERT_TRUE(gnss_pvt.IsPositionValid());
            ASSERT_FALSE(gnss_pvt.IsVelocityValid());
            ASSERT_TRUE(gnss_pvt.IsPositionCovValid());
            ASSERT_FALSE(gnss_pvt.IsVelocityCovValid());

            mm.GetCurrentMeasurement(right_t, gnss_pvt);
            ASSERT_EQ(gnss_pvt_num * dt, gnss_pvt.GetTimestamp().ToSec());
            ASSERT_EQ(holo::common::Coordinate::Wgs84Coordinate(), gnss_pvt.GetCoordinate());
            ASSERT_EQ(GnssPvtType::Mode::RTK_INT_FIX, gnss_pvt.GetMode());
            ASSERT_EQ(Vector3Type(gnss_pvt_num, gnss_pvt_num + 1.0, gnss_pvt_num + 2.0),
                      gnss_pvt.GetVelocity<Vector3Type>());
            ASSERT_EQ(Vector3Type(gnss_pvt_num + 3.0, gnss_pvt_num + 4.0, gnss_pvt_num + 5.0),
                      gnss_pvt.GetPosition<Vector3Type>());
            ASSERT_EQ(Vector3Type(gnss_pvt_num - 2.0 + 6.0, gnss_pvt_num - 2.0 + 7.0, gnss_pvt_num - 2.0 + 8.0),
                      gnss_pvt.GetVelocityCov<Vector3Type>());
            ASSERT_EQ(Vector3Type(gnss_pvt_num - 2.0 + 9.0, gnss_pvt_num - 2.0 + 10.0, gnss_pvt_num - 2.0 + 11.0),
                      gnss_pvt.GetPositionCov<Vector3Type>());
            ASSERT_TRUE(gnss_pvt.IsPositionValid());
            ASSERT_FALSE(gnss_pvt.IsVelocityValid());
            ASSERT_TRUE(gnss_pvt.IsPositionCovValid());
            ASSERT_FALSE(gnss_pvt.IsVelocityCovValid());
        }
        /* test the too little measurement case */
        {
            MeasurementsManagerBase mm1;
            GnssPvtType             gnss_pvt;
            ASSERT_FALSE(mm1.GetCurrentMeasurement(holo::common::Timestamp(), gnss_pvt));

            gnss_pvt.SetTimestamp(holo::common::Timestamp(1.0));
            mm1.AddMeasurement(gnss_pvt);

            ASSERT_FALSE(mm1.GetCurrentMeasurement(holo::common::Timestamp(0.5), gnss_pvt));
            ASSERT_FALSE(mm1.GetCurrentMeasurement(holo::common::Timestamp(1.5), gnss_pvt));
        }
        /* test the target time is equal to the timestamp of memeber of buffer */
        {
            for (uint64_t i = 1u; i < gnss_pvt_num; i++)
            {
                const holo::common::Timestamp current_time(static_cast<float64_t>(i) * dt);

                /* call method and check results */
                GnssPvtType gnss_pvt;
                mm.GetCurrentMeasurement(current_time, gnss_pvt);
                ASSERT_EQ(static_cast<float64_t>(i) * dt, gnss_pvt.GetTimestamp().ToSec());
                ASSERT_EQ(holo::common::Coordinate::Wgs84Coordinate(), gnss_pvt.GetCoordinate());
                ASSERT_EQ(GnssPvtType::Mode::RTK_INT_FIX, gnss_pvt.GetMode());
                ASSERT_EQ(Vector3Type(i, i + 1.0, i + 2.0), gnss_pvt.GetVelocity<Vector3Type>());
                ASSERT_EQ(Vector3Type(i + 3.0, i + 4.0, i + 5.0), gnss_pvt.GetPosition<Vector3Type>());
                ASSERT_EQ(Vector3Type(i + 6.0, i + 7.0, i + 8.0), gnss_pvt.GetVelocityCov<Vector3Type>());
                ASSERT_EQ(Vector3Type(i + 9.0, i + 10.0, i + 11.0), gnss_pvt.GetPositionCov<Vector3Type>());
                ASSERT_TRUE(gnss_pvt.IsPositionValid());
                ASSERT_FALSE(gnss_pvt.IsVelocityValid());
                ASSERT_TRUE(gnss_pvt.IsPositionCovValid());
                ASSERT_FALSE(gnss_pvt.IsVelocityCovValid());
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddOdometry)
{
    MeasurementsManagerBase mm;

    /* zero buffer at beginning */
    {
        ASSERT_EQ(0u, mm.GetOdometryNum());
        OdometryType odo;
        ASSERT_FALSE(mm.GetLatestMeasurement(odo));
        ASSERT_FALSE(mm.GetNearestMeasurement(holo::common::Timestamp(0.0), odo));
        ASSERT_FALSE(mm.GetCurrentMeasurement(holo::common::Timestamp(0.0), odo));
    }

    /* add measurement */
    const uint64_t  odo_num = 10u;
    const float64_t dt      = 0.01;  // seconds
    for (uint64_t i = 1u; i < odo_num; i++)
    {
        OdometryType odo;

        /* set timestamp */
        odo.SetTimestamp(holo::common::Timestamp(static_cast<float64_t>(i) * dt));

        /* set pose */
        odo.SetPose(Pose3Type(Rot3Type::Identity(), Point3Type(i, i + 1.0, i + 2.0)));

        /* set velocity */
        odo.SetVelocity(Vector6Type(i, i - 1.0, i - 2.0, i - 3.0, i - 4.0, i - 5.0));

        /* insert to buffer */
        mm.AddMeasurement(odo);
    }

    /* check buffer size after inserting */
    {
        ASSERT_EQ(odo_num - 1, mm.GetOdometryNum());
        OdometryType odo;
        ASSERT_TRUE(mm.GetLatestMeasurement(odo));
        ASSERT_EQ(0.09, odo.GetTimestamp().ToSec());
        ASSERT_EQ(Point3Type(9.0, 10.0, 11.0), odo.GetPose().GetTranslation());
        ASSERT_EQ(Vector6Type(9.0, 8.0, 7.0, 6.0, 5.0, 4.0), odo.GetVelocity());
    }

    /* get nearest measurement */
    for (uint64_t i = 1u; i < odo_num; i++)
    {
        const holo::common::Timestamp timestamp(static_cast<float64_t>(i) * dt);

        /* call method and check results */
        OdometryType odo;
        ASSERT_TRUE(mm.GetNearestMeasurement(timestamp, odo));
        ASSERT_EQ(timestamp, odo.GetTimestamp());
        ASSERT_EQ(Point3Type(i, i + 1.0, i + 2.0), odo.GetPose().GetTranslation());
        ASSERT_EQ(Vector6Type(i, i - 1.0, i - 2.0, i - 3.0, i - 4.0, i - 5.0), odo.GetVelocity());
    }

    /* get current measurement */
    for (uint64_t i = 1u; i < odo_num - 1u; i++)
    {
        const holo::common::Timestamp left_t(static_cast<float64_t>(i) * dt);
        const holo::common::Timestamp right_t(static_cast<float64_t>(i + 1u) * dt);

        /* call method and check results */
        OdometryType left_odo, right_odo;
        ASSERT_TRUE(mm.GetNearestMeasurement(left_t, left_odo));
        ASSERT_TRUE(mm.GetNearestMeasurement(right_t, right_odo));

        /* create ground truth value of interpolated odo */
        const holo::common::Timestamp current_t((i + i + 1u) / 2.0 * dt);
        const Point3Type      current_translation =
            (left_odo.GetPose().GetTranslation() + right_odo.GetPose().GetTranslation()) / 2.0;
        const Vector6Type current_velocity = (left_odo.GetVelocity() + right_odo.GetVelocity()) / 2.0;

        /* call method and check results */
        OdometryType odo;
        ASSERT_TRUE(mm.GetCurrentMeasurement(current_t, odo));
        ASSERT_EQ(current_t, odo.GetTimestamp());
        ASSERT_EQ(current_translation, odo.GetPose().GetTranslation());
        ASSERT_EQ(current_velocity, odo.GetVelocity());
    }

    OdometryType left_odo, right_odo, est_left_odo, est_right_odo;
    Scalar       left  = Scalar(0.5);
    Scalar       right = Scalar(9.5);

    /* set timestamp */
    const holo::common::Timestamp left_t  = holo::common::Timestamp(static_cast<float64_t>(left) * dt);
    const holo::common::Timestamp right_t = holo::common::Timestamp(static_cast<float64_t>(right) * dt);
    left_odo.SetTimestamp(left_t);
    right_odo.SetTimestamp(right_t);

    /* set pose */
    left_odo.SetPose(Pose3Type(Rot3Type::Identity(), Point3Type(left, left + 1.0, left + 2.0)));
    right_odo.SetPose(Pose3Type(Rot3Type::Identity(), Point3Type(right, right + 1.0, right + 2.0)));

    /* set velocity */
    left_odo.SetVelocity(Vector6Type(left, left - 1.0, left - 2.0, left - 3.0, left - 4.0, left - 5.0));
    right_odo.SetVelocity(Vector6Type(right, right - 1.0, right - 2.0, right - 3.0, right - 4.0, right - 5.0));

    /* call method and check results */
    ASSERT_TRUE(mm.GetCurrentMeasurement(left_t, est_left_odo));
    ASSERT_EQ(left_t, est_left_odo.GetTimestamp());
    ASSERT_EQ(left_odo.GetPose().GetTranslation(), est_left_odo.GetPose().GetTranslation());
    ASSERT_EQ(left_odo.GetVelocity(), est_left_odo.GetVelocity());

    ASSERT_TRUE(mm.GetCurrentMeasurement(right_t, est_right_odo));
    ASSERT_EQ(right_t, est_right_odo.GetTimestamp());
    ASSERT_EQ(right_odo.GetPose().GetTranslation(), est_right_odo.GetPose().GetTranslation());
    ASSERT_EQ(right_odo.GetVelocity(), est_right_odo.GetVelocity());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddChassisState)
{
    MeasurementsManagerBase mm;

    /* zero buffer at beginning */
    {
        ASSERT_EQ(0u, mm.GetChassisStateNum());
        holo::common::ChassisState chassis_state;
        ASSERT_FALSE(mm.GetLatestMeasurement(chassis_state));
        ASSERT_FALSE(mm.GetNearestMeasurement(holo::common::Timestamp(0.0), chassis_state));
        ASSERT_FALSE(mm.GetCurrentMeasurement(holo::common::Timestamp(0.0), chassis_state));
    }

    /* add measurement */
    const uint64_t  chassis_state_num = 10u;
    const float64_t dt                = 0.01;  // seconds
    for (uint64_t i = 1u; i < chassis_state_num; i++)
    {
        holo::common::ChassisState chassis_state;

        /* set timestamp */
        chassis_state.SetTimestamp(holo::common::Timestamp(static_cast<float64_t>(i) * dt));

        /* wheel speed */
        chassis_state.SetFrontLeftWheelSpeed(static_cast<float32_t>(i));
        chassis_state.SetFrontRightWheelSpeed(static_cast<float32_t>(i));
        chassis_state.SetRearLeftWheelSpeed(static_cast<float32_t>(i));
        chassis_state.SetRearRightWheelSpeed(static_cast<float32_t>(i));

        /* front wheel angle */
        chassis_state.SetFrontWheelAngle(static_cast<float32_t>(i));

        /* yaw rate */
        chassis_state.SetYawRate(static_cast<float32_t>(i));

        /* vehicle speed */
        chassis_state.SetVehicleSpeed(static_cast<float32_t>(i));

        /* longitudinal acceleration */
        chassis_state.SetLongitudinalAcceleration(static_cast<float32_t>(i));

        /* laternal acceleration */
        chassis_state.SetLateralAcceleration(static_cast<float32_t>(i));

        // add chassis state
        mm.AddMeasurement(chassis_state);
    }

    /* check buffer size after inserting */
    {
        ASSERT_EQ(chassis_state_num - 1u, mm.GetChassisStateNum());
    }

    /* get latest measurement */
    {
        holo::common::ChassisState chassis_state;
        ASSERT_TRUE(mm.GetLatestMeasurement(chassis_state));
        ASSERT_EQ(0.09, chassis_state.GetTimestamp().ToSec());
        ASSERT_EQ(static_cast<float32_t>(9), chassis_state.GetFrontLeftWheelSpeed());
        ASSERT_EQ(static_cast<float32_t>(9), chassis_state.GetFrontRightWheelSpeed());
        ASSERT_EQ(static_cast<float32_t>(9), chassis_state.GetRearLeftWheelSpeed());
        ASSERT_EQ(static_cast<float32_t>(9), chassis_state.GetRearRightWheelSpeed());
        ASSERT_EQ(static_cast<float32_t>(9), chassis_state.GetFrontWheelAngle());
        ASSERT_EQ(static_cast<float32_t>(9), chassis_state.GetYawRate());
        ASSERT_EQ(static_cast<float32_t>(9), chassis_state.GetVehicleSpeed());
        ASSERT_EQ(static_cast<float32_t>(9), chassis_state.GetLongitudinalAcceleration());
        ASSERT_EQ(static_cast<float32_t>(9), chassis_state.GetLateralAcceleration());
    }

    /* get nearest measurement */
    for (uint64_t i = 0u; i <= chassis_state_num; i++)
    {
        const holo::common::Timestamp query_timestamp(static_cast<float64_t>(i) * dt);

        /* call method and check results */
        holo::common::ChassisState chassis_state;
        ASSERT_TRUE(mm.GetNearestMeasurement(query_timestamp, chassis_state));

        /* boundary handling */
        const float32_t value = (i == 0u) ? (i + 1u) : ((i == chassis_state_num) ? (chassis_state_num - 1u) : i);

        ASSERT_EQ(holo::common::Timestamp(static_cast<float64_t>(value * dt)), chassis_state.GetTimestamp());
        ASSERT_EQ(static_cast<float32_t>(value), chassis_state.GetFrontLeftWheelSpeed());
        ASSERT_EQ(static_cast<float32_t>(value), chassis_state.GetFrontRightWheelSpeed());
        ASSERT_EQ(static_cast<float32_t>(value), chassis_state.GetRearLeftWheelSpeed());
        ASSERT_EQ(static_cast<float32_t>(value), chassis_state.GetRearRightWheelSpeed());
        ASSERT_EQ(static_cast<float32_t>(value), chassis_state.GetFrontWheelAngle());
        ASSERT_EQ(static_cast<float32_t>(value), chassis_state.GetYawRate());
        ASSERT_EQ(static_cast<float32_t>(value), chassis_state.GetVehicleSpeed());
        ASSERT_EQ(static_cast<float32_t>(value), chassis_state.GetLongitudinalAcceleration());
        ASSERT_EQ(static_cast<float32_t>(value), chassis_state.GetLateralAcceleration());
    }

    /* get current measurement, extrapolation happens when i == 0u or == chassis_state_num  */
    for (uint64_t i = 0u; i <= chassis_state_num; i++)
    {
        /* create ground truth value of interpolated/extrapolated chassis state */
        const holo::common::Timestamp current_t(static_cast<float64_t>(i + i + 1u) / 2.0 * dt);
        const float32_t       current_value = static_cast<float32_t>(i + i + 1u) / 2.0;

        /* call method and check results */
        holo::common::ChassisState chassis_state;
        ASSERT_TRUE(mm.GetCurrentMeasurement(current_t, chassis_state));
        ASSERT_EQ(current_t, chassis_state.GetTimestamp());
        ASSERT_EQ(current_value, chassis_state.GetFrontLeftWheelSpeed());
        ASSERT_EQ(current_value, chassis_state.GetFrontRightWheelSpeed());
        ASSERT_EQ(current_value, chassis_state.GetRearLeftWheelSpeed());
        ASSERT_EQ(current_value, chassis_state.GetRearRightWheelSpeed());
        ASSERT_EQ(current_value, chassis_state.GetFrontWheelAngle());
        ASSERT_EQ(current_value, chassis_state.GetYawRate());
        ASSERT_EQ(current_value, chassis_state.GetVehicleSpeed());
        ASSERT_EQ(current_value, chassis_state.GetLongitudinalAcceleration());
        ASSERT_EQ(current_value, chassis_state.GetLateralAcceleration());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddImage)
{
    MeasurementsManagerBase mm;

    /* zero buffer at begining */
    {
        ASSERT_EQ(0u, mm.GetImageNum());
        holo::Image image;
        ASSERT_FALSE(mm.GetLatestMeasurement(image));
        ASSERT_FALSE(mm.GetNearestMeasurement(holo::common::Timestamp(0u, 0u), image));
    }

    /* add measurement */
    const uint64_t  image_num = 10u;
    const float64_t dt        = 0.01;  // seconds
    for (uint64_t i = 0u; i < image_num; i++)
    {
        holo::Image image;

        /* set trigger and received timestamp with different order */
        image.SetTriggerStamp(holo::common::Timestamp(static_cast<float64_t>(i) * dt));
        image.SetReceivedStamp(holo::common::Timestamp(static_cast<float64_t>(image_num - i) * dt));

        // add image
        mm.AddMeasurement(image);
    }

    /* check buffer after insert */
    {
        ASSERT_EQ(image_num, mm.GetImageNum());
        holo::Image image;
        ASSERT_TRUE(mm.GetLatestMeasurement(image));
        ASSERT_EQ(0.09, image.GetTimestamp().ToSec());
        ASSERT_EQ(0.01, image.GetReceivedStamp().ToSec());
    }

    /* check nearest image */
    {
        for (uint64_t i = 0u; i < image_num; i++)
        {
            const holo::common::Timestamp timestamp(static_cast<float64_t>(i) * dt);

            holo::Image image;
            ASSERT_TRUE(mm.GetNearestMeasurement(timestamp, image));
            ASSERT_EQ(timestamp, image.GetTimestamp());
            ASSERT_EQ(static_cast<float64_t>(image_num - i) * dt, image.GetReceivedStamp().ToSec());
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddRoadFrame)
{
    MeasurementsManagerBase mm;

    /* zero buffer at beginning */
    {
        ASSERT_EQ(0u, mm.GetRoadFrameNum());
        RoadFrame rf;
        ASSERT_FALSE(mm.GetLatestMeasurement(rf));
        ASSERT_FALSE(mm.GetAndPopOldestMeasurement(rf));
    }

    /* add measurement */
    const uint64_t  num = 10u;
    const float64_t dt  = 0.01;  // seconds
    for (uint64_t i = 0u; i < num; i++)
    {
        RoadFrame rf;

        /* set timestamp */
        rf.SetTimestamp(holo::common::Timestamp(static_cast<float64_t>(i) * dt));

        /* add measurement */
        mm.AddMeasurement(rf);
    }

    /* check buffer size after inserting */
    {
        ASSERT_EQ(num, mm.GetRoadFrameNum());
        RoadFrame rf;
        ASSERT_TRUE(mm.GetLatestMeasurement(rf));
        ASSERT_EQ(0.09, rf.GetTimestamp().ToSec());
    }

    /* get and pop oldest measurements */
    for (uint64_t i = 0u; i < num; i++)
    {
        const holo::float64_t timestamp = static_cast<float64_t>(i) * dt;

        /* call method and check results */
        ASSERT_EQ(num - i, mm.GetRoadFrameNum());
        RoadFrame rf;
        ASSERT_TRUE(mm.GetAndPopOldestMeasurement(rf));
        ASSERT_EQ(timestamp, rf.GetTimestamp().ToSec());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddRouteInfo)
{
    using RouteInfoType = holo::localization::StampedRouteInfoType;
    MeasurementsManagerBase mm;

    /* add measurement */
    const uint64_t  num = 3u;
    const float64_t dt  = 0.01;  // seconds
    for (uint64_t i = 0u; i < num; i++)
    {
        RouteInfoType ri;

        /* set timestamp */
        ri.SetTimestamp(holo::common::Timestamp(static_cast<float64_t>(i) * dt));

        /* add measurement */
        mm.AddMeasurement(ri);
    }

    /* check nearest measurement */
    {
        for (uint64_t i = 0u; i < num; i++)
        {
            const holo::common::Timestamp timestamp(static_cast<float64_t>(i) * dt);

            RouteInfoType ri;
            ASSERT_TRUE(mm.GetNearestMeasurement(timestamp, ri));
            ASSERT_EQ(timestamp, ri.GetTimestamp());
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddMeasurementAndReset)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements */
    const holo::common::Timestamp st(0.0);
    const holo::common::Duration  dt  = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num = 10u;
    const holo::common::Timestamp et  = st + dt * (num - 1u);

    for (holo::common::Timestamp t = st; t <= et; t += dt)
    {
        /* ground truth */
        {
            OdometryType m;
            m.SetTimestamp(t);
            mm.AddGroundTruth(m);
        }

        /* odometry */
        {
            OdometryType m;
            m.SetTimestamp(t + holo::common::Duration(1e-5));
            mm.AddMeasurement(m);
        }

        /* imu */
        {
            ImuType m;
            m.SetTimestamp(t + holo::common::Duration(1e-3));
            mm.AddMeasurement(m);
        }

        /* position type */
        {
            holo::GnssPosition m;
            m.SetTimestamp(t + holo::common::Duration(1e-3));
            mm.AddMeasurement(m);
        }

        /* chassis state */
        {
            holo::common::ChassisState m;
            m.SetTimestamp(t + holo::common::Duration(1e-3));
            mm.AddMeasurement(m);
        }

        /* image type */
        {
            holo::Image m;
            m.SetTriggerStamp(t + holo::common::Duration(1e-3));
            mm.AddMeasurement(m);
        }

        /* gnss pvt type */
        {
            GnssPvtType m;
            m.SetTimestamp(t + holo::common::Duration(1e-3));
            mm.AddMeasurement(m);
        }
    }

    /* check results */
    ASSERT_EQ(num, mm.GetGroundTruthNum());
    ASSERT_EQ(num, mm.GetImuNum());
    ASSERT_EQ(num, mm.GetOdometryNum());
    ASSERT_EQ(num, mm.GetPositionNum());
    ASSERT_EQ(num, mm.GetChassisStateNum());
    ASSERT_EQ(num, mm.GetImageNum());
    ASSERT_EQ(num, mm.GetGnssPvtNum());

    /* reset mm */
    mm.Reset();
    ASSERT_EQ(0u, mm.GetGroundTruthNum());
    ASSERT_EQ(0u, mm.GetImuNum());
    ASSERT_EQ(0u, mm.GetOdometryNum());
    ASSERT_EQ(0u, mm.GetPositionNum());
    ASSERT_EQ(0u, mm.GetChassisStateNum());
    ASSERT_EQ(0u, mm.GetImageNum());
    ASSERT_EQ(0u, mm.GetGnssPvtNum());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, AddTheSameMeasurement)
{
    MeasurementsManagerBase mm;

    mm.AddMeasurement(ImuType());
    mm.AddMeasurement(OdometryType());
    mm.AddMeasurement(OdometryType());
    mm.AddMeasurement(holo::GnssPosition());
    mm.AddMeasurement(holo::GnssPosition());
    mm.AddMeasurement(holo::GnssPosition());
    mm.AddMeasurement(GnssPvtType());
    mm.AddMeasurement(GnssPvtType());

    /* check results */
    ASSERT_EQ(0u, mm.GetGroundTruthNum());
    ASSERT_EQ(1u, mm.GetImuNum());
    ASSERT_EQ(1u, mm.GetOdometryNum());
    ASSERT_EQ(1u, mm.GetPositionNum());
    ASSERT_EQ(1u, mm.GetGnssPvtNum());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetNearestOdometry)
{
    MeasurementsManagerBase mm;

    /* generate a set of odoms */
    const holo::common::Timestamp st(0.0);
    const holo::common::Duration  dt  = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num = 11u;
    const holo::common::Timestamp et  = st + dt * (num - 1u);
    OdometryType          sodo, eodo;

    /* test get from empty queue case */
    ASSERT_FALSE(mm.GetNearestMeasurement(st, sodo));

    for (holo::common::Timestamp t = st; t <= et; t += dt)
    {
        OdometryType odo;
        odo.SetTimestamp(t);
        mm.AddMeasurement(odo);
    }

    /* get the start and end odometries */
    mm.GetNearestMeasurement(st, sodo);
    mm.GetNearestMeasurement(et + dt, eodo);

    /* get a inner odometry */
    const Scalar          ratio = static_cast<Scalar>(0.21);
    const holo::common::Timestamp mt    = st + dt * ratio * (num - 1u);
    OdometryType          modo;
    mm.GetNearestMeasurement(mt, modo);
    const holo::common::Timestamp mt_z =
        st + dt * (std::round(ratio * static_cast<Scalar>(10.0)) / static_cast<Scalar>(10.0)) * (num - 1);

    /// 4. unit tests
    ASSERT_TRUE(mm.GetOdometryNum() == num);
    ASSERT_TRUE(sodo.GetTimestamp() == st);
    ASSERT_TRUE(eodo.GetTimestamp() == et);
    ASSERT_TRUE(modo.GetTimestamp() == mt_z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetImusBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements and ground truth */
    const holo::common::Timestamp begin(0.0);
    const holo::common::Duration  dt      = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num     = 11u;
    const holo::common::Timestamp end     = begin + dt * (num - 1u);
    const holo::common::Timestamp begin_1 = begin + holo::common::Duration(1e-5);
    const holo::common::Timestamp end_1   = end - holo::common::Duration(1e-5);

    std::vector<ImuType>         imus;
    std::vector<holo::common::Timestamp> gt;

    /* test get from empty queue case */
    bool_t ret = mm.GetMeasurementsBetween(begin, end, imus);
    ASSERT_FALSE(ret);

    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        ImuType m;
        m.SetTimestamp(t);
        mm.AddMeasurement(m);
        gt.push_back(t);
    }

    /* get the start and end */
    ret = mm.GetMeasurementsBetween(begin_1, end_1, imus);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num, mm.GetImuNum());
    ASSERT_EQ(num - 2u, imus.size());

    for (uint8_t i = 0u; i < imus.size(); i++)
    {
        ASSERT_EQ(gt.at(i + 1u), imus.at(i).GetTimestamp());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetOdometriesBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements and ground truth */
    const holo::common::Timestamp begin(0.0);
    const holo::common::Duration  dt      = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num     = 11u;
    const holo::common::Timestamp end     = begin + dt * (num - 1u);
    const holo::common::Timestamp begin_1 = begin + holo::common::Duration(1e-5);
    const holo::common::Timestamp end_1   = end - holo::common::Duration(1e-5);

    std::vector<OdometryType>    odometries;
    std::vector<holo::common::Timestamp> gt;

    /* test get from empty queue case */
    bool_t ret = mm.GetMeasurementsBetween(begin, end, odometries);
    ASSERT_FALSE(ret);

    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        OdometryType m;
        m.SetTimestamp(t);
        mm.AddMeasurement(m);
        gt.push_back(t);
    }

    /* get the start and end */
    ret = mm.GetMeasurementsBetween(begin_1, end_1, odometries);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num, mm.GetOdometryNum());
    ASSERT_EQ(num - 2u, odometries.size());

    for (uint8_t i = 0u; i < odometries.size(); i++)
    {
        ASSERT_EQ(gt.at(i + 1u), odometries.at(i).GetTimestamp());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetPositionsBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements and ground truth */
    const holo::common::Timestamp begin(0.0);
    const holo::common::Duration  dt      = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num     = 11u;
    const holo::common::Timestamp end     = begin + dt * (num - 1u);
    const holo::common::Timestamp begin_1 = begin + holo::common::Duration(1e-5);
    const holo::common::Timestamp end_1   = end - holo::common::Duration(1e-5);

    std::vector<holo::GnssPosition> positions;
    std::vector<holo::common::Timestamp> gt;

    /* test get from empty queue case */
    bool_t ret = mm.GetMeasurementsBetween(begin, end, positions);
    ASSERT_FALSE(ret);

    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        holo::GnssPosition m;
        m.SetTimestamp(t);
        mm.AddMeasurement(m);
        gt.push_back(t);
    }

    /* get the start and end */
    ret = mm.GetMeasurementsBetween(begin_1, end_1, positions);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num, mm.GetPositionNum());
    ASSERT_EQ(num - 2u, positions.size());

    for (uint8_t i = 0u; i < positions.size(); i++)
    {
        ASSERT_EQ(gt.at(i + 1u), positions.at(i).GetTimestamp());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetGnssPvtsBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements and ground truth */
    const holo::common::Timestamp begin(1.0);
    const holo::common::Duration  dt      = holo::common::Duration(1.0);  // 1hz
    const uint8_t         num     = 9u;
    const holo::common::Timestamp end     = begin + dt * (num - 1u);
    const holo::common::Timestamp begin_1 = begin + holo::common::Duration(1e-5);
    const holo::common::Timestamp end_1   = end - holo::common::Duration(1e-5);

    std::vector<GnssPvtType>     gnss_pvts;
    std::vector<holo::common::Timestamp> gt_time;
    std::vector<Vector3Type>     gt_velocity;
    std::vector<Vector3Type>     gt_velocity_cov;
    std::vector<Vector3Type>     gt_position;
    std::vector<Vector3Type>     gt_position_cov;

    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        GnssPvtType m;
        m.SetTimestamp(t);
        m.SetVelocity(Vector3Type(t.ToSec(), t.ToSec() + 1.0, t.ToSec() + 2.0));
        m.SetVelocityCov(Vector3Type(t.ToSec() + 3.0, t.ToSec() + 4.0, t.ToSec() + 5.0));
        m.SetPosition(Vector3Type(t.ToSec() + 6.0, t.ToSec() + 7.0, t.ToSec() + 8.0));
        m.SetPositionCov(Vector3Type(t.ToSec() + 9.0, t.ToSec() + 10.0, t.ToSec() + 11.0));

        mm.AddMeasurement(m);
        gt_time.push_back(t);
        gt_velocity.push_back(Vector3Type(t.ToSec(), t.ToSec() + 1.0, t.ToSec() + 2.0));
        gt_velocity_cov.push_back(Vector3Type(t.ToSec() + 3.0, t.ToSec() + 4.0, t.ToSec() + 5.0));
        gt_position.push_back(Vector3Type(t.ToSec() + 6.0, t.ToSec() + 7.0, t.ToSec() + 8.0));
        gt_position_cov.push_back(Vector3Type(t.ToSec() + 9.0, t.ToSec() + 10.0, t.ToSec() + 11.0));
    }

    {
        /* Case 1: the normal case */
        /* get the start and end */
        bool_t ret = mm.GetMeasurementsBetween(begin_1, end_1, gnss_pvts);

        /*  unit tests */
        ASSERT_TRUE(ret);
        ASSERT_EQ(num, mm.GetGnssPvtNum());
        ASSERT_EQ(num - 2u, gnss_pvts.size());

        for (uint8_t i = 0u; i < gnss_pvts.size(); i++)
        {
            ASSERT_EQ(gt_time.at(i + 1u), gnss_pvts.at(i).GetTimestamp());
            ASSERT_EQ(gt_velocity.at(i + 1u), gnss_pvts.at(i).GetVelocity<Vector3Type>());
            ASSERT_EQ(gt_velocity_cov.at(i + 1u), gnss_pvts.at(i).GetVelocityCov<Vector3Type>());
            ASSERT_EQ(gt_position.at(i + 1u), gnss_pvts.at(i).GetPosition<Vector3Type>());
            ASSERT_EQ(gt_position_cov.at(i + 1u), gnss_pvts.at(i).GetPositionCov<Vector3Type>());
        }
    }
    {
        /* Case 2: the empty buffer */
        MeasurementsManagerBase mm1;
        ASSERT_FALSE(mm1.GetMeasurementsBetween(begin_1, end_1, gnss_pvts));
    }
    {
        /* Case 3: the wrong timestamp input */
        ASSERT_FALSE(mm.GetMeasurementsBetween(end_1, begin_1, gnss_pvts));
    }
    {
        /* Case 4: there is no measurements between the start time and end time */
        const holo::common::Timestamp begin_2 = begin - 2u * holo::common::Duration(1e-5);
        const holo::common::Timestamp end_2   = begin - holo::common::Duration(1e-5);
        ASSERT_FALSE(mm.GetMeasurementsBetween(begin_2, end_2, gnss_pvts));

        const holo::common::Timestamp begin_3 = end + holo::common::Duration(1e-5);
        const holo::common::Timestamp end_3   = end + 2u * holo::common::Duration(1e-5);
        ASSERT_FALSE(mm.GetMeasurementsBetween(begin_3, end_3, gnss_pvts));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetRoadFramesBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements and ground truth */
    const holo::common::Timestamp begin(0.0);
    const holo::common::Duration dt      = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num     = 11u;
    const holo::common::Timestamp end     = begin + dt * (num - 1u);
    const holo::common::Timestamp begin_1 = begin + holo::common::Duration(1e-5);
    const holo::common::Timestamp end_1   = end - holo::common::Duration(1e-5);

    std::vector<RoadFrame>       road_frames;
    std::vector<holo::common::Timestamp> gt;

    /* test get from empty queue case */
    bool_t ret = mm.GetMeasurementsBetween(begin, end, road_frames);
    ASSERT_FALSE(ret);

    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        RoadFrame m;
        m.SetTimestamp(t);
        mm.AddMeasurement(m);
        gt.push_back(t);
    }

    /* get the start and end */
    ret = mm.GetMeasurementsBetween(begin_1, end_1, road_frames);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num, mm.GetRoadFrameNum());
    ASSERT_EQ(num - 2u, road_frames.size());

    for (uint8_t i = 0u; i < road_frames.size(); i++)
    {
        ASSERT_EQ(gt.at(i + 1u), road_frames.at(i).GetTimestamp());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetChassisStatesBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements and ground truth */
    const holo::common::Timestamp begin(0.0);
    const holo::common::Duration  dt      = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num     = 11u;
    const holo::common::Timestamp end     = begin + dt * (num - 1u);
    const holo::common::Timestamp begin_1 = begin + holo::common::Duration(1e-5);
    const holo::common::Timestamp end_1   = end - holo::common::Duration(1e-5);

    std::vector<holo::common::ChassisState> chassis_states;
    std::vector<holo::common::Timestamp>    gt;

    /* test get from empty queue case */
    bool_t ret = mm.GetMeasurementsBetween(begin, end, chassis_states);
    ASSERT_FALSE(ret);

    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        holo::common::ChassisState m;
        m.SetTimestamp(t);
        mm.AddMeasurement(m);
        gt.push_back(t);
    }

    /* get the start and end */
    ret = mm.GetMeasurementsBetween(begin_1, end_1, chassis_states);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num, mm.GetChassisStateNum());
    ASSERT_EQ(num - 2u, chassis_states.size());

    for (uint8_t i = 0u; i < chassis_states.size(); i++)
    {
        ASSERT_EQ(gt.at(i + 1u), chassis_states.at(i).GetTimestamp());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetAlignedImusBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of imu and ground truth */
    const holo::common::Timestamp begin(0.1);
    const holo::common::Duration  dt      = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num     = 11u;
    const holo::common::Timestamp end     = begin + dt * (num - 1u);
    const holo::common::Timestamp end_1   = end - holo::common::Duration(5e-3);
    const holo::common::Timestamp end_2   = end + holo::common::Duration(5e-3);
    const holo::common::Timestamp begin_3 = begin - holo::common::Duration(5e-3);

    std::vector<ImuType> imus;
    std::vector<ImuType> gt;

    /* test get from empty queue case */
    bool_t ret = mm.GetAlignedMeasurementsBetween(begin, end, imus);
    ASSERT_FALSE(ret);

    float64_t i = 0.0;
    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        ImuType imu;
        imu.SetTimestamp(t);

        /* set acc */
        imu.SetLinearAcceleration(Point3Type(i, i + 1.0, i + 2.0));

        /* set omega */
        imu.SetAngularVelocity(Point3Type(i, i - 1.0, i - 2.0));

        mm.AddMeasurement(imu);
        gt.push_back(imu);

        i++;
    }

    /* check imu number in buffer */
    ASSERT_EQ(num, mm.GetImuNum());

    /* @brief check interpolated imus */
    /* get the start and end imus */
    ret = mm.GetAlignedMeasurementsBetween(begin, end_1, imus);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num, imus.size());

    for (uint8_t i = 0u; i < num - 1u; i++)
    {
        ASSERT_EQ(gt.at(i).GetTimestamp(), imus.at(i).GetTimestamp());
        ASSERT_EQ(Vector3Type(i, i + 1.0, i + 2.0), imus.at(i).GetLinearAcceleration<Vector3Type>());
        ASSERT_EQ(Vector3Type(i, i - 1.0, i - 2.0), imus.at(i).GetAngularVelocity<Vector3Type>());
    }

    // check last interpolated measurements
    {
        ASSERT_EQ(end_1, imus.back().GetTimestamp());

        const Vector3Type acc = (gt.at(num - 2u).GetLinearAcceleration<Vector3Type>() +
                                 gt.at(num - 1u).GetLinearAcceleration<Vector3Type>()) /
                                2.0;
        const Vector3Type omega =
            (gt.at(num - 2u).GetAngularVelocity<Vector3Type>() + gt.at(num - 1u).GetAngularVelocity<Vector3Type>()) /
            2.0;

        ASSERT_EQ(acc, imus.back().GetLinearAcceleration<Vector3Type>());
        ASSERT_EQ(omega, imus.back().GetAngularVelocity<Vector3Type>());
    }
    /* @brief check interpolated imus ends*/

    /* @brief check extrapolated imus right */
    /* get the start and end imus */
    ret = mm.GetAlignedMeasurementsBetween(begin, end_2, imus);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num + 1u, imus.size());

    for (uint8_t i = 0u; i < num; i++)
    {
        ASSERT_EQ(gt.at(i).GetTimestamp(), imus.at(i).GetTimestamp());
        ASSERT_EQ(Vector3Type(i, i + 1.0, i + 2.0), imus.at(i).GetLinearAcceleration<Vector3Type>());
        ASSERT_EQ(Vector3Type(i, i - 1.0, i - 2.0), imus.at(i).GetAngularVelocity<Vector3Type>());
    }

    // check last extrapolated measurements
    {
        ASSERT_EQ(end_2, imus.back().GetTimestamp());

        const Vector3Type acc = gt.at(num - 1u).GetLinearAcceleration<Vector3Type>() +
                                (gt.at(num - 1u).GetLinearAcceleration<Vector3Type>() -
                                 gt.at(num - 2u).GetLinearAcceleration<Vector3Type>()) /
                                    2.0;
        const Vector3Type omega =
            gt.at(num - 1u).GetAngularVelocity<Vector3Type>() +
            (gt.at(num - 1u).GetAngularVelocity<Vector3Type>() - gt.at(num - 2u).GetAngularVelocity<Vector3Type>()) /
                2.0;

        ASSERT_TRUE(acc.IsApprox(imus.back().GetLinearAcceleration<Vector3Type>(), 1e-10));
        ASSERT_TRUE(omega.IsApprox(imus.back().GetAngularVelocity<Vector3Type>(), 1e-10));
    }
    /* @brief check extrapolated imus right ends */

    /* @brief check extrapolated imus left */
    /* get the start and end imus */
    ret = mm.GetAlignedMeasurementsBetween(begin_3, end, imus);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num + 1u, imus.size());

    for (uint8_t i = 0u; i < num; i++)
    {
        ASSERT_EQ(gt.at(i).GetTimestamp(), imus.at(i + 1u).GetTimestamp());
        ASSERT_EQ(gt.at(i).GetLinearAcceleration<Vector3Type>(), imus.at(i + 1u).GetLinearAcceleration<Vector3Type>());
        ASSERT_EQ(gt.at(i).GetAngularVelocity<Vector3Type>(), imus.at(i + 1u).GetAngularVelocity<Vector3Type>());
    }

    // check first extrapolated measurement
    {
        ASSERT_EQ(begin_3, imus.front().GetTimestamp());

        const Vector3Type acc =
            gt.at(0u).GetLinearAcceleration<Vector3Type>() -
            (gt.at(1u).GetLinearAcceleration<Vector3Type>() - gt.at(0u).GetLinearAcceleration<Vector3Type>()) / 2.0;
        const Vector3Type omega =
            gt.at(0u).GetAngularVelocity<Vector3Type>() -
            (gt.at(1u).GetAngularVelocity<Vector3Type>() - gt.at(0u).GetAngularVelocity<Vector3Type>()) / 2.0;

        ASSERT_TRUE(acc.IsApprox(imus.front().GetLinearAcceleration<Vector3Type>(), 1e-10));
        ASSERT_TRUE(omega.IsApprox(imus.front().GetAngularVelocity<Vector3Type>(), 1e-10));
    }
    /* @brief check extrapolated imus left ends */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetAlignedImusBetween2)
{
    MeasurementsManagerBase mm;

    /* generate only one imu */
    {
        ImuType imu;
        imu.SetTimestamp(holo::common::Timestamp(5.0));
        mm.AddMeasurement(imu);
    }

    /* case 1:  --- start -- end -- measurement ---*/
    /* expected result: get nothing */
    {
        const holo::common::Timestamp start(holo::common::Timestamp(0.0));
        const holo::common::Timestamp end(holo::common::Timestamp(1.0));

        std::vector<ImuType> imus;

        const bool_t ret = mm.GetAlignedMeasurementsBetween(start, end, imus);
        ASSERT_FALSE(ret);
        ASSERT_EQ(0u, imus.size());
    }

    /* case 2:  --- start -- measurement -- end ---*/
    /* expected result: get nothing */
    {
        const holo::common::Timestamp start(holo::common::Timestamp(0.0));
        const holo::common::Timestamp end(holo::common::Timestamp(10.0));

        std::vector<ImuType> imus;

        const bool_t ret = mm.GetAlignedMeasurementsBetween(start, end, imus);
        ASSERT_FALSE(ret);
        ASSERT_EQ(0u, imus.size());
    }

    /* case 3:  --- measurement -- start -- end ---*/
    /* expected result: get nothing */
    {
        const holo::common::Timestamp start(holo::common::Timestamp(10.0));
        const holo::common::Timestamp end(holo::common::Timestamp(15.0));

        std::vector<ImuType> imus;

        const bool_t ret = mm.GetAlignedMeasurementsBetween(start, end, imus);
        ASSERT_FALSE(ret);
        ASSERT_EQ(0u, imus.size());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetAlignedOdometriesBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements and ground truth */
    const holo::common::Timestamp begin(0.1);
    const holo::common::Duration  dt      = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num     = 11u;
    const holo::common::Timestamp end     = begin + dt * (num - 1u);
    const holo::common::Timestamp end_1   = end - holo::common::Duration(5e-3);
    const holo::common::Timestamp end_2   = end + holo::common::Duration(5e-3);
    const holo::common::Timestamp begin_3 = begin - holo::common::Duration(5e-3);

    std::vector<OdometryType> odos;
    std::vector<OdometryType> gt;

    /* test get from empty queue case */
    bool_t ret = mm.GetAlignedMeasurementsBetween(begin, end, odos);
    ASSERT_FALSE(ret);

    float64_t i = 0.0;
    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        OdometryType odo;
        odo.SetTimestamp(t);

        /* set pose */
        {
            Pose3Type pose(Rot3Type::Rz(i * 0.1), Point3Type(i, i + 0.1, i + 0.2));
            odo.SetPose(pose);
        }

        /* set velocity */
        odo.SetVelocity(Vector6Type(i, i + 1.0, i + 2.0, i + 3.0, i + 4.0, i + 5.0));

        mm.AddMeasurement(odo);
        gt.push_back(odo);

        i++;
    }

    /* check odometry number in buffer */
    ASSERT_EQ(num, mm.GetOdometryNum());

    /* @brief check interpolated measurements */
    /* get the start and end measurements */
    ret = mm.GetAlignedMeasurementsBetween(begin, end_1, odos);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num, odos.size());

    for (uint8_t i = 0u; i < num - 1u; i++)
    {
        ASSERT_EQ(gt.at(i).GetTimestamp(), odos.at(i).GetTimestamp());
        ASSERT_EQ(gt.at(i).GetPose(), odos.at(i).GetPose());
        ASSERT_EQ(gt.at(i).GetVelocity(), odos.at(i).GetVelocity());
    }

    // check last interpolated measurements
    {
        /* timestamp */
        ASSERT_EQ(end_1, odos.back().GetTimestamp());

        /* pose */
        {
            const Rot3Type   r = Rot3Type::Rz(0.95);
            const Point3Type t =
                (gt.at(num - 2u).GetPose().GetTranslation() + gt.at(num - 1u).GetPose().GetTranslation()) / 2.0;

            ASSERT_EQ(r, odos.back().GetPose().GetRotation());
            ASSERT_EQ(t, odos.back().GetPose().GetTranslation());
        }

        /* velocity */
        {
            const Vector6Type vel = (gt.at(num - 2u).GetVelocity() + gt.at(num - 1u).GetVelocity()) / 2.0;
            ASSERT_EQ(vel, odos.back().GetVelocity());
        }
    }
    /* @brief check interpolated measurements ends*/

    /* @brief check extrapolated measurements right */
    /* get the start and end measurements */
    ret = mm.GetAlignedMeasurementsBetween(begin, end_2, odos);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num + 1u, odos.size());

    for (uint8_t i = 0u; i < num; i++)
    {
        ASSERT_EQ(gt.at(i).GetTimestamp(), odos.at(i).GetTimestamp());
        ASSERT_EQ(gt.at(i).GetPose(), odos.at(i).GetPose());
        ASSERT_EQ(gt.at(i).GetVelocity(), odos.at(i).GetVelocity());
    }

    // check last extrapolated measurements
    {
        /* timestamp */
        ASSERT_EQ(end_2, odos.back().GetTimestamp());

        /* pose */
        {
            const Rot3Type   r = Rot3Type::Rz(1.05);
            const Point3Type t =
                gt.at(num - 1u).GetPose().GetTranslation() +
                (gt.at(num - 1u).GetPose().GetTranslation() - gt.at(num - 2u).GetPose().GetTranslation()) / 2.0;

            ASSERT_EQ(r, odos.back().GetPose().GetRotation());
            ASSERT_EQ(t, odos.back().GetPose().GetTranslation());
        }

        /* velocity */
        {
            const Vector6Type vel =
                gt.at(num - 1u).GetVelocity() + (gt.at(num - 1u).GetVelocity() - gt.at(num - 2u).GetVelocity()) / 2.0;
            ASSERT_TRUE(vel.IsApprox(odos.back().GetVelocity(), 1e-10));
        }
    }
    /* @brief check extrapolated odometry right ends */

    /* @brief check extrapolated odometry left */
    /* get the start and end odometry */
    ret = mm.GetAlignedMeasurementsBetween(begin_3, end, odos);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(num + 1u, odos.size());

    for (uint8_t i = 0u; i < num; i++)
    {
        ASSERT_EQ(gt.at(i).GetTimestamp(), odos.at(i + 1u).GetTimestamp());
        ASSERT_EQ(gt.at(i).GetPose(), odos.at(i + 1u).GetPose());
        ASSERT_EQ(gt.at(i).GetVelocity(), odos.at(i + 1u).GetVelocity());
    }

    // check first extrapolated measurement
    {
        /* timestamp */
        ASSERT_EQ(begin_3, odos.front().GetTimestamp());

        /* pose */
        {
            const Rot3Type   r = Rot3Type::Rz(-0.05);
            const Point3Type t = gt.at(0u).GetPose().GetTranslation() -
                                 (gt.at(1u).GetPose().GetTranslation() - gt.at(0u).GetPose().GetTranslation()) / 2.0;

            ASSERT_EQ(r, odos.front().GetPose().GetRotation());
            ASSERT_EQ(t, odos.front().GetPose().GetTranslation());
        }

        /* velocity */
        {
            const Vector6Type vel = gt.at(0u).GetVelocity() - (gt.at(1u).GetVelocity() - gt.at(0u).GetVelocity()) / 2.0;
            ASSERT_TRUE(vel.IsApprox(odos.front().GetVelocity(), 1e-10));
        }
    }
    /* @brief check extrapolated odo left ends */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetAlignedGnssPvtsBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements and ground truth */
    const holo::common::Timestamp begin(1.0);
    const holo::common::Duration  dt  = holo::common::Duration(1.0);  // 1hz
    const uint8_t         num = 9u;
    const holo::common::Timestamp end = begin + dt * (num - 1u);

    std::vector<holo::common::Timestamp> gt_time;
    std::vector<Vector3Type>     gt_velocity;
    std::vector<Vector3Type>     gt_velocity_cov;
    std::vector<Vector3Type>     gt_position;
    std::vector<Vector3Type>     gt_position_cov;

    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        GnssPvtType m;
        m.SetTimestamp(t);
        m.SetVelocity(Vector3Type(t.ToSec(), t.ToSec() + 1.0, t.ToSec() + 2.0));
        m.SetVelocityCov(Vector3Type(t.ToSec() + 3.0, t.ToSec() + 4.0, t.ToSec() + 5.0));
        m.SetPosition(Vector3Type(t.ToSec() + 6.0, t.ToSec() + 7.0, t.ToSec() + 8.0));
        m.SetPositionCov(Vector3Type(t.ToSec() + 9.0, t.ToSec() + 10.0, t.ToSec() + 11.0));

        mm.AddMeasurement(m);
        gt_time.push_back(t);
        gt_velocity.push_back(Vector3Type(t.ToSec(), t.ToSec() + 1.0, t.ToSec() + 2.0));
        gt_velocity_cov.push_back(Vector3Type(t.ToSec() + 3.0, t.ToSec() + 4.0, t.ToSec() + 5.0));
        gt_position.push_back(Vector3Type(t.ToSec() + 6.0, t.ToSec() + 7.0, t.ToSec() + 8.0));
        gt_position_cov.push_back(Vector3Type(t.ToSec() + 9.0, t.ToSec() + 10.0, t.ToSec() + 11.0));
    }

    /* test different case */
    std::vector<GnssPvtType> gnss_pvts;
    {
        /* Case 1: the empty buffer */
        MeasurementsManagerBase mm0;
        ASSERT_FALSE(mm0.GetAlignedMeasurementsBetween(begin, end, gnss_pvts));
    }
    {
        /* Case 2: the wrong input timestamp */
        ASSERT_FALSE(mm.GetAlignedMeasurementsBetween(end, begin, gnss_pvts));
    }
    {
        /* Case 3: all of measurements are earlier than start time */
        const holo::common::Timestamp start_time = end + dt;
        const holo::common::Timestamp end_time   = end + 3u * dt;
        ASSERT_FALSE(mm.GetAlignedMeasurementsBetween(start_time, end_time, gnss_pvts));
    }
    {
        /* Case 4: all of measurements are later than end time */
        const holo::common::Timestamp start_time = begin - 0.5 * dt;
        const holo::common::Timestamp end_time   = begin - 0.1 * dt;
        ASSERT_FALSE(mm.GetAlignedMeasurementsBetween(start_time, end_time, gnss_pvts));
    }
    {
        /* Case 5: the start and end measurments are both got by exterpolation */
        const holo::common::Timestamp start_time = begin - 0.5 * dt;
        const holo::common::Timestamp end_time   = end + 0.5 * dt;

        ASSERT_TRUE(mm.GetAlignedMeasurementsBetween(start_time, end_time, gnss_pvts));

        /* Check the first and the last values */
        ASSERT_EQ(start_time.ToSec(), gnss_pvts.front().GetTimestamp().ToSec());
        ASSERT_EQ(Vector3Type(start_time.ToSec(), start_time.ToSec() + 1.0, start_time.ToSec() + 2.0),
                  gnss_pvts.front().GetVelocity<Vector3Type>());
        ASSERT_EQ(Vector3Type(begin.ToSec() + 3.0, begin.ToSec() + 4.0, begin.ToSec() + 5.0),
                  gnss_pvts.front().GetVelocityCov<Vector3Type>());
        ASSERT_EQ(Vector3Type(start_time.ToSec() + 6.0, start_time.ToSec() + 7.0, start_time.ToSec() + 8.0),
                  gnss_pvts.front().GetPosition<Vector3Type>());
        ASSERT_EQ(Vector3Type(begin.ToSec() + 9.0, begin.ToSec() + 10.0, begin.ToSec() + 11.0),
                  gnss_pvts.front().GetPositionCov<Vector3Type>());

        ASSERT_EQ(end_time.ToSec(), gnss_pvts.back().GetTimestamp().ToSec());
        ASSERT_EQ(Vector3Type(end_time.ToSec(), end_time.ToSec() + 1.0, end_time.ToSec() + 2.0),
                  gnss_pvts.back().GetVelocity<Vector3Type>());
        ASSERT_EQ(Vector3Type((end - dt).ToSec() + 3.0, (end - dt).ToSec() + 4.0, (end - dt).ToSec() + 5.0),
                  gnss_pvts.back().GetVelocityCov<Vector3Type>());
        ASSERT_EQ(Vector3Type(end_time.ToSec() + 6.0, end_time.ToSec() + 7.0, end_time.ToSec() + 8.0),
                  gnss_pvts.back().GetPosition<Vector3Type>());
        ASSERT_EQ(Vector3Type((end - dt).ToSec() + 9.0, (end - dt).ToSec() + 10.0, (end - dt).ToSec() + 11.0),
                  gnss_pvts.back().GetPositionCov<Vector3Type>());

        /* Check other measurments */
        for (uint64_t i = 0u; i < num; ++i)
        {
            ASSERT_EQ(gt_time.at(i), gnss_pvts.at(i + 1u).GetTimestamp());
            ASSERT_EQ(gt_velocity.at(i), gnss_pvts.at(i + 1u).GetVelocity<Vector3Type>());
            ASSERT_EQ(gt_velocity_cov.at(i), gnss_pvts.at(i + 1u).GetVelocityCov<Vector3Type>());
            ASSERT_EQ(gt_position.at(i), gnss_pvts.at(i + 1u).GetPosition<Vector3Type>());
            ASSERT_EQ(gt_position_cov.at(i), gnss_pvts.at(i + 1u).GetPositionCov<Vector3Type>());
        }
    }
    {
        /* Case 6: the start and end measurments are both got by interpolation */
        const holo::common::Timestamp start_time = begin + 0.5 * dt;
        const holo::common::Timestamp end_time   = end - 0.5 * dt;

        ASSERT_TRUE(mm.GetAlignedMeasurementsBetween(start_time, end_time, gnss_pvts));

        /* Check the first and the last values */
        ASSERT_EQ(start_time.ToSec(), gnss_pvts.front().GetTimestamp().ToSec());
        ASSERT_EQ(Vector3Type(start_time.ToSec(), start_time.ToSec() + 1.0, start_time.ToSec() + 2.0),
                  gnss_pvts.front().GetVelocity<Vector3Type>());
        ASSERT_EQ(Vector3Type(begin.ToSec() + 3.0, begin.ToSec() + 4.0, begin.ToSec() + 5.0),
                  gnss_pvts.front().GetVelocityCov<Vector3Type>());
        ASSERT_EQ(Vector3Type(start_time.ToSec() + 6.0, start_time.ToSec() + 7.0, start_time.ToSec() + 8.0),
                  gnss_pvts.front().GetPosition<Vector3Type>());
        ASSERT_EQ(Vector3Type(begin.ToSec() + 9.0, begin.ToSec() + 10.0, begin.ToSec() + 11.0),
                  gnss_pvts.front().GetPositionCov<Vector3Type>());

        ASSERT_EQ(end_time.ToSec(), gnss_pvts.back().GetTimestamp().ToSec());
        ASSERT_EQ(Vector3Type(end_time.ToSec(), end_time.ToSec() + 1.0, end_time.ToSec() + 2.0),
                  gnss_pvts.back().GetVelocity<Vector3Type>());
        ASSERT_EQ(Vector3Type((end - dt).ToSec() + 3.0, (end - dt).ToSec() + 4.0, (end - dt).ToSec() + 5.0),
                  gnss_pvts.back().GetVelocityCov<Vector3Type>());
        ASSERT_EQ(Vector3Type(end_time.ToSec() + 6.0, end_time.ToSec() + 7.0, end_time.ToSec() + 8.0),
                  gnss_pvts.back().GetPosition<Vector3Type>());
        ASSERT_EQ(Vector3Type((end - dt).ToSec() + 9.0, (end - dt).ToSec() + 10.0, (end - dt).ToSec() + 11.0),
                  gnss_pvts.back().GetPositionCov<Vector3Type>());

        /* Check other measurments */
        for (uint64_t i = 1u; i < num - 1; ++i)
        {
            ASSERT_EQ(gt_time.at(i).ToSec(), gnss_pvts.at(i).GetTimestamp().ToSec());
            ASSERT_EQ(gt_velocity.at(i), gnss_pvts.at(i).GetVelocity<Vector3Type>());
            ASSERT_EQ(gt_velocity_cov.at(i), gnss_pvts.at(i).GetVelocityCov<Vector3Type>());
            ASSERT_EQ(gt_position.at(i), gnss_pvts.at(i).GetPosition<Vector3Type>());
            ASSERT_EQ(gt_position_cov.at(i), gnss_pvts.at(i).GetPositionCov<Vector3Type>());
        }
    }
    {
        /* Case 7: the start and end timestamp are equal to the timestamp of the member of buffer */
        const holo::common::Timestamp start_time = begin;
        const holo::common::Timestamp end_time   = end;

        ASSERT_TRUE(mm.GetAlignedMeasurementsBetween(start_time, end_time, gnss_pvts));

        /* Check other measurments */
        for (uint64_t i = 1u; i < num; ++i)
        {
            ASSERT_EQ(gt_time.at(i).ToSec(), gnss_pvts.at(i).GetTimestamp().ToSec());
            ASSERT_EQ(gt_velocity.at(i), gnss_pvts.at(i).GetVelocity<Vector3Type>());
            ASSERT_EQ(gt_velocity_cov.at(i), gnss_pvts.at(i).GetVelocityCov<Vector3Type>());
            ASSERT_EQ(gt_position.at(i), gnss_pvts.at(i).GetPosition<Vector3Type>());
            ASSERT_EQ(gt_position_cov.at(i), gnss_pvts.at(i).GetPositionCov<Vector3Type>());
        }
    }
    {
        /* Case 8: Only one measurement, could not be extrapolated or interpolated */
        MeasurementsManagerBase mm2;
        GnssPvtType             gnss_pvt;
        gnss_pvt.SetTimestamp(holo::common::Timestamp(1.0));
        mm2.AddMeasurement(gnss_pvt);
        {
            {
                /* Could not be interpolated */
                const holo::common::Timestamp start_time = holo::common::Timestamp(0.5);
                const holo::common::Timestamp end_time   = holo::common::Timestamp(1.0);
                std::vector<GnssPvtType> gnss_pvts;
                ASSERT_FALSE(mm2.GetAlignedMeasurementsBetween(start_time, end_time, gnss_pvts));
            }
            {
                /* Could not be extrapolated */
                const holo::common::Timestamp start_time = holo::common::Timestamp(1.0);
                const holo::common::Timestamp end_time   = holo::common::Timestamp(1.5);
                std::vector<GnssPvtType> gnss_pvts;
                ASSERT_FALSE(mm2.GetAlignedMeasurementsBetween(start_time, end_time, gnss_pvts));
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MeasurementsManagerBase, GetAlignedChassisStatesBetween)
{
    MeasurementsManagerBase mm;

    /* generate a set of measurements and ground truth */
    const holo::common::Timestamp begin(0.0);
    const holo::common::Duration  dt      = holo::common::Duration(1e-2);  // 100hz
    const uint8_t         num     = 11u;
    const holo::common::Timestamp end     = begin + dt * (num - 1u);
    const holo::common::Timestamp begin_1 = begin + holo::common::Duration(1e-5);
    const holo::common::Timestamp end_1   = end - holo::common::Duration(1e-5);

    for (holo::common::Timestamp t = begin; t <= end; t += dt)
    {
        holo::common::ChassisState m;
        m.SetTimestamp(t);
        mm.AddMeasurement(m);
    }

    /* get the start and end */
    std::vector<holo::common::ChassisState> chassis_states;
    holo::bool_t                    ret = mm.GetAlignedMeasurementsBetween(begin_1, end_1, chassis_states);

    /*  unit tests */
    ASSERT_TRUE(ret);
    ASSERT_EQ(begin_1, chassis_states.front().GetTimestamp());
    ASSERT_EQ(end_1, chassis_states.back().GetTimestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
