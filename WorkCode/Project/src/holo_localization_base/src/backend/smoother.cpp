/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file smoother.cpp
 * @brief the implementation of smoother class
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date Dec 04, 2019
 */

#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Key.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/inference/inferenceExceptions.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/navigation/GPSFactor.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/nonlinear/ExpressionFactor.h>
#include <gtsam/nonlinear/LevenbergMarquardtParams.h>
#include <gtsam/nonlinear/Marginals.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/slam/ProjectionFactor.h>
#include <gtsam/slam/expressions.h>
#include <gtsam_unstable/nonlinear/IncrementalFixedLagSmoother.h>

#include <holo/core/exception.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <holo/localization/backend/smoother.h>
#include <holo/localization/sam/factors/internal/camera_imu_extrinsic_factor_inl.h>
#include <holo/localization/sam/factors/internal/gnss_position_velocity_factor_inl.h>
#include <holo/localization/sam/factors/internal/imu_body_extrinsic_factor_inl.h>
#include <holo/localization/sam/factors/internal/lane_factor_inl.h>
#include <holo/localization/sam/factors/internal/prior_rpy_factor_inl.h>
#include <holo/localization/sam/factors/internal/projection_line_factor_inl.h>
#include <holo/localization/sam/factors/internal/velocity_factor_inl.h>
#include <holo/localization/sam/factors/internal/wheel_speed_factor_inl.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
using gtsam::symbol_shorthand::B;  // Bias (ax, ay, az, gx, gy, gz)
using gtsam::symbol_shorthand::E;  // Rot3 for imu-body extrinsic calibration
using gtsam::symbol_shorthand::L;  // Landmark Position (x, y, z)
using gtsam::symbol_shorthand::T;  // Vector3 for extrinsic calibration
using gtsam::symbol_shorthand::V;  // Vel (xdot, ydot, zdot)
using gtsam::symbol_shorthand::X;  // Pose3 (x, y, z, r, p, y)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Implementation class
 *
 */
class Smoother::Implement
{
public:
    /// gtsam interface doesn't support float/double class
    using Factor                       = gtsam::Factor;
    using FixedLagSmoother             = gtsam::FixedLagSmoother;
    using GtsamGnssFactor              = gtsam::GPSFactor;
    using ConstantBias                 = gtsam::imuBias::ConstantBias;
    using GtsamImuFactor               = gtsam::ImuFactor;
    using IncrementalFixedLagSmoother  = gtsam::IncrementalFixedLagSmoother;
    using ISAM2Params                  = gtsam::ISAM2Params;
    using Key                          = gtsam::Key;
    using GTSymbol                     = gtsam::Symbol;
    using GTLMParams                   = gtsam::LevenbergMarquardtParams;
    using GTMatrix3                    = gtsam::Matrix3;
    using Marginals                    = gtsam::Marginals;
    using Diagonal                     = gtsam::noiseModel::Diagonal;
    using Isotropic                    = gtsam::noiseModel::Isotropic;
    using NonlinearFactorGraph         = gtsam::NonlinearFactorGraph;
    using GTPoint2                     = gtsam::Point2;
    using GTPoint3                     = gtsam::Point3;
    using GTPose3                      = gtsam::Pose3;
    using GTRot3                       = gtsam::Rot3;
    using PreintegratedImuMeasurements = gtsam::PreintegratedImuMeasurements;
    using Values                       = gtsam::Values;
    using GTVector3                    = gtsam::Vector3;
    using GTVector6                    = gtsam::Vector6;
    using KeyTimestampMap              = std::map<Key, float64_t>;
    using SmootherMap                  = std::multimap<Key, NonlinearFactorGraph::sharedFactor>;
    using PriorFactorPose3             = gtsam::PriorFactor<GTPose3>;
    using PriorFactorVel3              = gtsam::PriorFactor<GTVector3>;
    using PriorFactorImuBias           = gtsam::PriorFactor<ConstantBias>;
    using PriorFactorVector3           = gtsam::PriorFactor<GTVector3>;
    using PriorFactorRot3              = gtsam::PriorFactor<GTRot3>;
    using BetweenFactorPose3           = gtsam::BetweenFactor<GTPose3>;
    using BetweenFactorVel3            = gtsam::BetweenFactor<GTVector3>;
    using BetweenFactorImuBias         = gtsam::BetweenFactor<ConstantBias>;
    using Gaussian                     = gtsam::noiseModel::Gaussian;
    using Robust                       = gtsam::noiseModel::Robust;
    using Huber                        = gtsam::noiseModel::mEstimator::Huber;
    using GeneralCamera                = gtsam::PinholeCamera<gtsam::Cal3_S2>;
    using GtsamProjectionFactor        = gtsam::GenericProjectionFactor<GTPose3, GTPoint3>;
    /* @todo add lane and velocity factor */
    using GtsamLaneFactor                  = holo::localization::internal::Lane2Factor;
    using GtsamVelocityFactor              = holo::localization::internal::VelocityFactor;
    using GtsamWheelSpeedFactor            = holo::localization::internal::WheelSpeedFactor;
    using GtsamCameraImuExtrinsicFactor    = holo::localization::internal::CameraImuExtrinsicFactor;
    using GtsamProjectionLineFactor        = holo::localization::internal::ProjectionLineFactor;
    using GtsamImuBodyExtrinsicFactor      = holo::localization::internal::ImuBodyExtrinsicFactor;
    using GtsamGnssPositionVelocityFactor  = holo::localization::internal::GnssPositionVelocityFactor;
    using GtsamPriorRPYFactor              = holo::localization::internal::PriorRPYFactor;
    using InconsistentEliminationRequested = gtsam::InconsistentEliminationRequested;

    using SmootherPtr = std::shared_ptr<IncrementalFixedLagSmoother>;

    /**
     * @brief Construct a new Implement object
     *
     * @param params the configuration of implement
     */
    Implement(const Parameters& params = Parameters()) : params_(params)
    {
        ISAM2Params isam_params = createIsam2Parameters();
        isam_params.print("ISAM Parameters: ");

        /* initialize smoother pointer */
        smoother_ = std::make_shared<IncrementalFixedLagSmoother>(params_.lag_size, isam_params);
    }

    /**
     * @brief Destroy the Implement object
     *
     */
    ~Implement()
    {
    }

    /**
     * @brief Add factor graph into smoother.
     *
     * @param factor_graph factor graph which contains factors and values.
     * @return OptionalT<SmootherState> return SmootherState if success, otherwise nonetype.
     */
    OptionalT<SmootherState> Run(const FactorGraph& factor_graph);

    /**
     * @brief reset the states of implement
     */
    void Reset()
    {
        ISAM2Params isam2_params = createIsam2Parameters();
        /* reset smoother */
        smoother_.reset(new IncrementalFixedLagSmoother(params_.lag_size, isam2_params));
    }

    /**
     * @brief Get the Marginal Covariance object
     *
     * @param symbol variable symbol
     * @return MatrixXType
     */
    MatrixXType GetMarginalCovariance(const Symbol& symbol) const
    {
        const gtsam::Symbol s   = convertSymbol(symbol);
        const gtsam::Matrix cov = smoother_->marginalCovariance(s);
        return convertToHoloMatrix(cov);
    }

    /**
     * @brief Get the Marginal Covariance object
     *
     * @param symbols variable symbols vector
     * @return MatrixXType
     */
    MatrixXType GetMarginalCovariance(std::vector<Symbol> const& symbols) const
    {
        // get optimized graph and values
        NonlinearFactorGraph const& graph            = smoother_->getFactors();
        Values const&               estimated_values = smoother_->calculateEstimate();

        Marginals const marginals(graph, estimated_values /*, Factoring, Ordering */);

        gtsam::KeyVector keyvector;
        keyvector.reserve(symbols.size());

        for (auto const& symbol : symbols)
        {
            gtsam::Symbol const s = convertSymbol(symbol);
            keyvector.emplace_back(s);
        }

        return convertToHoloMatrix((marginals.jointMarginalCovariance(keyvector)).fullMatrix());
    }

protected:
    /**
     * @brief Convert holo factor graph to gtsam factor graph
     *
     * @param[in] g factor graph which contains factors and navstates
     * @param[in] factors the gtsam nonlinear factor graph
     * @param[in] values the gtsam values
     * @param[in] stamps the key-timetamp map
     */
    void convertFactorGraph(const FactorGraph& g, NonlinearFactorGraph& factors, Values& values,
                            KeyTimestampMap& stamps);

    /**
     * @brief Optimize the factor graph
     *
     * @param[in] factors the gtsam nonlinear factor graph
     * @param[in] values the gtsam values
     * @param[in] stamps the key-timetamp map
     * @param[in] result the optimized values and optimization informations.
     */
    void optimizeFactorGraph(const NonlinearFactorGraph& factors, const Values& values, const KeyTimestampMap& stamps,
                             SmootherState& result);

    /**
     * @brief Convert prior pose factor
     *
     * @param factor prior pose factor in holo
     * @return OptionalT<PriorFactorPose3> return prior pose factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<PriorFactorPose3> convertPriorPoseFactor(const PriorPoseFactor& factor) const;

    /**
     * @brief Convert prior velocity factor
     *
     * @param factor prior velocity factor in holo
     * @return OptionalT<PriorFactorVel3> return prior velocity factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<PriorFactorVel3> convertPriorVelocityFactor(const PriorVelocityFactor& factor) const;

    /**
     * @brief Convert prior imu bias factor
     *
     * @param factor prior imu bias factor in holo
     * @return OptionalT<PriorFactorImuBias> return prior imu bias factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<PriorFactorImuBias> convertPriorImuBiasFactor(const PriorImuBiasFactor& factor) const;

    /**
     * @brief Convert piror vector3 factor
     *
     * @param[in] factor vector3 factor in holo
     * @return OptionalT<PriorFactotVector3> return prior factor vector3 in gtsam if success, otherwise nonetype.
     */
    OptionalT<PriorFactorVector3> convertPriorVector3Factor(const PriorVector3Factor& factor) const;

