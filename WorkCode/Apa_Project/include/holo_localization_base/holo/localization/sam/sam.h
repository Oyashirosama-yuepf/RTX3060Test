/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sam.h
 * @brief this file defines gtsam elements used in localization
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-02-18"
 */

#ifndef HOLO_LOCALIZATION_SAM_SAM_H_
#define HOLO_LOCALIZATION_SAM_SAM_H_

#include <gtsam/base/FastList.h>
#include <gtsam/base/FastMap.h>
#include <gtsam/base/FastSet.h>
#include <gtsam/base/FastVector.h>
#include <gtsam/base/GenericValue.h>
#include <gtsam/base/Matrix.h>
#include <gtsam/base/OptionalJacobian.h>
#include <gtsam/base/Testable.h>
#include <gtsam/base/Value.h>
#include <gtsam/base/Vector.h>

#include <gtsam/geometry/Cal3_S2.h>
#include <gtsam/geometry/CalibratedCamera.h>
#include <gtsam/geometry/PinholeCamera.h>
#include <gtsam/geometry/PinholePose.h>
#include <gtsam/geometry/Point2.h>
#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/geometry/Rot3.h>
#include <gtsam/geometry/SimpleCamera.h>

#include <gtsam/inference/Factor.h>
#include <gtsam/inference/FactorGraph.h>
#include <gtsam/inference/Key.h>
#include <gtsam/inference/Symbol.h>

#include <gtsam/linear/GaussianFactor.h>
#include <gtsam/linear/GaussianFactorGraph.h>
#include <gtsam/linear/JacobianFactor.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/linear/VectorValues.h>

#include <gtsam/navigation/GPSFactor.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/navigation/NavState.h>

#include <gtsam/nonlinear/DoglegOptimizer.h>
#include <gtsam/nonlinear/DoglegOptimizerImpl.h>
#include <gtsam/nonlinear/ExpressionFactor.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/ISAM2Params.h>
#include <gtsam/nonlinear/ISAM2Result.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/LevenbergMarquardtParams.h>
#include <gtsam/nonlinear/Marginals.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>

#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/slam/ProjectionFactor.h>
#include <gtsam/slam/expressions.h>

#include <gtsam_unstable/nonlinear/BatchFixedLagSmoother.h>
#include <gtsam_unstable/nonlinear/FixedLagSmoother.h>
#include <gtsam_unstable/nonlinear/IncrementalFixedLagSmoother.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// base type
using GTScalar = double;

template <typename T>
using GTFastList = gtsam::FastList<T>;

template <typename KEY, typename T>
using GTFastMap = gtsam::FastMap<KEY, T>;

template <typename T>
using GTFastSet = gtsam::FastSet<T>;

template <typename T>
using GTFastVector = gtsam::FastVector<T>;

template <class T>
using GTGenericValue = gtsam::GenericValue<T>;

using GTMatrix    = gtsam::Matrix;
using GTRowMatrix = gtsam::MatrixRowMajor;
using GTMatrix2   = gtsam::Matrix2;
using GTMatrix3   = gtsam::Matrix3;
using GTMatrix4   = gtsam::Matrix4;
using GTMatrix6   = gtsam::Matrix6;
using GTMatrix9   = gtsam::Matrix9;

template <int Rows, int Cols>
using GTOptionalJacobian = gtsam::OptionalJacobian<Rows, Cols>;

using GTDynamicOptionalJacobian = gtsam::OptionalJacobian<Eigen::Dynamic, Eigen::Dynamic>;

template <typename T>
using GTIsTestable = gtsam::IsTestable<T>;

template <typename T>
using GTTestable = gtsam::Testable<T>;

using GTValue = gtsam::Value;

using GTVector  = gtsam::Vector;
using GTVector2 = gtsam::Vector2;
using GTVector3 = gtsam::Vector3;
using GTVector4 = gtsam::Vector4;
using GTVector6 = gtsam::Vector6;
using GTVector9 = gtsam::Vector9;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// geometry type
using GTCal3_S2             = gtsam::Cal3_S2;
using GTCheiralityException = gtsam::CheiralityException;
using GTPinholeBase         = gtsam::PinholeBase;
using GTCalibratedCamera    = gtsam::CalibratedCamera;

template <typename CALIBRATION>
using GTPinholeBaseK = gtsam::PinholeBaseK<CALIBRATION>;

template <typename CALIBRATION>
using GTPinholePose = gtsam::PinholePose<CALIBRATION>;

template <typename CALIBRATION>
using GTPinholeCamera = gtsam::PinholeCamera<CALIBRATION>;

using GTSimpleCamera = gtsam::SimpleCamera;

using GTPoint2 = gtsam::Point2;
using GTPoint3 = gtsam::Point3;
using GTPose3  = gtsam::Pose3;
using GTRot3   = gtsam::Rot3;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// inference type
using GTFactor = gtsam::Factor;

template <typename FACTOR>
using GTFactorGraph = gtsam::FactorGraph<FACTOR>;

