#ifdef __cplusplus
extern "C" {
#endif

//#include <TadlInference.h>

#include <VX/vx_khr_pipelining.h>
#include <utils/console_io/include/app_get.h>
#include <utils/draw2d/include/draw2d.h>
#include <utils/grpx/include/app_grpx.h>
#include <utils/perf_stats/include/app_perf_stats.h>

#ifdef APP_TIDL_TRACE_DUMP
#include <tivx_utils_tidl_trace.h>
#endif
#include <localization/vision/birdview/tda4_nv12torgb/app_common.h>
#include <localization/vision/birdview/tda4_nv12torgb/app_pre_proc_module.h>
#include <localization/vision/birdview/tda4_nv12torgb/app_scaler_module.h>
// #include "app_tidl_module.h"
// #include "app_draw_detections_module.h"
// #include "app_img_mosaic_module.h"
// #include "app_display_module.h"
#include <TI/tivx.h>
#include <app_init.h>

#ifdef __cplusplus
}
#endif

#include <assert.h>
#include <localization/vision/birdview/tda4_nv12torgb/TadlInference.h>
#include <localization/vision/birdview/tda4_nv12torgb/tadl.h>

#include <fstream>
#include <iostream>
#include <string>

/* #define WRITE_INTERMEDIATE_OUTPUTS */

//#define x86_64
#ifndef x86_64
#define APP_ENABLE_PIPELINE_FLOW
#endif

#define APP_PIPELINE_DEPTH (6)
#define APP_FOUR_CAMERA_TOGETHER

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

class GetTimeDiffApp
{
public:
    struct timeval start, end;
    void           StartTiming()
    {
        gettimeofday(&start, NULL);
    }
    float GetTimeDiff()  // ms
    {
        gettimeofday(&end, NULL);
        return (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_usec - start.tv_usec) / 1e3;
    }
};

void StoreData(uint8_t* featuremap, int data_size, const char* file_tmp)
{
    std::fstream fs;
    fs.open(file_tmp, std::ios::out | std::ios::trunc);
    for (int i = 0; i < data_size; i++)
    {
        //    std::cout<<featuremap[i]<<" ";
        fs << (int)featuremap[i] << std::endl;
    }
    // std::cout<<std::endl;
    fs.close();
}

void StoreData(float* featuremap, int data_size, const char* file_tmp)
{
    std::fstream fs;
    fs.open(file_tmp, std::ios::out | std::ios::trunc);
    for (int i = 0; i < data_size; i++)
    {
        //    std::cout<<featuremap[i]<<" ";
        fs << featuremap[i] << std::endl;
    }
    // std::cout<<std::endl;
    fs.close();
}

