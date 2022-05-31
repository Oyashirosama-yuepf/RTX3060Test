/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_types.h
 * @brief Renaming common types.
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-08-30
 */

#ifndef HOLO_CALIBRATION_DEV_COMMON_TYPES_H_
#define HOLO_CALIBRATION_DEV_COMMON_TYPES_H_

#include <holo/3d/common/io.h>
#include <holo/3d/filter/voxel_grid_filter.h>
#include <holo/3d/registration/gicp.h>
#include <holo/3d/registration/super_fpcs.h>
#include <holo/calibration/apriltag_cpp/apriltags2_adapter.h>
#include <holo/calibration/apriltag_cpp/tag_detection.h>
#include <holo/localization/sam/sam.h>

namespace holo
{
namespace calibration
{
/**
 *  @addtogroup calibration
 *  @{
 *
 */
///@brief core types of holo
using Scalar      = holo::float64_t;
using Scalar_32_t = holo::float32_t;
using bool_t      = holo::bool_t;

///@brief basic types of holo::common
using Extrinsicf = holo::common::ExtrinsicT<Scalar_32_t>;
using Extrinsicd = holo::common::ExtrinsicT<Scalar>;
using Coordinate = holo::common::Coordinate;

///@brief basic types of holo::numerics
using Vector3 = holo::numerics::Vector3T<Scalar>;

///@brief basic types of holo::geometry
using Pose3  = holo::geometry::Pose3T<Scalar>;
using Rot3   = holo::geometry::Rot3T<Scalar>;
using Point3 = holo::geometry::Point3T<Scalar>;
using Point2 = holo::geometry::Point2T<Scalar>;

///@brief basic types of holo::pointcloud
using PointT              = holo::pointcloud::PointXYZIRSt<Scalar_32_t>;
using PointCloud          = holo::pointcloud::PointCloudT<PointT>;
using PointCloudPtr       = std::shared_ptr<PointCloud>;
using PointNormalT        = holo::pointcloud::PointXYZNormalt<Scalar_32_t>;
using PointCloudNormal    = holo::pointcloud::PointCloudT<PointNormalT>;
using PointCloudNormalPtr = std::shared_ptr<PointCloudNormal>;
using SuperFPCS           = holo::pointcloud::SuperFPCST<PointT, PointT, Scalar>;
using SuperFPCSParams     = SuperFPCS::Parameters;
using GICP                = pointcloud::GICPT<PointT, PointT, Scalar>;
using KdTree              = pointcloud::KdTreeT<PointT, Scalar_32_t>;
using KdTreeParameters    = pointcloud::KdTreeParameters;
using KdTreePtr           = KdTree::Ptr;
using VoxelGridFilter     = holo::pointcloud::VoxelGridFilterT<PointT, false>;

///@brief types in localization base
using namespace holo::localization;

///@brief Calibration status
enum CalibrationStatus
{
    ///@brief Need help message
    NEED_HELP = -2,

    ///@brief Calibration is fail
    FAILURE = -1,

    ///@brief Calibration is successful
    SUCCESS = 0,

    ///@brief Lack of algorithm parameter file of lidar-camera calibration
    LACK_ALGO_PARA_FILE = 1,

    ///@brief Lack of camera data (images)
    LACK_CAMERA_DATAS = 2,

    ///@brief Lack of lidar data (point clouds)
    LACK_LIDAR_DATAS = 3,

    ///@brief The number of camera datas is not equal to lidar datas
    UNEQUAL_DATA_NUMBER = 4,

    ///@brief Lack of Apriltag database
    LACK_APRILTAG_DATABASE = 5,

    ///@brief Lack of Riegle database
    LACK_RIEGL_DATABASE = 6,

    ///@brief Lack of camera intrinsic file
    LACK_CAMERA_INTRINSIC_FILE = 7,

    ///@brief Unknown status
    UNKNOWN = 127
};
/**
 * @}
 */
}  // namespace calibration
}  // namespace holo

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
///@brief basic types of gtsam
using GTVector8  = gtsam::Vector8;
using GTVector9  = gtsam::Vector9;
using GTVectorXd = gtsam::Vector;

