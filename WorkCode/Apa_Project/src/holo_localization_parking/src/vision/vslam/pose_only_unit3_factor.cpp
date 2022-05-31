/*!
 * \brief pose only unit3 factor implementation file
 * \author duyanwei@holomatic.com
 * \date Dec-11-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/pose_only_unit3_factor.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseOnlyUnit3Factor::PoseOnlyUnit3Factor(const gtsam::Point3& landmark, const gtsam::Point3& feature,
                                         const gtsam::SharedNoiseModel& model, const gtsam::Key& key,
                                         boost::optional<gtsam::Pose3> optional_T_bc)
  : Base(model, key), landmark_(landmark), feature_(feature), optional_T_bc_(optional_T_bc)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector PoseOnlyUnit3Factor::evaluateError(const gtsam::Pose3&                   T_wb,
                                                 const boost::optional<gtsam::Matrix&> H) const
{
    // construct camera pose
    gtsam::Pose3  T_wc(T_wb);
    gtsam::Matrix H0;  // 6x6

    if (optional_T_bc_)
    {
        T_wc = T_wb.compose(*optional_T_bc_, H0);
    }

    // transform landmark to camera frame
    gtsam::Matrix       H1;  // 3x6
    const gtsam::Point3 ptc = T_wc.transform_to(landmark_, H1);

    // construct Unit3 from landmark
    gtsam::Matrix      H2;  // 2 x 3
    const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(ptc, H2);

    // construct Unit3 from feature point
    const gtsam::Unit3 p(feature_);

    // compute error
    gtsam::Matrix        H3;  // 2x2
    const gtsam::Vector2 error = p.errorVector(q, boost::none, H3);

    if (H)
    {
        *H = H3 * H2 * H1 * H0;
    }

    return error;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
