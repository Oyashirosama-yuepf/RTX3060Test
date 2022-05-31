/*!
 * \brief pose only unit3 factor header file
 * \author duyanwei@holomatic.com
 * \date Dec-11-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_POSE_ONLY_UNIT3_FACTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_POSE_ONLY_UNIT3_FACTOR_H_

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief VSLAM pose only uint3 factor
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
    PoseOnlyUnit3Factor(const gtsam::Point3& landmark, const gtsam::Point3& feature,
                        const gtsam::SharedNoiseModel& model, const gtsam::Key& key,
                        boost::optional<gtsam::Pose3> optional_T_bc = boost::none);

    /**
     * @brief evaluate error
     *
     * @param T_wb pose of body in world frame
     * @param H jacobian of error to pose
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3&                   T_wb,
                                        const boost::optional<gtsam::Matrix&> H = boost::none) const override;

    /**
     * @brief Get the Landmark Measurement object
     *
     * @return const gtsam::Point3& landmark measurement
     */
    const gtsam::Point3& GetLandmarkMeasurement() const
    {
        return landmark_;
    }

    /**
     * @brief Get the Feature Measurement object
     *
     * @return const gtsam::Point3& feature point measurement
     */
    const gtsam::Point3& GetFeatureMeasurement() const
    {
        return feature_;
    }

private:
    /// @brief 3D landmark of world coordinate
    gtsam::Point3 landmark_;

    /// @brief 2D feature measurement of normalized coordinate (on normalized plane. z == 1)
    gtsam::Point3 feature_;

    /// @brief extrinsic parameters
    boost::optional<gtsam::Pose3> optional_T_bc_;

};  // class PoseOnlyUnit3Factor
typedef PoseOnlyUnit3Factor::Ptr PoseOnlyUnit3FactorPtr;

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_POSE_ONLY_UNIT3_FACTOR_H_
