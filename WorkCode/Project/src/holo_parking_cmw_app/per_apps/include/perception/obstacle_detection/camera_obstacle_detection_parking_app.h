/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2019-09-23
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_CMW_APPS_PERCEPTION_CAMERA_OBSTACLE_DETECYION_APP_H_
#define _HOLO_CMW_APPS_PERCEPTION_CAMERA_OBSTACLE_DETECYION_APP_H_

#include <exception>
#include <map>
#include <vector>
// #include <holo/common/car_state.h>
// #include <holo/common/coord.h>
#include <holo/common/chassis_state.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/app/vision_model_inference_parking_app.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo/utils/yaml.h>

#include <cmw_wrapper/cmw_bus.h>
#include <holo_base_msg/traits.h>
#include<atomic>
using BusType = cmw_wrapper::BusType;

namespace holo_cmw
{
class CameraObstacleDetectionApp
{
    
public:
    CameraObstacleDetectionApp(int argc, char** argv, const std::string config_file, uint32_t domain_id);
    void Run();
    void Terminate();

private:
    void InitConfig();
    void CreateSubscribersAndPunlishers();

    /**
     * @brief will be called by the app. receive front center image from the comunication middleware.
     * @param msg the image.
     */
    void FrontCenterCameraSubscriberCallback(uint32_t msg);
    
    /**
     * @brief will be called by the app. receive front left image from the comunication middleware.
     * @param msg the image.
     */
    void FrontLeftCameraSubscriberCallback(uint32_t msg);

    /**
     * @brief will be called by the app. receive front right image from the comunication middleware.
     * @param msg the image.
     */
    void FrontRightCameraSubscriberCallback(uint32_t msg);

   /**
     * @brief will be called by the app. receive rear center image from the comunication middleware.
     * @param msg the image.
     */
    
    void RearCenterCameraSubscriberCallback(uint32_t msg);
    
    /**
     * @brief will be called by the app. receive front center gs image from the comunication middleware.
     * @param msg the image.
     */
    void FrontCenterGsCameraSubscriberCallback(uint32_t msg); 
    
    /**
     * @brief will be called by the app. receive car state from the comunication middleware.
     * @param msg the carstate.
     */
    void CallbackCarState(const holo::ChassisState& msg);

    /**
     * @brief will be called by the app. receive odometry from the comunication middleware.
     * @param msg the odometry.
     */
    // void CallbackInOdometry(const holo_cmw::CMW::OdometryTopicType& msg);

    /**
     * @brief will be called by the app. publish front center camera obstacles from the comunication middleware.
     * @param msg the front center camera obstacles.
     */
    // void FrontCenterCameraPublisherCallback(const holo::ObstaclePtrListT<holo::ObstacleCameraT<holo::float32_t> >&
    // input);

    /**
     * @brief will be called by the app. publish front left camera obstacles from the comunication middleware.
     * @param msg the front left camera obstacles.
     */
    // void FrontLeftCameraPublisherCallback(const holo::ObstaclePtrListT<holo::ObstacleCameraT<holo::float32_t> >&
    // input);

    /**
     * @brief will be called by the app. publish front right camera obstacles from the comunication middleware.
     * @param msg the front right camera obstacles.
     */
    // void FrontRightCameraPublisherCallback(const holo::ObstaclePtrListT<holo::ObstacleCameraT<holo::float32_t> >&
    // input);

    /**
     * @brief will be called by the app. publish rear center camera obstacles from the comunication middleware.
     * @param msg the rear center camera obstacles.
     */
    // void RearCenterCameraPublisherCallback(const holo::ObstaclePtrListT<holo::ObstacleCameraT<holo::float32_t> >&
    // input);
    void FusionHandlerOutParkingObstacles(const holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>,
                                                                  holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>& input);


    void SetIpc(std::unordered_map<std::string, uint32_t> sensor_id, std::unordered_map<std::string, std::vector<size_t>> camera_raw_wh);

                                                        
    void PublishCameraDetection2d(const holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>,
                                                                  holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>& input);

    /**
     * @brief will be called by the app. receive planning path from the comunication middleware.
     * @param msg the planning path.
     */
    //static void PlanningPathSubscribeCallback(const holo::common::Pathf &msg);
    void release_resources();
private:
    holo::float32_t                                                                   hz_;
    std::string                                                                       config_file_name_;
    std::string                                                                       detection_params_file_;
    std::string                                                                       topic_car_state_subscriber_;
    std::string                                                                       topic_in_odometry_name_;
    std::vector<std::string>                                                          camera_names_;
    std::vector<size_t>                                                               camera_flag_;
    std::vector<std::vector<holo::int16_t>>                                           camera_resolution_;
    std::unordered_map<std::string, std::shared_ptr<holo::sensors::camera::ImageIpc>> images_ipcs_;
    std::unordered_map<std::string, std::string>                                      topic_camera_image_subscribers_;
    std::unordered_map<std::string, std::string> topic_camera_detection_publishers_;
    std::vector<std::string> topic_detection_publishers_;

    std::shared_ptr<holo::perception::VisionModelInferenceParkingApp> detection_ptr_;

    /* dds ros wrapper */
    uint32_t domain_id_;
    std::shared_ptr<BusType>                                              bus_ptr_;
    BusType::WriterType <holo::perception::VisionModelInferenceParkingApp::ObstacleGeneralList >  detection_writer;
    BusType::WriterType <holo::perception::VisionModelInferenceParkingApp::ObstacleGeneralList >  image_detection_writer;
    BusType::WriterType<std::string> test_writer;
    BusType::ReaderType<std::string> test_reader;


public:
    void test(holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>, holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY> const& msg);


    std::string planning_path_name_;  // topic name
};
}  // namespace holo_cmw

#endif