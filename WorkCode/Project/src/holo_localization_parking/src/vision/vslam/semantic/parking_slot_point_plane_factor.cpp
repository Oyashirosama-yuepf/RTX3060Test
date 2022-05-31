/*!
 * \brief semantic parking slot point plane factor in vslam
 * \author Changsong Yu, yuchangsong@holomatic.com
 * \author Changxi Cheng, chengchangxi@holomatic.com
 * \date March-10-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/semantic/parking_slot_point_plane_factor.h>

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
ParkingSlotPointPlaneFactor::ParkingSlotPointPlaneFactor(const gtsam::Key& point_key, const gtsam::Key& plane_key,
                                                         const gtsam::SharedNoiseModel& model)
  : Base(model, point_key, plane_key)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector ParkingSlotPointPlaneFactor::evaluateError(const gtsam::Point3& point, const gtsam::OrientedPlane3& plane,
                                                         boost::optional<gtsam::Matrix&> H_point,
                                                         boost::optional<gtsam::Matrix&> H_plane) const
{
    const gtsam::Unit3 normal   = plane.normal();
    const double       distance = plane.distance();

    gtsam::Vector error(1);

    if (H_point)
    {
        *H_point = normal.unitVector().transpose();
    }

    if (H_plane)
    {
        // A, B, C has two and D has one degrees of freedom
        gtsam::Matrix43 H_plane_retract;
        H_plane_retract << normal.basis(), gtsam::Vector3::Zero(), 0, 0, 1;
        gtsam::Vector4 p;
        p << point, -1;
        *H_plane = p.transpose() * H_plane_retract;
    }

    error << point.dot(normal.unitVector()) - distance;
    return error;
}
}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo