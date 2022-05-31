/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file defines.h
 * @brief This header file defines common data types
 */

#include <holo/dnn/interface.h>

#include <opencv2/opencv.hpp>
#include <vector>
namespace holo
{
namespace dnn
{
namespace tda4
{
using BBox         = holo::perception::Box2Df;
using BoxObject    = holo::perception::BoxObjectf;
using ClassifyInfo = holo::perception::ClassifyInfo;
class FeaturePoint
{
public:
    int   x;
    int   y;
    float score;
    float descriptor_data_[128];
};

struct SrvDetResult
{
    std::vector<std::list<holo::perception::BoxObjectf>> detection_obs_results;
    std::vector<cv::Mat>                                 freespace_results;

    bool det_decode_flag;
    bool freespace_decode_flag;
};

}  // namespace tda4
}  // namespace dnn
}  // namespace holo
