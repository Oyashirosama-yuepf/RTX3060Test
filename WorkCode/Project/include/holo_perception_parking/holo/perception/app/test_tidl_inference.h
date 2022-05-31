
#ifndef _TEST_TIDL_INFERENCE_
#define _TEST_TIDL_INFERENCE_

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <vector>
#include <queue>
#include <mutex>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <holo/perception/inference/tidl/TadlInference.h>
#include <iostream>
#include <holo/utils/holo_root.h>
#include <atomic>
#include <signal.h>
#include <holo/utils/holo_root.h>
#include<cmath>

extern std::atomic<int> TERMINATE_STATE;
extern void             tidl_release_memory_handler(int sig);

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

class Decode
{
    // centernet decode
public:
    bool decode(std::vector<std::vector<float>>& det_result, bool nms_flag=false, int decode_type=0);
    bool nms(std::vector<std::vector<float>>& det_result);
    virtual ~Decode(){};

public:
    int    height_, width_;
    int    crop_start_x_=0, crop_start_y_=0, crop_end_x_=0, crop_end_y_=0;
    int    dl_height_, dl_width_;
    int    dl_output_height_, dl_output_width_;
    float  score_ = 0;
    float* featuremap_;
    int    featuremap_size_;
    int    cls_num, wh_num, attr_num, keypoints_num;
};

class TidlInferenceDet : public Decode
{
public:
    TidlBase* app_inference_;  // AppTadlInference* app_inference_;
    // AppTidl* app_inference_;

    std::string tidl_config_file_;
    std::string tidl_network_file_;
    uint32_t pipeline_depth_;

