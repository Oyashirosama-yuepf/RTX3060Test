/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vision_parkingslot.h
 * @brief This header file defines base vision parkingslot class.
 * @author lizhijian (lizhijian@holomatic.com)
 * @date "2019-09-17"
 */
#ifndef HOLO_PERCEPTION_LIB_VISION_PARKINGSLOT_H_
#define HOLO_PERCEPTION_LIB_VISION_PARKINGSLOT_H_

#include <holo/common/image.h>
#include <holo/perception/algorithm/tracking/bbox_kf_tracker.h>
// #include <holo/perception/app/test_tidl_inference.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/utility.h>
#include <holo/perception/utils/worker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

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
 * @brief define VisionParkingslot class
 */
class VisionParkingslot : public Worker
{
public:
    typedef std::function<void(std::vector<std::vector<float>>&)> ParkingslotCallback;

    VisionParkingslot(const std::string cfg_file, float hz = 10);
    bool InitConfig(const std::string cfg_file);
    bool InitDNN();

    void ReceiveAVMImage(const holo::Image& image);
    bool DoWork();
    void SetParkingslotCallback(ParkingslotCallback pks_callback);

    std::vector<std::vector<float>> GetResult()
    {
        PreProcessImage();
        DetectParkingslots();
        return det_result_;
    }

private:
    bool PreProcessImage();  // will call ResizeCropImage; MaskImage, update last_image_;
    bool DetectParkingslots();
    bool IPMParkingslots();
    bool GenParkingslot();

    // tools
    bool                     ResizeCropImage(holo::Image& image);  // in /out
    bool                     MaskImage(holo::Image& image);        // in /out
    std::vector<cv::Point2f> RestorePointsOnOriginImage(const std::vector<cv::Point>& pts_in);
    ///////////////////
    holo::Image last_image_;

    std::string                                         tidl_cfg_file_;
    uint8_t*                                            data;
    std::mutex                                          receiver_protector_;
    ParkingslotCallback                                 parkingslot_callback;
    std::vector<std::vector<float>>                     det_result_;
    std::shared_ptr<holo::dnn::DnnInterface>            dnn_interface_ptr_detection_psd_;

    float hz_;
};

/**
 * @}
 */

}  // namespace perception

}  // namespace holo

#endif
