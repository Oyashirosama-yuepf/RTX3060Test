/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_intrinsic_calibration_base.h
 * @brief Base class for camera calibration
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-08-12
 */

#ifndef HOLO_CALIBRATION_DEV_CAMERA_INTRINSIC_CALIBRATION_BASE_H_
#define HOLO_CALIBRATION_DEV_CAMERA_INTRINSIC_CALIBRATION_BASE_H_

#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

#include <holo/calibration/camera/field/types.h>
#include <holo/calibration/dev/common_types.h>
#include <holo/common/details/intrinsic.h>
#include <holo/core/exception.h>
#include <holo/log/hololog.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 *  @addtogroup camera
 *  @{
 *
 */
using Model = holo::calibration::camera::CameraModel;
/**
 * @brief This is a base class for camera calibration
 */
class CameraIntrinsicCalibrationBase
{
public:
    ///@brief Default constructor.
    CameraIntrinsicCalibrationBase() : is_plane_mode_(false), verbose_(false), visualize_(false)
    {
    }

    /**
     * @brief Advanced constructor
     * @param[in] camera_model Camera len models, currently PINHOLE, FISHEYE and OCAM are supported.
     * @param[in] sensor_id A sensor-id is consist of three parts: Category, Model and Location.
     * @param[in] verbose Whether print log information.
     * @param[in] visualize Whether visualize crucial processes.
     * @param[in] is_plane_mode Whether all calibration objects on one plane.
     */
    CameraIntrinsicCalibrationBase(Model const& camera_model, holo::common::SensorId const& sensor_id,
                                   bool_t const& verbose, bool_t const& visualize, bool_t const& is_plane_mode)
      : camera_model_(camera_model)
      , sensor_id_(sensor_id)
      , is_plane_mode_(is_plane_mode)
      , verbose_(verbose)
      , visualize_(visualize)
    {
        LOG_IF(INFO, verbose_) << "CameraIntrinsicCalibrationBase --- Call advanced constructor";
    }

    /**
     * @brief Destructor
     */
    virtual ~CameraIntrinsicCalibrationBase() noexcept = default;

    /**
     * @brief Interface function to calibrate camera.
     * @param[in] multi_images Input source image sequence.
     * @return True if the calibration algorithm is successful. Otherwise, false.
     */
    bool_t Compute(std::vector<CvMat> const& multi_images);

    /**
     * @brief Template function, save the intrinsic file (yaml type) to the specified path.
     * @tparam IntrinsicType Type of camera's intrinsic.
     * @param[in] intrinsic Type of camera's intrinsic, currently Pinhole, Fisheye, Omnidirectional are supported.
     * @param[in] intrinsic_output_path The path to which the file should be written.
     * @note Currently, only absolute paths(output_path) are supported.
     */
    template <typename IntrinsicType>
    void Save(IntrinsicType const& intrinsic, std::string const& intrinsic_output_path) const
    {
        YAML::Node node(intrinsic);

        std::ofstream out(intrinsic_output_path);
        out << node;
        out.close();

        LOG(INFO) << "CameraIntrinsicCalibrationBase::Save() --- the " << typeid(IntrinsicType).name()
                  << " type's intrinsic has been saved to " << intrinsic_output_path;
    }

    /**
     * @brief Set field of view of omnidirectional camera.
     *
     * @param[in] fov Field of view
     */
    void SetFov(Scalar const fov)
    {
        fov_ = fov;
    }

    /**
     * @brief Set down sample ratio
     *
     */
    void SetDownSampleRatio(Scalar const down_sample_ratio)
    {
        down_sample_ratio_ = down_sample_ratio;
    }

protected:
    /**
     * @brief Pure virtual function, supply to function Compute().
     * @param[in] multi_images Input image sequence.
     * @return True if the calibration algorithm is successful. Otherwise, false.
     */
    virtual bool_t run(std::vector<CvMat> const& multi_images) = 0;

    /**
     * @brief Process each source image to get multi-correspondences.
     * @param[in] source_images Input source image sequence.
     * @param[in] apriltag_db  Shared pointer of AprilTagDatabase, which should be generated using the specified
     *                         application "generate_apriltag_database", please refer to it's documentation for more
     *                         details.
     * @return Sequence of multi-correspondences.
     */
    std::vector<std::vector<PointCorrespondence>> processImages(std::vector<CvMat> const&  source_images,
                                                                AprilTagDatabasePtr const& apriltag_db) const;

    /**
     * @brief Project 3D points to the image plane if get specific intrinsic and extrinsic.
     * @tparam IntrinsicType Type of camera's intrinsic.
     * @param[in] intrinsic Type of camera's intrinsic, currently Pinhole, Fisheye, Omnidirectional are supported.
     * @param[in] correspondence a pair of 2D-3D corresponding points.
     * @param[in] cTw Camera's pose (from world frame to camera frame).
     * @return Projected point of a 3D point and its status.
     */
    template <typename IntrinsicType>
    std::pair<bool_t, CvPoint2f> project(IntrinsicType const& intrinsic, PointCorrespondence const& correspondence,
                                         Pose3 const& cTw) const
    {
        ///@brief Transform 3D point from world frame to camera frame.
        Point3 point3d_world(correspondence.object_point.x, correspondence.object_point.y,
                             correspondence.object_point.z);
        Point3 point3d_camera = cTw.TransformFrom(point3d_world);
        ///@brief Project 3D point via custom Projector
        bool_t point2d_status = false;
        Point2 point2d;

        if (intrinsic.GetModel() == camera::CameraIntrinsicBase::Model::PINHOLE ||
            intrinsic.GetModel() == camera::CameraIntrinsicBase::Model::FISHEYE)
        {
            if (point3d_camera.GetZ() > 0.0)
            {
                point2d_status = true;
                intrinsic.Project(point3d_camera, point2d);
            }
            else
            {
                point2d_status = false;
                point2d        = Point2(-1.0, -1.0);
            }
        }
        else if (intrinsic.GetModel() == camera::CameraIntrinsicBase::Model::OMNIDIRECTIONAL)
        {
            point2d_status = true;
            intrinsic.Project(point3d_camera, point2d);
        }
        else
        {
            std::stringstream ss;
            ss << "CameraIntrinsicCalibrationBase::project() --- invalid camera len model";
            LOG(ERROR) << ss.str();
            throw holo::exception::OutOfRangeException(ss.str());
        }

        return std::make_pair(point2d_status, CvPoint2f(point2d.GetX(), point2d.GetY()));
    }

    /**
     * @brief Calculate the mean projection error.
     * @tparam IntrinsicType Type of camera's intrinsic.
     * @param[in] intrinsic Type of camera's intrinsic, currently Pinhole, Fisheye, Omnidirectional are supported.
     * @param[in] correspondences_seq A sequence of 2D-3D corresponding points.
     * @param[in] multi_cTw A set of camera pose (from world frame to camera frame).
     * @return The mean projection error.
     */
    template <typename IntrinsicType>
    std::vector<Scalar> evaluate(IntrinsicType const&                                 intrinsic,
                                 std::vector<std::vector<PointCorrespondence>> const& correspondences_seq,
                                 std::vector<Pose3> const&                            multi_cTw) const
    {
        std::vector<Scalar> errors;  ///< vector of average projection error of each image
        uint16_t const      sequence_size = correspondences_seq.size();  ///< size of multi-correspondences sequence

        for (uint16_t image_ind = 0u; image_ind < sequence_size; image_ind++)
        {
            Scalar                 separate_err = 0.0;  ///< projection error for a camera view
            std::vector<CvPoint2f> detect_points;       ///< a set of 2D measurement points (detected 2D corner points)
            std::vector<CvPoint2f> project_points;      ///< a set of 2D observation points (projected 3D points)
            uint32_t const         number_of_points = correspondences_seq[image_ind].size();  ///< number of points

            for (uint32_t point_ind = 0u; point_ind < number_of_points; point_ind++)
            {
                ///@brief Get a measurement point and a observation point
                CvPoint2f const detect_point = correspondences_seq[image_ind][point_ind].image_point;
                bool_t          project_point_status;
                CvPoint2f       project_point;
                std::tie(project_point_status, project_point) =
                    project<IntrinsicType>(intrinsic, correspondences_seq[image_ind][point_ind], multi_cTw[image_ind]);

                ///@brief Accumulate projection error of each point.
                if (project_point_status)
                {
                    separate_err += cv::norm(project_point - detect_point);
                }
                else  ///< penalty error function
                {
                    separate_err += 30.0;
                }

                ///@brief Construct vectors containing 2D measurement points and 2D observation points for
                ///       visualization.
                detect_points.push_back(detect_point);
                project_points.push_back(project_point);
            }
            ///@brief Visualize the projection image.
            if (visualize_)
            {
                CvMat projection_image = drawProjectionResult(detect_points, project_points, source_images_[image_ind]);
                std::string const window_name = "projection image";
                cv::namedWindow(window_name, cv::WINDOW_NORMAL);
                cv::imshow(window_name, projection_image);
                cv::waitKey(0);
            }
            ///@brief Compute the mean projection error of all points in one image.
            separate_err /= number_of_points;
            LOG_IF(INFO, verbose_) << "The average projection error of all points in the [" << image_ind
                                   << "th] image is:  " << separate_err;

            errors.push_back(separate_err);
        }
        return errors;
    }

    /**
     * @brief Draw the detected points and projection points on a image.
     * @param[in] detected_points Detected 2D corner points on input image.
     * @param[in] reprojected_points Image points which are the projection results of 3D points use function
     * project().
     * @param[in] source_image Input source image.
     * @note If the src_image encoding is GRAYSCALE, visual interface GUI may be gray rather than RGB, so it's best
     * to use RGB images for visualization.
     * @return Visualization image.
     */
    CvMat drawProjectionResult(std::vector<CvPoint2f> const& detected_points,
                               std::vector<CvPoint2f> const& reprojected_points, CvMat const& source_image) const;

protected:
    /**
     * @brief Source image sequence
     *
     */
    std::vector<CvMat> source_images_;

    /**
     * @brief A sequence of 2D-3D corresponding points
     *
     */
    std::vector<std::vector<PointCorrespondence>> correspondences_seq_;

    /**
     * @brief Size (width and height) of image
     *
     */
    CvSize image_size_;

    /**
     * @brief Camera lens model (PINHOLE, FISHEYE, OMNIDIRECTIONAL are supported)
     *
     */
    Model camera_model_;

    /**
     * @brief Sensor id
     *
     */
    holo::common::SensorId sensor_id_;

    /**
     * @brief Whether all calibration objects on one plane
     */
    bool_t is_plane_mode_;

    /**
     * @brief Whether output detailed log information.
     *
     */
    bool_t verbose_;

    /**
     * @brief Whether visualize crucial processes.
     *
     */
    bool_t visualize_;

    /**
     * @brief Limit the field of view of camera。
     *
     * @details Only the image points in FOV will be consider
     */
    Scalar fov_ = 160.0;

    /**
     * @brief Down sample ratio to source image
     *
     * @note To speed up Apriltag detection
     */
    Scalar down_sample_ratio_ = 1.0;

};  // CameraIntrinsicCalibrationBase
/**
 * @}
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_CAMERA_INTRINSIC_CALIBRATION_BASE_H_