    int             num_bytes_;
    std::queue<int> image_q;
    // int cls_num, wh_num, attr_num, keypoints_num;
    std::string data_format_ = "YUV";  // RGB YUV
    std::string yuv_type_ = "nv12";
    uint8_t*    data_;
    cv::Mat     rgb_img_resize_;
    // to do organize
    uint8_t graph_tidl_model_ = 1;
    std::vector<Sp_point> sp_point_;
    int sp_num_ = 500;
    float* descriptor_data_;
    uint8_t graph_node_work[2];

public:
    TidlInferenceDet(std::string cfg_file)
    {
        char* cfg = (char*)cfg_file.c_str();
        std::cout << "read config" << std::endl;
        std::cout << cfg << std::endl;
        read_config(cfg);
        tidl_config_file_  = GetConfigFileAbsolutePath(tidl_config_file_);
        tidl_network_file_ = GetConfigFileAbsolutePath(tidl_network_file_);
        score_ = -std::log(1/score_-1);
        std::cout << "cls_num: " << cls_num << " wh_num: " << wh_num << " attr_num: " << attr_num
                  << " keypoints_num: " << keypoints_num << " data_format: " << data_format_ << std::endl;
        std::cout << "graph tidl model: " << (int)graph_tidl_model_ << std::endl;
        
        if(data_format_ == "YUV" || data_format_ == "NV12")
        {
            data_format_ = "YUV";
            yuv_type_ = "nv12";
        }
        else if(data_format_ == "UYVY")
        {
            data_format_ = "YUV";
            yuv_type_ = "uyvy";
        }
        else if(data_format_ == "RGBX")
        {  
            data_format_ = "YUV";
            yuv_type_ = "rgbx";
        }

        if (data_format_ == "YUV" && graph_tidl_model_ == 1)
        {
            std::cout << "yuv set" << std::endl;
            // app_inference_ = new AppTadlInference(cfg);
            std::cout << "tidl config file: " << tidl_config_file_ << std::endl;
            std::cout << "tidl network file: " << tidl_network_file_ << std::endl;
            std::cout << "pipeline depth: " << pipeline_depth_ << std::endl;
            std::cout << "crop param: " << crop_start_x_ << " " << crop_start_y_ << " " << crop_end_x_ << " " << crop_end_y_ << std::endl;             
            std::cout << "height width dl_height dl_width: " << height_ << " " << width_ << " " << dl_height_ << " " << dl_width_ << std::endl;
            std::cout << "yuv type: "<< yuv_type_<<std::endl;
            // if crop param is not set
            if(crop_start_x_ == 0 && crop_start_y_==0 && crop_end_x_ == 0 && crop_end_y_== 0)
            {
                crop_end_x_ = width_;
                crop_end_y_ = height_;
            }
            app_inference_ = new AppTadlInference((char*)tidl_config_file_.c_str(), (char*)tidl_network_file_.c_str(), pipeline_depth_, 
                                                  height_, width_, (std::vector<int>){crop_start_y_, crop_start_x_, crop_end_y_, crop_end_x_}, dl_height_,
                                                  dl_width_, yuv_type_, std::string("RGB"));
            height_        = app_inference_->height_;
            width_         = app_inference_->width_;
            dl_height_     = app_inference_->dl_height_;
            dl_width_      = app_inference_->dl_width_;
            if(yuv_type_ == "uyvy")
            {
                num_bytes_     = height_ * width_ * 2;
                data_          = new uint8_t[num_bytes_];
            }
            else if(yuv_type_ == "rgbx")
            {
                num_bytes_     = height_ * width_ * 4;
                data_          = new uint8_t[num_bytes_];
            }
            else
            {
                num_bytes_     = height_ * width_ * 3 / 2;
                data_          = new uint8_t[num_bytes_];
            }
        }
        else if (data_format_ == "RGB" && graph_tidl_model_ == 1)
        {
            std::cout << "rgb set" << std::endl;
            tidl_config_file_  = GetConfigFileAbsolutePath(tidl_config_file_);
            tidl_network_file_ = GetConfigFileAbsolutePath(tidl_network_file_);
            std::cout << tidl_config_file_ << std::endl;
            std::cout << tidl_network_file_ << std::endl;
            std::cout << pipeline_depth_ << std::endl;
            // app_inference_ = new AppTidl(cfg);
            std::cout << height_ << " " << width_ << " " << dl_height_ << " " << dl_width_ << std::endl;
            app_inference_ = new AppTidl((char*)tidl_config_file_.c_str(), (char*)tidl_network_file_.c_str(), pipeline_depth_, 
                                          height_, width_, (std::vector<int>){0, 0, 720, 1280}, dl_height_, dl_width_);
            // height_ = app_inference_->height_;
            // width_ = app_inference_->width_;
            dl_height_ = app_inference_->dl_height_;
            dl_width_  = app_inference_->dl_width_;
            // height_    = app_inference_->dl_height_;
            // width_     = app_inference_->dl_width_;
            num_bytes_ = dl_height_ * dl_width_ * 3;
            data_      = new uint8_t[num_bytes_];
            rgb_img_resize_.create(dl_height_, dl_width_, CV_8UC3);
        }
        else if(graph_tidl_model_ == 2)   // to do organize
        {
            std::cout << "yuv set" << std::endl;
            // app_inference_ = new AppTadlInference(cfg);
            std::cout << tidl_config_file_ << std::endl;
            std::cout << tidl_network_file_ << std::endl;
            std::cout << pipeline_depth_ << std::endl;
            std::cout << crop_start_x_ << " " << crop_start_y_ << " " << crop_end_x_ << " " << crop_end_y_ << std::endl;             
            std::cout << height_ << " " << width_ << " " << dl_height_ << " " << dl_width_ << std::endl;
            std::cout << "yuv type "<< yuv_type_<<std::endl;
            // if crop param is not set
            if(crop_start_x_ == 0 && crop_start_y_==0 && crop_end_x_ == 0 && crop_end_y_== 0)
            {
                crop_end_x_ = width_;
                crop_end_y_ = height_;
            }

            std::vector<AppTidlConfig> config_param;
            config_param.push_back(AppTidlConfig());
            config_param.push_back(AppTidlConfig());
            config_param[0].tidl_config_ = (char *)tidl_config_file_.c_str();
            config_param[0].tidl_network_ = (char*)tidl_network_file_.c_str();
            config_param[0].pipeline_depth_ = 4;
            config_param[0].height_ = height_;
            config_param[0].width_ = width_;
            config_param[0].crop_param_ = (std::vector<int>){crop_start_y_, crop_start_x_, crop_end_y_, crop_end_x_};
            config_param[0].dl_height_ = dl_height_;
            config_param[0].dl_width_ = dl_width_;
            config_param[0].yuv_type_ = yuv_type_;
            config_param[0].data_format_ = std::string("RGB");
            std::string tidl_config_file_fix = "holo_localization_deep/app_config/tda4_feature_detector_1.bin";
            std::string tidl_network_file_fix = "holo_localization_deep/app_config/tda4_feature_detector.bin";
            tidl_config_file_fix  = GetConfigFileAbsolutePath(tidl_config_file_fix);
            tidl_network_file_fix = GetConfigFileAbsolutePath(tidl_network_file_fix);
            
            config_param[1].tidl_config_ = (char *)tidl_config_file_fix.c_str();
            config_param[1].tidl_network_ = (char*)tidl_network_file_fix.c_str();
            config_param[1].pipeline_depth_ = 4;
            config_param[1].height_ = height_;
            config_param[1].width_ = width_;
            config_param[1].crop_param_ = (std::vector<int>){crop_start_y_, crop_start_x_, crop_end_y_, crop_end_x_};
            config_param[1].dl_height_ = 480;
            config_param[1].dl_width_ = 640;
            config_param[1].yuv_type_ = yuv_type_;
            config_param[1].data_format_ = std::string("RGB");
            config_param[1].sp_num_ = sp_num_;

            app_inference_ = new AppTadlInference(config_param);
            
            // tmp
            descriptor_data_ = new float[sp_num_ * 128];
            height_ = app_inference_->height_;
            width_         = app_inference_->width_;
            dl_height_     = app_inference_->dl_height_;
            dl_width_      = app_inference_->dl_width_;

            if (yuv_type_ == "uyvy")
            {
                num_bytes_     = height_ * width_ * 2;
                data_          = new uint8_t[num_bytes_];
            }
            else
            {
                num_bytes_     = height_ * width_ * 3 / 2;
                data_          = new uint8_t[num_bytes_];
            }
            graph_node_work[0] = 1;
            graph_node_work[1] = 1;
        }
        // score_ = 0;
        // need a neat way to set these handlers.
        // signal(SIGHUP, tidl_release_memory_handler);
        signal(SIGINT, tidl_release_memory_handler);
        // signal(SIGSEGV, tidl_release_memory_handler);
        // signal(SIGPIPE, tidl_release_memory_handler);
        // signal(SIGALRM, tidl_release_memory_handler);
        // signal(SIGTERM, tidl_release_memory_handler);
    }

