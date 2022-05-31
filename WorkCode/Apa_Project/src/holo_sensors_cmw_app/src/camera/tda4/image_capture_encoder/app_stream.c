#include <utils/draw2d/include/draw2d.h>
#include <utils/perf_stats/include/app_perf_stats.h>
#include <utils/console_io/include/app_get.h>
#include <utils/grpx/include/app_grpx.h>
#include <VX/vx_khr_pipelining.h>

#include "app_common.h"
#include "app_sensor_module.h"
#include "app_capture_module.h"
#include "app_img_mosaic_module.h"
#include "app_encode_module.h"
#include "app_file_module.h"
#include "app_img_convert.h"
#include "app_stream.h"

#include "errno.h"
#include "signal.h"
#include <unistd.h>

#define APP_BUFFER_Q_DEPTH   (4)
#define APP_PIPELINE_DEPTH   (7)

#define ENCODE_FILE_NUM      (3)
#define ENCODE_FRAME_NUM     (600)
#define LOOP_RECODE

#define CAP_CHANNEL_F        (0)
#define CAP_CHANNEL_B	     (1)
#define CAP_CHANNEL_L	     (2)
#define CAP_CHANNEL_R 	     (3)
#define WR_QUEUE_LEN	     (1)
#define MAX_ATTRIBUTE_NAME   (32u)

#define SENSOR_OMNIVISON_OX01F10_MAX9286        "OX01F10-MAX9286"
#define SENSOR_SONY_IMX390_UB953                "IMX390-UB953-FRONT"

#define SENSOR_CONFIG        (0x03)
#define SENSOR_STREAM_ON     (0x04)
#define SENSOR_STREAM_OFF    (0x05)

typedef struct {

    SensorObj     sensorObj;
    CaptureObj    captureObj;
    ImgMosaicObj  imgMosaicObj[NUM_ENCODE_CHANNEL];
    EncodeObj     encodeObj[NUM_ENCODE_CHANNEL];
    ImgConvertObj imgConvertObj;

    vx_char output_file_path[APP_MAX_FILE_PATH];

    /* OpenVX references */
    vx_context context;
    vx_graph   graph;
    vx_graph   encode_graph;
    vx_node    convert_node;

    vx_int32 en_out_img_write;

    vx_uint32 num_frames_to_run;

    vx_uint32 num_frames_to_write;
    vx_uint32 num_frames_to_skip;

    tivx_task task;
    vx_uint32 stop_task;
    vx_uint32 stop_task_done;

    app_perf_point_t total_perf;
    app_perf_point_t fileio_perf;
    app_perf_point_t draw_perf;
    app_perf_point_t encode_deq_perf;
    app_perf_point_t query_perf;

    int32_t enable_ldc;

    int32_t pipeline;

    int32_t enqueueCnt;
    int32_t dequeueCnt;

    int32_t write_file;

} AppObj;

typedef struct
{
    AppObj *obj;
    uint8_t channel;
}thread_arg;

static Nv12OutBuf Nv12OutBufMem[NUM_CAPT_CHANNELS];
static EncodeStreamInfo gStream_info[NUM_ENCODE_CHANNEL];

AppObj gAppObj;
static vx_image nv12_output_image[4];
static vx_image mosaic_output_image;
static vx_uint8 init_param = 0x00;

static vx_status app_init(AppObj *obj);
static void app_deinit(AppObj *obj);
static vx_status app_create_graph(AppObj *obj);
static vx_status app_verify_graph(AppObj *obj);
static vx_status app_run_graph(AppObj *obj);
static void app_delete_graph(AppObj *obj);
static void app_default_param_set(AppObj *obj);
static void app_update_param_set(AppObj *obj);
static void app_pipeline_params_defaults(AppObj *obj);
static void add_graph_parameter_by_node_index(vx_graph graph, vx_node node, vx_uint32 node_parameter_index);
static void set_img_mosaic_params(ImgMosaicObj *imgMosaicObj, vx_uint32 in_width, vx_uint32 in_height, vx_int32 numCh);
static void set_encode_params(AppObj *obj);
static vx_status app_display_init(AppObj *obj);


static void app_deinit_resource()
{
    int channel;

    for(channel = 0; channel < NUM_ENCODE_CHANNEL; channel++)
    {
        free(gStream_info[channel].mem);
        gStream_info[channel].mem = NULL;
    }

    for(channel = 0; channel < NUM_CAPT_CHANNELS; channel++)
    {
        if(Nv12OutBufMem[channel].Luma_ptr)
        {
            free(Nv12OutBufMem[channel].Luma_ptr);
            Nv12OutBufMem[channel].Luma_ptr = NULL;
        }
        if(Nv12OutBufMem[channel].Cbcr_ptr)
        {
            free(Nv12OutBufMem[channel].Cbcr_ptr);
            Nv12OutBufMem[channel].Cbcr_ptr = NULL;
        }
    }

    return;
}


