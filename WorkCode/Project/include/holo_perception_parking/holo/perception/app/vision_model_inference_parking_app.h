/*!
 *  \brief
 *  \author pengcheng (pengcheng@holomatic.com)
 *  \date 2019-08-21
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_APP_VISOIN_MODEL_INFERENCE_H_
#define HOLO_PERCEPTION_APP_VISOIN_MODEL_INFERENCE_H_
#include <holo/common/chassis_state.h>
#include <holo/common/odometry.h>
#include <holo/common/path.h>
#include <holo/common/sensor_id.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <mutex>
#include <queue>
#include <string>
#ifdef TIDL_INFERENCE
#include <holo/perception/app/test_tidl_inference.h>

#else
#include <holo/perception/detection/center_net_parking.h>
#endif

#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/worker.h>
// #include <holo/perception/space_convertor/projection_convertor.h>
#include <holo/perception/utils/class_registry.h>
// #include <holo/perception/detection/image_detector_resource.h>
// #include <holo/perception/utils/utility.h>
//#include <holo/perception/common/box2d.h>

#include <holo/common/details/timestamp.h>
#include <holo/common/extrinsic.h>
#include <holo/common/image.h>
#include <holo/common/intrinsic.h>
#include <holo/map/current_route_info.h>

#include <holo/common/impl/intrinsic.hpp>

#include "holo/perception/common/camera_config_ex.h"
//#include <holo/common/impl/extrinsic.hpp>
#include <holo/perception/algorithm/ipm.h>
#include <holo/perception/algorithm/tracking/bbox_kf_tracker.h>
#include <sys/time.h>

extern std::atomic<int> TERMINATE_STATE;

namespace holo
{
namespace perception
{
/**
 * @brief define the VisionModelINferenceParkingApp class
 */
class VisionModelInferenceParkingApp  //: public Worker
{
public:
    /*

        class CamConfig
        {
            public:
            /**
             * @brief the constructor
             * @param name camera device name.
             * @param intrinsic camera intrinsic.
             * @param extrinsic camera extrinsic.
             * @param scale scale of the image, currently not used(reserved).
             * @param body_pitch_ground pitch that from car body to the ground(in radian).
             * @param imu_above_ground height that from the ground to the imu(in meters).
             * @param ROI_mask binary image that will be used to mask the imput images(all invalid areas will be filled
       with 0).
             /
            // CamConfig(std::string name, holo::Intrinsic intrinsic,holo::Extrinsic extrinsic, float64_t scale, cv::Mat
       &ROI_mask):
            //     name_(name), intrinsic_(intrinsic),extrinsic_(extrinsic),scale_(scale), ROI_mask_(ROI_mask)
            // {
            //     //set defaults.
            //     crop_x_start_ = 140;
            //     crop_y_start_ =  100;
            //     crop_width_ =  1780;
            //     crop_height_ =  920;
            //     do_crop_ =  true;
            //     do_rot_ =  true;
            // }

            CamConfig(std::string name, holo::Intrinsicf intrinsic, holo::Extrinsicf extrinsic,
                     cv::Size2i input_size, cv::Size2i input_resize, cv::Size2i crop_start,cv::Size2i crop_size, cv::Mat
       &ROI_mask, float64_t visible_radius): name_(name), intrinsic_(intrinsic),extrinsic_(extrinsic),
             input_size_(input_size), input_resize_(input_resize),crop_start_(crop_start),crop_size_(crop_size),
       ROI_mask_(ROI_mask),visible_radius_(visible_radius)
            {
                scale_.width = (float)input_resize_.width / (float)input_size_.width;
                scale_.height = (float)input_resize_.height / (float)input_size_.height;
            }

            std::string name_;
            holo::Intrinsicf intrinsic_;
            holo::Extrinsicf extrinsic_;
            // float64_t scale_;

            uint32_t crop_x_start_;
            uint32_t crop_y_start_;
            uint32_t crop_width_;
            uint32_t crop_height_;
            bool do_crop_;
            bool do_rot_;

            cv::Size2i input_size_;
            cv::Size2i input_resize_;
            cv::Size2i crop_start_;
            cv::Size2i crop_size_;
            cv::Mat ROI_mask_;
            float64_t visible_radius_;
            cv::Size2f scale_;
        };

    */
    using ObstacleCamera    = ObstacleVisionT<float32_t>;
    using ObstacleCameraPtr = std::shared_ptr<ObstacleVisionT<float32_t>>;
    typedef typename holo::ObstaclePtrListT<ObstacleVisionT<float32_t>, holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>
        CameraObstacleList;
    typedef typename holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>,
                                            holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>
        ObstacleGeneralList;