AppTadlPrec::AppTadlPrec(int height, int width, std::string data_format)
{
    int              dl_height  = height;
    int              dl_width   = width;
    std::vector<int> crop_param = {0, 0, width, height};

    AppInit();
    obj             = new AppObj();
    obj->enqueueCnt = 0;
    frame_id        = 0;
    h_crop_         = 0;

    /////test
    // obj->channel_convert = new combine_channel_test(width, height);

    ///////////
    /*Optional parameter setting*/
    app_default_param_set(obj);
    APP_PRINTF("Default param set! \n");

    obj->scalerObj.input.height = height;
    obj->scalerObj.input.width  = width;

    // dl_height dl_width
    obj->scalerObj.output1.height = dl_height;
    obj->preProcObj.height_       = dl_height;
    obj->scalerObj.output1.width  = dl_width;
    obj->preProcObj.width_        = dl_width;

    /*Config parameter reading*/
    obj->scalerObj.crop_start_x = crop_param[0];
    obj->scalerObj.crop_start_y = crop_param[1];
    obj->scalerObj.crop_width   = crop_param[2];
    obj->scalerObj.crop_height  = crop_param[3];

    // assert
    assert(obj->scalerObj.crop_start_y + obj->scalerObj.crop_height <= height);
    assert(obj->scalerObj.crop_start_x + obj->scalerObj.crop_width <= width);
    assert(obj->scalerObj.crop_height >= dl_height);
    assert(obj->scalerObj.crop_width >= dl_width);

    /*Update of parameters are config file read*/
    // app_update_param_set(obj);
    // APP_PRINTF("Updated user params! \n");
    // optimize the crop param
    if (obj->scalerObj.crop_start_y + obj->scalerObj.crop_height == height &&
        obj->scalerObj.crop_start_x + obj->scalerObj.crop_width == width)
    {
        obj->scalerObj.crop_use = false;
        // obj->rgb_chw_data = new uint8_t[dl_width_*dl_height_*3];
    }
    else
    {
        obj->scalerObj.crop_use = true;
    }
    if (dl_height == height && dl_width == width)
    {
        obj->use_resize = false;
    }
    else
    {
        obj->use_resize = true;
    }
    // optimize the crop param
    if (obj->scalerObj.crop_start_y + obj->scalerObj.crop_height == height &&
        obj->scalerObj.crop_start_x + obj->scalerObj.crop_width == width)
    {
        obj->scalerObj.crop_use = false;
    }
    else
    {
        obj->scalerObj.crop_use = true;
    }
    assert(data_format == "RGB" || data_format == "BGR" || data_format == "RGB-HWC" || data_format == "BGR-HWC");
    if (data_format == "RGB" || data_format == "RGB-HWC")
        obj->preProcObj.data_format_ = 1;
    else
        obj->preProcObj.data_format_ = 0;
    if (data_format == "RGB-HWC" || data_format == "BGR-HWC")
    {
        obj->use_channel_convert = 1;
    }
    else
    {
        obj->use_channel_convert = 0;
    }

    app_preproc_init(obj) APP_PRINTF("App Init Done! \n");

    printf("obj->en_out_img_write: %d\n", obj->en_out_img_write);

    app_create_pre_graph(obj);
    APP_PRINTF("App Create Graph Done! \n");
    std::cout << "1" << std::endl;

    app_verify_graph(obj);

    APP_PRINTF("App Verify Graph Done! \n");

    printf("obj->en_out_img_write: %d\n", obj->en_out_img_write);
    std::cout << "1" << std::endl;

    height_    = obj->scalerObj.input.height;
    width_     = obj->scalerObj.input.width;
    dl_height_ = obj->scalerObj.output1.height;
    dl_width_  = obj->scalerObj.output1.width;
}