static vx_status PostImageNv12Output(vx_image out_img, uint8_t channel)
{
  	vx_status status;

    status = vxGetStatus((vx_reference)out_img);

    if(status == VX_SUCCESS)
    {
      vx_rectangle_t rect;
      vx_imagepatch_addressing_t image_addr;
      vx_map_id map_id;
      void * data_ptr;
      vx_uint32  img_width;
      vx_uint32  img_height;

      vxQueryImage(out_img, VX_IMAGE_WIDTH, &img_width, sizeof(vx_uint32));
      vxQueryImage(out_img, VX_IMAGE_HEIGHT, &img_height, sizeof(vx_uint32));

      rect.start_x = 0;
      rect.start_y = 0;
      rect.end_x = img_width;
      rect.end_y = img_height;

      status = vxMapImagePatch(out_img,&rect,0,&map_id,&image_addr,&data_ptr,VX_READ_ONLY,VX_MEMORY_TYPE_HOST,VX_NOGAP_X);
      if(status == VX_SUCCESS)
      {
        Nv12OutBufMem[channel].Luma_size = img_width * img_height;
        memcpy(Nv12OutBufMem[channel].Luma_ptr,data_ptr,Nv12OutBufMem[channel].Luma_size);
        vxUnmapImagePatch(out_img, map_id);
      }
      else
        return VX_FAILURE;
      status = vxMapImagePatch(out_img, &rect,1,&map_id,&image_addr,&data_ptr,VX_READ_ONLY,VX_MEMORY_TYPE_HOST,VX_NOGAP_X);
      if(status == VX_SUCCESS)
      {
        Nv12OutBufMem[channel].Cbcr_size = img_width*img_height/2;
        memcpy(Nv12OutBufMem[channel].Cbcr_ptr,data_ptr,Nv12OutBufMem[channel].Cbcr_size);
        vxUnmapImagePatch(out_img, map_id);
      }
      else
        return VX_FAILURE;
    }
    return(status);
}

static vx_status PostEncodeOutput(EncodeObj* encodeObj, EncodeStreamInfo* info, vx_uint8 channel)
{
	vx_status status;
	vx_map_id map_id;
	vx_size   bitstream_size;
	vx_uint8 *bitstream;

	status = vxQueryUserDataObject(encodeObj->bitstream_obj,
			TIVX_USER_DATA_OBJECT_VALID_SIZE,
			&(bitstream_size), sizeof(vx_size));
	APP_ASSERT(status==VX_SUCCESS);

	status = vxMapUserDataObject(encodeObj->bitstream_obj, 0,
			bitstream_size,
			&map_id, (void*) &bitstream,
			VX_READ_ONLY, VX_MEMORY_TYPE_HOST, 0);
	APP_ASSERT(status==VX_SUCCESS);
    if((bitstream != NULL) && (info->mem))
        memcpy(info->mem,bitstream,bitstream_size);
    else
        APP_ASSERT(1);
	info->valid = 1;
	info->datalen = bitstream_size;
	vxUnmapUserDataObject(encodeObj->bitstream_obj, map_id);
    PostImageNv12Output(gAppObj.imgMosaicObj[channel].output_image[0], channel);
	return(status);
}


static vx_status encode_resource_init(AppObj *obj)
{
    vx_status ret = VX_SUCCESS;
    uint8_t channel = 0;

    for(channel = 0; channel < NUM_ENCODE_CHANNEL; channel++)
    {
	    for(int i = 0;i < WR_QUEUE_LEN; i++)
	    {
            gStream_info[channel].mem = (char *)malloc(3*1024*1024);	
            gStream_info[channel].valid = 0;
            gStream_info[channel].datalen = 0;
	    }
        
	    if(ret != 0)
	    {
            APP_PRINTF("write output thread failed\n");
            return ret;
	    }
    }
    for(int channel = 0; channel < NUM_CAPT_CHANNELS; channel++)
    {
        Nv12OutBufMem[channel].Luma_ptr = (uint8_t *)malloc(3*1024*1024);
        Nv12OutBufMem[channel].Cbcr_ptr = (uint8_t *)malloc(3*1024*1024);
    }
    return ret;
}

