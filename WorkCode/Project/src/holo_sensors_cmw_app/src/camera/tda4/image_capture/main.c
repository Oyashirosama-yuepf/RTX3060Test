/*
 *
 * Copyright (c) 2020 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <utils/draw2d/include/draw2d.h>
#include <utils/perf_stats/include/app_perf_stats.h>
#include <utils/console_io/include/app_get.h>
#include <utils/grpx/include/app_grpx.h>
#include <VX/vx_khr_pipelining.h>

#include <app_common.h>
#include <app_sensor_module.h>
#include <app_capture_module.h>
#include <app_img_mosaic_module.h>

#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

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

#define SENSOR_CONFIG        (0x03)
#define SENSOR_STREAM_ON     (0x04)
#define SENSOR_STREAM_OFF    (0x05)

typedef struct {

    SensorObj     sensorObj;
    CaptureObj    captureObj;
    ImgMosaicObj  imgMosaicObj;

    vx_char output_file_path[APP_MAX_FILE_PATH];

    /* OpenVX references */
    vx_context context;
    vx_graph   graph;

    vx_int32 en_out_img_write;

    vx_uint32 num_frames_to_run;

    vx_uint32 num_frames_to_write;
    vx_uint32 num_frames_to_skip;

    tivx_task task;
    vx_uint32 stop_task;
    vx_uint32 stop_task_done;

    app_perf_point_t total_perf;
    app_perf_point_t fileio_perf;

    int32_t pipeline;

    int32_t enqueueCnt;
    int32_t dequeueCnt;

    int32_t write_file;

} AppObj;

typedef struct{
	vx_uint8 *Luma_ptr;
	vx_uint32 Luma_size;
	vx_uint8 *Cbcr_ptr;
	vx_uint32 Cbcr_size;
}NV12OutImg;

AppObj gAppObj;
NV12OutImg NV12OutImgMem[NUM_CAPT_CHANNELS];
sem_t img_sem;

static vx_object_array convert_output_arr[APP_BUFFER_Q_DEPTH];
static vx_image nv12_output_image[4];
static vx_int32 convert_graph_index = 0;
static vx_node node_convert;

static void app_parse_cmd_line_args(AppObj *obj, vx_int32 argc, vx_char *argv[]);
static vx_status app_init(AppObj *obj);
static void app_deinit(AppObj *obj);
static vx_status app_create_graph(AppObj *obj);
static vx_status app_verify_graph(AppObj *obj);
static vx_status app_run_graph(AppObj *obj);
static vx_status app_run_graph_interactive(AppObj *obj);
static void app_delete_graph(AppObj *obj);
static void app_update_param_set(AppObj *obj);
static void app_pipeline_params_defaults(AppObj *obj);
static void add_graph_parameter_by_node_index(vx_graph graph, vx_node node, vx_uint32 node_parameter_index);
static vx_int32 calc_grid_size(vx_uint32 ch);
static void set_img_mosaic_params(ImgMosaicObj *imgMosaicObj, vx_uint32 in_width, vx_uint32 in_height, vx_int32 numCh);
static void set_encode_params(AppObj *obj);
static vx_status app_display_init(AppObj *obj);

void test_cap();

static void app_show_usage(vx_int32 argc, vx_char* argv[])
{
    printf("\n");
    printf(" Camera Demo - (c) Texas Instruments 2020\n");
    printf(" ========================================================\n");
    printf("\n");
    printf(" Usage,\n");
    printf("  %s --cfg <config file>\n", argv[0]);
    printf("\n");
}

static char menu[] = {
    "\n"
    "\n ========================="
    "\n Demo : Camera Demo"
    "\n ========================="
    "\n"
    "\n s: Save CSIx, VISS and LDC outputs"
    "\n"
    "\n p: Print performance statistics"
    "\n"
    "\n x: Exit"
    "\n"
    "\n Enter Choice: "
};

static void app_run_task(void *app_var)
{
    AppObj *obj = (AppObj *)app_var;

    while(!obj->stop_task)
    {
        app_run_graph(obj);
    }
    obj->stop_task_done = 1;
}

