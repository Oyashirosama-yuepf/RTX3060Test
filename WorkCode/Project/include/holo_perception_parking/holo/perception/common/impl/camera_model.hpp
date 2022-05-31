/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-10-09
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_CAMERA_MODEL_HPP_
#define HOLO_PERCEPTION_COMMON_CAMERA_MODEL_HPP_

#include <fstream>

#include <holo/perception2/utils/utility.h>
#include "holo/perception2/common/camera_model.h"

namespace holo
{
namespace perception
{
template <typename Scalar>
CameraModel<Scalar>::CameraModel(const std::string& intrinsic_file, const std::string& extrinsic_file,
                                 const CameraModel<Scalar>::Value& mode)
{
    mode_ = mode;
    LoadIntrinsicParams(intrinsic_file);
    LoadExtrinsicParams(extrinsic_file);
    ComputeInitMap();
}

template <typename Scalar>
void CameraModel<Scalar>::LoadIntrinsicParams(const std::string& fn)
{
    intrinsic_ = holo::Intrinsic::LoadYaml(fn);
    k_         = intrinsic_.K().template cast<Scalar>();
    k_inv_     = k_.inverse();

    new_k_ = k_;
    // new_k_(0,0) *= 0.6;
    // new_k_(1,1) *= 0.6;
    new_k_(0, 0) *= 1.0;
    new_k_(1, 1) *= 1.0;
    new_k_inv_ = new_k_.inverse();

    cv::eigen2cv(k_, cv_k_);
    cv::eigen2cv(k_inv_, cv_k_inv_);
    cv::eigen2cv(new_k_, cv_new_k_);
    cv::eigen2cv(new_k_inv_, cv_new_k_inv_);

    d_ = intrinsic_.D().template cast<Scalar>();

    /*
    holo::yaml::Node node_root = holo::yaml::LoadFile(fn);
    resolution_x_ = node_root["width"].as<int32_t>();
    resolution_y_ = node_root["height"].as<int32_t>();
    */
    resolution_x_ = intrinsic_.Dimension().Width();
    resolution_y_ = intrinsic_.Dimension().Height();

    // initialize mapping matrix according to camera model
    if (mode_ == CameraModel::Value::PINHOLE)
    {
        cv::eigen2cv(intrinsic_.D(), cv_d_);
    }
    else if (mode_ == CameraModel::Value::FISHEYE)
    {
        Vector8 D           = intrinsic_.D().template cast<Scalar>();
        cv_d_               = cv::Mat::zeros(4, 1, CV_64F);
        cv_d_.at<Scalar>(0) = D(0);  // k1
        cv_d_.at<Scalar>(1) = D(1);  // k2
        cv_d_.at<Scalar>(2) = D(4);  // k3
        cv_d_.at<Scalar>(3) = D(5);  // k4
    }
    else
    {
        std::stringstream ss;
        ss << "Undistortion --- unsupported camera model: " << intrinsic_.Model().String();
        LOG(ERROR) << ss.str();
        throw HoloException(ss.str());
    }
}

template <typename Scalar>
void CameraModel<Scalar>::LoadExtrinsicParams(const std::string& fn)
{
    holo::yaml::Node node_root = holo::yaml::LoadFile(fn);
    camera_height_             = node_root["camera_height"].as<Scalar>();
    pitch_degree_              = node_root["pitch"].as<Scalar>();
    yaw_degree_                = node_root["yaw"].as<Scalar>();
    roll_degree_               = node_root["roll"].as<Scalar>();

    pitch_radian_ = holo::Radian(pitch_degree_);
    yaw_radian_   = holo::Radian(yaw_degree_);
    roll_radian_  = holo::Radian(roll_degree_);

    /// translation from novatel to ground
    novatel2ground_ = node_root["novatel2ground"].as<Scalar>();

    std::string parent_coord       = node_root["parent_coord"].as<std::string>();
    std::string child_coord        = node_root["child_coord"].as<std::string>();
    std::string dataset            = node_root["dataset"].as<std::string>();
    std::string car                = node_root["car"].as<std::string>();
    int         calibration_method = node_root["calibration_method"].as<holo::int32_t>();
    ParaseExtrinsicCameraToBody<holo::float64_t>(extrinsic_, node_root["novatel_vlp_extrinsic_file"].as<std::string>(),
                                                 node_root["lidar_front_camera_file"].as<std::string>(),
                                                 node_root["body_gnss_extrinsic_file"].as<std::string>(), parent_coord,
                                                 dataset, child_coord, car, calibration_method);

    /// TODO, load camera extrinsic with holo::Extrinsic
    // std::string extrinsic_file = GetConfigFileAbsolutePath(node_root["extrinsic_file"].as<std::string>());
    // extrinsic_ = holo::Extrinsic::LoadYaml(extrinsic_file);
}

template <typename Scalar>
typename CameraModel<Scalar>::Vector2 CameraModel<Scalar>::Project(const Vector3& in) const
{
    Vector3 output = k_ * in;
    output         = output / output(2);
    return output.head(2);
}

template <typename Scalar>
typename CameraModel<Scalar>::Vector2 CameraModel<Scalar>::Project(const Vector3& in, const Matrix3& k) const
{
    Vector3 output = k * in;
    output         = output / output(2);
    return output.head(2);
}

template <typename Scalar>
typename CameraModel<Scalar>::Point2 CameraModel<Scalar>::Project(const Point3& in) const
{
    Vector2 p = Project(in.Vector());
    return Point2(p);
}

template <typename Scalar>
typename CameraModel<Scalar>::Point2 CameraModel<Scalar>::Project(const Point3& in, const Matrix3& k) const
{
    Vector2 p = Project(in.Vector(), k);
    return Point2(p);
}

template <typename Scalar>
void CameraModel<Scalar>::ProjectPoints(const std::vector<Vector3>& in, std::vector<Vector2>& out) const
{
    out.clear();
    out.reserve(in.size());
    for (auto& p : in)
    {
        Vector2 p_out = Project(p);
        out.push_back(p_out);
    }
}

template <typename Scalar>
void CameraModel<Scalar>::ProjectPoints(const std::vector<Vector3>& in, std::vector<Vector2>& out,
                                        const Matrix3& k) const
{
    out.clear();
    out.reserve(in.size());
    for (auto& p : in)
    {
        Vector2 p_out = Project(p, k);
        out.push_back(p_out);
    }
}

template <typename Scalar>
void CameraModel<Scalar>::ProjectPoints(const std::vector<Point3>& in, std::vector<Point2>& out) const
{
    out.clear();
    out.reserve(in.size());
    for (auto& p : in)
    {
        Point2 p_out = Project(p);
        out.push_back(p_out);
    }
}

template <typename Scalar>
void CameraModel<Scalar>::ProjectPoints(const std::vector<Point3>& in, std::vector<Point2>& out, const Matrix3& k) const
{
    out.clear();
    out.reserve(in.size());
    for (auto& p : in)
    {
        Point2 p_out = Project(p, k);
        out.push_back(p_out);
    }
}

template <typename Scalar>
typename CameraModel<Scalar>::Vector3 CameraModel<Scalar>::Unproject(const Vector2& in) const
{
    Vector3 input;
    input << in(0), in(1), 1;
    Vector3 output = k_inv_ * input;
    output         = output / output(2);
    return output;
}

template <typename Scalar>
typename CameraModel<Scalar>::Vector3 CameraModel<Scalar>::Unproject(const Vector2& in, const Matrix3& k_inv) const
{
    Vector3 input;
    input << in(0), in(1), 1;
    Vector3 output = k_inv * input;
    output         = output / output(2);
    return output;
}

template <typename Scalar>
typename CameraModel<Scalar>::Point3 CameraModel<Scalar>::Unproject(const Point2& in) const
{
    Vector3 p = Unproject(in.Vector());
    return Point3(p);
}

template <typename Scalar>
typename CameraModel<Scalar>::Point3 CameraModel<Scalar>::Unproject(const Point2& in, const Matrix3& k_inv) const
{
    Vector3 p = Unproject(in.Vector(), k_inv);
    return Point3(p);
}

template <typename Scalar>
void CameraModel<Scalar>::UnprojectPoints(const std::vector<Vector2>& in, std::vector<Vector3>& out) const
{
    out.clear();
    out.reserve(in.size());
    for (auto& p : in)
    {
        Vector3 p_out = Unproject(p);
        out.push_back(p_out);
    }
}

template <typename Scalar>
void CameraModel<Scalar>::UnprojectPoints(const std::vector<Vector2>& in, std::vector<Vector3>& out,
                                          const Matrix3& k_inv) const
{
    out.clear();
    out.reserve(in.size());
    for (auto& p : in)
    {
        Vector3 p_out = Unproject(p, k_inv);
        out.push_back(p_out);
    }
}

template <typename Scalar>
void CameraModel<Scalar>::UnprojectPoints(const std::vector<Point2>& in, std::vector<Point3>& out) const
{
    out.clear();
    out.reserve(in.size());
    for (auto& p : in)
    {
        Point3 p_out = Unproject(p);
        out.push_back(p_out);
    }
}

template <typename Scalar>
void CameraModel<Scalar>::UnprojectPoints(const std::vector<Point2>& in, std::vector<Point3>& out,
                                          const Matrix3& k_inv) const
{
    out.clear();
    out.reserve(in.size());
    for (auto& p : in)
    {
        Point3 p_out = Unproject(p, k_inv);
        out.push_back(p_out);
    }
}

template <typename Scalar>
void CameraModel<Scalar>::UndistortPoints(const std::vector<Vector2>& in, std::vector<Vector2>& out,
                                          const Matrix3& new_k) const
{
    // conver to cv type
    std::vector<cv::Point2f> cv_in, cv_out;
    cv_in.reserve(in.size());
    for (size_t i = 0; i < in.size(); i++)
    {
        cv_in.push_back(cv::Point2f(in.at(i).x(), in.at(i).y()));
    }

    UndistortPoints(cv_in, cv_out, new_k);

    // convert back to holo type
    out.clear();
    out.reserve(cv_out.size());
    for (size_t i = 0; i < cv_out.size(); i++)
    {
        out.push_back(Vector2(cv_out.at(i).x, cv_out.at(i).y));
    }
}

template <typename Scalar>
void CameraModel<Scalar>::UndistortPoints(const std::vector<cv::Point2f>& in, std::vector<cv::Point2f>& out,
                                          const Matrix3& new_k) const
{
    cv::Mat tmp_new_k;
    cv::eigen2cv(new_k, tmp_new_k);
    if (mode_ == CameraModel::Value::FISHEYE)
    {
        cv::fisheye::undistortPoints(in, out, cv_k_, cv_d_, cv::Matx33d::eye(), tmp_new_k);
    }
    else
    {
        cv::undistortPoints(in, out, cv_k_, cv_d_, cv::Matx33d::eye(), tmp_new_k);
    }
}

////////////////////////////////////////////////////////////////////////////
template <typename Scalar>
void CameraModel<Scalar>::UndistortImage(const cv::Mat& in, cv::Mat& out)
{
    if (mode_ == CameraModel::Value::FISHEYE)
    {
        cv::fisheye::undistortImage(in, out, cv_k_, cv_d_, cv_new_k_);
    }
    else
    {
        cv::undistort(in, out, cv_k_, cv_d_, cv_new_k_);
    }
}

////////////////////////////////////////////////////////////////////////////
template <typename Scalar>
typename CameraModel<Scalar>::Vector3 CameraModel<Scalar>::QueryInitPosition(Scalar x, Scalar y) const
{
    /// avoid out of range
    size_t col = std::floor(x) > 0 ? std::floor(x) : 0;
    size_t row = std::floor(y) > 0 ? std::floor(y) : 0;
    col        = col >= size_t(resolution_x_) ? size_t(resolution_x_ - 2) : col;
    row        = row >= size_t(resolution_y_) ? size_t(resolution_y_ - 2) : row;

    size_t col_plus_one = (Scalar)col + 1 >= resolution_x_ ? resolution_x_ - 1 : col + 1;
    size_t row_plus_one = (Scalar)row + 1 >= resolution_y_ ? resolution_y_ - 1 : row + 1;

    // compute the initial position by bilinear interpolation
    Scalar    dx        = x - col;
    Scalar    dy        = y - row;
    cv::Vec3d cv_result = init_map_.at<cv::Vec3d>(row, col) * (1 - dx) * (1 - dy) +
                          init_map_.at<cv::Vec3d>(row, col_plus_one) * dx * (1 - dy) +
                          init_map_.at<cv::Vec3d>(row_plus_one, col) * (1 - dx) * dy +
                          init_map_.at<cv::Vec3d>(row_plus_one, col_plus_one) * dx * dy;
    return Vector3(cv_result[0], cv_result[1], cv_result[2]);
}

////////////////////////////////////////////////////////////////////////////
template <typename Scalar>
typename CameraModel<Scalar>::Pose3 CameraModel<Scalar>::GetPoseGround2Camera() const
{
    return (extrinsic_.Pose().Inverse().Cast<Scalar>()) * GetPoseGround2Novatel();
}

////////////////////////////////////////////////////////////////////////////
template <typename Scalar>
typename CameraModel<Scalar>::Pose3 CameraModel<Scalar>::GetPoseGround2Novatel() const
{
    return Pose3(Rot3(), Vector3(0, 0, -novatel2ground_));
}

////////////////////////////////////////////////////////////////////////////
template <typename Scalar>
Scalar CameraModel<Scalar>::GetHeightNovatel2Ground() const
{
    return novatel2ground_;
}

////////////////////////////////////////////////////////////////////////////
template <typename Scalar>
void CameraModel<Scalar>::ComputeInitMap()
{
    init_map_.create(resolution_y_, resolution_x_, CV_64FC3);

    /// position of camera in ground coordinate system
    Vector3 t_gc;
    /// position in novatel
    t_gc = extrinsic_.Pose().Translation().Vector().template cast<Scalar>();
    /// translate from novatel coordinate to ground coordinate
    t_gc(2) += novatel2ground_;

    /// rotation matrix from camera to ground coordinate
    Matrix3 R_gc;
    R_gc = extrinsic_.Pose().Rotation().Matrix().template cast<Scalar>();

    std::fstream ofile("./init_map.txt", std::ios::out);
    for (size_t row_ind = 0; row_ind < (size_t)init_map_.rows; row_ind++)
    {
        for (size_t col_ind = 0; col_ind < (size_t)init_map_.cols; col_ind++)
        {
            Vector3 init_pt3d(-1, -1, -1);

            /// convert from homogeneous coordinate in image coordinate
            /// to direction vector in ground coordinate
            Vector3 pt3d_pixel(col_ind, row_ind, 1.0);
            Vector3 pt3d_normalized_camera = new_k_inv_ * pt3d_pixel;
            Vector3 direction_in_ground    = R_gc * pt3d_normalized_camera;
            direction_in_ground.normalize();

            /// if the direction of light in ground coordinate is horizontal
            /// or toward sky means the plane hypothes is not suitable
            /// -0.001 is about 1000m away from the point on the ground to
            /// the camera
            if (direction_in_ground(2) < -0.001)
            {
                direction_in_ground /= std::abs(direction_in_ground(2));
                /// the crossover point the light and ground under the coordinate
                /// which is place at the position of camera and the attitude
                /// is the same as the coordinate system of the ground
                direction_in_ground *= std::abs(t_gc(2));

                init_pt3d = direction_in_ground + t_gc;
            }

            cv::Vec3d& cv_pt3d = init_map_.at<cv::Vec3d>(row_ind, col_ind);
            for (size_t i = 0; i < 3; i++)
            {
                cv_pt3d[i] = init_pt3d(i);
                ofile << init_pt3d(i) << " ";
            }
            ofile << std::endl;
        }
    }
    ofile.close();
}

}  // namespace perception
}  // namespace holo

#endif  /// HOLO_PERCEPTION_COMMON_CAMERA_MODEL_HPP_
