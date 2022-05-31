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
#include <holo/common/details/timestamp.h>
#include <holo/common/extrinsic.h>
#include <holo/common/image.h>
#include <holo/common/intrinsic.h>
#include <holo/common/odometry.h>
#include <holo/common/path.h>
#include <holo/common/sensor_id.h>
#include <holo/map/current_route_info.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/perception/algorithm/ipm.h>
#include <holo/perception/algorithm/tracking/bbox_kf_tracker.h>
#include <holo/perception/app/obstacle_detection_parameter.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/class_registry.h>
#include <holo/perception/utils/worker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <sys/time.h>

#include <mutex>
#include <queue>
#include <string>

#include "holo/perception/common/camera_config_ex.h"

extern std::atomic<int> TERMINATE_STATE;

namespace holo
{
namespace perception
{
struct Feature
{
    cv::Point2f              image_point;          ///< 2d point detected on image
    boost::optional<cv::Mat> optional_descriptor;  ///< an optional descriptor of this point
    float32_t                score;                ///< feature score
    uint16_t                 camera_id;  /// @brief camera id. indicate which camera does this feature comes from

    /**
     * @brief constructor
     * @param _image_point 2d point coordinate on image
     * @param _optional_descriptor optional descriptor
     * @param _camera_id camera id
     * @param _score feature score
     ＊
     */
    Feature(const cv::Point2f& _image_point, const boost::optional<cv::Mat> _optional_descriptor = boost::none,
            const float32_t _score = 1.0, const uint16_t _camera_id = 0)
      : image_point(_image_point), optional_descriptor(_optional_descriptor), score(_score), camera_id(_camera_id)
    {
    }
};

void plt_img_text(cv::Mat& m, cv::Point2f pt, std::string str, double font_scale = 1,
                  cv::Scalar color = cv::Scalar(255, 255, 255))
{
    cv::Point origin;
    int       eps    = 20;
    int       width  = m.cols;
    int       height = m.rows;
    origin.x         = pt.x;
    origin.y         = pt.y;
    origin.x         = width - origin.x < eps ? width - eps / 2 : origin.x;
    origin.y         = height - origin.y < eps ? height - eps / 2 : origin.y;
    origin.x         = origin.x < eps ? eps : origin.x;
    origin.y         = origin.y < eps ? eps : origin.y;

    int font_face = cv::FONT_HERSHEY_COMPLEX;
    // double font_scale = 1;
    int thickness = 0.2;
    int baseline;

    cv::getTextSize(str, font_face, font_scale, thickness, &baseline);
    cv::putText(m, str, origin, font_face, font_scale, color, thickness, 1, 0);
}
class PltIpmPoints
{
public:
    cv::Mat canvas_data;
    int     width_, height_;

    std::pair<cv::Point2f, cv::Point2f> range_;

    float x_len_, y_len_;
    float w_scale;
    float h_scale;
    /**
     * @brief Construct a new Plt Ipm Points object
     *
     * @param width
     * @param height
     * @param range first (x_min y_min) second (x_max y_max)  height(x) width(y)
     */
    PltIpmPoints(int width, int height, std::pair<cv::Point2f, cv::Point2f> range)
    {
        canvas_data = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);

        width_      = width;
        height_     = height;
        range_      = range;
        float x_min = range.first.x;
        float y_min = range.first.y;
        float x_max = range.second.x;
        float y_max = range.second.y;

