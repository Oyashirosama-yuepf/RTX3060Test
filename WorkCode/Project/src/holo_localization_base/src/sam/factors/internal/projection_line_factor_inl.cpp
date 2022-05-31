/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file projection_line_factor_inl.cpp
 * @brief source file of projection lane factor
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date June 20, 2020
 */

#include <holo/localization/sam/factors/internal/projection_line_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ProjectionLineFactor::ProjectionLineFactor() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ProjectionLineFactor::ProjectionLineFactor(gtsam::Key const& key, gtsam::SharedNoiseModel const& model,
                                           gtsam::Point3 const& point, gtsam::Pose3 const& bTc, gtsam::Cal3_S2 const& K,
                                           Line2Type const& line, bool_t const enable_rotation_constraint)
  : gtsam::NoiseModelFactor1<gtsam::Pose3>(model, key)
  , point_(point)
  , bTc_(bTc)
  , K_(K)
  , line_(line)
  , enable_rotation_constraint_(enable_rotation_constraint)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector ProjectionLineFactor::evaluateError(gtsam::Pose3 const& wTb, boost::optional<gtsam::Matrix&> H) const
{
    gtsam::Vector1 error;

    try
    {
        gtsam::Matrix H0, H1;

        // Step1: project map point to image plane
        gtsam::PinholeCamera<gtsam::Cal3_S2> camera(wTb.compose(bTc_, H0), K_);
        gtsam::Point2 const                  point_in_image = camera.project(point_, H1, boost::none, boost::none);

        // Step2: compute distance of projection point to fitted line
        double const a       = line_.GetCoeffs()[0];
        double const b       = line_.GetCoeffs()[1];
        double const c       = line_.GetCoeffs()[2];
        double const norm_ab = sqrt(a * a + b * b);

        // define the fitted line is a*x + b*y + c = 0, the distance from point(x, y) to the line is (a*x + b*y +
        // c)/sqrt(a^2+b^2)
        error(0) = (a * point_in_image.x() + b * point_in_image.y() + c) / norm_ab;

        // Step3: compute jacobian matrix
        if (H)
        {
            *H = gtsam::Vector2(a / norm_ab, b / norm_ab).transpose() * H1 * H0;

            if (!enable_rotation_constraint_)
            {
                (*H).block<1, 3>(0, 0) = gtsam::Matrix13::Zero();
            }
        }

        return error;
    }
    catch (gtsam::CheiralityException& e)
    {
        if (H)
        {
            *H = gtsam::Matrix::Zero(1, 6);
        }

        error(0) = 0.0;

        std::cout << "Projection line factor: cheirality exception";
        return error;
    }
}
}  // namespace internal
}  // namespace localization
}  // namespace holo