    /**
     * @brief Convert piror rot3 factor
     *
     * @param[in] factor rot3 factor in holo
     * @return OptionalT<PriorFactotRot3> return prior factor rot3 in gtsam if success, otherwise nonetype.
     */
    OptionalT<PriorFactorRot3> convertPriorRot3Factor(const PriorRot3Factor& factor) const;

    /**
     * @brief Convert gnss factor
     *
     * @param factor gnss factor in holo
     * @return OptionalT<GtsamGnssFactor> return gnss factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<GtsamGnssFactor> convertGnssFactor(const GnssFactor& factor) const;

    /**
     * @brief Convert imu factor
     *
     * @param factor imu factor in holo
     * @return OptionalT<GtsamImuFactor> return imu factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<GtsamImuFactor> convertImuFactor(const ImuFactor& factor) const;

    /**
     * @brief Convert imu bias factor
     *
     * @param factor imu bias factor
     * @return OptionalT<BetweenFactorImuBias> return imu bias factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<BetweenFactorImuBias> convertImuBiasFactor(const ImuBiasFactor& factor) const;

    /**
     * @brief Convert relative pose factor
     *
     * @param factor relative pose factor in holo
     * @return OptionalT<BetweenFactorPose3> return relative pose factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<BetweenFactorPose3> convertRelativePoseFactor(const RelativePoseFactor& factor) const;

    /**
     * @brief Convert relative velocity factor
     *
     * @param factor relative velocity factor in holo
     * @return OptionalT<BetweenFactorVel3> return relative velocity factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<BetweenFactorVel3> convertRelativeVelocityFactor(const RelativeVelocityFactor& factor) const;

    /**
     * @brief Convert lane factor
     *
     * @param factor lane factor in holo
     * @return OptionalT<GtsamLaneFactor> return lane factor in gtsam if suceess, otherwise nonetype.
     */
    OptionalT<std::vector<Smoother::Implement::GtsamLaneFactor>> convertLaneFactor(const LaneFactor& factor) const;

    /**
     * @brief add sign factor to factor graph
     *
     * @param factor sign factor in holo
     * @param factor_graph factor graph
     */
    void addSignFactor(const SignFactor& factor, NonlinearFactorGraph& factor_graph) const;

    /**
     * @brief COnvert projection factor
     *
     * @param factor projection factor in holo
     * @param stamps key timestamp map
     * @return OptionalT<GtsamProjectionFactor> return projection factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<GtsamProjectionFactor> convertProjectionFactor(const ProjectionFactor& factor,
                                                             KeyTimestampMap&        stamps) const;

    /**
     * @brief Convert velocity factor
     *
     * @param factor velocity factor in holo
     * @return OptionalT<GtsamVelocityFactor> return velocity factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<GtsamVelocityFactor> convertVelocityFactor(const VelocityFactor& factor) const;

    /**
     * @brief Convert wheel speed factor
     *
     * @param factor wheel speed factor in holo
     * @return OptionalT<GtsamWheelSpeedFactor> return wheel speed factor in gtsam if success, otherwise nonetype.
     */
    OptionalT<GtsamWheelSpeedFactor> convertWheelSpeedFactor(const WheelSpeedFactor& factor) const;

    /**
     * @brief Convert camera imu extrinsic factor
     *
     * @param[in] factor camera imu extrinsic in holo
     * @param[in] key timestamp map
     * @return OptionalT<GtsamCameraImuExtrinsicFactor> return camera imu extrinsic factor in gtsam if success,
     * otherwise nonetype.
     */
    OptionalT<GtsamCameraImuExtrinsicFactor>
    convertCameraImuExtrinsicCalibFactor(const CameraImuExtrinsicCalibFactor& factor, KeyTimestampMap& stamps) const;

    /**
     * @brief Convert projection line factor
     *
     * @param[in] factor projection line in holo
     * @return GtsamProjectionLineFactor return projection line factor in gtsam if success,
     * otherwise nonetype.
     */
    std::vector<GtsamProjectionLineFactor> convertProjectionLineFactor(const ProjectedLineFactor& factor) const;

    /**
     * @brief Convert imu body extrinsic factor
     *
     * @param[in] factor imu body extrinsic in holo
     * @param[in] key timestamp map
     * @return OptionalT<GtsamImuBodyExtrinsicFactor> return imu body extrinsic factor in gtsam if success,
     * otherwise nonetype.
     */
    OptionalT<GtsamImuBodyExtrinsicFactor> convertImuBodyExtrinsicCalibFactor(const ImuBodyExtrinsicCalibFactor& factor,
                                                                              KeyTimestampMap& stamps) const;

    /**
     * @brief Convert gnss position velocity factor
     *
     * @param factor holo gnss position velocity factor
     * @return OptionalT<GtsamGnssPositionVelocityFactor>
     */
    OptionalT<GtsamGnssPositionVelocityFactor>
    convertGnssPositionVelocityFactor(const GnssPositionVelocityFactor& factor) const;

    /**
     * @brief Convert RPY factor
     *
     * @param[in] factor prior rpy factor in holo type
     * @return Optional<GtsamPriorRPYFactor> return prior rpy factor in gtsam if success otherwise nonetype
     */
    OptionalT<GtsamPriorRPYFactor> convertPriorRPYFactor(PriorRPYFactor const& factor) const;

    /**
     * @brief Convert imu preintegration measurement
     *
     * @param pim_holo imu preintegrartion measurement in holo
     * @return OptionalT<PreintegratedImuMeasurements> return preintegration measurement in gtsam if success, otherwise
     * nonetype.
     */
    OptionalT<PreintegratedImuMeasurements>
    convertImuPreintegrationMeasurement(const ImuPreintegrationMeasurement& pim_holo) const;

    /**
     * @brief Convert the Values object
     *
     * @param values values in gtsam
     * @param factor_graph factor graph in holo which contains all of values
     */
    void convertValues(const Values& values, FactorGraph& factor_graph) const;

    /**
     * @brief Convert the Pose3 Values object from values
     *
     * @param values values in gtsam
     * @param pose_values pose values in holo.
     */
    void convertPose3Values(const Values& values, Pose3Values& pose_values) const;

    /**
     * @brief Convert the Velocity3 Values object from values
     *
     * @param values values in gtsam
     * @param velocity_values velocity values in holo.
     */
    void convertVelocity3Values(const Values& values, Velocity3Values& velocity_values) const;

    /**
     * @brief Convert the Imu Bias Values object from values
     *
     * @param values values in gtsam
     * @param imu_bias_values imu bias values in holo.
     */
    void convertImuBiasValues(const Values& values, ImuBiasValues& imu_bias_values) const;

    /**
     * @brief Convert the Position3 Values object from values
     *
     * @param values values in gtsam
     * @param position_values position values in holo.
     */
    void convertPosition3Values(const Values& values, Position3Values& position_values) const;

    /**
     * @brief Convert the Vector3 Values object from values
     *
     * @param[in] values values in gtsam
     * @param[in] vector3_values vector3 values in holo.
     */
    void convertVector3Values(const Values& values, Vector3Values& vector3_values) const;

    /**
     * @brief Convert the Rot3 Values object from values
     *
     * @param[in] values values in gtsam
     * @param[in] rot3_values rot3 values in holo.
     */
    void convertRot3Values(const Values& values, Rot3Values& rot3_values) const;

    /**
     * @brief Create a Isam2 Parameters object by smoother parameters
     *
     * @return ISAM2Params which create by smoother parameters
     */
    ISAM2Params createIsam2Parameters() const;

private:
    /**
     * @brief convert symbol
     *
     * @param in holo symbol
     * @return gtsam::Symbol
     */
    gtsam::Symbol convertSymbol(const Symbol& in) const
    {
        char c = 'x';
        switch (in.value_type)
        {
            case ValueType::POSITION3:
            {
                c = 'l';
                break;
            }
            case ValueType::POSE3:
            {
                c = 'x';
                break;
            }
            case ValueType::VELOCITY3:
            {
                c = 'v';
                break;
            }
            case ValueType::IMUBIAS:
            {
                c = 'b';
                break;
            }
            case ValueType::VECTOR3:
            {
                c = 't';
                break;
            }
            case ValueType::ROT3:
            {
                c = 'e';
                break;
            }
            default:
            {
                std::stringstream ss;
                ss << "Unsupported symbol: " << (uint16_t)in.value_type;
                LOG(ERROR) << ss.str();
                throw std::runtime_error(ss.str());
                break;
            }
        }
        return gtsam::Symbol(c, in.index);
    }

    /**
     * @brief Convert holo type matrix to eigen type matrix
     *
     * @tparam RowValue the rows of matrix
     * @tparam ColValue the columns of matrix
     * @param mat input holo type matrix
     * @return Eigen::Matrix<float64_t, RowValue, ColValue> eigen type matrix
     */
    template <uint8_t RowValue, uint8_t ColValue>
    Eigen::Matrix<float64_t, RowValue, ColValue>
    convertMatrix(const holo::numerics::MatrixT<float64_t, RowValue, ColValue>& mat) const
    {
        const uint32_t array_size = mat.GetCols() * mat.GetRows();

        Eigen::Matrix<float64_t, RowValue, ColValue> result;
        memcpy(result.data(), mat.GetData(), sizeof(float64_t) * array_size);
        return result;
    }

