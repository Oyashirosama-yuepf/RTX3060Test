/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-10-08
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_CAMERA_MODEL_H_
#define HOLO_PERCEPTION_COMMON_CAMERA_MODEL_H_

#include <memory>
#include <string>
// #include <Eigen/Eigen>
#include <opencv2/core/eigen.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <holo/common/intrinsic.h>
#include <holo/common/extrinsic.h>
#include "holo/core/exception.h"
#include "holo/core/types.h"
#include "holo/geometry/angle.h"
#include <holo/geometry/pose3.h>
#include <holo/geometry/rot3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/utils/holo_root.h>
#include <holo/numerics/vector.h>


namespace holo
{
namespace perception
{

template <typename Scalar>
class CameraModel
{
public:
    /**
     * @brief define camera model
     */
    enum class Value
    {
        PINHOLE = 0x0000,
        FISHEYE = 0x0010,
        UNKNOWN = 0xFFFF,
    };

    typedef holo::Matrix3T<Scalar> Matrix3;
    typedef holo::Matrix4T<Scalar> Matrix4;
    typedef holo::Vector2T<Scalar> Vector2;
    typedef holo::Vector3T<Scalar> Vector3;
    typedef holo::Vector4T<Scalar> Vector4;
    typedef holo::Vector8T<Scalar> Vector8;
    typedef holo::Point2T<Scalar> Point2;
    typedef holo::Point3T<Scalar> Point3;
    typedef holo::Pose3T<Scalar> Pose3;
    typedef holo::Rot3T<Scalar> Rot3;
    typedef Pose3T<holo::float64_t> Pose3Type;
    typedef holo::Rot3T<holo::float64_t> Rot3Type;
    typedef holo::Point3T<holo::float64_t> Point3Type;

    CameraModel(const std::string& intrinsic_file, 
        const std::string& extrinsic_file, 
        const CameraModel::Value& mode = CameraModel::Value::FISHEYE);

    /**
     * set camera distortion mode
    */
    void SetDistortionMode(const CameraModel::Value& mode);

    /**
     * get camera resolution width
    */
    size_t ResolutionWidth() const { return intrinsic_.GetDimension()[0]; }

    /**
     * get camera resolution height
    */
    size_t ResolutionHeight() const {return intrinsic_.GetDimension()[1]; }

    /**
     * get camera height
    */
    const Scalar CameraHeight() const { return camera_height_; }

    /**
     * get camera yaw
    */
    const Scalar Yaw() const { return yaw_radian_; }

    /**
     * get camera Roll
    */
    const Scalar Roll() const { return roll_radian_; }

    /**
     * get camera Picth
    */
    const Scalar Pitch() const { return pitch_radian_; }

    /**
     * get k matrix
    */
    const Matrix3& K() const { return k_; }

    /**
     * get inverse k matrix
    */
    const Matrix3& K_inv() const {return k_inv_; }

    /**
     * get new k matrix
    */
    const Matrix3& New_K() const { return new_k_; }

    /**
     * get inverse new k matrix
    */
    const Matrix3& New_K_inv() const { return new_k_inv_; }

    /**
     * get camera extrinsic object
    */
    const holo::Extrinsicf& GetExtrinsic() const { return extrinsic_; }

    /**
     * project a 3d point to image 2d point without distort
    */
    Vector2 Project(const Vector3& in) const;
    Vector2 Project(const Vector3& in, const Matrix3& k) const;

    Point2 Project(const Point3& in) const;
    Point2 Project(const Point3& in, const Matrix3& k) const;

    /**
     * project a 3d points vector to image
    */
    void ProjectPoints(const std::vector<Vector3>& in, std::vector<Vector2>& out) const;
    void ProjectPoints(const std::vector<Vector3>& in, std::vector<Vector2>& out, const Matrix3& k) const;

    void ProjectPoints(const std::vector<Point3>& in, std::vector<Point2>& out) const;
    void ProjectPoints(const std::vector<Point3>& in, std::vector<Point2>& out, const Matrix3& k) const;

    /**
     * unporject a 2d point to 3d point
    */
    Vector3 Unproject(const Vector2& in) const;
    Vector3 Unproject(const Vector2& in, const Matrix3& k_inv) const;

