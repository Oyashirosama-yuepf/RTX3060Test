#ifndef _APP_HOLO_NMS_MODULE
#define _APP_HOLO_NMS_MODULE

#ifdef __cplusplus
extern "C" {
#endif

#include <TI/tivx.h>
#include <stdio.h>

#include "app_common.h"
#include "holo/dnn/tda4/common/app_c6x_kernel_holo_nms.h"
#include "tiadalg_interface.h"

typedef struct
{
    vx_graph graph;

    vx_node nms_node;

    vx_user_data_object nms_config;
    tivxHoloNmsParams   nmsParams;

    vx_user_data_object  nms_out_config;
    tivxHoloNmsOutParams nmsOutParams;
    vx_context           context;

    vx_tensor input_tensor;
    vx_tensor output_tensor;

} HoloNmsObj;

void print_nms_config(tivxHoloNmsParams nmsParams);

#define MAX_TENSOR_DIMS 3

vx_status app_create_holo_nms_graph(vx_context context, HoloNmsObj* nmsObj);
vx_status app_run_holo_nms_graph(HoloNmsObj* nmsObj, vx_uint8* img_file, void** kp_list);
void      app_delete_holo_nms_graph(HoloNmsObj* nmsObj);

void app_set_holo_nms_cfg_default(HoloNmsObj* nmsObj);
void app_holo_nms_parse_cfg_file(HoloNmsObj* nmsObj, char* token);

vx_status app_c6x_kernels_holo_nms_load(vx_context context);
vx_status app_c6x_kernels_holo_nms_unload(vx_context context);

#ifdef __cplusplus
}
#endif

#endif