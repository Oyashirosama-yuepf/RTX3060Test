
#ifndef _UPSAMPLE_TIDL_
#define _UPSAMPLE_TIDL_
#define restrict
#include <TI/j7.h>
#include <TI/tivx.h>
#include <assert.h>
#include <holo/log/hololog.h>
#include <holo/utils/holo_root.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tivx_utils_file_rd_wr.h>

#include "app_c6x_kernel_holo_upsample.h"
#include "app_common.h"
#include "app_holo_upsample_module.h"
#include "tiadalg_interface.h"

namespace holo
{
namespace perception
{

class UpSampleTidl
{
public:
    std::string         tidl_config_file_;
    tivxHoloUpsampleObj upsampleObj_;

public:
    UpSampleTidl(std::string cfg_file);

    ~UpSampleTidl();
    vx_status app_init();
    vx_status app_deinit();
    vx_status app_create_graph();
    vx_status app_run_graph(vx_uint8* img_file, vx_int32* kp_list, void** ans_ptr);
    void      app_delete_graph();
};

}  // namespace perception
}  // namespace holo

#endif