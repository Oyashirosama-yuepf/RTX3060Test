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

#include "itidl_ti.h"
#include "tiadalg_interface.h"
#include "tivx_kernels_host_utils.h"
#include <TI/tivx.h>
#include <TI/tivx_img_proc.h>
#include <TI/tivx_target_kernel.h>
#include <TI/tivx_task.h>

#include <TI/j7.h>
#include <TI/j7_tidl.h>
#include <tivx_utils_file_rd_wr.h>
#include <tivx_utils_graph_perf.h>

#ifdef __cplusplus
}
#endif

#include <iostream>
#ifdef USE_OPECV_CPP
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif
#include <fstream>

#include "holo/localization/vision/tidl/app_nms.h"
#include "holo/localization/vision/tidl/tivx_self_img_proc.h"

vx_status app_update_pre_proc_test(vx_context context, test_obj* preProcObj, vx_user_data_object config);
vx_status app_init_pre_proc_test(vx_context context, test_obj* preProcObj, char* objName);
vx_status app_update_pre_proc_data_convert_test(vx_context context, test_obj* preProcObj);
void      app_deinit_pre_proc_test(test_obj* obj);
void      app_delete_pre_proc_test(test_obj* obj);
vx_status app_create_graph_pre_proc_test(vx_graph graph, test_obj* preProcObj);
vx_status writePreProcOutput_test(char* file_name, test_obj* preProcObj);

extern "C" {
int32_t appCommonInit();
int32_t appCommonDeInit();
}

int32_t appInit()
{
    int32_t status = 0;

    status = appCommonInit();

    if (status == 0)
    {
        tivxInit();
        tivxHostInit();
    }
    return status;
}

int32_t appDeInit()
{
    int32_t status = 0;
    tivxHostDeInit();
    tivxDeInit();
    appCommonDeInit();

    return status;
}

typedef struct test_obj
{
    vx_node node;

    vx_array             config;
    tivxImgPreProcParams params;

    sTIDL_IOBufDesc_t ioBufDesc;
    // test
    vx_tensor        input1[APP_PRE_PROC_MAX_TENSORS], input2[APP_PRE_PROC_MAX_TENSORS];
    vx_tensor        scores, indexs;
    vx_int32         graph_parameter_index[16];
    std::vector<int> data_len;
    std::vector<int> data_type;
} test_obj;

class AppTest
{
public:
    // ScalerObj  scalerObj;
    test_obj preProcObj;
    /* OpenVX references */
    vx_context context;
    vx_graph   graph;

    vx_int32 en_out_img_write;

    vx_int32 start_frame;
    vx_int32 num_frames;

    vx_uint32 delay_in_msecs;
    vx_uint32 num_iterations;
    vx_uint32 is_interactive;

    int32_t pipeline;

    int32_t enqueueCnt;
    int32_t dequeueCnt;

    vx_map_id map_id;

public:
    AppTest();
    AppTest(std::vector<int> data_len, std::vector<int> data_type);
    bool map_tensor_data(vx_tensor& data, void*& data_buf, bool read = false);
    void unmap_tensor_data(const vx_tensor& data);
};

AppTest::AppTest()
{
}

AppTest::AppTest(std::vector<int> data_len, std::vector<int> data_type)
{
    preProcObj.data_len  = data_len;
    preProcObj.data_type = data_type;
}

int app_init(AppTest* obj)
{
    int                  status = VX_SUCCESS;
    app_grpx_init_prms_t grpx_prms;

    /* Create OpenVx Context */
    obj->context = vxCreateContext();
    APP_ASSERT_VALID_REF(obj->context);
    std::cout << "load kernel start" << std::endl;
    tivxHwaLoadKernels(obj->context);
    tivxImgProcLoadKernels(obj->context);
    tivxSelfProcLoadKernels(obj->context);
    std::cout << "load kernel end" << std::endl;
    // tivxTIDLLoadKernels(obj->context);
    /* Initialize modules */
    app_init_pre_proc_test(obj->context, &obj->preProcObj, (char*)"test");
    app_update_pre_proc_data_convert_test(obj->context, &obj->preProcObj);

    return status;
    (void)grpx_prms;
}

void add_graph_parameter_by_node_index(vx_graph graph, vx_node node, vx_uint32 node_parameter_index)
{
    vx_parameter parameter = vxGetParameterByIndex(node, node_parameter_index);

    vxAddParameterToGraph(graph, parameter);
    vxReleaseParameter(&parameter);
}

vx_status app_create_graph(AppTest* obj)
{
    vx_status                         status = VX_SUCCESS;
    vx_graph_parameter_queue_params_t graph_parameters_queue_params_list[GRAPH_PARAMETER_MAX];
    vx_int32                          graph_parameter_index;
    obj->graph = vxCreateGraph(obj->context);
    status     = vxGetStatus((vx_reference)obj->graph);
    vxSetReferenceName((vx_reference)obj->graph, "OpenVxGraph");
    app_create_graph_pre_proc_test(obj->graph, &obj->preProcObj);

    return status;
    (void)graph_parameters_queue_params_list;
    (void)graph_parameter_index;
}

vx_status app_verify_graph(AppTest* obj)
{
    vx_status status = VX_SUCCESS;
    status           = vxVerifyGraph(obj->graph);

    APP_PRINTF("App Verify Graph Done!\n");
    /* wait a while for prints to flush */
    tivxTaskWaitMsecs(100);

    return status;
}

bool AppSelfKernel::getdata(int8_t* data, const int data_len, int index)
{
    vx_status status = VX_SUCCESS;
    // get output data
    status = vxProcessGraph(obj->graph);
    if (index == 0)
    {
        vx_float32* data_ptr;
        obj->map_tensor_data(obj->preProcObj.scores, (void*&)data_ptr);
        memcpy((int8_t*)data, data_ptr, data_len);
        obj->unmap_tensor_data(obj->preProcObj.scores);
    }
    else
    {
        vx_float32* data_ptr;
        obj->map_tensor_data(obj->preProcObj.indexs, (void*&)data_ptr);
        memcpy((int8_t*)data, data_ptr, data_len);
        obj->unmap_tensor_data(obj->preProcObj.indexs);
    }
    return true;
    (void)status;
}

AppSelfKernel::AppSelfKernel()
{
}

AppSelfKernel::AppSelfKernel(std::vector<int> data_len, std::vector<int> data_type)
{
    appInit();
    obj = new AppTest(data_len, data_type);
    app_init(obj);
    std::cout << "app init end" << std::endl;
    app_create_graph(obj);
    std::cout << "app create end" << std::endl;
    app_verify_graph(obj);
    std::cout << "app verify end" << std::endl;
}

AppSelfKernel::~AppSelfKernel()
{
    appDeInit();
}

bool AppTest::map_tensor_data(vx_tensor& data, void*& data_buf, bool read)
{
    vx_status status = VX_SUCCESS;
    vx_tensor input1 = data;
    vx_size   start[3];
    start[0] = 0;
    vx_size output_sizes[3];
    vx_size output_strides[3];
    output_strides[0] = sizeof(VX_TYPE_INT8);
    if (!read)
    {
        output_sizes[0] = preProcObj.data_len[0];
        status = tivxMapTensorPatch(input1, 1, start, output_sizes, &map_id, output_strides, &data_buf, VX_WRITE_ONLY,
                                    VX_MEMORY_TYPE_HOST);
        return true;
    }
    else
    {
        output_sizes[0] = preProcObj.data_len[1];
        status = tivxMapTensorPatch(input1, 1, start, output_sizes, &map_id, output_strides, &data_buf, VX_READ_ONLY,
                                    VX_MEMORY_TYPE_HOST);
        return true;
    }
    return false;
    (void)status;
}

void AppTest::unmap_tensor_data(const vx_tensor& data)
{
    tivxUnmapTensorPatch(data, map_id);
}

int AppSelfKernel::setdata(int8_t* data, int data_len, int index)
{
    if (index == 0)
    {
        int8_t* data_ptr;
        obj->map_tensor_data(obj->preProcObj.input1[0], (void*&)data_ptr);
        // std::cout<<"map id "<<map_id<<std::endl;
        // set data_ptr
        // std::cout << "set data in buffer 0" << std::endl;
        memcpy(data_ptr, data, data_len);
        obj->unmap_tensor_data(obj->preProcObj.input1[0]);
        // std::cout << "set data in buffer 0 done " << std::endl;
    }
    else if (index == 1)
    {
        int8_t* data_ptr_tmp;
        obj->map_tensor_data(obj->preProcObj.input2[0], (void*&)data_ptr_tmp);
        // std::cout<<"map id "<<map_id<<std::endl;
        // set data_ptr
        // std::cout << "set data in buffer 1" << std::endl;
        data_ptr_tmp[0] = 1;
        // std::cout << "set data in buffer 1 done " << std::endl;
        memcpy(data_ptr_tmp, data, data_len);
        obj->unmap_tensor_data(obj->preProcObj.input2[0]);
    }
    return 1;
}

