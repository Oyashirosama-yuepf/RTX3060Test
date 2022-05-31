/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file orthonormal_line.cpp
 * @brief This file defines src of orthonormal line
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-12-09"
 */

#include <holo/localization/sam/vision/line/orthonormal_line.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::OrthonormalLine(GTRot3 const& U, GTRot2 const& W)
{
    U_ = U;
    W_ = W;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::OrthonormalLine(GTVector3 const& u, GTScalar const w)
{
    U_ = GTRot3::Expmap(u);
    W_ = GTRot2::Expmap(GTVector1(w));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::OrthonormalLine(GTVector4 const& orthonormal_line)
{
    GTVector3 const u = GTVector3(orthonormal_line(0u), orthonormal_line(1u), orthonormal_line(2u));
    GTScalar const  w = orthonormal_line(3u);
    (void)new (this) OrthonormalLine(u, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::OrthonormalLine(PluckerLine const& plucker_line)
{
    GTVector3 const direction              = plucker_line.getDirectionVector();
    GTVector3 const normal                 = plucker_line.getNormalVector();
    GTVector3 const normal_cross_direction = plucker_line.getNormalVector().cross(plucker_line.getDirectionVector());

    U_ = GTRot3(normal.normalized(), direction.normalized(), normal_cross_direction.normalized());
    // distance = normal.norm() / direction.norm() = cos(phi) / sin(phi) = cot(phi)
    W_ = GTRot2::atan2(direction.norm(), normal.norm());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::~OrthonormalLine()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::GTRot3 OrthonormalLine::getU() const
{
    return U_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::GTRot2 OrthonormalLine::getW() const
{
    return W_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PluckerLine OrthonormalLine::convertToPluckerLine(gtsam::OptionalJacobian<6u, 4u> H) const
{
    GTVector3 const normal_vector    = W_.c() * (U_.r1());
    GTVector3 const direction_vector = W_.s() * (U_.r2());

    if (H)
    {
        // Jacobian of pucker line to orthornormal line, H = d(L) / d(O), where the plucker line is represented in 6
        // dimension vector form，the orthonormal line is represented in 4 dimension vector form, derivation of formula
        // can be found in: "PL-VIO: Tightly-Coupled Monocular Visual–Inertial Odometry Using Point and Line Features"
        *H << GTVector3::Zero(), -W_.c() * (U_.r3()), W_.c() * (U_.r2()), -W_.s() * (U_.r1()), W_.s() * (U_.r3()),
            GTVector3::Zero(), -W_.s() * (U_.r1()), W_.c() * (U_.r2());
    }

    return PluckerLine(normal_vector, direction_vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OrthonormalLine::print(std::string const& s) const
{
    U_.print(s);
    W_.print(s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool OrthonormalLine::equals(OrthonormalLine const& rhs, double tol) const
{
    return U_.equals(rhs.getU(), tol) && W_.equals(rhs.getW(), tol);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine OrthonormalLine::inverse(ChartJacobian H) const
{
    if (H)
    {
        *H = -this->AdjointMap();
    }

    return OrthonormalLine(U_.inverse(), W_.inverse());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine OrthonormalLine::operator*(OrthonormalLine const& rhs) const
{
    GTRot3 const U = U_ * rhs.getU();
    GTRot2 const W = W_ * rhs.getW();
    return OrthonormalLine(U, W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine OrthonormalLine::Expmap(GTVector4 const& v, ChartJacobian H)
{
    if (H)
    {
        *H = ExpmapDerivative(v);
    }

    GTVector3 const u(v(0u), v(1u), v(2u));
    GTRot3 const    U = GTRot3(gtsam::traits<GTSO3>::Expmap(u));
    GTRot2 const    W = GTRot2::Expmap(GTVector1(v(3u)));
    return OrthonormalLine(U, W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::GTVector4 OrthonormalLine::Logmap(OrthonormalLine const& orthonormal_line, ChartJacobian H)
{
    gtsam::OptionalJacobian<3, 3> u_jacobian;
    GTVector3 const               u = GTRot3::Logmap(orthonormal_line.getU(), u_jacobian);

    gtsam::OptionalJacobian<1, 1> w_jacobian;
    GTVector1 const               w = GTRot2::Logmap(orthonormal_line.getW(), w_jacobian);

    if (H)
    {
        *H = LogmapDerivative(GTVector4(u(0u), u(1u), u(2u), w(0u)));
    }

    return GTVector4(u(0u), u(1u), u(2u), w(0u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::GTMatrix4 OrthonormalLine::AdjointMap() const
{
    GTMatrix4 adjoint_matrix             = GTMatrix4::Zero();
    adjoint_matrix.block<3u, 3u>(0u, 0u) = U_.matrix();
    adjoint_matrix.block<1u, 1u>(3u, 3u) = gtsam::I_1x1;
    return adjoint_matrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine OrthonormalLine::identity()
{
    GTRot3 const U = GTRot3::identity();
    GTRot2 const W = GTRot2::identity();
    return OrthonormalLine(U, W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::GTMatrix4 OrthonormalLine::ExpmapDerivative(GTVector4 const& v)
{
    GTMatrix4 expmap_derivative;
    expmap_derivative.block<3u, 3u>(0u, 0u) = GTSO3::ExpmapDerivative(GTVector3(v(0u), v(1u), v(2u)));
    expmap_derivative.block<1u, 1u>(3u, 3u) = gtsam::I_1x1;
    return expmap_derivative;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::GTMatrix4 OrthonormalLine::LogmapDerivative(GTVector4 const& v)
{
    GTMatrix4 logmap_derivative;
    logmap_derivative.block<3u, 3u>(0u, 0u) = GTSO3::LogmapDerivative(GTVector3(v(0u), v(1u), v(2u)));
    logmap_derivative.block<1u, 1u>(3u, 3u) = gtsam::I_1x1;
    return logmap_derivative;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine OrthonormalLine::ChartAtOrigin::Retract(const GTVector4& v, ChartJacobian H)
{
    return Expmap(v, H);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthonormalLine::GTVector4 OrthonormalLine::ChartAtOrigin::Local(const OrthonormalLine& orthonormal_line,
                                                                 ChartJacobian          H)
{
    return Logmap(orthonormal_line, H);
}

}  // namespace localization
}  // namespace holo