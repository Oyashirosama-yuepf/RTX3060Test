/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file freespace_postprocess.h
 * @brief This header file defines freespace common post process.
 * @author zhouchengwei (zhouchengwei@holomatic.com)
 * @date "2022-02-18"
 */

#ifndef _HOLO_PERCEPTION_COMMON_FREESPACE_POSTPROCESS_H_
#define _HOLO_PERCEPTION_COMMON_FREESPACE_POSTPROCESS_H_

#include <assert.h>
#include <holo/common/freespace.h>
#include <holo/common/image.h>
#include <holo/perception/common/params_loader.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/utility.h>
#include <sys/time.h>

#include <cmath>
#include <mutex>
#include <queue>

#include "holo/perception/common/camera_config_ex.h"

namespace holo
{
namespace perception
{
class FreespacePostProcess
{
public:
    using IntrinsicBaseType            = holo::common::details::CameraIntrinsicBaseT<float32_t>;
    using IntrinsicBaseTypePtr         = std::shared_ptr<IntrinsicBaseType>;
    using FisheyeIntrinsicType         = holo::common::details::FisheyeIntrinsicT<float32_t>;
    using PinholeIntrinsicType         = holo::common::details::PinholeIntrinsicT<float32_t>;
    using OmnidirectionalIntrinsicType = holo::common::details::OmnidirectionalIntrinsicT<float32_t>;

    typedef std::vector<std::vector<cv::Point>> CV_ContoursT;
    typedef std::vector<cv::Vec4i>              CV_ContoursHierarchyT;

    typedef typename holo::common::AutoFreespace<holo::geometry::Point3f> FreespaceType;
    typedef std::function<void(FreespaceType&)>                           FreespaceCallback;

public:
    FreespacePostProcess(Parameters::Ptr parameters) : parameters_(parameters)
    {
    }

    void SetFreespaceCallback(FreespaceCallback fs_callback);

    bool IsFreespace(size_t batch_index, size_t contour_index);

    cv::Point2f Clamp2DVectorByNorm(const cv::Point2f& pt, float32_t lo, float32_t hi);

    float32_t CalculateGroundPitch();

    std::vector<cv::Point2f> RestorePointsOnOriginImage(const std::string             camera_name,
                                                        const std::vector<cv::Point>& pts_in);

    bool GetContours(const std::string camera_name, const cv::Mat segm, const cv::Mat mask,
                     std::vector<CV_ContoursT>&          contours,  // support multi cameras.
                     std::vector<CV_ContoursHierarchyT>& hierarchy);

    bool GenObservablespace();

    bool IPMFreespaces();

    bool TestPointInRadianRange(const cv::Point2f& point_prev, const cv::Point2f& point_current,
                                const cv::Point2f& origin, float32_t start, float32_t end, cv::Point2f& revised_point);

    bool PeekFreespace(size_t batch_index, std::vector<std::vector<cv::Point2f>>& cv_contours,
                       std::vector<bool>& freespace_indicator);

    bool GenFreespace();

    bool CreateDebugResult(const std::string camera_name, cv::Mat binary_segm, cv::Mat mask);

    bool Run(const Srv_Result::Ptr srv_result);

    Parameters::Ptr parameters_;

private:
    Srv_Result::Ptr                       srv_result_;
    std::vector<CV_ContoursT>             contours_results_;  // support multi cameras.
    std::vector<CV_ContoursHierarchyT>    contours_hierarchy_results_;
    std::vector<std::vector<cv::Mat>>     contours_on_images_;
    holo::Pathd                           planning_path_;
    std::unordered_map<std::string, bool> cameras_updated_;
    float32_t                             current_ground_pitch_;

    FreespaceType     observablespace_;
    FreespaceCallback freespace_callback_;
};
}  // namespace perception
}  // namespace holo
#endif
