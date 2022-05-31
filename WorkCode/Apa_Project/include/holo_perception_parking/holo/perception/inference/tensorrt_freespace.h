/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vision_freespace.h
 * @brief This header file defines base vision freespace class.
 * @author lizhijian (lizhijian@holomatic.com)
 * @date "2019-09-23"
 */
#ifndef HOLO_PERCEPTION_DETECTION_TENSORRT_FREESPACE_H_
#define HOLO_PERCEPTION_DETECTION_TENSORRT_FREESPACE_H_

#include <algorithm>
#include <iterator>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

//#include "holo/perception/inference/image_segmentor.h"
#include <glog/logging.h>

#include "freespace_fpn.pb.h"
#include "holo/core/exception.h"
#include "holo/core/types.h"
#include "holo/perception/utils/dg_port.h"

//#define SAVE_INFERENCE_OUTPUT_INTO_TXT  1
//#define SAVE_CONTOUR_IMAGES             1
//#define ARGMAX_GPU                      1

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
 * @brief define freespace fpn class
 */
class FreespaceFPN
{
public:
    typedef std::vector<std::vector<cv::Point>> CV_ContoursT;
    typedef std::vector<cv::Vec4i>              CV_ContoursHierarchyT;

    using Ptr      = std::shared_ptr<FreespaceFPN>;
    using ConstPtr = std::shared_ptr<const FreespaceFPN>;

    /**
     * @brief the constructor
     * @param config_path the path to the configure file.
     * @param is_gen_debug_image specify if to generate debug image.
     */
    explicit FreespaceFPN(const std::string& config_path, bool is_gen_debug_image = false);
    ~FreespaceFPN();

    /**
     * @brief segment images, wo produce contours and the hierarchy of contours.
     * @param [in] images images to be segmentated.
     * @param [out] freespace contours that from image segmentation(contours are in image coordinates).
     * @param [out] hierarchy of the freespace contours.
     * @return bool
     */
    bool DoSegmentation(const std::vector<cv::Mat>& images, const std::vector<cv::Mat*>& mask_ptrs,
                        std::vector<CV_ContoursT>& contours, std::vector<CV_ContoursHierarchyT>& hierarchy);

    bool is_gen_debug_image_;
    // cv::Mat debug_img_;
    std::vector<cv::Mat> debug_imgs_;

private:
    /**
     * @brief init object with specified configure file.
     * @param config_file_path path to the config file.
     */
    void InitConfig(const std::string& config_file_path);

    /**
     * @brief resize image (which should be in RGB format) and copy data to inputs_.
     * @param images images to be processed.
     */
    void LoadImages(const std::vector<cv::Mat>& images);

    /**
     * @brief do the actuall inference.
     */
    void Inference(void);

    /**
     * @brief post process.
     */
    void PostProcess(const std::vector<cv::Mat*>& mask_ptrs, std::vector<CV_ContoursT>& contours,
                     std::vector<CV_ContoursHierarchyT>& hierarchy);

    /**
     * @brief apply mask on the debug image.
     */
    void ApplyMaskOnDebugImg(size_t index, cv::Mat mask);

private:
    FreespaceFPNConfig     config_;
    size_t                 batch_size_  = 0;
    size_t                 num_classes_ = 0;
    float32_t              scale_       = 1;
    std::vector<float32_t> mean_        = {0, 0, 0};
    std::vector<float32_t> dev_         = {1, 1, 1};
    // TRTInference::Ptr                               p_trt_inference_;
    void*                                           p_trt_inference_;
    std::vector<std::pair<std::string, float32_t*>> inputs_;
    std::vector<std::pair<std::string, float32_t*>> outputs_;
    size_t                                          cnn_input_width_;
    size_t                                          cnn_input_height_;
    size_t                                          cnn_input_channel_;
    size_t                                          cnn_output_width_;
    size_t                                          cnn_output_height_;
    size_t                                          cnn_output_channel_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  /// HOLO_PERCEPTION_DETECTION_FreespaceFPN_H_