static void show_graph_attributes(vx_graph graph)
{
     vx_uint32 num_nodes=0, num_params=0, ref_count=0;
     vx_enum state=0;
     vx_perf_t perf={0};
     vx_char *ref_name=NULL;
     char ref_name_invalid[MAX_ATTRIBUTE_NAME];
     char state_name[MAX_ATTRIBUTE_NAME];
 
     vxQueryGraph(graph, (vx_enum)VX_GRAPH_NUMNODES, &num_nodes, sizeof(vx_uint32));
     vxQueryGraph(graph, (vx_enum)VX_GRAPH_NUMPARAMETERS, &num_params, sizeof(vx_uint32));
     vxQueryGraph(graph, (vx_enum)VX_GRAPH_STATE, &state, sizeof(vx_enum));
     vxQueryGraph(graph, (vx_enum)VX_GRAPH_PERFORMANCE, &perf, sizeof(vx_perf_t));
     vxQueryReference((vx_reference)graph, (vx_enum)VX_REFERENCE_NAME, &ref_name, sizeof(vx_char*));
     vxQueryReference((vx_reference)graph, (vx_enum)VX_REFERENCE_COUNT, &ref_count, sizeof(vx_uint32));
 
     switch(state)
     {
         case (vx_enum)VX_GRAPH_STATE_UNVERIFIED:
             strncpy(state_name, "VX_GRAPH_STATE_UNVERIFIED", MAX_ATTRIBUTE_NAME);
             break;
         case (vx_enum)VX_GRAPH_STATE_VERIFIED:
             strncpy(state_name, "VX_GRAPH_STATE_VERIFIED", MAX_ATTRIBUTE_NAME);
             break;
         case (vx_enum)VX_GRAPH_STATE_RUNNING:
             strncpy(state_name, "VX_GRAPH_STATE_RUNNING", MAX_ATTRIBUTE_NAME);
             break;
         case (vx_enum)VX_GRAPH_STATE_ABANDONED:
             strncpy(state_name, "VX_GRAPH_STATE_ABANDONED", MAX_ATTRIBUTE_NAME);
             break;
         case (vx_enum)VX_GRAPH_STATE_COMPLETED:
             strncpy(state_name, "VX_GRAPH_STATE_COMPLETED", MAX_ATTRIBUTE_NAME);
             break;
         default:
             strncpy(state_name, "VX_GRAPH_STATE_UNKNOWN", MAX_ATTRIBUTE_NAME);
             break;
     }
 
     if(ref_name==NULL)
     {
         strncpy(ref_name_invalid, "INVALID_REF_NAME", MAX_ATTRIBUTE_NAME);
         ref_name = &ref_name_invalid[0];
     }
 
     printf(" VX_TYPE_GRAPH: %s, %d nodes, %s, avg perf %9.6fs, %d parameters, %d refs,ref name %s\n",
         ref_name,
         num_nodes,
         state_name,
         perf.avg/1000000000.0,
         num_params,
         ref_count,
	 ref_name
         );
 }
 
static void show_node_attributes(vx_node node)
{
    vx_uint32 num_params=0, ref_count=0;
    vx_status status=(vx_status)VX_FAILURE;
    vx_perf_t perf={0};
    vx_char *ref_name=NULL;
    char ref_name_invalid[MAX_ATTRIBUTE_NAME];
    char status_name[MAX_ATTRIBUTE_NAME];

    vxQueryNode(node, (vx_enum)VX_NODE_STATUS, &status, sizeof(vx_status));
    vxQueryNode(node, (vx_enum)VX_NODE_PARAMETERS, &num_params, sizeof(vx_uint32));
    vxQueryNode(node, (vx_enum)VX_NODE_PERFORMANCE, &perf, sizeof(vx_perf_t));
    vxQueryReference((vx_reference)node, (vx_enum)VX_REFERENCE_NAME, &ref_name, sizeof(vx_char*));
    vxQueryReference((vx_reference)node, (vx_enum)VX_REFERENCE_COUNT, &ref_count, sizeof(vx_uint32));

    switch(status)
    {
        case (vx_status)VX_SUCCESS:
            strncpy(status_name, "VX_SUCCESS", MAX_ATTRIBUTE_NAME);
            break;
        case (vx_status)VX_FAILURE:
            strncpy(status_name, "VX_FAILURE", MAX_ATTRIBUTE_NAME);
            break;
        default:
            strncpy(status_name, "VX_FAILURE_OTHER", MAX_ATTRIBUTE_NAME);
            break;
    }

    if(ref_name==NULL)
    {
        strncpy(ref_name_invalid, "INVALID_REF_NAME", MAX_ATTRIBUTE_NAME);
        ref_name = &ref_name_invalid[0];
    }

    printf(" VX_TYPE_NODE: %s, %d params, avg perf %9.6fs, %s, %d refs\n",
        ref_name,
        num_params,
        perf.avg/1000000000.0,
        status_name,
        ref_count
        );
}


