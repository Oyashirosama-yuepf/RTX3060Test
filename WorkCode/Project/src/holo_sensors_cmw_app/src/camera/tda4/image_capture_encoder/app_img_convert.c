#include "app_img_convert.h"


vx_status app_init_img_convert(vx_context context, ImgConvertObj *imgConvertObj, SensorObj *sensorObj, vx_int32 bufq_depth)
{
  vx_status status = VX_SUCCESS;
  vx_image  img_nv12;
  vx_int32  i;
   
  imgConvertObj->input_width = sensorObj->image_width;
  imgConvertObj->input_height = sensorObj->image_height;
  imgConvertObj->num_inputs = sensorObj->num_cameras_enabled;
 
  img_nv12 = vxCreateImage(context,imgConvertObj->input_width,imgConvertObj->input_height,(vx_df_image)VX_DF_IMAGE_NV12);
  for(i = 0;i < bufq_depth; i++)
      imgConvertObj->output_arr[i] = vxCreateObjectArray(context, (vx_reference)img_nv12, imgConvertObj->num_inputs);
  vxReleaseImage(&img_nv12);

  return status;
}

void app_deinit_img_convert(ImgConvertObj *imgConvertObj, vx_int32 bufq_depth)
{
  vx_int32 q;

  for(q = 0; q < bufq_depth; q++)
  {
	vxReleaseObjectArray(&imgConvertObj->output_arr[q]);
  }
  return;
}

void app_delete_img_convert(ImgConvertObj *imgConvertObj)
{
  if(imgConvertObj->node != NULL)
  {
    vxReleaseNode(&imgConvertObj->node);
  }
  return;
}

vx_status app_create_graph_img_convert(vx_graph graph, ImgConvertObj *imgConvertObj, vx_object_array raw_image_arr, char *objName)
{
  vx_status status = VX_SUCCESS;
  vx_image img_nv12,sample_img;
  vx_bool replicate[] = { vx_true_e, vx_true_e};

  sample_img = (vx_image) vxGetObjectArrayItem(raw_image_arr,0);
  img_nv12 =  (vx_image) vxGetObjectArrayItem(imgConvertObj->output_arr[0],0);
  imgConvertObj->node = vxColorConvertNode(graph,sample_img,img_nv12);
  vxSetReferenceName((vx_reference)imgConvertObj->node,objName);
  vxSetNodeTarget(imgConvertObj->node, VX_TARGET_STRING, TIVX_TARGET_DSP2);
  vxReleaseImage(&sample_img);
  vxReleaseImage(&img_nv12);

  if(NUM_CAPT_CHANNELS == 4)
    vxReplicateNode(graph, imgConvertObj->node, replicate, 2);

  return (status);

}