    /**
     * @brief Convert eigen type matrix to holo type matrix
     *
     * @tparam RowValue the row number of matrix
     * @tparam ColValue the column number of matrix
     * @param mat input eigen type matrix
     * @return MatrixT<float64_t, RowValue, ColValue> holo type matrix
     */
    template <uint8_t RowValue, uint8_t ColValue>
    holo::numerics::MatrixT<float64_t, RowValue, ColValue>
    convertToHoloMatrix(const Eigen::Matrix<float64_t, RowValue, ColValue>& mat) const
    {
        uint32_t array_size = mat.cols() * mat.rows();

        holo::numerics::MatrixT<float64_t, RowValue, ColValue> result;
        memcpy(result.GetData(), mat.data(), sizeof(float64_t) * array_size);
        return result;
    }

    /**
     * @brief for dynamic matrix convert eigen type matrix to holo type matrix
     *
     * @param mat input gtsam matrix type
     * @return MatrixXType
     */
    MatrixXType convertToHoloMatrix(const gtsam::Matrix& mat) const
    {
        MatrixXType result(mat.rows(), mat.cols());

        for (uint16_t i = 0u; i < result.GetRows(); i++)
        {
            for (uint16_t j = 0u; j < result.GetCols(); j++)
            {
                result(i, j) = mat(i, j);
            }
        }

        return result;
    }

    /**
     * @brief Convert the order of covariance matrix, because the order of pose covariance is different. For gtsam, the
     * order of pose covariance is [RR RT; TR TT], For holo, the order of pose covariance is [TT TR; RT RR].
     * @details from [A B    =>   [D C
     *                C D]         B A]
     *
     * @param input
     * @return Matrix6Type
     */
    Matrix6Type convertCovarianceMatrixOrder(const Matrix6Type& input) const
    {
        Matrix6Type result;
        result.SetBlock(0u, 0u, Matrix3Type(input.GetBlock(3u, 3u, 3u, 3u)));
        result.SetBlock(0u, 3u, Matrix3Type(input.GetBlock(3u, 0u, 3u, 3u)));
        result.SetBlock(3u, 0u, Matrix3Type(input.GetBlock(0u, 3u, 3u, 3u)));
        result.SetBlock(3u, 3u, Matrix3Type(input.GetBlock(0u, 0u, 3u, 3u)));
        return result;
    }

    /* parameters of fixed lag smoother*/
    Parameters params_;

