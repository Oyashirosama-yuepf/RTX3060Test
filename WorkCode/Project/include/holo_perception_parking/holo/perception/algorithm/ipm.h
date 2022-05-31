/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ipm.h
 * @brief Header file for the IPM algorithm(inverse perspective mapping).
 * @author lizhijian (lizhijian@holomatic.com)
 * @date "2020-02-07"
 */
#ifndef HOLO_PERCEPTION_LIB_ALGO_IPM_H_
#define HOLO_PERCEPTION_LIB_ALGO_IPM_H_

#include <Eigen/Eigen>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

#include <holo/common/extrinsic.h>
#include <holo/common/intrinsic.h>
#include <holo/perception/utils/dg_port.h>
#include "holo/perception/common/camera_config_ex.h"

namespace holo
{
namespace perception
{
/**
 * @addtogroup detection
 *
 * @{
 */

class InversePerspectivMappingBase
{
public:
    InversePerspectivMappingBase(holo::Extrinsicf extrinsic, std::vector<float32_t> body_ground_extrinsic,
                                 float32_t ground_pitch, bool is_gTc = false)
      : extrinsic_(extrinsic)
      , body_ground_extrinsic_(body_ground_extrinsic)
      , ground_pitch_(ground_pitch)
      , is_gTc_(is_gTc)
    {
        if (is_gTc)
        {
            std::vector<float32_t>::iterator it = body_ground_extrinsic_.begin();
            for (; it != body_ground_extrinsic_.end(); it++)
            {
                *it = 0;
            }
        }
    }

    virtual bool TransformPoints(const cv::Mat&, cv::Mat&)
    {
        return false;
    }

    virtual bool TransformPoints(const std::vector<cv::Point2f>&, cv::Mat&)
    {
        return false;
    }

    virtual bool TransformPoints(const std::vector<holo::Point2f>&, std::vector<holo::Point2f>&)
    {
        return false;
    }

    /**
     * @brief transform points or rays from Camera-coordinates to World-coordinates.
     * @param mat_points points or Rays to be transformed from Camera-coordinates to World-coordinates.
     * @return cv::Mat the results
     */
    cv::Mat CamCoord2WorldCoord(cv::Mat mat_points);  // wTc
    /**
     * @brief calculate the points where the rays intersect with the ground plain.
     * @param mat_points points or Rays to be calculated.
     * @return cv::Mat the results
     */
    cv::Mat RayGroundIntersect(const cv::Mat& mat_points);

public:
    // holo::Intrinsicf       intrinsic_;
    holo::Extrinsicf       extrinsic_;
    std::vector<float32_t> body_ground_extrinsic_;

    float32_t ground_pitch_;
    bool      is_gTc_;  // indicate if extrinsic_ is gTc or bTc, default is false.

    cv::Mat cam_pose_rotate_;
    cv::Mat cam_pose_trans_;

    std::vector<bool> valid_intersects_;
};

/**
 * @brief implement of the IPM algorithm (InversePerspectivMapping)
 */
class InversePerspectivMappingFisheye : public InversePerspectivMappingBase
{
public:
    /**
     * @brief the constructor
     * @param intrinsic camera intrinsic.
     * @param new_K new_K for the undistorted image.
     * @param extrinsic camera extrinsic.
     * @param body_pitch_ground pitch that from car body to the ground(in radian).
     * @param ground_pitch ground pitch(in radian).
     * @param body_above_ground height that from the ground to the body(in meters).
     *
     */
    InversePerspectivMappingFisheye(holo::common::FisheyeIntrinsicf specialized_intrinsic, const cv::Mat& new_K,
                                    const holo::Extrinsicf& extrinsic, std::vector<float32_t> body_ground_extrinsic,
                                    float32_t ground_pitch, bool is_gTc = false)
      : InversePerspectivMappingBase(extrinsic, body_ground_extrinsic, ground_pitch, is_gTc)
      , P_(new_K)
      , specialized_intrinsic_(specialized_intrinsic)
    {
        auto cam_pos         = extrinsic_.GetPose();
        auto holo_cam_matrix = cam_pos.ToMatrix();  // holo or eigen
        auto em              = holo::holo2eigen<holo::Matrix4f>(holo_cam_matrix);
        cv::eigen2cv(Eigen::MatrixXf(em.block(0, 0, 3, 3)), cam_pose_rotate_);
        cv::eigen2cv(Eigen::MatrixXf(em.block(0, 3, 3, 1)), cam_pose_trans_);

        /*
        auto D = intrinsic.GetD();
        auto K = intrinsic.GetK();

        _specialized_intrinsic_.SetDistortionParameter(D(0), D(1), D(4), D(5));
        _specialized_intrinsic_.SetFocalLength(K(0, 0), K(0, 1));
        _specialized_intrinsic_.SetPrinciplePoint(K(0, 2), K(1, 2));
        _specialized_intrinsic_.SetSkew(K(0, 1));
        _specialized_intrinsic_.SetDimension(intrinsic.GetDimension()(0), intrinsic.GetDimension()(1));
        _specialized_intrinsic_.SetCoordinate(intrinsic.GetCoordinate());
        */
    }

