/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_function.h
 * @brief Some common functions.
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-09-01
 */

#ifndef HOLO_CALIBRATION_DEV_COMMON_FUNCTION_H_
#define HOLO_CALIBRATION_DEV_COMMON_FUNCTION_H_

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <holo/3d/feature/normal.h>
#include <holo/calibration/camera/field/types.h>
#include <holo/calibration/common/data_container_base.h>
#include <holo/calibration/dev/common_types.h>
#include <holo/geometry/polyfit2.h>
#include <holo/localization/sam/type_converter.h>
#include <holo/localization/vision/common/image_undistorter.h>
#include <holo/numerics/eigen_solver.h>
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
/**
 * @brief Get all file names with the given suffix under the input path.
 * @param[in] path Path of files
 * @param[in] suffix Format of files
 * @return Vectors of file names with input suffix in the input path.
 */
std::vector<std::string> GetFiles(const std::string& path, const std::string& suffix);

/**
 * @brief Initialize intrinsic parameters when calibration pattern is on one plane.
 * @param[in] all_image_points 2D image points detected in each image.
 * @param[in] all_object_points 3D corresponding points to 2D image points.
 * @param[in] image_size Size of source images
 * @param[in] verbose Whether print log information
 * @return Intrinsic fx and fy
 */
std::pair<Scalar, Scalar> InitFocalLengthWithPlanar(std::vector<std::vector<CvPoint2f>> const& all_image_points,
                                                    std::vector<std::vector<CvPoint3f>> const& all_object_points,
                                                    CvSize const& image_size, bool_t const verbose,
                                                    CameraModel const& camera_model);

/**
 * @brief Init camera intrinsic parameters when the calibration pattern is not coplanar
 * @param[in] all_image_points 2D image points detected in each image.
 * @param[in] all_object_points 3D corresponding points to 2D image points.
 * @param[in] image_size Size of source images
 * @param[in] verbose Whether print log information
 * @return Intrinsic fx and fy
 */
std::pair<Scalar, Scalar> InitFocalLengthWithNonPlanar(std::vector<std::vector<CvPoint2f>> const& all_image_points,
                                                       std::vector<std::vector<CvPoint3f>> const& all_object_points,
                                                       CvSize const& image_size, bool_t verbose);

/**
 * @brief Normalize 2D points.
 * @param[in] image_points Original 2D points.
 * @param[out] normalized_2d Normalized 2D points.
 * @param[out] normalized_trans2d_inv Inverse of the transformation to normalize point.
 */
void Normalize2DPoints(std::vector<CvPoint2f> const& image_points, std::vector<CvPoint2f>& normalized_2d,
                       Matrix3& normalized_trans2d_inv);

/**
 * @brief Normalize 3D points.
 * @param[in] object_points Original 3D points.
 * @param[out] normalized_3d Normalized 3D points.
 * @param[out] normalized_trans3d The transformation to normalize point.
 */
void Normalize3DPoints(std::vector<CvPoint3f> const& object_points, std::vector<CvPoint3f>& normalized_3d,
                       Matrix4& normalized_trans3d);

/**
 * @brief Construct two constraints by first column of each H34.
 * @param[in] hi ith column of H34
 * @param[in] hj jth column of H34
 * @param[out] vij Constructed vector
 */
void Constructvij(Eigen::Vector3d const& hi, Eigen::Vector3d const& hj, Eigen::Matrix<Scalar, 6, 1>& vij);

/**
 * @brief convert Eigen::VectorX to numerics::VectorX
 *
 * @param[in] src Eigen::VectorXd
 * @param[in][out] tgt Eigen::VectorXd
 */
void EigenConvert(Eigen::VectorXd const& src, numerics::VectorX& tgt);

/**
 * @brief Fit a higher order polynomial.
 *
 * @param points A set of x-y data.
 * @param order Polynomial's order
 * @param[in][out] coeffs Polynomial's coefficients
 * @return Fitting succeed flag and fitting error.
 */
std::pair<bool_t, Scalar> FitPolynomial(std::vector<Point2> const& points, uint16_t const order,
                                        numerics::VectorXd& coeffs);

