/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vision_freespace_dnn.h
 * @brief This header file defines base dnn version vision freespace class.
 * @author zhouchengwei (zhouchengwei@holomatic.com)
 * @date "2022-01-11"
 */

#ifndef HOLO_PERCEPTION_LIB_VISION_FREESPACE_DNN_H_
#define HOLO_PERCEPTION_LIB_VISION_FREESPACE_DNN_H_

#include <assert.h>
#include <holo/common/freespace.h>
#include <holo/common/image.h>
#include <holo/dnn/interface.h>
#include <holo/io/common/intrinsic.h>
#include <holo/perception/common/boundary_point2d.h>
#include <holo/perception/common/freespace/freespace_postprocess.h>
#include <holo/perception/common/params_loader.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/utility.h>
#include <holo/perception/utils/worker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <sys/time.h>

#include <cmath>
#include <mutex>
#include <queue>


namespace holo
{
namespace perception
{
class VisionFreespaceDnn
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
    VisionFreespaceDnn(const std::string& algorithm_config_yaml);

    void ReceiveImageFromCamera(const std::vector<holo::Image>&            msg,
                                const std::unordered_map<std::string, int> camera_order);

    bool CheckImageReady();

    bool UndistortImage(const std::string camera_name, Eigen::Matrix3f& new_K, bool only_estimate_new_K);

    bool DoWork();

    Parameters::Ptr parameters_;

private:
    Srv_Result::Ptr srv_result_;
    std::mutex                                       receiver_protector_;
    std::shared_ptr<holo::dnn::DnnInterface>         dnn_interface_ptr_freespace_;
    std::shared_ptr<holo::perception::FreespacePostProcess> freespace_postprocess_;
    std::unordered_map<std::string, bool>            cameras_updated_;

    FreespaceType     observablespace_;
    FreespaceCallback freespace_callback_;
};
}  // namespace perception
}  // namespace holo

#endif