static int32_t app_run_task_create(AppObj *obj)
{
    tivx_task_create_params_t params;
    int32_t status;

    tivxTaskSetDefaultCreateParams(&params);
    params.task_main = app_run_task;
    params.app_var = obj;

    obj->stop_task_done = 0;
    obj->stop_task = 0;

    status = tivxTaskCreate(&obj->task, &params);

    return status;
}

static void app_run_task_delete(AppObj *obj)
{
    while(obj->stop_task_done==0)
    {
         tivxTaskWaitMsecs(100);
    }

    tivxTaskDelete(&obj->task);
}

static vx_status app_get_graph_perf(AppObj *obj)
{
    vx_status status;
    uint32_t done = 0;

    char ch;
    appPerfStatsResetAll();
    while(!done)
    {
        printf(menu);
        ch = getchar();
        printf("\n");

        switch(ch)
        {
            case 'p':
                appPerfStatsPrintAll();
                tivx_utils_graph_perf_print(obj->graph);
                appPerfPointPrint(&obj->fileio_perf);
                appPerfPointPrint(&obj->total_perf);
                printf("\n");
                appPerfPointPrintFPS(&obj->total_perf);
                printf("\n");
                break;
          case 'x':
                obj->stop_task = 1;
                done = 1;
                break;
        }
    }
    return status;
}

vx_status PostEncodeOutput(vx_image *out_img)
{
  	vx_status status;
	for(vx_uint8 i=0; i < NUM_CAPT_CHANNELS; i++)
  	{
	      if(out_img[i] != nv12_output_image[i])
			APP_PRINTF("ERROR -----\n");
		  status = vxGetStatus((vx_reference)out_img[i]);

		  if(status == VX_SUCCESS)
		  {
			  vx_rectangle_t rect;
			  vx_imagepatch_addressing_t image_addr;
			  vx_map_id map_id;
			  void * data_ptr;
			  vx_uint32  img_width;
			  vx_uint32  img_height;

			  vxQueryImage(out_img[i], VX_IMAGE_WIDTH, &img_width, sizeof(vx_uint32));
			  vxQueryImage(out_img[i], VX_IMAGE_HEIGHT, &img_height, sizeof(vx_uint32));

			  rect.start_x = 0;
			  rect.start_y = 0;
			  rect.end_x = img_width;
			  rect.end_y = img_height;

			  status = vxMapImagePatch(out_img[i],&rect,0,&map_id,&image_addr,&data_ptr,VX_READ_ONLY,VX_MEMORY_TYPE_HOST,VX_NOGAP_X);
			  if(status == VX_SUCCESS)
			  {
			  	NV12OutImgMem[i].Luma_size = img_width * img_height;
			  	memcpy(NV12OutImgMem[i].Luma_ptr,data_ptr,NV12OutImgMem[i].Luma_size);
			  	vxUnmapImagePatch(out_img[i], map_id);
			  }
			  else
				return VX_FAILURE;
			  status = vxMapImagePatch(out_img[i], &rect,1,&map_id,&image_addr,&data_ptr,VX_READ_ONLY,VX_MEMORY_TYPE_HOST,VX_NOGAP_X);
			  if(status == VX_SUCCESS)
			  {
			  	NV12OutImgMem[i].Cbcr_size = img_width*img_height/2;
			  	memcpy(NV12OutImgMem[i].Cbcr_ptr,data_ptr,NV12OutImgMem[i].Cbcr_size);
			  	vxUnmapImagePatch(out_img[i], map_id);
			  }
			  else
				return VX_FAILURE;
			}
			else
				return VX_FAILURE;
	}
    sem_post(&img_sem);
    return(status);
}
void (*pcallback)(uint8_t, const NV12OutImg*) = NULL;
static void * writeoutput_thread()
{
  size_t write_size = 0;
  FILE *fp;

  static uint32_t cnt = 0;
  while(1)
  {
        sem_wait(&img_sem);
        if (pcallback)
        {
            for (uint32_t i = 0; i < NUM_CAPT_CHANNELS; ++i)
            {
                pcallback(i, &NV12OutImgMem[i]);
            }
        }
        // if(cnt == 200)
        // {
        //     fp = fopen("/root/cap/output_mosic_img.yuv", "wb");
        //     write_size = fwrite(NV12OutImgMem[0].Luma_ptr,1,NV12OutImgMem[0].Luma_size, fp);

        //     if(write_size != NV12OutImgMem[0].Luma_size)
        //         printf("Luma bytes written = %d, expected = %d", write_size, NV12OutImgMem[0].Luma_size);
        //     write_size = fwrite(NV12OutImgMem[0].Cbcr_ptr,1,NV12OutImgMem[0].Cbcr_size, fp);
        //     if(write_size != NV12OutImgMem[0].Cbcr_size)
        //         printf("CbCr bytes written = %d, expected = %d", write_size, NV12OutImgMem[0].Luma_size);
        //     fclose(fp);
        // }
        cnt++;
  } 
  return NULL;
}


