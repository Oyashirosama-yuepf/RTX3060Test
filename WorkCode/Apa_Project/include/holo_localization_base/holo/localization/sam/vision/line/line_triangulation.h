/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_triangulation.h
 * @brief This file defines header of line triangulation.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-12-07"
 * @ref "PL-VIO: Tightly-Coupled Monocular Visual–Inertial Odometry Using Point and Line Features"
 *      "Multiple View Geometry in Computer Vision"
 */

#ifndef HOLO_LOCALIZATION_VISION_LINE_LINE_TRIANGULATION_H_
#define HOLO_LOCALIZATION_VISION_LINE_LINE_TRIANGULATION_H_

#include <gtsam/base/Matrix.h>
#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Pose3.h>

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
 * @brief This class defines triangulation of plucker space line, through solving intersection of two space planes.
 * Define left_plane = [a1 b1 c1 d1], right_plane = [a2 b2 c2 d2], which can be computed from camera info:
 * PluckerMatrix = [[d]^ n] = left_plane * right_plane' - right_plane * left_plane'
 *                 [-n'  0]
 * The d[direction vector] and n[normal vector] can be extract from this matrix, PluckerLine = [n d].
 *
 */
class LineTriangulation
{
public:
    /**
     * @brief defination of handy types
     *
     */
    using GTScalar  = double;
    using GTVector2 = gtsam::Vector2;
    using GTVector3 = gtsam::Vector3;
    using GTVector4 = gtsam::Vector4;
    using GTMatrix3 = gtsam::Matrix3;
    using GTMatrix4 = gtsam::Matrix4;
    using GTRot3    = gtsam::Rot3;
    using GTPoint3  = gtsam::Point3;
    using GTPose3   = gtsam::Pose3;

    /**
     * @brief parameters for line triangulation
     *
     */
    struct Parameters
    {
        GTScalar min_distance_between_two_frames;  ///< minimum distance between two candidate frames, unit: m
        GTScalar min_angle_between_two_planes;     ///< minimum angle between two candidate planes, unit: rad

        /**
         * @brief Construct a new Parameters object
         *
         * @param[in] _min_distance_between_two_frames ///< minimum distance between two candidate frames, unit: m
         * @param[in] _min_angle_between_two_planes ///< minimum angle between two candidate planes, unit: rad
         */
        Parameters(GTScalar const _min_distance_between_two_frames, GTScalar const _min_angle_between_two_planes)
          : min_distance_between_two_frames(_min_distance_between_two_frames)
          , min_angle_between_two_planes(_min_angle_between_two_planes)
        {
        }

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return Parameters generated line triangulation parameters
         */
        static Parameters GenerateExample();

        /**
         * @brief output stream for line triangulation parameters
         *
         * @param[in] os output stream
         * @param[in] parameters line triangulation parameters
         * @return std::ostream& output parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "\n line triangulation paramters : "
               << "\n min_distance_between_two_frames = " << parameters.min_distance_between_two_frames << "m"
               << "\n min_angle_between_two_planes = " << parameters.min_angle_between_two_planes << "rad" << std::endl;
            return os;
        }
    };

    /**
     * @brief struct to store camera info with detected start point and end point of the image line for
     * triangulation from different cameras
     *
     */
    struct CameraInfoWithLineEndpoints
    {
        GTPose3   wTc;  ///< pose of camera coordinate in world coordinate
        GTMatrix3 K;    ///< intrinsic matrix of camera, when the given line is on normalized plane, K need to be set to
                        ///< Identity matrix
        GTVector2 start_point;  ///< start point of the line on image plane or normalized plane
        GTVector2 end_point;    ///< end point of the line on image plane or normalized plane

        CameraInfoWithLineEndpoints(GTPose3 const& _wTc, GTMatrix3 const& _K, GTVector2 const& _start_point,
                                    GTVector2 const& _end_point)
          : wTc(_wTc), K(_K), start_point(_start_point), end_point(_end_point)
        {
        }
    };

    /**
     * @brief struct to store camera info with image line coefficient for triangulation from different cameras
     *
     */
    struct CameraInfoWithLineCoefficient
    {
        GTPose3   wTc;  ///< pose of camera coordinate in world coordinate
        GTMatrix3 K;    ///< intrinsic matrix of camera, when the given line is on normalized plane, K need to be set to
                        ///< Identity matrix
        GTVector3 line_coefficient;  ///< coefficient of the line on image plane or normalized plane

        CameraInfoWithLineCoefficient(GTPose3 const& _wTc, GTMatrix3 const& _K, GTVector3 const& _line_coefficient)
          : wTc(_wTc), K(_K), line_coefficient(_line_coefficient)
        {
        }
    };

    /**
     * @brief Construct a new line triangulation object
     *
     * @param[in] Parameters line triangulation parameters
     */
    LineTriangulation(Parameters const& Parameters) : parameters_(Parameters)
    {
    }

    /**
     * @brief Destroy the line triangulation object
     *
     */
    ~LineTriangulation() noexcept;

    /**
     * @brief triangulate space line through solving intersection of left plane and right plane. Planes are
     * determined by respective camera info with line representation of image line endpoints
     *
     * @param[in] lhs left camera info with detected image line endpoints
     * @param[in] rhs right camera info with detected image line endpoints
     * @return std::pair<bool_t, PluckerLine> triangulated plucker line in world frame
     *         if triangulate failed:
     *         1. delta_trans < = min_distance_between_two_frames
     *         2. angle_between_two_planes < = min_angle_between_two_planes
     *         return std::make_pair(false, PluckerLine)
     *         otherwise, triangulated success, return std::make_pair(true, PluckerLine)
     */
    std::pair<bool, PluckerLine> run(CameraInfoWithLineEndpoints const& lhs,
                                     CameraInfoWithLineEndpoints const& rhs) const;

    /**
     * @brief triangulate space line through solving intersection of left plane and right plane. Planes are
     * determined by respective camera info with line representation of image line coefficient
     *
     * @param[in] lhs left camera info with detected image line coefficient
     * @param[in] rhs right camera info with detectd image line coefficient
     * @return std::pair<bool_t, PluckerLine> triangulated plucker line in world frame
     * @details when the given line is on normalized plane, K in CameraInfoWithLineCoefficient need to be set to
     * Identity matrix
     */
    std::pair<bool, PluckerLine> run(CameraInfoWithLineCoefficient const& lhs,
                                     CameraInfoWithLineCoefficient const& rhs) const;

protected:
    /**
     * @brief compute space plane from detected line coefficient on normalized plane, the plane is composed from the
     * line and the projection center.
     *
     * @param[in] line_coefficient_on_normalized_plane line coefficient on normalized plane
     * @return GTVector4 computed plane, whose equation is plane[0] * x + plane[1] * y + plane[2] * z + plane[3] = 0
     * @details plane normal vector = K' * image_line, image_line is defined as [a b c]'，satisfing equation
     *          a * x + b * y + c = 0
     * @ref  "Multiple View Geometry in Computer Vision - Version2 Chapter8"
     */
    GTVector4 computePlaneFromLineCoefficient(GTVector3 const& line_coefficient_on_normalized_plane) const;

    /**
     * @brief compute angle between the two planes, whose intersection is the space line
     *
     * @param[in] left_plane left plane contains the space line to be solved, whose equation is plane1[0] * x +
     * plane1[1] * y + plane1[2] * z + plane1[3] = 0
     * @param[in] right_plane right plane contains the space line to be solved, whose equation is plane2[0] * x +
     * plane2[1] * y + plane2[2] * z + plane2[3] = 0
     * @return GTScalar the computed angle, unit: rad
     * @details the angle between two planes is defined as angle between normal vectors of planes.
     */
    GTScalar computeAngleBetweenTwoPlanes(GTVector4 const& left_plane, GTVector4 const& right_plane) const;

    Parameters parameters_;  ///< parameters for line triangulation
};

using GTLineTriangulation = LineTriangulation;

/**
 * @}
 *
 */

}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_VISION_LINE_LINE_TRIANGULATION_H_