/**
 * @brief Template class for determining whether a point exceeds the FOV
 *
 * @tparam IntrinsicType Camera intrinsic type
 * @param point A 2d point in pixel plane.
 * @param intrinsic Camera intrinsic
 * @param fov field of view
 * @return True, if this point is not exceeding the FOV; otherwise, is exceeding the FOV.
 */
template <typename IntrinsicType>
bool_t IsPointAvailable(CvPoint2f const& point, IntrinsicType const& intrinsic, Scalar fov)
{
    Point2 point2d(point.x, point.y);
    Point3 point3d_camera;
    intrinsic.Unproject(point2d, point3d_camera);

    ///@brief 3D point
    Scalar x = point3d_camera.GetX();
    Scalar y = point3d_camera.GetY();
    Scalar z = point3d_camera.GetZ();

    ///@brief The angle from the sensor plane
    auto const theta = holo::geometry::Degree<Scalar>(std::atan2(z, std::sqrt(x * x + y * y)));

    if (theta > (90.0 - fov / 2.0))
    {
        return true;
    }

    return false;
}

class CalibrationPatternAssociatorBase
{
public:
    /**
     * @brief Process each source image to get multi-correspondences.
     * @param[in] source_images Input source image sequence.
     * @param[in] apriltag_db  Shared pointer of AprilTagDatabase, which should be generated using the specified
     *                         application "generate_apriltag_database", please refer to it's documentation for more
     *                         details.
     * @param[in] verbose Whether print log information.
     * @param[in] visualize Whether visualize crucial processes.
     * @param[in] down_sample_ratio Image down_sampling ratio: 1.0, 1.5, 2, 3, 4.
     * @return Sequence of multi-correspondences.
     */
    static std::vector<std::vector<PointCorrespondence>> ProcessImages(std::vector<CvMat> const&    source_images,
                                                                       AprilTagDatabase::Ptr const& apriltag_db,
                                                                       bool_t const verbose, bool_t const visualize,
                                                                       Scalar const down_sample_ratio = 1.0);

    /**
     * @brief Process one source image to get multi-correspondences.
     * @param[in] source_image Input source image.
     * @param[in] apriltag_db  Shared pointer of AprilTagDatabase, which should be generated using the specified
     *                         application "generate_apriltag_database", please refer to it's documentation for more
     *                         details.
     * @param[in] verbose Whether print log information.
     * @param[in] visualize Whether visualize crucial processes.
     * @param[in] down_sample_ratio Image down_sampling ratio: 1.0, 1.5, 2, 3, 4.
     * @return Multi-correspondences
     */
    static std::vector<PointCorrespondence> ProcessImage(CvMat const&                 source_image,
                                                         AprilTagDatabase::Ptr const& apriltag_db, bool_t const verbose,
                                                         bool_t const visualize, Scalar const down_sample_ratio = 1.0);

    /**
     * @brief Process tags in source image to get multi-correspondences.
     * @param[in] tag_results  Extracted tags from current image.
     * @param[in] apriltag_db  Shared pointer of AprilTagDatabase, which should be generated using the specified
     *                         application "generate_apriltag_database", please refer to it's documentation for more
     *                         details.
     * @param[in] current_image Current source image in color.
     * @param[in] verbose Whether print log information.
     * @param[in] visualize Whether visualize crucial processes.
     * @return A vector of color image draw within tags and multi-correspondences.
     */
    static std::pair<CvMat, std::vector<PointCorrespondence>> ProcessTags(std::vector<TagDetection> const& tag_results,
                                                                          AprilTagDatabase::Ptr const&     apriltag_db,
                                                                          CvMat const& current_image,
                                                                          bool_t const verbose, bool_t const visualize);

    /**
     * @brief Judge whether a point is in the image.
     * @param[in] u X-coordinate of the image point [unit: pixel].
     * @param[in] v Y-coordinate of the image point [unit: pixel].
     * @param[in] margin Threshold at the edge of the image, default value is 2.0 pixel.
     * @return False if a point isn't in the image.
     */
    static bool_t IsInImage(Scalar const& u, Scalar const& v, CvSize const& image_size, Scalar const& margin = 2.0);