static vx_status WriteOutput_thread_init()
{
    vx_status ret = VX_SUCCESS;
    pthread_t pid; 
    ret = sem_init(&img_sem,0,0);
    if(ret == -1)
    {
        APP_PRINTF("sem init failed\n");
        return ret;
    }
	for(vx_uint8 i = 0; i < NUM_CAPT_CHANNELS; i++)
	{
    	NV12OutImgMem[i].Luma_ptr = (vx_uint8 *)malloc(CAP_IMG_WIDTH*CAP_IMG_HEIGHT);
    	NV12OutImgMem[i].Cbcr_ptr = (vx_uint8 *)malloc(CAP_IMG_WIDTH*CAP_IMG_HEIGHT/2);
	}
    ret = pthread_create(&pid,NULL,writeoutput_thread,NULL);
    if(ret != 0)
    {
        APP_PRINTF("write output thread failed\n");
        return ret;
    }
    usleep(10);
    return ret;
}


static void * getperf_thread(AppObj *obj)
{
	while(1)
	{
	   app_get_graph_perf(obj);
	}
	return NULL;
}

static vx_status getperf_thread_init(AppObj *obj)
{
    vx_status ret = VX_SUCCESS;
    //pthread_create(&pid,NULL,getperf_thread,obj);
    APP_PRINTF("getperf thread create success\n");
    return ret;
}

void show_graph_attributes(vx_graph graph)
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
 
 void show_node_attributes(vx_node node)
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
void app_stop_graph()
{
	AppObj *obj = &gAppObj;
	obj->stop_task = 1;
}

vx_int32 app_encode_main(vx_int32 argc, vx_char* argv[])
{
    vx_status status = VX_SUCCESS;
    AppObj *obj = &gAppObj;
  
	signal(SIGINT,app_stop_graph);  
//    test_cap();
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
//app_display_init(obj);
            status = app_verify_graph(obj);
			WriteOutput_thread_init();
            if(status == VX_SUCCESS)
            {
                APP_PRINTF("App Verify Graph Done! \n");

                if (obj->captureObj.enable_error_detection)
                {
                  APP_PRINTF("App Error Frame deteced! \n");
                  status = app_send_error_frame(obj->context, &obj->captureObj, &obj->sensorObj);
                }
	
                if (status == VX_SUCCESS)
                {
                  APP_PRINTF("App Send Error Frame Done! \n");
                  app_run_graph(obj);
                }
            }
        }

        APP_PRINTF("App Run Graph Done! \n");
    }

    app_delete_graph(obj);

    APP_PRINTF("App Delete Graph Done! \n");

    app_deinit(obj);

    APP_PRINTF("App De-init Done! \n");

    return 0;
}

 
static vx_status app_init(AppObj *obj)
{
    vx_status status = VX_SUCCESS;
    /* Create OpenVx Context */
    obj->context = vxCreateContext();
    APP_ASSERT_VALID_REF(obj->context);
    APP_PRINTF("Creating context done!\n");

    tivxHwaLoadKernels(obj->context);
    tivxImagingLoadKernels(obj->context);
    tivxFileIOLoadKernels(obj->context);
    APP_PRINTF("Kernel loading done!\n");

    /* Initialize modules */

    //app_init_sensor(&obj->sensorObj, "sensor_obj");
    APP_PRINTF("Sensor init done!\n");

    app_init_capture(obj->context, &obj->captureObj, &obj->sensorObj, "capture_obj", APP_BUFFER_Q_DEPTH);
    APP_PRINTF("Capture init done!\n");
 
    appPerfPointSetName(&obj->total_perf , "TOTAL");
    appPerfPointSetName(&obj->fileio_perf, "FILEIO");

    return status;
}

