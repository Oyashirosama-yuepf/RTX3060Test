/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file srv_multi_task_dnn.h
 * @brief This header file defines base dnn version srv multi task class.
 * @author zhouchengwei (zhouchengwei@holomatic.com)
 * @date "2022-01-11"
 */

#ifndef HOLO_PERCEPTION_LIB_VISION_SRV_DNN_H_
#define HOLO_PERCEPTION_LIB_VISION_SRV_DNN_H_

#include <assert.h>
#include <holo/common/freespace.h>
#include <holo/common/image.h>
#include <holo/dnn/interface.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/perception/algorithm/ipm.h>
#include <holo/perception/common/boundary_point2d.h>
#include <holo/perception/common/detection/det_postprocess.h>
#include <holo/perception/common/freespace/freespace_simple_postprocess.h>
#include <holo/perception/common/params_loader.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/srv_multi_task/srv_multi_task_input_checker.h>
#include <holo/perception/utils/class_registry.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/utility.h>
#include <holo/perception/utils/worker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <sys/time.h>

#include <cmath>
#include <mutex>
#include <queue>

namespace holo
{
namespace perception
{
struct SrvDetResult
{
    std::vector<std::list<holo::perception::BoxObjectf>> detection_obs_results;
    std::vector<cv::Mat>                                 freespace_results;

    bool det_decode_flag;
    bool freespace_decode_flag;
};
class SrvMultiTaskDnn
{
public:
    using IntrinsicBaseType            = holo::common::details::CameraIntrinsicBaseT<float32_t>;
    using IntrinsicBaseTypePtr         = std::shared_ptr<IntrinsicBaseType>;
    using FisheyeIntrinsicType         = holo::common::details::FisheyeIntrinsicT<float32_t>;
    using PinholeIntrinsicType         = holo::common::details::PinholeIntrinsicT<float32_t>;
    using OmnidirectionalIntrinsicType = holo::common::details::OmnidirectionalIntrinsicT<float32_t>;
    using OdometryType                 = holo::common::Odometryf;
    using OdometryPtr                  = std::shared_ptr<holo::common::Odometryf>;
    using OdometryCache                = std::queue<OdometryType>;

    using Plane   = std::array<holo::float32_t, 3U>;
    using Frustum = std::array<Plane, 4U>;

    typedef typename holo::perception::FreespaceSimplePostProcess FsPostProcess;
    typedef typename holo::perception::DetPostProcess             DetPostProcess;

    typedef typename holo::perception::SrvMultiTaskInputChecker SrvInputCheckType;
    typedef typename holo::ObstaclePtrListT<ObstacleVisionT<float32_t>, holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>
        CameraObstacleList;
    typedef typename holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>,
                                            holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>
        ObstacleGeneralList;

    typedef std::vector<std::vector<cv::Point>> CV_ContoursT;
    typedef std::vector<cv::Vec4i>              CV_ContoursHierarchyT;

    typedef typename holo::common::AutoFreespace<holo::geometry::Point3f> FreespaceType;
    typedef std::function<void(FreespaceType&)>                           FreespaceCallback;

    typedef std::function<void(CameraObstacleList&)> ObstacleDetectionCallback;

    typedef std::function<void(uint32_t)> SrvNodeStateCallback;

public:
    SrvMultiTaskDnn(const std::string& algorithm_config_yaml);

    Plane GetPlane(Point3f const& a, Point3f const& b) const;

    void InitCameraFrustum();

    void SetCallback(ObstacleDetectionCallback callback);

    void SetSrvMultiTaskCallback(FreespaceCallback fs_callback);

    void SetSrvNodeStateCallback(SrvNodeStateCallback state_callback);

    bool Preprocess();

    void CreateDebugFlags();

    /**
     * @brief Cache the received odometry
     *
     * @param msg
     */
    void CacheOdometry(OdometryType const& msg);

    void ReceiveImageFromCamera(const std::vector<holo::Image>&            msg,
                                const std::unordered_map<std::string, int> camera_order);

    bool CheckImageReady();

    bool UndistortImage(const std::string camera_name, Eigen::Matrix3f& new_K, bool only_estimate_new_K);

    bool DoWork();

private:
    Parameters::Ptr                          parameters_;
    std::vector<holo::Image>                 msg_;
    std::unordered_map<std::string, int>     camera_order_;
    bool                                     flag_received_image_;
    uint32_t                                 input_image_state_;
    Srv_Result::Ptr                          srv_result_;
    std::mutex                               receiver_protector_;
    std::mutex                               odometry_receive_mutex_;
    std::shared_ptr<holo::dnn::DnnInterface> dnn_interface_ptr_freespace_;
    std::shared_ptr<FsPostProcess>           freespace_postprocess_;
    std::shared_ptr<DetPostProcess>          det_postprocess_;
    std::shared_ptr<SrvInputCheckType>       input_check_ptr_;
    holo::common::Timestamp                  time_stamp_last_;
    std::unordered_map<std::string, cv::Mat> cameras_debug_image_container_;
    std::unordered_map<std::string, bool>    cameras_updated_;
    std::unordered_map<std::string, Frustum> camera_frustums_;
    std::vector<std::string>                 receive_camera_names_;
    FreespaceType                            observablespace_;
    FreespaceCallback                        freespace_callback_;
    ObstacleDetectionCallback                detection_callback_;
    SrvNodeStateCallback                     srv_state_callback_;

    float32_t     smooth_dt_;             ///< max dt threshold between odometry and image
    OdometryCache odometry_cache_;        // queue of recieved odometry
    OdometryType  current_odometry_;      // current  odometry
    OdometryPtr   current_odometry_ptr_;  // current odometry ptr
    size_t        max_odom_cache_size_;   // max cached vehicle odometry size

    /**
     * @brief get odometry
     *
     * @return bool_t
     */
    bool_t receiveOdometry();
};
}  // namespace perception
}  // namespace holo

#endif
