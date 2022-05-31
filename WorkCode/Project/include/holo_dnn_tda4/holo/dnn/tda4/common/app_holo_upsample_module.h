#ifndef _APP_HOLO_UPSAMPLE_MODULE
#define _APP_HOLO_UPSAMPLE_MODULE
#ifdef __cplusplus
extern "C" {
#endif
#include "app_c6x_kernel_holo_upsample.h"
#include "app_common.h"

typedef struct
{
    vx_graph graph;
    vx_node  upsample_node;
    vx_array upsample_config;

    tivxHoloUpsampleParams upsampleParams;
    vx_context             context;
    vx_tensor              input_tensor_upsample;
    vx_tensor              input_keypoints_upsample;
    vx_tensor              output_tensor_unpsample;
} tivxHoloUpsampleObj;

void print_upsample_config(tivxHoloUpsampleParams nmsParams);

#define MAX_TENSOR_DIMS 3

vx_status app_create_holo_upsample_graph(vx_context context, tivxHoloUpsampleObj* usObj);
vx_status app_run_holo_upsample_graph(tivxHoloUpsampleObj* usObj, vx_uint8* img_data_upsample, vx_int32* keypoint_data,
                                      void** ans_data_upsample);
;
void app_delete_holo_upsample_graph(tivxHoloUpsampleObj* usObj);

void app_set_holo_upsample_cfg_default(tivxHoloUpsampleObj* usObj);
void app_holo_upsample_parse_cfg_file(tivxHoloUpsampleObj* usObj, char* token);

vx_status app_c6x_kernels_holo_upsample_load(vx_context context);
vx_status app_c6x_kernels_holo_upsample_unload(vx_context context);

void Read7x7_s8(char* file, vx_int8* f);
void printf_7x7_s8(vx_int8* f, char* message);
void Read1x1_s16(char* file, vx_int16* f);
void printf_1x1_s16(vx_int16* f, char* message);

void copy_7x7_to_all_plane_s8(vx_int8* f, int plane);
void copy_1x1_to_all_plane_s16(vx_int16* f, int plane);

void printf_128x7x7_s8(vx_int8* f, char* message, int plane);
void printf_128x1x1_s16(vx_int16* f, char* message, int plane);

#ifdef __cplusplus
}
#endif
#endif