void app_deinit_img_convert()
{
  vx_int32 q;

  for(q = 0; q < 4; q++)
  {
	vxReleaseObjectArray(&convert_output_arr[q]);
  }
  for(q = 0; q < 4; q++)
 	vxReleaseImage(&nv12_output_image[q]); 
  return;
}

void app_delete_img_convert()
{
  if(node_convert != NULL)
  {
    vxReleaseNode(&node_convert);
  }
  return;
}


static void app_deinit(AppObj *obj)
{

    app_deinit_sensor(&obj->sensorObj);
    APP_PRINTF("Sensor deinit done!\n");

    app_deinit_capture(&obj->captureObj, APP_BUFFER_Q_DEPTH);
    APP_PRINTF("Capture deinit done!\n");

	app_deinit_img_convert();
    APP_PRINTF("Convert deinit done!\n");

    tivxHwaUnLoadKernels(obj->context);
    tivxImagingUnLoadKernels(obj->context);
    tivxFileIOUnLoadKernels(obj->context);
    APP_PRINTF("Kernels unload done!\n");

    vxReleaseContext(&obj->context);
    APP_PRINTF("Release context done!\n");
}

static void app_delete_graph(AppObj *obj)
{

    app_delete_capture(&obj->captureObj);
    APP_PRINTF("Capture delete done!\n");

	app_delete_img_convert();
    APP_PRINTF("Convert delete done!\n");

    vxReleaseGraph(&obj->graph);
    APP_PRINTF("Graph delete done!\n");
}

static vx_status app_create_graph(AppObj *obj)
{
    vx_status status = VX_SUCCESS;
    vx_graph_parameter_queue_params_t graph_parameters_queue_params_list[3];
    vx_int32 graph_parameter_index;
    vx_image sample_img;
    vx_image img_nv12;
    vx_bool replicate[] = { vx_true_e, vx_true_e};

    obj->graph = vxCreateGraph(obj->context);
    status = vxGetStatus((vx_reference)obj->graph);
    vxSetReferenceName((vx_reference)obj->graph, "app_encode_graph");
    APP_PRINTF("Graph create done!\n");

    if(status == VX_SUCCESS)
    {
        status = app_create_graph_capture(obj->graph, &obj->captureObj);
        APP_PRINTF("Capture graph done!\n");
    }

     img_nv12 = vxCreateImage(obj->context,obj->sensorObj.image_width,obj->sensorObj.image_height,(vx_df_image)VX_DF_IMAGE_NV12);
     for(int i = 0;i < APP_BUFFER_Q_DEPTH; i++)
         convert_output_arr[i] = vxCreateObjectArray(obj->context, (vx_reference)img_nv12, obj->sensorObj.num_cameras_enabled);
     vxReleaseImage(&img_nv12);

    sample_img = (vx_image) vxGetObjectArrayItem(obj->captureObj.raw_image_arr[0],0);
    img_nv12 =  (vx_image) vxGetObjectArrayItem(convert_output_arr[0],0); 
    node_convert = vxColorConvertNode(obj->graph,sample_img,img_nv12);  
    vxSetReferenceName((vx_reference)node_convert,"colorconvert_node");    
    vxSetNodeTarget(node_convert, VX_TARGET_STRING, TIVX_TARGET_DSP2);
    vxReleaseImage(&sample_img);
    vxReleaseImage(&img_nv12);
    
    if(NUM_CAPT_CHANNELS == 4)
        vxReplicateNode(obj->graph, node_convert, replicate, 2);

    APP_PRINTF("create color convert node  done\n");
    
    for(int i = 0; i < NUM_CAPT_CHANNELS; i++)
        nv12_output_image[i] =  (vx_image) vxGetObjectArrayItem(convert_output_arr[0],i);

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
#if 0
        if (obj->en_out_img_write == 1)
        {
            add_graph_parameter_by_node_index(obj->graph, obj->imgMosaicObj.node, 1);
            obj->imgMosaicObj.graph_parameter_index = graph_parameter_index;
            graph_parameters_queue_params_list[graph_parameter_index].graph_parameter_index = graph_parameter_index;
            graph_parameters_queue_params_list[graph_parameter_index].refs_list_size = APP_BUFFER_Q_DEPTH;
            graph_parameters_queue_params_list[graph_parameter_index].refs_list = (vx_reference*)&obj->imgMosaicObj.output_image[0];
            graph_parameter_index++;
        }
#endif
 
        vxSetGraphScheduleConfig(obj->graph,
                VX_GRAPH_SCHEDULE_MODE_QUEUE_AUTO,
                graph_parameter_index,
                graph_parameters_queue_params_list);   

       tivxSetGraphPipelineDepth(obj->graph, APP_PIPELINE_DEPTH);
       tivxSetNodeParameterNumBufByIndex(node_convert, 1, APP_BUFFER_Q_DEPTH);
       APP_PRINTF("Pipeline params setup done!\n");
    }
    show_graph_attributes(obj->graph);
    show_node_attributes(node_convert);
    return status;
}