    typedef std::list<ObstacleCameraPtr>              ObstacleCameraPtrList;
    typedef std::function<void(CameraObstacleList&)>  ObstacleDetectionCallback;
    typedef std::function<void(ObstacleGeneralList&)> ObstacleGeneralCallback;

    using ImageBBox2DType = ImageBBox2D<float32_t>;

    // typedef holo::Point2T<holo::float32_t> Point2Type;
    typedef holo::Point2f Point2Type;
    // using Point3Type  = holo::geometry::Point3T<float32_t>;
    using Point3Type = holo::Point3f;
    typedef Box2DT<float32_t> Box2DType;

    /**
     * @brief the constructor
     * @param cfg_file the config file path.
     * @param hz the running frequency.
     */
    VisionModelInferenceParkingApp(const std::string cfg_file, std::vector<size_t> camera_flag, float hz = 10);
    /**
     * @brief init the instance with given config file.
     * @param cfg_file the config file path.
     */
    void InitConfig(const std::string cfg_file);
    void InitResources();

    /**
     * @brief sef publish callback
     * @param callback the calllback function.
     * @param camera_name the camera name.
     */
    void SetCallback(ObstacleGeneralCallback callback, const std::string& camera_name);

    /**
     * @brief
     *
     * @param callback
     * @param camera_name
     */
    void SetCallback(ObstacleDetectionCallback callback, const std::string& camera_name);

    /**
     * @breif reveive image
     * @param image the imge that will be put into the receiving container.
     * @param camera_name the camera name.
     */
    void ReceiveImageFromCamera(const holo::Image& image, const std::string& camera_name);

    /**
     * @brief Cache car state
     * @param car_state the car_state that will be cached.
     */
    void CacheCarState(const ChassisState& car_state);

    void CacheInOdometry(const holo::common::Odometryf& input);

    void DeleteInvalidCamera(const std::vector<size_t>& camera_flag);
    /**
     * @brief will be called by the app. receive planning path from the comunication middleware.
     * @param path the planning path.
     */
    void ReceivePlanningPath(const holo::Pathd& path);

    float64_t CalculateGroundPitch();
    /**
     * @brief get senser id
     * @param camera_name the camera name.
     * @param [out] sensor_id the sensor_id will be returned.
     */
    void GetSensorIdByCameraName(const std::string& camera_name, holo::common::SensorId& sensor_id);
    std::vector<std::vector<cv::Point2f>> RefineLine(cv::Mat& img1);
    bool                                  DoWork();

    std::unordered_map<std::string, uint32_t>            sensor_id_;
    std::unordered_map<std::string, std::vector<size_t>> camera_raw_wh_;
    std::vector<std::pair<uint8_t*, uint8_t*>>           image_buff_vector_;
    std::map<std::string, std::pair<uint8_t*, uint8_t*>> image_ptr_map_;
    std::map<std::string, holo::Image>                   image_vector_;

    void CreateStaticImage(std::map<std::string, holo::Image>& image_vector);

    void CreateTidlResource();
    void ReleaseTidlResource();

private:
    /**
     * @brief fetch data for this frame
     */
    void FetchData();

    /**
     * @brief check whether camera time stamp is time out
     * param[in] camera_name - camera name
     * param[return] - true is time out, false is not time out
     */
    bool IsCameraTimeStampTimeOut(const std::string& camera_name) const;

    /**
     * @brief get Image matrix form Cache image
     * param[out] images the Matrixes of images
     */
    void LaunchImages(std::vector<cv::Mat>& images);

    /**
     * @brief receive car state
     */
    bool ReceiveCarState();

    /**
     * @brief public
     */
    void Publish(ObstacleGeneralList& cam_obs_list, const std::string& name);

    /**
     * @brief
     *
     * @param cam_obs_list
     * @param name
     */
    void Publish(CameraObstacleList& cam_obs_list, const std::string& name);

    /**
     * @brief remap in origin size
     */
    void UnmapBox(Box2DType& box, const std::string& camera_name);
    /**
     * @brief checkout time
     */
    void CheckSensorDataTimeout();

