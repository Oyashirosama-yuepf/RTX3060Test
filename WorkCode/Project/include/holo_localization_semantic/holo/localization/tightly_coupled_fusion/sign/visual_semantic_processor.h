/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file visual_semantic_processor.h
 * @brief a class which do visual semantic data association
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @author Li Yue (liyue@holomatic.com)
 * @date Dec 28, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_VISUAL_SEMANTIC_PROCESSOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_VISUAL_SEMANTIC_PROCESSOR_H_

#include <glog/logging.h>

#include <holo/os/tictoc_timer.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <holo/common/extrinsic.h>
#include <holo/common/optional.h>

#include <holo/localization/common/types.h>
#include <holo/localization/tightly_coupled_fusion/map/map_service_client_base.h>
#include <holo/localization/tightly_coupled_fusion/sign/bounded_dfs.h>
#include <holo/localization/tightly_coupled_fusion/sign/data_association_problem.h>
#include <holo/localization/tightly_coupled_fusion/sign/likelihood_computer.h>
#include <holo/localization/tightly_coupled_fusion/sign/types.h>
#include <holo/localization/vision/common/image_undistorter.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace sign
{
/**
 * @addtogroup sign
 * @{
 *
 */

/**
 * @brief This class is responsible for the data association of visual semantic detection result and semantic objects in
 * map
 */
class VisualSemanticProcessor
{
public:
    /**
     * @brief Define common type.
     */
    using Ptr                = std::shared_ptr<VisualSemanticProcessor>;
    using ConstPtr           = std::shared_ptr<const VisualSemanticProcessor>;
    using ExtrinsicType      = holo::common::Extrinsicf;
    using LikelihoodComputer = holo::localization::tightly_coupled_fusion::sign::LikelihoodComputer;
    using Classification =
        holo::localization::tightly_coupled_fusion::map::MapServiceClientBase::MapObject::Classification;
    using MapServiceClientBasePtr       = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase::Ptr;
    using VisionSemanticCorrespondences = holo::localization::VisionSemanticCorrespondences;
    using ImageUndistorterType          = ImageUndistorterT<CameraIntrinsicBaseType>;

    /**
     * @brief Define error code.
     */
    enum class Status : uint32_t
    {
        ALLGOOD                   = 0x00000000,  ///< all good
        MAP_CONNECTION_FAILED     = 0x00000001,  ///< map connection is failed
        MAP_DATA_INVALID          = 0x00000002,  ///< map data is invaild
        KEYPOINT_UNAVAILABLE      = 0x00000004,  ///< vision keypoint data is unavailable
        NO_CORRESPONDENCES        = 0x00000008,  ///< no correspondence is created
        LOAD_CAMERA_PARAMS_FAILED = 0x00000010,  ///< failed to load camera intrinsics or extrinsics
    };

    /**
     * @brief Define find correspondences method.
     */
    enum Method : uint32_t
    {
        DISTANCE    = 0u,  ///< By euclidean distance.
        STDDEV      = 1u,  ///< By standard deviation of both horizontical and vertical offset.
        PROBABILITY = 2u,  ///< By maximum posterior probability.
        BOUNDED_DFS = 3u,  ///< By maximum posterior probability with bounded DFS acceleration.
    };

    struct ObjectParameters
    {
        bool_t verbose = false;             ///< verbosity
        Scalar min_semantic_instance_size;  ///< The min size of visual semantic instance. If size less than this
                                            ///< therhold, semantic instance will not be used. (unit: pixel or pixel^2)
        Scalar min_map_object_size;    ///< The min size of map objetc. If size less than this therhold, map object will
                                       ///< not be used (unit: m or m^2)
        Scalar min_reprojection_size;  ///< The min reprojection size of map object. If size less than this therhold,
                                       ///< map object will not be used.(unit: pixel or pixel^2)
        Method data_association_method = Method::BOUNDED_DFS;  ///< Data association method.
        Scalar max_object_count =
            Scalar(6);  ///< max map and image object count of PROBABILITY method. If count larger than this threshold,
                        ///< change to DISTANCE method,because it takes too much time.
        Classification classification_type;  ///< semantic classification.
        uint32_t max_match_pixel_distance;  ///< [DISTANCE] Max match pixel distance of prediction point and measurement
                                            ///< point. If pixel distance greater than max match pixel distance, match
                                            ///< pair will be rejected (unit: pixel)
        Scalar max_ratio = Scalar(0.75);    ///< [DISTANCE] Max ratio between the best two pairs match (ratio = pixel
                                            ///< distace of best match pair / pixel distance of better match pair). If
                                            ///< ratio greater than max ratio, best match pair will be rejected.
        Scalar max_corres_stddev;           ///< [STDDEV] The max of correspondence standard deviation.
        Scalar max_corres_dist;             ///< [STDDEV] The max of correspondence standard deviation.
        Scalar projection_error_sigma;      ///< [PROBABILITY] The standard deviation of reprojection error.
        Scalar max_opposite_side_ratio;  ///< The sign's two oppsite sides's max ratio to judge it is or not a regular
                                         ///< shape. A wrong detection point may create an odd sign shape.
        Scalar max_angle_with_y_axis;    ///< The max angle of pole with photo y axis(unit: degree). The pole should be
                                         ///< parallel to the  y axis, a large angle may respect the detection point is
                                         ///< wrong.
        Scalar max_projection_side_length_ratio;  ///< The max sign side length ratio between image object and project
                                                  ///< map object.
        Scalar min_count;                         ///< The min count of correspondence
        Scalar min_distance_diff;                 ///< The min diff of better and best match pair.
        Scalar max_reprojection_size_ratio;       ///< The max pole reprojection size ratio of match pair
        Scalar min_reprojection_side_length;      ///< Min sign reprojection side length

        /**
         * @brief generate example parameters
         *
         * @return Parameters example parameters
         */
        static ObjectParameters GenerateExample();

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static ObjectParameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief output stream for parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, ObjectParameters const& parameters);
    };

    /**
     * @brief Define the parameters of visual semantic processor.
     */
    struct Parameters
    {
        bool_t               verbose                   = false;  ///< verbosity
        bool_t               enable_visualization      = false;  ///< enable visualization of correspondence result
        Pose3Type            bTc                       = Pose3Type();             ///< the pose of camera in body frame
        FisheyeIntrinsicType camera_intrinsic          = FisheyeIntrinsicType();  ///< the intrinsic of camera.
        Scalar               horizontal_fov            = 150.0;                   ///< horizontal fov;
        Scalar               front_valid_range_of_map  = 150.0;               ///< front valid range of map (unit: m)
        Scalar               behind_valid_range_of_map = 0.0;                 ///< behind valid range of map (unit: m)
        Scalar               upper_valid_range_of_map  = 100.0;               ///< upper valid range of map (unit: m)
        Scalar               below_valid_range_of_map  = 20.0;                ///< below valid range of map (unit: m)
        ObjectParameters     sign_params               = ObjectParameters();  ///< sign object params
        ObjectParameters     pole_params               = ObjectParameters();  ///< pole object params
        Scalar               point_u_sigma             = 5.0;  ///< sigma of point u measurement (unit: pixel)
        Scalar               point_v_sigma             = 5.0;  ///< sigma of point v measurement (unit: pixel)
        Scalar               line_sigma                = 5.0;  ///< sigma of line contour measurement (unit: pixel)
        bool_t is_load_camera_params_succeed = true;  ///< whether or not loading camera intrinsic or extrinsic file
                                                      ///< succeed. [TRUE: succeed, FALSE: failed]

        /**
         * @brief generate example parameters
         *
         * @return Parameters example parameters
         */
        static Parameters GenerateExample();

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief output stream for parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters);
    };

    /**
     * @brief Constructor a new VisualSemanticProcessor object.
     *
     * @param [in] parameters The parameters of visual semantic processor.
     */
    explicit VisualSemanticProcessor(Parameters const& parameters) : params_(parameters)
    {
        if (params_.is_load_camera_params_succeed)
        {
            image_undistorter_ptr_ = std::make_shared<ImageUndistorterType>(
                std::make_shared<FisheyeIntrinsicType>(params_.camera_intrinsic));
        }
    }

    /**
     * @brief Create association between image objects and map objects.
     *
     * @param [in] visual_semantic_raw_measurements vector of visual semantic raw measurements.
     * @param [in] map_service_client_ptr ptr of map service
     * @param [out] correspondences vision semantic correspondences result
     * @return Status error code status
     */
    Status Run(std::vector<VisualSemanticRawMeasurement> const&       visual_semantic_raw_measurements,
               MapServiceClientBasePtr const&                         map_service_client_ptr,
               OptionalT<std::vector<VisionSemanticCorrespondences>>& correspondences) const;

