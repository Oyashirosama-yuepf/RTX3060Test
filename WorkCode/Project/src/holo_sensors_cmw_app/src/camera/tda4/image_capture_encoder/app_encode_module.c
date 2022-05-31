#include "app_encode_module.h"


vx_status app_init_encode(vx_context context, EncodeObj *encodeObj, char *objName)
{
	uint32_t max_bitstream_size;

	vx_status status = VX_SUCCESS;

	/* Create object for encode parameters */
	tivx_video_encoder_params_init(&(encodeObj->encode_params));
	encodeObj->configuration_obj = vxCreateUserDataObject(context,
			"tivx_video_encoder_params_t",
			sizeof(tivx_video_encoder_params_t),
			NULL);

	if (vxGetStatus((vx_reference)encodeObj->configuration_obj) != VX_SUCCESS)
	{
		APP_PRINTF("configuration_obj create failed\n");
		return VX_FAILURE;
	}

	/* Set bitstream format  */
	encodeObj->encode_params.bitstream_format = TIVX_BITSTREAM_FORMAT_H264;

	/* Copy object back onto main graph object ??? */
	vxCopyUserDataObject(encodeObj->configuration_obj, 0,
			sizeof(tivx_video_encoder_params_t),
			&(encodeObj->encode_params),
			VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);

	max_bitstream_size = ((uint32_t)(encodeObj->inWidth / 16)
			* (uint32_t)(encodeObj->inHeight / 16) * WORST_QP_SIZE)
	                    				  + ((encodeObj->inHeight >> 4) * CODED_BUFFER_INFO_SECTION_SIZE);

	APP_PRINTF("max bitstream size = %d\n",max_bitstream_size);
	encodeObj->bitstream_obj = vxCreateUserDataObject(context,
			"tivx_video_bitstream_t",
			sizeof(uint8_t) * max_bitstream_size,
			NULL);
	for(int i = 0; i < NUM_ENCODE_CHANNEL; i++)
	{
	   encodeObj->eof = 0;
	   encodeObj->out_fp = NULL;
	}
	return status;
}

void app_deinit_encode(EncodeObj *encodeObj)
{
	if(NULL != encodeObj->configuration_obj)
	{
		vxReleaseUserDataObject(&encodeObj->configuration_obj);
		APP_PRINTF("releasing encode configuration object done\n");
		encodeObj->configuration_obj = NULL;
	}

	if(NULL != encodeObj->bitstream_obj)
	{
		vxReleaseUserDataObject(&encodeObj->bitstream_obj);
		APP_PRINTF("releasing encode bitstream object done\n");
		encodeObj->bitstream_obj = NULL;
	}

	return;
}

void app_delete_encode(EncodeObj *encodeObj)
{
	if(encodeObj->node != NULL)
	{
		vxReleaseNode(&encodeObj->node);
	}
	if(encodeObj->kernel != NULL)
	{
		vxRemoveKernel(encodeObj->kernel);
	}
	return;
}

vx_status app_create_graph_encode(vx_graph graph, EncodeObj *encodeObj, vx_image output_image,vx_uint8 index)
{
	vx_status status = VX_SUCCESS;
	encodeObj->node = tivxVideoEncoderNode(graph,
			encodeObj->configuration_obj, /* Encode parameters          (0) */
			output_image,                 /* From Mosaic                (1) */
			encodeObj->bitstream_obj);    /* Bitstream to write to file (2) */
	APP_ASSERT_VALID_REF(encodeObj->node);

	vxSetNodeTarget(encodeObj->node, VX_TARGET_STRING, TIVX_TARGET_VENC1);

	vxSetReferenceName((vx_reference)encodeObj->node, "Encode_node");
	status = vxGetStatus((vx_reference)encodeObj->node);

	return (status);

}

vx_status writeEncodeOutput(EncodeObj *encodeObj)
{
	vx_status status;
	vx_map_id map_id;
	vx_size   bitstream_size;

	size_t num_read;
	uint8_t *bitstream;
	status = vxQueryUserDataObject(encodeObj->encoded_image,
			TIVX_USER_DATA_OBJECT_VALID_SIZE,
			&(bitstream_size), sizeof(vx_size));
	APP_ASSERT(status==VX_SUCCESS);

	status = vxMapUserDataObject(encodeObj->encoded_image, 0,
			bitstream_size,
			&map_id, (void*) &bitstream,
			VX_READ_ONLY, VX_MEMORY_TYPE_HOST, 0);
	APP_ASSERT(status==VX_SUCCESS);

	if (NULL != encodeObj->out_fp)
	{
		num_read = fwrite(bitstream, sizeof(uint8_t), bitstream_size, encodeObj->out_fp);
		if (bitstream_size != num_read)
		{
	        	APP_PRINTF("app_create_graph: encoder: %s: Wrote less than expected (%d < %d)!!!\n", encodeObj->output_file, (uint32_t)num_read, (uint32_t)(bitstream_size));
		}
	}
	else
	{
		APP_PRINTF("app_create_graph: encoder: %s: Output file not found!!!\n", encodeObj->output_file);
	}
	vxUnmapUserDataObject(encodeObj->encoded_image, map_id);

	return(status);
}


