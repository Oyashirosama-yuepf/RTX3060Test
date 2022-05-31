/*!
 * * \brief Geometric conversion between holo and GTSAM
 * * \author Li Chao (lichao@holomatic.com)
 * * \date Aug 14, 2017
 * * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice. */

#ifndef HOLO_LOCALIZATION_COMMON_HOLO_GTSAM_H_
#define HOLO_LOCALIZATION_COMMON_HOLO_GTSAM_H_

#include <gtsam/geometry/Pose3.h>
#include <gtsam/navigation/NavState.h>

#include <holo/geometry/pose3.h>
#include <holo/localization/common/navstate.h>

namespace holo
{
namespace localization
{
/******************************************************************************
 * This class is responsible for converting the geometry models between holo and
 * gtsam(Georgia Tech Smoothing and Mapping library) which can be refered from
 * https://bitbucket.org/gtborg/gtsam/.
 *****************************************************************************/
class HoloGtsam
{
public:
    /* constructor */
    HoloGtsam()
    {
    }

    /* destructor */
    ~HoloGtsam()
    {
    }

    /**************************************************************************/
    /* convert holo::Point2 to gtsam::Point2 */
    static gtsam::Point2 Convert(const Point2& point)
    {
        gtsam::Point2 result = (gtsam::Vector(2) << point.GetX(), point.GetY()).finished();
        return result;
    }

    /**************************************************************************/
    /* convert gtsam::Point2 to holo::Point2 */
    static Point2 Convert(const gtsam::Point2& point)
    {
        return Point2(point.x(), point.y());
    }

    /**************************************************************************/
    /* convert holo::Point3 to gtsam::Point3 */
    static gtsam::Point3 Convert(const Point3& point)
    {
        gtsam::Point3 result = (gtsam::Vector(3) << point.GetX(), point.GetY(), point.GetZ()).finished();
        return result;
    }

    /**************************************************************************/
    /* convert gtsam::Point3 to holo::Point3 */
    static Point3 Convert(const gtsam::Point3& point)
    {
        return Point3(point.x(), point.y(), point.z());
    }

    /**************************************************************************/
    /* convert between gtsam Matrix3 and holo Matrix3 */
    static gtsam::Matrix3 Convert(const Matrix3& holo_matrix3)
    {
        gtsam::Matrix3 gtsam_matrix3;

        for (auto row = 0; row < holo_matrix3.GetRows(); row++)
        {
            for (auto col = 0; col < holo_matrix3.GetCols(); col++)
            {
                gtsam_matrix3(row, col) = holo_matrix3(row, col);
            }
        }

        return gtsam_matrix3;
    }

    /**************************************************************************/
    /* convert between gtsam Matrix3 and holo Matrix3 */
    static Matrix3 Convert(const gtsam::Matrix3& gtsam_matrix3)
    {
        Matrix3 holo_matrix3;

        for (auto row = 0; row < gtsam_matrix3.rows(); row++)
        {
            for (auto col = 0; col < gtsam_matrix3.cols(); col++)
            {
                holo_matrix3(row, col) = gtsam_matrix3(row, col);
            }
        }

        return holo_matrix3;
    }

    /**************************************************************************/
    /* convert between gtsam Matrix4 and holo Matrix4 */
    static gtsam::Matrix4 Convert(const Matrix4& holo_matrix4)
    {
        gtsam::Matrix4 gtsam_matrix4;

        for (auto row = 0; row < holo_matrix4.GetRows(); row++)
        {
            for (auto col = 0; col < holo_matrix4.GetCols(); col++)
            {
                gtsam_matrix4(row, col) = holo_matrix4(row, col);
            }
        }

        return gtsam_matrix4;
    }

    /**************************************************************************/
    /* convert between gtsam Matrix4 and holo Matrix4 */
    static Matrix4 Convert(const gtsam::Matrix4& gtsam_matrix4)
    {
        Matrix4 holo_matrix4;

        for (auto row = 0; row < gtsam_matrix4.rows(); row++)
        {
            for (auto col = 0; col < gtsam_matrix4.cols(); col++)
            {
                holo_matrix4(row, col) = gtsam_matrix4(row, col);
            }
        }

        return holo_matrix4;
    }

