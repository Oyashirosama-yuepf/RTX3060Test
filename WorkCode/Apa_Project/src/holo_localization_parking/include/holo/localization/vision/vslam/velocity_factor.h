/*!
 * \brief VSLAM velocity factor header file
 * \author Yetong. Zhang, zhangyetong@holomatic.com
 * \date June-02-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_VELOCITY_FACTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_VELOCITY_FACTOR_H_

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
 * @brief vslam vehicle velocity factor
 * @details error = V_b - T_wb.TransformTo(V_w)
 */
class VelocityFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Velocity3>
{
public:
    /**
     * @brief smart pointer
     */
    typedef boost::shared_ptr<VelocityFactor>                        Ptr;
    typedef boost::shared_ptr<const VelocityFactor>                  ConstPtr;
    typedef gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Velocity3> Base;

    /**
     * @brief Construct a new VelocityFactor object
     *
     * @param pose_key associated pose variable key
     * @param velocity_key associated velocity variable key
     * @param measurement Velocity3 measurement in body frame
     * @param model noise model for velocity snesor, in X-Y-Z
     */
    VelocityFactor(const gtsam::Key& pose_key, const gtsam::Key& velocity_key, const gtsam::Velocity3& measurement,
                   const gtsam::SharedNoiseModel& model);

    /**
     * @brief Get the Velocity Measurement object
     *
     * @return const gtsam::Velocity3&
     */
    const gtsam::Velocity3& GetVelocityMeasurement() const;

    /**
     * @brief error function
     *
     * @param T_wb body pose in world frame
     * @param V_w the velocity in world frame
     * @param H1 the optional Jacobian matrix for pose
     * @param H2 the optional Jacobian matrix for velocity
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3& T_wb, const gtsam::Velocity3& V_w,
                                        boost::optional<gtsam::Matrix&> H1 = boost::none,
                                        boost::optional<gtsam::Matrix&> H2 = boost::none) const override;

private:
    /// @brief measurement velocity in body frame
    gtsam::Velocity3 measurement_;
};  // class VelocityFactor

typedef VelocityFactor::Ptr VelocityFactorPtr;

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_VELOCITY_FACTOR_H_