    /**
     * @brief Subpixel correction
     * @param[in] gray_image Grayscale source image, it must be an 8-bit grayscale.
     * @param[in] multi_correspondence A set of 2D-3D corresponding points.
     * @param[in] visualize Whether visualize crucial processes.
     * @note Only 2D image points in multi_correspondence are used.
     * @return A set of 2D-3D corresponding points within refined 2D image points.
     */
    static std::vector<PointCorrespondence> RefineCorner(CvMat const&                            gray_image,
                                                         std::vector<PointCorrespondence> const& multi_correspondence,
                                                         bool_t const                            visualize);
};

/**
 * @brief Transform a binary image to a set of points
 *
 * @details Extract the coordinates of pixels with non-zero value in binary image.
 * @param[in] binary_image Binary image
 * @param[in,out] points A set of points
 * @return True, if success.
 */
bool_t TransformBinaryImageToPoints(CvMat const& binary_image, std::vector<cv::Point2f>& points);

/**
 * @brief Transform a set of points to a binary image
 *
 * @details Set the value of some pixels in the binary image to 255, those pixels whose coordinates are point
 *          coordinates.
 * @param[in] points A set of points
 * @param[in,out] binary_image Binary image
 * @return True, if success.
 */
bool_t TransformPointsToBinaryImage(std::vector<cv::Point2f> const& points, CvMat& binary_image);

/**
 * @brief 'Alpha Shapes' algorithm
 *
 * @details Please see 'Sampling and reconstructing manifolds using alpha-shapes' for details.
 * @details Alpha Shapes can estimate the cursory contour of a set of 2D points.
 * @param[in] points A set of 2D points.
 * @param[in] radius Radius of the fitting circle [unit: m].
 */
std::vector<cv::Point2f> AlphaShape(std::vector<cv::Point2f> const& points, Scalar const radius);

/**
 * @brief Estimate projected point cloud edge's points in ROI
 *
 * @param[in] pointcloud_projection_image The projection image of point cloud
 * @param[in] roi Region of interests
 * @return Projected point cloud's edge points
 */