vx_status app_stream_init()
{
    vx_status status = VX_SUCCESS;
    AppObj *obj = &gAppObj;

    /*Optional parameter setting*/
    app_default_param_set(obj);

    /* Querry sensor parameters */
    app_querry_sensor(&obj->sensorObj);

    /*Update of parameters are config file read*/
    app_update_param_set(obj);

    status = app_init(obj);

    if(status == VX_SUCCESS)
    {
        APP_PRINTF("App Init Done! \n");

        status = app_create_graph(obj);

        if(status == VX_SUCCESS)
        {
            APP_PRINTF("App Create Graph Done! \n");
            status = app_verify_graph(obj);
        }
    }

    if(status == VX_SUCCESS)
    {
        encode_resource_init(obj);
    }
    return status;
}

vx_status app_stream_run()
{
    vx_status status = VX_SUCCESS;
    AppObj *obj = &gAppObj;

    status = app_run_graph(obj);

    return status;
}

vx_status app_stream_stop()
{
    vx_status status = VX_SUCCESS;
    AppObj *obj = &gAppObj; 

    status = appStopImageSensor(obj->sensorObj.sensor_name, ((1 << obj->sensorObj.num_cameras_enabled) - 1));

    return status;
}

void app_stream_deinit()
{
    AppObj *obj = &gAppObj;

    app_delete_graph(obj);

    APP_PRINTF("App Delete Graph Done! \n");

    app_deinit(obj);

    APP_PRINTF("App De-init Done! \n");

}

vx_status app_get_streambuf(EncodeStreamInfo *info, uint8_t channel)
{
    vx_status status = VX_SUCCESS;
    if(info != NULL && channel < NUM_ENCODE_CHANNEL)
    {
        info->mem = gStream_info[channel].mem;
        info->valid = gStream_info[channel].valid;
        info->datalen = gStream_info[channel].datalen;
    }
    else
        return VX_FAILURE;

    return status;
}

vx_status app_get_nv12buf(Nv12OutBuf *buf, uint8_t channel)
{
    vx_status status = VX_SUCCESS;

    if(buf != NULL  && channel < NUM_ENCODE_CHANNEL)
    {
        buf->Cbcr_ptr = Nv12OutBufMem[channel].Cbcr_ptr;
        buf->Cbcr_size = Nv12OutBufMem[channel].Cbcr_size;
        buf->Luma_ptr = Nv12OutBufMem[channel].Luma_ptr;
        buf->Luma_size = Nv12OutBufMem[channel].Luma_size;
    }
    else
        return VX_FAILURE;

    return status;
}

static vx_status app_init(AppObj *obj)
{
    vx_status status = VX_SUCCESS;
    vx_char encode_nod_name[4][12] = {"encode_obj_0","encode_obj_1","encode_obj_2","encode_obj_3"};
    /* Create OpenVx Context */
    obj->context = vxCreateContext();
    APP_ASSERT_VALID_REF(obj->context);
    APP_PRINTF("Creating context done!\n");

    tivxHwaLoadKernels(obj->context);
    tivxImagingLoadKernels(obj->context);
    tivxFileIOLoadKernels(obj->context);
    APP_PRINTF("Kernel loading done!\n");

    /* Initialize modules */

    app_init_capture(obj->context, &obj->captureObj, &obj->sensorObj, "capture_obj", APP_BUFFER_Q_DEPTH);
    APP_PRINTF("Capture init done!\n");
 
    //app_init_img_convert(obj->context,&obj->imgConvertObj,&obj->sensorObj,APP_BUFFER_Q_DEPTH);
    if(NUM_CAPT_CHANNELS == 4)
        app_init_img_convert(obj->context,&obj->imgConvertObj,&obj->sensorObj,APP_BUFFER_Q_DEPTH);
    else if(NUM_CAPT_CHANNELS == 1)
        app_init_img_convert(obj->context,&obj->imgConvertObj,&obj->sensorObj,1);
    APP_PRINTF("convert init done!\n");

    for(int i = 0; i < NUM_ENCODE_CHANNEL; i++)
        app_init_img_mosaic(obj->context, &obj->imgMosaicObj[i], "img_mosaic_obj", 1); 
    APP_PRINTF("Img Mosaic init done!\n");

    for(int i = 0; i < NUM_ENCODE_CHANNEL; i++) 
    	app_init_encode(obj->context, &obj->encodeObj[i], encode_nod_name[i]);
    APP_PRINTF("Encode init done!\n");

    appPerfPointSetName(&obj->total_perf , "TOTAL");
    appPerfPointSetName(&obj->fileio_perf, "FILEIO");
    appPerfPointSetName(&obj->encode_deq_perf, "DEQUEUE");
    appPerfPointSetName(&obj->query_perf, "QUERY");

    return status;
}