    void PostProcess(std::map<std::string, std::list<ImageBBox2D<float32_t>>>& det_objects, int det_flag);
    void publish_camera_detection_obstacle(std::map<std::string, std::list<ImageBBox2D<float32_t>>>& det_objects);

    void GenImageBBoxListUnorderedMap(const ImageBBoxList& bboxes, std::unordered_map<uint64_t, ImageBBox2f>& out_map);

    void LoadCamConfigs();

    /**
     * @brief undistort the image, or just estimate the new_K for the undisorted image.
     * @param camera_name which camera the processing image came from.
     * @param[out] new_K the undistorted image's K.
     * @param only_estimate_new_K indicate whether only the new_K will be estimated or the undistortion will be actually
     * performed.
     */
    bool UndistortImage(const std::string camera_name, Eigen::Matrix3d& new_K, bool only_estimate_new_K = true);

    // void GetCarKeypoints(std::vector<cv::Point2f>& hm_keypoints_tmp,
    //                     std::vector<ImageBBox2D<float32_t>>& car_pts,
    //                     std::vector<std::vector<cv::Point2f>>& car_hm_keypoints);

    /**
     * @brief set obstacle state
     * @param history_camera_track_tmp  the history tracked obstacles
     * @param camera_name the camera where that the obstacle come from
     * @param tracked_id the obstacle tracked id
     * @param pt the obstacle center point
     * @param camera_obstacle_ptr the obstacle ptr
     */
    void SetObstacleState(std::map<uint64_t, std::vector<cv::Point2f>>& history_camera_track_tmp,
                          std::string camera_name, uint64_t tracked_id, cv::Point2f pt,
                          std::shared_ptr<holo::ObstacleGeneralT<float32_t>>& camera_obstacle_ptr);

    /**
     * @brief preprocess all the images that recently received.
     */
    bool PreProcessImages();

    std::unordered_map<std::string, std::shared_ptr<CamConfig>> camera_configs_;
    std::unordered_map<std::string, Eigen::Matrix3d>            camera_newK_;

    std::vector<float32_t> body_ground_extrinsic_;
    std::vector<float32_t> ground_pitch_gradiant_samples_;
    std::vector<float32_t> blind_zone_nearst_coeffs_;

    /// params
    float32_t                                 hz_;
    std::string                               tensorrt_cfg_file_;
    std::string                               tidl_cfg_file_;
    ChassisState                              car_state_;
    int32_t                                   detection_width_;
    int32_t                                   detection_height_;
    std::vector<std::string>                  camera_names_;
    std::vector<size_t>                       camera_flag_;
    std::map<std::string, bool>               camera_update_flag_;
    std::map<std::string, bool>               camera_send_flag_;
    std::map<std::string, bool>               camera_decode_flag_;
    std::vector<std::string>                  camera_config_files_;
    int32_t                                   camera_num_;
    std::unordered_map<std::string, uint32_t> camera_current_counter_;
    float32_t                                 start_y_for_height_query_;
    float32_t                                 end_y_for_height_query_;
    float32_t                                 step_y_for_height_query_;
    float32_t                                 novatel2ground_height_;
    float32_t                                 tracking_min_iou_;
    size_t                                    save_img_flag_;
    size_t                                    detection_limit_x_flag_;
    std::vector<size_t>                       detection_limit_x_;
    size_t                                    detection_range_flag_;
    std::vector<float32_t>                    detection_range_x_;
    std::vector<float32_t>                    detection_range_y_;

    /// TODO
    // std::unordered_map<std::string, ObstacleDetectionCallback> camera_callbacks_;
    // ClassRegistry<ImageDetectorResource, std::string>        camera_detector_resource_registry_;
    // ClassRegistry<BBoxKFTracker, std::string>                camera_bbox_trakcer_registry_;
    // ClassRegistry<ScaleIPMConvertor<float32_t>, std::string> camera_scale_ipm_convertor_registry_;
    // std::unordered_map<std::string, ImageBBoxList>   history_camera_image_bbox_;
    // std::unordered_map<std::string, holo::TimeStamp> history_camera_time_stamp_;
    // std::unordered_map<std::string, holo::TimeStamp> current_camera_time_stamp_;
    // std::unordered_map<std::string, uint32_t>        cameras_topic_msg_seq_;
    // std::unordered_map<std::string, VelocityFilterMap> camera_obs_velocity_filters_;

