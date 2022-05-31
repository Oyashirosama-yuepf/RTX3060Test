/*!
 * \brief parking slot parallel factor in vslam
 * \author Changsong. Yu
 * \author Changxi Cheng (chengchangxi@holomatic.com)
 * \date June-02-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/semantic/parking_slot_parallel_factor.h>

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
ParkingSlotParallelFactor::ParkingSlotParallelFactor(const gtsam::Key& vertex0_key, const gtsam::Key& vertex1_key,
                                                     const gtsam::Key& vertex2_key, const gtsam::Key& vertex3_key,
                                                     const gtsam::SharedNoiseModel& model)
  : Base(model, vertex0_key, vertex1_key, vertex2_key, vertex3_key)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector ParkingSlotParallelFactor::evaluateError(const gtsam::Point3& vertex0, const gtsam::Point3& vertex1,
                                                       const gtsam::Point3& vertex2, const gtsam::Point3& vertex3,
                                                       boost::optional<gtsam::Matrix&> H0,
                                                       boost::optional<gtsam::Matrix&> H1,
                                                       boost::optional<gtsam::Matrix&> H2,
                                                       boost::optional<gtsam::Matrix&> H3) const
{
    const gtsam::Point3 point10 = vertex1 - vertex0;
    const gtsam::Point3 point23 = vertex2 - vertex3;

    gtsam::Matrix33 H10;
    gtsam::Matrix33 H23;

    gtsam::Vector3 error = gtsam::cross(point10, point23, H10, H23);

    if (H0)
    {
        *H0 = -H10;
    }

    if (H1)
    {
        *H1 = H10;
    }

    if (H2)
    {
        *H2 = H23;
    }

    if (H3)
    {
        *H3 = -H23;
    }

    return error;
}
}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo