/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file orthonormal_line.h
 * @brief This file defines header of orthonormal line.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-12-06"
 * @ref "Structure-from-motion using lines: Representation, triangulation,and bundle adjustment"
 */

#ifndef HOLO_LOCALIZATION_SAM_VISION_LINE_ORTHONORMAL_LINE_H_
#define HOLO_LOCALIZATION_SAM_VISION_LINE_ORTHONORMAL_LINE_H_

#include <gtsam/base/Matrix.h>
#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Rot2.h>
#include <gtsam/geometry/Rot3.h>

#include <holo/localization/sam/vision/line/plucker_line.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

/**
 * @brief This class defines orthonormal line. U_ represents rotation of line coordinate in reference coordinate. W_
 *        include distance information from origin of reference coordinate to the line.
 *        The line coordinate defines as below:
 *        x axis -> normal vector
 *        y axis -> direction vector
 *        z axis -> x cross y
 */
class OrthonormalLine : public gtsam::LieGroup<OrthonormalLine, 4u>
{
public:
    /**
     * @brief Define some common type
     */
    using GTScalar      = double;
    using GTVector      = gtsam::Vector;
    using GTVector1     = gtsam::Vector1;
    using GTVector3     = gtsam::Vector3;
    using GTVector4     = gtsam::Vector4;
    using GTVector6     = gtsam::Vector6;
    using GTRot2        = gtsam::Rot2;
    using GTRot3        = gtsam::Rot3;
    using ChartJacobian = gtsam::OptionalJacobian<4, 4>;
    using GTMatrix      = gtsam::Matrix;
    using GTMatrix3     = gtsam::Matrix3;
    using GTMatrix4     = gtsam::Matrix4;
    using GTSO3         = gtsam::SO3;

    /**
     * @brief Construct a new Orthonormal Line object
     *
     * @param[in] U rotation matrix represents rotation of line coordinate in reference coordinate.
     * @param[in] W rotation matrix includes distance information from origin of reference coordinate to the line.
     * @details U = R(u) = [n/|n| d/|d| n×d/|n×d|] where n is the normal vector of line and d is direction vector
     *          W = [w1 -w2] = [cos(w) -sin(w)] = 1/(sqrt(|n|^2+|d|^2)) * [|n| -|d|]
     *              [w2  w1]   [sin(w)  cos(w)]                           [|d|  |n|]
     *          W includes distance information from origin of reference coordinate to the line, distance = |n|/|d|
     */
    OrthonormalLine(GTRot3 const& U, GTRot2 const& W);

    /**
     * @brief Construct a new Orhornormal Line object
     *
     * @param[in] u Lie algebra of U, U = R(u)
     * @param[in] w Lie algebra of W, W = R(w)
     */
    OrthonormalLine(GTVector3 const& u, GTScalar const w);

    /**
     * @brief Construct a new Orthonormal Line object
     *
     * @param[in] orthonormal_line orthonormal line in 4 dimensional form, orthonormal_line = [u,w]
     * @details first 3 dimensional of it is u(lie algebra of U) and the last dimensional is w(lie algebra of W)
     */
    OrthonormalLine(GTVector4 const& orthonormal_line);

    /**
     * @brief Construct a new Orthonormal Line object
     *
     * @param[in] plucker_line plucker line consist of direction vector and normal vector
     */
    OrthonormalLine(PluckerLine const& plucker_line);

    /**
     * @brief Destroy the Orthonormal Line object
     *
     */
    ~OrthonormalLine() noexcept;

    /**
     * @brief Get U_
     *
     * @return GTRot3
     */
    GTRot3 getU() const;

    /**
     * @brief Get W_
     *
     * @return GTRot2
     */
    GTRot2 getW() const;

    /**
     * @brief convert orthonormal line to plucker line
     *
     * @param[in] H Jacobian of plucker line to orthonormal line, H = d(output) / d(orthonormal line in vector form)
     * @return PluckerLine
     */
    PluckerLine convertToPluckerLine(gtsam::OptionalJacobian<6u, 4u> H = boost::none) const;

    /**
     * @brief print U_ and W_
     *
     * @param[in] s input string to indicate the information of this orthonormal line
     */
    void print(std::string const& s) const;

    /**
     * @brief judge if rhs is equal to *this, the tolerate error is 1e-9
     *
     * @param[in] rhs input orthonormal line
     * @param[in] tol tolerate error
     * @return true
     * @return false
     */
    bool equals(OrthonormalLine const& rhs, double tol = 1e-9) const;

    /**
     * @brief inverse of U_ and W_
     *
     * @return OrthonormalLine
     */
    OrthonormalLine inverse(ChartJacobian H = boost::none) const;

    /**
     * @brief operator*
     *
     * @param[in] rhs the right hand side
     * @return OrthonormalLine
     */
    OrthonormalLine operator*(OrthonormalLine const& rhs) const;

    /**
     * @brief liegroup expmap
     *
     * @param[in] v lie algebra
     * @param[in] H ExpmapDerivative, size: 4 * 4
     */
    static OrthonormalLine Expmap(GTVector4 const& v, ChartJacobian H = boost::none);

    /**
     * @brief liegroup logmap
     *
     * @param[in] orthonormal_line orthonormal line
     * @param[in] H LogmapDerivative, size: 4 * 4
     * @return GTVector4 lie algebra
     */
    static GTVector4 Logmap(OrthonormalLine const& orthonormal_line, ChartJacobian H = boost::none);

    /**
     * @brief adjoint map
     *
     * @return GTMatrix4 adjoint matrix
     */
    GTMatrix4 AdjointMap() const;

    /**
     * @brief identity matrix
     *
     * @return GTMatrix4
     */
    static OrthonormalLine identity();

    /**
     * @brief liegroup Expmap Derivative
     *
     * @param[in] v lie algebra
     * @return GTMatrix4 Derivative result
     */
    static GTMatrix4 ExpmapDerivative(GTVector4 const& v);

    /**
     * @brief liegroup Logmap Derivative
     *
     * @param[in] v lie algebra
     * @return GTMatrix4 Derivative result
     */
    static GTMatrix4 LogmapDerivative(GTVector4 const& v);

    /**
     * @brief Chart At Origin
     *
     */
    struct ChartAtOrigin
    {
        /**
         * @brief map from the tangent space back to the manifold
         *
         * @param[in] v lie algebra
         * @param[in] H Jacobian, size: 4 * 4
         * @return OrthonormalLine
         */
        static OrthonormalLine Retract(const GTVector4& v, ChartJacobian H = boost::none);

        /**
         * @brief map from the manifold back to the tangent space
         *
         * @param[in] orthonormal_line orthonormal line
         * @param[in] H Jacobian, size: 4 * 4
         * @return GTVector4
         */
        static GTVector4 Local(const OrthonormalLine& orthonormal_line, ChartJacobian H = boost::none);
    };

private:
    GTRot3 U_;  ///< 3 dimensional matrix represents rotation of line coordinate in reference coordinate.
    GTRot2 W_;  ///< 2 dimensional matrix includes distance information from origin of reference coordinate to the line.
};

using GTOrthonormalLine = OrthonormalLine;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

namespace gtsam
{
/**
 * @brief gtsam traits
 *
 * @tparam
 */
template <>
struct traits<holo::localization::OrthonormalLine> : public internal::LieGroup<holo::localization::OrthonormalLine>
{
};
}  // namespace gtsam

#endif  // HOLO_LOCALIZATION_SAM_VISION_LINE_ORTHONORMAL_LINE_H_