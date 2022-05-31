/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vision_parkingslot.h
 * @brief This header file defines base vision srv parkingslot class.
 * @author zhangyang (zhangyang@holomatic.com)
 * @date "2022-04-18"
 */

#ifndef HOLO_PERCEPTION_LIB_VISION_PARKINGSLOT_H_
#define HOLO_PERCEPTION_LIB_VISION_PARKINGSLOT_H_

#include <holo/common/image.h>
#include <holo/common/parking_slot.h>
#include <holo/perception/algorithm/tracking/bbox_kf_tracker.h>
// #include <holo/perception/app/test_tidl_inference.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/utility.h>
#include <holo/perception/utils/worker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo/perception/common/parkingslot/parkingslot_postprocess.h>
#include <holo/perception/common/params_loader.h>

#include <cmath>
#include <mutex>
#include <queue>

namespace holo
{

namespace dnn{
    class DnnInterface;
}

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
 * @brief define VisionSrvParkingslot class
 */
class VisionSrvParkingslot : public Worker
{
public:
    typedef typename holo::common::ParkingSlotFrameT<float64_t>   ParkingslotType;
    typedef std::function<void(ParkingslotType&)>                 ParkingslotCallback;
    typedef typename holo::perception::ParkingSlotPostProcess     PsdPostProcess;

    VisionSrvParkingslot(const std::string cfg_file, float hz = 10);
    bool InitConfig(const std::string cfg_file);

    void ReceiveImageFromCamera(const std::vector<holo::Image>&            msg,
                                             const std::unordered_map<std::string, int> camera_order);
    void BGR2YUV_nv12(cv::Mat& src, cv::Mat& nv12_data);
    bool DoWork();
    void SetParkingslotCallback(ParkingslotCallback pks_callback);

private:
    bool PreProcessImage();  // will call ResizeCropImage; MaskImage, update last_image_;
    bool DetectParkingslots();

    float hz_;
    std::vector<holo::Image>                 msg_;
    std::unordered_map<std::string, int>     camera_order_;
    bool                                     flag_received_image_;
    std::mutex                               receiver_protector_;
    std::string                              tidl_cfg_file_;
    uint8_t*                                 data;
    ParkingslotCallback                      parkingslot_callback;
    std::vector<std::vector<float>>          det_result_;
    std::shared_ptr<holo::dnn::DnnInterface> dnn_interface_ptr_detection_psd_;
    std::shared_ptr<PsdPostProcess>          parkingslot_postprocess_; 
    std::vector<std::string>                 receive_camera_names_;
    Srv_Result::Ptr                          srv_result_;
    holo::common::Timestamp                  time_stamp_last_;
    std::string                              inference_yaml;
    std::unordered_map<std::string, cv::Mat> cameras_debug_image_container_;
    std::vector<std::string>                 srv_camera_names_;
    std::vector<size_t>                      srv_camera_index_;

};

/**
 * @}
 */

}  // namespace perception

}  // namespace holo

#endif