        float x_len = x_max - x_min;
        float y_len = y_max - y_min;
        x_len_      = x_len;
        y_len_      = y_len;
        h_scale     = x_len / height;
        w_scale     = y_len / width;
        std::cout << "test ipm " << x_len << " " << y_len << std::endl;
        for (int i = 0; i < x_len; i = i + 5)
        {
            cv::line(canvas_data, cv::Point(0, height - i / h_scale), cv::Point(width, height - i / h_scale),
                     cv::Scalar(255, 255, 255), 1, 4);
        }
        for (int i = 0; i < y_len / 2; i = i + 5)
        {
            cv::line(canvas_data, cv::Point(width / 2 + (-i) / w_scale, 0),
                     cv::Point(width / 2 + (-i) / w_scale, height), cv::Scalar(255, 255, 255), 1, 4);
        }
        for (int i = 0; i > -y_len / 2; i = i - 5)
        {
            cv::line(canvas_data, cv::Point(width / 2 + (-i) / w_scale, 0),
                     cv::Point(width / 2 + (-i) / w_scale, height), cv::Scalar(255, 255, 255), 1, 4);
        }
        plt_img_text(canvas_data, cv::Point2f(width / 2, height / 4), "x");
        plt_img_text(canvas_data, cv::Point2f(width / 4, height), "y");
        plt_img_text(canvas_data, cv::Point2f(width / 2, height), "0");
        plt_img_text(canvas_data, cv::Point2f(0, height), std::to_string(y_max));
        plt_img_text(canvas_data, cv::Point2f(width / 2, 0), std::to_string(x_max));
    }
    void resetdata()
    {
        canvas_data = cv::Mat::zeros(cv::Size(width_, height_), CV_8UC3);
        float x_min = range_.first.x;
        float y_min = range_.first.y;
        float x_max = range_.second.x;
        float y_max = range_.second.y;

        for (int i = 0; i < x_len_; i = i + 5)
        {
            cv::line(canvas_data, cv::Point(0, height_ - i / h_scale), cv::Point(width_, height_ - i / h_scale),
                     cv::Scalar(255, 255, 255), 1, 4);
        }
        for (int i = 0; i < y_len_ / 2; i = i + 5)
        {
            cv::line(canvas_data, cv::Point(width_ / 2 + (-i) / w_scale, 0),
                     cv::Point(width_ / 2 + (-i) / w_scale, height_), cv::Scalar(255, 255, 255), 1, 4);
        }
        for (int i = 0; i > -y_len_ / 2; i = i - 5)
        {
            cv::line(canvas_data, cv::Point(width_ / 2 + (-i) / w_scale, 0),
                     cv::Point(width_ / 2 + (-i) / w_scale, height_), cv::Scalar(255, 255, 255), 1, 4);
        }
        plt_img_text(canvas_data, cv::Point2f(width_ / 2, height_ / 4), "x");
        plt_img_text(canvas_data, cv::Point2f(width_ / 4, height_), "y");
        plt_img_text(canvas_data, cv::Point2f(width_ / 2, height_), "0");

        plt_img_text(canvas_data, cv::Point2f(0, height_), std::to_string(y_max));
        plt_img_text(canvas_data, cv::Point2f(width_ / 2, 0), std::to_string(x_max));
    }
    /**
     * @brief
     *
     * @param pt1 pt1.x (height) pt1.y (width)
     * @param pt2 pt1.x (height) pt1.y (width)
     */
    void plt_img_line(cv::Point2f pt1, cv::Point2f pt2)
    {
        float x1 = pt1.x, y1 = pt1.y;
        float x2 = pt2.x, y2 = pt2.y;
        cv::line(canvas_data, cv::Point(width_ / 2 - y1 / w_scale, height_ - x1 / h_scale),
                 cv::Point(width_ / 2 - y2 / w_scale, height_ - x2 / h_scale), cv::Scalar(255, 255, 255), 1, 4);
    }
    void plt_img_line(float x1, float y1, float x2, float y2)
    {
        cv::line(canvas_data, cv::Point(width_ / 2 - y1 / w_scale, height_ - x1 / h_scale),
                 cv::Point(width_ / 2 - y2 / w_scale, height_ - x2 / h_scale), cv::Scalar(255, 255, 255), 1, 4);
    }
};

class FeaturePoint
{
public:
    int   x;
    int   y;
    float score;
    float descriptor_data_[128];
};

/**
 * @brief define the VisionModelInferenceApp class
 */
class VisionModelInferenceApp : public VisionDet
{
public:
    using Features          = std::vector<holo::perception::Feature>;
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

