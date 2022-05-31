/*!
 *  \brief
 *  \author xuhan (xuhan@holomatic.com)
 *  \date 2022-01-07
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_PERCEPTION_APP_VISOIN_DET_H_
#define HOLO_PERCEPTION_APP_VISOIN_DET_H_
#include <holo/common/chassis_state.h>
#include <holo/common/details/timestamp.h>
#include <holo/common/extrinsic.h>
#include <holo/common/image.h>
#include <holo/common/intrinsic.h>
#include <holo/common/odometry.h>
#include <holo/common/path.h>
#include <holo/common/sensor_id.h>
#include <holo/dnn/apps/factory.h>
#include <holo/dnn/detection_2d_interface.h>
#include <holo/dnn/interface.h>
#include <holo/map/current_route_info.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/perception/algorithm/ipm.h>
#include <holo/perception/algorithm/tracking/bbox_kf_tracker.h>
#include <holo/perception/common/box_object.h>
#include <holo/perception/common/detection/det_postprocess.h>
#include <holo/perception/common/params_loader.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/class_registry.h>
#include <holo/perception/utils/worker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <sys/time.h>

#include <holo/common/impl/intrinsic.hpp>
#include <mutex>
#include <queue>
#include <string>

#include "holo/perception/common/camera_config_ex.h"

extern std::atomic<int> TERMINATE_STATE;

namespace holo
{
namespace perception
{
/**
 * @brief define the VisionModelINferenceParkingApp class
 */
class VisionDet
{
public:
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

    using Point2Type = holo::geometry::Point2f;
    using Point3Type = holo::geometry::Point3f;
    using Box2DType  = Box2DT<float32_t>;

    void ReceiveImageFromCamera(const holo::Image& image, const std::string& camera_name);
    void ReceiveImageFromCamera(const std::vector<holo::Image>& image_vec,
                                const std::vector<std::string>& camera_name_vec);
    VisionDet()
    {
    }
    VisionDet(const Parameters::Ptr& parameters);

    bool DoWork();

    /////////////////////det//////////////////////
    void convert_bbox_list(const std::vector<std::vector<holo::perception::BoxObjectf>>& detection_obs_results,
                           std::vector<ImageBBoxList>&                                   image_bbox_list);
    void Get3DPoints(const std::vector<cv::Point3f>& ground_points, holo::Point3T<holo::float32_t>& center,
                     holo::geometry::Box3f& bounding_box3d);

    void SetCallback(ObstacleDetectionCallback callback, const std::string& camera_name);
    void Publish(CameraObstacleList& cam_obs_list, std::string name);
    void DrawRec(cv::Mat& img, int x, int y, int w, int h, float sin_theta, int track_id = 0);
    void DumpDebugImage(std::vector<cv::Mat>                                 images_to_detect,
                        std::vector<std::list<holo::perception::BoxObjectf>> det_objects);
    void DumpDebugImage(std::vector<cv::Mat> images_to_detect, std::vector<ImageBBoxList> det_objects);

    /////////////////////freespace////////////////////////
    void FrespacePostProcess(std::vector<std::vector<std::vector<float32_t>>> freespace_results);

private:
    //////////////////////////////////////////common parameter/////////////////////////
    std::shared_ptr<holo::dnn::DnnInterface> dnn_interface_ptr_detection_obs_;
    holo::common::Timestamp                  time_stamp_last_;
    holo::common::Timestamp                  time_stamp_postprocess_;
    std::shared_ptr<IpmApp>                  ipm_ptr_;
    bool                                     save_img_flag_;

    //////////////////////////////////////////det parameter//////////////////////////////
    // Cache and Reveive car state lock mutex
    std::mutex mutex_in_odometry_;
    std::mutex receiver_protector_;
    // current image matrix and flag
    std::map<std::string, bool>               camera_update_flag_;
    std::vector<std::string>                  camera_update_vector_;
    std::vector<std::string>                  camera_postprocess_vector_;
    std::vector<cv::Mat>                      current_images_;
    std::unordered_map<std::string, bool>     camera_has_image_to_detect_;
    ClassRegistry<BBoxKFTracker, std::string> camera_bbox_trakcer_registry_;

    std::shared_ptr<holo::perception::DetPostProcess> det_postprocess_;
    // Cache car state
    // Max cache size
    const size_t                        kQueueSize = 10;
    std::queue<holo::common::Odometryf> in_odometry_deque_;

    CameraObstacleList camera_obstacle_vision_list_;
    CameraObstacleList camera_obstacle_2d_;

    // publish callbacks
    std::unordered_map<std::string, ObstacleDetectionCallback> camera_callbacks_;
    std::unordered_map<std::string, ObstacleGeneralCallback>   camera_general_callbacks_;

    ////////////////////////////////////////Freespace parameter////////////////////////
};

}  // namespace perception
}  // namespace holo

#endif