AppTadlPrec::AppTadlPrec(int height, int width, std::vector<int> crop_param, int dl_height, int dl_width,
                         std::string data_format)
{
    AppInit();
    obj             = new AppObj();
    obj->enqueueCnt = 0;
    frame_id        = 0;
    h_crop_         = 0;

    /////test
    // obj->channel_convert = new combine_channel_test(width, height);

    ///////////
    /*Optional parameter setting*/
    app_default_param_set(obj);
    APP_PRINTF("Default param set! \n");

    obj->scalerObj.input.height = height;
    obj->scalerObj.input.width  = width;

    // dl_height dl_width
    obj->scalerObj.output1.height = dl_height;
    obj->preProcObj.height_       = dl_height;
    obj->scalerObj.output1.width  = dl_width;
    obj->preProcObj.width_        = dl_width;

    /*Config parameter reading*/
    obj->scalerObj.crop_start_x = crop_param[0];
    obj->scalerObj.crop_start_y = crop_param[1];
    obj->scalerObj.crop_width   = crop_param[2];
    obj->scalerObj.crop_height  = crop_param[3];

    // assert
    assert(obj->scalerObj.crop_start_y + obj->scalerObj.crop_height <= height);
    assert(obj->scalerObj.crop_start_x + obj->scalerObj.crop_width <= width);
    assert(obj->scalerObj.crop_height >= dl_height);
    assert(obj->scalerObj.crop_width >= dl_width);

    /*Update of parameters are config file read*/
    // app_update_param_set(obj);
    // APP_PRINTF("Updated user params! \n");
    // optimize the crop param
    if (obj->scalerObj.crop_start_y + obj->scalerObj.crop_height == height &&
        obj->scalerObj.crop_start_x + obj->scalerObj.crop_width == width)
    {
        obj->scalerObj.crop_use = false;
        // obj->rgb_chw_data = new uint8_t[dl_width_*dl_height_*3];
    }
    else
    {
        obj->scalerObj.crop_use = true;
    }
    if (dl_height == height && dl_width == width)
    {
        obj->use_resize = false;
    }
    else
    {
        obj->use_resize = true;
    }
    // optimize the crop param
    if (obj->scalerObj.crop_start_y + obj->scalerObj.crop_height == height &&
        obj->scalerObj.crop_start_x + obj->scalerObj.crop_width == width)
    {
        obj->scalerObj.crop_use = false;
    }
    else
    {
        obj->scalerObj.crop_use = true;
    }
    assert(data_format == "RGB" || data_format == "BGR" || data_format == "RGB-HWC" || data_format == "BGR-HWC");
    if (data_format == "RGB" || data_format == "RGB-HWC")
        obj->preProcObj.data_format_ = 1;
    else
        obj->preProcObj.data_format_ = 0;
    if (data_format == "RGB-HWC" || data_format == "BGR-HWC")
    {
        obj->use_channel_convert = 1;
    }
    else
    {
        obj->use_channel_convert = 0;
    }

    app_preproc_init(obj) APP_PRINTF("App Init Done! \n");

    printf("obj->en_out_img_write: %d\n", obj->en_out_img_write);

    app_create_pre_graph(obj);
    APP_PRINTF("App Create Graph Done! \n");
    std::cout << "1" << std::endl;

    app_verify_graph(obj);

    APP_PRINTF("App Verify Graph Done! \n");

    printf("obj->en_out_img_write: %d\n", obj->en_out_img_write);
    std::cout << "1" << std::endl;

    height_    = obj->scalerObj.input.height;
    width_     = obj->scalerObj.input.width;
    dl_height_ = obj->scalerObj.output1.height;
    dl_width_  = obj->scalerObj.output1.width;
}

AppTadlPrec::~AppTadlPrec()
{
    std::cout << "~App" << std::endl;
    vxWaitGraph(obj->graph);
    std::cout << "wait" << std::endl;
    app_delete_graph(obj);
    std::cout << "delete" << std::endl;
    app_deinit(obj);
    std::cout << "deinit obj" << std::endl;

    AppDeInit();
    std::cout << "destructor" << std::endl;
}

void AppTadlPrec::ReadFile(char* input_file_name)
{
    write_pre_data(obj, input_file_name);
    frame_id++;
}

void AppTadlPrec::ReadArr(uint8_t* data, int height, int h_start)
{
    int data_size = dl_width_ * dl_height_ * 3 / 2;
    std::cout << dl_width_ << " " << dl_height_ << " " << data_size << std::endl;
    h_       = height;
    h_start_ = h_start;
    h_crop_  = 1;
    ReadArr(data, data_size);
}

