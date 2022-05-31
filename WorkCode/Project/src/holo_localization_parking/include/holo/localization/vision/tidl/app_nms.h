
#ifndef HOLO_LOCALIZATION_VISION_TIDL_APP_NUMS_H_
#define HOLO_LOCALIZATION_VISION_TIDL_APP_NUMS_H_

#include <assert.h>
#include <vector>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

#include <VX/vx_khr_pipelining.h>
#include <utils/console_io/include/app_get.h>
#include <utils/draw2d/include/draw2d.h>
#include <utils/grpx/include/app_grpx.h>
#include <utils/perf_stats/include/app_perf_stats.h>

#ifdef APP_TIDL_TRACE_DUMP
#include <tivx_utils_tidl_trace.h>
#endif

#include <TI/j7.h>
#include <TI/j7_tidl.h>
#include <TI/tivx.h>
#include <TI/tivx_img_proc.h>
#include <TI/tivx_target_kernel.h>
#include <TI/tivx_task.h>
#include <tivx_utils_file_rd_wr.h>
#include <tivx_utils_graph_perf.h>

#include "itidl_ti.h"
#include "tiadalg_interface.h"
#include "time.h"
#include "tivx_kernels_host_utils.h"

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define APP_PRE_PROC_MAX_TENSORS 4
#define GRAPH_PARAMETER_MAX 16
#define APP_ASSERT_VALID_REF(ref) (APP_ASSERT(vxGetStatus((vx_reference)(ref)) == VX_SUCCESS));
#ifdef APP_DEBUG
#define APP_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#else
#define APP_PRINTF(f_, ...)
#endif

#define APP_ASSERT(x) assert((x))
#define APP_ASSERT_VALID_REF(ref) (APP_ASSERT(vxGetStatus((vx_reference)(ref)) == VX_SUCCESS));
#define APP_MAX_FILE_PATH (256u)
#define APP_MAX_TENSORS (8u)
#define APP_MAX_TENSOR_DIMS (8u)
#define APP_TIDL_MAX_PARAMS (16u)
#define NUM_CH (1)
#define APP_BUFFER_Q_DEPTH (4)  // pipeline

extern "C" {
int32_t appCommonInit();
int32_t appCommonDeInit();
}

int32_t appInit();
int32_t appDeInit();

struct test_obj;

class AppTest;
class AppSelfKernel
{
public:
    AppSelfKernel();
    AppSelfKernel(std::vector<int> data_len, std::vector<int> data_type);
    ~AppSelfKernel();

    int setdata(int8_t* data, int data_len, int index = 0);
    int setdata(int8_t* data, std::vector<int> data_shape, std::vector<int> data_crop);

    int  getdata(int8_t* data);
    bool getdata(int8_t* data, const int data_len, int index = 0);

public:
    AppTest* obj;
};

#ifdef __cplusplus
}
#endif

#endif