static vx_status app_verify_graph(AppObj *obj)
{
    vx_status status = VX_SUCCESS;

    status = vxVerifyGraph(obj->graph);

    if(status == VX_SUCCESS)
    {
        APP_PRINTF("Grapy verify done!\n");
    }

    #if 1
    if(VX_SUCCESS == status)
    {
      status = tivxExportGraphToDot(obj->graph,".", "vx_app_encode");
    }
    #endif

    /* wait a while for prints to flush */
    tivxTaskWaitMsecs(100);

    return status;
}

static vx_status app_display_init(AppObj *obj)
{
	vx_status status;
	tivx_display_params_t display_params;
	vx_user_data_object display_param_obj;
//	tivx_display_select_channel_params_t channel_prms;
//        vx_user_data_object switch_ch_obj;
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
        sample_image = (vx_image) vxGetObjectArrayItem(obj->captureObj.raw_image_arr[0],0);
        displayNode = tivxDisplayNode(obj->graph, display_param_obj, sample_image); 
        vxReleaseImage(&sample_image);

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
	CaptureObj *captureObj = &obj->captureObj;
	appPerfPointBegin(&obj->total_perf);
	if(obj->pipeline < 0)
	{
		/* Enqueue outputs */

		/* Enqueue inputs during pipeup dont execute */
		vxGraphParameterEnqueueReadyRef(obj->graph, captureObj->graph_parameter_index, (vx_reference*)&obj->captureObj.raw_image_arr[obj->enqueueCnt], 1);
		obj->enqueueCnt++;
		obj->enqueueCnt   = (obj->enqueueCnt  >= APP_BUFFER_Q_DEPTH)? 0 : obj->enqueueCnt;
		obj->pipeline++;
	}

	if(obj->pipeline == 0)
	{
		/* Execute 1st frame */
		vxGraphParameterEnqueueReadyRef(obj->graph, captureObj->graph_parameter_index, (vx_reference*)&obj->captureObj.raw_image_arr[obj->enqueueCnt], 1);

		obj->enqueueCnt++;
		obj->enqueueCnt   = (obj->enqueueCnt  >= APP_BUFFER_Q_DEPTH)? 0 : obj->enqueueCnt;
		obj->pipeline++;
	}

	if(obj->pipeline > 0)
	{
		vx_image capture_input_image;
		vx_image convert_output_image;
		uint32_t num_refs;
		
		/* Dequeue input */
		vxGraphParameterDequeueDoneRef(obj->graph, captureObj->graph_parameter_index, (vx_reference*)&capture_input_image, 1, &num_refs);

        /* Dequeue output */
		usleep(20000);
		PostEncodeOutput(nv12_output_image);
        /* Enqueue output */

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
    vx_int32 frame_id;

    app_pipeline_params_defaults(obj);

    if(NULL == sensorObj->sensor_name)
    {
        printf("sensor name is NULL \n");
        return VX_FAILURE;
    }
    app_init_sensor(&obj->sensorObj, SENSOR_CONFIG);
#ifdef LOOP_RECODE
while(1)
{
#else
for(int file_id = 0; file_id < ENCODE_FILE_NUM; file_id++)
{
#endif
    //for(frame_id = 0; frame_id < obj->num_frames_to_run; frame_id++)
    for(frame_id = 0; frame_id < ENCODE_FRAME_NUM; frame_id++)
    {
        app_run_graph_for_one_frame_pipeline(obj, frame_id);
		/* user asked to stop processing */
   	    if(obj->stop_task)
           break;
   	}
     
    vxWaitGraph(obj->graph);
    appPerfPointPrintFPS(&obj->total_perf);
   	if(obj->stop_task)
        break;
}
    obj->stop_task = 1;
    status = appStopImageSensor(obj->sensorObj.sensor_name, ((1 << sensorObj->num_cameras_enabled) - 1));

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
//    strcpy(sensorObj->sensor_name, SENSOR_SONY_IMX390_UB953_D3)
    strcpy(sensorObj->sensor_name, FRONT_SENOSR_NAME);
    sensorObj->num_sensors_found = 0;
    sensorObj->sensor_features_enabled = 0;
    sensorObj->sensor_features_supported = 0;
    sensorObj->sensor_dcc_enabled = 0;
    sensorObj->sensor_wdr_enabled = 0;
    sensorObj->sensor_exp_control_enabled = 0;
    sensorObj->sensor_gain_control_enabled = 0;
}
static vx_int32 calc_grid_size(vx_uint32 ch)
{
    if(0==ch)
    {
        return -1;
    }
    else if(1==ch)
    {
        return 1;
    }
    else if(4>=ch)
    {
        return 2;
    }
    else if(9>=ch)
    {
        return 3;
    }
    else if(16>=ch)
    {
        return 4;
    }else
    {
        return -1;
    }
}

static void set_img_mosaic_params(ImgMosaicObj *imgMosaicObj, vx_uint32 in_width, vx_uint32 in_height, vx_int32 numCh)
{
    vx_int32 idx, ch;
    vx_int32 grid_size = calc_grid_size(numCh);

    imgMosaicObj->out_width    = CAP_IMG_WIDTH * 2;
    imgMosaicObj->out_height   = CAP_IMG_HEIGHT * 2;
    imgMosaicObj->num_inputs   = 1;

    idx = 0;

    for(ch = 0; ch < numCh; ch++)
    {
        vx_int32 winX = ch%grid_size;
        vx_int32 winY = ch/grid_size;

#if 0
        imgMosaicObj->params.windows[idx].startX  = (winX * (in_width/grid_size));
        imgMosaicObj->params.windows[idx].startY  = (winY * (in_height/grid_size));
        imgMosaicObj->params.windows[idx].width   = in_width/grid_size;
        imgMosaicObj->params.windows[idx].height  = in_height/grid_size;
#else
        imgMosaicObj->params.windows[idx].startX  = (winX * (in_width));
        imgMosaicObj->params.windows[idx].startY  = (winY * (in_height));
        imgMosaicObj->params.windows[idx].width   = in_width;
        imgMosaicObj->params.windows[idx].height  = in_height;
#endif
        imgMosaicObj->params.windows[idx].input_select   = 0;
        imgMosaicObj->params.windows[idx].channel_select = ch;
        idx++;
    }

    imgMosaicObj->params.num_windows  = idx;

    /* Number of time to clear the output buffer before it gets reused */
    imgMosaicObj->params.clear_count  = APP_BUFFER_Q_DEPTH;
    imgMosaicObj->params.enable_overlay = 0;
}


static void app_update_param_set(AppObj *obj)
{

    vx_uint16 resized_width, resized_height;
    appIssGetResizeParams(obj->sensorObj.image_width, obj->sensorObj.image_height, DISPLAY_WIDTH, DISPLAY_HEIGHT, &resized_width, &resized_height);
    set_img_mosaic_params(&obj->imgMosaicObj, resized_width, resized_height, obj->sensorObj.num_cameras_enabled/1);
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