    Point3 Unproject(const Point2& in) const;
    Point3 Unproject(const Point2& in, const Matrix3& k_inv) const;

    /**
     * unproject a 2d points vector to 3d world
    */
    void UnprojectPoints(const std::vector<Vector2>& in, std::vector<Vector3>& out) const;
    void UnprojectPoints(const std::vector<Vector2>& in, std::vector<Vector3>& out, const Matrix3& k_inv) const;

    void UnprojectPoints(const std::vector<Point2>& in, std::vector<Point3>& out) const;
    void UnprojectPoints(const std::vector<Point2>& in, std::vector<Point3>& out, const Matrix3& k_inv) const;

    /**
     * distort a 2d point
    */
    void DistortPoints(const std::vector<Vector2>& in, std::vector<Vector2>& out) const;

    void DistortPoints(const std::vector<cv::Point2f>& in, std::vector<cv::Point2f>& out) const;

    /**
     * undistort a 2d point
    */
    void UndistortPoints(const std::vector<Vector2>& in, std::vector<Vector2>& out, const Matrix3& new_k) const;

    void UndistortPoints(const std::vector<cv::Point2f>& in, std::vector<cv::Point2f>& out, const Matrix3& new_k) const;

    /**
     * undistort image
     */
    void UndistortImage(const cv::Mat& in, cv::Mat& out);

    /**
     * get a initial position in ground coordinate
     * corresponding to a pixel
     */
    Vector3 QueryInitPosition(Scalar x, Scalar y) const;

    /**
     * get pose from ground to camera coordinate
     */
    Pose3 GetPoseGround2Camera() const;

    /**
     * get pose from ground to novatel
     */
    Pose3 GetPoseGround2Novatel() const;

    /**
     * get novatel to ground height
    */
    Scalar GetHeightNovatel2Ground() const;

private:
    /**
     * load camera intrinsic parameters
    */
    void LoadIntrinsicParams(const std::string& fn);

    /**
     * load camera extrinsic parameters
    */
    void LoadExtrinsicParams(const std::string& fn);

    /*
     * compute init_map_ with
     * 1. plane hypothesis
     * 2. extrinsic from camera to novatel
     * 3. extrinsic from novatel to ground
     * 4. intrinsic of camera
     * the coordinate system of ground has the same of with novatel and
     * is translated along -z axis of novatel with novatel2ground_ meter
     */
    void ComputeInitMap();

private:
    /// intrinsic params
    CameraModel::Value mode_;
    int32_t   resolution_x_;   // image width
    int32_t   resolution_y_;   // image height
    Matrix3   k_;              // k matirx of camera
    Matrix3   k_inv_;          // inverse k matrix of camera
    Matrix3   new_k_;
    Matrix3   new_k_inv_;
    Vector8   d_;
    cv::Mat   cv_k_;
    cv::Mat   cv_k_inv_;
    cv::Mat   cv_new_k_;
    cv::Mat   cv_new_k_inv_;
    cv::Mat   cv_d_;

    /// extrinsic params, pose is from novatel to camera coordinate
    /// base coordinate is novatel
    Scalar camera_height_;
    Scalar pitch_degree_;   // angle, not radian
    Scalar yaw_degree_;     // angle, not radian
    Scalar roll_degree_;    // angle, not radian
    Scalar pitch_radian_;   // radian, not degree
    Scalar yaw_radian_;     // radian, not degree
    Scalar roll_radian_;    // radian, not degree

    holo::Intrinsicf intrinsic_;

    /// novatel coordinate x:right y:forward z:up
    /// camera coordinate x:right y:down z:forward
    /// ground coordinate the same as novatel coordinate

    /// extrinsic from camera to novatel
    holo::Extrinsicf extrinsic_;

    /// initial position map which contians a initial position
    /// for each pixel on undistorted image
    cv::Mat init_map_;

    /// translation along z axis from novatel to ground
    Scalar novatel2ground_;
};

}   // end namespace perception
}   // end namespace holo

#endif  // HOLO_PERCEPTION_COMMON_CAMERA_MODEL_H_