std::vector<cv::Point2f> Estimate2DPointCloudEdgeInROI(CvMat const& pointcloud_projection_image, cv::Rect const& roi,
                                                       Scalar const radius);
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
 * @addtogroup lidar
 * @{
 *
 */
/**
 * @brief A class for constructing the reference point cloud database
 *
 */
class ReferencePointCloudDataBase
{
public:
    /**
     * @brief Disable default constructor
     *
     */
    ReferencePointCloudDataBase() = delete;

    /**
     * @brief Advanced constructor
     *
     * @param[in] ref_pointcloud_ptr Reference point cloud ptr
     * @param[in] normal_knn The number of neighbors to be queried for estimating normals
     * @param[in] verbose Whether to print verbose log
     */
    ReferencePointCloudDataBase(PointCloudPtr const& ref_pointcloud_ptr, int64_t const normal_knn,
                                bool_t const verbose = false, bool_t const need_boundary = false)
      : ref_pointcloud_ptr_(ref_pointcloud_ptr)
      , normal_knn_(normal_knn)
      , ref_pointcloud_normal_ptr_(new PointCloudNormal())
      , verbose_(verbose)
    {
        LOG_IF(INFO, verbose_) << "ReferencePointCloudDataBase --- Advanced constructor!";
        creatRefPointCloudDatabase(ref_pointcloud_ptr_, ref_pointcloud_tree_ptr_, ref_pointcloud_normal_ptr_,
                                   ref_pointcloud_curvatures_, need_boundary);
    }

    /**
     * @brief Destructor
     *
     */
    virtual ~ReferencePointCloudDataBase() noexcept = default;

    /**
     * @brief Get reference point cloud ptr
     *
     * @return Reference point cloud ptr
     */
    PointCloudPtr GetRefPointCloud() const
    {
        return ref_pointcloud_ptr_;
    }

    /**
     * @brief Get reference point cloud surface normal ptr
     *
     * @return Reference point cloud surface normal ptr
     */
    PointCloudNormalPtr GetRefPointCloudNormal() const
    {
        return ref_pointcloud_normal_ptr_;
    }

    /**
     * @brief Get reference point cloud curvatures
     *
     * @return Reference point cloud curvatures
     */
    std::vector<Scalar_32_t> GetRefPointCloudCurvatures() const
    {
        return ref_pointcloud_curvatures_;
    }

    /**
     * @brief Get reference point cloud boundary
     *
     * @return Reference point cloud boundary ptr
     */
    PointCloudPtr GetRefPointCloudBoundary() const
    {
        return ref_pointcloud_boundary_ptr_;
    }

    /**
     * @brief Get reference point cloud Kdtree Ptr
     *
     * @return Reference point cloud KdTree ptr
     */
    KdTreePtr GetRefPointKdTree() const
    {
        return ref_pointcloud_tree_ptr_;
    }

    /**
     * @brief Save reference point cloud
     *
     * @param[in] file_name Path of reference point cloud file
     */
    void SaveRefPointCloud(std::string const file_name) const
    {
        holo::pointcloud::SavePly<PointT>(file_name, *ref_pointcloud_ptr_);
    }

    /**
     * @brief Save reference point cloud surface normal
     *
     * @param[in] file_name Path of reference point cloud normal file
     */
    void SaveRefPointCloudNormal(std::string const file_name) const
    {
        holo::pointcloud::SavePly<PointNormalT>(file_name, *ref_pointcloud_normal_ptr_);
    }

private:
    /**
     * @brief Estimate surface normal of reference point cloud
     *
     * @param[in] ref_pointcloud_ptr Source reference point cloud ptr
     * @param[in,out] ref_pointcloud_tree KdTree of reference point cloud
     * @param[in,out] ref_pointcloud_normal_ptr Surface normal ptr of reference point cloud
     * @param[in] need_boundary Whether to estimate the boundary of reference point cloud
     */
    bool_t creatRefPointCloudDatabase(PointCloudPtr const& ref_pointcloud_ptr, KdTreePtr& ref_pointcloud_tree,
                                      PointCloudNormalPtr&      ref_pointcloud_normal_ptr,
                                      std::vector<Scalar_32_t>& ref_pointcloud_curvatures_,
                                      bool_t const              need_boundary = false);

    /**
     * @brief Estimate boundary of reference
     *
     * @param[in] ref_pointcloud_ptr Source reference point cloud ptr
     * @param[in] ref_pointcloud_tree KdTree of reference point cloud
     * @param[in] ref_pointcloud_normal_ptr Surface normal ptr of reference point cloud
     * @param[in,out] ref_pointcloud_boundary_ptr Ptr of reference point cloud boundary
     */
    void estimateRefPointCloudBoundary(PointCloudPtr const& ref_pointcloud_ptr, KdTreePtr const& ref_pointcloud_tree,
                                       PointCloudNormalPtr const& ref_pointcloud_normal_ptr,
                                       PointCloudPtr&             ref_pointcloud_boundary_ptr);

    PointCloudPtr            ref_pointcloud_ptr_;  ///< reference point cloud ptr
    int64_t                  normal_knn_;          ///< the number of neighbors to be queried for estimating normals.
    KdTreePtr                ref_pointcloud_tree_ptr_;    ///< KdTree of reference point cloud ptr
    PointCloudNormalPtr      ref_pointcloud_normal_ptr_;  ///< surface normal ptr of reference point cloud
    std::vector<Scalar_32_t> ref_pointcloud_curvatures_;
    PointCloudPtr            ref_pointcloud_boundary_ptr_;  ///< ptr of reference point cloud boundary
    bool_t                   verbose_;                      ///< Whether to print verbose log
};

class DualPointCloudsAssociatorBase
{
public:
    /**
     * @brief Process each pair of point clouds to get multi-correspondences.
     *
     * @param[in] src_pointcloud Source point cloud
     * @param[in] ref_pointcloud_ptr Reference point cloud ptr
     * @param[in] ref_pointcloud_normal_ptr Reference point cloud normal ptr
     * @param[in] ref_pointcloud_curvatures Reference point cloud curvatures
     * @param[in] knn The max number of neighbors to be queried.
     * @param[in] distance_threshold Distance threshold of corresponding points.
     * @param[in] rTs_with_status Source sensor poses in reference sensor coordinate, and their statuses.
     *
     * @return 3D-3D (source point - reference point) correspondences sequence
     */
    static std::vector<std::vector<LidarCorrespondence>>
    ProcessPointcloud(std::vector<PointCloud> const& src_pointclouds, PointCloudPtr const& ref_pointcloud_ptr,
                      PointCloudNormalPtr const& ref_pointcloud_normal_ptr,
                      std::vector<Scalar_32_t> ref_pointcloud_curvatures, uint16_t const knn,
                      Scalar const distance_threshold, std::vector<std::pair<bool_t, Pose3>> const& rTs_with_status);

    /**
     * @brief Check Point
     *
     * @param point Point type with x, y, z, intensity, ring, timestamp
     * @return True, if point's value is finite
     */
    static bool_t IsFinite(PointT const& point);

    /**
     * @brief Check Point
     *
     * @param point Point type with x, y, z, intensity, ring, timestamp
     * @return True, if point's value is zero
     */
    static bool_t IsZero(PointT const& point);
};
/**
 * @}
 */
}  // namespace lidar
}  // namespace calibration
}  // namespace holo