    /**************************************************************************/
    /* convert between gtsam Vector2 and holo Vector2 */
    static Vector2 Convert(const gtsam::Vector2& gtsam_vector2)
    {
        Vector2 holo_vector2;

        for (auto index = 0; index < 2; index++)
        {
            holo_vector2[index] = gtsam_vector2[index];
        }

        return holo_vector2;
    }

    /**************************************************************************/
    /* convert between gtsam Vector2 and holo Vector2 */
    static gtsam::Vector2 Convert(const Vector2& holo_vector2)
    {
        gtsam::Vector2 gtsam_vector2;

        for (auto index = 0; index < 2; index++)
        {
            gtsam_vector2[index] = holo_vector2[index];
        }

        return gtsam_vector2;
    }

    /**************************************************************************/
    /* convert between gtsam Vector3 and holo Vector3 */
    static Vector3 Convert(const gtsam::Vector3& gtsam_vector3)
    {
        Vector3 holo_vector3;

        for (auto index = 0; index < 3; index++)
        {
            holo_vector3[index] = gtsam_vector3[index];
        }

        return holo_vector3;
    }

    /**************************************************************************/
    /* convert between gtsam Vector3 and holo Vector3 */
    static gtsam::Vector3 Convert(const Vector3& holo_vector3)
    {
        gtsam::Vector3 gtsam_vector3;

        for (auto index = 0; index < 3; index++)
        {
            gtsam_vector3[index] = holo_vector3[index];
        }

        return gtsam_vector3;
    }

    /**************************************************************************/
    /* convert between gtsam Vector6 and holo Vector6 */
    static gtsam::Vector6 Convert(const Vector6& holo_vector6)
    {
        gtsam::Vector6 gtsam_vector6;

        for (auto index = 0; index < 6; index++)
        {
            gtsam_vector6[index] = holo_vector6[index];
        }

        return gtsam_vector6;
    }

    /**************************************************************************/
    /* convert between gtsam Vector6 and holo Vector6 */
    static Vector6 Convert(const gtsam::Vector6& gtsam_vector6)
    {
        Vector6 holo_vector6;

        for (auto index = 0; index < 6; index++)
        {
            holo_vector6[index] = gtsam_vector6[index];
        }

        return holo_vector6;
    }

    /**************************************************************************/
    /* convert holo::Rot3 to gtsam::Rot3 */
    static gtsam::Rot3 Convert(const Rot3& rot)
    {
        return gtsam::Rot3(Convert(rot.ToMatrix()));
    }

    /**************************************************************************/
    /* convert gtsam::Rot3 to holo::Rot3 */
    static Rot3 Convert(const gtsam::Rot3& rot)
    {
        return Rot3(Convert(rot.matrix()));
    }

    /**************************************************************************/
    /* convert holo::Pose3 to gtsam::Pose3 */
    static gtsam::Pose3 Convert(const Pose3& pos)
    {
        return gtsam::Pose3(Convert(pos.ToMatrix()));
    }

    /**************************************************************************/
    /* convert gtsam::Pose3 to holo::Pose3 */
    static Pose3 Convert(const gtsam::Pose3& pos)
    {
        return Pose3(Convert(pos.matrix()));
    }

    /**************************************************************************/
    /* convert holo::NavState to gtsam::NavState */
    static gtsam::NavState Convert(const Navstate& navs)
    {
        return gtsam::NavState(Convert(navs.GetPose()), Convert(navs.GetVelocity()));
    }

    /**************************************************************************/
    /* convert gtsam::NavState to holo::NavState */
    static Navstate Convert(const gtsam::NavState& navs)
    {
        return Navstate(Convert(navs.pose()), Convert(navs.velocity()));
    }

};  // class HoloGtsam

/*****************************************************************************/

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_COMMON_HOLO_GTSAM_H_
