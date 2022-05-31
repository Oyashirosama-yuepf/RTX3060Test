/*!
 * \brief SEMANTIC parking slot plane factor header file
 * \author Changsong Yu, yuchangsong@holomatic.com
 * \author Changxi Cheng, chengchangxi@holomatic.com
 * \date March-10-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_POINT_PLANE_FACTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_POINT_PLANE_FACTOR_H_

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief semantic slam parking slot point plane factor
 * @details error = x * A + y * B + z * C - D
 *          (x, y, z) represents point in world coordinate, estimated values
 *          A, B, C, D are parameters of the plane in world coordinate, estimated values
 */

class ParkingSlotPointPlaneFactor : public gtsam::NoiseModelFactor2<gtsam::Point3, gtsam::OrientedPlane3>
{
public:
    /**
     * @brief smart pointer
     */
    typedef boost::shared_ptr<ParkingSlotPointPlaneFactor>                 Ptr;
    typedef boost::shared_ptr<const ParkingSlotPointPlaneFactor>           ConstPtr;
    typedef gtsam::NoiseModelFactor2<gtsam::Point3, gtsam::OrientedPlane3> Base;

    /**
     * @brief Construct a new ParkingSlotPointPlaneFactor object
     *
     * @param point_key associated point variable key
     * @param plane_key associated plane variable key
     * @param model noise model for velocity sensor, in X-Y-Z
     */
    ParkingSlotPointPlaneFactor(const gtsam::Key& point_key, const gtsam::Key& plane_key,
                                const gtsam::SharedNoiseModel& model);

    /**
     * @brief deconstructor
     */
    virtual ~ParkingSlotPointPlaneFactor()
    {
    }

    /**
     * @brief error function
     *
     * @param Point point in world frame
     * @param Plane Plane in world frame
     * @param H1 the optional Jacobian matrix for point
     * @param H2 the optional Jacobian matrix for plane
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(const gtsam::Point3& point, const gtsam::OrientedPlane3& plane,
                                        boost::optional<gtsam::Matrix&> H_point = boost::none,
                                        boost::optional<gtsam::Matrix&> H_plane = boost::none) const override;

private:
};  // class ParkingSlotPointPlaneFactor

typedef ParkingSlotPointPlaneFactor::Ptr ParkingSlotPointPlaneFactorPtr;

}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_PLANE_FACTOR_H_