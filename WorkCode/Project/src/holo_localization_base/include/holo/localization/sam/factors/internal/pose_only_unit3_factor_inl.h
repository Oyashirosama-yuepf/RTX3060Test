/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose_only_unit3_facotr_inl.h
 * @brief This header file defines pose only unit3 factor
 * @author duyanwei@holomatic.com (Yanwei Du)
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-12-06
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_POSE_ONLY_UNIT3_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_POSE_ONLY_UNIT3_FACTOR_INL_H_

#include <gtsam/geometry/Pose3.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <holo/localization/common/types.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup internal
 * @brief Pose only unit3 factor
 *
 * @details it measures the error between two directions:
 *          1, The ray obtained by project the gt landmark into the camera coordinate
 *          2, The ray from detected feature measurement in normalized coordinate to camera center
 */
class PoseOnlyUnit3Factor : public gtsam::NoiseModelFactor1<gtsam::Pose3>
{
public:
    /**
     * @brief smart pointer
     */
    typedef boost::shared_ptr<PoseOnlyUnit3Factor>       Ptr;
    typedef boost::shared_ptr<const PoseOnlyUnit3Factor> ConstPtr;
    typedef gtsam::NoiseModelFactor1<gtsam::Pose3>       Base;

    /**
     * @brief constructor a new PoseOnlyUnit3Factor object
     *
     * @param landmark landmark measurement in world coordinate
     * @param feature feature measurement in normalized coordinate (normalized plane. z == 1)
     * @param model noise model
     * @param key key of estimated pose
     * @param optional_T_bc transform from body to sensor frame (default identity)
     */
    PoseOnlyUnit3Factor(gtsam::Point3 const& landmark, gtsam::Point3 const& feature,
                        gtsam::SharedNoiseModel const& model, gtsam::Key const& key,
                        boost::optional<gtsam::Pose3> optional_bTc = boost::none);

    /**
     * @brief evaluate error
     *
     * @param wTb pose of body in world frame
     * @param H jacobian of error to pose
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const&             wTb,
                                        boost::optional<gtsam::Matrix&> H = boost::none) const override;

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

    /// @brief extrinsic parameters
    boost::optional<gtsam::Pose3> optional_bTc_;

};  // class PoseOnlyUnit3Factor
typedef PoseOnlyUnit3Factor::Ptr PoseOnlyUnit3FactorPtr;

}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_POSE_ONLY_UNIT3_FACTOR_INL_H_