using GTKey                = gtsam::Key;
using GTKeyList            = gtsam::KeyList;
using GTKeySet             = gtsam::KeySet;
using GTKeyGroupMap        = gtsam::KeyGroupMap;
using GTSymbol             = gtsam::Symbol;
namespace symbol_shorthand = gtsam::symbol_shorthand;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// linear type
using GTGaussianFactor      = gtsam::GaussianFactor;
using GTGaussianFactorGraph = gtsam::GaussianFactorGraph;
using GTJacobianFactor      = gtsam::JacobianFactor;
using GTGaussian            = gtsam::noiseModel::Gaussian;
using GTDiagonal            = gtsam::noiseModel::Diagonal;
using GTConstrained         = gtsam::noiseModel::Constrained;
using GTIsotropic           = gtsam::noiseModel::Isotropic;
using GTUnit                = gtsam::noiseModel::Unit;
using GTHuber               = gtsam::noiseModel::mEstimator::Huber;
using GTFair                = gtsam::noiseModel::mEstimator::Fair;
using GTCauchy              = gtsam::noiseModel::mEstimator::Cauchy;
using GTRobust              = gtsam::noiseModel::Robust;
using GTSharedNoiseModel    = gtsam::noiseModel::Base::shared_ptr;
using GTVectorValues        = gtsam::VectorValues;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// navigation type
using GTGPSFactor                    = gtsam::GPSFactor;
using GTGPSFactor2                   = gtsam::GPSFactor2;
using GTConstantBias                 = gtsam::imuBias::ConstantBias;
using GTPreintegrationParams         = gtsam::PreintegrationParams;
using GTPreintegratedImuMeasurements = gtsam::PreintegratedImuMeasurements;
using GTImuFactor                    = gtsam::ImuFactor;
using GTImuFactor2                   = gtsam::ImuFactor2;
using GTVelocity3                    = gtsam::Velocity3;
using GTNavState                     = gtsam::NavState;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// nonlinear type
using GTDoglegParams                = gtsam::DoglegParams;
using GTDoglegOptimizer             = gtsam::DoglegOptimizer;
using GTDoglegOptimizerImpl         = gtsam::DoglegOptimizerImpl;
using GTGaussNewtonParams           = gtsam::GaussNewtonParams;
using GTGaussNewtonOptimizer        = gtsam::GaussNewtonOptimizer;
using GTISAM2                       = gtsam::ISAM2;
using GTISAM2Params                 = gtsam::ISAM2Params;
using GTISAM2GaussNewtonParams      = gtsam::ISAM2GaussNewtonParams;
using GTISAM2DoglegParams           = gtsam::ISAM2DoglegParams;
using GTISAM2Result                 = gtsam::ISAM2Result;
using GTLevenbergMarquardtParams    = gtsam::LevenbergMarquardtParams;
using GTLevenbergMarquardtOptimizer = gtsam::LevenbergMarquardtOptimizer;
using GTMarginals                   = gtsam::Marginals;
using GTJointMarginal               = gtsam::JointMarginal;
using GTNonlinearFactor             = gtsam::NonlinearFactor;
using GTNoiseModelFactor            = gtsam::NoiseModelFactor;

template <typename T>
using GTNoiseModelFactor1 = gtsam::NoiseModelFactor1<T>;

template <typename T1, typename T2>
using GTNoiseModelFactor2 = gtsam::NoiseModelFactor2<T1, T2>;

template <typename T1, typename T2, typename T3>
using GTNoiseModelFactor3 = gtsam::NoiseModelFactor3<T1, T2, T3>;

template <typename T1, typename T2, typename T3, typename T4>
using GTNoiseModelFactor4 = gtsam::NoiseModelFactor4<T1, T2, T3, T4>;

template <typename T1, typename T2, typename T3, typename T4, typename T5>
using GTNoiseModelFactor5 = gtsam::NoiseModelFactor5<T1, T2, T3, T4, T5>;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
using GTNoiseModelFactor6 = gtsam::NoiseModelFactor6<T1, T2, T3, T4, T5, T6>;

using GTNonlinearFactorGraph = gtsam::NonlinearFactorGraph;
using GTValues               = gtsam::Values;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// slam type
template <typename T>
using GTBetweenFactor = gtsam::BetweenFactor<T>;

template <typename T>
using GTBetweenConstraint = gtsam::BetweenConstraint<T>;

template <typename T>
using GTPriorFactor = gtsam::PriorFactor<T>;

template <class POSE, class LANDMARK, class CALIBRATION = gtsam::Cal3_S2>
using GTGenericProjectionFactor = gtsam::GenericProjectionFactor<POSE, LANDMARK, CALIBRATION>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// unstable nonlinear type
using GTBatchFixedLagSmoother       = gtsam::BatchFixedLagSmoother;
using GTFixedLagSmoother            = gtsam::FixedLagSmoother;
using GTIncrementalFixedLagSmoother = gtsam::IncrementalFixedLagSmoother;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_SAM_H_
