/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vision_freespace.h
 * @brief This header file defines base vision freespace class.
 * @author lizhijian (lizhijian@holomatic.com)
 * @date "2019-09-17"
 */
#ifndef HOLO_PERCEPTION_LIB_VISION_FREESPACE_H_
#define HOLO_PERCEPTION_LIB_VISION_FREESPACE_H_

#include <holo/common/extrinsic.h>
#include <holo/common/image.h>
#include <holo/common/intrinsic.h>
#include <holo/common/lane_scene.h>
#include <holo/common/odometry.h>
#include <holo/common/path.h>
//#include <holo/freespace/local_map_free_space_v2.h>
#include <holo/perception/utils/worker.h>
#include <holo/common/freespace.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/utility.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <cmath>
#include <mutex>
#include <queue>
#include "holo/perception/common/camera_config_ex.h"
// #define TIDL_INFERENCE
#ifdef TIDL_INFERENCE
#include <holo/perception/app/test_tidl_inference_freespace.h>
#else
#include "holo/perception/inference/tensorrt_freespace.h"

#endif
//#define OUTPUT_DEBUG_IMG 1

namespace holo
{
namespace perception
{
/**
 * @addtogroup detection
 *
 * @{
 */

/**
 * @brief define camera config class
 */

/**
 * @brief define VisionFreespace class
 */
class VisionFreespace : public Worker
{
public:
    typedef typename holo::common::AutoFreespace<holo::geometry::Point3f> FreespaceType;

    // typedef typename std::vector<uint8_t> EncodedImage;

    typedef std::function<void(FreespaceType&)> FreespaceCallback;

    typedef std::vector<std::vector<cv::Point>> CV_ContoursT;
    typedef std::vector<cv::Vec4i>              CV_ContoursHierarchyT;

public:
    /**
     * @brief the constructor.
     * @param cfg_file the path of the config file.
     * @param hz the runing frequency.
     * @param debug_2d_image debug 2d image level(0:no debug image; 1:save local image file; 2:send h264 image as
     * message).
     */
    VisionFreespace(const std::string cfg_file, float hz = 10, int debug_2d_image = 0,
                    size_t debug_image_skip_frames = 0, std::string debug_image_path = "");

    /**
     * @brief initial object from config file.
     */
    void InitConfig();

    /**
     * @brief load comare configs from config file.
     */
    void LoadCamConfigs();

    /**
     * @brief will be called by the app. receive images from the comunication middleware.
     * @param image the image.
     * @param camera_name the name of a camera which the image comes from.
     */
    void ReceiveImageFromCamera(const holo::Image& image, const std::string& camera_name);

    /**
     * @brief will be called by the app. receive planning path from the comunication middleware.
     * @param path the planning path.
     */
    void ReceivePlanningPath(const holo::Pathd& path);

    /**
     * @brief using the stored planning path to calculate ground pitch(car body to ground).
     */
    float32_t CalculateGroundPitch();

    /**
     * @brief set the obstacle detection callback.
     * @param callback the calllback function.
     */
    void SetFreespaceCallback(FreespaceCallback fs_callback);

    /**
     * @brief set the debug image callback.
     * @param callback the calllback function.
     */
    // void SetDebugImageCallback(EncodedImageCallback callback);

    /**
     * @brief check the images' timestamp to determin if they are expired .
     */
    void CheckSensorDataTimeout();

    // if only_estimate_new_K is true, the origin image will keep the distoration.

    /**
     * @brief undistort the image, or just estimate the new_K for the undisorted image.
     * @param camera_name which camera the processing image came from.
     * @param[out] new_K the undistorted image's K.
     * @param only_estimate_new_K indicate whether only the new_K will be estimated or the undistortion will be actually
     * performed.
     */
    bool UndistortImage(const std::string camera_name, Eigen::Matrix3f& new_K, bool only_estimate_new_K = true);

    /**
     * @brief resize the recieved image.
     * @param camera_name which camera the processing image came from.
     * @param new_size the new size.
     */
    bool ResizeCropImage(const std::string camera_name);

    // to f type
    std::vector<cv::Point2f> RestorePointsOnOriginImage(const std::string             camera_name,
                                                        const std::vector<cv::Point>& pts_in);

    /**
     * @brief mask the sepcified image with ROI mask.
     * @param camera_name which camera the processing image came from.
     */
    bool MaskImage(const std::string camera_name);

    /**
     * @brief preprocess all the images that recentely received.
     */
    bool PreProcessImages();

    /**
     * @brief crop-resize all the images that recentely received.
     */
    // bool CropResizeImages();
    /**
     * @brief detect freespaces.
     */

#ifdef TIDL_INFERENCE
    bool DetectFreespacesTidl();
#else
    bool                          DetectFreespaces();
#endif

    /**
     * @brief IPM the detected 2D freespaces to 3D.
     */
    bool IPMFreespaces();