    ~TidlInferenceDet()
    {
        std::cout << "del tidl" << std::endl;
        if (app_inference_ != NULL)
            delete app_inference_;
        std::cout << "del tidl end" << std::endl;
        if (featuremap_ != NULL)
            delete[] featuremap_;
    }
    // int setdata(cv::Mat& data);
    void SetFeatureMap(int feature_size)
    {
        featuremap_size_ = feature_size;
        featuremap_      = new float[featuremap_size_];
    }
    void read_config(char* cfg_file);

    int  setdata(uint8_t* data);
    bool setdata(uint8_t* data, int flag);
    bool setdataref(int index);
    int  getdata(float* featuremap);
    int getdecodedata(std::vector<std::vector<float>>& det_result);
    int  getdata();
    void getspdata();
    void GetImgDataPtr(std::vector<std::pair<uint8_t *, uint8_t *>> &image_buff_vector)
    {
        if(yuv_type_ == "uyvy")
        {
            std::vector<uint8_t*> uyvy_data_vector;
            app_inference_->GetImageDataPtr(uyvy_data_vector);
            for(int i=0; i<uyvy_data_vector.size(); i++)
            {
                image_buff_vector.push_back(std::make_pair(uyvy_data_vector[i], nullptr));
            }
        }
        else
        {
            app_inference_->GetScalerNodeInputDataAddr(image_buff_vector);
        }        
    }
};

class FeatureMap
{
public:
    float* data;
    int    channel_;
    int    height_;
    int    width_;
    int    data_len_;
    //   FeatureMap();
    FeatureMap(float* data_tmp, int channel, int height, int width);
    virtual ~FeatureMap();
    bool  JudgeCenterMax(int index);
    float GetDataElement(int index_c, int index_h, int index_w);
    //   void StoreFeauremapData(std::string file_tmp);
};

}  // namespace perception
}  // namespace holo

#endif