    /**
     * @brief IPM transform points
     * @param points points to be transformed by IPM.
     * @param [out] results.
     * @return bool
     */
    bool TransformPoints(const cv::Mat& points, cv::Mat& results);  // to be implemented.

    /**
     * @brief IPM transform points
     * @param points points to be transformed by IPM.
     * @param [out] results.
     * @return bool
     */
    bool TransformPoints(const std::vector<cv::Point2f>& points, cv::Mat& results);

    bool TransformPoints(const std::vector<holo::Point2f>& points, std::vector<holo::Point2f>& results);

protected:
    /**
     * @brief Points to Rays
     * @param points points to be transformed to Rays.
     * @return cv::Mat the results
     */
    cv::Mat Points2Ray(const cv::Mat& mat_points);

protected:
    cv::Mat                         P_;  // new_K
    holo::common::FisheyeIntrinsicf specialized_intrinsic_;
};

class InversePerspectivMappingOcam : public InversePerspectivMappingBase
{
public:
    InversePerspectivMappingOcam(holo::common::OmnidirectionalIntrinsicf specialized_intrinsic,
                                 const holo::Extrinsicf& extrinsic, std::vector<float32_t> body_ground_extrinsic,
                                 float32_t ground_pitch, bool is_gTc = false)
      : InversePerspectivMappingBase(extrinsic, body_ground_extrinsic, ground_pitch, is_gTc)
      , specialized_intrinsic_(specialized_intrinsic)
    {
    }

    bool                                    TransformPoints(const std::vector<cv::Point2f>& points, cv::Mat& results);
    holo::common::OmnidirectionalIntrinsicf specialized_intrinsic_;
};

class IpmApp
{
    using Scalar     = holo::float32_t;
    using Pose3Type  = holo::geometry::Pose3T<Scalar>;
    using Point3Type = holo::geometry::Point3T<Scalar>;

private:
    struct ipm_param
    {
        std::shared_ptr<CamConfig> camera_config;
        Eigen::Matrix3d            camera_newK;
        std::vector<float32_t>     body_ground_extrinsic;

        // undistort pts
        cv::Mat K, D, P;

        std::shared_ptr<holo::perception::InversePerspectivMappingBase> ipm_ptr;

        Pose3Type bTc;  // body to camera frame transform
        Pose3Type gTc;  // ground to camera frame transform
    };
    std::map<std::string, ipm_param> ipm_param_map;

public:
    IpmApp(std::vector<std::string> camera_names, std::vector<std::string> camera_config_files);

    void TransformPoints(const std::string& camera_name, const std::vector<cv::Point2f>& points, cv::Mat& results);
};

/*
class InversePerspectivMappingOcamDirectHK : public InversePerspectivMappingBase
{
public:
    InversePerspectivMappingOcamDirectHK(cv::Mat h, cv::Mat k, std::vector<float32_t> body_ground_extrinsic,
                                         float32_t ground_pitch)
      : InversePerspectivMappingBase(holo::Extrinsicf(), body_ground_extrinsic, ground_pitch)
    {
        h_ = h;
        k_ = k;
    }

    bool TransformPoints(const std::vector<cv::Point2f>& points, cv::Mat& results);

    cv::Mat h_;
    cv::Mat k_;
};
*/
/*
class InversePerspectivMappingOcamDirectPose : public InversePerspectivMappingBase
{
public:
    InversePerspectivMappingOcamDirectPose(const holo::Intrinsic& intrinsic,
                                           const holo::Extrinsic& camera_ground_extrinsic,
                                           std::vector<float32_t> body_ground_extrinsic, float32_t ground_pitch)
      : InversePerspectivMappingBase(intrinsic, holo::Extrinsic(), body_ground_extrinsic, ground_pitch)
    {
        camera_ground_extrinsic_ = camera_ground_extrinsic;
    }

    // bool    TransformPoints(const std::vector<cv::Point2f>& points, cv::Mat& results);
    cv::Mat CamCoord2WorldCoord(const cv::Mat& mat_points);  // wTc

    // cv::Mat RayGroundIntersect(const cv::Mat& mat_points);

    holo::Extrinsic camera_ground_extrinsic_;
};
*/

/**
 * @}
 */
}  // namespace perception

}  // namespace holo
#endif  /// HOLO_PERCEPTION_LIB_ALGO_IPM_H_
