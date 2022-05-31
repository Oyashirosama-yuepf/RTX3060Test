/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file fabricated_factor_graph.h
 * @brief the test fixture which fabricate a factor graph
 * @author lichao@holomatic.com
 * @date Dec 10, 2019
 */

#ifndef HOLO_LOCALIZATION_TEST_FIXTURES_FABRICATED_FACTOR_GRAPH_H_
#define HOLO_LOCALIZATION_TEST_FIXTURES_FABRICATED_FACTOR_GRAPH_H_

#include <gtest/gtest.h>
#include <holo/numerics/matrix.h>

#include <holo/localization/backend/factor_graph.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
using Odometry     = OdometryType;
using Imu          = ImuType;
using ImuBias      = ImuBiasType;
using GnssPosition = GnssPositionType;
using Pose3        = Pose3Type;
using Rot3         = Rot3Type;
using Point3       = Point3Type;
using Point3d      = Point3Type;
using Vector3      = Vector3Type;

/**
 * @brief This class defines test data generator for smoother unit test.
 *
 */
class FabricatedFactorGraph : public ::testing::Test
{
public:
    using ProjectionMeasurement = ProjectionFactor::ProjectionMeasurement;
    /**
     * @brief Construct a new Fabricated Factor Graph object
     *
     */
    FabricatedFactorGraph()
    {
    }

    /**
     * @brief Destroy the Fabricated Factor Graph object
     *
     */
    virtual ~FabricatedFactorGraph() noexcept
    {
    }

    /**
     * @brief Setup data
     *
     */
    virtual void SetUp()
    {
        /* create camera extrinsic */
        extrinsic_ = Pose3Type(Rot3Type::Rz(-M_PI/2.0), Point3Type()) * Pose3Type(Rot3Type::Rx(-M_PI/2.0), Point3Type());

        /* create camera intrinsic */
        const Scalar f = Scalar(952), s = Scalar(0), u0 = Scalar(1920/2), v0 = Scalar(1024/2);
        K_ = Matrix3Type::Identity();
        K_(0, 0) = f;
        K_(1, 1) = f;
        K_(0, 2) = u0;
        K_(1, 2) = v0;
        K_(0, 1) = s;

        /* create landmark in global coordinate */
        landmark_ = Point3Type(UTMxBeijing + 30.0, UTMyBeijing + 5.0, 2.0);

    }

    /**
     * @brief Teardowm data
     *
     */
    virtual void TearDown()
    {
    }

