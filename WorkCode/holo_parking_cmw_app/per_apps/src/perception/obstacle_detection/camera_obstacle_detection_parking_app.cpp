/*!
 *  \brief
 *  \author pengcheng (pengcheng@holomatic.com)
 *  \date2019-08-23
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/perception/utils/worker.h>
#include <holo/utils/yaml.h>
#include <holo/log/hololog.h>
#include <math.h>
#include <perception/obstacle_detection/camera_obstacle_detection_parking_app.h>
#include <atomic>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <fstream>

namespace holo_cmw
{
// static const char* APP_NAME = "camera_obstacle_detection";
CameraObstacleDetectionApp::CameraObstacleDetectionApp(int argc, char** argv, const std::string config_file, uint32_t domain_id)
  : config_file_name_(config_file)
{
    (void)argc;
    (void)argv;
    domain_id_ = domain_id;
    InitConfig();  
    detection_ptr_ = std::make_shared<holo::perception::VisionModelInferenceParkingApp>(detection_params_file_, std::vector<size_t>(), hz_);
    detection_ptr_->DeleteInvalidCamera(camera_flag_);
    SetIpc(detection_ptr_->sensor_id_, detection_ptr_->camera_raw_wh_);
    CreateSubscribersAndPunlishers();
    // detection_ptr_->Run();
}

void CameraObstacleDetectionApp::InitConfig()
{
    try
    {
        holo::yaml::Node node  = holo::yaml::LoadFile(config_file_name_);
        hz_                    = node["hz"].as<holo::float32_t>(hz_);
        detection_params_file_ = node["detection_params_file"].as<std::string>();
        camera_names_          = node["camera_names"].as<std::vector<std::string>>();
        std::vector<std::string> tmp_topic_publishers =
            node["topic_camera_image_detection_publishers"].as<std::vector<std::string>>();
        topic_detection_publishers_ = node["topic_detection_publishers"].as<std::vector<std::string>>();
        std::vector<std::string> tmp_topic_sunscribers =
            node["topic_camera_image_subscriber"].as<std::vector<std::string>>();

        topic_car_state_subscriber_ = node["topic_car_state_subscriber"].as<std::string>();
        topic_in_odometry_name_     = node["topic_in_odometry_name"].as<std::string>();

        planning_path_name_ = node["topic_planning_path"].as<std::string>();

        camera_flag_ = node["camera_flag"].as<std::vector<size_t>>();
        for (int i = 0; i < camera_flag_.size(); i++)
        {
            std::cout << camera_flag_[i] << " ";
        }
        std::cout << std::endl;

        for (size_t i = 0; i < camera_names_.size(); i++)
        {
            topic_camera_image_subscribers_[camera_names_[i]]    = tmp_topic_sunscribers[i];
            topic_camera_detection_publishers_[camera_names_[i]] = tmp_topic_publishers[i];
        }
    }
    catch (const std::exception& e)
    {
        LOG(FATAL) << "InitConfig Failure : " << config_file_name_ << std::endl << e.what();
    }
 
    for (auto name : camera_names_)
    {
        holo::common::SensorId        sensor_id;
        holo::common::VehicleLocation vehicle_location;
        if (name == "FRONT_CENTER_CAMERA")
        {
            vehicle_location.SetLocation(holo::common::VehicleLocation::Location::FRONT,
                                         holo::common::VehicleLocation::Location::CENTER);
            sensor_id.SetLocation(vehicle_location);
            sensor_id.SetCategory(holo::common::SensorId::Category::CAMERA);
        }
        else if (name == "FRONT_LEFT_CAMERA")
        {
            vehicle_location.SetLocation(holo::common::VehicleLocation::Location::FRONT,
                                         holo::common::VehicleLocation::Location::LEFT);
            sensor_id.SetLocation(vehicle_location);
            sensor_id.SetCategory(holo::common::SensorId::Category::CAMERA);
        }
        else if (name == "FRONT_RIGHT_CAMERA")
        {
            vehicle_location.SetLocation(holo::common::VehicleLocation::Location::FRONT,
                                         holo::common::VehicleLocation::Location::RIGHT);
            sensor_id.SetLocation(vehicle_location);
            sensor_id.SetCategory(holo::common::SensorId::Category::CAMERA);
        }
        else if (name == "REAR_CENTER_CAMERA")
        {
            vehicle_location.SetLocation(holo::common::VehicleLocation::Location::REAR,
                                         holo::common::VehicleLocation::Location::CENTER);
            sensor_id.SetLocation(vehicle_location);
            sensor_id.SetCategory(holo::common::SensorId::Category::CAMERA);
        }
        else if (name == "FRONT_CENTER_GS_CAMERA")
        {
            vehicle_location.SetLocation(holo::common::VehicleLocation::Location::FRONT,
                                         holo::common::VehicleLocation::Location::CENTER);
            sensor_id.SetLocation(vehicle_location);
            sensor_id.SetCategory(holo::common::SensorId::Category::CAMERA);
        }
        else
        {
            LOG(ERROR) << "Invalid camera name!";
            // throw holo::HoloException("Invalid camera name!");
        }

    }
}

class GetTimeDiffApp
{
   public:
       struct timeval start, end;
       
       void StartTiming()
       {
           gettimeofday(&start, NULL);
       }

       holo::float32_t GetTimeDiff()    //ms 
       {
           gettimeofday(&end, NULL);
           return (end.tv_sec-start.tv_sec)*1e3+(end.tv_usec-start.tv_usec)/1e3;
       }
};

void CameraObstacleDetectionApp::Run()
{
    // BusType::Spin(1);
    BusType::AsyncSpin(1);
    GetTimeDiffApp det_time_use;
    holo::float32_t det_time = 0;
    holo::float32_t pipeline_time = 1.0/hz_*1e3;

    while (BusType::IsRunning())
    {
        usleep(pipeline_time - det_time);   //50ms
        det_time_use.StartTiming();
        detection_ptr_->DoWork();
        det_time = det_time_use.GetTimeDiff();
    }
}

void CameraObstacleDetectionApp::Terminate()
{
    // detection_ptr_->Terminate();
}

void CameraObstacleDetectionApp::test(holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>,
                                                             holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY> const& msg)
{
    (void)msg;   
    std::cout << "get message" << std::endl;
    std::cout << msg.GetSize() << std::endl;  // obstacle num
}

void CameraObstacleDetectionApp::CreateSubscribersAndPunlishers()
{
    bus_ptr_ = std::make_shared<BusType>(domain_id_, std::string("detection"));
    for (auto name : camera_names_)
    {
        auto reader = bus_ptr_->AddReader<uint32_t>(topic_camera_image_subscribers_[name]);
        if (name == "FRONT_CENTER_CAMERA" && camera_flag_[0])
        {
            reader.SetOnDataAvailableCallback(std::bind(
                &CameraObstacleDetectionApp::FrontCenterCameraSubscriberCallback, this, std::placeholders::_1));
            std::cout << "bind front center camera" << std::endl;
        }
        else if (name == "FRONT_CENTER_GS_CAMERA" && camera_flag_[1])
        {
            reader.SetOnDataAvailableCallback(std::bind(
                &CameraObstacleDetectionApp::FrontCenterGsCameraSubscriberCallback, this, std::placeholders::_1));
            std::cout << "bind front center gs camera end" << std::endl;
        }
        else if (name == "FRONT_LEFT_CAMERA" && camera_flag_[2])
        {
            reader.SetOnDataAvailableCallback(
                std::bind(&CameraObstacleDetectionApp::FrontLeftCameraSubscriberCallback, this, std::placeholders::_1));
            std::cout << "bind front left camera" << std::endl;
        }
        else if (name == "FRONT_RIGHT_CAMERA" && camera_flag_[3])
        {
            reader.SetOnDataAvailableCallback(std::bind(&CameraObstacleDetectionApp::FrontRightCameraSubscriberCallback,
                                                        this, std::placeholders::_1));
            std::cout << "bind front right camera" << std::endl;
        }
        else if (name == "REAR_CENTER_CAMERA" && camera_flag_[4])
        {
            reader.SetOnDataAvailableCallback(std::bind(&CameraObstacleDetectionApp::RearCenterCameraSubscriberCallback,
                                                        this, std::placeholders::_1));
            std::cout << "bind rear center camera" << std::endl;
        }
    }
    // get car state 
    auto car_state_reader = bus_ptr_->AddReader<holo::ChassisState>(topic_car_state_subscriber_);
    car_state_reader.SetOnDataAvailableCallback(std::bind(&CameraObstacleDetectionApp::CallbackCarState,
                                                        this, std::placeholders::_1));
    // auto path_reader = bus.AddReader<holo::Pathd>(planning_path_name_);
    // path_reader.SetOnDataAvailableCallback(PlanningPathSubscribeCallback);
    detection_writer = bus_ptr_->AddWriter<holo::perception::VisionModelInferenceParkingApp::ObstacleGeneralList>(
        topic_camera_detection_publishers_[camera_names_[0]]);
    image_detection_writer = bus_ptr_->AddWriter<holo::perception::VisionModelInferenceParkingApp::ObstacleGeneralList>(
        topic_detection_publishers_[0]);
    detection_ptr_->SetCallback(
        std::bind(&CameraObstacleDetectionApp::FusionHandlerOutParkingObstacles, this, std::placeholders::_1),
        camera_names_[0]);
    detection_ptr_->SetCallback(
        std::bind(&CameraObstacleDetectionApp::PublishCameraDetection2d, this, std::placeholders::_1), "test_det_2d");
}

void CameraObstacleDetectionApp::SetIpc(std::unordered_map<std::string, uint32_t>            sensor_id,
                                        std::unordered_map<std::string, std::vector<size_t>> camera_raw_wh)
{
    size_t i = 0;
    for (auto name : camera_names_)
    {
        if (camera_flag_[i] && sensor_id.find(name) != sensor_id.end())
        {
            LOG(INFO) << name << " " << sensor_id[name] << " " << camera_raw_wh[name][0] << " "
                      << camera_raw_wh[name][1];
#ifdef TIDL_INFERENCE
            images_ipcs_[name] = std::make_shared<holo::sensors::camera::ImageIpc>(
                sensor_id[name], camera_raw_wh[name][1], camera_raw_wh[name][0], holo::Image::Encoding::NV12);
#else
            images_ipcs_[name] = std::make_shared<holo::sensors::camera::ImageIpc>(
                sensor_id[name], camera_raw_wh[name][1], camera_raw_wh[name][0], holo::Image::Encoding::RGB);
#endif
        }
        i++;
    }
}

void CameraObstacleDetectionApp::FrontCenterCameraSubscriberCallback(uint32_t msg)
{
    (void)msg;
    std::string camera_name = "FRONT_CENTER_CAMERA";
    LOG(INFO) << "get front center camera data";
    if (!images_ipcs_[camera_name])
    {
        LOG(ERROR) << camera_name << " image ipc not created!";
        // throw holo::HoloException("Front center camera image ipc not created!");
    }
    holo::Image img;
    images_ipcs_[camera_name]->GetImageData(img); 
    // static int i=0;
    // std::string tmp = "/home/holo/result/front_center_" + std::to_string(i) + ".jpeg"; 
    // std::cout<<tmp<<std::endl;  
    // cv::imwrite(tmp, img.GetCvType());  
    // i++;
    detection_ptr_->ReceiveImageFromCamera(img, camera_name);
}

void CameraObstacleDetectionApp::FrontCenterGsCameraSubscriberCallback(uint32_t msg)
{
    (void)msg;
    std::string camera_name = "FRONT_CENTER_GS_CAMERA"; 
    std::cout << "get fisheye 0 data" << std::endl;
    if (!images_ipcs_[camera_name])
    {
        LOG(ERROR) << camera_name << " image ipc not created!"; 
        // throw holo::HoloException("Front center camera image ipc not created!"); 
    }
    holo::Image img;
    images_ipcs_[camera_name]->GetImageData(img); 

    img.SetReceivedStamp(img.GetTriggerStamp());
    detection_ptr_->ReceiveImageFromCamera(img, camera_name);
}

void CameraObstacleDetectionApp::FrontLeftCameraSubscriberCallback(uint32_t msg)
{
    (void)msg;
    std::string camera_name = "FRONT_LEFT_CAMERA";
    std::cout << "get fisheye 1 data" << std::endl;
    if (!images_ipcs_[camera_name])
    {
        LOG(ERROR) << camera_name << " image ipc not created!";
        // throw holo::HoloException("Front left camera image ipc not created!");
    }
    holo::Image img;
    images_ipcs_[camera_name]->GetImageData(img);
    // static int i=0;
    // std::string tmp = "/home/holo/result/front_left_" + std::to_string(i) + ".jpeg";
    // std::cout<<tmp<<" "<<img.GetWidth()<<" "<<img.GetHeight()<<std::endl;
    // auto img1 = img.GetCvType();
    // std::cout<<img1.dims<<std::endl;
    // cv::imwrite(tmp, img.GetCvType());
    // i++;

    img.SetReceivedStamp(img.GetTriggerStamp());
    detection_ptr_->ReceiveImageFromCamera(img, camera_name);
}

void CameraObstacleDetectionApp::FrontRightCameraSubscriberCallback(uint32_t msg)
{
    (void)msg;
    std::cout << "get fisheye 2 data" << std::endl;
    std::string camera_name = "FRONT_RIGHT_CAMERA";
    if (!images_ipcs_[camera_name])
    {
        LOG(ERROR) << camera_name << " image ipc not created!";
        // throw holo::HoloException("Front right camera image ipc not created!");
    }
    holo::Image img;
    images_ipcs_[camera_name]->GetImageData(img);

    // static int i=0;
    // std::string tmp = "/home/holo/result/front_right_" + std::to_string(i) + ".jpeg";
    // std::cout<<tmp<<" "<<img.GetWidth()<<" "<<img.GetHeight()<<std::endl;
    // auto img1 = img.GetCvType();
    // std::cout<<img1.dims<<std::endl;
    // cv::imwrite(tmp, img.GetCvType());
    // i++;

    img.SetReceivedStamp(img.GetTriggerStamp());
    detection_ptr_->ReceiveImageFromCamera(img, camera_name);
}

void CameraObstacleDetectionApp::RearCenterCameraSubscriberCallback(uint32_t msg)
{
    (void)msg;
    std::cout << "get fisheye 3 data" << std::endl;
    std::string camera_name = "REAR_CENTER_CAMERA";
    if (!images_ipcs_[camera_name])
    {
        LOG(ERROR) << camera_name << " image ipc not created!";
        // throw holo::HoloException("Rear center camera image ipc not created!");
    }
    holo::Image img;
    images_ipcs_[camera_name]->GetImageData(img);

    // static int i=0;
    // std::string tmp = "/home/holo/result/rear_center_gs_" + std::to_string(i) + ".jpeg";
    // std::cout<<tmp<<" "<<img.GetWidth()<<" "<<img.GetHeight()<<std::endl;
    // auto img1 = img.GetCvType();
    // std::cout<<img1.dims<<std::endl;
    // cv::imwrite(tmp, img.GetCvType());
    // i++;

    img.SetReceivedStamp(img.GetTriggerStamp());
    images_ipcs_[camera_name]->GetImageData(img);
    detection_ptr_->ReceiveImageFromCamera(img, camera_name);
}

void CameraObstacleDetectionApp::CallbackCarState(const holo::ChassisState& msg)
{
    std::cout<<"get car state"<<std::endl;
    (void)msg;
    holo::common::ChassisState msg1;
    msg1.SetGearPosition((holo::common::ChassisState::GearPosition)(msg.GetGearLevel()));
    detection_ptr_->CacheCarState(msg1);
}

// void CameraObstacleDetectionApp::CallbackInOdometry(const holo_cmw::CMW::OdometryTopicType& msg)
// {
//     holo::Odometry cache;
//     holo_cmw::Convert(msg, cache);
//     detection_ptr_->CacheInOdometry(cache);
// }

void CameraObstacleDetectionApp::FusionHandlerOutParkingObstacles(
    const holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>, holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>&
        input)
{
    (void)(input);
    LOG(INFO) << "publish camera obstacle";
    detection_writer.Write(input);
}

void CameraObstacleDetectionApp::PublishCameraDetection2d(
    const holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>, holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>&
        input)
{
    (void)(input);

    LOG(INFO) << "publish camera obstacle 2d";
    image_detection_writer.Write(input);
}

}  // namespace holo_cmw

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "SideCameraObstacleDetection");
    options.add_options()("h,help", "show this message")(
        "c,config_file", "configuration file path",
        cxxopts::value<std::string>()->default_value(
            "/opt/holo/config/holo_perception/app_config/side_camera_vision_detection.yaml"))(
        "v,verbose", "if also outputs glog to console")(
        "n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("camera_detection"))(
        "m,min_log_level", "minimum log level, INFO(0), WARNING(1), ERROR(2), FATAL(3)",
        cxxopts::value<holo::uint8_t>()->default_value("1"))(
        "d,domain_id", "domain id", cxxopts::value<uint32_t>()->default_value("5"));
    options.parse(argc, argv);

    if (options.count("help"))
    {
        std::cout << options.help();
        return 0;
    }
    // ros
    uint32_t domain_id = options["domain_id"].as<uint32_t>();
    BusType::Initialize(argc, argv, std::string("camera_detection"));

    // holo::CreateHoloLogSubdirectory("holo_perception");
    std::string log_file =
        "";  // holo::GetLogFileAbsolutePath("holo_perception/" + options["node_name"].as<std::string>()+ ".log");
    // google::InitGoogleLogging(argv[0]);
    // google::SetLogDestination(google::FATAL, "");
    // google::SetLogDestination(google::ERROR, "");
    // google::SetLogDestination(google::WARNING, "");
    // google::SetLogDestination(google::INFO, log_file.c_str());
    // FLAGS_alsologtostderr = bool(options.count("verbose") > 0);
    // FLAGS_minloglevel     = options["min_log_level"].as<holo::uint8_t>();
    // FLAGS_logtostderr     = true;

    holo_cmw::CameraObstacleDetectionApp app(argc, argv, options["config_file"].as<std::string>(), domain_id);
    app.Run();
    app.Terminate();
    // google::ShutdownGoogleLogging();
    return 0;
}
