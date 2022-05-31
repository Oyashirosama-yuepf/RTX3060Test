/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose_only_unit3_facotr_inl.cpp
 * @brief This header file defines pose only unit3 factor implementation
 * @author duyanwei@holomatic.com (Yanwei Du)
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-12-06
 */

#include <holo/localization/sam/factors/internal/pose_only_unit3_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseOnlyUnit3Factor::PoseOnlyUnit3Factor(gtsam::Point3 const& landmark, gtsam::Point3 const& feature,
                                         gtsam::SharedNoiseModel const& model, gtsam::Key const& key,
                                         boost::optional<gtsam::Pose3> optional_bTc)
  : Base(model, key), landmark_(landmark), feature_(feature), optional_bTc_(optional_bTc)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector PoseOnlyUnit3Factor::evaluateError(gtsam::Pose3 const& wTb, boost::optional<gtsam::Matrix&> H) const
{
    ///@brief construct camera pose
    gtsam::Pose3  wTc(wTb);
    gtsam::Matrix H0;  // 6x6

    if (optional_bTc_)
    {
        wTc = wTb.compose(*optional_bTc_, H0);
    }

    ///@brief transform landmark to camera frame
    gtsam::Matrix       H1;  // 3x6
    gtsam::Point3 const ptc = wTc.transform_to(landmark_, H1);

    ///@brief construct Unit3 from landmark
    gtsam::Matrix      H2;  // 2 x 3
    gtsam::Unit3 const q = gtsam::Unit3::FromPoint3(ptc, H2);

    ///@brief construct Unit3 from feature point
    gtsam::Unit3 const p(feature_);

    ///@brief compute error
    gtsam::Matrix        H3;  // 2x2
    gtsam::Vector2 const error = p.errorVector(q, boost::none, H3);

    if (H)
    {
        *H = H3 * H2 * H1 * H0;
    }

    return error;
}

}  // namespace internal
}  // namespace localization
}  // namespace holo
