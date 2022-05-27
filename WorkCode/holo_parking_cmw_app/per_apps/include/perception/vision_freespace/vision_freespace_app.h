/*!
 *  \brief
 *  \author lizhijian (lizhijian@holomatic.com)
 *  \date 2020-12-07
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_CMW_APPS_VISION_FREESPACE_APP_H_
#define _HOLO_CMW_APPS_VISION_FREESPACE_APP_H_
#include <holo/log/hololog.h>
#include <holo/common/chassis_state.h>
#include <holo/common/freespace.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <cmw_wrapper/cmw_bus.h>
#ifdef TIDL_INFERENCE
#include <holo/perception/app/vision_freespace_tidl.h>
#endif
#ifdef HOLO_PERCEPTION_PARKING_WITH_CUDA
#include <holo/perception/app/vision_freespace.h>
#endif
#include <exception>
#include <map>
#include <unordered_map>
#include <vector>

using BusType = cmw_wrapper::CmwBus;

namespace holo_cmw
{
class VisionFreespaceApp
{
#ifdef TIDL_INFERENCE
    typedef holo::perception::VisionFreespaceTidl VISION_FREESPACE_LIB_TYPE;
#endif

#ifdef HOLO_PERCEPTION_PARKING_WITH_CUDA
    typedef holo::perception::VisionFreespace VISION_FREESPACE_LIB_TYPE;
#endif
public:
    // typedef typename holo::common::AutoFreespace<holo::geometry::Point3d> FreespaceType;
    VisionFreespaceApp(int argc, char** argv, const std::string config_file, uint32_t domain_id);
    void Run();
    void Terminate();

private:
    void InitConfig();
    void CreateSubscribersAndPunlishers();

    void InitDetector();

    /**
     * @brief will be called by the app. receive front center image from the comunication middleware.
     * @param msg the image.
     */
    void CameraSubscriberCallback(const std::string camera_name, holo::uint32_t msg);
    void PublishFreespaceCallback(VISION_FREESPACE_LIB_TYPE::FreespaceType& fs);

private:
    holo::float32_t hz_;
    int32_t         debug_image_;  // 0:no , 1:local file, 2:h264 pub
    size_t          debug_image_skip_frames_;
    uint32_t        domain_id_;
    std::string     debug_image_path_;
    std::string     config_file_name_;
    std::string     detection_params_file_;

    std::vector<std::string>                     camera_names_;
    std::unordered_map<std::string, std::string> topic_camera_image_subscribers_;
    // std::unordered_map<std::string, std::vector<holo::int16_t>> camera_resolutions_;

    std::string topic_camera_obstacle_publisher_;
    std::string topic_debug_image_publisher_;

    std::unordered_map<std::string, std::shared_ptr<holo::sensors::camera::ImageIpc>> image_ipcs_;

    // std::unordered_map<std::string, std::string> topic_camera_detection_publishers_;
    std::string topic_vision_freespace_publisher_;

    std::shared_ptr<BusType>                                      bus_ptr_;
    BusType::WriterType<VISION_FREESPACE_LIB_TYPE::FreespaceType> fs_writer_;

    std::shared_ptr<VISION_FREESPACE_LIB_TYPE> vision_freespace_;
};
}  // namespace holo_cmw

#endif