static void app_deinit(AppObj *obj)
{
    vx_uint8 i;

    app_deinit_sensor(&obj->sensorObj);
    APP_PRINTF("Sensor deinit done!\n");

    app_deinit_capture(&obj->captureObj, APP_BUFFER_Q_DEPTH);
    APP_PRINTF("Capture deinit done!\n");

    if(NUM_CAPT_CHANNELS == 4)
        app_deinit_img_convert(&obj->imgConvertObj,APP_BUFFER_Q_DEPTH);
    else if(NUM_CAPT_CHANNELS == 1)
        app_deinit_img_convert(&obj->imgConvertObj,1);
    APP_PRINTF("Img Convert deinit done!\n");

    for(int i = 0;i < NUM_ENCODE_CHANNEL; i++)
        app_deinit_img_mosaic(&obj->imgMosaicObj[i],1);
    APP_PRINTF("Img Mosaic deinit done\n");

    app_deinit_resource();

    for(i = 0; i < NUM_ENCODE_CHANNEL; i++)
    	app_deinit_encode(&obj->encodeObj[i]);
    APP_PRINTF("Encode deinit done!\n");

    tivxHwaUnLoadKernels(obj->context);
    tivxImagingUnLoadKernels(obj->context);
    tivxFileIOUnLoadKernels(obj->context);
    APP_PRINTF("Kernels unload done!\n");

    vxReleaseContext(&obj->context);
    APP_PRINTF("Release context done!\n");
}

static void app_delete_graph(AppObj *obj)
{
    vx_uint8 i;   

    app_delete_capture(&obj->captureObj);
    APP_PRINTF("Capture delete done!\n");

    app_delete_img_convert(&obj->imgConvertObj);
    APP_PRINTF("Convert delet done!\n");

    for(i = 0; i < NUM_ENCODE_CHANNEL; i++)
        app_delete_img_mosaic(&obj->imgMosaicObj[i]);
    APP_PRINTF("Mosaic delete done!\n");

    for(i = 0; i < NUM_ENCODE_CHANNEL; i++)
    	app_delete_encode(&obj->encodeObj[i]);
    APP_PRINTF("Encode delete done!\n");

    vxReleaseGraph(&obj->graph);
    vxReleaseGraph(&obj->encode_graph);
    APP_PRINTF("Graph delete done!\n");
}