    /**
     * @brief clamp a 2d vector by its norm length.
     * @param pt the vector.
     * @param lo lowest value for the clamp function.
     * @param hi highest value for the clamp function.
     */
    cv::Point2f Clamp2DVectorByNorm(const cv::Point2f& pt, float32_t lo, float32_t hi);

    /**
     * @brief test if a point is in range wrt to the origin(conter-clockwise).
     * @param point_prev the previous point.
     * @param point_current the current point.
     * @param origin the origin.
     * @param start start value for the clamp function.(range 0:2PI)
     * @param end end value for the clamp function.(range 0:2PI)
     * @param revised_point if the current point is outside the range, revise the point to be on the boundry.
     * @return bool return true the current point is in range, otherwise return false.
     */
    bool TestPointInRadianRange(const cv::Point2f& point_prev, const cv::Point2f& point_current,
                                const cv::Point2f& origin, float32_t start, float32_t end, cv::Point2f& revised_point);

    /**
     * @brief determin if a countour is freespace or obstacle that inside the freespace.
     * @param batch_index batch index indicate which image this coutour belongs to(multiple images might went through
     * inference at same time).
     * @param contour_index contour index that retrive by cv::findcontours.
     */
    bool IsFreespace(size_t batch_index, size_t contour_index);

    /**
     * @brief Peek valid freespace.
     * @param batch_index batch index indicate which image this coutour belongs to(multiple images might went through
     * inference at same time).
     * @param contours all contours on the image that the batch_index specified.
     * @param is_freespace is_freespace flags for all contours of on the image that the batch_index specified.
     */
    bool PeekFreespace(size_t batch_index, std::vector<std::vector<cv::Point2f>>& contours,
                       std::vector<bool>& is_freespace);  // do filtering.

    /**
     * @brief generate freespace obstacles.
     */
    bool GenFreespace();

    /**
     * @brief generate observable space.
     */
    bool GenObservablespace();

    /**
     * @brief do all the work.  the app will call this function after update images and planning path.
     */
    bool DoWork();

    holo::Pathd planning_path_;

    // std::unordered_map<std::string, ObstacleDetectionCallback> camera_callbacks_;
    // EncodedImageCallback debug_image_callback_;

    std::vector<float32_t> body_ground_extrinsic_;
    std::vector<float32_t> ground_pitch_gradiant_samples_;
    std::vector<float32_t> blind_zone_nearst_coeffs_;
    // float32_t   visable_radius_;

    std::unordered_map<std::string, std::shared_ptr<CamConfig>> camera_configs_;
    std::unordered_map<std::string, Eigen::Matrix3f>            camera_newK_;
    std::vector<std::vector<cv::Mat>>                           contours_on_images_;

    std::string              config_file_;
    std::string              tensorrt_cfg_file_;
    std::vector<std::string> camera_names_;
    std::vector<std::string> camera_config_files_;
    float32_t                hz_;
    int                      debug_2d_image_;
    size_t                   debug_image_skip_frames_;
    std::string              debug_image_path_;

    // TRTInference::Ptr p_trt_inference_;

    std::unordered_map<std::string, bool> cameras_updated_;
    // std::unordered_map<std::string, uint32_t>                     cameras_topic_msg_seq_;
    // std::unordered_map<std::string, std::vector<holo::float32_t>> camera_resolutions_;  // will update on the arrival
    // of
    // images
    std::unordered_map<std::string, std::shared_ptr<SafeMsgDataContainer<cv::Mat>>> cameras_msg_data_container_;
#ifdef TIDL_INFERENCE
    uint8_t*                                           data;
    std::shared_ptr<holo::perception::TidlInferenceFs> tidl_freespace_fpn_;
    std::string                                        tidl_cfg_file_;
#else
    std::shared_ptr<FreespaceFPN> freespace_fpn_;
#endif

    std::vector<CV_ContoursT>          contours_results_;  // support multi cameras.
    std::vector<CV_ContoursHierarchyT> contours_hierarchy_results_;

    std::vector<cv::Mat>     images_to_inference_;
    std::vector<cv::Mat*>    mask_ptrs_to_inference_;
    std::vector<std::string> updated_images_name_;
    std::set<std::string> updated_images_set_;  // to record and test if images from a particular camere are already in
                                                // the inference queue.

    // holo::sensors::camera::RGB2H264 h264_encoder_;

    float32_t current_ground_pitch_;

    // ObstacleGeneralPtrList observablespace_;  // obspace

    FreespaceType     observablespace_;
    FreespaceCallback freespace_callback_;
    std::mutex        receiver_protector_;
};

/**
 * @}
 */

}  // namespace perception

}  // namespace holo

#endif  /// HOLO_PERCEPTION_APP_VISION_OBSTACLE_DETECTION_APP_V2_H_