void AppTadlPrec::ReadArr(uint8_t* data, int data_size)
{
    ScalerObj*  scalerObj  = &obj->scalerObj;
    PreProcObj* preProcObj = &obj->preProcObj;
    /* Enqueue outpus */
    std::cout << "enqueue data: " << obj->enqueueCnt << std::endl;
    vxGraphParameterEnqueueReadyRef(obj->graph, preProcObj->graph_parameter_index,
                                    (vx_reference*)&preProcObj->output_tensor_arr[obj->enqueueCnt], 1);

    vx_status                  status;
    vx_rectangle_t             rect;
    vx_imagepatch_addressing_t image_addr;
    vx_map_id                  map_id;
    void*                      data_ptr;
    vx_uint32                  img_width;
    vx_uint32                  img_height;
    vx_image                   in_img;
    vx_uint32                  num_bytes;

    in_img = (vx_image)vxGetObjectArrayItem(scalerObj->input.arr[0], 0);

    vxQueryImage(in_img, VX_IMAGE_WIDTH, &img_width, sizeof(vx_uint32));
    vxQueryImage(in_img, VX_IMAGE_HEIGHT, &img_height, sizeof(vx_uint32));

    rect.start_x = 0;
    rect.start_y = 0;
    rect.end_x   = img_width;
    rect.end_y   = img_height;

    status = vxMapImagePatch(in_img, &rect, 0, &map_id, &image_addr, &data_ptr, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST,
                             VX_NOGAP_X);
    vx_int32 one_frame = img_width * img_height * 1.5;
    // Copy Luma
    // num_bytes = fread(data_ptr,1,img_width*img_height, fp);
    // data_ptr = data;
    // std::cout<<data<<std::endl;
    // std::cout<<"copy data start "<<h_start_*width_<<" "<<data_size<<std::endl;
    if (!h_crop_)
    {
        memcpy(data_ptr, data, data_size * 2 / 3);
    }
    else
    {
        memcpy(data_ptr, data + h_start_ * width_, data_size * 2 / 3);
    }

    // if(num_bytes != (img_width*img_height))
    //   printf("Luma bytes read = %d, expected = %d", num_bytes, img_width*img_height);

    vxUnmapImagePatch(in_img, map_id);
    rect.start_x = 0;
    rect.start_y = 0;
    rect.end_x   = img_width;
    rect.end_y   = img_height / 2;
    status = vxMapImagePatch(in_img, &rect, 1, &map_id, &image_addr, &data_ptr, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST,
                             VX_NOGAP_X);
    // Copy CbCr
    // num_bytes = fread(data_ptr,1,img_width*img_height/2, fp);
    // fread(data1,1,img_width*imgheight/2, fp);
    std::cout << "copy data start1 " << (h_ + h_start_ / 2) * dl_width_ << " " << data_size << std::endl;
    if (!h_crop_)
    {
        memcpy(data_ptr, data + data_size * 2 / 3, data_size * 1 / 3);
    }
    else
    {
        memcpy(data_ptr, data + (h_ + h_start_ / 2) * dl_width_, data_size * 1 / 3);
        int a1 = (h_ + h_start_ / 2) * dl_width_;
        int a2 = (h_ + h_start_ / 2) * dl_width_ + data_size / 3;
        std::cout << "test1" << std::endl;
        for (int i = a1; i < a1 + 10; i++)
        {
            std::cout << (int)data[i] << " ";
        }
        std::cout << std::endl;
        for (int i = a2; i > a2 - 10; i--)
        {
            std::cout << (int)data[i] << " ";
        }
        std::cout << std::endl;
    }
    // data_ptr = &data[img_width*img_height];
    // if(num_bytes != (img_width*img_height/2))
    //   printf("CbCr bytes read = %d, expected = %d", num_bytes, img_width*img_height/2);

    vxUnmapImagePatch(in_img, map_id);
    vxReleaseImage(&in_img);

    // vxReleaseImage(&in_img);

    //////////image arr -> dsp(gpu)////////////////
    /* Enqueue input - start execution */
    vxGraphParameterEnqueueReadyRef(obj->graph, scalerObj->graph_parameter_index,
                                    (vx_reference*)&obj->scalerObj.input_images[obj->enqueueCnt], 1);

    // obj->enqueueCnt++;
    // obj->enqueueCnt   = (obj->enqueueCnt  >= APP_BUFFER_Q_DEPTH)? 0 : obj->enqueueCnt;
}

void AppTadlPrec::GetConvertData(uint8_t* img_data)
{
    read_convert_data(obj, img_data);
}

int32_t AppTadlPrec::AppInit()
{
    std::unique_lock<std::mutex> lock(app_mutex_);
    num_of_inited_app_++;

    // it can only be initialized once
    if (num_of_inited_app_ > 1u)
    {
        return 0;
    }

    std::cout << "AppTadlPrec::AppInit is called!!!" << std::endl;

    return appInit();
}

int32_t AppTadlPrec::AppDeInit()
{
    std::unique_lock<std::mutex> lock(app_mutex_);
    num_of_inited_app_--;

    if (num_of_inited_app_)
    {
        return 0;
    }

    std::cout << "AppTadlPrec::AppDeInit is called!!!" << std::endl;

    return appDeInit();
}

uint16_t   AppTadlPrec::num_of_inited_app_ = 0u;
std::mutex AppTadlPrec::app_mutex_;
