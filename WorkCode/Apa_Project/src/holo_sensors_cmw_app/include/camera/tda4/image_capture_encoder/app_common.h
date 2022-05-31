#ifndef _APP_CAM_COMMON
#define _APP_CAM_COMMON

#include <TI/tivx.h>
#include <TI/tivx_task.h>
#include <TI/tivx_target_kernel.h>
#include "tivx_kernels_host_utils.h"

#include <TI/j7.h>
#include <TI/j7_tidl.h>
#include <tivx_utils_file_rd_wr.h>
#include <tivx_utils_graph_perf.h>
#include <utils/iss/include/app_iss.h>
#include <TI/tivx_img_proc.h>
#include <TI/tivx_fileio.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <float.h>
#include <math.h>

#define APP_DEBUG

#define APP_USE_FILEIO

#define APP_MAX_FILE_PATH           (256u)
#define APP_ASSERT(x)               assert((x))
#define APP_ASSERT_VALID_REF(ref)   (APP_ASSERT(vxGetStatus((vx_reference)(ref))==VX_SUCCESS));

#define APP_MAX_NUM_CLASSES         (3u)
#define APP_MAX_TENSORS             (4u)
#define APP_MAX_TENSOR_DIMS         (4u)
#define APP_TIDL_MAX_PARAMS         (16u)

#define ABS_FLT(a) ((a) > 0)?(a):(-(a))

#define MAX_IMG_WIDTH  (2048)
#define MAX_IMG_HEIGHT (2048)
//#define DISPLAY_WIDTH  (1920)
//#define DISPLAY_HEIGHT (1080)
#define DISPLAY_WIDTH  (1280)
#define DISPLAY_HEIGHT (960)
//#define NUM_CH    (1)
#define NUM_ALGOS (5)
#define NUM_CHANNEL_MOSAIC (1)
#define APP_MAX_BUFQ_DEPTH (4)

#if 0
#ifdef APP_DEBUG
#define APP_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#else
#define APP_PRINTF(f_, ...)
#endif
#endif


#define APP_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)

#endif
