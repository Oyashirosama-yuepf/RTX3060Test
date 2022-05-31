#ifndef _APP_CAPTURE_MODULE
#define _APP_CAPTURE_MODULE

#include "app_common.h"
#include "app_sensor_module.h"
#include "app_stream.h"

#define INSTANCE_ID         (1)

typedef struct {
    vx_node node;

    vx_user_data_object config;
    tivx_capture_params_t params;

    vx_user_data_object dcc_config;

    vx_object_array raw_image_arr[APP_MAX_BUFQ_DEPTH];

    vx_int32 graph_parameter_index;

    /* These params are needed only for writing intermediate output */
    vx_int32 en_out_capture_write;
    vx_node write_node;
    vx_array file_path;
    vx_array file_prefix;
    vx_user_data_object write_cmd;

    vx_char output_file_path[TIVX_FILEIO_FILE_PATH_LENGTH];

    vx_char objName[APP_MAX_FILE_PATH];

    tivx_raw_image black_raw_image;

    vx_uint8 enable_error_detection;
}CaptureObj;

vx_status app_init_capture(vx_context context, CaptureObj *captureObj, SensorObj *sensorObj, char *objName, int32_t bufq_depth);
void app_deinit_capture(CaptureObj *captureObj, vx_int32 bufq_depth);
void app_delete_capture(CaptureObj *captureObj);
vx_status app_create_graph_capture(vx_graph graph, CaptureObj *captureObj);
vx_status app_create_graph_capture_write_output(vx_graph graph, CaptureObj *captureObj);
vx_status app_send_cmd_capture_node(CaptureObj *captureObj, vx_uint32 start_frame, vx_uint32 num_frames, vx_uint32 num_skip);
vx_status app_send_error_frame(vx_context context, CaptureObj *captureObj, SensorObj *sensorObj);
#endif
