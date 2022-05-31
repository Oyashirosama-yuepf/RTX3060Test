
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vision_freespace_avm.h
 * @brief This header file defines base vision freespace avm class.
 * @author lizhijian  (lizhijian@holomatic.com), zhouchengwei (zhouchengwei@holomatic.com)
 * @date "2021-04-23"
 */
#ifndef HOLO_PERCEPTION_LIB_VISION_FREESPACE_AVM_H_
#define HOLO_PERCEPTION_LIB_VISION_FREESPACE_AVM_H_

#include <holo/common/image.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/utility.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo/perception/utils/worker.h>
#include <holo/common/freespace.h>
#include <holo/perception/common/boundary_point2d.h>
//#include <holo/perception/algorithm/tracking/bbox_kf_tracker.h>

#include <holo/perception/app/vision_freespace_avm_tidl_inference.h>
#include <cmath>
#include <mutex>
#include <queue>

#include <sys/time.h>

#include "holo/perception/common/camera_avm.h"

namespace holo
{
namespace perception
{
/**
 * @addtogroup detection
 *
 * @{
 */

/**
 * @brief define camera config class
 */

/**
 * @brief define VisionFreespaceAVM class
 */

// class VisionFreespaceAVM : public Worker
class VisionFreespaceAVM
{
public:
    typedef typename holo::common::AutoFreespace<holo::geometry::Point3f> FreespaceType;
    // typedef typename std::vector<uint8_t> EncodedImage;
    typedef std::function<void(FreespaceType&)> FreespaceCallback;  // point to function: void(FreespaceType &)

    void SetFreespaceCallback(FreespaceCallback fs_callback);

    VisionFreespaceAVM(const std::string cfg_file, float hz = 10, int debug_2d_image = 0,
                                size_t debug_image_skip_frames = 0, std::string debug_image_path = "");
    bool InitConfig(const std::string cfg_file);
    bool LoadCamConfigs();
    bool InitDNN();

    void ReceiveAVMImage(const holo::Image& image, const std::string& camera_name);
    bool DoWork();

    std::unordered_map<std::string, std::shared_ptr<CamAVMConfig>> camera_configs_;

    // unit test interface
    bool LoadImage(cv::Mat input_image)
    {
        int bit_num = input_image.rows * input_image.cols * input_image.channels();
        last_image_.SetData(input_image.data, bit_num, input_image.rows, input_image.cols, holo::Image::Encoding::RGB);
        image_flag_ = true;
        last_camera_name_ = "AVM_CAMERA";
        return true;
    }
    std::vector<std::vector<std::vector<holo::float32_t>>> GetResult()
    {
        PreProcessImage();
        DetectFreespaceAVM();
        return det_result_;
    }

private:
    bool PreProcessImage();     // will call ResizeCropImage; MaskImage, update last_image_;
    bool ReadImageFromeFile();  // read image from path.
    bool DetectFreespaceAVM();
    bool IMPFreespaceAVM();
    bool GenFreespaceAVM();


    // tools
    bool                     ResizeCropImage(holo::Image& image);
    bool                     MaskImage(holo::Image& image);
    std::pair<float32_t, float32_t>      ConvertToBodyCoord(float32_t x, float32_t y);
    std::vector<cv::Point2f> RestorePointsOnOriginImage(const std::vector<cv::Point2f>& pts_in);
    ///////////////
    int32_t                                               split_num_;
    holo::Image                                           last_image_;
    holo::Image                                           processing_image_;
    std::string                                           last_camera_name_;
    std::string                                           tidl_cfg_file_;
    uint8_t*                                              data_;
    std::shared_ptr<holo::perception::TidlInferenceDetFs> tidl_center_net_;
    std::mutex                                            receiver_protector_;

    FreespaceCallback freespace_callback_;

    std::vector<std::string>                               camera_names_;
    std::vector<std::string>                               camera_config_files_;
    std::vector<std::vector<std::vector<holo::float32_t>>> det_result_;
    // std::unordered_map<std::string, std::shared_ptr<CamAVMConfig>> camera_configs_;

    float hz_;
    float confidence_threshold_;

    // debug
    std::vector<std::string> rgb_paths_;
    std::vector<std::string> yuv_paths_;
    std::vector<std::string> rgb_names_;
    std::vector<std::string> yuv_names_;
    int debug_2d_image_;
    size_t debug_image_skip_frames_;
    std::string debug_image_path_;

    bool image_flag_;
};
}  // namespace perception

}  // namespace holo

#endif