static vx_status app_create_graph(AppObj *obj)
{
    vx_status status = VX_SUCCESS;
    vx_graph_parameter_queue_params_t graph_parameters_queue_params_list[6];
    vx_int32 graph_parameter_index;

    obj->graph = vxCreateGraph(obj->context);
    obj->encode_graph = vxCreateGraph(obj->context);
    status = vxGetStatus((vx_reference)obj->encode_graph);
    if(status != VX_SUCCESS)
        printf("create encode graph failed!\n");
    vxSetReferenceName((vx_reference)obj->encode_graph, "app_encode_graph");
    status = vxGetStatus((vx_reference)obj->graph);
    vxSetReferenceName((vx_reference)obj->graph, "app_cap_graph");
    APP_PRINTF("Graph create done!\n");

    if(status == VX_SUCCESS)
    {
        status = app_create_graph_capture(obj->graph, &obj->captureObj);
        APP_PRINTF("Capture graph done!\n");
    }
      
    if(status == VX_SUCCESS)
    {
        status = app_create_graph_img_convert(obj->graph,&obj->imgConvertObj,obj->captureObj.raw_image_arr[0],"color_convert");
    	APP_PRINTF("Convert graph done!\n");
    }

    if(status == VX_SUCCESS)
    {
        for(int i = 0; i < NUM_ENCODE_CHANNEL; i++)
        {
            obj->imgMosaicObj[i].input_arr[0] = obj->imgConvertObj.output_arr[0];
            obj->imgMosaicObj[i].num_inputs = 1;
            status = app_create_graph_img_mosaic(obj->graph, &obj->imgMosaicObj[i]);
        }       
    }
    APP_PRINTF("create mosaic graph done\n");

    if(status == VX_SUCCESS)
    {
          for(vx_uint8 i = 0;i < NUM_ENCODE_CHANNEL; i++)
          { 
            status = app_create_graph_encode(obj->encode_graph, &obj->encodeObj[i], obj->imgMosaicObj[i].output_image[0], 0);
          }
          
          APP_PRINTF("Encode graph done!\n");
    }
    if(status == VX_SUCCESS)
    {
        graph_parameter_index = 0;
        add_graph_parameter_by_node_index(obj->graph, obj->captureObj.node, 1);
        obj->captureObj.graph_parameter_index = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].graph_parameter_index = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list_size = APP_BUFFER_Q_DEPTH;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list = (vx_reference*)&obj->captureObj.raw_image_arr[0];
        graph_parameter_index++;


        obj->en_out_img_write = 0;
        for(int i = 0;i < NUM_ENCODE_CHANNEL; i++)
        {
            if (obj->en_out_img_write == 1)
            {
                add_graph_parameter_by_node_index(obj->graph, obj->imgMosaicObj[i].node, 1);
                obj->imgMosaicObj[i].graph_parameter_index = graph_parameter_index;
                graph_parameters_queue_params_list[graph_parameter_index].graph_parameter_index = graph_parameter_index;
                graph_parameters_queue_params_list[graph_parameter_index].refs_list_size = APP_BUFFER_Q_DEPTH;
                graph_parameters_queue_params_list[graph_parameter_index].refs_list = (vx_reference*)&obj->imgMosaicObj[i].output_image[0];
                graph_parameter_index++;
            }
        }

        vxSetGraphScheduleConfig(obj->graph,
                VX_GRAPH_SCHEDULE_MODE_QUEUE_AUTO,
                graph_parameter_index,
                graph_parameters_queue_params_list);   

        if(NUM_ENCODE_CHANNEL == 4)
            tivxSetNodeParameterNumBufByIndex(obj->imgConvertObj.node, 1, APP_BUFFER_Q_DEPTH);
        else if(NUM_ENCODE_CHANNEL == 1)
            tivxSetNodeParameterNumBufByIndex(obj->imgConvertObj.node, 1, 1);

        for(int i = 0; i < NUM_ENCODE_CHANNEL; i++)
        tivxSetNodeParameterNumBufByIndex(obj->imgMosaicObj[i].node, 1, 1);
        tivxSetGraphPipelineDepth(obj->graph, 7);
    }
    show_graph_attributes(obj->graph);
    show_node_attributes(obj->imgConvertObj.node);
    show_node_attributes(obj->captureObj.node);
    for(int i = 0; i <  NUM_ENCODE_CHANNEL; i++)
        show_node_attributes(obj->imgMosaicObj[i].node);
    show_node_attributes(obj->encodeObj[0].node);
    show_graph_attributes(obj->encode_graph);
    return status;
}

static vx_status app_verify_graph(AppObj *obj)
{
    vx_status status = VX_SUCCESS;

    status = vxVerifyGraph(obj->graph);
    status = vxVerifyGraph(obj->encode_graph);

    if(status == VX_SUCCESS)
    {
        APP_PRINTF("Grapy verify done!\n");
    }

    if(VX_SUCCESS == status)
    {
      status = tivxExportGraphToDot(obj->graph,".", "vx_app_encode");
    }

    /* wait a while for prints to flush */
    tivxTaskWaitMsecs(100);

    return status;
}

static vx_status app_display_init(AppObj *obj)
{
	vx_status status;
	tivx_display_params_t display_params;
	vx_user_data_object display_param_obj;
    vx_node displayNode = 0;
    vx_image sample_image;

    memset(&display_params, 0, sizeof(tivx_display_params_t));
    display_params.opMode=TIVX_KERNEL_DISPLAY_ZERO_BUFFER_COPY_MODE;
    display_params.pipeId=2;
    display_params.outWidth=1920;
    display_params.outHeight=1080;
    display_params.posX=0;
    display_params.posY=0;

    display_param_obj = vxCreateUserDataObject(obj->context, "tivx_display_params_t", sizeof(tivx_display_params_t), &display_params);
    //sample_image = (vx_image) vxGetObjectArrayItem(obj->captureObj.raw_image_arr[0],2);
    sample_image = (vx_image) vxGetObjectArrayItem(obj->imgConvertObj.output_arr[0],0);

    displayNode = tivxDisplayNode(obj->graph, display_param_obj, sample_image); 
    //displayNode = tivxDisplayNode(obj->graph, display_param_obj, roi_img[3]); 
    //vxReleaseImage(&sample_image);

    //displayNode = tivxDisplayNode(obj->graph, display_param_obj, obj->imgMosaicObj.output_image[0]);
    vxSetNodeTarget(displayNode, VX_TARGET_STRING, TIVX_TARGET_DISPLAY1);
    vxSetReferenceName((vx_reference)displayNode,"display_node");    
    /* Create User Data object for channel switching */
    status = vxGetStatus((vx_reference)displayNode);

	return status;
}