    typedef std::function<int32_t(const Features&, const Timestamp&)> FeaturesCallback;
    FeaturesCallback                                                  features_callback_;

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
    VisionModelInferenceApp(const std::string cfg_file, std::vector<size_t> camera_flag, float hz = 10);
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

    int32_t SetFeaturesCallback(const FeaturesCallback& cb);
    /**
     * @breif reveive image
     * @param image the imge that will be put into the receiving container.
     * @param camera_name the camera name.
     */
    void ReceiveImageFromCamera(const holo::Image& image, const std::string& camera_name);

    void FpReceiveImageFromCamera(const holo::Image& image, const std::string& camera_name);

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

    void DetPostProcess(std::vector<std::vector<holo::perception::BoxObjectf>>& detection_obs_results);
    void FdPostProcess(std::vector<std::vector<FeaturePoint>>& fd_res);
    void SetWorkState(uint8_t od_work_state, uint8_t fd_work_state);

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

    // /**
    //  * @brief get Image matrix form Cache image
    //  * param[out] images the Matrixes of images
    //  */
    // void LaunchImages(std::vector<cv::Mat>& images);

    /**
     * @brief receive car state
     */
    bool ReceiveCarState();

    /**
     * @brief public
     */
    void Publish(ObstacleGeneralList& cam_obs_list, std::string name);

    /**
     * @brief
     *
     * @param cam_obs_list
     * @param name
     */
    void Publish(CameraObstacleList& cam_obs_list, std::string name);

    /**
     * @brief remap in origin size
     */
    void UnmapBox(Box2DType& box, const std::string& camera_name);
    /**
     * @brief checkout time
     */
    void CheckSensorDataTimeout();

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

    void FixDetKeypoints(std::vector<std::vector<float>>& det_result);
    void convert_det_data(std::vector<std::vector<float>>&         det_result,
                          std::list<ImageBBox2D<holo::float32_t>>& det_object);

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

    std::vector<cv::Mat> images_to_detect_;  // vector for the input image

    std::shared_ptr<holo::perception::PltIpmPoints> test_plt_ipm_;

    SafeMsgDataContainer<holo::common::Odometryf>     odometry_msg_data_container_;
    SafeMsgDataContainer<holo::map::CurrentRouteInfo> route_info_msg_data_container_;
    // std::unordered_map<std::string, bool> camera_has_image_to_detect_;
    // std::unordered_map<std::string, cv::Mat> current_images_;
    holo::common::Odometryf     current_odometry_;
    holo::map::CurrentRouteInfo current_route_info_;
    bool                        current_has_odometry_;
    bool                        current_has_route_info_;

    std::vector<std::string> camera_update_vector_;
    std::vector<std::string> camera_postprocess_vector_;
    std::vector<std::string> camera_fp_update_vector_;

    std::map<std::string, std::list<ImageBBox2D<holo::float32_t>>> history_det_objects_;

    // Cache and Reveive car state lock mutex
    std::mutex mutex_car_state_;
    std::mutex mutex_in_odometry_;
    std::mutex receiver_protector_;

    // Cache car state
    std::queue<ChassisState> car_state_deque_;

    std::queue<holo::common::Odometryf>  in_odometry_deque_;
    std::vector<holo::common::Odometryf> in_odometry_vector_;

    // current image matrix and flag
    std::vector<cv::Mat>                  current_images_;
    std::unordered_map<std::string, bool> camera_has_image_to_detect_;

    // Fp camera image
    std::vector<cv::Mat> fp_current_images_;
    int32_t                                   input_width_;
    int32_t                                   input_height_;
    int32_t                                   image_width_;
    int32_t                                   image_height_;

    std::shared_ptr<holo::dnn::DnnInterface> dnn_interface_ptr_detection_obs_;
    std::shared_ptr<holo::dnn::DnnInterface> dnn_interface_ptr_fp_;
    std::shared_ptr<IpmApp>                  ipm_ptr_;

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
    holo::common::Timestamp                                  fp_time_stamp_last_;
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

    //
    std::uint8_t od_work_state_;
    std::uint8_t fd_work_state_;
};

}  // namespace perception
}  // namespace holo

#endif
