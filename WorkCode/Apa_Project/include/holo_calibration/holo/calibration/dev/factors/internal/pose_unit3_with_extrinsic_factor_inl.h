/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose_unit3_with_extrinsic_factor_inl.h
 * @brief This header file defines pose unit3 with extrinsic factor
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2022-01-21
 */

#ifndef HOLO_CLIBRATION_DEV_FACTORS_INTERNAL_POSE_UNIT3_WITH_EXTRINSIC_FACTOR_INL_H_
#define HOLO_CLIBRATION_DEV_FACTORS_INTERNAL_POSE_UNIT3_WITH_EXTRINSIC_FACTOR_INL_H_

#include <gtsam/geometry/Pose3.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <holo/localization/common/types.h>

namespace holo
{
namespace calibration
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup internal
 * @brief Pose unit3 with extrinsic factor
 *
 * @details it measures the error between two directions:
 *          1, The ray obtained by project the gt landmark into the camera coordinate
 *          2, The ray from detected feature measurement in normalized coordinate to camera center
 */
class PoseUnit3WithExtrinsicFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3>
{
public:
    /**
     * @brief smart pointer
     *
     */
    typedef boost::shared_ptr<PoseUnit3WithExtrinsicFactor>       Ptr;
    typedef boost::shared_ptr<const PoseUnit3WithExtrinsicFactor> ConstPtr;
    typedef gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3>  Base;

    /**
     * @brief constructor a new PoseUnit3WithExtrinsicFactor object
     *
     * @param landmark landmark measurement in world coordinate
     * @param feature feature measurement in normalized coordinate (normalized plane. z == 1)
     * @param model noise model
     * @param wTt key of estimated target pose in world coordinate
     * @param tTs key of estimated extrinsic - transformation from source coordinate to target coordinate
     */
    PoseUnit3WithExtrinsicFactor(gtsam::Point3 const& landmark, gtsam::Point3 const& feature,
                                 gtsam::SharedNoiseModel const& model, gtsam::Key const& wTt, gtsam::Key const& tTs);

    /**
     * @brief destructor
     *
     */
    ~PoseUnit3WithExtrinsicFactor() override = default;

    /**
     * @brief evaluate error
     *
     * @param wTt target pose in world frame
     * @param tTs extrinsic - transformation from source coordinate to target coordinate
     * @param H_pose ray error w.r.t pose
     * @param H_extrinsic ray error w.r.t extrinsic
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const& wTt, gtsam::Pose3 const& tTs,
                                        boost::optional<gtsam::Matrix&> H_pose      = boost::none,
                                        boost::optional<gtsam::Matrix&> H_extrinsic = boost::none) const override;

    /**
     * @brief Get the Landmark Measurement object
     *
     * @return const gtsam::Point3& landmark measurement
     */
    gtsam::Point3 const& GetLandmarkMeasurement() const
    {
        return landmark_;
    }

    /**
     * @brief Get the Feature Measurement object
     *
     * @return const gtsam::Point3& feature point measurement
     */
    gtsam::Point3 const& GetFeatureMeasurement() const
    {
        return feature_;
    }

private:
    /// @brief 3D landmark of world coordinate
    gtsam::Point3 landmark_;

    /// @brief 2D feature measurement of normalized coordinate (on normalized plane. z == 1)
    gtsam::Point3 feature_;

};  // class PoseUnit3WithExtrinsicFactor
using PoseUnit3WithExtrinsicFactorPtr = PoseUnit3WithExtrinsicFactor::Ptr;

}  // namespace internal
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CLIBRATION_DEV_FACTORS_INTERNAL_POSE_UNIT3_WITH_EXTRINSIC_FACTOR_INL_H_