static vx_status app_run_graph_for_one_frame_pipeline(AppObj *obj, vx_int32 frame_id)
{
	vx_status status = VX_SUCCESS;
    vx_uint8 i = 0;

	appPerfPointBegin(&obj->total_perf);

	CaptureObj *captureObj = &obj->captureObj;
	EncodeObj  *encodeObj;
	if(obj->pipeline < 0)
	{
		/* Enqueue outputs */
		if (obj->en_out_img_write == 1)
		{
            for(int i = 0;i < NUM_ENCODE_CHANNEL; i++)
			vxGraphParameterEnqueueReadyRef(obj->graph, obj->imgMosaicObj[i].graph_parameter_index, (vx_reference*)&obj->imgMosaicObj[i].output_image[obj->enqueueCnt], 1);
		}

    	/* Enqueue inputs during pipeup dont execute */
		vxGraphParameterEnqueueReadyRef(obj->graph, captureObj->graph_parameter_index, (vx_reference*)&obj->captureObj.raw_image_arr[obj->enqueueCnt], 1);
		obj->enqueueCnt++;
		obj->enqueueCnt   = (obj->enqueueCnt  >= APP_BUFFER_Q_DEPTH)? 0 : obj->enqueueCnt;
		obj->pipeline++;
	}

	if(obj->pipeline == 0)
	{
		if (obj->en_out_img_write == 1)
		{
            for(int i = 0; i < NUM_ENCODE_CHANNEL; i++)
			vxGraphParameterEnqueueReadyRef(obj->graph, obj->imgMosaicObj[i].graph_parameter_index, (vx_reference*)&obj->imgMosaicObj[i].output_image[obj->enqueueCnt], 1);
		}

		/* Execute 1st frame */
		vxGraphParameterEnqueueReadyRef(obj->graph, captureObj->graph_parameter_index, (vx_reference*)&obj->captureObj.raw_image_arr[obj->enqueueCnt], 1);

		obj->enqueueCnt++;
		obj->enqueueCnt   = (obj->enqueueCnt  >= APP_BUFFER_Q_DEPTH)? 0 : obj->enqueueCnt;
		obj->pipeline++;
	}

	if(obj->pipeline > 0)
	{
		vx_image capture_input_image;
		uint32_t num_refs;
		/* Dequeue input */
        vxGraphParameterDequeueDoneRef(obj->graph, captureObj->graph_parameter_index, (vx_reference*)&capture_input_image, 1, &num_refs);
        if(obj->en_out_img_write == 1)
        {
            for(i = 0;i < NUM_ENCODE_CHANNEL; i++)
            {
                /* Dequeue output */
                vxGraphParameterDequeueDoneRef(obj->graph, obj->imgMosaicObj[i].graph_parameter_index, (vx_reference*)&mosaic_output_image, 1, &num_refs);
                /* Enqueue output */
                vxGraphParameterEnqueueReadyRef(obj->graph, obj->imgMosaicObj[i].graph_parameter_index, (vx_reference*)&mosaic_output_image, 1);
            }
        }
        
        usleep(35000);
        vxProcessGraph(obj->encode_graph);
		for(i = 0; i < NUM_ENCODE_CHANNEL; i++)
		{
			encodeObj = &obj->encodeObj[i];
			/* Dequeue Bitstream Object */
            PostEncodeOutput(encodeObj, &gStream_info[i], i);
		}

		/* Enqueue input - start execution */
		vxGraphParameterEnqueueReadyRef(obj->graph, captureObj->graph_parameter_index, (vx_reference*)&capture_input_image, 1);

		obj->enqueueCnt++;
		obj->dequeueCnt++;

		obj->enqueueCnt = (obj->enqueueCnt >= APP_BUFFER_Q_DEPTH)? 0 : obj->enqueueCnt;
		obj->dequeueCnt = (obj->dequeueCnt >= APP_BUFFER_Q_DEPTH)? 0 : obj->dequeueCnt;
	}

	appPerfPointEnd(&obj->total_perf);

	return status;
}

