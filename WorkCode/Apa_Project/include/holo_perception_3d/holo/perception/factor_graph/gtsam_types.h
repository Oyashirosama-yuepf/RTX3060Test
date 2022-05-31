/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gtsam_types.h
 * @brief This header file defines basic types used in gtsam.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2021-06-01"
 */

#ifndef HOLO_PERCEPTION_3D_FACTOR_GRAPH_GTSAM_TYPES_H_
#define HOLO_PERCEPTION_3D_FACTOR_GRAPH_GTSAM_TYPES_H_

#include <gtsam/geometry/CalibratedCamera.h>
#include <gtsam/geometry/Point2.h>
#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/geometry/SimpleCamera.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam_unstable/nonlinear/BatchFixedLagSmoother.h>
#include <gtsam_unstable/nonlinear/IncrementalFixedLagSmoother.h>

#include <holo/common/optional.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/perception/common/box_object.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////
// @brief define gtsam variables
////////////////////////////////////////////////////////////////////////////////

using Scalar    = holo::float32_t;
using Timestamp = holo::common::Timestamp;
using Object    = BoxObjectT<Scalar, 128U>;

using gtsam::Cal3_S2;
using gtsam::Key;
using gtsam::Matrix;
using gtsam::Matrix1;
using gtsam::Matrix13;
using gtsam::Matrix22;
using gtsam::Matrix23;
using gtsam::Matrix3;
using gtsam::Matrix33;
using gtsam::Point2;
using gtsam::Point3;
using gtsam::Pose3;
using gtsam::Rot3;
using gtsam::Vector;
using gtsam::Vector1;
using gtsam::Vector2;
using gtsam::Vector3;
using gtsam::Vector4;

using gtsam::GaussNewtonOptimizer;
using gtsam::GaussNewtonParams;
using gtsam::LevenbergMarquardtOptimizer;
using gtsam::LevenbergMarquardtParams;
using gtsam::NonlinearFactorGraph;
using gtsam::PinholeBase;
using gtsam::SharedNoiseModel;
using gtsam::Values;

using gtsam::BatchFixedLagSmoother;
using gtsam::IncrementalFixedLagSmoother;
using gtsam::ISAM2Params;
using KeyTimestampMap      = gtsam::FixedLagSmoother::KeyTimestampMap;
using PriorDimensionFactor = gtsam::PriorFactor<Vector3>;
using PriorYawFactor       = gtsam::PriorFactor<Vector1>;

using gtsam::symbol_shorthand::D;
using gtsam::symbol_shorthand::V;
using gtsam::symbol_shorthand::X;
using gtsam::symbol_shorthand::Y;

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_FACTOR_GRAPH_GTSAM_TYPES_H_