///@brief basic types of Eigen
using EigVector2 = Eigen::Vector2d;

///@brief basic types of cv
using CvPoint2f   = cv::Point2f;
using CvPoint2d   = cv::Point2d;
using CvPoint3f   = cv::Point3f;
using CvPoint3d   = cv::Point3d;
using CvSize      = cv::Size;
using CvMat       = cv::Mat;
using CvKeyPoint  = cv::KeyPoint;
using CvVector3d  = cv::Vec3d;
using CvVector4d  = cv::Vec4d;
using CvVector5d  = cv::Vec<double, 5>;
using CvMatrix33d = cv::Matx33d;

///@brief basic types of AprilTag2
using AprilTagDatabase    = holo::calibration::AprilTagDatabase;
using AprilTagDatabasePtr = AprilTagDatabase::Ptr;
using AprilTagDetector    = AprilTags2::AprilTags2Adapter;
using TagDetection        = AprilTags2::TagDetection;

/**
 * @brief  A pair of 2D-3D corresponding points.
 *
 */
struct PointCorrespondence
{
    /**
     * @brief Advanced constructor
     * @param[in] image_point 2D corner point detected on a image.
     * @param[in] object_point 3D point corresponding to the 2D corner point.
     */
    PointCorrespondence(CvPoint2f const& image_point, CvPoint3f const& object_point)
      : image_point(image_point), object_point(object_point)
    {
    }

    ///@brief 2D corner point detected on a image.
    CvPoint2f image_point;
    ///@brief 3D point corresponding to the 2D corner point.
    CvPoint3f object_point;
};  // PointCorrespondence

struct CameraCalibrateParameters
{
    CameraCalibrateParameters() = default;

    CameraCalibrateParameters(holo::yaml::Node const& node)
    {
        error_tolerance = node["error_tolerance"].as<Scalar>();
        sigma           = node["sigma"].as<Scalar>();
        fov             = node["fov"].as<Scalar>();
    }

    CameraCalibrateParameters(YAML::Node const& node, std::string const& camera_name)
    {
        error_tolerance = node[camera_name]["error_tolerance"].as<Scalar>();
        sigma           = node[camera_name]["sigma"].as<Scalar>();
        fov             = node[camera_name]["fov"].as<Scalar>();
    }

    ///@brief Tolerance of re-projection error.
    Scalar error_tolerance;  ///< error tolerance of camera
    Scalar sigma;            ///< measurement noise of camera

    /**
     * @brief Limit the field of view of camera
     *
     * @details Only the image points in FOV will be consider
     */
    Scalar fov;
};  // CameraCalibrateParameters
/**
 * @}
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo

namespace holo
{
namespace calibration
{
namespace lidar
{
/**
 *  @addtogroup lidar
 *  @{
 *
 */
/**
 * @brief This is struct store parameters for lidar registration
 *
 */
struct LidarCalibrateParameters
{
    /**
     * @brief define parameters for GICP
     */
    struct GICPParameters
    {
        uint16_t max_iterations;  ///< the maximum number of iterations the registration algorithm can run for.
        Scalar   max_correspondence_distance;  ///< the maximum correspondence distance used in kdtree search. Unit[m]
        Scalar   rotation_epsilon;     ///< the maximum rotation difference between two consecutive transformations
        Scalar   translation_epsilon;  ///< the maximum translation difference between two consecutive transformations
        Scalar   euclidean_fitness_epsilon;  ///< the maximum allowed Euclidean error between two consecutive icp steps
        uint16_t knn;                        ///< k neighbors for computing covariances
        bool_t   verbose;                    ///< verbose flag
    };

    LidarCalibrateParameters() = default;

