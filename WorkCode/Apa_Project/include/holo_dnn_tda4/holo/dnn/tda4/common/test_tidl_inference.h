
#ifndef _TEST_TIDL_INFERENCE_
#define _TEST_TIDL_INFERENCE_

#include <assert.h>
#include <holo/dnn/tda4/common/TadlInference.h>
#include <holo/utils/holo_root.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <atomic>
#include <cmath>
#include <iostream>
#include <mutex>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <queue>
#include <vector>

extern std::atomic<int> TERMINATE_STATE;

namespace holo
{
namespace perception
{
class TIDLLocker
{
public:
    TIDLLocker(std::atomic<int>& l) : l_(l)
    {
        l_--;
    }
    ~TIDLLocker()
    {
        l_++;
    }
    std::atomic<int>& l_;
};

class TidlInferenceDet
{
public:
    TidlBase* app_inference_;

    std::string tidl_config_file_;
    std::string tidl_network_file_;
    uint32_t    pipeline_depth_;

    int             num_bytes_;
    std::queue<int> image_q;
    std::string     data_format_;
    std::string     yuv_type_;
    uint8_t*        data_;

    std::vector<std::pair<uint8_t*, uint8_t*>> image_buff_vector_;

    int    height_, width_;
    int    crop_start_x_ = 0, crop_start_y_ = 0, crop_end_x_ = 0, crop_end_y_ = 0;
    int    crop_width_, crop_height_;
    int    dl_height_, dl_width_;
    int    dl_output_height_, dl_output_width_;
    float* featuremap_;
    int    featuremap_size_;

    int                           buf_depth_;
    std::vector<std::vector<int>> featuremap_vector_;

public:
    TidlInferenceDet(std::string cfg_file)
    {
        char* cfg = (char*)cfg_file.c_str();
        std::cout << "read config: " << cfg << std::endl;
        read_config(cfg);
        tidl_config_file_  = GetConfigFileAbsolutePath(tidl_config_file_);
        tidl_network_file_ = GetConfigFileAbsolutePath(tidl_network_file_);

        std::vector<std::string> data_format_list = {"NV12", "UYVY", "RGBX", "RGB"};
        if (std::find(data_format_list.begin(), data_format_list.end(), data_format_) == data_format_list.end())
        {
            std::cout << "YOU SHOULD SET INVALID DATA_FORMAT: NV12, UYVY, RGBX" << std::endl;
            while (1)
            {
                usleep(100);
            }
        }

        std::cout << "tidl config file: " << tidl_config_file_ << std::endl;
        std::cout << "tidl network file: " << tidl_network_file_ << std::endl;
        std::cout << "pipeline depth: " << pipeline_depth_ << std::endl;
        std::cout << "crop param: " << crop_start_x_ << " " << crop_start_y_ << " " << crop_end_x_ << " " << crop_end_y_
                  << std::endl;
        std::cout << "height width dl_height dl_width: " << height_ << " " << width_ << " " << dl_height_ << " "
                  << dl_width_ << std::endl;
        std::cout << "data format: " << data_format_ << std::endl;
        buf_depth_ = pipeline_depth_;
        // if crop param is not set
        assert(crop_start_x_ >= 0 && crop_start_y_ >= 0 && crop_end_x_ <= width_ && crop_end_y_ <= height_);
        if (crop_start_x_ == 0 && crop_start_y_ == 0 && crop_end_x_ == 0 && crop_end_y_ == 0)
        {
            crop_end_x_ = width_;
            crop_end_y_ = height_;
        }
        assert(crop_end_x_ - crop_start_x_ >= dl_width_ && crop_end_y_ - crop_start_y_ >= dl_height_);
        crop_width_  = crop_end_x_ - crop_start_x_;
        crop_height_ = crop_end_y_ - crop_start_y_;

        app_inference_ = new AppTadlInference(
            (char*)tidl_config_file_.c_str(), (char*)tidl_network_file_.c_str(), pipeline_depth_, height_, width_,
            (std::vector<int>){crop_start_y_, crop_start_x_, crop_height_, crop_width_}, dl_height_, dl_width_,
            data_format_);
        height_    = app_inference_->height_;
        width_     = app_inference_->width_;
        dl_height_ = app_inference_->dl_height_;
        dl_width_  = app_inference_->dl_width_;
        if (data_format_ == "UYVY")
        {
            num_bytes_ = height_ * width_ * 2;
            data_      = new uint8_t[num_bytes_];
        }
        else if (data_format_ == "RGBX")
        {
            num_bytes_ = height_ * width_ * 4;
            data_      = new uint8_t[num_bytes_];
        }
        else if (data_format_ == "RGB")
        {
            num_bytes_ = height_ * width_ * 3;
            data_      = new uint8_t[num_bytes_];
        }
        else
        {
            num_bytes_ = height_ * width_ * 3 / 2;
            data_      = new uint8_t[num_bytes_];
        }
        GetImgDataPtr(image_buff_vector_);
        std::cout << "input arr address" << std::endl;
        for (int i = 0; i < image_buff_vector_.size(); i++)
        {
            std::cout << (void*)image_buff_vector_[i].first << " " << (void*)image_buff_vector_[i].second << std::endl;
        }

        std::cout << "app_inference_->featuremap_size_: " << app_inference_->featuremap_size_ << std::endl;
        SetFeatureMap(app_inference_->featuremap_size_);
    }

    ~TidlInferenceDet()
    {
        while (TERMINATE_STATE != 0)
        {
            usleep(100);
        }
        std::cout << "del tidl" << std::endl;
        if (app_inference_ != NULL)
            delete app_inference_;
        std::cout << "del tidl end" << std::endl;
        if (featuremap_ != NULL)
            delete[] featuremap_;
    }
    void SetFeatureMap(int feature_size)
    {
        featuremap_size_ = feature_size;
        featuremap_      = new float[featuremap_size_];
    }
    void read_config(char* cfg_file);

    /**
     * @brief map tensor memcpy start inference
     *
     * @param data
     * @return int
     */
    int setdata(uint8_t* data);

    /**
     * @brief memcpy
     *
     * @param data
     * @param index
     * @return true
     * @return false
     */
    bool setdatapre(uint8_t* data, int index);

    /**
     * @brief zero copy(don't need map tensor and memcpy)
     *
     * @param data_arr1
     * @param index
     * @return true
     * @return false
     */
    bool SetDataNoCopy(uint64_t* data_arr1, int index);

    /**
     * @brief start inference
     *
     * @param index
     * @return true
     * @return false
     */
    bool startinference(int index);

    /**
     * @brief get output data
     *
     * @return int
     */
    int getdata();

    void GetImgDataPtr(std::vector<std::pair<uint8_t*, uint8_t*>>& image_buff_vector)
    {
        if (data_format_ != "NV12")
        {
            std::vector<uint8_t*> data_vector;
            app_inference_->GetImageDataPtr(data_vector);
            for (int i = 0; i < data_vector.size(); i++)
            {
                image_buff_vector.push_back(std::make_pair(data_vector[i], nullptr));
            }
        }
        else
        {
            app_inference_->GetScalerNodeInputDataAddr(image_buff_vector);
        }
    }
};

}  // namespace perception
}  // namespace holo

#endif
