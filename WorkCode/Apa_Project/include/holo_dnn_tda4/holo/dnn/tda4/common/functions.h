/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file functions.h
 * @brief This header file defines common functions
 * @author xuhan(xuhan@holomatic.com)
 * @date "2021-12-27"
 */

#ifndef HOLO_COMMON_FUNCTIONS_H_
#define HOLO_COMMON_FUNCTIONS_H_

#include <holo/common/camera_fisheye.h>
#include <holo/common/timestamp.h>
#include <holo/perception/common/box2d.h>

#include <algorithm>
#include <functional>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "defines.h"
#include "utils.h"

namespace holo
{
namespace dnn
{
namespace tda4
{
class FeatureMap
{
public:
    float* data;
    int    channel_;
    int    height_;
    int    width_;
    int    data_len_;
    FeatureMap();
    FeatureMap(float* data_tmp, int channel, int height, int width);
    virtual ~FeatureMap();
    bool  JudgeCenterMax(int index);
    bool  JudgeCenterMax(int index_c, int index_h, int index_w, int index);
    float GetDataElement(int index_c, int index_h, int index_w);
    //   void StoreFeauremapData(std::string file_tmp);
};

////////det///////
struct DecodeConfig
{
    int height;
    int width;
    int crop_x_start, crop_x_end;
    int crop_y_start, crop_y_end;
    int dl_height;
    int dl_width;

    float score;
    bool  nms_flag;

    int       decode_type;
    int       keypoints_num;
    int       attr_num;
    size_t    class_num;
    size_t    bins;
    float32_t bbox_score;
    float32_t nms_score;
    DecodeConfig(int h, int w, int x_start, int y_start, int x_end, int y_end, int dl_h, int dl_w)
    {
        height       = h;
        width        = w;
        crop_x_start = x_start;
        crop_y_start = y_start;
        crop_x_end   = x_end;
        crop_y_end   = y_end;
        dl_height    = dl_h;
        dl_width     = dl_w;
    }
};

// psd entra struct
struct EntraMidPoints
{
    cv::Point2f              entra_mid_points;
    std::vector<cv::Point2f> corner_points;
    float32_t   score;
};

cv::Mat FreespaceMat(FeatureMap freespace_fm);

cv::Mat FreespaceMat(FeatureMapRawData freespace_fm);

void RefineKeypoints(std::vector<std::vector<float32_t>>&  det_result,
                     std::vector<std::vector<cv::Point2f>> hm_keypoints);

void RefineBothKeypoints(
    std::list<BoxObject>& det_result,
    std::vector<std::vector<cv::Point2f>> hm_keypoints,
    std::vector<std::vector<float32_t>> keypoints_confidences);

void RefineKeypoints(std::list<BoxObject>& det_result, std::vector<std::vector<cv::Point2f>> hm_keypoints,
                     std::vector<std::vector<float32_t>> keypoints_confidences);

bool det_centernet_decode(const std::vector<FeatureMap>& featuremap_vec, const DecodeConfig decode_config,
                          std::vector<std::vector<float>>& det_result);

bool det_centernet_fast_decode(const std::vector<FeatureMapRawData>& featuremap_vec, const DecodeConfig decode_config,
                               std::list<BoxObject>& det_result);

bool det_yolox_decode(const std::vector<FeatureMapRawData>& featuremap_vec, const DecodeConfig decode_config,
                      std::list<std::shared_ptr<BoxObject>>&        det_result,
                      std::shared_ptr<holo::CameraFisheyeT<float>>& camera_model);

void DetImagebox(const std::vector<FeatureMap>& featuremap, const DecodeConfig& decode_config,
                 std::vector<BoxObject>& det_imagebox);

bool psd_centernet_decode(std::vector<FeatureMap>& featuremap_vec, std::vector<std::vector<float>>& det_result,
                          DecodeConfig decode_config);
void Match_Entra_Points(std::vector<std::vector<float32_t>>&  det_result, std::vector<EntraMidPoints>& entra_hm_keypoints);
void Refine_Entry_Points(std::vector<std::vector<float32_t>>&  det_result);
// bool PsdSort(std::vector<float> p1, std::vector<float> p2);
void Refine_PSD_Vertex(std::vector<std::vector<float32_t>>&  det_result,
                     std::vector<std::vector<cv::Point2f>> hm_keypoints);
bool psd_srv_centernet_decode(std::vector<FeatureMap>& featuremap_vec, std::vector<std::vector<float>>& det_result,
                          DecodeConfig decode_config);
void NonMaximumSuppressionTDA4VX_bk(const int input_height, const int input_width, const int input_patch_size,
                                    const int input_nms_radius, const float input_confidence_threshold,
                                    float* input_max_score_along_channel, int16_t* input_max_indice_along_channel,
                                    std::vector<FeatureTDA4VX_bk>& output_features);
bool sortFun(const FeatureTDA4VX_bk& p1, const FeatureTDA4VX_bk& p2);

inline float fast_exp(float y)
{
    float d;
    *(reinterpret_cast<short*>(&d) + 0) = 0;
    *(reinterpret_cast<short*>(&d) + 1) = static_cast<short>(184 * y + (16256 - 7));
    return d;
}

}  // namespace tda4
}  // namespace dnn
}  // namespace holo

#endif  // !HOLO_COMMON_FUNCTIONS_H_