namespace holo
{
namespace calibration
{
/**
 * @addtogroup calibration
 * @{
 *
 */
/**
 * @brief Base class for sensor pose estimation
 *
 */
class SensorPoseEstimatorBase
{
public:
    /**
     * @brief Advanced constructor
     *
     * @param verbose Whether to display verbose log
     */
    SensorPoseEstimatorBase(bool_t const verbose) : verbose_(verbose)
    {
    }

    /**
     * @brief Destructor
     *
     */
    virtual ~SensorPoseEstimatorBase() = default;

    /**
     * @brief Interface for sensor pose estimation
     *
     * @return Sensor pose and its status.
     */
    virtual std::pair<bool_t, Pose3> Run() = 0;

protected:
    bool_t verbose_;  ///< whether to display verbose log
};

/**
 * @brief Class for camera pose estimation
 *
 */
class CameraPoseEstimator : public SensorPoseEstimatorBase
{
    using Base = SensorPoseEstimatorBase;

public:
    /**
     * @brief Disable default constructor
     *
     */
    CameraPoseEstimator() = delete;

    /**
     * @brief Advanced constructor
     *
     * @param pts3 Set of object points
     * @param pts2 Set of image points
     * @param intrinsic Camera intrinsic base ptr
     * @param fov Field of view for map the omnidirectional to pinhole len model
     * @param verbose Whether to display verbose log
     */
    CameraPoseEstimator(std::vector<camera::CvPoint3f> const& pts3, std::vector<camera::CvPoint2f> const& pts2,
                        std::shared_ptr<camera::CameraIntrinsicBase> const& intrinsic, Scalar const fov,
                        bool_t const verbose);

    /**
     * @brief Destructor
     *
     */
    ~CameraPoseEstimator() override = default;

    /**
     * @brief Implementation of camera pose estimation
     *
     * @return Camera pose and its status.
     */
    std::pair<bool_t, Pose3> Run() override;

private:
    /**
     * @brief Set of object points
     *
     */
    std::vector<camera::CvPoint3f> object_points_;

    /**
     * @brief Set of image points
     *
     */
    std::vector<camera::CvPoint2f> image_points_;

    /**
     * @brief Source camera intrinsic
     *
     */
    std::shared_ptr<camera::CameraIntrinsicBase> src_camera_intrinsic_ptr_;

