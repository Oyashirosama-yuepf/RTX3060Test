/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file test_smoother.cpp
 * @brief the unit test for smoother wrapper.
 * @author lichao@holomatic.com
 * @date Dec 10, 2019
 */

#include <gtest/gtest.h>
#include <holo/localization/backend/smoother.h>
#include "../fixture/fabricated_factor_graph.h"

using FactorGraph        = holo::localization::FactorGraph;
using Smoother           = holo::localization::Smoother;
using SmootherState      = holo::localization::SmootherState;
using SmootherResult     = holo::OptionalT<SmootherState>;
using SmootherParameters = holo::localization::SmootherParameters;

using FabricatedFactorGraph = holo::localization::FabricatedFactorGraph;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CheckEquivalentBetweenTwoVectors(const T& actual, const T& expected)
{
    ASSERT_TRUE(actual.size() == expected.size());

    const uint8_t num_poses = actual.size();
    for (uint8_t i = 0; i < num_poses; ++i)
    {
        ASSERT_TRUE(actual[i] == expected[i]);
        ASSERT_TRUE(actual[i] == expected[i]);
        ASSERT_TRUE(actual[i] == expected[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckEquivalentBetweenSmootherState(const SmootherState& actual, const SmootherState& expected)
{
    LOG(INFO) << "actual size: " << actual.factor_graph.pose_values.GetData().size();
    LOG(INFO) << "expected size: " << expected.factor_graph.pose_values.GetData().size();
    ASSERT_TRUE(actual.factor_graph.pose_values.GetData().size() == expected.factor_graph.pose_values.GetData().size());
    ASSERT_TRUE(actual.factor_graph.position_values.GetData().size() ==
                expected.factor_graph.position_values.GetData().size());

    const uint8_t num_poses = actual.factor_graph.pose_values.GetData().size();
    for (uint8_t i = 0; i < num_poses; ++i)
    {
        ASSERT_TRUE(actual.factor_graph.pose_values.GetData()[i].state ==
                    expected.factor_graph.pose_values.GetData()[i].state);
        ASSERT_TRUE(actual.factor_graph.velocity_values.GetData()[i].state.IsApprox(
            expected.factor_graph.velocity_values.GetData()[i].state, 1e-9));
    }

    const uint8_t num_positions = actual.factor_graph.position_values.GetData().size();
    for (uint8_t i = 0; i < num_positions; ++i)
    {
        ASSERT_TRUE(actual.factor_graph.position_values.GetData()[i].state ==
                    expected.factor_graph.position_values.GetData()[i].state);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(FabricatedFactorGraph, GnssAndImuPoseOnlySmoothingTest)
{
    /* Step1, Prepare factor graph */
    const FactorGraph factor_graph = GenerateFactorGraph();

    /* Step2, Generate expected SmootherState */
    SmootherState expected_smoother_state;
    expected_smoother_state.factor_graph = factor_graph;

    /* Step3, Smoothing factor graph, then get actual SmootherState*/
    SmootherParameters params;
    Smoother           smoother(params);
    SmootherResult     actual_smoother_state = smoother.Run(factor_graph);

    /* Step4, Check correctioness of SmootherState */
    CheckEquivalentBetweenSmootherState(*actual_smoother_state, expected_smoother_state);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(FabricatedFactorGraph, GnssAndImuPoseOnlySmoothingGetAllValuesTest)
{
    /* Step1, Prepare factor graph */
    const FactorGraph factor_graph = GenerateFactorGraph();

    /* Step2, Generate expected SmootherState */
    SmootherState expected_smoother_state;
    expected_smoother_state.factor_graph = factor_graph;

    /* Step3, Smoothing factor graph, then get actual SmootherState*/
    SmootherParameters params;
    params.get_all_values = true;
    Smoother       smoother(params);
    SmootherResult actual_smoother_state = smoother.Run(factor_graph);

    /* Step4, Check correctioness of SmootherState */
    CheckEquivalentBetweenSmootherState(*actual_smoother_state, expected_smoother_state);

    /* Check Copy constructor */
    ASSERT_NO_THROW(const Smoother smoother1(smoother));

    /* Check Copy assignment operator */
    Smoother smoother2(params);
    ASSERT_NO_THROW(smoother2 = smoother);

    /* Check Move constructor */
    ASSERT_NO_THROW(const Smoother smoother3 = std::move(smoother2));

    /* Check Move assignment operator */
    Smoother smoother4(params);
    Smoother smoother5(params);
    ASSERT_NO_THROW(smoother5 = std::move(smoother4));

    /* Check Reset function */
    ASSERT_NO_THROW(smoother.Reset());

    /* Check GetParameter */
    ASSERT_NO_THROW(smoother.GetParameters());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEST_F(FabricatedFactorGraph, GnssImuAndLanePoseOnlySmoothingTest)
//{
//    /* Step1, Prepare factor graph */
//    FactorGraph factor_graph;
//
//    /* Step2, Generate expected SmootherState */
//    SmootherState expected_smoother_state;
//
//    /* Step3, Smoothing factor graph, then get actual SmootherState*/
//    SmootherParameters params;
//    Smoother           smoother(params);
//    SmootherState      actual_smoother_state = smoother.Run(factor_graph);
//
//    /* Step4, Check correctioness of SmootherState */
//    CheckEquivalentBetweenSmootherState(actual_smoother_state, expected_smoother_state);
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEST_F(FabricatedFactorGraph, VslamSmoothingTest)
//{
//    /* Step1, Prepare factor graph */
//    FactorGraph factor_graph;
//
//    /* Step2, Generate expected SmootherState */
//    SmootherState expected_smoother_state;
//
//    /* Step3, Smoothing factor graph, then get actual SmootherState*/
//    SmootherParameters params;
//    Smoother           smoother(params);
//    SmootherState      actual_smoother_state = smoother.Run(factor_graph);
//
//    /* Step4, Check correctioness of SmootherState */
//    CheckEquivalentBetweenSmootherState(actual_smoother_state, expected_smoother_state);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Smoother, velocity_factor)
{
    /* groundtruth */
    /// @brief velocity in body frame
    const holo::localization::Vector3Type velocity_b(5.0f, 0.0f, 0.0f);

    /// @brief rotation of body frame in world frame
    const holo::localization::Rot3Type wRb = holo::localization::Rot3Type::Ry(M_PI_2);

    /// @brief translation of body frame in world frame
    const holo::localization::Point3Type wtb = holo::localization::Point3Type(2.0f, 0.0f, 0.0f);

    /// @brief body pose in world frame
    const holo::localization::Pose3Type wTb = holo::localization::Pose3Type(wRb, wtb);

    /// @brief velocity in world frame
    const holo::localization::Vector3Type velocity_w = wRb.Rotate(velocity_b);

    /// @brief pose and velocity index
    const holo::uint64_t                  pose_index     = 1u;
    const holo::uint64_t                  velocity_index = 1u;
    const holo::localization::Vector6Type pose_sigmas(1e-9, 1e-9, 1e-9, 1e-9, 1e-9, 1e-9);
    const holo::localization::Vector3Type velocity_sigmas(1e-9, 1e-9, 1e-9);

    holo::localization::FactorGraph graph;

    // create prior pose factor
    {
        // initialize symbol
        holo::localization::Symbol symbol;
        {
            symbol.value_type = holo::localization::ValueType::POSE3;
            symbol.index      = pose_index;
        }

        // initialize factor
        holo::localization::PriorPoseFactor factor;
        {
            factor.symbol            = symbol;
            factor.measurement       = wTb;
            factor.covariance_matrix = pose_sigmas.CwiseSquare().AsDiagonal();
        }

        // initialize pose value
        holo::localization::Pose3Value value;
        {
            value.symbol    = symbol;
            value.timestamp = holo::Timestamp(1.0);
            value.state     = wTb;
        }

        // add to graph
        graph.prior_pose_factors =
            holo::make_optional<holo::localization::PriorPoseFactors>(holo::localization::PriorPoseFactors{factor});
        graph.pose_values =
            holo::make_optional<holo::localization::Pose3Values>(holo::localization::Pose3Values{value});
    }

    // create velocity factor
    {
        holo::localization::VelocityFactor factor;
        holo::localization::Symbol         ps, vs;
        ps.value_type = holo::localization::ValueType::POSE3;
        ps.index      = pose_index;
        vs.value_type = holo::localization::ValueType::VELOCITY3;
        vs.index      = velocity_index;
        factor.symbols.emplace_back(ps);
        factor.symbols.emplace_back(vs);
        factor.measurement       = velocity_b;
        factor.covariance_matrix = velocity_sigmas.CwiseSquare().AsDiagonal();

        // initialize velocity value
        holo::localization::Velocity3Value value;
        {
            value.symbol    = vs;
            value.timestamp = holo::Timestamp(1.0);
            value.state     = holo::localization::Vector3Type(1.0f, -1.0f, -4.0f);
        }

        // add to graph
        graph.velocity_factors =
            holo::make_optional<holo::localization::VelocityFactors>(holo::localization::VelocityFactors({factor}));
        graph.velocity_values =
            holo::make_optional<holo::localization::Velocity3Values>(holo::localization::Velocity3Values({value}));
    }

    holo::localization::SmootherParameters smoother_params;
    smoother_params.get_all_values                  = true;
    smoother_params.enable_factor_error_computation = true;

    holo::localization::Smoother                             smoother(smoother_params);
    const holo::OptionalT<holo::localization::SmootherState> state = smoother.Run(graph);

    ASSERT_TRUE(state);
    ASSERT_TRUE(state->factor_graph.pose_values);
    ASSERT_TRUE(state->factor_graph.velocity_values);
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.pose_values->size()));
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.velocity_values->size()));
    ASSERT_EQ(wTb, state->factor_graph.pose_values->at(0u).state);
    ASSERT_TRUE(velocity_w.IsApprox(state->factor_graph.velocity_values->at(0u).state, 1e-5));

    // test getCovariance
    for (const auto symbol : graph.velocity_factors->at(0u).symbols)
    {
        auto cov = smoother.GetMarginalCovariance(symbol);
        ASSERT_NE(cov.GetRows(), 0u);
    }
    ASSERT_THROW(smoother.GetMarginalCovariance(holo::localization::Symbol()), std::runtime_error);

    // test GetMarginalCovariance which input symbols
    std::vector<holo::localization::Symbol> symbols;

    for (const auto symbol : graph.velocity_factors->at(0u).symbols)
    {
        symbols.push_back(symbol);
        auto cov = smoother.GetMarginalCovariance(symbols);
        ASSERT_NE(cov.GetRows(), 0u);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Smoother, wheel_speed_factor)
{
    /* groundtruth */
    /// @brief wheel preintegrated measurement
    const holo::localization::Vector3Type preintegrated_dist(2.0, 0.0, 0.0);
    const holo::localization::Point3Type  pwm_m(2.0, 0.0, 0.0);
    // body pose in imu frame
    const holo::localization::Pose3Type iTb = holo::localization::Pose3Type::Identity();
    holo::localization::WheelPreintegrationMeasurement::WheelPreintegrationParams pwm_params =
        holo::localization::WheelPreintegrationMeasurement::WheelPreintegrationParams();

    // create new pwm
    holo::localization::WheelPreintegrationMeasurement pwm = holo::localization::WheelPreintegrationMeasurement(
        pwm_params, iTb, preintegrated_dist, holo::localization::Matrix3Type::Zero(),
        (holo::localization::Vector3Type(1e-4, 1e-4, 1e-4)).AsDiagonal(), 0.1);

    /// @brief rotation 1 of body frame in world frame
    const holo::localization::Rot3Type wRb1 = holo::localization::Rot3Type::Ry(M_PI_2);
    /// @brief translation of body frame in world frame
    const holo::localization::Point3Type wtb1 = holo::localization::Point3Type(2.0, 0.0, 0.0);
    /// @brief pose1 body pose in world frame
    const holo::localization::Pose3Type wTb1 = holo::localization::Pose3Type(wRb1, wtb1);
    /// @brief pose2 body translation in world frame
    const holo::localization::Point3Type wtb2 = wRb1 * pwm_m + wtb1;
    /// @brief pose2 body pose in world frame
    const holo::localization::Pose3Type wTb2 = holo::localization::Pose3Type(wRb1, wtb2);

    /// @brief pose index
    const holo::uint64_t                  pose1_index = 1u;
    const holo::uint64_t                  pose2_index = 2u;
    const holo::localization::Vector6Type pose_sigmas(1e-9, 1e-9, 1e-9, 1e-9, 1e-9, 1e-9);

    holo::localization::FactorGraph graph;

    holo::localization::PriorPoseFactors prior_pose_factors;
    // create prior pose factor
    {
        // initialize symbol
        holo::localization::Symbol pose1_symbol;
        {
            pose1_symbol.value_type = holo::localization::ValueType::POSE3;
            pose1_symbol.index      = pose1_index;
        }

        // initialize factor
        holo::localization::PriorPoseFactor factor1;
        {
            factor1.symbol            = pose1_symbol;
            factor1.measurement       = wTb1;
            factor1.covariance_matrix = pose_sigmas.CwiseSquare().AsDiagonal();
        }

        prior_pose_factors.emplace_back(factor1);

        // initialize symbol
        holo::localization::Symbol pose2_symbol;
        {
            pose2_symbol.value_type = holo::localization::ValueType::POSE3;
            pose2_symbol.index      = pose2_index;
        }

        // initialize factor
        holo::localization::PriorPoseFactor factor2;
        {
            factor2.symbol            = pose2_symbol;
            factor2.measurement       = wTb2;
            factor2.covariance_matrix = pose_sigmas.CwiseSquare().AsDiagonal();
        }
        prior_pose_factors.emplace_back(factor2);
    }
    graph.prior_pose_factors = holo::make_optional<holo::localization::PriorPoseFactors>(prior_pose_factors);

    // create wheel speed factor
    {
        holo::localization::WheelSpeedFactor factor;
        holo::localization::Symbol           ps1, ps2;
        ps1.value_type = holo::localization::ValueType::POSE3;
        ps1.index      = pose1_index;
        ps2.value_type = holo::localization::ValueType::POSE3;
        ps2.index      = pose2_index;
        factor.symbols.emplace_back(ps1);
        factor.symbols.emplace_back(ps2);
        factor.measurement       = pwm;
        factor.covariance_matrix = pwm.GetPreintegratedMeasurementCovariance();

        // initialize pose value
        holo::localization::Pose3Value pose1_value;
        {
            pose1_value.symbol    = ps1;
            pose1_value.timestamp = holo::Timestamp(1.0);
            pose1_value.state     = wTb1;
        }

        // initialize pose value
        holo::localization::Pose3Value pose2_value;
        {
            pose2_value.symbol    = ps2;
            pose2_value.timestamp = holo::Timestamp(1.0);
            pose2_value.state     = holo::localization::Pose3Type::Identity();
        }

        // add to graph
        graph.wheel_speed_factors =
            holo::make_optional<holo::localization::WheelSpeedFactors>(holo::localization::WheelSpeedFactors({factor}));
        graph.pose_values = holo::make_optional<holo::localization::Pose3Values>(
            holo::localization::Pose3Values({pose1_value, pose2_value}));
    }

    holo::localization::SmootherParameters smoother_params;
    smoother_params.get_all_values                  = true;
    smoother_params.enable_factor_error_computation = true;

    holo::localization::Smoother                             smoother(smoother_params);
    const holo::OptionalT<holo::localization::SmootherState> state = smoother.Run(graph);

    ASSERT_TRUE(state);
    ASSERT_TRUE(state->factor_graph.pose_values);
    ASSERT_EQ(2u, static_cast<uint64_t>(state->factor_graph.pose_values->size()));
    ASSERT_EQ(wTb1, state->factor_graph.pose_values->at(0u).state);
    ASSERT_EQ(wTb2, state->factor_graph.pose_values->at(1u).state);

    // test wheel_speed_factor's symbols is empty case
    for (auto& factor : graph.wheel_speed_factors.GetData())
    {
        factor.symbols.clear();
    }

    graph.prior_pose_factors.GetData().clear();

    holo::localization::SmootherParameters smoother_parameters;
    smoother_parameters.get_all_values        = true;
    smoother_parameters.additional_iterations = 10u;
    smoother_parameters.optimizer_type        = holo::localization::SmootherParameters::OptimizerType::DOGLEG;
    smoother_parameters.relinearize_threshold = 1e-9;
    smoother_parameters.relinearize_skip      = 1u;

    holo::localization::Smoother smoother1(smoother_parameters);
    ASSERT_THROW(smoother1.Run(graph), std::exception);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Smoother, sign_factor)
{
    /* groundtruth */
    /// @brief point in body frame
    const holo::localization::Point3Type map_point(5.0f, 5.0f, 5.0f);

    /// @brief rotation of body frame in world frame
    const holo::localization::Rot3Type wRb = holo::localization::Rot3Type::Ry(M_PI_2);

    /// @brief translation of body frame in world frame
    const holo::localization::Point3Type wtb = holo::localization::Point3Type(2.0f, 0.0f, 0.0f);

    /// @brief body pose in world frame
    const holo::localization::Pose3Type wTb = holo::localization::Pose3Type(wRb, wtb);

    /// @brief camera pose in body frame
    const holo::localization::Pose3Type bTc = holo::localization::Pose3Type();

    /// @brief camera matrix
    holo::localization::Matrix3Type k(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    /// @brief 2d semantic keypoint
    const holo::localization::Vector3Type point3 =
        k * (wTb.Inverse() * map_point).As<holo::localization::Vector3Type>();
    holo::localization::Point2Type        semantic_key_point(point3[0u] / point3[2u], point3[1u] / point3[2u]);

    /// @brief pose and sign index
    const holo::uint64_t                  pose_index = 1u;
    const holo::localization::Vector6Type pose_sigmas(1e-9, 1e-9, 1e-9, 1e-9, 1e-9, 1e-9);
    const holo::localization::Scalar      sign_u_cov_sigma(2.0f);
    const holo::localization::Scalar      sign_v_cov_sigma(2.0f);

    holo::localization::FactorGraph graph;

    // create prior pose factor
    {
        // initialize symbol
        holo::localization::Symbol symbol;
        {
            symbol.value_type = holo::localization::ValueType::POSE3;
            symbol.index      = pose_index;
        }

        // initialize factor
        holo::localization::PriorPoseFactor factor;
        {
            factor.symbol            = symbol;
            factor.measurement       = wTb;
            factor.covariance_matrix = pose_sigmas.AsDiagonal();
        }

        // initialize pose value
        holo::localization::Pose3Value value;
        {
            value.symbol    = symbol;
            value.timestamp = holo::Timestamp(1.0);
            value.state     = wTb;
        }

        // add to graph
        graph.prior_pose_factors =
            holo::make_optional<holo::localization::PriorPoseFactors>(holo::localization::PriorPoseFactors{factor});
        graph.pose_values =
            holo::make_optional<holo::localization::Pose3Values>(holo::localization::Pose3Values{value});
    }

    // create sign factor
    {
        holo::localization::SignFactor factor;
        holo::localization::Symbol     symbol;
        symbol.value_type = holo::localization::ValueType::POSE3;
        symbol.index      = pose_index;
        factor.symbol     = symbol;

        holo::localization::SignFactor::SignMeasurement sign_measurement;
        sign_measurement.bTc = bTc;
        sign_measurement.K   = k;
        std::vector<std::pair<holo::localization::Point2Type, holo::localization::Point3Type>> measured;
        measured.push_back(
            std::pair<holo::localization::Point2Type, holo::localization::Point3Type>(semantic_key_point, map_point));
        sign_measurement.measured = measured;

        factor.measurement = sign_measurement;
        holo::localization::Vector2Type covariance_vector(sign_u_cov_sigma, sign_v_cov_sigma);
        holo::localization::Matrix2Type covariance_matrix = covariance_vector.AsDiagonal();

        factor.covariance_matrix = covariance_matrix;

        // add to graph
        graph.sign_factors =
            holo::make_optional<holo::localization::SignFactors>(holo::localization::SignFactors({factor}));
    }

    holo::localization::SmootherParameters smoother_params;
    smoother_params.get_all_values                  = true;
    smoother_params.enable_factor_error_computation = true;

    holo::localization::Smoother                             smoother(smoother_params);
    const holo::OptionalT<holo::localization::SmootherState> state = smoother.Run(graph);

    ASSERT_TRUE(state);
    ASSERT_EQ(1u, graph.prior_pose_factors.GetData().size());
    ASSERT_EQ(1u, graph.sign_factors.GetData().size());
    ASSERT_TRUE(state->factor_graph.pose_values);
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.pose_values->size()));
    ASSERT_EQ(wTb, state->factor_graph.pose_values->at(0u).state);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Smoother, projection_line_factor)
{
    /**
     * @brief map point of pole
     *
     */
    struct PoleMapPoint
    {
        holo::localization::Point3Type start;  ///< start point
        holo::localization::Point3Type end;    ///< end point
    };

    /**
     * @brief 2d point of pole in image plane
     *
     */
    struct PoleImagePoint
    {
        holo::localization::Point2Type start;  ///< start point
        holo::localization::Point2Type end;    ///< end point
    };

    // create camera intrinsic
    holo::localization::Scalar const fx = holo::localization::Scalar(960);
    holo::localization::Scalar const fy = holo::localization::Scalar(512);
    holo::localization::Scalar const s  = holo::localization::Scalar(0.0);
    holo::localization::Scalar const cx = holo::localization::Scalar(1920 / 2);
    holo::localization::Scalar const cy = holo::localization::Scalar(1024 / 2);

    holo::localization::Matrix3Type K = holo::localization::Matrix3Type::Identity();
    K(0u, 0u)                         = fx;
    K(1u, 1u)                         = fy;
    K(0u, 1u)                         = s;
    K(0u, 2u)                         = cx;
    K(1u, 2u)                         = cy;

    // create truth wTb
    holo::localization::Pose3Type const truth_wTb(holo::localization::Rot3Type::Rz(M_PI / 2),
                                                  holo::localization::Point3Type());

    // create bTc
    holo::localization::Pose3Type const bTc =
        holo::localization::Pose3Type(holo::localization::Rot3Type::Rz(-M_PI / 2), holo::localization::Point3Type()) *
        holo::localization::Pose3Type(holo::localization::Rot3Type::Rx(-M_PI / 2), holo::localization::Point3Type());

    holo::localization::Scalar const left_x = -5.0;
    holo::localization::Scalar const y      = 10.0;
    holo::localization::Scalar const z      = 5.0;

    // cerate map point
    PoleMapPoint pole_map_point;

    holo::localization::Point3Type start_map_point(left_x, y, 0.0);
    holo::localization::Point3Type end_map_point(left_x, y, z);
    pole_map_point.start = start_map_point;
    pole_map_point.end   = end_map_point;

    // create image point
    PoleImagePoint pole_image_point;

    holo::localization::Vector3Type start_point3 =
        K * ((truth_wTb * bTc).Inverse() * pole_map_point.start).As<holo::localization::Vector3Type>();
    holo::localization::Point2Type  start_point2(start_point3[0u] / start_point3[2u],
                                                start_point3[1u] / start_point3[2u]);
    holo::localization::Vector3Type end_point3 =
        K * ((truth_wTb * bTc).Inverse() * pole_map_point.end).As<holo::localization::Vector3Type>();
    holo::localization::Point2Type  end_point2(end_point3[0u] / end_point3[2u], end_point3[1u] / end_point3[2u]);
    pole_image_point.start = start_point2;
    pole_image_point.end   = end_point2;

    // create index
    uint64_t const index = 1u;

    // create factor graph
    holo::localization::FactorGraph factor_graph;

    // add prior pose factor
    holo::localization::PriorPoseFactor prior_pose_factor;
    prior_pose_factor.symbol.index = index;
    prior_pose_factor.measurement  = truth_wTb;
    holo::localization::Vector6Type sigmas{0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    holo::localization::Matrix6Type covariance_matrix = sigmas.CwiseSquare().AsDiagonal();
    prior_pose_factor.covariance_matrix               = covariance_matrix;

    factor_graph.prior_pose_factors = holo::make_optional<holo::localization::PriorPoseFactors>(
        holo::localization::PriorPoseFactors({prior_pose_factor}));

    // add projection line factor and init value
    holo::localization::Line2Type const line =
        holo::localization::Line2Type(pole_image_point.start, pole_image_point.end);

    std::vector<holo::localization::Point3Type> pts;
    pts.push_back(pole_map_point.start);
    pts.push_back(pole_map_point.end);

    holo::localization::ProjectedLineFactor projection_line_factor;
    projection_line_factor.symbol.index            = index;
    projection_line_factor.measurement.bTc         = bTc;
    projection_line_factor.measurement.K           = K;
    projection_line_factor.measurement.source_pts  = pts;
    projection_line_factor.measurement.target_line = line;
    projection_line_factor.huber_loss_threshold    = 10.0;
    holo::localization::Scalar const noise_sigma   = 1.0;
    projection_line_factor.covariance_matrix       = noise_sigma * noise_sigma;
    factor_graph.projection_line_factors           = holo::make_optional<holo::localization::ProjectedLineFactors>(
        holo::localization::ProjectedLineFactors({projection_line_factor}));

    // add values
    holo::localization::Pose3Value pose3value;
    pose3value.symbol.index = index;
    pose3value.state        = truth_wTb;
    factor_graph.pose_values =
        holo::make_optional<holo::localization::Pose3Values>(holo::localization::Pose3Values({pose3value}));

    holo::localization::SmootherParameters smoother_params;

    holo::localization::Smoother                             smoother(smoother_params);
    const holo::OptionalT<holo::localization::SmootherState> state = smoother.Run(factor_graph);

    ASSERT_TRUE(state);
    ASSERT_EQ(1u, factor_graph.projection_line_factors.GetData().size());
    ASSERT_TRUE(state->factor_graph.pose_values);
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.pose_values->size()));
    ASSERT_EQ(truth_wTb, state->factor_graph.pose_values->at(0u).state);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Smoother, camera_imu_extrinsic_calib_factor)
{
    /// @brief gtsam type ground truth
    holo::localization::Matrix3Type const             K(900.0, 0.0, 640.0, 0.0, 900.0, 510.0, 0.0, 0.0, 1.0);
    std::vector<holo::localization::Point3Type> const gt_pt3_ws{holo::localization::Point3Type(23.0, 7.5, 9.0),
                                                                holo::localization::Point3Type(22.5, 5.0, 7.0),
                                                                holo::localization::Point3Type(25.0, 2.5, 8.0)};
    holo::localization::Scalar const                  roll  = -M_PI / 2.0;
    holo::localization::Scalar const                  pitch = 0.0;
    holo::localization::Scalar const                  yaw   = -M_PI / 2.0;
    holo::localization::Vector3Type const             rpy(roll, pitch, yaw);
    holo::localization::Rot3Type const                iRc = holo::localization::Rot3Type::RzRyRx(roll, pitch, yaw);
    holo::localization::Point3Type const              itc = holo::localization::Point3Type(2.0, 0.0, 1.0);
    holo::localization::Pose3Type const               iTc(iRc, itc);
    holo::uint64_t                                    rpy_index = 0u;
    holo::uint64_t                                    itc_index = 1u;
    holo::localization::Vector2Type                   sigmas{0.1, 0.1};
    holo::localization::Matrix2Type                   covariance_matrix = sigmas.CwiseSquare().AsDiagonal();

    /// @brief construct factor graph
    holo::uint16_t                                                    num_poses = 3u;
    FactorGraph                                                       graph;
    holo::localization::CameraImuExtrinsicCalibFactors                camera_imu_factors;
    std::unordered_map<holo::uint16_t, holo::localization::Pose3Type> gt_poses;
    std::unordered_map<holo::uint16_t, holo::localization::Pose3Type> noise_poses;

    for (holo::uint16_t i = 0u; i < gt_pt3_ws.size(); i++)
    {
        holo::localization::Point3Type ptw = gt_pt3_ws.at(i);

        for (holo::uint16_t j = 0u; j < num_poses; j++)
        {
            holo::localization::Scalar const      step  = holo::localization::Scalar(j);
            holo::localization::Scalar const      roll  = 0.01 * step;
            holo::localization::Scalar const      pitch = -0.03 * step;
            holo::localization::Scalar const      yaw   = 0.03 * step;
            holo::localization::Scalar const      x     = 4.0 + 1.0 * step;
            holo::localization::Scalar const      y     = 5.0 - 0.5 * step;
            holo::localization::Scalar const      z     = 6.0 + 0.5 * step;
            holo::localization::Rot3Type const    wRi   = holo::localization::Rot3Type::RzRyRx(roll, pitch, yaw);
            holo::localization::Point3Type const  wti   = holo::localization::Point3Type(x, y, z);
            holo::localization::Pose3Type const   wTi(wRi, wti);
            holo::localization::Point3Type const  ptc = (wTi * iTc).TransformTo(ptw);
            holo::localization::Vector3Type const pti = K * ptc.As<holo::localization::Vector3Type>();
            holo::localization::Point2Type const  measured(pti(0u) / pti(2u), pti(1u) / pti(2u));

            // symbols
            holo::localization::Symbol wTi_symbol;
            wTi_symbol.value_type = holo::localization::ValueType::POSE3;
            wTi_symbol.index      = j;
            holo::localization::Symbol ptw_symbol;
            ptw_symbol.value_type = holo::localization::ValueType::POSITION3;
            ptw_symbol.index      = i;
            holo::localization::Symbol rpy_symbol;
            rpy_symbol.value_type = holo::localization::ValueType::VECTOR3;
            rpy_symbol.index      = rpy_index;
            holo::localization::Symbol itc_symbol;
            itc_symbol.value_type = holo::localization::ValueType::VECTOR3;
            itc_symbol.index      = itc_index;

            holo::localization::CameraImuExtrinsicCalibFactor camera_imu_extrinsic_calib_factor;
            camera_imu_extrinsic_calib_factor.symbols           = {wTi_symbol, ptw_symbol, rpy_symbol, itc_symbol};
            camera_imu_extrinsic_calib_factor.measurement       = {K, measured};
            camera_imu_extrinsic_calib_factor.covariance_matrix = covariance_matrix;
            camera_imu_extrinsic_calib_factor.fix_wTi           = false;
            camera_imu_extrinsic_calib_factor.fix_ptw           = false;
            camera_imu_extrinsic_calib_factor.fix_roll          = false;
            camera_imu_extrinsic_calib_factor.fix_pitch         = false;
            camera_imu_extrinsic_calib_factor.fix_yaw           = false;
            camera_imu_extrinsic_calib_factor.fix_itc           = false;

            camera_imu_factors.push_back(camera_imu_extrinsic_calib_factor);

            if (!gt_poses.count(j))
            {
                holo::localization::Rot3Type const noise_wRi =
                    holo::localization::Rot3Type::RzRyRx(roll + 0.01 * step, pitch + 0.01 * step, yaw - 0.01 * step);
                holo::localization::Point3Type const noise_wti =
                    wti + holo::localization::Point3Type(0.1 * step, -0.1 * step, 0.2 * step);
                holo::localization::Pose3Type const noise_wTi(noise_wRi, noise_wti);
                noise_poses[j] = noise_wTi;  ///< store noise values as initial values for optimization
                gt_poses[j]    = wTi;        ///< store ground truth
            }
        }
    }

    graph.camera_imu_extrinsic_calib_factors =
        holo::make_optional<holo::localization::CameraImuExtrinsicCalibFactors>(camera_imu_factors);

    // add prior vector3 factors
    {
        holo::localization::Vector3Type sigmas;
        sigmas.SetConstant(1e-3);
        holo::localization::Matrix3Type vector3_covariance = sigmas.CwiseSquare().AsDiagonal();

        holo::localization::Symbol rpy_symbol;
        rpy_symbol.value_type = holo::localization::ValueType::VECTOR3;
        rpy_symbol.index      = rpy_index;
        holo::localization::PriorVector3Factor prior_rpy_factor;
        prior_rpy_factor.symbol            = rpy_symbol;
        prior_rpy_factor.measurement       = rpy;
        prior_rpy_factor.covariance_matrix = vector3_covariance;

        holo::localization::Symbol itc_symbol;
        itc_symbol.value_type = holo::localization::ValueType::VECTOR3;
        itc_symbol.index      = itc_index;
        holo::localization::PriorVector3Factor prior_itc_factor;
        prior_itc_factor.symbol            = itc_symbol;
        prior_itc_factor.measurement       = itc.As<holo::localization::Vector3Type>();
        prior_itc_factor.covariance_matrix = vector3_covariance;

        holo::localization::PriorVector3Factors prior_vector3_factors{prior_rpy_factor, prior_itc_factor};
        graph.prior_vector3_factors =
            holo::make_optional<holo::localization::PriorVector3Factors>(prior_vector3_factors);
    }

    // add prior factor for first pose and between factor for two consecutive pose
    holo::localization::PriorPoseFactors    prior_pose_factors;
    holo::localization::RelativePoseFactors relative_pose_factors;
    for (holo::uint16_t i = 0u; i < num_poses; i++)
    {
        holo::localization::Symbol pose_i_symbol;
        {
            pose_i_symbol.value_type = holo::localization::ValueType::POSE3;
            pose_i_symbol.index      = i;
        }
        holo::localization::Pose3Type const pose_i = gt_poses.at(i);

        if (i == 0u)
        {
            holo::localization::PriorPoseFactor prior_pose_factor;
            prior_pose_factor.symbol      = pose_i_symbol;
            prior_pose_factor.measurement = pose_i;
            holo::localization::Vector6Type sigmas;
            sigmas.SetConstant(1e-6);
            prior_pose_factor.covariance_matrix = sigmas.CwiseSquare().AsDiagonal();
            prior_pose_factors.push_back(prior_pose_factor);
        }
        else
        {
            holo::localization::Symbol pose_i_1_symbol;
            {
                pose_i_1_symbol.value_type = holo::localization::ValueType::POSE3;
                pose_i_1_symbol.index      = i - 1u;
            }
            holo::localization::Pose3Type const    pose_i_1 = gt_poses.at(i - 1u);
            holo::localization::RelativePoseFactor rel_pose_factor;
            rel_pose_factor.symbols     = {pose_i_1_symbol, pose_i_symbol};
            rel_pose_factor.measurement = pose_i_1.Inverse() * pose_i;
            holo::localization::Vector6Type sigmas;
            sigmas.SetConstant(1e-3);
            rel_pose_factor.covariance_matrix = sigmas.CwiseSquare().AsDiagonal();
            relative_pose_factors.push_back(rel_pose_factor);
        }
    }
    graph.prior_pose_factors    = holo::make_optional<holo::localization::PriorPoseFactors>(prior_pose_factors);
    graph.relative_pose_factors = holo::make_optional<holo::localization::RelativePoseFactors>(relative_pose_factors);

    // generate noisy initial values for rpy, itc, pt3_ws and poses
    holo::localization::Scalar const      delta_roll  = 0.1;
    holo::localization::Scalar const      delta_pitch = 0.1;
    holo::localization::Scalar const      delta_yaw   = 0.1;
    holo::localization::Vector3Type const noise_rpy =
        holo::localization::Vector3Type(roll + delta_roll, pitch + delta_pitch, yaw + delta_yaw);
    holo::localization::Vector3Type const noise_itc =
        itc.As<holo::localization::Vector3Type>() + holo::localization::Vector3Type(0.2, 0.2, 0.2);
    holo::localization::Vector3Value      rpy_value;
    rpy_value.symbol.value_type = holo::localization::ValueType::VECTOR3;
    rpy_value.symbol.index      = rpy_index;
    rpy_value.timestamp         = holo::Timestamp(0u, 0u);
    // rpy_value.state             = rpy;
    rpy_value.state = noise_rpy;
    holo::localization::Vector3Value itc_value;
    itc_value.symbol.value_type = holo::localization::ValueType::VECTOR3;
    itc_value.symbol.index      = itc_index;
    itc_value.timestamp         = holo::Timestamp(0u, 0u);
    //  itc_value.state             = itc.ToVector();
    itc_value.state = noise_itc;
    holo::localization::Vector3Values const vector3_values{rpy_value, itc_value};

    holo::localization::Position3Values position_values;
    for (holo::uint16_t i = 0u; i < gt_pt3_ws.size(); i++)
    {
        holo::localization::Position3Value position_value;
        position_value.symbol.value_type = holo::localization::ValueType::POSITION3;
        position_value.symbol.index      = i;
        position_value.timestamp         = holo::Timestamp(0u, 0u);
        holo::localization::Point3Type const noise_pt3_w =
            gt_pt3_ws.at(i) + holo::localization::Point3Type(0.2 * i, -0.2 * i, 0.8 * i);
        // position_value.state = gt_pt3_ws.at(i);
        position_value.state = noise_pt3_w;
        position_values.push_back(position_value);
    }

    holo::localization::Pose3Values pose_values;
    for (holo::uint16_t i = 0u; i < noise_poses.size(); i++)
    {
        holo::localization::Pose3Value pose_value;
        pose_value.symbol.value_type = holo::localization::ValueType::POSE3;
        pose_value.symbol.index      = i;
        pose_value.timestamp         = holo::Timestamp(0u, 0u);
        // pose_value.state             = gt_poses.at(i);
        pose_value.state = noise_poses.at(i);
        pose_values.push_back(pose_value);
    }

    graph.vector3_values  = holo::make_optional<holo::localization::Vector3Values>(vector3_values);
    graph.position_values = holo::make_optional<holo::localization::Position3Values>(position_values);
    graph.pose_values     = holo::make_optional<holo::localization::Pose3Values>(pose_values);

    holo::bool_t get_all_values[2]{true, false};

    for (uint16_t i = 0u; i < 2u; i++)
    {
        /// @brief optimize
        holo::localization::SmootherParameters smoother_params;
        smoother_params.get_all_values        = get_all_values[i];
        smoother_params.additional_iterations = 10u;
        smoother_params.optimizer_type        = holo::localization::SmootherParameters::OptimizerType::DOGLEG;
        smoother_params.relinearize_threshold = 1e-9;
        smoother_params.relinearize_skip      = 1u;

        holo::localization::Smoother                             smoother(smoother_params);
        holo::OptionalT<holo::localization::SmootherState> const state = smoother.Run(graph);

        // check results
        ASSERT_TRUE(state);
        ASSERT_EQ(2u, state->factor_graph.vector3_values->size());
        ASSERT_EQ(gt_pt3_ws.size(), state->factor_graph.position_values->size());
        ASSERT_EQ(num_poses, state->factor_graph.pose_values->size());

        holo::localization::Vector3Values const& optimized_vector3_values =
            state->factor_graph.vector3_values.GetData();
        for (holo::uint16_t i = 0u; i < optimized_vector3_values.size(); i++)
        {
            holo::localization::Vector3Value const& optimized_vector3_value = optimized_vector3_values.at(i);

            if (optimized_vector3_value.symbol.index == rpy_index)
            {
                ASSERT_TRUE(rpy.IsApprox(optimized_vector3_value.state, 1e-5))
                    << rpy << ", " << optimized_vector3_value.state;  ///< 5e-4 degree
            }
            else if (optimized_vector3_value.symbol.index == itc_index)
            {
                ASSERT_TRUE(itc.As<holo::localization::Vector3Type>().IsApprox(optimized_vector3_value.state, 1e-5))
                    << itc << ", " << optimized_vector3_value.state;
            }
            else
            {
                ASSERT_TRUE(false);
            }
        }

        holo::localization::Position3Values const& optimized_position_values =
            state->factor_graph.position_values.GetData();
        for (holo::uint16_t i = 0u; i < gt_pt3_ws.size(); i++)
        {
            holo::localization::Position3Value const& optimized_position_value = optimized_position_values.at(i);
            ASSERT_TRUE(gt_pt3_ws.at(optimized_position_value.symbol.index).IsEqual(optimized_position_value.state))
                << "index: " << i << ", gt: " << gt_pt3_ws.at(optimized_position_value.symbol.index)
                << ", est: " << optimized_position_value.state;
        }

        holo::localization::Pose3Values const& optimized_pose_values = state->factor_graph.pose_values.GetData();
        for (holo::uint16_t i = 0u; i < num_poses; i++)
        {
            holo::localization::Pose3Value const& optimized_pose_value = optimized_pose_values.at(i);
            holo::localization::Pose3Type const&  gt_pose              = gt_poses.at(optimized_pose_value.symbol.index);
            holo::localization::Pose3Type const&  optimized_pose       = optimized_pose_value.state;
            ASSERT_TRUE(gt_pose.IsEqual(optimized_pose)) << "gt pose: " << gt_pose << ", est pose: " << optimized_pose;
        }

        // test getCovariance
        for (const auto symbol : camera_imu_factors.at(0u).symbols)
        {
            auto cov = smoother.GetMarginalCovariance(symbol);
            ASSERT_NE(cov.GetRows(), 0u);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Smoother, lane_factor_type_body)
{
    /* groundtruth */
    /// rotation of body frame in world frame
    const holo::localization::Rot3Type wRb = holo::localization::Rot3Type::Rz(holo::geometry::Radian(85.0));

    /// translation of body frame in world frame
    const holo::localization::Point3Type wtb = holo::localization::Point3Type(5.0, 0.0, 0.0);

    /// body pose in world frame
    const holo::localization::Pose3Type wTb = holo::localization::Pose3Type(wRb, wtb);

    /// pose index
    const holo::uint64_t pose_index = 0u;

    /// create factor graph and symbols
    const holo::localization::Scalar sigma = 0.1;
    FactorGraph                      graph;

    // create prior pose factor
    {
        const holo::localization::Rot3Type prior_wRb = holo::localization::Rot3Type::Rz(holo::geometry::Radian(85.0));

        /// translation of body frame in world frame
        const holo::localization::Point3Type prior_wtb = holo::localization::Point3Type(5.0, 0.1, 0.0);

        /// body pose in world frame
        const holo::localization::Pose3Type prior_wTb = holo::localization::Pose3Type(prior_wRb, prior_wtb);

        // initialize symbol
        holo::localization::Symbol symbol;
        {
            symbol.value_type = holo::localization::ValueType::POSE3;
            symbol.index      = pose_index;
        }

        // initialize factor
        holo::localization::PriorPoseFactor factor;
        {
            factor.symbol      = symbol;
            factor.measurement = prior_wTb;

            holo::localization::Vector6Type sigmas;
            sigmas(0) = 0.1;
            sigmas(1) = 0.1;
            sigmas(2) = 0.1;
            sigmas(3) = 1e-3;
            sigmas(4) = 1e-3;
            sigmas(5) = 1e-3;

            holo::localization::Matrix6Type prior_pose_covariance = sigmas.CwiseSquare().AsDiagonal();
            factor.covariance_matrix                              = prior_pose_covariance;
        }

        // initialize pose value
        holo::localization::Pose3Value value;
        {
            value.symbol    = symbol;
            value.timestamp = holo::Timestamp(1.0);
            value.state     = prior_wTb;
        }

        // add to graph
        graph.prior_pose_factors =
            holo::make_optional<holo::localization::PriorPoseFactors>(holo::localization::PriorPoseFactors{factor});
        graph.pose_values =
            holo::make_optional<holo::localization::Pose3Values>(holo::localization::Pose3Values{value});
    }

    // create lane factor
    {
        holo::localization::LaneFactor factor;
        holo::localization::Symbol     symbol;
        symbol.value_type = holo::localization::ValueType::POSE3;
        symbol.index      = pose_index;
        factor.symbol     = symbol;

        holo::localization::LaneCorrespondences lane_correspondences;
        lane_correspondences.timestamp = holo::Timestamp(1.0);
        lane_correspondences.line      = holo::Line2d(holo::localization::Vector3Type(0.0, 1.0, -3.0));

        std::vector<holo::localization::Point3Type> map_points;
        std::vector<holo::localization::Scalar>     sigmas;
        map_points.push_back(holo::localization::Point3Type(5.0, 3.1, 0.0));
        sigmas.push_back(sigma);

        lane_correspondences.points = map_points;
        lane_correspondences.sigmas = sigmas;
        lane_correspondences.type   = holo::localization::LaneCorrespondences::Type::PROJECT_TO_BODY;
        factor.measurement          = lane_correspondences;

        std::vector<holo::localization::Scalar> covariances;
        covariances.push_back(sigma * sigma);
        factor.covariance_matrix = covariances;

        // add lane factor to graph
        graph.lane_factors =
            holo::make_optional<holo::localization::LaneFactors>(holo::localization::LaneFactors({factor}));
    }

    holo::localization::SmootherParameters smoother_params;
    smoother_params.get_all_values                  = true;
    smoother_params.enable_factor_error_computation = true;

    holo::localization::Smoother                             smoother(smoother_params);
    const holo::OptionalT<holo::localization::SmootherState> state = smoother.Run(graph);

    ASSERT_TRUE(state);
    ASSERT_EQ(1u, graph.prior_pose_factors.GetData().size());
    ASSERT_EQ(1u, graph.lane_factors.GetData().size());
    ASSERT_TRUE(state->factor_graph.pose_values);
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.pose_values->size()));
    ASSERT_NEAR(wTb.GetY(), state->factor_graph.pose_values->at(0u).state.GetY(), 0.1);
    ASSERT_NEAR(holo::geometry::Degree(wTb.GetRotation().RPY()(2)),
                holo::geometry::Degree(state->factor_graph.pose_values->at(0u).state.GetRotation().RPY()(2)), 0.5);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Smoother, lane_factor_type_world)
{
    /* groundtruth */
    /// rotation of body frame in world frame
    const holo::localization::Rot3Type wRb = holo::localization::Rot3Type::Rz(holo::geometry::Radian(85.0));

    /// translation of body frame in world frame
    const holo::localization::Point3Type wtb = holo::localization::Point3Type(5.0, 0.0, 0.0);

    /// body pose in world frame
    const holo::localization::Pose3Type wTb = holo::localization::Pose3Type(wRb, wtb);

    /// pose index
    const holo::uint64_t pose_index = 0u;

    /// create factor graph and symbols
    const holo::localization::Scalar sigma = 0.1;
    FactorGraph                      graph;

    // create prior pose factor
    {
        const holo::localization::Rot3Type prior_wRb = holo::localization::Rot3Type::Rz(holo::geometry::Radian(85.0));

        /// translation of body frame in world frame
        const holo::localization::Point3Type prior_wtb = holo::localization::Point3Type(5.0, 0.1, 0.0);

        /// body pose in world frame
        const holo::localization::Pose3Type prior_wTb = holo::localization::Pose3Type(prior_wRb, prior_wtb);

        // initialize symbol
        holo::localization::Symbol symbol;
        {
            symbol.value_type = holo::localization::ValueType::POSE3;
            symbol.index      = pose_index;
        }

        // initialize factor
        holo::localization::PriorPoseFactor factor;
        {
            factor.symbol      = symbol;
            factor.measurement = prior_wTb;

            holo::localization::Vector6Type sigmas;
            sigmas(0) = 0.1;
            sigmas(1) = 0.1;
            sigmas(2) = 0.1;
            sigmas(3) = 1e-3;
            sigmas(4) = 1e-3;
            sigmas(5) = 1e-3;

            holo::localization::Matrix6Type prior_pose_covariance = sigmas.CwiseSquare().AsDiagonal();
            factor.covariance_matrix                              = prior_pose_covariance;
        }

        // initialize pose value
        holo::localization::Pose3Value value;
        {
            value.symbol    = symbol;
            value.timestamp = holo::Timestamp(1.0);
            value.state     = prior_wTb;
        }

        // add to graph
        graph.prior_pose_factors =
            holo::make_optional<holo::localization::PriorPoseFactors>(holo::localization::PriorPoseFactors{factor});
        graph.pose_values =
            holo::make_optional<holo::localization::Pose3Values>(holo::localization::Pose3Values{value});
    }

    // create lane factor
    {
        holo::localization::LaneFactor factor;
        holo::localization::Symbol     symbol;
        symbol.value_type = holo::localization::ValueType::POSE3;
        symbol.index      = pose_index;
        factor.symbol     = symbol;

        holo::localization::LaneCorrespondences lane_correspondences;
        lane_correspondences.timestamp = holo::Timestamp(1.0);
        lane_correspondences.line      = holo::Line2d(holo::localization::Vector3Type(0.0, 1.0, -3.0));
        lane_correspondences.type      = holo::localization::LaneCorrespondences::Type::PROJECT_TO_WORLD;

        std::vector<holo::localization::Point3Type> points_body;
        std::vector<holo::localization::Scalar>     sigmas;
        holo::geometry::Point3 point_body = wTb.TransformTo(holo::localization::Point3Type(5.0, 3.1, 0.0));
        points_body.push_back(point_body);
        sigmas.push_back(sigma);

        lane_correspondences.points = points_body;
        lane_correspondences.sigmas = sigmas;
        factor.measurement          = lane_correspondences;

        std::vector<holo::localization::Scalar> covariances;
        covariances.push_back(sigma * sigma);
        factor.covariance_matrix = covariances;

        // add lane factor to graph
        graph.lane_factors =
            holo::make_optional<holo::localization::LaneFactors>(holo::localization::LaneFactors({factor}));
    }

    holo::localization::SmootherParameters smoother_params;
    smoother_params.get_all_values                  = true;
    smoother_params.enable_factor_error_computation = true;

    holo::localization::Smoother                             smoother(smoother_params);
    const holo::OptionalT<holo::localization::SmootherState> state = smoother.Run(graph);

    ASSERT_TRUE(state);
    ASSERT_EQ(1u, graph.prior_pose_factors.GetData().size());
    ASSERT_EQ(1u, graph.lane_factors.GetData().size());
    ASSERT_TRUE(state->factor_graph.pose_values);
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.pose_values->size()));
    ASSERT_NEAR(wTb.GetY(), state->factor_graph.pose_values->at(0u).state.GetY(), 0.1);
    ASSERT_NEAR(holo::geometry::Degree(wTb.GetRotation().RPY()(2)),
                holo::geometry::Degree(state->factor_graph.pose_values->at(0u).state.GetRotation().RPY()(2)), 0.5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ImuBodyExtrinsicCalibFixture : public ::testing::Test
{
public:
    using Timestamp = holo::common::Timestamp;
    using Duration  = holo::common::Duration;

    using Scalar      = holo::localization::Scalar;
    using Matrix3Type = holo::localization::Matrix3Type;
    using Point3Type  = holo::localization::Point3Type;
    using Pose3Type   = holo::localization::Pose3Type;
    using Rot3Type    = holo::localization::Rot3Type;
    using Vector3Type = holo::localization::Vector3Type;
    using Navstate    = holo::localization::Navstate;

    using WheelPreintegrationMeasurement = holo::localization::WheelPreintegrationMeasurement;
    using WheelPreintegrationParams      = WheelPreintegrationMeasurement::WheelPreintegrationParams;

    /**
     * @brief Construct a new Imu Body Fixture object
     *
     */
    ImuBodyExtrinsicCalibFixture()
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
    virtual ~ImuBodyExtrinsicCalibFixture()
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
     * @brief give timestamp generate navstate(body pose and velocity in body frame)
     *
     * @param stamp timestamp
     * @return Navstate
     */
    Navstate GenerateNavstate(holo::Timestamp const& stamp) const
    {
        Scalar const    t    = stamp.ToSec();
        Pose3Type const pose = Pose3Type(Rot3Type::Rz(holo::geometry::Radian(90.0) + omega_z_ * t),
                                         Point3Type(origin_.GetX() + radius_ * std::cos(omega_z_ * t),
                                                    origin_.GetY() + radius_ * std::sin(omega_z_ * t), 0.0));

        // generate velocity in body frame
        Vector3Type const velocity_body = Vector3Type(omega_z_ * radius_, 0.0, 0.0);

        return Navstate(pose, velocity_body);
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
    WheelPreintegrationMeasurement ComputeNewPwm(holo::Timestamp const& start_t, Timestamp const& end_t,
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
};  // class ImuBodyExtrinsicCalibFixture

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ImuBodyExtrinsicCalibFixture, imu_body_extrinsic_calib_factor)
{
    // get ground truth iTb
    Pose3Type const   iTb = GetGroundTruthiTb();
    Vector3Type const rpy = iTb.GetRotation().RPY();

    // construct factor graph
    holo::uint16_t                                   num_poses = 4u;
    FactorGraph                                      graph;
    holo::localization::ImuBodyExtrinsicCalibFactors imu_body_factors;
    std::unordered_map<holo::uint16_t, Pose3Type>    gt_poses;
    std::unordered_map<holo::uint16_t, Pose3Type>    noise_poses;

    // start timestamp
    Timestamp const      t(0u, 0u);
    Duration const       seg       = GetPoseDuration();
    holo::uint64_t const iRb_index = 1u;

    for (holo::uint16_t i = 0u; i < num_poses; i++)
    {
        Duration const dur(seg * Scalar(i));

        Timestamp const start_t = t + dur;
        Timestamp const end_t   = start_t + seg;

        Pose3Type                      wTi1;
        WheelPreintegrationMeasurement new_pwm;
        std::tie(wTi1, new_pwm) = GetImuPoseAndPwm(start_t, end_t);

        // symbols
        holo::localization::Symbol wTi1_symbol;
        wTi1_symbol.value_type = holo::localization::ValueType::POSE3;
        wTi1_symbol.index      = i;

        holo::localization::Symbol wTi2_symbol;
        wTi2_symbol.value_type = holo::localization::ValueType::POSE3;
        wTi2_symbol.index      = i + 1;

        holo::localization::Symbol iRb_symbol;
        iRb_symbol.value_type = holo::localization::ValueType::ROT3;
        iRb_symbol.index      = iRb_index;

        // create imu body extrinsic factors
        if (i < num_poses - 1u)
        {
            holo::localization::ImuBodyExtrinsicCalibFactor imu_body_extrinsic_calib_factor;
            imu_body_extrinsic_calib_factor.symbols           = {wTi1_symbol, wTi2_symbol, iRb_symbol};
            imu_body_extrinsic_calib_factor.measurement       = new_pwm;
            imu_body_extrinsic_calib_factor.covariance_matrix = new_pwm.GetPreintegratedMeasurementCovariance();
            imu_body_factors.push_back(imu_body_extrinsic_calib_factor);
        }

        if (!gt_poses.count(i))
        {
            Vector3Type      imu_rpy   = wTi1.GetRotation().RPY();
            Point3Type       wti       = wTi1.GetTranslation();
            Rot3Type const   noise_wRi = Rot3Type::RzRyRx(imu_rpy(0u) + 0.01, imu_rpy(1u) + 0.01, imu_rpy(2u) - 0.01);
            Point3Type const noise_wti = wti + Point3Type(0.1, 0.1, 0.2);
            Pose3Type const  noise_wTi(noise_wRi, noise_wti);
            noise_poses[i] = noise_wTi;  ///< store noise values as initial values for optimization
            gt_poses[i]    = wTi1;       ///< store ground truth
        }
    }

    graph.imu_body_extrinsic_calib_factors =
        holo::make_optional<holo::localization::ImuBodyExtrinsicCalibFactors>(imu_body_factors);

    // add prior rot3 factors
    {
        Vector3Type sigmas;
        sigmas.SetConstant(1);
        Matrix3Type rot3_covariance = sigmas.CwiseSquare().AsDiagonal();

        holo::localization::Symbol iRb_symbol;
        iRb_symbol.value_type = holo::localization::ValueType::ROT3;
        iRb_symbol.index      = iRb_index;
        holo::localization::PriorRot3Factor prior_iRb_factor;
        prior_iRb_factor.symbol            = iRb_symbol;
        prior_iRb_factor.measurement       = iTb.GetRotation();
        prior_iRb_factor.covariance_matrix = rot3_covariance;

        holo::localization::PriorRot3Factors prior_rot3_factors{prior_iRb_factor};
        graph.prior_rot3_factors = holo::make_optional<holo::localization::PriorRot3Factors>(prior_rot3_factors);
    }

    // add prior factor for first pose and between factor for two consecutive pose
    holo::localization::PriorPoseFactors    prior_pose_factors;
    holo::localization::RelativePoseFactors relative_pose_factors;
    for (holo::uint16_t i = 0u; i < num_poses; i++)
    {
        holo::localization::Symbol pose_i_symbol;
        {
            pose_i_symbol.value_type = holo::localization::ValueType::POSE3;
            pose_i_symbol.index      = i;
        }
        Pose3Type const pose_i = gt_poses.at(i);

        if (i == 0u)
        {
            holo::localization::PriorPoseFactor prior_pose_factor;
            prior_pose_factor.symbol      = pose_i_symbol;
            prior_pose_factor.measurement = pose_i;
            holo::localization::Vector6Type sigmas;
            sigmas.SetConstant(1e-6);
            prior_pose_factor.covariance_matrix = sigmas.CwiseSquare().AsDiagonal();
            prior_pose_factors.push_back(prior_pose_factor);
        }
        else
        {
            holo::localization::Symbol pose_i_1_symbol;
            {
                pose_i_1_symbol.value_type = holo::localization::ValueType::POSE3;
                pose_i_1_symbol.index      = i - 1u;
            }
            Pose3Type const                        pose_i_1 = gt_poses.at(i - 1u);
            holo::localization::RelativePoseFactor rel_pose_factor;
            rel_pose_factor.symbols     = {pose_i_1_symbol, pose_i_symbol};
            rel_pose_factor.measurement = pose_i_1.Inverse() * pose_i;
            holo::localization::Vector6Type sigmas;
            sigmas.SetConstant(1e-5);
            rel_pose_factor.covariance_matrix = sigmas.CwiseSquare().AsDiagonal();
            relative_pose_factors.push_back(rel_pose_factor);
        }
    }
    graph.prior_pose_factors    = holo::make_optional<holo::localization::PriorPoseFactors>(prior_pose_factors);
    graph.relative_pose_factors = holo::make_optional<holo::localization::RelativePoseFactors>(relative_pose_factors);

    // generate noisy initial values for iRb and poses
    Scalar const   delta_roll  = 0.0;
    Scalar const   delta_pitch = 0.2;
    Scalar const   delta_yaw   = 0.2;
    Rot3Type const noise_iRb =
        Rot3Type::RzRyRx(rpy.At(0u) + delta_roll, rpy.At(1u) + delta_pitch, rpy.At(2u) + delta_yaw);

    holo::localization::Rot3Value iRb_value;
    iRb_value.symbol.value_type = holo::localization::ValueType::ROT3;
    iRb_value.symbol.index      = iRb_index;
    iRb_value.timestamp         = holo::Timestamp(0u, 0u);
    iRb_value.state             = noise_iRb;

    holo::localization::Pose3Values pose_values;
    for (holo::uint16_t i = 0u; i < noise_poses.size(); i++)
    {
        holo::localization::Pose3Value pose_value;
        pose_value.symbol.value_type = holo::localization::ValueType::POSE3;
        pose_value.symbol.index      = i;
        pose_value.timestamp         = holo::Timestamp(0u, 0u);
        pose_value.state             = noise_poses.at(i);
        pose_values.push_back(pose_value);
    }

    graph.rot3_values = holo::make_optional<holo::localization::Rot3Values>(holo::localization::Rot3Values{iRb_value});
    graph.pose_values = holo::make_optional<holo::localization::Pose3Values>(pose_values);

    holo::bool_t get_all_values[2]{true, false};

    for (uint16_t i = 0u; i < 2u; i++)
    {
        /// @brief optimize
        holo::localization::SmootherParameters smoother_params;
        smoother_params.get_all_values        = get_all_values[i];
        smoother_params.additional_iterations = 10u;
        smoother_params.optimizer_type        = holo::localization::SmootherParameters::OptimizerType::DOGLEG;
        smoother_params.relinearize_threshold = 1e-9;
        smoother_params.relinearize_skip      = 1u;

        holo::localization::Smoother                             smoother(smoother_params);
        holo::OptionalT<holo::localization::SmootherState> const state = smoother.Run(graph);

        // check results
        ASSERT_TRUE(state);
        ASSERT_EQ(1u, state->factor_graph.rot3_values->size());
        ASSERT_EQ(num_poses, state->factor_graph.pose_values->size());

        holo::localization::Rot3Values const& optimized_rot3_values = state->factor_graph.rot3_values.GetData();
        holo::localization::Rot3Value const&  optimized_rot3_value  = optimized_rot3_values.at(0);

        ASSERT_NEAR(rpy(0u), optimized_rot3_value.state.RPY()(0u), 1e-5)
            << "gt roll: " << rpy(0u)
            << "\n est roll: " << optimized_rot3_value.state.RPY()(0u);  // roll has no constraints
        ASSERT_NEAR(rpy(1u), optimized_rot3_value.state.RPY()(1u), 1e-5)
            << "gt pitch: " << rpy(1u) << "\n est pitch: " << optimized_rot3_value.state.RPY()(1u);
        ASSERT_NEAR(rpy(2u), optimized_rot3_value.state.RPY()(2u), 1e-5)
            << "gt yaw: " << rpy(2u) << "\n est yaw: " << optimized_rot3_value.state.RPY()(2u);

        holo::localization::Pose3Values const& optimized_pose_values = state->factor_graph.pose_values.GetData();
        for (holo::uint16_t i = 0u; i < num_poses; i++)
        {
            holo::localization::Pose3Value const& optimized_pose_value = optimized_pose_values.at(i);
            Pose3Type const&                      gt_pose              = gt_poses.at(optimized_pose_value.symbol.index);
            Pose3Type const&                      optimized_pose       = optimized_pose_value.state;
            ASSERT_TRUE(gt_pose.IsEqual(optimized_pose, 1e-5))
                << "gt pose: " << gt_pose << ", est pose: " << optimized_pose;
        }

        // test getCovariance
        for (const auto symbol : imu_body_factors.at(0u).symbols)
        {
            auto cov = smoother.GetMarginalCovariance(symbol);
            ASSERT_NE(cov.GetRows(), 0u);
        }
    }

    // test imu_body_extrinsic_calib_factor's symbols is empty case
    for (auto& factor : graph.imu_body_extrinsic_calib_factors.GetData())
    {
        factor.symbols.clear();
    }

    for (auto& factor : graph.relative_pose_factors.GetData())
    {
        factor.symbols.clear();
    }

    holo::localization::SmootherParameters smoother_parameters;
    smoother_parameters.get_all_values        = true;
    smoother_parameters.additional_iterations = 10u;
    smoother_parameters.optimizer_type        = holo::localization::SmootherParameters::OptimizerType::DOGLEG;
    smoother_parameters.relinearize_threshold = 1e-9;
    smoother_parameters.relinearize_skip      = 1u;

    holo::localization::Smoother smoother1(smoother_parameters);
    ASSERT_THROW(smoother1.Run(graph), std::exception);
}

TEST(smoother, prior_rpy_factor)
{
    // 1. prepare symbol
    holo::uint64_t             pose_index = 1u;
    holo::localization::Symbol pose_symbol;
    {
        pose_symbol.value_type = holo::localization::ValueType::POSE3;
        pose_symbol.index      = pose_index;
    }

    // 2. prepare factor graph
    holo::localization::FactorGraph       graph;
    holo::localization::Matrix3Type const covariance_matrix =
        holo::localization::Vector3Type(1e-3, 1e-3, 1e-3).CwiseSquare().AsDiagonal();

    /** roll, pitch factor which constrains roll and pitch **/
    holo::localization::PriorRPYFactor prior_rpy_factor1;
    {
        prior_rpy_factor1.symbol            = pose_symbol;
        prior_rpy_factor1.measurement       = holo::localization::Vector3Type(0.1, 0.2, 0.3);
        prior_rpy_factor1.covariance_matrix = covariance_matrix;
        prior_rpy_factor1.fix_roll          = false;
        prior_rpy_factor1.fix_pitch         = false;
        prior_rpy_factor1.fix_yaw           = true;
    }

    /** yaw factor which constrains yaw **/
    holo::localization::PriorRPYFactor prior_rpy_factor2;
    {
        prior_rpy_factor2.symbol            = pose_symbol;
        prior_rpy_factor2.measurement       = holo::localization::Vector3Type(0.7, 0.8, 0.9);
        prior_rpy_factor2.covariance_matrix = covariance_matrix;
        prior_rpy_factor2.fix_roll          = true;
        prior_rpy_factor2.fix_pitch         = true;
        prior_rpy_factor2.fix_yaw           = false;
    }

    /** prior pose factor which constrains translation **/
    holo::localization::PriorPoseFactor prior_pose_factor;
    {
        prior_pose_factor.symbol      = pose_symbol;
        prior_pose_factor.measurement = holo::localization::Pose3Type(
            holo::localization::Rot3Type::RzRyRx(holo::geometry::Radian(0.0), holo::geometry::Radian(0.0),
                                                 holo::geometry::Radian(0.0)),
            holo::localization::Point3Type(0.1, 0.3, 0.5));
        prior_pose_factor.covariance_matrix =
            holo::localization::Vector6Type(1e-3, 1e-3, 1e-3, 1e7, 1e7, 1e7).CwiseSquare().AsDiagonal();
    }

    graph.prior_rpy_factors =
        holo::OptionalT<holo::localization::PriorRPYFactors>({prior_rpy_factor1, prior_rpy_factor2});
    graph.prior_pose_factors = holo::OptionalT<holo::localization::PriorPoseFactors>({prior_pose_factor});

    // 3. prepare initial value
    holo::Timestamp                     pose_timestamp(0u, 10u);
    holo::localization::Pose3Type const pose(holo::localization::Rot3Type::RzRyRx(holo::geometry::Radian(0.0),
                                                                                  holo::geometry::Radian(0.0),
                                                                                  holo::geometry::Radian(0.0)),
                                             holo::localization::Point3Type(0.4, 0.5, 0.6));
    holo::localization::Pose3Value pose_value;
    {
        pose_value.symbol    = pose_symbol;
        pose_value.timestamp = pose_timestamp;
        pose_value.state     = pose;
    }

    graph.pose_values = holo::OptionalT<holo::localization::Pose3Values>({pose_value});

    // 4. optimize
    holo::localization::SmootherParameters smoother_params;
    smoother_params.get_all_values        = true;
    smoother_params.additional_iterations = 10u;
    smoother_params.optimizer_type        = holo::localization::SmootherParameters::OptimizerType::DOGLEG;
    smoother_params.relinearize_threshold = 1e-9;
    smoother_params.relinearize_skip      = 1u;

    holo::localization::Smoother                             smoother(smoother_params);
    holo::OptionalT<holo::localization::SmootherState> const state = smoother.Run(graph);

    // check results
    ASSERT_TRUE(state);
    ASSERT_EQ(1u, state->factor_graph.pose_values->size());
    holo::localization::Pose3Type   est_pose = state->factor_graph.pose_values->at(0u).state;
    holo::localization::Vector3Type est_rpy  = est_pose.GetRotation().RPY();
    ASSERT_NEAR(est_rpy(0u), prior_rpy_factor1.measurement(0u), holo::geometry::Radian(0.001));
    ASSERT_NEAR(est_rpy(1u), prior_rpy_factor1.measurement(1u), holo::geometry::Radian(0.001));
    ASSERT_NEAR(est_rpy(2u), prior_rpy_factor2.measurement(2u), holo::geometry::Radian(0.001));
    ASSERT_TRUE(est_pose.GetTranslation().IsEqual(prior_pose_factor.measurement.GetTranslation(), 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Smoother, gnss_position_velocity_factor)
{
    /**
     * @brief for a detail factor test, please check out "factors/test_gnss_position_velocity_factor.cpp"
     *
     */

    using namespace holo::localization;

    /// Step 1: Prepare the input variables

    Rot3Type const    wRb = Rot3Type::RzRyRx(0.1, 0.2, -0.3);
    Point3Type const  wtb(1.0, 1.0, 1.0);
    Pose3Type const   wTb(wRb, wtb);
    Vector3Type const wVb(20.0, 1.0, 0.5);

    // define gnss position velocity factor
    FactorGraph graph;
    uint64_t    index = 1u;
    {
        GnssPositionVelocityFactor factor;

        Symbol symbol;
        symbol.value_type = ValueType::POSE3;
        symbol.index      = index;
        factor.symbols.emplace_back(symbol);  // pose
        symbol.value_type = ValueType::VELOCITY3;
        factor.symbols.emplace_back(symbol);  // velocity

        factor.position = wtb;
        factor.velocity = wVb;
        factor.sigmas   = Vector6Type(1.0, 1.1, 1.2, 0.1, 0.2, 0.3);

        graph.gnss_position_velocity_factors = GnssPositionVelocityFactors({factor});
    }

    // add a prior pose factor, because rotation needs a contraint to avoid indeterminant system error
    {
        // initialize factor
        holo::localization::PriorPoseFactor factor;
        {
            factor.symbol.value_type = ValueType::POSE3;
            factor.symbol.index      = index;
            factor.measurement       = wTb;
            factor.covariance_matrix = Matrix6Type::Identity() * 1e-2;
        }

        // add to graph
        graph.prior_pose_factors = PriorPoseFactors({factor});
    }

    // insert initial values
    {
        Pose3Value pose_value;
        pose_value.symbol.index = index;
        pose_value.state        = Pose3Type(wRb, Point3Type(1.2, 1.1, 1.4));
        graph.pose_values       = Pose3Values({pose_value});

        Velocity3Value velocity_value;
        velocity_value.symbol.index = index;
        velocity_value.state        = Vector3Type(20.5, 1.1, 0.7);
        graph.velocity_values       = Velocity3Values({velocity_value});
    }

    holo::localization::SmootherParameters smoother_params;
    smoother_params.get_all_values                  = true;
    smoother_params.enable_factor_error_computation = true;

    holo::localization::Smoother                             smoother(smoother_params);
    holo::OptionalT<holo::localization::SmootherState> const state = smoother.Run(graph);

    ASSERT_EQ(1u, graph.gnss_position_velocity_factors->size());
    ASSERT_TRUE(state);
    ASSERT_TRUE(state->factor_graph.pose_values);
    ASSERT_TRUE(state->factor_graph.velocity_values);
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.pose_values->size()));
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.velocity_values->size()));
    ASSERT_TRUE(state->factor_graph.pose_values->at(0u).state.IsEqual(wTb, 1e-6));
    ASSERT_TRUE(state->factor_graph.velocity_values->at(0u).state.IsApprox(wVb, 1e-6));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Smoother, gnss_position_velocity_factor_with_pim)
{
    /**
     * @brief for a detail factor test, please check out "factors/test_gnss_position_velocity_factor.cpp"
     *
     */

    using namespace holo::localization;

    /**
     * @brief scenario
     *
     * 1. The vehicle is moving with a constant acceleration of (ax = 1.5, ay = 0.1, az = 0.0)
     * 2. The first state is estimated at time t_k (0.0), next state is estimated at time t_(k+1) (1.0)
     * 3. GPS is measured at time t_j (0.1)
     * 4. PIM is created between time [t_k, t_j] ([0.0, 0.1]) at a frequency of 100hz, i.e. 10 Imus
     */

    /// Step 1: Prepare the input variables

    // first state
    Rot3Type const    wRbk = Rot3Type::RzRyRx(0.1, 0.2, -0.3);
    Point3Type const  wtbk(1.0, 1.0, 1.0);
    Pose3Type const   wTbk(wRbk, wtbk);
    Vector3Type const wVbk(20.0, 1.0, 0.5);

    // define vehicle dynamics
    Vector3Type const acc(0.5, 0.1, 0.0);   // m/s^2
    Vector3Type const gyro(0.0, 0.0, 0.0);  // rad/s
    Scalar const      dt = 0.1;             // s

    // define state when sampled gps measurement at time t_j
    Vector3Type const w_acc = wRbk * acc;
    Rot3Type const    wRbj  = wRbk;  // keep rotation unchanged
    Point3Type const  wtbj  = wtbk + Point3Type(wVbk * dt + w_acc * (0.5 * dt * dt));
    Vector3Type const wVbj  = wVbk + w_acc * dt;

    // now we are good to go, let's define gnss position velocity factor
    FactorGraph graph;
    uint64_t    index = 1u;
    {
        GnssPositionVelocityFactor factor;

        Symbol symbol;
        symbol.value_type = ValueType::POSE3;
        symbol.index      = index;
        factor.symbols.emplace_back(symbol);  // pose
        symbol.value_type = ValueType::VELOCITY3;
        factor.symbols.emplace_back(symbol);  // velocity

        factor.position = wtbj;
        factor.velocity = wVbj;

        ImuPreintegrationMeasurement pim;
        int32_t const                num = int32_t(dt * 100.0);  // hardcode imu frequency
        Vector3Type const            g(0.0, 0.0, 9.81);
        Vector3Type const            acc_m = acc + wRbk.Unrotate(g);  // consider gravity
        for (int32_t i = 0; i < num; i++)
        {
            pim.IntegrateMeasurement(acc_m, gyro, 0.01);  // hardcode imu interval
        }
        factor.pim = pim;

        factor.wRb    = wRbk;
        factor.sigmas = Vector6Type(1.0, 1.1, 1.2, 0.1, 0.2, 0.3);

        graph.gnss_position_velocity_factors = GnssPositionVelocityFactors({factor});
    }

    // add a prior pose factor, because rotation needs a contraint to avoid indeterminant system error
    {
        // initialize factor
        holo::localization::PriorPoseFactor factor;
        {
            factor.symbol.value_type = ValueType::POSE3;
            factor.symbol.index      = index;
            factor.measurement       = wTbk;
            factor.covariance_matrix = Matrix6Type::Identity() * 1e-2;
        }

        // add to graph
        graph.prior_pose_factors = PriorPoseFactors({factor});
    }

    // insert initial values
    {
        Pose3Value pose_value;
        pose_value.symbol.index = index;
        pose_value.state        = Pose3Type(wRbk, Point3Type(1.2, 1.1, 1.4));
        graph.pose_values       = Pose3Values({pose_value});

        Velocity3Value velocity_value;
        velocity_value.symbol.index = index;
        velocity_value.state        = Vector3Type(20.5, 1.1, 0.7);
        graph.velocity_values       = Velocity3Values({velocity_value});
    }

    holo::localization::SmootherParameters smoother_params;
    smoother_params.get_all_values                  = true;
    smoother_params.enable_factor_error_computation = true;

    holo::localization::Smoother                             smoother(smoother_params);
    holo::OptionalT<holo::localization::SmootherState> const state = smoother.Run(graph);

    ASSERT_EQ(1u, graph.gnss_position_velocity_factors->size());
    ASSERT_TRUE(state);
    ASSERT_TRUE(state->factor_graph.pose_values);
    ASSERT_TRUE(state->factor_graph.velocity_values);
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.pose_values->size()));
    ASSERT_EQ(1u, static_cast<uint64_t>(state->factor_graph.velocity_values->size()));
    ASSERT_TRUE(state->factor_graph.pose_values->at(0u).state.IsEqual(wTbk, 1e-6));
    ASSERT_TRUE(state->factor_graph.velocity_values->at(0u).state.IsApprox(wVbk, 1e-6));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