    FactorGraph GenerateFactorGraph(const OdometrySource& mode = static_cast<OdometrySource>(7) /* GNSS + IMU + VISION */)
    {
        /* create factor arrays */
        PriorPoseFactors     prior_pose_factors;
        PriorVelocityFactors prior_velocity_factors;
        PriorImuBiasFactors  prior_imubias_factors;
        GnssFactors          gnss_factors;
        ImuFactors           imu_factors;
        ImuBiasFactors       imubias_factors;
        LaneFactors          lane_factors;
        ProjectionFactors    projection_factors;
        VelocityFactors      velocity_factors;

        /* Create value arrays */
        Pose3Values     pose_values;
        Velocity3Values velocity_values;
        ImuBiasValues   imubias_values;
        Position3Values position_values;

        /* reserve factor arrays */
        prior_pose_factors.reserve(1u);
        prior_velocity_factors.reserve(1u);
        prior_imubias_factors.reserve(1u);
        gnss_factors.reserve(100u);
        imu_factors.reserve(100u);
        imubias_factors.reserve(100u);
        lane_factors.reserve(100u);
        projection_factors.reserve(1000u);
        velocity_factors.reserve(100u);

        /* reserve value arrays */
        pose_values.reserve(100u);
        velocity_values.reserve(100u);
        imubias_values.reserve(100u);
        position_values.reserve(1000u);

        /* construct a factor graph */
        FactorGraph fg;
        Timestamp   last_stamp;
        Timestamp   stamp   = Timestamp(87u, 0u);  // initial time
        Duration    gps_dur = Duration(0.1);       // imu duration
        for (size_t i = 0; i <= 20; i++)
        {
            Point3d p(UTMxBeijing + i, UTMyBeijing, 0.0);  // location

            if (i == 0)
            {
                PriorPoseFactor     prior_pose_factor;
                PriorVelocityFactor prior_velocity_factor;
                PriorImuBiasFactor  prior_imubias_factor;

                Pose3 prior_pose(Rot3(), Point3(p.GetX(), p.GetY(), p.GetZ()));
                last_pose_ = prior_pose.GetTranslation();
                Vector3          prior_vel(10.0, 0.0, 0.0);
                AdvancedNavstate prior_navs(prior_pose, prior_vel);

                /* Create prior pose factor */
                prior_pose_factor.symbol.value_type = ValueType::POSE3;
                prior_pose_factor.symbol.index      = stamp.ToNsec();
                prior_pose_factor.measurement       = prior_pose;
                prior_pose_factor.covariance_matrix = Matrix6Type::Identity();

                /* Create prior velocity factor */
                prior_velocity_factor.symbol.value_type = ValueType::VELOCITY3;
                prior_velocity_factor.symbol.index      = stamp.ToNsec();
                prior_velocity_factor.measurement       = prior_vel;
                prior_velocity_factor.covariance_matrix = Matrix3Type::Identity();

                /* create prior imubias factor */
                prior_imubias_factor.symbol.value_type = ValueType::IMUBIAS;
                prior_imubias_factor.symbol.index      = stamp.ToNsec();
                prior_imubias_factor.measurement       = ImuBiasType();
                prior_imubias_factor.covariance_matrix = Matrix6Type::Identity();

                StampedAdvancedNavstate prior_state(stamp, prior_navs);
                LOG(INFO) << "Add prior factor: " << prior_state.GetTimestamp().ToString()
                          << "\tprior positon: " << prior_state.GetData().GetPose().GetTranslation()
                          << "\tprior rotation: " << prior_state.GetData().GetPose().GetRotation().RPY().Transpose()
                          << "\tprior velocity: " << prior_state.GetData().GetVelocity().Transpose();

                prior_pose_factors.push_back(prior_pose_factor);
                prior_velocity_factors.push_back(prior_velocity_factor);
                prior_imubias_factors.push_back(prior_imubias_factor);
            }
            else
            {
                if (mode | OdometrySource::ODOMETRY_SOURCE_GNSS)
                {
                    GnssFactor gnss_factor;
                    gnss_factor.symbol.value_type = ValueType::POSE3;
                    gnss_factor.symbol.index      = stamp.ToNsec();
                    gnss_factor.measurement       = p;
                    gnss_factor.covariance_matrix = Matrix3Type::Identity();
                    gnss_factors.push_back(gnss_factor);
                }

                if (mode | OdometrySource::ODOMETRY_SOURCE_VISION)
                {
                    ProjectionFactor prj_factor;
                    prj_factor.symbols.reserve(2u);
                    Symbol prj_symbol;
                    prj_symbol.value_type = ValueType::POSE3;
                    prj_symbol.index      = stamp.ToNsec();
                    prj_factor.symbols.push_back(prj_symbol);
                    prj_symbol.value_type = ValueType::POSITION3;
                    prj_symbol.index      = 1u;
                    prj_factor.symbols.push_back(prj_symbol);

                    /* Create measurement */
                    // T_wc = T_wb * T_bc
                    Pose3Type   car_pose(Rot3(), p);
                    const Pose3 T_wc = car_pose * extrinsic_;
                    // reproject the point with camera pose
                    const Vector3Type point3 = K_ * (T_wc.Inverse() * landmark_).As<Vector3Type>();

                    /* Create Projection Measurement */
                    ProjectionMeasurement prj_measurement;
                    prj_measurement.bTc              = extrinsic_;
                    prj_measurement.K                = K_;
                    prj_measurement.measured         = Point2Type(point3[0] / point3[2], point3[1] / point3[2]);
                    prj_factor.measurement           = prj_measurement;
                    prj_factor.covariance_matrix     = 0.2 * Matrix2Type::Identity();
                    projection_factors.push_back(prj_factor);
                }

                /* binary factors */
                /* Create imu factor */
                std::vector<Imu> imu_set;
                Duration         imu_dur     = Duration(0.01);
                size_t           imu_counter = 1u;
                for (Timestamp ts = last_stamp; ts <= stamp; ts += imu_dur)
                {
                    Imu imu;
                    imu.SetTimestamp(ts);
                    imu.SetLinearAcceleration(Point3Type(0.0, 0.0, 9.81));
                    imu_set.push_back(imu);
                    LOG(INFO) << "imu counter: " << imu_counter;
                    imu_counter++;
                }

                ImuPreintegrationParameters  parameters;
                ImuPreintegration            preintegration(parameters);
                ImuPreintegrationMeasurement pim = *(preintegration.Preintegrate(imu_set, ImuBiasType()));

                ImuFactor imu_factor;
                imu_factor.symbols.reserve(5u);
                Symbol imu_symbol;
                imu_symbol.value_type = ValueType::POSE3;
                imu_symbol.index      = last_stamp.ToNsec();
                imu_factor.symbols.push_back(imu_symbol);
                imu_symbol.value_type = ValueType::VELOCITY3;
                imu_symbol.index      = last_stamp.ToNsec();
                imu_factor.symbols.push_back(imu_symbol);
                imu_symbol.value_type = ValueType::POSE3;
                imu_symbol.index      = stamp.ToNsec();
                imu_factor.symbols.push_back(imu_symbol);
                imu_symbol.value_type = ValueType::VELOCITY3;
                imu_symbol.index      = stamp.ToNsec();
                imu_factor.symbols.push_back(imu_symbol);
                imu_symbol.value_type = ValueType::IMUBIAS;
                imu_symbol.index      = last_stamp.ToNsec();
                imu_factor.symbols.push_back(imu_symbol);

                imu_factor.measurement       = pim;
                imu_factor.covariance_matrix = pim.GetPreintegratedMeasurementCovariance();
                imu_factors.push_back(imu_factor);

                /* Create imu bias factor */
                ImuBiasFactor imubias_factor;
                imubias_factor.symbols.reserve(2u);
                Symbol imubias_symbol;
                imubias_symbol.value_type = ValueType::IMUBIAS;
                imubias_symbol.index      = last_stamp.ToNsec();
                imubias_factor.symbols.push_back(imubias_symbol);
                imubias_symbol.value_type = ValueType::IMUBIAS;
                imubias_symbol.index      = stamp.ToNsec();
                imubias_factor.symbols.push_back(imubias_symbol);

                imubias_factor.measurement       = ImuBiasType();
                imubias_factor.covariance_matrix = Matrix6Type::Identity();
                imubias_factors.push_back(imubias_factor);
            }

            /* Create initial navstates */
            Pose3                   nav_p(Rot3(), Point3(p.GetX(), p.GetY(), 0.0));
            Vector3                 v(10.0, 0.0, 0.0);
            AdvancedNavstate        fns(nav_p, v);
            StampedAdvancedNavstate sns(stamp, fns);
            LOG(INFO) << "Add navstate: " << sns.GetTimestamp().ToString()
                      << "\t, position: " << sns.GetData().GetPose().GetTranslation()
                      << "\t, rotation: " << sns.GetData().GetPose().GetRotation().RPY().Transpose()
                      << "\t, velocity: " << sns.GetData().GetVelocity().Transpose();

            Pose3Value pose_value;
            pose_value.symbol.value_type = ValueType::POSE3;
            pose_value.symbol.index      = stamp.ToNsec();
            pose_value.timestamp         = stamp;
            pose_value.state             = nav_p;

            Velocity3Value velocity_value;
            velocity_value.symbol.value_type = ValueType::VELOCITY3;
            velocity_value.symbol.index      = stamp.ToNsec();
            velocity_value.timestamp         = stamp;
            velocity_value.state             = v;

            ImuBiasValue imubias_value;
            imubias_value.symbol.value_type = ValueType::IMUBIAS;
            imubias_value.symbol.index      = stamp.ToNsec();
            imubias_value.timestamp         = stamp;
            imubias_value.state             = ImuBiasType();

            if (position_values.size() == 0u)
            {
                Position3Value position_value;
                position_value.symbol.value_type = ValueType::POSITION3;
                position_value.symbol.index      = 1u;
                position_value.timestamp         = stamp;
                position_value.state             = landmark_;
                position_values.push_back(position_value);
            }

            pose_values.push_back(pose_value);
            velocity_values.push_back(velocity_value);
            imubias_values.push_back(imubias_value);
            LOG(INFO) << "==============================================";

            /* update timestamps */
            last_stamp = stamp;
            last_pose_ = p;
            stamp += gps_dur;
        }

        fg.prior_pose_factors     = OptionalT<PriorPoseFactors>(prior_pose_factors);
        fg.prior_velocity_factors = OptionalT<PriorVelocityFactors>(prior_velocity_factors);
        fg.prior_imu_bias_factors = OptionalT<PriorImuBiasFactors>(prior_imubias_factors);

        fg.gnss_factors     = OptionalT<GnssFactors>(gnss_factors);
        fg.imu_factors      = OptionalT<ImuFactors>(imu_factors);
        fg.imu_bias_factors = OptionalT<ImuBiasFactors>(imubias_factors);
        // fg.relative_pose_factors     = OptionalT<RelativePoseFactors>(relative_pose_factors);
        // fg.relative_velocity_factors = OptionalT<RelativeVelocityFactors>(relative_velocity_factors);
        // fg.lane_factors              = OptionalT<LaneFactors>(lane_factors);
        // fg.sign_factors              = OptionalT<SignFactors>(sign_factors);
        fg.projection_factors           = OptionalT<ProjectionFactors>(projection_factors);
        // fg.velocity_factors              = OptionalT<VelocityFactors>(velocity_factors);

        fg.pose_values     = OptionalT<Pose3Values>(pose_values);
        fg.velocity_values = OptionalT<Velocity3Values>(velocity_values);
        fg.imu_bias_values = OptionalT<ImuBiasValues>(imubias_values);
        fg.position_values = OptionalT<Position3Values>(position_values);

        return fg;
    }

private:
    // Latitude of a known test point in Beijing
    const float64_t LatitudeBeijing = 39.90421111;
    // Longitude of a known test point in Beijing
    const float64_t LongitudeBeijing = 116.40741111;
    // UTM coordinate X of the known test point in Beijing
    const float64_t UTMxBeijing = 449346.01934345544;
    // UTM coordinate Y of the known test point in Beijing
    const float64_t UTMyBeijing = 4417293.7209900115;
    // UTM Zone Id of Beijing
    // const size_t    UTMZoneIdBeijing = 50;

    Point3 last_pose_;

    Pose3Type   extrinsic_;        //< extrinsic from camera to body
    Matrix3Type K_;                //< intrinsic matrix
    Point3Type  landmark_;         //< the global position of landmark

};  // class FabricatedFactorGraph

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_TEST_FIXTURES_FABRICATED_FACTOR_GRAPH_H_
