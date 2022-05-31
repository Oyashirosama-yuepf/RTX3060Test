/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
/**
 * @file virtual_camera_interface.h
 * @brief define the virtual camera interface class
 * @author yongchuan<yongchuan@holomatic.com>
 * @date 2021-12-14
 */
#ifndef HOLO_SENSORS_CMW_APP_INTERFACE_VIRTUAL_CAMERA_INTERFACE_H
#define HOLO_SENSORS_CMW_APP_INTERFACE_VIRTUAL_CAMERA_INTERFACE_H

#include <dirent.h>
#include <holo/os/timer.h>
#include <holo/utils/yaml.h>
#include <opencv2/highgui/highgui_c.h>
#include <functional>
#include <opencv2/opencv.hpp>
#include <thread>

namespace holo
{
namespace sensors
{
namespace interface
{
using holo::common::Timestamp;
using holo::sensors::camera::StreamBuffer;

struct VirtCamInterfaceParam
{
    std::string img_dir;
    uint32_t    fps;
};

class VirtCamInterface
{
public:
    using BufferCallbackType = std::function<void(const StreamBuffer&, const Timestamp&, const Timestamp&)>;
    VirtCamInterface()       = delete;
    VirtCamInterface(const VirtCamInterfaceParam param)
      : buffer_callback_(nullptr), counts_(0), running_(true), image_name_mode_(true), namelist_(nullptr)
    {
        Init(param);
    }
    VirtCamInterface(const holo::yaml::Node& node)
    {
        VirtCamInterfaceParam param;
        param.img_dir = node["device_name"].as<std::string>();
        param.fps     = node["fps"].as<uint32_t>();
        Init(param);
    }
    void InstallCallback(const BufferCallbackType& handler) noexcept
    {
        buffer_callback_ = handler;
    }
    ~VirtCamInterface()
    {
        running_ = false;
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
    }

private:
    void Init(const VirtCamInterfaceParam& param)
    {
        param_  = param;
        counts_ = scandir(param_.img_dir.c_str(), &namelist_, ImgNameFilter, versionsort);
        LOG(INFO) << "Image directory:" << param_.img_dir;
        if (counts_ < 0)
        {
            std::string error = "Read image directory error ";
            LOG(INFO) << ":" << error;
            throw std::runtime_error(error);
        }
        else
        {
            LOG(INFO) << "Total image number is: " << counts_;
        }
        // calculate fps
        std::string            first_img(namelist_[0]->d_name);
        std::string::size_type first_underline = first_img.find("_");
        if (first_underline == first_img.npos)
        {
            std::string error = "The format of image name is error";
            LOG(INFO) << error << ": " << strerror(errno);
            throw std::runtime_error(error);
        }
        std::string::size_type second_underline = first_img.find("_", first_underline + 1);
        std::string::size_type dot              = first_img.find(".", second_underline + 1);
        std::string            first_sec;
        if (dot == first_img.npos)
        {
            std::string error = "The format of image name is error";
            LOG(INFO) << error << ": " << strerror(errno);
            throw std::runtime_error(error);
        }
        if (second_underline != first_img.npos)
        {
            first_sec.assign(first_img, first_underline + 1, second_underline - first_underline - 1);
        }
        else
        {
            first_sec.assign(first_img, 0, first_underline);
            image_name_mode_ = false;
        }
        int32_t     not_equal_count = 0;
        std::string img_name;
        for (int j = 1; j < counts_; j++)
        {
            img_name         = namelist_[j]->d_name;
            first_underline  = img_name.find("_");
            second_underline = img_name.find("_", first_underline + 1);
            std::string second;
            if (image_name_mode_)
            {
                second.assign(img_name, first_underline + 1, second_underline - first_underline - 1);
            }
            else
            {
                second.assign(img_name, 0, first_underline);
            }
            if (second.compare(first_sec) == 0)
            {
                if (not_equal_count == 1)
                {
                    param_.fps++;
                }
            }
            else
            {
                if (not_equal_count == 0)
                {
                    first_sec.clear();
                    first_sec = second;
                    param_.fps++;
                }
                not_equal_count++;
                if (not_equal_count == 2)
                {
                    break;
                }
            }
        }
        if (param_.fps >= 7 && param_.fps < 15)
        {
            param_.fps = 10;
        }
        else if (param_.fps >= 15 && param_.fps < 25)
        {
            param_.fps = 20;
        }
        else if (param_.fps >= 25 && param_.fps < 33)
        {
            param_.fps = 30;
        }
        LOG(INFO) << "FPS = " << param_.fps;
        thread_ = std::make_shared<std::thread>(&VirtCamInterface::ReadImg, this);
    }

