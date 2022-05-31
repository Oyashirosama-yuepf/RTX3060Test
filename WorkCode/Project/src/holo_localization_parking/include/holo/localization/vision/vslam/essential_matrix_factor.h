/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file essential_matrix_factor.h
 * @brief This header file defines essential matrix factor
 * @author Lifeng(lifeng@holomaitc.com)
 * @date "Jan-03-2022"
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_ESSENTIAL_MATRIX_FACTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_ESSENTIAL_MATRIX_FACTOR_H_

#include <gtsam/geometry/EssentialMatrix.h>
#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @addtogroup vslam
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief this class measures the error between two pose
 */
class EssentialMatrixFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3>
{
public:
    /**
     * @brief define smart pointer
     */
    typedef boost::shared_ptr<EssentialMatrixFactor>             Ptr;
    typedef boost::shared_ptr<const EssentialMatrixFactor>       ConstPtr;
    typedef gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3> Base;

    /**
     * @brief Construct a new Unit3Factor object
     *
     * @param feature feature measurement in normalized coordinate
     * @param model noise model
     * @param pose_key key of estimated pose
     * @param landmark_key key of estimated landmark
     * @param optional_T_bc transform from body to sensor frame (default identity)
     */
    EssentialMatrixFactor(const gtsam::Point3& p1, const gtsam::Point3& p2, const gtsam::Key& pose1_key,
                          const gtsam::Key& pose2_key, const gtsam::SharedNoiseModel& model,
                          const boost::optional<gtsam::Pose3>& optional_T_bc = boost::none);

    /**
     * @brief evaluate error
     *
     * @param T_wb pose of body in world frame
     * @param landmark landmark in world frame
     * @param H_pose jacobian of error to pose (2x6)
     * @param H_landmark jacobian of error to landmark (2x3)
     * @return gtsam::Vector contain the evaluated error(2x1)
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3& wTb1, const gtsam::Pose3& wTb2,
                                        const boost::optional<gtsam::Matrix&> H_pose1 = boost::none,
                                        const boost::optional<gtsam::Matrix&> H_pose2 = boost::none) const override;

    /**
     * @brief get feature point measurement
     *
     * @return feature point measurement
     */
    const gtsam::Point3& GetFeatureMeasurement1() const noexcept
    {
        return p1_;
    }

    /**
     * @brief get feature point measurement
     *
     * @return feature point measurement
     */
    const gtsam::Point3& GetFeatureMeasurement2() const noexcept
    {
        return p2_;
    }

private:
    gtsam::Point3 p1_;  ///< 3D feature measurement of normalized coordinate.(on normalized plane. z == 1)
    gtsam::Point3 p2_;  ///< 3D feature measurement of normalized coordinate.(on normalized plane. z == 1)

    boost::optional<gtsam::Pose3> optional_T_bc_;  ///< extrinsic parameters

};  // class EssentialMatrixFactor

typedef EssentialMatrixFactor::Ptr EssentialMatrixFactorPtr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief this class measures the error between two pose
 */
class EssentialMatrixFactor2 : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3>
{
public:
    /**
     * @brief define smart pointer
     */
    typedef boost::shared_ptr<EssentialMatrixFactor2>            Ptr;
    typedef boost::shared_ptr<const EssentialMatrixFactor2>      ConstPtr;
    typedef gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3> Base;

    /**
     * @brief Construct a new Unit3Factor object
     *
     * @param feature feature measurement in normalized coordinate
     * @param model noise model
     * @param pose_key key of estimated pose
     * @param landmark_key key of estimated landmark
     * @param optional_T_bc transform from body to sensor frame (default identity)
     */
    EssentialMatrixFactor2(const gtsam::EssentialMatrix& measuredE, const gtsam::Key& pose1_key,
                           const gtsam::Key& pose2_key, const gtsam::SharedNoiseModel& model,
                           const boost::optional<gtsam::Pose3>& optional_T_bc = boost::none);

    /**
     * @brief evaluate error
     *
     * @param T_wb pose of body in world frame
     * @param landmark landmark in world frame
     * @param H_pose jacobian of error to pose (2x6)
     * @param H_landmark jacobian of error to landmark (2x3)
     * @return gtsam::Vector contain the evaluated error(2x1)
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3& wTb1, const gtsam::Pose3& wTb2,
                                        const boost::optional<gtsam::Matrix&> H_pose1 = boost::none,
                                        const boost::optional<gtsam::Matrix&> H_pose2 = boost::none) const override;

    ///@brief return measured E
    const gtsam::EssentialMatrix& measured() const
    {
        return measuredE_;
    }

private:
    gtsam::EssentialMatrix        measuredE_;      /** The measurement is an essential matrix */
    boost::optional<gtsam::Pose3> optional_T_bc_;  ///< extrinsic parameters

};  // class EssentialMatrixFactor

typedef EssentialMatrixFactor2::Ptr EssentialMatrixFactor2Ptr;
/**
 * @}
 *
 */

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_ESSENTIAL_MATRIX_FACTOR_H_