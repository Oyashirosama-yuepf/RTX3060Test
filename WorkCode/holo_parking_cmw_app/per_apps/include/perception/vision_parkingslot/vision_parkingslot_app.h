/*!
 *  \brief
 *  \author lizhijian (lizhijian@holomatic.com)
 *  \date 2020-12-07
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_CMW_APPS_VISION_PARKINGSLOT_APP_H_
#define _HOLO_CMW_APPS_VISION_PARKINGSLOT_APP_H_
#include <holo/sensors/camera/image_ipc.h>
#include <holo/utils/yaml.h>
#include <cmw_wrapper/cmw_bus.h>

#include <exception>
#include <map>
#include <unordered_map>
#include <vector>

using BusType = cmw_wrapper::CmwBus;

namespace holo {
namespace perception {
    class VisionParkingslot;
}
}

namespace holo_cmw
{
class VisionParkingslotApp
{
public:
    VisionParkingslotApp(int argc, char** argv, const std::string config_file);
    void Run();
    void Terminate();

    void AVMImageSubscriberCallback(holo::uint32_t msg);
    void CreateSubscribersAndPunlishers();

private:
    void InitConfig();

private:
    holo::float32_t hz_;
    std::string     config_file_name_;
    std::string     detection_params_file_;

    std::string topic_avm_sub_subscriber_;
    std::string topic_vision_parkingslot_publisher_;

    std::shared_ptr<BusType>         bus_ptr_;
    BusType::WriterType<std::string> fs_writer_;

    std::shared_ptr<holo::perception::VisionParkingslot> vision_parkingslot_;
    std::shared_ptr<holo::sensors::camera::ImageIpc>     avm_img_ipc_;
};
}  // namespace holo_cmw

#endif
