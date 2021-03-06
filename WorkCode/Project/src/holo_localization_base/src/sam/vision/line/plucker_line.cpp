/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file plucker_line.cpp
 * @brief This file defines source of plucker line.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-12-08"
 */

#include <holo/localization/sam/vision/line/plucker_line.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine::PluckerLine(GTVector6 const& plucker_line)
{
    plucker_line_ = plucker_line;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine::PluckerLine(GTVector3 const& n, GTVector3 const& d)
{
    plucker_line_ << n, d;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine::PluckerLine(GTMatrix4 const& dual_plucker_matrix)
{
    GTVector3 direction_vector;
    direction_vector << -dual_plucker_matrix(1, 2), dual_plucker_matrix(0, 2), -dual_plucker_matrix(0, 1);
    GTVector3 normal_vector;
    normal_vector << dual_plucker_matrix(0, 3), dual_plucker_matrix(1, 3), dual_plucker_matrix(2, 3);
    plucker_line_ << normal_vector, direction_vector;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine::PluckerLine(GTVector4 const& plane1, GTVector4 const& plane2)
{
    GTMatrix4 const plucker_matrix = plane1 * plane2.transpose() - plane2 * plane1.transpose();
    (void)new (this) PluckerLine(plucker_matrix);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine::~PluckerLine()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine::GTVector3 PluckerLine::getDirectionVector(gtsam::OptionalJacobian<3u, 6u> Dplucker) const
{
    GTVector3 direction_vector(plucker_line_[3u], plucker_line_[4u], plucker_line_[5u]);

    if (Dplucker)
    {
        *Dplucker << GTMatrix3::Zero(), GTMatrix3::Identity();
    }

    return direction_vector;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine::GTVector3 PluckerLine::getNormalVector(gtsam::OptionalJacobian<3u, 6u> Dplucker) const
{
    GTVector3 const normal_vector = GTVector3(plucker_line_[0u], plucker_line_[1u], plucker_line_[2u]);

    if (Dplucker)
    {
        *Dplucker << GTMatrix3::Identity(), GTMatrix3::Zero();
    }

    return normal_vector;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine PluckerLine::transformFrom(GTPose3 const& tTs, gtsam::OptionalJacobian<6u, 6u> Dpose,
                                       gtsam::OptionalJacobian<6u, 6u> Dplucker) const
{
    GTVector3 const translation                          = tTs.translation().vector();
    GTMatrix3 const skew_symmetric_matrix_of_translation = gtsam::skewSymmetric(translation);

    GTRot3 const    tRs        = tTs.rotation();
    GTMatrix3 const tRs_matrix = tRs.matrix();
    GTMatrix6       tTs_for_line_transformation;
    tTs_for_line_transformation.block<3u, 3u>(0u, 0u) = tRs_matrix;
    tTs_for_line_transformation.block<3u, 3u>(0u, 3u) = skew_symmetric_matrix_of_translation * tRs_matrix;
    tTs_for_line_transformation.block<3u, 3u>(3u, 0u) = GTMatrix3::Zero();
    tTs_for_line_transformation.block<3u, 3u>(3u, 3u) = tRs_matrix;

    GTVector6 const     target_plucker_line_vector = tTs_for_line_transformation * plucker_line_;
    GTPluckerLine const target_plukcer_line        = GTPluckerLine(target_plucker_line_vector);

    if (Dplucker)
    {
        *Dplucker = tTs_for_line_transformation;
    }

    if (Dpose)
    {
        // TODO(mayufei@holomatic.com): replace the jacobian H_Lt_to_sTt generated by transformTo to analytical
        // derivation solution
        GTMatrix6     H_sTt_to_tTs;
        GTPose3 const sTt = tTs.inverse(H_sTt_to_tTs);
        GTMatrix6     H_Lt_to_sTt;
        GTMatrix6     H_Lt_to_Ls;
        GTPluckerLine source_plucker_line = GTPluckerLine(plucker_line_);
        source_plucker_line.transformTo(sTt, H_Lt_to_sTt, H_Lt_to_Ls);
        GTMatrix6 H_Lt_to_tTs = H_Lt_to_sTt * H_sTt_to_tTs;
        Dpose                 = H_Lt_to_tTs;
    }

    return target_plukcer_line;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine PluckerLine::transformTo(GTPose3 const& tTs, gtsam::OptionalJacobian<6u, 6u> Dpose,
                                     gtsam::OptionalJacobian<6u, 6u> Dplucker) const
{
    GTPose3 const   sTt                                  = tTs.inverse();
    GTMatrix3 const skew_symmetric_matrix_of_translation = gtsam::skewSymmetric(sTt.translation());
    GTMatrix6       transformation_matrix;
    transformation_matrix.block<3u, 3u>(0u, 0u) = sTt.rotation().matrix();
    transformation_matrix.block<3u, 3u>(0u, 3u) = skew_symmetric_matrix_of_translation * sTt.rotation().matrix();
    transformation_matrix.block<3u, 3u>(3u, 0u) = GTMatrix3::Zero();
    transformation_matrix.block<3u, 3u>(3u, 3u) = sTt.rotation().matrix();

    GTVector6 const     target_plucker_line_vector = plucker_line_;
    GTVector6 const     source_plucker_line_vector = transformation_matrix * target_plucker_line_vector;
    GTPluckerLine const source_plucker_line(source_plucker_line_vector);
    GTPluckerLine const target_plucker_line(target_plucker_line_vector);

    if (Dplucker)
    {
        *Dplucker = transformation_matrix;
    }

    if (Dpose)
    {
        Dpose->block<3u, 3u>(0u, 0u) =
            gtsam::skewSymmetric(sTt.rotation().matrix() *
                                 (target_plucker_line.getNormalVector() +
                                  gtsam::skewSymmetric(target_plucker_line.getDirectionVector()) * tTs.translation()));
        Dpose->block<3u, 3u>(3u, 0u) = gtsam::skewSymmetric(
            sTt.rotation().matrix() * target_plucker_line.getDirectionVector());  ///< Jacobian of Lc to rotation
        Dpose->block<3u, 3u>(0u, 3u) = sTt.rotation().matrix() *
                                       gtsam::skewSymmetric(target_plucker_line.getDirectionVector()) *
                                       tTs.rotation().matrix();  ///< Jacobian of Lc to translation
        Dpose->block<3u, 3u>(3u, 3u) = GTMatrix3::Zero();
    }

    return source_plucker_line;
}
}  // namespace localization
}  // namespace holo