    /**
     * @brief Target camera intrinsic
     *
     */
    std::shared_ptr<camera::PinholeIntrinsic> tgt_camera_intrinsic_ptr_;
};

/**
 * @brief Class for lidar pose estimation
 *
 */
class LidarPoseEstimator : public SensorPoseEstimatorBase
{
    using Base = SensorPoseEstimatorBase;

public:
    /**
     * @brief Disable default constructor
     *
     */
    LidarPoseEstimator() = delete;

    /**
     * @brief Advanced constructor
     *
     * @param src_pointcloud_ptr Source point cloud ptr
     * @param tgt_pointcloud_ptr Target point cloud ptr
     * @param lidar_parameters Parameters for point clouds registration
     * @param verbose Whether to display verbose log
     * @param tTs_guess The guess of the transformation from source coordinate to target coordinate
     */
    LidarPoseEstimator(PointCloudPtr const& src_pointcloud_ptr, PointCloudPtr const& tgt_pointcloud_ptr,
                       lidar::LidarCalibrateParameters const& lidar_parameters, bool_t const verbose,
                       Pose3 const& tTs_guess = Pose3::Identity())
      : Base(verbose)
      , src_pointcloud_ptr_(src_pointcloud_ptr)
      , tgt_pointcloud_ptr_(tgt_pointcloud_ptr)
      , lidar_parameters_(lidar_parameters)
      , tTs_guess_(tTs_guess)
    {
    }

    /**
     * @brief Destructor
     *
     */
    ~LidarPoseEstimator() override = default;

    /**
     * @brief Implementation of lidar pose estimation
     *
     * @return Lidar pose and its status.
     */
    std::pair<bool_t, Pose3> Run() override;

private:
    /**
     * @brief Source point cloud ptr
     *
     */
    PointCloudPtr src_pointcloud_ptr_;

    /**
     * @brief Target point cloud ptr
     *
     */
    PointCloudPtr tgt_pointcloud_ptr_;

    /**
     * @brief Parameters for point clouds registration
     *
     */
    lidar::LidarCalibrateParameters lidar_parameters_;

    /**
     * @brief The guess of the transformation from source coordinate to target coordinate
     *
     */
    Pose3 tTs_guess_;
};

/**
 * @brief Render color to a point cloud
 *
 * @details Assign colors from red to blue according to the distance of points to camera coordinate.
 * @param[in] projection_points_with_depth A set of projection points with depth.
 * @param[in] source_image Source image
 * @param[in] circle_radius Radius of circle representing projected point
 * @param[in] circle_thickness Thickness of circle representing projected point
 * @return Visualization image
 */
camera::CvMat PointCloudShader(std::vector<camera::CvPoint3d> const& projection_points_with_depth,
                               camera::CvMat const& source_image, int64_t const circle_radius = 2,
                               int64_t const circle_thickness = 2);

/**
 * @brief Project the source point cloud to the source image
 *
 * @param[in] src_pointcloud Source point cloud
 * @param[in] src_image Source image
 * @param[in] camera_intrinsic_ptr Camera intrinsic base ptr
 * @param[in] cTl Camera-lidar extrinsic
 * @param[in] min_depth_threshold The minimum depth threshold of projection point
 * @param[in] max_depth_threshold The maximum depth threshold of projection point
 * @param[in] visualize Whether visualize crucial process
 * @param[in] circle_radius Radius of circle representing projected point
 * @param[in] circle_thickness Thickness of circle representing projected point
 * @param[in] shader_method True, render color by point cloud depth, otherwise, by intensity
 * @return Visualization image
 */
camera::CvMat ProjectPointCloudToImage(PointCloud const& src_pointcloud, camera::CvMat const& src_image,
                                       std::shared_ptr<camera::CameraIntrinsicBase> const& camera_intrinsic_ptr,
                                       Pose3 const& cTl, Scalar const min_depth_threshold,
                                       Scalar const max_depth_threshold, holo::bool_t visualize,
                                       int64_t const circle_radius = 2, int64_t const circle_thickness = 2,
                                       bool_t shader_method = true);
/**
 * @}
 */
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_COMMON_FUNCTION_H_
