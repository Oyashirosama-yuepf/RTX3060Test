
#ifndef _TADL_INFERENCE_H
#define _TDAL_INFERENCE_H
#include <iostream>
#include <vector>
#include <mutex>

#include <sys/time.h>
#include <math.h>
#include <string>

class AppTadlPrec;
class AppTadlInference;
class AppObj;
// class TIDL_outArgs;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef int vx_enum;
typedef vx_enum vx_status;
typedef int32_t  vx_int32;
typedef size_t vx_size;
typedef char vx_char;
struct PreProcObj;
struct DisplayObj;

void StoreData(uint8_t* featuremap, int data_size, const char* file_tmp);
void StoreData(float* featuremap, int data_size, const char* file_tmp);

class TidlLibrary
{
    public:
       int app_init(AppObj *obj);   
       void app_deinit(AppObj *obj);
       // kernel init
       int app_preproc_init(AppObj *obj);
       int app_tidl_init(AppObj *obj);
       vx_status app_create_pre_graph(AppObj *obj);
    //    vx_status app_create_tidl_graph(AppObj *obj);
       vx_status app_create_graph(AppObj *obj);
       void app_delete_graph(AppObj *obj);
       vx_status app_verify_tidl_graph(AppObj *obj);
       vx_status app_verify_graph(AppObj *obj);
       
       void read_convert_data(AppObj *obj, uint8_t* img_data);
       void write_pre_data(AppObj *obj, char* input_file_name);
       void write_det_data(AppObj *obj, char* input_file_name);
       //
       vx_status app_read_image(AppObj *obj, vx_int32 frame_id);
       void write_det_data(AppObj *obj, vx_int32 frame_id);
       void read_det_result(AppObj *obj, vx_int32 frame_id, float* data=NULL, bool display_flag=false);
    //    void app_find_object_array_index(vx_object_array object_array[], vx_reference ref, vx_int32 array_size, vx_int32 *array_idx);
    //    void app_parse_cfg_file(AppObj *obj, vx_char *cfg_file_name);
       void app_default_param_set(AppObj *obj);
       void set_pre_proc_defaults(PreProcObj *preProcObj);
       void set_display_defaults(DisplayObj *displayObj);
    //    vx_size getTensorDataType(vx_int32 tidl_type);
       void app_pipeline_params_defaults(AppObj *obj);
};
class AppTadlPrec: public TidlLibrary
{
   public:
     AppObj* obj;
     void* quantscale;
     uint32_t frame_id;
     int height_, width_;
     int dl_height_, dl_width_;
     int h_, h_start_, h_crop_;
     /**
      * @author lishuaijie@holomatic.com
      * static option used to record whehter AppInit and AppDeInit is called
      */
     static uint16_t num_of_inited_app_;
     static std::mutex app_mutex_;
   public:
     AppTadlPrec(int height, int width, std::string data_format);
     AppTadlPrec(int height, int width, std::vector<int> crop_param,
                 int dl_height, int dl_width, std::string data_format);
     ~AppTadlPrec();
     void ReadArr(uint8_t* data, int h_start, int h_end);
     void ReadArr(uint8_t* data, int data_size);
     void ReadFile(char* input_file_name);
     void GetConvertData(uint8_t* img_data);
     /**
      * @author lishuaijie@holomatic.com
      * app init and deinit is called in constructor and destructor used to
      * init and deinit TI sdk , and could only be called once
      */
     static int32_t AppInit();
     static int32_t AppDeInit();
};

#endif
