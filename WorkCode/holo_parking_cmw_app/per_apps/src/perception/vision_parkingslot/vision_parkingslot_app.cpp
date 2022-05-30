/*!
 *  \brief
 *  \author lizhijian (lizhijian@holomatic.com)
 *  \date 2020-12-07
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/perception/utils/worker.h>
#include <holo/utils/yaml.h>
#include <perception/vision_parkingslot/vision_parkingslot_app.h>
#include <holo/perception/app/vision_parkingslot.h>

#include <fstream>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <holo/log/hololog.h>

namespace holo_cmw
{
VisionParkingslotApp::VisionParkingslotApp(int argc, char** argv, const std::string config_file)
  : config_file_name_(config_file)
{
    (void)argc;
    (void)argv;
    InitConfig();
    CreateSubscribersAndPunlishers();
}

///  TEST

static void swapYUV_I420toNV12(unsigned char* i420bytes, unsigned char* nv12bytes, int width, int height)
{
    int nLenY = width * height;
    int nLenU = nLenY / 4;

    memcpy(nv12bytes, i420bytes, width * height);

    for (int i = 0; i < nLenU; i++)
    {
        nv12bytes[nLenY + 2 * i]     = i420bytes[nLenY + i];          // U
        nv12bytes[nLenY + 2 * i + 1] = i420bytes[nLenY + nLenU + i];  // V
    }
}

static void BGR2YUV_nv12(cv::Mat src, cv::Mat& src_YUV_I420, cv::Mat& dst)
{
    int w_img = src.cols;
    int h_img = src.rows;
    cvtColor(src, src_YUV_I420, CV_BGR2YUV_I420);
    swapYUV_I420toNV12(src_YUV_I420.data, dst.data, w_img, h_img);
}

static holo::Image LoadImageToYUV(std::string fn)
{
    holo::Image img;
    cv::Mat     bgr_data = cv::imread(fn);  // default bgr
    std::cout << bgr_data.cols << " " << bgr_data.rows << std::endl;
    cv::Mat src_YUV_I420(bgr_data.rows * 1.5, bgr_data.cols, CV_8UC1, cv::Scalar(0));  // YUV_I420
    cv::Mat yuv_data = cv::Mat(bgr_data.rows * 1.5, bgr_data.cols, CV_8UC1, cv::Scalar(0));

    BGR2YUV_nv12(bgr_data, src_YUV_I420, yuv_data);
    img.SetData(yuv_data.data, bgr_data.cols * bgr_data.rows * 1.5, bgr_data.cols, bgr_data.rows,
                holo::Image::Encoding::NV12);
    return img;
}

///

void VisionParkingslotApp::InitConfig()
{
    try
    {
        holo::yaml::Node node  = holo::yaml::LoadFile(config_file_name_);
        hz_                    = node["hz"].as<holo::float32_t>(hz_);
        detection_params_file_ = node["detection_params_file"].as<std::string>();

        topic_avm_sub_subscriber_           = node["topic_avm_sub_subscriber"].as<std::string>();
        topic_vision_parkingslot_publisher_ = node["topic_vision_parkingslot_publisher"].as<std::string>();
    }
    catch (std::exception& e)
    {
        LOG(FATAL) << "InitConfig Failure : " << config_file_name_ << std::endl << e.what();
    }

    vision_parkingslot_ = std::make_shared<holo::perception::VisionParkingslot>(detection_params_file_, hz_);

    // holo::common::SensorId sensor_id;  // set this to real ones.

    // avm_img_ipc_ = std::make_shared<holo::sensors::camera::ImageIpc>(sensor_id, 512, 512);

    /// TEST
    vision_parkingslot_->Run();
    LOG(INFO) << "Done TEST!";
}  // namespace holo_cmw

void VisionParkingslotApp::CreateSubscribersAndPunlishers()
{
    bus_ptr_ = std::make_shared<BusType>(0, std::string("parkingslot"));

    auto reader = bus_ptr_->AddReader<holo::uint32_t>(topic_avm_sub_subscriber_);

    reader.SetOnDataAvailableCallback(
        std::bind(&VisionParkingslotApp::AVMImageSubscriberCallback, this, std::placeholders::_1));

    std::cout << "bind callback on avm subscriber : " << topic_avm_sub_subscriber_ << std::endl;

    fs_writer_ = bus_ptr_->AddWriter<std::string>(topic_vision_parkingslot_publisher_);
}

void VisionParkingslotApp::AVMImageSubscriberCallback(holo::uint32_t msg)
{
    LOG_EVERY_N(INFO, 10) << "AVMImageSubscriberCallback invoked: " << msg;

    holo::Image     img;
    static uint32_t seq = 0;

    char path_buf[64];
    snprintf(path_buf, 128, "/root/perception/multi_ps_test_jpg/%03d.jpeg", seq % 9);
    std::cout << "read file -> " << path_buf << std::endl;

    seq++;
    cv::Mat bgr_data = cv::imread(path_buf);  // LoadImageToYUV("/root/perception/ps_test_jpg/0000000000.jpg");

    img.SetData(bgr_data.data, bgr_data.cols * bgr_data.rows * 3, bgr_data.cols, bgr_data.rows,
                holo::Image::Encoding::RGB);  // BGR actually

    vision_parkingslot_->ReceiveAVMImage(img);
}

void VisionParkingslotApp::Run()
{
    BusType::Spin(1);
}

void VisionParkingslotApp::Terminate()
{
}

}  // namespace holo_cmw

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "vision_parkingslot");

    options.add_options()("h,help", "show this message")(
        "c,config_file", "configuration file path",
        cxxopts::value<std::string>()->default_value(
            "/opt/holo/config/holo_perception/app_config/vision_parkingslot.yaml"))("v,verbose",
                                                                                    "if also outputs glog to console")(
        "n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("camera_detection"))(
        "m,min_log_level", "minimum log level, INFO(0), WARNING(1), ERROR(2), FATAL(3)",
        cxxopts::value<holo::uint8_t>()->default_value("1"));

    options.parse(argc, argv);

    if (options.count("help"))
    {
        std::cout << options.help();
        return 0;
    }

    // ros
    BusType::Initialize(argc, argv, std::string("vision_parkingslot"));
    signal(SIGINT, BusType::SignalHandler);

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

    holo_cmw::VisionParkingslotApp app(argc, argv, options["config_file"].as<std::string>());
    app.Run();
    app.Terminate();

    // google::ShutdownGoogleLogging();
    return 0;
}
