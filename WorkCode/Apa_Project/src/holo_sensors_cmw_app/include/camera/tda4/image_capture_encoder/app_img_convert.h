#ifndef _APP_IMG_CONVERT_
#define _APP_IMG_CONVERT_

#include "app_common.h"
#include "app_sensor_module.h"
#include "app_stream.h"

typedef struct {
  vx_node  node;

  vx_object_array output_arr[NUM_ENCODE_CHANNEL];

  vx_int32 graph_parameter_index;

  vx_int32 input_width;
  vx_int32 input_height;
  vx_int32 num_inputs;
} ImgConvertObj;


vx_status app_init_img_convert(vx_context context, ImgConvertObj *imgConvertObj, SensorObj *sensorObj, vx_int32 bufq_depth);
void app_deinit_img_convert(ImgConvertObj *imgConvertObj, vx_int32 bufq_depth);
void app_delete_img_convert(ImgConvertObj *imgCOnvertObj);
vx_status app_create_graph_img_convert(vx_graph graph, ImgConvertObj *imgConvertObj, vx_object_array raw_image_arr,char *objName);

#endif
