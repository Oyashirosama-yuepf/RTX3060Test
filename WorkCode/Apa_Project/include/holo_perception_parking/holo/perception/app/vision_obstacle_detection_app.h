/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vision_obstacle_detection_app.h
 * @brief This header file defines vision obstacle detection app class.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2022-03-01"
 */

#ifndef HOLO_PERCEPTION_VISION_OBSTACLE_DETECTION_APP_H_
#define HOLO_PERCEPTION_VISION_OBSTACLE_DETECTION_APP_H_

#include <holo/common/image.h>
#include <holo/common/odometry.h>
#include <holo/dnn/apps/factory.h>
#include <holo/geometry/pose3.h>
#include <holo/io/common/extrinsic.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/parking/sensors/front_nocopy_image.h>
#include <holo/perception/algorithm/tracking/camera_tracking_algorithm.h>
#include <holo/perception/common/box_object.h>
#include <holo/perception/detection/vision_obstacle_detection_input_checker.h>
#include <holo/perception/space_convertor/obstacle_3d_estimator.h>
#include <holo/perception/space_convertor/obstacle_3d_smoother.h>
#include <holo/perception/utils/valid_checker.h>
#include <holo/perception/vision_obstacle_detection/bbox2d_filter.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <chrono>
#include <functional>
#include <mutex>
#include <queue>
#include <set>

namespace holo
{
namespace perception
{
class VisionObstacleDetectionApp
{
public:
    using MessagePubType           = obstacle::ObstacleVisionPtrList;
    using PublishCallback          = std::function<void(const MessagePubType&)>;
    using AppStatusPublishCallback = std::function<void(const uint32_t)>;
    using ObstacleVisionType       = holo::obstacle::ObstacleVisionT<float32_t>;
    using ObstacleVisionPtr        = std::shared_ptr<ObstacleVisionType>;
    using CameraDetectedObjectType = BoxObjectT<float32_t, 8U>;
    using CameraDetectedObjectPtr  = std::shared_ptr<CameraDetectedObjectType>;
    using CameraDetectedObjectList = std::list<CameraDetectedObjectPtr>;
    using ImageCache               = std::queue<Image>;
    using TrackingAlgorithmType    = CameraTrackingAlgorithmT<float32_t>;
    using TrackingAlgorithmPtr     = std::shared_ptr<TrackingAlgorithmType>;
    using SpaceConvertorType       = Obstacle3DEstimator;
    using SpaceConvertorPtr        = std::shared_ptr<SpaceConvertorType>;
    using OdometryType             = holo::common::Odometryf;
    using OdometryCache            = std::queue<OdometryType>;
    using Obstacle3DSmootherPtr    = std::shared_ptr<Obstacle3DSmoother>;
    using ObstacleVisionPtrList    = obstacle::ObstacleVisionPtrList;
    using Timestamp                = holo::common::Timestamp;
    using FilterBbox2dType         = FilterBbox2dT<float32_t, 8U>;
    using FilterBbox2dPtr          = std::shared_ptr<FilterBbox2dType>;
    using DnnInterfacePtr          = std::shared_ptr<holo::dnn::DnnInterface>;
    using InputType                = std::vector<cv::Mat>;
    using OutputType               = std::vector<std::vector<ObstacleVisionType>>;
    using SensorId                 = holo::common::SensorId;
    using Point3f                  = holo::geometry::Point3f;
    using FrontCameraData          = holo::parking::sensors::FrontNocopyImage<2u>;
    using ImagePtr                 = std::shared_ptr<FrontCameraData>;
    using InputCheckerType         = VisionObstacleDetectionInputChecker;
    using InputCheckerPtr          = std::shared_ptr<InputCheckerType>;
    using ValidCheckerPtr          = std::shared_ptr<ValidChecker>;

    /**
     * @brief Construct a new VisionObstacleDetectionApp object
     *
     * @param config_file
     * @param hz
     */
    explicit VisionObstacleDetectionApp(std::string const& config_file, float32_t hz = 10.0f)
    {
        initialize(config_file, hz);
    }

    /**
     * @brief Receive Camera Image
     *
     * @return bool_t
     */
    bool_t receiveCameraImage();

    /**
     * @brief
     *
     * @param msg
     * @return bool_t
     */
    bool_t receiveCameraImage(FrontCameraData msg);

    /**
     * @brief Cache the received image
     *
     * @param image
     */
    void CacheCameraImage(Image const& image);

    /**
     * @brief Cache receive image with check
     *
     * @param image
     */
    void CacheCameraImageWithCheck(FrontCameraData const& image);

