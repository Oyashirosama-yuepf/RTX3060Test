/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file birdview_splicer_cmw.cpp
 * @brief cmw node of birdview splicer.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-01-07"
 */
#include <fstream>
#include <iomanip>
#include <thread>

#include <glog/logging.h>
#include <opencv2/opencv.hpp>

#include <holo/common/image.h>
#include <holo/geometry/angle.h>
#include <holo/io/common/intrinsic.h>
#include <holo/os/timer.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <localization/vision/birdview/birdview_mask.h>
#include <localization/vision/birdview/birdview_splicer_cmw.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

namespace holo_cmw
{
static const char* APP_NAME = "BirdviewSplicerCmwNode";
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewSplicerCmw::BirdviewSplicerCmw(holo::int32_t argc, char** argv, std::string const& config_file,
                                       uint32_t domain_id, std::string participant_namespace)
  : bus_(domain_id, participant_namespace)
  , bus_spin_thread_ptr_(nullptr)
  , birdview_show_ptr_(nullptr)
  , birdview_image_ipc_(nullptr)
  , encoded_birdview_image_buffer_(nullptr)
  , rgb_to_h264x_encoder_(nullptr)
  , image_encode_size_max_(holo::sensors::camera::IMAGE_ENCODE_SIZE_MAX)
{
    (void)argc;
    (void)argv;
    signal(SIGINT, BusType::SignalHandler);
    setUp(config_file);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewSplicerCmw::~BirdviewSplicerCmw()
{
    if (bus_spin_thread_ptr_)
    {
        bus_spin_thread_ptr_->join();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BirdviewSplicerCmw::IsRunning()
{
    return bus_.IsRunning();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BirdviewSplicerCmw::Spin()
{
    bus_spin_thread_ptr_ = std::make_shared<std::thread>(&cmw_wrapper::BusType::Spin, 1u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::bool_t BirdviewSplicerCmw::ComputeBirdviewImage(holo::Image& birdview_image)
{
    holo::bool_t is_successful = false;

    if (!birdview_show_ptr_)
    {
        LOG(WARNING) << "birdview_show_ptr_ is not initialized";
        return is_successful;
    }

    if (image_timestamps_.empty())
    {
        LOG(WARNING) << "there is not input image";
        return is_successful;
    }

    std::vector<cv::Mat>             input_images;
    Timestamp                        birdview_image_timestamp;
    holo::uint16_t const             number_of_camera = images_readers_.size();

    {
        std::unique_lock<std::mutex> lock(timestamp_with_images_mutex_);
        while (image_timestamps_.size())
        {
            Timestamp const      front_timestamp = image_timestamps_.front();
            holo::uint64_t const nsec            = front_timestamp.ToNsec();

            if (image_timestamps_.size() > 3u ||
                (image_timestamps_.size() == 3u && timestamp_with_images_.at(nsec).size() < number_of_camera))
            {
                if (image_timestamps_.size() == 3u)
                {
                    LOG(WARNING) << "BirdviewSplicerCmw --- the number of old image is not enough, when new image "
                                    "arrived, number of old image is "
                                 << timestamp_with_images_.at(nsec).size() << ", the timestamp is " << nsec
                                 << ", drop old images";
                }
                else
                {
                    LOG(WARNING) << "BirdviewSplicerCmw --- the speed of birdview spicer is too slow, drop old images";
                }

                image_timestamps_.pop_front();
                timestamp_with_images_.erase(nsec);
                continue;
            }

            if (timestamp_with_images_.at(nsec).size() == number_of_camera)
            {
                for (holo::uint16_t i = 0u; i < number_of_camera; i++)
                {
                    input_images.push_back(timestamp_with_images_.at(nsec).at(i));
                }

                image_timestamps_.pop_front();
                timestamp_with_images_.erase(nsec);
                birdview_image_timestamp = front_timestamp;
                is_successful = true;
                LOG(INFO) << "BirdviewSplicerCmw --- the birdview image at timestmap " << nsec << " will be generated";
                break;
            }
            else
            {
                return is_successful;
            }
        }
    }

    cv::Mat birdview_img = birdview_show_ptr_->Compute(input_images);
    cv::Mat birdview_img_output;
    cvtColor(birdview_img, birdview_img_output, CV_RGB2BGR);

    uint8_t*              birdview_image_buffer      = birdview_img_output.ptr<uint8_t>(0);
    uint32_t              birdview_image_buffer_size = birdview_img_output.rows * birdview_img_output.cols * 3;
    holo::Image::Encoding birdview_image_encoding    = holo::Image::Encoding::RGB;
    birdview_image.SetData(birdview_image_buffer, birdview_image_buffer_size, birdview_img_output.cols,
                           birdview_img_output.rows, birdview_image_encoding);
    birdview_image.SetTriggerStamp(birdview_image_timestamp);
    return is_successful;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BirdviewSplicerCmw::PublishBirdviewImage(holo::Image const& image)
{
    birdview_image_ipc_->SetImageData(image);
    static holo::uint32_t counter = 0u;

    // publisher counter
    birdview_image_writer_.Write(counter);

    // publish info
    birdview_image_info_writer_.Write((static_cast<holo::uint64_t>(birdview_image_ipc_->GetSensorId()) << 32u) |
                                      static_cast<holo::uint64_t>(counter));
    // publish encoded image
    if (rgb_to_h264x_encoder_)
    {
        rgb_to_h264x_encoder_->Encode(image);
    }

    counter++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<holo::sensors::camera::ImageIpc> BirdviewSplicerCmw::getImgIpc(holo::common::SensorId sensor_id,
                                                                               uint32_t height, uint32_t width,
                                                                               holo::Image::Encoding encoding)
{
    std::shared_ptr<holo::sensors::camera::ImageIpc> img_ipc;
    img_ipc = std::make_shared<holo::sensors::camera::ImageIpc>(sensor_id, height, width, encoding);
    return img_ipc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BirdviewSplicerCmw::setUp(std::string const& config_file)
{
    holo::vision::BirdviewShow::BirdviewParameter birdview_parameter;
    holo::vision::BirdviewMask::MaskParameter     mask_parameter;
    std::vector<cv::Mat>                          masks;
    std::vector<BirdviewShow::IntrinsicType>      intrinsics;

    try
    {
        // initialize yaml node
        LOG(INFO) << "load config file from : " << config_file;
        holo::yaml::Node node_root = holo::yaml::LoadFile(config_file);

        // read birdview parameters
        const holo::yaml::Node birdview_parameters_node = node_root["birdview_parameters"];
        birdview_parameter.min_x                        = birdview_parameters_node["min_x"].as<Scalar>();
        birdview_parameter.max_x                        = birdview_parameters_node["max_x"].as<Scalar>();
        birdview_parameter.min_y                        = birdview_parameters_node["min_y"].as<Scalar>();
        birdview_parameter.max_y                        = birdview_parameters_node["max_y"].as<Scalar>();
        birdview_parameter.car_front_length             = birdview_parameters_node["car_front_length"].as<Scalar>();
        birdview_parameter.car_rear_length              = birdview_parameters_node["car_rear_length"].as<Scalar>();
        birdview_parameter.car_half_width               = birdview_parameters_node["car_half_width"].as<Scalar>();
        birdview_parameter.milimeter_per_pixel          = birdview_parameters_node["milimeter_per_pixel"].as<Scalar>();

        // read mask parameters
        const holo::yaml::Node mask_parameters_node = node_root["mask_parameters"];
        mask_parameter.min_x                        = birdview_parameters_node["min_x"].as<Scalar>();
        mask_parameter.max_x                        = birdview_parameters_node["max_x"].as<Scalar>();
        mask_parameter.min_y                        = birdview_parameters_node["min_y"].as<Scalar>();
        mask_parameter.max_y                        = birdview_parameters_node["max_y"].as<Scalar>();
        mask_parameter.milimeter_per_pixel          = birdview_parameters_node["milimeter_per_pixel"].as<Scalar>();
        mask_parameter.half_max_theta               = holo::Radian(mask_parameters_node["half_max_theta"].as<Scalar>());

        holo::yaml::Node camera_node      = node_root["cameras"];
        size_t           number_of_camera = camera_node.size();
        LOG(INFO) << "number_of_camera= " << number_of_camera;
        images_readers_.reserve(number_of_camera);

        for (size_t i = 0; i < number_of_camera; i++)
        {
            std::string intrinsic_file = holo::GetConfigFileAbsolutePath(camera_node[i]["intrinsic"].as<std::string>());
            LOG(INFO) << "intrinsic file path: " << intrinsic_file << std::endl;
            holo::yaml::Node                         intrinsic_node = holo::yaml::LoadFile(intrinsic_file);
            BirdviewShow::IntrinsicType              intrinsic      = intrinsic_node.as<BirdviewShow::IntrinsicType>();
            intrinsics.push_back(intrinsic);

            // initialize image ipc
            holo::common::SensorId camera_sensor_id = intrinsic.GetSensorId();
            uint16_t image_encoding = camera_node[i]["image_encoding"].as<uint16_t>();
            image_ipcs_.push_back(getImgIpc(camera_sensor_id, static_cast<uint32_t>(intrinsic.GetHeight()),
                                            static_cast<uint32_t>(intrinsic.GetWidth()),
                                            holo::Image::Encoding(image_encoding)));

            // load homography matrix and camera K
            std::string   HK_matrix_file          = camera_node[i]["HK"].as<std::string>();
            std::string   HK_matrix_file_absolute = holo::GetConfigFileAbsolutePath(HK_matrix_file);
            std::ifstream HK_matrix_stream(HK_matrix_file_absolute.c_str());
            std::string   temp;
            Scalar        f_temp;
            cv::Mat       cv_K(3, 3, CV_64FC1);
            cv::Mat       cv_H(3, 3, CV_64FC1);
            int8_t        number_of_input = 0;
            int8_t        H_row           = 0;
            int8_t        H_col           = 0;
            int8_t        K_row           = 0;
            int8_t        K_col           = 0;

            while (HK_matrix_stream >> temp)
            {
                temp.pop_back();
                f_temp = std::atof(temp.c_str());

                if (number_of_input > 10)
                {
                    if (K_col > 2)
                    {
                        K_col = 0;
                        K_row++;
                    }

                    cv_K.at<Scalar>(K_row, K_col) = f_temp;
                    K_col++;
                }
                else if (number_of_input > 0 && number_of_input < 10)
                {
                    if (H_col > 2)
                    {
                        H_col = 0;
                        H_row++;
                    }

                    cv_H.at<Scalar>(H_row, H_col) = f_temp;
                    H_col++;
                }

                number_of_input++;
            }

            LOG(INFO) << "camera matrix K: \n" << cv_K << std::endl;
            LOG(INFO) << "matrix H: \n" << cv_H << std::endl;

            image_type_converters_.push_back(
                std::make_shared<holo::vision::ImageTypeConverter>(intrinsic.GetHeight(), intrinsic.GetWidth()));
            birdview_parameter.Hs.push_back(cv_H);
            birdview_parameter.Ks.push_back(cv_K);

            Scalar rows = intrinsic.GetHeight();
            Scalar cols = intrinsic.GetWidth();
            birdview_parameter.images_rows.push_back(rows);
            birdview_parameter.images_cols.push_back(cols);

            // initialize subscribers
            std::string camera_topic = camera_node[i]["topic"].as<std::string>();
            LOG(INFO) << "camera_topic : " << camera_topic;
            images_readers_.emplace_back(bus_.AddReader<holo::uint32_t>(camera_topic));
            images_readers_[i].SetOnDataAvailableCallback(
                std::bind(&BirdviewSplicerCmw::inputImageCallback, this, i, std::placeholders::_1));
        }

        // load birdview mask parameters and compute mask
        const holo::yaml::Node     mask_point_node = mask_parameters_node["mask_points"];
        holo::vision::BirdviewMask birdview_mask(mask_parameter);

        for (uint8_t i = 0u; i < mask_point_node.size(); i++)
        {
            std::vector<Scalar>    point_x = mask_point_node[i]["x"].as<std::vector<Scalar>>();
            std::vector<Scalar>    point_y = mask_point_node[i]["y"].as<std::vector<Scalar>>();
            std::vector<cv::Point> points;

            for (uint8_t j = 0u; j < point_x.size(); j++)
            {
                cv::Point point = cv::Point(point_x[j], point_y[j]);
                points.push_back(point);
            }

            cv::Mat mask = birdview_mask.ComputeImageMask(points);
            masks.push_back(mask);
        }

        // initialize birdview image encoder and publisher
        holo::common::SensorId birdview_sensor_id = birdview_parameters_node["sensor_id"].as<uint32_t>();
        uint32_t birdview_height = static_cast<uint32_t>((birdview_parameter.max_y - birdview_parameter.min_y) /
                                                         birdview_parameter.milimeter_per_pixel);
        uint32_t birdview_width  = static_cast<uint32_t>((birdview_parameter.max_x - birdview_parameter.min_x) /
                                                        birdview_parameter.milimeter_per_pixel);
        birdview_image_ipc_ =
            std::make_shared<holo::sensors::camera::ImageIpc>(birdview_sensor_id, birdview_height, birdview_width);
        std::string const birdview_topic = birdview_parameters_node["topic"].as<std::string>();
        LOG(INFO) << "birdview_topic : " << birdview_topic;
        birdview_image_writer_      = bus_.AddWriter<holo::uint32_t>(birdview_topic + "_counter");
        birdview_image_info_writer_ = bus_.AddWriter<holo::uint64_t>(birdview_topic + "_info");

        // check whether enable encoder
        bool const enable_birdview_image_encoder =
            birdview_parameters_node["enable_birdview_image_encoder"].as<bool>(false);

        if (enable_birdview_image_encoder)
        {
            encoded_birdview_image_buffer_ = std::shared_ptr<holo::uint8_t>(new holo::uint8_t[image_encode_size_max_](),
                                                                            std::default_delete<uint8_t[]>());
            rgb_to_h264x_encoder_ =
                std::make_shared<holo::sensors::camera::H264Encoder>(birdview_width, birdview_height, 20u);
            rgb_to_h264x_encoder_->SetSender(
                std::bind(&BirdviewSplicerCmw::processEncodedImage, this, std::placeholders::_1));
            birdview_image_encoded_writer_ = bus_.AddWriter<holo::uint8_t*>(birdview_topic + "_encoder");
        }

        // other paramters
        verbose_ = node_root["verbose"].as<bool>(false);
    }

    catch (const std::exception& e)
    {
        LOG(ERROR) << "Birdview_splicer_cmw --- load parameters from '" << config_file << "' failed:\n" << e.what();
        throw e;
    }

    birdview_show_ptr_ = std::make_shared<holo::vision::BirdviewShow>(birdview_parameter, masks, intrinsics);
    LOG(INFO) << "BirdviewSplicerCmw --- Finished set Up!!!";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BirdviewSplicerCmw::inputImageCallback(size_t const i, holo::uint32_t msg)
{
    (void)msg;

    if (i >= image_type_converters_.size() || i >= image_ipcs_.size())
    {
        LOG(ERROR)
            << "inputImageCallback --- the number of camera, type converter does not match!!! there is problem for "
            << i << "th camera, "
            << ", #converter = " << image_type_converters_.size() << ", #ipc = " << image_ipcs_.size();
        return;
    }

    LOG_IF(INFO, verbose_) << "inputImageCallback --- process " << std::to_string(i) << "th camera!";

    holo::Image image;
    image_ipcs_[i]->GetImageData(image);

    cv::Mat input_image;

    if (image.GetEncoding() == holo::Image::Encoding::NV12)
    {
        input_image = image_type_converters_[i]->Compute(image.GetCvType());
        LOG_IF(INFO, verbose_) << "inputImageCallback --- finished " << std::to_string(i) << "th camera nv12 convert!";
    }
    else
    {
        input_image = image.GetCvType();
    }

    if (verbose_)
    {
        std::string const file_name = "./" + std::to_string(i) + "_rgb.png";
        cv::imwrite(file_name, input_image);
        cv::imshow(std::to_string(i) + "_rgb", input_image);
    }


    Timestamp const              trigger_timestamp = image.GetTriggerStamp();
    holo::uint64_t const         nsec              = trigger_timestamp.ToNsec();
    cv::putText(input_image, std::to_string(trigger_timestamp.GetSec()),
                cv::Point2f(input_image.cols / 3.0, input_image.rows * 7.0 / 12.0 - 50), 2, 2, cv::Scalar(0, 0, 255));
    cv::putText(input_image, std::to_string(trigger_timestamp.GetNsec()),
                cv::Point2f(input_image.cols / 3.0, input_image.rows * 7.0 / 12.0), 2, 2, cv::Scalar(0, 0, 255));

    std::unique_lock<std::mutex> lock(timestamp_with_images_mutex_);

    if (image_timestamps_.empty() || trigger_timestamp >= image_timestamps_.back())
    {
        if (timestamp_with_images_.find(nsec) == timestamp_with_images_.end())
        {
            image_timestamps_.push_back(trigger_timestamp);
        }

        timestamp_with_images_[nsec][i] = input_image;
    }
    else
    {
        LOG(WARNING) << "BirdviewSplicerCmw --- the image of " << i
                     << "th camera is later than other cameras, the image timestamp is " << nsec
                     << ", the newest image timestamp is " << image_timestamps_.back().ToNsec();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BirdviewSplicerCmw::processEncodedImage(ImagePacket const& encoded_image)
{
    holo::serialization::Serializer<false, 4> serializer(encoded_birdview_image_buffer_.get(),
                                                         image_encode_size_max_);  ///< serializer for encoder
    if (encoded_image.Serialize(serializer))
    {
        birdview_image_encoded_writer_.Write(serializer.GetData(), serializer.GetSize());
    }
}
}  // namespace holo_cmw

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t main(int argc, char** argv)
{
    cxxopts::Options options(holo_cmw::APP_NAME, "Birdview CMW Node");
    options.add_options()("help", "help message")("c,config_file", "configure file path and name in .yaml format",
                                                  cxxopts::value<std::string>())(
        "d,domain_id", "domain id to initialize ddsBus", cxxopts::value<uint32_t>()->default_value("100"))(
        "n,participant_namespace", "namespace for the domain participant tag, defalut is empty",
        cxxopts::value<std::string>()->default_value(""))("v,visualize", "switch of visualizing image",
                                                          cxxopts::value<uint16_t>()->default_value("0"))(
        "s,save", "switch of saving image",
        cxxopts::value<uint16_t>()->default_value("0"))("o,output_path", "output path to save image, default is /tmp",
                                                        cxxopts::value<std::string>()->default_value("/tmp"))(
        "f,frequency", "frequency of publishing images",
        cxxopts::value<holo_cmw::BirdviewSplicerCmw::Scalar>()->default_value("10.0"));

    options.parse(argc, argv);

    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 1;
    }

    std::string                          config_file           = options["config_file"].as<std::string>();
    uint32_t                             domain_id             = options["domain_id"].as<uint32_t>();
    std::string                          participant_namespace = options["participant_namespace"].as<std::string>();
    std::string                          output_path           = options["output_path"].as<std::string>();
    bool                                 visualize_switch      = options["visualize"].as<uint16_t>() ? true : false;
    bool                                 save_switch           = options["save"].as<uint16_t>() ? true : false;
    holo_cmw::BirdviewSplicerCmw::Scalar frequency = options["frequency"].as<holo_cmw::BirdviewSplicerCmw::Scalar>();

    LOG(INFO) << "Start splice!";
    // set birdview splice app
    holo_cmw::BirdviewSplicerCmw::BusType::Initialize(argc, argv, holo_cmw::APP_NAME);
    holo_cmw::BirdviewSplicerCmw app(argc, argv, config_file, domain_id, participant_namespace);
    app.Spin();
    holo::Timer timer(frequency);

    while (app.IsRunning())
    {
        timer.Start();
        holo::Image birdview_image;

        if (!app.ComputeBirdviewImage(birdview_image))
        {
            usleep(1e3);
            continue;
        }

        cv::Mat result = birdview_image.GetCvType();

        if (visualize_switch && !result.empty())
        {
            cv::imshow("birdview", result);
            cv::waitKey(1);
        }

        app.PublishBirdviewImage(birdview_image);

        if (save_switch && !result.empty())
        {
            std::stringstream     ss;
            static holo::uint64_t count = 0u;
            count++;
            ss << std::setw(8) << std::setfill('0') << count << ".png";
            std::string output_image = ss.str();
            output_image             = std::to_string(birdview_image.GetTriggerStamp().ToSec()) + "_" + output_image;
            LOG(INFO) << "save image to : " << output_image;
            cv::imwrite(output_path + "/" + output_image, result);
            ss.str("");
        }

        timer.Stop();
    }

    return 0;
}