    SafeMsgDataContainer<holo::common::Odometryf>     odometry_msg_data_container_;
    SafeMsgDataContainer<holo::map::CurrentRouteInfo> route_info_msg_data_container_;
    // std::unordered_map<std::string, bool> camera_has_image_to_detect_;
    // std::unordered_map<std::string, cv::Mat> current_images_;
    holo::common::Odometryf     current_odometry_;
    holo::map::CurrentRouteInfo current_route_info_;
    bool                        current_has_odometry_;
    bool                        current_has_route_info_;

    std::map<std::string, std::list<ImageBBox2D<holo::float32_t>>> history_det_objects_;
    // IPM
    // std::unordered_map<std::string, std::shared_ptr<holo::perception::IpmConvertor<float32_t>>> ipm_convertor_map_;
    std::unordered_map<std::string, std::shared_ptr<holo::perception::InversePerspectivMappingBase>> ipm_convertor_map_;

    // Cache and Reveive car state lock mutex
    std::mutex  mutex_car_state_;
    std::mutex  mutex_in_odometry_;
    std::mutex* receiver_protector_;

    // Cache car state
    std::queue<ChassisState> car_state_deque_;

    std::queue<holo::common::Odometryf>  in_odometry_deque_;
    std::vector<holo::common::Odometryf> in_odometry_vector_;

    // current image matrix and flag
    std::unordered_map<std::string, cv::Mat> current_images_;
    std::unordered_map<std::string, bool>    camera_has_image_to_detect_;

// CenterNetParking model ptr
#ifdef TIDL_INFERENCE
    uint8_t*                                            data;
    std::shared_ptr<holo::perception::TidlInferenceDet> tidl_center_net_;
#else
    std::shared_ptr<holo::perception::CenterNetParking<holo::float32_t>> center_net_;
#endif

    // publish callbacks
    std::unordered_map<std::string, ObstacleDetectionCallback> camera_callbacks_;
    std::unordered_map<std::string, ObstacleGeneralCallback>   camera_general_callbacks_;

    // image precess tool, eg: corp
    // ClassRegistry<ImageDetectorResource, std::string> camera_detector_resource_registry_;

    // Cache Image
    std::unordered_map<std::string, std::shared_ptr<SafeMsgDataContainer<cv::Mat>>> cameras_msg_data_container_;
    std::unordered_map<std::string, uint32_t>                                       cameras_topic_msg_seq_;

    /// time stamp parameters
    holo::common::Timestamp                                  time_stamp_last_;
    std::unordered_map<std::string, holo::common::Timestamp> image_time_stamp_;
    std::unordered_map<std::string, holo::common::Timestamp> history_camera_time_stamp_;
    std::unordered_map<std::string, holo::common::Timestamp> current_camera_time_stamp_;
    std::unordered_map<std::string, holo::common::Timestamp> received_image_time_stamp_;

    // Max cache size
    const size_t kQueueSize = 10;

    const static std::array<std::string, 4> kCameraNamesStringArray;

    // ClassRegistry<ProjectionConvertor, std::string> camera_projection_convertor_registry_;
    // ClassRegistry<ImageDetectorResource, std::string> camera_detector_resource_registry_;

    ClassRegistry<BBoxKFTracker, std::string> camera_bbox_trakcer_registry_;

    // std::unordered_map<std::string, holo::Timestamp> history_camera_time_stamp_;
    std::unordered_map<std::string, ImageBBoxList>                                history_camera_image_bbox_;
    std::unordered_map<std::string, std::map<uint64_t, std::vector<cv::Point2f>>> history_camera_track;

    ObstacleGeneralList camera_obstacle_general_list_;
    CameraObstacleList  camera_obstacle_2d_;

    CameraObstacleList camera_obstacle_vision_list_;

    holo::Pathd planning_path_;
};

// class GetTimeDiffApp
// {
//    public:
//        struct timeval start, end;
//        void StartTiming()
//        {
//            gettimeofday(&start, NULL);
//        }
//        float32_t GetTimeDiff()   //ms
//        {
//            gettimeofday(&end, NULL);
//            return (end.tv_sec-start.tv_sec)*1e3+(end.tv_usec-start.tv_usec)/1e3;
//        }
// };

}  // namespace perception
}  // namespace holo

#endif
