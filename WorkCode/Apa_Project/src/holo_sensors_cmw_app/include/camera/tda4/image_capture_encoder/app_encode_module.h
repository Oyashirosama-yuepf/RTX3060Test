#ifndef _APP_ENCODE_MODULE
#define _APP_ENCODE_MODULE

#include "app_common.h"
#include "app_stream.h"
#include <utils/perf_stats/include/app_perf_stats.h>


#define FILENAME_SIZE_MAX 1024

typedef struct {
  vx_node  node;
  vx_kernel kernel;

  char output_file[NUM_ENCODE_CHANNEL];
  vx_char output_file_path[TIVX_FILEIO_FILE_PATH_LENGTH];
  FILE *out_fp;
  vx_uint8 eof;

  tivx_video_encoder_params_t encode_params;
  vx_user_data_object configuration_obj;
  vx_user_data_object bitstream_obj;
  vx_user_data_object encoded_image;

  vx_int32 graph_parameter_index;
  vx_int32 inWidth;
  vx_int32 inHeight;

} EncodeObj;

vx_status app_init_encode(vx_context context, EncodeObj *encodeObj, char *objName);
void app_deinit_encode(EncodeObj *encodeObj);
void app_delete_encode(EncodeObj *encodeObj);
vx_status app_create_graph_encode(vx_graph graph, EncodeObj *encodeObj, vx_image output_image, vx_uint8 index);
//vx_status app_create_graph_encode(vx_graph graph, EncodeObj *encodeObj, vx_image input_image, vx_uint8 index);

vx_status writeEncodeOutput(EncodeObj *encodeObj);
#endif