protected:
    /**
     * @brief construct sign measurements
     *
     * @param[in] visual_semantic_raw_measurements visual semantic raw measurements
     * @param[in] map_service_client_ptr ptr of map service
     * @param[out] status error code status
     * @return std::vector<VisualSemanticMeasurement> vector of sign measurement
     */
    std::vector<VisualSemanticMeasurement>
    createVisualSemanticMeasurements(std::vector<VisualSemanticRawMeasurement> const& visual_semantic_raw_measurements,
                                     MapServiceClientBasePtr const& map_service_client_ptr, Status& status) const;

    /**
     * @brief Convert AdvancedNavstate to Odometry
     *
     * @param [in] navstate navstate of vehicle
     * @return OdometryType converted odometry
     */
    OdometryType convertAdvancedNavstateToOdometry(AdvancedNavstateType const& navstate) const;

    /**
     * @brief Get centroid and contour of image object.
     *
     * @param [in] image_objects vector of image object.
     * @param [in] image_object_info_map  map of image object type and object Info
     */
    void getImageObjectCentroidAndContour(
        ImageObjectsType const&                                    image_objects,
        std::map<MapObjectType::Classification, ImageObjectsInfo>& image_object_info_map) const;

    /**
     * @brief compute centroid of image object.
     *
     * @param [in][out] object_double input vector of disordered image object contours,output ordered contours.
     * @param [in] classification classification of objects
     * @param [out] image_object_info_map image object centriod
     * @return true if input data vaild and successfully computed centriod.
     */
    bool_t computeImageObjectsCentroid(std::vector<Point2Type>&            object_double,
                                       holo::Classification::SubType const classification, Point2Type& centroid) const;

    /**
     * @brief Judge image object is or not in range
     *
     * @param [in] image_object_contours vector of image object contours.
     * @return true if this object is in image range, otherwise false.
     */
    bool_t isInImage(std::vector<Point2Type> const& image_object_contours) const;

    /**
     * @brief Get centroid and contour of map object.
     *
     * @param [in] map_objects vector of map object.
     * @param [in] car_pose the pose of car.
     * @param [out] map_objects_info_map map of map classification type and object info.
     */
    void
    getMapObjectCentroidAndContour(std::vector<MapObjectType> const& map_objects, Pose3Type const& car_pose,
                                   std::map<MapObjectType::Classification, MapObjectsInfo>& map_objects_info_map) const;

    /**
     * @brief Judge map object point whether in range
     *
     * @param[in] point_in_world point of map object outline
     * @param[in] car_pose pose of body in world
     * @param[in] camera_pose pose of camera in world
     * @return true if map object in range
     */
    bool_t inRange(Point3Type const& point_in_world, Pose3Type const& car_pose, Pose3Type const& camera_pose) const;

    /**
     * @brief compute centroid of map object.
     *
     * @param [in][out] object_double input vector of disordered image object contours,output ordered.
     * @param [in] classification classification of objects
     * @param [out] image_object_info_map image object centriod
     * @return true if input data vaild and successfully computed centriod
     */
    bool_t computeMapObjectsCentroid(std::vector<Point3Type>& map_contour, MapObjectType::Classification classification,
                                     std::vector<Point2Type>& projection_map_contour, Point3Type& centroid) const;

    /**
     * @brief Create correspondences.
     *
     * @param [in] image_object_info_map vector of image object.
     * @param [in] map_objects_info_map map of map classification type and map object info.
     * @param [in] Pose3Type the pose of car.
     * @return correspondences
     */
    OptionalT<VisionSemanticCorrespondences> createCorrespondence(
        std::map<MapObjectType::Classification, ImageObjectsInfo> image_object_info_map,
        std::map<MapObjectType::Classification, MapObjectsInfo> map_objects_info_map, Pose3Type const& car_pose) const;

    /**
     * @brief Find correspondences between two set by euclidean distance.
     *
     * @param [in] measurements vector of measurement.
     * @param [in] predictions vector of prediction.
     * @param [in] params object params.
     * @return correspondences.
     */
    std::vector<uint32_t> findCorrespondencesDist(std::vector<Point2Type> const& measurements,
                                                  std::vector<Point2Type> const& predictions,
                                                  ObjectParameters const&        params) const;

    /**
     * @brief Find correspondences between two set of by pick the best data association which standard deviation of both
     * horizontal and vertical offset is minimal one.
     *
     * @param [in] measurements vector of measurement.
     * @param [in] predictions vector of prediction.
     * @param [in] params object params.
     * @return correspondences.
     */
    std::vector<uint32_t> findCorrespondencesStdDev(std::vector<Point2Type> const& measurements,
                                                    std::vector<Point2Type> const& predictions,
                                                    ObjectParameters const&        params) const;

    /**
     * @brief Find correspondences between two set of by probability.
     *
     * @note For more details, please refer to Frank document "doc/data_association.pdf".
     * @param [in] measurements vector of measurement.
     * @param [in] predictions vector of prediction.
     * @param [in] params object params.
     * @return correspondences.
     */
    std::vector<uint32_t> findCorrespondencesWithProbability(std::vector<Point2Type> const& measurements,
                                                             std::vector<Point2Type> const& predictions,
                                                             ObjectParameters const&        params) const;

    /**
     * @brief Enumerate all of correspondence vectors with a detection pattern.
     *
     * @param [in] detection_pattern the detection pattern where 1 is represent detected, otherwise undetected.
     * @param [in] num_of_measurements the number of measurements.
     * @return correspondence vectors which is compatible with the detection pattern.
     */
    std::vector<std::vector<uint32_t>> enumerateCorrespondenceVectors(std::vector<bool_t> const& detection_pattern,
                                                                      uint32_t const num_of_measurements) const;

    /**
     * @brief Find correspondences between two set of by probability and accelerate with Bounded
     *        DFS algorithm.
     *
     * @note For more details, please refer to Frank document "doc/data_association.pdf".
     * @param [in] measurements vector of measurement.
     * @param [in] predictions vector of prediction.
     * @param [in] params object params.
     * @return correspondences.
     */
    std::vector<uint32_t> findCorrespondencesWithProbabilityBoundedDfs(std::vector<Point2Type> const& measurements,
                                                                       std::vector<Point2Type> const& predictions,
                                                                       ObjectParameters const&        params) const;

    /**
     * @brief Compute average distance and standard deviation.
     *
     * @param [in] inliers correspondences inliers
     * @param [in] image_object_info image object
     * @param [in] map_objects_info map object.
     * @param [in] classification object classification.
     * @param [out] valid_inliers_count count of inliers
     * @return return a pair<distance, standard_deviation>
     */
    std::pair<Scalar, Scalar> computeAverageDistanceAndStandardDeviation(
        std::vector<uint32_t> const& inliers, ImageObjectsInfo const& image_object_info,
        MapObjectsInfo const& map_object_info, MapObjectType::Classification const& classification,
        uint32_t& valid_inliers_count) const;

    /**
     * @brief Re-project 3d point in world frame to image plane with camera pose and calibration.
     *
     * @param [in] point map point in world frame.
     * @param [in] pose camera pose.
     * @return reprojection point.
     */
    Point2Type reproject(Point3Type const& point, Pose3Type const& pose) const;

    /**
     * @brief Sort clockwise in left-hand coordinate
     *
     * @param [in] points input vector of points.
     * @return return vector of clockwisely sorted points index
     */
    std::vector<uint32_t> clockWiseSort(std::vector<Point2Type> const& points) const;

    /**
     * @brief Convert holo point to opencv points
     *
     * @param points vector of points in holo format
     * @return vector of points in opencv format
     */
    std::vector<cv::Point> convert(std::vector<Point2Type> const& points) const;

    const Parameters          params_;                 ///< the parameters of visual semantic processor.
    ImageUndistorterType::Ptr image_undistorter_ptr_;  ///< the image undistorter.
};

/**
 * @}
 *
 */

}  // namespace sign
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_VISUAL_SEMANTIC_PROCESSOR_H_