    LidarCalibrateParameters(holo::yaml::Node const& node)
    {
        ///@brief Set Super 4PCS algorithm parameters
        with_super_fpcs = node["SuperFPCSParams"]["with_super_fpcs"].as<bool_t>();

        if (with_super_fpcs)
        {
            super_fpcs_parameters.delta               = node["SuperFPCSParams"]["delta"].as<Scalar>();
            super_fpcs_parameters.distance_factor     = node["SuperFPCSParams"]["distance_factor"].as<Scalar>();
            super_fpcs_parameters.approximate_overlap = node["SuperFPCSParams"]["approximate_overlap"].as<Scalar>();
            super_fpcs_parameters.expected_overlap    = node["SuperFPCSParams"]["expected_overlap"].as<Scalar>();
            super_fpcs_parameters.sample_size         = node["SuperFPCSParams"]["sample_size"].as<int64_t>();
            super_fpcs_parameters.base_diameter_fraction =
                node["SuperFPCSParams"]["base_diameter_fraction"].as<Scalar>();
            super_fpcs_parameters.max_normal_diff = node["SuperFPCSParams"]["max_normal_diff"].as<Scalar>();
            super_fpcs_parameters.max_translation_distance =
                node["SuperFPCSParams"]["max_translation_distance"].as<Scalar>();
            super_fpcs_parameters.max_angle = node["SuperFPCSParams"]["max_angle"].as<Scalar>();
            super_fpcs_parameters.min_distance_threshold =
                node["SuperFPCSParams"]["min_distance_threshold"].as<Scalar>();
            super_fpcs_parameters.num_diameter_trials = node["SuperFPCSParams"]["num_diameter_trials"].as<int64_t>();
            super_fpcs_parameters.max_time_elapsed    = node["SuperFPCSParams"]["max_time_elapsed"].as<Scalar>();
            super_fpcs_parameters.verbose             = node["SuperFPCSParams"]["verbose"].as<bool_t>();
        }

        ///@brief Set GICP algorithm parameters
        gicp_parameters.max_iterations = node["GICPParameters"]["max_iterations"].as<uint16_t>();
        gicp_parameters.max_correspondence_distance =
            node["GICPParameters"]["max_correspondence_distance"].as<Scalar>();
        gicp_parameters.rotation_epsilon          = node["GICPParameters"]["rotation_epsilon"].as<Scalar>();
        gicp_parameters.translation_epsilon       = node["GICPParameters"]["translation_epsilon"].as<Scalar>();
        gicp_parameters.euclidean_fitness_epsilon = node["GICPParameters"]["euclidean_fitness_epsilon"].as<Scalar>();
        gicp_parameters.knn                       = node["GICPParameters"]["knn"].as<uint16_t>();
        gicp_parameters.verbose                   = node["GICPParameters"]["verbose"].as<bool_t>();

        error_tolerance    = node["error_tolerance"].as<Scalar>();
        sigma              = node["sigma"].as<Scalar>();
        resolution         = node["RefDatabase"]["resolution"].as<Scalar>();
        normal_knn         = node["RefDatabase"]["normal_knn"].as<int64_t>();
        associate_knn      = node["DualPointCloudsAssociatorBase"]["associate_knn"].as<uint16_t>();
        distance_threshold = node["DualPointCloudsAssociatorBase"]["distance_threshold"].as<Scalar>();
    }

    SuperFPCSParams super_fpcs_parameters;
    bool_t          with_super_fpcs;     ///< whether to use Super-4FPCS coarse registration
    GICPParameters  gicp_parameters;     ///< parameters of gicp algorithm
    Scalar          error_tolerance;     ///< error tolerance of lidar
    Scalar          sigma;               ///< measurement noise of lidar
    Scalar          resolution;          ///< Resolution of voxel filter
    int64_t         normal_knn;          ///< The max number of neighbors to be queried for estimating normal.
    uint16_t        associate_knn;       ///< the max number of neighbors to be queried for association
    Scalar          distance_threshold;  ///< threshold of the 3D-3D correspondences point-to-point distance.
};                                       // LidarCalibrateParameters

/**
 * @brief  A pair of 3D-3D corresponding lidar points.
 *
 */
struct LidarCorrespondence
{
    /**
     * @brief Advanced constructor
     *
     * @param[in] source_point source point
     * @param[in] target_point target point with normal
     */
    LidarCorrespondence(PointT const& source_point, PointNormalT const& target_point)
      : source_point(source_point), target_point(target_point)
    {
    }

    PointT       source_point;  ///< source point
    PointNormalT target_point;  ///< target point with normal

};  // LidarCorrespondence
/**
 * @}
 */
}  // namespace lidar
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_COMMON_TYPES_H_
