
#ifndef _TADL_INFERENCE_H
#define _TDAL_INFERENCE_H
#include <iostream>
#include <vector>

#include <sys/time.h>
#include <math.h>
#include <string>
#include <atomic>

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

extern std::atomic<int> TERMINATE_STATE;

void StoreData(uint8_t* featuremap, int data_size, const char* file_tmp);
void StoreData(float* featuremap, int data_size, const char* file_tmp);


class Sp_point
{
    public:
        int x;
        int y;
        float score;
};

int32_t appInit();
int32_t appDeInit();

class TidlLibrary
{
    public:
       int app_init(AppObj *obj);   
       void app_deinit(AppObj *obj);
       // kernel init
       int app_preproc_init(AppObj *obj);
       int app_tidl_init(AppObj *obj);
       vx_status app_create_pre_graph(AppObj *obj);
       vx_status app_create_tidl_graph(AppObj *obj);
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
       void read_det_result(AppObj *obj, vx_int32 frame_id, float* data=NULL, bool display_flag=false, bool decode_flag=false);
       void read_superpoint_result(AppObj *obj, vx_int32 frame_id, float *des, float *scores, int *x, int *y);
       //    void app_find_object_array_index(vx_object_array object_array[], vx_reference ref, vx_int32 array_size, vx_int32 *array_idx);
       void app_parse_cfg_file(AppObj *obj, vx_char *cfg_file_name);
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
    //  TIDL_outArgs *quantscale;
     void* quantscale;
     uint32_t frame_id;
     int height_, width_;
     int dl_height_, dl_width_;
   public:
     AppTadlPrec(char* config_file);
     ~AppTadlPrec();
     void ReadArr(uint8_t* data, int data_size);
     void ReadFile(char* input_file_name);
     void GetConvertData(uint8_t* img_data);
};

class TidlBase: public TidlLibrary
{
  public:
      virtual void ReadArr(uint8_t* data, int data_size) = 0;
      virtual void ReadArrTest(uint8_t* data, int data_size) = 0;
      virtual void ReadArrTestRef(int index) = 0;
      virtual void GetArr(float* featuremap) = 0;
      virtual void GetSpResult(std::vector<Sp_point>& sp_result, float* descriptor_data) = 0; 
      virtual void GetImageDataPtr(std::vector<uint8_t*>& image_buff_vector) = 0;
      virtual void GetScalerNodeInputDataAddr(std::vector<std::pair<uint8_t*, uint8_t*>>& image_buff_vector) = 0;
      virtual ~TidlBase()
      {
      };
      int height_, width_;
      int dl_height_, dl_width_;
};

class AppTidl: public TidlBase
{
  public:
     AppObj *obj;
    //  TIDL_outArgs *quantscale;
     void* quantscale;
     uint32_t frame_id;
     vx_enum data_type_;
     
  public:
     AppTidl(char* config_file);
   
     /**
      * @brief Construct a new App Tidl object
      * 
      * @param tidl_config 
      * @param tidl_network 
      * @param height invalid param
      * @param width  invalid param
      * @param crop_param invalid param
      * @param dl_height 
      * @param dl_width  
      */
     AppTidl(char* tidl_config, char* tidl_network,
             uint32_t pipeline_depth,
             int height, int width, std::vector<int> crop_param,
             int dl_height, int dl_width);
     
     ~AppTidl();
     void ReadArr(uint8_t* img_data, int data_size);
     void ReadArrTest(uint8_t* data, int data_size)
     {
       (void)data;
       (void)data_size;
     }
     void ReadArrTestRef(int index)
     {
        (void)index;
     }
     void GetImageDataPtr(std::vector<uint8_t*>& image_buff_vector)
     {
       (void)image_buff_vector;
     }
     void GetScalerNodeInputDataAddr(std::vector<std::pair<uint8_t*, uint8_t*>>& image_buff_vector)
     {
       (void)image_buff_vector;
     }
     void GetArr(float* featuremap);
     void GetSpResult(std::vector<Sp_point> &sp_result, float* descriptor_data)
     {
        (void)sp_result;
        (void)descriptor_data;
     };
};

class AppTidlConfig
{
    public:
        char* tidl_config_;
        char *tidl_network_;
        uint32_t pipeline_depth_;
        int height_;
        int width_;
        std::vector<int> crop_param_;
        int dl_height_;
        int dl_width_;
        std::string yuv_type_ = std::string("nv12");
        std::string data_format_ = std::string("RGB");

        int sp_num_;
};

class AppTadlInference: public TidlBase
{
  public:
    AppObj* obj;
    // TIDL_outArgs *quantscale;
    void* quantscale;
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
    AppTadlInference(char* tidl_config, char* tidl_network,
                     uint32_t pipeline_depth,
                     int height, int width, std::vector<int> crop_param,
                     int dl_height, int dl_width, 
                     std::string yuv_type=std::string("nv12"),
                     std::string data_format=std::string("RGB"));
    AppTadlInference(std::vector<AppTidlConfig> config_param);
    ~AppTadlInference();
    void GetImageDataPtr(std::vector<uint8_t*>& image_buff_vector);
    void GetScalerNodeInputDataAddr(std::vector<std::pair<uint8_t*, uint8_t*>>& image_buff_vector);
    void ReadFile(char* input_file_name);
    void ReadArr(uint8_t* data, int data_size);
    void ReadArrTest(uint8_t* data, int data_size);
    void ReadArrTestRef(int index);
    void GetInferenceResult();
    void GetArr(float* featuremap);   
    void GetDecodeArr(float* featuremap, std::vector<std::vector<float>>& det_result);
    void GetSpResult(std::vector<Sp_point>& sp_result, float* descriptor_data);
};

#endif
