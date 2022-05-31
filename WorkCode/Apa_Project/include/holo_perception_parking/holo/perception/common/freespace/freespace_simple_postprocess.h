/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file freespace_simple_postprocess.h
 * @brief This header file defines freespace simple post process.
 * @author zhouchengwei (zhouchengwei@holomatic.com)
 * @date "2022-03-11"
 */

#ifndef _HOLO_PERCEPTION_COMMON_FREESPACE_SIMPLE_POSTPROCESS_H_
#define _HOLO_PERCEPTION_COMMON_FREESPACE_SIMPLE_POSTPROCESS_H_

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
class FreespaceSimplePostProcess
{
public:
    using IntrinsicBaseType            = holo::common::details::CameraIntrinsicBaseT<float32_t>;
    using IntrinsicBaseTypePtr         = std::shared_ptr<IntrinsicBaseType>;
    using FisheyeIntrinsicType         = holo::common::details::FisheyeIntrinsicT<float32_t>;
    using PinholeIntrinsicType         = holo::common::details::PinholeIntrinsicT<float32_t>;
    using OmnidirectionalIntrinsicType = holo::common::details::OmnidirectionalIntrinsicT<float32_t>;

    typedef typename holo::common::AutoFreespace<holo::geometry::Point3f> FreespaceType;
    typedef std::function<void(FreespaceType&)>                           FreespaceCallback;

    FreespaceSimplePostProcess(Parameters::Ptr parameters);
    void                     InitCameraMask();
    std::vector<cv::Point2f> RestorePointsOnOriginImage(const std::string               camera_name,
                                                        const std::vector<cv::Point2f>& pts_in);
    void                     SetFreespaceCallback(FreespaceCallback fs_callback);
    bool                     CreateDebugResult(const std::string camera_name, std::vector<cv::Point2f> boundary_points);
    bool                     GetBoundary(std::string process_name, cv::Mat process_mat);
    bool                     inFrustum(const std::string camera_name, Point3f const& x) const;
    bool                     IPMFreespaces();
    bool                     GenFreespace();
    uint32_t                 Run(const Srv_Result::Ptr srv_result);

private:
    uint32_t                                          fs_state_;
    int                                               down_sampling_scale_;
    Parameters::Ptr                                   parameters_;
    Srv_Result::Ptr                                   srv_result_;
    std::unordered_map<std::string, std::vector<int>> camera_masks_;
    std::vector<std::vector<cv::Point2f>>             boundary_results_;
    std::vector<cv::Mat>                              contour_on_images_;
    float32_t                                         current_ground_pitch_;

    FreespaceType     observablespace_;
    FreespaceCallback freespace_callback_;
};
}  // namespace perception
}  // namespace holo
#endif
