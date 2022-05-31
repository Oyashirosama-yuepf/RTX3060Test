#ifndef _APP_IMG_MOSAIC_MODULE
#define _APP_IMG_MOSAIC_MODULE

#include "app_common.h"
#include "app_stream.h"

typedef struct {
  vx_node  node;
  vx_kernel kernel;

  vx_user_data_object config;
  tivxImgMosaicParams params;

  vx_object_array input_arr[TIVX_IMG_MOSAIC_MAX_INPUTS];

  vx_image output_image[APP_MAX_BUFQ_DEPTH];

  vx_int32 graph_parameter_index;

  vx_int32 out_width;
  vx_int32 out_height;
  vx_int32 num_inputs;

  char output_file[NUM_ENCODE_CHANNEL];
  vx_char output_file_path[TIVX_FILEIO_FILE_PATH_LENGTH];
  FILE *out_fp;
  vx_uint8 eof;
} ImgMosaicObj;

vx_status app_init_img_mosaic(vx_context context, ImgMosaicObj *imgMosaicObj, char *objName, vx_int32 bufq_depth);
void app_deinit_img_mosaic(ImgMosaicObj *imgMosaicObj, vx_int32 bufq_depth);
void app_delete_img_mosaic(ImgMosaicObj *imgMosaicObj);
vx_status app_create_graph_img_mosaic(vx_graph graph, ImgMosaicObj *imgMosaicObj);

vx_status writeMosaicOutput(char* file_name, vx_image out_img);
#endif
