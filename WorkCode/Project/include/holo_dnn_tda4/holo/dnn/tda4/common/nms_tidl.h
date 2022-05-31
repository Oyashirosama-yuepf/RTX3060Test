
#ifndef _NMS_TIDL_
#define _NMS_TIDL_
#define restrict
#include <TI/j7.h>
#include <TI/tivx.h>
#include <assert.h>
#include <holo/utils/holo_root.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tivx_utils_file_rd_wr.h>

#include "app_common.h"
#include "holo/dnn/tda4/common/app_c6x_kernel_holo_nms.h"
#include "holo/dnn/tda4/common/app_holo_nms_module.h"
#include "tiadalg_interface.h"

namespace holo
{
namespace perception
{

class NmsTidl
{
public:
    std::string tidl_config_file_;
    HoloNmsObj  nmsObj_;

public:
    NmsTidl(std::string cfg_file);

    ~NmsTidl();
    vx_status app_init();
    vx_status app_deinit();
    vx_status app_create_graph();
    vx_status app_run_graph(vx_uint8* img_file, void** kp_list);
    void      app_delete_graph();
};

}  // namespace perception
}  // namespace holo

#endif