int AppSelfKernel::setdata(int8_t* data, std::vector<int> data_shape, std::vector<int> data_crop)
{
    int8_t* data_ptr;
    obj->map_tensor_data(obj->preProcObj.input1[0], (void*&)data_ptr);
    std::cout << "set data" << std::endl;
    int data_channel = data_shape[0];
    int data_h       = data_shape[1];
    int data_w       = data_shape[2];
    int start_y      = data_crop[0];
    int start_x      = data_crop[1];
    int end_y        = data_crop[2];
    int end_x        = data_crop[3];
    std::cout << "data crop " << start_x << " " << start_y << " " << end_x << " " << end_y << std::endl;
    std::ofstream file1;
    int           num = 0;
    for (int i = 0; i < data_channel; i++)
    {
        // use crop
        if (1)
        {
            int start_pixel  = i * (data_h * data_w) + start_y * data_w + start_x;
            int data_valid_w = end_x - start_x + 1;
            for (int j = start_y; j < end_y + 1; j++)
            {
                memcpy(data_ptr + data_valid_w * (num++), data + start_pixel + data_w * (j - start_y), data_valid_w);
            }
        }
    }
    std::cout << "copy pixel: " << end_x << " " << start_x << " " << num * (end_x - start_x) << std::endl;
    obj->unmap_tensor_data(obj->preProcObj.input1[0]);
    std::cout << "set data end" << std::endl;
    return 1;
}

int AppSelfKernel::getdata(int8_t* data)
{
    return 1;
    (void)data;
}

vx_status app_init_pre_proc_test(vx_context context, test_obj* preProcObj, char* objName)
{
    vx_status status = VX_SUCCESS;

    vx_enum config_type = VX_TYPE_INVALID;
    config_type         = vxRegisterUserStruct(context, sizeof(tivxImgPreProcParams));
    APP_ASSERT(config_type >= VX_TYPE_USER_STRUCT_START && config_type <= VX_TYPE_USER_STRUCT_END);

    preProcObj->config = vxCreateArray(context, config_type, 1);
    APP_ASSERT_VALID_REF(preProcObj->config);

    vx_char ref_name[APP_MAX_FILE_PATH];
    vxAddArrayItems(preProcObj->config, 1, &preProcObj->params, sizeof(tivxImgPreProcParams));
    snprintf(ref_name, APP_MAX_FILE_PATH, "%s_config", objName);
    vxSetReferenceName((vx_reference)preProcObj->config, ref_name);

    return status;
}

vx_status app_update_pre_proc_data_convert_test(vx_context context, test_obj* preProcObj)
{
    vx_status status = VX_SUCCESS;
    vx_map_id map_id_config;
    vx_enum   data_type;

    vx_size input_sizes_tmp[APP_MAX_TENSOR_DIMS];
    input_sizes_tmp[0]    = preProcObj->data_len[0] * preProcObj->data_type[0];
    preProcObj->input1[0] = vxCreateTensor(context, 1, input_sizes_tmp, VX_TYPE_INT8, 0);
    input_sizes_tmp[0]    = preProcObj->data_len[1] * preProcObj->data_type[1];
    std::cout << "-----------" << input_sizes_tmp[0] << std::endl;
    preProcObj->input2[0] = vxCreateTensor(context, 1, input_sizes_tmp, VX_TYPE_INT8, 0);

    input_sizes_tmp[0] = preProcObj->data_len[2] * preProcObj->data_type[2];
    preProcObj->scores = vxCreateTensor(context, 1, input_sizes_tmp, VX_TYPE_INT8, 0);
    input_sizes_tmp[0] = preProcObj->data_len[3] * preProcObj->data_type[3];
    preProcObj->indexs = vxCreateTensor(context, 1, input_sizes_tmp, VX_TYPE_INT8, 0);
    return status;
    (void)status;
    (void)map_id_config;
    (void)data_type;
}

vx_status app_create_graph_pre_proc_test(vx_graph graph, test_obj* preProcObj)
{
    vx_status status = VX_SUCCESS;

    vx_tensor input1 = preProcObj->input1[0];
    vx_tensor input2 = preProcObj->input2[0];

    vx_tensor scores = preProcObj->scores;
    vx_tensor indexs = preProcObj->indexs;

    preProcObj->node = tivxSelfHirainThresholdNode(graph, input1, input2, scores, indexs);
    APP_ASSERT_VALID_REF(preProcObj->node);

    status = vxSetNodeTarget(preProcObj->node, VX_TARGET_STRING, TIVX_TARGET_DSP2);
    vxSetReferenceName((vx_reference)preProcObj->node, "PreProcNode");

    vx_bool replicate[] = {vx_true_e, vx_true_e, vx_true_e, vx_true_e};

    printf("test replicate\n");
    vxReplicateNode(graph, preProcObj->node, replicate, 4);
    printf("test replicate end\n");

    vxReleaseTensor(&input1);
    vxReleaseTensor(&input2);

    return (status);
}