static vx_status app_run_graph(AppObj *obj)
{
    vx_status status = VX_SUCCESS;
    SensorObj *sensorObj = &obj->sensorObj;

    if(init_param == 0x00)
    {
        app_pipeline_params_defaults(obj);

        if(NULL == sensorObj->sensor_name)
        {
            printf("sensor name is NULL \n");
            return VX_FAILURE;
        }
        app_init_sensor(&obj->sensorObj, SENSOR_CONFIG);
        for(int i = 0;i < APP_BUFFER_Q_DEPTH; i++)
        {
            app_run_graph_for_one_frame_pipeline(obj, 0);
        }
        init_param = 0x01;
    }
 
    app_run_graph_for_one_frame_pipeline(obj, 0);

    return status;
}

static void app_pipeline_params_defaults(AppObj *obj)
{
  obj->pipeline       = -APP_BUFFER_Q_DEPTH + 1;
  obj->enqueueCnt     = 0;
  obj->dequeueCnt     = 0;
}


static void set_sensor_defaults(SensorObj *sensorObj)
{
    strcpy(sensorObj->sensor_name, SENSOR_SONY_IMX390_UB953);
    //strcpy(sensorObj->sensor_name, SENSOR_OMNIVISON_OX01F10_MAX9286);
    sensorObj->num_sensors_found = 0;
    sensorObj->sensor_features_enabled = 0;
    sensorObj->sensor_features_supported = 0;
    sensorObj->sensor_dcc_enabled = 0;
    sensorObj->sensor_wdr_enabled = 0;
    sensorObj->sensor_exp_control_enabled = 0;
    sensorObj->sensor_gain_control_enabled = 0;
}

static void app_default_param_set(AppObj *obj)
{
    set_sensor_defaults(&obj->sensorObj);

    obj->write_file = 0;
    obj->sensorObj.enable_ldc = 0;
    obj->sensorObj.num_cameras_enabled = 1;
    obj->sensorObj.usecase_option = APP_SENSOR_FEATURE_CFG_UC0;
}

static void set_img_mosaic_params(ImgMosaicObj *imgMosaicObj, vx_uint32 in_width, vx_uint32 in_height, vx_int32 ch)
{

    imgMosaicObj->out_width    = CAP_IMAGE_WIDTH * 1;
    imgMosaicObj->out_height   = CAP_IMAGE_HEIGHT * 1;
    imgMosaicObj->num_inputs   = 1;

    imgMosaicObj->params.windows[0].startX  = 0;
    imgMosaicObj->params.windows[0].startY  = 0;
    imgMosaicObj->params.windows[0].width   = in_width;
    imgMosaicObj->params.windows[0].height  = in_height;
    imgMosaicObj->params.windows[0].input_select   = 0;
    imgMosaicObj->params.windows[0].channel_select = ch;

    imgMosaicObj->params.num_windows  = 1;

    /* Number of time to clear the output buffer before it gets reused */
    imgMosaicObj->params.clear_count  = 1;
    imgMosaicObj->params.enable_overlay = 0;
}

static void set_encode_params(AppObj *obj)
{
	for(int i = 0; i < NUM_ENCODE_CHANNEL; i++)
	{
	    obj->encodeObj[i].inWidth =  obj->sensorObj.image_width * 1;
	    obj->encodeObj[i].inHeight = obj->sensorObj.image_height * 1;
	}
}

static void app_update_param_set(AppObj *obj)
{

    vx_uint16 resized_width, resized_height;
    appIssGetResizeParams(obj->sensorObj.image_width, obj->sensorObj.image_height, DISPLAY_WIDTH, DISPLAY_HEIGHT, &resized_width, &resized_height);
    for(int i = 0; i < NUM_ENCODE_CHANNEL; i++)
        set_img_mosaic_params(&obj->imgMosaicObj[i], resized_width, resized_height, i);
    set_encode_params(obj);
}

/*
 * Utility API used to add a graph parameter from a node, node parameter index
 */
static void add_graph_parameter_by_node_index(vx_graph graph, vx_node node, vx_uint32 node_parameter_index)
{
    vx_parameter parameter = vxGetParameterByIndex(node, node_parameter_index);

    vxAddParameterToGraph(graph, parameter);
    vxReleaseParameter(&parameter);
}