    static int ImgNameFilter(const struct dirent* cur)
    {
        std::string str(cur->d_name);
        if (str.find(".jpg") != std::string::npos || str.find(".jpeg") != std::string::npos ||
            str.find(".png") != std::string::npos)
        {
            return 1;
        }
        return 0;
    }

    void ReadImg()
    {
        // read image
        std::string  abs_path;
        cv::Mat      bgr_img;
        cv::Mat      nv12_img;
        StreamBuffer buffer;
        for (uint64 i = 0; i < counts_; i++)
        {
            std::chrono::steady_clock::time_point beforeTime = std::chrono::steady_clock::now();
            if (!running_)
            {
                break;
            }
            /* skip . && .. */
            if (namelist_[i]->d_name[0] == '.')
                continue;

            // get timestamp
            std::string            sec;
            std::string            nsec;
            std::string::size_type first_underline;
            std::string::size_type second_underline;
            std::string::size_type dot;
            std::string            img(namelist_[i]->d_name);
            if (image_name_mode_)
            {
                first_underline  = img.find("_");
                second_underline = img.find("_", first_underline + 1);
                dot              = img.find(".", second_underline + 1);
                sec.assign(img, first_underline + 1, second_underline - first_underline - 1);
                nsec.assign(img, second_underline + 1, dot - second_underline - 1);
            }
            else
            {
                first_underline = img.find("_");
                dot             = img.find(".", first_underline + 1);
                if (dot == std::string::npos)
                    std::cout << "dot" << std::endl;
                sec.assign(img, 0, first_underline);
                nsec.assign(img, first_underline + 1, dot - first_underline - 1);
            }

            Timestamp stamp(strtoul(sec.c_str(), NULL, 10), strtoul(nsec.c_str(), NULL, 10));
            // LOG(INFO) << std::setprecision(19) << "stamp =" << stamp.ToSec();

            // read image
            abs_path = param_.img_dir + "/" + namelist_[i]->d_name;
            bgr_img  = cv::imread(abs_path);
            if (bgr_img.empty())
            {
                continue;
            }
            cv::cvtColor(bgr_img, nv12_img, CV_BGR2YUV_I420);  // yuv420p == YUV_I420

            int height = bgr_img.rows;
            int width  = bgr_img.cols;

            uint8_t* yuv      = nv12_img.ptr<uint8_t>();
            cv::Mat  img_nv12 = cv::Mat(height * 3 / 2, width, CV_8UC1);
            uint8_t* ynv12    = img_nv12.ptr<uint8_t>();

            int32_t uv_height = height / 2;
            int32_t uv_width  = width / 2;

            // copy y data
            int32_t y_size = height * width;
            memcpy(ynv12, yuv, y_size);

            // copy uv data
            uint8_t* nv12   = ynv12 + y_size;
            uint8_t* u_data = yuv + y_size;
            uint8_t* v_data = u_data + uv_height * uv_width;

            for (int32_t i = 0; i < uv_width * uv_height; i++)
            {
                *nv12++ = *u_data++;
                *nv12++ = *v_data++;
            }

            int32_t yuv_size = y_size + 2 * uv_height * uv_width;

            buffer.init     = true;
            buffer.start    = yuv;
            buffer.capacity = height * width * 3 / 2;
            buffer.size     = height * width * 3 / 2;
            uint32_t utc_sec, utc_nsec;
            holo::os::GetSystemTime(utc_sec, utc_nsec);
            Timestamp received_stamp = holo::common::Timestamp(utc_sec, utc_nsec);
            if (buffer_callback_)
            {
                buffer_callback_(buffer, received_stamp, stamp);
            }
            std::chrono::steady_clock::time_point afterTime = std::chrono::steady_clock::now();
            double    duration_millsecond = std::chrono::duration<double, std::milli>(afterTime - beforeTime).count();
            float64_t run_duration        = trunc(duration_millsecond);
            float64_t wait_duration       = MSEC_PER_SEC / param_.fps;
            if (wait_duration >= run_duration)
            {
                usleep((wait_duration - run_duration) * MSEC_PER_SEC);
            }
            else
            {
                LOG(WARNING) << "camera fps may decline";
            }
            free(namelist_[i]);
        }
        free(namelist_);
    }

private:
    uint64_t                     counts_;
    bool                         running_;
    bool                         image_name_mode_;
    VirtCamInterfaceParam        param_;
    struct dirent**              namelist_;
    BufferCallbackType           buffer_callback_;
    std::shared_ptr<std::thread> thread_;

private:
    static int32_t const MSEC_PER_SEC  = 1000;
    static int32_t const NSEC_PER_MSEC = 1000000;
};
}  // namespace interface
}  // namespace sensors
}  // namespace holo
#endif