    /**
     * @brief Cache the received odometry
     *
     * @param msg
     */
    void CacheOdometry(OdometryType const& msg);

    /**
     * @brief Set the PublishCallback object
     *
     * @param publish_callback
     */
    void SetPublishCallback(PublishCallback const& publish_callback);

    /**
     * @brief Set the AppStatus Publish Callback object
     *
     * @param publish_callback
     */
    void SetAppStatusPublishCallback(AppStatusPublishCallback const& publish_callback);

    /**
     * @brief Set the output txt directory
     *
     * @param output_dir, directory for saving detected results
     */
    void SetOutputTxtDir(std::string const& output_dir);

    /**
     * @brief Set the Detection Debug flag
     *
     * @param debug
     */
    void SetDetectionDebug(uint32_t debug);

    /**
     * @brief main pipeline
     * 1. receive front center camera image;
     * 2. detection 2d and 2.5d info;
     * 3. filter;
     * 4. process: tracking, spcace convertor to get 3d info;
     * 5. generate ObstacleVisionList;
     * 6. publish.
     *
     * @return bool_t
     */
    bool_t DoWork();

private:
    /**
     * @brief initialize config and resources
     *
     * @param cfg_file
     * @param hz
     */
    void initialize(std::string const& cfg_file, float32_t hz);

    /**
     * @brief initialize resources for detection 2d
     *
     * @param node
     */
    void initDetection2D(holo::yaml::Node const& node);

    /**
     * @brief initialize resources for filtering
     *
     * @param node
     */
    void initFiltering(holo::yaml::Node const& node);

    /**
     * @brief initialize resources for tracking
     *
     * @param node
     */
    void initTracking(holo::yaml::Node const& node);

    /**
     * @brief init resources for space convertor
     *
     * @param node
     */
    void initSpaceConvertor(holo::yaml::Node const& node);

    /**
     * @brief fetch image
     *
     * @return bool_t
     */
    bool_t fetchData();

    /**
     * @brief get odometry
     *
     * @return bool_t
     */
    bool_t receiveOdometry();

    /**
     * @brief initialize config and resources
     *
     * @param
     */
    void detection2D();

    /**
     * @brief save detection results on image
     *
     */
    void saveInferenceResults();

    /**
     * @brief smooth obstacle 3d post process
     *
     */
    void obstacle3DPostProcess();

    /**
     * @brief Convert camera detected object to vision obstacle

     * @param det_obj
     * @param obs_vis
     */
    void convert(CameraDetectedObjectType const& det_obj, ObstacleVisionType& obs_vis) const;

    /**
     * @brief Generate obstacle vision pointer list
     *
     * @param det_obj_list
     * @param obs_vis_list
     */
    void generateObstacleVision(CameraDetectedObjectList const& det_obj_list, ObstacleVisionPtrList& obs_vis_list);

    /**
     * @brief save detected object list to txt file
     *
     * @param camera_name
     * @param det_obj_list, detected object list
     */
    void saveToTxt(std::string const& camera_name, CameraDetectedObjectList const& det_obj_list) const;

private:
    std::mutex               mutex_;
    size_t                   max_image_cache_size_;
    ImageCache               image_cache_;
    bool                     camera_update_flag_;
    PublishCallback          publish_callback_;
    FilterBbox2dPtr          filter_bbox2d_ptr_;
    TrackingAlgorithmPtr     tracking_algorithm_ptr_;
    SpaceConvertorPtr        space_convertor_ptr_;
    Obstacle3DSmootherPtr    obstacle_smooth_ptr_;
    float32_t                smooth_dt_;  ///< max dt threshold between odometry and image
    OdometryCache            odometry_cache_;
    OdometryType             current_odometry_;
    Timestamp                current_timestamp_;
    std::string              det2d_config_file_;
    DnnInterfacePtr          dnn_interface_ptr_det2d_;
    Image                    current_image_;
    MessagePubType           current_detection_;
    CameraDetectedObjectList detection2d_results_;
    std::set<uint32_t>       vehicle_cat_ids_;
    uint32_t                 speed_bump_cat_id_;
    SensorId                 sensor_id_;
    bool_t                   output_to_file_;
    std::string              output_file_dir_;
    uint64_t                 current_yuv_data_arr_[2U];
    InputCheckerPtr          input_checker_ptr_;
    uint32_t                 current_app_status_;
    AppStatusPublishCallback app_status_publish_callback_;
    uint32_t                 mode_;
    bool_t                   det_debug_;
    float32_t                time_cost_max_;
    ValidCheckerPtr          time_cost_checker;
};

}  // namespace perception
}  // namespace holo

#endif
