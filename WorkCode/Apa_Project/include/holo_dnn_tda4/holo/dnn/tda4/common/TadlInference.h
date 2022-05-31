
#ifndef _TADL_INFERENCE_H
#define _TDAL_INFERENCE_H
#include <math.h>
#include <sys/time.h>

#include <atomic>
#include <iostream>
#include <string>
#include <vector>

#include "holo/dnn/tda4/common/app_common.h"
#include "utils.h"
class AppTadlInference;
class AppObj;
typedef unsigned int  uint32_t;
typedef unsigned char uint8_t;
typedef int           vx_enum;
typedef vx_enum       vx_status;
typedef int32_t       vx_int32;
typedef size_t        vx_size;
typedef char          vx_char;
struct PreProcObj;
struct DisplayObj;

extern std::atomic<int> TERMINATE_STATE;

void StoreData(uint8_t* featuremap, int data_size, const char* file_tmp);
void StoreData(float* featuremap, int data_size, const char* file_tmp);

class Sp_point
{
public:
    int   x;
    int   y;
    float score;
};

int32_t appInit();
int32_t appDeInit();

class TidlLibrary
{
public:
    int  app_init(AppObj* obj);
    void app_deinit(AppObj* obj);

    vx_status app_create_graph(AppObj* obj);
    void      app_delete_graph(AppObj* obj);
    vx_status app_verify_graph(AppObj* obj);

    void read_convert_data(AppObj* obj, uint8_t* img_data);
    //
    vx_status app_read_image(AppObj* obj, vx_int32 frame_id);
    void      write_det_data(AppObj* obj, vx_int32 frame_id);
    void      read_det_result(AppObj* obj, vx_int32 frame_id, float* data = NULL, bool data_flag = true);
    void      app_parse_cfg_file(AppObj* obj, vx_char* cfg_file_name);
    void      app_default_param_set(AppObj* obj);
    void      set_pre_proc_defaults(PreProcObj* preProcObj);
    void      set_display_defaults(DisplayObj* displayObj);
    void      app_pipeline_params_defaults(AppObj* obj);
};

class TidlBase : public TidlLibrary
{
public:
    virtual void ReadArr(uint8_t* data, int data_size)                                                     = 0;
    virtual void ReadArrNoCopy(uint64_t* data_arr, int index)                                              = 0;
    virtual void ReadArrTest(uint8_t* data, int data_size)                                                 = 0;
    virtual void ReadArrTestRef(int index)                                                                 = 0;
    virtual void GetArr(float* featuremap, bool map_tensor_flag)                                           = 0;
    virtual void GetImageDataPtr(std::vector<uint8_t*>& image_buff_vector)                                 = 0;
    virtual void GetScalerNodeInputDataAddr(std::vector<std::pair<uint8_t*, uint8_t*>>& image_buff_vector) = 0;
    int          GetInferenceDataSize(void* tidlObj);
    virtual ~TidlBase(){};
    int                           height_, width_;
    int                           dl_height_, dl_width_;
    int                           featuremap_size_;
    std::vector<std::vector<int>> fp_shape_;

    std::vector<FeatureMapRawData> fp_data_vec;
    FeatureMapRawData              tensors_data[APP_TIDL_MAX_TENSORS][APP_BUFFER_Q_DEPTH];

    bool get_raw_data = false;
};

class AppTidlConfig
{
public:
    char*            tidl_config_;
    char*            tidl_network_;
    uint32_t         pipeline_depth_;
    int              height_;
    int              width_;
    std::vector<int> crop_param_;
    int              dl_height_;
    int              dl_width_;
    std::string      yuv_type_;
    std::string      data_format_;
};

class AppTadlInference : public TidlBase
{
public:
    AppObj* obj;
    // TIDL_outArgs *quantscale;
    void*    quantscale;
    uint32_t frame_id;

public:
    AppTadlInference(char* config_file);
    /**
     * @brief Construct a new App Tadl Inference object
     *
     * @param tidl_config
     * @param tidl_network
     * @param height origin image height
     * @param width  origin image width
     * @param crop_param  crop x_start y_start x_width, y_height
     * @param dl_height resize dl height
     * @param dl_width resize dl width
     * @param data_format color pattern "RGB" "BGR" default "RGB"
     */
    AppTadlInference(char* tidl_config, char* tidl_network, uint32_t pipeline_depth, int height, int width,
                     std::vector<int> crop_param, int dl_height, int dl_width, std::string data_format);
    ~AppTadlInference();
    void GetImageDataPtr(std::vector<uint8_t*>& image_buff_vector);
    void GetScalerNodeInputDataAddr(std::vector<std::pair<uint8_t*, uint8_t*>>& image_buff_vector);

    /**
     * @brief read image data
     *
     * @param data
     * @param data_size
     */
    void ReadArr(uint8_t* data, int data_size);

    /**
     * @brief read uyvy rgbx data
     *
     * @param data
     * @param data_size
     */
    void ReadArrTest(uint8_t* data, int data_size);
    void ReadArrNoCopy(uint64_t* data_arr, int index);
    void ReadArrTestRef(int index);
    void GetArr(float* featuremap, bool map_tensor_flag);
    void PipelineQueueInit();
};

#endif