    SmootherPtr smoother_;

};  // class Smoother::Implement

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::PriorFactorPose3>
Smoother::Implement::convertPriorPoseFactor(const PriorPoseFactor& factor) const
{
    /* @todo: (lichao@holomatic.com) add factor check */
    return OptionalT<PriorFactorPose3>(PriorFactorPose3(
        X(Key(factor.symbol.index)), GTPose3(convertMatrix<4u, 4u>((factor.measurement.ToMatrix()))),
        Gaussian::Covariance(convertMatrix<6u, 6u>(convertCovarianceMatrixOrder(factor.covariance_matrix)))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::PriorFactorVel3>
Smoother::Implement::convertPriorVelocityFactor(const PriorVelocityFactor& factor) const
{
    /* @todo: (lichao@holomatic.com) add factor check */
    return OptionalT<PriorFactorVel3>(
        PriorFactorVel3(V(Key(factor.symbol.index)), convertMatrix<3u, 1u>(factor.measurement),
                        Gaussian::Covariance(convertMatrix<3u, 3u>(factor.covariance_matrix))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::PriorFactorImuBias>
Smoother::Implement::convertPriorImuBiasFactor(const PriorImuBiasFactor& factor) const
{
    /* @todo: (lichao@holomatic.com) add factor check */
    /* init imu bias */
    ConstantBias prior_imu_bias(convertMatrix<3u, 1u>(factor.measurement.GetLinearAccelerationBias<Vector3Type>()),
                                convertMatrix<3u, 1u>(factor.measurement.GetAngularVelocityBias<Vector3Type>()));
    return OptionalT<PriorFactorImuBias>(
        PriorFactorImuBias(B(Key(factor.symbol.index)), prior_imu_bias,
                           Gaussian::Covariance(convertMatrix<6u, 6u>(factor.covariance_matrix))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::PriorFactorVector3>
Smoother::Implement::convertPriorVector3Factor(const PriorVector3Factor& factor) const
{
    return OptionalT<PriorFactorVector3>(
        PriorFactorVector3(T(factor.symbol.index), convertMatrix<3u, 1u>(factor.measurement),
                           Gaussian::Covariance(convertMatrix<3u, 3u>(factor.covariance_matrix))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::PriorFactorRot3>
Smoother::Implement::convertPriorRot3Factor(const PriorRot3Factor& factor) const
{
    return OptionalT<PriorFactorRot3>(
        PriorFactorRot3(E(factor.symbol.index), GTRot3(convertMatrix<3u, 3u>(factor.measurement.ToMatrix())),
                        Gaussian::Covariance(convertMatrix<3u, 3u>(factor.covariance_matrix))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::GtsamGnssFactor> Smoother::Implement::convertGnssFactor(const GnssFactor& factor) const
{
    /* @todo: (lichao@holomatic.com) add factor check */
    return OptionalT<GtsamGnssFactor>(GtsamGnssFactor(
        X(Key(factor.symbol.index)), GTPoint3(convertMatrix<3u, 1u>((factor.measurement.As<Vector3Type>()))),
        Gaussian::Covariance(convertMatrix<3u, 3u>(factor.covariance_matrix))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::PreintegratedImuMeasurements>
Smoother::Implement::convertImuPreintegrationMeasurement(const ImuPreintegration::Measurement& pim_holo) const
{
    /// 2.1.1 initialize gtsam pim2

    /* get parameters */
    const ImuPreintegrationParameters params = pim_holo.GetParameters();

    /* get imu bias */
    const ImuBiasType imu_bias = pim_holo.GetImuBias();

    // PreintegrationBase params
    boost::shared_ptr<gtsam::PreintegratedImuMeasurements::Params> preint_param =
        gtsam::PreintegratedImuMeasurements::Params::MakeSharedU(params.GetGravity());
    preint_param->setBodyPSensor(gtsam::Pose3(convertMatrix<4u, 4u>(params.GetExtrinsicBodyImu().ToMatrix())));
    // ENU navigation frame, gravity vector default is -9.81 m/s^2
    // acc white noise in continuous
    preint_param->accelerometerCovariance =
        convertMatrix<3u, 3u>(params.GetAccNoiseSigmas().CwiseSquare().AsDiagonal());
    // gyro white noise in continuous
    preint_param->gyroscopeCovariance = convertMatrix<3u, 3u>(params.GetGyroNoiseSigmas().CwiseSquare().AsDiagonal());
    // integration uncertainty continuous
    // TODO: hard code 1e-8 (@lichao)
    preint_param->integrationCovariance =
        convertMatrix<3u, 3u>((Scalar)params.GetIntegrationUncertainty() * Matrix3Type::Identity());

    /* convert holo::ImuBias to gtsam::ConstantBias */
    gtsam::imuBias::ConstantBias imubias(convertMatrix<3u, 1u>(imu_bias.GetLinearAccelerationBias<Vector3Type>()),
                                         convertMatrix<3u, 1u>(imu_bias.GetAngularVelocityBias<Vector3Type>()));

    return OptionalT<PreintegratedImuMeasurements>(PreintegratedImuMeasurements(
        gtsam::PreintegrationType(preint_param, pim_holo.GetDeltaTime(),
                                  convertMatrix<9u, 1u>(pim_holo.GetPreintegratedNavstate()),
                                  convertMatrix<9u, 3u>(pim_holo.GetPreintegratedJacobianBiasAcc()),
                                  convertMatrix<9u, 3u>(pim_holo.GetPreintegratedJacobianBiasGyro()), imubias),
        convertMatrix<9u, 9u>(pim_holo.GetPreintegratedMeasurementCovariance())));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::GtsamImuFactor> Smoother::Implement::convertImuFactor(const ImuFactor& factor) const
{
    /* Step1, Convert holo::PIM to gtsam::PIM */
    OptionalT<PreintegratedImuMeasurements> pim = convertImuPreintegrationMeasurement(factor.measurement);

    if (!pim || factor.symbols.empty())
    {
        LOG(WARNING) << "PIM cannot be converted or factor symbols is empty ..";
        return OptionalT<GtsamImuFactor>();
    }

    GtsamImuFactor imu_factor = GtsamImuFactor(X(Key(factor.symbols[0u].index)), V(Key(factor.symbols[1u].index)),
                                               X(Key(factor.symbols[2u].index)), V(Key(factor.symbols[3u].index)),
                                               B(Key(factor.symbols[4u].index)), pim.GetData());
    /* Step2, Create gtsam factor */
    return OptionalT<GtsamImuFactor>(imu_factor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::BetweenFactorImuBias>
Smoother::Implement::convertImuBiasFactor(const ImuBiasFactor& factor) const
{
    if (factor.symbols.empty())
    {
        LOG(WARNING) << "factor symbols is empty ..";
        return OptionalT<BetweenFactorImuBias>();
    }

    /* @todo: (lichao@holomatic.com) add factor check */
    ConstantBias imu_bias(convertMatrix<3u, 1u>(factor.measurement.GetLinearAccelerationBias<Vector3Type>()),
                          convertMatrix<3u, 1u>(factor.measurement.GetAngularVelocityBias<Vector3Type>()));

    return OptionalT<BetweenFactorImuBias>(
        BetweenFactorImuBias(B(Key(factor.symbols[0u].index)), B(Key(factor.symbols[1u].index)), imu_bias,
                             Gaussian::Covariance(convertMatrix<6u, 6u>(factor.covariance_matrix))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::BetweenFactorPose3>
Smoother::Implement::convertRelativePoseFactor(const RelativePoseFactor& factor) const
{
    if (factor.symbols.empty())
    {
        LOG(WARNING) << "factor symbols is empty ..";
        return OptionalT<BetweenFactorPose3>();
    }

    return OptionalT<BetweenFactorPose3>(BetweenFactorPose3(
        X(Key(factor.symbols[0u].index)), X(Key(factor.symbols[1u].index)),
        GTPose3(convertMatrix<4u, 4u>(factor.measurement.ToMatrix())),
        Gaussian::Covariance(convertMatrix<6u, 6u>(convertCovarianceMatrixOrder(factor.covariance_matrix)))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::BetweenFactorVel3>
Smoother::Implement::convertRelativeVelocityFactor(const RelativeVelocityFactor& factor) const
{
    if (factor.symbols.empty())
    {
        LOG(WARNING) << "factor symbols is empty ..";
        return OptionalT<BetweenFactorVel3>();
    }

    return OptionalT<BetweenFactorVel3>(
        BetweenFactorVel3(V(Key(factor.symbols[0u].index)), V(Key(factor.symbols[1u].index)),
                          GTVector3(convertMatrix<3u, 1u>(factor.measurement)),
                          Gaussian::Covariance(convertMatrix<3u, 3u>(factor.covariance_matrix))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<std::vector<Smoother::Implement::GtsamLaneFactor>>
Smoother::Implement::convertLaneFactor(const LaneFactor& factor) const
{
    std::vector<Smoother::Implement::GtsamLaneFactor> lane_factors;
    std::vector<Scalar>::const_iterator               covariance_iter = factor.covariance_matrix.begin();
    for (std::vector<Point3Type>::const_iterator iter = factor.measurement.points.begin();
         iter != factor.measurement.points.end() && covariance_iter != factor.covariance_matrix.end();
         iter++, covariance_iter++)
    {
        gtsam::SharedNoiseModel noise_model(Gaussian::Covariance(convertMatrix<1u, 1u>(*covariance_iter)));

        GtsamLaneFactor lane_factor = GtsamLaneFactor(X(Key(factor.symbol.index)), noise_model, *iter,
                                                      factor.measurement.line, factor.measurement.type);
        lane_factors.push_back(lane_factor);
    }
    return OptionalT<std::vector<Smoother::Implement::GtsamLaneFactor>>(lane_factors);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::addSignFactor(const SignFactor& factor, NonlinearFactorGraph& factor_graph) const
{
    /* Step1: create unknown expression pose which from body to world */
    gtsam::Expression<GTPose3> pose_unknown_expression(X(Key(factor.symbol.index)));
    gtsam::Expression<GTPose3> pose_bTc_expression(GTPose3(convertMatrix<4u, 4u>(factor.measurement.bTc.ToMatrix())));

    /* Step2: create expression pose which from camera to world */
    gtsam::Expression<GTPose3> pose_wTc_expression =
        gtsam::compose<GTPose3>(pose_unknown_expression, pose_bTc_expression);

    /* Step3: create const expression calibration from camera intrinsic */
    const Scalar fx   = factor.measurement.K(0u, 0u);
    const Scalar fy   = factor.measurement.K(1u, 1u);
    const Scalar cx   = factor.measurement.K(0u, 2u);
    const Scalar cy   = factor.measurement.K(1u, 2u);
    const Scalar skew = factor.measurement.K(0u, 1u);

    gtsam::Expression<gtsam::Cal3_S2> calibration_constant_expression(gtsam::Cal3_S2(fx, fy, skew, cx, cy));

    /* Step4: convert 2d-3d point correspondence to expression point2 factor and add it to factor graph */
    std::vector<std::pair<Point2Type, Point3Type>>::const_iterator iter = factor.measurement.measured.begin();
    for (; iter != factor.measurement.measured.end(); iter++)
    {
        GTPoint2 measurement(iter->first.GetX(), iter->first.GetY());

        gtsam::Expression<GTPoint3> landmark_constant_expression(
            GTPoint3(iter->second.GetX(), iter->second.GetY(), iter->second.GetZ()));

        gtsam::Expression<GTPoint2> expression_point2(gtsam::project3<gtsam::Cal3_S2, gtsam::Point3>(
            pose_wTc_expression, landmark_constant_expression, calibration_constant_expression));

        gtsam::SharedNoiseModel noise_model(Gaussian::Covariance(convertMatrix<2u, 2u>(factor.covariance_matrix)));

        if (factor.use_huber_loss)
        {
            const Robust::shared_ptr huber_noise_model = gtsam::noiseModel::Robust::Create(
                gtsam::noiseModel::mEstimator::Huber::Create(factor.huber_loss_threshold), noise_model);

            factor_graph.addExpressionFactor(huber_noise_model, measurement, expression_point2);
        }
        else
        {
            factor_graph.addExpressionFactor(noise_model, measurement, expression_point2);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::GtsamProjectionFactor>
Smoother::Implement::convertProjectionFactor(const ProjectionFactor& factor, KeyTimestampMap& stamps) const
{
    if (factor.symbols.empty())
    {
        LOG(WARNING) << "factor symbols is empty ..";
        return OptionalT<GtsamProjectionFactor>();
    }

    /* Update timestamp of old landmarks */
    GTSymbol pose_key     = X(Key(factor.symbols[0u].index));
    GTSymbol landmark_key = L(Key(factor.symbols[1u].index));
    if (stamps.find(landmark_key) == stamps.end())
    {
        stamps[landmark_key] = stamps[pose_key];
    }

    /* Create huber loss */
    const Robust::shared_ptr huber =
        Robust::Create(Huber::Create(1.0), Gaussian::Covariance(convertMatrix<2u, 2u>(factor.covariance_matrix)));

    const Scalar fx   = factor.measurement.K(0u, 0u);
    const Scalar fy   = factor.measurement.K(1u, 1u);
    const Scalar cx   = factor.measurement.K(0u, 2u);
    const Scalar cy   = factor.measurement.K(1u, 2u);
    const Scalar skew = factor.measurement.K(0u, 1u);

    const gtsam::Cal3_S2::shared_ptr K = boost::make_shared<gtsam::Cal3_S2>(fx, fy, skew, cx, cy);

    return OptionalT<GtsamProjectionFactor>(
        GtsamProjectionFactor(GTPoint2(convertMatrix<2u, 1u>(factor.measurement.measured.ToVector())), huber, pose_key,
                              landmark_key, K, params_.throw_cheirality, params_.verbose_cheirality,
                              GTPose3(convertMatrix<4u, 4u>(factor.measurement.bTc.ToMatrix()))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::GtsamVelocityFactor>
Smoother::Implement::convertVelocityFactor(const VelocityFactor& factor) const
{
    if (factor.symbols.empty())
    {
        LOG(WARNING) << "factor symbols is empty ..";
        return OptionalT<GtsamVelocityFactor>();
    }

    return OptionalT<GtsamVelocityFactor>(
        GtsamVelocityFactor(X(Key(factor.symbols[0].index)), V(Key(factor.symbols[1].index)),
                            GTVector3(convertMatrix<3u, 1u>(factor.measurement)),
                            Gaussian::Covariance(convertMatrix<3u, 3u>(factor.covariance_matrix))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::GtsamWheelSpeedFactor>
Smoother::Implement::convertWheelSpeedFactor(const WheelSpeedFactor& factor) const
{
    if (factor.symbols.empty())
    {
        LOG(WARNING) << "factor symbols is empty ..";
        return OptionalT<GtsamWheelSpeedFactor>();
    }

    GTPose3 const iEb = GTPose3(convertMatrix<4u, 4u>(factor.measurement.GetEibHat().ToMatrix()));

    Vector3Type const wheel_preintegrated_dist = factor.measurement.GetPreintegrated();

    GTVector3 const preintegrated_dist(wheel_preintegrated_dist(0u), wheel_preintegrated_dist(1u),
                                       wheel_preintegrated_dist(2u));

    return OptionalT<GtsamWheelSpeedFactor>(GtsamWheelSpeedFactor(
        X(Key(factor.symbols[0].index)), X(Key(factor.symbols[1].index)), iEb,
        convertMatrix<3u, 3u>(factor.measurement.GetPreintegratedMeasurementCovariance()), preintegrated_dist));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::GtsamCameraImuExtrinsicFactor> Smoother::Implement::convertCameraImuExtrinsicCalibFactor(
    const CameraImuExtrinsicCalibFactor& factor, KeyTimestampMap& stamps) const
{
    if (factor.symbols.empty())
    {
        LOG(WARNING) << "factor symbols is empty ..";
        return OptionalT<GtsamCameraImuExtrinsicFactor>();
    }

    /* Update timestamp of old landmarks and extrinsics */
    GTSymbol wTi_key = X(Key(factor.symbols[0u].index));
    GTSymbol ptw_key = L(Key(factor.symbols[1u].index));
    GTSymbol rpy_key = T(Key(factor.symbols[2u].index));
    GTSymbol itc_key = T(Key(factor.symbols[3u].index));
    if (stamps.find(ptw_key) == stamps.end())
    {
        stamps[ptw_key] = stamps[wTi_key];
    }

    if (stamps.find(rpy_key) == stamps.end())
    {
        stamps[rpy_key] = stamps[wTi_key];
    }

    if (stamps.find(itc_key) == stamps.end())
    {
        stamps[itc_key] = stamps[wTi_key];
    }

    /* Create huber loss */
    const Robust::shared_ptr huber =
        Robust::Create(Huber::Create(1.0), Gaussian::Covariance(convertMatrix<2u, 2u>(factor.covariance_matrix)));

    const Scalar fx   = factor.measurement.K(0u, 0u);
    const Scalar fy   = factor.measurement.K(1u, 1u);
    const Scalar cx   = factor.measurement.K(0u, 2u);
    const Scalar cy   = factor.measurement.K(1u, 2u);
    const Scalar skew = factor.measurement.K(0u, 1u);

    const gtsam::Cal3_S2::shared_ptr K = boost::make_shared<gtsam::Cal3_S2>(fx, fy, skew, cx, cy);

    return OptionalT<GtsamCameraImuExtrinsicFactor>(GtsamCameraImuExtrinsicFactor(
        huber, wTi_key, ptw_key, rpy_key, itc_key, K,
        GTPoint2(convertMatrix<2u, 1u>(factor.measurement.measured.ToVector())), factor.fix_wTi, factor.fix_ptw,
        factor.fix_roll, factor.fix_pitch, factor.fix_yaw, factor.fix_itc));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Smoother::Implement::GtsamProjectionLineFactor>
Smoother::Implement::convertProjectionLineFactor(const ProjectedLineFactor& factor) const
{
    // Create huber loss
    const Robust::shared_ptr huber_noise_model =
        Robust::Create(Huber::Create(factor.huber_loss_threshold),
                       Gaussian::Covariance((gtsam::Vector1(1) << factor.covariance_matrix).finished()));

    const Scalar fx   = factor.measurement.K(0u, 0u);
    const Scalar fy   = factor.measurement.K(1u, 1u);
    const Scalar cx   = factor.measurement.K(0u, 2u);
    const Scalar cy   = factor.measurement.K(1u, 2u);
    const Scalar skew = factor.measurement.K(0u, 1u);

    const gtsam::Cal3_S2 K = gtsam::Cal3_S2(fx, fy, skew, cx, cy);

    std::vector<Smoother::Implement::GtsamProjectionLineFactor> projection_line_factors;
    GTPose3 bTc = GTPose3(convertMatrix<4u, 4u>(factor.measurement.bTc.ToMatrix()));

    for (std::vector<Point3Type>::const_iterator iter = factor.measurement.source_pts.begin();
         iter != factor.measurement.source_pts.end(); iter++)
    {
        GTPoint3 point = GTPoint3((*iter).GetX(), (*iter).GetY(), (*iter).GetZ());

        GtsamProjectionLineFactor smart_camera_factor = GtsamProjectionLineFactor(
            X(Key(factor.symbol.index)), huber_noise_model, point, bTc, K, factor.measurement.target_line);

        projection_line_factors.push_back(smart_camera_factor);
    }
    return projection_line_factors;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::GtsamImuBodyExtrinsicFactor> Smoother::Implement::convertImuBodyExtrinsicCalibFactor(
    const ImuBodyExtrinsicCalibFactor& factor, KeyTimestampMap& stamps) const
{
    if (factor.symbols.empty())
    {
        LOG(WARNING) << "factor symbols is empty ..";
        return OptionalT<GtsamImuBodyExtrinsicFactor>();
    }

    /* Update timestamp of extrinsics */
    GTSymbol wTi_key = X(Key(factor.symbols[1u].index));
    GTSymbol rot_key = E(Key(factor.symbols[2u].index));

    if (stamps.find(rot_key) == stamps.end())
    {
        stamps[rot_key] = stamps[wTi_key];
    }

    GTMatrix3 const D_iRb = convertMatrix<3u, 3u>(factor.measurement.GetPreintegratedHRib());

    GTPose3 const iEb = GTPose3(convertMatrix<4u, 4u>(factor.measurement.GetEibHat().ToMatrix()));

    Vector3Type const wheel_preintegrated_dist = factor.measurement.GetPreintegrated();

    GTVector3 const preintegrated_dist(wheel_preintegrated_dist(0u), wheel_preintegrated_dist(1u),
                                       wheel_preintegrated_dist(2u));

    return OptionalT<GtsamImuBodyExtrinsicFactor>(GtsamImuBodyExtrinsicFactor(
        X(Key(factor.symbols[0].index)), X(Key(factor.symbols[1].index)), E(Key(factor.symbols[2].index)),
        iEb.translation(), convertMatrix<3u, 3u>(factor.measurement.GetPreintegratedMeasurementCovariance()), D_iRb,
        iEb.rotation(), preintegrated_dist));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::GtsamGnssPositionVelocityFactor>
Smoother::Implement::convertGnssPositionVelocityFactor(const GnssPositionVelocityFactor& factor) const
{
    GTSymbol const pose_key     = X(factor.symbols[0].index);
    GTSymbol const velocity_key = V(factor.symbols[1].index);

    GTPoint3 const  gnss_position(factor.position.GetX(), factor.position.GetY(), factor.position.GetZ());
    GTVector3 const gnss_velocity(factor.velocity(0u), factor.velocity(1u), factor.velocity(2u));

    GTVector6 const sigmas = (GTVector6() << factor.sigmas(0u), factor.sigmas(1u), factor.sigmas(2u), factor.sigmas(3u),
                              factor.sigmas(4u), factor.sigmas(5u))
                                 .finished();

    if (!factor.pim)
    {
        return GtsamGnssPositionVelocityFactor(pose_key, velocity_key, gnss_position, gnss_velocity, sigmas);
    }

    gtsam::PreintegratedImuMeasurements pim = *convertImuPreintegrationMeasurement(*(factor.pim));

    GTMatrix3 wRb;
    wRb << factor.wRb.R00(), factor.wRb.R01(), factor.wRb.R02(), factor.wRb.R10(), factor.wRb.R11(), factor.wRb.R12(),
        factor.wRb.R20(), factor.wRb.R21(), factor.wRb.R22();

    return GtsamGnssPositionVelocityFactor(pose_key, velocity_key, gnss_position, gnss_velocity, sigmas, pim, wRb);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<Smoother::Implement::GtsamPriorRPYFactor>
Smoother::Implement::convertPriorRPYFactor(PriorRPYFactor const& factor) const
{
    gtsam::Key const   pose_key        = gtsam::symbol_shorthand::X(factor.symbol.index);
    Vector3Type const& rpy_measurement = factor.measurement;
    GTVector3 const    measurement(rpy_measurement(0u), rpy_measurement(1u), rpy_measurement(2u));
    return OptionalT<GtsamPriorRPYFactor>(
        GtsamPriorRPYFactor(Gaussian::Covariance(convertMatrix<3u, 3u>(factor.covariance_matrix)), pose_key,
                            measurement, factor.fix_roll, factor.fix_pitch, factor.fix_yaw));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::convertFactorGraph(const FactorGraph& factor_graph, NonlinearFactorGraph& factors,
                                             Values& values, KeyTimestampMap& stamps)
{
    /* clear output container */
    factors.resize(0);
    values.clear();
    stamps.clear();

    LOG_IF(INFO, params_.verbose) << "Start to convert factor graph.. ";

    /* Step1. Convert value arrays*/
    /* 1.1 Convert pose values */
    if (factor_graph.pose_values)
    {
        Pose3Values::const_iterator pose_iter = factor_graph.pose_values->cbegin();
        for (; pose_iter != factor_graph.pose_values->cend(); ++pose_iter)
        {
            const Key k = Key(pose_iter->symbol.index);
            if (!values.exists(X(k)))
            {
                stamps[X(k)] = pose_iter->timestamp.ToSec();
                values.insert(X(k), GTPose3(convertMatrix<4u, 4u>(pose_iter->state.ToMatrix())));
            }
            else
            {
                LOG(WARNING) << "skip to insert repeated value, please check factor graph ..";
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert pose values.. ";

    /* 1.2 Convert velocity values */
    if (factor_graph.velocity_values)
    {
        Velocity3Values::const_iterator vel_iter = factor_graph.velocity_values.GetData().begin();
        for (; vel_iter != factor_graph.velocity_values.GetData().end(); ++vel_iter)
        {
            const Key k = Key(vel_iter->symbol.index);
            if (!values.exists(V(k)))
            {
                stamps[V(k)] = vel_iter->timestamp.ToSec();
                values.insert(V(k), convertMatrix<3u, 1u>(vel_iter->state));
            }
            else
            {
                LOG(WARNING) << "skip to insert repeated value, please check factor graph ..";
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert velocity values.. ";

    /* 1.3 Convert imubias values */
    if (factor_graph.imu_bias_values)
    {
        ImuBiasValues::const_iterator bias_iter = factor_graph.imu_bias_values.GetData().begin();
        for (; bias_iter != factor_graph.imu_bias_values.GetData().end(); ++bias_iter)
        {
            const Key k = Key(bias_iter->symbol.index);
            if (!values.exists(B(k)))
            {
                stamps[B(k)] = bias_iter->timestamp.ToSec();
                values.insert(
                    B(k), ConstantBias(convertMatrix<3u, 1u>(bias_iter->state.GetLinearAccelerationBias<Vector3Type>()),
                                       convertMatrix<3u, 1u>(bias_iter->state.GetAngularVelocityBias<Vector3Type>())));
            }
            else
            {
                LOG(WARNING) << "skip to insert repeated value, please check factor graph ..";
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert imu bias values.. ";

    /* 1.4 Convert position values */
    if (factor_graph.position_values)
    {
        Position3Values::const_iterator lm_iter = factor_graph.position_values.GetData().begin();
        for (; lm_iter != factor_graph.position_values.GetData().end(); ++lm_iter)
        {
            const Key k = Key(lm_iter->symbol.index);
            if (!values.exists(L(k)))
            {
                stamps[L(k)] = lm_iter->timestamp.ToSec();
                values.insert(L(k), GTPoint3(convertMatrix<3u, 1u>(lm_iter->state.As<Vector3Type>())));
            }
            else
            {
                LOG(WARNING) << "skip to insert repeated value, please check factor graph ..";
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert position values.. ";

    /* 1.5 Convert vector3 values */
    if (factor_graph.vector3_values)
    {
        Vector3Values::const_iterator vec3_iter = factor_graph.vector3_values.GetData().begin();

        for (; vec3_iter != factor_graph.vector3_values.GetData().end(); ++vec3_iter)
        {
            const Key k = Key(vec3_iter->symbol.index);

            if (!values.exists(T(k)))
            {
                stamps[T(k)] = vec3_iter->timestamp.ToSec();
                values.insert(T(k), GTVector3(convertMatrix<3u, 1u>(vec3_iter->state)));
            }
            else
            {
                LOG(WARNING) << "skip to insert repeated value, please check factor graph ..";
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert vector3 values.. ";

    /* 1.6 Convert rot3 values */
    if (factor_graph.rot3_values)
    {
        Rot3Values::const_iterator rot3_iter = factor_graph.rot3_values.GetData().begin();

        for (; rot3_iter != factor_graph.rot3_values.GetData().end(); ++rot3_iter)
        {
            const Key k = Key(rot3_iter->symbol.index);

            if (!values.exists(E(k)))
            {
                stamps[E(k)] = rot3_iter->timestamp.ToSec();
                values.insert(E(k), GTRot3(convertMatrix<3u, 3u>(rot3_iter->state.ToMatrix())));
            }
            else
            {
                LOG(WARNING) << "skip to insert repeated value, please check factor graph ..";
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert rot3 values.. ";

    /* Step2. Convert factor arrays*/
    /* 2.1 Convert prior pose factors */
    if (factor_graph.prior_pose_factors)
    {
        PriorPoseFactors::const_iterator prior_pose_iter = factor_graph.prior_pose_factors.GetData().begin();
        for (; prior_pose_iter != factor_graph.prior_pose_factors.GetData().end(); ++prior_pose_iter)
        {
            OptionalT<PriorFactorPose3> factor = convertPriorPoseFactor(*prior_pose_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert prior pose factors .. ";

    /* 2.2 Convert prior velocity factors */
    if (factor_graph.prior_velocity_factors)
    {
        PriorVelocityFactors::const_iterator prior_vel_iter = factor_graph.prior_velocity_factors.GetData().begin();
        for (; prior_vel_iter != factor_graph.prior_velocity_factors.GetData().end(); ++prior_vel_iter)
        {
            OptionalT<PriorFactorVel3> factor = convertPriorVelocityFactor(*prior_vel_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert prior velocity factors .. ";

    /* 2.3 Convert prior imubias factors */
    if (factor_graph.prior_imu_bias_factors)
    {
        PriorImuBiasFactors::const_iterator prior_bias_iter = factor_graph.prior_imu_bias_factors.GetData().begin();
        for (; prior_bias_iter != factor_graph.prior_imu_bias_factors.GetData().end(); ++prior_bias_iter)
        {
            OptionalT<PriorFactorImuBias> factor = convertPriorImuBiasFactor(*prior_bias_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert prior imubias factors .. ";

    /* 2.4 Convert prior vector3 factors */
    if (factor_graph.prior_vector3_factors)
    {
        PriorVector3Factors::const_iterator prior_vector3_iter = factor_graph.prior_vector3_factors.GetData().begin();

        for (; prior_vector3_iter != factor_graph.prior_vector3_factors.GetData().end(); ++prior_vector3_iter)
        {
            OptionalT<PriorFactorVector3> factor = convertPriorVector3Factor(*prior_vector3_iter);

            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert prior vector3 factors .. ";

    /* 2.5 Convert prior rot3 factors */
    if (factor_graph.prior_rot3_factors)
    {
        PriorRot3Factors::const_iterator prior_rot3_iter = factor_graph.prior_rot3_factors.GetData().begin();

        for (; prior_rot3_iter != factor_graph.prior_rot3_factors.GetData().end(); ++prior_rot3_iter)
        {
            OptionalT<PriorFactorRot3> factor = convertPriorRot3Factor(*prior_rot3_iter);

            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert prior rot3 factors .. ";

    /* 2.6 Convert gnss factors */
    if (factor_graph.gnss_factors)
    {
        GnssFactors::const_iterator gnss_iter = factor_graph.gnss_factors.GetData().begin();
        for (; gnss_iter != factor_graph.gnss_factors.GetData().end(); ++gnss_iter)
        {
            OptionalT<GtsamGnssFactor> factor = convertGnssFactor(*gnss_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert gnss factors .. ";

    /* 2.7 Convert imu factors */
    if (factor_graph.imu_factors)
    {
        ImuFactors::const_iterator imu_iter = factor_graph.imu_factors.GetData().begin();
        for (; imu_iter != factor_graph.imu_factors.GetData().end(); ++imu_iter)
        {
            OptionalT<GtsamImuFactor> factor = convertImuFactor(*imu_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert imu factors .. ";

    /* 2.8 Convert imu bias factors */
    if (factor_graph.imu_bias_factors)
    {
        ImuBiasFactors::const_iterator imu_bias_iter = factor_graph.imu_bias_factors.GetData().begin();
        for (; imu_bias_iter != factor_graph.imu_bias_factors.GetData().end(); ++imu_bias_iter)
        {
            OptionalT<BetweenFactorImuBias> factor = convertImuBiasFactor(*imu_bias_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert imu bias factors .. ";

    /* 2.9 Convert relative pose factors */
    if (factor_graph.relative_pose_factors)
    {
        RelativePoseFactors::const_iterator rel_pose_iter = factor_graph.relative_pose_factors.GetData().begin();
        for (; rel_pose_iter != factor_graph.relative_pose_factors.GetData().end(); ++rel_pose_iter)
        {
            OptionalT<BetweenFactorPose3> factor = convertRelativePoseFactor(*rel_pose_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert relative pose factors .. ";

    /* 2.10 Convert relative velocity factors */
    if (factor_graph.relative_velocity_factors)
    {
        RelativeVelocityFactors::const_iterator rel_vel_iter = factor_graph.relative_velocity_factors.GetData().begin();
        for (; rel_vel_iter != factor_graph.relative_velocity_factors.GetData().end(); ++rel_vel_iter)
        {
            OptionalT<BetweenFactorVel3> factor = convertRelativeVelocityFactor(*rel_vel_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert relative velocity factors .. ";

    /* 2.11 Convert lane factors */
    if (factor_graph.lane_factors)
    {
        LaneFactors::const_iterator lane_iter = factor_graph.lane_factors.GetData().begin();
        for (; lane_iter != factor_graph.lane_factors.GetData().end(); ++lane_iter)
        {
            OptionalT<std::vector<Smoother::Implement::GtsamLaneFactor>> lane_factors = convertLaneFactor(*lane_iter);
            if (lane_factors)
            {
                for (std::vector<Smoother::Implement::GtsamLaneFactor>::const_iterator iter =
                         lane_factors.GetData().begin();
                     iter != lane_factors->end(); iter++)
                {
                    factors.push_back(*iter);
                }
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert lane factors .. ";

    /* 2.12 Convert sign factors */
    if (factor_graph.sign_factors)
    {
        SignFactors::const_iterator sign_iter = factor_graph.sign_factors.GetData().begin();
        for (; sign_iter != factor_graph.sign_factors.GetData().end(); sign_iter++)
        {
            addSignFactor(*sign_iter, factors);
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert sign factors .. ";

    /* 2.13 Convert projection factors */
    if (factor_graph.projection_factors)
    {
        ProjectionFactors::const_iterator prj_iter = factor_graph.projection_factors.GetData().begin();
        for (; prj_iter != factor_graph.projection_factors.GetData().end(); ++prj_iter)
        {
            OptionalT<GtsamProjectionFactor> factor = convertProjectionFactor(*prj_iter, stamps);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert projection factors .. ";

    /* 2.14 Convert wheel speed factors */
    if (factor_graph.wheel_speed_factors)
    {
        WheelSpeedFactors::const_iterator ws_factor_iter = factor_graph.wheel_speed_factors.GetData().begin();
        for (; ws_factor_iter != factor_graph.wheel_speed_factors.GetData().end(); ++ws_factor_iter)
        {
            OptionalT<GtsamWheelSpeedFactor> factor = convertWheelSpeedFactor(*ws_factor_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    /* 2.15 Convert velocity factors */
    if (factor_graph.velocity_factors)
    {
        VelocityFactors::const_iterator vel_factor_iter = factor_graph.velocity_factors.GetData().begin();
        for (; vel_factor_iter != factor_graph.velocity_factors.GetData().end(); ++vel_factor_iter)
        {
            OptionalT<GtsamVelocityFactor> factor = convertVelocityFactor(*vel_factor_iter);
            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    /* 2.16 Convert camera imu extrinsic factors */
    if (factor_graph.camera_imu_extrinsic_calib_factors)
    {
        CameraImuExtrinsicCalibFactors::const_iterator cam_imu_ext_calib_iter =
            factor_graph.camera_imu_extrinsic_calib_factors.GetData().begin();
        for (; cam_imu_ext_calib_iter != factor_graph.camera_imu_extrinsic_calib_factors.GetData().end();
             ++cam_imu_ext_calib_iter)
        {
            OptionalT<GtsamCameraImuExtrinsicFactor> factor =
                convertCameraImuExtrinsicCalibFactor(*cam_imu_ext_calib_iter, stamps);

            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    /* 2.17 Convert projection line factors */
    if (factor_graph.projection_line_factors)
    {
        ProjectedLineFactors::const_iterator projection_line_iter =
            factor_graph.projection_line_factors.GetData().begin();
        for (; projection_line_iter != factor_graph.projection_line_factors.GetData().end(); ++projection_line_iter)
        {
            std::vector<Smoother::Implement::GtsamProjectionLineFactor> projection_line_factors =
                convertProjectionLineFactor(*projection_line_iter);

            if (!projection_line_factors.empty())
            {
                for (std::vector<Smoother::Implement::GtsamProjectionLineFactor>::const_iterator iter =
                         projection_line_factors.begin();
                     iter != projection_line_factors.end(); iter++)
                {
                    factors.push_back(*iter);
                }
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert camera imu extrinsic calib factors .. ";

    /* 2.18 Convert imu body extrinsic factors */
    if (factor_graph.imu_body_extrinsic_calib_factors)
    {
        ImuBodyExtrinsicCalibFactors::const_iterator imu_body_ext_calib_iter =
            factor_graph.imu_body_extrinsic_calib_factors.GetData().begin();
        for (; imu_body_ext_calib_iter != factor_graph.imu_body_extrinsic_calib_factors.GetData().end();
             ++imu_body_ext_calib_iter)
        {
            OptionalT<GtsamImuBodyExtrinsicFactor> factor =
                convertImuBodyExtrinsicCalibFactor(*imu_body_ext_calib_iter, stamps);

            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert imu body extrinsic calib factors .. ";

    /* 2.19 Convert gnss position velocity factors */
    if (factor_graph.gnss_position_velocity_factors)
    {
        GnssPositionVelocityFactors::const_iterator gnss_position_velocity_iter =
            factor_graph.gnss_position_velocity_factors.GetData().begin();
        for (; gnss_position_velocity_iter != factor_graph.gnss_position_velocity_factors.GetData().end();
             ++gnss_position_velocity_iter)
        {
            OptionalT<GtsamGnssPositionVelocityFactor> factor =
                convertGnssPositionVelocityFactor(*gnss_position_velocity_iter);

            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert gnss position velocity factors .. ";

    /* 2.20 Convert prior rpy factors */
    if (factor_graph.prior_rpy_factors)
    {
        PriorRPYFactors::const_iterator prior_rpy_factor_iter = factor_graph.prior_rpy_factors.GetData().begin();

        for (; prior_rpy_factor_iter != factor_graph.prior_rpy_factors.GetData().end(); ++prior_rpy_factor_iter)
        {
            OptionalT<GtsamPriorRPYFactor> factor = convertPriorRPYFactor(*prior_rpy_factor_iter);

            if (factor)
            {
                factors.push_back(*factor);
            }
        }
    }

    LOG_IF(INFO, params_.verbose) << "Finished convert prior rpy factors .. ";

    LOG_IF(INFO, params_.verbose) << "Num of all factors: " << factors.size();
    LOG_IF(INFO, params_.verbose) << "Num of stamps: " << stamps.size();
    LOG_IF(INFO, params_.verbose) << "Num of values: " << values.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::convertValues(const Values& values, FactorGraph& factor_graph) const
{
    /* reset factor graph */
    factor_graph = FactorGraph();

    Pose3Values     pose_values;
    Velocity3Values vel_values;
    ImuBiasValues   imubias_values;
    Position3Values position_values;
    Vector3Values   vector3_values;
    Rot3Values      rot3_values;

    Values::const_iterator iter = values.begin();
    for (; iter != values.end(); ++iter)
    {
        GTSymbol symbol(iter->key);
        if (symbol.chr() == 'x')
        {
            Pose3Value pose_value;
            pose_value.symbol.value_type = ValueType::POSE3;
            pose_value.symbol.index      = symbol.index();
            pose_value.state             = Pose3Type(convertToHoloMatrix<4u, 4u>(iter->value.cast<GTPose3>().matrix()));

            if (params_.get_covariance_matrix)
            {
                pose_value.covariance_matrix =
                    convertCovarianceMatrixOrder(convertToHoloMatrix<6u, 6u>(smoother_->marginalCovariance(iter->key)));
            }

            pose_values.push_back(pose_value);
        }
        else if (symbol.chr() == 'v')
        {
            Velocity3Value vel_value;
            vel_value.symbol.value_type = ValueType::VELOCITY3;
            vel_value.symbol.index      = symbol.index();
            vel_value.state             = convertToHoloMatrix<3u, 1u>(iter->value.cast<GTVector3>());

            if (params_.get_covariance_matrix)
            {
                vel_value.covariance_matrix = convertToHoloMatrix<3u, 3u>(smoother_->marginalCovariance(iter->key));
            }

            vel_values.push_back(vel_value);
        }
        else if (symbol.chr() == 'b')
        {
            ImuBiasValue imubias_value;
            imubias_value.symbol.value_type = ValueType::IMUBIAS;
            imubias_value.symbol.index      = symbol.index();
            const ConstantBias imubias      = iter->value.cast<ConstantBias>();
            imubias_value.state.SetAngularVelocityBias(Point3Type(convertToHoloMatrix<3u, 1u>(imubias.gyroscope())));
            imubias_value.state.SetLinearAccelerationBias(
                Point3Type(convertToHoloMatrix<3u, 1u>(imubias.accelerometer())));

            if (params_.get_covariance_matrix)
            {
                imubias_value.covariance_matrix = convertToHoloMatrix<6u, 6u>(smoother_->marginalCovariance(iter->key));
            }

            imubias_values.push_back(imubias_value);
        }
        else if (symbol.chr() == 'l')
        {
            Position3Value position_value;
            position_value.symbol.value_type = ValueType::POSITION3;
            position_value.symbol.index      = symbol.index();
            position_value.state = Point3Type(convertToHoloMatrix<3u, 1u>(GTVector3(iter->value.cast<GTPoint3>())));

            if (params_.get_covariance_matrix)
            {
                position_value.covariance_matrix =
                    convertToHoloMatrix<3u, 3u>(smoother_->marginalCovariance(iter->key));
            }

            position_values.push_back(position_value);
        }
        else if (symbol.chr() == 't')
        {
            Vector3Value vector3_value;
            vector3_value.symbol.value_type = ValueType::VECTOR3;
            vector3_value.symbol.index      = symbol.index();
            vector3_value.state             = Vector3Type(convertToHoloMatrix<3u, 1u>(iter->value.cast<GTVector3>()));

            if (params_.get_covariance_matrix)
            {
                vector3_value.covariance_matrix = convertToHoloMatrix<3u, 3u>(smoother_->marginalCovariance(iter->key));
            }

            vector3_values.push_back(vector3_value);
        }
        else if (symbol.chr() == 'e')
        {
            Rot3Value rot3_value;
            rot3_value.symbol.value_type = ValueType::ROT3;
            rot3_value.symbol.index      = symbol.index();
            rot3_value.state             = Rot3Type(convertToHoloMatrix<3u, 3u>(iter->value.cast<GTRot3>().matrix()));

            if (params_.get_covariance_matrix)
            {
                rot3_value.covariance_matrix = convertToHoloMatrix<3u, 3u>(smoother_->marginalCovariance(iter->key));
            }

            rot3_values.push_back(rot3_value);
        }
        else
        {
            LOG(WARNING) << "the type of value doesn't defined in the smoother .. ";
        }
    }

    factor_graph.pose_values     = OptionalT<Pose3Values>(pose_values);
    factor_graph.velocity_values = OptionalT<Velocity3Values>(vel_values);
    factor_graph.imu_bias_values = OptionalT<ImuBiasValues>(imubias_values);
    factor_graph.position_values = OptionalT<Position3Values>(position_values);
    factor_graph.vector3_values  = OptionalT<Vector3Values>(vector3_values);
    factor_graph.rot3_values     = OptionalT<Rot3Values>(rot3_values);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::convertPose3Values(const Values& values, Pose3Values& pose_values) const
{
    Pose3Values::iterator pose_iter = pose_values.begin();
    for (; pose_iter != pose_values.end(); ++pose_iter)
    {
        const Key k = Key(pose_iter->symbol.index);
        if (values.exists(X(k)))
        {
            pose_iter->state = Pose3Type(convertToHoloMatrix<4u, 4u>(values.at<GTPose3>(X(k)).matrix()));

            if (params_.get_covariance_matrix)
            {
                pose_iter->covariance_matrix =
                    convertCovarianceMatrixOrder(convertToHoloMatrix<6u, 6u>(smoother_->marginalCovariance(X(k))));
            }
        }
        else
        {
            LOG(WARNING) << "the pose value doesn't exist in factor graph, skip to get value ..";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::convertVelocity3Values(const Values& values, Velocity3Values& velocity_values) const
{
    Velocity3Values::iterator vel_iter = velocity_values.begin();
    for (; vel_iter != velocity_values.end(); ++vel_iter)
    {
        const Key k = Key(vel_iter->symbol.index);
        if (values.exists(V(k)))
        {
            vel_iter->state = convertToHoloMatrix<3u, 1u>(values.at<GTVector3>(V(k)));

            if (params_.get_covariance_matrix)
            {
                vel_iter->covariance_matrix = convertToHoloMatrix<3u, 3u>(smoother_->marginalCovariance(V(k)));
            }
        }
        else
        {
            LOG(WARNING) << "the velocity value doesn't exist in factor graph, skip to get value ..";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::convertImuBiasValues(const Values& values, ImuBiasValues& imu_bias_values) const
{
    ImuBiasValues::iterator bias_iter = imu_bias_values.begin();
    for (; bias_iter != imu_bias_values.end(); ++bias_iter)
    {
        const Key k = Key(bias_iter->symbol.index);
        if (values.exists(B(k)))
        {
            const ConstantBias imubias = values.at<ConstantBias>(B(k));
            bias_iter->state.SetAngularVelocityBias(Point3Type(convertToHoloMatrix<3u, 1u>(imubias.gyroscope())));
            bias_iter->state.SetLinearAccelerationBias(
                Point3Type(convertToHoloMatrix<3u, 1u>(imubias.accelerometer())));

            if (params_.get_covariance_matrix)
            {
                bias_iter->covariance_matrix = convertToHoloMatrix<6u, 6u>(smoother_->marginalCovariance(B(k)));
            }
        }
        else
        {
            LOG(WARNING) << "the imu bias value doesn't exist in factor graph, skip to get value ..";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::convertPosition3Values(const Values& values, Position3Values& position_values) const
{
    Position3Values::iterator lm_iter = position_values.begin();
    for (; lm_iter != position_values.end(); ++lm_iter)
    {
        const Key k = Key(lm_iter->symbol.index);
        if (values.exists(L(k)))
        {
            lm_iter->state = Point3Type(convertToHoloMatrix<3u, 1u>(GTVector3(values.at<GTPoint3>(L(k)))));

            if (params_.get_covariance_matrix)
            {
                lm_iter->covariance_matrix = convertToHoloMatrix<3u, 3u>(smoother_->marginalCovariance(L(k)));
            }
        }
        else
        {
            LOG(WARNING) << "the position value doesn't exist in factor graph, skip to get value ..";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::convertVector3Values(const Values& values, Vector3Values& vector3_values) const
{
    Vector3Values::iterator vec3_iter = vector3_values.begin();
    for (; vec3_iter != vector3_values.end(); ++vec3_iter)
    {
        const Key k = Key(vec3_iter->symbol.index);
        if (values.exists(T(k)))
        {
            vec3_iter->state = Vector3Type(convertToHoloMatrix<3u, 1u>(values.at<GTVector3>(T(k))));

            if (params_.get_covariance_matrix)
            {
                vec3_iter->covariance_matrix = convertToHoloMatrix<3u, 3u>(smoother_->marginalCovariance(T(k)));
            }
        }
        else
        {
            LOG(WARNING) << "the vector3 value doesn't exist in factor graph, skip to get value ..";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::convertRot3Values(const Values& values, Rot3Values& rot3_values) const
{
    Rot3Values::iterator rot3_iter = rot3_values.begin();
    for (; rot3_iter != rot3_values.end(); ++rot3_iter)
    {
        const Key k = Key(rot3_iter->symbol.index);
        if (values.exists(E(k)))
        {
            rot3_iter->state = Rot3Type(convertToHoloMatrix<3u, 3u>(values.at<GTRot3>(E(k)).matrix()));

            if (params_.get_covariance_matrix)
            {
                rot3_iter->covariance_matrix = convertToHoloMatrix<3u, 3u>(smoother_->marginalCovariance(E(k)));
            }
        }
        else
        {
            LOG(WARNING) << "the rot3 value doesn't exist in factor graph, skip to get value ..";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Implement::optimizeFactorGraph(const NonlinearFactorGraph& factors, const Values& values,
                                              const KeyTimestampMap& stamps, SmootherState& result)
{
    FixedLagSmoother::Result res = smoother_->update(factors, values, stamps);

    /* when smoother type is incremental, optionally perform multiple ISAM2
     * iterations*/
    for (uint8_t i = 0u; i < params_.additional_iterations; ++i)
    {
        smoother_->update();
    }

    /* logging smoother info */
    LOG_IF(INFO, params_.verbose) << " iterations: " << res.getIterations()
                                  << "\t intermediate steps: " << res.getIntermediateSteps()
                                  << "\t num of non-linear variables: " << res.getNonlinearVariables()
                                  << "\t num of linear variables: " << res.getLinearVariables()
                                  << "\t final error: " << res.getError();

    /* TODO: currently compute all of values in the lag */
    Values estimated_values = smoother_->calculateEstimate();

    /* Compute factor error */
    /* @todo (lichao@holomatic.com) get all factors for debug and visualization using */
    LOG_IF(INFO, params_.verbose) << "optimization result size: " << estimated_values.size();

    if (params_.get_all_values)
    {
        convertValues(estimated_values, result.factor_graph);
    }
    else
    {
        /* Get optimized pose values */
        if (result.factor_graph.pose_values)
        {
            Pose3Values pose_values = result.factor_graph.pose_values.GetData();
            convertPose3Values(estimated_values, pose_values);
            result.factor_graph.pose_values = OptionalT<Pose3Values>(pose_values);
        }

        /* Get optimized velocity values */
        if (result.factor_graph.velocity_values)
        {
            Velocity3Values velocity_values = result.factor_graph.velocity_values.GetData();
            convertVelocity3Values(estimated_values, velocity_values);
            result.factor_graph.velocity_values = OptionalT<Velocity3Values>(velocity_values);
        }

        /* Get optimized imubias values */
        if (result.factor_graph.imu_bias_values)
        {
            ImuBiasValues imu_bias_values = result.factor_graph.imu_bias_values.GetData();
            convertImuBiasValues(estimated_values, imu_bias_values);
            result.factor_graph.imu_bias_values = OptionalT<ImuBiasValues>(imu_bias_values);
        }

        /* Get optimized position values */
        if (result.factor_graph.position_values)
        {
            Position3Values position_values = result.factor_graph.position_values.GetData();
            convertPosition3Values(estimated_values, position_values);
            result.factor_graph.position_values = OptionalT<Position3Values>(position_values);
        }

        /* Get optimized vector3 values */
        if (result.factor_graph.vector3_values)
        {
            Vector3Values vector3_values = result.factor_graph.vector3_values.GetData();
            convertVector3Values(estimated_values, vector3_values);
            result.factor_graph.vector3_values = OptionalT<Vector3Values>(vector3_values);
        }

        /* Get optimized rot3 values */
        if (result.factor_graph.rot3_values)
        {
            Rot3Values rot3_values = result.factor_graph.rot3_values.GetData();
            convertRot3Values(estimated_values, rot3_values);
            result.factor_graph.rot3_values = OptionalT<Rot3Values>(rot3_values);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<SmootherState> Smoother::Implement::Run(const FactorGraph& factor_graph)
{
    SmootherState result;

    /* Step1, Convert holo::FactorGraph to gtsam::FactorGraph and gtsam::Values */
    /* Create container of factors */
    gtsam::NonlinearFactorGraph new_factors;

    /* Create container of linearization points */
    gtsam::Values new_values;

    /* key_timestamp map */
    std::map<gtsam::Key, float64_t> new_timestamps;

    convertFactorGraph(factor_graph, new_factors, new_values, new_timestamps);

    /* Step2, Optimization */
    result.factor_graph = factor_graph;

    /* catch gtsam indeterminant linear system exception */
    try
    {
        optimizeFactorGraph(new_factors, new_values, new_timestamps, result);
    }
    catch (gtsam::IndeterminantLinearSystemException& e)
    {
        LOG(ERROR) << "GTSAM Indeterminant Linear System Exception: " << e.what();
        return OptionalT<SmootherState>();
    }
    catch (gtsam::InconsistentEliminationRequested& e)
    {
        LOG(ERROR) << "GTSAM Inconsistent Elimination Requested Exception: " << e.what();
        return OptionalT<SmootherState>();
    }

    return OptionalT<SmootherState>(result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Smoother::Implement::ISAM2Params Smoother::Implement::createIsam2Parameters() const
{
    ISAM2Params params;

    if (params_.optimizer_type == SmootherParameters::OptimizerType::DOGLEG)
    {
        params.setOptimizationParams(gtsam::ISAM2DoglegParams());
    }
    else
    {
        params.setOptimizationParams(gtsam::ISAM2GaussNewtonParams());
    }

    params.setRelinearizeThreshold(params_.relinearize_threshold);
    params.setRelinearizeSkip(params_.relinearize_skip);
    params.findUnusedFactorSlots = params_.find_unused_factor_slots;
    return params;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Smoother::Smoother(const Parameters params) : params_(params), impl_(new Implement(params_))
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Smoother::~Smoother()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Smoother::Smoother(Smoother&&) noexcept = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Smoother& Smoother::operator=(Smoother&&) noexcept = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Smoother::Smoother(const Smoother& smoother) : params_(smoother.params_), impl_(new Implement(*smoother.impl_))
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Smoother& Smoother::operator=(const Smoother& smoother)
{
    if (this != &smoother)
    {
        this->impl_.reset(new Implement(*smoother.impl_));
        this->params_ = smoother.params_;
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OptionalT<SmootherState> Smoother::Run(const FactorGraph& factor_graph)
{
    return impl_->Run(factor_graph);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smoother::Reset()
{
    impl_->Reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MatrixXType Smoother::GetMarginalCovariance(const Symbol& symbol) const
{
    return impl_->GetMarginalCovariance(symbol);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MatrixXType Smoother::GetMarginalCovariance(const std::vector<Symbol>& symbols) const
{
    return impl_->GetMarginalCovariance(symbols);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}  // namespace localization

}  // namespace holo
