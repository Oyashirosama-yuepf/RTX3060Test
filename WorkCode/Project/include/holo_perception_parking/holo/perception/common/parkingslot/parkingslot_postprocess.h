/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parkingslot_postprocess.h
 * @brief This header file defines srv parkingslot post process.
 * @author zhangyang (zhangyang@holomatic.com)
 * @date "2022-04-18"
 */

#ifndef _HOLO_PERCEPTION_COMMON_FREESPACE_SIMPLE_POSTPROCESS_H_
#define _HOLO_PERCEPTION_COMMON_FREESPACE_SIMPLE_POSTPROCESS_H_

#include <assert.h>
#include <holo/common/parking_slot.h>   
#include <holo/common/image.h>
#include <holo/perception/algorithm/ipm.h>
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
class ParkingSlotPostProcess
{
public:
    typedef typename holo::common::ParkingSlotFrameT<float64_t>   ParkingslotType;
    typedef std::function<void(ParkingslotType&)>                 ParkingslotCallback;

    ParkingSlotPostProcess(std::string config_file);
    void Run(const Srv_Result::Ptr  srv_result);
    bool IPMParkingslot();
    void SetParkingslotPostCallback(ParkingslotCallback psd);
    bool DumpDebugImage(ParkingslotType tmp_parkingslot_frame_, std::string camera_name, 
                                    std::vector<std::vector<float>> psd_result);
    void save_ipm_vis();
private:
    Srv_Result::Ptr                               srv_result_;
    std::shared_ptr<IpmApp>                       ipm_ptr_;
    std::vector<std::string>                      camera_names;
    std::vector<std::string>                      camera_config_files;
    // holo::common::ParkingSlot                     st_parkingslot_;
    ParkingslotType                               c_parkingslot_frame_;
    std::unordered_map<std::string, cv::Mat>      debug_imgs;
    int16_t                                       debug_image_num ;
    ParkingslotCallback                           parkingslot_callback_;

    std::shared_ptr<holo::perception::PltIpmPoints_bk> test_plt_ipm_;
};
} // namespace perception
}// namespace holo
#endif